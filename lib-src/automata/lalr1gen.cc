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

//////////////////////////////////////////////////////////////////////////////
//  This file contains the implementation of class |LALR1Gen|, which
//  is a parser table generator for LALR(1) grammars.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  A whole bunch of include files.
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <new.h>
#include <AD/automata/lalr1gen.h>   // LALR(1) parser generator
#include <AD/automata/lr0.h>        // LR(0) finite state machine
#include <AD/automata/lookahd.h>    // Lookahead set computation
#include <AD/memory/mempool.h>      // Memory pools

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////

typedef LR0::ItemNum         ItemNum;
typedef Grammar::Symbol      Symbol;
typedef Grammar::Terminal    Terminal;
typedef Grammar::NonTerminal NonTerminal;
typedef Grammar::EquivMap    EquivMap;
typedef LALR1Gen::State      State;

//////////////////////////////////////////////////////////////////////////////
//  The implementation of this class is hidden below
//////////////////////////////////////////////////////////////////////////////

struct LALR1Gen_Impl
{
  const Grammar&  G;       // the current grammar
  MemPool         mem;     // memory pool
  LR0             lr0;     // the characteristic LR(0) finite state machine
  LookaheadSets   la_sets; // the lookahead sets

  ///////////////////////////////////////////////////////////////////////////
  // The constructor
  ///////////////////////////////////////////////////////////////////////////
  LALR1Gen_Impl(const Grammar& g, const OpPrecedence& P) :
      G(g),                         // set up the grammar
      mem(4096),                    // create a memory pool (4K pages)
      lr0(G,P,mem),                 // create a LR(0) dfa
      la_sets(G, P, lr0, mem, true) // Compute the lookahead sets!!!
  {}

private:
  LALR1Gen_Impl(const LALR1Gen_Impl&);    // no copy constructor
  void operator = (const LALR1Gen_Impl&); // no assignment
};

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////

LALR1Gen:: LALR1Gen() : impl(0)
{}

LALR1Gen:: LALR1Gen( const Grammar& G, const OpPrecedence& P)
    : impl(0)
{
  compile(G,P);
}

LALR1Gen::~LALR1Gen()
{
  delete impl;
}

//////////////////////////////////////////////////////////////////////////////
//  Entry point of the parser compiler.
//  Briefly, the algorithm is as follows:
//    (a) Compute the characteristic finite state machine (CFSM), i.e.
//        the LR(0) dfa.
//    (b) Set all lookahead sets to empty and propagate lookahead sets
//        until the least fixed point is reached.
//////////////////////////////////////////////////////////////////////////////

void LALR1Gen::compile(const Grammar& G, const OpPrecedence& P)
{
  ///////////////////////////////////////////////////////////////////////////
  //  Let the super class do its stuff first
  ///////////////////////////////////////////////////////////////////////////
  Super::compile(G);

  ///////////////////////////////////////////////////////////////////////////
  // Initialize a new implementation
  ///////////////////////////////////////////////////////////////////////////
  delete impl;
  impl = new LALR1Gen_Impl(G, P);

  ///////////////////////////////////////////////////////////////////////////
  // Preprocess grammar and compute the CSFM.
  ///////////////////////////////////////////////////////////////////////////
  MemPool&       mem     = impl->mem; // memory pool
  LR0&           lr0     = impl->lr0; // the characteristic LR(0) FSM
  LookaheadSets& la_sets = impl->la_sets;

  ///////////////////////////////////////////////////////////////////////////
  // Start generating the parser tables.
  ///////////////////////////////////////////////////////////////////////////
  create_tables(lr0.number_of_states() * 2, // an estimate only!
                lr0.number_of_states(),
                0, G.max_non_terminal());
  start();
  clear_errors();

  ///////////////////////////////////////////////////////////////////////////
  // Now compute the transition function of each state.
  // Also look for shift-reduce, reduce-reduce conflicts and resolve
  // them if possible.
  ///////////////////////////////////////////////////////////////////////////
  int num_of_symbols = G.number_of_symbols();
  int num_of_states  = lr0.number_of_states();
  State  * delta     = (State *)mem.m_alloc(sizeof(State)*num_of_symbols);
  Symbol * syms      = (Symbol*)mem.m_alloc(sizeof(Symbol)*num_of_symbols);
  State  * singleton = (State*)mem.c_alloc(sizeof(State) * num_of_states);
  // for (State s = num_of_states - 1; s > 0; s--)
  for (State s = 1; s < num_of_states; s++)
  {
    State default_reduce;
    int fan_out = la_sets.transitions(s, syms, delta, default_reduce);
    add_state(s, fan_out, syms, delta);
    defact[s] = default_reduce;
    //len[s]    = lr0[s]->len();
    //ncount[s] = lr0[s]->ncount(G);

    // if it is reducing using the last rule then
    // it is an accept state.
    if (G.isReduce(default_reduce) &&
        G.reduceRule(default_reduce) == G.size() - 1)
    {
      final = s;
    }

    // A state is a singleton if the only action from this state
    // is reduction.
    if ((fan_out == 0 && G.isReduce(default_reduce)) ||
        fan_out == 1 && syms[0] > G.max_normal_non_terminal())
    {
      singleton[s] = default_reduce;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Set the error counts
  ///////////////////////////////////////////////////////////////////////////
  shift_reduce_error_count  = la_sets.shift_reduce_conflicts();
  reduce_reduce_error_count = la_sets.reduce_reduce_conflicts();

  ///////////////////////////////////////////////////////////////////////////
  // Finish the table compression process.
  ///////////////////////////////////////////////////////////////////////////
  finish();

  ///////////////////////////////////////////////////////////////////////////
  //  Update shift actions into singleton states
  //  If the destination state can only be reduced and if it is not
  //  the final state.
  ///////////////////////////////////////////////////////////////////////////
  for (int i = 0; i <= max_check; i++)
  {
    State s = next[i];
    if (s != Grammar::error_state && G.isShift(s) && s != check[i]
        && singleton[s] && s != final)
    {
      next[i] = G.makeShiftReduce(s);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Report printing
//////////////////////////////////////////////////////////////////////////////

std::ostream& LALR1Gen::print_report(std::ostream& out, int verbosity)
{
  const Grammar&  G = impl->G;
  LookaheadSets& la = impl->la_sets;

  out << "Grammar (" << G.size() << " rules):\n" << G << '\n';
  la.print_report(out,verbosity & 1, verbosity & 2);
  out << "Max next/check                     = " << (max_check + 1) << '\n'
  << "Equivalence map size               = " << map_size() << '\n'
  << "Memory used (in k-bytes)           = " <<
  (impl->mem.bytes_used() + 512) / 1024 << '\n'
  ;
  return out;
}
