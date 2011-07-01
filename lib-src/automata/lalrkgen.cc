//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <iostream.h>
#include <AD/automata/lalrkgen.h>   // LALR(k) parser generator
#include <AD/automata/lr_gla.h>     // LR(k) general lookahead automaton

//////////////////////////////////////////////////////////////////////////////
//  Import some type definitions.
//////////////////////////////////////////////////////////////////////////////

typedef LALR_k_Gen::Symbol      Symbol;
typedef LALR_k_Gen::Terminal    Terminal;
typedef LALR_k_Gen::NonTerminal NonTerminal;
typedef LALR_k_Gen::Production  Production;
typedef LALR_k_Gen::State       State;
typedef LR_GLA::ItemSet         ItemSet;
typedef LR_GLA::NonTerminalSet  NonTerminalSet;

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
