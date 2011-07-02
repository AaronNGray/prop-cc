///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\rwmix.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/rwmix.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the rewriting partial evaluator/supercompiler.
//  This is used to optimize Prop's rewriting systems.
//
///////////////////////////////////////////////////////////////////////////////

#include <AD/automata/topdowng.h>
#include "ast.h"
#include "ir.h"
#include "rwmix.h"
#include "patenv.h"
#include "type.h"
#include "funmap.h"
#include "options.h"
#include "trs.h"

///////////////////////////////////////////////////////////////////////////////
//
//  The constructors and destructors
//
///////////////////////////////////////////////////////////////////////////////

RewriteMix::RewriteMix() { reduction_limit = 10; }
RewriteMix::~RewriteMix() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to optimize a set of rewrite rules.
//  Currently, we'll only optimize if there are no other rules
//  except bottomup rules.
//
///////////////////////////////////////////////////////////////////////////////

void RewriteMix::optimize_rewrite()
{
  if (options.optimize_rewrite && Fmap != 0)
  {
    if (Fmap->topdown_rule_map.size() > 0 ||
        Fmap->preorder_rule_map.size() > 0 ||
        Fmap->postorder_rule_map.size() > 0 ||
        Fmap->before_rule_map.size() > 0)
    {
      msg( "%Lrewrite class %s will not be optimized due to the presence"
           " of non-bottomup rules\n",Fmap->class_name);
      return;
    }

    msg( "%Lpartial evaluating rewrite class %s\n", Fmap->class_name);
    trs = new TRS(*this);
    trs->mix();
    msg( "%Lfinished optimizing rewrite class %s\n", Fmap->class_name);
  }
}
#line 55 "../../prop-src/rwmix.pcc"
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
