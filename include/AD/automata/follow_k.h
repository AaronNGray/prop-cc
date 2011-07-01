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

#ifndef follow_set_with_k_lookaheads_computation_h
#define follow_set_with_k_lookaheads_computation_h

#include <AD/automata/first_k.h>

class FollowSet_k : public FirstSet_k
{
  FollowSet_k( const FollowSet_k&);      // no copy constructor
  void operator = ( const FollowSet_k&); // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////
  typedef FirstSet_k            Super;
  typedef Super::Symbol         Symbol;
  typedef Super::Terminal       Terminal;
  typedef Super::NonTerminal    NonTerminal;
  typedef Super::Production     Production;
  typedef Super::ProductionList ProductionList;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  BitSet *** follow_set_k;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructors
  ///////////////////////////////////////////////////////////////////////////
  FollowSet_k( const Grammar&, Mem&);
  ~FollowSet_k();

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the sets
  ///////////////////////////////////////////////////////////////////////////
  virtual void compute_sets( int k, int max_k);

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline const BitSet& follow( int k, NonTerminal A) const
  {
    return *follow_set_k[k][A];
  }
};

#endif
