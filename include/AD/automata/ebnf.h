///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.1.4),
//  last updated on August 28, 1995.
//  The original source file is "ebnf.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "ebnf.ph"
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


//////////////////////////////////////////////////////////////////////////////
//  Extended BNF syntax definition
//////////////////////////////////////////////////////////////////////////////
#line 35 "ebnf.ph"
#line 53 "ebnf.ph"
///////////////////////////////////////////////////////////////////////////////
// Forward class definition for EBNF
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_EBNF_defined
#define datatype_EBNF_defined
typedef class a_EBNF * EBNF;
#endif

///////////////////////////////////////////////////////////////////////////////
// Class hierarchy for datatype EBNF
///////////////////////////////////////////////////////////////////////////////
class a_EBNF; // base class for datatype EBNF
class EBNF_ebnf_or;	// subclass for 'ebnf_or (EBNF, EBNF)'
class EBNF_ebnf_dot;	// subclass for 'ebnf_dot (EBNF, EBNF)'
class EBNF_ebnf_star;	// subclass for 'ebnf_star EBNF'
class EBNF_ebnf_plus;	// subclass for 'ebnf_plus EBNF'
class EBNF_ebnf_terminal;	// subclass for 'ebnf_terminal Grammar::Terminal'
class EBNF_ebnf_nonterminal;	// subclass for 'ebnf_nonterminal Grammar::NonTerminal'
class EBNF_ebnf_action;	// subclass for 'ebnf_action Grammar::Action'
class EBNF_syntactic_predicate;	// subclass for 'syntactic_predicate EBNF'
class EBNF_semantic_predicate;	// subclass for 'semantic_predicate EBNF'

///////////////////////////////////////////////////////////////////////////////
// Base class for datatype 'EBNF'
///////////////////////////////////////////////////////////////////////////////
class a_EBNF
{
public:
  enum Tag_EBNF {
    tag_ebnf_or = 0, tag_ebnf_dot = 1, tag_ebnf_star = 2, tag_ebnf_plus = 3,
    tag_ebnf_terminal = 4, tag_ebnf_nonterminal = 5, tag_ebnf_action = 6, tag_syntactic_predicate = 7,
    tag_semantic_predicate = 8
  };

protected:
  const Tag_EBNF _tag_;
  inline a_EBNF(Tag_EBNF _t_) : _tag_(_t_)
  {}
public:
  inline int untag() const
  {
    return _tag_;
  }
  inline friend int boxed(const a_EBNF * x)
  {
    return 1;
  }
  inline friend int untag(const a_EBNF * x)
  {
    return x->_tag_;
  }
  ////////////////////////////////////////////////////////////////////////////
  // Downcasting functions for EBNF
  ////////////////////////////////////////////////////////////////////////////
  inline friend EBNF_ebnf_or * _ebnf_or(EBNF _x_)
  {
    return (EBNF_ebnf_or *)_x_;
  }
  inline friend EBNF_ebnf_dot * _ebnf_dot(EBNF _x_)
  {
    return (EBNF_ebnf_dot *)_x_;
  }
  inline friend EBNF_ebnf_star * _ebnf_star(EBNF _x_)
  {
    return (EBNF_ebnf_star *)_x_;
  }
  inline friend EBNF_ebnf_plus * _ebnf_plus(EBNF _x_)
  {
    return (EBNF_ebnf_plus *)_x_;
  }
  inline friend EBNF_ebnf_terminal * _ebnf_terminal(EBNF _x_)
  {
    return (EBNF_ebnf_terminal *)_x_;
  }
  inline friend EBNF_ebnf_nonterminal * _ebnf_nonterminal(EBNF _x_)
  {
    return (EBNF_ebnf_nonterminal *)_x_;
  }
  inline friend EBNF_ebnf_action * _ebnf_action(EBNF _x_)
  {
    return (EBNF_ebnf_action *)_x_;
  }
  inline friend EBNF_syntactic_predicate * _syntactic_predicate(EBNF _x_)
  {
    return (EBNF_syntactic_predicate *)_x_;
  }
  inline friend EBNF_semantic_predicate * _semantic_predicate(EBNF _x_)
  {
    return (EBNF_semantic_predicate *)_x_;
  }
#line 45 "ebnf.ph"

  ///////////////////////////////////////////////////////////////////////////
  //  We redefine the memory management operators to allocate from a
  //  memory pool.
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator new    (size_t n)
  {
    return new char [n];
  }
  inline void * operator new    (size_t n, Mem& m)
  {
    return m.m_alloc(n);
  }
  inline void   operator delete (void * x)
  {
    delete (char*) x;
  }
#line 53 "ebnf.ph"
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::ebnf_or (EBNF, EBNF)'
///////////////////////////////////////////////////////////////////////////////
class EBNF_ebnf_or : public a_EBNF
{
public:
#line 35 "ebnf.ph"

