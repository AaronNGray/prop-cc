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

#ifndef prop_deterministic_finite_automata_h
#define prop_deterministic_finite_automata_h

#include <AD/automata/nfa.h>

class DFA : public NFA
{
  DFA( const DFA&);                // no copy constructor
  void operator = ( const DFA&);   // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import inherited types
  ///////////////////////////////////////////////////////////////////////////
  typedef NFA           Super;
  typedef Super::Symbol Symbol;
  typedef Super::State  State;
  typedef Super::PState PState;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////
  DFA( Symbol min, Symbol max);
  DFA( const NFA&);
  virtual ~DFA();

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //  Mutators
  ///////////////////////////////////////////////////////////////////////////
  virtual void add( State s, int fan_out, const Symbol[], const State[]);
  virtual void minimize_dfa();
};

#endif
