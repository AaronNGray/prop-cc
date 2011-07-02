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

#ifndef gc_bitmaps_h
#define gc_bitmaps_h

#include <new>
#include <string>
#include <AD/generic/generic.h>
#include <AD/gc/gcconfig.h>
#include <AD/gc/gcintern.h>


class GCBitMap
{
  GCBitMap(const GCBitMap&);          // no copy constructor
  void operator = (const GCBitMap&);  // no assignment

protected:
  typedef unsigned long Glob;

  void * lowest_addr;     // lowest address
  void * highest_addr;    // highest address
  Glob * bitmap;          // the offseted bitmap array
  Glob * bitmap_bot;      // bottom of the bitmap array
  Glob * bitmap_top;      // top of the bitmap array
  void * bitmap_core;     // actual storage from the system
  long   bitmap_size;     // size of bitmap in bytes

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  GCBitMap();
  ~GCBitMap();

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline void * lowest()  const
  {
    return lowest_addr;
  }
  inline void * highest() const
  {
    return highest_addr;
  }
  inline Bool is_within_bounds(void * addr) const
  {
    return (void*)lowest_addr <= addr && addr < (void*)highest_addr;
  }

  inline Bool is_marked(void * addr) const
  {
    return bitmap[(size_t)addr / (GC_ALIGNMENT * 8 * sizeof(Glob))] &
           (1 << (((size_t)addr / GC_ALIGNMENT) % (8 * sizeof(Glob))));
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Bottom and top of the actual bitmap
  ///////////////////////////////////////////////////////////////////////////
  inline void * bottom() const
  {
    return bitmap_bot;
  }
  inline void * top()    const
  {
    return bitmap_top;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Method to locate the last marked bit
  ///////////////////////////////////////////////////////////////////////////
  inline void * starting_addr(void * addr) const
  {
    size_t index       =
      ((size_t)addr / GC_ALIGNMENT) / (8 * sizeof(Glob));
    register int    bit         =
      ((size_t)addr / GC_ALIGNMENT) % (8 * sizeof(Glob));
    register const Glob * map   = bitmap + index;
    if (*map & (1 << bit))
      return (void*)(((size_t)addr / GC_ALIGNMENT) * GC_ALIGNMENT);
    for ( ;map >= bitmap_bot; map--)
    {
      const Glob mask = *map;
      if (mask)
      {
        for (; bit >= 0; bit--)
        {
          if (mask & (1 << bit))
          {
            return (void*)(((map - bitmap) * 8 * sizeof(Glob) + bit)
                           * GC_ALIGNMENT);
          }
        }
      }
      bit = 8 * sizeof(Glob) - 1;
    }
    return 0;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Mutators
  ///////////////////////////////////////////////////////////////////////////
  inline void mark(void * addr)
  {
    bitmap[(size_t)addr/(GC_ALIGNMENT * 8 * sizeof(Glob))] |=
      (1 << (((size_t)addr/GC_ALIGNMENT) % (8 * sizeof(Glob))));
  }
  inline void unmark(void * addr)
  {
    bitmap[(size_t)addr/(GC_ALIGNMENT * 8 * sizeof(Glob))] &=
      ~(1 << (((size_t)addr/GC_ALIGNMENT) % (8 * sizeof(Glob))));
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Unmark the entire bitmap and reset everything to empty.
  ///////////////////////////////////////////////////////////////////////////
  void clear();    // reset everything to zero
  void release();  // clear the map and release all storage

  ///////////////////////////////////////////////////////////////////////////
  //  Unmark a portion of the bitmap
  ///////////////////////////////////////////////////////////////////////////
  inline void clear(void * start, void * stop)
  {
    if (start < lowest_addr)
      start = lowest_addr;
    if (stop  > highest_addr)
      stop = highest_addr;
    register Glob * block =
      bitmap + ((size_t)start/ (GC_ALIGNMENT * 8 * sizeof(Glob)));
    register size_t len   =
      ((Byte*)stop - (Byte*)start) / (GC_ALIGNMENT * 8 * sizeof(Glob));
    while (len > 0)
    {
      len--;
      *block++ = 0;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Copy a portion of the bitmap into another
  ///////////////////////////////////////////////////////////////////////////
  inline void copy(void * start, void * stop, const GCBitMap& map)
  {
    if (start < lowest_addr)
      start = lowest_addr;
    if (stop  > highest_addr)
      stop = highest_addr;
    register Glob * dest =
      bitmap + ((size_t)start/ (GC_ALIGNMENT * 8 * sizeof(Glob)));
    register const Glob * src  =
      map.bitmap + ((size_t)start/ (GC_ALIGNMENT * 8 * sizeof(Glob)));
    register size_t len  =
      ((Byte*)stop - (Byte*)start) / (GC_ALIGNMENT * 8 * sizeof(Glob));
    while (len > 0)
    {
      len--;
      *dest++ = *src++;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Method to grow the bitmap
  ///////////////////////////////////////////////////////////////////////////
  void grow (void * low, void * high);
};

#endif
