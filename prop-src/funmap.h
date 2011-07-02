///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\funmap.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/funmap.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file decribes the functor map data structure, which is
//  used internally during rewriting compilation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef functor_map_h
#define functor_map_h

#include <iostream>
#include <AD/automata/treegram.h>
#include "ir.h"
#include "ast.h"
#include "type.h"
#include "hashtab.h"
#include "functortab.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Import some type definitions from the tree grammar and hash table
//  classes.
//
///////////////////////////////////////////////////////////////////////////////

class TreeAutomaton;
class TopDownGen;
typedef TreeGrammar::Functor        Functor;
typedef TreeGrammar::Variable       Variable;

///////////////////////////////////////////////////////////////////////////////
//
//  Vector Id
//
///////////////////////////////////////////////////////////////////////////////

#line 38 "../../prop-src/funmap.ph"
#line 38 "../../prop-src/funmap.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for VectorId
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_VectorId_defined
#define datatype_VectorId_defined
  class a_VectorId;
  typedef a_VectorId * VectorId;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor VectorId::vector_id
//
///////////////////////////////////////////////////////////////////////////////
class a_VectorId : public MEM {
public:
#line 38 "../../prop-src/funmap.ph"
  Cons cons; Ty ty; int arity; 
  inline a_VectorId (Cons x_cons, Ty x_ty, int x_arity)
   : cons(x_cons), ty(x_ty), arity(x_arity)
  {
  }
};
inline int boxed(const a_VectorId *) { return 1; }
inline int untag(const a_VectorId *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for VectorId
//
///////////////////////////////////////////////////////////////////////////////
inline a_VectorId * vector_id (Cons x_cons, Ty x_ty, int x_arity)
{
  return new a_VectorId (x_cons, x_ty, x_arity);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for VectorId
//
///////////////////////////////////////////////////////////////////////////////


#line 38 "../../prop-src/funmap.ph"
#line 38 "../../prop-src/funmap.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Functor mapping table.
//
///////////////////////////////////////////////////////////////////////////////

class FunctorMap
{
  FunctorMap(const FunctorMap&);      // no copy constructor
  void operator = (const FunctorMap&);  // no assignment
public:
  ////////////////////////////////////////////////////////////////////////////
  //  Internals
  ////////////////////////////////////////////////////////////////////////////
  FunctorTable   literal_map;  // mapping from literals to Functors
  FunctorTable   type_map;     // mapping from types to Functors
  FunctorTable   vector_map;   // mapping from vector constructors to Functors
  FunctorTable   var_map;      // mapping from non-terminals to Functors
  HashTable      rule_map;     // mapping from types to rule lists
  HashTable      topdown_rule_map; // mapping from types to topdown rules
  HashTable      before_rule_map;  // mapping from types to before rules
  HashTable      preorder_rule_map;  // mapping from types to preorder rules
  HashTable      postorder_rule_map; // mapping from types to postorder rules
  HashTable*     rule_maps[MatchRuleInfo::LAST_REWRITING_MODE]; // rule maps
  HashTable      protocols;    // mapping from type to type
  HashTable      nonterm_map;  // mapping from (lhs) nonterminal to type
  HashTable      nonterm_rules;// mapping from (lhs) nonterminal to rules.
  HashTable      nonterm_rules_bits;// mapping from (lhs) nonterminal to size of rules.
  HashTable      chain_rules;  // mapping of rhs to rules of form lhs -> rhs
  TreeGrammar     G;           // the current tree grammar
  TreeGrammar::Functor         functors;    // number of functors
  TreeGrammar::Variable        variables;   // number of variables
  TreeAutomaton * tree_gen;    // the tree automaton generator
  TopDownGen *    topdown_gen; // topdown tree automaton generator
  Bool        use_compression; // should we use index compression?
  Bool        has_guard;       // the set of rules contain guards?
  Bool        has_cost;        // the set of rules contain costs?
  Bool        has_cost_exp;    // the set of rules contain cost exprs?
  Bool        has_syn_attrib;  // are we using synthesized attributes?
  Bool        has_replacement; // the set of rules have replacements?
  Bool        is_applicative;  // Is rewriting done applicatively?
  Bool        gen_reducers;    // Should we generate a reducer?
  Bool        dynamic_search;  // Use runtime search?
  int         N;               // number of rules
  int         max_arity;       // maximum arity of patterns.
  Id          class_name;      // name of rewrite class
  Id *        functor_names;   // names of functors
  Id *        variable_names;  // names of variables
  Bool        is_ok;           // no errors found?
  MatchRules  bottomup_rules;  // only the bottomup rules are here

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor
  //
  ////////////////////////////////////////////////////////////////////////////
  FunctorMap(Id name, MatchRules rules);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Check whether we have an error
  //
  ////////////////////////////////////////////////////////////////////////////
  inline Bool ok() const { return is_ok; }

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Check whether a type known to the compiler?
  //
  ////////////////////////////////////////////////////////////////////////////
  Bool is_known_type      (Ty);
  Bool is_rewritable_type (Ty);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to compute the cost expression of a pattern.
  //
  ////////////////////////////////////////////////////////////////////////////
  Exp cost_expr (Id, Pat);
  Exp cost_expr (Id, Pat,     Exp);
  Exp cost_expr (Id, Pats,    Exp);
  Exp cost_expr (Id, LabPats, Exp);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Method to print a report detailing the functor/variable encoding,
  //  the tree grammar and the generated table size
  //
  ////////////////////////////////////////////////////////////////////////////
  void print_report(std::ostream&);

private:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to build the protocol list
  //
  ////////////////////////////////////////////////////////////////////////////
  void enter_protocols ();
  void check_for_missing_protocols ();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to convert literal patterns into guards
  //
  ////////////////////////////////////////////////////////////////////////////
  void    make_guard (MatchRules);
  Pat     make_guard (Pat, Exp&);
  Pats    make_guard (Pats, Exp&);
  LabPats make_guard (LabPats, Exp&);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Method to build the tree grammar
  //
  ////////////////////////////////////////////////////////////////////////////
  void build_tree_grammar (MatchRules);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Encoding methods
  //
  ////////////////////////////////////////////////////////////////////////////
  void encode (Ty);  // encode a type
  void encode (Pat); // encode a pattern
  void encode (Id);  // encode a non-terminal
  Id   chain_rule_rhs (Pat);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Translation methods
  //
  ////////////////////////////////////////////////////////////////////////////
  TreeTerm trans(Pat);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Method to partition a set of rules according to the types of the
  //  top level pattern, also encode the pattern in the process.
  //
  ////////////////////////////////////////////////////////////////////////////
  MatchRules partition_rules (MatchRules);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Method to compute the functor and variable names
  //
  ////////////////////////////////////////////////////////////////////////////
  void compute_names ();
};

#endif
#line 191 "../../prop-src/funmap.ph"
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
