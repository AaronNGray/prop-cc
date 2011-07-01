///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the interface to the pattern matching compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef match_compiler_h
#define match_compiler_h

#include <iostream>
#include "ir.h"
#include "ast.h"
#include "patenv.h"
#include "hashtab.h"
#include "labelgen.h"
#include "codegen.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Forward type declarations.
//
///////////////////////////////////////////////////////////////////////////////

class BitSet;       // bit sets

///////////////////////////////////////////////////////////////////////////////
//
//  Pattern matching decision tree (dag)
//
///////////////////////////////////////////////////////////////////////////////

struct MatchBase : public MEM
{
  int shared;
  Id label;
  MatchBase();
};

datatype Match : public MatchBase =
    FAILmatch
  | SUCCESSmatch   (int, MatchRule)
  | SUCCESSESmatch (int, BitSet *, MatchRules)
  | COSTmatch      (int, Cost [], BitSet *, MatchRules)
  | GUARDmatch     (Exp, Match, Match)
  | LITERALmatch   (Pos, Exp, Literal [], int, Match [], Match)
  | RANGEmatch     (Pos, Exp, int, int, Match, Match)
  | CONSmatch      (Pos, Exp, Ty, Ty, int, Match [], Match)
    // special nodes
  | TREECOSTmatch  (Match, BitSet *, MatchRules)
  | TREELABELmatch (Match, Ty, Ty, int)
  | DONTCAREmatch                    // unused alternative
  | BACKEDGEmatch  (int, Id, Match)  // used for forming loops

///////////////////////////////////////////////////////////////////////////////
//
//  Cost of a pattern matching/rewrite rule
//
///////////////////////////////////////////////////////////////////////////////

and Cost : MEM = NOcost                   // zero cost
               | EXPcost (Exp,Ty = NOty)  // cost is a function
               | INTcost (int)            // cost is an integer

///////////////////////////////////////////////////////////////////////////////
//
//  Position element (for use during pattern matching compilation.)
//
///////////////////////////////////////////////////////////////////////////////

and  Pos : MEM = POSzero
               | POSinfinity
               | POSint      (int, Pos)
               | POSlabel    (Id,  Pos)
               | POSadaptive (int, int [], Pos)
;

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printer for matching trees.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, Match);

///////////////////////////////////////////////////////////////////////////////
//
//  Function to reverse the polarity of a pattern.
//
///////////////////////////////////////////////////////////////////////////////

extern Polarity rev( Polarity);

///////////////////////////////////////////////////////////////////////////////
//
//  Function to compute the match variables for a list of match expressions.
//  Match variables are temporaries generated for complex expressions to
//  prevent redundent evaluations.
//
///////////////////////////////////////////////////////////////////////////////

extern void compute_match_variables( MatchExps);

///////////////////////////////////////////////////////////////////////////////
//
//  Function to convert a string into an array pattern.  This converts string
//  patterns to be decomposed into a web of character patterns, allowing
//  (potentially) more efficient matching.
//
///////////////////////////////////////////////////////////////////////////////

extern Pats make_string_pattern( const char *);

///////////////////////////////////////////////////////////////////////////////
//
//  Functions to decorate the pattern for projection bindings.
//  These are called to annotate a pattern with pattern variable bindings.
//  The new bindings are entered into the pattern variable environments.
//  These are called from the parser.
//
///////////////////////////////////////////////////////////////////////////////

extern void decor( Pat, Exp, Polarity, Bool, PatternVarEnv&, int&);
extern void decor( MatchExps, Pat, Polarity, Bool, PatternVarEnv&, int&);
extern void decor( MatchExps&, Pat, PatternVarEnv&, int&, int = -1);

///////////////////////////////////////////////////////////////////////////////
//
//  Functions to decorate the pattern for attribute and cost bindings
//  inside rewrite rules.  These are also called from the parser.
//
///////////////////////////////////////////////////////////////////////////////

extern int decor_rewrite( Pat,  int, int, PatternVarEnv&);
extern int decor_rewrite( Pats, int, int, PatternVarEnv&);
extern int decor_rewrite( Pat,  int, PatternVarEnv&);

///////////////////////////////////////////////////////////////////////////////
//
//  Auxiliary function to retrieve the position vector of a decision tree.
//  This is used during the pattern matching compilation process.
//
///////////////////////////////////////////////////////////////////////////////

