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

#ifndef predict_set_computation_h
#define predict_set_computation_h

#include <AD/automata/follow.h>

//////////////////////////////////////////////////////////////////////////////
// Class |PredictSet| computes the lookahead symbol for each rule.
//////////////////////////////////////////////////////////////////////////////
class PredictSet : public FollowSet
{
  PredictSet( const PredictSet&);       // no copy constructor
  void operator = ( const PredictSet&); // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import inherited types
  ///////////////////////////////////////////////////////////////////////////
  typedef FollowSet          Super;
  typedef Super::Symbol      Symbol;
  typedef Super::Terminal    Terminal;
  typedef Super::NonTerminal NonTerminal;
  typedef Super::Production  Production;
  typedef Grammar::Rule      Rule;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  BitSet ** predict_set;
  BitSet *  conflict_set;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  PredictSet( const Grammar&, Mem&);
  ~PredictSet();

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline const BitSet& predict( Rule r)        const
  {
    return *predict_set[r];
  }
  const BitSet& conflict( NonTerminal A) const;
};

#endif
