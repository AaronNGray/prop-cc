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
#include <AD/automata/llkgen.h>    // LL(k) parser generator definition
#include <AD/automata/follow_k.h>  // Follow set computation
#include <AD/memory/mempool.h>     // Memory pool

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////

typedef Grammar::Symbol      Symbol;
typedef Grammar::Terminal    Terminal;
typedef Grammar::NonTerminal NonTerminal;
typedef Grammar::Action      Action;
typedef Grammar::Production  Production;

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////

LLkGen:: LLkGen()
{}

LLkGen:: LLkGen(const Grammar& G)
{
  compile(G);
}

LLkGen::~LLkGen()
{}

//////////////////////////////////////////////////////////////////////////////
//  Compilation
//////////////////////////////////////////////////////////////////////////////

void LLkGen::compile( const Grammar& G)
{
  MemPool     mem(4096);    // a memory pool
  FollowSet_k F(G,mem);     // follow set module

  ///////////////////////////////////////////////////////////////////////////
  //  Compute nullable/first/follow/predict sets
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //  Emit tables
  ///////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////////
//  Code emission
//////////////////////////////////////////////////////////////////////////////

std::ostream& LLkGen::gen_code( std::ostream& out, const char name[]) const
{
  Super::gen_code(out,name);
  return out;
}
