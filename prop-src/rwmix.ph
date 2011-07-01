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
