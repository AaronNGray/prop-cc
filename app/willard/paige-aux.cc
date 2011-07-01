///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "paige-aux.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "paige-aux.pcc"
#include "paige.h"
#include "willard-ast.h"
#include <AD/strings/quark.h>

//
//  Auxiliary routines to generate new variable names
//
Id PaigeGoyal::gensym() { return gensym("Q"); }
Id PaigeGoyal::gensym(Id prefix) 
   { return Quark(Quark(prefix,"_"),++new_name); }

//
//  Auxiliary routines to check whether a variable is free in an expression
//
Bool PaigeGoyal::is_free(Id x, Exp e) const
{  IdSet S;
   free_vars(e,S);
   return ! S.contains(x);
}

Bool PaigeGoyal::is_free(Ids xs, Exp e) const
{  IdSet S;
   free_vars(e,S);
   
#line 24 "paige-aux.pcc"
#line 24 "paige-aux.pcc"
{
   for (;;) {
      if (xs) {
#line 24 "paige-aux.pcc"
        if (S.contains(xs->_1)) return false; xs = xs->_2; 
#line 24 "paige-aux.pcc"
      } else { goto L1; }
   }
   L1:;
}
#line 25 "paige-aux.pcc"
#line 25 "paige-aux.pcc"

   return true;
}

void PaigeGoyal::remove_vars(IdSet& S, Ids ids) const
{
   
#line 31 "paige-aux.pcc"
#line 31 "paige-aux.pcc"
{
   for (;;) {
      if (ids) {
#line 31 "paige-aux.pcc"
        S.remove(ids->_1); ids = ids->_2; 
#line 31 "paige-aux.pcc"
      } else { goto L2; }
   }
   L2:;
}
#line 31 "paige-aux.pcc"
#line 31 "paige-aux.pcc"

}

void PaigeGoyal::remove_vars(IdSet& S, const IdSet& T) const
{  foreach(i,T) S.remove(T.key(i));
}

//
//  Methods to collect free variables in a term
//
void PaigeGoyal::free_vars(Exp e, IdSet& S) const
{  
#line 42 "paige-aux.pcc"
#line 52 "paige-aux.pcc"
{
   switch (e->tag__) {
      case a_Exp::tag_OP: {
#line 43 "paige-aux.pcc"
        free_vars(_OP(e)->_2,S); 
#line 43 "paige-aux.pcc"
         } break;
      case a_Exp::tag_APP: {
#line 44 "paige-aux.pcc"
        free_vars(_APP(e)->_2,S); 
#line 44 "paige-aux.pcc"
         } break;
      case a_Exp::tag_LIT: {
#line 45 "paige-aux.pcc"
        return; 
#line 45 "paige-aux.pcc"
         } break;
      case a_Exp::tag_ID: {
#line 46 "paige-aux.pcc"
        S.insert(_ID(e)->ID); 
#line 46 "paige-aux.pcc"
         } break;
      case a_Exp::tag_TUPLE: {
#line 47 "paige-aux.pcc"
        free_vars(_TUPLE(e)->TUPLE,S); 
#line 47 "paige-aux.pcc"
         } break;
      case a_Exp::tag_FORALL: {
#line 48 "paige-aux.pcc"
        free_vars(_FORALL(e)->_2,S); free_vars(_FORALL(e)->_3,S); S.remove(_FORALL(e)->_1); 
#line 48 "paige-aux.pcc"
         } break;
      case a_Exp::tag_EXISTS: {
#line 49 "paige-aux.pcc"
        free_vars(_EXISTS(e)->_2,S); free_vars(_EXISTS(e)->_3,S); S.remove(_EXISTS(e)->_1); 
#line 49 "paige-aux.pcc"
         } break;
      case a_Exp::tag_GUARD: {
#line 51 "paige-aux.pcc"
        free_vars(_GUARD(e)->_1,S); free_vars(_GUARD(e)->_2,S); 
#line 51 "paige-aux.pcc"
         } break;
      case a_Exp::tag_GENERATOR: {
#line 52 "paige-aux.pcc"
        free_vars(_GENERATOR(e)->_2,S); free_vars(_GENERATOR(e)->_3,S); remove_vars(S,_GENERATOR(e)->_1); 
#line 52 "paige-aux.pcc"
         } break;
      default: {
#line 50 "paige-aux.pcc"
        free_vars(_LET(e)->_2,S); free_vars(_LET(e)->_3,S); S.remove(_LET(e)->_1); 
#line 50 "paige-aux.pcc"
         } break;
   }
}
#line 54 "paige-aux.pcc"
#line 54 "paige-aux.pcc"

}

void PaigeGoyal::free_vars(Exps es, IdSet& S) const
{  
#line 58 "paige-aux.pcc"
#line 59 "paige-aux.pcc"
{
   for (;;) {
      if (es) {
#line 59 "paige-aux.pcc"
        free_vars(es->_1,S); es = es->_2; 
#line 59 "paige-aux.pcc"
      } else { goto L3; }
   }
   L3:;
}
#line 59 "paige-aux.pcc"
#line 59 "paige-aux.pcc"

}

void PaigeGoyal::free_vars(Ids xs, IdSet& S) const
{  
#line 63 "paige-aux.pcc"
#line 64 "paige-aux.pcc"
{
   for (;;) {
      if (xs) {
#line 64 "paige-aux.pcc"
        S.insert(xs->_1); xs = xs->_2; 
#line 64 "paige-aux.pcc"
      } else { goto L4; }
   }
   L4:;
}
#line 64 "paige-aux.pcc"
#line 64 "paige-aux.pcc"

}
#line 66 "paige-aux.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 4
Number of ifs generated      = 4
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
