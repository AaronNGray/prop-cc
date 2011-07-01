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

#ifndef attribute_grammar_parse_tree_nodes_h
#define attribute_grammar_parse_tree_nodes_h

#include <AD/ag/parsetree.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Terminal node of a parse tree.
//
//////////////////////////////////////////////////////////////////////////////

class AGTerminal : public AGParseTree
{
  AGTerminal();                        // no default constructor
  AGTerminal(const AGTerminal&);       // no copy constructor
  void operator = (const AGTerminal&); // no assignment
protected:
  const char * the_id;
public:
  AGTerminal(const char * id, AGParseTree *, AGParseTree *);
  virtual ~AGTerminal();

  virtual void print_tree (std::ostream&) const;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Non-Terminal node of a parse tree.
//
//////////////////////////////////////////////////////////////////////////////

class AGNonterminal : public AGParseTree
{
  AGNonTerminal();                        // no default constructor
  AGNonTerminal(const AGNonTerminal&);    // no copy constructor
  void operator = (const AGNonTerminal&); // no assignment
protected:
  int the_production_number;
public:
  AGNonTerminal(int production_no, AGParseTree *, AGParseTree *);
  virtual ~AGNonTerminal();

  virtual void print_tree (std::ostream&) const;
};

#endif