  EBNF _1;
  EBNF _2;
  inline EBNF_ebnf_or (EBNF _x1, EBNF _x2)
      : a_EBNF(a_EBNF::tag_ebnf_or), _1(_x1), _2(_x2)
  {}
  inline friend a_EBNF * ebnf_or (EBNF _x1, EBNF _x2)
  {
    return new EBNF_ebnf_or (_x1, _x2);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::ebnf_dot (EBNF, EBNF)'
///////////////////////////////////////////////////////////////////////////////
class EBNF_ebnf_dot : public a_EBNF
{
public:
#line 36 "ebnf.ph"

  EBNF _1;
  EBNF _2;
  inline EBNF_ebnf_dot (EBNF _x1, EBNF _x2)
      : a_EBNF(a_EBNF::tag_ebnf_dot), _1(_x1), _2(_x2)
  {}
  inline friend a_EBNF * ebnf_dot (EBNF _x1, EBNF _x2)
  {
    return new EBNF_ebnf_dot (_x1, _x2);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::ebnf_star EBNF'
///////////////////////////////////////////////////////////////////////////////
class EBNF_ebnf_star : public a_EBNF
{
public:
#line 37 "ebnf.ph"

  EBNF ebnf_star;
  inline EBNF_ebnf_star (EBNF _xebnf_star)
      : a_EBNF(a_EBNF::tag_ebnf_star), ebnf_star(_xebnf_star)
  {}
  inline friend a_EBNF * ebnf_star (EBNF _xebnf_star)
  {
    return new EBNF_ebnf_star (_xebnf_star);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::ebnf_plus EBNF'
///////////////////////////////////////////////////////////////////////////////
class EBNF_ebnf_plus : public a_EBNF
{
public:
#line 38 "ebnf.ph"

  EBNF ebnf_plus;
  inline EBNF_ebnf_plus (EBNF _xebnf_plus)
      : a_EBNF(a_EBNF::tag_ebnf_plus), ebnf_plus(_xebnf_plus)
  {}
  inline friend a_EBNF * ebnf_plus (EBNF _xebnf_plus)
  {
    return new EBNF_ebnf_plus (_xebnf_plus);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::ebnf_terminal Grammar::Terminal'
///////////////////////////////////////////////////////////////////////////////
class EBNF_ebnf_terminal : public a_EBNF
{
public:
#line 39 "ebnf.ph"

  Grammar::Terminal ebnf_terminal;
  inline EBNF_ebnf_terminal (Grammar::Terminal _xebnf_terminal)
      : a_EBNF(a_EBNF::tag_ebnf_terminal), ebnf_terminal(_xebnf_terminal)
  {}
  inline friend a_EBNF * ebnf_terminal (Grammar::Terminal _xebnf_terminal)
  {
    return new EBNF_ebnf_terminal (_xebnf_terminal);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::ebnf_nonterminal Grammar::NonTerminal'
///////////////////////////////////////////////////////////////////////////////
class EBNF_ebnf_nonterminal : public a_EBNF
{
public:
#line 40 "ebnf.ph"

  Grammar::NonTerminal ebnf_nonterminal;
  inline EBNF_ebnf_nonterminal (Grammar::NonTerminal _xebnf_nonterminal)
      : a_EBNF(a_EBNF::tag_ebnf_nonterminal), ebnf_nonterminal(_xebnf_nonterminal)
  {}
  inline friend a_EBNF * ebnf_nonterminal (Grammar::NonTerminal _xebnf_nonterminal)
  {
    return new EBNF_ebnf_nonterminal (_xebnf_nonterminal);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::ebnf_action Grammar::Action'
///////////////////////////////////////////////////////////////////////////////
class EBNF_ebnf_action : public a_EBNF
{
public:
#line 41 "ebnf.ph"

  Grammar::Action ebnf_action;
  inline EBNF_ebnf_action (Grammar::Action _xebnf_action)
      : a_EBNF(a_EBNF::tag_ebnf_action), ebnf_action(_xebnf_action)
  {}
  inline friend a_EBNF * ebnf_action (Grammar::Action _xebnf_action)
  {
    return new EBNF_ebnf_action (_xebnf_action);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::syntactic_predicate EBNF'
///////////////////////////////////////////////////////////////////////////////
class EBNF_syntactic_predicate : public a_EBNF
{
public:
#line 42 "ebnf.ph"

  EBNF syntactic_predicate;
  inline EBNF_syntactic_predicate (EBNF _xsyntactic_predicate)
      : a_EBNF(a_EBNF::tag_syntactic_predicate), syntactic_predicate(_xsyntactic_predicate)
  {}
  inline friend a_EBNF * syntactic_predicate (EBNF _xsyntactic_predicate)
  {
    return new EBNF_syntactic_predicate (_xsyntactic_predicate);
  }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EBNF::semantic_predicate EBNF'
///////////////////////////////////////////////////////////////////////////////
class EBNF_semantic_predicate : public a_EBNF
{
public:
#line 43 "ebnf.ph"

  EBNF semantic_predicate;
  inline EBNF_semantic_predicate (EBNF _xsemantic_predicate)
      : a_EBNF(a_EBNF::tag_semantic_predicate), semantic_predicate(_xsemantic_predicate)
  {}
  inline friend a_EBNF * semantic_predicate (EBNF _xsemantic_predicate)
  {
    return new EBNF_semantic_predicate (_xsemantic_predicate);
  }
};

#line 53 "ebnf.ph"
#line 53 "ebnf.ph"


//////////////////////////////////////////////////////////////////////////////
//  Class EBNFGrammar represents a grammar in extended Backus/Naur form.
//////////////////////////////////////////////////////////////////////////////
class EBNFGrammar : public Grammar
{

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
#line 90 "ebnf.ph"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
