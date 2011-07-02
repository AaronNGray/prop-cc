///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\trs.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_STRCMP_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/trs.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  These are the routines for building the data structure
//  for partial evaluting a TRS
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "trs.h"
#include "ir.h"
#include "ast.h"
#include "type.h"
#include "list.h"
#include "matchcom.h"
#include "datagen.h"
#include "rwgen.h"
#include "funmap.h"
#include "setlgen.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Constructors for represents a term
//
///////////////////////////////////////////////////////////////////////////////

#line 28 "../../prop-src/trs.pcc"
#line 28 "../../prop-src/trs.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Term
//
///////////////////////////////////////////////////////////////////////////////
#line 28 "../../prop-src/trs.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Term
//
///////////////////////////////////////////////////////////////////////////////
#line 28 "../../prop-src/trs.pcc"


#line 28 "../../prop-src/trs.pcc"
#line 28 "../../prop-src/trs.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor for TRS
//
///////////////////////////////////////////////////////////////////////////////

TRS::TRS( RewritingCompiler& C)
    : compiler(C), Fmap(*C.Fmap), treeauto(*C.Fmap->tree_gen),
      count_redex(false)
{
  MatchRules rules = Fmap.bottomup_rules;
  number_of_rules  = length(rules);
  rule_map    = new MatchRule [number_of_rules];
  guard_map   = new Exp       [number_of_rules];
  lhs_map     = new Term      [number_of_rules];
  rhs_map     = new Term      [number_of_rules];
  num_var_map = new int       [number_of_rules];
  var_map     = new Exp *     [number_of_rules];
  var_pat_map = new Pat *     [number_of_rules];
  residue_map = new Residues *[number_of_rules];
  literal_map = new Literal   [Fmap.G.functors()];
  optimized_map = new Exp     [number_of_rules];

  clear_statistics();

  int i = 0;
  for_each( MatchRule, r, rules)
  {
  
#line 58 "../../prop-src/trs.pcc"
#line 75 "../../prop-src/trs.pcc"
{
#line 61 "../../prop-src/trs.pcc"
  
  if (r->rule_number != i)
    bug("%LTRS::TRS()");
  rule_map[i]  = r;
  guard_map[i] = r->_3;
  make_lhs( i, r->_2);
  
  
#line 68 "../../prop-src/trs.pcc"
#line 73 "../../prop-src/trs.pcc"
  {
    a_List<Decl> *  _V1 = r->_5;
    if (_V1) {
      if (_V1->_1) {
        switch (_V1->_1->tag__) {
          case a_Decl::tag_MARKEDdecl: {
            if (_MARKEDdecl(_V1->_1)->_2) {
              switch (_MARKEDdecl(_V1->_1)->_2->tag__) {
                case a_Decl::tag_REPLACEMENTdecl: {
                  if (_V1->_2) {
                    L1:; 
#line 73 "../../prop-src/trs.pcc"
                   rhs_map[i] = OPAQUEterm( r->_5); 
#line 73 "../../prop-src/trs.pcc"
                  } else {
#line 71 "../../prop-src/trs.pcc"
                   make_rhs( i, _REPLACEMENTdecl(_MARKEDdecl(_V1->_1)->_2)->_1); 
#line 71 "../../prop-src/trs.pcc"
                  }
                  } break;
                default: { goto L1; } break;
              }
            } else { goto L1; }
            } break;
          default: { goto L1; } break;
        }
      } else { goto L1; }
    } else { goto L1; }
  }
#line 74 "../../prop-src/trs.pcc"
#line 74 "../../prop-src/trs.pcc"
  
  
#line 75 "../../prop-src/trs.pcc"
}
#line 76 "../../prop-src/trs.pcc"
#line 76 "../../prop-src/trs.pcc"

    i++;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Destructor for TRS
//
///////////////////////////////////////////////////////////////////////////////

TRS::~TRS()
{
  delete [] rule_map;
  delete [] guard_map;
  delete [] lhs_map;
  delete [] rhs_map;
  delete [] num_var_map;
  delete [] var_map;
  delete [] var_pat_map;
  delete [] residue_map;
  delete [] literal_map;
  delete [] optimized_map;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to determine if any expression is a pattern variable.
//
///////////////////////////////////////////////////////////////////////////////

Bool is_pattern_var( Exp exp)
{
  
#line 109 "../../prop-src/trs.pcc"
#line 120 "../../prop-src/trs.pcc"
{
  for (;;) {
    if (exp) {
      switch (exp->tag__) {
        case a_Exp::tag_DOTexp: {
          if (_DOTexp(exp)->_1) {
            switch (_DOTexp(exp)->_1->tag__) {
              case a_Exp::tag_SELECTORexp: {
                if (_SELECTORexp(_DOTexp(exp)->_1)->_1) {
                  switch (_SELECTORexp(_DOTexp(exp)->_1)->_1->tag__) {
                    case a_Exp::tag_IDexp: {
                      if (_equal_string(_IDexp(_SELECTORexp(_DOTexp(exp)->_1)->_1)->IDexp,"redex")) {
#line 114 "../../prop-src/trs.pcc"
                     return true; 
#line 114 "../../prop-src/trs.pcc"
}
                      else {
                      L3:; 
#line 116 "../../prop-src/trs.pcc"
                     exp = _SELECTORexp(_DOTexp(exp)->_1)->_1; 
#line 116 "../../prop-src/trs.pcc"
}
                      } break;
                    default: { goto L3; } break;
                  }
                } else { goto L3; }
                } break;
              default: {
                L4:; 
#line 120 "../../prop-src/trs.pcc"
               return false; 
#line 120 "../../prop-src/trs.pcc"
                } break;
            }
          } else { goto L4; }
          } break;
        case a_Exp::tag_SELECTORexp: {
          if (_SELECTORexp(exp)->_1) {
            switch (_SELECTORexp(exp)->_1->tag__) {
              case a_Exp::tag_IDexp: {
                if (_equal_string(_IDexp(_SELECTORexp(exp)->_1)->IDexp,"redex")) {
#line 112 "../../prop-src/trs.pcc"
               return true; 
#line 112 "../../prop-src/trs.pcc"
}
                else {
                L5:; 
#line 118 "../../prop-src/trs.pcc"
               exp = _SELECTORexp(exp)->_1; 
#line 118 "../../prop-src/trs.pcc"
}
                } break;
              default: { goto L5; } break;
            }
          } else { goto L5; }
          } break;
        default: { goto L4; } break;
      }
    } else { goto L4; }
  }
}
#line 121 "../../prop-src/trs.pcc"
#line 121 "../../prop-src/trs.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the lhs
//
///////////////////////////////////////////////////////////////////////////////

void TRS::make_lhs( Rule r, Pat pat)
{
  num_vars = 0;
  lhs_map[r] = make_term(pat);

  num_var_map[r] = num_vars;
  var_map[r]     = (Exp*) mem_pool.m_alloc( sizeof(Exp)*num_vars);
  var_pat_map[r] = (Pat*) mem_pool.m_alloc( sizeof(Pat)*num_vars);
  residue_map[r] = (Residues*) mem_pool.c_alloc( sizeof(Residues)*num_vars);
  optimized_map[r] = NOexp;

  memcpy( var_map[r], vars, sizeof(Exp)*num_vars);
  memcpy( var_pat_map[r], var_pats, sizeof(Pat)*num_vars);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the lhs for rule r
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::make_term( Pat pat)
{
  
#line 153 "../../prop-src/trs.pcc"
#line 184 "../../prop-src/trs.pcc"
{
  for (;;) {
    if (pat) {
      switch (pat->tag__) {
        case a_Pat::tag_IDpat: {
#line 160 "../../prop-src/trs.pcc"
         return make_term_var( pat, pat->selector); 
#line 160 "../../prop-src/trs.pcc"
          } break;
        case a_Pat::tag_CONSpat: {
#line 166 "../../prop-src/trs.pcc"
         return make_term( pat, _CONSpat(pat)->CONSpat, 
#line 166 "../../prop-src/trs.pcc"
#line 166 "../../prop-src/trs.pcc"
          nil_1_
#line 166 "../../prop-src/trs.pcc"
#line 166 "../../prop-src/trs.pcc"
          ); 
#line 166 "../../prop-src/trs.pcc"
          } break;
        case a_Pat::tag_APPpat: {
          if (_APPpat(pat)->_1) {
            switch (_APPpat(pat)->_1->tag__) {
              case a_Pat::tag_CONSpat: {
                if (_APPpat(pat)->_2) {
                  switch (_APPpat(pat)->_2->tag__) {
                    case a_Pat::tag_TUPLEpat: {
#line 162 "../../prop-src/trs.pcc"
                     return make_term( pat, _CONSpat(_APPpat(pat)->_1)->CONSpat, _TUPLEpat(_APPpat(pat)->_2)->TUPLEpat); 
#line 162 "../../prop-src/trs.pcc"
                      } break;
                    default: {
                      L7:; 
#line 164 "../../prop-src/trs.pcc"
                     return make_term( pat, _CONSpat(_APPpat(pat)->_1)->CONSpat, 
#line 164 "../../prop-src/trs.pcc"
#line 164 "../../prop-src/trs.pcc"
                      list_1_(_APPpat(pat)->_2)
#line 164 "../../prop-src/trs.pcc"
#line 164 "../../prop-src/trs.pcc"
                      ); 
#line 164 "../../prop-src/trs.pcc"
                      } break;
                  }
                } else { goto L7; }
                } break;
              default: {
                L8:; 
#line 184 "../../prop-src/trs.pcc"
               return PATterm(pat); 
#line 184 "../../prop-src/trs.pcc"
                } break;
            }
          } else { goto L8; }
          } break;
        case a_Pat::tag_ASpat: {
#line 158 "../../prop-src/trs.pcc"
         pat = _ASpat(pat)->_2; 
#line 158 "../../prop-src/trs.pcc"
          } break;
        case a_Pat::tag_LITERALpat: {
          if (
#line 177 "../../prop-src/trs.pcc"
          Fmap.literal_map.contains(_LITERALpat(pat)->LITERALpat)
#line 177 "../../prop-src/trs.pcc"
) {
            
#line 178 "../../prop-src/trs.pcc"
            
            Functor f = Fmap.literal_map[_LITERALpat(pat)->LITERALpat];
            	  literal_map[f] = _LITERALpat(pat)->LITERALpat;
            	  return CONSterm(f,NOcons,0,0);
            
#line 182 "../../prop-src/trs.pcc"
          } else {
             goto L8; }
          } break;
        case a_Pat::tag_LISTpat: {
          if (_LISTpat(pat)->head) {
#line 172 "../../prop-src/trs.pcc"
            
            Pat tl_pat = 
#line 173 "../../prop-src/trs.pcc"
#line 173 "../../prop-src/trs.pcc"
            LISTpat(_LISTpat(pat)->cons, _LISTpat(pat)->nil, _LISTpat(pat)->head->_2, _LISTpat(pat)->tail)
#line 173 "../../prop-src/trs.pcc"
#line 173 "../../prop-src/trs.pcc"
            ;
            	  tl_pat->ty = pat->ty;
            	  return make_term(pat,_LISTpat(pat)->cons,
#line 175 "../../prop-src/trs.pcc"
#line 175 "../../prop-src/trs.pcc"
            list_1_(_LISTpat(pat)->head->_1,list_1_(tl_pat))
#line 175 "../../prop-src/trs.pcc"
#line 175 "../../prop-src/trs.pcc"
            );
            
#line 176 "../../prop-src/trs.pcc"
          } else {
            if (_LISTpat(pat)->tail) {
#line 170 "../../prop-src/trs.pcc"
             pat = _LISTpat(pat)->tail; 
#line 170 "../../prop-src/trs.pcc"
            } else {
#line 168 "../../prop-src/trs.pcc"
             return make_term( pat, _LISTpat(pat)->nil, 
#line 168 "../../prop-src/trs.pcc"
#line 168 "../../prop-src/trs.pcc"
              nil_1_
#line 168 "../../prop-src/trs.pcc"
#line 168 "../../prop-src/trs.pcc"
              ); 
#line 168 "../../prop-src/trs.pcc"
            }
          }
          } break;
        case a_Pat::tag_MARKEDpat: {
#line 156 "../../prop-src/trs.pcc"
         pat = _MARKEDpat(pat)->_2; 
#line 156 "../../prop-src/trs.pcc"
          } break;
        default: { goto L8; } break;
      }
    } else { goto L8; }
  }
}
#line 185 "../../prop-src/trs.pcc"
#line 185 "../../prop-src/trs.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the lhs for rule r
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::make_term( Pat pat, Cons cons, Pats pats)
{
  int n       = length(pats);
  FunctorTable::Entry * E = Fmap.type_map.lookup( pat->ty);
  if (E == 0)
    { return PATterm(pat); }
  
#line 200 "../../prop-src/trs.pcc"
#line 209 "../../prop-src/trs.pcc"
{
  Ty _V2 = cons->alg_ty;
  if (_V2) {
    switch (_V2->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V2)->_1)) {
          switch (_TYCONty(_V2)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 203 "../../prop-src/trs.pcc"
              
              Functor f = Fmap.type_map.value(E) + cons->tag +
              	       (cons->ty == NOty ? 0 : _DATATYPEtycon(_TYCONty(_V2)->_1)->unit);
              	  return CONSterm( f, cons, n, make_term( pats));
              
#line 207 "../../prop-src/trs.pcc"
              } break;
            default: {
              L9:; 
#line 209 "../../prop-src/trs.pcc"
             bug("TRS::make_term"); return PATterm( pat); 
#line 209 "../../prop-src/trs.pcc"
              } break;
          }
        } else { goto L9; }
        } break;
      default: { goto L9; } break;
    }
  } else { goto L9; }
}
#line 210 "../../prop-src/trs.pcc"
#line 210 "../../prop-src/trs.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the lhs for rule r
//
///////////////////////////////////////////////////////////////////////////////

Term * TRS::make_term( Pats pats)
{
  int n = length( pats);
  Term * args = (Term *) mem_pool.m_alloc( sizeof( Term) * n);
  int i = 0;
  for_each( Pat, p, pats)
    args[i++] = make_term(p);
  return args;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return the type of an expression
//
///////////////////////////////////////////////////////////////////////////////

Ty type_of( Exp e)
{
  return type_of( e, Env());
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the rhs for rule r
//
///////////////////////////////////////////////////////////////////////////////

void TRS::make_rhs( Rule r, Exp exp)
{
  type_of( exp);
  rhs_map[r] = make_term( exp);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the rhs
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::make_term(Exp exp)
{
  Exp law_exp;
  
#line 261 "../../prop-src/trs.pcc"
#line 306 "../../prop-src/trs.pcc"
{
  for (;;) {
    if (exp) {
      switch (exp->tag__) {
        case a_Exp::tag_LITERALexp: {
          if (
#line 301 "../../prop-src/trs.pcc"
          Fmap.literal_map.contains(_LITERALexp(exp)->LITERALexp)
#line 301 "../../prop-src/trs.pcc"
) {
            
#line 302 "../../prop-src/trs.pcc"
           return CONSterm( Fmap.literal_map[_LITERALexp(exp)->LITERALexp], 0, 0, 0); 
#line 302 "../../prop-src/trs.pcc"
          } else {
            
            L11:; 
            if (
#line 303 "../../prop-src/trs.pcc"
            is_pattern_var(exp)
#line 303 "../../prop-src/trs.pcc"
) {
              
              L12:; 
#line 304 "../../prop-src/trs.pcc"
             return make_term_var( NOpat, exp); 
#line 304 "../../prop-src/trs.pcc"
            } else {
              
              L13:; 
#line 306 "../../prop-src/trs.pcc"
             return CODEterm( exp); 
#line 306 "../../prop-src/trs.pcc"
            }
          }
          } break;
        case a_Exp::tag_IDexp: {
#line 266 "../../prop-src/trs.pcc"
         return make_term( exp, _IDexp(exp)->IDexp, 
#line 266 "../../prop-src/trs.pcc"
#line 266 "../../prop-src/trs.pcc"
          nil_1_
#line 266 "../../prop-src/trs.pcc"
#line 266 "../../prop-src/trs.pcc"
          ); 
#line 266 "../../prop-src/trs.pcc"
          } break;
        case a_Exp::tag_APPexp: {
          if (
#line 303 "../../prop-src/trs.pcc"
          is_pattern_var(exp)
#line 303 "../../prop-src/trs.pcc"
) {
            
            if (_APPexp(exp)->_1) {
              switch (_APPexp(exp)->_1->tag__) {
                case a_Exp::tag_IDexp: {
                  L14:; 
                  if (_APPexp(exp)->_2) {
                    switch (_APPexp(exp)->_2->tag__) {
                      case a_Exp::tag_TUPLEexp: {
                        L15:; 
#line 286 "../../prop-src/trs.pcc"
                        
                        law_exp = DatatypeCompiler::lookup_law( _IDexp(_APPexp(exp)->_1)->IDexp, _TUPLEexp(_APPexp(exp)->_2)->TUPLEexp);
                        if (law_exp == NOexp)
                          return make_term( exp, _IDexp(_APPexp(exp)->_1)->IDexp, _TUPLEexp(_APPexp(exp)->_2)->TUPLEexp);
                        type_of( law_exp);
                        exp = law_exp;
                        
#line 292 "../../prop-src/trs.pcc"
                        } break;
                      default: {
                        L16:; 
#line 294 "../../prop-src/trs.pcc"
                        
                        law_exp = DatatypeCompiler::lookup_law(_IDexp(_APPexp(exp)->_1)->IDexp,
#line 295 "../../prop-src/trs.pcc"
#line 295 "../../prop-src/trs.pcc"
                        list_1_(_APPexp(exp)->_2)
#line 295 "../../prop-src/trs.pcc"
#line 295 "../../prop-src/trs.pcc"
                        );
                        if (law_exp == NOexp)
                          return make_term(exp,_IDexp(_APPexp(exp)->_1)->IDexp,
#line 297 "../../prop-src/trs.pcc"
#line 297 "../../prop-src/trs.pcc"
                        list_1_(_APPexp(exp)->_2)
#line 297 "../../prop-src/trs.pcc"
#line 297 "../../prop-src/trs.pcc"
                        );
                        type_of(law_exp);
                        exp = law_exp;
                        
#line 300 "../../prop-src/trs.pcc"
                        } break;
                    }
                  } else { goto L16; }
                  } break;
                default: { goto L12; } break;
              }
            } else { goto L12; }
          } else {
            
            if (_APPexp(exp)->_1) {
              switch (_APPexp(exp)->_1->tag__) {
                case a_Exp::tag_IDexp: { goto L14; } break;
                default: { goto L13; } break;
              }
            } else { goto L13; }
          }
          } break;
        case a_Exp::tag_LISTexp: {
          if (
#line 303 "../../prop-src/trs.pcc"
          is_pattern_var(exp)
#line 303 "../../prop-src/trs.pcc"
) {
            
            if (_LISTexp(exp)->_3) {
              L17:; 
              if (_LISTexp(exp)->_3->_2) {
                L18:; 
#line 280 "../../prop-src/trs.pcc"
                
                Exp e2 = LISTexp(_LISTexp(exp)->_1, _LISTexp(exp)->_2, _LISTexp(exp)->_3->_2, _LISTexp(exp)->_4);
                e2->ty = exp->ty;
                return make_term(exp,_LISTexp(exp)->_1->name,
#line 283 "../../prop-src/trs.pcc"
#line 283 "../../prop-src/trs.pcc"
                list_1_(_LISTexp(exp)->_3->_1,list_1_(e2))
#line 283 "../../prop-src/trs.pcc"
#line 283 "../../prop-src/trs.pcc"
                );
                
#line 284 "../../prop-src/trs.pcc"
              } else {
                L19:; 
#line 274 "../../prop-src/trs.pcc"
                
                Exp nil_exp = _LISTexp(exp)->_4 == NOexp ? CONSexp( _LISTexp(exp)->_2, 
#line 275 "../../prop-src/trs.pcc"
#line 275 "../../prop-src/trs.pcc"
                nil_1_
#line 275 "../../prop-src/trs.pcc"
#line 275 "../../prop-src/trs.pcc"
                , NOexp) : _LISTexp(exp)->_4;
                nil_exp->ty = exp->ty;
                return make_term( exp, _LISTexp(exp)->_1->name, 
#line 277 "../../prop-src/trs.pcc"
#line 277 "../../prop-src/trs.pcc"
                list_1_(_LISTexp(exp)->_3->_1,list_1_(nil_exp))
#line 277 "../../prop-src/trs.pcc"
#line 277 "../../prop-src/trs.pcc"
                );
                
#line 278 "../../prop-src/trs.pcc"
              }
            } else { goto L12; }
          } else {
            
            if (_LISTexp(exp)->_3) { goto L17; } else { goto L13; }
          }
          } break;
        case a_Exp::tag_CONSexp: {
          if (
#line 303 "../../prop-src/trs.pcc"
          is_pattern_var(exp)
#line 303 "../../prop-src/trs.pcc"
) {
            
            if (_CONSexp(exp)->_2) { goto L12; } else {
              L20:; 
              if (_CONSexp(exp)->_3) {
                switch (_CONSexp(exp)->_3->tag__) {
                  case a_Exp::tag_TUPLEexp: {
                    L21:; 
#line 270 "../../prop-src/trs.pcc"
                   return make_term( exp, _CONSexp(exp)->_1->name, _TUPLEexp(_CONSexp(exp)->_3)->TUPLEexp); 
#line 270 "../../prop-src/trs.pcc"
                    } break;
                  default: {
                    L22:; 
#line 272 "../../prop-src/trs.pcc"
                   return make_term( exp, _CONSexp(exp)->_1->name, 
#line 272 "../../prop-src/trs.pcc"
#line 272 "../../prop-src/trs.pcc"
                    list_1_(_CONSexp(exp)->_3)
#line 272 "../../prop-src/trs.pcc"
#line 272 "../../prop-src/trs.pcc"
                    ); 
#line 272 "../../prop-src/trs.pcc"
                    } break;
                }
              } else {
                L23:; 
#line 268 "../../prop-src/trs.pcc"
               return make_term( exp, _CONSexp(exp)->_1->name, 
#line 268 "../../prop-src/trs.pcc"
#line 268 "../../prop-src/trs.pcc"
                nil_1_
#line 268 "../../prop-src/trs.pcc"
#line 268 "../../prop-src/trs.pcc"
                ); 
#line 268 "../../prop-src/trs.pcc"
              }
            }
          } else {
            
            if (_CONSexp(exp)->_2) { goto L13; } else { goto L20; }
          }
          } break;
        case a_Exp::tag_MARKEDexp: {
#line 264 "../../prop-src/trs.pcc"
         exp = _MARKEDexp(exp)->_2; 
#line 264 "../../prop-src/trs.pcc"
          } break;
        default: { goto L11; } break;
      }
    } else { goto L11; }
  }
}
#line 307 "../../prop-src/trs.pcc"
#line 307 "../../prop-src/trs.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the rhs
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::make_term( Exp exp, Id id, Exps exps)
{
  int n = length( exps);
  Cons cons = find_cons( id);
  if (cons == NOcons)
    { return CODEterm( exp); }
  FunctorTable::Entry * E = Fmap.type_map.lookup( exp->ty);
  if (E == 0)
    { return CODEterm( exp); }
  
#line 325 "../../prop-src/trs.pcc"
#line 334 "../../prop-src/trs.pcc"
{
  Ty _V3 = cons->alg_ty;
  if (_V3) {
    switch (_V3->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V3)->_1)) {
          switch (_TYCONty(_V3)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 328 "../../prop-src/trs.pcc"
              
              Functor f = Fmap.type_map.value(E) + cons->tag +
              			 (cons->ty == NOty ? 0 : _DATATYPEtycon(_TYCONty(_V3)->_1)->unit);
              	  return CONSterm( f, cons, n, make_term( exps));
              
#line 332 "../../prop-src/trs.pcc"
              } break;
            default: {
              L24:; 
#line 334 "../../prop-src/trs.pcc"
             bug("TRS::make_term"); return CODEterm(exp); 
#line 334 "../../prop-src/trs.pcc"
              } break;
          }
        } else { goto L24; }
        } break;
      default: { goto L24; } break;
    }
  } else { goto L24; }
}
#line 335 "../../prop-src/trs.pcc"
#line 335 "../../prop-src/trs.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the term variable
//
///////////////////////////////////////////////////////////////////////////////

Term TRS::make_term_var(Pat pat, Exp exp)
{
  for (int i = 0; i < num_vars; i++)
  {
    if ( equal( exp, vars[i]))
      return VARterm(i,var_pats[i],vars[i]);
  }
  if (pat == NOpat)
    return CODEterm(exp);
  if (num_vars == MAX_VARS)
     bug("%LTRS::make_term_var() too many variables");
  vars[num_vars] = exp;
  var_pats[num_vars] = pat;
  return VARterm( num_vars++, pat, exp);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create the term from a list of expressions
//
///////////////////////////////////////////////////////////////////////////////

Term * TRS::make_term( Exps exps)
{
  int n = length( exps);
  Term * args = (Term *)mem_pool.m_alloc( sizeof( Term) * n);
  int i = 0;
  for_each( Exp, e, exps)
    args[i++] = make_term( e);
  return args;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a term
//
///////////////////////////////////////////////////////////////////////////////

void TRS::print( std::ostream& s, Term term) const
{
  
#line 384 "../../prop-src/trs.pcc"
#line 432 "../../prop-src/trs.pcc"
{
  switch (term->tag__) {
    case a_Term::tag_CONSterm: {
      switch (_CONSterm(term)->_3) {
        case 2: {
          if (
#line 386 "../../prop-src/trs.pcc"
          is_list_constructor(_CONSterm(term)->_2)
#line 386 "../../prop-src/trs.pcc"
) {
            
#line 387 "../../prop-src/trs.pcc"
            
            s << '#' << _CONSterm(term)->_2->name[1];
            	  Term t = term;
            	  Id comma = "";
            	  
#line 391 "../../prop-src/trs.pcc"
#line 394 "../../prop-src/trs.pcc"
            {
              for (;;) {
                switch (t->tag__) {
                  case a_Term::tag_CONSterm: {
                    switch (_CONSterm(t)->_3) {
                      case 2: {
                        if (
#line 393 "../../prop-src/trs.pcc"
                        (_CONSterm(t)->_1 == _CONSterm(term)->_1)
#line 393 "../../prop-src/trs.pcc"
) {
                          
#line 394 "../../prop-src/trs.pcc"
                        s << comma; print( s, _CONSterm(t)->_4[0]); t = _CONSterm(t)->_4[1]; comma = ", "; 
#line 394 "../../prop-src/trs.pcc"
                        } else {
                           goto L25; }
                      } break;
                      default: { goto L25; }
                    }
                    } break;
                  default: { goto L25; } break;
                }
              }
              L25:;
            }
#line 395 "../../prop-src/trs.pcc"
#line 395 "../../prop-src/trs.pcc"
            
            	  
#line 396 "../../prop-src/trs.pcc"
#line 401 "../../prop-src/trs.pcc"
            {
              switch (t->tag__) {
                case a_Term::tag_CONSterm: {
                  switch (_CONSterm(t)->_3) {
                    case 0: {
                      if (
#line 399 "../../prop-src/trs.pcc"
                      (_CONSterm(term)->_2 && is_list_constructor(_CONSterm(t)->_2))
#line 399 "../../prop-src/trs.pcc"
) {
                        } else {
                        
                        L26:; 
#line 401 "../../prop-src/trs.pcc"
                       s << comma; print( s, t); 
#line 401 "../../prop-src/trs.pcc"
                      }
                    } break;
                    default: { goto L26; }
                  }
                  } break;
                default: { goto L26; } break;
              }
            }
#line 402 "../../prop-src/trs.pcc"
#line 402 "../../prop-src/trs.pcc"
            
            	  s << _CONSterm(term)->_2->name[5];
                
#line 404 "../../prop-src/trs.pcc"
          } else {
            
            L27:; 
#line 406 "../../prop-src/trs.pcc"
            
            s << (_CONSterm(term)->_2 != NOcons ? _CONSterm(term)->_2->name : Fmap.G.functor_name(_CONSterm(term)->_1));
            if (_CONSterm(term)->_3 > 0)
            {
              s << '(';
              for (int i = 0; i < _CONSterm(term)->_3; i++)
              {
                 print(s,_CONSterm(term)->_4[i]);
                 if (i < _CONSterm(term)->_3 - 1)
                   s << ", ";
              }
              s << ')';
            }
            
#line 419 "../../prop-src/trs.pcc"
          }
        } break;
        default: { goto L27; }
      }
      } break;
    case a_Term::tag_VARterm: {
#line 421 "../../prop-src/trs.pcc"
     s << _VARterm(term)->_2; 
#line 421 "../../prop-src/trs.pcc"
      } break;
    case a_Term::tag_CODEterm: {
#line 423 "../../prop-src/trs.pcc"
      
      Bool save = pretty_print_exp;
      pretty_print_exp = true;
      s << "[[" << _CODEterm(term)->CODEterm << "]]";
      pretty_print_exp = save;
      
#line 428 "../../prop-src/trs.pcc"
      } break;
    case a_Term::tag_OPAQUEterm: {
#line 430 "../../prop-src/trs.pcc"
     s << "..."; 
#line 430 "../../prop-src/trs.pcc"
      } break;
    default: {
#line 432 "../../prop-src/trs.pcc"
     s << "[[" << _PATterm(term)->PATterm << "]]"; 
#line 432 "../../prop-src/trs.pcc"
      } break;
  }
}
#line 433 "../../prop-src/trs.pcc"
#line 433 "../../prop-src/trs.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a TRS
//
///////////////////////////////////////////////////////////////////////////////

void TRS::print( std::ostream& s) const
{
  s << "\n\nBottom-up term rewriting system:\n";
  Bool save = pretty_print_exp;
  pretty_print_exp = true;

  for (Rule r = 0; r < number_of_rules; r++)
  {
    MatchRule rule = rule_map[r];
    s << "line " << rule->begin_line << ": ";
    print(s,lhs_map[r]);

    if (guard_map[r] != NOexp)
      s << " | " << guard_map[r];
    s << ":\n\t";
    print( s, rhs_map[r]);
    s << '\n';

    for (int i = 0; i < num_var_map[r]; i++)
    {
      Pat pat_var = var_pat_map[r][i];
      Ty pat_ty   = pat_var->ty;
	  s << "\tvariable " << pat_var << " : " << pat_ty;
      if (! compiler.has_index( pat_ty))
        s << " has no index";
	  s << '\n';
    }
    s << '\n';
  }
  s << '\n';
  pretty_print_exp = save;
}
#line 474 "../../prop-src/trs.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 686
Number of ifs generated      = 38
Number of switches generated = 24
Number of labels             = 23
Number of gotos              = 40
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
