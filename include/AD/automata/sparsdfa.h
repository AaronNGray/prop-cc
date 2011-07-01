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

#ifndef sparse_compressed_dfa_tables_h
#define sparse_compressed_dfa_tables_h

//////////////////////////////////////////////////////////////////////////////
// Class |SparseDFA| is used to represent dfa's with ``sparse''
// output transitions, that is, the transition function from each
// state goes to the error state on most symbols.
//////////////////////////////////////////////////////////////////////////////

#include <AD/automata/compdfa.h>  // compressed dfa

class SparseDFA : public CompressedDFA
{
  SparseDFA( const SparseDFA&);          // no copy constructor
  void operator = ( const SparseDFA&);   // no assignment

  //////////////////////////////////////////////////////////////////////////
  //  Internally, class SparseDFA contains a stack of states with
  //  single non-error transition.  These types of states are treated
  //  as a special case to during table compression.
  //
  //  The implementation of this stack is hidden.
  //////////////////////////////////////////////////////////////////////////

  struct SparseDFA_Impl * impl;
  int    offset_base;

public:

  //////////////////////////////////////////////////////////////////////////
  //  Make hidden types visible
  //////////////////////////////////////////////////////////////////////////
  typedef CompressedDFA           Super;
  typedef Super::State            State;
  typedef Super::Symbol           Symbol;
  typedef Super::Offset           Offset;
  typedef Super::Rule             Rule;
  typedef Super::ProductionLength ProductionLength;
  typedef Super::EquivMap         EquivMap;

public:

  //////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////////////////////
  SparseDFA ();
  ~SparseDFA ();

  //////////////////////////////////////////////////////////////////////////
  // Insert a new transition function from state |s|.  Grow table if
  // necessary.  The transition function is represented by the
  // two arrays |symbols| and |delta|, i.e. state |s| goes to state
  // |delta[i]| on |symbols[i]|.  Each array is of length |fan_out|.
  //////////////////////////////////////////////////////////////////////////
  virtual void start();   // start generating tables
  virtual void add_state  // add a new state
  ( State s, int fan_out, const Symbol symbols[], const State delta[] );
  virtual void finish();  // finish generating tables

  //////////////////////////////////////////////////////////////////////////
  // Advance thru the automata.  Notice that the table is derived so that
  // |go(error_state,c) == error_state| for all symbols |c|.
  //////////////////////////////////////////////////////////////////////////
  inline State go( register State s, register Symbol c) const
  {
    register State offset;
    return check[offset = base[s] + c] == s ? next[offset]
           : (State)error_state;
  }
};

#endif
