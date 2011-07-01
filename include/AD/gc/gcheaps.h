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

#ifndef garbage_collection_spaces_h
#define garbage_collection_spaces_h

#include <new>
#include <iostream>
#include <AD/generic/generic.h>  // generic definitions
#include <AD/gc/gcconfig.h>      // system configurations
#include <AD/gc/gcintern.h>      // internal data structures
#include <AD/gc/gc.h>            // garbage collector base class
#include <AD/gc/gcbitmap.h>      // bitmaps
#include <AD/gc/gcmacros.h>      // useful macros


//////////////////////////////////////////////////////////////////////////////
//  Garbage collection space manager.
//  The space manager provides the following services:
//     (1)  Partition the collectable heaps into pages
//     (2)  Maintain bitmaps on these pages so that starting addresses
//          of objects can be found (for interior pointers.)
//////////////////////////////////////////////////////////////////////////////

class GCHeapManager
{
  GCHeapManager (const GCHeapManager&);   // no copy constructor
  void operator = (const GCHeapManager&); // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef size_t        GCPageId;  // a page id
  typedef GC::GC_ID     GC_ID;     // collector id.

  ///////////////////////////////////////////////////////////////////////////
  //  Statistics
  ///////////////////////////////////////////////////////////////////////////

protected:
  static size_t number_of_pages_allocated;
  static size_t number_of_pages_used;
  static size_t number_of_pages_free;
  static size_t number_of_pages_blacklisted;

  ///////////////////////////////////////////////////////////////////////////
  //  Message verbosity
  ///////////////////////////////////////////////////////////////////////////
  static int verbosity_level;

  ///////////////////////////////////////////////////////////////////////////
  // Status of a page in the alloc table.  The page status is one byte long
  // and stored in an array in the heap.  To prevent them from mistaken
  // for real heap addresses, we choose some high numbers.  On Unix
  // most platforms these resemble stack addresses.
  ///////////////////////////////////////////////////////////////////////////

public:
  enum PageStatus {
    not_allocated   = 0x00, // we don't have this page; the OS has it
    blacklisted     = 0xfc, // this page will never be used by the application
    from_space      = 0xfd, // this is the from space of a heap
    to_space        = 0xfe, // this is the to space of a heap
    newly_allocated = 0xff  // this is the space used during the copying phase
  };

  ///////////////////////////////////////////////////////////////////////////
  //  An address range
  ///////////////////////////////////////////////////////////////////////////
  struct AddrRange
  {
    void * start, * stop;
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Make it possible for certain classes to use the page table info
  //  directly without going thru the inline functions since inlining
  //  may not be as efficient as macros.
  ///////////////////////////////////////////////////////////////////////////

private:
  friend class BGC;
  friend class MarkSweepGC;
  friend class BGC_F;
  friend class CGC;
  friend class GCVerifier;

  ///////////////////////////////////////////////////////////////////////////
  //  Page tables.
  //    We store them in page_table and bitmap_table respectively.  These
  //  tables are stored in an offseted manner.
  //  Empty pages are stored as null pointers.
  //  Tracked addresses are addresses that have corresponding page table
  //  entries while mapped addresses are addresses that have bitmap entries.
  ///////////////////////////////////////////////////////////////////////////
  static void *   lowest_mapped_addr;  // lowest of the mapped addresses
  static void *   highest_mapped_addr; // highest of the mapped addresses
  static void *   lowest_tracked_addr; // lowest of the tracked addresses
  static void *   highest_tracked_addr;// highest of the tracked addresses

  static Byte *   gc_table;            // mapping from page id to collector id
  static Byte *   gc_table_mem;        // the tables memory
  static Byte *   page_table;          // mark all pages that we own
  static Byte *   page_table_mem;      // the tables memory
  static size_t   page_table_size;     // number of pages in the table.
  static GCBitMap object_map;          // map of starting addresses of objects
  static GCBitMap live_map;            // map of live objects
  static GCBitMap traversed_map;       // map of cross heap objects

