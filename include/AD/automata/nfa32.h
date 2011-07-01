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

#ifndef nondeterministic_finite_automata_with_at_most_32_states_h
#define nondeterministic_finite_automata_with_at_most_32_states_h

//
//  NFA represented as a bit vector.  At most 32 states allowed
//

#include <AD/generic/generic.h> // Generic definitions

class NFA32
{
  NFA32( const NFA32&);              // no copy constructor
  void operator = ( const NFA32&);   // no assignment

public:

  typedef LongWord State;

protected:

  int min_symbol;
  int max_symbol;

  State * delta;    // delta transitions
  State * epsilon;  // epsilon transitions
  State the_state;  // current state

public:

  NFA32();
  ~NFA32();

  State& state()
  {
    return the_state;
  }
  void go()
  {}
};

#endif
