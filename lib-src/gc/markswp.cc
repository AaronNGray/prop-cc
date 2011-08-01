/////////////////////////////////////////////////////////////////////////////
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

#include <assert.h>
#include <iostream>
#include <strstream>
#include <stdlib.h>
#include <string>
#include <setjmp.h>
#include <io.h>
#include <sys/types.h>
#include <AD/gc/gcconfig.h>    // system configuration
#include <AD/gc/markswp.h>     // Marksweep garbage collector
#include <AD/gc/gcobject.h>    // garbage collectable objects
#include <AD/gc/gcheaps.h>     // the heap manager
#include <AD/gc/gcmacros.h>    // useful macros
#include <AD/gc/gctimer.h>


//////////////////////////////////////////////////////////////////////////////
//  Implementation note: small objects are allocated from a set of
//  free lists partitioned by sizes.  We also keep a block of consecutive
//  memory for allocation purposes.  When we need a small object, the
//  appropriate free list is checked first, then if the block of memory
//  is used.   If both are empty we'll try to perform garbage collection
//  and/or heap expansion.  No attempt is made to coalesce adjacent
//  free memory together, so fragmentation may be a problem in
//  degenerate cases.
//
//  Large objects are allocated from the heap manager directly.  They
//  are rounded up to the page size.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Some identifying information.
//////////////////////////////////////////////////////////////////////////////

// #define DEBUG_GC  // no debugging for production use
#define ALGORITHM "Conservative mark/sweep"
#define VERSION   "0.2 (Feb 7th, 1995)"

//////////////////////////////////////////////////////////////////////////////
//  Import some types
//////////////////////////////////////////////////////////////////////////////

typedef HM::GCPageId   GCPageId;
typedef HM::PageStatus PageStatus;

//////////////////////////////////////////////////////////////////////////////
//  Method that returns a name for this class
//////////////////////////////////////////////////////////////////////////////

const char * MarkSweepGC::my_name() const
{
  return "MarkSweepGC";
}

//////////////////////////////////////////////////////////////////////////////
//  Small objects are allocated and deallocated using the free
//  lists.  Large objects are allocated by just calling the heap manager.
//////////////////////////////////////////////////////////////////////////////

#define FREE_LIST_SIZE         43
#define MAX_SMALL_OBJECT_SIZE  (512 * GC_ALIGNMENT)

//////////////////////////////////////////////////////////////////////////////
//  Method to select the freelist to go.
//////////////////////////////////////////////////////////////////////////////

inline int LEN_TO_FREELIST_INDEX(size_t len)
{
  // Bytes 0 ... 128     -> Indices 0 ...  15
  if (len <= 16 * GC_ALIGNMENT)
    return (len-1)/GC_ALIGNMENT;
  // Bytes 129 ... 1024   -> Indices 16 ... 29
  if (len <= 128 * GC_ALIGNMENT)
    return 16 + (len-16* GC_ALIGNMENT-1)/GC_ALIGNMENT/8;
  // Bytes 1025 ... 4096 -> Indices 30 ... 41
  return 30 + (len-128*GC_ALIGNMENT-1)/GC_ALIGNMENT/32;
}

//////////////////////////////////////////////////////////////////////////////
//  Index to length of cell.
//////////////////////////////////////////////////////////////////////////////

static size_t index_to_len[FREE_LIST_SIZE];

//////////////////////////////////////////////////////////////////////////////
//  Constructor.
//////////////////////////////////////////////////////////////////////////////

