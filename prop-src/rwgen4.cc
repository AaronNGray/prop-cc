///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\rwgen4.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_STRCMP_USED
#include <propdefs.h>
#line 1 "../../prop-src/rwgen4.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the tree rewriting/tree parsing compiler.
//  This is used to implement the rewrite class/rewrite constructs of Prop.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <strstream>
#include "funmap.h"
#include "ir.h"
#include "ast.h"
#include "matchcom.h"
#include "type.h"
#include "hashtab.h"
#include "list.h"
#include "rwgen.h"
#include "trs.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a set of pattern matching rules for a labeler
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_auxiliary_rules
   (FunctorMap& F, Ty ty, MatchRuleInfo::RewritingMode mode)
{
  if (F.rule_maps[mode]->contains(ty))
  {
    MatchRules rules = rev(MatchRules((*F.rule_maps[mode])[ty]));
    debug_msg("%Lgenerating auxiliary rules for rewrite class %s type %T:\n",
        F.class_name, ty);
    for_each(MatchRule,r,rules) debug_msg("%!\t%r\n",r->loc(),r);
    gen_match_stmt(
#line 36 "../../prop-src/rwgen4.pcc"
#line 36 "../../prop-src/rwgen4.pcc"
list_1_(MATCHexp(IDexp(redex_name(ty)),0))
#line 36 "../../prop-src/rwgen4.pcc"
#line 36 "../../prop-src/rwgen4.pcc"
,rules,MATCHnocheck);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the before rules of a labeler
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_before_rules( FunctorMap& F, Ty ty)
{
  gen_auxiliary_rules( F, ty, MatchRuleInfo::BEFORE);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the preorder rules of a labeler
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_preorder_rules( FunctorMap& F, Ty ty)
{
  gen_auxiliary_rules( F, ty, MatchRuleInfo::PREORDER);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the postorder rules of a labeler
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_postorder_rules( FunctorMap& F, Ty ty)
{
  gen_auxiliary_rules( F, ty, MatchRuleInfo::POSTORDER);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the topdown rules of a labeler
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_topdown_rules( FunctorMap& F, Ty ty)
{
  gen_auxiliary_rules( F, ty, MatchRuleInfo::TOPDOWN);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a tracing macro
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_trace_macro( Id name, FunctorMap& F)
{
  pr(
    "%n%/"
    "%n//"
    "%n// This macro can be redefined by the user for debugging"
    "%n//"
    "%n%/"
    "%n#ifndef DEBUG_%S"
    "%n#define DEBUG_%S(repl,redex,file,line,rule) repl"
    "%n#else"
    "%nstatic const char * %S_file_name = \"%s\";"
    "%n#endif\n\n",
    name, name, name, file
    );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to find out whether the replacement term is simple.
//  A replacement term is simple if it is a projection/selection from
//  the redex, or the redex itself.
//
///////////////////////////////////////////////////////////////////////////////

Bool is_simple_replacement( Exp exp)
{
  
#line 117 "../../prop-src/rwgen4.pcc"
#line 122 "../../prop-src/rwgen4.pcc"
{
  for (;;) {
    if (exp) {
      switch (exp->tag__) {
        case a_Exp::tag_IDexp: {
          if (_equal_string(_IDexp(exp)->IDexp,"redex")) {
#line 118 "../../prop-src/rwgen4.pcc"
         return true; 
#line 118 "../../prop-src/rwgen4.pcc"
}
          else {
          L2:; 
#line 122 "../../prop-src/rwgen4.pcc"
         return false; 
#line 122 "../../prop-src/rwgen4.pcc"
}
          } break;
        case a_Exp::tag_DOTexp: {
          if (_DOTexp(exp)->_1) {
            switch (_DOTexp(exp)->_1->tag__) {
              case a_Exp::tag_SELECTORexp: {
#line 119 "../../prop-src/rwgen4.pcc"
               exp = _SELECTORexp(_DOTexp(exp)->_1)->_1; 
#line 119 "../../prop-src/rwgen4.pcc"
                } break;
              default: { goto L2; } break;
            }
          } else { goto L2; }
          } break;
        case a_Exp::tag_SELECTORexp: {
#line 120 "../../prop-src/rwgen4.pcc"
         exp = _SELECTORexp(exp)->_1; 
#line 120 "../../prop-src/rwgen4.pcc"
          } break;
        case a_Exp::tag_MARKEDexp: {
#line 121 "../../prop-src/rwgen4.pcc"
         exp = _MARKEDexp(exp)->_2; 
#line 121 "../../prop-src/rwgen4.pcc"
          } break;
        default: { goto L2; } break;
      }
    } else { goto L2; }
  }
}
#line 123 "../../prop-src/rwgen4.pcc"
#line 123 "../../prop-src/rwgen4.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a replacement statement.  We'll optimize all
//  bottomup and after rewriting rules.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_replacement
   (Exp exp, MatchRuleInfo::RewritingMode mode)
{
  Bool optimized =
	trs && trs->gen_replacement(*this,current_rule->rule_number,exp);
  pr(
       "%^{ redex = DEBUG_%S(%e,redex,%S_file_name,%i,%s);",
       Fmap->class_name, (optimized ? IDexp("repl__") : exp),
       Fmap->class_name, current_rule_line(), current_rule_text()
    );
  pr ("%^  r__ = 1; goto replacement__; }");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a failrewrite statement.
//
///////////////////////////////////////////////////////////////////////////////#

void RewritingCompiler::gen_failrewrite( MatchRuleInfo::RewritingMode)
{
  pr("%^{ ++o__; goto accept__; }");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a cut/replacement statement
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_cutreplacement
   (Exp exp, MatchRuleInfo::RewritingMode mode)
{
  if (Fmap == 0)
  {
    error("%Lcutrewrite is not used within a rewrite class: cutrewrite %e\n",
        exp);
    return;
  }

  if (Fmap->is_applicative)
  {
    if (exp == NOexp)
      pr("%^{ s__ = 0; return redex; }");
    else
      pr("%^{ s__ = 0; return DEBUG_%S(%e,redex,%S_file_name,%i,%s); }",
    Fmap->class_name, exp, Fmap->class_name,
    current_rule_line(), current_rule_text());
  }
  else
  {
    if (exp == NOexp)
      pr("%^{ s__ = 0; return; }");
    else
      pr("%^{ s__ = 0; redex = DEBUG_%S(%e,redex);"
    " return; }",
    Fmap->class_name, exp, Fmap->class_name,
    current_rule_line(), current_rule_text());
  }
}
#line 193 "../../prop-src/rwgen4.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 71
Number of ifs generated      = 3
Number of switches generated = 2
Number of labels             = 1
Number of gotos              = 4
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
