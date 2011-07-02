///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\parser-util.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#define PROP_REGEXP_MATCHING_USED
#define PROP_PARSER_USED
#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_p_a_r_s_e_rcn_u_t_i_lco_c_c_Q1("$$");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_p_a_r_s_e_rcn_u_t_i_lco_c_c_Q2("$");
#line 1 "../../prop-src/parser-util.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the utility routines for the parser.
//
///////////////////////////////////////////////////////////////////////////////

#include <new>
#include <iostream>
#include <AD/pretty/postream.h>
#include <strstream>
#include <string>
#include <stdlib.h>
#include "ir.h"
#include "ast.h"
#include "parser.h"
#include "type.h"
#include "matchcom.h"
#include "keywords.h"
#include "config.h"
#include "list.h"
#include "compiler.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Explaination mechanism for parser error.
//
///////////////////////////////////////////////////////////////////////////////

#line 31 "../../prop-src/parser-util.pcc"
#line 31 "../../prop-src/parser-util.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype PropToken
//
///////////////////////////////////////////////////////////////////////////////
#line 31 "../../prop-src/parser-util.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for PropToken
//
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& strm__, PropToken  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, PropToken  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype PropToken
//
///////////////////////////////////////////////////////////////////////////////
#line 31 "../../prop-src/parser-util.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for PropToken
//
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& strm__, PropToken  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, PropToken  obj__)
{
  switch (obj__)
  {
    case XX_r_e_w_r_i_t_eXX: 
      strm__ << "rewrite";
      break;
    case XX_i_n_f_e_r_e_n_c_eXX: 
      strm__ << "inference";
      break;
    case XX_m_a_t_c_hXX: 
      strm__ << "match";
      break;
    case XX_m_a_t_c_h_a_l_lXX: 
      strm__ << "matchall";
      break;
    case XX_m_a_t_c_h_s_c_a_nXX: 
      strm__ << "matchscan";
      break;
    case XX_r_e_f_i_n_eXX: 
      strm__ << "refine";
      break;
    case XX_c_l_a_s_s_o_fXX: 
      strm__ << "classof";
      break;
    case XX_t_y_p_eXX: 
      strm__ << "type";
      break;
    case XX_d_a_t_a_t_y_p_eXX: 
      strm__ << "datatype";
      break;
    case XX_i_n_s_t_a_n_t_i_a_t_eXX: 
      strm__ << "instantiate";
      break;
    case XX_l_e_x_e_m_eXX: 
      strm__ << "lexeme";
      break;
    case XX_b_i_t_f_i_e_l_dXX: 
      strm__ << "bitfield";
      break;
    case XX_b_e_g_i_nXX: 
      strm__ << "begin";
      break;
    case XX_s_y_n_t_a_xXX: 
      strm__ << "syntax";
      break;
    case XX_d_a_t_a_f_l_o_wXX: 
      strm__ << "dataflow";
      break;
    case XX_m_o_d_u_l_eXX: 
      strm__ << "module";
      break;
    case XX_s_i_g_n_a_t_u_r_eXX: 
      strm__ << "signature";
      break;
    case XX_c_o_n_s_t_r_a_i_n_tXX: 
      strm__ << "constraint";
      break;
    case XX_d_e_c_l_a_r_eXX: 
      strm__ << "declare";
      break;
    case XX_p_r_o_c_e_d_u_r_eXX: 
      strm__ << "procedure";
      break;
    case XX_f_u_nXX: 
      strm__ << "fun";
      break;
    case XX_f_u_n_c_t_i_o_nXX: 
      strm__ << "function";
      break;
    case XX_g_r_a_p_h_t_y_p_eXX: 
      strm__ << "graphtype";
      break;
    case XX_g_r_a_p_h_r_e_w_r_i_t_eXX: 
      strm__ << "graphrewrite";
      break;
    case XX_c_u_t_r_e_w_r_i_t_eXX: 
      strm__ << "cutrewrite";
      break;
    case XX_f_a_i_l_r_e_w_r_i_t_eXX: 
      strm__ << "failrewrite";
      break;
    case XX_a_t_t_r_i_b_u_t_e_g_r_a_m_m_a_rXX: 
      strm__ << "attributegrammar";
      break;
    case XX_i_fXX: 
      strm__ << "if";
      break;
    case XX_t_h_e_nXX: 
      strm__ << "then";
      break;
    case XX_e_l_s_eXX: 
      strm__ << "else";
      break;
    case XX_e_l_s_i_fXX: 
      strm__ << "elsif";
      break;
    case XX_w_h_i_l_eXX: 
      strm__ << "while";
      break;
    case XX_l_o_o_pXX: 
      strm__ << "loop";
      break;
    case XX_i_sXX: 
      strm__ << "is";
      break;
    case XX_c_l_a_s_sXX: 
      strm__ << "class";
      break;
    case XX_u_n_i_f_i_a_b_l_eXX: 
      strm__ << "unifiable";
      break;
    case XX_o_fXX: 
      strm__ << "of";
      break;
    case XX_d_oXX: 
      strm__ << "do";
      break;
    case XX_b_r_e_a_kXX: 
      strm__ << "break";
      break;
    case XX_c_o_n_t_i_n_u_eXX: 
      strm__ << "continue";
      break;
    case XX_g_o_t_oXX: 
      strm__ << "goto";
      break;
    case XX_w_h_e_r_eXX: 
      strm__ << "where";
      break;
    case XX_a_sXX: 
      strm__ << "as";
      break;
    case XX_p_u_b_l_i_cXX: 
      strm__ << "public";
      break;
    case XX_p_r_o_t_e_c_t_e_dXX: 
      strm__ << "protected";
      break;
    case XX_p_r_i_v_a_t_eXX: 
      strm__ << "private";
      break;
    case XX_c_o_n_s_tXX: 
      strm__ << "const";
      break;
    case XX_e_x_t_e_r_nXX: 
      strm__ << "extern";
      break;
    case XX_m_u_t_a_b_l_eXX: 
      strm__ << "mutable";
      break;
    case XX_a_p_p_l_i_c_a_t_i_v_eXX: 
      strm__ << "applicative";
      break;
    case XX_v_i_r_t_u_a_lXX: 
      strm__ << "virtual";
      break;
    case XX_t_r_u_eXX: 
      strm__ << "true";
      break;
    case XX_f_a_l_s_eXX: 
      strm__ << "false";
      break;
    case XX_c_o_l_l_e_c_t_a_b_l_eXX: 
      strm__ << "collectable";
      break;
    case XX_f_i_n_a_l_i_z_a_b_l_eXX: 
      strm__ << "finalizable";
      break;
    case XX_p_r_i_n_t_a_b_l_eXX: 
      strm__ << "printable";
      break;
    case XX_t_r_a_c_e_dXX: 
      strm__ << "traced";
      break;
    case XX_p_e_r_s_i_s_t_e_n_tXX: 
      strm__ << "persistent";
      break;
    case XX_t_r_e_e_p_a_r_s_e_rXX: 
      strm__ << "treeparser";
      break;
    case XX_i_n_l_i_n_eXX: 
      strm__ << "inline";
      break;
    case XX_w_i_t_hXX: 
      strm__ << "with";
      break;
    case XX_s_w_i_t_c_hXX: 
      strm__ << "switch";
      break;
    case XX_u_n_s_i_g_n_e_dXX: 
      strm__ << "unsigned";
      break;
    case XX_s_i_g_n_e_dXX: 
      strm__ << "signed";
      break;
    case XX_f_o_rXX: 
      strm__ << "for";
      break;
    case XX_c_a_t_e_g_o_r_yXX: 
      strm__ << "category";
      break;
    case XX_f_u_n_c_t_o_rXX: 
      strm__ << "functor";
      break;
    case XX_f_e_a_t_u_r_eXX: 
      strm__ << "feature";
      break;
    case XX_s_h_a_r_i_n_gXX: 
      strm__ << "sharing";
      break;
    case XX_r_e_l_a_t_i_o_nXX: 
      strm__ << "relation";
      break;
    case XX_v_i_e_wXX: 
      strm__ << "view";
      break;
    case XX_i_n_h_e_r_i_t_e_dXX: 
      strm__ << "inherited";
      break;
    case XX_r_e_t_u_r_nXX: 
      strm__ << "return";
      break;
    case XX_s_y_n_t_h_e_s_i_z_e_dXX: 
      strm__ << "synthesized";
      break;
    case XX_l_a_wXX: 
      strm__ << "law";
      break;
    case XX_l_e_f_tdkXX: 
      strm__ << "left:";
      break;
    case XX_r_i_g_h_tdkXX: 
      strm__ << "right:";
      break;
    case XX_e_x_p_e_c_tdkXX: 
      strm__ << "expect:";
      break;
    case XX_p_r_e_cdkXX: 
      strm__ << "prec:";
      break;
    case XX_m_a_p_o_fXX: 
      strm__ << "mapof";
      break;
    case XX_s_e_t_o_fXX: 
      strm__ << "setof";
      break;
    case XX_b_a_g_o_fXX: 
      strm__ << "bagof";
      break;
    case XX_m_u_l_t_i_m_a_p_o_fXX: 
      strm__ << "multimapof";
      break;
    case XX_l_i_s_t_o_fXX: 
      strm__ << "listof";
      break;
    case XX_p_r_i_q_u_e_u_e_o_fXX: 
      strm__ << "priqueueof";
      break;
    case XX_q_u_e_u_e_o_fXX: 
      strm__ << "queueof";
      break;
    case XX_d_e_q_u_e_o_fXX: 
      strm__ << "dequeof";
      break;
    case XX_t_u_p_l_e_o_fXX: 
      strm__ << "tupleof";
      break;
    case XX_f_o_r_a_l_lXX: 
      strm__ << "forall";
      break;
    case XX_e_x_i_s_t_sXX: 
      strm__ << "exists";
      break;
    case XX_d_o_mXX: 
      strm__ << "dom";
      break;
    case XX_r_a_nXX: 
      strm__ << "ran";
      break;
    case XX_a_r_bXX: 
      strm__ << "arb";
      break;
    case XX_l_e_s_sXX: 
      strm__ << "less";
      break;
    case XX_i_n_c_l_u_d_eXX: 
      strm__ << "include";
      break;
    case XX_l_f_pXX: 
      strm__ << "lfp";
      break;
    case XX_g_f_pXX: 
      strm__ << "gfp";
      break;
    case XX_h_o_mXX: 
      strm__ << "hom";
      break;
    case XX_i_m_p_l_i_e_sdkXX: 
      strm__ << "implies:";
      break;
    case XX_x_o_rdkXX: 
      strm__ << "xor:";
      break;
    case XX_e_q_u_i_vdkXX: 
      strm__ << "equiv:";
      break;
    case XX_t_i_m_edkXX: 
      strm__ << "time:";
      break;
    case XX_s_p_a_c_edkXX: 
      strm__ << "space:";
      break;
    case XX_n_o_d_e_sdkXX: 
      strm__ << "nodes:";
      break;
    case XX_e_d_g_e_sdkXX: 
      strm__ << "edges:";
      break;
    case XX_i_n_d_e_xdkXX: 
      strm__ << "index:";
      break;
    case XX_h_a_s_hdkXX: 
      strm__ << "hash:";
      break;
    case XX_e_q_u_a_l_i_t_ydkXX: 
      strm__ << "equality:";
      break;
    case XX_p_r_e_o_r_d_e_rdkXX: 
      strm__ << "preorder:";
      break;
    case XX_p_o_s_t_o_r_d_e_rdkXX: 
      strm__ << "postorder:";
      break;
    case XX_b_e_f_o_r_edkXX: 
      strm__ << "before:";
      break;
    case XX_t_o_p_d_o_w_ndkXX: 
      strm__ << "topdown:";
      break;
    case XX_b_o_t_t_o_m_u_pdkXX: 
      strm__ << "bottomup:";
      break;
    case XX_s_t_r_a_t_e_g_ydkXX: 
      strm__ << "strategy:";
      break;
    case XX_o_r_d_e_rdkXX: 
      strm__ << "order:";
      break;
    case XX_p_r_a_g_m_adkXX: 
      strm__ << "pragma:";
      break;
    case XX_c_a_s_eXX: 
      strm__ << "case";
      break;
    case XX_a_n_dXX: 
      strm__ << "and";
      break;
    case XX_e_n_dXX: 
      strm__ << "end";
      break;
    case XXcocoXX: 
      strm__ << "..";
      break;
    case XXcococoXX: 
      strm__ << "...";
      break;
    case XXdmcndoXX: 
      strm__ << "<->";
      break;
    case XXdkdkXX: 
      strm__ << "::";
      break;
    case XXcgcgXX: 
      strm__ << "&&";
      break;
    case XXhmhmXX: 
      strm__ << "||";
      break;
    case XXclclXX: 
      strm__ << "++";
      break;
    case XXcncnXX: 
      strm__ << "--";
      break;
    case XXcndoXX: 
      strm__ << "->";
      break;
    case XXdmdmXX: 
      strm__ << "<<";
      break;
    case XXdodoXX: 
      strm__ << ">>";
      break;
    case XXdodnXX: 
      strm__ << ">=";
      break;
    case XXdmdnXX: 
      strm__ << "<=";
      break;
    case XXcldnXX: 
      strm__ << "+=";
      break;
    case XXcndnXX: 
      strm__ << "-=";
      break;
    case XXckdnXX: 
      strm__ << "*=";
      break;
    case XXcpdnXX: 
      strm__ << "/=";
      break;
    case XXcfdnXX: 
      strm__ << "%=";
      break;
    case XXdndnXX: 
      strm__ << "==";
      break;
    case XXcbdnXX: 
      strm__ << "!=";
      break;
    case XXdmdmdnXX: 
      strm__ << "<<=";
      break;
    case XXdododnXX: 
      strm__ << ">>=";
      break;
    case XXcgdnXX: 
      strm__ << "&=";
      break;
    case XXhmdnXX: 
      strm__ << "|=";
      break;
    case XXfodnXX: 
      strm__ << "^=";
      break;
    case XXdndoXX: 
      strm__ << "=>";
      break;
    case XXdmcnXX: 
      strm__ << "<-";
      break;
    case XXdmdndoXX: 
      strm__ << "<=>";
      break;
    case XXdkdnXX: 
      strm__ << ":=";
      break;
    case XXdkcnXX: 
      strm__ << ":-";
      break;
    case LONG_BAR: 
      strm__ << "LONG_BAR";
      break;
    case CONS_TOK: 
      strm__ << "CONS_TOK";
      break;
    case DOMAIN_TOK: 
      strm__ << "DOMAIN_TOK";
      break;
    case CONS_EXP: 
      strm__ << "CONS_EXP";
      break;
    case META_QUOTE: 
      strm__ << "META_QUOTE";
      break;
    case POLY_DATATYPE: 
      strm__ << "POLY_DATATYPE";
      break;
    case ATTRIB_ID: 
      strm__ << "ATTRIB_ID";
      break;
    case XXcihmXX: 
      strm__ << "(|";
      break;
    case XXhmcjXX: 
      strm__ << "|)";
      break;
    case XXflhmXX: 
      strm__ << "[|";
      break;
    case XXhmfnXX: 
      strm__ << "|]";
      break;
    case XXhlhmXX: 
      strm__ << "{|";
      break;
    case XXhmhnXX: 
      strm__ << "|}";
      break;
    case XXcociXX: 
      strm__ << ".(";
      break;
    case XXcoflXX: 
      strm__ << ".[";
      break;
    case XXgagaXX: 
      strm__ << "``";
      break;
    case XXchchXX: 
      strm__ << "''";
      break;
    case INT_TOK: 
      strm__ << "INT_TOK";
      break;
    case REAL_TOK: 
      strm__ << "REAL_TOK";
      break;
    case CHAR_TOK: 
      strm__ << "CHAR_TOK";
      break;
    case STRING_TOK: 
      strm__ << "STRING_TOK";
      break;
    case ID_TOK: 
      strm__ << "ID_TOK";
      break;
    case REGEXP_TOK: 
      strm__ << "REGEXP_TOK";
      break;
    case QUARK_TOK: 
      strm__ << "QUARK_TOK";
      break;
    case BIGINT_TOK: 
      strm__ << "BIGINT_TOK";
      break;
    case PUNCTUATIONS: 
      strm__ << "PUNCTUATIONS";
      break;
  }
  return strm__;
}



