//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1997
//////////////////////////////////////////////////////////////////////////////

#ifndef graphtype_base_class_h
#define graphtype_base_class_h

#include <AD/generic/generic.h>

//////////////////////////////////////////////////////////////////////////////
//
//  This class represents the base class to all graphtype objects generated
//  by Prop.
//
//////////////////////////////////////////////////////////////////////////////

class GraphType
{
  GraphType(const GraphType&);
  void operator = (const GraphType&);
public:
  struct Link
  {
    Link * next, * prev;
    inline void unlink()
    {
      prev->next = next;
      next->prev = prev;
      next = prev = 0;
    }
    inline void link(Link& l) // this is a sentinel
    {  l.next = next;
      l.prev = this;
      next->prev = next = &l;
    }
    inline Bool non_nil() const
    {
      return next != 0;
    }
    inline Bool is_nil() const
    {
      return next == 0;
    }
    inline Bool is_empty() const
    {
      return next == this;
    }
  };
public:
  GraphType();
  virtual ~GraphType();
};

#endif
