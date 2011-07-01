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

#ifndef LR1_parser_generator_h
#define LR1_parser_generator_h

#include <iostream>
#include <AD/automata/grammar.h>  // Parser grammar
#include <AD/automata/lrgen.h>    // LR parser generator base class


class LR1Gen : public LRGen
{
  LR1Gen( const LR1Gen&);             // no copy constructor
  void operator = ( const LR1Gen&);   // no assignment

public:

  /////////////////////////////////////////////////////////////////////////
  //  Inherit some types
  /////////////////////////////////////////////////////////////////////////
  typedef LRGen                   Super;
  typedef Super::Symbol           Symbol;
  typedef Super::State            State;
  typedef Super::Offset           Offset;
  typedef Super::Rule             Rule;
  typedef Super::ProductionLength ProductionLength;
  typedef Super::EquivMap         EquivMap;

public:

  /////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////////////////////////
  LR1Gen();
  ~LR1Gen();

  /////////////////////////////////////////////////////////////////////////
  //  Table compilation and code generation
  /////////////////////////////////////////////////////////////////////////
  virtual void compile( const Grammar&);
  virtual std::ostream& gen_code( std::ostream&, const char []) const;
};

#endif
