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

#ifndef singly_linked_list_h
#define singly_linked_list_h

#include <AD/generic/generic.h>
#include <AD/contain/slink.h>

class SList
{
  int     len;   // current length of list
  SLink * front; // front of the list

  SList( const SList&);            // no copy constructor
  void operator = ( const SList&); // no assignment

  ///////////////////////////////////////////////////////////////
  // Constructors and destructor
  ///////////////////////////////////////////////////////////////

public:
  SList() : len(0), front(0)
  {}
  ~SList()
  {
    clear();
  }

  ///////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////

  int length() const
  {
    return len;
  }

  int capacity() const
  {
    return len;
  }

  Bool is_empty() const
  {
    return len == 0;
  }

  Bool is_full() const
  {
    return false;
  }

  ///////////////////////////////////////////////////////////////
  // Mutators
  ///////////////////////////////////////////////////////////////

  void clear();
  void insert_head( SLink *);
  SLink* delete_head();
  void insert_after( SLink *, SLink *);

  ///////////////////////////////////////////////////////////////
  // Iterators
  ///////////////////////////////////////////////////////////////

  SLink* first() const
  {
    return front;
  }

  SLink* next( SLink * l) const
  {
    return l->next;
  }
  SLink* circ_next( SLink* l) const
  {
    return l->next ? l->next : front;
  }
};

#endif
