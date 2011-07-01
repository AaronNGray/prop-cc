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

#ifndef regular_tree_matcher_h
#define regular_tree_matcher_h

//////////////////////////////////////////////////////////////////////////
//
// Class |TreeMatcher| represents a tree automaton with compressed
// lookup tables.  See class |TreeGen| for the generator.
//
//////////////////////////////////////////////////////////////////////////

#include <AD/automata/treetab.h>  // tree automata tables

class TreeMatcher : public TreeTables
{
  TreeMatcher( const TreeMatcher&);       // no copy constructor
  void operator = ( const TreeMatcher&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////
  //  Inport some types
  ///////////////////////////////////////////////////////////////////////
  typedef TreeTables     Super;
  typedef Super::Functor Functor;
  typedef Super::Arity   Arity;
  typedef Super::State   State;
  typedef Super::Offset  Offset;
  typedef Super::Rule    Rule;

protected:

  ///////////////////////////////////////////////////////////////////////
  //  Compressed tables
  ///////////////////////////////////////////////////////////////////////
  const Arity  * const arity;   // Mapping from functors to arities
  const Offset * const base;    // Mapping from functors to base offset
  const State  * const index;   // Tables mu and theta in linearized form

public:

  ///////////////////////////////////////////////////////////////////////
  //  Constructor
  ///////////////////////////////////////////////////////////////////////
  TreeMatcher(
      const Arity  arity_table[],
      const Offset base_table [],
      const State  index_table[]
      ) : arity(arity_table), base(base_table), index(index_table)
  {}

  ///////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////

  inline int rank( Functor f) const
  {
    return arity[f];
  }

  //////////////////////////////////////////////////////////////////////////
  // Advance one state within the tree automaton.
  //    The first go() function is an optimized form for a unit functor--
  // i.e. a functor with 0 arity.  The second go() function is the general
  // form which looks up all three tables.
  //////////////////////////////////////////////////////////////////////////

  inline State go( Functor f) const
  {
    return (State) base[f];
  }
  inline State go(Functor f, const State * inputs) const
  {
    register Offset offset;         // current offset
    register const State * indices; // indices;
    register int i;
    for (i = arity[f], offset = base[f], indices = index + offset + 1;
         i > 0; i--, indices += indices[-1])
      offset += indices[ *inputs++ ];
    return index[offset];
  }
};

#endif
