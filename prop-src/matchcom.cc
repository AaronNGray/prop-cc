///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\matchcom.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_m_a_t_c_h_c_o_mco_c_c_Q1("?lexeme");
#line 1 "../../prop-src/matchcom.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the pattern matching compiler of the Prop -> C++
//  translator.  The following methods are implemented:
//
//    (i)   Variable bindings computation of patterns.
//    (ii)  Translation of patterns into decision trees.
//    (iii) Merging, transformation and minimization of decision trees/dags.
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <limits.h>
#include <stdlib.h>
#include <AD/contain/bitset.h>
#include <AD/generic/ordering.h>
#include <AD/strings/quark.h>
#include <AD/strings/charesc.h>
#include "ir.h"
#include "ast.h"
#include "matchcom.h"
#include "patenv.h"
#include "hashtab.h"
#include "config.h"
#include "type.h"
#include "options.h"
#include "list.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for class MatchCompiler
//
///////////////////////////////////////////////////////////////////////////////

MatchCompiler:: MatchCompiler()
    : vars("_X"), labels("L"),
      merges(0), ifs(0), switches(0), gotos(0), goto_labels(0),
      current_options(MATCHnone), current_rule(0)
    {}

MatchCompiler::~MatchCompiler() {}

MatchBase::MatchBase() : shared(0), label(0) {}

HashTable MatchCompiler::quark_map( string_hash, string_equal);
LabelGen MatchCompiler::quark_labels("_Q");

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor for MatchRuleInfo
//
///////////////////////////////////////////////////////////////////////////////

MatchRuleInfo::MatchRuleInfo ()
  : used(false), ty(NOty), rule_number(0), negated(false), rewriting(false),
    is_chain_rule(false), mode(BOTTOMUP), option(NO_OPTIONS)
  {}

///////////////////////////////////////////////////////////////////////////////
//
//  Flag that makes all selectors refer to the same object.
//
///////////////////////////////////////////////////////////////////////////////

Bool same_selectors = false;

///////////////////////////////////////////////////////////////////////////////
//
//  Allocation routines
//
///////////////////////////////////////////////////////////////////////////////

Literal * MatchCompiler::Literals(int n)
  { return (Literal *)mem_pool[n * sizeof(Literal)]; }

Match   * MatchCompiler::Matches(int n)
  { return (Match *)mem_pool[n * sizeof(Match)]; }

static Literal * vec (Literal l)
{
  Literal * L = (Literal *)mem_pool[sizeof(Literal)];
  L[0] = l;
  return L;
}

static Match * vec (Match m)
{
  Match * M = (Match *)mem_pool[sizeof(Match)];
  M[0] = m;
  return M;
}

///////////////////////////////////////////////////////////////////////////////
//
//  The mapping from quark name to identifiers
//
///////////////////////////////////////////////////////////////////////////////

