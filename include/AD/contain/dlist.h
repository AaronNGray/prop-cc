#ifndef doubly_linked_lists_h
#define doubly_linked_lists_h

#include <AD/generic/generic.h>

//////////////////////////////////////////////////////////////////////////////
//  Linked node structure; this class is be made visible to the
//  client.  Notice that the link structure is made hidden to the user
//  for safety.
//////////////////////////////////////////////////////////////////////////////

template <class T>
class DLinkList;

template <class T>
class DNode
{
  ////////////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////////////

  T      element;
  DNode * _prev, * _next;
  friend class DLinkList<T>;
  inline DNode * set_prev(DNode * p)
  {
    _prev = p;
  }
  inline DNode * set_next(DNode * n)
  {
    _next = n;
  }

  ////////////////////////////////////////////////////////////////////////
  // Public operations.
  ////////////////////////////////////////////////////////////////////////

public:
  inline DNode(const T& e, DNode * p = 0, DNode * n = 0)
      : element(e), _prev(p), _next(n)
  {}

  inline DNode * prev() const
  {
    return _prev;
  }

  inline DNode * next() const
  {
    return _next;
  }

  inline const T& value() const
  {
    return element;
  }

  inline       T& value()
  {
    return element;
  }
};

//////////////////////////////////////////////////////////////////////////////
//
//  Doubly linked lists template.
//  This class implements a double linked list datatype.
//  The list nodes can be manipulated directly using the link/unlink methods,
//  while the insert/remove methods provide an encapsulated interface to
//  the list.
//
//////////////////////////////////////////////////////////////////////////////

template <class T>
class DLinkList
{
public:
  ////////////////////////////////////////////////////////////////////////
  //  Type equivalences.
  ////////////////////////////////////////////////////////////////////////

  typedef T          Element; // element type
  typedef DNode<T> * Ix;      // index type

  ////////////////////////////////////////////////////////////////////////
  //  Data members
  ////////////////////////////////////////////////////////////////////////

  int        count;          // number of elements in list
  DNode<T> * front, * back;  // link to first and last element

  ////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ////////////////////////////////////////////////////////////////////////

public:
  DLinkList();
  DLinkList(const DLinkList&);
  ~DLinkList();

  ////////////////////////////////////////////////////////////////////////
  //  Assignment
  ////////////////////////////////////////////////////////////////////////

  DLinkList& operator = (const DLinkList&);

  ////////////////////////////////////////////////////////////////////////
  //  Selectors
  ////////////////////////////////////////////////////////////////////////

  inline int  size     () const
  {
    return count;
  }