extern Pos get_pos( Match);

///////////////////////////////////////////////////////////////////////////////
//
//  Auxiliary functions to compute information on a matching tree.
//  These are used during the pattern matching compilation process to
//  eliminate redundant tests and for error detection.
//
///////////////////////////////////////////////////////////////////////////////

Bool          refutable( Match);                  // Is the pattern refutable?
void          matchables( Match, BitSet&);        // Set of matchable rules.
void          always_matchables( Match, BitSet&); // Set of always matching
const BitSet& always_matchables( Match, int);     // rules.

///////////////////////////////////////////////////////////////////////////////
//
//  Functions to perform substitutions on expressions.
//  All INDexp(i) nodes are substituted with the corresponding replacement.
//
///////////////////////////////////////////////////////////////////////////////

extern Exp     subst (Exp,     Exp replacements[]);
extern Exps    subst (Exps,    Exp replacements[]);
extern LabExps subst (LabExps, Exp replacements[]);

///////////////////////////////////////////////////////////////////////////////
//
//  Hashing and equality for literals.
//  These are used in the matching tree -> dag conversion process.
//
///////////////////////////////////////////////////////////////////////////////

extern unsigned int literal_hash  (HashTable::Key);
extern Bool         literal_equal (HashTable::Key, HashTable::Key);

///////////////////////////////////////////////////////////////////////////////
//
//  Hashing and equality for position vectors.
//  These are used in the matching tree -> dag conversion process.
//
///////////////////////////////////////////////////////////////////////////////

extern unsigned int pos_hash  (HashTable::Key);
extern Bool         pos_equal (HashTable::Key, HashTable::Key);

///////////////////////////////////////////////////////////////////////////////
//
//  Functions to check for refutability of a pattern.  These are used
//  in the pattern sindexing scheme.
//
///////////////////////////////////////////////////////////////////////////////

extern Bool is_refutable  (Pat);
extern Bool is_refutable  (Pats);
extern Bool is_refutable  (LabPats);

///////////////////////////////////////////////////////////////////////////////
//
//  The current index map.  This map is computed when using the adaptive
//  pattern matching scheme.
//
///////////////////////////////////////////////////////////////////////////////

extern HashTable * current_index_map;

///////////////////////////////////////////////////////////////////////////////
//
//  Methods for compute indexing information of a pattern.  These are
//  used in the adaptive scheme.
//
///////////////////////////////////////////////////////////////////////////////

extern void indexing (int, Pat, Pos, HashTable&);
extern void indexing (int, Pats, Pos, HashTable&);
extern void indexing (MatchRules, HashTable&);

extern       Bool same_selectors;

extern Exp select (Exp, Cons, Ty = NOty);

///////////////////////////////////////////////////////////////////////////////
//
//   Equality on expressions.
//
///////////////////////////////////////////////////////////////////////////////

extern Bool equal (Exp, Exp);
extern Bool equal (Exps, Exps);
extern Bool equal (LabExps, LabExps);

///////////////////////////////////////////////////////////////////////////////
//
//  Substitution functions on patterns.  These are used to implement
//  pattern laws.
//
///////////////////////////////////////////////////////////////////////////////

extern Pat     subst (Pat,     Pat [], Bool);
extern Pats    subst (Pats,    Pat [], Bool);
extern LabPats subst (LabPats, Pat [], Bool);

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to translate a match tree into an anotated tree with tree parsing
//  cost.
//
///////////////////////////////////////////////////////////////////////////////

extern Match translate_treecost (Match, MatchRules);

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to enter and lookup a pattern constructor.
//  These interact with the pattern/constructor environment.
//  Called from the parser.
//
///////////////////////////////////////////////////////////////////////////////

extern Pat  apply_pat  (Pat, Pat);

///////////////////////////////////////////////////////////////////////////////
//
//  The following is the interface definition of the pattern matching compiler.
//
///////////////////////////////////////////////////////////////////////////////

class MatchCompiler : virtual public CodeGen
{
  MatchCompiler(const MatchCompiler&);    // no copy constructor
  void operator = (const MatchCompiler&); // no assignment

protected:
  LabelGen vars, labels;                         // labels generators
  int merges, ifs, switches, gotos, goto_labels; // match compiler statistics
  MatchOptions     current_options;
  MatchRule        current_rule;

