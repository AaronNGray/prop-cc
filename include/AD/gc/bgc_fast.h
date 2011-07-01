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

#ifndef Bartletts_mostly_copying_conservative_garbage_collector_aux_h
#define Bartletts_mostly_copying_conservative_garbage_collector_aux_h

#include <AD/gc/bgc.h>
#include <AD/gc/gcmacros.h>
#include <AD/gc/gcheaps.h>

//////////////////////////////////////////////////////////////////////////////
//  Method to allocate a new object of a given size
//////////////////////////////////////////////////////////////////////////////

inline void * BGC::operator [] (size_t n)
{  // round up the size
  register size_t bytes = GC_ROUNDUP_SIZE(n + sizeof(GCHeader));

  // if we don't have enough space in current fragment,
  // call the default allocation routine.

  if (heap_pointer + bytes > gc_limit)
  {
    return m_alloc(n);
  }

  // Get new storage for object.
  // Stamp the starting address into the bitmap.

  register GCObject * new_obj = GC_OBJ_OBJECT_ADDR(heap_pointer);
  GC_OBJ_SET_HEADER(new_obj, bytes);
  heap_pointer += bytes;
  GCHeapManager::object_map.mark(new_obj);
  return new_obj;
}

#endif
