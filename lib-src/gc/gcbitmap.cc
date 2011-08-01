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
#include <string>
#include <assert.h>
#include <AD/gc/gcbitmap.h>
#include <AD/gc/gcheaps.h>
#include <AD/gc/gcmacros.h>

// #define DEBUG_GC

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

GCBitMap::GCBitMap()
    : lowest_addr(0), highest_addr(0),
    bitmap(0), bitmap_bot(0), bitmap_top(0), bitmap_core(0),
    bitmap_size(0)
{}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

GCBitMap::~GCBitMap()
{
  release();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to clear the entire bitmap
//////////////////////////////////////////////////////////////////////////////

void GCBitMap::clear()
{
  memset(bitmap_bot, 0, bitmap_size);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to release all the memory of a bitmap
//////////////////////////////////////////////////////////////////////////////

void GCBitMap::release()
{
  if (bitmap_core)
  {
    HM::deallocate_pages_on_boundaries(bitmap_core, bitmap_size);
    lowest_addr  = 0;
    highest_addr = 0;
    bitmap       = 0;
    bitmap_bot   = 0;
    bitmap_top   = 0;
    bitmap_core  = 0;
    bitmap_size  = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to grow the bitmap.
//////////////////////////////////////////////////////////////////////////////

void GCBitMap::grow (void * low, void * high)
{
  // roundup to page size
  void * real_low  = GC_TRUNC_PAGE_ADDR(low);
  void * real_high = GC_ROUNDUP_PAGE_ADDR((Byte*)high + 1);

  // compute new address boundaries
  void * new_low   = (real_low < lowest_addr || lowest_addr == 0)
                     ? real_low : lowest_addr;
  void * new_high  = real_high > highest_addr ? real_high : highest_addr;

  // Check whether the boundaries have changed.
  // If so, expand the bitmap
  if (new_low != lowest_addr || new_high != highest_addr)
  {
    size_t new_size        = ((Byte*)new_high - (Byte*)new_low) /
                             (8 * GC_ALIGNMENT);
    new_size = GC_ROUNDUP_PAGE_SIZE(new_size);
    void * new_bitmap_core;
    Glob * new_bitmap_bot  =
      (Glob*)HM::allocate_pages_on_boundaries(new_size, new_bitmap_core);
    size_t shift           =
      lowest_addr == 0 ? 0 :
      (((Byte*)lowest_addr - (Byte*)new_low) /
       (8 * GC_ALIGNMENT * sizeof(Glob)));

    // copy old bitmap to new
    memcpy(new_bitmap_bot + shift, bitmap_bot, bitmap_size);

    // clean up old bitmap and delete it
    HM::deallocate_pages_on_boundaries(bitmap_core, bitmap_size);

    // readjust bitmap pointers and offsets
    lowest_addr  = new_low;
    highest_addr = new_high;
    bitmap_size  = new_size;
    bitmap_core  = new_bitmap_core;
    bitmap_bot   = new_bitmap_bot;
    bitmap       = new_bitmap_bot -
                   ((size_t)new_low / (sizeof(Glob) * 8 * GC_ALIGNMENT));
    bitmap_top   = bitmap_bot + new_size / sizeof(Glob);

#ifdef DEBUG_GC

    std::cerr << "[ New bitmap at " << (void*)bitmap_bot
    << " ... " << (void*)bitmap_top << " ]\n";
#endif

  }
}
