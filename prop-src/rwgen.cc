///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\rwgen.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_nco_c_c_Q1("redex");
#line 1 "../../prop-src/rwgen.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the tree rewriting/tree parsing compiler.
//  This is used to implement the rewrite class/rewrite constructs of Prop.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <strstream>
#include <AD/automata/treegram.h>
#include <AD/automata/treegen.h>
#include <AD/automata/topdowng.h>
#include <AD/rewrite/burs_gen.h>
#include <AD/strings/quark.h>
#include "funmap.h"
#include "ir.h"
#include "ast.h"
#include "matchcom.h"
#include "type.h"
#include "hashtab.h"
#include "datagen.h"
#include "config.h"
#include "rwgen.h"
#include "options.h"
#include "trs.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor of the rewriting compiler.
//
///////////////////////////////////////////////////////////////////////////////

RewritingCompiler::RewritingCompiler()
    : rewriters(
#line 35 "../../prop-src/rwgen.pcc"
#line 35 "../../prop-src/rwgen.pcc"
nil_1_
#line 35 "../../prop-src/rwgen.pcc"
#line 35 "../../prop-src/rwgen.pcc"
), Fmap(0), trs(0) {}
RewritingCompiler::~RewritingCompiler() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Import some type definitions from the tree grammar and hash table
//  classes.
//
///////////////////////////////////////////////////////////////////////////////

typedef TreeGrammar::TreeProduction TreeProduction;
typedef TreeGrammar::Cost           TreeCost;

///////////////////////////////////////////////////////////////////////////////
//
//  Compute the name of the redex.
//
//////////////////////////////////////////////////////////////////////////////

Id redex_name( Ty ty)
{
  
#line 56 "../../prop-src/rwgen.pcc"
#line 61 "../../prop-src/rwgen.pcc"
{
  Ty _V1 = deref_all(ty);
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
              if (
#line 58 "../../prop-src/rwgen.pcc"
              (_DATATYPEtycon(_TYCONty(_V1)->_1)->opt & OPTtaggedpointer)
#line 58 "../../prop-src/rwgen.pcc"
) {
                
#line 59 "../../prop-src/rwgen.pcc"
               return "derefp(redex)"; 
#line 59 "../../prop-src/rwgen.pcc"
              } else {
                
                L1:; 
#line 61 "../../prop-src/rwgen.pcc"
               return "redex"; 
#line 61 "../../prop-src/rwgen.pcc"
              }
              } break;
            default: { goto L1; } break;
          }
        } else { goto L1; }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 62 "../../prop-src/rwgen.pcc"
#line 62 "../../prop-src/rwgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create a RewriteClass
//
///////////////////////////////////////////////////////////////////////////////

RewriteClass::RewriteClass( Id id, Protocols p, Inherits i, TyQual q, Decls b)
    : ClassDefinition( REWRITE_CLASS, id, 
#line 72 "../../prop-src/rwgen.pcc"
#line 72 "../../prop-src/rwgen.pcc"
nil_1_
#line 72 "../../prop-src/rwgen.pcc"
#line 72 "../../prop-src/rwgen.pcc"
,
        add_inherit("BURS", 
#line 73 "../../prop-src/rwgen.pcc"
#line 73 "../../prop-src/rwgen.pcc"
nil_1_
#line 73 "../../prop-src/rwgen.pcc"
#line 73 "../../prop-src/rwgen.pcc"
, i), q, b), index_info(ty_hash,ty_equal)
{
  protocols = p;
  RewritingCompiler::add_rewrite_class(this);
}

RewriteClass::~RewriteClass() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate an interface of a rewrite class.
//
///////////////////////////////////////////////////////////////////////////////

