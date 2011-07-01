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

#ifndef double_ended_heap_h
#define double_ended_heap_h

#include <A/generic/ordering.h>

template <class T, class Array>
class DHeap : public Array
{
public:

  //////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  //////////////////////////////////////////////////////////////////////

  DHeap();
  DHeap(const DHeap&);
  ~DHeap();

  //////////////////////////////////////////////////////////////////////
  // Assignment
  //////////////////////////////////////////////////////////////////////

  DHeap& operator = (const DHeap&);

  //////////////////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////////////////

  int  size()     const;
  int  capacity() const;
  Bool is_empty() const;
  Bool is_full()  const;
  T&   min()      const;
  T&   max()      const;

  //////////////////////////////////////////////////////////////////////
  //  Mutators
  //////////////////////////////////////////////////////////////////////

  Ix   insert(const T&);
  Ix   enque(const T&);
  Bool delete_min();
  Bool delete_max();

  //////////////////////////////////////////////////////////////////////
  //  Iterators
  //////////////////////////////////////////////////////////////////////
  // Inherited from class Array
};

#endif
