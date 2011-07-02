///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\printing.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_p_r_i_n_t_i_n_gco_c_c_Q1("x_");
#line 1 "../../prop-src/printing.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements various pretty printing and formating routines.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <strstream>
#include <AD/contain/bitset.h>
#include <AD/strings/charesc.h>
#include <AD/strings/quark.h>
#include <stdio.h>
#include <ctype.h>
#include "ir.h"
#include "ast.h"
#include "matchcom.h"
#include "type.h"
#include "options.h"
#include "list.h"
#include "graphtype.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Flags controlling printing formats of types.
//
///////////////////////////////////////////////////////////////////////////////

Bool      pretty_print_ty      = true;
Bool      pretty_print_pattern = false;
Bool      pretty_print_exp     = false;
Bool      print_semantic_stack = false;
Bool      print_inner_action   = false;
Bool      print_default_value  = true;
Id        ty_id                = 0;
Parameter ty_parameter         = TYformal;

///////////////////////////////////////////////////////////////////////////////
//
//  Print an identifier list
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Ids vars)
{
  for( Ids vs = vars; vs; vs = vs->_2)
  {
    f << vs->_1;
    if (vs->_2)
      f << ", ";
    }
  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print a scope
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Scope s)
{
  
#line 63 "../../prop-src/printing.pcc"
#line 68 "../../prop-src/printing.pcc"
{
  switch (s) {
    case PRIVATEscope: {
#line 67 "../../prop-src/printing.pcc"
   f << "private";
      
#line 68 "../../prop-src/printing.pcc"
      } break;
    case PROTECTEDscope: {
#line 66 "../../prop-src/printing.pcc"
     f << "protected";
      
#line 67 "../../prop-src/printing.pcc"
      } break;
    default: {
#line 65 "../../prop-src/printing.pcc"
  f << "public";
      
#line 66 "../../prop-src/printing.pcc"
      } break;
  }
}
#line 68 "../../prop-src/printing.pcc"
#line 68 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//  Return the label for an tuple element index
///////////////////////////////////////////////////////////////////////////////

Id index_of( int i, Id prefix)
{
  if (prefix == 0)
    prefix = "";
  return Quark( Quark( prefix, "_"), i);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print a persistent id.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Pid pid)
{
  
#line 91 "../../prop-src/printing.pcc"
#line 95 "../../prop-src/printing.pcc"
{
  if (pid) {
#line 93 "../../prop-src/printing.pcc"
   f << pid->PERSISTid; 
#line 93 "../../prop-src/printing.pcc"
  } else {}
}
#line 95 "../../prop-src/printing.pcc"
#line 95 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print a literal.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Literal l)
{
  
#line 107 "../../prop-src/printing.pcc"
#line 138 "../../prop-src/printing.pcc"
{
  switch (l->tag__) {
    case a_Literal::tag_INTlit: {
#line 109 "../../prop-src/printing.pcc"
     f << _INTlit(l)->INTlit; 
#line 109 "../../prop-src/printing.pcc"
      } break;
    case a_Literal::tag_BOOLlit: {
#line 110 "../../prop-src/printing.pcc"
     f << (_BOOLlit(l)->BOOLlit ? "true" : "false"); 
#line 110 "../../prop-src/printing.pcc"
      } break;
    case a_Literal::tag_CHARlit: {
#line 111 "../../prop-src/printing.pcc"
     char b[32]; print_char(b,_CHARlit(l)->CHARlit); f << '\'' << b << '\''; 
#line 111 "../../prop-src/printing.pcc"
      } break;
    case a_Literal::tag_REALlit: {
#line 113 "../../prop-src/printing.pcc"
      
      // use sprintf due to library problems in libg++ 2.5.8 on Linux
      char buf[256];
      sprintf( buf,"%lf", _REALlit(l)->REALlit);
      f << buf;
      // std::ostrstream S(buf,sizeof(buf));
      // std::ostream& S2 = S;
      // S2 << r << std::ends;
      // f << S.str();
      
#line 122 "../../prop-src/printing.pcc"
      } break;
    case a_Literal::tag_STRINGlit: {
#line 123 "../../prop-src/printing.pcc"
     f << _STRINGlit(l)->STRINGlit; 
#line 123 "../../prop-src/printing.pcc"
      } break;
    case a_Literal::tag_REGEXPlit: {
#line 124 "../../prop-src/printing.pcc"
     f << _REGEXPlit(l)->REGEXPlit; 
#line 124 "../../prop-src/printing.pcc"
      } break;
    case a_Literal::tag_QUARKlit: {
#line 126 "../../prop-src/printing.pcc"
      
      if (pretty_print_pattern)
        f << '#' << _QUARKlit(l)->QUARKlit;
      else
        f << MatchCompiler::quark_name(_QUARKlit(l)->QUARKlit);
      
#line 131 "../../prop-src/printing.pcc"
      } break;
    default: {
#line 133 "../../prop-src/printing.pcc"
      
      if (pretty_print_pattern)
        f << "#" << _BIGINTlit(l)->BIGINTlit;
      else
        f << _BIGINTlit(l)->BIGINTlit;
      
#line 138 "../../prop-src/printing.pcc"
      } break;
  }
}
#line 139 "../../prop-src/printing.pcc"
#line 139 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print type list.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Tys tys)
{
  for(Tys t = tys; t; t = t->_2)
  {
    f << t->_1;
    if (t->_2 != 
#line 154 "../../prop-src/printing.pcc"
#line 154 "../../prop-src/printing.pcc"
nil_1_
#line 154 "../../prop-src/printing.pcc"
#line 154 "../../prop-src/printing.pcc"
)
      f << ", ";
  }
  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print type variables (i.e. template actual arguments)
//
///////////////////////////////////////////////////////////////////////////////
void print_tyvars( std::ostream& f, Tys tys, Bool is_datatype)
{
  if (tys != 
#line 167 "../../prop-src/printing.pcc"
#line 167 "../../prop-src/printing.pcc"
nil_1_
#line 167 "../../prop-src/printing.pcc"
#line 167 "../../prop-src/printing.pcc"
)
    if (is_datatype)
      f << "(" << tys << ")";
    else
      f << '<' << tys << "> ";
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print type variables (i.e. formal template arguments)
//
///////////////////////////////////////////////////////////////////////////////

void print_tyvars( std::ostream& f, TyVars tyvars, char open, char close, Bool header)
{
  if (tyvars != 
#line 182 "../../prop-src/printing.pcc"
#line 182 "../../prop-src/printing.pcc"
nil_1_
#line 182 "../../prop-src/printing.pcc"
#line 182 "../../prop-src/printing.pcc"
)
  {
    if (header) f << "template ";
    f << open;
    for(TyVars t = tyvars; t; t = t->_2)
    {
      if (header)
        f << "class ";
      f << t->_1;
      if (t->_2)
        f << ", ";
    }
    f << close;
    if (header)
      f << ' ';
   }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print a tuple type.
//
///////////////////////////////////////////////////////////////////////////////

void print_tuple(std::ostream& f, Tys tys)
{
  if (pretty_print_ty)
    f << '(' << tys << ')';
  else
  {
    f << "struct {";
    int i = 1;
    for (Tys t = tys; t; t = t->_2)
    {
      ty_id = index_of(i);
      f << t->_1 << "; ";
      ty_id = 
#line 218 "../../prop-src/printing.pcc"
#line 218 "../../prop-src/printing.pcc"
nil_1_
#line 218 "../../prop-src/printing.pcc"
#line 218 "../../prop-src/printing.pcc"
;
    }
    f << "} ";
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print a mktuple type
//
///////////////////////////////////////////////////////////////////////////////

void print_mktuple( std::ostream& f, Tys tys)
{
  if (pretty_print_ty)
    f << ".[" << tys << ']';
  else
  {
    f << "Tuple" << length(tys);
    print_tyvars(f,tys,false);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print a record type.
//
///////////////////////////////////////////////////////////////////////////////

void print_record( std::ostream& f, Ids labs, Tys tys, Bool flex)
{
  if ( !pretty_print_ty) f << "struct ";
  f << "{ ";
  Tys t; Ids l;
  for (t = tys, l = labs; t && l; t = t->_2, l = l->_2)
  {
    if (pretty_print_ty)
    {
      f << l->_1 << " : " << t->_1;
      if (t->_2) f << ", ";
    }
    else
    {
      ty_id = l->_1; f << t->_1 << "; ";
      ty_id = 
#line 262 "../../prop-src/printing.pcc"
#line 262 "../../prop-src/printing.pcc"
nil_1_
#line 262 "../../prop-src/printing.pcc"
#line 262 "../../prop-src/printing.pcc"
;
    }
  }
  if (pretty_print_ty && flex)
    f << " ... ";
  f << " }";
}

///////////////////////////////////////////////////////////////////////////////
//
//  Print a function parameter.
//
///////////////////////////////////////////////////////////////////////////////

void print_parameter( std::ostream& f, Ty ty, Id id, Parameter p)
{
  Parameter save = ty_parameter;
  Bool      sp = pretty_print_ty;
  pretty_print_ty = false;
  ty_parameter = p;
  
#line 282 "../../prop-src/printing.pcc"
#line 352 "../../prop-src/printing.pcc"
{
  Ty _V1 = deref(ty);
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_RECORDtycon: {
#line 304 "../../prop-src/printing.pcc"
              
              Ids l;
              Tys t;
              if (p == TYformal || p == TYsimpleformal ||
                  p == TYactual && _TYCONty(_V1)->_2 != 
#line 308 "../../prop-src/printing.pcc"
#line 308 "../../prop-src/printing.pcc"
              nil_1_
#line 308 "../../prop-src/printing.pcc"
#line 308 "../../prop-src/printing.pcc"
              )
              f << '(';
              
              for (l = _RECORDtycon(_TYCONty(_V1)->_1)->_1, t = _TYCONty(_V1)->_2; l && t; l = l->_2, t = t->_2)
              {
              if (p != TYbody)
                ty_id = 
#line 314 "../../prop-src/printing.pcc"
#line 314 "../../prop-src/printing.pcc"
              cocofmcocofm_p_r_o_pcn_s_r_cfm_p_r_i_n_t_i_n_gco_c_c_Q1
#line 314 "../../prop-src/printing.pcc"
#line 314 "../../prop-src/printing.pcc"
             + l->_1;
              else
                ty_id = l->_1;
              if (p != TYactual)
                f << t->_1;
              else
                f << ty_id;
              if (p != TYbody)
              {
                if (t->_2)
                  f << ", ";
              }
              else
                f << "; ";
              ty_id = 
#line 328 "../../prop-src/printing.pcc"
#line 328 "../../prop-src/printing.pcc"
              nil_1_
#line 328 "../../prop-src/printing.pcc"
#line 328 "../../prop-src/printing.pcc"
              ;
              }
              
              if (p == TYformal || p == TYsimpleformal ||
                  p == TYactual && _TYCONty(_V1)->_2 != 
#line 332 "../../prop-src/printing.pcc"
#line 332 "../../prop-src/printing.pcc"
              nil_1_
#line 332 "../../prop-src/printing.pcc"
#line 332 "../../prop-src/printing.pcc"
              )
              f << ')';
              
#line 334 "../../prop-src/printing.pcc"
              } break;
            default: {
              L1:; 
#line 336 "../../prop-src/printing.pcc"
              
              if (p != TYbody)
                f << '(';
              if (p != TYbody)
                ty_id = 
#line 340 "../../prop-src/printing.pcc"
#line 340 "../../prop-src/printing.pcc"
              cocofmcocofm_p_r_o_pcn_s_r_cfm_p_r_i_n_t_i_n_gco_c_c_Q1
#line 340 "../../prop-src/printing.pcc"
#line 340 "../../prop-src/printing.pcc"
             + id;
              else
                ty_id = id;
              if (p != TYactual)
                f << _V1;
              else
                f << ty_id;
              if (p == TYbody)
                f << "; ";
              ty_id = 0;
              if (p != TYbody)
                f << ')';
              
#line 352 "../../prop-src/printing.pcc"
              } break;
          }
        } else {
          switch ((int)_TYCONty(_V1)->_1) {
            case ((int)TUPLEtycon): {
#line 285 "../../prop-src/printing.pcc"
              
              int i = 1;
              if (p == TYformal || p == TYsimpleformal ||
                  p == TYactual && _TYCONty(_V1)->_2 != 
#line 288 "../../prop-src/printing.pcc"
#line 288 "../../prop-src/printing.pcc"
              nil_1_
#line 288 "../../prop-src/printing.pcc"
#line 288 "../../prop-src/printing.pcc"
              ) f << '(';
              for (Tys ts = _TYCONty(_V1)->_2; ts; ts = ts->_2)
              {
                ty_id = index_of(i,(p != TYbody ? "x" : ""));
                if (p != TYactual) f << ts->_1;
                else f << ty_id;
                if (p != TYbody) { if (ts->_2) f << ", "; }
                else f << "; ";
                i++;
                ty_id = 
#line 297 "../../prop-src/printing.pcc"
#line 297 "../../prop-src/printing.pcc"
              nil_1_
#line 297 "../../prop-src/printing.pcc"
#line 297 "../../prop-src/printing.pcc"
              ;
              }
              if (p == TYformal || p == TYsimpleformal ||
                  p == TYactual && _TYCONty(_V1)->_2 != 
#line 300 "../../prop-src/printing.pcc"
#line 300 "../../prop-src/printing.pcc"
              nil_1_
#line 300 "../../prop-src/printing.pcc"
#line 300 "../../prop-src/printing.pcc"
              )
              f << ')';
              
#line 302 "../../prop-src/printing.pcc"
              } break;
            default: { goto L1; } break;
          }
        }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 353 "../../prop-src/printing.pcc"
#line 353 "../../prop-src/printing.pcc"

  ty_parameter = save;
  pretty_print_ty = sp;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a type expression.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Ty ty)
{
  Id this_id = 0;
  if (ty_id)
  {
    this_id = ty_id;
    ty_id = 0;
  }

  ty = deref(ty);
  
#line 374 "../../prop-src/printing.pcc"
#line 480 "../../prop-src/printing.pcc"
{
  if (ty) {
    switch (ty->tag__) {
      case a_Ty::tag_VARty: {
#line 377 "../../prop-src/printing.pcc"
       f << "???"; 
#line 377 "../../prop-src/printing.pcc"
        } break;
      case a_Ty::tag_INDty: {
#line 378 "../../prop-src/printing.pcc"
       f << _INDty(ty)->_1; 
#line 378 "../../prop-src/printing.pcc"
        } break;
      case a_Ty::tag_QUALty: {
#line 446 "../../prop-src/printing.pcc"
        
        if (_QUALty(ty)->_1 & QUALunsigned)
          f << "unsigned ";
        if (_QUALty(ty)->_1 & QUALsigned)
          f << "signed ";
        if ((ty_parameter == TYformal || ty_parameter == TYsimpleformal)
        	      && (_QUALty(ty)->_1 & QUALclass))
          f << (TYCONty((TyCon)REFtycon,
#line 453 "../../prop-src/printing.pcc"
#line 453 "../../prop-src/printing.pcc"
        list_1_(QUALty(QUALconst,_QUALty(ty)->_2))
#line 453 "../../prop-src/printing.pcc"
#line 453 "../../prop-src/printing.pcc"
        ));
        else
          f << _QUALty(ty)->_2;
        if (_QUALty(ty)->_1 & QUALconst)
          f << " const";
        
#line 458 "../../prop-src/printing.pcc"
        } break;
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(ty)->_1)) {
          switch (_TYCONty(ty)->_1->tag__) {
            case a_TyCon::tag_IDtycon: {
#line 391 "../../prop-src/printing.pcc"
              
              if (options.new_type_format && _TYCONty(ty)->_2 != 
#line 392 "../../prop-src/printing.pcc"
#line 392 "../../prop-src/printing.pcc"
              nil_1_
#line 392 "../../prop-src/printing.pcc"
#line 392 "../../prop-src/printing.pcc"
              )
              {
                
#line 394 "../../prop-src/printing.pcc"
#line 411 "../../prop-src/printing.pcc"
              {
                Ty _V2 = deref_all(ty);
                if (_V2) {
                  switch (_V2->tag__) {
                    case a_Ty::tag_TYCONty: {
                      if (boxed(_TYCONty(_V2)->_1)) {
                        switch (_TYCONty(_V2)->_1->tag__) {
                          case a_TyCon::tag_DATATYPEtycon: {
#line 397 "../../prop-src/printing.pcc"
                            
                            if ( !pretty_print_ty) f << "a_";
                            f << _DATATYPEtycon(_TYCONty(_V2)->_1)->id; print_tyvars(f,_TYCONty(ty)->_2,false);
                            if ( !pretty_print_ty)
                            {
                              if (_TYCONty(ty)->_2 == 
#line 402 "../../prop-src/printing.pcc"
#line 402 "../../prop-src/printing.pcc"
                            nil_1_
#line 402 "../../prop-src/printing.pcc"
#line 402 "../../prop-src/printing.pcc"
                            )
                            f << ' ';
                            f << "* ";
                            }
                            
#line 406 "../../prop-src/printing.pcc"
                            } break;
                          default: {
                            L2:; 
#line 408 "../../prop-src/printing.pcc"
                            
                            f << _IDtycon(_TYCONty(ty)->_1)->IDtycon;
                            print_tyvars(f,_TYCONty(ty)->_2,false);
                            
#line 411 "../../prop-src/printing.pcc"
                            } break;
                        }
                      } else { goto L2; }
                      } break;
                    default: { goto L2; } break;
                  }
                } else { goto L2; }
              }
#line 412 "../../prop-src/printing.pcc"
#line 412 "../../prop-src/printing.pcc"
              
              }
              else
              {
                f << _IDtycon(_TYCONty(ty)->_1)->IDtycon;
                
#line 417 "../../prop-src/printing.pcc"
#line 420 "../../prop-src/printing.pcc"
              {
                Ty _V3 = deref_all(ty);
                if (_V3) {
                  switch (_V3->tag__) {
                    case a_Ty::tag_TYCONty: {
                      if (boxed(_TYCONty(_V3)->_1)) {
                        switch (_TYCONty(_V3)->_1->tag__) {
                          case a_TyCon::tag_DATATYPEtycon: {
#line 419 "../../prop-src/printing.pcc"
                           print_tyvars( f, _TYCONty(ty)->_2, !pretty_print_ty); 
#line 419 "../../prop-src/printing.pcc"
                            } break;
                          default: {
                            L3:; 
#line 420 "../../prop-src/printing.pcc"
                           print_tyvars( f, _TYCONty(ty)->_2, false); 
#line 420 "../../prop-src/printing.pcc"
                            } break;
                        }
                      } else { goto L3; }
                      } break;
                    default: { goto L3; } break;
                  }
                } else { goto L3; }
              }
#line 421 "../../prop-src/printing.pcc"
#line 421 "../../prop-src/printing.pcc"
              
              }
              
#line 423 "../../prop-src/printing.pcc"
              } break;
            case a_TyCon::tag_RECORDtycon: {
#line 389 "../../prop-src/printing.pcc"
             print_record(f,_RECORDtycon(_TYCONty(ty)->_1)->_1,_TYCONty(ty)->_2,_RECORDtycon(_TYCONty(ty)->_1)->_2); 
#line 389 "../../prop-src/printing.pcc"
              } break;
            case a_TyCon::tag_ARRAYtycon: {
              if (_TYCONty(ty)->_2) {
                if (_TYCONty(ty)->_2->_2) {
                  L4:; 
#line 478 "../../prop-src/printing.pcc"
                  
                  bug ("operator << (std::ostream&, Ty)");
                  
#line 480 "../../prop-src/printing.pcc"
                } else {
#line 425 "../../prop-src/printing.pcc"
                  
                  if (this_id)
                  {
                    ty_id = this_id;
                    this_id = 0;
                  }
                  f << _TYCONty(ty)->_2->_1 << '[' << _ARRAYtycon(_TYCONty(ty)->_1)->ARRAYtycon << ']';
                  
#line 432 "../../prop-src/printing.pcc"
                }
              } else { goto L4; }
              } break;
            case a_TyCon::tag_DATATYPEtycon: {
              if (_TYCONty(ty)->_2) {
#line 461 "../../prop-src/printing.pcc"
                
                if ( !pretty_print_ty)
                  f << "a_";
                f << _DATATYPEtycon(_TYCONty(ty)->_1)->id;
                print_tyvars( f, _TYCONty(ty)->_2, false);
                if ( !pretty_print_ty)
                {
                  if (_TYCONty(ty)->_2 == 
#line 468 "../../prop-src/printing.pcc"
#line 468 "../../prop-src/printing.pcc"
                nil_1_
#line 468 "../../prop-src/printing.pcc"
#line 468 "../../prop-src/printing.pcc"
                )
                f << ' ';
                f << "* ";
                }
                
#line 472 "../../prop-src/printing.pcc"
              } else {
#line 459 "../../prop-src/printing.pcc"
               f << _DATATYPEtycon(_TYCONty(ty)->_1)->id; 
#line 459 "../../prop-src/printing.pcc"
              }
              } break;
            case a_TyCon::tag_GRAPHtycon: {
#line 384 "../../prop-src/printing.pcc"
             f << _GRAPHtycon(_TYCONty(ty)->_1)->GRAPHtycon->class_name; 
#line 384 "../../prop-src/printing.pcc"
              } break;
            case a_TyCon::tag_NODEtycon: {
#line 385 "../../prop-src/printing.pcc"
             f << _NODEtycon(_TYCONty(ty)->_1)->NODEtycon->graph()->class_name <<"::"<< _NODEtycon(_TYCONty(ty)->_1)->NODEtycon->name(); 
#line 385 "../../prop-src/printing.pcc"
              } break;
            case a_TyCon::tag_EDGEtycon: {
#line 386 "../../prop-src/printing.pcc"
             f << "edge " << _EDGEtycon(_TYCONty(ty)->_1)->EDGEtycon->name(); 
#line 386 "../../prop-src/printing.pcc"
              } break;
            default: { goto L4; } break;
          }
        } else {
          switch ((int)_TYCONty(ty)->_1) {
            case ((int)POINTERtycon): {
              if (_TYCONty(ty)->_2) {
                if (_TYCONty(ty)->_2->_2) { goto L4; } else {
#line 381 "../../prop-src/printing.pcc"
                 f << _TYCONty(ty)->_2->_1 << " *"; 
#line 381 "../../prop-src/printing.pcc"
                }
              } else { goto L4; }
              } break;
            case ((int)REFtycon): {
              if (_TYCONty(ty)->_2) {
                if (_TYCONty(ty)->_2->_2) { goto L4; } else {
#line 382 "../../prop-src/printing.pcc"
                 f << _TYCONty(ty)->_2->_1 << " &"; 
#line 382 "../../prop-src/printing.pcc"
                }
              } else { goto L4; }
              } break;
            case ((int)TUPLEtycon): {
#line 387 "../../prop-src/printing.pcc"
             print_tuple(f,_TYCONty(ty)->_2); 
#line 387 "../../prop-src/printing.pcc"
              } break;
            case ((int)EXTUPLEtycon): {
#line 388 "../../prop-src/printing.pcc"
             print_mktuple(f,_TYCONty(ty)->_2); 
#line 388 "../../prop-src/printing.pcc"
              } break;
            case ((int)FUNtycon): {
              if (_TYCONty(ty)->_2) {
                if (_TYCONty(ty)->_2->_2) {
                  if (_TYCONty(ty)->_2->_2->_2) { goto L4; } else {
#line 383 "../../prop-src/printing.pcc"
                   f << _TYCONty(ty)->_2->_1 << " -> " << _TYCONty(ty)->_2->_2->_1; 
#line 383 "../../prop-src/printing.pcc"
                  }
                } else { goto L4; }
              } else { goto L4; }
              } break;
            default: {
              if (_TYCONty(ty)->_2) { goto L4; } else {
#line 380 "../../prop-src/printing.pcc"
               f << "type"; 
#line 380 "../../prop-src/printing.pcc"
              }
              } break;
          }
        }
        } break;
      case a_Ty::tag_POLYty: {
#line 379 "../../prop-src/printing.pcc"
       f << _POLYty(ty)->_1; 
#line 379 "../../prop-src/printing.pcc"
        } break;
      case a_Ty::tag_DEFVALty: {
#line 434 "../../prop-src/printing.pcc"
        
        if (this_id)
        {
          ty_id = this_id;
          this_id = 0;
        }
        f << _DEFVALty(ty)->_1;
        if (ty_parameter != TYbody && ty_parameter != TYsimpleformal
        	      && print_default_value)
        	    f << " = " << _DEFVALty(ty)->_2;
        
#line 444 "../../prop-src/printing.pcc"
        } break;
      default: {
#line 474 "../../prop-src/printing.pcc"
        
        f << _NESTEDty(ty)->_1 << "::" << _NESTEDty(ty)->_2;
        
#line 476 "../../prop-src/printing.pcc"
        } break;
    }
  } else {
#line 376 "../../prop-src/printing.pcc"
   f << "error"; 
#line 376 "../../prop-src/printing.pcc"
  }
}
#line 481 "../../prop-src/printing.pcc"
#line 481 "../../prop-src/printing.pcc"

  if (this_id)
    f << ' ' << this_id;
  return f;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a pattern list.
//
///////////////////////////////////////////////////////////////////////////////

void print( std::ostream& f, Pats pats, Id open, Id close,
            Bool flex1, Pat p, Bool flex2 = false,
            Pat len = NOpat, Pat array = NOpat)
{
  f << open;
  if (len != NOpat)
  {
    f << " |" << len;
    if (array != NOpat)
      f << " : " << array;
    f << " |";
  }
  if (flex2)
    f << " ... ";
  for (Pats ps = pats; ps; ps = ps->_2)
  {
    f << ps->_1;
    if (ps->_2)
      f << ", ";
  }
  if (flex1 && pats != 
#line 514 "../../prop-src/printing.pcc"
#line 514 "../../prop-src/printing.pcc"
nil_1_
#line 514 "../../prop-src/printing.pcc"
#line 514 "../../prop-src/printing.pcc"
 && p != NOpat)
    f << " ... ";
  if (p != NOpat)
    f << p;
  f << close;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a labeled pattern list.
//
///////////////////////////////////////////////////////////////////////////////

void print( std::ostream& f, LabPats lab_pats, Bool flex)
{
  f << '{';
  for (LabPats ps = lab_pats; ps; ps = ps->_2)
  {
    f << ps->_1.label << " = " << ps->_1.pat;
    if (ps->_2)
      f << ", ";
  }
  f << '}';
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods extract the open and close brace of a list.
//
///////////////////////////////////////////////////////////////////////////////

Id open_of( Cons c)
{
  
#line 547 "../../prop-src/printing.pcc"
#line 558 "../../prop-src/printing.pcc"
{
  if (c) {
#line 550 "../../prop-src/printing.pcc"
    
    char s[3];
    s[0] = c->name[0];
    s[1] = c->name[1];
    s[2] = '\0';
    return Quark(s);
    
#line 556 "../../prop-src/printing.pcc"
  } else {
#line 558 "../../prop-src/printing.pcc"
   return "<\?\?>["; 
#line 558 "../../prop-src/printing.pcc"
  }
}
#line 559 "../../prop-src/printing.pcc"
#line 559 "../../prop-src/printing.pcc"

}

Id close_of( Cons c)
{
  
#line 564 "../../prop-src/printing.pcc"
#line 567 "../../prop-src/printing.pcc"
{
  if (c) {
#line 566 "../../prop-src/printing.pcc"
   return c->name+2; 
#line 566 "../../prop-src/printing.pcc"
  } else {
#line 567 "../../prop-src/printing.pcc"
   return "]"; 
#line 567 "../../prop-src/printing.pcc"
  }
}
#line 568 "../../prop-src/printing.pcc"
#line 568 "../../prop-src/printing.pcc"

}

Id close_of2( Cons c)
{
  
#line 573 "../../prop-src/printing.pcc"
#line 576 "../../prop-src/printing.pcc"
{
  if (c) {
#line 575 "../../prop-src/printing.pcc"
   return c->name + strlen( c->name) - 2; 
#line 575 "../../prop-src/printing.pcc"
  } else {
#line 576 "../../prop-src/printing.pcc"
   return "]"; 
#line 576 "../../prop-src/printing.pcc"
  }
}
#line 577 "../../prop-src/printing.pcc"
#line 577 "../../prop-src/printing.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a pattern list.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Pats ps)
{
  print( f, ps, "", "", false, NOpat);
  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a pattern.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Pat p)
{
  
#line 600 "../../prop-src/printing.pcc"
#line 654 "../../prop-src/printing.pcc"
{
  if (p) {
    switch (p->tag__) {
      case a_Pat::tag_WILDpat: {
#line 603 "../../prop-src/printing.pcc"
       f << '_'; 
#line 603 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_INDpat: {
#line 606 "../../prop-src/printing.pcc"
       f << '?' << _INDpat(p)->_1; 
#line 606 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_POLYpat: {
        if (_POLYpat(p)->_3) {
#line 631 "../../prop-src/printing.pcc"
         f << _POLYpat(p)->_1 << '(' << _POLYpat(p)->_3 << ") = " << _POLYpat(p)->_4; 
#line 631 "../../prop-src/printing.pcc"
        } else {
#line 630 "../../prop-src/printing.pcc"
         f << _POLYpat(p)->_1 << " = " << _POLYpat(p)->_4; 
#line 630 "../../prop-src/printing.pcc"
        }
        } break;
      case a_Pat::tag_IDpat: {
#line 605 "../../prop-src/printing.pcc"
       f << _IDpat(p)->_1; 
#line 605 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_CONSpat: {
        if (_CONSpat(p)->CONSpat) {
          if (_CONSpat(p)->CONSpat->alg_ty) {
            switch (_CONSpat(p)->CONSpat->alg_ty->tag__) {
              case a_Ty::tag_TYCONty: {
                if (boxed(_TYCONty(_CONSpat(p)->CONSpat->alg_ty)->_1)) {
                  switch (_TYCONty(_CONSpat(p)->CONSpat->alg_ty)->_1->tag__) {
                    case a_TyCon::tag_DATATYPEtycon: {
                      if (
#line 624 "../../prop-src/printing.pcc"
                      (_CONSpat(p)->CONSpat->qual & QUALvariable)
#line 624 "../../prop-src/printing.pcc"
) {
                        
#line 625 "../../prop-src/printing.pcc"
                       f << _DATATYPEtycon(_TYCONty(_CONSpat(p)->CONSpat->alg_ty)->_1)->id << "?"; 
#line 625 "../../prop-src/printing.pcc"
                      } else {
                        
                        L5:; 
#line 626 "../../prop-src/printing.pcc"
                       f << _CONSpat(p)->CONSpat->name; 
#line 626 "../../prop-src/printing.pcc"
                      }
                      } break;
                    default: { goto L5; } break;
                  }
                } else { goto L5; }
                } break;
              default: { goto L5; } break;
            }
          } else { goto L5; }
        } else {
#line 627 "../../prop-src/printing.pcc"
         f << "<none>"; 
#line 627 "../../prop-src/printing.pcc"
        }
        } break;
      case a_Pat::tag_APPpat: {
#line 628 "../../prop-src/printing.pcc"
       f << _APPpat(p)->_1 << ' ' << _APPpat(p)->_2; 
#line 628 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_TYPEDpat: {
#line 608 "../../prop-src/printing.pcc"
       f << _TYPEDpat(p)->_1 << " : " << _TYPEDpat(p)->_2; 
#line 608 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_ASpat: {
#line 607 "../../prop-src/printing.pcc"
       f << _ASpat(p)->_1 << " as " << _ASpat(p)->_2; 
#line 607 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_LITERALpat: {
#line 649 "../../prop-src/printing.pcc"
        
        Bool save = pretty_print_pattern;
        pretty_print_pattern = true;
        f << _LITERALpat(p)->LITERALpat;
        pretty_print_pattern = save;
        
#line 654 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_CONTEXTpat: {
#line 637 "../../prop-src/printing.pcc"
        
        f << "<<";
        for (Conses ids = _CONTEXTpat(p)->_1; ids; ids = ids->_2)
        {
          if (ids->_1 != NOcons)
            f << ids->_1->name;
          if (ids->_2)
            f << ", ";
        }
        f << ">>" << _CONTEXTpat(p)->_2;
        
#line 647 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_LEXEMEpat: {
#line 629 "../../prop-src/printing.pcc"
       f << "lexeme class " << _LEXEMEpat(p)->_1; 
#line 629 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_ARRAYpat: {
#line 611 "../../prop-src/printing.pcc"
       print(f,_ARRAYpat(p)->_1,"[","]",_ARRAYpat(p)->_2,NOpat); 
#line 611 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_TUPLEpat: {
#line 609 "../../prop-src/printing.pcc"
       print(f,_TUPLEpat(p)->TUPLEpat,"(",")",false,NOpat); 
#line 609 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_EXTUPLEpat: {
#line 610 "../../prop-src/printing.pcc"
       print(f,_EXTUPLEpat(p)->EXTUPLEpat,".(",")",false,NOpat); 
#line 610 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_RECORDpat: {
#line 612 "../../prop-src/printing.pcc"
       print(f,_RECORDpat(p)->_1,_RECORDpat(p)->_2); 
#line 612 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_LISTpat: {
#line 635 "../../prop-src/printing.pcc"
       print( f, _LISTpat(p)->head, open_of(_LISTpat(p)->nil), close_of(_LISTpat(p)->nil), true, _LISTpat(p)->tail); 
#line 635 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_VECTORpat: {
#line 633 "../../prop-src/printing.pcc"
       print( f, _VECTORpat(p)->elements, open_of(_VECTORpat(p)->cons), close_of2(_VECTORpat(p)->cons), _VECTORpat(p)->tail_flex, NOpat, _VECTORpat(p)->head_flex, _VECTORpat(p)->len, _VECTORpat(p)->array); 
#line 633 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_APPENDpat: {
#line 620 "../../prop-src/printing.pcc"
       f << '(' << _APPENDpat(p)->_1 << " ; " << _APPENDpat(p)->_2 << ')'; 
#line 620 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_GUARDpat: {
#line 619 "../../prop-src/printing.pcc"
       f << _GUARDpat(p)->_1 << " | " << _GUARDpat(p)->_2; 
#line 619 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_LOGICALpat: {
        switch (_LOGICALpat(p)->_1) {
          case NOTpat: {
#line 613 "../../prop-src/printing.pcc"
           f << "(! " << _LOGICALpat(p)->_2 << ")"; 
#line 613 "../../prop-src/printing.pcc"
            } break;
          case ANDpat: {
#line 614 "../../prop-src/printing.pcc"
           f << '(' << _LOGICALpat(p)->_2 << " && " << _LOGICALpat(p)->_3 << ')'; 
#line 614 "../../prop-src/printing.pcc"
            } break;
          case ORpat: {
#line 615 "../../prop-src/printing.pcc"
           f << '(' << _LOGICALpat(p)->_2 << " || " << _LOGICALpat(p)->_3 << ')'; 
#line 615 "../../prop-src/printing.pcc"
            } break;
          case EQUIVpat: {
#line 617 "../../prop-src/printing.pcc"
           f << '(' << _LOGICALpat(p)->_2 << " equiv: " << _LOGICALpat(p)->_3 << ')'; 
#line 617 "../../prop-src/printing.pcc"
            } break;
          case XORpat: {
#line 618 "../../prop-src/printing.pcc"
           f << '(' << _LOGICALpat(p)->_2 << " xor: " << _LOGICALpat(p)->_3 << ')'; 
#line 618 "../../prop-src/printing.pcc"
            } break;
          default: {
#line 616 "../../prop-src/printing.pcc"
           f << '(' << _LOGICALpat(p)->_2 << " implies: " << _LOGICALpat(p)->_3 << ')'; 
#line 616 "../../prop-src/printing.pcc"
            } break;
        }
        } break;
      case a_Pat::tag_BACKEDGEpat: {
#line 604 "../../prop-src/printing.pcc"
       f << '<' << _BACKEDGEpat(p)->_2 << '>'; 
#line 604 "../../prop-src/printing.pcc"
        } break;
      case a_Pat::tag_UNIFYpat: {
#line 621 "../../prop-src/printing.pcc"
       f << '(' << _UNIFYpat(p)->_1 << " := " << _UNIFYpat(p)->_2 << ")"; 
#line 621 "../../prop-src/printing.pcc"
        } break;
      default: {
#line 622 "../../prop-src/printing.pcc"
       f << _MARKEDpat(p)->_2; 
#line 622 "../../prop-src/printing.pcc"
        } break;
    }
  } else {}
}
#line 655 "../../prop-src/printing.pcc"
#line 655 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Convert a string into a suitable encoding
//
///////////////////////////////////////////////////////////////////////////////

void encode_string( char * buf, const char * s)
{
  while (*s)
  {
    unsigned char c = *s++;
    if (c == '"')
    {
      *buf++ = 'X';
      *buf++ = 'X';
    }
    else if (isalnum(c) || c == '_')
    {
      *buf++ = '_';
      *buf++ = c;
    }
    else
    {
       int lo = c % 16, hi = c / 16;
       *buf++ = hi + 'a';
       *buf++ = lo + 'a';
    }
  }
  *buf++ = '\0';
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print the mangled name of list constructors.
//
///////////////////////////////////////////////////////////////////////////////

#line 696 "../../prop-src/printing.pcc"
#line 713 "../../prop-src/printing.pcc"
Id mangle (char const * x_1);
Id mangle (char const * x_1)
{
  if ((x_1 == 0)) {
    
#line 696 "../../prop-src/printing.pcc"
   return "(null)"; 
#line 696 "../../prop-src/printing.pcc"
  } else {
    
    if (_less_string(x_1,"#{}")) {
      if (_less_string(x_1,"#[]")) {
        if (_equal_string(x_1,"#()")) {
#line 701 "../../prop-src/printing.pcc"
       return "nil_2_"; 
#line 701 "../../prop-src/printing.pcc"
}
        else if (_equal_string(x_1,"#(...)")) {
#line 698 "../../prop-src/printing.pcc"
       return "list_2_"; 
#line 698 "../../prop-src/printing.pcc"
}
        else if (_equal_string(x_1,"#[...]")) {
#line 697 "../../prop-src/printing.pcc"
       return "list_1_"; 
#line 697 "../../prop-src/printing.pcc"
}
        else {
        if ((x_1[0] == '\"')) {
          
#line 707 "../../prop-src/printing.pcc"
          
          char buf[256];
          encode_string( buf, x_1);
          return Quark( buf);
          
#line 711 "../../prop-src/printing.pcc"
        } else {
          
#line 712 "../../prop-src/printing.pcc"
         return x_1; 
#line 712 "../../prop-src/printing.pcc"
        }
}
      } else {
        if (_equal_string(x_1,"#[]")) {
#line 700 "../../prop-src/printing.pcc"
       return "nil_1_"; 
#line 700 "../../prop-src/printing.pcc"
}
        else if (_equal_string(x_1,"#{...}")) {
#line 699 "../../prop-src/printing.pcc"
       return "list_3_"; 
#line 699 "../../prop-src/printing.pcc"
}
        else {
        if ((x_1[0] == '\"')) {
          
#line 707 "../../prop-src/printing.pcc"
          
          char buf[256];
          encode_string( buf, x_1);
          return Quark( buf);
          
#line 711 "../../prop-src/printing.pcc"
        } else {
          
#line 712 "../../prop-src/printing.pcc"
         return x_1; 
#line 712 "../../prop-src/printing.pcc"
        }
}
      }
    } else {
      if (_equal_string(x_1,"#{}")) {
#line 702 "../../prop-src/printing.pcc"
     return "nil_3_"; 
#line 702 "../../prop-src/printing.pcc"
}
      else if (_equal_string(x_1,"(|...|)")) {
#line 704 "../../prop-src/printing.pcc"
     return "vector_2_"; 
#line 704 "../../prop-src/printing.pcc"
}
      else if (_equal_string(x_1,"[|...|]")) {
#line 703 "../../prop-src/printing.pcc"
     return "vector_1_"; 
#line 703 "../../prop-src/printing.pcc"
}
      else if (_equal_string(x_1,"{|...|}")) {
#line 705 "../../prop-src/printing.pcc"
     return "vector_3_"; 
#line 705 "../../prop-src/printing.pcc"
}
      else {
      if ((x_1[0] == '\"')) {
        
#line 707 "../../prop-src/printing.pcc"
        
        char buf[256];
        encode_string( buf, x_1);
        return Quark( buf);
        
#line 711 "../../prop-src/printing.pcc"
      } else {
        
#line 712 "../../prop-src/printing.pcc"
       return x_1; 
#line 712 "../../prop-src/printing.pcc"
      }
}
    }
  }
}
#line 713 "../../prop-src/printing.pcc"
#line 713 "../../prop-src/printing.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Method to print the name of a constructor
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& print_cons( std::ostream& f, Cons cons)
{
  
#line 723 "../../prop-src/printing.pcc"
#line 734 "../../prop-src/printing.pcc"
{
  if (cons) {
    if (cons->alg_ty) {
      switch (cons->alg_ty->tag__) {
        case a_Ty::tag_TYCONty: {
          if (cons->ty) {
            if (boxed(_TYCONty(cons->alg_ty)->_1)) {
              switch (_TYCONty(cons->alg_ty)->_1->tag__) {
                case a_TyCon::tag_DATATYPEtycon: {
                  L6:; 
#line 727 "../../prop-src/printing.pcc"
                  
                  if (_DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->opt & OPTsubclassless)
                    f << "a_" << _DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->id;
                  else
                    f << _DATATYPEtycon(_TYCONty(cons->alg_ty)->_1)->id << "_" << mangle( cons->name);
                  
#line 732 "../../prop-src/printing.pcc"
                  } break;
                default: {
                  L7:; 
#line 734 "../../prop-src/printing.pcc"
                bug("print_cons()"); 
#line 734 "../../prop-src/printing.pcc"
                  } break;
              }
            } else { goto L7; }
          } else {
            L8:; 
#line 725 "../../prop-src/printing.pcc"
          f << mangle(cons->name); 
#line 725 "../../prop-src/printing.pcc"
          }
          } break;
        default: {
          L9:; 
          if (cons->ty) { goto L7; } else { goto L8; }
          } break;
      }
    } else { goto L9; }
  } else { goto L7; }
}
#line 735 "../../prop-src/printing.pcc"
#line 735 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print an expression list
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Exps es)
{
  for (Exps l = es; l; l = l->_2)
  {
    f << l->_1;
    if (l->_2)
      f << ',';
  }
  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print an expression.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Exp e)
{
  
#line 764 "../../prop-src/printing.pcc"
#line 974 "../../prop-src/printing.pcc"
{
  if (e) {
    switch (e->tag__) {
      case a_Exp::tag_LITERALexp: {
#line 771 "../../prop-src/printing.pcc"
       f << _LITERALexp(e)->LITERALexp; 
#line 771 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_IDexp: {
#line 767 "../../prop-src/printing.pcc"
       f << _IDexp(e)->IDexp; 
#line 767 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_RELexp: {
        if (
#line 768 "../../prop-src/printing.pcc"
        same_selectors
#line 768 "../../prop-src/printing.pcc"
) {
          
#line 768 "../../prop-src/printing.pcc"
         f << "_0"; 
#line 768 "../../prop-src/printing.pcc"
        } else {
          
#line 769 "../../prop-src/printing.pcc"
         f << '_' << _RELexp(e)->RELexp; 
#line 769 "../../prop-src/printing.pcc"
        }
        } break;
      case a_Exp::tag_DOTexp: {
        if (_DOTexp(e)->_1) {
          switch (_DOTexp(e)->_1->tag__) {
            case a_Exp::tag_SELECTORexp: {
              if (
#line 773 "../../prop-src/printing.pcc"
              pretty_print_exp
#line 773 "../../prop-src/printing.pcc"
) {
                
#line 774 "../../prop-src/printing.pcc"
                
                f << _SELECTORexp(_DOTexp(e)->_1)->_1 << '!' << _SELECTORexp(_DOTexp(e)->_1)->_2->name << '.';
                	  int n = atol(_DOTexp(e)->_2+1);
                	  if (n > 0)
                	    f << n;
                	  else
                	    f << _DOTexp(e)->_2;
                
#line 781 "../../prop-src/printing.pcc"
              } else {
                
#line 785 "../../prop-src/printing.pcc"
               f << MatchCompiler::make_select( _SELECTORexp(_DOTexp(e)->_1)->_1, _SELECTORexp(_DOTexp(e)->_1)->_2, _SELECTORexp(_DOTexp(e)->_1)->_3, _DOTexp(e)->_2); 
#line 785 "../../prop-src/printing.pcc"
              }
              } break;
            case a_Exp::tag_DEREFexp: {
#line 788 "../../prop-src/printing.pcc"
             f << _DEREFexp(_DOTexp(e)->_1)->DEREFexp << "->" << _DOTexp(e)->_2; 
#line 788 "../../prop-src/printing.pcc"
              } break;
            default: {
              L10:; 
#line 789 "../../prop-src/printing.pcc"
             f << _DOTexp(e)->_1 << '.' << _DOTexp(e)->_2; 
#line 789 "../../prop-src/printing.pcc"
              } break;
          }
        } else { goto L10; }
        } break;
      case a_Exp::tag_SELECTORexp: {
        if (
#line 782 "../../prop-src/printing.pcc"
        pretty_print_exp
#line 782 "../../prop-src/printing.pcc"
) {
          
#line 783 "../../prop-src/printing.pcc"
         f << _SELECTORexp(e)->_1 << '!' << _SELECTORexp(e)->_2->name; 
#line 783 "../../prop-src/printing.pcc"
        } else {
          
#line 787 "../../prop-src/printing.pcc"
         f << MatchCompiler::make_select( _SELECTORexp(e)->_1, _SELECTORexp(e)->_2, _SELECTORexp(e)->_3); 
#line 787 "../../prop-src/printing.pcc"
        }
        } break;
      case a_Exp::tag_DEREFexp: {
#line 790 "../../prop-src/printing.pcc"
       f << "(*" << _DEREFexp(e)->DEREFexp << ')'; 
#line 790 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_ARROWexp: {
#line 791 "../../prop-src/printing.pcc"
       f << _ARROWexp(e)->_1 << "->" << _ARROWexp(e)->_2; 
#line 791 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_INDEXexp: {
#line 793 "../../prop-src/printing.pcc"
       f << _INDEXexp(e)->_1 << '[' << _INDEXexp(e)->_2 << ']'; 
#line 793 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_BINOPexp: {
#line 794 "../../prop-src/printing.pcc"
       f << '(' << _BINOPexp(e)->_2 << ' ' << _BINOPexp(e)->_1 << ' ' << _BINOPexp(e)->_3 << ')'; 
#line 794 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_PREFIXexp: {
#line 795 "../../prop-src/printing.pcc"
       f << '(' << _PREFIXexp(e)->_1 << ' ' << _PREFIXexp(e)->_2 << ')'; 
#line 795 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_POSTFIXexp: {
#line 796 "../../prop-src/printing.pcc"
       f << '(' << _POSTFIXexp(e)->_2 << ' ' << _POSTFIXexp(e)->_1 << ')'; 
#line 796 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_APPexp: {
#line 792 "../../prop-src/printing.pcc"
       f << _APPexp(e)->_1 << '(' << _APPexp(e)->_2 << ')'; 
#line 792 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_ASSIGNexp: {
#line 772 "../../prop-src/printing.pcc"
       f << '(' << _ASSIGNexp(e)->_1 << " = " << _ASSIGNexp(e)->_2 << ')'; 
#line 772 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_IFexp: {
#line 811 "../../prop-src/printing.pcc"
       f << '(' << _IFexp(e)->_1 << " ? " << _IFexp(e)->_2 << " : " << _IFexp(e)->_3 <<')';
#line 811 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_TUPLEexp: {
#line 809 "../../prop-src/printing.pcc"
       f << _TUPLEexp(e)->TUPLEexp; 
#line 809 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_EXTUPLEexp: {
#line 810 "../../prop-src/printing.pcc"
       f << "mkTuple" << length(_EXTUPLEexp(e)->EXTUPLEexp) << '(' << _EXTUPLEexp(e)->EXTUPLEexp << ')'; 
#line 810 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_RECORDexp: {
#line 917 "../../prop-src/printing.pcc"
        
        f << "{ ";
        for (LabExps l = _RECORDexp(e)->RECORDexp; l; l = l->_2)
          {
          f << l->_1.label << " = " << l->_1.exp;
          if (l->_2)
            f << ", ";
        }
        f << " }";
        
#line 926 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_LISTexp: {
        if (
#line 927 "../../prop-src/printing.pcc"
        pretty_print_exp
#line 927 "../../prop-src/printing.pcc"
) {
          
#line 928 "../../prop-src/printing.pcc"
          
          f << open_of(_LISTexp(e)->_2);
          	  for( Exps exp_list = _LISTexp(e)->_3; exp_list; exp_list = exp_list->_2)
          	  {
          	    f << exp_list->_1;
          	    if (exp_list->_2)
          	      f << ", ";
          }
          	  if (_LISTexp(e)->_4 != NOexp)
          	    f << " ... " << _LISTexp(e)->_4;
          f << close_of(_LISTexp(e)->_2);
          
#line 939 "../../prop-src/printing.pcc"
        } else {
          
          if (_LISTexp(e)->_1) {
            if (_LISTexp(e)->_2) {
#line 941 "../../prop-src/printing.pcc"
              
              int i = 0;
              for( Exps exp_list = _LISTexp(e)->_3; exp_list; exp_list = exp_list->_2)
              	  {
              	    Exp exp = exp_list->_1;
                f << mangle(_LISTexp(e)->_1->name) << '(' << exp;
              	    if (exp_list->_2)
              	      f << ',';
              	    i++;
              }
              if (_LISTexp(e)->_4 != NOexp)
                f << ',' << _LISTexp(e)->_4;
              	  else if (_LISTexp(e)->_3 == 
#line 953 "../../prop-src/printing.pcc"
#line 953 "../../prop-src/printing.pcc"
              nil_1_
#line 953 "../../prop-src/printing.pcc"
#line 953 "../../prop-src/printing.pcc"
              )
              	    f << mangle(_LISTexp(e)->_2->name);
                    while (i-- > 0)
                      f << ')';
                  
#line 957 "../../prop-src/printing.pcc"
            } else {
              L11:; }
          } else { goto L11; }
        }
        } break;
      case a_Exp::tag_VECTORexp: {
        if (_VECTORexp(e)->_1) {
#line 960 "../../prop-src/printing.pcc"
          
          f << mangle(_VECTORexp(e)->_1->name) << '(';
          {
            for(Exps exps = _VECTORexp(e)->_2; exps; exps = exps->_2)
            {
              f << exps->_1;
              if (exps->_2 != 
#line 966 "../../prop-src/printing.pcc"
#line 966 "../../prop-src/printing.pcc"
          nil_1_
#line 966 "../../prop-src/printing.pcc"
#line 966 "../../prop-src/printing.pcc"
          )
          f << ',';
          }
          }
          f << ')';
          
#line 971 "../../prop-src/printing.pcc"
        } else {}
        } break;
      case a_Exp::tag_CONSexp: {
        if (_CONSexp(e)->_1) {
          if (_CONSexp(e)->_3) {
            switch (_CONSexp(e)->_3->tag__) {
              case a_Exp::tag_RECORDexp: {
                if (_CONSexp(e)->_1->ty) {
                  switch (_CONSexp(e)->_1->ty->tag__) {
                    case a_Ty::tag_TYCONty: {
                      if (boxed(_TYCONty(_CONSexp(e)->_1->ty)->_1)) {
                        switch (_TYCONty(_CONSexp(e)->_1->ty)->_1->tag__) {
                          case a_TyCon::tag_RECORDtycon: {
                            if (_CONSexp(e)->_3) {
                              switch (_CONSexp(e)->_3->tag__) {
                                case a_Exp::tag_RECORDexp: {
                                  L12:; 
#line 838 "../../prop-src/printing.pcc"
                                // rearrange arguments to
                                  if (_CONSexp(e)->_2)
                                  {
                                    f << "new (" << _CONSexp(e)->_2 << ") ";
                                    print_cons( f, _CONSexp(e)->_1);
                                  }
                                  else
                                    f << mangle(_CONSexp(e)->_1->name);
                                  
                                  f << '(';
                                  
                                  {
                                    for_each ( LabExp, i, _RECORDexp(_CONSexp(e)->_3)->RECORDexp)
                                    {
                                      for_each ( Id, j, _RECORDtycon(_TYCONty(_CONSexp(e)->_1->ty)->_1)->_1)
                                        if (i.label == j)
                                          goto next;
                                      error( "%Lillegal record label '%s' in expression: %s%e\n",
                                             i.label, _CONSexp(e)->_1->name, _CONSexp(e)->_3);
                                      next: ;
                                    }
                                  }
                                  {
                                    Bool comma = false;
                                    Ids is; Tys ts;
                                    for(is = _RECORDtycon(_TYCONty(_CONSexp(e)->_1->ty)->_1)->_1, ts = _TYCONty(_CONSexp(e)->_1->ty)->_2; is; is = is->_2, ts = ts->_2)
                                    {
                                      Id i = is->_1;
                                      Bool found = false;
                                      for_each (LabExp, j, _RECORDexp(_CONSexp(e)->_3)->RECORDexp)
                                      {
                                        if (i == j.label) {
                                          if (found)
                                            error( "%Lduplicated label '%s' in expression: %s%e\n",
                                                   j.label, _CONSexp(e)->_1->name, _CONSexp(e)->_3);
                                          found = true;
                                          if (comma)
                                            f << ", ";
                                          comma = true;
                                          f << j.exp;
                                        }
                                      }
                                      if ( !found)
                                      {
                                        
#line 882 "../../prop-src/printing.pcc"
#line 892 "../../prop-src/printing.pcc"
                                  {
                                    Exp _V4 = default_val(ts->_1);
                                    if (_V4) {
#line 887 "../../prop-src/printing.pcc"
                                      
                                      if (comma)
                                        f << ", ";
                                      comma = true;
                                      f << _V4;
                                      
#line 892 "../../prop-src/printing.pcc"
                                    } else {
#line 885 "../../prop-src/printing.pcc"
                                     error ("%Lmissing label '%s' in expression: %s%e\n", i, _CONSexp(e)->_1->name, _CONSexp(e)->_3); 
#line 885 "../../prop-src/printing.pcc"
                                    }
                                  }
#line 893 "../../prop-src/printing.pcc"
#line 893 "../../prop-src/printing.pcc"
                                  
                                  }
                                  }
                                  }
                                  f << ')';
                                  
#line 898 "../../prop-src/printing.pcc"
                                  } break;
                                default: {
                                  L13:; 
#line 900 "../../prop-src/printing.pcc"
                                  
                                  error("%Lconstructor '%s' doesn't take labeled arguments\n", _CONSexp(e)->_1->name);
                                  
#line 902 "../../prop-src/printing.pcc"
                                  } break;
                              }
                            } else { goto L13; }
                            } break;
                          default: { goto L13; } break;
                        }
                      } else { goto L13; }
                      } break;
                    default: { goto L13; } break;
                  }
                } else { goto L13; }
                } break;
              default: {
                L14:; 
                if (_CONSexp(e)->_1->ty) {
                  switch (_CONSexp(e)->_1->ty->tag__) {
                    case a_Ty::tag_TYCONty: {
                      L15:; 
                      if (boxed(_TYCONty(_CONSexp(e)->_1->ty)->_1)) {
                        switch (_TYCONty(_CONSexp(e)->_1->ty)->_1->tag__) {
                          case a_TyCon::tag_RECORDtycon: {
                            L16:; 
                            if (_CONSexp(e)->_3) {
                              switch (_CONSexp(e)->_3->tag__) {
                                case a_Exp::tag_RECORDexp: { goto L12; } break;
                                default: {
                                  L17:; 
#line 906 "../../prop-src/printing.pcc"
                                  
                                  if (_CONSexp(e)->_2)
                                  {
                                    f << "new (" << _CONSexp(e)->_2 << ") ";
                                    print_cons(f,_CONSexp(e)->_1);
                                  }
                                  else
                                    f << mangle(_CONSexp(e)->_1->name);
                                  f << '(' << _CONSexp(e)->_3 << ')';
                                  
#line 915 "../../prop-src/printing.pcc"
                                  } break;
                              }
                            } else { goto L17; }
                            } break;
                          default: { goto L17; } break;
                        }
                      } else { goto L17; }
                      } break;
                    default: { goto L17; } break;
                  }
                } else {
                  L18:; 
                  if (_CONSexp(e)->_2) { goto L17; } else {
                    L19:; 
                    if (_CONSexp(e)->_3) { goto L17; } else {
                      L20:; 
#line 904 "../../prop-src/printing.pcc"
                    f << mangle(_CONSexp(e)->_1->name); 
#line 904 "../../prop-src/printing.pcc"
                    }
                  }
                }
                } break;
            }
          } else { goto L14; }
        } else {
          L21:; 
#line 974 "../../prop-src/printing.pcc"
         bug("operator << (std::ostream&, Exp);"); 
#line 974 "../../prop-src/printing.pcc"
        }
        } break;
      case a_Exp::tag_CASTexp: {
#line 798 "../../prop-src/printing.pcc"
        
        Bool save = pretty_print_ty;
        pretty_print_ty = false;
        f << "((" << _CASTexp(e)->_1 << ')' << _CASTexp(e)->_2 << ')';
        pretty_print_ty = save;
        
#line 803 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_QUALexp: {
#line 804 "../../prop-src/printing.pcc"
       f << _QUALexp(e)->_1 << "::" << _QUALexp(e)->_2; 
#line 804 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_EQexp: {
#line 805 "../../prop-src/printing.pcc"
       f << "equality_of(" << _EQexp(e)->_2 << ',' << _EQexp(e)->_3 << ')'; 
#line 805 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_UNIFYexp: {
#line 806 "../../prop-src/printing.pcc"
       f << "unify(" << _UNIFYexp(e)->_2 << ',' << _UNIFYexp(e)->_3 << ')'; 
#line 806 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_LTexp: {
#line 807 "../../prop-src/printing.pcc"
       f << '(' << _LTexp(e)->_2 << " < " << _LTexp(e)->_3 << ')'; 
#line 807 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_HASHexp: {
#line 808 "../../prop-src/printing.pcc"
       f << "hash(" << _HASHexp(e)->_2 << ')'; 
#line 808 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_THISCOSTexp: {
#line 834 "../../prop-src/printing.pcc"
       f << "t__->cost"; 
#line 834 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_COSTexp: {
#line 833 "../../prop-src/printing.pcc"
       f << "t__->kids[" << _COSTexp(e)->COSTexp << "]->cost"; 
#line 833 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_THISSYNexp: {
#line 827 "../../prop-src/printing.pcc"
        
        if (_THISSYNexp(e)->_3)
          f << "__";
        else // in parser
          f << "t__->u._" << _THISSYNexp(e)->_1;
        
#line 832 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_SYNexp: {
#line 813 "../../prop-src/printing.pcc"
        
        if (_SYNexp(e)->_4)
          f << '_' << _SYNexp(e)->_1 << "__";
        else if (_SYNexp(e)->_2 < 0) // parser semantic action
        {
          if (_SYNexp(e)->_1 == 0)
            f << "syn_" << "._" << -_SYNexp(e)->_2;
          else
            f << "t__[" << _SYNexp(e)->_1 << "+to__]._" << -_SYNexp(e)->_2;
        }
        else
          f << "t__->kids[" << _SYNexp(e)->_1 << "]->u._" << _SYNexp(e)->_2;
        
#line 825 "../../prop-src/printing.pcc"
        } break;
      case a_Exp::tag_MARKEDexp: {
#line 770 "../../prop-src/printing.pcc"
       f << _MARKEDexp(e)->_2; 
#line 770 "../../prop-src/printing.pcc"
        } break;
      default: { goto L21; } break;
    }
  } else {
#line 766 "../../prop-src/printing.pcc"
   
#line 766 "../../prop-src/printing.pcc"
  }
}
#line 975 "../../prop-src/printing.pcc"
#line 975 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print an inheritance type.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Inherit i)
{
  if (i->qualifiers & QUALvirtual)
    f << "virtual ";
  return f << i->scope << ' ' << i->super_class;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a class inheritance list.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Inherits i)
{
  for ( ;i; i = i->_2)
  {
    f << i->_1;
    if (i->_2)
      f << ", ";
  }
  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a cost expression
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Cost c)
{
  
#line 1017 "../../prop-src/printing.pcc"
#line 1021 "../../prop-src/printing.pcc"
{
  if (c) {
    if (c->tag__) {
      
#line 1021 "../../prop-src/printing.pcc"
     f << " \\ " << _INTcost(c)->INTcost; 
#line 1021 "../../prop-src/printing.pcc"
    } else {
      
#line 1020 "../../prop-src/printing.pcc"
     f << " \\ " << _EXPcost(c)->_1; 
#line 1020 "../../prop-src/printing.pcc"
    }
  } else {}
}
#line 1022 "../../prop-src/printing.pcc"
#line 1022 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a qualified identifier.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, QualId id)
{
  
#line 1034 "../../prop-src/printing.pcc"
#line 1038 "../../prop-src/printing.pcc"
{
  if (id->tag__) {
    
    if (
#line 1037 "../../prop-src/printing.pcc"
    isalpha(_SIMPLEid(id)->SIMPLEid[0])
#line 1037 "../../prop-src/printing.pcc"
) {
      
#line 1037 "../../prop-src/printing.pcc"
     f << _SIMPLEid(id)->SIMPLEid; 
#line 1037 "../../prop-src/printing.pcc"
    } else {
      
#line 1038 "../../prop-src/printing.pcc"
     f << "operator " << _SIMPLEid(id)->SIMPLEid; 
#line 1038 "../../prop-src/printing.pcc"
    }
  } else {
    
#line 1036 "../../prop-src/printing.pcc"
   f << _NESTEDid(id)->_1 << "::" << _NESTEDid(id)->_2; 
#line 1036 "../../prop-src/printing.pcc"
  }
}
#line 1039 "../../prop-src/printing.pcc"
#line 1039 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//  Method to print a pattern match rule.
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, MatchRule mr)
{
  
#line 1049 "../../prop-src/printing.pcc"
#line 1061 "../../prop-src/printing.pcc"
{
#line 1052 "../../prop-src/printing.pcc"
  
  Bool save = pretty_print_exp;
  	  pretty_print_exp = true;
  	  if (mr->_1)
  	    f << mr->_1 << " -> ";
  f << mr->_2;
  if (mr->_3 != NOexp) f << " | " << mr->_3;
  f << mr->_4 << ": ...";
  	  pretty_print_exp = save;
  
#line 1061 "../../prop-src/printing.pcc"
}
#line 1062 "../../prop-src/printing.pcc"
#line 1062 "../../prop-src/printing.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to pretty print a decision tree.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Match m)
{
  
#line 1074 "../../prop-src/printing.pcc"
#line 1142 "../../prop-src/printing.pcc"
{
  if (boxed(m)) {
    switch (m->tag__) {
      case a_Match::tag_SUCCESSmatch: {
#line 1079 "../../prop-src/printing.pcc"
       f << _SUCCESSmatch(m)->_1; 
#line 1079 "../../prop-src/printing.pcc"
        } break;
      case a_Match::tag_SUCCESSESmatch: {
#line 1082 "../../prop-src/printing.pcc"
        
        f << '{';
        Bool comma = false;
        for (int i = 0; i < _SUCCESSESmatch(m)->_1; i++)
          if ((*_SUCCESSESmatch(m)->_2)[i])
          {
            if (comma)
              f << ", ";
            f << i;
            comma = true;
          }
        f << '}';
        
#line 1094 "../../prop-src/printing.pcc"
        } break;
      case a_Match::tag_COSTmatch: {
#line 1096 "../../prop-src/printing.pcc"
        
        f << '{';
        Bool comma = false;
        for (int i = 0; i < _COSTmatch(m)->_1; i++)
          if ((*_COSTmatch(m)->_3)[i])
          {
             if (comma)
               f << ", ";
             f << _COSTmatch(m)->_2[i] << " = " << i;
             comma = true;
          }
        f << '}';
        
#line 1108 "../../prop-src/printing.pcc"
        } break;
      case a_Match::tag_GUARDmatch: {
#line 1080 "../../prop-src/printing.pcc"
       f << _GUARDmatch(m)->_1 << '(' << _GUARDmatch(m)->_2 << ',' << _GUARDmatch(m)->_3 << ')'; 
#line 1080 "../../prop-src/printing.pcc"
        } break;
      case a_Match::tag_LITERALmatch: {
        switch (_LITERALmatch(m)->_3[0]->tag__) {
          case a_Literal::tag_REGEXPlit: {
#line 1114 "../../prop-src/printing.pcc"
            
            f << "[\n";
            for (int i = 0; i < _LITERALmatch(m)->_4; i++)
              f << "  {" << i << "}" << _LITERALmatch(m)->_3[i] << " => " << _LITERALmatch(m)->_5[i] << ",\n";
            f << _LITERALmatch(m)->_6 << ']';
            
#line 1119 "../../prop-src/printing.pcc"
            } break;
          default: {
#line 1121 "../../prop-src/printing.pcc"
            
            f << '[';
            for (int i = 0; i < _LITERALmatch(m)->_4; i++)
              f << _LITERALmatch(m)->_3[i] << ':' << _LITERALmatch(m)->_5[i] << ", ";
            f << _LITERALmatch(m)->_6 << ']';
            
#line 1126 "../../prop-src/printing.pcc"
            } break;
        }
        } break;
      case a_Match::tag_RANGEmatch: {
#line 1140 "../../prop-src/printing.pcc"
       f << '[' << _RANGEmatch(m)->_3 << ".." << _RANGEmatch(m)->_4 << ": " << _RANGEmatch(m)->_5 << ", " << _RANGEmatch(m)->_6 << ']'; 
#line 1140 "../../prop-src/printing.pcc"
        } break;
      case a_Match::tag_CONSmatch: {
        if (_CONSmatch(m)->_4) {
          switch (_CONSmatch(m)->_4->tag__) {
            case a_Ty::tag_TYCONty: {
              if (boxed(_TYCONty(_CONSmatch(m)->_4)->_1)) {
                switch (_TYCONty(_CONSmatch(m)->_4)->_1->tag__) {
                  case a_TyCon::tag_DATATYPEtycon: {
#line 1128 "../../prop-src/printing.pcc"
                    
                    f << _DATATYPEtycon(_TYCONty(_CONSmatch(m)->_4)->_1)->id << '[';
                    for (int i = 0; i < _CONSmatch(m)->_5; i++)
                    {
                      f << _CONSmatch(m)->_6[i];
                      if (i < _CONSmatch(m)->_5 - 1) f << ", ";
                    }
                    if (_DATATYPEtycon(_TYCONty(_CONSmatch(m)->_4)->_1)->qualifiers & QUALextensible)
                      f << ", " << _CONSmatch(m)->_7;
                    f << ']';
                    
#line 1138 "../../prop-src/printing.pcc"
                    } break;
                  default: {
                    L22:; 
#line 1142 "../../prop-src/printing.pcc"
                   bug("operator << (std::ostream&, Match);"); 
#line 1142 "../../prop-src/printing.pcc"
                    } break;
                }
              } else { goto L22; }
              } break;
            default: { goto L22; } break;
          }
        } else { goto L22; }
        } break;
      case a_Match::tag_TREECOSTmatch: {
#line 1110 "../../prop-src/printing.pcc"
       f << "TREE{" << *_TREECOSTmatch(m)->_2 << "} => " << _TREECOSTmatch(m)->_1; 
#line 1110 "../../prop-src/printing.pcc"
        } break;
      case a_Match::tag_TREELABELmatch: {
#line 1112 "../../prop-src/printing.pcc"
       f << "LABEL{" << _TREELABELmatch(m)->_2 << "(" << _TREELABELmatch(m)->_4 << ")} => " << _TREELABELmatch(m)->_1; 
#line 1112 "../../prop-src/printing.pcc"
        } break;
      default: {
#line 1078 "../../prop-src/printing.pcc"
       f << '<' << _BACKEDGEmatch(m)->_2 << '>'; 
#line 1078 "../../prop-src/printing.pcc"
        } break;
    }
  } else {
    if (m) {
      
#line 1077 "../../prop-src/printing.pcc"
     f << '-'; 
#line 1077 "../../prop-src/printing.pcc"
    } else {
      
#line 1076 "../../prop-src/printing.pcc"
     f << '_'; 
#line 1076 "../../prop-src/printing.pcc"
    }
  }
}
#line 1143 "../../prop-src/printing.pcc"
#line 1143 "../../prop-src/printing.pcc"

  return f;
}
#line 1146 "../../prop-src/printing.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 4392
Number of ifs generated      = 77
Number of switches generated = 31
Number of labels             = 22
Number of gotos              = 47
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
