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

#ifndef CSP_solver_heap_h
#define CSP_solver_heap_h

#include <AD/memory/mem.h>

class CSP_Heap : public Mem
{
  CSP_Heap(const CSP_Heap&);         // no copy constructor
  void operator = (const CSP_Heap&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  CSP_Heap();
  CSP_Heap(Mem&);
  virtual ~CSP_Heap();

  ///////////////////////////////////////////////////////////////////////////
  //  Fast allocation methods
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator [] (size_t n)
  { }

  ///////////////////////////////////////////////////////////////////////////
  //  Mem protocol methods.
  ///////////////////////////////////////////////////////////////////////////
  virtual void * m_alloc(size_t);
  virtual void * c_alloc(size_t);
  virtual void * free   (size_t);
};
