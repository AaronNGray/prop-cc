///////////////////////////////////////////////////////////////////////////////
//
//  Data structure for partial evaluting a TRS
//
///////////////////////////////////////////////////////////////////////////////

#ifndef term_rewrite_system_h
#define term_rewrite_system_h

#include <iostream>
#include <AD/automata/treeauto.h>
#include "basics.ph"
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

datatype Term : public MEM =
  CONSterm   (TreeAutomaton::Functor, Cons, int, Term [])
| VARterm    (int, Pat, Exp)
| CODEterm   (Exp)
| OPAQUEterm (Decls)
| PATterm    (Pat)
;


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

  typedef .[State, Term] Residue;
  typedef List<Residue> Residues;

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
