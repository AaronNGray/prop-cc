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
// Allen Leung (leunga@valis.cs.nyu.edu)
// 1994-1996
//////////////////////////////////////////////////////////////////////////////

#ifndef logical_term_h
#define logical_term_h

#include <new.h>
#include <AD/generic/generic.h>
#include <AD/csp/trail.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Definition of a logical term object.  All unifiable objects will
//  be derived from this class.
//
//////////////////////////////////////////////////////////////////////////////

class LogicalTerm
{
public:
  virtual ~LogicalTerm()
  {}

  ///////////////////////////////////////////////////////////////////////////
  //
  //  The instantiation/uninstantiation methods must be redefined by
  //  subclasses.
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual void uninstantiate ();
  virtual Bool is_instantiable () const;
  virtual Bool is_instantiated () const;

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Memory management is handled by the trail class.
  //
  ///////////////////////////////////////////////////////////////////////////
  static UnificationTrail& trail; // current trail
  inline static void * operator new (size_t n)
  {
    return trail.m_alloc(n);
  }
  inline static void operator delete (void *)
  {} // no-op
};

#endif
