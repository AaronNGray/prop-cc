///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\setl-ast.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/setl-ast.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the basic routines on definitions and statements
//  ASTs.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "ir.h"
#include "ast.h"
#include "setl-ast.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the AST datatypes.
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/setl-ast.pcc"
#line 20 "../../prop-src/setl-ast.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Def
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Sig
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Stmt
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Def>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Sig>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<LabSig>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Def
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Sig
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Stmt
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Def>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Def>;
template a_List<Def> * list_1_(Stmt x_1, a_List<Stmt> *  x_2);
template a_List<Def> * list_1_(Stmt x_list_1_);
template int boxed(const a_List<Def> *);
template int untag(const a_List<Def> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Sig>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Sig>;
template a_List<Sig> * list_1_(Def x_1, a_List<Def> *  x_2);
template a_List<Sig> * list_1_(Def x_list_1_);
template int boxed(const a_List<Sig> *);
template int untag(const a_List<Sig> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<LabSig>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<LabSig>;
template a_List<LabSig> * list_1_(Sig x_1, a_List<Sig> *  x_2);
template a_List<LabSig> * list_1_(Sig x_list_1_);
template int boxed(const a_List<LabSig> *);
template int untag(const a_List<LabSig> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Stmt>;
template a_List<Stmt> * list_1_(LabSig x_1, a_List<LabSig> *  x_2);
template a_List<Stmt> * list_1_(LabSig x_list_1_);
template int boxed(const a_List<Stmt> *);
template int untag(const a_List<Stmt> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

#line 22 "../../prop-src/setl-ast.pcc"
#line 22 "../../prop-src/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  The rest of pretty printing functions for definitions and statements
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a signature
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Sig s)
{
  
#line 38 "../../prop-src/setl-ast.pcc"
#line 45 "../../prop-src/setl-ast.pcc"
{
  if (s) {
    switch (s->tag__) {
      case a_Sig::tag_IDsig: {
#line 41 "../../prop-src/setl-ast.pcc"
       f << _IDsig(s)->IDsig; 
#line 41 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Sig::tag_DOTsig: {
#line 42 "../../prop-src/setl-ast.pcc"
       f << _DOTsig(s)->_1 << '.' << _DOTsig(s)->_2; 
#line 42 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Sig::tag_APPsig: {
#line 43 "../../prop-src/setl-ast.pcc"
       f << _APPsig(s)->_1 << '(' << _APPsig(s)->_2 << ')'; 
#line 43 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Sig::tag_DEFsig: {
#line 44 "../../prop-src/setl-ast.pcc"
       f << "<def>"; 
#line 44 "../../prop-src/setl-ast.pcc"
        } break;
      default: {
#line 45 "../../prop-src/setl-ast.pcc"
       f << "<lambda>"; 
#line 45 "../../prop-src/setl-ast.pcc"
        } break;
    }
  } else {
#line 40 "../../prop-src/setl-ast.pcc"
   f << "none"; 
#line 40 "../../prop-src/setl-ast.pcc"
  }
}
#line 46 "../../prop-src/setl-ast.pcc"
#line 46 "../../prop-src/setl-ast.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a signature list
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Sigs ss)
{
  
#line 58 "../../prop-src/setl-ast.pcc"
#line 61 "../../prop-src/setl-ast.pcc"
{
  for (;;) {
    if (ss) {
      if (ss->_2) {
#line 61 "../../prop-src/setl-ast.pcc"
       f << ss->_1 << ", "; ss = ss->_2; 
#line 61 "../../prop-src/setl-ast.pcc"
      } else {
#line 60 "../../prop-src/setl-ast.pcc"
       f << ss->_1; ss = 
#line 60 "../../prop-src/setl-ast.pcc"
#line 60 "../../prop-src/setl-ast.pcc"
        nil_1_
#line 60 "../../prop-src/setl-ast.pcc"
#line 60 "../../prop-src/setl-ast.pcc"
        ; 
#line 60 "../../prop-src/setl-ast.pcc"
      }
    } else { goto L1; }
  }
  L1:;
}
#line 62 "../../prop-src/setl-ast.pcc"
#line 62 "../../prop-src/setl-ast.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a statement
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Stmt s)
{
  
#line 74 "../../prop-src/setl-ast.pcc"
#line 92 "../../prop-src/setl-ast.pcc"
{
  if (s) {
    switch (s->tag__) {
      case a_Stmt::tag_ASSIGNstmt: {
#line 77 "../../prop-src/setl-ast.pcc"
       f << _ASSIGNstmt(s)->_1 << " := " << _ASSIGNstmt(s)->_2 << ';'; 
#line 77 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Stmt::tag_BLOCKstmt: {
#line 78 "../../prop-src/setl-ast.pcc"
       f << _BLOCKstmt(s)->_2; 
#line 78 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Stmt::tag_WHILEstmt: {
#line 80 "../../prop-src/setl-ast.pcc"
       f << "while " << _WHILEstmt(s)->_1 <<  " loop " << _WHILEstmt(s)->_2 << " end loop"; 
#line 80 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Stmt::tag_IFstmt: {
#line 82 "../../prop-src/setl-ast.pcc"
       f << "if " << _IFstmt(s)->_1 << " then " << _IFstmt(s)->_2 << " else " << _IFstmt(s)->_3 << "end if"; 
#line 82 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Stmt::tag_MATCHstmt: {
#line 88 "../../prop-src/setl-ast.pcc"
       f << "match ..."; 
#line 88 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Stmt::tag_REWRITEstmt: {
#line 90 "../../prop-src/setl-ast.pcc"
       f << "rewrite ..."; 
#line 90 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Stmt::tag_REPLACEMENTstmt: {
#line 92 "../../prop-src/setl-ast.pcc"
       f << "rewrite ..."; 
#line 92 "../../prop-src/setl-ast.pcc"
        } break;
      case a_Stmt::tag_FORALLstmt: {
#line 84 "../../prop-src/setl-ast.pcc"
       f << "forall " << _FORALLstmt(s)->_1 << " loop " << _FORALLstmt(s)->_2 << "end loop"; 
#line 84 "../../prop-src/setl-ast.pcc"
        } break;
      default: {
#line 86 "../../prop-src/setl-ast.pcc"
       f << "return " << _RETURNstmt(s)->RETURNstmt << ';'; 
#line 86 "../../prop-src/setl-ast.pcc"
        } break;
    }
  } else {
#line 76 "../../prop-src/setl-ast.pcc"
   f << "skip;"; 
#line 76 "../../prop-src/setl-ast.pcc"
  }
}
#line 93 "../../prop-src/setl-ast.pcc"
#line 93 "../../prop-src/setl-ast.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a list of statements
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Stmts s)
{
  
#line 105 "../../prop-src/setl-ast.pcc"
#line 108 "../../prop-src/setl-ast.pcc"
{
  for (;;) {
    if (s) {
      if (s->_2) {
#line 108 "../../prop-src/setl-ast.pcc"
       f << s->_1 << " "; s = s->_2; 
#line 108 "../../prop-src/setl-ast.pcc"
      } else {
#line 107 "../../prop-src/setl-ast.pcc"
       f << s->_1; s = 
#line 107 "../../prop-src/setl-ast.pcc"
#line 107 "../../prop-src/setl-ast.pcc"
        nil_1_
#line 107 "../../prop-src/setl-ast.pcc"
#line 107 "../../prop-src/setl-ast.pcc"
        ; 
#line 107 "../../prop-src/setl-ast.pcc"
      }
    } else { goto L2; }
  }
  L2:;
}
#line 109 "../../prop-src/setl-ast.pcc"
#line 109 "../../prop-src/setl-ast.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a generator expression
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Generator b)
{
  
#line 121 "../../prop-src/setl-ast.pcc"
#line 129 "../../prop-src/setl-ast.pcc"
{
#line 124 "../../prop-src/setl-ast.pcc"
  
  f << b->pat;
  if (b->guard != NOexp)
    f << " | " << b->guard;
  f << " <- " << b->exp;
  
#line 129 "../../prop-src/setl-ast.pcc"
}
#line 130 "../../prop-src/setl-ast.pcc"
#line 130 "../../prop-src/setl-ast.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a list of generator expressions
//
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& f, Generators b)
{
  
#line 141 "../../prop-src/setl-ast.pcc"
#line 144 "../../prop-src/setl-ast.pcc"
{
  for (;;) {
    if (b) {
      if (b->_2) {
#line 144 "../../prop-src/setl-ast.pcc"
       f << b->_1 << ", "; b = b->_2; 
#line 144 "../../prop-src/setl-ast.pcc"
      } else {
#line 143 "../../prop-src/setl-ast.pcc"
       f << b->_1; b = 
#line 143 "../../prop-src/setl-ast.pcc"
#line 143 "../../prop-src/setl-ast.pcc"
        nil_1_
#line 143 "../../prop-src/setl-ast.pcc"
#line 143 "../../prop-src/setl-ast.pcc"
        ; 
#line 143 "../../prop-src/setl-ast.pcc"
      }
    } else { goto L3; }
  }
  L3:;
}
#line 145 "../../prop-src/setl-ast.pcc"
#line 145 "../../prop-src/setl-ast.pcc"

  return f;
}
#line 148 "../../prop-src/setl-ast.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 6
Number of ifs generated      = 8
Number of switches generated = 2
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
