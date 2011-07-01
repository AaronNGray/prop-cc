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

#ifndef top_down_tree_parser_with_dynamic_programming_h
#define top_down_tree_parser_with_dynamic_programming_h

//////////////////////////////////////////////////////////////////////////////
//  This file implements a topdown tree parser with dynamic programming
//  similar to the ``twig'' tool from AT&T.  See Aho, Tsiang, et al.
//////////////////////////////////////////////////////////////////////////////

#include <AD/automata/topdowng.h>    // top down tree matcher
#include <AD/memory/mem.h>           // memory manager

//////////////////////////////////////////////////////////////////////////////
//  Class TwigGen is a refinement of class TopDown, a bareboned topdown tree
//  parser.
//////////////////////////////////////////////////////////////////////////////

class TwigGen : public TopDownGen
{
  TwigGen(const TwigGen&);           // no copy constructor
  void operator = (const TwigGen&);  // no assignment

  /////////////////////////////////////////////////////////////////////////
  //  Import some types from superclass.
  /////////////////////////////////////////////////////////////////////////

public:
  typedef TopDownGen    Super;
  typedef Super::Symbol Symbol;
  typedef Super::State  State;
  typedef Super::Offset Offset;
  typedef Super::Rule   Rule;

  /////////////////////////////////////////////////////////////////////////
  //  The implementation is hidden.
  /////////////////////////////////////////////////////////////////////////

protected:
  class TwigGen_Impl* impl;   // internals

  /////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////////////////////////

public:
  TwigGen();
  TwigGen(const TreeGrammar&);
  virtual ~TwigGen();

  /////////////////////////////////////////////////////////////////////////
  //  Compilation
  /////////////////////////////////////////////////////////////////////////
  virtual void compile( const TreeGrammar&);

  /////////////////////////////////////////////////////////////////////////
  //  Method for printing the compiled tables
  /////////////////////////////////////////////////////////////////////////
  virtual std::ostream& gen_code( std::ostream&, const char []) const;
};

#endif
