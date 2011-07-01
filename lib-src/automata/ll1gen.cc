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

#include <iostream.h>
#include <string.h>
#include <AD/automata/ll1gen.h>   // LL(1) parser generator
#include <AD/automata/follow.h>   // Follow set computation
#include <AD/memory/mempool.h>    // Memory pool

/////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
/////////////////////////////////////////////////////////////////////////

LL1Gen::LL1Gen()
{} // nothing to add

LL1Gen::~LL1Gen()
{} // nothing to add

/////////////////////////////////////////////////////////////////////////
//  Entry point of the compiler
/////////////////////////////////////////////////////////////////////////

void LL1Gen::compile(const Grammar& G)
{
  MemPool     mem(4096);  // memory pool
  FollowSet   F(G,mem);   // compute the follow set

  //////////////////////////////////////////////////////////////////////
  // Allocate the dfa tables
  //////////////////////////////////////////////////////////////////////
  create_tables( G.number_of_terminals() * 3, G.number_of_non_terminals(),
                 G.min_terminal(), G.max_terminal() );

  //////////////////////////////////////////////////////////////////////
  // Allocate a mapping from non-terminals A to sets of terminals
  // that A predicts.
  //////////////////////////////////////////////////////////////////////
  BitSet ** predict_set = new BitSet * [ G.max_non_terminal() + 1 ];
  {
    for (Symbol A = G.min_non_terminal(); A <= G.max_non_terminal(); A++)
    {
      predict_set[A] = new (mem, G.max_terminal() + 1) BitSet;
    }
  }

  //////////////////////////////////////////////////////////////////////
  //  Allocate temporary buffers
  //////////////////////////////////////////////////////////////////////
  Symbol * symbols = new Symbol [ G.number_of_terminals() ];
  State  * delta   = new State  [ G.number_of_terminals() ];
  //int fan_out;          // fan out of a state

  //////////////////////////////////////////////////////////////////////
  // Now compute the predict sets.
  //
  // predict(A -> XYZ) = first(XYZ) if ! nullable(XYZ)
  //                     first(XYZ) U follow(A) if nullable(XYZ)
  // predict_set(A) = U predict(A->XYZ)
  //////////////////////////////////////////////////////////////////////
  BitSet * predict = new (mem, G.max_terminal() + 1) BitSet;
  {
    for (int i = 0; i < G.size(); i++)
    {
      Symbol     A = G.lhs(i);
      Production P = G.rhs(i);
      predict->clear();
      if (F.first(*predict,P))
        predict->Union(F.follow(A));
    }
  }

  //////////////////////////////////////////////////////////////////////
  //  Compute the states
  //////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////
  //  Clean up properly
  //////////////////////////////////////////////////////////////////////
  delete [] symbols;
  delete [] delta;
  delete [] predict_set;
}

/////////////////////////////////////////////////////////////////////////
// Code emitter
/////////////////////////////////////////////////////////////////////////

std::ostream& LL1Gen::gen_code( std::ostream& out, const char name[]) const
{
  return Super::gen_code( out, name);
}
