///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\setltype.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/setltype.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the type checker for the SETL-like sublanguage.
//
///////////////////////////////////////////////////////////////////////////////

#include "ir.h"
#include "ast.h"
#include "setl-ast.h"
#include "setlgen.h"
#include "type.h"
#include "env.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Method to elaborate a definition.
//
///////////////////////////////////////////////////////////////////////////////

Env type_of( Def def, const Env& E)
{
  return E;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to elaborate a definition list.
//
///////////////////////////////////////////////////////////////////////////////
Env type_of( Defs defs, const Env& E)
{
  return E;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to unify two expressions type.
//
///////////////////////////////////////////////////////////////////////////////
Bool unify( Exp exp, Ty a, Ty b)
{
  if (! unify(a,b))
  {
    error( "%Ltype mismatch in expression: %f\n"
           "%Lexpecting '%T' but found '%T'\n", exp, a, b);
    return false;
  }
  else
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to infer the type of an expression.
//
///////////////////////////////////////////////////////////////////////////////

Ty type_of( Exp exp, const Env& E)
{
  Ty ty = NOty;
  
#line 61 "../../prop-src/setltype.pcc"
#line 121 "../../prop-src/setltype.pcc"
{
  if (exp) {
    switch (exp->tag__) {
      case a_Exp::tag_LITERALexp: {
#line 63 "../../prop-src/setltype.pcc"
       ty = type_of(_LITERALexp(exp)->LITERALexp); 
#line 63 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_IDexp: {
#line 64 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 64 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_RELexp: {
#line 73 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 73 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_DOTexp: {
#line 74 "../../prop-src/setltype.pcc"
       ty = component_ty(type_of(_DOTexp(exp)->_1,E),_DOTexp(exp)->_2); 
#line 74 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_SELECTORexp: {
#line 75 "../../prop-src/setltype.pcc"
       ty = component_ty(type_of(_SELECTORexp(exp)->_1,E),_SELECTORexp(exp)->_2); 
#line 75 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_DEREFexp: {
#line 76 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 76 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_ARROWexp: {
#line 77 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 77 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_INDEXexp: {
#line 78 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 78 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_BINOPexp: {
#line 79 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 79 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_PREFIXexp: {
#line 80 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 80 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_POSTFIXexp: {
#line 81 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 81 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_APPexp: {
#line 82 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 82 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_ASSIGNexp: {
#line 83 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 83 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_IFexp: {
#line 84 "../../prop-src/setltype.pcc"
       ty = mkvar(); 
#line 84 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_TUPLEexp: {
#line 85 "../../prop-src/setltype.pcc"
       return mktuplety(type_of(_TUPLEexp(exp)->TUPLEexp,E)); 
#line 85 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_EXTUPLEexp: {
#line 86 "../../prop-src/setltype.pcc"
       return extuplety(type_of(_EXTUPLEexp(exp)->EXTUPLEexp,E)); 
#line 86 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_RECORDexp: {
#line 88 "../../prop-src/setltype.pcc"
        
        
#line 89 "../../prop-src/setltype.pcc"
Tuple2<Ids, Tys>  
#line 89 "../../prop-src/setltype.pcc"
       t = type_of( _RECORDexp(exp)->RECORDexp, E);
        return mkrecordty( t._1, t._2, false);
        } break;
      case a_Exp::tag_LISTexp: {
        if (_LISTexp(exp)->_1) {
#line 94 "../../prop-src/setltype.pcc"
          
          Tys head_tys = type_of( _LISTexp(exp)->_3, E);
          	  Ty  tail_ty  = type_of( _LISTexp(exp)->_4, E);
          	  Ty  arg_ty   = mkvar();
          	  for_each (Ty, one_ty, head_tys)
          	    unify( exp, one_ty, arg_ty);
          Ty fun_ty = inst( _LISTexp(exp)->_1->cons_ty);
          	  ty = mkvar();
          	  unify( exp, fun_ty, mkfunty( mktuplety( 
#line 102 "../../prop-src/setltype.pcc"
#line 102 "../../prop-src/setltype.pcc"
          list_1_(arg_ty,list_1_(mkvar()))
#line 102 "../../prop-src/setltype.pcc"
#line 102 "../../prop-src/setltype.pcc"
          ), ty));
          if (_LISTexp(exp)->_4 != NOexp)
            unify( exp, tail_ty, ty);
          
#line 105 "../../prop-src/setltype.pcc"
        } else {
          L1:; 
#line 121 "../../prop-src/setltype.pcc"
         ty = NOty; 
#line 121 "../../prop-src/setltype.pcc"
        }
        } break;
      case a_Exp::tag_VECTORexp: {
#line 106 "../../prop-src/setltype.pcc"
       return mkvar(); 
#line 106 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_CONSexp: {
        if (_CONSexp(exp)->_1) {
          if (_CONSexp(exp)->_3) {
#line 69 "../../prop-src/setltype.pcc"
          Ty fun_ty   = inst(_CONSexp(exp)->_1->cons_ty);
            	ty = mkvar();
            	unify(exp,fun_ty,mkfunty(type_of(_CONSexp(exp)->_3,E),ty));
                
#line 72 "../../prop-src/setltype.pcc"
          } else {
#line 67 "../../prop-src/setltype.pcc"
          ty = inst(_CONSexp(exp)->_1->cons_ty); 
#line 67 "../../prop-src/setltype.pcc"
          }
        } else { goto L1; }
        } break;
      case a_Exp::tag_CASTexp: {
#line 107 "../../prop-src/setltype.pcc"
       type_of(_CASTexp(exp)->_2,E); return _CASTexp(exp)->_1; 
#line 107 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_QUALexp: {
#line 108 "../../prop-src/setltype.pcc"
       return mkvar(); 
#line 108 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_EQexp: {
#line 109 "../../prop-src/setltype.pcc"
       return bool_ty; 
#line 109 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_UNIFYexp: {
#line 110 "../../prop-src/setltype.pcc"
       return NOty; 
#line 110 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_LTexp: {
#line 111 "../../prop-src/setltype.pcc"
       return bool_ty; 
#line 111 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_HASHexp: {
#line 112 "../../prop-src/setltype.pcc"
       return integer_ty; 
#line 112 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_THISCOSTexp: {
#line 113 "../../prop-src/setltype.pcc"
       return integer_ty; 
#line 113 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_COSTexp: {
#line 114 "../../prop-src/setltype.pcc"
       return integer_ty; 
#line 114 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_THISSYNexp: {
#line 115 "../../prop-src/setltype.pcc"
       return _THISSYNexp(exp)->_2; 
#line 115 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_SYNexp: {
#line 116 "../../prop-src/setltype.pcc"
       return _SYNexp(exp)->_3; 
#line 116 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_SENDexp: {
#line 92 "../../prop-src/setltype.pcc"
       return mkvar(); 
#line 92 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_SETLexp: {
#line 117 "../../prop-src/setltype.pcc"
       ty = NOty; 
#line 117 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_LISTCOMPexp: {
#line 118 "../../prop-src/setltype.pcc"
       ty = NOty; 
#line 118 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_FORALLexp: {
#line 119 "../../prop-src/setltype.pcc"
       ty = NOty; 
#line 119 "../../prop-src/setltype.pcc"
        } break;
      case a_Exp::tag_EXISTSexp: {
#line 120 "../../prop-src/setltype.pcc"
       ty = NOty; 
#line 120 "../../prop-src/setltype.pcc"
        } break;
      default: {
#line 65 "../../prop-src/setltype.pcc"
       _MARKEDexp(exp)->_1.set_loc(); ty = type_of(_MARKEDexp(exp)->_2,E); 
#line 65 "../../prop-src/setltype.pcc"
        } break;
    }
  } else {
#line 62 "../../prop-src/setltype.pcc"
   ty = NOty; 
#line 62 "../../prop-src/setltype.pcc"
  }
}
#line 122 "../../prop-src/setltype.pcc"
#line 122 "../../prop-src/setltype.pcc"


  ty = deref(ty);
  if (boxed(exp))
    exp->ty = ty;
  return ty;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to infer the type of an expression list.
//
///////////////////////////////////////////////////////////////////////////////

Tys type_of( Exps es, const Env& E)
{
  
#line 138 "../../prop-src/setltype.pcc"
#line 140 "../../prop-src/setltype.pcc"
{
  if (es) {
#line 140 "../../prop-src/setltype.pcc"
    return list_1_(type_of(es->_1,E),type_of(es->_2,E));
#line 140 "../../prop-src/setltype.pcc"
  } else {
#line 139 "../../prop-src/setltype.pcc"
    return nil_1_;
#line 139 "../../prop-src/setltype.pcc"
  }
}
#line 141 "../../prop-src/setltype.pcc"
#line 141 "../../prop-src/setltype.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to infer the type of an labeled expression list.
//
///////////////////////////////////////////////////////////////////////////////

#line 150 "../../prop-src/setltype.pcc"
Tuple2<Ids, Tys>  
#line 150 "../../prop-src/setltype.pcc"
 type_of( LabExps es, const Env& E)
{  Ids labels = 
#line 151 "../../prop-src/setltype.pcc"
nil_1_
#line 151 "../../prop-src/setltype.pcc"
#line 151 "../../prop-src/setltype.pcc"
;
   Tys tys    = 
#line 152 "../../prop-src/setltype.pcc"
#line 152 "../../prop-src/setltype.pcc"
nil_1_
#line 152 "../../prop-src/setltype.pcc"
#line 152 "../../prop-src/setltype.pcc"
;
   
#line 153 "../../prop-src/setltype.pcc"
#line 160 "../../prop-src/setltype.pcc"
{
  for (;;) {
    if (es) {
#line 156 "../../prop-src/setltype.pcc"
      
      labels = 
#line 157 "../../prop-src/setltype.pcc"
#line 157 "../../prop-src/setltype.pcc"
      list_1_(es->_1.label,labels)
#line 157 "../../prop-src/setltype.pcc"
#line 157 "../../prop-src/setltype.pcc"
      ;
      	   tys = 
#line 158 "../../prop-src/setltype.pcc"
#line 158 "../../prop-src/setltype.pcc"
      list_1_(type_of(es->_1.exp,E),tys)
#line 158 "../../prop-src/setltype.pcc"
#line 158 "../../prop-src/setltype.pcc"
      ;
      	   es = es->_2;
           
#line 160 "../../prop-src/setltype.pcc"
    } else { goto L2; }
  }
  L2:;
}
#line 161 "../../prop-src/setltype.pcc"
#line 161 "../../prop-src/setltype.pcc"

   return 
#line 162 "../../prop-src/setltype.pcc"
#line 162 "../../prop-src/setltype.pcc"
mkTuple2(labels,tys)
#line 162 "../../prop-src/setltype.pcc"
#line 162 "../../prop-src/setltype.pcc"
;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to infer the type of a statement.
//
///////////////////////////////////////////////////////////////////////////////

void type_of (Stmt s, const Env& E)
{
  
#line 173 "../../prop-src/setltype.pcc"
#line 185 "../../prop-src/setltype.pcc"
{
  if (s) {
    switch (s->tag__) {
      case a_Stmt::tag_ASSIGNstmt: {} break;
      case a_Stmt::tag_BLOCKstmt: {} break;
      case a_Stmt::tag_WHILEstmt: {} break;
      case a_Stmt::tag_IFstmt: {} break;
      case a_Stmt::tag_MATCHstmt: {} break;
      case a_Stmt::tag_REWRITEstmt: {} break;
      case a_Stmt::tag_REPLACEMENTstmt: {} break;
      case a_Stmt::tag_FORALLstmt: {} break;
      default: {} break;
    }
  } else {}
}
#line 185 "../../prop-src/setltype.pcc"
#line 185 "../../prop-src/setltype.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to infer the type of a list of statements.
//
///////////////////////////////////////////////////////////////////////////////

void type_of( Stmts ss, const Env& E)
{
  
#line 196 "../../prop-src/setltype.pcc"
#line 198 "../../prop-src/setltype.pcc"
{
  for (;;) {
    if (ss) {
#line 198 "../../prop-src/setltype.pcc"
     type_of( ss->_1, E); ss = ss->_2; 
#line 198 "../../prop-src/setltype.pcc"
    } else { goto L3; }
  }
  L3:;
}
#line 199 "../../prop-src/setltype.pcc"
#line 199 "../../prop-src/setltype.pcc"

}
#line 201 "../../prop-src/setltype.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 43
Number of ifs generated      = 8
Number of switches generated = 2
Number of labels             = 1
Number of gotos              = 1
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
