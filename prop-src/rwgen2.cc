///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\rwgen2.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_n_2co_c_c_Q2("() {}\n");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_n_2co_c_c_Q1("\npublic:\n  inline ");
#line 1 "../../prop-src/rwgen2.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the 'rewrite (x) { ... }' construct.
//  We'll transform this construct into the equivalent 'rewrite class ...'
//  and 'rewrite id { ... };' statements.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "ir.h"
#include "ast.h"
#include "type.h"
#include "rwgen.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////////////
//
//   Method for compiling a 'rewrite (x) { ... }' statement.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_rewriting
   ( Protocols        protocols,
     Exp              exp,
     Exp              dest,
     RewriteIndexings Is,
     MatchRules       rules,
     TyQual           qualifiers
   )
{
  MEM::use_global_pools();
  Id rewriter_name = Quark(options.mangled_file_prefix,vars.new_label());
  Ty exp_ty        = NOty;
  Ty ret_ty        = NOty;
  TyQual qual =
      (qualifiers & ~QUALapplicative) |
      (dest == NOexp ? QUALnone : QUALapplicative);

  // Get the return and argument types
  
#line 41 "../../prop-src/rwgen2.pcc"
#line 45 "../../prop-src/rwgen2.pcc"
{
  if (protocols) {
    if (dest) {
#line 44 "../../prop-src/rwgen2.pcc"
     exp_ty = ret_ty = protocols->_1->ty; 
#line 44 "../../prop-src/rwgen2.pcc"
    } else {
#line 43 "../../prop-src/rwgen2.pcc"
     exp_ty = protocols->_1->ty; ret_ty = void_ty; 
#line 43 "../../prop-src/rwgen2.pcc"
    }
  } else {
#line 45 "../../prop-src/rwgen2.pcc"
   error("%Lempty type list in rewrite (...) ..."); 
#line 45 "../../prop-src/rwgen2.pcc"
  }
}
#line 46 "../../prop-src/rwgen2.pcc"
#line 46 "../../prop-src/rwgen2.pcc"


  // If it is destructive, use call by reference
  if ( !(qual & QUALapplicative))
    exp_ty = mkrefty(exp_ty);

  // Print the interface to the auxiliary function
  pr( "%+%^extern %t %s_rewrite(%t);", ret_ty, "", rewriter_name, exp_ty, "");

  // Generate the rewriting call
  
#line 56 "../../prop-src/rwgen2.pcc"
#line 59 "../../prop-src/rwgen2.pcc"
{
  if (dest) {
#line 59 "../../prop-src/rwgen2.pcc"
   pr( "%^%e = %s_rewrite(%e);", dest, rewriter_name, exp); 
#line 59 "../../prop-src/rwgen2.pcc"
  } else {
#line 58 "../../prop-src/rwgen2.pcc"
   pr( "%^%s_rewrite(%e);", rewriter_name, exp); 
#line 58 "../../prop-src/rwgen2.pcc"
  }
}
#line 60 "../../prop-src/rwgen2.pcc"
#line 60 "../../prop-src/rwgen2.pcc"


  pr( "%-");

  // Add to the list of outstanding rewriting classes
  Decl body = OPAQUEdecl(
      
#line 66 "../../prop-src/rwgen2.pcc"
#line 66 "../../prop-src/rwgen2.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_n_2co_c_c_Q1
#line 66 "../../prop-src/rwgen2.pcc"
#line 66 "../../prop-src/rwgen2.pcc"
 + rewriter_name + 
#line 66 "../../prop-src/rwgen2.pcc"
#line 66 "../../prop-src/rwgen2.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_n_2co_c_c_Q2
#line 66 "../../prop-src/rwgen2.pcc"
#line 66 "../../prop-src/rwgen2.pcc"
);
  Decl new_def =
     CLASSDEFdecl(new RewriteClass(rewriter_name,protocols,
#line 68 "../../prop-src/rwgen2.pcc"
#line 68 "../../prop-src/rwgen2.pcc"
nil_1_
#line 68 "../../prop-src/rwgen2.pcc"
#line 68 "../../prop-src/rwgen2.pcc"
,qual,
#line 68 "../../prop-src/rwgen2.pcc"
#line 68 "../../prop-src/rwgen2.pcc"
list_1_(body)
#line 68 "../../prop-src/rwgen2.pcc"
#line 68 "../../prop-src/rwgen2.pcc"
));
  rewriters = 
#line 69 "../../prop-src/rwgen2.pcc"
#line 69 "../../prop-src/rwgen2.pcc"
list_1_(new_def,list_1_(REWRITEdecl(rewriter_name,Is,rules),rewriters))
#line 69 "../../prop-src/rwgen2.pcc"
#line 69 "../../prop-src/rwgen2.pcc"
;
  MEM::use_local_pools();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method for compiling rewrite classes for the 'rewrite (...) { ... }'
//  construct.
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_rewriters()
{
  debug_msg("[Generating the rewriters in this file]\n");
  for_each (Decl, d, rewriters)
  {
    pr ("%D", d);
    
#line 86 "../../prop-src/rwgen2.pcc"
#line 132 "../../prop-src/rwgen2.pcc"
{
  if (d) {
    switch (d->tag__) {
      case a_Decl::tag_CLASSDEFdecl: {
        if (
#line 88 "../../prop-src/rwgen2.pcc"
        ((_CLASSDEFdecl(d)->CLASSDEFdecl->class_type == ClassDefinition::REWRITE_CLASS) && _CLASSDEFdecl(d)->CLASSDEFdecl->protocols)
#line 90 "../../prop-src/rwgen2.pcc"
) {
          
#line 91 "../../prop-src/rwgen2.pcc"
          
          Id id       = _CLASSDEFdecl(d)->CLASSDEFdecl->class_name;
          Ty ty       = _CLASSDEFdecl(d)->CLASSDEFdecl->protocols->_1->ty;
          TyQual qual = _CLASSDEFdecl(d)->CLASSDEFdecl->qualifiers;
          // If it is destructive, use call by reference
          Bool is_applicative = qual & QUALapplicative;
          Bool do_traversal   = qual & QUALtreeparser;
          Ty exp_ty = is_applicative ? ty : mkrefty(ty);
          Ty ret_ty = is_applicative ? ty : void_ty;
          
          // protocol
          pr ("%^%t %s_rewrite(%t _x_) ", ret_ty, "", id, exp_ty, "");
          // declare the rewriter
          pr ("%^{  %s _r_;", id);
          // call the labeler
          if (do_traversal)
          {
            if (is_applicative)
            {
              pr( "%^  return _r_.reduce(_r_(_x_));");
            }
            else
            {
              pr( "%^  _r_(_x_); %s_r_.reduce(_x_);",
                  ret_ty == void_ty ? "" : "return ");
            }
          }
          else
          {
            if (is_applicative)
            {
              pr ("%^   return _r_(_x_);");
            }
            else
            {
              pr ("%^   _r_(_x_);");
            }
          }
          pr ("%^}\n\n");
          
#line 130 "../../prop-src/rwgen2.pcc"
        } else {
          
          L1:; }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 132 "../../prop-src/rwgen2.pcc"
#line 132 "../../prop-src/rwgen2.pcc"

  }
  debug_msg("[Finished generating the rewriters in this file]\n");
}
#line 136 "../../prop-src/rwgen2.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 104
Number of ifs generated      = 5
Number of switches generated = 1
Number of labels             = 1
Number of gotos              = 2
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
