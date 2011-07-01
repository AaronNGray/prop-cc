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

#ifndef cached_first_set_computation_h
#define cached_first_set_computation_h

#include <AD/automata/firstset.h>
#include <AD/hash/lhash.h>

//////////////////////////////////////////////////////////////////////////////
//  This class computes the first(A) function for grammar analysis.
//  Since it needs to know whether a non-terminal can derive a null string,
//  we'll inherit from Nullable's implementation.
//////////////////////////////////////////////////////////////////////////////

class CachedFirstSetProduction;

inline unsigned int hash( CachedFirstSetProduction * P)
{
  return (unsigned int)P;
}

inline Bool equal( CachedFirstSetProduction * a, CachedFirstSetProduction * b)
{
  return a == b;
}

class CachedFirstSet : public FirstSet
{

  CachedFirstSet( const CachedFirstSet&);    // no copy constructor
  void operator = ( const CachedFirstSet&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

  typedef FirstSet              Super;
  typedef Super::Symbol         Symbol;
  typedef Super::Terminal       Terminal;
  typedef Super::NonTerminal    NonTerminal;
  typedef Super::Production     Production;
  typedef Super::EquivMap       EquivMap;
  typedef Super::ProductionList ProductionList;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  struct FirstAndNullable
  {
    BitSet * first;
    Bool     nullable;
  };

  typedef LHashTable <CachedFirstSetProduction *, FirstAndNullable> FirstCache;
  FirstCache Fs;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

  CachedFirstSet(const Grammar&, Mem&);
  ~CachedFirstSet();

  ///////////////////////////////////////////////////////////////////////////
  //  first()
  ///////////////////////////////////////////////////////////////////////////
  Bool first( BitSet&, Production) const;
  Bool first( BitSet&, Production, Bool& changed) const;
};

//////////////////////////////////////////////////////////////////////////////
//  Compute the ``first'' set of a production
//  Also returns true iff the production P can derive lambda.
//////////////////////////////////////////////////////////////////////////////

inline Bool CachedFirstSet::first( BitSet& set, Production P) const
{
  Ix ix = Fs.lookup((CachedFirstSetProduction *)P);
  if (ix)
  {
    const FirstAndNullable& f = Fs.value(ix);
    set.Union(*f.first);
    return f.nullable;
  }
  else
  {
    FirstAndNullable f;
    f.first = new (mem, set.size()) BitSet;
    f.nullable = Super::first(*f.first,P);
    ((FirstCache *)&Fs)->insert((CachedFirstSetProduction *)P,f);
    set.Union(*f.first);
    return f.nullable;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Compute the ``first'' set of a production
//  Also returns true iff the production P can derive lambda.
//  All set changed if set has changed.
//////////////////////////////////////////////////////////////////////////////

inline Bool CachedFirstSet::first( BitSet& set, Production P, Bool& changed) const
{
  Ix ix = Fs.lookup((CachedFirstSetProduction *)P);
  if (ix)
  {
    const FirstAndNullable& f = Fs.value(ix);
    changed = set.Union_if_changed(*f.first);
    return f.nullable;
  }
  else
  {
    FirstAndNullable f;
    f.first = new (mem, set.size()) BitSet;
    f.nullable = Super::first(*f.first,P);
    ((FirstCache *)&Fs)->insert((CachedFirstSetProduction *)P,f);
    changed = set.Union_if_changed(*f.first);
    return f.nullable;
  }
}

#endif
