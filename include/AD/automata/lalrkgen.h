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

#ifndef LALR_k_parser_generator_h
#define LALR_k_parser_generator_h

#include <AD/automata/lrgen.h>      // LR-style parser generator base class
#include <AD/automata/operprec.h>   // Operator precedence

class LALR_k_Gen : public LRGen
{
  LALR_k_Gen( const LALR_k_Gen&);         // no copy constructor
  void operator = ( const LALR_k_Gen&);   // no assignment

public:

  /////////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  /////////////////////////////////////////////////////////////////////////
  typedef LRGen                   Super;
  typedef Super::Symbol           Symbol;
  typedef Super::State            State;
  typedef Super::Rule             Rule;
  typedef Super::Offset           Offset;
  typedef Super::ProductionLength ProductionLength;

protected:

  /////////////////////////////////////////////////////////////////////////
  //  The implementation is hidden within
  /////////////////////////////////////////////////////////////////////////
  struct LALR_k_Gen_Impl * impl;

public:

  /////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  /////////////////////////////////////////////////////////////////////////
  LALR_k_Gen();
  LALR_k_Gen( const Grammar&, const OpPrecedence&);
  ~LALR_k_Gen();

  /////////////////////////////////////////////////////////////////////////
  //  Table compilation and code generation
  /////////////////////////////////////////////////////////////////////////

  virtual void compile( const Grammar&, const OpPrecedence&);
  virtual std::ostream& print_report( std::ostream&, int verbosity = 0);
};

#endif
