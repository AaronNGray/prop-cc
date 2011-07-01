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

#ifndef user_collected_heap_h
#define user_collected_heap_h

#include <AD/gc/gc.h>
#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  Opaque objects (i.e. objects without any pointers)
//  can be allocated from the class UserHeap using the methods
//  m_alloc, c_alloc and free.
//
//  Class UserHeap gets its memory from the underlying collector, which
//  is specified during initialization.
//////////////////////////////////////////////////////////////////////////////
class UserHeap : public GC
{
  UserHeap(const UserHeap&);          // no copy constructor
  void operator = (const UserHeap&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef GC::Statistics Statistics;
  typedef GC::GCNotify   GCNofity;

  ///////////////////////////////////////////////////////////////////////////
  //  The underlying garbage collector.
  ///////////////////////////////////////////////////////////////////////////

protected:
  GC& underlying_gc;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  UserHeap();     // use GC::default_gc as default
  UserHeap(GC&);  // use given gc
  virtual ~UserHeap();

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for memory allocation and deallocation.
  //  These should only be used for objects without pointers to
  //  GCObject's !!!
  ///////////////////////////////////////////////////////////////////////////

  virtual void * m_alloc (size_t);
  virtual void * c_alloc (size_t);
  virtual void   free    (void *);
};

#endif
