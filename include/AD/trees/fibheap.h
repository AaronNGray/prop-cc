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

#ifndef fibonacci_heap_h
#define fibonacci_heap_h

///////////////////////////////////////////////////////////////////////////
// Class |FibHeap| implements Fibonacci heaps, by Fredman and Tarjan.
///////////////////////////////////////////////////////////////////////////

#include <AD/trees/trees.h>
#include <AD/generic/tables.h>

template <class T>
struct FibNode
{
  T data;
  FibNode * parent, * child;
  FibNode * left_sibling, right_sibling;
  int rank;
  FibNode(const T& d) : data(d) {}
};

template <class T>
class FibHeap
{

  FibNode<T> * heap;
  int count;
  int (*compare)(const T&, const T&);

public:

  ///////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////
  FibHeap() : count(0), heap(0)
  {}
  FibHeap(int (*cmp)(const T&, const T&)) : count(0), heap(0), compare(cmp)
  {}
  FibHeap(const FibHeap&);
  ~FibHeap()
  {
    clear();
  }

  ///////////////////////////////////////////////////////////////////////
  //  Assignment
  ///////////////////////////////////////////////////////////////////////
  FibHeap& operator = (const FibHeap&);
  inline void setCompare(int (*cmp)(const T&, const T&))
  {
    compare = cmp;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////
  inline int  size()     const
  {
    return count;
  }
  inline int  capacity() const
  {
    return count;
  }
  inline Bool is_empty() const
  {
    return count == 0;
  }
  inline Bool is_full()  const
  {
    return false;
  }
  inline const T& min()  const
  {
    return heap->data;
  }
  inline       T& min()
  {
    return heap->data;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Mutators
  ///////////////////////////////////////////////////////////////////////
  void clear();
  Ix   enqueue(const T&);
  Bool delete_min();
  Bool dequeue(Ix i);
};

/////////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
/////////////////////////////////////////////////////////////////////////////

template <class T>
FibHeap<T>::FibHeap(const FibHeap<T>& H) : heap(0)
{
  *this = H;
}

template <class T>
void FibHeap<T>::clear()
{}

template <class T>
FibHeap<T>& FibHeap<T>::operator = (const FibHeap<T>& H)
{
  if (this != &H)
  {}
  return *this;
}

/////////////////////////////////////////////////////////////////////////////
//  Add a new element onto the queue
/////////////////////////////////////////////////////////////////////////////

template <class T>
Ix FibHeap<T>::enqueue(const T& e)
{
  FibNode<T> * v = new FibNode<T>(e);
  v->parent = 0;
  v->rank = 0;
  if (heap == 0)
  {
    heap = v->left_sibling = v->right_silbling = v;
  }
  else
  {
    FibNode<T> * t = heap->left_sibling;
    v->left_sibling = t;
    v->right_sibling = heap;
    heap->left_sibling = t->right_sibling = v;
    if (compare(heap->data,e) > 0)
      heap = v;
  }
  count++;
  return Ix(v);
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

template <class T>
Bool FibHeap<T>::delete_min()
{}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

template <class T>
Bool FibHeap<T>::dequeue(Ix i)
{}

#endif
