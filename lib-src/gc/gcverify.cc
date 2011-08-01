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
#include <AD/gc/gcverify.h>  // verifier
#include <AD/gc/gcheaps.h>   // heap manager
#include <AD/gc/gcbitmap.h>  // bitmap
#include <AD/gc/gcmacros.h>  // useful macros

//////////////////////////////////////////////////////////////////////////////
//  Import some types
//////////////////////////////////////////////////////////////////////////////

typedef GCVerifier::Statistics Statistics;

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

GCVerifier:: GCVerifier() : ok(true), testing_gc(0), traversed(0)
{}

GCVerifier::~GCVerifier()
{
  delete traversed;
}

//////////////////////////////////////////////////////////////////////////////
//  Name of this class
//////////////////////////////////////////////////////////////////////////////

const char * GCVerifier::my_name() const
{
  return "GCVerifier";
}

//////////////////////////////////////////////////////////////////////////////
//  Method for verifying that a pointer is to a valid object.
//////////////////////////////////////////////////////////////////////////////

Bool GCVerifier::is_valid_pointer( GCObject * obj, GC * gc)
{
  if (! IS_WITHIN_BOUNDS(obj))
    return false;
  if (! IS_USED(obj,gc->gc_id()))
    return false;
  if (! HM::object_map.is_marked(obj))
    return false;
  return true;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for verifying that a pointer is a valid interior pointer to
//  an object.
//////////////////////////////////////////////////////////////////////////////

Bool GCVerifier::is_valid_interior_pointer( GCObject* obj, GC* gc)
{
  if (! IS_WITHIN_BOUNDS(obj))
    return false;
  if (! IS_USED(obj,gc->gc_id()))
    return false;
  void * obj_ptr = HM::object_map.starting_addr(obj);
  if (obj_ptr == 0)
    return false;
  if (! IS_USED(obj_ptr,gc->gc_id()))
    return false;
  GCHeader header = GC_OBJ_HEADER(obj_ptr);
  if (GC_OBJ_IS_FORWARDED(header))
    return false;
  size_t   size  = GC_OBJ_HEADER_LEN(header);
  Byte *   limit =
    (Byte*)obj_ptr + size - GC_ALIGNMENT + sizeof(GCHeader);
  if ((Byte*)obj >= limit)
    return false;
  return true;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for verifying an allocated structure on the heap.
//////////////////////////////////////////////////////////////////////////////

Bool GCVerifier::is_valid_structure( GCObject* obj, GC* gc)
{
  if (! is_valid_interior_pointer(obj, gc))
    return false;
  traversed = new GCBitMap; // allocate a bitmap
  testing_gc = gc;          // set the default gc
  nodes = 0;                // reset the number of nodes traced
  ok = true;                // everything is ok for now
  obj->trace(gc);           // trace object
  delete traversed;         // delete the bitmap
  return ok;                // return result
}

//////////////////////////////////////////////////////////////////////////////
//  Method for tracing an object and verifying its correctness.
//////////////////////////////////////////////////////////////////////////////

GCObject* GCVerifier::trace(GCObject* obj)
{
  if (! GC_IS_A_POINTER(obj))
    return obj;

  register void * obj_ptr = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Check only objects lying within the same heap.
  ///////////////////////////////////////////////////////////////////////////
  if (IS_WITHIN_BOUNDS(obj)            &&
      IS_USED(obj,testing_gc->gc_id()) &&
      (obj_ptr = HM::object_map.starting_addr(obj)) != 0 &&
      IS_USED(obj_ptr,testing_gc->gc_id()))
  {
    ////////////////////////////////////////////////////////////////////////
    //  Check to see if object is a valid interior pointer to object.
    ////////////////////////////////////////////////////////////////////////
    GCHeader header = GC_OBJ_HEADER(obj_ptr);
    size_t   size  = GC_OBJ_HEADER_LEN(header);
    Byte *   limit =
      (Byte*)obj_ptr + size - GC_ALIGNMENT + sizeof(GCHeader);
    if ((Byte*)obj >= limit)
    {
      // Not a valid object pointer.
      if (verbosity_level & gc_print_debugging_info)
      {
        std::cerr << "[ WARNING: object pointer "
        << (void*)obj << " is invalid ]\n";
      }
      ok = false;
      return obj;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Trace subobject, but make sure that we don't visit the same node twice.
  ///////////////////////////////////////////////////////////////////////////
  if (! traversed->is_within_bounds(obj_ptr))
    traversed->grow(obj_ptr, (Byte*)obj_ptr + GC_PAGE_SIZE);
  if (traversed->is_marked(obj_ptr))
    return obj;
  traversed->mark(obj_ptr);
  nodes++;
  obj->trace(this);
  return obj;
}

//////////////////////////////////////////////////////////////////////////////
//  Dummied methods
//////////////////////////////////////////////////////////////////////////////

void* GCVerifier::m_alloc( size_t)
{
  error("m_alloc is unimplemented");
  return 0;
}

void GCVerifier::free( void *)
{
  error("free is unimplemented");
}

void GCVerifier::collect( int)
{
  error("collect is unimplemented");
}

void GCVerifier::grow_heap( size_t)
{
  error("grow_heap is unimplemented");
}

Statistics GCVerifier::statistics()
{
  Statistics s;
  reset_statistics(s);
  error("statistics is unimplemented");
  return s;
}
