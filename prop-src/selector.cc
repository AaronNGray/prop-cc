///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\selector.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q1("deref_");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q2("derefp");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q6("tag__");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q5("untagp");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q3("_");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q4("untag");
#line 1 "../../prop-src/selector.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the selection/projection code generation.
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <limits.h>
#include <stdlib.h>
#include <AD/strings/quark.h>
#include "ir.h"
#include "ast.h"
#include "matchcom.h"
#include "type.h"
#include "options.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the proper selector into a component argument
//  of a constructor
//
///////////////////////////////////////////////////////////////////////////////

Exp select( Exp e, Cons c, Ty t) { return SELECTORexp( e, c, t); }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the proper selector into a component argument
//  of a constructor
//
///////////////////////////////////////////////////////////////////////////////

Exp MatchCompiler::make_select
    (
      Exp  e,             // the expression
      Cons c,             // constructor
      Ty   expected_ty,   // expected type (if applicable)
      Id   component      // component to extract
    )
{
  Exp  result         = e;
  Bool use_projection = component != 0;
  
#line 43 "../../prop-src/selector.pcc"
#line 149 "../../prop-src/selector.pcc"
{
  if (c) {
    if (c->alg_ty) {
      switch (c->alg_ty->tag__) {
        case a_Ty::tag_TYCONty: {
          if (boxed(_TYCONty(c->alg_ty)->_1)) {
            switch (_TYCONty(c->alg_ty)->_1->tag__) {
              case a_TyCon::tag_DATATYPEtycon: {
                if (
#line 51 "../../prop-src/selector.pcc"
                (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->qualifiers & QUALview)
#line 51 "../../prop-src/selector.pcc"
) {
                  
#line 52 "../../prop-src/selector.pcc"
                  
                  Ty comp_ty = c->ty;
                  if (component)
                  	  {
                  	  
#line 56 "../../prop-src/selector.pcc"
#line 69 "../../prop-src/selector.pcc"
                  {
                    Ty _V1 = c->ty;
                    if (_V1) {
                      switch (_V1->tag__) {
                        case a_Ty::tag_TYCONty: {
                          if (boxed(_TYCONty(_V1)->_1)) {
                            switch (_TYCONty(_V1)->_1->tag__) {
                              case a_TyCon::tag_RECORDtycon: {
#line 64 "../../prop-src/selector.pcc"
                                
                                	        use_projection = false;
                                			comp_ty = component_ty(c->ty,component);
                                		  
#line 67 "../../prop-src/selector.pcc"
                                } break;
                              default: {
                                L1:; 
#line 69 "../../prop-src/selector.pcc"
                               comp_ty = _V1; 
#line 69 "../../prop-src/selector.pcc"
                                } break;
                            }
                          } else {
                            switch ((int)_TYCONty(_V1)->_1) {
                              case ((int)TUPLEtycon): {
#line 59 "../../prop-src/selector.pcc"
                                
                                	        use_projection = false;
                                			comp_ty = component_ty(c->ty,atol(component+1));
                                		  
#line 62 "../../prop-src/selector.pcc"
                                } break;
                              default: { goto L1; } break;
                            }
                          }
                          } break;
                        default: { goto L1; } break;
                      }
                    } else { goto L1; }
                  }
#line 70 "../../prop-src/selector.pcc"
#line 70 "../../prop-src/selector.pcc"
                  
                  }
                  Exp selector_exp = default_val(comp_ty);
                  if (selector_exp == NOexp)
                  {
                    error( "%Lview accessor is undefined for constructor %s\n", c->name);
                    return NOexp;
                  }
                  result = subst(selector_exp,&e);
                  
#line 79 "../../prop-src/selector.pcc"
                } else {
                  
#line 88 "../../prop-src/selector.pcc"
                  
                  Bool simple;
                  
                  
#line 91 "../../prop-src/selector.pcc"
#line 94 "../../prop-src/selector.pcc"
                  {
                    Ty _V2 = c->ty;
                    if (_V2) {
                      switch (_V2->tag__) {
                        case a_Ty::tag_TYCONty: {
                          if (boxed(_TYCONty(_V2)->_1)) {
                            switch (_TYCONty(_V2)->_1->tag__) {
                              case a_TyCon::tag_RECORDtycon: {
                                L2:; 
#line 93 "../../prop-src/selector.pcc"
                               simple = false; 
#line 93 "../../prop-src/selector.pcc"
                                } break;
                              default: {
                                L3:; 
#line 94 "../../prop-src/selector.pcc"
                               simple = true; 
#line 94 "../../prop-src/selector.pcc"
                                } break;
                            }
                          } else {
                            switch ((int)_TYCONty(_V2)->_1) {
                              case ((int)TUPLEtycon): { goto L2; } break;
                              default: { goto L3; } break;
                            }
                          }
                          } break;
                        default: { goto L3; } break;
                      }
                    } else { goto L3; }
                  }
#line 95 "../../prop-src/selector.pcc"
#line 95 "../../prop-src/selector.pcc"
                  
                  
                        if ( is_array_constructor( c->name))
                          simple = false;
                  
                        Id nm = mangle(c->name);
                  
                        if (c->opt & OPTunboxed)
                           result = APPexp( IDexp( 
#line 103 "../../prop-src/selector.pcc"
#line 103 "../../prop-src/selector.pcc"
                  cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q1
#line 103 "../../prop-src/selector.pcc"
#line 103 "../../prop-src/selector.pcc"
                 + c->name), e);
                  else
                  {
                    if ((_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->opt & OPTtaggedpointer) && c->tag != 0)
                      e = APPexp( IDexp( 
#line 107 "../../prop-src/selector.pcc"
#line 107 "../../prop-src/selector.pcc"
                  cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q2
#line 107 "../../prop-src/selector.pcc"
#line 107 "../../prop-src/selector.pcc"
                  ), e);
                  if (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->opt & OPTsubclassless) // No subclass hierarchy
                  {
                    if (simple)
                      result = ARROWexp( e, nm);
                    else
                      result = DEREFexp( e);
                  }
                  else // with subclass hierachy
                  {
                    // Dereference the pointer if the pointer needs to be stripped
                    // of the tag.
                    Exp downcast_exp = NOexp;
                    if (options.inline_casts && _DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->tyvars == 
#line 120 "../../prop-src/selector.pcc"
#line 120 "../../prop-src/selector.pcc"
                  nil_1_
#line 120 "../../prop-src/selector.pcc"
#line 120 "../../prop-src/selector.pcc"
                  )
                  {
                    downcast_exp =
                        CASTexp( mkptrty( mkidty( _DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->id + 
#line 123 "../../prop-src/selector.pcc"
#line 123 "../../prop-src/selector.pcc"
                  cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q3
#line 123 "../../prop-src/selector.pcc"
#line 123 "../../prop-src/selector.pcc"
                 + nm, 
#line 123 "../../prop-src/selector.pcc"
#line 123 "../../prop-src/selector.pcc"
                  nil_1_
#line 123 "../../prop-src/selector.pcc"
#line 123 "../../prop-src/selector.pcc"
                  )), e);
                  }
                  else if (options.inline_casts && expected_ty != NOty)
                  {
                  		    
#line 127 "../../prop-src/selector.pcc"
#line 135 "../../prop-src/selector.pcc"
                  {
                    Ty _V3 = deref_all(expected_ty);
                    if (_V3) {
                      switch (_V3->tag__) {
                        case a_Ty::tag_TYCONty: {
#line 130 "../../prop-src/selector.pcc"
                          
                          downcast_exp =
                                  CASTexp( mkptrty( mkidty( _DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->id + 
#line 132 "../../prop-src/selector.pcc"
#line 132 "../../prop-src/selector.pcc"
                          cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q3
#line 132 "../../prop-src/selector.pcc"
#line 132 "../../prop-src/selector.pcc"
                         + nm, _TYCONty(_V3)->_2)), e);
                          
#line 133 "../../prop-src/selector.pcc"
                          } break;
                        default: {
                          L4:; 
#line 135 "../../prop-src/selector.pcc"
                         bug( "%Lmake_select"); 
#line 135 "../../prop-src/selector.pcc"
                          } break;
                      }
                    } else { goto L4; }
                  }
#line 136 "../../prop-src/selector.pcc"
#line 136 "../../prop-src/selector.pcc"
                  
                  }
                  else
                    downcast_exp = APPexp( IDexp( 
#line 139 "../../prop-src/selector.pcc"
#line 139 "../../prop-src/selector.pcc"
                  cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q3
#line 139 "../../prop-src/selector.pcc"
#line 139 "../../prop-src/selector.pcc"
                 + nm), e);
                  
                            if (simple)
                              result = ARROWexp( downcast_exp, nm);
                            else
                              result = DEREFexp( downcast_exp);
                          }
                        }
                      
#line 147 "../../prop-src/selector.pcc"
                }
                } break;
              default: {
                L5:; } break;
            }
          } else { goto L5; }
          } break;
        default: { goto L5; } break;
      }
    } else { goto L5; }
  } else { goto L5; }
}
#line 149 "../../prop-src/selector.pcc"
#line 149 "../../prop-src/selector.pcc"

  return use_projection ? DOTexp(result,component) : result;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the tag name of a constructor
//
///////////////////////////////////////////////////////////////////////////////

Exp MatchCompiler::tag_name_of( Cons cons, Bool normalized)
{
  
#line 161 "../../prop-src/selector.pcc"
#line 193 "../../prop-src/selector.pcc"
{
  if (cons) {
    if (cons->alg_ty) {
      switch (cons->alg_ty->tag__) {
        case a_Ty::tag_TYCONty: {
          if (cons->ty) {
            L6:; 
            if (boxed(_TYCONty(cons->alg_ty)->_1)) {
              switch (_TYCONty(cons->alg_ty)->_1->tag__) {
                case a_TyCon::tag_DATATYPEtycon: {
                  L7:; 
                  if (
#line 164 "../../prop-src/selector.pcc"
                  (_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->qualifiers & QUALview)
#line 164 "../../prop-src/selector.pcc"
) {
                    
                    L8:; 
#line 165 "../../prop-src/selector.pcc"
                    
                    if (cons->view_predicate == NOexp)
                    {
                      error("%Lview case for constructor %s is undefined\n",cons->name);
                        return NOexp;
                    	  }
                    	  return cons->view_predicate;
                    
#line 172 "../../prop-src/selector.pcc"
                  } else {
                    
                    L9:; 
                    if (
#line 183 "../../prop-src/selector.pcc"
                    (((! normalized) && (_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->tyvars == nil_1_)) && (_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->arg > 1))
#line 183 "../../prop-src/selector.pcc"
) {
                      
                      L10:; 
#line 184 "../../prop-src/selector.pcc"
                      
                      return IDexp( Quark( "a_", _DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->id, "::tag_", mangle( cons->name)));
                      
#line 186 "../../prop-src/selector.pcc"
                    } else {
                      
                      L11:; 
#line 188 "../../prop-src/selector.pcc"
                      
                      int this_tag = tag_of(cons) + (normalized ? _DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->unit : 0);
                      return LITERALexp(INTlit(this_tag));
                      
#line 191 "../../prop-src/selector.pcc"
                    }
                  }
                  } break;
                default: {
                  L12:; 
#line 193 "../../prop-src/selector.pcc"
                 return NOexp; 
#line 193 "../../prop-src/selector.pcc"
                  } break;
              }
            } else { goto L12; }
          } else {
            if (cons->alg_ty) {
              switch (cons->alg_ty->tag__) {
                case a_Ty::tag_TYCONty: {
                  if (boxed(_TYCONty(cons->alg_ty)->_1)) {
                    switch (_TYCONty(cons->alg_ty)->_1->tag__) {
                      case a_TyCon::tag_DATATYPEtycon: {
                        if (
#line 164 "../../prop-src/selector.pcc"
                        (_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->qualifiers & QUALview)
#line 164 "../../prop-src/selector.pcc"
) {
                           goto L8; } else {
                          
                          L13:; 
                          if (
#line 174 "../../prop-src/selector.pcc"
                          (_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->arg == 0)
#line 174 "../../prop-src/selector.pcc"
) {
                            
                            L14:; 
#line 175 "../../prop-src/selector.pcc"
                            
                            return IDexp( mangle( cons->name));
                            
#line 177 "../../prop-src/selector.pcc"
                          } else {
                            
                            L15:; 
#line 179 "../../prop-src/selector.pcc"
                            
                            return CASTexp( integer_ty, IDexp( mangle( cons->name)));
                            
#line 181 "../../prop-src/selector.pcc"
                          }
                        }
                        } break;
                      default: { goto L12; } break;
                    }
                  } else { goto L12; }
                  } break;
                default: { goto L6; } break;
              }
            } else { goto L6; }
          }
          } break;
        default: {
          L16:; 
          if (cons->ty) { goto L12; } else {
            L17:; 
            if (cons->alg_ty) {
              switch (cons->alg_ty->tag__) {
                case a_Ty::tag_TYCONty: {
                  L18:; 
                  if (boxed(_TYCONty(cons->alg_ty)->_1)) {
                    switch (_TYCONty(cons->alg_ty)->_1->tag__) {
                      case a_TyCon::tag_DATATYPEtycon: { goto L13; } break;
                      default: { goto L12; } break;
                    }
                  } else { goto L12; }
                  } break;
                default: { goto L12; } break;
              }
            } else { goto L12; }
          }
          } break;
      }
    } else { goto L16; }
  } else { goto L12; }
}
#line 194 "../../prop-src/selector.pcc"
#line 194 "../../prop-src/selector.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to extract the tag from a term
//
///////////////////////////////////////////////////////////////////////////////

Exp MatchCompiler::untag( Exp e, Ty ty)
{
  
#line 205 "../../prop-src/selector.pcc"
#line 221 "../../prop-src/selector.pcc"
{
  Ty _V4 = deref(ty);
  if (_V4) {
    switch (_V4->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V4)->_1)) {
          switch (_TYCONty(_V4)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
              if (
#line 207 "../../prop-src/selector.pcc"
              (_DATATYPEtycon(_TYCONty(_V4)->_1)->qualifiers & QUALview)
#line 207 "../../prop-src/selector.pcc"
) {
                
#line 208 "../../prop-src/selector.pcc"
                
                if (_DATATYPEtycon(_TYCONty(_V4)->_1)->view_match == NOexp)
                {
                  error("%Lview test for datatype %T is undefined\n", ty);
                  return NOexp;
                }
                return subst(_DATATYPEtycon(_TYCONty(_V4)->_1)->view_match,&e);
                
#line 215 "../../prop-src/selector.pcc"
              } else {
                
                if (
#line 216 "../../prop-src/selector.pcc"
                (_DATATYPEtycon(_TYCONty(_V4)->_1)->arg > 0)
#line 216 "../../prop-src/selector.pcc"
) {
                  
#line 217 "../../prop-src/selector.pcc"
                  
                  return APPexp( IDexp( 
#line 218 "../../prop-src/selector.pcc"
#line 218 "../../prop-src/selector.pcc"
                  cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q4
#line 218 "../../prop-src/selector.pcc"
#line 218 "../../prop-src/selector.pcc"
                  ), e);
                  
#line 219 "../../prop-src/selector.pcc"
                } else {
                  
                  L19:; 
#line 221 "../../prop-src/selector.pcc"
                 return e; 
#line 221 "../../prop-src/selector.pcc"
                }
              }
              } break;
            default: { goto L19; } break;
          }
        } else { goto L19; }
        } break;
      default: { goto L19; } break;
    }
  } else { goto L19; }
}
#line 222 "../../prop-src/selector.pcc"
#line 222 "../../prop-src/selector.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to extract the tag from a term (optimized for arg/unit constructors)
//
///////////////////////////////////////////////////////////////////////////////