Id MatchCompiler::quark_name(Id id)
{
  HashTable::Entry * e = quark_map.lookup(id);
  if (e)
    return (Id)e->v;
  else
  {
    Id name = Quark( options.mangled_file_name, quark_labels.new_label());
    quark_map.insert( (HashTable::Key) id, (HashTable::Value) name);
    return name;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Reverse the polarity of a pattern.
//
///////////////////////////////////////////////////////////////////////////////

#line 118 "../../prop-src/matchcom.pcc"
#line 121 "../../prop-src/matchcom.pcc"
Polarity rev (Polarity x_1);
Polarity rev (Polarity x_1)
{
  switch (x_1) {
    case ISpositive: {
#line 118 "../../prop-src/matchcom.pcc"
      return ISnegative;
#line 119 "../../prop-src/matchcom.pcc"
      } break;
    case ISnegative: {
#line 119 "../../prop-src/matchcom.pcc"
      return ISpositive;
#line 120 "../../prop-src/matchcom.pcc"
      } break;
    default: {
#line 120 "../../prop-src/matchcom.pcc"
      return ISneither;
#line 121 "../../prop-src/matchcom.pcc"
      } break;
  }
}
#line 121 "../../prop-src/matchcom.pcc"
#line 121 "../../prop-src/matchcom.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Method to perform substitution on a pattern.
//
///////////////////////////////////////////////////////////////////////////////

Pat subst( Pat pat, Pat env[], Bool copy)
{
  
#line 131 "../../prop-src/matchcom.pcc"
#line 189 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (pat) {
      switch (pat->tag__) {
        case a_Pat::tag_INDpat: {
          if (
#line 143 "../../prop-src/matchcom.pcc"
          copy
#line 143 "../../prop-src/matchcom.pcc"
) {
            
#line 144 "../../prop-src/matchcom.pcc"
           return INDpat( _INDpat(pat)->_1, _INDpat(pat)->_2, _INDpat(pat)->_3); 
#line 144 "../../prop-src/matchcom.pcc"
          } else {
            
#line 146 "../../prop-src/matchcom.pcc"
           return subst( env[_INDpat(pat)->_2], env, true); 
#line 146 "../../prop-src/matchcom.pcc"
          }
          } break;
        case a_Pat::tag_IDpat: {
#line 136 "../../prop-src/matchcom.pcc"
         return IDpat(_IDpat(pat)->_1,_IDpat(pat)->_2,_IDpat(pat)->_3); 
#line 136 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_CONSpat: {
#line 140 "../../prop-src/matchcom.pcc"
         return CONSpat(_CONSpat(pat)->CONSpat); 
#line 140 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_APPpat: {
#line 148 "../../prop-src/matchcom.pcc"
         return APPpat( subst( _APPpat(pat)->_1, env, copy), subst( _APPpat(pat)->_2, env, copy)); 
#line 148 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_TYPEDpat: {
#line 150 "../../prop-src/matchcom.pcc"
         return TYPEDpat( subst( _TYPEDpat(pat)->_1, env, copy), _TYPEDpat(pat)->_2); 
#line 150 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_ASpat: {
#line 152 "../../prop-src/matchcom.pcc"
         return ASpat( _ASpat(pat)->_1, subst( _ASpat(pat)->_2, env, copy), _ASpat(pat)->_3, _ASpat(pat)->_4); 
#line 152 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_LITERALpat: {
#line 138 "../../prop-src/matchcom.pcc"
         return LITERALpat(_LITERALpat(pat)->LITERALpat); 
#line 138 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_CONTEXTpat: {
#line 142 "../../prop-src/matchcom.pcc"
         return CONTEXTpat( _CONTEXTpat(pat)->_1, subst( _CONTEXTpat(pat)->_2, env, copy)); 
#line 142 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_ARRAYpat: {
#line 158 "../../prop-src/matchcom.pcc"
         return ARRAYpat( subst( _ARRAYpat(pat)->_1, env, copy), _ARRAYpat(pat)->_2); 
#line 158 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_TUPLEpat: {
#line 154 "../../prop-src/matchcom.pcc"
         return TUPLEpat( subst( _TUPLEpat(pat)->TUPLEpat, env, copy)); 
#line 154 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_EXTUPLEpat: {
#line 156 "../../prop-src/matchcom.pcc"
         return EXTUPLEpat( subst( _EXTUPLEpat(pat)->EXTUPLEpat, env, copy)); 
#line 156 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_RECORDpat: {
#line 172 "../../prop-src/matchcom.pcc"
         return RECORDpat( subst( _RECORDpat(pat)->_1, env, copy), _RECORDpat(pat)->_2); 
#line 172 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_LISTpat: {
#line 174 "../../prop-src/matchcom.pcc"
          
          return 
#line 175 "../../prop-src/matchcom.pcc"
#line 175 "../../prop-src/matchcom.pcc"
          LISTpat(_LISTpat(pat)->cons, _LISTpat(pat)->nil, subst(_LISTpat(pat)->head,env,copy), subst(_LISTpat(pat)->tail,env,copy))
#line 180 "../../prop-src/matchcom.pcc"
#line 180 "../../prop-src/matchcom.pcc"
          ;
          
#line 181 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_VECTORpat: {
#line 160 "../../prop-src/matchcom.pcc"
          
          return 
#line 161 "../../prop-src/matchcom.pcc"
#line 161 "../../prop-src/matchcom.pcc"
          VECTORpat(_VECTORpat(pat)->cons, subst(_VECTORpat(pat)->len,env,copy), subst(_VECTORpat(pat)->array,env,copy), subst(_VECTORpat(pat)->elements,env,copy), _VECTORpat(pat)->head_flex, _VECTORpat(pat)->tail_flex)
#line 169 "../../prop-src/matchcom.pcc"
#line 169 "../../prop-src/matchcom.pcc"
          ;
          
#line 170 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_GUARDpat: {
#line 187 "../../prop-src/matchcom.pcc"
         return GUARDpat( subst( _GUARDpat(pat)->_1, env, copy), _GUARDpat(pat)->_2); 
#line 187 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_LOGICALpat: {
#line 183 "../../prop-src/matchcom.pcc"
         return LOGICALpat( _LOGICALpat(pat)->_1, subst( _LOGICALpat(pat)->_2, env, copy), subst( _LOGICALpat(pat)->_3, env, copy)); 
#line 183 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_MARKEDpat: {
#line 185 "../../prop-src/matchcom.pcc"
         pat = _MARKEDpat(pat)->_2; 
#line 185 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_WILDpat:
        case a_Pat::tag_LEXEMEpat: {
          L2:; 
#line 134 "../../prop-src/matchcom.pcc"
         return pat; 
#line 134 "../../prop-src/matchcom.pcc"
          } break;
        default: {
#line 189 "../../prop-src/matchcom.pcc"
         bug("subst()"); 
#line 189 "../../prop-src/matchcom.pcc"
          } break;
      }
    } else { goto L2; }
  }
}
#line 190 "../../prop-src/matchcom.pcc"
#line 190 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to perform substitution on a pattern list.
//
///////////////////////////////////////////////////////////////////////////////

Pats subst( Pats pats, Pat env[], Bool copy)
{
  
#line 201 "../../prop-src/matchcom.pcc"
#line 204 "../../prop-src/matchcom.pcc"
{
  if (pats) {
#line 204 "../../prop-src/matchcom.pcc"
   return 
#line 204 "../../prop-src/matchcom.pcc"
#line 204 "../../prop-src/matchcom.pcc"
    list_1_(subst(pats->_1,env,copy),subst(pats->_2,env,copy))
#line 204 "../../prop-src/matchcom.pcc"
#line 204 "../../prop-src/matchcom.pcc"
    ; 
#line 204 "../../prop-src/matchcom.pcc"
  } else {
#line 203 "../../prop-src/matchcom.pcc"
   return 
#line 203 "../../prop-src/matchcom.pcc"
#line 203 "../../prop-src/matchcom.pcc"
    nil_1_
#line 203 "../../prop-src/matchcom.pcc"
#line 203 "../../prop-src/matchcom.pcc"
    ; 
#line 203 "../../prop-src/matchcom.pcc"
  }
}
#line 205 "../../prop-src/matchcom.pcc"
#line 205 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to perform substitution on a labeled pattern list.
//
///////////////////////////////////////////////////////////////////////////////

LabPats subst( LabPats pats, Pat env[], Bool copy)
{
  
#line 216 "../../prop-src/matchcom.pcc"
#line 225 "../../prop-src/matchcom.pcc"
{
  if (pats) {
#line 220 "../../prop-src/matchcom.pcc"
    
    LabPat l;
    l.label = pats->_1.label;
    l.pat   = subst(pats->_1.pat,env,copy);
    return 
#line 224 "../../prop-src/matchcom.pcc"
#line 224 "../../prop-src/matchcom.pcc"
    list_1_(l,subst(pats->_2,env,copy))
#line 224 "../../prop-src/matchcom.pcc"
#line 224 "../../prop-src/matchcom.pcc"
    ;
    
#line 225 "../../prop-src/matchcom.pcc"
  } else {
#line 218 "../../prop-src/matchcom.pcc"
   return 
#line 218 "../../prop-src/matchcom.pcc"
#line 218 "../../prop-src/matchcom.pcc"
    nil_1_
#line 218 "../../prop-src/matchcom.pcc"
#line 218 "../../prop-src/matchcom.pcc"
    ; 
#line 218 "../../prop-src/matchcom.pcc"
  }
}
#line 226 "../../prop-src/matchcom.pcc"
#line 226 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Pattern application.
//
///////////////////////////////////////////////////////////////////////////////

Pat apply_pat (Pat scheme, Pat arg)
{
  
#line 237 "../../prop-src/matchcom.pcc"
#line 253 "../../prop-src/matchcom.pcc"
{
  if (scheme) {
    switch (scheme->tag__) {
      case a_Pat::tag_POLYpat: {
        if (arg) {
          switch (arg->tag__) {
            case a_Pat::tag_TUPLEpat: {
              if (
#line 241 "../../prop-src/matchcom.pcc"
              (length(_TUPLEpat(arg)->TUPLEpat) == _POLYpat(scheme)->_2)
#line 241 "../../prop-src/matchcom.pcc"
) {
                
                switch (_POLYpat(scheme)->_2) {
                  case 0: {
                    if (arg) {
                      L3:; 
#line 242 "../../prop-src/matchcom.pcc"
                      
                      Pat env[256];
                      int i = 0;
                      for_each (Pat, p, _TUPLEpat(arg)->TUPLEpat) env[i++] = p;
                      return subst(_POLYpat(scheme)->_4,env,false);
                      
#line 247 "../../prop-src/matchcom.pcc"
                    } else {
                      L4:; 
#line 239 "../../prop-src/matchcom.pcc"
                     return subst( _POLYpat(scheme)->_4, 0, false); 
#line 239 "../../prop-src/matchcom.pcc"
                    }
                  } break;
                  case 1: {
                    L5:; 
#line 240 "../../prop-src/matchcom.pcc"
                   return subst( _POLYpat(scheme)->_4, &arg, false); 
#line 240 "../../prop-src/matchcom.pcc"
                  } break;
                  default: { goto L3; }
                }
              } else {
                
                L6:; 
                switch (_POLYpat(scheme)->_2) {
                  case 0: {
                    L7:; 
                    if (arg) {
                      L8:; 
#line 249 "../../prop-src/matchcom.pcc"
                      
                      error( "%Lunable to apply pattern scheme %p\n"
                             "%Lwith argument %p\n", scheme, arg);
                      return NOpat;
                      
#line 253 "../../prop-src/matchcom.pcc"
                    } else { goto L4; }
                  } break;
                  case 1: { goto L5; } break;
                  default: { goto L8; }
                }
              }
              } break;
            default: { goto L6; } break;
          }
        } else { goto L6; }
        } break;
      default: { goto L8; } break;
    }
  } else { goto L8; }
}
#line 254 "../../prop-src/matchcom.pcc"
#line 254 "../../prop-src/matchcom.pcc"

}

////////////////////////////////////////////////////////////////////////////////
//
//  Substitution on expressions.
//
///////////////////////////////////////////////////////////////////////////////

Exp subst(Exp exp, Exp s[])
{
  
#line 265 "../../prop-src/matchcom.pcc"
#line 316 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (exp) {
      switch (exp->tag__) {
        case a_Exp::tag_RELexp: {
#line 270 "../../prop-src/matchcom.pcc"
         return s[_RELexp(exp)->RELexp]; 
#line 270 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_DOTexp: {
#line 268 "../../prop-src/matchcom.pcc"
         return DOTexp( subst( _DOTexp(exp)->_1, s), _DOTexp(exp)->_2); 
#line 268 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_SELECTORexp: {
#line 272 "../../prop-src/matchcom.pcc"
         return SELECTORexp( subst( _SELECTORexp(exp)->_1, s), _SELECTORexp(exp)->_2, _SELECTORexp(exp)->_3); 
#line 272 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_DEREFexp: {
#line 274 "../../prop-src/matchcom.pcc"
         return DEREFexp( subst( _DEREFexp(exp)->DEREFexp, s)); 
#line 274 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_ARROWexp: {
#line 276 "../../prop-src/matchcom.pcc"
         return ARROWexp( subst( _ARROWexp(exp)->_1, s), _ARROWexp(exp)->_2); 
#line 276 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_INDEXexp: {
#line 278 "../../prop-src/matchcom.pcc"
         return INDEXexp( subst( _INDEXexp(exp)->_1, s), subst( _INDEXexp(exp)->_2, s)); 
#line 278 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_BINOPexp: {
#line 280 "../../prop-src/matchcom.pcc"
         return BINOPexp( _BINOPexp(exp)->_1, subst( _BINOPexp(exp)->_2, s),subst( _BINOPexp(exp)->_3, s)); 
#line 280 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_PREFIXexp: {
#line 282 "../../prop-src/matchcom.pcc"
         return PREFIXexp( _PREFIXexp(exp)->_1, subst( _PREFIXexp(exp)->_2, s)); 
#line 282 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_POSTFIXexp: {
#line 284 "../../prop-src/matchcom.pcc"
         return POSTFIXexp( _POSTFIXexp(exp)->_1, subst( _POSTFIXexp(exp)->_2, s)); 
#line 284 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_APPexp: {
#line 286 "../../prop-src/matchcom.pcc"
         return APPexp( subst( _APPexp(exp)->_1, s), subst( _APPexp(exp)->_2, s)); 
#line 286 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_ASSIGNexp: {
#line 288 "../../prop-src/matchcom.pcc"
         return ASSIGNexp( subst( _ASSIGNexp(exp)->_1, s), subst( _ASSIGNexp(exp)->_2, s)); 
#line 288 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_IFexp: {
#line 290 "../../prop-src/matchcom.pcc"
         return IFexp( subst( _IFexp(exp)->_1, s), subst( _IFexp(exp)->_2, s), subst( _IFexp(exp)->_3, s)); 
#line 290 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_TUPLEexp: {
#line 292 "../../prop-src/matchcom.pcc"
         return TUPLEexp( subst( _TUPLEexp(exp)->TUPLEexp, s)); 
#line 292 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_RECORDexp: {
#line 294 "../../prop-src/matchcom.pcc"
         return RECORDexp( subst( _RECORDexp(exp)->RECORDexp, s)); 
#line 294 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_LISTexp: {
#line 298 "../../prop-src/matchcom.pcc"
         return LISTexp( _LISTexp(exp)->_1, _LISTexp(exp)->_2, subst( _LISTexp(exp)->_3, s), subst( _LISTexp(exp)->_4, s)); 
#line 298 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_CONSexp: {
#line 300 "../../prop-src/matchcom.pcc"
         return CONSexp( _CONSexp(exp)->_1, subst( _CONSexp(exp)->_2, s), subst( _CONSexp(exp)->_3, s)); 
#line 300 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_CASTexp: {
#line 302 "../../prop-src/matchcom.pcc"
         return CASTexp( _CASTexp(exp)->_1, subst( _CASTexp(exp)->_2, s)); 
#line 302 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_EQexp: {
#line 304 "../../prop-src/matchcom.pcc"
         return EQexp( _EQexp(exp)->_1, subst( _EQexp(exp)->_2, s), subst( _EQexp(exp)->_3, s)); 
#line 304 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_UNIFYexp: {
#line 306 "../../prop-src/matchcom.pcc"
         return UNIFYexp( _UNIFYexp(exp)->_1, subst( _UNIFYexp(exp)->_2, s), subst( _UNIFYexp(exp)->_3, s)); 
#line 306 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_LTexp: {
#line 308 "../../prop-src/matchcom.pcc"
         return LTexp( _LTexp(exp)->_1, subst( _LTexp(exp)->_2, s), subst( _LTexp(exp)->_3, s)); 
#line 308 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_HASHexp: {
#line 310 "../../prop-src/matchcom.pcc"
         return HASHexp( _HASHexp(exp)->_1, subst( _HASHexp(exp)->_2, s)); 
#line 310 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_SENDexp: {
#line 296 "../../prop-src/matchcom.pcc"
         return SENDexp( _SENDexp(exp)->_1, subst( _SENDexp(exp)->_2, s)); 
#line 296 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_SETLexp: {
#line 312 "../../prop-src/matchcom.pcc"
         return SETLexp( _SETLexp(exp)->_1, subst( _SETLexp(exp)->_2, s)); 
#line 312 "../../prop-src/matchcom.pcc"
          } break;
        case a_Exp::tag_MARKEDexp: {
#line 314 "../../prop-src/matchcom.pcc"
         exp = _MARKEDexp(exp)->_2; 
#line 314 "../../prop-src/matchcom.pcc"
          } break;
        default: {
          L10:; 
#line 316 "../../prop-src/matchcom.pcc"
         return exp; 
#line 316 "../../prop-src/matchcom.pcc"
          } break;
      }
    } else { goto L10; }
  }
}
#line 317 "../../prop-src/matchcom.pcc"
#line 317 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Substitution on expression lists.
//
///////////////////////////////////////////////////////////////////////////////

Exps subst( Exps es, Exp s[])
{
  
#line 328 "../../prop-src/matchcom.pcc"
#line 331 "../../prop-src/matchcom.pcc"
{
  if (es) {
#line 331 "../../prop-src/matchcom.pcc"
   return 
#line 331 "../../prop-src/matchcom.pcc"
#line 331 "../../prop-src/matchcom.pcc"
    list_1_(subst(es->_1,s),subst(es->_2,s))
#line 331 "../../prop-src/matchcom.pcc"
#line 331 "../../prop-src/matchcom.pcc"
    ; 
#line 331 "../../prop-src/matchcom.pcc"
  } else {
#line 330 "../../prop-src/matchcom.pcc"
   return 
#line 330 "../../prop-src/matchcom.pcc"
#line 330 "../../prop-src/matchcom.pcc"
    nil_1_
#line 330 "../../prop-src/matchcom.pcc"
#line 330 "../../prop-src/matchcom.pcc"
    ; 
#line 330 "../../prop-src/matchcom.pcc"
  }
}
#line 332 "../../prop-src/matchcom.pcc"
#line 332 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Substitution on labeled expression lists.
//
///////////////////////////////////////////////////////////////////////////////
LabExps subst( LabExps es, Exp s[])
{
  
#line 342 "../../prop-src/matchcom.pcc"
#line 350 "../../prop-src/matchcom.pcc"
{
  if (es) {
#line 345 "../../prop-src/matchcom.pcc"
    
    LabExp e;
    e.label = es->_1.label;
    e.exp   = subst(es->_1.exp,s);
    return 
#line 349 "../../prop-src/matchcom.pcc"
#line 349 "../../prop-src/matchcom.pcc"
    list_1_(e,subst(es->_2,s))
#line 349 "../../prop-src/matchcom.pcc"
#line 349 "../../prop-src/matchcom.pcc"
    ;
    
#line 350 "../../prop-src/matchcom.pcc"
  } else {
#line 344 "../../prop-src/matchcom.pcc"
   return 
#line 344 "../../prop-src/matchcom.pcc"
#line 344 "../../prop-src/matchcom.pcc"
    nil_1_
#line 344 "../../prop-src/matchcom.pcc"
#line 344 "../../prop-src/matchcom.pcc"
    ; 
#line 344 "../../prop-src/matchcom.pcc"
  }
}
#line 351 "../../prop-src/matchcom.pcc"
#line 351 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Compute the view selector given the type
//
///////////////////////////////////////////////////////////////////////////////

Exp view_selector_of( Cons cons, Pat pat, Exp e, Ty ty)
{
  Exp selector_exp = default_val(ty);
  if (selector_exp == NOexp)
  {
    error(
           "%Laccessor is undefined for view pattern: %s %p\n",
           (cons != NOcons ? cons->name : "???"), pat
         );
    return NOexp;
  }
  else
    return subst( selector_exp, &e);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Decorate selector bindings for a view constructor
//
///////////////////////////////////////////////////////////////////////////////

void decor_view
   (Cons cons, Pat pat, Exp sel,
    Polarity polarity, Bool visible, PatternVarEnv& E, int& match_rule)
{
   if (boxed(pat)) pat->selector = sel; // annotate selector
   
#line 386 "../../prop-src/matchcom.pcc"
#line 434 "../../prop-src/matchcom.pcc"
{
  if (cons) {
    if (
#line 388 "../../prop-src/matchcom.pcc"
    (cons->view_selectors != 0)
#line 388 "../../prop-src/matchcom.pcc"
) {
      
#line 389 "../../prop-src/matchcom.pcc"
      
      
#line 390 "../../prop-src/matchcom.pcc"
#line 428 "../../prop-src/matchcom.pcc"
      {
        int _V1 = arity_of(cons->ty);
        Ty _V2 = deref(cons->ty);
        switch (_V1) {
          case 0: {
#line 392 "../../prop-src/matchcom.pcc"
           bug ("decor_view()"); 
#line 392 "../../prop-src/matchcom.pcc"
          } break;
          case 1: {
#line 394 "../../prop-src/matchcom.pcc"
            
            decor( pat, view_selector_of( cons, pat, sel, cons->ty),
                  polarity, visible, E, match_rule); 
#line 396 "../../prop-src/matchcom.pcc"
          } break;
          default: {
            if (pat) {
              switch (pat->tag__) {
                case a_Pat::tag_TUPLEpat: {
                  if (_V2) {
                    switch (_V2->tag__) {
                      case a_Ty::tag_TYCONty: {
                        if (boxed(_TYCONty(_V2)->_1)) {
                          L11:; 
#line 428 "../../prop-src/matchcom.pcc"
                         error ("%Lbad view constructor pattern: %p", pat); 
#line 428 "../../prop-src/matchcom.pcc"
                        } else {
                          switch ((int)_TYCONty(_V2)->_1) {
                            case ((int)v_TUPLEtycon): {
#line 398 "../../prop-src/matchcom.pcc"
                              
                              int i;
                              
#line 400 "../../prop-src/matchcom.pcc"
a_List<Pat> *  
#line 400 "../../prop-src/matchcom.pcc"
                             pat_list;
                              a_List<Ty> *  
#line 401 "../../prop-src/matchcom.pcc"
                            ty_list;
                              for (i = 0, pat_list = _TUPLEpat(pat)->TUPLEpat, ty_list = _TYCONty(_V2)->_2;
                                   pat_list && ty_list;
                                   pat_list = pat_list->_2, ty_list = ty_list->_2)
                              {
                                decor( pat_list->_1, view_selector_of( cons, pat, sel, ty_list->_1),
                                       polarity, visible, E, match_rule);
                                i++;
                              }
                              } break;
                            default: { goto L11; } break;
                          }
                        }
                        } break;
                      default: { goto L11; } break;
                    }
                  } else { goto L11; }
                  } break;
                case a_Pat::tag_RECORDpat: {
                  if (_V2) {
                    switch (_V2->tag__) {
                      case a_Ty::tag_TYCONty: {
                        if (boxed(_TYCONty(_V2)->_1)) {
                          switch (_TYCONty(_V2)->_1->tag__) {
                            case a_TyCon::tag_RECORDtycon: {
#line 412 "../../prop-src/matchcom.pcc"
                              
                              for_each ( LabPat, p, _RECORDpat(pat)->_1)
                              {
                                int i;
                                
#line 416 "../../prop-src/matchcom.pcc"
a_List<Id> *  
#line 416 "../../prop-src/matchcom.pcc"
                             lab_list;
                              a_List<Ty> *  
#line 417 "../../prop-src/matchcom.pcc"
                             ty_list;
                              for (i = 0, lab_list = _RECORDtycon(_TYCONty(_V2)->_1)->_1, ty_list = _TYCONty(_V2)->_2;
                                   lab_list && ty_list;
                                   lab_list = lab_list->_2, ty_list = ty_list->_2, i++)
                              {  if (lab_list->_1 == p.label)
                                    decor(p.pat,view_selector_of(cons,pat,sel,ty_list->_1),
                                          polarity,visible,E,match_rule);
                              }
                              }
                              } break;
                            default: { goto L11; } break;
                          }
                        } else { goto L11; }
                        } break;
                      default: { goto L11; } break;
                    }
                  } else { goto L11; }
                  } break;
                default: { goto L11; } break;
              }
            } else { goto L11; }
          }
        }
      }
#line 429 "../../prop-src/matchcom.pcc"
#line 429 "../../prop-src/matchcom.pcc"
      
      
#line 430 "../../prop-src/matchcom.pcc"
    } else {
      
#line 432 "../../prop-src/matchcom.pcc"
     error ("%Lmissing view selector for pattern: %p", pat); 
#line 432 "../../prop-src/matchcom.pcc"
    }
  } else {}
}
#line 434 "../../prop-src/matchcom.pcc"
#line 434 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Decorate patterns with selector bindings.
//
///////////////////////////////////////////////////////////////////////////////
void decor
   (Pat pat, Exp sel, Polarity polarity, Bool visible, PatternVarEnv& E,
    int& match_rule)
{
  for(;;)
  {
    if (! boxed(pat)) return;
    pat->selector = sel; // annotate selector
    
#line 450 "../../prop-src/matchcom.pcc"
#line 580 "../../prop-src/matchcom.pcc"
{
  if (pat) {
    switch (pat->tag__) {
      case a_Pat::tag_IDpat: {
#line 469 "../../prop-src/matchcom.pcc"
        
        if (visible)
        {
          Exp exp = E.add(_IDpat(pat)->_1,sel,_IDpat(pat)->_2,polarity);
          if (E.separate_guard() && ! E.tree_grammar() && exp != NOexp)
            E.add_guard(EQexp(_IDpat(pat)->_2,sel,exp));
          else
            _IDpat(pat)->_3 = exp;
        }
        return;
        
#line 479 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_APPpat: {
        if (_APPpat(pat)->_1) {
          switch (_APPpat(pat)->_1->tag__) {
            case a_Pat::tag_CONSpat: {
              if (_CONSpat(_APPpat(pat)->_1)->CONSpat) {
                if (_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty) {
                  switch (_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty->tag__) {
                    case a_Ty::tag_TYCONty: {
                      if (boxed(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)) {
                        switch (_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1->tag__) {
                          case a_TyCon::tag_DATATYPEtycon: {
                            if (
#line 556 "../../prop-src/matchcom.pcc"
                            (_DATATYPEtycon(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)->qualifiers & QUALview)
#line 556 "../../prop-src/matchcom.pcc"
) {
                              
#line 557 "../../prop-src/matchcom.pcc"
                            decor_view( _CONSpat(_APPpat(pat)->_1)->CONSpat, _APPpat(pat)->_2, sel, polarity, visible, E, match_rule); return; 
#line 557 "../../prop-src/matchcom.pcc"
                            } else {
                              
                              L12:; 
#line 559 "../../prop-src/matchcom.pcc"
                            decor( _APPpat(pat)->_2, select( sel, _CONSpat(_APPpat(pat)->_1)->CONSpat), polarity, visible, E, match_rule); return; 
#line 559 "../../prop-src/matchcom.pcc"
                            }
                            } break;
                          default: { goto L12; } break;
                        }
                      } else { goto L12; }
                      } break;
                    default: { goto L12; } break;
                  }
                } else { goto L12; }
              } else { goto L12; }
              } break;
            default: {
              L13:; 
#line 580 "../../prop-src/matchcom.pcc"
             bug("decor()"); 
#line 580 "../../prop-src/matchcom.pcc"
              } break;
          }
        } else { goto L13; }
        } break;
      case a_Pat::tag_TYPEDpat: {
#line 495 "../../prop-src/matchcom.pcc"
       pat = _TYPEDpat(pat)->_1; 
#line 495 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_ASpat: {
#line 481 "../../prop-src/matchcom.pcc"
        
        if (visible)
        {
          Exp exp = E.add(_ASpat(pat)->_1,sel,_ASpat(pat)->_3,polarity);
          if (E.separate_guard() && ! E.tree_grammar() && exp != NOexp)
            E.add_guard(EQexp(_ASpat(pat)->_3,sel,exp));
          else
            _ASpat(pat)->_4 = exp;
        }
        pat = _ASpat(pat)->_2;
        
#line 491 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_CONTEXTpat: {
#line 494 "../../prop-src/matchcom.pcc"
       pat = _CONTEXTpat(pat)->_2; 
#line 494 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_LEXEMEpat: {
        if (
#line 453 "../../prop-src/matchcom.pcc"
        _LEXEMEpat(pat)->_4
#line 453 "../../prop-src/matchcom.pcc"
) {
          
#line 455 "../../prop-src/matchcom.pcc"
          
          if (visible)
          {
            Ty t = NOty;
            Exp binding =
               CASTexp( _LEXEMEpat(pat)->_2, BINOPexp( "+", IDexp( "rule__"),
                       LITERALexp( INTlit( _LEXEMEpat(pat)->_4[0]->tag + 256 - 1 - match_rule))));
            E.add( 
#line 462 "../../prop-src/matchcom.pcc"
#line 462 "../../prop-src/matchcom.pcc"
          cocofmcocofm_p_r_o_pcn_s_r_cfm_m_a_t_c_h_c_o_mco_c_c_Q1
#line 462 "../../prop-src/matchcom.pcc"
#line 462 "../../prop-src/matchcom.pcc"
          , binding, t, polarity);
          match_rule += _LEXEMEpat(pat)->_3 - 1;
          }
          return;
          
#line 466 "../../prop-src/matchcom.pcc"
        } else {
          
#line 467 "../../prop-src/matchcom.pcc"
         return; 
#line 467 "../../prop-src/matchcom.pcc"
        }
        } break;
      case a_Pat::tag_ARRAYpat: {
#line 518 "../../prop-src/matchcom.pcc"
        
        int i = 0;
        for_each ( Pat, p, _ARRAYpat(pat)->_1)
        {
          decor( p, INDEXexp( sel, LITERALexp( INTlit(i))), polarity, visible, E,
                 match_rule);
           i++;
        }
        return;
        
#line 527 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_TUPLEpat: {
#line 498 "../../prop-src/matchcom.pcc"
        
        int i = 1;
        for_each ( Pat, p, _TUPLEpat(pat)->TUPLEpat)
        {
          decor( p, DOTexp( sel, index_of(i)), polarity, visible, E, match_rule);
          i++;
        }
        return;
        
#line 506 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_EXTUPLEpat: {
#line 508 "../../prop-src/matchcom.pcc"
        
        int i = 1;
        for_each ( Pat, p, _EXTUPLEpat(pat)->EXTUPLEpat)
        {
          decor( p, DOTexp( sel, index_of(i)), polarity, visible, E, match_rule);
          i++;
        }
        return;
        
#line 516 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_RECORDpat: {
#line 548 "../../prop-src/matchcom.pcc"
        
        for_each ( LabPat, lab_pat, _RECORDpat(pat)->_1)
            decor( lab_pat.pat, DOTexp( sel, lab_pat.label),
                  polarity, visible, E, match_rule);
         return;
        
#line 553 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_LISTpat: {
#line 571 "../../prop-src/matchcom.pcc"
        
        for_each (Pat, apat, _LISTpat(pat)->head)
        {
          decor( apat, DOTexp( select( sel, _LISTpat(pat)->cons), "_1"), polarity, visible,
                 E, match_rule);
          sel = DOTexp( select( sel, _LISTpat(pat)->cons), "_2");
        }
        pat = _LISTpat(pat)->tail;
        
#line 579 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_VECTORpat: {
#line 529 "../../prop-src/matchcom.pcc"
        
        int i       = 0;
        Exp s       = select( sel, _VECTORpat(pat)->cons);
        Exp len_exp = DOTexp( s, "len()");
        int n       = length( _VECTORpat(pat)->elements);
        for_each ( Pat, p, _VECTORpat(pat)->elements)
        {
          Exp index_exp =
            _VECTORpat(pat)->head_flex ? BINOPexp( "-", len_exp, LITERALexp( INTlit( n-i)))
                      : LITERALexp( INTlit(i));
          decor( p, APPexp( DOTexp( s, "at"), index_exp), polarity, visible, E,
                match_rule);
          i++;
        }
        decor( _VECTORpat(pat)->len, len_exp, polarity, visible, E, match_rule);
        decor( _VECTORpat(pat)->array, DOTexp( s, "array()"), polarity, visible, E, match_rule);
        return;
        
#line 546 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_GUARDpat: {
#line 496 "../../prop-src/matchcom.pcc"
       pat = _GUARDpat(pat)->_1; 
#line 496 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_LOGICALpat: {
        switch (_LOGICALpat(pat)->_1) {
          case NOTpat: {
#line 560 "../../prop-src/matchcom.pcc"
           polarity = rev(polarity); pat = _LOGICALpat(pat)->_2; 
#line 560 "../../prop-src/matchcom.pcc"
            } break;
          case ANDpat: {
#line 562 "../../prop-src/matchcom.pcc"
           decor( _LOGICALpat(pat)->_2, sel, polarity, visible, E, match_rule); pat = _LOGICALpat(pat)->_3; 
#line 562 "../../prop-src/matchcom.pcc"
            } break;
          case ORpat: {
#line 564 "../../prop-src/matchcom.pcc"
           decor(_LOGICALpat(pat)->_2,sel,polarity,false,E,match_rule); pat = _LOGICALpat(pat)->_3; visible = false; 
#line 564 "../../prop-src/matchcom.pcc"
            } break;
          default: {
#line 566 "../../prop-src/matchcom.pcc"
            
            decor( _LOGICALpat(pat)->_2, sel, ISneither, false, E, match_rule);
            pat = _LOGICALpat(pat)->_3; visible = false; polarity = ISneither;
            
#line 569 "../../prop-src/matchcom.pcc"
            } break;
        }
        } break;
      case a_Pat::tag_UNIFYpat: {
#line 493 "../../prop-src/matchcom.pcc"
       pat = _UNIFYpat(pat)->_1; 
#line 493 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 492 "../../prop-src/matchcom.pcc"
       pat = _MARKEDpat(pat)->_2; 
#line 492 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_WILDpat:
      case a_Pat::tag_CONSpat:
      case a_Pat::tag_LITERALpat: {
        L14:; 
#line 452 "../../prop-src/matchcom.pcc"
       return; 
#line 452 "../../prop-src/matchcom.pcc"
        } break;
      default: { goto L13; } break;
    }
  } else { goto L14; }
}
#line 581 "../../prop-src/matchcom.pcc"
#line 581 "../../prop-src/matchcom.pcc"

  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Decorate a pattern list with bindings.
//
///////////////////////////////////////////////////////////////////////////////

void decor
   (MatchExps exps, Pat pat, Polarity polarity, Bool visible,
    PatternVarEnv& E, int& match_rule)
{
  int arity = length(exps);
  if (arity == 1)
  {
    
#line 598 "../../prop-src/matchcom.pcc"
#line 601 "../../prop-src/matchcom.pcc"
{
  MatchExp _V3 = exps->_1;
#line 601 "../../prop-src/matchcom.pcc"
decor( pat, _V3->_2 ? IDexp(_V3->_2) : _V3->_1, polarity, visible, E, match_rule); 
#line 601 "../../prop-src/matchcom.pcc"
}
#line 602 "../../prop-src/matchcom.pcc"
#line 602 "../../prop-src/matchcom.pcc"

  }
  else
  {
    
#line 606 "../../prop-src/matchcom.pcc"
#line 647 "../../prop-src/matchcom.pcc"
{
  if (pat) {
    switch (pat->tag__) {
      case a_Pat::tag_WILDpat: {
#line 608 "../../prop-src/matchcom.pcc"
       /* skip */ 
#line 608 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_CONTEXTpat: {
#line 610 "../../prop-src/matchcom.pcc"
       decor( exps, _CONTEXTpat(pat)->_2, polarity, visible, E, match_rule); 
#line 610 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_TUPLEpat: {
        if (
#line 611 "../../prop-src/matchcom.pcc"
        (length(_TUPLEpat(pat)->TUPLEpat) == arity)
#line 611 "../../prop-src/matchcom.pcc"
) {
          
#line 612 "../../prop-src/matchcom.pcc"
          
          Pats      ps;
          MatchExps es;
          for (ps = _TUPLEpat(pat)->TUPLEpat, es = exps; ps; ps = ps->_2, es = es->_2)
          {
            
#line 617 "../../prop-src/matchcom.pcc"
#line 623 "../../prop-src/matchcom.pcc"
          {
            MatchExp _V4 = es->_1;
#line 620 "../../prop-src/matchcom.pcc"
            
            decor( ps->_1, _V4->_2 ? IDexp(_V4->_2) : _V4->_1, polarity,
                   visible, E, match_rule);
            
#line 623 "../../prop-src/matchcom.pcc"
          }
#line 624 "../../prop-src/matchcom.pcc"
#line 624 "../../prop-src/matchcom.pcc"
          
          }
          
#line 626 "../../prop-src/matchcom.pcc"
        } else {
          
          L15:; 
#line 645 "../../prop-src/matchcom.pcc"
          
          error( "%Larity mismatch (expecting %i) in pattern: %p\n", arity, pat);
          
#line 647 "../../prop-src/matchcom.pcc"
        }
        } break;
      case a_Pat::tag_LOGICALpat: {
        switch (_LOGICALpat(pat)->_1) {
          case NOTpat: {
#line 628 "../../prop-src/matchcom.pcc"
           decor( exps, _LOGICALpat(pat)->_2, rev(polarity), false, E, match_rule); 
#line 628 "../../prop-src/matchcom.pcc"
            } break;
          case ANDpat: {
#line 630 "../../prop-src/matchcom.pcc"
            
            decor( exps, _LOGICALpat(pat)->_2, polarity, visible, E, match_rule);
            decor( exps, _LOGICALpat(pat)->_3, polarity, visible, E, match_rule);
            
#line 633 "../../prop-src/matchcom.pcc"
            } break;
          case ORpat: {
#line 635 "../../prop-src/matchcom.pcc"
            
            decor( exps, _LOGICALpat(pat)->_2, polarity, false, E, match_rule);
            decor( exps, _LOGICALpat(pat)->_3, polarity, false, E, match_rule);
            
#line 638 "../../prop-src/matchcom.pcc"
            } break;
          default: {
#line 640 "../../prop-src/matchcom.pcc"
            
            decor( exps, _LOGICALpat(pat)->_2, ISneither, false, E, match_rule);
            decor( exps, _LOGICALpat(pat)->_3, ISneither, false, E, match_rule);
            
#line 643 "../../prop-src/matchcom.pcc"
            } break;
        }
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 609 "../../prop-src/matchcom.pcc"
       decor( exps, _MARKEDpat(pat)->_2, polarity, visible, E, match_rule); 
#line 609 "../../prop-src/matchcom.pcc"
        } break;
      default: { goto L15; } break;
    }
  } else { goto L15; }
}
#line 648 "../../prop-src/matchcom.pcc"
#line 648 "../../prop-src/matchcom.pcc"

  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return the arity of a pattern
//
///////////////////////////////////////////////////////////////////////////////

#line 658 "../../prop-src/matchcom.pcc"
#line 674 "../../prop-src/matchcom.pcc"
int arity_of (Pat x_1);
int arity_of (Pat x_1)
{
  if (x_1) {
    switch (x_1->tag__) {
      case a_Pat::tag_CONTEXTpat: {
#line 662 "../../prop-src/matchcom.pcc"
        return arity_of(_CONTEXTpat(x_1)->_2);
#line 663 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_TUPLEpat: {
#line 658 "../../prop-src/matchcom.pcc"
        return length(_TUPLEpat(x_1)->TUPLEpat);
#line 659 "../../prop-src/matchcom.pcc"
        } break;
      case a_Pat::tag_RECORDpat: {
        if ((! _RECORDpat(x_1)->_2)) {
          
#line 659 "../../prop-src/matchcom.pcc"
          return length(_RECORDpat(x_1)->_1);
#line 660 "../../prop-src/matchcom.pcc"
        } else {
          
#line 671 "../../prop-src/matchcom.pcc"
         error ("%Lillegal incomplete record pattern: %p\n", x_1); return 0; 
#line 671 "../../prop-src/matchcom.pcc"
        }
        } break;
      case a_Pat::tag_LOGICALpat: {
        switch (_LOGICALpat(x_1)->_1) {
          case NOTpat: {
#line 661 "../../prop-src/matchcom.pcc"
            return arity_of(_LOGICALpat(x_1)->_2);
#line 662 "../../prop-src/matchcom.pcc"
            } break;
          default: {
#line 664 "../../prop-src/matchcom.pcc"
            
            int i = arity_of(_LOGICALpat(x_1)->_2);
            int j = arity_of(_LOGICALpat(x_1)->_3);
            if (i != j) error ("%Larity mismatch in logical pattern: %p\n", x_1);
            return i;
            
#line 669 "../../prop-src/matchcom.pcc"
            } break;
        }
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 660 "../../prop-src/matchcom.pcc"
        return arity_of(_MARKEDpat(x_1)->_2);
#line 661 "../../prop-src/matchcom.pcc"
        } break;
      default: {
        L16:; 
#line 673 "../../prop-src/matchcom.pcc"
       return 1; 
#line 673 "../../prop-src/matchcom.pcc"
        } break;
    }
  } else { goto L16; }
}
#line 674 "../../prop-src/matchcom.pcc"
#line 674 "../../prop-src/matchcom.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Make a list of match expressions
//
///////////////////////////////////////////////////////////////////////////////

MatchExps make_match_exps( int i, int n, int j)
{
  if (i > n)
    return 
#line 685 "../../prop-src/matchcom.pcc"
#line 685 "../../prop-src/matchcom.pcc"
nil_1_
#line 685 "../../prop-src/matchcom.pcc"
#line 685 "../../prop-src/matchcom.pcc"
;
  else
  {
     Exp e = j < 0 ? IDexp( index_of(i,"x")) : RELexp(j);
     return 
#line 689 "../../prop-src/matchcom.pcc"
#line 689 "../../prop-src/matchcom.pcc"
list_1_(MATCHexp(e,nil_1_),make_match_exps((i + 1),n,j))
#line 689 "../../prop-src/matchcom.pcc"
#line 689 "../../prop-src/matchcom.pcc"
;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Main decoration routine
//
///////////////////////////////////////////////////////////////////////////////

void decor( MatchExps& exps, Pat pat, PatternVarEnv& E, int& match_rule, int i)
{
  if (exps == 
#line 701 "../../prop-src/matchcom.pcc"
#line 701 "../../prop-src/matchcom.pcc"
nil_1_
#line 701 "../../prop-src/matchcom.pcc"
#line 701 "../../prop-src/matchcom.pcc"
)  // create default match expressions if there are none
      exps = make_match_exps( 1, arity_of(pat), i);
  decor( exps, pat, ISpositive, true, E, match_rule);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Translate a string literal into a character array pattern.
//
///////////////////////////////////////////////////////////////////////////////

#line 712 "../../prop-src/matchcom.pcc"
a_List<Pat> *  
#line 712 "../../prop-src/matchcom.pcc"
 make_string_pattern( const char * string)
{
  if (string[0] == '\"' && string[1] == '\0')
    return 
#line 715 "../../prop-src/matchcom.pcc"
list_1_(LITERALpat(CHARlit('\000')))
#line 715 "../../prop-src/matchcom.pcc"
#line 715 "../../prop-src/matchcom.pcc"
;
  else
  {
    char c;
    const char * next_pos = parse_char( string,c);
    
#line 720 "../../prop-src/matchcom.pcc"
a_List<Pat> *  
#line 720 "../../prop-src/matchcom.pcc"
 pats        = make_string_pattern( next_pos);
    return 
#line 721 "../../prop-src/matchcom.pcc"
list_1_(LITERALpat(CHARlit(c)),pats)
#line 721 "../../prop-src/matchcom.pcc"
#line 721 "../../prop-src/matchcom.pcc"
;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Translate a pattern into a matching tree.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::trans( Pat pat, Pos pos, Bool neg, Match yes, Match no)
{  
#line 732 "../../prop-src/matchcom.pcc"
#line 870 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (pat) {
      switch (pat->tag__) {
        case a_Pat::tag_WILDpat: {
          L18:; 
#line 734 "../../prop-src/matchcom.pcc"
         return neg ? no : yes; 
#line 734 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_IDpat: {
          if (_IDpat(pat)->_3) {
#line 741 "../../prop-src/matchcom.pcc"
           return GUARDmatch( EQexp( _IDpat(pat)->_2, pat->selector, _IDpat(pat)->_3),
            neg ? no : yes, neg ? yes : no); 
#line 742 "../../prop-src/matchcom.pcc"
          } else { goto L18; }
          } break;
        case a_Pat::tag_CONSpat: {
          if (_CONSpat(pat)->CONSpat) {
            if (_CONSpat(pat)->CONSpat->alg_ty) {
              switch (_CONSpat(pat)->CONSpat->alg_ty->tag__) {
                case a_Ty::tag_TYCONty: {
                  if (boxed(_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1)) {
                    switch (_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1->tag__) {
                      case a_TyCon::tag_DATATYPEtycon: {
#line 816 "../../prop-src/matchcom.pcc"
                        
                        int arity = _DATATYPEtycon(_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1)->unit + _DATATYPEtycon(_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1)->arg;
                        Match * m = Matches( arity);
                        for (int i = arity - 1; i >= 0; i--) m[i] = neg ? yes : no;
                        m[_CONSpat(pat)->CONSpat->tag] = neg ? no : yes;
                        return CONSmatch( pos, pat->selector, pat->ty, _CONSpat(pat)->CONSpat->alg_ty, arity, m, neg ? yes : no);
                        
#line 822 "../../prop-src/matchcom.pcc"
                        } break;
                      default: {
                        L19:; 
#line 870 "../../prop-src/matchcom.pcc"
                       bug("MatchCompiler::trans(): %p", pat); 
#line 870 "../../prop-src/matchcom.pcc"
                        } break;
                    }
                  } else { goto L19; }
                  } break;
                default: { goto L19; } break;
              }
            } else { goto L19; }
          } else {
            L20:; 
#line 869 "../../prop-src/matchcom.pcc"
           return neg ? no : yes; 
#line 869 "../../prop-src/matchcom.pcc"
          }
          } break;
        case a_Pat::tag_APPpat: {
          if (_APPpat(pat)->_1) {
            switch (_APPpat(pat)->_1->tag__) {
              case a_Pat::tag_CONSpat: {
                if (_CONSpat(_APPpat(pat)->_1)->CONSpat) {
                  if (_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty) {
                    switch (_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty->tag__) {
                      case a_Ty::tag_TYCONty: {
                        if (boxed(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)) {
                          switch (_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1->tag__) {
                            case a_TyCon::tag_DATATYPEtycon: {
#line 802 "../../prop-src/matchcom.pcc"
                              
                              int arity = _DATATYPEtycon(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)->unit + _DATATYPEtycon(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)->arg;
                              Match * m = Matches(arity);
                              int i;
                              for (i = arity - 1; i >= 0; i--)
                                m[i] = neg ? yes : no;
                              i = _CONSpat(_APPpat(pat)->_1)->CONSpat->tag + _DATATYPEtycon(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)->unit;
                              m[i] = trans( _APPpat(pat)->_2, POSint( i, pos), neg, yes, no);
                              return CONSmatch( pos, pat->selector, pat->ty, _CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty, arity, m, neg ? yes : no);
                              
#line 811 "../../prop-src/matchcom.pcc"
                              } break;
                            default: { goto L19; } break;
                          }
                        } else { goto L19; }
                        } break;
                      default: { goto L19; } break;
                    }
                  } else { goto L19; }
                } else { goto L20; }
                } break;
              default: { goto L19; } break;
            }
          } else { goto L19; }
          } break;
        case a_Pat::tag_TYPEDpat: {
#line 736 "../../prop-src/matchcom.pcc"
         pat = _TYPEDpat(pat)->_1; 
#line 736 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_ASpat: {
          if (_ASpat(pat)->_4) {
#line 749 "../../prop-src/matchcom.pcc"
            
            Exp guard = EQexp( _ASpat(pat)->_3, pat->selector, _ASpat(pat)->_4);
            if (neg)
              no  = GUARDmatch( guard, no, yes);
            else
              yes = GUARDmatch( guard, yes, no);
            pat = _ASpat(pat)->_2;
            
#line 756 "../../prop-src/matchcom.pcc"
          } else {
#line 735 "../../prop-src/matchcom.pcc"
           pat = _ASpat(pat)->_2; 
#line 735 "../../prop-src/matchcom.pcc"
          }
          } break;
        case a_Pat::tag_LITERALpat: {
#line 758 "../../prop-src/matchcom.pcc"
          
          return LITERALmatch( pos, pat->selector, vec(_LITERALpat(pat)->LITERALpat), 1, vec(neg ? no : yes),
                              neg ? yes : no);
          
#line 761 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_CONTEXTpat: {
#line 738 "../../prop-src/matchcom.pcc"
         pat = add_contexts(_CONTEXTpat(pat)->_1,_CONTEXTpat(pat)->_2); 
#line 738 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_LEXEMEpat: {
#line 739 "../../prop-src/matchcom.pcc"
         pat = expand_lexeme_pat(pat,_LEXEMEpat(pat)->_2,_LEXEMEpat(pat)->_3,_LEXEMEpat(pat)->_4); 
#line 739 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_ARRAYpat: {
#line 784 "../../prop-src/matchcom.pcc"
         return trans( _ARRAYpat(pat)->_1, 0, pos, neg, yes, no); 
#line 784 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_TUPLEpat: {
#line 763 "../../prop-src/matchcom.pcc"
          
          if (current_index_map)
          {
            HashTable::Entry * e = current_index_map->lookup(pos);
            if (e)
              return trans( _TUPLEpat(pat)->TUPLEpat, pos, neg, yes, no,
                              (int *)current_index_map->value(e));
          }
          return trans( _TUPLEpat(pat)->TUPLEpat, 0, pos, neg, yes, no);
          
#line 772 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_EXTUPLEpat: {
#line 774 "../../prop-src/matchcom.pcc"
          
          if (current_index_map)
          {
              HashTable::Entry * e = current_index_map->lookup(pos);
              if (e)
                 return trans( _EXTUPLEpat(pat)->EXTUPLEpat, pos, neg, yes, no,
                              (int *)current_index_map->value(e));
          }
          return trans( _EXTUPLEpat(pat)->EXTUPLEpat, 0, pos, neg, yes, no);
          
#line 783 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_RECORDpat: {
#line 796 "../../prop-src/matchcom.pcc"
         return trans(_RECORDpat(pat)->_1,pos,neg,yes,no); 
#line 796 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_LISTpat: {
          if (_LISTpat(pat)->cons) {
            if (_LISTpat(pat)->head) {
              L21:; 
#line 857 "../../prop-src/matchcom.pcc"
              
              Pat new_tail   = 
#line 858 "../../prop-src/matchcom.pcc"
#line 858 "../../prop-src/matchcom.pcc"
              LISTpat(_LISTpat(pat)->cons, _LISTpat(pat)->nil, _LISTpat(pat)->head->_2, _LISTpat(pat)->tail)
#line 858 "../../prop-src/matchcom.pcc"
#line 858 "../../prop-src/matchcom.pcc"
              ;
              Pat list_pat   = APPpat( CONSpat( _LISTpat(pat)->cons), TUPLEpat( 
#line 859 "../../prop-src/matchcom.pcc"
#line 859 "../../prop-src/matchcom.pcc"
              list_1_(_LISTpat(pat)->head->_1,list_1_(new_tail))
#line 859 "../../prop-src/matchcom.pcc"
#line 859 "../../prop-src/matchcom.pcc"
              ));
              new_tail->selector = DOTexp( select( pat->selector, _LISTpat(pat)->cons), "_2");
              list_pat->selector = pat->selector;
              pat = list_pat;
              
#line 863 "../../prop-src/matchcom.pcc"
            } else {
              L22:; 
              if (_LISTpat(pat)->tail) {
                L23:; 
#line 855 "../../prop-src/matchcom.pcc"
               pat = _LISTpat(pat)->tail; 
#line 855 "../../prop-src/matchcom.pcc"
              } else {
                L24:; 
#line 850 "../../prop-src/matchcom.pcc"
                
                Pat p = CONSpat(_LISTpat(pat)->nil);
                p->selector = pat->selector;
                pat = p;
                
#line 854 "../../prop-src/matchcom.pcc"
              }
            }
          } else {
            if (_LISTpat(pat)->head) { goto L21; } else { goto L22; }
          }
          } break;
        case a_Pat::tag_VECTORpat: {
#line 786 "../../prop-src/matchcom.pcc"
          
          int low   = length(_VECTORpat(pat)->elements);
          int high  = (_VECTORpat(pat)->head_flex || _VECTORpat(pat)->tail_flex) ? INT_MAX : low;
          int start = _VECTORpat(pat)->head_flex ? (INT_MAX - length(_VECTORpat(pat)->elements)) : 0;
          Match p1 = trans( _VECTORpat(pat)->elements, start, pos, neg, yes, no);
          Match p2 = trans( _VECTORpat(pat)->array, pos, neg, (neg ? no : p1),(neg ? p1 : no));
          Match p3 = trans( _VECTORpat(pat)->len, pos, neg, (neg ? no : p2),(neg ? p3 : no));
          return RANGEmatch( pos, ARROWexp( pat->selector,"len()"), low, high,
                            (neg ? no : p3), (neg ? p3 : no));
          
#line 795 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_GUARDpat: {
#line 744 "../../prop-src/matchcom.pcc"
          
          Match m = trans( _GUARDpat(pat)->_1, pos, neg, yes, no);
          return GUARDmatch(_GUARDpat(pat)->_2, neg ? no : m, neg ? m : no);
          
#line 747 "../../prop-src/matchcom.pcc"
          } break;
        case a_Pat::tag_LOGICALpat: {
          switch (_LOGICALpat(pat)->_1) {
            case NOTpat: {
#line 824 "../../prop-src/matchcom.pcc"
             return trans( _LOGICALpat(pat)->_2, pos,! neg, yes, no); 
#line 824 "../../prop-src/matchcom.pcc"
              } break;
            case ANDpat: {
#line 826 "../../prop-src/matchcom.pcc"
              
              return neg ? merge( trans( _LOGICALpat(pat)->_2, pos, neg, yes, no), trans( _LOGICALpat(pat)->_3, pos, neg, yes, no))
                         : trans( _LOGICALpat(pat)->_2, pos, neg, trans(_LOGICALpat(pat)->_3, pos, neg, yes, no), no);
              
#line 829 "../../prop-src/matchcom.pcc"
              } break;
            case ORpat: {
#line 831 "../../prop-src/matchcom.pcc"
             return neg ? trans( _LOGICALpat(pat)->_2, pos, neg, trans(_LOGICALpat(pat)->_3, pos, neg, yes, no), no)
              : merge( trans( _LOGICALpat(pat)->_2, pos, neg, yes, no), trans( _LOGICALpat(pat)->_3, pos, neg, yes, no));
              
#line 833 "../../prop-src/matchcom.pcc"
              } break;
            case EQUIVpat: {
#line 837 "../../prop-src/matchcom.pcc"
              
              pat = LOGICALpat( ORpat,
                       LOGICALpat( ANDpat, _LOGICALpat(pat)->_2, _LOGICALpat(pat)->_3),
                       LOGICALpat( ANDpat, LOGICALpat( NOTpat, _LOGICALpat(pat)->_2, NOpat),
                                          LOGICALpat( NOTpat, _LOGICALpat(pat)->_3, NOpat)));
              
#line 842 "../../prop-src/matchcom.pcc"
              } break;
            case XORpat: {
#line 844 "../../prop-src/matchcom.pcc"
              
              pat = LOGICALpat( ORpat,
                       LOGICALpat( ANDpat, _LOGICALpat(pat)->_2, LOGICALpat( NOTpat, _LOGICALpat(pat)->_3, NOpat)),
                       LOGICALpat( ANDpat, LOGICALpat( NOTpat, _LOGICALpat(pat)->_2, NOpat), _LOGICALpat(pat)->_3));
              
#line 848 "../../prop-src/matchcom.pcc"
              } break;
            default: {
#line 835 "../../prop-src/matchcom.pcc"
             pat = LOGICALpat( ORpat, LOGICALpat( NOTpat, _LOGICALpat(pat)->_2, NOpat), _LOGICALpat(pat)->_3); 
#line 835 "../../prop-src/matchcom.pcc"
              } break;
          }
          } break;
        case a_Pat::tag_MARKEDpat: {
#line 737 "../../prop-src/matchcom.pcc"
         pat = _MARKEDpat(pat)->_2; 
#line 737 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L19; } break;
      }
    } else { goto L18; }
  }
}
#line 871 "../../prop-src/matchcom.pcc"
#line 871 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Translate a pattern list into a matching tree using ranking function.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::trans
   (Pats ps, Pos pos, Bool neg, Match yes, Match no, int rank[])
{
  Pat Ps[256];
  int i = 0;
  for_each (Pat, p, ps)
    Ps[i++] = p;
  int n = i;
  Match m = yes;
  for (i = n - 1; i >= 0; i--)
     m = trans( Ps[ rank[i]], POSint( i, pos), neg, m, no);
  return m;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Translate a pattern list into a matching tree.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::trans
   (Pats ps, int i, Pos pos, Bool neg, Match yes, Match no)
{
  
#line 903 "../../prop-src/matchcom.pcc"
#line 909 "../../prop-src/matchcom.pcc"
{
  if (ps) {
#line 906 "../../prop-src/matchcom.pcc"
    
    return trans( ps->_1, POSint( i, pos), neg,
              trans( ps->_2, i+1, pos, neg, yes, no), no);
    
#line 909 "../../prop-src/matchcom.pcc"
  } else {
#line 905 "../../prop-src/matchcom.pcc"
   return yes; 
#line 905 "../../prop-src/matchcom.pcc"
  }
}
#line 910 "../../prop-src/matchcom.pcc"
#line 910 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Translate a labeled pattern list into a matching tree.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::trans
   (LabPats ps, Pos pos, Bool neg, Match yes, Match no)
{
  
#line 922 "../../prop-src/matchcom.pcc"
#line 928 "../../prop-src/matchcom.pcc"
{
  if (ps) {
#line 925 "../../prop-src/matchcom.pcc"
    
    return trans( ps->_1.pat, POSlabel( ps->_1.label, pos), neg,
               trans( ps->_2, pos, neg, yes, no), no);
    
#line 928 "../../prop-src/matchcom.pcc"
  } else {
#line 924 "../../prop-src/matchcom.pcc"
   return yes; 
#line 924 "../../prop-src/matchcom.pcc"
  }
}
#line 929 "../../prop-src/matchcom.pcc"
#line 929 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Get the position list of a matching tree node.
//
///////////////////////////////////////////////////////////////////////////////

#line 938 "../../prop-src/matchcom.pcc"
#line 944 "../../prop-src/matchcom.pcc"
Pos get_pos (Match x_1);
Pos get_pos (Match x_1)
{
  if (boxed(x_1)) {
    switch (x_1->tag__) {
      case a_Match::tag_LITERALmatch: {
#line 938 "../../prop-src/matchcom.pcc"
       return _LITERALmatch(x_1)->_1; 
#line 938 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_RANGEmatch: {
#line 939 "../../prop-src/matchcom.pcc"
       return _RANGEmatch(x_1)->_1; 
#line 939 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_CONSmatch: {
#line 940 "../../prop-src/matchcom.pcc"
       return _CONSmatch(x_1)->_1; 
#line 940 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_SUCCESSmatch:
      case a_Match::tag_SUCCESSESmatch:
      case a_Match::tag_COSTmatch: {
#line 942 "../../prop-src/matchcom.pcc"
       return (Pos)POSinfinity; 
#line 942 "../../prop-src/matchcom.pcc"
        } break;
      default: {
        L25:; 
#line 943 "../../prop-src/matchcom.pcc"
       return POSzero; 
#line 943 "../../prop-src/matchcom.pcc"
        } break;
    }
  } else { goto L25; }
}
#line 944 "../../prop-src/matchcom.pcc"
#line 944 "../../prop-src/matchcom.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Position list comparison result.
//
///////////////////////////////////////////////////////////////////////////////

#line 952 "../../prop-src/matchcom.pcc"
#line 952 "../../prop-src/matchcom.pcc"
enum CompareResult {
  LESS = 0, SAME = 1, MORE = 2, 
  NEITHER = 3
};




#line 952 "../../prop-src/matchcom.pcc"
#line 952 "../../prop-src/matchcom.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Compare two position lists lexicographically.
//
///////////////////////////////////////////////////////////////////////////////

CompareResult compare_pos(Pos a, Pos b)
{
  Pos u, v;
  
#line 963 "../../prop-src/matchcom.pcc"
#line 1000 "../../prop-src/matchcom.pcc"
{
  if (
#line 965 "../../prop-src/matchcom.pcc"
  (a == b)
#line 965 "../../prop-src/matchcom.pcc"
) {
    
#line 965 "../../prop-src/matchcom.pcc"
   return SAME; 
#line 965 "../../prop-src/matchcom.pcc"
  } else {
    
    if (boxed(a)) {
      switch (a->tag__) {
        case a_Pos::tag_POSint: {
          if (boxed(b)) {
            switch (b->tag__) {
              case a_Pos::tag_POSint: {
#line 977 "../../prop-src/matchcom.pcc"
                
                CompareResult r = compare_pos(_POSint(a)->_2,_POSint(b)->_2);
                if (r != SAME) return r;
                if (_POSint(a)->_1 == _POSint(b)->_1) return SAME;
                if (_POSint(a)->_1 <  _POSint(b)->_1)  return LESS;
                return MORE;
                
#line 983 "../../prop-src/matchcom.pcc"
                } break;
              case a_Pos::tag_POSlabel: {
#line 970 "../../prop-src/matchcom.pcc"
               u = _POSint(a)->_2; v = _POSlabel(b)->_2; 
#line 970 "../../prop-src/matchcom.pcc"
                } break;
              default: {
#line 971 "../../prop-src/matchcom.pcc"
               u = _POSint(a)->_2; v = _POSadaptive(b)->_3; 
#line 971 "../../prop-src/matchcom.pcc"
                } break;
            }
          } else {
            if (b) {
              
              L26:; 
#line 969 "../../prop-src/matchcom.pcc"
             return LESS; 
#line 969 "../../prop-src/matchcom.pcc"
            } else {
              
              L27:; 
#line 967 "../../prop-src/matchcom.pcc"
             return MORE; 
#line 967 "../../prop-src/matchcom.pcc"
            }
          }
          } break;
        case a_Pos::tag_POSlabel: {
          if (boxed(b)) {
            switch (b->tag__) {
              case a_Pos::tag_POSint: {
#line 972 "../../prop-src/matchcom.pcc"
               u = _POSlabel(a)->_2; v = _POSint(b)->_2; 
#line 972 "../../prop-src/matchcom.pcc"
                } break;
              case a_Pos::tag_POSlabel: {
#line 985 "../../prop-src/matchcom.pcc"
                
                CompareResult r = compare_pos(_POSlabel(a)->_2,_POSlabel(b)->_2);
                if (r != SAME) return r;
                int s = strcmp(_POSlabel(a)->_1,_POSlabel(b)->_1);
                if (s == 0) return SAME;
                if (s < 0)  return LESS;
                return MORE;
                
#line 992 "../../prop-src/matchcom.pcc"
                } break;
              default: {
#line 973 "../../prop-src/matchcom.pcc"
               u = _POSlabel(a)->_2; v = _POSadaptive(b)->_3; 
#line 973 "../../prop-src/matchcom.pcc"
                } break;
            }
          } else {
            if (b) {
               goto L26; } else {
               goto L27; }
          }
          } break;
        default: {
          if (boxed(b)) {
            switch (b->tag__) {
              case a_Pos::tag_POSint: {
#line 974 "../../prop-src/matchcom.pcc"
               u = _POSint(b)->_2; v = _POSadaptive(a)->_3; 
#line 974 "../../prop-src/matchcom.pcc"
                } break;
              case a_Pos::tag_POSlabel: {
#line 975 "../../prop-src/matchcom.pcc"
               u = _POSlabel(b)->_2; v = _POSadaptive(a)->_3; 
#line 975 "../../prop-src/matchcom.pcc"
                } break;
              default: {
#line 994 "../../prop-src/matchcom.pcc"
                
                CompareResult r = compare_pos(_POSadaptive(a)->_3,_POSadaptive(b)->_3);
                if (r != SAME) return r;
                if (_POSadaptive(a)->_2[_POSadaptive(a)->_1] == _POSadaptive(b)->_2[_POSadaptive(b)->_1]) return SAME;
                if (_POSadaptive(a)->_2[_POSadaptive(a)->_1] <  _POSadaptive(b)->_2[_POSadaptive(b)->_1]) return LESS;
                return MORE;
                
#line 1000 "../../prop-src/matchcom.pcc"
                } break;
            }
          } else {
            if (b) {
               goto L26; } else {
               goto L27; }
          }
          } break;
      }
    } else {
      if (a) {
        
        if (boxed(b)) {
          L28:; 
#line 968 "../../prop-src/matchcom.pcc"
         return MORE; 
#line 968 "../../prop-src/matchcom.pcc"
        } else {
          if (b) {
             goto L28; } else {
             goto L27; }
        }
      } else {
        
#line 966 "../../prop-src/matchcom.pcc"
       return LESS; 
#line 966 "../../prop-src/matchcom.pcc"
      }
    }
  }
}
#line 1001 "../../prop-src/matchcom.pcc"
#line 1001 "../../prop-src/matchcom.pcc"


  CompareResult r = compare_pos(u,v);
  if (r != SAME) return r;
  return NEITHER;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Compare two position lists lexicographically.
//
///////////////////////////////////////////////////////////////////////////////

Bool pos_equal( HashTable::Key p, HashTable::Key q)
{  return compare_pos((Pos)p, (Pos)q) == SAME; }

///////////////////////////////////////////////////////////////////////////////
//
//  Compare two literals.
//
///////////////////////////////////////////////////////////////////////////////

#line 1023 "../../prop-src/matchcom.pcc"
#line 1032 "../../prop-src/matchcom.pcc"
int compare_literals (Literal x_1, Literal x_2);
int compare_literals (Literal x_1, Literal x_2)
{
  switch (x_1->tag__) {
    case a_Literal::tag_INTlit: {
      switch (x_2->tag__) {
        case a_Literal::tag_INTlit: {
#line 1023 "../../prop-src/matchcom.pcc"
         return _INTlit(x_1)->INTlit - _INTlit(x_2)->INTlit; 
#line 1023 "../../prop-src/matchcom.pcc"
          } break;
        default: {
          L29:; 
#line 1031 "../../prop-src/matchcom.pcc"
         return 1; 
#line 1031 "../../prop-src/matchcom.pcc"
          } break;
      }
      } break;
    case a_Literal::tag_BOOLlit: {
      switch (x_2->tag__) {
        case a_Literal::tag_BOOLlit: {
#line 1026 "../../prop-src/matchcom.pcc"
         return _BOOLlit(x_1)->BOOLlit - _BOOLlit(x_2)->BOOLlit; 
#line 1026 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L29; } break;
      }
      } break;
    case a_Literal::tag_CHARlit: {
      switch (x_2->tag__) {
        case a_Literal::tag_CHARlit: {
#line 1025 "../../prop-src/matchcom.pcc"
         return (int)_CHARlit(x_1)->CHARlit - (int)_CHARlit(x_2)->CHARlit; 
#line 1025 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L29; } break;
      }
      } break;
    case a_Literal::tag_REALlit: {
      switch (x_2->tag__) {
        case a_Literal::tag_REALlit: {
#line 1024 "../../prop-src/matchcom.pcc"
         return _REALlit(x_1)->REALlit < _REALlit(x_2)->REALlit ? -1 : (_REALlit(x_1)->REALlit > _REALlit(x_2)->REALlit ? 1 : 0); 
#line 1024 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L29; } break;
      }
      } break;
    case a_Literal::tag_STRINGlit: {
      switch (x_2->tag__) {
        case a_Literal::tag_STRINGlit: {
#line 1027 "../../prop-src/matchcom.pcc"
         return strcmp(_STRINGlit(x_1)->STRINGlit,_STRINGlit(x_2)->STRINGlit); 
#line 1027 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L29; } break;
      }
      } break;
    case a_Literal::tag_REGEXPlit: {
      switch (x_2->tag__) {
        case a_Literal::tag_REGEXPlit: {
#line 1028 "../../prop-src/matchcom.pcc"
         return strcmp(_REGEXPlit(x_1)->REGEXPlit,_REGEXPlit(x_2)->REGEXPlit); 
#line 1028 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L29; } break;
      }
      } break;
    case a_Literal::tag_QUARKlit: {
      switch (x_2->tag__) {
        case a_Literal::tag_QUARKlit: {
#line 1029 "../../prop-src/matchcom.pcc"
         return strcmp(_QUARKlit(x_1)->QUARKlit,_QUARKlit(x_2)->QUARKlit); 
#line 1029 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L29; } break;
      }
      } break;
    default: {
      switch (x_2->tag__) {
        case a_Literal::tag_BIGINTlit: {
#line 1030 "../../prop-src/matchcom.pcc"
         return strcmp(_BIGINTlit(x_1)->BIGINTlit,_BIGINTlit(x_2)->BIGINTlit); 
#line 1030 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L29; } break;
      }
      } break;
  }
}
#line 1032 "../../prop-src/matchcom.pcc"
#line 1032 "../../prop-src/matchcom.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Compare two expressions.
//
///////////////////////////////////////////////////////////////////////////////

Bool equal( Exp a, Exp b)
{
  
#line 1042 "../../prop-src/matchcom.pcc"
#line 1079 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (
#line 1044 "../../prop-src/matchcom.pcc"
    (a == b)
#line 1044 "../../prop-src/matchcom.pcc"
) {
      
#line 1044 "../../prop-src/matchcom.pcc"
     return true; 
#line 1044 "../../prop-src/matchcom.pcc"
    } else {
      
      if (a) {
        switch (a->tag__) {
          case a_Exp::tag_LITERALexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_LITERALexp: {
#line 1045 "../../prop-src/matchcom.pcc"
                 return compare_literals(_LITERALexp(a)->LITERALexp,_LITERALexp(b)->LITERALexp)==0; 
#line 1045 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: {
                  L31:; 
#line 1078 "../../prop-src/matchcom.pcc"
                 b = _MARKEDexp(b)->_2; 
#line 1078 "../../prop-src/matchcom.pcc"
                  } break;
                default: {
                  L32:; 
#line 1079 "../../prop-src/matchcom.pcc"
                 return false; 
#line 1079 "../../prop-src/matchcom.pcc"
                  } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_IDexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_IDexp: {
#line 1046 "../../prop-src/matchcom.pcc"
                 return _IDexp(a)->IDexp == _IDexp(b)->IDexp; 
#line 1046 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_RELexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_RELexp: {
#line 1047 "../../prop-src/matchcom.pcc"
                 return same_selectors || _RELexp(a)->RELexp == _RELexp(b)->RELexp; 
#line 1047 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_DOTexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_DOTexp: {
#line 1048 "../../prop-src/matchcom.pcc"
                 return _DOTexp(a)->_2 == _DOTexp(b)->_2 && equal(_DOTexp(a)->_1,_DOTexp(b)->_1); 
#line 1048 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_SELECTORexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_SELECTORexp: {
#line 1050 "../../prop-src/matchcom.pcc"
                 return _SELECTORexp(a)->_2 == _SELECTORexp(b)->_2 && equal(_SELECTORexp(a)->_1,_SELECTORexp(b)->_1); 
#line 1050 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_DEREFexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_DEREFexp: {
#line 1051 "../../prop-src/matchcom.pcc"
                 return equal(_DEREFexp(a)->DEREFexp,_DEREFexp(b)->DEREFexp); 
#line 1051 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_ARROWexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_ARROWexp: {
#line 1052 "../../prop-src/matchcom.pcc"
                 return _ARROWexp(a)->_2 == _ARROWexp(b)->_2 && equal(_ARROWexp(a)->_1,_ARROWexp(b)->_1); 
#line 1052 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_INDEXexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_INDEXexp: {
#line 1053 "../../prop-src/matchcom.pcc"
                 return equal(_INDEXexp(a)->_1,_INDEXexp(b)->_1) && equal(_INDEXexp(a)->_2,_INDEXexp(b)->_2); 
#line 1053 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_BINOPexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_BINOPexp: {
#line 1055 "../../prop-src/matchcom.pcc"
                 return strcmp(_BINOPexp(a)->_1,_BINOPexp(b)->_1) == 0 && equal(_BINOPexp(a)->_2,_BINOPexp(b)->_2) && equal(_BINOPexp(a)->_3,_BINOPexp(b)->_3); 
#line 1055 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_PREFIXexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_PREFIXexp: {
#line 1056 "../../prop-src/matchcom.pcc"
                 return !strcmp(_PREFIXexp(a)->_1,_PREFIXexp(b)->_1) && equal(_PREFIXexp(a)->_2,_PREFIXexp(b)->_2);
#line 1056 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_POSTFIXexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_POSTFIXexp: {
#line 1057 "../../prop-src/matchcom.pcc"
                 return !strcmp(_POSTFIXexp(a)->_1,_POSTFIXexp(b)->_1) && equal(_POSTFIXexp(a)->_2,_POSTFIXexp(b)->_2);
#line 1057 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_APPexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_APPexp: {
#line 1058 "../../prop-src/matchcom.pcc"
                 return equal(_APPexp(a)->_1,_APPexp(b)->_1) && equal(_APPexp(a)->_2,_APPexp(b)->_2); 
#line 1058 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_ASSIGNexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_ASSIGNexp: {
#line 1059 "../../prop-src/matchcom.pcc"
                 return equal(_ASSIGNexp(a)->_1,_ASSIGNexp(b)->_1) && equal(_ASSIGNexp(a)->_2,_ASSIGNexp(b)->_2); 
#line 1059 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_IFexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_IFexp: {
#line 1061 "../../prop-src/matchcom.pcc"
                 return equal(_IFexp(a)->_1,_IFexp(b)->_1) && equal(_IFexp(a)->_2,_IFexp(b)->_2) && equal(_IFexp(a)->_3,_IFexp(b)->_3); 
#line 1061 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_TUPLEexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_TUPLEexp: {
#line 1062 "../../prop-src/matchcom.pcc"
                 return equal(_TUPLEexp(a)->TUPLEexp,_TUPLEexp(b)->TUPLEexp); 
#line 1062 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_RECORDexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_RECORDexp: {
#line 1063 "../../prop-src/matchcom.pcc"
                 return equal(_RECORDexp(a)->RECORDexp,_RECORDexp(b)->RECORDexp); 
#line 1063 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_LISTexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_LISTexp: {
#line 1066 "../../prop-src/matchcom.pcc"
                 return _LISTexp(a)->_1 == _LISTexp(b)->_1 && equal(_LISTexp(a)->_3,_LISTexp(b)->_3) && equal(_LISTexp(a)->_4,_LISTexp(b)->_4); 
#line 1066 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_CONSexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_CONSexp: {
#line 1067 "../../prop-src/matchcom.pcc"
                 return _CONSexp(a)->_1 == _CONSexp(b)->_1 && equal(_CONSexp(a)->_2,_CONSexp(b)->_2) && equal(_CONSexp(a)->_3,_CONSexp(b)->_3); 
#line 1067 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_EQexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_EQexp: {
#line 1068 "../../prop-src/matchcom.pcc"
                 return equal(_EQexp(a)->_2,_EQexp(b)->_2) && equal(_EQexp(a)->_3,_EQexp(b)->_3); 
#line 1068 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_UNIFYexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_UNIFYexp: {
#line 1069 "../../prop-src/matchcom.pcc"
                 return equal(_UNIFYexp(a)->_2,_UNIFYexp(b)->_2) && equal(_UNIFYexp(a)->_3,_UNIFYexp(b)->_3); 
#line 1069 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_LTexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_LTexp: {
#line 1070 "../../prop-src/matchcom.pcc"
                 return equal(_LTexp(a)->_2,_LTexp(b)->_2) && equal(_LTexp(a)->_3,_LTexp(b)->_3); 
#line 1070 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_HASHexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_HASHexp: {
#line 1071 "../../prop-src/matchcom.pcc"
                 a = _HASHexp(a)->_2; b = _HASHexp(b)->_2; 
#line 1071 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_THISCOSTexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_THISCOSTexp: {
#line 1072 "../../prop-src/matchcom.pcc"
                 return true; 
#line 1072 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_COSTexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_COSTexp: {
#line 1073 "../../prop-src/matchcom.pcc"
                 return _COSTexp(a)->COSTexp == _COSTexp(b)->COSTexp; 
#line 1073 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_THISSYNexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_THISSYNexp: {
#line 1076 "../../prop-src/matchcom.pcc"
                 return _THISSYNexp(a)->_1 == _THISSYNexp(b)->_1; 
#line 1076 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_SYNexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_SYNexp: {
#line 1074 "../../prop-src/matchcom.pcc"
                 return _SYNexp(a)->_1 == _SYNexp(b)->_1 && _SYNexp(a)->_2 == _SYNexp(b)->_2; 
#line 1074 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_SENDexp: {
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_SENDexp: {
#line 1064 "../../prop-src/matchcom.pcc"
                 return _SENDexp(a)->_1 == _SENDexp(b)->_1 && equal(_SENDexp(a)->_2,_SENDexp(b)->_2); 
#line 1064 "../../prop-src/matchcom.pcc"
                  } break;
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
          case a_Exp::tag_MARKEDexp: {
#line 1077 "../../prop-src/matchcom.pcc"
           a = _MARKEDexp(a)->_2; 
#line 1077 "../../prop-src/matchcom.pcc"
            } break;
          default: {
            L33:; 
            if (b) {
              switch (b->tag__) {
                case a_Exp::tag_MARKEDexp: { goto L31; } break;
                default: { goto L32; } break;
              }
            } else { goto L32; }
            } break;
        }
      } else { goto L33; }
    }
  }
}
#line 1080 "../../prop-src/matchcom.pcc"
#line 1080 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Equality between two expression lists
//
///////////////////////////////////////////////////////////////////////////////

Bool equal( Exps a, Exps b)
{
  
#line 1091 "../../prop-src/matchcom.pcc"
#line 1094 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (a) {
      if (b) {
#line 1094 "../../prop-src/matchcom.pcc"
       if (! equal(a->_1, b->_1)) return false; a = a->_2; b = b->_2; 
#line 1094 "../../prop-src/matchcom.pcc"
      } else { goto L34; }
    } else { goto L34; }
  }
  L34:;
}
#line 1095 "../../prop-src/matchcom.pcc"
#line 1095 "../../prop-src/matchcom.pcc"

  return a == 
#line 1096 "../../prop-src/matchcom.pcc"
#line 1096 "../../prop-src/matchcom.pcc"
nil_1_
#line 1096 "../../prop-src/matchcom.pcc"
#line 1096 "../../prop-src/matchcom.pcc"
 && b == 
#line 1096 "../../prop-src/matchcom.pcc"
#line 1096 "../../prop-src/matchcom.pcc"
nil_1_
#line 1096 "../../prop-src/matchcom.pcc"
#line 1096 "../../prop-src/matchcom.pcc"
;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Equality between two labeled expression lists
//
///////////////////////////////////////////////////////////////////////////////

Bool equal( LabExps a, LabExps b)
{
  
#line 1107 "../../prop-src/matchcom.pcc"
#line 1110 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (a) {
      if (b) {
#line 1110 "../../prop-src/matchcom.pcc"
      if (! equal(a->_1.exp, b->_1.exp)) return false; a = a->_2; b = b->_2; 
#line 1110 "../../prop-src/matchcom.pcc"
      } else { goto L35; }
    } else { goto L35; }
  }
  L35:;
}
#line 1111 "../../prop-src/matchcom.pcc"
#line 1111 "../../prop-src/matchcom.pcc"

  return a == 
#line 1112 "../../prop-src/matchcom.pcc"
#line 1112 "../../prop-src/matchcom.pcc"
nil_1_
#line 1112 "../../prop-src/matchcom.pcc"
#line 1112 "../../prop-src/matchcom.pcc"
 && b == 
#line 1112 "../../prop-src/matchcom.pcc"
#line 1112 "../../prop-src/matchcom.pcc"
nil_1_
#line 1112 "../../prop-src/matchcom.pcc"
#line 1112 "../../prop-src/matchcom.pcc"
;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Check to see if we have a regular expression.
//
///////////////////////////////////////////////////////////////////////////////

Bool has_regexp( int n, Literal l[])
{
  for (int i = n - 1; i >= 0; i--)
  { 
#line 1124 "../../prop-src/matchcom.pcc"
#line 1124 "../../prop-src/matchcom.pcc"
{
  Literal _V5 = l[i];
  switch (_V5->tag__) {
    case a_Literal::tag_REGEXPlit: {
#line 1124 "../../prop-src/matchcom.pcc"
     return true; 
#line 1124 "../../prop-src/matchcom.pcc"
      } break;
    default: {
#line 1124 "../../prop-src/matchcom.pcc"
     /* skip */ 
#line 1124 "../../prop-src/matchcom.pcc"
      } break;
  }
}
#line 1124 "../../prop-src/matchcom.pcc"
#line 1124 "../../prop-src/matchcom.pcc"
 }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Convert all string literals into regular expression literals.
//
///////////////////////////////////////////////////////////////////////////////

void convert_regexp( int n, Literal l[])
{
  for (int i = n-1; i >= 0; i--)
  {
    
#line 1138 "../../prop-src/matchcom.pcc"
#line 1141 "../../prop-src/matchcom.pcc"
{
  Literal _V6 = l[i];
  switch (_V6->tag__) {
    case a_Literal::tag_STRINGlit: {
#line 1140 "../../prop-src/matchcom.pcc"
     l[i] = REGEXPlit( convert_regexp(_STRINGlit(_V6)->STRINGlit)); 
#line 1140 "../../prop-src/matchcom.pcc"
      } break;
    default: {
#line 1141 "../../prop-src/matchcom.pcc"
     /* skip */ 
#line 1141 "../../prop-src/matchcom.pcc"
      } break;
  }
}
#line 1142 "../../prop-src/matchcom.pcc"
#line 1142 "../../prop-src/matchcom.pcc"

  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Compose two matching trees.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::compose( Match a, Match b)
{
  
#line 1154 "../../prop-src/matchcom.pcc"
#line 1214 "../../prop-src/matchcom.pcc"
{
  if (boxed(a)) {
    switch (a->tag__) {
      case a_Match::tag_SUCCESSESmatch: {
        if (boxed(b)) {
          switch (b->tag__) {
            case a_Match::tag_SUCCESSESmatch: {
#line 1158 "../../prop-src/matchcom.pcc"
              
              BitSet * c = new (mem_pool, _SUCCESSESmatch(a)->_1) BitSet;
              c->Union( *_SUCCESSESmatch(a)->_2, *_SUCCESSESmatch(b)->_2);
              return SUCCESSESmatch( _SUCCESSESmatch(a)->_1, c, _SUCCESSESmatch(a)->_3);
              
#line 1162 "../../prop-src/matchcom.pcc"
              } break;
            default: {
              L36:; 
#line 1214 "../../prop-src/matchcom.pcc"
             /* skip */ 
#line 1214 "../../prop-src/matchcom.pcc"
              } break;
          }
        } else { goto L36; }
        } break;
      case a_Match::tag_COSTmatch: {
        if (boxed(b)) {
          switch (b->tag__) {
            case a_Match::tag_COSTmatch: {
#line 1165 "../../prop-src/matchcom.pcc"
              
              register BitSet * set = new (mem_pool, _COSTmatch(a)->_1) BitSet;
              set->Union (*_COSTmatch(a)->_3, *_COSTmatch(b)->_3);
              register int min_cost = MAX_COST;
              register int r;
              
              // Find the minimal known cost
              
              for (r = 0; r < _COSTmatch(a)->_1; r++)
              {
                if (set->contains(r))
                {
                  
#line 1177 "../../prop-src/matchcom.pcc"
#line 1182 "../../prop-src/matchcom.pcc"
              {
                Cost _V7 = _COSTmatch(a)->_2[r];
                if (_V7) {
                  if (_V7->tag__) {
                    
                    if (
#line 1180 "../../prop-src/matchcom.pcc"
                    (_INTcost(_V7)->INTcost < min_cost)
#line 1180 "../../prop-src/matchcom.pcc"
) {
                      
#line 1180 "../../prop-src/matchcom.pcc"
                     min_cost = _INTcost(_V7)->INTcost; 
#line 1180 "../../prop-src/matchcom.pcc"
                    } else {
                      
                      L37:; }
                  } else {
                     goto L37; }
                } else {
#line 1179 "../../prop-src/matchcom.pcc"
                 min_cost = 0; 
#line 1179 "../../prop-src/matchcom.pcc"
                }
              }
#line 1182 "../../prop-src/matchcom.pcc"
#line 1182 "../../prop-src/matchcom.pcc"
              
              }
              }
              
              // Prune away all the rules with higher or equal cost than min_cost.
              
              Bool found = false;
              for (r = 0; r < _COSTmatch(a)->_1; r++)
              {
              if (set->contains(r))
              {
                
#line 1193 "../../prop-src/matchcom.pcc"
#line 1208 "../../prop-src/matchcom.pcc"
              {
                Cost _V8 = _COSTmatch(a)->_2[r];
                if (_V8) {
                  if (_V8->tag__) {
                    
#line 1202 "../../prop-src/matchcom.pcc"
                    
                    if (_INTcost(_V8)->INTcost > min_cost || found)
                      set->remove(r);
                    found = true;
                    
#line 1206 "../../prop-src/matchcom.pcc"
                  } else {
                    }
                } else {
#line 1196 "../../prop-src/matchcom.pcc"
                  
                  if (! found)
                    set->remove(r);
                  found = true;
                  
#line 1200 "../../prop-src/matchcom.pcc"
                }
              }
#line 1208 "../../prop-src/matchcom.pcc"
#line 1208 "../../prop-src/matchcom.pcc"
              
              }
              }
              
              return COSTmatch( _COSTmatch(a)->_1, _COSTmatch(a)->_2, set, _COSTmatch(a)->_4);
              
#line 1213 "../../prop-src/matchcom.pcc"
              } break;
            default: { goto L36; } break;
          }
        } else { goto L36; }
        } break;
      default: { goto L36; } break;
    }
  } else { goto L36; }
}
#line 1215 "../../prop-src/matchcom.pcc"
#line 1215 "../../prop-src/matchcom.pcc"


  
#line 1217 "../../prop-src/matchcom.pcc"
#line 1243 "../../prop-src/matchcom.pcc"
{
  if (boxed(a)) {
    switch (a->tag__) {
      case a_Match::tag_SUCCESSmatch: {
#line 1222 "../../prop-src/matchcom.pcc"
       return a; 
#line 1222 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_GUARDmatch: {
#line 1225 "../../prop-src/matchcom.pcc"
       return GUARDmatch( _GUARDmatch(a)->_1, merge( _GUARDmatch(a)->_2, b), merge( _GUARDmatch(a)->_3, b)); 
#line 1225 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_LITERALmatch: {
#line 1227 "../../prop-src/matchcom.pcc"
        
        Match * br = Matches(_LITERALmatch(a)->_4);
        for (int i = _LITERALmatch(a)->_4 - 1; i >= 0; i--)
          br[i] = merge(_LITERALmatch(a)->_5[i],b);
        return LITERALmatch( _LITERALmatch(a)->_1, _LITERALmatch(a)->_2, _LITERALmatch(a)->_3, _LITERALmatch(a)->_4, br, merge( _LITERALmatch(a)->_6, b));
        
#line 1232 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_RANGEmatch: {
#line 1241 "../../prop-src/matchcom.pcc"
       return RANGEmatch( _RANGEmatch(a)->_1, _RANGEmatch(a)->_2, _RANGEmatch(a)->_3, _RANGEmatch(a)->_4, merge( _RANGEmatch(a)->_5, b), merge( _RANGEmatch(a)->_6, b)); 
#line 1241 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_CONSmatch: {
#line 1234 "../../prop-src/matchcom.pcc"
        
        Match * br = Matches(_CONSmatch(a)->_5);
        for (int i = _CONSmatch(a)->_5 - 1; i >= 0; i--)
          br[i] = merge(_CONSmatch(a)->_6[i],b);
        return CONSmatch( _CONSmatch(a)->_1, _CONSmatch(a)->_2, _CONSmatch(a)->_3, _CONSmatch(a)->_4, _CONSmatch(a)->_5, br, merge( _CONSmatch(a)->_7, b));
        
#line 1239 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_BACKEDGEmatch: {
#line 1221 "../../prop-src/matchcom.pcc"
       return a; 
#line 1221 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_SUCCESSESmatch:
      case a_Match::tag_COSTmatch: {
#line 1223 "../../prop-src/matchcom.pcc"
       return compose(b,a); 
#line 1223 "../../prop-src/matchcom.pcc"
        } break;
      default: {
#line 1243 "../../prop-src/matchcom.pcc"
       bug("MatchCompiler::compose: %m, %m",a,b); return a; 
#line 1243 "../../prop-src/matchcom.pcc"
        } break;
    }
  } else {
    if (a) {
      
#line 1220 "../../prop-src/matchcom.pcc"
     return a; 
#line 1220 "../../prop-src/matchcom.pcc"
    } else {
      
#line 1219 "../../prop-src/matchcom.pcc"
     return b; 
#line 1219 "../../prop-src/matchcom.pcc"
    }
  }
}
#line 1244 "../../prop-src/matchcom.pcc"
#line 1244 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Merge two matching trees.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::merge( Match a, Match b)
{
  
#line 1255 "../../prop-src/matchcom.pcc"
#line 1266 "../../prop-src/matchcom.pcc"
{
  if (boxed(a)) {
    switch (a->tag__) {
      case a_Match::tag_SUCCESSmatch: {
        if (boxed(b)) {
          L38:; 
#line 1259 "../../prop-src/matchcom.pcc"
         return a; 
#line 1259 "../../prop-src/matchcom.pcc"
        } else {
          if (b) {
             goto L38; } else {
            
            L39:; 
#line 1258 "../../prop-src/matchcom.pcc"
           return a; 
#line 1258 "../../prop-src/matchcom.pcc"
          }
        }
        } break;
      case a_Match::tag_SUCCESSESmatch:
      case a_Match::tag_COSTmatch: {
        if (boxed(b)) {
          L40:; 
#line 1264 "../../prop-src/matchcom.pcc"
         return compose(a,b); 
#line 1264 "../../prop-src/matchcom.pcc"
        } else {
          if (b) {
             goto L40; } else {
             goto L39; }
        }
        } break;
      default: {
        L41:; 
        if (boxed(b)) {
          switch (b->tag__) {
            case a_Match::tag_SUCCESSmatch:
            case a_Match::tag_SUCCESSESmatch:
            case a_Match::tag_COSTmatch: { goto L40; } break;
            default: {
              L42:; } break;
          }
        } else {
          if (b) {
             goto L42; } else {
             goto L39; }
        }
        } break;
    }
  } else {
    if (a) {
       goto L41; } else {
      
#line 1257 "../../prop-src/matchcom.pcc"
     return b; 
#line 1257 "../../prop-src/matchcom.pcc"
    }
  }
}
#line 1266 "../../prop-src/matchcom.pcc"
#line 1266 "../../prop-src/matchcom.pcc"


  
#line 1268 "../../prop-src/matchcom.pcc"
#line 1387 "../../prop-src/matchcom.pcc"
{
  CompareResult _V9 = compare_pos(get_pos(a),get_pos(b));
  switch (_V9) {
    case LESS: {
      if (boxed(a)) {
        switch (a->tag__) {
          case a_Match::tag_GUARDmatch: {
#line 1356 "../../prop-src/matchcom.pcc"
           return GUARDmatch( _GUARDmatch(a)->_1, merge( _GUARDmatch(a)->_2, b), merge( _GUARDmatch(a)->_3, b)); 
#line 1356 "../../prop-src/matchcom.pcc"
            } break;
          case a_Match::tag_LITERALmatch: {
#line 1358 "../../prop-src/matchcom.pcc"
            
            Match * br = Matches(_LITERALmatch(a)->_4);
            for (int i = _LITERALmatch(a)->_4 - 1; i >= 0; i--)
              br[i] = merge( _LITERALmatch(a)->_5[i], b);
            return LITERALmatch( _LITERALmatch(a)->_1, _LITERALmatch(a)->_2, _LITERALmatch(a)->_3, _LITERALmatch(a)->_4, br, merge( _LITERALmatch(a)->_6, b));
            
#line 1363 "../../prop-src/matchcom.pcc"
            } break;
          case a_Match::tag_CONSmatch: {
#line 1365 "../../prop-src/matchcom.pcc"
            
            Match * br = Matches(_CONSmatch(a)->_5);
            for (int i = _CONSmatch(a)->_5 - 1; i >= 0; i--)
              br[i] = merge( _CONSmatch(a)->_6[i], b);
            return CONSmatch( _CONSmatch(a)->_1, _CONSmatch(a)->_2, _CONSmatch(a)->_3, _CONSmatch(a)->_4, _CONSmatch(a)->_5, br, merge( _CONSmatch(a)->_7, b));
            
#line 1370 "../../prop-src/matchcom.pcc"
            } break;
          default: {
            L43:; 
#line 1387 "../../prop-src/matchcom.pcc"
           return compose( a, b); 
#line 1387 "../../prop-src/matchcom.pcc"
            } break;
        }
      } else { goto L43; }
      } break;
    case SAME: {
      if (boxed(a)) {
        switch (a->tag__) {
          case a_Match::tag_GUARDmatch: {
            if (boxed(b)) {
              switch (b->tag__) {
                case a_Match::tag_GUARDmatch: {
#line 1271 "../../prop-src/matchcom.pcc"
                  
                  if (equal( _GUARDmatch(a)->_1, _GUARDmatch(b)->_1))
                    return GUARDmatch( _GUARDmatch(a)->_1, merge( _GUARDmatch(a)->_2, _GUARDmatch(b)->_2), merge( _GUARDmatch(a)->_3, _GUARDmatch(b)->_3));
                  else
                    return GUARDmatch( _GUARDmatch(a)->_1, merge( _GUARDmatch(a)->_2, b), merge( _GUARDmatch(a)->_3, b));
                  
#line 1276 "../../prop-src/matchcom.pcc"
                  } break;
                default: { goto L43; } break;
              }
            } else { goto L43; }
            } break;
          case a_Match::tag_LITERALmatch: {
            if (boxed(b)) {
              switch (b->tag__) {
                case a_Match::tag_LITERALmatch: {
#line 1287 "../../prop-src/matchcom.pcc"
                  
                  int i, n = _LITERALmatch(a)->_4 + _LITERALmatch(b)->_4;
                  Match   * br = Matches(n);
                  Literal * ls = Literals(n);
                  
                  if (has_regexp( _LITERALmatch(a)->_4, _LITERALmatch(a)->_3) || has_regexp( _LITERALmatch(b)->_4, _LITERALmatch(b)->_3))
                  {
                    for (i = 0; i < _LITERALmatch(a)->_4; i++)
                    {
                      br[i] = _LITERALmatch(a)->_5[i];
                      ls[i] = _LITERALmatch(a)->_3[i];
                    }
                    for (i = 0; i < _LITERALmatch(b)->_4; i++)
                    {
                      br[_LITERALmatch(a)->_4+i] = _LITERALmatch(b)->_5[i];
                      ls[_LITERALmatch(a)->_4+i] = _LITERALmatch(b)->_3[i];
                    }
                    convert_regexp(n,ls);
                  }
                  else
                  {
                    // merge and eliminate duplicates
                    int i, j, k;
                    for (i = 0, j = 0, k = 0; i < _LITERALmatch(a)->_4 && j < _LITERALmatch(b)->_4; )
                    {
                      int dir = compare_literals( _LITERALmatch(a)->_3[i], _LITERALmatch(b)->_3[j]);
                      if (dir == 0)
                      {
                        ls[k] = _LITERALmatch(a)->_3[i];
                        br[k] = merge( _LITERALmatch(a)->_5[i], _LITERALmatch(b)->_5[j]);
                        i++;
                        j++;
                      }
                      else if (dir < 0)
                      {
                        ls[k] = _LITERALmatch(a)->_3[i];
                        br[k] = merge( _LITERALmatch(a)->_5[i], _LITERALmatch(b)->_6);
                        i++;
                      }
                      else
                      {
                        ls[k] = _LITERALmatch(b)->_3[j];
                        br[k] = merge( _LITERALmatch(a)->_6, _LITERALmatch(b)->_5[j]);
                        j++;
                      }
                      k++;
                    }
                    while (i < _LITERALmatch(a)->_4)
                    {
                      ls[k] = _LITERALmatch(a)->_3[i];
                      br[k++] = merge( _LITERALmatch(a)->_5[i++], _LITERALmatch(b)->_6);
                    }
                    while (j < _LITERALmatch(b)->_4)
                    {
                      ls[k] = _LITERALmatch(b)->_3[j];
                      br[k++] = merge( _LITERALmatch(a)->_6, _LITERALmatch(b)->_5[j++]);
                    }
                    n = k;
                  }
                  return LITERALmatch( _LITERALmatch(a)->_1, _LITERALmatch(a)->_2, ls, n, br, merge( _LITERALmatch(a)->_6, _LITERALmatch(b)->_6));
                  
#line 1347 "../../prop-src/matchcom.pcc"
                  } break;
                default: { goto L43; } break;
              }
            } else { goto L43; }
            } break;
          case a_Match::tag_RANGEmatch: {
            if (boxed(b)) {
              switch (b->tag__) {
                case a_Match::tag_RANGEmatch: {
#line 1278 "../../prop-src/matchcom.pcc"
                  
                  if (_RANGEmatch(a)->_3 == 0 && _RANGEmatch(a)->_4 == INT_MAX)
                    return merge(_RANGEmatch(a)->_5,b);
                  else if (_RANGEmatch(a)->_3 <= _RANGEmatch(b)->_3 && _RANGEmatch(a)->_4 >= _RANGEmatch(b)->_4)
                    return RANGEmatch( _RANGEmatch(a)->_1, _RANGEmatch(a)->_2, _RANGEmatch(a)->_3, _RANGEmatch(a)->_4, merge( _RANGEmatch(a)->_5, _RANGEmatch(b)->_5), merge( _RANGEmatch(a)->_6, _RANGEmatch(b)->_6));
                  else
                    return RANGEmatch( _RANGEmatch(a)->_1, _RANGEmatch(b)->_2, _RANGEmatch(a)->_3, _RANGEmatch(a)->_4, merge( _RANGEmatch(a)->_5, b), merge( _RANGEmatch(a)->_6, b));
                  
#line 1285 "../../prop-src/matchcom.pcc"
                  } break;
                default: { goto L43; } break;
              }
            } else { goto L43; }
            } break;
          case a_Match::tag_CONSmatch: {
            if (boxed(b)) {
              switch (b->tag__) {
                case a_Match::tag_CONSmatch: {
#line 1349 "../../prop-src/matchcom.pcc"
                  
                  Match * br = Matches(_CONSmatch(a)->_5);
                  for (int i = _CONSmatch(a)->_5 - 1; i >= 0; i--)
                    br[i] = merge( _CONSmatch(a)->_6[i], _CONSmatch(b)->_6[i]);
                  return CONSmatch( _CONSmatch(a)->_1, _CONSmatch(a)->_2, _CONSmatch(a)->_3, _CONSmatch(a)->_4, _CONSmatch(a)->_5, br, merge( _CONSmatch(a)->_7, _CONSmatch(b)->_7));
                  
#line 1354 "../../prop-src/matchcom.pcc"
                  } break;
                default: { goto L43; } break;
              }
            } else { goto L43; }
            } break;
          default: { goto L43; } break;
        }
      } else { goto L43; }
      } break;
    case MORE: {
      if (boxed(b)) {
        switch (b->tag__) {
          case a_Match::tag_GUARDmatch: {
#line 1372 "../../prop-src/matchcom.pcc"
           return GUARDmatch( _GUARDmatch(b)->_1, merge( a, _GUARDmatch(b)->_2), merge( a, _GUARDmatch(b)->_3)); 
#line 1372 "../../prop-src/matchcom.pcc"
            } break;
          case a_Match::tag_LITERALmatch: {
#line 1374 "../../prop-src/matchcom.pcc"
            
            Match * br = Matches(_LITERALmatch(b)->_4);
            for (int i = _LITERALmatch(b)->_4 - 1; i >= 0; i--)
              br[i] = merge( a, _LITERALmatch(b)->_5[i]);
            return LITERALmatch( _LITERALmatch(b)->_1, _LITERALmatch(b)->_2, _LITERALmatch(b)->_3, _LITERALmatch(b)->_4, br, merge( a, _LITERALmatch(b)->_6));
            
#line 1379 "../../prop-src/matchcom.pcc"
            } break;
          case a_Match::tag_CONSmatch: {
#line 1381 "../../prop-src/matchcom.pcc"
            
            Match * br = Matches(_CONSmatch(b)->_5);
            for (int i = _CONSmatch(b)->_5 - 1; i >= 0; i--)
              br[i] = merge( a, _CONSmatch(b)->_6[i]);
            return CONSmatch( _CONSmatch(b)->_1, _CONSmatch(b)->_2, _CONSmatch(b)->_3, _CONSmatch(b)->_4, _CONSmatch(b)->_5, br, merge( a, _CONSmatch(b)->_7));
            
#line 1386 "../../prop-src/matchcom.pcc"
            } break;
          default: { goto L43; } break;
        }
      } else { goto L43; }
      } break;
    default: { goto L43; } break;
  }
}
#line 1388 "../../prop-src/matchcom.pcc"
#line 1388 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Equality between two matching tree.
//
///////////////////////////////////////////////////////////////////////////////

Bool match_equal( HashTable::Key a, HashTable::Key b)
{
  
#line 1399 "../../prop-src/matchcom.pcc"
#line 1434 "../../prop-src/matchcom.pcc"
{
  Match _V10 = Match(a);
  Match _V11 = Match(b);
  if (boxed(_V10)) {
    switch (_V10->tag__) {
      case a_Match::tag_SUCCESSmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_SUCCESSmatch: {
#line 1402 "../../prop-src/matchcom.pcc"
             return a == b; 
#line 1402 "../../prop-src/matchcom.pcc"
              } break;
            default: {
              L44:; 
#line 1434 "../../prop-src/matchcom.pcc"
             return false; 
#line 1434 "../../prop-src/matchcom.pcc"
              } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_SUCCESSESmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_SUCCESSESmatch: {
#line 1403 "../../prop-src/matchcom.pcc"
             return equal(_SUCCESSESmatch(_V10)->_2,_SUCCESSESmatch(_V11)->_2); 
#line 1403 "../../prop-src/matchcom.pcc"
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_COSTmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_COSTmatch: {
#line 1404 "../../prop-src/matchcom.pcc"
             return equal(_COSTmatch(_V10)->_3,_COSTmatch(_V11)->_3); 
#line 1404 "../../prop-src/matchcom.pcc"
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_GUARDmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_GUARDmatch: {
#line 1406 "../../prop-src/matchcom.pcc"
             return equal(_GUARDmatch(_V10)->_1,_GUARDmatch(_V11)->_1) && _GUARDmatch(_V10)->_2 == _GUARDmatch(_V11)->_2 && _GUARDmatch(_V10)->_3 == _GUARDmatch(_V11)->_3; 
#line 1406 "../../prop-src/matchcom.pcc"
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_LITERALmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_LITERALmatch: {
              if (
#line 1411 "../../prop-src/matchcom.pcc"
              (_LITERALmatch(_V10)->_4 == _LITERALmatch(_V11)->_4)
#line 1411 "../../prop-src/matchcom.pcc"
) {
                
#line 1412 "../../prop-src/matchcom.pcc"
                
                if (compare_pos(_LITERALmatch(_V10)->_1,_LITERALmatch(_V11)->_1) != SAME)
                  return false;
                for (int k = _LITERALmatch(_V10)->_4-1; k >= 0; k--)
                  if (_LITERALmatch(_V10)->_5[k] != _LITERALmatch(_V11)->_5[k])
                    return false;
                return _LITERALmatch(_V10)->_6 == _LITERALmatch(_V11)->_6;
                
#line 1419 "../../prop-src/matchcom.pcc"
              } else {
                 goto L44; }
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_RANGEmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_RANGEmatch: {
#line 1430 "../../prop-src/matchcom.pcc"
              
              return compare_pos(_RANGEmatch(_V10)->_1,_RANGEmatch(_V11)->_1) == SAME &&
                      _RANGEmatch(_V10)->_3 == _RANGEmatch(_V11)->_3 && _RANGEmatch(_V10)->_4 == _RANGEmatch(_V11)->_4 && _RANGEmatch(_V10)->_5 == _RANGEmatch(_V11)->_5 && _RANGEmatch(_V10)->_6 == _RANGEmatch(_V11)->_6;
              
#line 1433 "../../prop-src/matchcom.pcc"
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_CONSmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_CONSmatch: {
              if (
#line 1420 "../../prop-src/matchcom.pcc"
              ((_CONSmatch(_V10)->_4 == _CONSmatch(_V11)->_4) && (_CONSmatch(_V10)->_5 == _CONSmatch(_V11)->_5))
#line 1420 "../../prop-src/matchcom.pcc"
) {
                
#line 1421 "../../prop-src/matchcom.pcc"
                
                if (compare_pos(_CONSmatch(_V10)->_1,_CONSmatch(_V11)->_1) != SAME)
                  return false;
                for (int k = _CONSmatch(_V10)->_5-1; k >= 0; k--)
                  if (_CONSmatch(_V10)->_6[k] != _CONSmatch(_V11)->_6[k])
                    return false;
                return _CONSmatch(_V10)->_7 == _CONSmatch(_V11)->_7;
                
#line 1428 "../../prop-src/matchcom.pcc"
              } else {
                 goto L44; }
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_TREECOSTmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_TREECOSTmatch: {
#line 1408 "../../prop-src/matchcom.pcc"
             return _TREECOSTmatch(_V10)->_1 == _TREECOSTmatch(_V11)->_1 && equal(_TREECOSTmatch(_V10)->_2,_TREECOSTmatch(_V11)->_2); 
#line 1408 "../../prop-src/matchcom.pcc"
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      case a_Match::tag_TREELABELmatch: {
        if (boxed(_V11)) {
          switch (_V11->tag__) {
            case a_Match::tag_TREELABELmatch: {
#line 1410 "../../prop-src/matchcom.pcc"
             return _TREELABELmatch(_V10)->_1 == _TREELABELmatch(_V11)->_1 && ty_equal(_TREELABELmatch(_V10)->_2,_TREELABELmatch(_V11)->_2) && ty_equal(_TREELABELmatch(_V10)->_3,_TREELABELmatch(_V11)->_3) && _TREELABELmatch(_V10)->_4 == _TREELABELmatch(_V11)->_4; 
#line 1410 "../../prop-src/matchcom.pcc"
              } break;
            default: { goto L44; } break;
          }
        } else { goto L44; }
        } break;
      default: { goto L44; } break;
    }
  } else {
    if (_V10) {
       goto L44; } else {
      
      if (boxed(_V11)) { goto L44; } else {
        if (_V11) {
           goto L44; } else {
          
#line 1401 "../../prop-src/matchcom.pcc"
         return true; 
#line 1401 "../../prop-src/matchcom.pcc"
        }
      }
    }
  }
}
#line 1435 "../../prop-src/matchcom.pcc"
#line 1435 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Hashing function on a literal.
//
///////////////////////////////////////////////////////////////////////////////

unsigned int literal_hash( HashTable::Key k)
{
  
#line 1446 "../../prop-src/matchcom.pcc"
#line 1455 "../../prop-src/matchcom.pcc"
{
  Literal _V12 = Literal(k);
  switch (_V12->tag__) {
    case a_Literal::tag_INTlit: {
#line 1448 "../../prop-src/matchcom.pcc"
     return _INTlit(_V12)->INTlit; 
#line 1448 "../../prop-src/matchcom.pcc"
      } break;
    case a_Literal::tag_BOOLlit: {
#line 1449 "../../prop-src/matchcom.pcc"
     return _BOOLlit(_V12)->BOOLlit; 
#line 1449 "../../prop-src/matchcom.pcc"
      } break;
    case a_Literal::tag_CHARlit: {
#line 1453 "../../prop-src/matchcom.pcc"
     return _CHARlit(_V12)->CHARlit; 
#line 1453 "../../prop-src/matchcom.pcc"
      } break;
    case a_Literal::tag_REALlit: {
#line 1450 "../../prop-src/matchcom.pcc"
     return (unsigned int)_REALlit(_V12)->REALlit; 
#line 1450 "../../prop-src/matchcom.pcc"
      } break;
    case a_Literal::tag_STRINGlit: {
#line 1451 "../../prop-src/matchcom.pcc"
     return hash(_STRINGlit(_V12)->STRINGlit); 
#line 1451 "../../prop-src/matchcom.pcc"
      } break;
    case a_Literal::tag_REGEXPlit: {
#line 1452 "../../prop-src/matchcom.pcc"
     return hash(_REGEXPlit(_V12)->REGEXPlit); 
#line 1452 "../../prop-src/matchcom.pcc"
      } break;
    case a_Literal::tag_QUARKlit: {
#line 1454 "../../prop-src/matchcom.pcc"
     return hash(_QUARKlit(_V12)->QUARKlit); 
#line 1454 "../../prop-src/matchcom.pcc"
      } break;
    default: {
#line 1455 "../../prop-src/matchcom.pcc"
     return hash(_BIGINTlit(_V12)->BIGINTlit); 
#line 1455 "../../prop-src/matchcom.pcc"
      } break;
  }
}
#line 1456 "../../prop-src/matchcom.pcc"
#line 1456 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Equality function on literals.
//
///////////////////////////////////////////////////////////////////////////////

Bool literal_equal( HashTable::Key a, HashTable::Key b)
{
  return compare_literals((Literal)a, (Literal)b) == 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Hashing function on a matching tree.
//
///////////////////////////////////////////////////////////////////////////////

unsigned int match_hash( HashTable::Key m)
{
  
#line 1478 "../../prop-src/matchcom.pcc"
#line 1504 "../../prop-src/matchcom.pcc"
{
  Match _V13 = Match(m);
  if (boxed(_V13)) {
    switch (_V13->tag__) {
      case a_Match::tag_SUCCESSmatch: {
#line 1483 "../../prop-src/matchcom.pcc"
       return (unsigned int)m; 
#line 1483 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_SUCCESSESmatch: {
#line 1484 "../../prop-src/matchcom.pcc"
       return 93 + hash (_SUCCESSESmatch(_V13)->_2); 
#line 1484 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_COSTmatch: {
#line 1485 "../../prop-src/matchcom.pcc"
       return 457 + hash (_COSTmatch(_V13)->_3); 
#line 1485 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_GUARDmatch: {
#line 1488 "../../prop-src/matchcom.pcc"
       return (unsigned int)_GUARDmatch(_V13)->_2 + (unsigned int)_GUARDmatch(_V13)->_3;
#line 1488 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_LITERALmatch: {
#line 1492 "../../prop-src/matchcom.pcc"
        
        unsigned h = 117 + _LITERALmatch(_V13)->_4 + (unsigned int)_LITERALmatch(_V13)->_6;
        for (int i = _LITERALmatch(_V13)->_4 - 1; i >= 0; i--)
          h += literal_hash(_LITERALmatch(_V13)->_3[i]) + (unsigned int)_LITERALmatch(_V13)->_5[i];
        return h;
        
#line 1497 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_RANGEmatch: {
#line 1490 "../../prop-src/matchcom.pcc"
       return 235 + _RANGEmatch(_V13)->_3 + _RANGEmatch(_V13)->_4 + (unsigned int) _RANGEmatch(_V13)->_5 + (unsigned int) _RANGEmatch(_V13)->_6; 
#line 1490 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_CONSmatch: {
#line 1499 "../../prop-src/matchcom.pcc"
        
        unsigned h = 657 + _CONSmatch(_V13)->_5 + (unsigned int)_CONSmatch(_V13)->_7;
        for (int i = _CONSmatch(_V13)->_5 - 1; i >= 0; i--)
          h += (unsigned int)_CONSmatch(_V13)->_6[i];
        return h;
        
#line 1504 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_TREECOSTmatch: {
#line 1486 "../../prop-src/matchcom.pcc"
       return hash(_TREECOSTmatch(_V13)->_2) + (unsigned int)_TREECOSTmatch(_V13)->_1; 
#line 1486 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_TREELABELmatch: {
#line 1487 "../../prop-src/matchcom.pcc"
       return ty_hash(_TREELABELmatch(_V13)->_2) + ty_hash(_TREELABELmatch(_V13)->_3) + _TREELABELmatch(_V13)->_4 + (unsigned int)_TREELABELmatch(_V13)->_1; 
#line 1487 "../../prop-src/matchcom.pcc"
        } break;
      default: {
#line 1482 "../../prop-src/matchcom.pcc"
       return _BACKEDGEmatch(_V13)->_1 + 1249; 
#line 1482 "../../prop-src/matchcom.pcc"
        } break;
    }
  } else {
    if (_V13) {
      
#line 1481 "../../prop-src/matchcom.pcc"
     return 179; 
#line 1481 "../../prop-src/matchcom.pcc"
    } else {
      
#line 1480 "../../prop-src/matchcom.pcc"
     return 0; 
#line 1480 "../../prop-src/matchcom.pcc"
    }
  }
}
#line 1505 "../../prop-src/matchcom.pcc"
#line 1505 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Tree to dag conversion for a matching tree.
//
///////////////////////////////////////////////////////////////////////////////
Match make_dag( Match m, HashTable& map, int& merges)
{
  int i;
  if (boxed(m)) { m->shared = 0; m->label = 0; }
  
#line 1517 "../../prop-src/matchcom.pcc"
#line 1569 "../../prop-src/matchcom.pcc"
{
  if (boxed(m)) {
    switch (m->tag__) {
      case a_Match::tag_GUARDmatch: {
#line 1552 "../../prop-src/matchcom.pcc"
        
        if ((_GUARDmatch(m)->_2 = make_dag(_GUARDmatch(m)->_2,map,merges)) == (_GUARDmatch(m)->_3 = make_dag(_GUARDmatch(m)->_3,map,merges)))
        {
          merges++;
          return _GUARDmatch(m)->_2;
        }
        
#line 1558 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_LITERALmatch: {
#line 1520 "../../prop-src/matchcom.pcc"
        
        for (i = _LITERALmatch(m)->_4 - 1; i >= 0; i--) _LITERALmatch(m)->_5[i] = make_dag (_LITERALmatch(m)->_5[i], map, merges);
        _LITERALmatch(m)->_6 = make_dag(_LITERALmatch(m)->_6, map, merges);
        // Eliminate the node if every branch is the same.
        for (i = _LITERALmatch(m)->_4 - 1; i >= 1; i--) if (_LITERALmatch(m)->_5[i] != _LITERALmatch(m)->_5[i-1]) break;
        if (i == 0 && _LITERALmatch(m)->_5[0] == _LITERALmatch(m)->_6) { merges++; return _LITERALmatch(m)->_6; }
        // Eliminate all branches that are the same as the default
        for (i = 0; i < _LITERALmatch(m)->_4; i++)
        {
          if (_LITERALmatch(m)->_5[i] == _LITERALmatch(m)->_6)
          { // shift one over
            for (int j = i+1; j < _LITERALmatch(m)->_4; j++)
            {  _LITERALmatch(m)->_5[j-1] = _LITERALmatch(m)->_5[j]; _LITERALmatch(m)->_3[j-1] = _LITERALmatch(m)->_3[j]; }
            _LITERALmatch(m)->_4--;
          }
        }
        
#line 1536 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_RANGEmatch: {
#line 1560 "../../prop-src/matchcom.pcc"
        
        if ((_RANGEmatch(m)->_5 = make_dag(_RANGEmatch(m)->_5,map,merges)) == (_RANGEmatch(m)->_6 = make_dag(_RANGEmatch(m)->_6,map,merges)))
        {
          merges++;
          return _RANGEmatch(m)->_5;
        }
        
#line 1566 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_CONSmatch: {
#line 1538 "../../prop-src/matchcom.pcc"
        
        for (i = _CONSmatch(m)->_5 - 1; i >= 0; i--) _CONSmatch(m)->_6[i] = make_dag (_CONSmatch(m)->_6[i], map, merges);
        _CONSmatch(m)->_7 = make_dag(_CONSmatch(m)->_7, map, merges);
        // Eliminate the node if every branch is the same.
        for (i = _CONSmatch(m)->_5 - 1; i >= 1; i--)
          if (_CONSmatch(m)->_6[i] != _CONSmatch(m)->_6[i-1])
            break;
        if (i == 0 && _CONSmatch(m)->_6[0] == _CONSmatch(m)->_7)
        {
          merges++;
          return _CONSmatch(m)->_7;
        }
        
#line 1550 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_TREECOSTmatch: {
#line 1567 "../../prop-src/matchcom.pcc"
      _TREECOSTmatch(m)->_1 = make_dag(_TREECOSTmatch(m)->_1,map,merges); 
#line 1567 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_TREELABELmatch: {
#line 1568 "../../prop-src/matchcom.pcc"
      _TREELABELmatch(m)->_1 = make_dag(_TREELABELmatch(m)->_1,map,merges); 
#line 1568 "../../prop-src/matchcom.pcc"
        } break;
      default: {
        L45:; 
#line 1569 "../../prop-src/matchcom.pcc"
       /* skip */ 
#line 1569 "../../prop-src/matchcom.pcc"
        } break;
    }
  } else { goto L45; }
}
#line 1570 "../../prop-src/matchcom.pcc"
#line 1570 "../../prop-src/matchcom.pcc"


  HashTable::Entry * found = map.lookup(m);
  if (found)
  {
    merges++;
    return (Match)found->v;
  }
  else
  {
    map.insert(m,m);
    return m;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Mark all sharing
//
///////////////////////////////////////////////////////////////////////////////

void mark( Match m)
{
  if (boxed(m))
    m->shared++;
  
#line 1595 "../../prop-src/matchcom.pcc"
#line 1625 "../../prop-src/matchcom.pcc"
{
  if (boxed(m)) {
    switch (m->tag__) {
      case a_Match::tag_SUCCESSmatch: {
#line 1597 "../../prop-src/matchcom.pcc"
       _SUCCESSmatch(m)->_2->used = true; 
#line 1597 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_GUARDmatch: {
#line 1600 "../../prop-src/matchcom.pcc"
       mark(_GUARDmatch(m)->_2); mark(_GUARDmatch(m)->_3); 
#line 1600 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_LITERALmatch: {
#line 1601 "../../prop-src/matchcom.pcc"
       for (int i = _LITERALmatch(m)->_4-1; i >= 0; i--) mark(_LITERALmatch(m)->_5[i]);
        mark(_LITERALmatch(m)->_6);
        
#line 1603 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_RANGEmatch: {
#line 1604 "../../prop-src/matchcom.pcc"
       mark(_RANGEmatch(m)->_5); mark(_RANGEmatch(m)->_6); 
#line 1604 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_CONSmatch: {
        if (_CONSmatch(m)->_4) {
          switch (_CONSmatch(m)->_4->tag__) {
            case a_Ty::tag_TYCONty: {
              if (boxed(_TYCONty(_CONSmatch(m)->_4)->_1)) {
                switch (_TYCONty(_CONSmatch(m)->_4)->_1->tag__) {
                  case a_TyCon::tag_DATATYPEtycon: {
#line 1608 "../../prop-src/matchcom.pcc"
                    
                    for (int i = _CONSmatch(m)->_5-1; i >= 0; i--) mark(_CONSmatch(m)->_6[i]);
                    // if (unit > 0)
                    // {  int i;
                    //    for (i = unit - 2; i >= 0; i--) if (a[i] != a[i+1]) break;
                    //    if (i < 0) mark(a[0]);
                    //    else       for (i = unit - 1; i >= 0; i--) mark(a[i]);
                    // }
                    // if (arg > 0)
                    // {  int i;
                    //    for (i = n - 2; i >= unit; i--) if (a[i] != a[i+1]) break;
                    //    if (i < unit) mark(a[unit]);
                    //    else          for (i = n - 1; i >= unit; i--) mark(a[i]);
                    // }
                    if (_DATATYPEtycon(_TYCONty(_CONSmatch(m)->_4)->_1)->qualifiers & QUALextensible)
                      mark(_CONSmatch(m)->_7);
                    
#line 1624 "../../prop-src/matchcom.pcc"
                    } break;
                  default: {
                    L46:; 
#line 1625 "../../prop-src/matchcom.pcc"
                   bug ("mark()"); 
#line 1625 "../../prop-src/matchcom.pcc"
                    } break;
                }
              } else { goto L46; }
              } break;
            default: { goto L46; } break;
          }
        } else { goto L46; }
        } break;
      case a_Match::tag_TREECOSTmatch: {
#line 1605 "../../prop-src/matchcom.pcc"
       mark(_TREECOSTmatch(m)->_1); 
#line 1605 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_TREELABELmatch: {
#line 1606 "../../prop-src/matchcom.pcc"
       mark(_TREELABELmatch(m)->_1); 
#line 1606 "../../prop-src/matchcom.pcc"
        } break;
      case a_Match::tag_BACKEDGEmatch: { goto L46; } break;
      default: {
        L47:; 
#line 1599 "../../prop-src/matchcom.pcc"
       /* skip */ 
#line 1599 "../../prop-src/matchcom.pcc"
        } break;
    }
  } else {
    if (m) {
       goto L46; } else {
       goto L47; }
  }
}
#line 1626 "../../prop-src/matchcom.pcc"
#line 1626 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Top level tree to dag conversion.
//
///////////////////////////////////////////////////////////////////////////////

Match MatchCompiler::make_dag( Match m, MatchOptions options, MatchRules rules)
{
  HashTable map( match_hash, match_equal, 257);
  m = ::make_dag( m, map, merges);
  if (options & MATCHwithtreecost)
    m = translate_treecost( m, rules);
  mark(m);
  return m;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Check to see if a matching tree is refutable (i.e. can fail.)
//
///////////////////////////////////////////////////////////////////////////////

Bool refutable( Match m)
{
  
#line 1653 "../../prop-src/matchcom.pcc"
#line 1679 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (boxed(m)) {
      switch (m->tag__) {
        case a_Match::tag_GUARDmatch: {
#line 1657 "../../prop-src/matchcom.pcc"
         return refutable(_GUARDmatch(m)->_2) || refutable(_GUARDmatch(m)->_3); 
#line 1657 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_LITERALmatch: {
#line 1660 "../../prop-src/matchcom.pcc"
          
          for (int i = _LITERALmatch(m)->_4 - 1; i >= 0; i--) if (refutable(_LITERALmatch(m)->_5[i])) return true;
          
#line 1662 "../../prop-src/matchcom.pcc"
#line 1665 "../../prop-src/matchcom.pcc"
          {
            Literal _V14 = _LITERALmatch(m)->_3[0];
            switch (_V14->tag__) {
              case a_Literal::tag_BOOLlit: {
                if (
#line 1664 "../../prop-src/matchcom.pcc"
                (_LITERALmatch(m)->_4 >= 2)
#line 1664 "../../prop-src/matchcom.pcc"
) {
                  
#line 1664 "../../prop-src/matchcom.pcc"
                 return false; 
#line 1664 "../../prop-src/matchcom.pcc"
                } else {
                  
                  L49:; 
#line 1665 "../../prop-src/matchcom.pcc"
                 m = _LITERALmatch(m)->_6; 
#line 1665 "../../prop-src/matchcom.pcc"
                }
                } break;
              default: { goto L49; } break;
            }
          }
#line 1666 "../../prop-src/matchcom.pcc"
#line 1666 "../../prop-src/matchcom.pcc"
          
          
#line 1667 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_RANGEmatch: {
#line 1658 "../../prop-src/matchcom.pcc"
         return refutable(_RANGEmatch(m)->_5) || refutable(_RANGEmatch(m)->_6); 
#line 1658 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_CONSmatch: {
          if (_CONSmatch(m)->_4) {
            switch (_CONSmatch(m)->_4->tag__) {
              case a_Ty::tag_TYCONty: {
                if (boxed(_TYCONty(_CONSmatch(m)->_4)->_1)) {
                  switch (_TYCONty(_CONSmatch(m)->_4)->_1->tag__) {
                    case a_TyCon::tag_DATATYPEtycon: {
#line 1669 "../../prop-src/matchcom.pcc"
                      
                      for (int i = _CONSmatch(m)->_5 - 1; i >= 0; i--)
                        if (refutable(_CONSmatch(m)->_6[i]))
                          return true;
                      if (! (_DATATYPEtycon(_TYCONty(_CONSmatch(m)->_4)->_1)->qualifiers & QUALextensible))
                        return false;
                      m = _CONSmatch(m)->_7;
                      
#line 1676 "../../prop-src/matchcom.pcc"
                      } break;
                    default: {
                      L50:; 
#line 1679 "../../prop-src/matchcom.pcc"
                     bug ("refutable()"); 
#line 1679 "../../prop-src/matchcom.pcc"
                      } break;
                  }
                } else { goto L50; }
                } break;
              default: { goto L50; } break;
            }
          } else { goto L50; }
          } break;
        case a_Match::tag_TREECOSTmatch: {
#line 1677 "../../prop-src/matchcom.pcc"
         m = _TREECOSTmatch(m)->_1; 
#line 1677 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_TREELABELmatch: {
#line 1678 "../../prop-src/matchcom.pcc"
         m = _TREELABELmatch(m)->_1; 
#line 1678 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_BACKEDGEmatch: { goto L50; } break;
        default: {
#line 1656 "../../prop-src/matchcom.pcc"
         return false; 
#line 1656 "../../prop-src/matchcom.pcc"
          } break;
      }
    } else {
      if (m) {
         goto L50; } else {
        
#line 1655 "../../prop-src/matchcom.pcc"
       return true; 
#line 1655 "../../prop-src/matchcom.pcc"
      }
    }
  }
}
#line 1680 "../../prop-src/matchcom.pcc"
#line 1680 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Compute the set of rules that can possibly match as a bitset.
//
///////////////////////////////////////////////////////////////////////////////

void matchables( Match m, BitSet& set)
{
  
#line 1691 "../../prop-src/matchcom.pcc"
#line 1715 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (boxed(m)) {
      switch (m->tag__) {
        case a_Match::tag_SUCCESSmatch: {
#line 1696 "../../prop-src/matchcom.pcc"
         set.add(_SUCCESSmatch(m)->_1); return; 
#line 1696 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_SUCCESSESmatch: {
#line 1694 "../../prop-src/matchcom.pcc"
         set.Union(*_SUCCESSESmatch(m)->_2); return; 
#line 1694 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_COSTmatch: {
#line 1695 "../../prop-src/matchcom.pcc"
         set.Union(*_COSTmatch(m)->_3); return; 
#line 1695 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_GUARDmatch: {
#line 1697 "../../prop-src/matchcom.pcc"
         matchables(_GUARDmatch(m)->_2,set); m = _GUARDmatch(m)->_3; 
#line 1697 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_LITERALmatch: {
#line 1700 "../../prop-src/matchcom.pcc"
          
          for (int i = _LITERALmatch(m)->_4 - 1; i >= 0; i--)
            matchables(_LITERALmatch(m)->_5[i],set);
          m = _LITERALmatch(m)->_6;
          
#line 1704 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_RANGEmatch: {
#line 1698 "../../prop-src/matchcom.pcc"
         matchables(_RANGEmatch(m)->_5,set); m = _RANGEmatch(m)->_6; 
#line 1698 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_CONSmatch: {
          if (_CONSmatch(m)->_4) {
            switch (_CONSmatch(m)->_4->tag__) {
              case a_Ty::tag_TYCONty: {
                if (boxed(_TYCONty(_CONSmatch(m)->_4)->_1)) {
                  switch (_TYCONty(_CONSmatch(m)->_4)->_1->tag__) {
                    case a_TyCon::tag_DATATYPEtycon: {
#line 1706 "../../prop-src/matchcom.pcc"
                      
                      for (int i = _CONSmatch(m)->_5 - 1; i >= 0; i--)
                        matchables(_CONSmatch(m)->_6[i],set);
                      if ( !(_DATATYPEtycon(_TYCONty(_CONSmatch(m)->_4)->_1)->qualifiers & QUALextensible))
                        return;
                      m = _CONSmatch(m)->_7;
                      
#line 1712 "../../prop-src/matchcom.pcc"
                      } break;
                    default: {
                      L52:; 
#line 1715 "../../prop-src/matchcom.pcc"
                     bug("matchables()"); 
#line 1715 "../../prop-src/matchcom.pcc"
                      } break;
                  }
                } else { goto L52; }
                } break;
              default: { goto L52; } break;
            }
          } else { goto L52; }
          } break;
        case a_Match::tag_TREECOSTmatch: {
#line 1713 "../../prop-src/matchcom.pcc"
         set.Union(*_TREECOSTmatch(m)->_2); m = _TREECOSTmatch(m)->_1; 
#line 1713 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_TREELABELmatch: {
#line 1714 "../../prop-src/matchcom.pcc"
         m = _TREELABELmatch(m)->_1; 
#line 1714 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L52; } break;
      }
    } else {
      if (m) {
         goto L52; } else {
        
#line 1693 "../../prop-src/matchcom.pcc"
       return; 
#line 1693 "../../prop-src/matchcom.pcc"
      }
    }
  }
}
#line 1716 "../../prop-src/matchcom.pcc"
#line 1716 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Compute the set of rules that can always match as a bitset.
//
///////////////////////////////////////////////////////////////////////////////

void always_matchables( Match m, BitSet& set)
{
  
#line 1727 "../../prop-src/matchcom.pcc"
#line 1743 "../../prop-src/matchcom.pcc"
{
  for (;;) {
    if (boxed(m)) {
      switch (m->tag__) {
        case a_Match::tag_SUCCESSESmatch: {
#line 1729 "../../prop-src/matchcom.pcc"
         set.Intersect(*_SUCCESSESmatch(m)->_2); return; 
#line 1729 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_COSTmatch: {
#line 1730 "../../prop-src/matchcom.pcc"
         set.Intersect(*_COSTmatch(m)->_3); return; 
#line 1730 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_GUARDmatch: {
#line 1731 "../../prop-src/matchcom.pcc"
         always_matchables(_GUARDmatch(m)->_2,set); m = _GUARDmatch(m)->_3; 
#line 1731 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_LITERALmatch: {
#line 1734 "../../prop-src/matchcom.pcc"
        for (int i = _LITERALmatch(m)->_4 - 1; i >= 0; i--) always_matchables(_LITERALmatch(m)->_5[i],set);
          m = _LITERALmatch(m)->_6;
          
#line 1736 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_RANGEmatch: {
#line 1732 "../../prop-src/matchcom.pcc"
         always_matchables(_RANGEmatch(m)->_5,set); m = _RANGEmatch(m)->_6; 
#line 1732 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_CONSmatch: {
          if (_CONSmatch(m)->_4) {
            switch (_CONSmatch(m)->_4->tag__) {
              case a_Ty::tag_TYCONty: {
                if (boxed(_TYCONty(_CONSmatch(m)->_4)->_1)) {
                  switch (_TYCONty(_CONSmatch(m)->_4)->_1->tag__) {
                    case a_TyCon::tag_DATATYPEtycon: {
#line 1738 "../../prop-src/matchcom.pcc"
                    for (int i = _CONSmatch(m)->_5 - 1; i >= 0; i--) always_matchables(_CONSmatch(m)->_6[i],set);
                      if (! (_DATATYPEtycon(_TYCONty(_CONSmatch(m)->_4)->_1)->qualifiers & QUALextensible)) return;
                      m = _CONSmatch(m)->_7;
                      
#line 1741 "../../prop-src/matchcom.pcc"
                      } break;
                    default: { goto L53; } break;
                  }
                } else { goto L53; }
                } break;
              default: { goto L53; } break;
            }
          } else { goto L53; }
          } break;
        case a_Match::tag_TREECOSTmatch: {
#line 1742 "../../prop-src/matchcom.pcc"
         set.Intersect(*_TREECOSTmatch(m)->_2); m = _TREECOSTmatch(m)->_1; 
#line 1742 "../../prop-src/matchcom.pcc"
          } break;
        case a_Match::tag_TREELABELmatch: {
#line 1743 "../../prop-src/matchcom.pcc"
         m = _TREELABELmatch(m)->_1; 
#line 1743 "../../prop-src/matchcom.pcc"
          } break;
        default: { goto L53; } break;
      }
    } else { goto L53; }
  }
  L53:;
}
#line 1744 "../../prop-src/matchcom.pcc"
#line 1744 "../../prop-src/matchcom.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Top level routine to call the above
//
///////////////////////////////////////////////////////////////////////////////

const BitSet& always_matchables( Match m, int n)
{
  BitSet * set = new (mem_pool, n) BitSet;
  set->complement();
  always_matchables(m, *set);
  return *set;
}
#line 1760 "../../prop-src/matchcom.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 3366
Number of ifs generated      = 151
Number of switches generated = 114
Number of labels             = 44
Number of gotos              = 210
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
