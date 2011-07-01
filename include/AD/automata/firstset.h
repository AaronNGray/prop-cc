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

#ifndef first_set_computation_h
#define first_set_computation_h

#include <new>
#include <AD/automata/nullable.h>
#include <AD/contain/bitset.h>
#include <AD/contain/slnklist.h>


//////////////////////////////////////////////////////////////////////////////
//  This class computes the first(A) function for grammar analysis.
//  Since it needs to know whether a non-terminal can derive a null string,
//  we'll inherit from Nullable's implementation.
//////////////////////////////////////////////////////////////////////////////
class FirstSet : public Nullable
{
  FirstSet( const FirstSet&);          // no copy constructor
  void operator = ( const FirstSet&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

  typedef Nullable              Super;
  typedef Super::Symbol         Symbol;
  typedef Super::Terminal       Terminal;
  typedef Super::NonTerminal    NonTerminal;
  typedef Super::Production     Production;
  typedef Super::EquivMap       EquivMap;
  typedef SLinkList<Production> ProductionList;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  BitSet **         first_set;         // array of terminal set indexed by non-terminal
  ProductionList ** production_lists;  // maps non-terminal to productions

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

  FirstSet(const Grammar&, Mem&);
  ~FirstSet();

  ///////////////////////////////////////////////////////////////////////////
  //  Mapping from non-terminal to production list
  ///////////////////////////////////////////////////////////////////////////
  inline ProductionList * productions(NonTerminal A) const
  {
    return production_lists[A];
  }

  ///////////////////////////////////////////////////////////////////////////
  //  first()
  ///////////////////////////////////////////////////////////////////////////
  inline const BitSet& first( NonTerminal A)       const
  {
    return *first_set[A];
  }

  Bool                 first( BitSet&, Production) const;
  Bool                 first( BitSet&, Production, Bool& changed) const;
};

//////////////////////////////////////////////////////////////////////////////
//  Compute the ``first'' set of a production
//  Also returns true iff the production P can derive lambda.
//////////////////////////////////////////////////////////////////////////////

inline Bool FirstSet::first( BitSet& set, Production P) const
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

inline Bool FirstSet::first( BitSet& set, Production P, Bool& changed) const
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
