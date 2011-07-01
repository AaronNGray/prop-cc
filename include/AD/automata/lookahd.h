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

#ifndef LALR1_lookahead_sets_h
#define LALR1_lookahead_sets_h

#include <iostream>
#include <AD/automata/grammar.h>  // Grammar
#include <AD/automata/lr0.h>      // LR(0) finite state machine
#include <AD/automata/operprec.h> // operator precedence
#include <AD/memory/mem.h>        // Memory manager
#include <AD/contain/bitset.h>    // Bit sets


//////////////////////////////////////////////////////////////////////////////
//  Class for computing the lookahead sets in LALR(1) parser generation.
//////////////////////////////////////////////////////////////////////////////

class LookaheadSets
{
  LookaheadSets( const LookaheadSets&);     // no copy constructor
  void operator = ( const LookaheadSets&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import types
  ///////////////////////////////////////////////////////////////////////////
  typedef Grammar::Symbol      Symbol;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Terminal    Terminal;
  typedef Grammar::Production  Production;
  typedef Grammar::EquivMap    EquivMap;
  typedef LR0::Rule            Rule;
  typedef LR0::State           State;
  typedef LR0::ItemNum         ItemNum;
  typedef LR0::ItemSet         ItemSet;

  ///////////////////////////////////////////////////////////////////////////
  // Shift or Reduce
  ///////////////////////////////////////////////////////////////////////////
  enum ShiftReduce { SHIFT, REDUCE };

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Hidden implementation
  ///////////////////////////////////////////////////////////////////////////
  struct LookaheadSets_Impl * impl;

  ///////////////////////////////////////////////////////////////////////////
  //  Members
  ///////////////////////////////////////////////////////////////////////////
  const Grammar&         G;    // the grammar
  const OpPrecedence&    prec; // operator precedence
  LR0&                   lr0;  // LR(0) dfa
  Mem&                   mem;  // memory manager

  ///////////////////////////////////////////////////////////////////////////
  //  Error counts
  ///////////////////////////////////////////////////////////////////////////
  int shift_reduce_error_count;
  int reduce_reduce_error_count;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  LookaheadSets( const Grammar&,       // the grammar
                 const OpPrecedence&,  // operator precedence
                 LR0&,                 // LR(0) core
                 Mem&,                 // memory manager
                 Bool lazy = false
               );
  virtual ~LookaheadSets();

  ///////////////////////////////////////////////////////////////////////////
  //  Transition computation
  ///////////////////////////////////////////////////////////////////////////
  int transitions( State, Symbol [], State [], State&, std::ostream * log = 0);

  ///////////////////////////////////////////////////////////////////////////
  //  Conflict resolution
  ///////////////////////////////////////////////////////////////////////////
  ShiftReduce resolve_shift_reduce_conflict( ItemNum i, Terminal, std::ostream *);
  ShiftReduce resolve_reduce_reduce_conflict( ItemNum i, Terminal, std::ostream *);

  ///////////////////////////////////////////////////////////////////////////
  //  Error counts
  ///////////////////////////////////////////////////////////////////////////
  inline int shift_reduce_conflicts()  const
  {
    return shift_reduce_error_count;
  }

  inline int reduce_reduce_conflicts() const
  {
    return reduce_reduce_error_count;
  }

  inline int conflicts()               const
  {
    return shift_reduce_conflicts() + reduce_reduce_conflicts();
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Print a report
  ///////////////////////////////////////////////////////////////////////////
  std::ostream& print_report( std::ostream&, Bool print_closures, Bool print_lookaheads);
};

#endif
