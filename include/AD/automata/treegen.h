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

#ifndef deterministic_finite_state_tree_automata_generator_h
#define deterministic_finite_state_tree_automata_generator_h

#include <iostream>
#include <AD/automata/treeauto.h>  // Tree automata
#include <AD/automata/treegram.h>  // Tree grammars


//////////////////////////////////////////////////////////////////////////////
//
// The class TreeGen generates a tree-matching automaton
// using a NFA to DFA subset construction generalized to
// k-algebra/tree grammars.
//
//////////////////////////////////////////////////////////////////////////////

class TreeGen : public TreeAutomaton
{

  TreeGen( const TreeGen&);             // no copy constructor
  void operator = ( const TreeGen&);    // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  // Inherit some types
  ///////////////////////////////////////////////////////////////////////////
  typedef TreeAutomaton               Super;
  typedef Super::Functor              Functor;
  typedef Super::Functor              Variable;
  typedef Super::Arity                Arity;
  typedef Super::State                State;
  typedef TreeGrammar::TreeProduction TreeProduction;

private:

  ///////////////////////////////////////////////////////////////////////////
  //  Internal data structure.
  ///////////////////////////////////////////////////////////////////////////
  class TreeGenerator* impl;  // opaque! for your sanitary protection.

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////
  TreeGen( Mem&);
  TreeGen( Mem&, TreeGrammar&);
  virtual ~TreeGen();

  ///////////////////////////////////////////////////////////////////////////
  //  Compilation and table emission
  ///////////////////////////////////////////////////////////////////////////
  virtual void compile( TreeGrammar&);
  virtual std::ostream& print_report( std::ostream&) const;
  virtual std::ostream& print_state( std::ostream&, State) const;

  ///////////////////////////////////////////////////////////////////////////
  //  Name of algorithm
  ///////////////////////////////////////////////////////////////////////////
  virtual const char * algorithm() const;
};

#endif
