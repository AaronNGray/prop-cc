///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\logicgen.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#define PROP_TUPLE2_USED
#define PROP_TUPLE3_USED
#include <propdefs.h>
#line 1 "../../prop-src/logicgen.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the constraint compiler.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/strings/quark.h>
#include "ir.h"
#include "ast.h"
#include "constraint.h"
#include "wam.h"
#include "type.h"
#include "hashtab.h"
#include "datagen.h"
#include "logicgen.h"
#include "pat.h"
#include "datatype.h"
#include "list.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Method for generating the interface methods for a logic
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeClass::generate_logic_interface( CodeGen&) {}
void DatatypeClass::generate_logic_implementation( CodeGen&, Tys, DefKind) {}

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor for the constraint compiler implementation
//
///////////////////////////////////////////////////////////////////////////////

ConstraintCompilerInternal::ConstraintCompilerInternal( Id id)
   : class_name(id),
     rule_map     (string_hash,string_equal),
     typing_map   (string_hash,string_equal),
     instness_map (string_hash,string_equal),
     det_map      (string_hash,string_equal)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Destructor for the constraint compiler implementation
//
///////////////////////////////////////////////////////////////////////////////

ConstraintCompilerInternal::~ConstraintCompilerInternal() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compile a set of constraint rules
//
///////////////////////////////////////////////////////////////////////////////