void RewriteClass::gen_class_interface( CodeGen& C)
{
  Bool is_app = qualifiers & QUALapplicative;
  C.pr(
        "%-%^private:%+"
        "%^%s(const %s&);               // no copy constructor"
        "%^void operator = (const %s&); // no assignment"
        "%-%^public:%+"
        "%^struct %s_StateRec * stack__, * stack_top__;",
        class_name, class_name, class_name, class_name
      );

  Bool gen_reducers = qualifiers & QUALtreeparser;

  if ( !gen_reducers)
    C.pr(
         "%-%^public:%+"
         "%^%s labeler(const char *, int&, int);"
         "%^%s labeler(Quark, int&, int);",
         (is_app ? "const char *" : "void"),
         (is_app ? "Quark       " : "void")
        );

  {
    for_each (Protocol, p, protocols)
    {
      
#line 113 "../../prop-src/rwgen.pcc"
#line 156 "../../prop-src/rwgen.pcc"
{
#line 116 "../../prop-src/rwgen.pcc"
  
  Ty t = (is_app || gen_reducers) ? p->ty : mkrefty(p->ty);
  Ty r = (is_app || gen_reducers) ? p->ty : void_ty;
  if (gen_reducers)
    C.pr(
         "%^       void labeler(%t);"
         "%^inline virtual void operator () (%t) { labeler(redex); }",
         t, "redex", t, "redex"
       );
  else
    C.pr(
         "%^       %t labeler(%t, int&, int);"
         "%^inline virtual %t operator () (%t) { int s; %slabeler(redex,s,0); }",
         r, "", t, "redex",
         r, "", t, "redex",
         (is_app ? "return " : "")
        );
  if (gen_reducers)
  {
    if (p->inh != NOty)
      C.pr(
            "%^       %t reduce(%t,%t,int lhs = 1);",
            (p->syn == NOty ? void_ty : p->syn), "", p->ty, "redex",
            p->inh, "inh__"
          );
    else
      C.pr(
            "%^       %t reduce(%t,int lhs = 1);",
            (p->syn == NOty ? void_ty : p->syn), "", p->ty, "redex"
          );
  }
  if (! gen_reducers && p->syn != NOty)
    error("%Lsynthesized attribute '%T' can only be used in treeparser mode in rewrite class %s\n",
          p->syn, class_name);
  if (! gen_reducers && p->inh != NOty)
    error("%Linherited attribute '%T' can only be used in treeparser mode in rewrite class %s\n",
          p->syn, class_name);
  //if (gen_reducers && ! has_qual(QUALrewritable,deref_all(ty)))
  //   error("%Ltype '%T' is not rewritable in treeparser mode rewrite class %s\n",
  //         ty, class_name);
  
#line 156 "../../prop-src/rwgen.pcc"
}
#line 157 "../../prop-src/rwgen.pcc"
#line 157 "../../prop-src/rwgen.pcc"

    }
  }

  C.pr( "%-%^private:%+");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the body of a rewrite class
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_rewrite
   (Id name, RewriteIndexings Is, MatchRules rules)
{
  ////////////////////////////////////////////////////////////////////////////
  // Get the current limit on the memory pool
  ////////////////////////////////////////////////////////////////////////////
  MemPoolMark marker = mem_pool.getMark();
  indices = Is;

  ////////////////////////////////////////////////////////////////////////////
  // Instrument the rules if tracing is used.
  ////////////////////////////////////////////////////////////////////////////
  if ( options.trace)
    instrument_trace( rules);

  ////////////////////////////////////////////////////////////////////////////
  // Create a functor map
  ////////////////////////////////////////////////////////////////////////////
  FunctorMap F( name, rules);
  FunctorMap * oldFmap = Fmap;
  Fmap = &F;

  ////////////////////////////////////////////////////////////////////////////
  // Compile rules into a tree grammar
  ////////////////////////////////////////////////////////////////////////////
  if ( F.ok())
  {
    gen_trace_macro( name, F);
    if (F.dynamic_search)
      gen_dynamic_rewriter( F);
    else
      gen_static_rewriter( F);
  }

  ////////////////////////////////////////////////////////////////////////////
  // Reset the limit on the memory pool
  ////////////////////////////////////////////////////////////////////////////
  mem_pool.setMark( marker);
  Fmap = oldFmap;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a bottom-up tree automaton, with static tables.
//  This is faster than the dynamic method but may utilize much more space
//  and preprocessing time.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_static_rewriter( FunctorMap& F)
{
  MemPool my_pool(4096);                    // Create a new memory pool
  // Create a new tree automaton

  if ( F.has_cost)
    F.tree_gen = new BURS_Gen(my_pool);
  else
    F.tree_gen = new TreeGen (my_pool);

  F.tree_gen->compile( F.G);                // Compile the tree grammar
  F.tree_gen->compile_compression_index();  // Generate the compressed index

  if (options.optimize_rewrite)
    optimize_rewrite();

  ////////////////////////////////////////////////////////////////////////////
  // Check whether we should use the compressed index maps.
  ////////////////////////////////////////////////////////////////////////////
  double shrinkage = F.tree_gen->compression_rate();
  if (shrinkage <= 0.3 || F.tree_gen->number_of_states() <= 40)
    F.use_compression = false;

  ////////////////////////////////////////////////////////////////////////////
  // Generate the set of tables
  ////////////////////////////////////////////////////////////////////////////
  generate_tables( F);

  ////////////////////////////////////////////////////////////////////////////
  // Generate code for the labelers
  ////////////////////////////////////////////////////////////////////////////
  generate_static_labelers( F);

  ////////////////////////////////////////////////////////////////////////////
  // Generate code for the reducers
  ////////////////////////////////////////////////////////////////////////////
  if (F.gen_reducers)
    generate_reducers(F);

  ////////////////////////////////////////////////////////////////////////////
  // Print a report
  ////////////////////////////////////////////////////////////////////////////
  if (options.generate_report)
  {
    F.print_report(open_logfile());
    if (trs)
      trs->print_report(open_logfile());
  }

  ////////////////////////////////////////////////////////////////////////////
  // Cleanup the tree automaton compiler.
  ////////////////////////////////////////////////////////////////////////////
  delete F.tree_gen;
  delete F.topdown_gen;
  delete trs;
  F.tree_gen = 0;
  F.topdown_gen = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the labelers.  The labelers are responsible for
//  traversing the tree bottom-up and compute the states.
//
///////////////////////////////////////////////////////////////////////////////#

void RewritingCompiler::generate_static_labelers( FunctorMap& F)
{
  ////////////////////////////////////////////////////////////////////////////
  // Generate the labelers for the literals
  ////////////////////////////////////////////////////////////////////////////
  gen_literal_labeler( F, string_ty);
  gen_literal_labeler( F, quark_ty);

  ////////////////////////////////////////////////////////////////////////////
  // Generate the labelers for the datatypes
  ////////////////////////////////////////////////////////////////////////////
  foreach_entry (e, F.type_map)
  {
    Ty ty = Ty(F.type_map.key(e));
    debug_msg("[Rewrite class %s: generating labeler for datatype %T\n",
              F.class_name, ty);
    gen_datatype_labeler(F, ty);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the automaton tables for a rewrite class.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::generate_tables( FunctorMap& F)
{
  Id id = F.class_name;

  ////////////////////////////////////////////////////////////////////////////
  // Table of the first matching rule.
  ////////////////////////////////////////////////////////////////////////////
  if (F.gen_reducers && ! F.has_guard) F.tree_gen->gen_accept1(*output,id);

  ////////////////////////////////////////////////////////////////////////////
  // Table of bitmaps of all the accepted rules.
  ////////////////////////////////////////////////////////////////////////////
  // if (F.has_cost_exp) F.tree_gen->gen_bitmap_accept(*output,id);

  ////////////////////////////////////////////////////////////////////////////
  // Table of lists of all the accepted rules.
  ////////////////////////////////////////////////////////////////////////////
  if (F.has_guard || F.has_cost_exp) F.tree_gen->gen_accept(*output,id);

  ////////////////////////////////////////////////////////////////////////////
  // Generate the theta tables
  ////////////////////////////////////////////////////////////////////////////

  for( Functor f = F.G.min_functor(); f <= F.G.max_functor(); f++)
  {
    if (F.G.arity(f) > 0)
    {
      Bool is_singleton = true;
      for (int i = 0; i < F.G.arity(f); i++)
      {
        if (F.tree_gen->index_range(f,i) > 1)
          { is_singleton = false; break; }
      }
      if (! is_singleton)
      {
        pr("%^");
        F.tree_gen->gen_theta(*output,f,id);
        pr("\n\n");
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
  // Generate the mu tables
  ////////////////////////////////////////////////////////////////////////////
  if (F.use_compression)
  {
    ////////////////////////////////////////////////////////////////////////
    // Generate the compressed mu's
    ////////////////////////////////////////////////////////////////////////
    F.tree_gen->gen_compressed_index(*output,id);
  }
  else
  {
    ////////////////////////////////////////////////////////////////////////
    // Generate the uncompressed mu's
    ////////////////////////////////////////////////////////////////////////
    for(Functor f = F.G.min_functor(); f <= F.G.max_functor(); f++)
    {
      for (int i = 0; i < F.G.arity(f); i++)
      {
        if (F.tree_gen->index_range(f,i) > 1)
        {
          pr("%^");
          F.tree_gen->gen_index(*output,f,i,id);
          pr("\n\n");
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the literal labelers.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_literal_labeler( FunctorMap& F, Ty ty)
{
  ///////////////////////////////////////////////////////////////////////////
  // Protocol of this new labeler
  ///////////////////////////////////////////////////////////////////////////
  pr(
      "%^inline %t %s::labeler(%t,int& s__,int)"
      "%^{%+",
      (F.is_applicative ? ty : void_ty), "", // return type
      F.class_name, ty, "redex"              // argument is always named redex
    );

  ///////////////////////////////////////////////////////////////////////////
  // Rules to apply before rewriting
  ///////////////////////////////////////////////////////////////////////////
  gen_before_rules( F,ty);
  gen_preorder_rules( F,ty);
  gen_topdown_rules( F,ty);

  ///////////////////////////////////////////////////////////////////////////
  // The selector is named 'redex'
  ///////////////////////////////////////////////////////////////////////////
  Exp        selector = IDexp("redex");
  MatchExps  exps     = 
#line 412 "../../prop-src/rwgen.pcc"
#line 412 "../../prop-src/rwgen.pcc"
list_1_(MATCHexp(selector,0))
#line 412 "../../prop-src/rwgen.pcc"
#line 412 "../../prop-src/rwgen.pcc"
;
  MatchRules rules    = // Default is state zero.
      
#line 414 "../../prop-src/rwgen.pcc"
#line 414 "../../prop-src/rwgen.pcc"
list_1_(MATCHrule(0,WILDpat(),NOexp,NOcost,list_1_(SETSTATEdecl(0))))
#line 414 "../../prop-src/rwgen.pcc"
#line 414 "../../prop-src/rwgen.pcc"
;

  ///////////////////////////////////////////////////////////////////////////
  // Now translate the pattern literals into a matching rule
  ///////////////////////////////////////////////////////////////////////////
  foreach_entry ( e, F.literal_map)
  {
    Literal l = Literal(F.literal_map.key(e));
    if (type_of(l) == ty)
    {
      Functor f      = F.literal_map.value(e);
      Pat pat        = LITERALpat(l);
      pat->selector  = selector;
      MatchRule rule = MATCHrule(0,pat,NOexp,NOcost,
                          
#line 428 "../../prop-src/rwgen.pcc"
#line 428 "../../prop-src/rwgen.pcc"
list_1_(SETSTATEdecl(F.tree_gen->go(f)))
#line 428 "../../prop-src/rwgen.pcc"
#line 428 "../../prop-src/rwgen.pcc"
);
      rules = 
#line 429 "../../prop-src/rwgen.pcc"
#line 429 "../../prop-src/rwgen.pcc"
list_1_(rule,rules)
#line 429 "../../prop-src/rwgen.pcc"
#line 429 "../../prop-src/rwgen.pcc"
;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Call the pattern matching compiler to generate the match statement.
  // Disable tracing code since this is not properly part of the user
  // program.
  ///////////////////////////////////////////////////////////////////////////
  gen_match_stmt( exps, rules, MATCHnotrace);

  ///////////////////////////////////////////////////////////////////////////
  //  Rules to apply after rewriting
  ///////////////////////////////////////////////////////////////////////////
  gen_postorder_rules( F, ty);

  ///////////////////////////////////////////////////////////////////////////
  // End of this routine
  ///////////////////////////////////////////////////////////////////////////
  if ( F.is_applicative)
    pr("%^return redex;");
  pr("%-%^}\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the datatype labeler
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_datatype_labeler( FunctorMap& F, Ty ty)
{
  Ty   arg_ty = F.is_applicative ? ty : mkrefty(ty); // argument type
  Ty   ret_ty = F.is_applicative ? ty : void_ty;     // return type

  ///////////////////////////////////////////////////////////////////////////
  // Should we cache the state we've computed?
  // Do so if the type is declared to be rewritable and it has at least
  // one boxed variant.
  ///////////////////////////////////////////////////////////////////////////
  // Bool cache_state = boxed_variants(ty) && has_qual(QUALrewritable,ty) &&
  //                   (Used::replacement || F.gen_reducers);
  Bool has_topdown_rules = F.topdown_rule_map.contains(ty);

  ///////////////////////////////////////////////////////////////////////////
  // Generate the protocol of this labeler routine
  ///////////////////////////////////////////////////////////////////////////
  pr(
      "%^%t %s::labeler (%t, int& s__, int r__)"
      "%^{",
      ret_ty, "", F.class_name, arg_ty, "redex"
    );

  ///////////////////////////////////////////////////////////////////////////
  // Name of the redex inside this routine.
  ///////////////////////////////////////////////////////////////////////////
  gen_before_rules( F, ty);

  pr ("%^replacement__:%+");

  gen_preorder_rules( F, ty);

  if (has_topdown_rules)
     pr("%^for (int topdown__ = 0; topdown__ <= 1; topdown__++) {%+");

  ///////////////////////////////////////////////////////////////////////////
  // Name of the redex inside this routine.
  ///////////////////////////////////////////////////////////////////////////
  Id redex = redex_name( ty);

  ///////////////////////////////////////////////////////////////////////////
  // Generate code to cut short the labeling process if we are caching the
  // state.
  ///////////////////////////////////////////////////////////////////////////
  // if (cache_state)
  //    pr ("%^if (r__ && boxed(redex) && %s->has_rewrite_state())"
  //        "%^{ s__ = %s->get_rewrite_state(); return%s; }",
  //        redex, redex, (F.is_applicative ? " redex" : ""));
  gen_get_rewrite_state( ty, redex);

  gen_topdown_rules( F, ty);

  ///////////////////////////////////////////////////////////////////////////
  // Generate code for bottomup traversal on the datatype
  ///////////////////////////////////////////////////////////////////////////
  gen_bottomup_traversals( F, ty);

  ///////////////////////////////////////////////////////////////////////////
  // Generate the suffix for topdown rules.
  ///////////////////////////////////////////////////////////////////////////
  if (has_topdown_rules)
     pr("%-%^}");

  ///////////////////////////////////////////////////////////////////////////
  // Generate code for the action routines
  ///////////////////////////////////////////////////////////////////////////
  gen_action( F, ty);

  ///////////////////////////////////////////////////////////////////////////
  // Generate code to update the cached state(when applicable)
  ///////////////////////////////////////////////////////////////////////////
  // pr("%-%^update_state__: ;%+");
  // if (cache_state)
  // {  pr ("%^if (boxed(redex)) {%+"
  //        "%^%s->set_rewrite_state(s__);", redex);
  //    if (F.gen_reducers)
  //       pr ("%^%s->set_rewrite_rule(rule__);", redex);
  //    pr ("%-%^}");
  // }
  gen_set_rewrite_state_and_rule( ty, redex);

  ///////////////////////////////////////////////////////////////////////////
  //  Rules to apply after rewriting
  ///////////////////////////////////////////////////////////////////////////
  gen_postorder_rules( F, ty);

  ///////////////////////////////////////////////////////////////////////////
  // If it is applicative, generate a return statement
  ///////////////////////////////////////////////////////////////////////////
  if (F.is_applicative)
    pr ( "%^return redex;");

  ///////////////////////////////////////////////////////////////////////////
  // End of this routine
  ///////////////////////////////////////////////////////////////////////////
  pr( "%^%-%^}\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the bottomup traversal code for a datatype labeler.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_bottomup_traversals(FunctorMap& F, Ty ty)
{
  Id redex  = redex_name(ty);
  Functor f = F.type_map[ty];             // functor encoding
  
#line 567 "../../prop-src/rwgen.pcc"
#line 620 "../../prop-src/rwgen.pcc"
{
  Ty _V2 = deref_all(ty);
  if (_V2) {
    switch (_V2->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V2)->_1)) {
          switch (_TYCONty(_V2)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 570 "../../prop-src/rwgen.pcc"
              
              int  arity         = _DATATYPEtycon(_TYCONty(_V2)->_1)->unit + _DATATYPEtycon(_TYCONty(_V2)->_1)->arg;  // arity of this datatype
              Bool fast_encoding = false;
              int  first_state   = F.tree_gen->go(f);
              
              // Check whether fast encoding should be used.
              // This changes a switch statement into addition.
              if (_DATATYPEtycon(_TYCONty(_V2)->_1)->arg == 0)
              {
                int i;
                for (i = arity - 1; i >= 0; i--)
                  if (first_state + i != F.tree_gen->go(f+i)) break;
                fast_encoding = i < 0;
              }
              
              //
              // Views cannot use the fast encoding
              //
              if (_DATATYPEtycon(_TYCONty(_V2)->_1)->qualifiers & QUALview)
                fast_encoding = false;
              
              if (fast_encoding)
              {
                pr ("%^s__ = redex + %i;", F.tree_gen->go(f));
              }
              else  // Slower encoding
              {
                if (_DATATYPEtycon(_TYCONty(_V2)->_1)->qualifiers & QUALview)
                {
                  gen_bottomup_traversals(F, f, _DATATYPEtycon(_TYCONty(_V2)->_1)->unit + _DATATYPEtycon(_TYCONty(_V2)->_1)->arg, _DATATYPEtycon(_TYCONty(_V2)->_1)->terms, ty);
                }
                else if (_DATATYPEtycon(_TYCONty(_V2)->_1)->arg == 0)  // all unit functors
                {
                  gen_bottomup_traversals(F, f, _DATATYPEtycon(_TYCONty(_V2)->_1)->unit, _DATATYPEtycon(_TYCONty(_V2)->_1)->terms, ty);
                }
                else if (_DATATYPEtycon(_TYCONty(_V2)->_1)->unit == 0)  // all argument functors
                {
                  gen_bottomup_traversals(F, f, _DATATYPEtycon(_TYCONty(_V2)->_1)->arg, _DATATYPEtycon(_TYCONty(_V2)->_1)->terms, ty);
                }
                else
                {
                  pr( "%^if (%s(redex)) {%+", (_DATATYPEtycon(_TYCONty(_V2)->_1)->unit > 1 ? "boxed" : ""));
                  gen_bottomup_traversals(F, f + _DATATYPEtycon(_TYCONty(_V2)->_1)->unit, _DATATYPEtycon(_TYCONty(_V2)->_1)->arg, _DATATYPEtycon(_TYCONty(_V2)->_1)->terms + _DATATYPEtycon(_TYCONty(_V2)->_1)->unit, ty);
                  pr( "%-%^} else {%+");
                  gen_bottomup_traversals(F, f, _DATATYPEtycon(_TYCONty(_V2)->_1)->unit, _DATATYPEtycon(_TYCONty(_V2)->_1)->terms, ty);
                  pr( "%-%^}");
                }
              }
              
#line 618 "../../prop-src/rwgen.pcc"
              } break;
            default: {
              L2:; } break;
          }
        } else { goto L2; }
        } break;
      default: { goto L2; } break;
    }
  } else { goto L2; }
}
#line 620 "../../prop-src/rwgen.pcc"
#line 620 "../../prop-src/rwgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a traversal routine for a set of terms in a datatype.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_bottomup_traversals
   ( FunctorMap& F, Functor f, int arity, Cons terms[], Ty ty)
{
  Bool is_boxed = terms[0]->ty != NOty; // are we dealing with boxed terms?
  //Id redex    = is_boxed ? redex_name(ty) : "(int)redex";
  //Id untagger = is_boxed ? "->tag__" : "";
  Exp redex = IDexp(
#line 635 "../../prop-src/rwgen.pcc"
#line 635 "../../prop-src/rwgen.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_nco_c_c_Q1
#line 635 "../../prop-src/rwgen.pcc"
#line 635 "../../prop-src/rwgen.pcc"
);

  if (arity == 1)
  {
    ////////////////////////////////////////////////////////////////////////
    //  (1 branch) No ifs or switches
    ////////////////////////////////////////////////////////////////////////
    gen_one_traversal( F, f, terms[0], ty);
  }
  else if (arity == 2)
  {
    ////////////////////////////////////////////////////////////////////////
    //  (2 branches) Generate an if
    ////////////////////////////////////////////////////////////////////////
    pr( "%^if (%e) {%+", untag_one(redex, terms[0]));
    gen_one_traversal(F, f + 1, terms[1], ty);
    pr( "%-%^} else {%+");
    gen_one_traversal(F, f, terms[0], ty);
    pr( "%-%^}");
  }
  else
  {
    ////////////////////////////////////////////////////////////////////////
    // (n-branches) Generate a switch
    ////////////////////////////////////////////////////////////////////////
    pr( "%^switch(%e) {%+", untag_one( redex, terms[0]));
    for ( int i = 0; i < arity; i++)
    {
      pr( i == arity - 1 ? "%^default: { %+" : "%^case %*: { %+",
          terms[i], false);
      gen_one_traversal(F, f+i, terms[i], ty);
      pr( "} break;%-");
    }
    pr("%-%^}");
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a traversal routine for one term in a datatype.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_one_traversal
    ( FunctorMap& F, Functor f, Cons term, Ty ty)
{
  if (is_array_constructor(term->name))
  {
    ////////////////////////////////////////////////////////////////////////
    // Generate array code
    ////////////////////////////////////////////////////////////////////////
    bug("RewritingCompiler::gen_one_traversal");
  }
  else
  {
    gen_component_traversal( F, f, term, ty);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code to traverse a component of a term.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_component_traversal
    ( FunctorMap& F, Functor f, Cons term, Ty ty)
{
  Ty  arg_ty = component_ty(ty, term);  // argument type of the term.
  int arity  = arity_of(arg_ty);        // arity of this type.
  Bool relevant[256];
  Bool is_record = false;

  ///////////////////////////////////////////////////////////////////////////
  // Generate code for the state temporary variables.
  ///////////////////////////////////////////////////////////////////////////
  { for (int i = 0; i < arity; i++) pr ("%^int s%i__;", i); }

  ///////////////////////////////////////////////////////////////////////////
  // Optimize out singleton.
  ///////////////////////////////////////////////////////////////////////////
  Bool is_singleton = true;
  //{ for (int i = 0; i < arity; i++)
  {
    for (int i = 0; i < F.G.arity(f); i++)
      if ( F.tree_gen->index_range(f,i) > 1)
        is_singleton = false;
  }

  ///////////////////////////////////////////////////////////////////////////
  // Call the constructor if it is applicative
  ///////////////////////////////////////////////////////////////////////////
  if ( F.is_applicative)
    pr( "%^redex = %S%+", term->name);
  if ( F.is_applicative && term->ty != NOty)
    pr( "(\n");

  ///////////////////////////////////////////////////////////////////////////
  // Generate code to call the labeler on subcomponents.
  ///////////////////////////////////////////////////////////////////////////

  
#line 736 "../../prop-src/rwgen.pcc"
#line 751 "../../prop-src/rwgen.pcc"
{
  if (arg_ty) {
    switch (arg_ty->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(arg_ty)->_1)) {
          switch (_TYCONty(arg_ty)->_1->tag__) {
            case a_TyCon::tag_RECORDtycon: {
#line 744 "../../prop-src/rwgen.pcc"
              
              gen_record_component_traversal(F,term,arity,relevant,_RECORDtycon(_TYCONty(arg_ty)->_1)->_1,_TYCONty(arg_ty)->_2);
              is_record = true;
              
#line 747 "../../prop-src/rwgen.pcc"
              } break;
            default: {
              L3:; 
#line 749 "../../prop-src/rwgen.pcc"
              
              gen_single_component_traversal(F,term,arg_ty);
              
#line 751 "../../prop-src/rwgen.pcc"
              } break;
          }
        } else {
          switch ((int)_TYCONty(arg_ty)->_1) {
            case ((int)TUPLEtycon): {
#line 740 "../../prop-src/rwgen.pcc"
              
              gen_tuple_component_traversal(F,term,arity,_TYCONty(arg_ty)->_2);
              
#line 742 "../../prop-src/rwgen.pcc"
              } break;
            default: { goto L3; } break;
          }
        }
        } break;
      default: { goto L3; } break;
    }
  } else {}
}
#line 752 "../../prop-src/rwgen.pcc"
#line 752 "../../prop-src/rwgen.pcc"


  if (F.is_applicative && term->ty != NOty)
    pr("%^)");
  if (F.is_applicative)
    pr(";\n%-");

  ///////////////////////////////////////////////////////////////////////////
  // Generate code to compute the new state
  ///////////////////////////////////////////////////////////////////////////
  if (F.tree_gen->arity_of(f) == 0 && arg_ty != NOty)
    pr("%?s__ = 0;");
  else if (is_singleton)
    pr("%?s__ = %i;", F.tree_gen->go(f));
  else // theta code
  {
    pr ("%^s__ = %s_theta_%i", F.class_name, f);
    for (int i = 0, j = 0; i < arity; i++)
    {
      if (is_record && ! relevant[i])
        continue;
      if (F.tree_gen->index_range(f,i) == 1)
        pr("[0]");
      else if (F.use_compression)
        pr( "[%s_check[%i + s%i__] == %i ? %s_next[%i + s%i__] : 0]",
            F.class_name, F.tree_gen->compressed_offset(f,j), j,
            F.tree_gen->compressed_index(f,j),
            F.class_name, F.tree_gen->compressed_offset(f,j), j
          );
      else
         pr("[%s_mu_%i_%i[s%i__]]", F.class_name, f, j, j);
      j++;
    }
    pr("; ");
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate traversal code on one single component of a datatype
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_single_component_traversal
  (FunctorMap& F, Cons term, Ty arg_ty)
{
  Exp e = select(IDexp("redex"),term);
  if (is_array_constructor(term->name))
  {
    if (F.is_known_type(arg_ty)) // generate traversal code for vectors
    {
      if (F.is_applicative)
        bug("RewritingCompiler::gen_single_component_traversal");
      else
        bug("RewritingCompiler::gen_single_component_traversal");
    }
    else                       // type is unknown.
    {
      if (F.is_applicative)
        bug("RewritingCompiler::gen_single_component_traversal");
      else
        pr("%^s0__ = 0; // %T", arg_ty);
    }
  }
  else
  {
    if (F.is_known_type(arg_ty))
      pr("%^labeler(%e, s0__, r__)%s\n", e, (F.is_applicative ? "" : ";"));
    else if (F.is_applicative)
      pr("%^(s0__ = 0, %e) // %T\n", e, arg_ty);
    else
      pr("%^s0__ = 0; // %T\n", arg_ty);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate traversal code on the tuple component of a datatype
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_tuple_component_traversal
    ( FunctorMap& F, Cons term, int arity, Tys tys)
{
  Tys ts; int i;
  Exp e = select(IDexp("redex"),term);
  for (i = 0, ts = tys; i < arity && ts; i++, ts = ts->_2)
  {
    Ty ty   = ts->_1;
    Id mark = F.is_applicative ? (i != arity - 1 ? "," : "") : ";";
    Exp  e_i  = DOTexp(e,index_of(i+1));

    if (F.is_known_type(ty))
      pr( "%^labeler(%e, s%i__, r__)%s\n", e_i, i, mark);
    else if (F.is_applicative)
      pr( "%^(s%i__ = 0, %e)%s // %T\n", i, e_i, mark, ty);
    else
      pr( "%^s%i__ = 0; // %T\n", i, ty);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate traversal code on the record component of a datatype
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_record_component_traversal
   (FunctorMap& F, Cons term, int arity, Bool relevant[], Ids labs, Tys tys)
{
  Tys ts; Ids ids; int i;
  Exp e = select(IDexp("redex"),term);
  for (ids = labs, ts = tys, i = 0; ids && ts; ids=ids->_2, ts=ts->_2, i++)
  {
    Ty   ty   = ts->_1;
    Exp  e_i  = DOTexp(e,ids->_1);
    Id   mark = F.is_applicative ? (i != arity - 1 ? "," : "") : ";";

    if (F.is_known_type(ty))
    {
      relevant[i] = true;
      pr( "%^labeler(%e,s%i__,r__)%s\n", e_i, i, mark);
    }
    else if (F.is_applicative)
    {
      relevant[i] = false;
      pr( "%^(s%i__ = 0, %e)%s // %T\n",i, e_i, mark, ty);
    }
    else
    {
      relevant[i] = false;
      pr( "%^s%i__ = 0; // %T\n",i,ty);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the action code for a datatype
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_action( FunctorMap& F, Ty ty)
{
  HashTable::Entry * e = F.rule_map.lookup(ty);
  if (e == 0) return; // no rules, no action

  ////////////////////////////////////////////////////////////////////////////
  // The set of rules on type 'ty.'
  ////////////////////////////////////////////////////////////////////////////
  MatchRules rules = MatchRules(F.rule_map.value(e));

  ////////////////////////////////////////////////////////////////////////////
  // Check whether this set of rules have guards and costs and cost exprs.
  ////////////////////////////////////////////////////////////////////////////
  Bool has_conditional_rules = false;
  Bool has_cost              = false;
  Bool has_cost_exp          = false;
  {
    for_each(MatchRule, r, rules)
    {
      
#line 913 "../../prop-src/rwgen.pcc"
#line 923 "../../prop-src/rwgen.pcc"
{
#line 915 "../../prop-src/rwgen.pcc"
  
  if (r->_3 != NOexp || (r->option & MatchRuleInfo::FAILREWRITE))
    has_conditional_rules = true;
  
#line 918 "../../prop-src/rwgen.pcc"
#line 921 "../../prop-src/rwgen.pcc"
  {
    Cost _V3 = r->_4;
    if (_V3) {
      if (_V3->tag__) {
        
#line 920 "../../prop-src/rwgen.pcc"
       has_cost = true; 
#line 920 "../../prop-src/rwgen.pcc"
      } else {
        
#line 921 "../../prop-src/rwgen.pcc"
       has_cost_exp = true; 
#line 921 "../../prop-src/rwgen.pcc"
      }
    } else {}
  }
#line 922 "../../prop-src/rwgen.pcc"
#line 922 "../../prop-src/rwgen.pcc"
  
  
#line 923 "../../prop-src/rwgen.pcc"
}
#line 924 "../../prop-src/rwgen.pcc"
#line 924 "../../prop-src/rwgen.pcc"

    }
  }

  ////////////////////////////////////////////////////////////////////////////
  //  Generate a rule variable if we have to deal with cost functions
  //  and/or annotate the tree for reducers.
  ////////////////////////////////////////////////////////////////////////////
  // if (has_cost_exp || F.gen_reducers) pr ("%^Rule r__ = -1;");

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Split into subcases
  //
  ////////////////////////////////////////////////////////////////////////////
  if (F.gen_reducers)
  {
    if (F.has_cost_exp)
      gen_cost_labeler_action(F,ty,rules,has_conditional_rules);
    else
      if (has_conditional_rules)
        gen_costless_guarded_labeler_action(F,rules);
      else
        gen_costless_guardless_labeler_action(F,rules);
  }
  else
  {
    if (F.has_cost_exp)
      gen_cost_rewriter_action(F,rules);
    else
      if (has_conditional_rules)
        gen_costless_guarded_rewriter_action(F,rules);
      else
        gen_costless_guardless_rewriter_action(F,rules);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate the action for a cost minimizing labeler.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_cost_labeler_action
   ( FunctorMap& F, Ty ty, MatchRules rules, Bool has_guard)
{
   bug("RewritingCompiler::gen_cost_labeler_action");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate the action for a simple labeler with guards.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_costless_guarded_labeler_action
   (FunctorMap& F, MatchRules rules)
{
  ////////////////////////////////////////////////////////////////////////////
  // Generate code to perform the mapping from state to the accept rule.
  ////////////////////////////////////////////////////////////////////////////
  pr(
      "%^const %s* o__ = %s_accept_vector + %s_accept_base[s__];"
      "%-%^accept__:%+"
      "%^switch (*o__) {%+",
      F.tree_gen->get_rule_type(), F.class_name, F.class_name
    );

  for_each (MatchRule, r, rules)
  {
    
#line 994 "../../prop-src/rwgen.pcc"
#line 1004 "../../prop-src/rwgen.pcc"
{
#line 997 "../../prop-src/rwgen.pcc"
  
  if (r->_3 != NOexp)
    {
      pr( "%^case %i: if (! (%e)) { ++o__; goto accept__; }",
          r->rule_number, r->_3
        );
    }
  
#line 1004 "../../prop-src/rwgen.pcc"
}
#line 1005 "../../prop-src/rwgen.pcc"
#line 1005 "../../prop-src/rwgen.pcc"

  }
  pr( "%-%^}" "%^%srule__ = *o__;", F.tree_gen->get_rule_type());
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate the action for a simple labeler without guards.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_costless_guardless_labeler_action
   (FunctorMap& F, MatchRules rules)
{
  ////////////////////////////////////////////////////////////////////////////
  // Generate code to perform the mapping from state to the first accept rule.
  ////////////////////////////////////////////////////////////////////////////
  pr( "%^%srule__ = %s_accept1[s__];",
      F.tree_gen->get_rule_type(), F.class_name
    );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate the action for a cost minimizing rewriter.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_cost_rewriter_action
   (FunctorMap& F, MatchRules rules)
{
  ////////////////////////////////////////////////////////////////////////////
  // Generate code to perform the mapping from state to set of accept rule.
  ////////////////////////////////////////////////////////////////////////////
  pr( "%^const %s* o__ = %s_accept_vector + %s_accept_base[s__];"
      "%^TreeTables::Rule rule__ = -1;"
      "%^TreeTables::Cost min_cost__  = TreeTables::infinite_cost;"
      "%^TreeTables::Cost temp_cost__;",
      F.tree_gen->get_rule_type(), F.class_name, F.class_name
    );

  ////////////////////////////////////////////////////////////////////////////
  //
  // Generate the cost minimalization code for each accept rule.
  //
  ////////////////////////////////////////////////////////////////////////////
  pr(
      "%^for ( ;*o__ >= 0; o__++) {%+"
      "%^switch (*o__) {%+"
    );

  {
    for_each (MatchRule, r, rules)
    {
      
#line 1059 "../../prop-src/rwgen.pcc"
#line 1086 "../../prop-src/rwgen.pcc"
{
#line 1062 "../../prop-src/rwgen.pcc"
  
  pr("%^case %i: %+",r->rule_number);
  if (r->_3 != NOexp) pr ("%^if (%e)%+", r->_3);
  
#line 1065 "../../prop-src/rwgen.pcc"
#line 1082 "../../prop-src/rwgen.pcc"
  {
    Cost _V4 = r->_4;
    if (_V4) {
      if (_V4->tag__) {
        
#line 1072 "../../prop-src/rwgen.pcc"
        
        pr( "%^if (min_cost__ > %i) { min_cost__ = %i; rule__ = %i; }",
            _INTcost(_V4)->INTcost, _INTcost(_V4)->INTcost, r->rule_number
          );
        
#line 1076 "../../prop-src/rwgen.pcc"
      } else {
        
#line 1078 "../../prop-src/rwgen.pcc"
        
        pr( "%^if (min_cost__ > (temp_cost__ = %e)) { min_cost__ = temp_cost__; rule__ = %i; }",
            _EXPcost(_V4)->_1, r->rule_number
          );
        
#line 1082 "../../prop-src/rwgen.pcc"
      }
    } else {
#line 1068 "../../prop-src/rwgen.pcc"
      
      pr( "%^{ rule__ = %i; goto found__; }", r->rule_number);
      
#line 1070 "../../prop-src/rwgen.pcc"
    }
  }
#line 1083 "../../prop-src/rwgen.pcc"
#line 1083 "../../prop-src/rwgen.pcc"
  
  if (r->_3 != NOexp) pr ("%-");
  pr ("%- break; ");
  
#line 1086 "../../prop-src/rwgen.pcc"
}
#line 1087 "../../prop-src/rwgen.pcc"
#line 1087 "../../prop-src/rwgen.pcc"

    }
  }

  pr( "%-%^}"
      "%-%^}"
      "%^found__: ;\n\n"
    );

  ////////////////////////////////////////////////////////////////////////////
  //
  // Now generate the action code
  //
  ////////////////////////////////////////////////////////////////////////////

  pr( "%^switch (rule__) {%+");

  {
    for_each (MatchRule, r, rules)
    {
      
#line 1107 "../../prop-src/rwgen.pcc"
#line 1113 "../../prop-src/rwgen.pcc"
{
#line 1110 "../../prop-src/rwgen.pcc"
  
  MarkCurrentRule mark( current_rule,r);
  	      pr("%^case %i: %+{%&}%- break;", r->rule_number, r->_5);
  	    
#line 1113 "../../prop-src/rwgen.pcc"
}
#line 1114 "../../prop-src/rwgen.pcc"
#line 1114 "../../prop-src/rwgen.pcc"

    }
  }
  pr("%-%^}\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate the action for a simple rewriter.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_costless_guarded_rewriter_action
   (FunctorMap& F, MatchRules rules)
{
  ////////////////////////////////////////////////////////////////////////////
  // Generate code to perform the mapping from state to accept rule.
  ////////////////////////////////////////////////////////////////////////////
  pr( "%^const %s* o__ = %s_accept_vector + %s_accept_base[s__];"
      "%-%^accept__:%+"
      "%^switch (*o__) {%+",
      F.tree_gen->get_rule_type(), F.class_name, F.class_name
    );

  for_each (MatchRule, r, rules)
  {
    
#line 1140 "../../prop-src/rwgen.pcc"
#line 1152 "../../prop-src/rwgen.pcc"
{
#line 1143 "../../prop-src/rwgen.pcc"
  
  pr( "%^case %i: ", r->rule_number);
  if (r->_3 != NOexp)
    pr( "if (%e)%^", r->_3);
  MarkCurrentRule mark(current_rule,r);
  pr( "%+{%&}%-", r->_5);
  if (r->_3 != NOexp)
    pr( "%^else { ++o__; goto accept__; }");
  pr( " break;");
  
#line 1152 "../../prop-src/rwgen.pcc"
}
#line 1153 "../../prop-src/rwgen.pcc"
#line 1153 "../../prop-src/rwgen.pcc"

  }
  pr("%-%^}");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate the action for a simple rewriter.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_costless_guardless_rewriter_action
   (FunctorMap& F, MatchRules rules)
{
  ////////////////////////////////////////////////////////////////////////////
  // Generate code with cases corresponding to the accept state directly.
  ////////////////////////////////////////////////////////////////////////////
  pr("%^switch (s__) {%+");
  for_each (MatchRule, r, rules)
  {
    
#line 1173 "../../prop-src/rwgen.pcc"
#line 1188 "../../prop-src/rwgen.pcc"
{
#line 1176 "../../prop-src/rwgen.pcc"
  
  Bool used = false;
  for (int s = F.tree_gen->number_of_states() - 1; s >= 0; s--)
  {
    if (F.tree_gen->accept1_rule(s) == r->rule_number)
    {
      pr( "%^case %i: ", s); used = true;
    }
  }
  MarkCurrentRule mark( current_rule,r);
  if (used)
    pr( "%+{%&}%- break;", r->_5);
  
#line 1188 "../../prop-src/rwgen.pcc"
}
#line 1189 "../../prop-src/rwgen.pcc"
#line 1189 "../../prop-src/rwgen.pcc"

  }
  pr("%-%^}");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the reducers.  Reducers take an rewrite
//  tree annotated with the accept rule(s) and traverse it perform
//  the reduction actions.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::generate_reducers( FunctorMap& F)
{
  ///////////////////////////////////////////////////////////////////////////
  // Generate reducers for all datatypes
  ///////////////////////////////////////////////////////////////////////////
  foreach_entry ( e, F.type_map)
  {
    Ty ty = Ty( F.type_map.key( e));
    debug_msg( "[Rewrite class %s: generating reducer for datatype %T\n",
               F.class_name, ty);
    gen_datatype_reducer( F, ty);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the datatype reducer.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_datatype_reducer( FunctorMap& F, Ty ty)
{
  HashTable::Entry * e = F.rule_map.lookup( ty);
  if (e == 0) return; // we have no rules for this type. Do nothing

  MatchRules rules  = MatchRules(F.rule_map.value(e)); // The set of rules
  Functor    f      = F.type_map[ty];         // The starting functor encoding
  Protocol   proto  = Protocol(F.protocols[ty]); // The protocol for this type

  ///////////////////////////////////////////////////////////////////////////
  // The synthesized attribute type.
  ///////////////////////////////////////////////////////////////////////////
  Ty         syn_ty = proto->syn == NOty ? void_ty : proto->syn;
  Ty         inh_ty = proto->inh;

  ///////////////////////////////////////////////////////////////////////////
  // Generate the protocol of this reducer (4 cases to worry about)
  ///////////////////////////////////////////////////////////////////////////
  if (syn_ty == void_ty && inh_ty == NOty)
    pr( "%^void %s::reduce(%t,int lhs)", F.class_name, ty, "redex");
  if (syn_ty == void_ty && inh_ty != NOty)
    pr( "%^void %s::reduce(%t, %t,int lhs)", F.class_name, ty, "redex",
        inh_ty, "inh__");
  if (syn_ty != void_ty && inh_ty == NOty)
    pr( "%^%t %s::reduce(%t,int lhs)", syn_ty, "", F.class_name, ty, "redex");
  if (syn_ty != void_ty && inh_ty != NOty)
    pr( "%^%t %s::reduce(%t,%t,int lhs)", syn_ty, "", F.class_name, ty, "redex",
        inh_ty, "inh__");

  pr ("%^{%+");

  ///////////////////////////////////////////////////////////////////////////
  // Generate a temporary called "__" for the synthesized attribute.
  // Also assigns redex to it if it is the same type.
  ///////////////////////////////////////////////////////////////////////////
  if (syn_ty != void_ty)
    pr( "%^%t%s;", syn_ty, "__", ty_equal(syn_ty,ty) ? " = redex" : "");

  ///////////////////////////////////////////////////////////////////////////
  // Generate the code that computes the accept rule
  ///////////////////////////////////////////////////////////////////////////
  if (F.dynamic_search)
  {
    pr( "%^const %s_StateRec * _state_rec = (const %s_StateRec *)(%s->get_state_rec());"
        "%^int r__;"
        "%^switch (lhs) {%+",
        F.class_name, F.class_name, redex_name(ty)
      );
    foreach_entry (p,F.var_map)
    {
      Id  lhs        = Id(p->k);
      int nonterm_no = int(p->v);
      pr( "%^case %i: r__ = %s_%S_accept[_state_rec->rule._%S]; break;",
          nonterm_no, F.class_name, lhs, lhs);
    }
    pr( "%^default: r__ = -1; break;%-"
        "%^}");
  }
  else
  {
    
#line 1282 "../../prop-src/rwgen.pcc"
#line 1333 "../../prop-src/rwgen.pcc"
{
  Ty _V5 = deref_all(ty);
  if (_V5) {
    switch (_V5->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V5)->_1)) {
          switch (_TYCONty(_V5)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 1285 "../../prop-src/rwgen.pcc"
              
              Id var        = redex_name(ty);
              Id table_name = 0;
              
              // generate mapping from unit tag to accept rule if necessary.
              if (_DATATYPEtycon(_TYCONty(_V5)->_1)->unit > 1)
              {
                table_name = vars.new_label();
                pr( "%^static const %s%s[] = { ",
                    F.tree_gen->get_rule_type(), table_name);
                for (int i = 0; i < _DATATYPEtycon(_TYCONty(_V5)->_1)->unit; i++)
                {
                  pr ("%i", F.tree_gen->accept1_rule(F.tree_gen->go(f+i)));
                  if (i != _DATATYPEtycon(_TYCONty(_V5)->_1)->unit - 1)
                    pr(", ");
                }
                pr( " };");
              }
              
              // Generate code that computes the accept rule(try to optimize a bit).
              if (_DATATYPEtycon(_TYCONty(_V5)->_1)->unit == 0)       // all boxed
              {  // pr ("%^int r__ = %s->get_rewrite_rule();",var);
                pr ("%^int r__ = ");
                gen_get_rewrite_rule(ty,var);
                pr (";");
              }
              else if (_DATATYPEtycon(_TYCONty(_V5)->_1)->arg == 0)   // all unboxed
              {
                pr ("%^int r__ = %s[redex]",table_name);
              }
              else if (_DATATYPEtycon(_TYCONty(_V5)->_1)->unit == 1)  // one is unboxed
              {
                // pr ("%^int r__ = redex ? %s->get_rewrite_rule() : %i;",var,
                //     F.tree_gen->accept1_rule(F.tree_gen->go(f)));
                pr ("%^int r__ = redex ? ");
                gen_get_rewrite_rule(ty,var);
                pr (" : %i;",F.tree_gen->accept1_rule(F.tree_gen->go(f)));
              }
              else
              {
                // pr ("%^int r__ = boxed(redex) ? %s->get_rewrite_rule() : %s[(int)redex];",
                //     var, table_name);
                pr ("%^int r__ = boxed(redex) ? ");
                gen_get_rewrite_rule(ty,var);
                pr (" : %s[(int)redex];", table_name);
              }
              
#line 1331 "../../prop-src/rwgen.pcc"
              } break;
            default: {
              L4:; 
#line 1333 "../../prop-src/rwgen.pcc"
             bug("RewritingCompiler::gen_datatype_labeler"); 
#line 1333 "../../prop-src/rwgen.pcc"
              } break;
          }
        } else { goto L4; }
        } break;
      default: { goto L4; } break;
    }
  } else { goto L4; }
}
#line 1334 "../../prop-src/rwgen.pcc"
#line 1334 "../../prop-src/rwgen.pcc"

  }

  ///////////////////////////////////////////////////////////////////////////
  // Generate the switch statement, one for each rule
  ///////////////////////////////////////////////////////////////////////////
  pr ("%^switch (r__) {%+");
  for_each(MatchRule, r, rules)
  {
    
#line 1343 "../../prop-src/rwgen.pcc"
#line 1350 "../../prop-src/rwgen.pcc"
{
#line 1345 "../../prop-src/rwgen.pcc"
  
  pr( "%^case %i: {%+ // %p\n", r->rule_number, r->_2);
  gen_pattern_traversal( F, r->_1, r->_2, 0);
  MarkCurrentRule mark( current_rule,r);
  pr( "%^%&} break;%-", r->_5);
  
#line 1350 "../../prop-src/rwgen.pcc"
}
#line 1351 "../../prop-src/rwgen.pcc"
#line 1351 "../../prop-src/rwgen.pcc"

  }
  pr ("%-%^}");

  ///////////////////////////////////////////////////////////////////////////
  // Return the value of the synthesized attribute (if any)
  ///////////////////////////////////////////////////////////////////////////
  if (syn_ty != void_ty) pr("%^return __; ");

  ///////////////////////////////////////////////////////////////////////////
  // End of routine
  ///////////////////////////////////////////////////////////////////////////
  pr ("%-%^}\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a reducer recursive call for one pattern.
//
///////////////////////////////////////////////////////////////////////////////

int RewritingCompiler::gen_pattern_traversal( FunctorMap& F, Id lhs, Pat pat, int i)
{
  
#line 1374 "../../prop-src/rwgen.pcc"
#line 1421 "../../prop-src/rwgen.pcc"
{
  if (pat) {
    switch (pat->tag__) {
      case a_Pat::tag_APPpat: {
#line 1381 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_APPpat(pat)->_2,i); 
#line 1381 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_TYPEDpat: {
#line 1378 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_TYPEDpat(pat)->_1,i); 
#line 1378 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_ASpat: {
#line 1377 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_ASpat(pat)->_2,i); 
#line 1377 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_ARRAYpat: {
#line 1382 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_ARRAYpat(pat)->_1,i); 
#line 1382 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_TUPLEpat: {
#line 1383 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_TUPLEpat(pat)->TUPLEpat,i); 
#line 1383 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_EXTUPLEpat: {
#line 1384 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_EXTUPLEpat(pat)->EXTUPLEpat,i); 
#line 1384 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_RECORDpat: {
#line 1385 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_RECORDpat(pat)->_1,i); 
#line 1385 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_LISTpat: {
#line 1387 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_LISTpat(pat)->head,i);
        i = gen_pattern_traversal(F,lhs,_LISTpat(pat)->tail,i);
        
#line 1389 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_VECTORpat: {
#line 1391 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_VECTORpat(pat)->elements,i);
        i = gen_pattern_traversal(F,lhs,_VECTORpat(pat)->array,i);
        i = gen_pattern_traversal(F,lhs,_VECTORpat(pat)->len,i);
        
#line 1394 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_GUARDpat: {
#line 1380 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_GUARDpat(pat)->_1,i); 
#line 1380 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 1379 "../../prop-src/rwgen.pcc"
       i = gen_pattern_traversal(F,lhs,_MARKEDpat(pat)->_2,i); 
#line 1379 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_WILDpat:
      case a_Pat::tag_IDpat: {
#line 1396 "../../prop-src/rwgen.pcc"
        
        if (F.is_rewritable_type(pat->ty))
        {
          Protocol proto = Protocol(F.protocols[pat->ty]);
          Ty inh_ty = proto->inh, syn_ty = proto->syn;
          Id inh_exp = inh_ty != NOty ? ",inh__" : "";
          int nonterm_no = (lhs && F.var_map.contains(lhs))
               ? int(F.var_map[lhs]) : 0;
          Id nonterm = lhs ? lhs : "(none)";
          if (syn_ty != NOty)
            pr(
                "%^%t _%i__ = reduce(%e%s,%i); // %s",
                syn_ty,"",i,pat->selector,inh_exp,nonterm_no,nonterm
              );
          else
            pr(
                "%^reduce(%e%s,%i); // %s",
                pat->selector,inh_exp,nonterm_no,nonterm
              );
          i++;
        }
        
#line 1417 "../../prop-src/rwgen.pcc"
        } break;
      case a_Pat::tag_CONSpat:
      case a_Pat::tag_LITERALpat:
      case a_Pat::tag_CONTEXTpat:
      case a_Pat::tag_LEXEMEpat: {
        L5:; } break;
      default: {
#line 1419 "../../prop-src/rwgen.pcc"
        
        bug("RewritingCompiler::gen_pattern_traversal on %p\n",pat);
        
#line 1421 "../../prop-src/rwgen.pcc"
        } break;
    }
  } else { goto L5; }
}
#line 1422 "../../prop-src/rwgen.pcc"
#line 1422 "../../prop-src/rwgen.pcc"

  return i;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a reducer recursive call for one pattern list.
//
///////////////////////////////////////////////////////////////////////////////

int RewritingCompiler::gen_pattern_traversal( FunctorMap& F, Id lhs, Pats pats, int i)
{
  for_each (Pat, p, pats)
    i = gen_pattern_traversal( F, lhs, p, i);
  return i;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a reducer recursive call for one labeled pattern list.
//
///////////////////////////////////////////////////////////////////////////////

int RewritingCompiler::gen_pattern_traversal( FunctorMap& F, Id lhs, LabPats ps, int i)
{
  for_each (LabPat, p, ps)
    i = gen_pattern_traversal( F, lhs, p.pat, i);
  return i;
}
#line 1451 "../../prop-src/rwgen.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 101
Number of ifs generated      = 14
Number of switches generated = 10
Number of labels             = 5
Number of gotos              = 13
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