  ///////////////////////////////////////////////////////////////////////////
  //  Free list.
  //     Deallocated pages are chained together into the free list
  //  so that it can be reused quickly.
  ///////////////////////////////////////////////////////////////////////////

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  GCHeapManager();
  ~GCHeapManager();

  ///////////////////////////////////////////////////////////////////////////
  //  Address boundaries
  ///////////////////////////////////////////////////////////////////////////
  inline static void * lo_mapped()
  {
    return lowest_mapped_addr;
  }
  inline static void * hi_mapped()
  {
    return highest_mapped_addr;
  }
  inline static void * lo_tracked()
  {
    return lowest_tracked_addr;
  }
  inline static void * hi_tracked()
  {
    return highest_tracked_addr;
  }
  inline static Bool is_mapped(void * addr)
  {
    return addr >= lowest_mapped_addr && addr < highest_mapped_addr;
  }
  inline static Bool is_tracked(void * addr)
  {
    return addr >= lowest_tracked_addr && addr < highest_tracked_addr;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Page table
  ///////////////////////////////////////////////////////////////////////////
  inline static PageStatus page_status(GCPageId id)
  {
    return (PageStatus)page_table[id];
  }
  inline static PageStatus page_status(void * addr)
  {
    return (PageStatus)page_table[GC_PAGE_ID(addr)];
  }
  inline static GC_ID page_gc(GCPageId id)
  {
    return gc_table[id];
  }
  inline static GC_ID page_gc(void * addr)
  {
    return gc_table[GC_PAGE_ID(addr)];
  }
  inline static void set_page_status(GCPageId id, PageStatus s)
  {
    page_table[id] = s;
  }
  inline static void set_page_gc(GCPageId id, GC_ID gc)
  {
    gc_table[id] = gc;
  }
  inline static void promote_page(GCPageId id)
  {
    page_table[id] = to_space;
  }
  inline static void promote_page(void * addr)
  {
    page_table[GC_PAGE_ID(addr)] = to_space;
  }

  ///////////////////////////////////////////////////////////////////////////
  // Bitmaps
  ///////////////////////////////////////////////////////////////////////////
  inline static GCBitMap& get_object_map()
  {
    return object_map;
  }
  inline static GCBitMap& get_live_map()
  {
    return live_map;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Free space
  ///////////////////////////////////////////////////////////////////////////
  inline static size_t pages_allocated()
  {
    return number_of_pages_allocated;
  }
  inline static size_t pages_used()
  {
    return number_of_pages_used;
  }
  inline static size_t pages_free()
  {
    return number_of_pages_free;
  }
  inline static size_t pages_blacklisted()
  {
    return number_of_pages_blacklisted;
  }
  inline static size_t bytes_allocated()
  {
    return number_of_pages_allocated * GC_PAGE_SIZE;
  }
  inline static size_t bytes_used()
  {
    return number_of_pages_used * GC_PAGE_SIZE;
  }
  inline static size_t bytes_free()
  {
    return number_of_pages_free * GC_PAGE_SIZE;
  }
  inline static size_t bytes_blacklisted()
  {
    return number_of_pages_blacklisted * GC_PAGE_SIZE;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Verbosity level
  ///////////////////////////////////////////////////////////////////////////
  inline static int  verbosity()
  {
    return verbosity_level;
  }
  inline static void set_verbosity(int v)
  {
    verbosity_level = v;
  }
  inline static Bool is_verbose()
  {
    return verbosity_level > 0;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for allocating/deallocating memory and manipulating
  //  the page tables.
  //    blacklisted_data()  -- return a table of blacklisted static addresses
  //    clear_page_table()  -- empty the entire page table
  //    release_all_pages() -- release all pages owned by a collector
  //    allocate_pages()    -- allocate a bunch of pages
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //  Method to return a table of blacklisted static data addresses.
  ///////////////////////////////////////////////////////////////////////////
  static const AddrRange * blacklisted_data (size_t& n);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to expand the ranges of the page tables.
  ///////////////////////////////////////////////////////////////////////////
  static void  grow_page_table (void * start, void * stop);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to release all the pages owned by a collector.
  ///////////////////////////////////////////////////////////////////////////
  static void   release_all_pages(GC *);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to allocate a set of consecutive pages from the heap manager.
  //  The client tells the heap manager how much space is needed, and
  //  how much is preferred.   The actual number of bytes is returned
  //  the parameter ``bytes_gotten'' and the address of the new pages
  //  is returned.
  ///////////////////////////////////////////////////////////////////////////
  static void * allocate_pages
  ( GC *       gc,                 // the collector to allocate for
    size_t     bytes_need,         // number of bytes we need
    size_t     bytes_wanted,       // number of bytes we prefer to have
    size_t&    bytes_gotten,       // number of bytes actually got
    PageStatus status = from_space // the default status of the pages
  );

  ///////////////////////////////////////////////////////////////////////////
  //  Method to deallocate pages owned by a collector
  ///////////////////////////////////////////////////////////////////////////
  static void deallocate_pages
  ( GC *     gc,          // the collector
    GCPageId page_id,     // starting page to deallocate
    size_t   pages        // number of pages
  );

  ///////////////////////////////////////////////////////////////////////////
  //  Method to discard all pages in the from space of the collector.
  //  As a side effect, the total number of bytes now owned by the collector
  //  and the total number of bytes freed are returned as the 2nd and 3rd
  //  parameter.
  ///////////////////////////////////////////////////////////////////////////
  static void   discard_from_space(GC *, size_t& total, size_t& removed);

  ///////////////////////////////////////////////////////////////////////////
  //  Mark all pages within start and stop to have certain page status.
  ///////////////////////////////////////////////////////////////////////////
  static void   mark_space(void * start, void * stop, PageStatus status);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to (un)blacklist a range of addresses.
  //  Use blacklist_system_heap(start,stop,true) to blacklist
  //  and blacklist_system_heap(start,stop,false) to unblacklist
  ///////////////////////////////////////////////////////////////////////////
  static void   blacklist_system_heap(void * start, void * stop, Bool mark);
  static void   blacklist   (const void * addr, size_t size_in_bytes);
  static void   unblacklist (const void * addr, size_t size_in_bytes);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to allocate some initialized memory on page boundaries.
  //  The storage is outside of the collectable heap and is meant to
  //  be used as auxiliary data.
  ///////////////////////////////////////////////////////////////////////////
  static void * allocate_pages_on_boundaries   (size_t size, void *& real);
  static void   deallocate_pages_on_boundaries (void *, size_t);

  ///////////////////////////////////////////////////////////////////////////
  //  Error reporting
  ///////////////////////////////////////////////////////////////////////////
  static std::ostream& error (const char *);
  static std::ostream& print_report(std::ostream&);

private:
  ///////////////////////////////////////////////////////////////////////////
  //  The following methods are not meant to be used by the clients directly.
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //  Method to clear the entire page table.  DO NOT USE!
  ///////////////////////////////////////////////////////////////////////////
  static void   clear_page_table ();

  ///////////////////////////////////////////////////////////////////////////
  //  Method to expand the page tables.  Used only internally
  ///////////////////////////////////////////////////////////////////////////
  static void * allocate_new_pages (GC *, size_t bytes); // allocate new pages

  ///////////////////////////////////////////////////////////////////////////
  //  Method to blacklist a set of newly allocated pages.  This method
  //  is only used internally by the heap manager.
  ///////////////////////////////////////////////////////////////////////////
  static void   blacklist_new_pages(void * start, void * stop);
};

//////////////////////////////////////////////////////////////////////////////
//  A synonym for class GCHeapManager to save keystrokes.
//////////////////////////////////////////////////////////////////////////////
typedef class GCHeapManager HM;

#endif