void ConstraintCompiler::compile_ruleset (Id id, ConstraintSet rule_set)
{
  ConstraintCompilerInternal G(id);
  internal = &G;

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Rules by kind.
  //
  ////////////////////////////////////////////////////////////////////////////

  ConstraintRules                rules          = 
#line 71 "../../prop-src/logicgen.pcc"
#line 71 "../../prop-src/logicgen.pcc"
nil_1_
#line 71 "../../prop-src/logicgen.pcc"
#line 71 "../../prop-src/logicgen.pcc"
;
  
#line 72 "../../prop-src/logicgen.pcc"
a_List<Tuple2<Id, Ty> > *  
#line 72 "../../prop-src/logicgen.pcc"
                typing_rules   = 
#line 72 "../../prop-src/logicgen.pcc"
nil_1_
#line 72 "../../prop-src/logicgen.pcc"
#line 72 "../../prop-src/logicgen.pcc"
;
  
#line 73 "../../prop-src/logicgen.pcc"
a_List<Tuple2<Id, Pat> > *  
#line 73 "../../prop-src/logicgen.pcc"
               instness_rules = 
#line 73 "../../prop-src/logicgen.pcc"
nil_1_
#line 73 "../../prop-src/logicgen.pcc"
#line 73 "../../prop-src/logicgen.pcc"
;
  
#line 74 "../../prop-src/logicgen.pcc"
a_List<Tuple3<Id, Pats, Determinism> > *  
#line 74 "../../prop-src/logicgen.pcc"
 det_rules      = 
#line 74 "../../prop-src/logicgen.pcc"
nil_1_
#line 74 "../../prop-src/logicgen.pcc"
#line 74 "../../prop-src/logicgen.pcc"
;

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Partition the rules by kind.
  //
  ////////////////////////////////////////////////////////////////////////////

  
#line 82 "../../prop-src/logicgen.pcc"
#line 101 "../../prop-src/logicgen.pcc"
{
#line 84 "../../prop-src/logicgen.pcc"
  
  ConstraintDefs ds = rule_set->CONSTRAINTset;
  
#line 86 "../../prop-src/logicgen.pcc"
#line 99 "../../prop-src/logicgen.pcc"
  {
    for (;;) {
      if (ds) {
#line 88 "../../prop-src/logicgen.pcc"
        
        
#line 89 "../../prop-src/logicgen.pcc"
#line 96 "../../prop-src/logicgen.pcc"
        {
          ConstraintDef _V1 = ds->_1;
          switch (_V1->tag__) {
            case a_ConstraintDef::tag_CONSTRAINTruledef: {
#line 90 "../../prop-src/logicgen.pcc"
             rules = 
#line 90 "../../prop-src/logicgen.pcc"
#line 90 "../../prop-src/logicgen.pcc"
              list_1_(_CONSTRAINTruledef(_V1)->CONSTRAINTruledef,rules)
#line 90 "../../prop-src/logicgen.pcc"
#line 90 "../../prop-src/logicgen.pcc"
              ;  
#line 90 "../../prop-src/logicgen.pcc"
              } break;
            case a_ConstraintDef::tag_CONSTRAINTtype: {
#line 92 "../../prop-src/logicgen.pcc"
             typing_rules = 
#line 92 "../../prop-src/logicgen.pcc"
#line 92 "../../prop-src/logicgen.pcc"
              list_1_(mkTuple2(_CONSTRAINTtype(_V1)->_1,_CONSTRAINTtype(_V1)->_2),typing_rules)
#line 92 "../../prop-src/logicgen.pcc"
#line 92 "../../prop-src/logicgen.pcc"
              ; 
#line 92 "../../prop-src/logicgen.pcc"
              } break;
            case a_ConstraintDef::tag_CONSTRAINTinstness: {
#line 94 "../../prop-src/logicgen.pcc"
             instness_rules = 
#line 94 "../../prop-src/logicgen.pcc"
#line 94 "../../prop-src/logicgen.pcc"
              list_1_(mkTuple2(_CONSTRAINTinstness(_V1)->_1,_CONSTRAINTinstness(_V1)->_2),instness_rules)
#line 94 "../../prop-src/logicgen.pcc"
#line 94 "../../prop-src/logicgen.pcc"
              ; 
#line 94 "../../prop-src/logicgen.pcc"
              } break;
            default: {
#line 96 "../../prop-src/logicgen.pcc"
             det_rules = 
#line 96 "../../prop-src/logicgen.pcc"
#line 96 "../../prop-src/logicgen.pcc"
              list_1_(mkTuple3(_CONSTRAINTdet(_V1)->_1,_CONSTRAINTdet(_V1)->_2,_CONSTRAINTdet(_V1)->_3),det_rules)
#line 96 "../../prop-src/logicgen.pcc"
#line 96 "../../prop-src/logicgen.pcc"
              ; 
#line 96 "../../prop-src/logicgen.pcc"
              } break;
          }
        }
#line 97 "../../prop-src/logicgen.pcc"
#line 97 "../../prop-src/logicgen.pcc"
        
        ds = ds->_2;
        
#line 99 "../../prop-src/logicgen.pcc"
      } else { goto L1; }
    }
    L1:;
  }
#line 100 "../../prop-src/logicgen.pcc"
#line 100 "../../prop-src/logicgen.pcc"
  
  
#line 101 "../../prop-src/logicgen.pcc"
}
#line 102 "../../prop-src/logicgen.pcc"
#line 102 "../../prop-src/logicgen.pcc"


  rules          = rev( rules);
  typing_rules   = rev( typing_rules);
  instness_rules = rev( instness_rules);
  det_rules      = rev( det_rules);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Process each kind of rules.
  //
  ////////////////////////////////////////////////////////////////////////////

  process_typing_rules( id, typing_rules);
  process_ruleset( id, rules);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Translate the rules into constraint abstract machine instructions.
  //
  ////////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to add a predicate : type judgement into the typing map.
//
///////////////////////////////////////////////////////////////////////////////

void ConstraintCompiler::add_predicate_type( Id id, Ty ty)
{
  HashTable::Entry * e = internal->typing_map.lookup(id);
  if (e)
  {
    Ty old_ty = Ty(internal->typing_map.value(e));
    if ( !unify( ty, old_ty))
      error( "%Lpredicate %s: expecting type %T but found %T\n",
             id, old_ty, ty);
  }
  else
    internal->typing_map.insert( id, ty);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to process the typing rules.
//
///////////////////////////////////////////////////////////////////////////////

void ConstraintCompiler::process_typing_rules( Id id, 
#line 151 "../../prop-src/logicgen.pcc"
a_List<Tuple2<Id, Ty> > *  
#line 151 "../../prop-src/logicgen.pcc"
 typing_rules)
{
  
#line 159 "../../prop-src/logicgen.pcc"
{
  for (;;) {
    if (typing_rules) {
#line 156 "../../prop-src/logicgen.pcc"
      
      add_predicate_type( typing_rules->_1._1, typing_rules->_1._2);
      typing_rules = typing_rules->_2;
      
#line 159 "../../prop-src/logicgen.pcc"
    } else { goto L2; }
  }
  L2:;
}
#line 160 "../../prop-src/logicgen.pcc"
#line 160 "../../prop-src/logicgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to partition a set of constraint rules by functor name and type.
//
///////////////////////////////////////////////////////////////////////////////

void ConstraintCompiler::process_ruleset( Id id, ConstraintRules rules)
{
  ////////////////////////////////////////////////////////////////////////////
  //
  //   Perform type checking on each of the rule.
  //
  ////////////////////////////////////////////////////////////////////////////
  for_each (ConstraintRule, r, rules)
  {
    
#line 178 "../../prop-src/logicgen.pcc"
#line 212 "../../prop-src/logicgen.pcc"
{
#line 181 "../../prop-src/logicgen.pcc"
  
  r->set_loc();
  
  // Lookup entry
  
  HashTable::Entry * e = internal->rule_map.lookup(r->id);
  
  // Infer the type of pattern.
  
  r->ty = mkfunty( type_of(r->pat), mktypety());
  add_predicate_type( r->id, r->ty);
  
  // Insert into the type
  
  if (e) // append rule
  {
    ConstraintRules old_rules = ConstraintRules(e->v);
    
#line 198 "../../prop-src/logicgen.pcc"
#line 207 "../../prop-src/logicgen.pcc"
  {
    if (old_rules) {
#line 200 "../../prop-src/logicgen.pcc"
      
      if (! unify( r->ty, old_rules->_1->ty))
        error( "%Ltype mismatch in rule %s%p\n"
               "%Lexpecting %T but found %T\n",
               r->id, r->pat, old_rules->_1->ty, r->ty);
      
#line 205 "../../prop-src/logicgen.pcc"
    } else {}
  }
#line 207 "../../prop-src/logicgen.pcc"
#line 207 "../../prop-src/logicgen.pcc"
  
  internal->rule_map.insert( r->id, 
#line 208 "../../prop-src/logicgen.pcc"
#line 208 "../../prop-src/logicgen.pcc"
  list_1_(r,old_rules)
#line 208 "../../prop-src/logicgen.pcc"
#line 208 "../../prop-src/logicgen.pcc"
  );
  }
  else // insert new rule
    internal->rule_map.insert( r->id, 
#line 211 "../../prop-src/logicgen.pcc"
#line 211 "../../prop-src/logicgen.pcc"
  list_1_(r)
#line 211 "../../prop-src/logicgen.pcc"
#line 211 "../../prop-src/logicgen.pcc"
  );
  
#line 212 "../../prop-src/logicgen.pcc"
}
#line 213 "../../prop-src/logicgen.pcc"
#line 213 "../../prop-src/logicgen.pcc"

  }

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Makes sure all the rules have all the type information annotated.
  //
  ////////////////////////////////////////////////////////////////////////////
  for_each (ConstraintRule, R, rules)
  {
    
#line 223 "../../prop-src/logicgen.pcc"
#line 233 "../../prop-src/logicgen.pcc"
{
#line 226 "../../prop-src/logicgen.pcc"
  
  R->set_loc();
  // Check to make sure it has all the type information.
  if ( !is_ground(R->ty))
    error( "%Lmissing type info in rule: %s%p : %T\n", R->id, R->pat, R->ty);
  R->pat = unifier_of(R->pat);
  debug_msg( "%s %p :- ...\n", R->id, R->pat);
  
#line 233 "../../prop-src/logicgen.pcc"
}
#line 234 "../../prop-src/logicgen.pcc"
#line 234 "../../prop-src/logicgen.pcc"

  }
}
#line 237 "../../prop-src/logicgen.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 4
Number of ifs generated      = 3
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
