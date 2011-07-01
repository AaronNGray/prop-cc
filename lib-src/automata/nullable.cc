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

#include <AD/automata/nullable.h>

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////

typedef Nullable::Symbol         Symbol;
typedef Nullable::Production     Production;
typedef Nullable::Terminal       Terminal;
typedef Nullable::NonTerminal    NonTerminal;
typedef Nullable::EquivMap       EquivMap;

///////////////////////////////////////////////////////////////////////////
// Grammar analysis
///////////////////////////////////////////////////////////////////////////

Nullable::Nullable( register const Grammar& g, Mem& m ) : G(g), mem(m)
{
  register char * null =
    null_set = (char*)mem.c_alloc(sizeof(char) * (g.max_non_terminal() + 1));
  Bool changed;

  ////////////////////////////////////////////////////////////////////////
  // Compute nullable.  This should converge after $n+1$ iterations,
  // where $n$ is the maximal length of a production
  ////////////////////////////////////////////////////////////////////////
  do
  {
    changed = false;
    for (int i = g.size() - 1; i >= 0; i--)
    {
      register Symbol      X;
      register Production  P = g[i];
      NonTerminal A = P[0];
      for (P++; (X = *P) != Grammar::END_PRODUCTION; P++)
        if (g.isTerminal(X) ||
            g.isNonTerminal(X) && ! null[X])
          goto next_iteration;
      if (! null[A])
      {
        null[A] = true;
        changed = true;
      }
next_iteration:
      ;
    }
  }
  while (changed);
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor: memory is deallocated by the Mem destructor.
//////////////////////////////////////////////////////////////////////////////

Nullable::~Nullable()
{}