  inline Bool is_empty () const
  {
    return front == 0;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Iterators
  ////////////////////////////////////////////////////////////////////////

  inline DNode<T> * first()                  const
  {
    return front;
  }

  inline DNode<T> * last ()                  const
  {
    return back;
  }

  inline DNode<T> * next (DNode<T> * i)      const
  {
    return i->next();
  }

  inline DNode<T> * prev (DNode<T> * i)      const
  {
    return i->prev();
  }

  inline const T& operator () (DNode<T> * i) const
  {
    return i->value();
  }

  inline       T& operator () (DNode<T> * i)
  {
    return i->value();
  }

  ////////////////////////////////////////////////////////////////////////
  //  Mutators.
  //    Two interfaces are provided:
  //    (1) insert/delete
  ////////////////////////////////////////////////////////////////////////

  DLinkList& clear            ();

  inline DLinkList& insert_before    (DNode<T> *, const T&);
  inline DLinkList& insert_after     (DNode<T> *, const T&);
  inline DLinkList& insert_to_front  (const T& e);
  inline DLinkList& insert_to_back   (const T& e);
  inline DLinkList& remove
    (DNode<T> *);
  inline DLinkList& remove_from_front();
  inline DLinkList& remove_from_back ();

  inline DNode<T> *  unlink           (DNode<T> *);
  inline DNode<T> *  unlink_from_front();
  inline DNode<T> *  unlink_from_back ();
  inline DLinkList& link_to_front     (DNode<T> *);
  inline DLinkList& link_to_back      (DNode<T> *);
  inline DLinkList& link_before       (DNode<T> *, DNode<T> *);
  inline DLinkList& link_after        (DNode<T> *, DNode<T> *);

  ////////////////////////////////////////////////////////////////////////
  //  Short hands.
  ////////////////////////////////////////////////////////////////////////

  inline DLinkList& operator ,  (const T& e)
  {
    return insert_to_back(e);
  }

  inline DLinkList& operator ,  (DNode<T> * n)
  {
    return link_to_back(n);
  }

  inline DLinkList& operator += (const T& e)
  {
    return insert_to_back(e);
  }

  inline DLinkList& operator += (DNode<T> * n)
  {
    return link_to_back(n);
  }

  inline DLinkList& operator =  (const T& e)
  {
    clear();
    return insert_to_back(e);
  }

  inline DLinkList& operator =  (DNode<T> * n)
  {
    clear();
    return link_to_back(n);
  }
};

//////////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructors
//////////////////////////////////////////////////////////////////////////////

template <class T>
DLinkList<T>::DLinkList() : count(0), front(0), back(0)
{}

template <class T>
DLinkList<T>::DLinkList(const DLinkList<T>& l)
    : count(0), front(0), back(0)
{
  *this = l;
}

template <class T>
DLinkList<T>::~DLinkList()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////////////////

template <class T>
DLinkList<T>& DLinkList<T>::operator = (const DLinkList<T>& list)
{
  if (this != &list)
  {
    clear();
    for(DNode<T> * n = list.first(); n; n = list.next(n))
      insert_to_back(n->value());
    count += list.size();
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Emptying the list and frees all nodes.
//////////////////////////////////////////////////////////////////////////////

template <class T>
DLinkList<T>& DLinkList<T>::clear()
{
  typename DLinkList<T>::Ix l;
  while (l = unlink_from_front())
    delete l;
  count = 0;
  back = front = 0;
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Insert an element to the front of the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::insert_to_front  (const T& e)
{  // Make ``e'' the head of the list
  DNode<T> * n = new DNode<T>(e,0,front);
  if (front)
    front->set_prev(n);
  else
    back = n;
  front = n;
  count++;
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Insert an element to the back of the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
DLinkList<T>& DLinkList<T>::insert_to_back(const T& e)
{  // Make ``e'' the tail of the list
  DNode<T> * n = new DNode<T>(e,back,0);
  if (back)
    back->set_next(n);
  else
    front = n;
  back = n;
  count++;
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Insert an element 'e' before position ``pos''.
//  Preconditions:
//     ``pos'' must be non-null and on the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
DLinkList<T>& DLinkList<T>::insert_before( DNode<T> * pos, const T& e)
{  // Insert a new element before position ``pos''.
  // ``pos'' must be non-null.
  if (pos)
  {
    DNode<T> * n = new DNode<T>(e,pos->prev(),pos);
    pos->set_next(n);
    if (pos == front)
      front = n;
    count++;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Insert an element 'e' after position ``pos''.
//  Preconditions:
//     ``pos'' must be non-null and on the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
DLinkList<T>& DLinkList<T>::insert_after( DNode<T> * pos, const T& e)
{  // Insert a new element after position ``pos''.
  // ``pos'' must be non-null.
  if (pos)
  {
    DNode<T> * n = new DNode<T>(e,pos,pos->next());
    pos->set_prev(n);
    if (pos == back)
      back = n;
    count++;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Delete a node from a list.
//  Precondition:
//     The node ``n'' must be on the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::remove( DNode<T> * n)
{
  if (n)
  {
    if (n == front)
      front = n->next();
    if (n == back)
      back  = n->prev();
    if (n->prev())
      n->prev()->set_next(n->next());
    if (n->next())
      n->next()->set_prev(n->prev());
    count--;
    delete n;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Delete a node from the front of the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::remove_from_front()
{
  DNode<T> * n = front;
  if (n)
  {
    front = n->next();
    if (n == back)
      back = n->prev();
    if (n->next())
      n->next()->set_prev(n->prev());
    count--;
    delete n;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Delete a node from the back of the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::remove_from_back()
{
  DNode<T> * n = back;
  if (n)
  {
    back = n->prev();
    if (n == front)
      front = n->next();
    if (n->prev())
      n->prev()->set_next(n->next());
    count--;
    delete n;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Unlink a node ``n'' from a list.
//  Precondition:
//     Node ``n'' must be on the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
DNode<T> * DLinkList<T>::unlink( DNode<T> * n)
{
  if (n)
  {
    if (n == front)
      front = n->next();
    if (n == back)
      back  = n->prev();
    if (n->prev())
      n->prev()->set_next(n->next());
    if (n->next())
      n->next()->set_prev(n->prev());
    count--;
  }
  return n;
}

//////////////////////////////////////////////////////////////////////////////
//  Unlink a node from the front of the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
DNode<T> * DLinkList<T>::unlink_from_front()
{
  DNode<T> * n = front;
  if (n)
  {
    count--;
    if (front = n->next())
      front->set_prev(0);
    else
      back = 0;
  }
  return n;
}

//////////////////////////////////////////////////////////////////////////////
//  Unlink a node from the back of the list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
DNode<T> * DLinkList<T>::unlink_from_back()
{
  DNode<T> * n = back;
  if (n)
  {
    count--;
    if (back = n->prev())
      back->set_next(0);
    else
      front = 0;
  }
  return n;
}

//////////////////////////////////////////////////////////////////////////////
//  Linking operations.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Link ``n'' to front of list.
//  Node ``n'' must not be already on any list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::link_to_front( DNode<T> * n)
{
  if (n)
  {
    n->set_next(front);
    n->set_prev(0);
    if (front)
      front->set_prev(n);
    else
      front = n;
    count++;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Link ``n'' to end of list.
//  Preconditions:
//     Node ``n'' must not be already on any list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::link_to_back( DNode<T> * n)
{
  if (n)
  {
    n->set_next(0);
    n->set_prev(back);
    if (back)
      back->set_next(n);
    else
      back = n;
    count++;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Link node ``n'' before ``pos''.
//  Preconditions:
//     Node ``pos'' must be somewhere on the list.
//     Node ``n'' must not be already on any list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::link_before( DNode<T> * pos, DNode<T> * n)
{
  if (n)
  {
    if (pos)
    {
      if (pos == front)
        front = n;
      n->set_next(pos->next());
      n->set_prev(pos);
      pos->set_next(n);
      count++;
    }
    else
    {
      link_to_front(n);
    }
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Link node ``n'' after ``pos''.
//  Preconditions:
//     Node ``pos'' must be somewhere on the list.
//     Node ``n'' must not be already on any list.
//////////////////////////////////////////////////////////////////////////////

template <class T>
inline DLinkList<T>& DLinkList<T>::link_after( DNode<T> * pos, DNode<T> * n)
{
  if (n)
  {
    if (pos)
    {
      if (pos == back)
        back = n;
      n->set_prev(pos->prev());
      n->set_next(pos);
      pos->set_prev(n);
      count++;
    }
    else
    {
      link_to_back(n);
    }
  }
  return *this;
}

#endif
