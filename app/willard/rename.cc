///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "rename.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "rename.pcc"
#include <AD/pretty/postream.h>
#include "rename.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for the renaming phase
//
///////////////////////////////////////////////////////////////////////////////
RemoveDuplicateNames::RemoveDuplicateNames() {}
RemoveDuplicateNames::~RemoveDuplicateNames() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create a new variable binding.  We'll only create a
//  new name if the current binding overshadows some previous name.
//
///////////////////////////////////////////////////////////////////////////////
void RemoveDuplicateNames::new_binding(Id& x) 
{  if (env.contains(x))
   {  Id y = gensym(x);
      env.insert(x,
#line 21 "rename.pcc"
#line 21 "rename.pcc"
list_1_(y,env[x])
#line 21 "rename.pcc"
#line 21 "rename.pcc"
); 
   } else
   {  env.insert(x,
#line 23 "rename.pcc"
#line 23 "rename.pcc"
list_1_(x)
#line 23 "rename.pcc"
#line 23 "rename.pcc"
); }
}

void RemoveDuplicateNames::new_binding(Ids ids)
{  
#line 27 "rename.pcc"
#line 28 "rename.pcc"
{
   for (;;) {
      if (ids) {
#line 28 "rename.pcc"
        new_binding(ids->_1); ids = ids->_2; 
#line 28 "rename.pcc"
      } else { goto L1; }
   }
   L1:;
}
#line 29 "rename.pcc"
#line 29 "rename.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to remove a variable binding.
//
///////////////////////////////////////////////////////////////////////////////
void RemoveDuplicateNames::old_binding(Id& x) 
{  Ids names = env[x];
   
#line 39 "rename.pcc"
#line 43 "rename.pcc"
{
   if (names) {
      if (names->_2) {
#line 41 "rename.pcc"
        env.insert(x,names->_2); x = names->_1; 
#line 41 "rename.pcc"
      } else {
#line 40 "rename.pcc"
        env.remove(x); x = names->_1; 
#line 40 "rename.pcc"
      }
   } else {}
}
#line 43 "rename.pcc"
#line 43 "rename.pcc"

}

void RemoveDuplicateNames::old_binding(Ids ids)
{  
#line 47 "rename.pcc"
#line 48 "rename.pcc"
{
   for (;;) {
      if (ids) {
#line 48 "rename.pcc"
        old_binding(ids->_1); ids = ids->_2; 
#line 48 "rename.pcc"
      } else { goto L2; }
   }
   L2:;
}
#line 49 "rename.pcc"
#line 49 "rename.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to rename a variable 
//
///////////////////////////////////////////////////////////////////////////////
void RemoveDuplicateNames::rename(Id& x) 
{  if (env.contains(x))
   {  Ids names = env[x];
      
#line 60 "rename.pcc"
#line 63 "rename.pcc"
{
   if (names) {
#line 61 "rename.pcc"
     x = names->_1; 
#line 61 "rename.pcc"
   } else {}
}
#line 63 "rename.pcc"
#line 63 "rename.pcc"

   }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to invoke the renaming phase.
//
///////////////////////////////////////////////////////////////////////////////
Exp RemoveDuplicateNames::remove_duplicate_names(Exp e) 
{  message("Renaming phase", e); env.clear(); (*this)(e); return e; }

///////////////////////////////////////////////////////////////////////////////
//
//  Transformation rules
//
///////////////////////////////////////////////////////////////////////////////
#line 80 "rename.pcc"
#line 100 "rename.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_RemoveDuplicateNames
#define DEBUG_RemoveDuplicateNames(repl,redex,file,line,rule) repl
#else
static const char * RemoveDuplicateNames_file_name = "rename.pcc";
#endif

inline void  RemoveDuplicateNames::labeler(char const * redex,int& s__,int)
{
   {
s__ = 0;
   }
}

inline void  RemoveDuplicateNames::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  RemoveDuplicateNames::labeler (Exp & redex, int& s__, int r__)
{
replacement__:
   {
      switch (redex->tag__) {
         case a_Exp::tag_ID: {
#line 94 "rename.pcc"
           rename(_ID(redex)->ID); 
#line 94 "rename.pcc"
            } break;
         case a_Exp::tag_FORALL: {
#line 89 "rename.pcc"
           new_binding(_FORALL(redex)->_1); 
#line 89 "rename.pcc"
            } break;
         case a_Exp::tag_EXISTS: {
#line 88 "rename.pcc"
           new_binding(_EXISTS(redex)->_1); 
#line 88 "rename.pcc"
            } break;
         case a_Exp::tag_GENERATOR: {
#line 90 "rename.pcc"
           new_binding(_GENERATOR(redex)->_1); 
#line 90 "rename.pcc"
            } break;
         case a_Exp::tag_LET: {
#line 91 "rename.pcc"
           new_binding(_LET(redex)->_1); 
#line 91 "rename.pcc"
            } break;
         default: {} break;
      }
   }
   switch(redex->tag__) {
      case a_Exp::tag_OP: { 
         int s0__;
         int s1__;
         labeler(_OP(redex)->_1, s0__, r__);
         labeler(_OP(redex)->_2, s1__, r__);
         s__ = 0;} break;
      case a_Exp::tag_APP: { 
         int s0__;
         int s1__;
         labeler(_APP(redex)->_1, s0__, r__);
         labeler(_APP(redex)->_2, s1__, r__);
         s__ = 0;} break;
      case a_Exp::tag_LIT: { 
         int s0__;
         labeler(_LIT(redex)->LIT, s0__, r__);
         s__ = 0;} break;
      case a_Exp::tag_ID: { 
         int s0__;
         labeler(_ID(redex)->ID, s0__, r__);
         s__ = 0;} break;
      case a_Exp::tag_TUPLE: { 
         int s0__;
         labeler(_TUPLE(redex)->TUPLE, s0__, r__);
         s__ = 0;} break;
      case a_Exp::tag_FORALL: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_FORALL(redex)->_1, s0__, r__);
         labeler(_FORALL(redex)->_2, s1__, r__);
         labeler(_FORALL(redex)->_3, s2__, r__);
         s__ = 0;} break;
      case a_Exp::tag_EXISTS: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_EXISTS(redex)->_1, s0__, r__);
         labeler(_EXISTS(redex)->_2, s1__, r__);
         labeler(_EXISTS(redex)->_3, s2__, r__);
         s__ = 0;} break;
      case a_Exp::tag_GUARD: { 
         int s0__;
         int s1__;
         labeler(_GUARD(redex)->_1, s0__, r__);
         labeler(_GUARD(redex)->_2, s1__, r__);
         s__ = 0;} break;
      case a_Exp::tag_GENERATOR: { 
         int s0__;
         int s1__;
         int s2__;
         s0__ = 0; // Ids
         labeler(_GENERATOR(redex)->_2, s1__, r__);
         labeler(_GENERATOR(redex)->_3, s2__, r__);
         s__ = 0;} break;
      default: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_LET(redex)->_1, s0__, r__);
         labeler(_LET(redex)->_2, s1__, r__);
         labeler(_LET(redex)->_3, s2__, r__);
         s__ = 0;} break;
   }
   {
      switch (redex->tag__) {
         case a_Exp::tag_FORALL: {
#line 98 "rename.pcc"
           old_binding(_FORALL(redex)->_1);  define_range(_FORALL(redex)->_1,_FORALL(redex)->_2); 
#line 98 "rename.pcc"
            } break;
         case a_Exp::tag_EXISTS: {
#line 97 "rename.pcc"
           old_binding(_EXISTS(redex)->_1);  define_range(_EXISTS(redex)->_1,_EXISTS(redex)->_2); 
#line 97 "rename.pcc"
            } break;
         case a_Exp::tag_GENERATOR: {
#line 99 "rename.pcc"
           old_binding(_GENERATOR(redex)->_1); define_range(_GENERATOR(redex)->_1,_GENERATOR(redex)->_2); 
#line 99 "rename.pcc"
            } break;
         case a_Exp::tag_LET: {
#line 100 "rename.pcc"
           old_binding(_LET(redex)->_1); 
#line 100 "rename.pcc"
            } break;
         default: {} break;
      }
   }
   
}

void  RemoveDuplicateNames::labeler (Literal & redex, int& s__, int r__)
{
replacement__:
   switch(redex->tag__) {
      case a_Literal::tag_INT: { 
         int s0__;
         s0__ = 0; // int
         s__ = 0;} break;
      case a_Literal::tag_STRING: { 
         int s0__;
         labeler(_STRING(redex)->STRING, s0__, r__);
         s__ = 0;} break;
      default: { 
         int s0__;
         s0__ = 0; // Bool
         s__ = 0;} break;
   }
   
}

void  RemoveDuplicateNames::labeler (a_List<Exp> *  & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = 0;
   } else {s__ = 0;
   }
   
}

#line 101 "rename.pcc"
#line 101 "rename.pcc"

#line 102 "rename.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 16
Number of ifs generated      = 5
Number of switches generated = 2
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
