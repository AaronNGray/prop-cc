///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase5.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase5.pcc"
#include <AD/pretty/postream.h>
#include "phase5.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for phase5 
//
///////////////////////////////////////////////////////////////////////////////
Phase5::Phase5() {}
Phase5::~Phase5() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to invoke phase5 
//
///////////////////////////////////////////////////////////////////////////////
Exp Phase5::phase5(Exp e) 
{ message("Simple find/count query decomposition phase", e);
  (*this)(e); return collect_subqueries(e); 
}

///////////////////////////////////////////////////////////////////////////////
//
//  Transformation to decompose conjunctions
//
///////////////////////////////////////////////////////////////////////////////
#line 27 "phase5.pcc"
#line 30 "phase5.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_Phase5
#define DEBUG_Phase5(repl,redex,file,line,rule) repl
#else
static const char * Phase5_file_name = "phase5.pcc";
#endif

inline void  Phase5::labeler(char const * redex,int& s__,int)
{
   {
s__ = 0;
   }
}

inline void  Phase5::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Phase5::labeler (Exp & redex, int& s__, int r__)
{
replacement__:
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
         s__ = 1;} break;
      default: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_LET(redex)->_1, s0__, r__);
         labeler(_LET(redex)->_2, s1__, r__);
         labeler(_LET(redex)->_3, s2__, r__);
         s__ = 0;} break;
   }
   switch (s__) {
      case 1: {
#line 30 "phase5.pcc"
        
#line 30 "phase5.pcc"
} break;
   }
   
}

void  Phase5::labeler (Literal & redex, int& s__, int r__)
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

void  Phase5::labeler (a_List<Exp> *  & redex, int& s__, int r__)
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

#line 31 "phase5.pcc"
#line 31 "phase5.pcc"


#line 33 "phase5.pcc"
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
