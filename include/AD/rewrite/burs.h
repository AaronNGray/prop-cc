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

#ifndef BURS_tree_matcher_h
#define BURS_tree_matcher_h

//////////////////////////////////////////////////////////////////////////
//
// Class |BURS| represents a tree automaton with compressed
// lookup tables.  See class |BURS_Gen| for the generator.
//
//////////////////////////////////////////////////////////////////////////

#include <AD/automata/treetab.h>  // tree automata tables
#include <AD/memory/mempool.h>    // memory pool

class BURS : public TreeTables
{
  BURS (const BURS&);             // no copy constructor
  void operator = (const BURS&);  // no assignment

  ///////////////////////////////////////////////////////////////////////
  //  Inport some types
  ///////////////////////////////////////////////////////////////////////

public:
  typedef TreeTables     Super;
  typedef Super::Functor Functor;
  typedef Super::Arity   Arity;
  typedef Super::State   State;
  typedef Super::Offset  Offset;
  typedef Super::Rule    Rule;

  enum { undefined_state = 65535 };

  ///////////////////////////////////////////////////////////////////////
  //  Memory pool
  ///////////////////////////////////////////////////////////////////////

protected:
  MemPool mem;

  ///////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////

public:
  BURS();
  virtual ~BURS();

  ///////////////////////////////////////////////////////////////////////
  //  Method to call in case there is no cover.
  ///////////////////////////////////////////////////////////////////////
  virtual void no_cover();
  virtual void clear();
};

#endif
