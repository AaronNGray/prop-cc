//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <string>
#include <setjmp.h>
#include <io.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <AD/gc/gcconfig.h>  // system configuration
#include <AD/gc/cgc.h>       // Conservative garbage collector
#include <AD/gc/gcobject.h>  // garbage collectable objects
#include <AD/gc/gcheaps.h>   // the heap manager
#include <AD/gc/gcmacros.h>  // useful macros
#include <AD/gc/weakptr.h>   // weak pointers
#ifdef GC_USE_TIMER
#  ifndef _WIN32
#    include <sys/time.h>
#    include <sys/resource.h>
#  endif
#include <AD/gc/gctimer.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//  Some identifying information.
//////////////////////////////////////////////////////////////////////////////

// #define DEBUG_GC  // no debugging for production use
#define SANITY_CHECK // inexpensive checking (left in place for your assurance)
#ifdef DEBUG_GC
#   define SANITY_CHECK
#endif

//////////////////////////////////////////////////////////////////////////////
//  Import some types
//////////////////////////////////////////////////////////////////////////////

typedef HM::GCPageId   GCPageId;
typedef HM::PageStatus PageStatus;

//////////////////////////////////////////////////////////////////////////////
//  Method to locate the bottom of the stack.
//  We'll take care of both upward growing and downward growing stacks.
//////////////////////////////////////////////////////////////////////////////

