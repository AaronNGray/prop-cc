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

#ifndef parametrized_doubly_linked_lists_h
#define parametrized_doubly_linked_lists_h

#include <AD/contain/dlist.h>

template <class T>
class DLinkList : public DList
{
  struct DNode : public DLink
    {
      T element;
      DNode(const T& e) : element(e)
      {}
    };

public:

  //////////////////////////////////////////////////////////////////////
  // Constructor and destructors
  //////////////////////////////////////////////////////////////////////

  DLinkList()
  {}
  DLinkList(const DLinkList&);
  ~DLinkList()
  {}

  //////////////////////////////////////////////////////////////////////
  // Assignment
  //////////////////////////////////////////////////////////////////////

  void operator = (const DLinkList&);

  //////////////////////////////////////////////////////////////////////
  // New mutators
  //////////////////////////////////////////////////////////////////////

  Ix   insert_head  (const T& e)
  {
    return DList::insert_head(new DNode<T>(e));
  }
  Ix   insert_tail  (const T& e)
  {
    return DList::insert_head(new DNode<T>(e));
  }
  Ix   insert_after (Ix i, const T& e)
  {
    return DList::insert_after((DList *)i,new DNode<T>(e));
  }
  Ix   insert_before(Ix i, const T& e)
  {
    return DList::insert_before((DList *)i,new DNode<T>(e));
  }

  //////////////////////////////////////////////////////////////////////
  // New iterators
  //////////////////////////////////////////////////////////////////////

  T& operator () (Ix i)
  {
    return ((DNode<T>*)i)->element;
  }
};

#endif
