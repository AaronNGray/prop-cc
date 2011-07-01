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

#ifndef CSP_solver_base_class_h
#define CSP_solver_base_class_h

#include <AD/generic/generic.h>
#include <AD/csp/trail.h>

class CSP_Solver
{
  CSP_Solver(const CSP_Solver&);        // no copy constructor
  void operator = (const CSP_Solver&);  // no assignment

  //////////////////////////////////////////////////////////////////////////
  //  Type definitions.
  //////////////////////////////////////////////////////////////////////////

public:
  typedef int    TimeStamp;     // time stamp
  typedef void * Continuation;  // continuation is an address.

protected:
  //////////////////////////////////////////////////////////////////////////
  //  Internal timestamp
  //////////////////////////////////////////////////////////////////////////
  TimeStamp time_stamp;  // time stamp counter
  CSP_Stack stack;       // stack
  Trail     trail;       // trail
  CSP_Heap  heap;        // heap

public:
  //////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////////////////////
  CSP_Solver();
  virtual ~CSP_Solver();

  //////////////////////////////////////////////////////////////////////////
  //  Ask/tell operations.
  //////////////////////////////////////////////////////////////////////////
  virtual Bool ask  (const Constraint&) = 0;
  virtual Bool tell (const Constraint&) = 0;

  //////////////////////////////////////////////////////////////////////////
  //  Cut and trailing/backtracking operations.
  //////////////////////////////////////////////////////////////////////////
  virtual void cut();
  virtual void create_choice();
  virtual void backtrack();
};

#endif