#line 31 "../../prop-src/parser-util.pcc"
#line 31 "../../prop-src/parser-util.pcc"


void PropParser::print_user_symbol(std::ostream& f, Symbol c)
{
  f << '"' << (PropToken)c << '"';
}

void PropParser::explain_error()
{
  nice_explain( std::cerr);
  std::cerr << '\n';
  if (options.debug)
    debug_explain( std::cerr);
}

extern int match_rule;

///////////////////////////////////////////////////////////////////////////////
//
//  Destructor
//
///////////////////////////////////////////////////////////////////////////////

PropParser::~PropParser() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to initialize the parser
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::initialize( Compiler& C)
{
  compiler         = &C;
  graphtype_def    = 0;
  SCs_top          = 0;
  quote_top        = 0;
  levels_top       = 0;
  options.emit_code = true;
  me_top           = 0;
  var_top          = 0;
  antecedent_count = 0;
  in_rewrite       = false;
  rule_count       = 0;
  is_view_def      = false;
  symbol_count     = 0;
  item_count       = 0;
  nonterm_count    = 0;
  code_top         = 0;
  includes_top     = 0;
  included_count   = 0;
  program          = 
#line 82 "../../prop-src/parser-util.pcc"
#line 82 "../../prop-src/parser-util.pcc"
nil_1_
#line 82 "../../prop-src/parser-util.pcc"
#line 82 "../../prop-src/parser-util.pcc"
;
  my_cons          = NOcons;
  my_exp           = NOexp;
  match_rule       = 0;
  rw_top           = -1;
  push_rw_stack();
}

