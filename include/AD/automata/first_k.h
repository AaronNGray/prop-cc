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

#ifndef first_set_with_k_lookaheads_computation_h
#define first_set_with_k_lookaheads_computation_h

#include <AD/automata/follow.h>

class FirstSet_k : public FollowSet
{
  FirstSet_k( const FirstSet_k&);       // no copy constructor
  void operator = ( const FirstSet_k&); // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////
  typedef FollowSet             Super;
  typedef Super::Symbol         Symbol;
  typedef Super::Terminal       Terminal;
  typedef Super::NonTerminal    NonTerminal;
  typedef Super::Production     Production;
  typedef Super::ProductionList ProductionList;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  int K;     // the current number of lookaheads
  int max_K; // the maximum number of lookaheads
  BitSet *** first_set_k;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructors
  ///////////////////////////////////////////////////////////////////////////
  FirstSet_k( const Grammar&, Mem&);
  ~FirstSet_k();

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the sets
  ///////////////////////////////////////////////////////////////////////////
  virtual void compute_sets( int k, int max_k);

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline int k()     const
  {
    return K;
  }
  inline int max_k() const
  {
    return max_K;
  }
  inline const BitSet& first( int k, NonTerminal A) const
  {
    return *first_set_k[k][A];
  }

  Bool first( int k, BitSet&, Production)        const;
  Bool first( int k, BitSet&, Production, Bool&) const;
};

#endif
