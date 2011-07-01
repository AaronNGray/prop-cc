///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the interface of the rewriting compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef rewriting_compiler_h
#define rewriting_compiler_h

#include "matchcom.h"
#include "classdef.h"
#include "ast.h"
#include "hashtab.h"
#include <AD/automata/treegram.h>

class FunctorMap;
class TRS;

///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent a rewrite class
//
///////////////////////////////////////////////////////////////////////////////

class RewriteClass : public ClassDefinition
{
  RewriteClass( const RewriteClass&);
  void operator = ( const RewriteClass&);

  HashTable index_info;
public:
  RewriteClass( Id, Protocols, Inherits, TyQual, Decls);
  ~RewriteClass();
  virtual void gen_class_interface( CodeGen&);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent indexing information
//
///////////////////////////////////////////////////////////////////////////////

class RewriteIndexing : public Loc
{
  RewriteIndexing( const RewriteIndexing&);
  void operator = ( const RewriteIndexing&);
public:
  Ty    ty;       // type in question
  Id    name;     // name of index
  Bool  external; // external index?
public:
  RewriteIndexing( Ty, Id, Bool);
  ~RewriteIndexing();
};

///////////////////////////////////////////////////////////////////////////////
//
//  The rewriting compiler is inherited from the pattern matcher.
//
///////////////////////////////////////////////////////////////////////////////

class RewritingCompiler : virtual public CodeGen,
      virtual public MatchCompiler
{
  RewritingCompiler( const RewritingCompiler&); // no copy constructor
  void operator = ( const RewritingCompiler&);  // no assignment

private:

  friend class RewriteClass;
  friend class RewriteMix;
  friend class TRS;

  Decls        rewriters;           // outstanding rewriting declarations.
  FunctorMap * Fmap;                // functormap;
  RewriteIndexings indices;         // current set of indices
  TRS *        trs;                 // for partial evaluation
  static HashTable rewrite_classes; // all the rewrite classes declared

public:
  ////////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////////
  RewritingCompiler();
  virtual ~RewritingCompiler();

  typedef TreeGrammar::Functor Functor;

protected:
  ////////////////////////////////////////////////////////////////////////////
  //  Methods for compiling rewriting
  ////////////////////////////////////////////////////////////////////////////

  // generate a set of rewrite rules
  void gen_rewrite( Id, RewriteIndexings, MatchRules);

  // generate a rewrite statement
  void gen_rewriting( Protocols, Exp, Exp,RewriteIndexings,MatchRules,TyQual);

  // generate a set of outstanding rewrite statements
  void gen_rewriters();

  // generate a replacement statement
  void gen_replacement( Exp, MatchRuleInfo::RewritingMode);

  // generate a cut/replacement statement
  void gen_cutreplacement( Exp, MatchRuleInfo::RewritingMode);

  // generate a failrewrite statement
  void gen_failrewrite( MatchRuleInfo::RewritingMode);

  virtual void optimize_rewrite() = 0;

private:
  ////////////////////////////////////////////////////////////////////////////
  //  Methods for compiling a bottomup tree pattern matcher
  ////////////////////////////////////////////////////////////////////////////
  void gen_static_rewriter( FunctorMap&);
  void gen_dynamic_rewriter( FunctorMap&);
  void generate_tables( FunctorMap&);

  ////////////////////////////////////////////////////////////////////////////
  //  Methods for generating static labelers
  ////////////////////////////////////////////////////////////////////////////
  void generate_static_labelers( FunctorMap&);
  void gen_literal_labeler( FunctorMap&, Ty);
  void gen_datatype_labeler( FunctorMap&, Ty);

  void gen_before_rules( FunctorMap&, Ty);
  void gen_preorder_rules( FunctorMap&, Ty);
  void gen_postorder_rules( FunctorMap&, Ty);
  void gen_topdown_rules( FunctorMap&, Ty);
  void gen_auxiliary_rules( FunctorMap&, Ty,MatchRuleInfo::RewritingMode);

  void gen_bottomup_traversals( FunctorMap&, Ty);
  void gen_bottomup_traversals( FunctorMap&, Functor, int, Cons[], Ty);
  void gen_one_traversal( FunctorMap&, Functor, Cons, Ty);
  void gen_component_traversal( FunctorMap&, Functor, Cons, Ty);
  void gen_single_component_traversal( FunctorMap&,Cons,Ty);
  void gen_tuple_component_traversal( FunctorMap&,Cons,int,Tys);
  void gen_record_component_traversal( FunctorMap&,Cons,int,Bool [],Ids,Tys);

  ////////////////////////////////////////////////////////////////////////////
  //  Methods for generating dynamic labelers
  ////////////////////////////////////////////////////////////////////////////
  void generate_dynamic_labelers( FunctorMap&);
  void generate_state_record( FunctorMap&);
  void generate_accept_rules_tables( FunctorMap&);
  void generate_closures( FunctorMap&);
  void gen_closure( FunctorMap&, Id, MatchRules);
  void gen_dynamic_datatype_labeler( FunctorMap&, Ty);
  void gen_dynamic_traversals( FunctorMap&, Ty);
  void gen_dynamic_traversals( FunctorMap&, int, Cons[], Ty);
  void gen_one_dynamic_traversal( FunctorMap&, Cons, Ty);
  void gen_component_dynamic_traversal( FunctorMap&, Cons, Ty);
  void gen_single_component_dynamic_traversal( FunctorMap&,Cons,Ty);
  void gen_tuple_component_dynamic_traversal( FunctorMap&,Cons,int,Tys);
  void gen_record_component_dynamic_traversal( FunctorMap&,Cons,int,Bool [],Ids,Tys);
  virtual void gen_treecost_match( Match, const BitSet *, MatchRules);
  virtual void gen_treelabel_match( Match, Ty, Ty, int);

  ////////////////////////////////////////////////////////////////////////////
  //  Methods for generating actions.
  ////////////////////////////////////////////////////////////////////////////
  void gen_action( FunctorMap&, Ty);
  void gen_cost_labeler_action( FunctorMap&, Ty, MatchRules, Bool);
  void gen_costless_guarded_labeler_action( FunctorMap&, MatchRules);
  void gen_costless_guardless_labeler_action( FunctorMap&, MatchRules);
  void gen_cost_rewriter_action( FunctorMap&, MatchRules);
  void gen_costless_guarded_rewriter_action( FunctorMap&, MatchRules);
  void gen_costless_guardless_rewriter_action( FunctorMap&, MatchRules);

  ////////////////////////////////////////////////////////////////////////////
  //  Methods for generating reducers.
  ////////////////////////////////////////////////////////////////////////////
  void generate_reducers( FunctorMap&);
  void gen_datatype_reducers( FunctorMap&);
  void gen_datatype_reducer( FunctorMap&, Ty);
  int  gen_pattern_traversal( FunctorMap&, Id lhs, Pat, int);
  int  gen_pattern_traversal( FunctorMap&, Id lhs, Pats, int);
  int  gen_pattern_traversal( FunctorMap&, Id lhs, LabPats, int);

  ////////////////////////////////////////////////////////////////////////////
  //  Methods to add and lookup a rewrite class
  ////////////////////////////////////////////////////////////////////////////
  friend class FunctorMap;
  static void add_rewrite_class( RewriteClass *);
  static RewriteClass * lookup_rewrite_class(Id);
  static Protocols      lookup_protocols(Id);
  static TyQual         lookup_qual(Id);

  ////////////////////////////////////////////////////////////////////////////
  //  Methods for indices
  ////////////////////////////////////////////////////////////////////////////
  const RewriteIndexing * get_index(Ty) const;
  Bool compute_index(Ty, Id& name, Bool& external) const;
  Bool has_index(Ty) const;
  Id   gen_get_rewrite_state( Ty, Exp);
  void gen_get_rewrite_state( Ty, Id);
  void gen_set_rewrite_state_and_rule( Ty, Id);
  void gen_get_rewrite_rule( Ty, Id);

  ////////////////////////////////////////////////////////////////////////////
  //  Methods for tracing
  ////////////////////////////////////////////////////////////////////////////
  void gen_trace_macro( Id, FunctorMap&);
};

extern Id redex_name(Ty);

#endif
