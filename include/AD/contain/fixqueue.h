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

#ifndef fixed_sized_queue_h
#define fixed_sized_queue_h

/////////////////////////////////////////////////////////////////////////
// Class FixQueue<T,Capacity> is a very simple double ended
// queue parameterized by the element type and its maximum capacity.
// For simplicity, no bounds checking is performed.
/////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>   // Generic definitions

template<class T, int Capacity>
class FixQueue
{

  // Our queue is actually implemented as an array with
  // indices to the front and the back of the queue.
  // Indices are ``wrapped around'' when they reach the
  // prescribed boundaries.

  T elements[Capacity];  // The queue itself.
  int front, back;             // indices to front and back of the queue
  int count;                   // number of elements

public:

  FixQueue() : front(0), back(1), count(0)
  {}

  inline int size() const
  {
    return count;
  }

  inline int capacity() const
  {
    return Capacity;
  }

  inline Bool is_empty() const
  {
    return count == 0;
  }

  inline Bool is_full() const
  {
    return count == Capacity;
  }

  inline const T& head() const
  {
    return elements[front];
  }

  inline T& head()
  {
    return elements[front];
  }

  inline const T& tail() const
  {
    return elements[back];
  }

  inline T& tail()
  {
    return elements[back];
  }

  inline const T& operator [] (int i) const
  {
    int index = front + i;
    if (index >= Capacity)
      index -= Capacity;
    return elements[index];
  }

  inline T& operator [] (int i)
  {
    int index = front + i;
    if (index >= Capacity)
      index -= Capacity;
    return elements[index];
  }

  inline void clear()
  {
    front = 0;
    back = 1;
  }

  inline void insert_head( const T& e)
  {
    if (++front >= Capacity)
      front = 0;
    elements[front] = e;
    count++;
  }

  inline T& remove_head()
  {
    int index = front--;
    count--;
    if (front < 0)
      front = Capacity-1;
    return elements[index];
  }

  inline void insert_tail( const T& e)
  {
    if (--back < 0)
      back = Capacity-1;
    elements[back] = e;
    count++;
  }

  inline T& remove_tail()
  {
    int index = back++;
    count--;
    if (back >= Capacity)
      back = 0;
    return elements[index];
  }

  /////////////////////////////////////////////////////////////////
  //  Iterators
  /////////////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return Ix(count);
  }

  inline Ix last() const
  {
    return Ix(count > 0 ? 1 : 0);
  }

  inline Ix next(Ix i) const
  {
    return Ix((int)i - 1);
  }

  inline Ix prev(Ix i) const
  {
    return Ix((int)i < count ? (int)i+1 : 0);
  }

  inline const T& operator () (Ix i) const
  {
    return (*this)[(int)i-1];
  }

  inline T& operator () (Ix i)
  {
    return (*this)[(int)i-1];
  }
};

#endif
