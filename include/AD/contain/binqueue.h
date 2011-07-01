//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef binominal_queue_h
#define binominal_queue_h

//////////////////////////////////////////////////////////////////////////
// Binominal queues
//////////////////////////////////////////////////////////////////////////

#include <limits>
#include <AD/generic/generic.h>


template <class T>
class BinominalQueue
{
  int elemCount;           // number of elements on queue

  BinominalQueue(const BinominalQueue&);  // no copy constructor
  void operator (const BinominalQueue&);  // no assignment

public:
  BinominalQueue();
  ~BinominalQueue();

  int  size()     const
  {
    return elemCount;
  }

  int  length()   const
  {
    return elemCount;
  }

  int  capacity() const
  {
    return INT_MAX;
  }

  Bool is_empty() const
  {
    return elemCount == 0;
  }

  T&   head() const;
  T&   tail() const;

  void clear();
  void insert(const T&);
  void remove
    ();
};

#endif
