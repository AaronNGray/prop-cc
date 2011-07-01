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

#ifndef garbage_collectable_objects_base_class_h
#define garbage_collectable_objects_base_class_h

#include <AD/gc/gc.h>  // garbage collector class

//////////////////////////////////////////////////////////////////////////////
//  All garbage collectable objects must be derived from the base class
//  GCObject.  The tracing method ``trace'' must also be redefined
//  in each subclass.
//////////////////////////////////////////////////////////////////////////////

class GCObject
{
public:
  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  inline          GCObject()
  {}  // nop
  inline virtual ~GCObject()
  {}  // nop

  ///////////////////////////////////////////////////////////////////////////
  //  Tracing method.  Must be redefined in each subclass.
  ///////////////////////////////////////////////////////////////////////////
  virtual void trace(GC *) = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Allocation and deallocation methods
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator new (size_t n, GC& gc = *GC::default_gc)
  {
    return gc.m_alloc(n);
  }
  inline void * operator new (size_t n, size_t N, GC& gc = *GC::default_gc)
  {
    return gc.m_alloc(n > N ? n : N);
  }
  void   operator delete (void * obj);

  ///////////////////////////////////////////////////////////////////////////
  //  Size of object.  This method can only be used with objects allocated
  //  on the collectable heap.
  //     (There may be some problem with multiple inheritance also if
  //      the GCObject base class is not at the start of the object...)
  ///////////////////////////////////////////////////////////////////////////
  inline int basic_size() const
  {
    return GC_OBJ_HEADER_LEN(GC_OBJ_HEADER(this));
  }
};

//////////////////////////////////////////////////////////////////////////////
//  Now define the body of the inline gc tracing method
//////////////////////////////////////////////////////////////////////////////
inline void GC::trace(GCObject& obj)
{
  obj.trace(this);
}

#endif
