///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\constraint.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/constraint.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the auxiliary methods of the constraint compiler,
//  which include various pretty printing and AST transformation routines.
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


///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the constraint datatypes
//
///////////////////////////////////////////////////////////////////////////////

#line 25 "../../prop-src/constraint.pcc"
#line 25 "../../prop-src/constraint.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype ConstraintSet
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype ConstraintDef
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype ConstraintRule
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<ConstraintDef>
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype ConstraintBody
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype ConstraintSet
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype ConstraintDef
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype ConstraintRule
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<ConstraintDef>
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<ConstraintDef>;
template a_List<ConstraintDef> * list_1_(ConstraintDef x_1, a_List<ConstraintDef> *  x_2);
template a_List<ConstraintDef> * list_1_(ConstraintDef x_list_1_);
template int boxed(const a_List<ConstraintDef> *);
template int untag(const a_List<ConstraintDef> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype ConstraintBody
//
///////////////////////////////////////////////////////////////////////////////
#line 25 "../../prop-src/constraint.pcc"


#line 30 "../../prop-src/constraint.pcc"
#line 30 "../../prop-src/constraint.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing routines.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a rule set.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << ( std::ostream& f, ConstraintSet ruleset)
{
  
#line 46 "../../prop-src/constraint.pcc"
#line 47 "../../prop-src/constraint.pcc"
{
#line 47 "../../prop-src/constraint.pcc"
 return f << ruleset->CONSTRAINTset; 
#line 47 "../../prop-src/constraint.pcc"
}
#line 48 "../../prop-src/constraint.pcc"
#line 48 "../../prop-src/constraint.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a list of constraint definition.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << ( std::ostream& f, ConstraintDefs defs)
{
  
#line 59 "../../prop-src/constraint.pcc"
#line 60 "../../prop-src/constraint.pcc"
{
  for (;;) {
    if (defs) {
#line 60 "../../prop-src/constraint.pcc"
     f << defs->_1; defs = defs->_2; 
#line 60 "../../prop-src/constraint.pcc"
    } else { goto L1; }
  }
  L1:;
}
#line 61 "../../prop-src/constraint.pcc"
#line 61 "../../prop-src/constraint.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a definition.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << ( std::ostream& f, ConstraintDef def)
{
  
#line 73 "../../prop-src/constraint.pcc"
#line 78 "../../prop-src/constraint.pcc"
{
  switch (def->tag__) {
    case a_ConstraintDef::tag_CONSTRAINTruledef: {
#line 74 "../../prop-src/constraint.pcc"
     return f << _CONSTRAINTruledef(def)->CONSTRAINTruledef << '\n'; 
#line 74 "../../prop-src/constraint.pcc"
      } break;
    case a_ConstraintDef::tag_CONSTRAINTtype: {
#line 75 "../../prop-src/constraint.pcc"
     return f << _CONSTRAINTtype(def)->_1 << " : " << _CONSTRAINTtype(def)->_2 << ";\n"; 
#line 75 "../../prop-src/constraint.pcc"
      } break;
    case a_ConstraintDef::tag_CONSTRAINTinstness: {
#line 76 "../../prop-src/constraint.pcc"
     return f << _CONSTRAINTinstness(def)->_1 << " = " << _CONSTRAINTinstness(def)->_2 << ";\n"; 
#line 76 "../../prop-src/constraint.pcc"
      } break;
    default: {
#line 78 "../../prop-src/constraint.pcc"
     return f << _CONSTRAINTdet(def)->_1 << " :: " << _CONSTRAINTdet(def)->_2 << " is " << _CONSTRAINTdet(def)->_3 << ";\n"; 
#line 78 "../../prop-src/constraint.pcc"
      } break;
  }
}
#line 79 "../../prop-src/constraint.pcc"
#line 79 "../../prop-src/constraint.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print a constraint rule.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << ( std::ostream& f, ConstraintRule rule)
{
  
#line 90 "../../prop-src/constraint.pcc"
#line 94 "../../prop-src/constraint.pcc"
{
  if (boxed(rule->body)) {
    L2:; 
#line 94 "../../prop-src/constraint.pcc"
  return f << rule->id << ' ' << rule->pat << " :- " << rule->body << ';'; 
#line 94 "../../prop-src/constraint.pcc"
  } else {
    if (rule->body) {
       goto L2; } else {
      
#line 92 "../../prop-src/constraint.pcc"
    return f << rule->id << ' ' << rule->pat << ';'; 
#line 92 "../../prop-src/constraint.pcc"
    }
  }
}
#line 95 "../../prop-src/constraint.pcc"
#line 95 "../../prop-src/constraint.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print the body of a constraint.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << ( std::ostream& f, ConstraintBody b)
{
  
#line 106 "../../prop-src/constraint.pcc"
#line 113 "../../prop-src/constraint.pcc"
{
  if (boxed(b)) {
    switch (b->tag__) {
      case a_ConstraintBody::tag_CONSTRAINTand: {
#line 109 "../../prop-src/constraint.pcc"
       f << _CONSTRAINTand(b)->_1 << ", " << _CONSTRAINTand(b)->_2; 
#line 109 "../../prop-src/constraint.pcc"
        } break;
      case a_ConstraintBody::tag_CONSTRAINTif: {
#line 110 "../../prop-src/constraint.pcc"
       f << "if " << _CONSTRAINTif(b)->_1 << " then " << _CONSTRAINTif(b)->_2
        << " else " << _CONSTRAINTif(b)->_3 << " end if"; 
#line 111 "../../prop-src/constraint.pcc"
        } break;
      case a_ConstraintBody::tag_CONSTRAINTbody: {
#line 112 "../../prop-src/constraint.pcc"
       f << "{ ... }"; 
#line 112 "../../prop-src/constraint.pcc"
        } break;
      default: {
#line 113 "../../prop-src/constraint.pcc"
       f << _CONSTRAINTcall(b)->CONSTRAINTcall; 
#line 113 "../../prop-src/constraint.pcc"
        } break;
    }
  } else {
    if (b) {
      
#line 108 "../../prop-src/constraint.pcc"
     f << "!"; 
#line 108 "../../prop-src/constraint.pcc"
    } else {
      }
  }
}
#line 114 "../../prop-src/constraint.pcc"
#line 114 "../../prop-src/constraint.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Hash function for id/type pair
//
///////////////////////////////////////////////////////////////////////////////

unsigned int id_ty_hash( HashTable::Key k)
{
  
#line 126 "../../prop-src/constraint.pcc"
a_Pair<Id, Ty> *  
#line 126 "../../prop-src/constraint.pcc"
 key = (a_Pair<Id, Ty> *  
#line 126 "../../prop-src/constraint.pcc"
)(k);
  return string_hash(key->fst); // + ty_hash(key->snd);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Equality function for id/type pair
//
///////////////////////////////////////////////////////////////////////////////

Bool id_ty_equal( HashTable::Key a, HashTable::Key b)
{
  a_Pair<Id, Ty> *  
#line 138 "../../prop-src/constraint.pcc"
 x = (a_Pair<Id, Ty> *  
#line 138 "../../prop-src/constraint.pcc"
)(a);
  a_Pair<Id, Ty> *  
#line 139 "../../prop-src/constraint.pcc"
 y = (a_Pair<Id, Ty> *  
#line 139 "../../prop-src/constraint.pcc"
)(b);
  return string_equal(x->fst,y->fst); // && ty_equal(x->snd,y->snd);
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor of the constraint compiler
//
///////////////////////////////////////////////////////////////////////////////

ConstraintCompiler:: ConstraintCompiler() : internal(0) {}
ConstraintCompiler::~ConstraintCompiler() {}
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 7
Number of ifs generated      = 5
Number of switches generated = 2
Number of labels             = 1
Number of gotos              = 1
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
