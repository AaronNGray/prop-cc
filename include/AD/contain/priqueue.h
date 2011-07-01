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

#ifndef priority_queue_h
#define priority_queue_h

///////////////////////////////////////////////////////////////////////
//  Class PriQueue<T> is a binary heap array based
//  priority queue parameterized by the element type
//  and the implementation array type.
//
//    Suitable implementation array types include
//        FixArray<T>   --- array with size fixed at compile type
//        Array<T>      --- array with size fixed at creation type
//        VarArray<T>   --- growable array
//        Indexable<T>  --- array-like object with fast growth
//
//  If a variable sized priority queue is desired, see also pagodas or
//  splay trees, which are also implemented in this library.
///////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>  // Generic definitions

template<class T, class A>
class PriQueue : public A
{
  int elemCount;  // number of elements currently here

public:

  ///////////////////////////////////////////////////////////
  // Constructors and destructor
  ///////////////////////////////////////////////////////////

  PriQueue(int size) : A(size), elemCount(0)
  {}
  PriQueue(const PriQueue& Q) : A(Q.capacity())
  {
    *this = Q;
  }
  ~PriQueue()
  {}

  ///////////////////////////////////////////////////////////
  // Assignment
  ///////////////////////////////////////////////////////////

  void operator = (const PriQueue&);

  ///////////////////////////////////////////////////////////
  // Selectors
  //   Method capacity() and operator [] are inherited from
  // the base class.
  ///////////////////////////////////////////////////////////
  // int capacity()         const; // inherited
  // T& operator [] (int i) const; // inherited

  inline int size() const
  {
    return elemCount;
  }

  inline Bool is_empty() const
  {
    return elemCount == 0;
  }

  inline Bool is_full() const
  {
    return elemCount == capacity();
  }

  inline const T& min() const
  {
    return (*this)[0];
  }

  inline T& min()
  {
    return (*this)[0];
  }

  ///////////////////////////////////////////////////////////
  // Mutators
  ///////////////////////////////////////////////////////////

  inline void clear()
  {
    elemCount = 0;
  }

  inline void delete_min()
  {
    dequeue();
  }

  void enqueue(const T&);
  void requeue(int);
  void dequeue(int = 0);
};

///////////////////////////////////////////////////////////////////////
//  Assignment is redefined to copy only the existing elements
///////////////////////////////////////////////////////////////////////

template<class T, class A>
void PriQueue<T,A>::operator = (const PriQueue<T,A>& Q)
{
  if (this != &Q)
  {
    elemCount = Q.elemCount;
    for (register int i = elemCount-1; i >= 0; i--)
      (*this)[i] = Q[i];
  }
}

///////////////////////////////////////////////////////////////////////
// Both insert and deletion algorithms below have been
// optimized to eliminate unnecessary assignments.
// The basic technique is quite simple: instead of swaping
// existing elements during reorganization, propagate the ``hole''
// instead.  This way we can cut down the number of moves
// by approximately 1/2.
///////////////////////////////////////////////////////////////////////

template<class T,class A>
void PriQueue<T,A>::dequeue(register int i)
{
  register int j;

  // Integer |i| is the index to the current ``hole''
  // and integer |j| is the index of its left child.
  // Therefore |j+1| is the index of the right child.
  // The pointer |pivot| fingers the current ``out of place''
  // element.  We'll proceed from the root (or the |i|th
  // element if the argument |i| is supplied) of the heap and work
  // our way down to the leaves.

  --elemCount;   // one less element
  register T& pivot = (*this)[elemCount];  // last element

  for ( ; (j = i + i + 1) <= elemCount; i = j)
  {
    if (compare(pivot,(*this)[j]) < 0)
    {
      if (j <= elemCount && compare((*this)[j], (*this)[j+1]) < 0)
        j++;
    }
    else if (j > elemCount || compare(pivot, (*this)[j+1]) >= 0)
      break;
    (*this)[i] = (*this)[j];
  }
  (*this)[i] = pivot;
}

///////////////////////////////////////////////////////////////////////
//  Enqueuing an element
///////////////////////////////////////////////////////////////////////

template<class T, class A>
void PriQueue<T,A>::enqueue(const T& element)
{
  register int i, j;

  // Integer |i| is the index to the current ``hole'' while
  // integer |j| is the index of its root, which is equal
  // to |(i - 1)/2|.  We'll start from the bottom of the heap
  // and work our way up to the root(min element).

  for (i = elemCount; i > 0; i = j)
  {
    j = (i-1) / 2;
    if (compare((*this)[j], element) < 0)
      break;
    (*this)[i] = (*this)[j];
  }
  (*this)[i] = element;
  elemCount++;
}

///////////////////////////////////////////////////////////////////////
// Requeuing is the operation of moving an element
// towards the front of the heap.   This is handled in a
// manner similar to the ``enqueue'' operation.
///////////////////////////////////////////////////////////////////////

template<class T, class A>
void PriQueue<T,A>::requeue(register int i)
{
  register int j;
  register T& pivot = (*this)[i];
  for ( ; i > 0; i = j)
  {
    j = (i-1) / 2;
    if (compare((*this)[j], pivot) < 0)
      break;
    (*this)[i] = (*this)[j];
  }
  (*this)[i] = pivot;
}

#endif