static void** compute_stack_bottom( void** stack_mark1, Bool& downward_stack)
{
  void * stack_mark2[1];
  size_t stack_alignment = 0x1000000;
  if (stack_mark1 < stack_mark2)
  {
    // case a: stack grows upward.
    // We'll truncate the address downward.
    downward_stack = false;
    return (void**)((size_t)stack_mark1 & (stack_alignment-1));
  }
  else
  {
    // case b: stack grows downward.
    // We'll round the address upward.
    downward_stack = true;
    return (void**)(((size_t)stack_mark1 + stack_alignment - 1)
                    & ~(stack_alignment-1));
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to locate the top of the heap
//////////////////////////////////////////////////////////////////////////////

void CGC::get_heap_top()
{ // This heap top is tentative.
  // On Linux sometimes this points to addresses that hasn't been
  // mapped.
  heap_top = (void**)GC_GET_HEAP_TOP;

  // Try read from the end of this address.
  // If a seg fault occurs, we know it is not the real thing.
  // We'll adjust the heap top stuff in that case.
  // If we don't have to adjust then this is does nothing.
  verify_heap_top();
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to verify the heap top
//
//////////////////////////////////////////////////////////////////////////////

void CGC::verify_heap_top()
{
  void ** try_addr = (void **)((char*)GC_TRUNC_ADDR(heap_top) - GC_ALIGNMENT);
  if (is_debugging() && console)
  {
    (*console) << "[ GC" << id
    << ": checking heap top address " << (void*)try_addr
    << " ]\n" << std::flush;
  }

  void * dummy_unused_variable = *try_addr; // may trap here

  if (is_debugging() && console)
  {
    (*console) << "[ GC" << id
    << ": heap top address " << (void*)try_addr
    << " is ok ]\n" << std::flush;
  }
}


//////////////////////////////////////////////////////////////////////////////
//  Method to flush the register windows on the sparc
//////////////////////////////////////////////////////////////////////////////

#if 0
#ifdef sparc
asm ("	.seg \"text\"");
asm ("	.globl _flush_sparc_register_windows");
asm ("_flush_sparc_register_windows:");
asm ("	ta 3");
asm ("	mov %sp, %o0");
asm ("	retl");
asm ("	nop");   // delay slot
extern "C" void * flush_sparc_register_windows();
#endif
#endif
void CGC::flush_registers()
{
#if 0
#ifdef sparc
  flush_sparc_register_windows();
#endif
#endif
}

//////////////////////////////////////////////////////////////////////////////
//
//  Get the bottom heap address
//
//////////////////////////////////////////////////////////////////////////////

void * CGC::global_heap_bottom = 0;
void * CGC::get_heap_bottom()
{
  if (global_heap_bottom != 0)
    return global_heap_bottom;
  global_heap_bottom = (void*)GC_GET_HEAP_BOTTOM;
  void * static_data_end = (void*)GC_DATA_END;
  global_heap_bottom =
    get_address_limit(global_heap_bottom, static_data_end, -1);
  return global_heap_bottom;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Retrieve the limit address
//
//////////////////////////////////////////////////////////////////////////////

static volatile Bool segfault;
static void segfault_handler(int)
{
  segfault = true;
}

void * CGC::get_address_limit(void * start, void * limit, int dir)
{
  segfault = false;
#ifdef DEBUG_GC

  if (console)
    (*console) << "[ CGC::get_address_limit(" << start << ", " << limit
    << ")]\n";
#endif

  typedef void (*signal_handler)(int);
  signal_handler old_handler = signal(SIGSEGV, segfault_handler);
  void * addr = start;
  void * new_addr;
  if (dir > 0)
  {
    long dummy = 0;
    for (addr = start; addr < limit; addr = ((long *)addr) + dir)
    {
      dummy += *(long *)addr;
      if (segfault)
        break;
    }
  }
  else
  {
    long dummy = 0;
    for (addr = start; addr > limit; addr = ((long *)addr) + dir)
    {
      dummy += *(long *)addr;
      if (segfault)
        break;
    }
  }
  addr = ((long*)addr) - dir;
  signal(SIGSEGV, old_handler);
#ifdef DEBUG_GC

  if (console)
  {
    (*console) << "[ CGC::get_address_limit(" << start << ", " << limit
    << ") = " << addr << "]\n";
  }
#endif
  return addr;
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor.
//////////////////////////////////////////////////////////////////////////////

CGC::CGC()
{
  //
  // Determine the boundaries of the stack, heap, and static area.
  //
  void * stack_mark1[1];
  stack_bottom    = compute_stack_bottom(stack_mark1, is_downward_stack);
  stack_top       = stack_bottom;
  data_bottom     = (void**)GC_DATA_START;
  data_top        = (void**)GC_DATA_END;
  heap_bottom     = (void**)get_heap_bottom();
  heap_top        = heap_bottom;

  // Set the initial heap size and heap growth.
  // Be conservative and let the subclass override them if necessary
  initial_heap_size = 128 * 1024;
  min_heap_growth   = 256 * 1024;

  // Initialize the scanning queue
  scan_queue                     = 0;
  scan_limit_queue               = 0;
  scan_queue_size                = 0;
  number_of_pages_to_scan        = 0;

  initialization_message();
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

CGC::~CGC()
{
  delete [] scan_queue;
  cleanup_message();
}

//////////////////////////////////////////////////////////////////////////////
//  Methods for setting the initial heap size and amount of heap growth
//////////////////////////////////////////////////////////////////////////////

void CGC::set_initial_heap_size (size_t n)
{
  initial_heap_size = n;
}

void CGC::set_min_heap_growth   (size_t n)
{
  min_heap_growth = n;
}

//////////////////////////////////////////////////////////////////////////////
//  Method that returns the size of an allocated block
//////////////////////////////////////////////////////////////////////////////

size_t CGC::size(const void * obj) const
{
  if (HM::is_mapped((void*)obj) &&
      HM::get_object_map().is_marked((void*)obj))
  {
    return GC_OBJ_HEADER_LEN(GC_OBJ_HEADER(obj));
  }
  else
  {
    return 0;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for growing the scan queue
//////////////////////////////////////////////////////////////////////////////

void CGC::grow_scan_queue(size_t pages)
{
  if (scan_queue_size < pages)
  {
    delete [] scan_queue;
    scan_queue       = new size_t [2 * pages];
    scan_limit_queue = scan_queue + pages;
    scan_queue_size  = pages;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for printing an initialization message
//////////////////////////////////////////////////////////////////////////////

void CGC::initialization_message() const
{
  if (is_debugging() && console)
    (*console) << "[ GC" << id
    << ": initializing (page size = " << GC_PAGE_SIZE
    << ", alignment = " << GC_ALIGNMENT << ") ]\n" << std::flush;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for printing a cleanup message
//////////////////////////////////////////////////////////////////////////////

void CGC::cleanup_message() const
{
  if (is_debugging() && console)
    (*console) << "[ GC" << id << ": cleaning up. ]\n" << std::flush;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for printing a scanning message.
//////////////////////////////////////////////////////////////////////////////

void CGC::scanning_message(const char * area, void * start, void * stop) const
{
  if (is_debugging() && console)
  {
    (*console) << "[ GC" << id << ": scanning the " << area
    << " (" << start << " ... " << stop << ") "
    << ((Byte*)stop - (Byte*)start) << " bytes ]\n" << std::flush;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for performing weak pointer collection
//////////////////////////////////////////////////////////////////////////////

void CGC::do_weak_pointer_collection()
{
  if (! should_collect_weak_pointers)
    return;
  int size     = WeakPointerManager::size();
  int capacity = WeakPointerManager::capacity();
  if (size == 0)
    return;
  if ((verbosity_level & gc_notify_weak_pointer_collection) && console)
  {
    (*console) << "[ GC" << id << ": weakpointer collection ("
    << size << "/" << capacity << ") ..." << std::flush;
  }
  WeakPointerManager::scavenge_wp_table(this);
  int new_size     = WeakPointerManager::size();
  int new_capacity = WeakPointerManager::capacity();
  if ((verbosity_level & gc_notify_weak_pointer_collection) && console)
  {
    (*console) << " done (" << new_size << "/" << new_capacity
    << ") ]\n" << std::flush;
  }
}
