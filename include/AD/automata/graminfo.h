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

#ifndef grammar_info_h
#define grammar_info_h

#include <AD/automata/grammar.h>
#include <AD/contain/intsets.h>  // array of integer sets

class GrammarInfo
{
  GrammarInfo( const GrammarInfo&);        // no copy constructor
  void operator = ( const GrammarInfo&);   // no assignment

protected:

  friend class LL1Gen;
  friend class LALR1Gen;
  friend Bool add_set( int, Byte *, Byte *);

  typedef Grammar::Symbol      Symbol;
  typedef Grammar::Terminal    Terminal;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Action      Action;
  typedef Grammar::Production  Production;
  const Symbol END_PRODUCTION = Grammar::END_PRODUCTION;

  Production * productions;
  Bool * nullable;        //  nullable(A)     = true iff A -> epsilon
  IntSetArray first;      //  first(A)        = { c | A -> cw } for some w
  IntSetArray follow;     //  follow(A)       = { c | B -> Ac } for some B

  Symbol min_non_terminal;
  Symbol max_non_terminal;
  int    number_of_non_terminals;
  int    production_size;

public:

  GrammarInfo() : nullable(0)
  {}
  ~GrammarInfo();

  void clear_info();
  void compute_info( const Grammar& G);
};

#endif
