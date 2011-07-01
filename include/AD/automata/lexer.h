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

#ifndef lexical_scanner_h
#define lexical_scanner_h

//////////////////////////////////////////////////////////////////////////////
// A standalone, bareboned lexical scanner\cite{Dragon-book}.
//////////////////////////////////////////////////////////////////////////////

#include <AD/automata/dfatable.h>  // dfa tables

class Lexer : public DFATables
{
  Lexer(const Lexer&);              // no copy constructor
  void operator = (const Lexer&);   // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  // Inherit some types
  ///////////////////////////////////////////////////////////////////////////
  typedef DFATables     Super;
  typedef Super::Symbol Symbol; // An input symbol
  typedef Super::State  State;  // A state in the automaton
  typedef Super::Offset Offset; // A state in the automaton
  typedef Super::Rule   Rule;   // Rule number of regular expressions

  ///////////////////////////////////////////////////////////////////////////
  //  The default start state
  ///////////////////////////////////////////////////////////////////////////
  enum Lexer_constants {
    start_state = 1  // the start state
  };

protected:

  ///////////////////////////////////////////////////////////////////////////
  // The lexical scanner tables, compressed.  See Aho et al. for details
  ///////////////////////////////////////////////////////////////////////////
  const Offset * const base;
  const State  * const check;
  const State  * const def;
  const State  * const next;
  const Rule   * const rule;
  const unsigned char * equiv_classes;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor
  ///////////////////////////////////////////////////////////////////////////
  Lexer( const Offset        base_table  [],
         const State         check_table [],
         const State         def_table   [],
         const State         next_table  [],
         const Rule          rule_table  [],
         const unsigned char equiv_table []
       )
      : base(base_table), check(check_table), def(def_table), next(next_table),
      rule(rule_table), equiv_classes(equiv_table)
  {}

  ///////////////////////////////////////////////////////////////////////////
  //  Advance thru the automaton:
  //      method accept(...) --- see if the state is an accept state.
  //      method go(...)     --- advance to a new state.
  ///////////////////////////////////////////////////////////////////////////
  inline Rule accept(State s) const            // accept rule of state
  {
    return rule[s];
  }

  inline State go( State s, Symbol c) const    // advance to the next state
  {
    register Offset offset;
    register int    disp = equiv_classes[c];
    while (check[ offset = base[s] + disp ] != s)
    {
      if ((s = def[ s ]) == 0)
        return 0;
    }
    return next[ offset ];
  }
};

#endif
