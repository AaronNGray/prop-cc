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

#include <AD/gc/userheap.h>
#include <AD/gc/gcobject.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////

UserHeap:: UserHeap()       : underlying_gc(GC::get_default_gc())
{}

UserHeap:: UserHeap(GC& gc) : underlying_gc(gc)
{}

UserHeap::~UserHeap()
{}

//////////////////////////////////////////////////////////////////////////////
//  This is a variable length dummy collectable object.
//  We'll use these object as template.
//////////////////////////////////////////////////////////////////////////////

class DummyVarLenGCObject : public GCObject
{
  DummyVarLenGCObject(const DummyVarLenGCObject&);
  void operator = (const DummyVarLenGCObject&);

public:
  int memory[1];

  inline          DummyVarLenGCObject()
  {}    // dummy constructor
  inline virtual ~DummyVarLenGCObject()
  {}    // dummy destructor
  virtual void trace (GC *)
  {}                // does nothing
}
;

//////////////////////////////////////////////////////////////////////////////
//  Memory management methods
//////////////////////////////////////////////////////////////////////////////

void * UserHeap::m_alloc( size_t n)
{
  DummyVarLenGCObject * obj =
    new (n + sizeof(DummyVarLenGCObject) - sizeof(int),
         underlying_gc) DummyVarLenGCObject;
  return obj->memory;
}

void * UserHeap::c_alloc( size_t n)
{
  DummyVarLenGCObject * obj =
    new (n + sizeof(DummyVarLenGCObject) - sizeof(int),
         underlying_gc) DummyVarLenGCObject;
  return obj->memory;
}

void   UserHeap::free(void *)
{  // no-op
}