Exp MatchCompiler::untag_one( Exp e, Cons c)
{
  
#line 233 "../../prop-src/selector.pcc"
#line 260 "../../prop-src/selector.pcc"
{
  if (c) {
    if (c->alg_ty) {
      switch (c->alg_ty->tag__) {
        case a_Ty::tag_TYCONty: {
          if (c->ty) {
            if (boxed(_TYCONty(c->alg_ty)->_1)) {
              switch (_TYCONty(c->alg_ty)->_1->tag__) {
                case a_TyCon::tag_DATATYPEtycon: {
                  L20:; 
                  if (
#line 236 "../../prop-src/selector.pcc"
                  (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->qualifiers & QUALview)
#line 236 "../../prop-src/selector.pcc"
) {
                    
                    L21:; 
#line 237 "../../prop-src/selector.pcc"
                    
                    if (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->view_match == NOexp)
                    {  error("%Lview test for constructor %s is undefined\n",c->name);
                       return NOexp;
                    }
                    return subst(_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->view_match,&e);
                    
#line 243 "../../prop-src/selector.pcc"
                  } else {
                    
                    L22:; 
#line 250 "../../prop-src/selector.pcc"
                    
                    if (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->opt & OPTtaggedpointer)
                      e = APPexp( IDexp( 
#line 252 "../../prop-src/selector.pcc"
#line 252 "../../prop-src/selector.pcc"
                    cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q5
#line 252 "../../prop-src/selector.pcc"
#line 252 "../../prop-src/selector.pcc"
                    ),e);
                    else if (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->opt & OPTtagless)
                      e = LITERALexp( INTlit(0));
                    else
                      e = ARROWexp( e, 
#line 256 "../../prop-src/selector.pcc"
#line 256 "../../prop-src/selector.pcc"
                    cocofmcocofm_p_r_o_pcn_s_r_cfm_s_e_l_e_c_t_o_rco_c_c_Q6
#line 256 "../../prop-src/selector.pcc"
#line 256 "../../prop-src/selector.pcc"
                    );
                    return e;
                    
#line 258 "../../prop-src/selector.pcc"
                  }
                  } break;
                default: {
                  L23:; 
#line 260 "../../prop-src/selector.pcc"
                 return NOexp; 
#line 260 "../../prop-src/selector.pcc"
                  } break;
              }
            } else { goto L23; }
          } else {
            if (c->alg_ty) {
              switch (c->alg_ty->tag__) {
                case a_Ty::tag_TYCONty: {
                  if (boxed(_TYCONty(c->alg_ty)->_1)) {
                    switch (_TYCONty(c->alg_ty)->_1->tag__) {
                      case a_TyCon::tag_DATATYPEtycon: {
                        if (
#line 236 "../../prop-src/selector.pcc"
                        (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->qualifiers & QUALview)
#line 236 "../../prop-src/selector.pcc"
) {
                           goto L21; } else {
                          
                          L24:; 
                          if (
#line 245 "../../prop-src/selector.pcc"
                          (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->arg == 0)
#line 245 "../../prop-src/selector.pcc"
) {
                            
                            L25:; 
#line 246 "../../prop-src/selector.pcc"
                           return e; 
#line 246 "../../prop-src/selector.pcc"
                          } else {
                            
                            L26:; 
#line 248 "../../prop-src/selector.pcc"
                           return CASTexp( integer_ty, e); 
#line 248 "../../prop-src/selector.pcc"
                          }
                        }
                        } break;
                      default: { goto L26; } break;
                    }
                  } else { goto L26; }
                  } break;
                default: {
                  L27:; 
                  if (boxed(_TYCONty(c->alg_ty)->_1)) {
                    switch (_TYCONty(c->alg_ty)->_1->tag__) {
                      case a_TyCon::tag_DATATYPEtycon: {
                        L28:; 
                        if (
#line 236 "../../prop-src/selector.pcc"
                        (_DATATYPEtycon(_TYCONty(c->alg_ty)->_1)->qualifiers & QUALview)
#line 236 "../../prop-src/selector.pcc"
) {
                           goto L21; } else {
                           goto L26; }
                        } break;
                      default: { goto L26; } break;
                    }
                  } else { goto L26; }
                  } break;
              }
            } else { goto L27; }
          }
          } break;
        default: {
          L29:; 
          if (c->ty) { goto L23; } else {
            L30:; 
            if (c->alg_ty) {
              switch (c->alg_ty->tag__) {
                case a_Ty::tag_TYCONty: {
                  L31:; 
                  if (boxed(_TYCONty(c->alg_ty)->_1)) {
                    switch (_TYCONty(c->alg_ty)->_1->tag__) {
                      case a_TyCon::tag_DATATYPEtycon: { goto L24; } break;
                      default: { goto L26; } break;
                    }
                  } else { goto L26; }
                  } break;
                default: { goto L26; } break;
              }
            } else { goto L26; }
          }
          } break;
      }
    } else { goto L29; }
  } else { goto L23; }
}
#line 261 "../../prop-src/selector.pcc"
#line 261 "../../prop-src/selector.pcc"

}
#line 263 "../../prop-src/selector.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 1358
Number of ifs generated      = 40
Number of switches generated = 24
Number of labels             = 31
Number of gotos              = 47
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
