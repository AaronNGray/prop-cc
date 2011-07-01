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

#include <assert.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <new>
#include <AD/generic/generic.h> // generic definitions
#include <AD/gc/gcconfig.h>     // system dependent configuration
#include <AD/gc/gcintern.h>     // internal data structures
#include <AD/gc/gc.h>           // garbage collector base class
#include <AD/gc/bgc.h>          // Bartlett garbage collector
#include <AD/gc/gcobject.h>     // garbage collectable objects
#include <AD/gc/gcheaps.h>      // heap manager
#include <AD/gc/gcmacros.h>     // useful macros
#include <AD/sort/insort.h>     // insertion sort

// #define DEBUG_GC  // no debugging during production use

//////////////////////////////////////////////////////////////////////////////
//  Static data
//////////////////////////////////////////////////////////////////////////////

size_t   HM::number_of_pages_allocated   = 0;
size_t   HM::number_of_pages_used        = 0;
size_t   HM::number_of_pages_free        = 0;
size_t   HM::number_of_pages_blacklisted = 0;
int      HM::verbosity_level             = 0;
void *   HM::lowest_mapped_addr;  // lowest of the mapped addresses
void *   HM::highest_mapped_addr; // highest of the mapped addresses
void *   HM::lowest_tracked_addr; // lowest of the tracked addresses
void *   HM::highest_tracked_addr;// highest of the tracked addresses
Byte *   HM::gc_table;            // mapping from page id to collector
Byte *   HM::gc_table_mem;        // the tables memory
Byte *   HM::page_table;
Byte *   HM::page_table_mem;
size_t   HM::page_table_size;     // number of pages in the table.
GCBitMap HM::object_map;          // map of starting addresses of objects
GCBitMap HM::live_map;            // map of live objects
GCBitMap HM::traversed_map;       // map of cross heap objects

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

