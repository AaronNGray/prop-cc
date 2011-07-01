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

#include <new.h>
#include <AD/automata/firstset.h>

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////

typedef FirstSet::Symbol         Symbol;
typedef FirstSet::Production     Production;
typedef FirstSet::Terminal       Terminal;
typedef FirstSet::NonTerminal    NonTerminal;
typedef FirstSet::ProductionList ProductionList;
typedef FirstSet::EquivMap       EquivMap;

///////////////////////////////////////////////////////////////////////////
// Grammar analysis
///////////////////////////////////////////////////////////////////////////

FirstSet::FirstSet
( register const Grammar& g,    // grammar
  Mem&                    m     // memory manager
) : Nullable(g, m)
{
  NonTerminal min = g.min_non_terminal();
  NonTerminal max = g.max_non_terminal();
  int    set_size = g.max_terminal() + 1;
  first_set       = (BitSet**)mem.c_alloc(sizeof(BitSet*) * (max + 1));
  Bool changed;

  ////////////////////////////////////////////////////////////////////////
  //  Compute the production list
  ////////////////////////////////////////////////////////////////////////
  production_lists =
    (ProductionList**)mem.c_alloc(sizeof(ProductionList*) * (max+1));
  {
    for (int i = 0; i < g.size(); i++)
    {
      Production  P = g[i];
      NonTerminal A = P[0];
      production_lists[A] = new (mem, P, production_lists[A]) ProductionList;
    }
  }

  ////////////////////////////////////////////////////////////////////////
  // Clear the first sets.
  ////////////////////////////////////////////////////////////////////////
  {  for (int i = min; i <= max; i++)
      first_set[i] = new (mem, set_size) BitSet;
  }

  ////////////////////////////////////////////////////////////////////////
  // Compute first
  ////////////////////////////////////////////////////////////////////////
  do
  {
    changed = false;
    for (int i = 0; i < g.size(); i++)
    {
      register Symbol      X;
      register Production  P = g[i];
      NonTerminal A = P[0];
      register BitSet&   fst = *first_set[A];
      for (P++; (X = *P) != Grammar::END_PRODUCTION; P++)
      {
        if (g.isTerminal(X))
        {
          if (! fst[X])
          {
            fst.add(X);
            changed = true;
          }
          break;
        }
        if (g.isNonTerminal(X))
        {
          if (fst.Union_if_changed(*first_set[X]))
            changed = true;
          if (! null_set[X])
            break;
        }
      }
    }
  }
  while (changed);
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor: memory is deallocated by the Mem destructor.
//////////////////////////////////////////////////////////////////////////////

FirstSet::~FirstSet()
{}

#if 0
//////////////////////////////////////////////////////////////////////////////
//  Compute the ``first'' set of a production
//  Also returns true iff the production P can derive lambda.
//////////////////////////////////////////////////////////////////////////////

Bool FirstSet::first( BitSet& set, Production P) const
  {
    Symbol X;
    for ( ; (X = *P) != Grammar::END_PRODUCTION; P++)
    {
      if (G.isTerminal(X))
      {
        set.add(X);
        return false;
      }
      if (G.isNonTerminal(X))
      {
        set.Union(*first_set[X]);
        if (! null_set[X])
          return false;
      }
    }
    return true;
  }

//////////////////////////////////////////////////////////////////////////////
//  Compute the ``first'' set of a production
//  Also returns true iff the production P can derive lambda.
//  All set changed if set has changed.
//////////////////////////////////////////////////////////////////////////////

Bool FirstSet::first( BitSet& set, Production P, Bool& changed) const
  {
    Symbol X;
    for ( ; (X = *P) != Grammar::END_PRODUCTION; P++)
    {
      if (G.isTerminal(X))
      {
        if (set
            [X] == 0) changed = true;
        set.add(X);
        return false;
      }
      if (G.isNonTerminal(X))
      {
        if (set.Union_if_changed(*first_set[X]))
          changed = true;
        if (! null_set[X])
          return false;
      }
    }
    return true;
  }
#endif