///////////////////////////////////////////////////////////////////////////////
//  Method to push/pop the rw stack
///////////////////////////////////////////////////////////////////////////////

void PropParser::push_rw_stack()
{
  ++rw_top;
  if (rw_top >= MAX_LEXICAL_DEPTH)
    bug("rw stack overflow");
  rw_stack[rw_top].mode    = MatchRuleInfo::BOTTOMUP;
  rw_stack[rw_top].option  = MatchRuleInfo::NO_OPTIONS;
  rw_stack[rw_top].qual    = QUALnone;
}

void PropParser::pop_rw_stack()
{
  --rw_top;
  if (rw_top < 0)
    bug("rw stack underflow");
}

///////////////////////////////////////////////////////////////////////////////
//  Functions to mark a tree with the current location.
///////////////////////////////////////////////////////////////////////////////

Pat  mark( Pat  p) { p = MARKEDpat(Loc(),p); return p; }
Exp  mark( Exp  e) { e = MARKEDexp(Loc(),e); return e; }
Decl mark( Decl d) { if (d != NOdecl) d = MARKEDdecl(Loc(),d); return d; }

///////////////////////////////////////////////////////////////////////////////
//
//  Function to mark tuples used
//
///////////////////////////////////////////////////////////////////////////////

void mark_tuple_used( int arity)
{
  if (arity <= 1 || arity > MAX_TUPLE_ARITY)
    bug("Illegal tuple arity: %i", arity);
  Used::tuple[arity] = true;
}

