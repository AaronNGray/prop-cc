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
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef garbage_collector_internals_h
#define garbage_collector_internals_h

#include <new>


//////////////////////////////////////////////////////////////////////////////
//  Some opaque forward definitions
//////////////////////////////////////////////////////////////////////////////

class GCObject;  // garbage collectable objects
class GC;        // garbage collectors
class BGC;       // Barlett's mostly copying garbage collector

//////////////////////////////////////////////////////////////////////////////
//  Object headers definitions.
//  The object header has the following format:
//  For copying collectors:
//     Bit 0     -- the forward bit.
//     Bit 1-31  -- If this is 1 then bit 1 - 31 is the forwarding address.
//                  Otherwise, bit 1 - 31 is the length of the object in bytes,
//                  *including* the length of the header and any other
//                  alignment needs.
//  For marksweep collectors:
//     Bit 0     -- the freelist bit; object in the free list has this
//                  bit set.
//     Bit 1-31  -- the length of the object with header info.
//////////////////////////////////////////////////////////////////////////////

typedef unsigned long GCHeader;

//////////////////////////////////////////////////////////////////////////////
//  Macros for manipulating headers.
// GC_OBJ_HEADER_ADDR(obj) --- return the address of the header given an object
// GC_OBJ_HEADER(obj)      --- return the header given an object address
// GC_OBJ_OBJECT_ADDR(ptr) --- return the object address given a header address
// GC_OBJ_HEADER_LEN(h)    --- return the object length given a header
// GC_OBJ_IS_FORWARDED(h)  --- test if a header is forwarded
// GC_OBJ_FORWARD_ADDR(h)  --- return the forwarded address of a header
// GC_OBJ_SET_FORWARD(obj,ptr) --- set the header to a forwarded address
// GC_OBJ_SET_HEADER(obj,len)  --- set a normal header with an object length
//////////////////////////////////////////////////////////////////////////////

#define GC_OBJ_HEADER_ADDR(obj) (((GCHeader*)(obj))-1)
#define GC_OBJ_HEADER(obj)      (*GC_OBJ_HEADER_ADDR(obj))
#define GC_OBJ_OBJECT_ADDR(ptr) ((GCObject*)(((GCHeader*)(ptr))+1))
#define GC_OBJ_HEADER_LEN(h)    (h)
#define GC_OBJ_IS_FORWARDED(h)  ((h) & 0x1)
#define GC_OBJ_FORWARD_ADDR(h)  ((GCObject*)((h) & 0xfffffffe))
#define GC_OBJ_SET_FORWARD(obj,ptr) \
   (GC_OBJ_HEADER(obj) = ((GCHeader)(ptr) | 0x1))
#define GC_OBJ_SET_HEADER(obj,len)  (GC_OBJ_HEADER(obj) = len)
#define GC_OBJ_FREELIST_LEN(h)       ((h) & 0xfffffffe)
#define GC_OBJ_SET_FREELIST(obj,len) (GC_OBJ_HEADER(obj) = ((len) & 0x1))
#define GC_OBJ_IS_ON_FREELIST(h)     ((h) & 0x1)

#endif
