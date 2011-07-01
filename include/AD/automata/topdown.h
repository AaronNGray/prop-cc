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

#ifndef top_down_tree_matcher_h
#define top_down_tree_matcher_h

#include <AD/automata/ac.h>    // Aho-Corasick string matcher

//////////////////////////////////////////////////////////////////////////////
//
//  The top-down tree matching algorithm\cite{tree-matching, AC}
// reduces the problem of tree matching to the problem of string matching
// a set of path strings.
//
//////////////////////////////////////////////////////////////////////////////

class TopDown : public AC
{
  TopDown(const TopDown&);           // no copy constructor
  void operator = (const TopDown&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  // Inherit some types
  ///////////////////////////////////////////////////////////////////////////
  typedef AC            Super;
  typedef Super::Symbol Symbol;
  typedef Super::Rule   Rule;
  typedef Super::Offset Offset;
  typedef Super::State  State;

public:

  /////////////////////////////////////////////////////////////////////////
  //  Constructor
  /////////////////////////////////////////////////////////////////////////
  TopDown( const Offset base_table  [],
           const State  check_table [],
           const State  failure     [],
           const State  next_table  [],
           const Rule   rule_table  []
         ) : AC(base_table, check_table, next_table, failure, rule_table)
  {}

  ///////////////////////////////////////////////////////////////////////////
  // Return the start state
  ///////////////////////////////////////////////////////////////////////////
  inline State start_state() const
  {
    return 0;
  }

  ///////////////////////////////////////////////////////////////////////////
  // Advance one state within the tree matching automaton
  ///////////////////////////////////////////////////////////////////////////
  inline State go( State s, int branch, Symbol c) const
  {
    return Super::go( Super::go( s, branch), c);
  }
};

#endif
