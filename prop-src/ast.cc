///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\ast.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/ast.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements some basic AST manipulation routines
//
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "basics.h"
#include "ast.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Select the ith component from an expression list
//
///////////////////////////////////////////////////////////////////////////////

Exp component_exp(Exps exps, int n)
{
  Exps es = exps;
  int  i  = n;
  
#line 21 "../../prop-src/ast.pcc"
#line 23 "../../prop-src/ast.pcc"
{
  for (;;) {
    if (es) {
      if (
#line 22 "../../prop-src/ast.pcc"
      (i == 1)
#line 22 "../../prop-src/ast.pcc"
) {
        
#line 22 "../../prop-src/ast.pcc"
       return es->_1; 
#line 22 "../../prop-src/ast.pcc"
      } else {
        
#line 23 "../../prop-src/ast.pcc"
       es = es->_2; i--; 
#line 23 "../../prop-src/ast.pcc"
      }
    } else { goto L1; }
  }
  L1:;
}
#line 24 "../../prop-src/ast.pcc"
#line 24 "../../prop-src/ast.pcc"

  error( "%Lexpression %e does not have component %i\n", TUPLEexp(exps), n);
  return NOexp;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Select the ith component from an expression list
//
///////////////////////////////////////////////////////////////////////////////

Exp component_exp(Exps exps, Id n)
{
  return component_exp(exps,atol(n+1));
}

///////////////////////////////////////////////////////////////////////////////
//
//  Select the ith component from a labeled expression list
//
///////////////////////////////////////////////////////////////////////////////

Exp component_exp( LabExps labeled_exps, Id n)
{
  LabExps les = labeled_exps;
  
#line 49 "../../prop-src/ast.pcc"
#line 51 "../../prop-src/ast.pcc"
{
  for (;;) {
    if (les) {
      if (
#line 50 "../../prop-src/ast.pcc"
      (les->_1.label == n)
#line 50 "../../prop-src/ast.pcc"
) {
        
#line 50 "../../prop-src/ast.pcc"
       return les->_1.exp; 
#line 50 "../../prop-src/ast.pcc"
      } else {
        
#line 51 "../../prop-src/ast.pcc"
       les = les->_2; 
#line 51 "../../prop-src/ast.pcc"
      }
    } else { goto L2; }
  }
  L2:;
}
#line 52 "../../prop-src/ast.pcc"
#line 52 "../../prop-src/ast.pcc"

  error( "%Lexpression %e does not have component %s\n",
         RECORDexp(labeled_exps), n);
  return NOexp;
}
#line 57 "../../prop-src/ast.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 2
Number of ifs generated      = 4
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
