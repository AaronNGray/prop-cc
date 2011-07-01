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

#ifndef object_clean_up_h
#define object_clean_up_h

#include <AD/gc/gcobject.h>

//////////////////////////////////////////////////////////////////////////////
//  Clean up protocol, somewhat based on Ellis' safe GC proposal.
//////////////////////////////////////////////////////////////////////////////

template <class T>
class CleanUp
{
  ////////////////////////////////////////////////////////////////////////
  // Some type defintions
  ////////////////////////////////////////////////////////////////////////

public:
  typedef void (*CleanUpFunction)(GCObject *);  // clean up function

private:
  CleanUp(const CleanUp&);           // no copy constructor
  void operator = (const CleanUp&);  // no assignment

  ////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////

public:
  CleanUp();
  ~CleanUp();

  ////////////////////////////////////////////////////////////////////////
  //  Register a clean up function
  ////////////////////////////////////////////////////////////////////////
  void set( GCObject *, CleanUpFunction);
};

#endif
