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

#ifndef min_max_heap_h
#define min_max_heap_h

//////////////////////////////////////////////////////////////////////////////
//  A min-max heap is a variant of binary heap that allows O(1) minimum
//  and maximum extraction.  The other operations(enqueue, delete_min)
//  stays at O(log n).
//////////////////////////////////////////////////////////////////////////////

#include <A/generic/ordering.h>

template <class T, class Array>
class MinMaxHeap : public Array
{
  int queued_elements; // number of elements on queue

  //////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  //////////////////////////////////////////////////////////////////////

public:
  MinMaxHeap(size) : queued_elements(0), Array(size)
  {}
  MinMaxHeap(const MinMaxHeap& H) : Array(H.size())
  {
    *this = H;
  }
  ~MinMaxHeap()
  {}

  //////////////////////////////////////////////////////////////////////
  // Assignment
  //////////////////////////////////////////////////////////////////////

  MinMaxHeap& operator = (const MinMaxHeap&);

  //////////////////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////////////////

  int  size()     const
  {
    return queued_elements;
  }
  // int  capacity() const; // inherited from Array
  Bool is_empty() const
  {
    return queued_elements == 0;
  }

  Bool is_full()  const
  {
    return queued_elements == capacity();
  }

  T&   min()      const;
  T&   max()      const;

  //////////////////////////////////////////////////////////////////////
  //  Mutators
  //////////////////////////////////////////////////////////////////////

  Ix insert(const T& e)
  {
    return enqueue(e);
  }
  Ix enqueue(const T&);
  Bool delete_min();
  Bool delete_max();

  //////////////////////////////////////////////////////////////////////
  //  Iterators
  //////////////////////////////////////////////////////////////////////
  // Inherited from class Array
};

////////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
////////////////////////////////////////////////////////////////////////////

template <class T, class A>
MinMaxHeap<T,A>& MinMaxHeap<T,A>::operator = (const MinMaxHeap<T,A>& H)
{
  if (this != &H)
  {}
  return *this;
}

template <class T, class A>
Ix MinMaxHeap<T,A>::enqueue(const T& e)
{}

template <class T, class A>
Bool MinMaxHeap<T,A>::delete_min()
{}

template <class T, class A>
Bool MinMaxHeap<T,A>::delete_max()
{}

#endif