  static HashTable quark_map;
  static LabelGen  quark_labels;

public:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor and destructor
  //
  ////////////////////////////////////////////////////////////////////////////
           MatchCompiler();
  virtual ~MatchCompiler();

  static Id quark_name(Id);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to compute the selection/projection function from a datatype
  //  domain.  This is used in the pattern binding annotation process.
  //
  ////////////////////////////////////////////////////////////////////////////
  static Exp untag(Exp, Ty);
  static Exp untag_one(Exp, Cons);
  static Exp make_select (Exp, Cons, Ty = NOty, Id = 0);
  static Exp tag_name_of (Cons, Bool normalized);

protected:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to compile pattern matching.
  //
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to for translation a pattern into a pattern matching tree.
  //
  ////////////////////////////////////////////////////////////////////////////
  Match trans          (Pat, Pos, Bool, Match, Match);
  Match trans          (Pats, int, Pos, Bool, Match, Match);
  Match trans          (Pats, Pos, Bool, Match, Match, int []);
  Match trans          (LabPats, Pos, Bool, Match, Match);
  Match trans_merge    (int, MatchRules, int, Cost *);
  Match trans_no_merge (int, int, MatchRules, int, Cost *);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to for tree composition/merging and tree to dag conversion.
  //
  ////////////////////////////////////////////////////////////////////////////
  Match compose        (Match, Match);
  Match merge          (Match, Match);
  Match make_dag       (Match, MatchOptions, MatchRules);
  Match match_of       (int, MatchRules, MatchOptions);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods for generating high level statements and trace instrumentation.
  //
  ////////////////////////////////////////////////////////////////////////////
  void gen_match_stmt              (MatchExps, MatchRules,
                                    MatchOptions = MATCHnone, Ty = NOty);
  void gen_fun_def                 (FunDefs);
  void gen_match_variables         (MatchExps, Ty);
  void gen                         (Match, MatchOptions=MATCHnone, Ty=NOty);
  void gen_matchall_suffix         (int, Match, MatchRules, Bool);
  void gen_match_cost_minimization (int, Match, MatchRules, Bool);
  void gen_success_match           (int, const BitSet *, MatchRules);
  void gen_cost_success_match      (int, const BitSet *, MatchRules);
  virtual void gen_treecost_match  (Match, const BitSet *, MatchRules) = 0;
  virtual void gen_treelabel_match (Match, Ty, Ty, int) = 0;

  void instrument_trace            (MatchRules);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Method for generating range matching
  //
  ////////////////////////////////////////////////////////////////////////////
  void gen_range_match (Pos, Exp, int, int, Match, Match, Match);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Method for generating view matching
  //
  ////////////////////////////////////////////////////////////////////////////
  void gen_view_match (Id, Exp, Exp, int, Cons [], Match [], Match,
                       TyOpt, TyQual);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Low level methods for specific pattern matching constructs:
  //  C/C++ switches, binary search on literals, regular expression matching,
  //  and quarks matching code.
  //
  ////////////////////////////////////////////////////////////////////////////
  void gen_switch  (Id, Exp, Ty, int, Cons [], Match [], Match, int shared,
                    Bool, Bool, TyOpt, Bool);
  void gen_binary_search_on_literals(Exp, int, Literal [], Match [], Match);
  void gen_regexp_match
       (Exp, int, Literal [], Match [], Match, MatchOptions, Ty);
  void gen_quark_match
       (Exp, int, Literal [], Match [], Match, MatchOptions);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to generating debugging code.
  //
  ////////////////////////////////////////////////////////////////////////////
  int current_rule_line () const;
  const char * current_rule_text () const;

private:
  ///////////////////////////////////////////////////////////////////////////////
  //
  //  Functions for allocating arrays of Literal and Match.
  //  Used during the pattern matching compilation process.
  //
  ///////////////////////////////////////////////////////////////////////////////
  Literal * Literals (int);
  Match *   Matches  (int);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Object to mark the current rule
//
///////////////////////////////////////////////////////////////////////////////

class MarkCurrentRule
{
  MarkCurrentRule();
  MarkCurrentRule(const MarkCurrentRule&);
  void operator = (const MarkCurrentRule&);
  MatchRule& current_rule;
  MatchRule  old_rule;
protected:
  MarkCurrentRule(MatchRule&, MatchRule);
  ~MarkCurrentRule();
  friend class MatchCompiler;
  friend class RewritingCompiler;
};

#endif
