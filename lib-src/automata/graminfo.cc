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

#include <string.h>
#include <AD/automata/graminfo.h>
#include <AD/sort/shellsrt.h>  // Shell sort

Bool add_set( register int i, register Byte * a_set, register Byte * b_set)
{
  register Byte changed;
  for (changed = 0; i > 0; i--, a_set++, b_set++)
  {
    changed |= ~ *a_set & *b_set;
    *a_set |= *b_set;
  }
  return changed;
}

void GrammarInfo::compute_info( const Grammar& G)
{
  register Production P;
  register Symbol X;
  register int i;

  clear_info();

  min_non_terminal  = 32767;
  max_non_terminal  = -32768;

  //
  // Preprocess the grammar; compute the following information:
  //
  //   max_non_terminal  -- maximal value of a non-terminal
  //   min_non_terminal  -- minimal value of a non-terminal
  //   productions[i]    -- an array of productions terminated by
  //                           Grammar::END_PRODUCTION
  //

  productions = new Production [ G.size() ];

  for (i = 0; i < G.size(); i++)
  {
    P = productions[i] = G[i];
    while ( (X = *P++) != Grammar::END_PRODUCTION)
    {
      if (G.isNonTerminal(X))
      {
        if (X > max_non_terminal)
          max_non_terminal = X;
        if (X < min_non_terminal)
          min_non_terminal = X;
      }
    }
  }
  production_size = i;

  //
  // Sort by left hand side non-terminal
  //
  shellSort(Production, productions, G.size(),
            key[0] < productions[i][0] );

  //
  // compute the amount of storage needed to store the tables:
  //
  number_of_non_terminals = max_non_terminal - min_non_terminal + 1;
  nullable = new Bool [ number_of_non_terminals ];
  memset(nullable,0,number_of_non_terminals * sizeof(Bool));
  nullable -= min_non_terminal;

  first.create(min_non_terminal,max_non_terminal,G.min_terminal(),G.max_terminal());
  follow.create(min_non_terminal,max_non_terminal,G.min_terminal(),G.max_terminal());

  //
  // Iterate and compute the fix points of first and follow and nullable:
  //
  //   For each A -> X_1 X_2 ... X_n
  //
  //   nullable(A) = /\_i nullable(X_i)
  //   Let first(c)    = { c }
  //   first(A)    <- first(X_i) if nullable(X_1 X_2 ... X_{i-1} c)
  //   follow(X_i) <- first(X_{i+1})
  //
  //
  Bool changed;
  do
  {
    changed = false;
    for (i = G.size() - 1; i >= 0; i--)
    {
      register NonTerminal A;
      register Symbol Y = max_non_terminal + 1;  // Last symbol
      Bool epsilon = true;
      for ( P = productions[i], A = *P++; (X = *P) != END_PRODUCTION; P++)
      {
        if (G.isAction(X))
        {           // X is an action symbol; skip it
        }
        else if (G.isTerminal(X))
        {  // X is a terminal
          if (G.isNonTerminal(Y) && ! follow.has(Y,X))
          {
            follow.insert(Y,X);
            changed = true;
          }
          if (epsilon && ! first.has(A,X))
          {
            first.insert(A,X);
            changed = true;
          }
          epsilon = false;
          Y = X;
        }
        else
        {                       // X is a nonterminal
          if (G.isNonTerminal(Y) &&
              add_set(first.set_size(),follow(X),first(Y)))
            changed = true;
          if (epsilon && add_set(first.set_size(),first(A),first(X)))
            changed = true;
          if (! nullable[X])
            epsilon = false;
          Y = X;
        }
      }
      if (epsilon && ! nullable[A])
      {
        nullable[A] = true;
        changed = true;
      }
    }
  }
  while (changed);
}

void GrammarInfo::clear_info()
{
  if (nullable)
  {
    delete [] productions;
    delete [] (nullable + min_non_terminal);
    first.destroy();
    follow.destroy();
    nullable = 0;
  }
}

GrammarInfo::~GrammarInfo()
{
  clear_info();
}
