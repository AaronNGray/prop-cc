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

#ifndef follow_set_computation_h
#define follow_set_computation_h

#include <AD/automata/firstset.h>
#include <AD/contain/bitset.h>
#include <AD/memory/mempool.h>

//////////////////////////////////////////////////////////////////////////////
//  This class computes the follow sets of a grammar.
//  follow(A) = { c | such that c can immediately follow A in a derivation }
//  Implicitly, we need to know compute first(X).  We'll inherit
//  from class FirstSet.
//////////////////////////////////////////////////////////////////////////////

class FollowSet : public FirstSet
{
  FollowSet( const FollowSet&);        // no copy constructor
  void operator = ( const FollowSet&); // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////
  typedef FirstSet              Super;
  typedef Super::Symbol         Symbol;
  typedef Super::Terminal       Terminal;
  typedef Super::NonTerminal    NonTerminal;
  typedef Super::Production     Production;
  typedef Super::ProductionList ProductionList;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  BitSet ** follow_set;  // an array of terminals set indexed by non-terminal

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  FollowSet( const Grammar&, Mem&);
  ~FollowSet();

  ///////////////////////////////////////////////////////////////////////////
  //  Follow set computation
  ///////////////////////////////////////////////////////////////////////////
  inline const BitSet& follow( NonTerminal A) const
  {
    return *follow_set[A];
  }
};

#endif
