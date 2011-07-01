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

#ifndef attribute_grammar_parse_tree_h
#define attribute_grammar_parse_tree_h

#include <AD/generic/generic.h>
#include <AD/memory/mem.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
//
//  This is the base class of all attribute grammar parser tree nodes
//
//////////////////////////////////////////////////////////////////////////////

class AGParseTree
{
  AGParseTree();                        // no default constructor
  AGParseTree(const AGParseTree&);      // no copy constructor
  void operator = (const AGParseTree&); // no assignment
public:
  static Mem& memory_manager; // the default memory manager
protected:
  AGParseTree * my_sibling;
  AGParseTree * my_child;
public:
  AGParseTree(AGParseTree *, AGParseTree *);
  virtual ~AGParseTree();

  static AGParseTree * make_node(int, AGParseTree *, AGParseTree *);

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Printing interface
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual void print_tree (std::ostream&) const = 0;

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Attribute evaluation interface
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual void visit_node (int alternative, int visit_no);
};

#endif
