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

#ifndef operator_precedence_h
#define operator_precedence_h

#include <iostream>
#include <AD/automata/grammar.h>


//////////////////////////////////////////////////////////////////////////////
//  Operator precedence
//////////////////////////////////////////////////////////////////////////////
class OpPrecedence
{
  OpPrecedence( const OpPrecedence&);       // no copy constructor
  void operator = ( const OpPrecedence&);   // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  First, import some predefined types
  ///////////////////////////////////////////////////////////////////////////

  typedef Grammar::Symbol      Symbol;
  typedef Grammar::Terminal    Terminal;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Production  Production;
  typedef int                  ProductionNum;

  ///////////////////////////////////////////////////////////////////////////
  //  Some types representing attributes related to operator precedence
  ///////////////////////////////////////////////////////////////////////////

  enum Fixity        { Nonfix, Prefix, Infix, Postfix };
  enum Associativity { None, Left, Right };
  typedef int Precedence;

protected:

  ///////////////////////////////////////////////////////////////////////////
  // Internals
  ///////////////////////////////////////////////////////////////////////////

  const Grammar&  G;
  Fixity        * fixity_table;
  Associativity * associativity_table;
  Precedence    * precedence_table;
  Fixity        * fixity_map;
  Associativity * associativity_map;
  Precedence    * precedence_map;

public:
  ///////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

  OpPrecedence(const Grammar&);
  virtual ~OpPrecedence();

  ///////////////////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////////////////

  inline Fixity fixity( Terminal X) const
  {
    return fixity_table[X];
  }

  inline Associativity associativity( Terminal X) const
  {
    return associativity_table[X];
  }

  inline Precedence precedence( Terminal X) const
  {
    return precedence_table[X];
  }

  inline Fixity p_fixity(ProductionNum P) const
  {
    return fixity_map[P];
  }

  inline Associativity p_associativity( ProductionNum P) const
  {
    return associativity_map[P];
  }

  inline int p_precedence( ProductionNum P) const
  {
    return precedence_map[P];
  }

  ///////////////////////////////////////////////////////////////////////////
  // Mutators
  ///////////////////////////////////////////////////////////////////////////

  inline void fixity( Terminal X, Fixity f)
  {
    fixity_table[X] = f;
  }

  inline void associativity( Terminal X, Associativity a)
  {
    associativity_table[X] = a;
  }

  inline void precedence( Terminal X, Precedence p)
  {
    precedence_table[X] = p;
  }

  inline void p_fixity( ProductionNum P, Fixity f)
  {
    fixity_map[P] = f;
  }

  inline void p_associativity( ProductionNum P, Associativity a)
  {
    associativity_map[P] = a;
  }

  inline void p_precedence( ProductionNum P, Precedence p)
  {
    precedence_map[P] = p;
  }
};

#endif