GCHeapManager::GCHeapManager()
{
  ///////////////////////////////////////////////////////////////////////////
  //  Initialize the statistics statistics.
  ///////////////////////////////////////////////////////////////////////////
  number_of_pages_allocated = 0;
  number_of_pages_used      = 0;
  number_of_pages_free      = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Initialize the page tables
  ///////////////////////////////////////////////////////////////////////////
  page_table_size     = 0;
  gc_table            = 0;
  gc_table_mem        = 0;
  page_table          = 0;
  page_table_mem      = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Initialize the address limits
  ///////////////////////////////////////////////////////////////////////////
  lowest_mapped_addr  = 0;
  highest_mapped_addr = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

GCHeapManager::~GCHeapManager()
{
  clear_page_table();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to allocate some storage on page boundaries
/////////////////////////////////////////////////////////////////////////////

void * HM::allocate_pages_on_boundaries(size_t size, void *& real_addr)
{
  size = GC_ROUNDUP_PAGE_SIZE( size ) + GC_PAGE_SIZE;
  real_addr = new char [ size ];
  memset(real_addr, 0, size);
  return GC_ROUNDUP_PAGE_ADDR(real_addr);
}

/////////////////////////////////////////////////////////////////////////////
//  Deallocate pages on boundaries
/////////////////////////////////////////////////////////////////////////////

void HM::deallocate_pages_on_boundaries(void * real_addr, size_t size)
{
  memset(GC_ROUNDUP_PAGE_ADDR(real_addr), 0, size);
  delete [] ((char*)real_addr);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to clear the entire page table and deallocate all storage
//////////////////////////////////////////////////////////////////////////////

void HM::clear_page_table()
{
  // free the page tables
  delete [] gc_table_mem;

  // reset statistics
  number_of_pages_allocated   = 0;
  number_of_pages_used        = 0;
  number_of_pages_free        = 0;
  number_of_pages_blacklisted = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to allocate a block of consecutive pages for a garbage
//  collector and returns its address.
//////////////////////////////////////////////////////////////////////////////

void * HM::allocate_pages
( GC *       gc,              // the collector to allocate for
  size_t     bytes_need,      // the number of bytes that we must have
  size_t     bytes_preferred, // the number of bytes that we prefer
  size_t&    bytes_gotten,    // actual number of bytes gotten
  PageStatus status           // the initial status of the allocated pages
)
{
  // number of pages we need
  register size_t page_count     = (bytes_need + GC_PAGE_SIZE - 1) / GC_PAGE_SIZE;
  register size_t max_page_count = (bytes_preferred + GC_PAGE_SIZE - 1) / GC_PAGE_SIZE;

  for (;;)
  {
    // We'll just use first fit to locate a set of consecutive pages.
    register size_t   found      = 0;
    register GCPageId first_page = 0;

    foreach_page (p)
    {
      if (page_table[p] == from_space && gc_table[p] == 0)
      {
        if (found == 0)
          first_page = p;
        found++;
      }
      else
      {
        if (found >= page_count)
          break; // found!
        found = 0;
      }
    }

    // Check to see if we have all we need
    if (found >= page_count)
    {
      // Check to see if we don't grab too much!
      if (max_page_count > page_count && found > max_page_count)
        found = max_page_count;

      // We now have the required number of pages, and may be a bit more.
      Byte * addr = (Byte*)GC_PAGE_ADDR(first_page);

      // return the number of bytes we actually give back
      bytes_gotten  = found * GC_PAGE_SIZE;

      // mark the pages as now owned by the collector
      GC_ID id = gc->gc_id();
      for (GCPageId p = first_page; p < first_page + found; p++)
      {
        gc_table[p]   = id;
        page_table[p] = status;
      }
      number_of_pages_used += found;
      number_of_pages_free -= found;
      memset (addr, 0, bytes_gotten); // clear the memory

      return addr;
    }
    else
    {
      // We don't have the required number of pages.
      // Try to acquire more pages from the system.
      size_t growth = gc->min_growth();
      if (growth < bytes_need)
        growth = bytes_need;
      if (allocate_new_pages(gc, growth) == 0)
        return 0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to allocate a set of new pages if/when the current heap runs out
//////////////////////////////////////////////////////////////////////////////

void * HM::allocate_new_pages(GC * /*gc*/, size_t bytes)
{  // First, round it up to the size of a page
  // Then try to allocate one more page than required so that
  // if the memory acquired do fall on page boundaries.
  size_t page_count        = (bytes + GC_PAGE_SIZE - 1) / GC_PAGE_SIZE;
  size_t bytes_to_allocate = (page_count + 1) * GC_PAGE_SIZE;
  Byte * memory            = (Byte *)malloc(bytes_to_allocate);
  Byte * memory_limit      = memory + bytes_to_allocate;

  if (memory == 0)
    return 0;
  //
  // Now round things up to the page boundary.
  //
  Byte * user_memory       = (Byte*)GC_ROUNDUP_PAGE_ADDR(memory);
  Byte * user_memory_limit = (Byte*)GC_TRUNC_PAGE_ADDR(memory_limit);
  assert(user_memory >= memory && user_memory_limit <= memory_limit);
  memset(memory, 0, user_memory - memory);
  memset(user_memory_limit, 0, memory_limit - user_memory_limit);

  // unblacklist the bitmaps
  blacklist_system_heap(object_map.bottom(),   object_map.top(),   false);
  blacklist_system_heap(live_map.bottom(),     live_map.top(),     false);
#ifdef GC_HAS_CROSS_HEAP_POINTERS

  blacklist_system_heap(traversed_map.bottom(),traversed_map.top(),false);
#endif

  // expand the object maps
  object_map.grow   (user_memory, user_memory_limit);
  live_map.grow     (user_memory, user_memory_limit);
#ifdef GC_HAS_CROSS_HEAP_POINTERS

  traversed_map.grow(user_memory, user_memory_limit);
#endif

  //
  // Compute the boundaries of the page table, taking into account
  // of blacklisting
  //
  void * low  = user_memory;
  void * high = user_memory_limit;

  if (object_map.bottom() < low)
    low = object_map.bottom();
  if (live_map.bottom() < low)
    low = live_map.bottom();
  if (object_map.top() > high)
    high = object_map.top();
  if (live_map.top() > high)
    high = live_map.top();
#ifdef GC_HAS_CROSS_HEAP_POINTERS

  if (traversed_map.bottom() < low)
    low = traversed_map.bottom();
  if (traversed_map.top() > high)
    high = traversed_map.top();
#endif

  //
  // Expand the page tables if necessary.  Round addresses to page boundaries.
  //
  grow_page_table(low, high);

  //
  // Update the mapped address range
  //
  if (lowest_mapped_addr == 0 || (void*)user_memory < lowest_mapped_addr)
    lowest_mapped_addr = user_memory;
  if (highest_mapped_addr < (void*)user_memory_limit)
    highest_mapped_addr = user_memory_limit;


  //
  // Update the page tables.
  //
  for (register Byte * p = user_memory;
       p < user_memory_limit; p += GC_PAGE_SIZE)
  {
    register GCPageId page_id  = GC_PAGE_ID(p);
    gc_table    [page_id] = 0;
    page_table  [page_id] = from_space;
  }

  // blacklist the bitmaps
  blacklist_system_heap(object_map.bottom(),   object_map.top(),   true);
  blacklist_system_heap(live_map.bottom(),     live_map.top(),     true);
#ifdef GC_HAS_CROSS_HEAP_POINTERS

  blacklist_system_heap(traversed_map.bottom(),traversed_map.top(),true);
#endif

  size_t pages_got = (user_memory_limit - user_memory) / GC_PAGE_SIZE;
  number_of_pages_free      += pages_got;
  number_of_pages_allocated += pages_got;

  // blacklist new pages that currently have false pointers into
  // them so that they won't be used.
  blacklist_new_pages (user_memory, user_memory_limit);

  return user_memory; // starting address of these pages
}

//////////////////////////////////////////////////////////////////////////////
//  Method to expand the page table if necessary
//////////////////////////////////////////////////////////////////////////////

void HM::grow_page_table( void * bottom, void * top)
{
  bottom  = GC_TRUNC_PAGE_ADDR(bottom);
  top     = GC_ROUNDUP_PAGE_ADDR(top);

  void * new_low;
  void * new_high;
  Bool   expansion = false;

  // Find out whether expansion is necessary
  if (bottom < lowest_tracked_addr || lowest_tracked_addr == 0)
  {
    new_low = bottom;
    expansion = true;
  }
  else
  {
    new_low = lowest_tracked_addr;
  }
  if (top > highest_tracked_addr)
  {
    new_high = top;
    expansion = true;
  }
  else
  {
    new_high = highest_tracked_addr;
  }

  if (expansion)
  {
    // Now resize the page tables
    GCPageId old_bottom_page   = GC_PAGE_ID(lowest_tracked_addr);
    //GCPageId old_top_page      = GC_PAGE_ID(highest_tracked_addr);
    GCPageId new_bottom_page   = GC_PAGE_ID(new_low);
    GCPageId new_top_page      = GC_PAGE_ID(new_high);
    size_t   old_size          = page_table_size;
    size_t   new_size          = new_top_page - new_bottom_page;
    Byte * new_gc_table        = new Byte [new_size * 2];
    Byte * new_page_table      = new_gc_table + new_size;
    size_t   shift             =
      old_bottom_page == 0 ? 0 : old_bottom_page - new_bottom_page;

    // unblacklist the old tables
    blacklist_system_heap(gc_table_mem, gc_table_mem + 2 * old_size, false);

    // initialize the new gc table
    memset (new_gc_table, 0, shift);
    memcpy (new_gc_table + shift, gc_table_mem, old_size);
    memset (new_gc_table + shift + old_size, 0, new_size - old_size - shift);

    // initialize the new alloc table
    memset (new_page_table, 0, shift);
    memcpy (new_page_table + shift, page_table_mem, old_size);
    memset (new_page_table + shift + old_size, 0, new_size - old_size - shift);

    // frees the old tables.  Clean things up first
    memset (gc_table_mem, 0, 2 * old_size);
    delete [] gc_table_mem;

    // setup the new tables
    gc_table_mem        = new_gc_table;
    gc_table            = new_gc_table - new_bottom_page;
    page_table_mem      = new_page_table;
    page_table          = new_page_table - new_bottom_page;

    lowest_tracked_addr  = new_low;
    highest_tracked_addr = new_high;
    page_table_size      = new_size;

    // blacklist the new tables
    blacklist_system_heap(new_gc_table, new_gc_table + 2 * new_size, true);
  }
}

/////////////////////////////////////////////////////////////////////////////
//  Method to deallocate a range of pages owned by collector
/////////////////////////////////////////////////////////////////////////////

void HM::deallocate_pages( GC * gc, GCPageId page_id, size_t number_of_pages)
{
  register GC_ID id = gc->gc_id();
  for ( ;number_of_pages > 0; number_of_pages--, page_id++)
  {
    if (gc_table[page_id] != id || page_table[page_id] <= blacklisted)
    {
      std::cerr << "[ Bug: failed to deallocate page " << page_id << " ]\n";
    }
    else
    {
      gc_table   [page_id] = 0;
      page_table [page_id] = from_space;
      number_of_pages_free++;
      number_of_pages_used--;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to deallocate all pages owned by collector
//////////////////////////////////////////////////////////////////////////////

void HM::release_all_pages( GC * gc)
{
  foreach_page_owned_by_collector (p,gc)
  {
    gc_table[p]   = 0;
    page_table[p] = from_space;
    number_of_pages_free++;
    number_of_pages_used--;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to mark all pages as to or from space
//////////////////////////////////////////////////////////////////////////////

void HM::mark_space( void* start, void* stop, PageStatus status)
{
  GCPageId p = GC_PAGE_ID(start);
  GCPageId q = GC_PAGE_ID(stop);
  if (p < LOWEST_PAGE())
    p = LOWEST_PAGE();
  if (q > HIGHEST_PAGE())
    q = HIGHEST_PAGE();
  for ( ;p < q; p++)
    page_table[p] = status;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to blacklist a section of noncollectable memory.
//  Can be safely used by other clients.
//
//////////////////////////////////////////////////////////////////////////////

void HM::blacklist( const void* addr, size_t size_in_bytes)
{
  void * start = GC_ROUNDUP_PAGE_ADDR(addr);
  void * stop  = GC_TRUNC_PAGE_ADDR(((Byte*)addr) + size_in_bytes);
  register GCPageId p = GC_PAGE_ID((Byte*)start + GC_PAGE_SIZE - 1);
  register GCPageId q = GC_PAGE_ID((Byte*)stop);
  if (p < LOWEST_TRACKED_PAGE())
    p = LOWEST_TRACKED_PAGE();
  if (q > HIGHEST_TRACKED_PAGE())
    q = HIGHEST_TRACKED_PAGE();
  for ( ; p < q; p++)
    if (page_table[p] == not_allocated)
      page_table[p] = blacklisted;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to unblacklist a section of noncollectable memory.
//  Can be safely used by other clients.
//
//////////////////////////////////////////////////////////////////////////////

void HM::unblacklist( const void* addr, size_t size_in_bytes)
{
  void * start = GC_ROUNDUP_PAGE_ADDR(addr);
  void * stop  = GC_TRUNC_PAGE_ADDR(((Byte*)addr) + size_in_bytes);
  register GCPageId p = GC_PAGE_ID((Byte*)start + GC_PAGE_SIZE - 1);
  register GCPageId q = GC_PAGE_ID((Byte*)stop);
  if (p < LOWEST_TRACKED_PAGE())
    p = LOWEST_TRACKED_PAGE();
  if (q > HIGHEST_TRACKED_PAGE())
    q = HIGHEST_TRACKED_PAGE();
  for ( ; p < q; p++)
    if (page_table[p] == blacklisted)
      page_table[p] = not_allocated;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to blacklist (or unblacklist?) a section of memory in the system
//  heap.  Blacklisting marks the pages that cannot contain references to
//  the collectable heap.   The pages marked MUST not be already
//  allocated by the heap manager.
//////////////////////////////////////////////////////////////////////////////

void HM::blacklist_system_heap( void* start, void* stop, Bool mark)
{
  //
  // Make sure that if we don't own the entire page
  // don't blacklist it.
  //
  register GCPageId p = GC_PAGE_ID((Byte*)start + GC_PAGE_SIZE - 1);
  register GCPageId q = GC_PAGE_ID((Byte*)stop);
  if (p < LOWEST_TRACKED_PAGE())
    p = LOWEST_TRACKED_PAGE();
  if (q > HIGHEST_TRACKED_PAGE())
    q = HIGHEST_TRACKED_PAGE();

  if (mark)
  {
#ifdef DEBUG_GC
    if (p < q)
      std::cerr << "[ Blacklisting system heap addresses " << (void*)GC_PAGE_ADDR(p)
      << " ... " << (void*)GC_PAGE_ADDR(q) << " ]\n";
#endif

    for ( ; p < q; p++)
    {
      if (page_table[p] != not_allocated)
      {
        std::cerr << "[ Bug: trying to blacklist allocated addresses "
        << (void*)GC_PAGE_ADDR(p) << " ... "
        << (void*)GC_PAGE_ADDR(p+1) << " ]\n";
      }
      else
      {
        page_table[p] = blacklisted;
      }
    }
  }
  else
  {
#ifdef DEBUG_GC
    if (p < q)
      std::cerr << "[ Unblacklisting system heap addresses " << (void*)GC_PAGE_ADDR(p)
      << " ... " << (void*)GC_PAGE_ADDR(q) << " ]\n";
#endif

    for ( ; p < q; p++)
    {
      if (page_table[p] != blacklisted)
      {
        std::cerr << "[ Bug: trying to unblacklist allocated addresses "
        << (void*)GC_PAGE_ADDR(p) << " ... "
        << (void*)GC_PAGE_ADDR(p+1) << " ]\n";
      }
      else
      {
        page_table[p] = not_allocated;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to blacklist a set of newly allocated pages that currently have
//  false pointers into them.
//////////////////////////////////////////////////////////////////////////////

void HM::blacklist_new_pages( void* bottom, void* top)
{

#ifndef GC_USE_BLACKLISTING
  return;
#endif

  void ** data_bottom = (void**)GC_DATA_START;
  void ** data_top    = (void**)GC_DATA_END;
  size_t n;
  const AddrRange * B = HM::blacklisted_data(n);
  size_t i = 0;
  void ** start          = data_bottom;
  void ** stop           = data_top;

  //
  // Compute the number of pages that can be blacklisted in the following
  // loop.
  //
  int new_pages       = (((Byte*)bottom) - ((Byte*)top)) / GC_PAGE_SIZE;
  int blacklist_limit = new_pages * GC_MAX_BLACKLISTED_PERCENTAGE / 100;
  if (blacklist_limit < GC_MIN_BLACKLISTED_PAGES)
    blacklist_limit = GC_MIN_BLACKLISTED_PAGES;
  if (blacklist_limit > GC_MAX_BLACKLISTED_PAGES)
    blacklist_limit = GC_MAX_BLACKLISTED_PAGES;
  if (number_of_pages_blacklisted + blacklist_limit >
      GC_MAX_TOTAL_BLACKLISTED_PAGES)
    blacklist_limit = GC_MAX_BLACKLISTED_PAGES - number_of_pages_blacklisted;

  if (blacklist_limit <= 0)
    return;

  //
  // Now scan the static area and look for false roots into the new
  // heap area that we have just allocated.  Blacklist all pages found,
  // up to our limit.
  //
  for (start = data_bottom; start < data_top; start = stop)
  {
    while (i < n)
    {
      if (start > (void**)B[i].stop)
      {
        i++;
      }
      else if (start >= (void**)B[i].start)
      {
        start = (void**)B[i].stop;
        i++;
      }
      else
        break;
    }
    if (i < n)
      stop = (void**)B[i].start;
    else
      stop = data_top;
    if (start < stop)
    {
      for (register void ** P = start; P < stop; P++)
      {
        register void * ptr = *P;
        if (bottom <= ptr && ptr < top)
        {
          GCPageId page_id = GC_PAGE_ID(ptr);
          if (page_table[page_id] > blacklisted && blacklist_limit > 0)
          {
            if (is_verbose())
            {
              std::cerr << "[ New heap page *"
              << (void*)P << " = " << ptr
              << " (" << (void*)GC_PAGE_ADDR(page_id)
              << " ... "
              << (void*)GC_PAGE_ADDR(page_id+1)
              << ") is blacklisted ]\n";
            }
            page_table[page_id] = blacklisted;
            number_of_pages_allocated--;
            number_of_pages_free--;
            number_of_pages_blacklisted++;
            blacklist_limit--;
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to delete unpromoted pages owned by a collector.
//  All to_space and newly_allocated pages are demoted to from-space.
//  Return the number of bytes owned the collector
//  and the number of bytes removed.
//////////////////////////////////////////////////////////////////////////////

void HM::discard_from_space
(GC * gc, size_t& total, size_t& removed)
{
  total = removed = 0;
  foreach_page_owned_by_collector (p,gc)
  {
    switch (page_table[p])
    {
    case from_space:
      {
        Byte * addr = (Byte*)GC_PAGE_ADDR(p);
        gc_table[p] = 0;
        removed ++;
        object_map.clear(addr, addr + GC_PAGE_SIZE);
      }
      break;
    case to_space:         // falls thru
    case newly_allocated:
      page_table[p] = from_space;
      total += GC_PAGE_SIZE;
      break;
    case blacklisted:
    case not_allocated:
      assert ("Bug in HM::discard_from_space()");
    }
  }
  number_of_pages_free += removed;
}

//////////////////////////////////////////////////////////////////////////////
//  Error reporting.
//  We'll just print a message to std::cerr.
//////////////////////////////////////////////////////////////////////////////

std::ostream& HM::error( const char * message)
{
  return std::cerr << "HM: " << message << '\n';
}

//////////////////////////////////////////////////////////////////////////////
//  Reporting.
//  We'll just print a message to std::cerr.
//////////////////////////////////////////////////////////////////////////////

std::ostream& HM::print_report( std::ostream& log)
{
  log  << "[ Heap manager info:"
  << "\n\tmapped addresses:  " << lowest_mapped_addr
  <<	               " - " << highest_mapped_addr
  << "\n\ttracked addresses: " << lowest_tracked_addr
  <<                     " - " << highest_tracked_addr
  << "\n\tpage_table_size:   " << page_table_size
  << "\n\tobject map:        " << object_map.lowest()
  <<                     " - " << object_map.highest()
  << "\n\tlive map:          " << live_map.lowest()
  <<                     " - " << live_map.highest()
  << "\n\ttranversed map:    " << traversed_map.lowest()
  <<                     " - " << traversed_map.highest()
  << "]\n"
  ;
  return log;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to return a list of blacklisted static data addresses.
//  These are the addresses of all the internal data structures
//  used by the collector and associated classes.   Since the collector
//  maintains various addresses into the collectable heap it is paramount
//  that they are blacklisted and not be mistaken for roots.
//////////////////////////////////////////////////////////////////////////////

const HM::AddrRange* HM::blacklisted_data(size_t& n)
{
  static Bool initialized = false;
  static AddrRange B[] =
    { { &number_of_pages_allocated,   &number_of_pages_allocated + 1 },
      { &number_of_pages_used,        &number_of_pages_used + 1 },
      { &number_of_pages_free,        &number_of_pages_free + 1 },
      { &number_of_pages_blacklisted, &number_of_pages_blacklisted + 1 },
      { &lowest_mapped_addr,          &lowest_mapped_addr + 1 },
      { &highest_mapped_addr,         &highest_mapped_addr + 1 },
      { &lowest_tracked_addr,         &lowest_tracked_addr + 1 },
      { &highest_tracked_addr,        &highest_tracked_addr + 1 },
      { &gc_table,                    &gc_table + 1 },
      { &gc_table_mem,                &gc_table_mem + 1 },
      { &page_table,                  &page_table + 1 },
      { &page_table_mem,              &page_table_mem + 1 },
      { &page_table_size,             &page_table_size + 1 },
      { &object_map,                  &object_map + 1 },
      { &live_map,                    &live_map + 1 },
      { &traversed_map,               &traversed_map + 1 },
      { &bgc,                         &bgc + 1 },
      { GC::collectors,               (Byte*)GC::collectors + sizeof(GC::collectors) },
      { &GC::number_of_collectors,    &GC::number_of_collectors + 1 },
      { &GC::default_gc,              &GC::default_gc + 1 },
      { &std::cout,                        &std::cout + 1 },
      { &std::cin,                         &std::cin + 1 },
      { &std::cerr,                        &std::cerr + 1 },
      { B,                            0 }
    };

  //
  // Sort the ranges by their starting addresses.
  //
  int N = sizeof(B) / sizeof(AddrRange);
  n = N;
  if (! initialized)
  {
    B[N-1].stop = (Byte*)B + sizeof(B);
    insertionSort(AddrRange, B, N, key.start < B[i].start);
    initialized = true;
  }

  return B;
}
