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
// Allen Leung (leunga@valis.cs.nyu.edu)
// 1994-1996
//////////////////////////////////////////////////////////////////////////////

#ifndef edge_object_h
#define edge_object_h

#include <AD/graph/graph_base.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Edge object represents the base class of an edge
//
//////////////////////////////////////////////////////////////////////////////

class EdgeObject
{
  NodeObject * the_src, * the_dst;

public:
  EdgeObject(NodeObject * a, NodeObject * b)
      : the_src(a), the_dst(b)
  {}
  EdgeObject(const EdgeObject& e)
      : the_src(e.the_src), the_dst(e.the_dst)
  {}
  EdgeObject(const EdgeObject* e)
      : the_src(e->the_src), the_dst(e->the_dst)
  {}
  virtual ~EdgeObject();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Selectors
  //
  ///////////////////////////////////////////////////////////////////////////

  const NodeObject * src() const
  {
    return the_src;
  }
  const NodeObject * dst() const
  {
    return the_dst;
  }
  NodeObject * src()
  {
    return the_src;
  }
  NodeObject * dst()
  {
    return the_dst;
  }

  virtual PrettyOStream& print(PrettyOStream&) const;
};

#endif
