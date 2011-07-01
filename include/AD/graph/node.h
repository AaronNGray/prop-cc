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

#ifndef node_object_h
#define node_object_h

#include <AD/graph/graph_base.h>

//////////////////////////////////////////////////////////////////////////////
//
//  A node object
//
//////////////////////////////////////////////////////////////////////////////

class NodeObject
{
protected:
  typedef struct hidden_node_label * Label;
  Label the_label;

public:
  NodeObject(Label l) : the_label(l)
  {}
  virtual ~NodeObject();
  Label label () const
  {
    return the_label;
  }
  virtual PrettyOStream& print (PrettyOStream&) const;

private:
  friend class GraphObject;
  friend class NodeSet;
  friend class EdgeSet;
  friend class AdjList;
  friend class EdgeObject;
  int label_num () const
  {
    return int(the_label);
  }
};

#endif
