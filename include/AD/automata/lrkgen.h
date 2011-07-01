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

#ifndef LR_k_parser_generator_h
#define LR_k_parser_generator_h

#include <iostream>
#include <AD/automata/grammar.h>
#include <AD/automata/densedfa.h>


//////////////////////////////////////////////////////////////////////////////
// LR(k) parser generator class.
//////////////////////////////////////////////////////////////////////////////

class LRkGen : public DenseDFA
{
  LRkGen( const LRkGen&);           // no copy constructor
  void operator = ( const LRkGen&); // no assignment

public:

  typedef DenseDFA      Super;
  typedef Super::State  State;
  typedef Super::Rule   Rule;
  typedef Super::Symbol Symbol;

public:

  LRkGen();
  ~LRkGen();

  virtual void compile( const Grammar&);
  virtual std::ostream& gen_code( std::ostream&, const char []) const;
};

#endif
