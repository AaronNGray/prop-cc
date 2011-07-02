///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\funmap.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q3("##");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q4("$$");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q1("#");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q2("$");
#line 1 "../../prop-src/funmap.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the FunctorMap data structure
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <strstream>
#include <AD/automata/treegram.h>
#include <AD/automata/treegen.h>
#include <AD/rewrite/burs_gen.h>
#include <AD/strings/quark.h>
#include "funmap.h"
#include "ir.h"
#include "ast.h"
#include "matchcom.h"
#include "type.h"
#include "hashtab.h"
#include "datagen.h"
#include "config.h"
#include "rwgen.h"
#include "options.h"
#include "list.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Import some type definitions from the tree grammar and hash table
//  classes.
//
///////////////////////////////////////////////////////////////////////////////

typedef TreeGrammar::TreeProduction TreeProduction;
typedef TreeGrammar::Cost           TreeCost;
typedef HashTable::Key              Key;
typedef HashTable::Value            Value;

///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the vector id type
//
///////////////////////////////////////////////////////////////////////////////

#line 44 "../../prop-src/funmap.pcc"
#line 44 "../../prop-src/funmap.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype VectorId
//
///////////////////////////////////////////////////////////////////////////////
#line 44 "../../prop-src/funmap.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype VectorId
//
///////////////////////////////////////////////////////////////////////////////
#line 44 "../../prop-src/funmap.pcc"


#line 44 "../../prop-src/funmap.pcc"
#line 44 "../../prop-src/funmap.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Hashing and equality on vector id's
//
///////////////////////////////////////////////////////////////////////////////

unsigned int vector_id_hash( HashTable::Key k)
{
  VectorId id = (VectorId)k;
  return (unsigned int)id->cons + ty_hash(id->ty) + id->arity;
}

