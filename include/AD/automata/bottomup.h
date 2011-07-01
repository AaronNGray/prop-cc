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

#ifndef prop_bottomup_pattern_matching_automata_h
#define prop_bottomup_pattern_matching_automata_h

/////////////////////////////////////////////////////////////////////////////
//  Bottom up tree matching automata\cite{tree-matching}.
//
//  Note: we'll use the index compression techique in\cite{Chase87} and
//  the match set unifiers in \cite{Lippe}.  Please see references
//  for details.
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/automata/treeauto.h>  // Tree automaton
#include <AD/automata/treepat.h>   // Tree patterns

class BottomUp : public TreeAutomaton
{
  BottomUp( const BottomUp&);          // no copy constructor
  void operator = ( const BottomUp&);  // no assignment

public:

  //////////////////////////////////////////////////////////////////////////
  //  Inherit types
  //////////////////////////////////////////////////////////////////////////
  typedef TreeAutomaton  Super;
  typedef Super::Offset  Offset;    // table offsets
  typedef Super::State   State;     // a state in the tree matcher
  typedef Super::Functor Functor;   // constructor of a term
  typedef Super::Arity   Arity;     // arity of a functor

public:

  //////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  //////////////////////////////////////////////////////////////////////////
  BottomUp( Mem&);
  ~BottomUp();

  //////////////////////////////////////////////////////////////////////////
  // Compilation and code generation
  //////////////////////////////////////////////////////////////////////////
  virtual void         compile( TreePatterns&);
  virtual const char * algorithm() const;
};

#endif