MarkSweepGC::MarkSweepGC()
{
  //  Initialize the index_to_len table
  {  int i;
    for (i = 0;  i < 16; i++)
      index_to_len[i] = (i+1) * GC_ALIGNMENT;
    for (i = 16; i < 30; i++)
      index_to_len[i] = (i-15) * GC_ALIGNMENT * 8 + 16 * GC_ALIGNMENT;
    for (i = 30; i < 42; i++)
      index_to_len[i] = (i-29) * GC_ALIGNMENT * 32 + 128 * GC_ALIGNMENT;
    index_to_len[42] = MAX_SMALL_OBJECT_SIZE;

    for (i = 0; i < 42; i++)
    {
      assert(LEN_TO_FREELIST_INDEX(index_to_len[i]) == i);
      assert(LEN_TO_FREELIST_INDEX(index_to_len[i]+1) == i+1);
    }
  }

  //  Initialize the statistics
  stat.algorithm = ALGORITHM;
  stat.version   = VERSION;
  reset_statistics(stat);

  //  Setup the limits
  heap_size         = 0;
  heap_used         = 0;
  heap_free         = 0;
  heap_pointer      = 0;
  heap_limit        = 0;
  initial_heap_size = 128 * 1024;
  min_heap_growth   = 256 * 1024;

  //  Expand heap if this ratio is exceeded after collection.
  gc_ratio = 50;

  //  Setup the free lists for small objects
  free_list_size = FREE_LIST_SIZE;
  free_lists     = new FreeList * [ FREE_LIST_SIZE ];
  for (size_t i = 0; i < free_list_size; i++)
    free_lists[i] = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

MarkSweepGC::~MarkSweepGC()
{
  clear();
  delete [] free_lists;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to release all the memory within the collector
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::clear()
{
  // Return all the pages back to the heap manager
  HM::release_all_pages(this);

  // Reset the free lists
  for (int i = 0; i < FREE_LIST_SIZE; i++)
    free_lists[i] = 0;

  heap_size       = 0;
  heap_used       = 0;
  heap_free       = 0;
  heap_pointer    = 0;
  heap_limit      = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Method that compute the minimal amount of heap expansion
// that should be done.
//////////////////////////////////////////////////////////////////////////////

size_t MarkSweepGC::min_growth()
{
  return min_heap_growth;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to allocate a new object of a given size
//////////////////////////////////////////////////////////////////////////////

void * MarkSweepGC::m_alloc( size_t n)
{
  register size_t bytes = GC_ROUNDUP_SIZE(n + sizeof(GCHeader));

  if (bytes <= MAX_SMALL_OBJECT_SIZE)
  {
    //
    // Small objects are handled by the free lists.
    //
    int    index = LEN_TO_FREELIST_INDEX(bytes);
    size_t len   = index_to_len[index];
    for (;;)
    {
      register FreeList * cell;
      if (heap_pointer + len < heap_limit)
      {
        //
        //  Try to use the new memory block first
        //
        register void * new_obj = GC_OBJ_OBJECT_ADDR(heap_pointer);
        GC_OBJ_SET_HEADER(new_obj, len);
        HM::get_object_map().mark(new_obj);
        heap_pointer += len;
        heap_used    += len;
        return new_obj;
      }
      else if ((cell = free_lists[index]))
      {
        //
        //  Then try free lists
        //
        free_lists[index] = cell->next;
        register void * new_obj = cell;
        HM::get_object_map().mark(new_obj);
        memset(new_obj, 0, n);
        heap_used += len;
        return new_obj;
      }
      else
      {
        if (heap_size > 0 && HM::bytes_free() <= len)
        {
          //
          // Try garbage collection first
          //
          collect();
          //
          // Expand heap if gc_ratio is reached
          //
          if (heap_used >= heap_size * gc_ratio / 100)
            grow_heap(bytes);
        }
        else
        {
          //
          // Expand heap as a last resort.
          //
          grow_heap(bytes);
        }
      }
    }
  }
  else
  {
    //
    // Large objects are allocated by calling the heap manager directly.
    // Hopefully most of the objects are small.
    //
    size_t bytes_gotten;
    bytes += GC_ALIGNMENT;
    void * new_memory = HM::allocate_pages(this, bytes, bytes, bytes_gotten);
    if (new_memory == 0)
    {
      std::cerr << "[ GC" << id << ": unable to allocate "
      << bytes << " bytes! ]\n" << std::flush;
      exit (1);
    }
    heap_size += bytes_gotten;
    heap_used += bytes_gotten;
    register void * new_obj = (Byte*)new_memory + GC_ALIGNMENT;
    GC_OBJ_SET_HEADER(new_obj, bytes_gotten);
    HM::get_object_map().mark(new_obj);
    return new_obj;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to deallocate an object manually.
//  Note: this method tries to catch errors involving deallocation.
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::free(void* obj)
{
  if (! GC_IS_A_POINTER(obj))
    return;
  if ( HM::is_mapped(obj)                &&
       HM::page_gc(obj) == id            &&
       HM::get_object_map().is_marked(obj)
     )
  {
    // clean up properly
    HM::get_object_map().unmark(obj);
    size_t obj_len = GC_OBJ_HEADER_LEN(GC_OBJ_HEADER(obj));
    memset(GC_OBJ_HEADER_ADDR(obj), 0, obj_len);

    // return object to free list
    // ...
    if (obj_len <= MAX_SMALL_OBJECT_SIZE)
    {
      int index = LEN_TO_FREELIST_INDEX(obj_len);
      ((FreeList*)obj)->next = free_lists[index];
      free_lists[index]      = (FreeList*)obj;
      heap_used             -= obj_len;
    }
    else
    {
      HM::deallocate_pages
      (this, GC_PAGE_ID(obj), (obj_len + GC_PAGE_SIZE - 1)/GC_PAGE_SIZE);
      heap_size -= obj_len;
      heap_used -= obj_len;
    }
  }
  else
  {
    std::cerr << "[ GC" << id << ": trying to free unallocated object at "
    << obj << " ]\n";
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for expanding the heap.
//  We try to expand the heap only if the number of bytes requested
//  is not immediately available.
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::grow_heap( size_t bytes)
{
  size_t bytes_gotten;
  void * new_memory =
    HM::allocate_pages
    ( this, bytes,
      (heap_size == 0 ? initial_heap_size : min_heap_growth),
      bytes_gotten);
  if (new_memory == 0)
  {
    std::cerr << "[ GC" << id << ": unable to allocate " << bytes << " bytes! ]\n"
              << std::flush;
    exit (1);
  }

  // Update statistics
  heap_size += bytes_gotten;
  stat.number_of_heap_expansions++;

  // Add memory into the new memory queue.
  heap_pointer = (Byte*)new_memory + GC_ALIGNMENT - sizeof(GCHeader);
  heap_limit   = (Byte*)new_memory + bytes_gotten;

  heap_expansion_message();
}

//////////////////////////////////////////////////////////////////////////////
//  Method for tracing an object pointer.
//  This marks objects currently in the heap.
//////////////////////////////////////////////////////////////////////////////

GCObject * MarkSweepGC::trace( GCObject* ptr)
{
  if (! GC_IS_A_POINTER(ptr))
    return ptr;

  // Trace out of heap objects if necessary
  if (! HM::is_mapped(ptr) || HM::page_gc(ptr) != id)
  {
#ifdef GC_HAS_CROSS_HEAP_POINTERS
#ifdef DEBUG_GC
    assert(HM::traversed_map.is_within_bounds(ptr));
#endif

    if (! HM::traversed_map.is_marked(ptr))
    {
      HM::traversed_map.mark(ptr);
      ptr->trace(this);
    }
#endif
    return ptr;
  }

  // Get the starting address of the object
  void * obj_ptr = HM::get_object_map().starting_addr(ptr);

  // If it is already marked live just return.
  if (HM::get_live_map().is_marked(obj_ptr))
    return ptr;

  // Otherwise, mark the current object as live and trace all subobjects.
  HM::get_live_map().mark(obj_ptr);
  ptr->trace(this);
  return ptr;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for starting the garbage collection
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::collect( int level)
{
  do_collect( level);
}

//////////////////////////////////////////////////////////////////////////////
//  Method that performs the actual garbage collection
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::do_collect( int /*level*/)
{
  ///////////////////////////////////////////////////////////////////////////
  //  Flush the registers onto the stack; setup the stack and heap limits.
  ///////////////////////////////////////////////////////////////////////////
  jmp_buf reg_roots; // flushed registers
  flush_registers();
  // if (_setjmp(reg_roots)) _longjmp(reg_roots,1);
  if (setjmp(reg_roots))
    longjmp(reg_roots,1);
  if (is_downward_stack)
  {
    stack_top = (void**)((Byte*)reg_roots);
  }
  else
  {
    stack_top = (void**)((Byte*)reg_roots + sizeof(reg_roots));
  }
  get_heap_top();

  ///////////////////////////////////////////////////////////////////////////
  //  Print a message
  ///////////////////////////////////////////////////////////////////////////
  start_collection_message();

  ///////////////////////////////////////////////////////////////////////////
  //  Get start time
  ///////////////////////////////////////////////////////////////////////////
#ifdef GC_USE_TIMER

  GCTimer user_time_at_start;
  GCTimer system_time_at_start;
  user_time_at_start.get_user_time();
  system_time_at_start.get_system_time();
#endif

  ///////////////////////////////////////////////////////////////////////////
  //  Mark the unused part of the heap space new so that it will be
  //  skipped during root scanning.
  ///////////////////////////////////////////////////////////////////////////
  HM::mark_space(GC_ROUNDUP_PAGE_ADDR(heap_pointer), heap_limit,
                 HM::newly_allocated);

#ifdef GC_HAS_CROSS_HEAP_POINTERS

  HM::traversed_map.grow(HM::lo_mapped(), HM::hi_mapped());
#endif

  ///////////////////////////////////////////////////////////////////////////
  //  Mark phase:
  ///////////////////////////////////////////////////////////////////////////
  scan_stack_area  ();
  scan_static_area ();
  scan_heap_area   ();
  scan_user_roots  ();

  ///////////////////////////////////////////////////////////////////////////
  // Scavenge any and all weakpointers.
  ///////////////////////////////////////////////////////////////////////////
  do_weak_pointer_collection();

  ///////////////////////////////////////////////////////////////////////////
  //  Sweep phase:
  //     Now scan over all the pages owned by ourselves and
  //  reconstruct the free list.
  ///////////////////////////////////////////////////////////////////////////
  sweep_pages      ();  // reconstruct free list and reset bitmaps

  ///////////////////////////////////////////////////////////////////////////
  //  Mark the unused part of the heap space as the from-space again.
  ///////////////////////////////////////////////////////////////////////////
  HM::mark_space(GC_ROUNDUP_PAGE_ADDR(heap_pointer), heap_limit,
                 HM::from_space);

  ///////////////////////////////////////////////////////////////////////////
  //  Update statistics
  ///////////////////////////////////////////////////////////////////////////
  stat.number_of_collections++;

  ///////////////////////////////////////////////////////////////////////////
  //  Compute time spent
  ///////////////////////////////////////////////////////////////////////////
#ifdef GC_USE_TIMER

  GCTimer user_time_at_end;
  GCTimer system_time_at_end;
  user_time_at_end.get_user_time();
  system_time_at_end.get_system_time();
  stat.gc_user_time         = user_time_at_end - user_time_at_start;
  stat.gc_system_time       = system_time_at_end - system_time_at_start;
  stat.total_gc_user_time   += stat.gc_user_time;
  stat.total_gc_system_time += stat.gc_system_time;
#endif
  ///////////////////////////////////////////////////////////////////////////
  //  Print a message;
  ///////////////////////////////////////////////////////////////////////////
  end_collection_message();

  ///////////////////////////////////////////////////////////////////////////
  //  Clean up
  ///////////////////////////////////////////////////////////////////////////
#ifdef GC_HAS_CROSS_HEAP_POINTERS

  HM::traversed_map.clear();
#endif
}

//////////////////////////////////////////////////////////////////////////////
//  Method for scanning a consecutive block of memory for roots.
//////////////////////////////////////////////////////////////////////////////

inline void MarkSweepGC::scan_for_roots( void** start, void** stop)
{
  // Scan consecutively.
  // Caution: addresses between start and stop (not including stop)
  // must be mapped by the OS.
  for (register void ** P = (void**)GC_TRUNC_ADDR(start); P < stop; P++)
  {
    register void * ptr = *P;

    // Try to interpret each cell as a pointer and see if it
    // falls within any pages of this collectable heap.
    if (! HM::is_mapped(ptr))
      continue;
    if (HM::page_gc(ptr) != id)
      continue;

    // If so, locate the starting address (the pointer may be
    // an interior pointer) and trace the object.
    Byte * obj = (Byte*)HM::get_object_map().starting_addr(ptr);
    if (obj == 0)
      continue;
    if (HM::page_gc(obj) != id)
      continue;

    // Get the header of the object.
    // If it is a forwarded header, then it is not really a live object
    // at all, but one left over from previous collection phase that
    // has not been unmarked.   The reason why this may happen is that
    // we are lazy only unmark objects one page at a time.  So objects
    // that falls half way between promoted and unpromoted and that
    // are actually moved will not have their live bit reset.
    // We'll reset the object now and continue.
    GCHeader header = GC_OBJ_HEADER(obj);

    //  Now check whether the pointer actually lies within the
    //  boundary of the object.
    Byte * limit = obj + GC_OBJ_HEADER_LEN(header) - sizeof(GCHeader);

    if ((Byte*)ptr >= limit)
      continue;  // Nope.

    // Finally, we've found a object.  Trace and mark it.

    if (HM::get_live_map().is_marked(obj))
      continue;
    HM::get_live_map().mark(obj);      // mark it as live
    ((GCObject*)obj)->trace(this);     // trace it
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for scanning the stack area
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::scan_stack_area()
{
  if (is_downward_stack)
  {
    // stack grows to lower addresses
    scanning_message("registers and stack", stack_top, stack_bottom);
    scan_for_roots (stack_top,  stack_bottom);
  }
  else
  {
    scanning_message("registers and stack", stack_bottom, stack_top);
    scan_for_roots (stack_bottom, stack_top);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for scanning the static area.
//  We'll have to take into account of all the static data used
//  by the heap manager.
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::scan_static_area()
{
  scanning_message("static data area", data_bottom, data_top);
  size_t n;
  register const HM::AddrRange * blacklisted = HM::blacklisted_data(n);
  register size_t i = 0;
  register void ** start = data_bottom;
  register void ** stop  = data_top;
  for (start = data_bottom; start < data_top; start = stop)
  {
    while (i < n)
    {
      if (start > (void**)blacklisted[i].stop)
      {
        i++;
      }
      else if (start >= (void**)blacklisted[i].start)
      {
        start = (void**)blacklisted[i].stop;
        i++;
      }
      else
        break;
    }
    if (i < n)
      stop = (void**)blacklisted[i].start;
    else
      stop = data_top;
    if (start < stop)
      scan_for_roots (start, stop);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for scanning the heap area
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::scan_heap_area()
{
  scanning_message("non-collectable heap", heap_bottom, heap_top);

  // Scan consecutively.
  // Caution: addresses between start and stop (not including stop)
  // must be mapped by the OS.

  //
  // Scan all pages in the user heap that are NOT owned by this heap.
  // We'll do it one page at a time for now.
  //
  register void ** P, ** page_limit;
  for (P = heap_bottom; P < heap_top; P = page_limit)
  {
    page_limit = (void**)GC_TRUNC_PAGE_ADDR((Byte*)P + GC_PAGE_SIZE);
    if (page_limit > heap_top)
      page_limit = heap_top;

    // Check to make sure that the address is not been currently
    // used by us or allocated but not used.
    register GCPageId page_id = GC_PAGE_ID(P);

    if (HM::is_tracked(P))
    {
      switch (HM::page_status(page_id))
      {
        // not allocated page will be scanned
      case HM::not_allocated:
        break;

        // blacklisted pages will be skipped
      case HM::blacklisted:
        continue;

        // This page has been allocated... check some more....
      case HM::from_space:
        {
          register GC_ID the_id = HM::page_gc(page_id);
          // unused pages will be skipped.
          if (the_id == 0)
            continue;

          // pages within this heap will be skipped.
          if (the_id == id)
            continue;

          // allocated pages on other heaps will be scanned.
        }
        break;

        // case HM::to_space:          continue;
        // case HM::newly_allocated:   continue;

        // promoted pages and newly allocated pages will be skipped.
      default:
        continue;
      }
    }

    // The rest of the stuff are scanned
    scan_for_roots(P, page_limit);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to sweep pages in the heap and reconstruct the free list.
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::sweep_pages()
{
  foreach_page_owned_by_collector(p, this)
  {
    if (HM::page_status(p) != HM::from_space)
      continue;
    register Byte * page_start = (Byte*)GC_PAGE_ADDR(p);
    register Byte * page_addr  = page_start;
    register Byte * page_limit = page_addr + GC_PAGE_SIZE;
    while (page_addr < page_limit)
    {
      if (HM::get_object_map().is_marked(page_addr))
      {
        if (! HM::get_live_map().is_marked(page_addr))
        {
          // Finalize the dying object.
          HM::get_object_map().unmark(page_addr);
          if (should_finalize)
            ((GCObject*)page_addr)->~GCObject();

          // Now reclaim the dying object.
          size_t obj_len = GC_OBJ_HEADER_LEN(GC_OBJ_HEADER(page_addr));
          if (obj_len <= MAX_SMALL_OBJECT_SIZE)
          {
            int index = LEN_TO_FREELIST_INDEX(obj_len);
#ifdef DEBUG_GC
            // clear freed storage to catch bugs.
            memset(page_addr, 0, obj_len - sizeof(GCHeader));
#endif

            ((FreeList*)page_addr)->next = free_lists[index];
            free_lists[index]            = (FreeList*)page_addr;
            heap_used                   -= obj_len;
          }
          else
          {
            HM::deallocate_pages
            (this, GC_PAGE_ID(page_addr),
             (obj_len + GC_PAGE_SIZE - 1) / GC_PAGE_SIZE);
            heap_size -= obj_len;
            heap_used -= obj_len;
          }
          page_addr += obj_len;
        }
        else
        {
          page_addr += GC_OBJ_HEADER_LEN(GC_OBJ_HEADER(page_addr));
        }
      }
      else
      {
        page_addr += GC_ALIGNMENT;
      }
    }
    // Reset bitmap
    HM::get_live_map().clear (page_start, page_limit);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Accounting method.
//////////////////////////////////////////////////////////////////////////////

MarkSweepGC::Statistics MarkSweepGC::statistics()
{
  stat.bytes_used    = heap_used;
  stat.bytes_free    = heap_size - heap_used;
  stat.bytes_managed = heap_size;
  return stat;
}

//////////////////////////////////////////////////////////////////////////////
//  Heap expansion message
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::heap_expansion_message()
{
  if ((verbosity_level & gc_notify_heap_expansion) && console)
  {
    (*console) << "[ GC" << id << ": increasing heap... "
    << heap_used << '/'
    << (heap_size + HM::bytes_free()) << " ]\n";
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Start collection message
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::start_collection_message()
{
  if (is_verbose() && console)
  {
    (*console) << "[ GC" << id << ": collecting... "
    << heap_used << '/'
    << (heap_size + HM::bytes_free()) << " ]\n";
  }
}

//////////////////////////////////////////////////////////////////////////////
//  End collection message
//////////////////////////////////////////////////////////////////////////////

void MarkSweepGC::end_collection_message()
{
  if (is_verbose() && console)
  {
    (*console) << "[ GC" << id << ": done... "
    << heap_used << '/'
    << (heap_size + HM::bytes_free()) << " ]\n";
  }
#ifdef GC_USE_TIMER
  if ((verbosity_level & gc_print_collection_time) && console)
  {
    (*console) << "[ user time: " << stat.gc_user_time
    << " system time: " << stat.gc_system_time << " ]\n";
  }
#endif
}
