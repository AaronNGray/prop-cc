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
//
// Kudos to James Litsios <litsios@iis.ee.ethz.ch> for his tireless
// testing efforts and useful feedbacks.  Certain part of Prop
// now incorporates some of James' ideas on reference counting and
// hash consing.
//////////////////////////////////////////////////////////////////////////////

#ifndef hash_consing_h
#define hash_consing_h

#include <new>
#include <AD/generic/ordering.h>    // hashing and comparison


template <class T>
class UniqueObj
{
public:
  ////////////////////////////////////////////////////////////////////////
  //  Memory management
  ////////////////////////////////////////////////////////////////////////
  void * operator new    (size_t);
  void   operator delete (void *);
};

#endif
