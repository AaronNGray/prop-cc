///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\rwmix.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/rwmix.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file defines the rewriting partial evaluator
//
///////////////////////////////////////////////////////////////////////////////

#ifndef rewriting_mix_h
#define rewriting_mix_h

#include "ast.h"
#include "ir.h"
#include "rwgen.h"

///////////////////////////////////////////////////////////////////////////////
//
//  The rewriting partial evaluator
//
///////////////////////////////////////////////////////////////////////////////

class RewriteMix : public virtual RewritingCompiler
{
  RewriteMix (const RewriteMix&);     // no copy constructor
  void operator = (const RewriteMix&);  // no assignment
private:
  int reduction_limit;
public:
           RewriteMix();
  virtual ~RewriteMix();

  virtual void optimize_rewrite ();
};

#endif
#line 34 "../../prop-src/rwmix.ph"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
