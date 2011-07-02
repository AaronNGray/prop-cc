///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\trs.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/trs.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  Data structure for partial evaluting a TRS
//
///////////////////////////////////////////////////////////////////////////////

#ifndef term_rewrite_system_h
#define term_rewrite_system_h

#include <iostream>
#include <AD/automata/treeauto.h>
#include "basics.h"
#include "ir.h"
#include "ast.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations
//
///////////////////////////////////////////////////////////////////////////////

class FunctorMap;
class RewritingCompiler;
class CodeGen;

///////////////////////////////////////////////////////////////////////////////
//
//  This class represents a rewriting term
//
///////////////////////////////////////////////////////////////////////////////

#line 33 "../../prop-src/trs.ph"
#line 39 "../../prop-src/trs.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Term
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Term_defined
#define datatype_Term_defined
  class a_Term;
  typedef a_Term * Term;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Term
//
///////////////////////////////////////////////////////////////////////////////
class a_Term : public MEM {
public:
  enum Tag_Term {
    tag_CONSterm = 0, tag_VARterm = 1, tag_CODEterm = 2, 
    tag_OPAQUEterm = 3, tag_PATterm = 4
  };

public:
  const Tag_Term tag__; // variant tag
protected:
  inline a_Term(Tag_Term t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Term *) { return 1; }
inline int untag(const a_Term * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Term::CONSterm
//
///////////////////////////////////////////////////////////////////////////////
class Term_CONSterm : public a_Term {
public:
#line 33 "../../prop-src/trs.ph"
  TreeAutomaton::Functor _1; Cons _2; int _3; Term * _4; 
  inline Term_CONSterm (TreeAutomaton::Functor x_1, Cons x_2, int x_3, Term * x_4)
   : a_Term(tag_CONSterm), _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Term::VARterm
//
///////////////////////////////////////////////////////////////////////////////
class Term_VARterm : public a_Term {
public:
#line 35 "../../prop-src/trs.ph"
  int _1; Pat _2; Exp _3; 
  inline Term_VARterm (int x_1, Pat x_2, Exp x_3)
   : a_Term(tag_VARterm), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Term::CODEterm
//
///////////////////////////////////////////////////////////////////////////////
class Term_CODEterm : public a_Term {
public:
#line 36 "../../prop-src/trs.ph"
  Exp CODEterm; 
  inline Term_CODEterm (Exp x_CODEterm)
   : a_Term(tag_CODEterm), CODEterm(x_CODEterm)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Term::OPAQUEterm
//
///////////////////////////////////////////////////////////////////////////////
class Term_OPAQUEterm : public a_Term {
public:
#line 37 "../../prop-src/trs.ph"
  Decls OPAQUEterm; 
  inline Term_OPAQUEterm (Decls x_OPAQUEterm)
   : a_Term(tag_OPAQUEterm), OPAQUEterm(x_OPAQUEterm)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Term::PATterm
//
///////////////////////////////////////////////////////////////////////////////
class Term_PATterm : public a_Term {
public:
#line 38 "../../prop-src/trs.ph"
  Pat PATterm; 
  inline Term_PATterm (Pat x_PATterm)
   : a_Term(tag_PATterm), PATterm(x_PATterm)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Term
//
///////////////////////////////////////////////////////////////////////////////
inline a_Term * CONSterm (TreeAutomaton::Functor x_1, Cons x_2, int x_3, Term * x_4)
{
  return new Term_CONSterm (x_1, x_2, x_3, x_4);
}
inline a_Term * VARterm (int x_1, Pat x_2, Exp x_3)
{
  return new Term_VARterm (x_1, x_2, x_3);
}
inline a_Term * CODEterm (Exp x_CODEterm)
{
  return new Term_CODEterm (x_CODEterm);
}
inline a_Term * OPAQUEterm (Decls x_OPAQUEterm)
{
  return new Term_OPAQUEterm (x_OPAQUEterm);
}
inline a_Term * PATterm (Pat x_PATterm)
{
  return new Term_PATterm (x_PATterm);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Term
//
///////////////////////////////////////////////////////////////////////////////
inline Term_CONSterm * _CONSterm(const a_Term * _x_) { return (Term_CONSterm *)_x_; }
inline Term_VARterm * _VARterm(const a_Term * _x_) { return (Term_VARterm *)_x_; }
inline Term_CODEterm * _CODEterm(const a_Term * _x_) { return (Term_CODEterm *)_x_; }
inline Term_OPAQUEterm * _OPAQUEterm(const a_Term * _x_) { return (Term_OPAQUEterm *)_x_; }
inline Term_PATterm * _PATterm(const a_Term * _x_) { return (Term_PATterm *)_x_; }

#line 39 "../../prop-src/trs.ph"
#line 39 "../../prop-src/trs.ph"



///////////////////////////////////////////////////////////////////////////////
//
//  This class represent a term rewriting system.
//
///////////////////////////////////////////////////////////////////////////////

class TRS
{
  TRS();                         // no default constructor
  TRS(const TRS&);               // no copy constructor
  void operator = (const TRS&);  // no assignment
public:
  typedef TreeAutomaton::Functor Functor;
  typedef TreeAutomaton::State   State;
  typedef TreeAutomaton::Rule    Rule;
  enum EvalResult { SUCCESS, FAILURE, UNKNOWN };

  typedef 
#line 59 "../../prop-src/trs.ph"
Tuple2<State, Term>  
#line 59 "../../prop-src/trs.ph"
 Residue;
  typedef a_List<Residue> *  
#line 60 "../../prop-src/trs.ph"
 Residues;

private:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Data to implement the tree automaton and the rules
  //
  ////////////////////////////////////////////////////////////////////////////
  enum { MAX_VARS = 256 };
  RewritingCompiler&   compiler; // the rewriting compiler
  const FunctorMap&    Fmap;     // the functor map
  const TreeAutomaton& treeauto; // the tree automata
  int         number_of_rules;   // number of rules
  MatchRule * rule_map;          // mapping from rule_no to rule
  Exp *       guard_map;         // mapping from rule_no to guard
  Term *      lhs_map;           // mapping from rule_no to lhs
  Term *      rhs_map;           // mapping from rule_no to rhs
  int *       num_var_map;       // mapping from rule_no to number of vars
  Exp **      var_map;           // mapping from rule_no to variable bindings
  Pat **      var_pat_map;       // mapping from rule_no to variable patterns
  Residues ** residue_map;       // mapping from rule_no x variable -> residue
  Literal *   literal_map;       // mapping from functor -> literal
  Exp *      optimized_map;     // mapping from rule_no -> optimized expr
  int         states[MAX_VARS];  // state table
  int         mus[MAX_VARS];     // mu table
  Bool        count_redex;       // count redex mode/don't normalize

  ////////////////////////////////////////////////////////////////////////////
  //
  //  The local variable environment.
  //
  ////////////////////////////////////////////////////////////////////////////
  int         num_vars;           // number of variables in environment
  Exp         vars[MAX_VARS];     // variable bindings
  Pat         var_pats[MAX_VARS]; // variable pattern names

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Partial evaluation statistics
  //
  ////////////////////////////////////////////////////////////////////////////
  int         number_of_specializations;
  void        clear_statistics();

public:
  TRS(RewritingCompiler&);
  ~TRS();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Pretty printing
  //
  ////////////////////////////////////////////////////////////////////////////
  void print (std::ostream&) const;
  void print (std::ostream&,Term) const;
  void print_report(std::ostream&) const;
  void print_specializations(std::ostream&) const;

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Partial evaluation and code generation methods
  //
  ////////////////////////////////////////////////////////////////////////////
  void mix();
  Bool gen_replacement(CodeGen&, Rule, Exp);

private:

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to construct the term representation.
  //
  ////////////////////////////////////////////////////////////////////////////
  void   make_lhs( Rule r, Pat);
  void   make_rhs( Rule r, Term);
  void   make_rhs( Rule r, Exp);

  Term   make_term( Pat);
  Term   make_term( Pat, Cons, Pats);
  Term * make_term( Pats);

  Term   make_term( Exp);
  Term   make_term( Exp, Id, Exps);
  Term * make_term( Exps);

  Term   make_term_var( Pat, Exp);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods for partial evaluation
  //
  ////////////////////////////////////////////////////////////////////////////
  void mix(Rule);
  void mix_0(Rule);
  void mix_1(Rule);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods for normalization and reduction
  //
  ////////////////////////////////////////////////////////////////////////////
  State normalize( Term& term, int& reductions);
  Bool  is_relevant( Rule);
  Term  reduce( Term term, State, int& reductions, Bool& changed);
  EvalResult eval_guard( Exp);
  Term  subst( Term, Term, Bool&);
  Term* subst( int, Term[], Term, Bool&);
  Term  proj( Exp, Term, Bool&);
  Exp   proj( Exp, Exp, Bool&);
  Term  copy( Term);
  Term* copy( int, Term[]);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods for generating residue code
  //
  ////////////////////////////////////////////////////////////////////////////
  void generate_residue( Rule, int, State, Term);
  Exp  make_exp( Term) const;
  Exps make_exp( int n, Term []) const;

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods for error reporting
  //
  ////////////////////////////////////////////////////////////////////////////
  void print_residue( Rule, Term) const;
};

#endif
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
