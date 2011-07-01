///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase3.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase3.pcc"
#include <AD/pretty/postream.h>
#include "phase3.h"
#include "list.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructors and destructors for phase3 
//
///////////////////////////////////////////////////////////////////////////////
Phase3::Phase3() {}
Phase3::~Phase3() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to invoke phase3 
//
///////////////////////////////////////////////////////////////////////////////
Exp Phase3::phase3(Exp e) 
{  message("Disjunction removal phase", e); (*this)(e); return e; }

///////////////////////////////////////////////////////////////////////////////
//
//  Transformations to change disjunctions into unions
//
///////////////////////////////////////////////////////////////////////////////
#line 26 "phase3.pcc"
#line 58 "phase3.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_Phase3
#define DEBUG_Phase3(repl,redex,file,line,rule) repl
#else
static const char * Phase3_file_name = "phase3.pcc";
#endif

static const TreeTables::ShortState Phase3_theta_0[2][2] = {
   { 0, 0 },
   { 4, 10 }
};


static const TreeTables::ShortState Phase3_theta_7[2][1] = {
   { 0 },
   { 6 }
};


static const TreeTables::ShortState Phase3_theta_8[1][1][2] = {
   { { 0, 8 } }
};


static const TreeTables::ShortState Phase3_theta_9[1][2][1] = {
   { { 3 },
   { 5 } }
};


static const TreeTables::ShortState Phase3_theta_11[2][3] = {
   { 0, 0, 9 },
   { 0, 7, 9 }
};


static const TreeTables::ShortState Phase3_mu_0_0[11] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState Phase3_mu_0_1[11] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
};


static const TreeTables::ShortState Phase3_mu_7_0[11] = {
   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
};


static const TreeTables::ShortState Phase3_mu_8_2[11] = {
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
};


