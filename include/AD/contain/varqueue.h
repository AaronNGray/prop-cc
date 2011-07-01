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

#ifndef variable_sized_queue_h
#define variable_sized_queue_h

#include <AD/generic/generic.h>

template <class T>
class VarQueue
{
  T * elements;  // array of elements
  int limit;     // current limit
  int count;     // number of elements
  int front;     // index to the front of the queue
  int back;      // index to the back of the queue
  int growth;    // number of elements to expand each time

  void grow();

  ////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////

public:
  VarQueue(int size = 8, int growthRate = 32);
  ~VarQueue();

  ////////////////////////////////////////////////////////////////////////
  //  Selectors
  ////////////////////////////////////////////////////////////////////////

  inline int size() const
  {
    return count;
  }

  inline int capacity() const
  {
    return limit;
  }

  inline Bool is_empty() const
  {
    return count == 0;
  }

  inline Bool is_full() const
  {
    return count == limit;
  }

  inline const T& head() const
  {
    return elements[front];
  }

  inline const T& tail() const
  {
    return elements[back];
  }

  inline T& head()
  {
    return elements[front];
  }

  inline T& tail()
  {
    return elements[back];
  }

  ////////////////////////////////////////////////////////////////////////
  //  Mutators
  ////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////
  //  Returns the i'th element from the queue.
  ////////////////////////////////////////////////////////////////////////

  inline T& operator [] (int i) const
  {
    int index = front - i;
    if (index < 0)
      index += limit;
    return elements[index];
  }

  ////////////////////////////////////////////////////////////////////////
  //  Empties the queue
  ////////////////////////////////////////////////////////////////////////

  inline void clear()
  {
    front = 0;
    back = 1;
    count = 0;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Insert an element to the head of the queue.
  ////////////////////////////////////////////////////////////////////////

  inline void insert_head( const T& e)
  {
    if (is_full())
      grow();
    if (++front >= limit)
      front = 0;
    elements[front] = e;
    count++;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Removes an element from the head of the queue
  ////////////////////////////////////////////////////////////////////////

  inline T& remove_head()
  {
    int index = front--;
    count--;
    if (front < 0)
      front = limit-1;
    return elements[index];
  }

  ////////////////////////////////////////////////////////////////////////
  //  Insert an element to the tail of the queue
  ////////////////////////////////////////////////////////////////////////

  inline void insert_tail( const T& e)
  {
    if (is_full())
      grow();
    if (--back < 0)
      back = limit-1;
    elements[back] = e;
    count++;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Removes an element from the tail of the queue
  ////////////////////////////////////////////////////////////////////////
  inline T& remove_tail()
  {
    int index = back++;
    count--;
    if (back >= limit)
      back = 0;
    return elements[index];
  }

  /////////////////////////////////////////////////////////////////
  //  Iterators
  /////////////////////////////////////////////////////////////////

  inline Ix last() const
  {
    return Ix(count);
  }

  inline Ix first() const
  {
    return Ix(count > 0 ? 1 : 0);
  }

  inline Ix prev(Ix i) const
  {
    return Ix((int)i - 1);
  }

  inline Ix next(Ix i) const
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

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
VarQueue<T>::VarQueue(int size, int growthRate)
    : elements(new T [size]),
    limit(size), count(0), front(0), back(1), growth(growthRate)
{}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
VarQueue<T>::~VarQueue()
{
  delete [] elements;
}

//////////////////////////////////////////////////////////////////////////////
//  Expand a queue
//////////////////////////////////////////////////////////////////////////////

template <class T>
void VarQueue<T>::grow()
{
  int new_limit = limit + growth + limit / 4;
  T * new_elements = new T [new_limit];
  for (int i = back, j = 0, n = count; n > 0; n--)
  {
    new_elements[j++] = elements[i];
    if (++i == limit)
      i = 0;
  }
  delete [] elements;
  elements = new_elements;
  front = count-1;
  back = 0;
  limit = new_limit;
}

#endif