Bool vector_id_equal( HashTable::Key a, HashTable::Key b)
{
  VectorId x = (VectorId) a;
  VectorId y = (VectorId) b;
  return x->cons == y->cons && x->arity == y->arity && ty_equal(x->ty,y->ty);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to decorate cost expression and attribute bindings for
//  a pattern.
//
///////////////////////////////////////////////////////////////////////////////

int decor_rewrite( Pat pat, int rule, int kid, PatternVarEnv& E)
{
  
#line 74 "../../prop-src/funmap.pcc"
#line 103 "../../prop-src/funmap.pcc"
{
  for (;;) {
    if (pat) {
      switch (pat->tag__) {
        case a_Pat::tag_APPpat: {
#line 80 "../../prop-src/funmap.pcc"
         pat = _APPpat(pat)->_2; 
#line 80 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_TYPEDpat: {
#line 78 "../../prop-src/funmap.pcc"
         pat = _TYPEDpat(pat)->_1; 
#line 78 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_ASpat: {
#line 94 "../../prop-src/funmap.pcc"
          
          Id attrib_name = 
#line 95 "../../prop-src/funmap.pcc"
#line 95 "../../prop-src/funmap.pcc"
          cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q1
#line 95 "../../prop-src/funmap.pcc"
#line 95 "../../prop-src/funmap.pcc"
         + _ASpat(pat)->_1;
          Id cost_name   = 
#line 96 "../../prop-src/funmap.pcc"
#line 96 "../../prop-src/funmap.pcc"
          cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q2
#line 96 "../../prop-src/funmap.pcc"
#line 96 "../../prop-src/funmap.pcc"
         + _ASpat(pat)->_1;
          Ty ty = mkvar();
          E.add( attrib_name, SYNexp( kid, rule, mkvar(), true), ty, ISpositive);
          E.add( cost_name, COSTexp(kid),  ty, ISpositive);
          kid = kid+1;
          pat = _ASpat(pat)->_2;
          
#line 102 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_CONTEXTpat: {
#line 81 "../../prop-src/funmap.pcc"
         pat = _CONTEXTpat(pat)->_2; 
#line 81 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_TUPLEpat: {
#line 83 "../../prop-src/funmap.pcc"
         return decor_rewrite( _TUPLEpat(pat)->TUPLEpat, rule, kid, E); 
#line 83 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_LISTpat: {
#line 85 "../../prop-src/funmap.pcc"
         kid = decor_rewrite( _LISTpat(pat)->head, rule, kid, E); pat = _LISTpat(pat)->tail; 
#line 85 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_VECTORpat: {
#line 87 "../../prop-src/funmap.pcc"
          
          kid = decor_rewrite(_VECTORpat(pat)->elements, rule, decor_rewrite(_VECTORpat(pat)->array, rule, kid, E), E);
          if (_VECTORpat(pat)->head_flex || _VECTORpat(pat)->tail_flex)
            error( "%Lflexible vector pattern currently not supported in rewriting: %p\n", pat);
          pat = _VECTORpat(pat)->len;
          
#line 92 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_GUARDpat: {
#line 79 "../../prop-src/funmap.pcc"
         pat = _GUARDpat(pat)->_1; 
#line 79 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_MARKEDpat: {
#line 77 "../../prop-src/funmap.pcc"
         pat = _MARKEDpat(pat)->_2; 
#line 77 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_CONSpat:
        case a_Pat::tag_LITERALpat: {
          L2:; 
#line 76 "../../prop-src/funmap.pcc"
         return kid; 
#line 76 "../../prop-src/funmap.pcc"
          } break;
        default: {
#line 103 "../../prop-src/funmap.pcc"
         return kid; 
#line 103 "../../prop-src/funmap.pcc"
          } break;
      }
    } else { goto L2; }
  }
}
#line 104 "../../prop-src/funmap.pcc"
#line 104 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Decorate a pattern list.
//
///////////////////////////////////////////////////////////////////////////////

int decor_rewrite (Pats pats, int rule, int kid, PatternVarEnv& E)
{
  for_each ( Pat, p, pats)
    kid = decor_rewrite( p, rule, kid, E);
  return kid;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Decorate rewriting patterns.
//
///////////////////////////////////////////////////////////////////////////////

int decor_rewrite( Pat pat, int rule, PatternVarEnv& E)
{
  Ty ty = mkvar();
  E.add( 
#line 129 "../../prop-src/funmap.pcc"
#line 129 "../../prop-src/funmap.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q3
#line 129 "../../prop-src/funmap.pcc"
#line 129 "../../prop-src/funmap.pcc"
, THISSYNexp(rule,mkvar(),true), ty, ISpositive);
  E.add( 
#line 130 "../../prop-src/funmap.pcc"
#line 130 "../../prop-src/funmap.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_f_u_n_m_a_pco_c_c_Q4
#line 130 "../../prop-src/funmap.pcc"
#line 130 "../../prop-src/funmap.pcc"
, THISCOSTexp(), ty, ISpositive);
  return decor_rewrite( pat, rule, 0, E);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor of the functor mapping table.
//
///////////////////////////////////////////////////////////////////////////////

FunctorMap::FunctorMap(Id name, MatchRules rules)
  : literal_map( literal_hash, literal_equal, 129),
    var_map( string_hash, string_equal),
    type_map( ty_hash, ty_equal),
    vector_map( vector_id_hash, vector_id_equal),
    rule_map( ty_hash, ty_equal),
    topdown_rule_map(ty_hash, ty_equal),
    before_rule_map(ty_hash, ty_equal),
    preorder_rule_map( ty_hash, ty_equal),
    postorder_rule_map( ty_hash, ty_equal),
    protocols( ty_hash, ty_equal),
    nonterm_map( string_hash, string_equal),
    nonterm_rules( string_hash, string_equal),
    nonterm_rules_bits( string_hash, string_equal),
    chain_rules( string_hash, string_equal),
    bottomup_rules(
#line 155 "../../prop-src/funmap.pcc"
#line 155 "../../prop-src/funmap.pcc"
nil_1_
#line 155 "../../prop-src/funmap.pcc"
#line 155 "../../prop-src/funmap.pcc"
)
{
  ///////////////////////////////////////////////////////////////////////////
  //
  //  Initialize the internals.
  //
  ///////////////////////////////////////////////////////////////////////////

  class_name      = name;
  N               = length(rules);
  functors        = 0;
  variables       = 0;
  tree_gen        = 0;
  topdown_gen     = 0;
  use_compression = true;
  has_guard       = false;
  has_replacement = false;
  has_cost        = false;
  has_cost_exp    = false;
  has_syn_attrib  = false;
  is_applicative  = false;
  gen_reducers    = false;
  dynamic_search  = false;
  max_arity       = 1;
  functor_names   = 0;
  variable_names  = 0;
  is_ok           = true;

  rule_maps[MatchRuleInfo::BOTTOMUP]  = &rule_map;
  rule_maps[MatchRuleInfo::TOPDOWN]   = &topdown_rule_map;
  rule_maps[MatchRuleInfo::BEFORE]    = &before_rule_map;
  rule_maps[MatchRuleInfo::PREORDER]  = &preorder_rule_map;
  rule_maps[MatchRuleInfo::POSTORDER] = &postorder_rule_map;

  TyQual qual = RewritingCompiler::lookup_qual(class_name);
  if (qual & QUALtreeparser)  gen_reducers = true;
  if (qual & QUALapplicative) is_applicative = true;

  int last_errors = errors;
  enter_protocols();             // enter the protocols
                                 // partition rule by type
  bottomup_rules = partition_rules(rules);
  check_for_missing_protocols();

  if (errors != last_errors)
  {
    is_ok = false;
    return;
  }

  build_tree_grammar(bottomup_rules);

  // BUG fix, always use dynamic search algorithm when treeparser
  // mode is on, since the class interface has to match.
  //dynamic_search = gen_reducers && (has_cost || has_cost_exp);

  dynamic_search = gen_reducers;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to enter the protocols into the protocol map
//
///////////////////////////////////////////////////////////////////////////////
void FunctorMap::enter_protocols()
{
  Protocols Ps = RewritingCompiler::lookup_protocols( class_name);
  {
    for_each (Protocol, p, Ps)
    {
      
#line 225 "../../prop-src/funmap.pcc"
#line 233 "../../prop-src/funmap.pcc"
{
#line 228 "../../prop-src/funmap.pcc"
  
  encode(p->ty);
  protocols.insert( p->ty, p);
  if (p->syn != NOty)
    has_syn_attrib = true;
  
#line 233 "../../prop-src/funmap.pcc"
}
#line 234 "../../prop-src/funmap.pcc"
#line 234 "../../prop-src/funmap.pcc"

    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Checks for missing protocol
//
///////////////////////////////////////////////////////////////////////////////

void FunctorMap::check_for_missing_protocols()
{
  foreach_entry (e, type_map)
  {
    Ty ty = Ty( type_map.key(e));
    if ( !protocols.contains(ty))
    {
      error("%Lmissing type %T in the traversal list of rewrite class %s\n",
             ty, class_name);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Otherwise, build the tree grammar and the functor/variable name maps.
//
///////////////////////////////////////////////////////////////////////////////

void FunctorMap::build_tree_grammar( MatchRules rules)
{
  N = length(rules);
  TreeProduction * Ps =
      (TreeProduction *) mem_pool.c_alloc( sizeof( TreeProduction) * N);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Translate patterns into terms
  //
  ////////////////////////////////////////////////////////////////////////////

  {
    int i = 0;
    for_each (MatchRule, r, rules)
    {
      
#line 281 "../../prop-src/funmap.pcc"
#line 299 "../../prop-src/funmap.pcc"
{
#line 284 "../../prop-src/funmap.pcc"
  
  int rule_no = r->_1 ? var_map[r->_1] : 0;
  int cst;
  
#line 287 "../../prop-src/funmap.pcc"
#line 291 "../../prop-src/funmap.pcc"
  {
    Cost _V1 = r->_4;
    if (_V1) {
      if (_V1->tag__) {
        
#line 290 "../../prop-src/funmap.pcc"
       cst = _INTcost(_V1)->INTcost; has_cost = true; 
#line 290 "../../prop-src/funmap.pcc"
      } else {
        
#line 291 "../../prop-src/funmap.pcc"
       cst = 0; has_cost_exp = true; 
#line 291 "../../prop-src/funmap.pcc"
      }
    } else {
#line 289 "../../prop-src/funmap.pcc"
     cst = 0; 
#line 289 "../../prop-src/funmap.pcc"
    }
  }
#line 292 "../../prop-src/funmap.pcc"
#line 292 "../../prop-src/funmap.pcc"
  
  Ps[i] = TreeProduction(rule_no,trans(r->_2),cst);
  if (r->_3 != NOexp || (r->option & MatchRuleInfo::FAILREWRITE))
    has_guard = true;
  if (r->option & MatchRuleInfo::REPLACEMENT)
    has_replacement = true;
  i++;
  
#line 299 "../../prop-src/funmap.pcc"
}
#line 300 "../../prop-src/funmap.pcc"
#line 300 "../../prop-src/funmap.pcc"

    }
  }

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Compute the functor/variable names
  //
  ////////////////////////////////////////////////////////////////////////////
  compute_names();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Compile the tree grammar
  //
  ////////////////////////////////////////////////////////////////////////////
  G.compile (N, Ps, functor_names, variable_names, 0, functors - 1, 0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to convert literal patterns inside a set of matching rules
//  into guards
//
///////////////////////////////////////////////////////////////////////////////
void FunctorMap::make_guard( MatchRules rules)
{
  
#line 327 "../../prop-src/funmap.pcc"
#line 333 "../../prop-src/funmap.pcc"
{
  for (;;) {
    if (rules) {
#line 330 "../../prop-src/funmap.pcc"
      
      rules->_1->_2   = make_guard( rules->_1->_2, rules->_1->_3);
      rules = rules->_2;
      
#line 333 "../../prop-src/funmap.pcc"
    } else { goto L3; }
  }
  L3:;
}
#line 334 "../../prop-src/funmap.pcc"
#line 334 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to convert literal patterns into guards.
//
///////////////////////////////////////////////////////////////////////////////

Pat FunctorMap::make_guard( Pat pat, Exp& e)
{
  Pat new_pat;
  // return pat; // BUG fix
  
#line 347 "../../prop-src/funmap.pcc"
#line 382 "../../prop-src/funmap.pcc"
{
  if (pat) {
    switch (pat->tag__) {
      case a_Pat::tag_APPpat: {
#line 354 "../../prop-src/funmap.pcc"
       new_pat = APPpat( make_guard( _APPpat(pat)->_1, e), make_guard( _APPpat(pat)->_2, e)); 
#line 354 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_TYPEDpat: {
#line 350 "../../prop-src/funmap.pcc"
       new_pat = TYPEDpat( make_guard( _TYPEDpat(pat)->_1, e), _TYPEDpat(pat)->_2); 
#line 350 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_ASpat: {
#line 349 "../../prop-src/funmap.pcc"
       new_pat = ASpat( _ASpat(pat)->_1, make_guard( _ASpat(pat)->_2, e), _ASpat(pat)->_3, _ASpat(pat)->_4); 
#line 349 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_LITERALpat: {
        switch (_LITERALpat(pat)->LITERALpat->tag__) {
          case a_Literal::tag_INTlit:
          case a_Literal::tag_BOOLlit:
          case a_Literal::tag_CHARlit:
          case a_Literal::tag_REALlit: {
#line 356 "../../prop-src/funmap.pcc"
            
            Exp guard_exp = BINOPexp( "==", pat->selector, LITERALexp(_LITERALpat(pat)->LITERALpat));
            e = e == NOexp ? guard_exp : BINOPexp( "&&", e, guard_exp);
            new_pat = WILDpat();
            
#line 360 "../../prop-src/funmap.pcc"
            } break;
          default: {
            L4:; 
#line 382 "../../prop-src/funmap.pcc"
           new_pat = pat; 
#line 382 "../../prop-src/funmap.pcc"
            } break;
        }
        } break;
      case a_Pat::tag_TUPLEpat: {
#line 352 "../../prop-src/funmap.pcc"
       new_pat = TUPLEpat( make_guard( _TUPLEpat(pat)->TUPLEpat, e)); 
#line 352 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_RECORDpat: {
#line 353 "../../prop-src/funmap.pcc"
       new_pat = RECORDpat( make_guard( _RECORDpat(pat)->_1, e), _RECORDpat(pat)->_2); 
#line 353 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_LISTpat: {
#line 362 "../../prop-src/funmap.pcc"
        
        new_pat = 
#line 363 "../../prop-src/funmap.pcc"
#line 363 "../../prop-src/funmap.pcc"
        LISTpat(_LISTpat(pat)->cons, _LISTpat(pat)->nil, make_guard(_LISTpat(pat)->head,e), make_guard(_LISTpat(pat)->tail,e))
#line 368 "../../prop-src/funmap.pcc"
#line 368 "../../prop-src/funmap.pcc"
        ;
        
#line 369 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_VECTORpat: {
#line 371 "../../prop-src/funmap.pcc"
        
        new_pat = 
#line 372 "../../prop-src/funmap.pcc"
#line 372 "../../prop-src/funmap.pcc"
        VECTORpat(_VECTORpat(pat)->cons, make_guard(_VECTORpat(pat)->len,e), make_guard(_VECTORpat(pat)->array,e), make_guard(_VECTORpat(pat)->elements,e), _VECTORpat(pat)->head_flex, _VECTORpat(pat)->tail_flex)
#line 380 "../../prop-src/funmap.pcc"
#line 380 "../../prop-src/funmap.pcc"
        ;
        
#line 381 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 351 "../../prop-src/funmap.pcc"
       new_pat = MARKEDpat( _MARKEDpat(pat)->_1, make_guard( _MARKEDpat(pat)->_2, e)); 
#line 351 "../../prop-src/funmap.pcc"
        } break;
      default: { goto L4; } break;
    }
  } else { goto L4; }
}
#line 383 "../../prop-src/funmap.pcc"
#line 383 "../../prop-src/funmap.pcc"

  if (new_pat != pat && boxed(new_pat))
  {
    new_pat->ty = pat->ty;
    new_pat->selector = pat->selector;
  }
  return new_pat;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Unguard a pattern list
//
///////////////////////////////////////////////////////////////////////////////

Pats FunctorMap::make_guard( Pats ps, Exp& e)
{
  
#line 400 "../../prop-src/funmap.pcc"
#line 403 "../../prop-src/funmap.pcc"
{
  if (ps) {
#line 403 "../../prop-src/funmap.pcc"
   return 
#line 403 "../../prop-src/funmap.pcc"
#line 403 "../../prop-src/funmap.pcc"
    list_1_(make_guard(ps->_1,e),make_guard(ps->_2,e))
#line 403 "../../prop-src/funmap.pcc"
#line 403 "../../prop-src/funmap.pcc"
    ; 
#line 403 "../../prop-src/funmap.pcc"
  } else {
#line 402 "../../prop-src/funmap.pcc"
   return 
#line 402 "../../prop-src/funmap.pcc"
#line 402 "../../prop-src/funmap.pcc"
    nil_1_
#line 402 "../../prop-src/funmap.pcc"
#line 402 "../../prop-src/funmap.pcc"
    ; 
#line 402 "../../prop-src/funmap.pcc"
  }
}
#line 404 "../../prop-src/funmap.pcc"
#line 404 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Unguard a labeled pattern list
//
///////////////////////////////////////////////////////////////////////////////

LabPats FunctorMap::make_guard( LabPats ps, Exp& e)
{
  
#line 415 "../../prop-src/funmap.pcc"
#line 423 "../../prop-src/funmap.pcc"
{
  if (ps) {
#line 418 "../../prop-src/funmap.pcc"
    
    LabPat lab_pat;
    lab_pat.label = ps->_1.label;
    lab_pat.pat   = make_guard( ps->_1.pat, e);
    return 
#line 422 "../../prop-src/funmap.pcc"
#line 422 "../../prop-src/funmap.pcc"
    list_1_(lab_pat,make_guard(ps->_2,e))
#line 422 "../../prop-src/funmap.pcc"
#line 422 "../../prop-src/funmap.pcc"
    ;
    
#line 423 "../../prop-src/funmap.pcc"
  } else {
#line 417 "../../prop-src/funmap.pcc"
   return 
#line 417 "../../prop-src/funmap.pcc"
#line 417 "../../prop-src/funmap.pcc"
    nil_1_
#line 417 "../../prop-src/funmap.pcc"
#line 417 "../../prop-src/funmap.pcc"
    ; 
#line 417 "../../prop-src/funmap.pcc"
  }
}
#line 424 "../../prop-src/funmap.pcc"
#line 424 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Check whether we know of the type
//
///////////////////////////////////////////////////////////////////////////////

Bool FunctorMap::is_known_type( Ty ty)
{
  return type_map.contains(ty)      ||
         ty_equal(ty, string_ty)    ||
         ty_equal(ty, quark_ty)
//       ty_equal(ty, integer_ty)   ||
//       ty_equal(ty, bool_ty)      ||
//       ty_equal(ty, real_ty)      ||
//       ty_equal(ty, character_ty)
  ;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Check whether we the type is rewritable.
//
///////////////////////////////////////////////////////////////////////////////

Bool FunctorMap::is_rewritable_type( Ty ty) { return type_map.contains(ty); }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to assign variable encoding to a non-terminal
//
///////////////////////////////////////////////////////////////////////////////

void FunctorMap::encode( Id id)
{
  if ( !var_map.contains( id))
  {
    ++variables;
    var_map.insert( id, variables);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to assign functor encoding to a type
//
///////////////////////////////////////////////////////////////////////////////

void FunctorMap::encode( Ty ty)
{
  
#line 476 "../../prop-src/funmap.pcc"
#line 488 "../../prop-src/funmap.pcc"
{
  Ty _V2 = deref_all(ty);
  if (_V2) {
    switch (_V2->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V2)->_1)) {
          switch (_TYCONty(_V2)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 479 "../../prop-src/funmap.pcc"
              
              if (! type_map.contains(_V2))
              {
                type_map.insert( _V2, functors);
                functors += _DATATYPEtycon(_TYCONty(_V2)->_1)->unit + _DATATYPEtycon(_TYCONty(_V2)->_1)->arg;
              }
              
#line 485 "../../prop-src/funmap.pcc"
              } break;
            default: {
              L5:; 
#line 486 "../../prop-src/funmap.pcc"
            for_each(Ty, ty, _TYCONty(_V2)->_2) encode(ty); 
#line 486 "../../prop-src/funmap.pcc"
              } break;
          }
        } else { goto L5; }
        } break;
      default: {
        L6:; } break;
    }
  } else { goto L6; }
}
#line 488 "../../prop-src/funmap.pcc"
#line 488 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to assign functor encoding to a pattern.
//  Assign a functor value to each distinct literal and pattern constructor.
//
///////////////////////////////////////////////////////////////////////////////

void FunctorMap::encode( Pat pat)
{
  
#line 500 "../../prop-src/funmap.pcc"
#line 578 "../../prop-src/funmap.pcc"
{
  for (;;) {
    if (pat) {
      switch (pat->tag__) {
        case a_Pat::tag_CONSpat: {
          if (_CONSpat(pat)->CONSpat) {
            if (_CONSpat(pat)->CONSpat->alg_ty) {
              switch (_CONSpat(pat)->CONSpat->alg_ty->tag__) {
                case a_Ty::tag_TYCONty: {
                  if (boxed(_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1)) {
                    switch (_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1->tag__) {
                      case a_TyCon::tag_DATATYPEtycon: {
#line 538 "../../prop-src/funmap.pcc"
                        
                        if (pat->ty != NOty && ! type_map.contains( pat->ty))
                        {  type_map.insert( pat->ty, functors);
                           functors += _DATATYPEtycon(_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1)->unit + _DATATYPEtycon(_TYCONty(_CONSpat(pat)->CONSpat->alg_ty)->_1)->arg;
                        }
                        return;
                        
#line 544 "../../prop-src/funmap.pcc"
                        } break;
                      default: {
                        L8:; 
#line 578 "../../prop-src/funmap.pcc"
                       error ("%LSorry: pattern not supported in rewriting: %p\n", pat); return; 
#line 578 "../../prop-src/funmap.pcc"
                        } break;
                    }
                  } else { goto L8; }
                  } break;
                default: { goto L8; } break;
              }
            } else { goto L8; }
          } else { goto L8; }
          } break;
        case a_Pat::tag_APPpat: {
#line 545 "../../prop-src/funmap.pcc"
         encode(pat->ty); pat = _APPpat(pat)->_2; 
#line 545 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_TYPEDpat: {
#line 504 "../../prop-src/funmap.pcc"
         pat = _TYPEDpat(pat)->_1; 
#line 504 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_ASpat: {
#line 503 "../../prop-src/funmap.pcc"
         pat = _ASpat(pat)->_2; 
#line 503 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_LITERALpat: {
          switch (_LITERALpat(pat)->LITERALpat->tag__) {
            case a_Literal::tag_BIGINTlit: { goto L8; } break;
            case a_Literal::tag_STRINGlit:
            case a_Literal::tag_REGEXPlit:
            case a_Literal::tag_QUARKlit: {
#line 525 "../../prop-src/funmap.pcc"
              
              if (! literal_map.contains(_LITERALpat(pat)->LITERALpat))
              {
                literal_map.insert( _LITERALpat(pat)->LITERALpat, functors);
                functors++;
              }
              return;
              
#line 532 "../../prop-src/funmap.pcc"
              } break;
            default: {
#line 534 "../../prop-src/funmap.pcc"
             bug ("%Luntransformed literal pattern %p found in rewriting\n",pat); 
#line 534 "../../prop-src/funmap.pcc"
              } break;
          }
          } break;
        case a_Pat::tag_TUPLEpat: {
#line 507 "../../prop-src/funmap.pcc"
          
          int i = 0;
          for_each (Pat, p, _TUPLEpat(pat)->TUPLEpat)
            { i++; encode(p); }
          if (max_arity < i)
            max_arity = i;
          return;
          
#line 514 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_RECORDpat: {
#line 516 "../../prop-src/funmap.pcc"
          
          for_each (LabPat, p, _RECORDpat(pat)->_1)
            encode(p.pat);
          int arity = arity_of(pat->ty);
          if (max_arity < arity)
            max_arity = arity;
          return;
          
#line 523 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_LISTpat: {
#line 547 "../../prop-src/funmap.pcc"
          
          Pat new_pat = CONSpat(_LISTpat(pat)->nil);
          new_pat->ty = pat->ty;
          encode( new_pat);
          for_each (Pat, i, _LISTpat(pat)->head)
            encode(i);
          if (max_arity < 2)
            max_arity = 2;
          pat = _LISTpat(pat)->tail;
          
#line 556 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_VECTORpat: {
#line 558 "../../prop-src/funmap.pcc"
          
          Pat new_pat = CONSpat(_VECTORpat(pat)->cons);
          new_pat->ty = pat->ty;
          encode(new_pat);
          for_each (Pat, p, _VECTORpat(pat)->elements)
            encode(p);
          int l = length(_VECTORpat(pat)->elements);
          if (max_arity < l)
            max_arity = l;
          if (pat->ty != NOty)
          {
            VectorId vec_id = vector_id( _VECTORpat(pat)->cons, pat->ty, l);
            if ( ! vector_map.contains(vec_id))
            {
              vector_map.insert(vec_id, functors);
              functors++;
            }
          }
          return;
          
#line 577 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_MARKEDpat: {
#line 505 "../../prop-src/funmap.pcc"
         pat = _MARKEDpat(pat)->_2; 
#line 505 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_WILDpat:
        case a_Pat::tag_IDpat: {
          L9:; 
#line 502 "../../prop-src/funmap.pcc"
         return; 
#line 502 "../../prop-src/funmap.pcc"
          } break;
        default: { goto L8; } break;
      }
    } else { goto L9; }
  }
}
#line 579 "../../prop-src/funmap.pcc"
#line 579 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to translate a pattern into a term.
//
///////////////////////////////////////////////////////////////////////////////

TreeTerm FunctorMap::trans( Pat pat)
{
  
#line 590 "../../prop-src/funmap.pcc"
#line 693 "../../prop-src/funmap.pcc"
{
  for (;;) {
    if (pat) {
      switch (pat->tag__) {
        case a_Pat::tag_WILDpat: {
          L11:; 
#line 592 "../../prop-src/funmap.pcc"
         return wild_term; 
#line 592 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_IDpat: {
#line 601 "../../prop-src/funmap.pcc"
          
          return var_map.contains(_IDpat(pat)->_1) ? var_term(var_map[_IDpat(pat)->_1]) : wild_term;
          
#line 603 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_CONSpat: {
          if (_CONSpat(pat)->CONSpat) {
#line 667 "../../prop-src/funmap.pcc"
           return new_term( mem_pool, type_map[pat->ty] + _CONSpat(pat)->CONSpat->tag); 
#line 667 "../../prop-src/funmap.pcc"
          } else {
            L12:; 
#line 693 "../../prop-src/funmap.pcc"
           error ("%LSorry: pattern not supported: %p\n", pat); return wild_term; 
#line 693 "../../prop-src/funmap.pcc"
          }
          } break;
        case a_Pat::tag_APPpat: {
          if (_APPpat(pat)->_1) {
            switch (_APPpat(pat)->_1->tag__) {
              case a_Pat::tag_CONSpat: {
                if (_CONSpat(_APPpat(pat)->_1)->CONSpat) {
                  if (_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty) {
                    switch (_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty->tag__) {
                      case a_Ty::tag_TYCONty: {
                        if (boxed(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)) {
                          switch (_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1->tag__) {
                            case a_TyCon::tag_DATATYPEtycon: {
#line 653 "../../prop-src/funmap.pcc"
                              
                              TreeTerm a = trans(_APPpat(pat)->_2);
                              
#line 655 "../../prop-src/funmap.pcc"
#line 663 "../../prop-src/funmap.pcc"
                              {
                                int _V4 = arity_of(_CONSpat(_APPpat(pat)->_1)->CONSpat->ty);
                                switch (_V4) {
                                  case 1: {
#line 658 "../../prop-src/funmap.pcc"
                                   return new_term( mem_pool, type_map[pat->ty] + _DATATYPEtycon(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)->unit + _CONSpat(_APPpat(pat)->_1)->CONSpat->tag, 1, &a); 
#line 658 "../../prop-src/funmap.pcc"
                                  } break;
                                  default: {
                                    if (a) {
                                      switch (a->tag__) {
                                        case a_TreeTerm::tag_tree_term: {
#line 660 "../../prop-src/funmap.pcc"
                                        _tree_term(a)->_1 = type_map[pat->ty] + _DATATYPEtycon(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)->unit + _CONSpat(_APPpat(pat)->_1)->CONSpat->tag; return a; 
#line 660 "../../prop-src/funmap.pcc"
                                          } break;
                                        default: {
                                          L13:; 
#line 662 "../../prop-src/funmap.pcc"
                                        return new_term( mem_pool, type_map[pat->ty] + _DATATYPEtycon(_TYCONty(_CONSpat(_APPpat(pat)->_1)->CONSpat->alg_ty)->_1)->unit + _CONSpat(_APPpat(pat)->_1)->CONSpat->tag, _V4);
                                          
#line 663 "../../prop-src/funmap.pcc"
                                          } break;
                                      }
                                    } else { goto L13; }
                                  }
                                }
                              }
#line 664 "../../prop-src/funmap.pcc"
#line 664 "../../prop-src/funmap.pcc"
                              
                              
#line 665 "../../prop-src/funmap.pcc"
                              } break;
                            default: { goto L12; } break;
                          }
                        } else { goto L12; }
                        } break;
                      default: { goto L12; } break;
                    }
                  } else { goto L12; }
                } else { goto L12; }
                } break;
              default: { goto L12; } break;
            }
          } else { goto L12; }
          } break;
        case a_Pat::tag_TYPEDpat: {
#line 594 "../../prop-src/funmap.pcc"
         pat = _TYPEDpat(pat)->_1; 
#line 594 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_ASpat: {
#line 593 "../../prop-src/funmap.pcc"
         pat = _ASpat(pat)->_2; 
#line 593 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_LITERALpat: {
          switch (_LITERALpat(pat)->LITERALpat->tag__) {
            case a_Literal::tag_STRINGlit:
            case a_Literal::tag_REGEXPlit:
            case a_Literal::tag_QUARKlit: {
#line 597 "../../prop-src/funmap.pcc"
             return new_term(mem_pool,literal_map[_LITERALpat(pat)->LITERALpat]); 
#line 597 "../../prop-src/funmap.pcc"
              } break;
            default: {
#line 599 "../../prop-src/funmap.pcc"
             return wild_term; 
#line 599 "../../prop-src/funmap.pcc"
              } break;
          }
          } break;
        case a_Pat::tag_TUPLEpat: {
#line 605 "../../prop-src/funmap.pcc"
          
          int arity = length (_TUPLEpat(pat)->TUPLEpat);
          TreeTerm * subterms =
             (TreeTerm *)mem_pool.c_alloc( sizeof( TreeTerm) * arity);
          int i = 0;
          for_each (Pat, p, _TUPLEpat(pat)->TUPLEpat)
            subterms[i++] = trans(p);
          return new_term( mem_pool, 0, arity, subterms);
          
#line 613 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_RECORDpat: {
#line 615 "../../prop-src/funmap.pcc"
          
          
#line 616 "../../prop-src/funmap.pcc"
#line 646 "../../prop-src/funmap.pcc"
          {
            Ty _V3 = deref(pat->ty);
            if (_V3) {
              switch (_V3->tag__) {
                case a_Ty::tag_TYCONty: {
                  if (boxed(_TYCONty(_V3)->_1)) {
                    switch (_TYCONty(_V3)->_1->tag__) {
                      case a_TyCon::tag_RECORDtycon: {
#line 619 "../../prop-src/funmap.pcc"
                        
                        Bool relevant[256];
                        int i;
                        int arity;
                        
                        i = arity = 0;
                        for_each(Ty, t, _TYCONty(_V3)->_2)
                          if (relevant[i++] = is_known_type(t))
                            arity++;
                        TreeTerm * subterms =
                           (TreeTerm *)mem_pool.c_alloc( sizeof( TreeTerm) * arity);
                        for (i = 0; i < arity; i++)
                           subterms[i] = wild_term;
                        for_each (LabPat, p, _RECORDpat(pat)->_1)
                        {
                          Ids labs; Tys ts;
                          for (i = 0, labs = _RECORDtycon(_TYCONty(_V3)->_1)->_1, ts = _TYCONty(_V3)->_2;
                               labs && ts; labs = labs->_2, ts = ts->_2)
                          {
                            if (p.label == labs->_1)
                              {  subterms[i] = trans(p.pat); break; }
                            if (is_known_type(ts->_1))
                              i++;
                          }
                        }
                        return new_term( mem_pool, 0, arity,subterms);
                        
#line 645 "../../prop-src/funmap.pcc"
                        } break;
                      default: {
                        L14:; 
#line 646 "../../prop-src/funmap.pcc"
                       bug( "%Lillegal record pattern %p\n", pat); 
#line 646 "../../prop-src/funmap.pcc"
                        } break;
                    }
                  } else { goto L14; }
                  } break;
                default: { goto L14; } break;
              }
            } else { goto L14; }
          }
#line 647 "../../prop-src/funmap.pcc"
#line 647 "../../prop-src/funmap.pcc"
          
          
#line 648 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_LISTpat: {
          if (_LISTpat(pat)->head) {
#line 672 "../../prop-src/funmap.pcc"
            
            Pat new_tail = 
#line 673 "../../prop-src/funmap.pcc"
#line 673 "../../prop-src/funmap.pcc"
            LISTpat(_LISTpat(pat)->cons, _LISTpat(pat)->nil, _LISTpat(pat)->head->_2, _LISTpat(pat)->tail)
#line 673 "../../prop-src/funmap.pcc"
#line 673 "../../prop-src/funmap.pcc"
            ;
            Pat new_p    = APPpat( CONSpat( _LISTpat(pat)->cons), TUPLEpat(
#line 674 "../../prop-src/funmap.pcc"
#line 674 "../../prop-src/funmap.pcc"
            list_1_(_LISTpat(pat)->head->_1,list_1_(new_tail))
#line 674 "../../prop-src/funmap.pcc"
#line 674 "../../prop-src/funmap.pcc"
            ));
            new_p->ty    = new_tail->ty = pat->ty;
            pat = new_p;
            
#line 677 "../../prop-src/funmap.pcc"
          } else {
            if (_LISTpat(pat)->tail) {
#line 670 "../../prop-src/funmap.pcc"
            pat = _LISTpat(pat)->tail; 
#line 670 "../../prop-src/funmap.pcc"
            } else {
#line 669 "../../prop-src/funmap.pcc"
             Pat p = CONSpat(_LISTpat(pat)->nil); p->ty = pat->ty; pat = p; 
#line 669 "../../prop-src/funmap.pcc"
            }
          }
          } break;
        case a_Pat::tag_VECTORpat: {
#line 679 "../../prop-src/funmap.pcc"
          
          TreeTerm a     = trans( TUPLEpat(_VECTORpat(pat)->elements));
          int      arity = length(_VECTORpat(pat)->elements);
          
#line 682 "../../prop-src/funmap.pcc"
#line 690 "../../prop-src/funmap.pcc"
          {
            if (a) {
              switch (a->tag__) {
                case a_TreeTerm::tag_tree_term: {
#line 685 "../../prop-src/funmap.pcc"
                  
                  _tree_term(a)->_1 = vector_map[ vector_id( _VECTORpat(pat)->cons, pat->ty, arity)];
                  return a;
                  
#line 688 "../../prop-src/funmap.pcc"
                  } break;
                default: {
                  L15:; 
#line 690 "../../prop-src/funmap.pcc"
                 bug ("%Lillegal pattern: %p\n", pat); return wild_term; 
#line 690 "../../prop-src/funmap.pcc"
                  } break;
              }
            } else { goto L15; }
          }
#line 691 "../../prop-src/funmap.pcc"
#line 691 "../../prop-src/funmap.pcc"
          
          
#line 692 "../../prop-src/funmap.pcc"
          } break;
        case a_Pat::tag_MARKEDpat: {
#line 595 "../../prop-src/funmap.pcc"
         pat = _MARKEDpat(pat)->_2; 
#line 595 "../../prop-src/funmap.pcc"
          } break;
        default: { goto L12; } break;
      }
    } else { goto L11; }
  }
}
#line 694 "../../prop-src/funmap.pcc"
#line 694 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Compute ceil(ln(2))
//
///////////////////////////////////////////////////////////////////////////////

int ln2 (int n)
{
  int bits = 0;
  while (n > 0)
    { n >>= 1; bits++; }
  return bits;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the rhs non-terminal (if it is a chain rule)
//  Otherwise, returns NIL.
//
///////////////////////////////////////////////////////////////////////////////

Id FunctorMap::chain_rule_rhs( Pat pat)
{
  
#line 720 "../../prop-src/funmap.pcc"
#line 726 "../../prop-src/funmap.pcc"
{
  if (pat) {
    switch (pat->tag__) {
      case a_Pat::tag_IDpat: {
#line 722 "../../prop-src/funmap.pcc"
       return var_map.contains(_IDpat(pat)->_1) ? _IDpat(pat)->_1 : 0; 
#line 722 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_TYPEDpat: {
#line 725 "../../prop-src/funmap.pcc"
       return chain_rule_rhs(_TYPEDpat(pat)->_1); 
#line 725 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_ASpat: {
#line 723 "../../prop-src/funmap.pcc"
       return chain_rule_rhs(_ASpat(pat)->_2); 
#line 723 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 724 "../../prop-src/funmap.pcc"
       return chain_rule_rhs(_MARKEDpat(pat)->_2); 
#line 724 "../../prop-src/funmap.pcc"
        } break;
      default: {
        L16:; 
#line 726 "../../prop-src/funmap.pcc"
       return 0; 
#line 726 "../../prop-src/funmap.pcc"
        } break;
    }
  } else { goto L16; }
}
#line 727 "../../prop-src/funmap.pcc"
#line 727 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to partition the set of rules according to the types of the
//  patterns.  Also encode the patterns in the process.
//
///////////////////////////////////////////////////////////////////////////////

MatchRules FunctorMap::partition_rules( MatchRules rules)
{
  bottomup_rules = 
#line 739 "../../prop-src/funmap.pcc"
#line 739 "../../prop-src/funmap.pcc"
nil_1_
#line 739 "../../prop-src/funmap.pcc"
#line 739 "../../prop-src/funmap.pcc"
;
  // First, we assign a new type variable for each lhs non-terminal.
  {
    for_each (MatchRule, r, rules)
    {
      
#line 744 "../../prop-src/funmap.pcc"
#line 772 "../../prop-src/funmap.pcc"
{
#line 747 "../../prop-src/funmap.pcc"
  
  if (r->mode == MatchRuleInfo::BOTTOMUP)
  {
    bottomup_rules = 
#line 750 "../../prop-src/funmap.pcc"
#line 750 "../../prop-src/funmap.pcc"
  list_1_(r,bottomup_rules)
#line 750 "../../prop-src/funmap.pcc"
#line 750 "../../prop-src/funmap.pcc"
  ;
  if (r->_1)
  {
    HashTable::Entry * lhs_entry = nonterm_map.lookup(r->_1);
    if (! lhs_entry)
      nonterm_map.insert(r->_1,mkvar());
    encode(r->_1);  // compute encoding for the variable
    HashTable::Entry * e = nonterm_rules.lookup(r->_1);
    if ( !e)
      nonterm_rules.insert( r->_1, 
#line 759 "../../prop-src/funmap.pcc"
#line 759 "../../prop-src/funmap.pcc"
  list_1_(r)
#line 759 "../../prop-src/funmap.pcc"
#line 759 "../../prop-src/funmap.pcc"
  );
  else
    { e->v = 
#line 761 "../../prop-src/funmap.pcc"
#line 761 "../../prop-src/funmap.pcc"
  list_1_(r,MatchRules(e->v))
#line 761 "../../prop-src/funmap.pcc"
#line 761 "../../prop-src/funmap.pcc"
  ; }
  }
  else if (dynamic_search)
    error( "%!missing non-terminal in tree grammar rule: %r\n",
           r->loc(), r);
  }
  else if (r->_1)
  {
  error( "%!illegal non-terminal in non bottom-up rule: %r\n",
         r->loc(), r);
  }
  
#line 772 "../../prop-src/funmap.pcc"
}
#line 773 "../../prop-src/funmap.pcc"
#line 773 "../../prop-src/funmap.pcc"

    }
  }

  bottomup_rules = rev(bottomup_rules);

  // Compute the size needed to encode each non-terminal

  {
    foreach_entry (e, nonterm_rules)
    {
      int bits = ln2( length( MatchRules( e->v))+1);
      nonterm_rules_bits.insert( e->k, HashTable::Value( bits));
    }
  }

  // Type check all the rules next.
  // We have to also compute the type map for each lhs non-terminal.
  // Of course, a non-terminal but have only one single type.
  // This is done by unifying all occurances of a non-terminal.

  patvar_typemap = &nonterm_map; // set the pattern variable type map

  for_each (MatchRule, r, bottomup_rules)
  {
    
#line 798 "../../prop-src/funmap.pcc"
#line 834 "../../prop-src/funmap.pcc"
{
#line 801 "../../prop-src/funmap.pcc"
  
  r->set_loc();
  Ty ty = r->ty = type_of(r->_2);
  
  // Check the type of the non-terminal (if any).
  if (r->_1)
  {
    Ty lhs_ty = Ty(nonterm_map.lookup(r->_1)->v);
    if (! unify(lhs_ty, ty))
    {
      error( "%!type mismatch between nonterminal %s(type %T) and rule %r(type %T)\n",
             r->loc(),r->_1,lhs_ty,r,ty);
    }
  }
  
  if ( !is_datatype(ty))
     error( "%!rule %r is of a non datatype: %T\n",r->loc(),r,ty);
  
  // Collect chain rules.
  
  if (r->_1)
  {
    Id rhs = chain_rule_rhs(r->_2);
    if (rhs)
    {
      HashTable::Entry * cr = chain_rules.lookup(rhs);
      if (! cr)
        chain_rules.insert( rhs, 
#line 828 "../../prop-src/funmap.pcc"
#line 828 "../../prop-src/funmap.pcc"
  list_1_(r)
#line 828 "../../prop-src/funmap.pcc"
#line 828 "../../prop-src/funmap.pcc"
  );
  else
    { cr->v = 
#line 830 "../../prop-src/funmap.pcc"
#line 830 "../../prop-src/funmap.pcc"
  list_1_(r,MatchRules(cr->v))
#line 830 "../../prop-src/funmap.pcc"
#line 830 "../../prop-src/funmap.pcc"
  ; }
  r->is_chain_rule = true;
  }
  }
  
#line 834 "../../prop-src/funmap.pcc"
}
#line 835 "../../prop-src/funmap.pcc"
#line 835 "../../prop-src/funmap.pcc"

  }

  patvar_typemap = 0; // reset the pattern variable type map

  // Now partition rules by type and assign functor encoding.
  // Since we have also typed the rules, this is quite simple: just
  // another pass.  We have to make sure that after the type inference
  // we don't have any more polymorphic types inside the patterns.
  int rule_num = 0;
  for_each (MatchRule, R, rules)
  {
    
#line 847 "../../prop-src/funmap.pcc"
#line 881 "../../prop-src/funmap.pcc"
{
  if (
#line 849 "../../prop-src/funmap.pcc"
  (R->mode != MatchRuleInfo::BOTTOMUP)
#line 849 "../../prop-src/funmap.pcc"
) {
    
#line 850 "../../prop-src/funmap.pcc"
    
    R->set_loc();
    R->ty = type_of(R->_2);
    HashTable::Entry * e = rule_maps[R->mode]->lookup(R->ty);
    if (e)
      e->v = 
#line 855 "../../prop-src/funmap.pcc"
#line 855 "../../prop-src/funmap.pcc"
    list_1_(R,MatchRules(e->v))
#line 855 "../../prop-src/funmap.pcc"
#line 855 "../../prop-src/funmap.pcc"
    ;
    else
      rule_maps[ R->mode]->insert( R->ty, 
#line 857 "../../prop-src/funmap.pcc"
#line 857 "../../prop-src/funmap.pcc"
    list_1_(R)
#line 857 "../../prop-src/funmap.pcc"
#line 857 "../../prop-src/funmap.pcc"
    );
    
#line 858 "../../prop-src/funmap.pcc"
  } else {
    
#line 860 "../../prop-src/funmap.pcc"
    
    if (! is_ground(R->ty))
      error( "%!rule %r has incomplete type %T\n", R->loc(), R, R->ty);
    
    HashTable::Entry * e = rule_map.lookup(R->ty);
    if (e)
      e->v = 
#line 866 "../../prop-src/funmap.pcc"
#line 866 "../../prop-src/funmap.pcc"
    list_1_(R,MatchRules(e->v))
#line 866 "../../prop-src/funmap.pcc"
#line 866 "../../prop-src/funmap.pcc"
    ;
    else
      rule_map.insert( R->ty, 
#line 868 "../../prop-src/funmap.pcc"
#line 868 "../../prop-src/funmap.pcc"
    list_1_(R)
#line 868 "../../prop-src/funmap.pcc"
#line 868 "../../prop-src/funmap.pcc"
    );
    
            // convert literals into guards
            // BUG: 2-6-97  This doesn't work right since
            // the guard testing is not prioritized properly !!!
    
            R->_2 = make_guard( R->_2, R->_3);
    
            // assign functor encoding
    
            encode( R->_2);
    
            R->rule_number = rule_num++;
          
#line 881 "../../prop-src/funmap.pcc"
  }
}
#line 882 "../../prop-src/funmap.pcc"
#line 882 "../../prop-src/funmap.pcc"

  }

  return bottomup_rules;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the functor and variable table.
//
///////////////////////////////////////////////////////////////////////////////

void FunctorMap::compute_names()
{
   functor_names  = (Id *) mem_pool.c_alloc( sizeof(Id) * functors);
   variable_names = (Id *) mem_pool.c_alloc( sizeof(Id) * (variables + N + 4));

   {  for (int i = N + variables - 1; i >= 0; i--) variable_names[i] = 0; }
   {  for (int i = functors - 1; i >= 0; i--)  functor_names[i] = "???"; }
   variable_names[0] = "_";

   // Compute variable names

   {
     foreach_entry (i,var_map)
       variable_names[var_map.value(i)] = (Id)var_map.key(i);
   }

   // Compute literal names
   {
     foreach_entry (i,literal_map)
     {
       Literal l = (Literal)literal_map.key(i);
       Functor f = literal_map.value(i);
       char buf[1024];
       std::ostrstream b(buf,sizeof(buf));
       std::ostream& s = b;
       s << l << std::ends;
       functor_names[f] = Quark(buf);
     }
   }

   // Compute constructor names
   {
     foreach_entry (i,type_map)
     {
       Ty      t = (Ty)type_map.key(i);
       Functor f = type_map.value(i);
       
#line 930 "../../prop-src/funmap.pcc"
#line 947 "../../prop-src/funmap.pcc"
{
  Ty _V5 = deref(t);
  if (_V5) {
    switch (_V5->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V5)->_1)) {
          switch (_TYCONty(_V5)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 933 "../../prop-src/funmap.pcc"
              
              int arity = _DATATYPEtycon(_TYCONty(_V5)->_1)->unit + _DATATYPEtycon(_TYCONty(_V5)->_1)->arg;
              for (int j = 0; j < arity; j++)
              {
                
#line 937 "../../prop-src/funmap.pcc"
#line 944 "../../prop-src/funmap.pcc"
              {
                Cons _V6 = _DATATYPEtycon(_TYCONty(_V5)->_1)->terms[j];
                if (_V6) {
#line 940 "../../prop-src/funmap.pcc"
                  
                  functor_names[f + (_V6->ty == NOty ? _V6->tag : _V6->tag + _DATATYPEtycon(_TYCONty(_V5)->_1)->unit)] = _V6->name;
                  
#line 942 "../../prop-src/funmap.pcc"
                } else {}
              }
#line 944 "../../prop-src/funmap.pcc"
#line 944 "../../prop-src/funmap.pcc"
              
              }
              
#line 946 "../../prop-src/funmap.pcc"
              } break;
            default: {
              L17:; 
#line 947 "../../prop-src/funmap.pcc"
             bug ("compute_names()"); 
#line 947 "../../prop-src/funmap.pcc"
              } break;
          }
        } else { goto L17; }
        } break;
      default: { goto L17; } break;
    }
  } else { goto L17; }
}
#line 948 "../../prop-src/funmap.pcc"
#line 948 "../../prop-src/funmap.pcc"

     }
   }

   // Compute vector constructor names
   {
     foreach_entry (i, vector_map)
     {
       VectorId id = (VectorId) vector_map.key(i);
       Functor  f  = vector_map.value(i);
       if (id->cons)
         functor_names[f] = id->cons->name;
     }
   }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print a report detailing the functor/variable encoding,
//  the tree grammar and the generated table size.
//
///////////////////////////////////////////////////////////////////////////////

void FunctorMap::print_report( std::ostream& log)
{
  if (var_map.size() > 0)
  {
    log << "Variable encoding:\n";
    foreach_entry (e, var_map)
    {
      log << "\tnon-terminal \"" << (Id)var_map.key(e) << "\"\t=\t"
          << var_map.value(e) << '\n';
    }
  }

  if (literal_map.size() > 0)
  {
    log << "\nFunctor encoding for literals:\n";
    foreach_entry (e, literal_map)
    {
      log << "literal " << (Literal)literal_map.key(e) << "\t=\t"
          << literal_map.value(e) << '\n';
    }
  }

  log << "\nFunctor encoding for constructors:\n";

  {
    foreach_entry (e, type_map)
    {
      Ty      t = (Ty)type_map.key(e);
      Functor f = type_map.value(e);
      log << "datatype " << t << ":\n";
      
#line 1001 "../../prop-src/funmap.pcc"
#line 1020 "../../prop-src/funmap.pcc"
{
  Ty _V7 = deref(t);
  if (_V7) {
    switch (_V7->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V7)->_1)) {
          switch (_TYCONty(_V7)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 1004 "../../prop-src/funmap.pcc"
              
              int arity = _DATATYPEtycon(_TYCONty(_V7)->_1)->unit + _DATATYPEtycon(_TYCONty(_V7)->_1)->arg;
              for (int i = 0; i < arity; i++)
              {
                
#line 1008 "../../prop-src/funmap.pcc"
#line 1016 "../../prop-src/funmap.pcc"
              {
                Cons _V8 = _DATATYPEtycon(_TYCONty(_V7)->_1)->terms[i];
                if (_V8) {
#line 1011 "../../prop-src/funmap.pcc"
                  
                  log << '\t' << _V8->name << "\t=\t"
                      << f + (_V8->ty == NOty ? _V8->tag : _V8->tag + _DATATYPEtycon(_TYCONty(_V7)->_1)->unit) << '\n';
                  
#line 1014 "../../prop-src/funmap.pcc"
                } else {}
              }
#line 1016 "../../prop-src/funmap.pcc"
#line 1016 "../../prop-src/funmap.pcc"
              
              }
              
#line 1018 "../../prop-src/funmap.pcc"
              } break;
            default: {
              L18:; } break;
          }
        } else { goto L18; }
        } break;
      default: { goto L18; } break;
    }
  } else { goto L18; }
}
#line 1020 "../../prop-src/funmap.pcc"
#line 1020 "../../prop-src/funmap.pcc"

    }
  }

  if (tree_gen)
  {
    log << "\nIndex compression is "
        << (use_compression ? "enabled" : "disabled")
        << "\nAlgorithm is " << tree_gen->algorithm();
    tree_gen->print_report(log);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to return the cost expression for a pattern.
//
///////////////////////////////////////////////////////////////////////////////

Exp FunctorMap::cost_expr( Id lhs, Pat pat)
{
  
#line 1041 "../../prop-src/funmap.pcc"
#line 1044 "../../prop-src/funmap.pcc"
{
  if (pat) {
#line 1044 "../../prop-src/funmap.pcc"
   return cost_expr( lhs, pat, LITERALexp( INTlit(1))); 
#line 1044 "../../prop-src/funmap.pcc"
  } else {
#line 1043 "../../prop-src/funmap.pcc"
   return LITERALexp( INTlit(0)); 
#line 1043 "../../prop-src/funmap.pcc"
  }
}
#line 1045 "../../prop-src/funmap.pcc"
#line 1045 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the cost expression for a pattern
//
///////////////////////////////////////////////////////////////////////////////

Exp FunctorMap::cost_expr( Id lhs, Pat pat, Exp exp)
{
  
#line 1056 "../../prop-src/funmap.pcc"
#line 1076 "../../prop-src/funmap.pcc"
{
  if (pat) {
    switch (pat->tag__) {
      case a_Pat::tag_WILDpat: {} break;
      case a_Pat::tag_IDpat: {} break;
      case a_Pat::tag_APPpat: {
#line 1063 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_APPpat(pat)->_2,exp); 
#line 1063 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_TYPEDpat: {
#line 1061 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_TYPEDpat(pat)->_1,exp); 
#line 1061 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_ASpat: {
#line 1059 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_ASpat(pat)->_2,exp); 
#line 1059 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_CONTEXTpat: {
#line 1064 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_CONTEXTpat(pat)->_2,exp); 
#line 1064 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_ARRAYpat: {
#line 1067 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_ARRAYpat(pat)->_1,exp); 
#line 1067 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_TUPLEpat: {
#line 1065 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_TUPLEpat(pat)->TUPLEpat,exp); 
#line 1065 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_EXTUPLEpat: {
#line 1066 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_EXTUPLEpat(pat)->EXTUPLEpat,exp); 
#line 1066 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_RECORDpat: {
#line 1068 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_RECORDpat(pat)->_1,exp); 
#line 1068 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_LISTpat: {
#line 1070 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_LISTpat(pat)->head,cost_expr(lhs,_LISTpat(pat)->tail,exp)); 
#line 1070 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_VECTORpat: {
#line 1072 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_VECTORpat(pat)->len,cost_expr(lhs,_VECTORpat(pat)->array,
        cost_expr(lhs,_VECTORpat(pat)->elements,exp))); 
#line 1073 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_GUARDpat: {
#line 1062 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_GUARDpat(pat)->_1,exp); 
#line 1062 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_MARKEDpat: {
#line 1060 "../../prop-src/funmap.pcc"
       return cost_expr(lhs,_MARKEDpat(pat)->_2,exp); 
#line 1060 "../../prop-src/funmap.pcc"
        } break;
      case a_Pat::tag_CONSpat:
      case a_Pat::tag_LITERALpat: {
        L19:; 
#line 1058 "../../prop-src/funmap.pcc"
       return exp; 
#line 1058 "../../prop-src/funmap.pcc"
        } break;
      default: {
#line 1076 "../../prop-src/funmap.pcc"
       return exp; 
#line 1076 "../../prop-src/funmap.pcc"
        } break;
    }
  } else { goto L19; }
}
#line 1077 "../../prop-src/funmap.pcc"
#line 1077 "../../prop-src/funmap.pcc"


  // BUG fix: if the argument type is not a datatype or
  // not rewritable, then there is no cost to consider.

  if ( !is_datatype(pat->ty) || !is_rewritable_type(pat->ty))
     return exp;

  Ty state_rec_ty = mkptrty( mkidty( Quark( class_name,"_StateRec"),
#line 1085 "../../prop-src/funmap.pcc"
#line 1085 "../../prop-src/funmap.pcc"
nil_1_
#line 1085 "../../prop-src/funmap.pcc"
#line 1085 "../../prop-src/funmap.pcc"
));
  Exp cost_e =
     INDEXexp(
       ARROWexp(
          CASTexp( state_rec_ty,
              APPexp( ARROWexp( pat->selector, "get_state_rec"), TUPLEexp(
#line 1090 "../../prop-src/funmap.pcc"
#line 1090 "../../prop-src/funmap.pcc"
nil_1_
#line 1090 "../../prop-src/funmap.pcc"
#line 1090 "../../prop-src/funmap.pcc"
))),
              "cost"), LITERALexp( INTlit( int( var_map[lhs]))));

  return exp == NOexp ? cost_e : BINOPexp( "+", cost_e,exp);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the cost expression for a pattern list
//
///////////////////////////////////////////////////////////////////////////////

Exp FunctorMap::cost_expr( Id lhs, Pats pats, Exp exp)
{
  
#line 1104 "../../prop-src/funmap.pcc"
#line 1107 "../../prop-src/funmap.pcc"
{
  if (pats) {
#line 1107 "../../prop-src/funmap.pcc"
   return cost_expr( lhs, pats->_1, cost_expr( lhs, pats->_2, exp)); 
#line 1107 "../../prop-src/funmap.pcc"
  } else {
#line 1106 "../../prop-src/funmap.pcc"
   return exp; 
#line 1106 "../../prop-src/funmap.pcc"
  }
}
#line 1108 "../../prop-src/funmap.pcc"
#line 1108 "../../prop-src/funmap.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the cost expression for a labeled pattern list
//
///////////////////////////////////////////////////////////////////////////////

Exp FunctorMap::cost_expr( Id lhs, LabPats pats, Exp exp)
{
  
#line 1119 "../../prop-src/funmap.pcc"
#line 1122 "../../prop-src/funmap.pcc"
{
  if (pats) {
#line 1122 "../../prop-src/funmap.pcc"
   return cost_expr( lhs, pats->_1.pat, cost_expr( lhs, pats->_2, exp)); 
#line 1122 "../../prop-src/funmap.pcc"
  } else {
#line 1121 "../../prop-src/funmap.pcc"
   return exp; 
#line 1121 "../../prop-src/funmap.pcc"
  }
}
#line 1123 "../../prop-src/funmap.pcc"
#line 1123 "../../prop-src/funmap.pcc"

}
#line 1125 "../../prop-src/funmap.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 352
Number of ifs generated      = 37
Number of switches generated = 25
Number of labels             = 15
Number of gotos              = 34
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
