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

#ifndef top_down_tree_parser_driver_h
#define top_down_tree_parser_driver_h

//////////////////////////////////////////////////////////////////////////////
//  This file implements a topdown tree parser driver with dynamic programming
//  similar to the ``twig'' tool from AT&T.  See Aho, Tsiang, et al.
//////////////////////////////////////////////////////////////////////////////

#include <AD/automata/topdown.h>    // top down tree matcher
#include <AD/memory/mem.h>          // memory manager

class Twig : public TopDown
{

  Twig(const Twig&);              // no copy constructor
  void operator = (const Twig&);  // no assignment

  /////////////////////////////////////////////////////////////////////////
  //  Import some types from superclass.
  /////////////////////////////////////////////////////////////////////////

public:
  typedef TopDown       Super;
  typedef Super::Symbol Symbol;
  typedef Super::State  State;
  typedef Super::Offset Offset;
  typedef Super::Rule   Rule;

  /////////////////////////////////////////////////////////////////////////
  //  The implementation is hidden.
  /////////////////////////////////////////////////////////////////////////

protected:
  Mem&              mem;    // memory manager
  class Twig_Impl * impl;   // internals

  /////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////////////////////////

public:
  Twig( const Offset base_table  [],
        const State  check_table [],
        const State  failure     [],
        const State  next_table  [],
        const Rule   rule_table  []
      );
  virtual ~Twig();

  /////////////////////////////////////////////////////////////////////////
  //  Tree matching.
  /////////////////////////////////////////////////////////////////////////
  virtual void open   ();
  virtual void close  ();
  virtual void reduce ();
  virtual void action (Rule);

  /////////////////////////////////////////////////////////////////////////
  //  Error handler: can be redefined in subclasses.
  /////////////////////////////////////////////////////////////////////////
  virtual void no_cover();
};

#endif
