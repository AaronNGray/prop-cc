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

#ifndef bottom_up_rewrite_system_generator_h
#define bottom_up_rewrite_system_generator_h

#include <iostream>
#include <AD/automata/treeauto.h>  // Tree automata
#include <AD/automata/treegram.h>  // Tree grammars


//////////////////////////////////////////////////////////////////////////////
//
// The class BURS_Gen generates a tree-matching automaton (annotated with
// cost) using an algorithm due to Todd A. Proebsting.  See PLDI '92.
//
// The table representation is derived from class TreeAutomaton, which
// provides the low-level methods for table memory allocation and
// printing.
//
//////////////////////////////////////////////////////////////////////////////

class BURS_Gen : public TreeAutomaton
{
  BURS_Gen(const BURS_Gen&);            // no copy constructor
  void operator = (const BURS_Gen&);    // no assignment

  ///////////////////////////////////////////////////////////////////////////
  // Inherit some types from superclass and make them visible.
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef TreeAutomaton      Super;
  typedef Super::Functor     Functor;     // functor
  typedef Super::Variable    Variable;    // pattern variable
  typedef Super::NonTerminal NonTerminal; // non-terminal in automata
  typedef Super::Arity       Arity;       // arity of functor
  typedef Super::State       State;       // state in tree automata
  typedef Super::Cost        Cost;        // reduction cost
  typedef Super::Rule        Rule;        // reduction rule number

  ///////////////////////////////////////////////////////////////////////////
  //  The internal representation of this class is completely hidden.
  ///////////////////////////////////////////////////////////////////////////

private:
  class BURS_Generator * impl;  // opaque! for your sanitary protection.

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  BURS_Gen( Mem& );
  BURS_Gen( Mem&, TreeGrammar& );
  virtual ~BURS_Gen();

  ///////////////////////////////////////////////////////////////////////////
  //  Compilation and table emission methods.
  ///////////////////////////////////////////////////////////////////////////
  virtual void compile (TreeGrammar&);
  virtual void clear   ();

  ///////////////////////////////////////////////////////////////////////////
  //  Check for completeness.
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool is_complete() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for code generation and report generation.
  ///////////////////////////////////////////////////////////////////////////
  virtual std::ostream& print_report (std::ostream&) const;
  virtual std::ostream& print_state (std::ostream&, State) const;

  ///////////////////////////////////////////////////////////////////////////
  //  Algorithm name
  ///////////////////////////////////////////////////////////////////////////
  virtual const char * algorithm () const;
};

#endif