///////////////////////////////////////////////////////////////////////////////
//  Functions to build lists.
///////////////////////////////////////////////////////////////////////////////

Pat mklistpat( Id cons, Id nil, Pats ps, Pat p = NOpat)
{
  return 
#line 138 "../../prop-src/parser-util.pcc"
#line 138 "../../prop-src/parser-util.pcc"
LISTpat(lookup_cons(cons), lookup_cons(nil), ps, p)
#line 144 "../../prop-src/parser-util.pcc"
#line 144 "../../prop-src/parser-util.pcc"
;
}

Pat mkvecpat
   (Id a, Pat len, Pat array, Pats ps, Bool flex1 = false, Bool flex2 = false)
{
  Used::vector = true;
  return 
#line 151 "../../prop-src/parser-util.pcc"
#line 151 "../../prop-src/parser-util.pcc"
VECTORpat(lookup_cons(a), len, array, ps, flex1, flex2)
#line 159 "../../prop-src/parser-util.pcc"
#line 159 "../../prop-src/parser-util.pcc"
;
}

Exp mklistexp( Id cons, Id nil, Exps es, Exp e = NOexp)
{
  return LISTexp(lookup_cons(cons), lookup_cons(nil), es, e);
}

Exp mkappexp( Exp a, Exp b)
{
  Cons c = NOcons;
/*
   match (a) and (b)
   {  IDexp id, RECORDexp _ | c = find_cons(id): { return CONSexp(c,#[],b); }
   |  _:                                         { return APPexp(a,b); }
   }
*/
  
#line 176 "../../prop-src/parser-util.pcc"
#line 179 "../../prop-src/parser-util.pcc"
{
  if (a) {
    switch (a->tag__) {
      case a_Exp::tag_IDexp: {
        if (
#line 178 "../../prop-src/parser-util.pcc"
        (c = find_cons(_IDexp(a)->IDexp))
#line 178 "../../prop-src/parser-util.pcc"
) {
          
#line 178 "../../prop-src/parser-util.pcc"
         return CONSexp( c, 
#line 178 "../../prop-src/parser-util.pcc"
#line 178 "../../prop-src/parser-util.pcc"
          nil_1_
#line 178 "../../prop-src/parser-util.pcc"
#line 178 "../../prop-src/parser-util.pcc"
          , b); 
#line 178 "../../prop-src/parser-util.pcc"
        } else {
          
          L1:; 
#line 179 "../../prop-src/parser-util.pcc"
         return APPexp( a, b); 
#line 179 "../../prop-src/parser-util.pcc"
        }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 180 "../../prop-src/parser-util.pcc"
#line 180 "../../prop-src/parser-util.pcc"

}

Exp mkvecexp( Id vec, Exps es)
{
  Used::vector = true;
  return VECTORexp( lookup_cons( vec), es);
}

TermDef mklistterm( Id c, Ty a, Ty b, Decls d)
{  //match (b)
   //{  ! DEFVALty _: { b = DEFVALty(b,LITERALexp(INTlit(0))); }
   //|  _: // skip
   //}
   return 
#line 194 "../../prop-src/parser-util.pcc"
#line 194 "../../prop-src/parser-util.pcc"
TERMdef(c, mktuplety(list_1_(a,list_1_(b))), d, nil_1_, NOpat, nil_1_, OPTnone, QUALnone, NOexp)
#line 194 "../../prop-src/parser-util.pcc"
#line 194 "../../prop-src/parser-util.pcc"
;
}

Exp extupleexp( Exps es) { mark_tuple_used(length(es)); return EXTUPLEexp(es); }
Pat extuplepat( Pats ps) { mark_tuple_used(length(ps)); return EXTUPLEpat(ps); }
Ty  extuplety( Tys ts)   { mark_tuple_used(length(ts));
                          return TYCONty( (TyCon)EXTUPLEtycon, ts); }

///////////////////////////////////////////////////////////////////////////////
//  Function to build a piece of verbatim code.
///////////////////////////////////////////////////////////////////////////////

Decls PropParser::mkcode( Decls decls)
{
  if (options.emit_code && scan.length() > 0)
  {
    Decl code = OPAQUEdecl( str_pool( scan.text(), scan.length()));
    decls = 
#line 211 "../../prop-src/parser-util.pcc"
#line 211 "../../prop-src/parser-util.pcc"
list_1_(mark(code),decls)
#line 211 "../../prop-src/parser-util.pcc"
#line 211 "../../prop-src/parser-util.pcc"
;
  }
  scan.reset();
  first_line = line;
  return decls;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to increment the line count
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::count_lines ()
{
  for (const char * p = lexbuf.text(); *p; p++)
    if (*p == '\n')
      line++;
}

///////////////////////////////////////////////////////////////////////////////
//  Method to lookup an expression from the pattern environment.
///////////////////////////////////////////////////////////////////////////////

Exp PropParser::lookup_exp(Id id)
{
  Bool from_current;
  Exp e = pv_env.lookup(id,&from_current);
  
#line 239 "../../prop-src/parser-util.pcc"
#line 247 "../../prop-src/parser-util.pcc"
{
  char _V1 = id[0];
  if (e) {
#line 247 "../../prop-src/parser-util.pcc"
   return e; 
#line 247 "../../prop-src/parser-util.pcc"
  } else {
    switch (_V1) {
      case '#':
      case '$': {
        L2:; 
#line 242 "../../prop-src/parser-util.pcc"
        
        error ("%Lpattern variable '%s' has no binding at this point\n", id);
        return NOexp;
        
#line 245 "../../prop-src/parser-util.pcc"
      } break;
      default: {
#line 246 "../../prop-src/parser-util.pcc"
       return IDexp(id); 
#line 246 "../../prop-src/parser-util.pcc"
      }
    }
  }
}
#line 248 "../../prop-src/parser-util.pcc"
#line 248 "../../prop-src/parser-util.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//  Type variable stack for building polymorphic type schemes.
///////////////////////////////////////////////////////////////////////////////

Ty PropParser::lookup_tyvar( Id id)
{
  for (int i = 0; i < var_top; i++)
    if (var_stack[i] == id)
      return INDty( id, i);
  return mkidty( id, 
#line 260 "../../prop-src/parser-util.pcc"
#line 260 "../../prop-src/parser-util.pcc"
nil_1_
#line 260 "../../prop-src/parser-util.pcc"
#line 260 "../../prop-src/parser-util.pcc"
);
}

Pat PropParser::lookup_patvar( Id id)
{
  for (int i = 0; i < var_top; i++)
    if (var_stack[i] == id)
	  return pat_stack[i] == NOpat
                ? (pat_stack[i] = INDpat( id, i, mkvar())) : pat_stack[i];
  Pat scheme = DatatypeCompiler::lookup_pat(id);
  if (scheme != NOpat)
    return apply_pat( scheme, NOpat);
  else
    return IDpat( id, mkvar(), NOexp);
}

///////////////////////////////////////////////////////////////////////////////
//  Create a pattern from a constructor
///////////////////////////////////////////////////////////////////////////////

Pat PropParser::mkconspat( Cons cons)
{
  
#line 282 "../../prop-src/parser-util.pcc"
#line 296 "../../prop-src/parser-util.pcc"
{
  if (cons) {
    if (cons->alg_ty) {
      switch (cons->alg_ty->tag__) {
        case a_Ty::tag_TYCONty: {
          if (boxed(_TYCONty(cons->alg_ty)->_1)) {
            switch (_TYCONty(cons->alg_ty)->_1->tag__) {
              case a_TyCon::tag_DATATYPEtycon: {
                if (
#line 286 "../../prop-src/parser-util.pcc"
                ((_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->qualifiers & QUALlexeme) && (match_kind[me_top] & MATCHscanner))
#line 286 "../../prop-src/parser-util.pcc"
) {
                  
#line 287 "../../prop-src/parser-util.pcc"
                  
                  if (cons->lexeme_pattern == NOpat)
                  {
                    error ("%Lpattern is undefined for lexeme %s\n", cons->name);
                    return NOpat;
                  }
                  else
                    return cons->lexeme_pattern;
                  
#line 295 "../../prop-src/parser-util.pcc"
                } else {
                  
                  L3:; 
#line 296 "../../prop-src/parser-util.pcc"
                 return CONSpat(cons); 
#line 296 "../../prop-src/parser-util.pcc"
                }
                } break;
              default: { goto L3; } break;
            }
          } else { goto L3; }
          } break;
        default: { goto L3; } break;
      }
    } else { goto L3; }
  } else { goto L3; }
}
#line 297 "../../prop-src/parser-util.pcc"
#line 297 "../../prop-src/parser-util.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//  Routine to add a new "$" variable binding
///////////////////////////////////////////////////////////////////////////////

void PropParser::add_parse_stack_binding
   (int item_number, int symbol_number, int nonterm_number)
{
  Ty junk_ty = NOty;
  if (item_number <= 0)
    pv_env.add( 
#line 309 "../../prop-src/parser-util.pcc"
#line 309 "../../prop-src/parser-util.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_p_a_r_s_e_rcn_u_t_i_lco_c_c_Q1
#line 309 "../../prop-src/parser-util.pcc"
#line 309 "../../prop-src/parser-util.pcc"
, SYNexp( 0, -symbol_number, NOty, false), junk_ty);
  else
    pv_env.add( 
#line 311 "../../prop-src/parser-util.pcc"
#line 311 "../../prop-src/parser-util.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_p_a_r_s_e_rcn_u_t_i_lco_c_c_Q2
#line 311 "../../prop-src/parser-util.pcc"
#line 311 "../../prop-src/parser-util.pcc"
 + item_number,
            SYNexp( nonterm_number, -symbol_number, NOty, false), junk_ty);
}

///////////////////////////////////////////////////////////////////////////////
//  Error handler for the parser
///////////////////////////////////////////////////////////////////////////////

PropParser::ErrorAction PropParser::error_report(const char * message)
{
  if (meta.length() > 0)
  {
    error ("%L%s at quotation text `%s`, ", message, meta.text());
    meta.reset();
  }
  else if (lexbuf.length() == 0)
    error ("%L%s at end of file, ", message);
  else
    error ("%L%s at token \"%s\", ", message, lexbuf.text());

  return Retry;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to initialize the lexer
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::initialize_lexer( const char * initial_file_name)
{
  if (initial_file_name == 0)
    initial_file_name = "<stdin>";
  file = initial_file_name; line = first_line = 1;
  SCs_top     = 0;
  levels_top  = 0;
  quote_top   = 0;
  options.emit_code   = true;
  program     = 
#line 349 "../../prop-src/parser-util.pcc"
#line 349 "../../prop-src/parser-util.pcc"
nil_1_
#line 349 "../../prop-src/parser-util.pcc"
#line 349 "../../prop-src/parser-util.pcc"
;
  levels[levels_top++] = -1;
  lexbuf.set_context(C);
  lexbuf.set_stream(*input_stream);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to cleanup the lexer
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::cleanup_lexer()
{
  while (quote_top != 0)
  {
    const Quote& quote = quote_stack[--quote_top];
    Loc loc;
    loc.file_name  = quote.file_name;
    loc.begin_line = quote.line_number;
    loc.end_line   = quote.line_number;
    error ("%!unbalanced %c ... %c at end of file\n",
           &loc, (int)quote.open, (int)quote.close);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to open a new include file
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::open_include_file( const char * file_name)
{
  for (int i = 0; i < included_count; i++)
    if (included_files[i] == file_name)
      return;
  std::istream * new_stream = options.open_input_file( file_name);
  if (options.gen_dependences)
    IncludeDependency::add_dependency( str_pool[options.current_file_path]);
  if (new_stream == 0)
  {
    error ("%Lcan't find include file \"%s\"\n", file_name);
    return;
  }
  if (includes_top >= MAX_INCLUDE_FILES)
    bug ("Include file stack overflow");
  if (included_count >= MAX_INCLUDE_FILES)
    bug ("Too many include files");
  included_files[included_count++] = file_name;
  includes[includes_top].file_stream = input_stream;
  includes[includes_top].file        = file;
  includes[includes_top].line        = line;
  includes[includes_top].first_line  = first_line;
  includes[includes_top].scan        = scan;
  includes[includes_top].doc         = doc;
  includes[includes_top].meta        = meta;
  includes_top++;
  line         = 1;
  first_line   = 1;
  file         = file_name;
  options.emit_code    = false;
  input_stream = new_stream;
  lexbuf.push_stream(*input_stream);
  lexbuf.set_context(C);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to open a new include file
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::close_include_file()
{
  if (includes_top <= 0)
    bug("Include file stack underflow");
  --includes_top;
  debug_msg("[Closing \"%s\" %i lines]\n", file, line-1);
  delete input_stream;
  input_stream = includes[includes_top].file_stream;
  file         = includes[includes_top].file;
  line         = includes[includes_top].line;
  first_line   = includes[includes_top].first_line;
  scan         = includes[includes_top].scan;
  doc          = includes[includes_top].doc;
  meta         = includes[includes_top].meta;
  options.emit_code    = includes_top == 0;
  input_stream = &lexbuf.pop_stream();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to append text to the code buffer.
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::emit()
{ emit(lexbuf.text(), lexbuf.length()); }

void PropParser::emit( const char * t, long len)
{  if (options.emit_code) scan.emit(t,len); }

void PropParser::emit( char c)
{  if (options.emit_code) scan.emit(c); }

void PropParser::emit_header()
{  if (options.emit_code)
      compiler->emit_header(lexbuf.text()+2,lexbuf.length()-2);
}

//  Append an expression

void PropParser::emit( Exp e)
{
  std::ostrstream b;
  std::ostream& f = b;
  f << e << std::ends;
  emit(b.str());
  b.rdbuf()->freeze(0);  // free buffer
}

// Append a constructor expression
void PropParser::emit_cons( Id cons_name)
{
  lookup_cons( cons_name);
  emit( mangle( cons_name));
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to enter/exit a lexical context.
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::start_sc(LexicalContext c)
{
  SCs[SCs_top++] = LexicalContext( lexbuf.context());
  lexbuf.set_context(c);
  // if (options.debug) std::cerr << "[+context " << c << "]";
}

void PropParser::end_sc()
{
  if (SCs_top != 0)
  {
    --SCs_top;
    lexbuf.set_context(SCs[SCs_top]);
  }
  // if (options.debug) std::cerr << "[-context " << SCs[SCs_top] << "]";
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to enter/exit a statement
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::start_statement()
{
  levels[levels_top++] = quote_top;
  start_sc(C);
}

void PropParser::end_statement()
{
  levels_top--;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to push and pop from the quotation stack
//
///////////////////////////////////////////////////////////////////////////////

void PropParser::start_quote( char a, char b)
{  quote_stack[quote_top++] = Quote( file, line, a, b);
}

char PropParser::end_quote( char c)
{
  if (quote_top == 0)
  {
    error("%Lunmatched ending quote %c\n",c);
    return c;
  }
  else
  {
    const Quote& quote = quote_stack[quote_top-1];
    if (quote.close != c)
    {
      error("%Lexpecting %c ... %c (from line %i) but found %c ... %c instead\n",
             (int)quote.open, (int)quote.close, quote.line_number,
             (int)quote.open, (int)c);
    }
    quote_top--;
    return quote.close;
  }
}
#line 548 "../../prop-src/parser-util.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 101
Number of ifs generated      = 7
Number of switches generated = 4
Number of labels             = 3
Number of gotos              = 7
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