static const TreeTables::ShortState Phase3_mu_9_1[11] = {
   0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState Phase3_mu_11_0[11] = {
   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
};


static const TreeTables::ShortState Phase3_mu_11_1[11] = {
   0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0
};


inline void  Phase3::labeler(char const * redex,int& s__,int)
{
   {
      if (_equal_string(redex,"or")) {s__ = 2;}
      else {s__ = 0;}
   }
}

inline void  Phase3::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Phase3::labeler (Exp & redex, int& s__, int r__)
{
replacement__:
   {
      switch (redex->tag__) {
         case a_Exp::tag_GENERATOR: {
            switch (_GENERATOR(redex)->_3->tag__) {
               case a_Exp::tag_GENERATOR: {
#line 31 "phase3.pcc"
                  { redex = DEBUG_Phase3(GENERATOR(append(_GENERATOR(redex)->_1,_GENERATOR(_GENERATOR(redex)->_3)->_1),append(_GENERATOR(redex)->_2,_GENERATOR(_GENERATOR(redex)->_3)->_2),_GENERATOR(_GENERATOR(redex)->_3)->_3),redex,Phase3_file_name,31,"GENERATOR (x, A, GENERATOR (y, B, C)): ...");
                    r__ = 1; goto replacement__; }
#line 33 "phase3.pcc"
                  } break;
               default: {} break;
            }
            } break;
         default: {} break;
      }
   }
   int cached__;
   if (r__ && boxed(redex) && (cached__ = redex->get_rewrite_state()) != BURS::undefined_state)
   { s__ = cached__; return; }
   switch(redex->tag__) {
      case a_Exp::tag_OP: { 
         int s0__;
         int s1__;
         labeler(_OP(redex)->_1, s0__, r__);
         labeler(_OP(redex)->_2, s1__, r__);
         s__ = Phase3_theta_0[Phase3_mu_0_0[s0__]][Phase3_mu_0_1[s1__]]; } break;
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
         s__ = Phase3_theta_7[Phase3_mu_7_0[s0__]][0]; } break;
      case a_Exp::tag_GENERATOR: { 
         int s0__;
         int s1__;
         int s2__;
         s0__ = 0; // Ids
         labeler(_GENERATOR(redex)->_2, s1__, r__);
         labeler(_GENERATOR(redex)->_3, s2__, r__);
         s__ = Phase3_theta_8[0][0][Phase3_mu_8_2[s2__]]; } break;
      default: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_LET(redex)->_1, s0__, r__);
         labeler(_LET(redex)->_2, s1__, r__);
         labeler(_LET(redex)->_3, s2__, r__);
         s__ = Phase3_theta_9[0][Phase3_mu_9_1[s1__]][0]; } break;
   }
   switch (s__) {
      case 5: {
#line 57 "phase3.pcc"
         { redex = DEBUG_Phase3(LET(_LET(_LET(redex)->_2)->_1,_LET(_LET(redex)->_2)->_2,LET(_LET(redex)->_1,_LET(_LET(redex)->_2)->_3,_LET(redex)->_3)),redex,Phase3_file_name,57,"LET (x, LET (y, b, a), e): ...");
           r__ = 1; goto replacement__; }
#line 58 "phase3.pcc"
} break;
      case 8: {
#line 40 "phase3.pcc"
       Ids  xs   = 
#line 40 "phase3.pcc"
#line 40 "phase3.pcc"
         nil_1_
#line 40 "phase3.pcc"
#line 40 "phase3.pcc"
         ;
         Exps Qs   = 
#line 41 "phase3.pcc"
#line 41 "phase3.pcc"
         nil_1_
#line 41 "phase3.pcc"
#line 41 "phase3.pcc"
         ;
         Exps exps = 
#line 42 "phase3.pcc"
#line 42 "phase3.pcc"
         nil_1_
#line 42 "phase3.pcc"
#line 42 "phase3.pcc"
         ;
         Exps disjuncts = _OP(_GUARD(_GENERATOR(redex)->_3)->_1)->_2;
         
#line 44 "phase3.pcc"
#line 51 "phase3.pcc"
         {
            for (;;) {
               if (disjuncts) {
#line 46 "phase3.pcc"
                Id Q = gensym();
                  	    xs   = 
#line 47 "phase3.pcc"
#line 47 "phase3.pcc"
                  list_1_(Q,xs)
#line 47 "phase3.pcc"
#line 47 "phase3.pcc"
                  ;
                  	    Qs   = 
#line 48 "phase3.pcc"
#line 48 "phase3.pcc"
                  list_1_(GENERATOR(_GENERATOR(redex)->_1,_GENERATOR(redex)->_2,GUARD(disjuncts->_1,_GUARD(_GENERATOR(redex)->_3)->_2)),Qs)
#line 48 "phase3.pcc"
#line 48 "phase3.pcc"
                  ;
                  exps = 
#line 49 "phase3.pcc"
#line 49 "phase3.pcc"
                  list_1_(ID(Q),exps)
#line 49 "phase3.pcc"
#line 49 "phase3.pcc"
                  ;
                  disjuncts = disjuncts->_2;
                  
#line 51 "phase3.pcc"
               } else { goto L1; }
            }
            L1:;
         }
#line 52 "phase3.pcc"
#line 52 "phase3.pcc"
         
         
#line 53 "phase3.pcc"
#line 53 "phase3.pcc"
         { redex = DEBUG_Phase3(make_let(xs,Qs,OP("union",exps)),redex,Phase3_file_name,39,"GENERATOR (x, A, GUARD (OP (\"or\", es), e)): ...");
           r__ = 1; goto replacement__; }
#line 53 "phase3.pcc"
#line 53 "phase3.pcc"
         
         
#line 54 "phase3.pcc"
} break;
      case 10: {
#line 36 "phase3.pcc"
         { redex = DEBUG_Phase3(OP("or",list_1_(_OP(redex)->_2->_1,_OP(_OP(redex)->_2->_2->_1)->_2)),redex,Phase3_file_name,36,"OP (\"or\", #[a, OP (\"or\", b)]): ...");
           r__ = 1; goto replacement__; }
#line 39 "phase3.pcc"
} break;
   }
   if (boxed(redex)) {
      redex->set_rewrite_state(s__);
   }
   
}

void  Phase3::labeler (Literal & redex, int& s__, int r__)
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

void  Phase3::labeler (a_List<Exp> *  & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = Phase3_theta_11[Phase3_mu_11_0[s0__]][Phase3_mu_11_1[s1__]]; 
   } else {s__ = 1;
   }
   
}

#line 58 "phase3.pcc"
#line 58 "phase3.pcc"

#line 59 "phase3.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 20
Number of ifs generated      = 2
Number of switches generated = 2
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
