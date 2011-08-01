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
#include <AD/gc/gcconfig.h>  // system configuration
#include <AD/gc/bgc.h>       // Bartlett's garbage collector
#include <AD/gc/gcobject.h>  // garbage collectable objects
#include <AD/gc/gcheaps.h>   // the heap manager
#include <AD/gc/gcmacros.h>  // useful macros
#include <AD/gc/weakptr.h>   // weak pointers
#include <AD/gc/gctimer.h>

//////////////////////////////////////////////////////////////////////////////
//  Some identifying information.
//////////////////////////////////////////////////////////////////////////////

// #define DEBUG_GC  // no debugging for production use
#define SANITY_CHECK // inexpensive checking (left in place for your assurance)
#define ALGORITHM "Mostly copying with blacklisting"
#define VERSION   "0.5 (Feb 11th, 1995)"

#ifdef DEBUG_GC
#   define SANITY_CHECK
#endif

//////////////////////////////////////////////////////////////////////////////
//  Import some types
//////////////////////////////////////////////////////////////////////////////

typedef HM::GCPageId   GCPageId;
typedef HM::PageStatus PageStatus;

//////////////////////////////////////////////////////////////////////////////
//  Method that returns a name for this class
//////////////////////////////////////////////////////////////////////////////

const char * BGC::my_name() const
{
  return "BGC";
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor.
//////////////////////////////////////////////////////////////////////////////

BGC::BGC()
{
  // Perform initialization steps:
  heap_pointer                   = 0;
  heap_limit                     = 0;
  gc_limit                       = 0;
  phase                          = mutation_phase;
  heap_used                      = 0;
  heap_size                      = 0;
  initial_heap_size              = 128 * 1024;
  min_heap_growth                = 512 * 1024;
  should_collect                 = false;

  stat.algorithm                 = ALGORITHM;
  stat.version                   = VERSION;
  reset_statistics(stat);
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

BGC::~BGC()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
//  Method that releases all the memory within the collector.
//  The collector is now in a clean slate (though the statistics are
//  not reset).  Use with caution!
//////////////////////////////////////////////////////////////////////////////

void BGC::clear()
{
  heap_pointer = 0;
  heap_limit   = 0;
  gc_limit     = 0;
  heap_used    = 0;
  heap_size    = 0;
  HM::release_all_pages(this);
}

//////////////////////////////////////////////////////////////////////////////
// Method that compute the minimal amount of heap expansion
// that should be done.
//////////////////////////////////////////////////////////////////////////////

size_t BGC::min_growth()
{
  return heap_size == 0 ? initial_heap_size : min_heap_growth;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to allocate a new object of a given size
//////////////////////////////////////////////////////////////////////////////

void * BGC::m_alloc( size_t n)
{  // round up the size
  size_t bytes = GC_ROUNDUP_SIZE(n + sizeof(GCHeader));

  // if we have enough space in current fragment, then use it.
  if (heap_pointer + bytes > gc_limit)
  {
    // No more space left, we'll try to get some more from the
    // the heap manager and/or garbage collect.

    //
    // Try garbage collection first if the gc_ratio is reached.
    //
    if (should_collect)
      collect();

    //
    // Now try to expand the heap if there is still a need to.
    //
    if (heap_pointer + bytes > gc_limit)
      grow_heap (bytes);
  }

  // Get new storage for object.
  // Stamp the starting address into the bitmap.

  GCObject * new_obj = GC_OBJ_OBJECT_ADDR(heap_pointer);
  GC_OBJ_SET_HEADER(new_obj, bytes);
  heap_pointer += bytes;
  HM::object_map.mark(new_obj);
  return new_obj;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to deallocate an object manually.
//  Note: this method tries to catch errors involving deallocation.
//////////////////////////////////////////////////////////////////////////////

void BGC::free( void * obj)
{
  // Ignores all requests that do not lie on our heap space
  if (! GC_IS_A_POINTER(obj))
    return;
  if (HM::is_mapped(obj)     &&
      HM::page_gc(obj) == id &&
      HM::get_object_map().is_marked(obj))
  {
    // Just unmark the object.  The space is not really
    // reclaimed at this point; instead it will be reclaimed
    // at the next collection.
    HM::object_map.unmark(obj);
  }
  else
  {

    // Hold on, Pedro!  The object doesn't seem to exist!
    std::cerr << "[ GC" << id
    << ": application tries to free non-existent object at "
    << (void*)obj << " ]\n" << std::flush;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for expanding the heap.
//  We try to expand the heap only if the number of bytes requested
//  is not immediately available.
//////////////////////////////////////////////////////////////////////////////

void BGC::grow_heap( size_t bytes)
{
  size_t old_total = heap_size + HM::bytes_free();
  size_t wanted    = bytes + sizeof(GCHeader);
  size_t growth;
  Byte * storage =
    (Byte*)HM::allocate_pages
    ( this, wanted,
      (heap_size == 0 ? initial_heap_size : min_heap_growth),
      growth,
      phase == copying_phase ? HM::newly_allocated :
      HM::from_space
    );

  if (storage == 0)
  {
    // Growth failed!
    std::cerr << "[ GC" << id << ": Out of memory!  Can't allocate "
    << bytes << " bytes from system. ]\n" << std::flush;
    exit (1);
  }

  heap_pointer = storage + GC_ALIGNMENT - sizeof(GCHeader);
  heap_limit   = storage + growth;
  heap_start   = heap_pointer;
  heap_size   += heap_limit - heap_pointer;
  heap_used    = heap_size - (heap_limit - heap_pointer);
  size_t new_total = heap_size + HM::bytes_free();
  gc_limit     = storage + new_total * gc_ratio / 100 - heap_used;
  should_collect = gc_limit <= heap_limit;
  if (gc_limit > heap_limit)
    gc_limit = heap_limit;
  if (heap_pointer + wanted > gc_limit)
    gc_limit = heap_limit;
  if (new_total > old_total)
  {
    stat.number_of_heap_expansions++;
    heap_growth_message(heap_size, growth);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for tracing an object pointer.
//  Tracing moves object currently in the heap into the to-space.
//////////////////////////////////////////////////////////////////////////////

GCObject * BGC::trace( GCObject * ptr)
{
#ifdef GC_HAS_CROSS_HEAP_POINTERS
  // make sure it is a pointer first.
  // Since Prop uses small unmapped addresses to represent
  // unit functors it is a good idea to check first if we allow
  // cross heap pointer lest these things get mistaken for the real thing.
  if (! GC_IS_A_POINTER(ptr))
    return ptr;
#endif

  // Objects not within the current collector heap are skipped.
  if (! IS_WITHIN_BOUNDS(ptr) || ! IS_USED_ADDR(ptr,id))
  {
#ifdef GC_HAS_CROSS_HEAP_POINTERS
    // We'll grow the traversed map incrementally
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

  // Get starting address of object.
  void * obj_ptr = HM::object_map.starting_addr(ptr);

  // If it is a new object then just return, since it must already
  // have been properly traced.
  if (IS_NEW_ADDR(obj_ptr))
    return ptr;

#ifdef DEBUG_GC

  if (ptr != obj_ptr)
    std::cerr << "[ Warning: pointer is at " << (void*)ptr << " but object is "
    << (void*)obj_ptr << " ]\n" << flush;
#endif

  // Get header of object
  GCHeader header = GC_OBJ_HEADER(obj_ptr);

  // If it is a forwarded object then set the forwarding address;
  // then exit.
  if (GC_OBJ_IS_FORWARDED(header))
  {
    return (GCObject*)((Byte*)GC_OBJ_FORWARD_ADDR(header) +
                       ((Byte*)ptr - (Byte*)obj_ptr));
  }

  // If the object is marked live then it cannot be moved, so just return
  if (HM::live_map.is_marked(obj_ptr))
    return ptr;

  // Okay, seems like we'll have to copy this object.
  size_t size = GC_OBJ_HEADER_LEN(header);
  if (heap_pointer + size > heap_limit)
  {
    bytes_copied += heap_pointer - heap_start;
    grow_heap (size);
    enqueue_pages_to_scan(heap_pointer, heap_limit);
  }

  // Mark new object
  GCObject * new_obj = GC_OBJ_OBJECT_ADDR(heap_pointer);
  HM::object_map.mark(new_obj);

  // Copy object
  int * src  = (int*)GC_OBJ_HEADER_ADDR(obj_ptr);
  int * dest = (int*)heap_pointer;
  size /= sizeof(int);
  while (size-- > 0)
  {
    *dest++ = *src++;
  }
  heap_pointer = (Byte*)dest;

  // Leave a forwarding address in the header of the old object.
  GC_OBJ_SET_FORWARD(obj_ptr, new_obj);

  // Update pointer
  return (GCObject*)((Byte*)new_obj + ((Byte*)ptr - (Byte*)obj_ptr));
}

//////////////////////////////////////////////////////////////////////////////
//  Method for starting the garbage collection
//////////////////////////////////////////////////////////////////////////////

void BGC::collect( int level)
{  // if we are already performing collection don't start
  // it up again until it is finished.
  if (phase == mutation_phase && heap_size > 0)
    do_collect (level);
}

//////////////////////////////////////////////////////////////////////////////
//  Method for doing the actual garbage collection
//////////////////////////////////////////////////////////////////////////////

void BGC::do_collect(int /* level */)
{
  ///////////////////////////////////////////////////////////////////////////
  // This will hold all the registers
  ///////////////////////////////////////////////////////////////////////////
  jmp_buf reg_roots;

  ///////////////////////////////////////////////////////////////////////////
  // Flush registers into the jmp_buf, which'll become part of the
  // stack to scan.
  ///////////////////////////////////////////////////////////////////////////
  flush_registers();
  // if (_setjmp(reg_roots) == 0) _longjmp(reg_roots,1);
  if (setjmp(reg_roots) == 0)
    longjmp(reg_roots,1);

  ///////////////////////////////////////////////////////////////////////////
  // Setup various limits for scanning
  ///////////////////////////////////////////////////////////////////////////
  if (is_downward_stack)
  {
    stack_top    = (void**)((Byte*)reg_roots);
  }
  else
  {
    stack_top    = (void**)((Byte*)reg_roots + sizeof(reg_roots));
  }

  ///////////////////////////////////////////////////////////////////////////
  // Move the heap pointer to the next page for the to-space.
  // Compute the amount of heap used.
  // Mark the new area as newly allocated.
  ///////////////////////////////////////////////////////////////////////////
  heap_pointer = (Byte*)GC_ROUNDUP_PAGE_ADDR(heap_pointer)
                 + GC_ALIGNMENT - sizeof(GCHeader);
  heap_used    = heap_size - (heap_limit - heap_pointer)
                 + (GC_ALIGNMENT - sizeof(GCHeader));
  heap_start   = heap_pointer;
  HM::mark_space(heap_pointer, heap_limit, HM::newly_allocated);
  gc_limit     = heap_limit;

  ///////////////////////////////////////////////////////////////////////////
  // Setup various statistics.
  ///////////////////////////////////////////////////////////////////////////
  bytes_copied     = 0;
  stat.number_of_collections++;

  ///////////////////////////////////////////////////////////////////////////
  // Set up the timer
  ///////////////////////////////////////////////////////////////////////////
#ifdef GC_USE_TIMER

  GCTimer user_time_at_start;
  GCTimer system_time_at_start;
  user_time_at_start.get_user_time();
  system_time_at_start.get_system_time();
#endif

  ///////////////////////////////////////////////////////////////////////////
  // Print the annoying garbage collection message
  ///////////////////////////////////////////////////////////////////////////
  start_collection_message();

  ///////////////////////////////////////////////////////////////////////////
  // Setup the new scanning queue if necessary.
  // The 4 below is just some slack;
  ///////////////////////////////////////////////////////////////////////////
  size_t max_pages = 2 * heap_used / GC_PAGE_SIZE + 4;
  clear_scan_queue();
  grow_scan_queue(max_pages);

  ///////////////////////////////////////////////////////////////////////////
  // Locate and mark all the roots in different areas of the memory
  ///////////////////////////////////////////////////////////////////////////
  phase = marking_phase;
  scan_stack_area  ();   // scan the stack area
  scan_static_area ();   // scan the static area
  get_heap_top();        // locate the start of the heap.
  scan_heap_area   ();   // scan the heap area
  scan_user_roots  ();   // scan the user supplied roots

  ///////////////////////////////////////////////////////////////////////////
  // Now scan all promoted pages and copy all promoted objects.
  ///////////////////////////////////////////////////////////////////////////
  phase = copying_phase;
  copy_promoted_pages ();    // now move objects around.
  bytes_copied += heap_pointer - heap_start;

  ///////////////////////////////////////////////////////////////////////////
  // Free all unpromoted pages
  ///////////////////////////////////////////////////////////////////////////
  HM::discard_from_space(this, heap_size, pages_removed);

  ///////////////////////////////////////////////////////////////////////////
  // Recompute statistics and adjust gc limit.
  ///////////////////////////////////////////////////////////////////////////
  heap_used  = heap_size - (heap_limit - heap_pointer);
  size_t new_total = heap_size + HM::bytes_free();
  gc_limit = heap_pointer + new_total * gc_ratio / 100L - heap_used;
  should_collect = gc_limit <= heap_limit;
  if (gc_limit > heap_limit)
    gc_limit = heap_limit;

  ///////////////////////////////////////////////////////////////////////////
  // Compute the time used for collection.
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
  // Now clean up properly
  ///////////////////////////////////////////////////////////////////////////
  phase = mutation_phase;
#ifdef GC_HAS_CROSS_HEAP_POINTERS

  HM::traversed_map.clear();
#endif

  memset(reg_roots, 0, sizeof(reg_roots));

  ///////////////////////////////////////////////////////////////////////////
  //  Print the equally annoying end of collection message.
  ///////////////////////////////////////////////////////////////////////////
  end_collection_message();
}

//////////////////////////////////////////////////////////////////////////////
//  Method for scanning a consecutive block of memory for roots.
//////////////////////////////////////////////////////////////////////////////

inline void BGC::scan_for_roots( void ** start, void ** stop)
{
  // Scan consecutively.
  // Caution: addresses between start and stop (not including stop)
  // must be mapped by the OS.
  for (void ** P = (void**)GC_TRUNC_ADDR(start); P < stop; P++)
  {
    void * ptr = *P;

    // Try to interpret each cell as a pointer and see if it
    // falls within any pages of this collectable heap.
    if (! IS_WITHIN_BOUNDS(ptr))
      continue;
    if (! IS_USED_ADDR(ptr, id))
      continue;

    // If so, locate the starting address (the pointer may be
    // an interior pointer) and trace the object.
    Byte * obj = (Byte*)HM::object_map.starting_addr(ptr);
    if (obj == 0)
      continue;
    if (! IS_USED_ADDR(obj, id))
      continue;

    // Get the header of the object.
    GCHeader header = GC_OBJ_HEADER(obj);

    //  Now check whether the pointer actually lies within the
    //  boundary of the object.
    Byte * limit = obj + GC_OBJ_HEADER_LEN(header) - sizeof(GCHeader);

    if ((Byte*)ptr >= limit)
      continue;  // Nope.

    // Finally, we've found a object.  Promote the page(s) in which
    // it resides and mark the object as live.
#ifdef DEBUG_GC

    std::cerr << "[ Promoting object *"
    << (void*)P << " = "
    << (void*)ptr << ", "
    << (void*)obj << " ... "
    << (void*)limit << " ]\n" << flush;

    if (! IS_PROMOTED_ADDR(obj) && ! IS_FROM_SPACE_ADDR(obj))
    {
      std::cerr << "[ Shit! Object is not at from space, header = "
      << (void*)header << " status = " << (int)SPACE_TYPE(obj)
      << " ]\n" << flush;
    }
#endif

    if (HM::live_map.is_marked(obj))
      continue;
    objects_promoted++;
    HM::live_map.mark(obj);      // mark it as live

    GCPageId p = GC_PAGE_ID(GC_OBJ_HEADER_ADDR(obj));
    GCPageId q = GC_PAGE_ID(limit-1);

    //
    // Now make all pages straddled by object as promote.  Be extremely
    // careful in promote all pages.   Make sure boundary conditions
    // are taken care of.
    for ( ;p <= q; p++)
    {
      if (! IS_PROMOTED_PAGE(p))
      {
        PROMOTE_PAGE(p);
        enqueue_pages_to_scan(GC_PAGE_ADDR(p), GC_PAGE_ADDR(p+1));
        pages_promoted++;

#ifdef DEBUG_GC

        std::cerr << "[ New promoted page "
        << (void*)GC_PAGE_ADDR(p)
        << " ... "
        << (void*)GC_PAGE_ADDR(p+1)
        << " gc = " << (int)PAGE_GC(p)
        << " space = " << (int)PAGE_SPACE_TYPE(p)
        << " ]\n" << flush;
#endif

      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for scanning the stack area
//////////////////////////////////////////////////////////////////////////////

void BGC::scan_stack_area()
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

void BGC::scan_static_area()
{
  scanning_message("static data area", data_bottom, data_top);
  size_t n;
  const HM::AddrRange * blacklisted = HM::blacklisted_data(n);
  size_t i = 0;
  void ** start = data_bottom;
  void ** stop  = data_top;
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

void BGC::scan_heap_area()
{
  scanning_message("non-collectable heap", heap_bottom, heap_top);

  // Scan consecutively.
  // Caution: addresses between start and stop (not including stop)
  // must be mapped by the OS.

  //
  // Scan all pages in the user heap that are NOT owned by this heap.
  // We'll do it one page at a time for now.
  //
  void ** P, ** page_limit;
  for (P = heap_bottom; P < heap_top; P = page_limit)
  {
    page_limit = (void**)GC_TRUNC_PAGE_ADDR((Byte*)P + GC_PAGE_SIZE);
    if (page_limit > heap_top)
      page_limit = heap_top;

    // Check to make sure that the address is not been currently
    // used by us or allocated but not used.
    GCPageId page_id = GC_PAGE_ID(P);

    if (IS_WITHIN_TRACKED_LIMITS(P))
    {
      switch (PAGE_SPACE_TYPE(page_id))
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
          GC_ID the_id = PAGE_GC(page_id);
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
//  Method to perform finalization after all promoted
//  objects have been moved.  Objects that hasn't been moved and
//  is not promoted must be garbage and can be safely finalized.
//////////////////////////////////////////////////////////////////////////////

void BGC::do_finalization()
{
  if (! should_finalize)
    return;

  //
  // Invoke finalization methods of dying objects.
  //
  foreach_page_owned_by_collector(page_id, this)
  {
    switch (PAGE_SPACE_TYPE(page_id))
    {
    case GCHeapManager::from_space:
    case GCHeapManager::to_space:
      {
        Byte * page_addr  = (Byte*)GC_PAGE_ADDR(page_id);
        Byte * page_limit = page_addr + GC_PAGE_SIZE;
        while (page_addr < page_limit)
        {
          if (GCHeapManager::object_map.is_marked(page_addr))
          {
            GCHeader header = GC_OBJ_HEADER(page_addr);
            if (GC_OBJ_IS_FORWARDED(header))
            {
              // Object has been moved; get its length from the
              // forwarded object.
              page_addr +=
                GC_OBJ_HEADER_LEN(
                  GC_OBJ_HEADER(
                    GC_OBJ_FORWARD_ADDR(header)));
            }
            else
            {
              // Object hasn't been forwarded.
              // Finalize all unpromoted objects.
              if (! GCHeapManager::live_map.is_marked(page_addr))
              {
                ((GCObject*)page_addr)->~GCObject();
              }
              page_addr += GC_OBJ_HEADER_LEN(header);
            }
          }
          else
          {
            page_addr += GC_ALIGNMENT;
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to scan pages within the scan queue and copy.
//////////////////////////////////////////////////////////////////////////////

void BGC::copy_promoted_pages ()
{
  size_t i;
  phase = copying_phase;


  // Set up the pages to scan
  enqueue_pages_to_scan(heap_pointer, heap_limit);

#ifdef SANITY_CHECK

  size_t objects_traced = 0;
#endif

  // Scan all promoted pages first.
  for (i = 0; i < pages_promoted; i++)
  {
    Byte * page_addr  = (Byte*)GC_PAGE_ADDR(scan_queue[i]);
    Byte * page_limit = page_addr + GC_PAGE_SIZE;
    while (page_addr < page_limit)
    {
      if (HM::object_map.is_marked(page_addr))
      {
        if (HM::live_map.is_marked(page_addr))
        {
          ((GCObject*)page_addr)->trace(this);
#ifdef SANITY_CHECK

          objects_traced++;
#endif

          page_addr += GC_OBJ_HEADER_LEN(GC_OBJ_HEADER(page_addr));
        }
        else
        {
          GCHeader header = GC_OBJ_HEADER(page_addr);
          if (GC_OBJ_IS_FORWARDED(header))
          {
            page_addr +=
              GC_OBJ_HEADER_LEN(
                GC_OBJ_HEADER(
                  GC_OBJ_FORWARD_ADDR(header)));
          }
          else
          {
            page_addr += GC_OBJ_HEADER_LEN(header);
          }
        }
      }
      else
      {
        page_addr += GC_ALIGNMENT;
      }
    }
  }

#ifdef SANITY_CHECK
  if (objects_traced != objects_promoted)
  {
    std::cerr << "[ Bug: number of objects promoted = " << objects_promoted
    << " while the number of objects traced = " << objects_traced
    << " ]\n" << std::flush;
  }
#endif

  // Now scan all other pages on the queue.
  // Since these are new objects they are guaranteed to packed together.
  // We'll use faster code that avoids searching thru the bitmap bit by bit.
  for (  ; i < number_of_pages_to_scan; i++)
  {
    Byte * page_addr  =
      (Byte*)GC_PAGE_ADDR(scan_queue[i]) + GC_ALIGNMENT;
    Byte * page_limit = (Byte*)GC_PAGE_ADDR(scan_limit_queue[i]);
    while (page_addr < page_limit)
    {
      if (! HM::object_map.is_marked(page_addr))
        break;
      ((GCObject*)page_addr)->trace(this);
      page_addr += GC_OBJ_HEADER_LEN(GC_OBJ_HEADER(page_addr));
    }
  }

  //
  // Scavenge the table of weak pointers.
  //
  do_weak_pointer_collection();

  // All objects have now been properly moved to a new space.
  // Perform proper finalization at this point.
  do_finalization();

  // Finally, clear the affected part of the live map in the promoted
  // pages.  All object currently marked as allocated but not alive will
  // be reset.  All live bit will also be cleared in the same process.
  for (i = 0; i < pages_promoted; i++)
  {
    GCPageId page = scan_queue[i];
    Byte * page_addr  = (Byte*)GC_PAGE_ADDR(page);
    Byte * page_limit = page_addr + GC_PAGE_SIZE;

    // copy the live map into the object map.
    HM::object_map.copy(page_addr,page_limit,HM::live_map);
    // clear the live map.
    HM::live_map.clear(page_addr, page_limit);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Accounting method.
//////////////////////////////////////////////////////////////////////////////

BGC::Statistics BGC::statistics()
{
  stat.bytes_used    = heap_size - (heap_limit - heap_pointer);
  stat.bytes_managed = heap_size;
  stat.bytes_free    = heap_limit - heap_pointer;
  return stat;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for printing a heap growth message
//////////////////////////////////////////////////////////////////////////////

void BGC::heap_growth_message( size_t/*heap_size_now*/, size_t /*growth*/) const
{
  if ((verbosity_level & gc_notify_heap_expansion) && console)
  {
    size_t total   = heap_size + HM::bytes_free();
    size_t percent = heap_used * 100 / total;
    (*console) << "[ GC" << id << ": increasing heap... "
    << heap_used << '/' << total
    << " (" << percent << "%) ]\n" << std::flush;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for printing a start collection message
//////////////////////////////////////////////////////////////////////////////

void BGC::start_collection_message() const
{
  if (is_verbose() && console)
  {
    size_t total   = heap_size + HM::bytes_free();
    size_t percent = heap_used * 100 / total;
    (*console) << "[ GC" << id << ": collecting... "
    << heap_used << '/' << total
    << " (" << percent << "%) ]\n" << std::flush;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method for printing a end collection message
//////////////////////////////////////////////////////////////////////////////

void BGC::end_collection_message() const
{
  if (is_verbose() && console)
  {
    size_t total   = heap_size + HM::bytes_free();
    size_t percent = heap_used * 100 / total;
    (*console) << "[ GC" << id << ": done... "
    << heap_used << '/' << total << " ("
    << percent << "%)";
    if (verbosity_level & gc_notify_heap_info)
    {
      (*console)
      << "("
      << (pages_promoted * GC_PAGE_SIZE) << " promoted, "
      << bytes_copied << " moved, "
      << (long)(GC_PAGE_SIZE * pages_removed - bytes_copied)
      << " freed)";
    }
    (*console) << " ]\n" << std::flush;
#ifdef GC_USE_TIMER

    if (verbosity_level & gc_print_collection_time)
    {
      (*console) << "[ GC" << id << ": user time: "
      << stat.gc_user_time
      << " system time: "
      << stat.gc_system_time
      << " ]\n"
      << std::flush;
    }
#endif

  }
}

//////////////////////////////////////////////////////////////////////////////
//  Create an instance of BGC and make that the default collector.
//  The users are free to create others if necessary.
//////////////////////////////////////////////////////////////////////////////

BGC bgc;
GC * GC::default_gc = &bgc;

GC_Initializer::GC_Initializer()
{
  GC::set_default_gc(bgc);
}
