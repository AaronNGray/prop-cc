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

#ifndef extended_Backus_Naur_form_h
#define extended_Backus_Naur_form_h

#include <iostream>
#include <AD/automata/grammar.h>  // grammar
#include <AD/memory/mem.h>        // memory manager

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//  Extended BNF syntax definition
//////////////////////////////////////////////////////////////////////////////
datatype EBNF = ebnf_or             (EBNF, EBNF)
              | ebnf_dot            (EBNF, EBNF)
              | ebnf_star           (EBNF)
              | ebnf_plus           (EBNF)
              | ebnf_terminal       (Grammar::Terminal)
              | ebnf_nonterminal    (Grammar::NonTerminal)
              | ebnf_action         (Grammar::Action)
              | syntactic_predicate (EBNF)
              | semantic_predicate  (EBNF)
public:
{
   ///////////////////////////////////////////////////////////////////////////
   //  We redefine the memory management operators to allocate from a
   //  memory pool.
   ///////////////////////////////////////////////////////////////////////////
   inline void * operator new    (size_t n)         { return new char [n]; }
   inline void * operator new    (size_t n, Mem& m) { return m.m_alloc(n); }
   inline void   operator delete (void * x)         { delete (char*) x; }
};

//////////////////////////////////////////////////////////////////////////////
//  Class EBNFGrammar represents a grammar in extended Backus/Naur form.
//////////////////////////////////////////////////////////////////////////////
class EBNFGrammar : public Grammar {

   EBNFGrammar(const EBNFGrammar&);  // no copy constructor
   void operator = (EBNFGrammar&);   // no assignment

public:

   ///////////////////////////////////////////////////////////////////////////
   //  Import some types
   ///////////////////////////////////////////////////////////////////////////
   typedef Grammar            Super;
   typedef Super::Symbol      Symbol;
   typedef Super::Terminal    Terminal;
   typedef Super::NonTerminal NonTerminal;
   typedef Super::Action      Action;
   typedef Super::Production  Production;

public:

   ///////////////////////////////////////////////////////////////////////////
   //  Constructor and destructor
   ///////////////////////////////////////////////////////////////////////////
   EBNFGrammar();
  ~EBNFGrammar();

   ///////////////////////////////////////////////////////////////////////////
   //  Selectors
   ///////////////////////////////////////////////////////////////////////////
   inline int size() const;
};

#endif
