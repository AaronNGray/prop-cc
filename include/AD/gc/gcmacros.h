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

#ifndef gc_macros_h
#define gc_macros_h

#include <AD/gc/gcconfig.h>

//////////////////////////////////////////////////////////////////////////////
//  Macros for dealing with addresses, page ids and the like.
//  We use macros instead of inlined functions since the latter
//  may not be properly inlined by the compiler: we need every last
//  ounce of speed in the collector.
//      GC_IS_A_POINTER(addr)      -- test whether it is a valid pointer
//      GC_PAGE_ID(addr)           -- returns the page id of an address
//      GC_PAGE_ADDR(id)           -- returns the page address of a page id
//      GC_ROUNDUP_SIZE(size)      -- round up the size to alignment
//      GC_TRUNC_ADDR(size)        -- truncate address to alignment
//      GC_ROUNDUP_PAGE_ADDR(addr) -- round up address to page boundaries
//      GC_TRUNC_PAGE_ADDR(addr)   -- truncate address to page boundaries
//////////////////////////////////////////////////////////////////////////////

#  define GC_IS_A_POINTER(addr) ((unsigned long)(addr) >= 4096)
#  define GC_PAGE_ID(addr) ((size_t)((size_t)(addr) / GC_PAGE_SIZE))
#  define GC_PAGE_ADDR(id) ((void *)((id) * GC_PAGE_SIZE))
#  define GC_ROUNDUP_SIZE(size) \
   ((((size) + GC_ALIGNMENT - 1) / GC_ALIGNMENT) * GC_ALIGNMENT)
#  define GC_ROUNDUP_PAGE_SIZE(size) \
   ((((size) + GC_PAGE_SIZE - 1) / GC_PAGE_SIZE) * GC_PAGE_SIZE)
#  define GC_TRUNC_SIZE(size) \
   (((size) / GC_ALIGNMENT) * GC_ALIGNMENT)
#  define GC_TRUNC_PAGE_SIZE(size) \
   (((size) / GC_PAGE_SIZE) * GC_PAGE_SIZE)
#  define GC_TRUNC_ADDR(addr) \
   ((void *)((((size_t)(addr)) / GC_ALIGNMENT) * GC_ALIGNMENT))
#  define GC_ROUNDUP_PAGE_ADDR(addr) \
   ((void *)((((size_t)(addr)+GC_PAGE_SIZE-1)/GC_PAGE_SIZE)*GC_PAGE_SIZE))
#  define GC_TRUNC_PAGE_ADDR(addr) \
   ((void *)((((size_t)(addr)) / GC_PAGE_SIZE) * GC_PAGE_SIZE))

//////////////////////////////////////////////////////////////////////////////
//  Macros for working with the heap manager
//////////////////////////////////////////////////////////////////////////////

#  define PAGE_GC(id)      (HM::gc_table[id])
#  define SPACE_TYPE(addr) (HM::page_table[GC_PAGE_ID(addr)])
#  define PAGE_SPACE_TYPE(id) (HM::page_table[id])
#  define IS_WITHIN_TRACKED_LIMITS(addr) \
   ((void *)(addr) >= HM::lowest_tracked_addr && \
    (void *)(addr) <  HM::highest_tracked_addr)
#  define IS_WITHIN_BOUNDS(addr) \
   ((void *)(addr) >= HM::lowest_mapped_addr && \
    (void *)(addr) <  HM::highest_mapped_addr)
#  define IS_ALLOCATED(addr) \
   (IS_WITHIN_BOUNDS(addr) && SPACE_TYPE(addr) > HM::blacklisted)
#  define IS_FREE(addr) \
   (IS_ALLOCATED(addr) && PAGE_GC(GC_PAGE_ID(addr)) == 0)
#  define IS_MAPPED(addr) \
   (IS_WITHIN_BOUNDS(addr) && PAGE_GC(GC_PAGE_ID(addr)))
#  define IS_USED_PAGE(page,gc) (PAGE_GC(page) == (gc))
#  define IS_USED_ADDR(addr,gc) (PAGE_GC(GC_PAGE_ID(addr)) == (gc))
#  define IS_USED(addr,gc) \
   (IS_WITHIN_BOUNDS(addr) && IS_USED_PAGE(GC_PAGE_ID(addr),gc))
#  define LOWEST_PAGE()   GC_PAGE_ID(HM::lo_mapped())
#  define HIGHEST_PAGE()  GC_PAGE_ID(HM::hi_mapped())
#  define LOWEST_TRACKED_PAGE()   GC_PAGE_ID(HM::lo_tracked())
#  define HIGHEST_TRACKED_PAGE()  GC_PAGE_ID(HM::hi_tracked())

//////////////////////////////////////////////////////////////////////////////
//  Macros and methods for manipulating the page tables
//////////////////////////////////////////////////////////////////////////////

#  define PROMOTE_PAGE(id) \
   (HM::page_table[id] = HM::to_space)
#  define PROMOTE_ADDR(addr) PROMOTE_PAGE(GC_PAGE_ID(addr))
#  define UNPROMOTE_PAGE(id) \
   (HM::page_table[id] = HM::from_space)
#  define UNPROMOTE_ADDR(addr) UNPROMOTE_PAGE(GC_PAGE_ID(addr))
#  define IS_PROMOTED_PAGE(id) \
   (HM::page_table[id] == HM::to_space)
#  define IS_PROMOTED_ADDR(addr) IS_PROMOTED_PAGE(GC_PAGE_ID(addr))
#  define IS_NEW_PAGE(id) \
   (HM::page_table[id] == HM::newly_allocated)
#  define IS_NEW_ADDR(addr) IS_NEW_PAGE(GC_PAGE_ID(addr))
#  define IS_FROM_SPACE_PAGE(id) \
   (HM::page_table[id] == HM::from_space)
#  define IS_FROM_SPACE_ADDR(addr) IS_FROM_SPACE_PAGE(GC_PAGE_ID(addr))
#  define IS_BLACKLISTED_PAGE(id) \
   (HM::page_table[id] == HM::blacklisted)
#  define IS_BLACKLISTED_ADDR(addr) IS_BLACKLISTED_PAGE(GC_PAGE_ID(addr))

//////////////////////////////////////////////////////////////////////////////
//  Macros for iterating over the page table
//////////////////////////////////////////////////////////////////////////////

#define foreach_page(p)                             \
   for (register HM::GCPageId p = LOWEST_PAGE();    \
        p < HIGHEST_PAGE(); p++)

#define foreach_page_owned_by_collector(p,gc)       \
   for (register HM::GCPageId p = LOWEST_PAGE(),    \
       _id_ = gc->gc_id(); p < HIGHEST_PAGE(); p++) \
         if (HM::page_gc(p) == _id_)

#endif
