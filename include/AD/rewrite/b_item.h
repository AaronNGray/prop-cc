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
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef BURS_item_h
#define BURS_item_h

#include <iostream>
#include <AD/automata/treegram.h>  // tree grammar
#include <AD/generic/ordering.h>   // hashing functions


//////////////////////////////////////////////////////////////////////////////
//  Items used in the bottom up rewrite system (BURS) generator.
//  An item encodes the following information:
//     (1) A non-terminal,
//     (2) The reduction rule used to arrive at this non-terminal, and
//     (3) The reduction cost.
//////////////////////////////////////////////////////////////////////////////

class BURS_Item
{
  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef TreeGrammar::State       State;
  typedef TreeGrammar::Functor     Functor;
  typedef TreeGrammar::Arity       Arity;
  typedef TreeGrammar::NonTerminal NonTerminal;
  typedef TreeGrammar::Cost        Cost;        // reduction cost
  typedef TreeGrammar::Rule        Rule;        // reduction rule

public:

  ///////////////////////////////////////////////////////////////////////////
  //  The internal representation is visible.
  ///////////////////////////////////////////////////////////////////////////
  Cost cost;   // cost of reduction
  Rule rule;   // reduction rule

  ///////////////////////////////////////////////////////////////////////////
  //  Printing method.
  ///////////////////////////////////////////////////////////////////////////

public:
  friend std::ostream& operator << (std::ostream&, const BURS_Item&);
};

#endif
