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

#ifndef doubly_linked_list_h
#define doubly_linked_list_h

///////////////////////////////////////////////////////////////////////////
// Doubly linked list
///////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>  // Generic definitions

template <class T>
class LinkedListIter;

template <class T>
class LinkedList
{

  friend class LinkedListIter<T>;

  struct Node
  {
    T element;
    Node * last, * next;
    Node (const T& e, Node * prev, Node * succ)
        : element(e), last(prev), next(succ)
    {}
  };

  Node * front;                     // pointer to the beginning
  Node * back;                      // pointer to the end
  int size;                         // length of list

  LinkedList(const LinkedList &);               // No copy constructor
  LinkedList& operator = (const LinkedList&);   // No assignment

public:
  class Unimplemented
    {};

  LinkedList() : front(0), back(0), size(0)
  {}
  ~LinkedList();

  int length() const
  {
    return size;
  }

  Bool is_empty() const
  {
    return size == 0;
  }

  T& head() const
  {
    return front->element;
  }

  T& tail() const
  {
    return back->element;
  }

  LinkedListIter<T> headPos() const
  {
    return LinkedListIter<T>(front);
  }

  LinkedListIter<T> tailPos() const
  {
    return LinkedListIter<T>(back);
  }

  LinkedList& insert_before (const T& e, LinkedListIter<T>& i);
  LinkedList& insert_after  (const T& e, LinkedListIter<T>& i);
  LinkedList& delete_before (LinkedListIter<T>& i);
  LinkedList& delete_after  (LinkedListIter<T>& i);

  LinkedList& insert_head (const T& e);
  LinkedList& insert_tail (const T& e);
  LinkedList& delete_head ();
  LinkedList& delete_tail ();

  LinkedList& operator += (const T& e)
  {
    return insert_tail(e);
  }
};

template <class T>
class LinkedListIter
{
  friend class LinkedList<T>;
  LinkedList<T>::Node * cursor;
  LinkedListIter(LinkedList<T>::Node * c) : cursor(c)
  {}

public:
  LinkedListIter() : cursor(0)
  {}
  LinkedListIter(LinkedList<T>& list) : cursor(list.front)
  {}
  ~LinkedListIter()
  {}

  void operator = (LinkedList<T>& list)
  {
    cursor = list.front;
  }

  void operator = (LinkedListIter& i)
  {
    cursor = i.cursor;
  }

  operator LinkedList<T>::Node * () const
  {
    return cursor;
  }

  void operator ++ (int)
  {
    cursor = cursor->next;
  }

  void operator ++ ()
  {
    cursor = cursor->next;
  }

  void operator -- (int)
  {
    cursor = cursor->last;
  }

  void operator -- ()
  {
    cursor = cursor->last;
  }

  T& operator () () const
  {
    return cursor->element;
  }
};

///////////////////////////////////////////////////////////////////////////
// Implementation of the template methods
///////////////////////////////////////////////////////////////////////////

template <class T>
LinkedList<T>::~LinkedList()
{
  Node * current, * succ;
  for (current = front; current; current = succ)
  {
    succ = current->next;
    delete current;
  }
}

template <class T>
inline LinkedList<T>& LinkedList<T>::insert_head(const T& e)
{
  Node * n = new Node(e,0,front);
  if (front)
    front->last = n;
  else
    back = n;
  front = n;
  size++;
  return *this;
}

template <class T>
inline LinkedList<T>& LinkedList<T>::insert_tail(const T& e)
{
  Node * n = new Node(e,back,0);
  if (back)
    back->next = n;
  else
    front = n;
  back = n;
  size++;
  return *this;
}

template <class T>
inline LinkedList<T>& LinkedList<T>::delete_head()
{
  Node * garbage = front;
  if (front == back)
    front = back = 0;
  else
  {
    front = front->next;
    front->last = 0;
  }
  delete garbage;
  size--;
  return *this;
}

template <class T>
inline LinkedList<T>& LinkedList<T>::delete_tail()
{
  Node * garbage = back;
  if (front == back)
    front = back = 0;
  else
  {
    back = back->last;
    back->next = 0;
  }
  delete garbage;
  size--;
  return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::insert_before
(const T& e, LinkedListIter<T>& i)
{
  Node * n = new Node(e,i.cursor->last,i.cursor);
  i.cursor->last->next = n;
  i.cursor->last = n;
  size++;
  return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::insert_after
(const T& e, LinkedListIter<T>& i)
{
  Node * n = new Node(e,i.cursor,i.cursor->next);
  i.cursor->next->last = n;
  i.cursor->next = n;
  size++;
  return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::delete_before(LinkedListIter<T>& i)
{
  size--;
  return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::delete_after(LinkedListIter<T>& i)
{
  size--;
  return *this;
}

#endif
