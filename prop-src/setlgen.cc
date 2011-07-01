///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\setlgen.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/setlgen.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the data structure mapping component of the
//  SETL sublanguage.
//
///////////////////////////////////////////////////////////////////////////////

#include "ir.h"
#include "ast.h"
#include "setl-ast.h"
#include "setlgen.h"
#include "type.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

SETLCompiler:: SETLCompiler() {}
SETLCompiler::~SETLCompiler() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Entry points of the SETL data structure mapping compiler
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Generate a SETL statement
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_setl( Stmt stmt)
{
  bug("SETL sublanguage is not implemented");
  gen_stmt(stmt);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generate a SETL definition
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_setl( Def def)
{
  pr( "%^/*\n");
  gen_def( def);
  pr( "%^*/\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Code generation method for definitions
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_def(Def def)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Code generation method for a list of definitions
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_defs( Defs defs)
{
  
#line 72 "../../prop-src/setlgen.pcc"
#line 74 "../../prop-src/setlgen.pcc"
{
  for (;;) {
    if (defs) {
#line 74 "../../prop-src/setlgen.pcc"
     gen_def( defs->_1); defs = defs->_2; 
#line 74 "../../prop-src/setlgen.pcc"
    } else { goto L1; }
  }
  L1:;
}
#line 75 "../../prop-src/setlgen.pcc"
#line 75 "../../prop-src/setlgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Code generation method for statements
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_stmt( Stmt stmt)
{
  
#line 86 "../../prop-src/setlgen.pcc"
#line 96 "../../prop-src/setlgen.pcc"
{
  if (stmt) {
    switch (stmt->tag__) {
      case a_Stmt::tag_ASSIGNstmt: {} break;
      case a_Stmt::tag_BLOCKstmt: {} break;
      case a_Stmt::tag_WHILEstmt: {} break;
      case a_Stmt::tag_IFstmt: {} break;
      case a_Stmt::tag_MATCHstmt: {
#line 92 "../../prop-src/setlgen.pcc"
        pr("%D",_MATCHstmt(stmt)->MATCHstmt);
#line 92 "../../prop-src/setlgen.pcc"
        } break;
      case a_Stmt::tag_REWRITEstmt: {
#line 93 "../../prop-src/setlgen.pcc"
        pr("%D",_REWRITEstmt(stmt)->REWRITEstmt);
#line 93 "../../prop-src/setlgen.pcc"
        } break;
      case a_Stmt::tag_REPLACEMENTstmt: {
#line 94 "../../prop-src/setlgen.pcc"
        pr("%D",_REPLACEMENTstmt(stmt)->REPLACEMENTstmt);
#line 94 "../../prop-src/setlgen.pcc"
        } break;
      case a_Stmt::tag_FORALLstmt: {} break;
      default: {
#line 96 "../../prop-src/setlgen.pcc"
        pr("return %e;",_RETURNstmt(stmt)->RETURNstmt);
#line 96 "../../prop-src/setlgen.pcc"
        } break;
    }
  } else {}
}
#line 97 "../../prop-src/setlgen.pcc"
#line 97 "../../prop-src/setlgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Code generation method for a list of statements
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_stmts( Stmts stmts)
{
  
#line 108 "../../prop-src/setlgen.pcc"
#line 110 "../../prop-src/setlgen.pcc"
{
  for (;;) {
    if (stmts) {
#line 110 "../../prop-src/setlgen.pcc"
     gen_stmt(stmts->_1); stmts = stmts->_2; 
#line 110 "../../prop-src/setlgen.pcc"
    } else { goto L2; }
  }
  L2:;
}
#line 111 "../../prop-src/setlgen.pcc"
#line 111 "../../prop-src/setlgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Code generation method for expressions
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_exp( Exp exp)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Code generation method for an expression list
//
///////////////////////////////////////////////////////////////////////////////

void SETLCompiler::gen_exps( Exps exps)
{
  
#line 132 "../../prop-src/setlgen.pcc"
#line 135 "../../prop-src/setlgen.pcc"
{
  for (;;) {
    if (exps) {
      if (exps->_2) {
#line 135 "../../prop-src/setlgen.pcc"
       gen_exp(exps->_1); exps = exps->_2; 
#line 135 "../../prop-src/setlgen.pcc"
      } else {
#line 134 "../../prop-src/setlgen.pcc"
       gen_exp(exps->_1); exps = 
#line 134 "../../prop-src/setlgen.pcc"
#line 134 "../../prop-src/setlgen.pcc"
        nil_1_
#line 134 "../../prop-src/setlgen.pcc"
#line 134 "../../prop-src/setlgen.pcc"
        ; 
#line 134 "../../prop-src/setlgen.pcc"
      }
    } else { goto L3; }
  }
  L3:;
}
#line 136 "../../prop-src/setlgen.pcc"
#line 136 "../../prop-src/setlgen.pcc"

}
#line 138 "../../prop-src/setlgen.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 4
Number of ifs generated      = 5
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
