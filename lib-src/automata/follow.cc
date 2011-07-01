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

#include <AD/automata/follow.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

FollowSet::FollowSet(const Grammar& g, Mem& m) : FirstSet(g,m)
{  // int  min      = G.min_terminal();
  int  max      = G.max_non_terminal();
  int  set_size = G.max_terminal() + 1;

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate memory for the follow set
  ///////////////////////////////////////////////////////////////////////////
  follow_set = (BitSet**)m.c_alloc(sizeof(BitSet*) * (max + 1));
  {
    for (int i = G.min_non_terminal(); i <= G.max_non_terminal(); i++)
    {
      follow_set[i] = new (m, set_size) BitSet;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the follow set.
  //  Iterate until fixed point is reached
  ///////////////////////////////////////////////////////////////////////////
  Bool changed;
  do
  {
    changed = false;
    ////////////////////////////////////////////////////////////////////////
    //  For each production A -> xyz.
    //  For each non-terminal X in    A -> a X b
    //    (1)   new follow(X) = follow(X) union first(b)
    //    (2)   new follow(X) = follow(X) union follow(A)  if nullable(b)
    ////////////////////////////////////////////////////////////////////////
    for (int i = g.size() - 1; i >= 0; i--)
    {
      register Symbol     X;
      register Production P = g[i];
      Symbol     A = P[0]; // A -> a X b
      for (P++; (X = *P++) != Grammar::END_PRODUCTION; )
      {
        if (g.isNonTerminal(X)              &&
            first(*follow_set[X],P,changed) &&
            X != A                          && // a slight optimization
            follow_set[X]->Union_if_changed(*follow_set[A]))
          changed = true;
      }
    }
  }
  while (changed);
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor.  Do nothing since memory is handled by the memory pool
//////////////////////////////////////////////////////////////////////////////

FollowSet::~FollowSet()
{}
