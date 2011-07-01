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

#ifndef nullable_nonterminal_computation_h
#define nullable_nonterminal_computation_h

#include <AD/generic/generic.h>
#include <AD/automata/grammar.h>
#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  This class computes whether a non-terminal can derive the null string
//////////////////////////////////////////////////////////////////////////////

class Nullable
{
  Nullable( const Nullable&);          // no copy constructor
  void operator = ( const Nullable&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

  typedef Grammar::Symbol      Symbol;
  typedef Grammar::Terminal    Terminal;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Production  Production;
  typedef Grammar::EquivMap    EquivMap;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  const Grammar& G;        // the current grammar
  Mem&           mem;      // the current memory manager
  char*          null_set; // non-terminal derives null?
  // boolean array indexed by non-terminal

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  Nullable( const Grammar&, Mem&);
  virtual ~Nullable();

  ///////////////////////////////////////////////////////////////////////////
  //  Returns whether a non-terminal A can derives the empty string,
  //  or      whether a production   P can derives the empty string.
  ///////////////////////////////////////////////////////////////////////////
  inline Bool nullable( NonTerminal A) const
  {
    return null_set[A];
  }
  inline Bool nullable( register Production P) const
  {
    register Symbol X;
    while ((X = *P++) != Grammar::END_PRODUCTION)
      if (X > Grammar::END_PRODUCTION && ! null_set[X])
        return false;
    return true;
  }
};

#endif
