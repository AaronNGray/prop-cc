///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\rwgen5.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_n_5co_c_c_Q1("none");
#line 1 "../../prop-src/rwgen5.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements indexing for rewriters
//
///////////////////////////////////////////////////////////////////////////////
#include "basics.h"
#include "hashtab.h"
#include "rwgen.h"
#include "funmap.h"
#include "type.h"
#include "options.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Indexing class
//
///////////////////////////////////////////////////////////////////////////////

RewriteIndexing::RewriteIndexing( Ty t, Id i, Bool e)
  : ty(t), name(i), external(e) {}

RewriteIndexing::~RewriteIndexing() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Mapping from id to RewriteClass
//
///////////////////////////////////////////////////////////////////////////////

HashTable RewritingCompiler::rewrite_classes( string_hash, string_equal);

///////////////////////////////////////////////////////////////////////////////
//
//  Enter a rewrite class
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::add_rewrite_class( RewriteClass * C)
{
  if (rewrite_classes.contains( C->class_name))
    error( "%Lrewrite class %s has already been defined\n", C->class_name);
  else
  {
    rewrite_classes.insert(C->class_name, C);
    debug_msg( "[Rewriting class %s declared]\n", C->class_name);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Lookup a rewrite class
//
///////////////////////////////////////////////////////////////////////////////

RewriteClass * RewritingCompiler::lookup_rewrite_class( Id id)
{
  HashTable::Entry * e = rewrite_classes.lookup(id);
  if (e == 0)
  {
    error ("%Lrewrite class %s is undefined\n", id);
    return 0;
  }
  else
     return (RewriteClass *) rewrite_classes.value( e);
}

Protocols RewritingCompiler::lookup_protocols( Id id)
{
  RewriteClass * C = lookup_rewrite_class(id);
  return C ? C->protocols : 
#line 70 "../../prop-src/rwgen5.pcc"
#line 70 "../../prop-src/rwgen5.pcc"
nil_1_
#line 70 "../../prop-src/rwgen5.pcc"
#line 70 "../../prop-src/rwgen5.pcc"
;
}

TyQual RewritingCompiler::lookup_qual( Id id)
{
  RewriteClass * C = lookup_rewrite_class(id);
  return C ? C->qualifiers : QUALnone;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to retrieve the indexing information for a type
//
///////////////////////////////////////////////////////////////////////////////

const RewriteIndexing * RewritingCompiler::get_index( Ty ty) const
{
  for_each (RewriteIndexing *, i, indices)
    if ( ty_equal( i->ty, ty))
      return i;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the index
//
///////////////////////////////////////////////////////////////////////////////

Bool RewritingCompiler::compute_index( Ty ty, Id& name, Bool& external) const
{
  Ty datatype_ty            = deref_all(ty);
  Bool is_boxed             = boxed_variants(datatype_ty) > 0;
  Bool rewritable           = has_qual(QUALrewritable, datatype_ty);
  const RewriteIndexing * I = get_index(ty);
  Bool need_cache           = Fmap->has_replacement || Fmap->gen_reducers;

  Bool ok = is_boxed && (rewritable || I != 0) && need_cache;

  if (I != 0 && I->name == 
#line 109 "../../prop-src/rwgen5.pcc"
#line 109 "../../prop-src/rwgen5.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_r_w_g_e_n_5co_c_c_Q1
#line 109 "../../prop-src/rwgen5.pcc"
#line 109 "../../prop-src/rwgen5.pcc"
) ok = false;

  if (ok)
  {
    if (I)
    {
      name = I->name;
      external = I->external;
    }
    else
    {
      name = "rewrite";
      external = false;
    }

    return true;
  }
  else
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to check whether a type has an index
//
///////////////////////////////////////////////////////////////////////////////

Bool RewritingCompiler::has_index( Ty ty) const
{
  Id name;
  Bool external;
  return compute_index( ty, name, external);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to emit code for retrieving the state from an expression
//
///////////////////////////////////////////////////////////////////////////////

Id RewritingCompiler::gen_get_rewrite_state( Ty ty, Exp pat_exp)
{
  Id name;
  Bool external;

  if (! compute_index( ty, name, external))
    bug("%Lexpression %e : %T has no index", pat_exp, ty);

  int units = unboxed_variants(ty);
  int args  = boxed_variants(ty);
  Functor f = Fmap->type_map[ty];
  Id state_var = vars.new_label();

  if (units == 0)
  {
    pr("%^int %s = ", state_var);
    if (external)
      pr("get_%s_state(%e);", name, pat_exp);
    else
      pr("%e->get_%s_state();", pat_exp, name);
  }
  else if (args == 0)
    pr("%^int %s = %e + %i;", state_var, pat_exp, f);
  else
  {
    Id pat_var = vars.new_label();
    pr("%^%t %s = %e;"
	"%^int %s = boxed(%s) ? ",
	ty, "", pat_var, pat_exp, state_var, pat_var);
    if (external)
      pr("get_%s_state(%s)", name, pat_var);
    else
      pr("%s->get_%s_state()", pat_var, name);
    pr(" : ((int)%s + %i);", pat_var, f);
  }
  return state_var;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to emit code for retrieving the state from index
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_get_rewrite_state( Ty ty, Id redex)
{
  Id name;
  Bool external;

  if (! compute_index( ty, name, external))
    return;

  if (external)
    pr(
        "%^int cached__;"
        "%^if (r__ && boxed(redex) && (cached__ = get_%s_state(%s)) != BURS::undefined_state)"
        "%^{ s__ = cached__; return%s; }",
        name, redex, (Fmap->is_applicative ? " redex" : "")
      );
  else
    pr(
        "%^int cached__;"
        "%^if (r__ && boxed(redex) && (cached__ = %s->get_%s_state()) != BURS::undefined_state)"
        "%^{ s__ = cached__; return%s; }",
        redex, name, (Fmap->is_applicative ? " redex" : "")
      );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to emit code for setting the index state
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_set_rewrite_state_and_rule( Ty ty, Id redex)
{
  Id name;
  Bool external;

  if (! compute_index( ty, name, external))
    return;

  if (external)
  {
    pr(
        "%^if (boxed(redex)) {%+"
        "%^set_%s_state(%s,s__);",name,redex
      );

    if (Fmap->gen_reducers)
        pr("%^set_%s_rule(%s,rule__);",name,redex);

    pr("%-%^}");
  }
  else
  {
    pr(
        "%^if (boxed(redex)) {%+"
        "%^%s->set_%s_state(s__);",redex,name
      );
    if (Fmap->gen_reducers)
      pr("%^%s->set_%s_rule(rule__);",redex,name);
    pr("%-%^}");
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to emit code for retrieving the cached rule
//
///////////////////////////////////////////////////////////////////////////////

void RewritingCompiler::gen_get_rewrite_rule( Ty ty, Id redex)
{
  Id name;
  Bool external;

  if (! compute_index(ty,name,external))
  {
    error( "%Ltype %T is no index defined in treeparser mode rewrite class %s\n",
           ty, Fmap->class_name);
    return;
  }
  if (external)
    pr("get_%s_rule(%s)", name, redex);
  else
    pr("%s->get_%s_rule()", redex, name);
}
#line 277 "../../prop-src/rwgen5.pcc"
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
