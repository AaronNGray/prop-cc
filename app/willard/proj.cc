///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "proj.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "proj.pcc"
#include <AD/pretty/postream.h>
#include "proj.h"
#include "list.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for projection recognition 
//
///////////////////////////////////////////////////////////////////////////////
Projection::Projection() {}
Projection::~Projection() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to invoke projection recognition 
//
///////////////////////////////////////////////////////////////////////////////
Exp Projection::projection_recognition(Exp e) 
{ message("Projection recognition phase", e); (*this)(e); return e;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create a projection 
//
///////////////////////////////////////////////////////////////////////////////
Exp Projection::make_projection
   (const IdSet& Invisible, Ids xs, Exps As, Exp P, Exp exp)
{  Ids  visible_xs = 
#line 29 "proj.pcc"
#line 29 "proj.pcc"
nil_1_
#line 29 "proj.pcc"
#line 29 "proj.pcc"
;
   Exps visible_As = 
#line 30 "proj.pcc"
#line 30 "proj.pcc"
nil_1_
#line 30 "proj.pcc"
#line 30 "proj.pcc"
;
   
#line 31 "proj.pcc"
#line 40 "proj.pcc"
{
   for (;;) {
      if (xs) {
         if (As) {
#line 33 "proj.pcc"
          if (Invisible.contains(xs->_1))
            	 {  P = EXISTS(xs->_1,As->_1,P); }
                     else
            	 {  visible_xs = 
#line 36 "proj.pcc"
#line 36 "proj.pcc"
            list_1_(xs->_1,visible_xs)
#line 36 "proj.pcc"
#line 36 "proj.pcc"
            ;
            	    visible_As = 
#line 37 "proj.pcc"
#line 37 "proj.pcc"
            list_1_(As->_1,visible_As)
#line 37 "proj.pcc"
#line 37 "proj.pcc"
            ;
            }
            	 xs = xs->_2; As = As->_2;
            
#line 40 "proj.pcc"
         } else { goto L1; }
      } else { goto L1; }
   }
   L1:;
}
#line 41 "proj.pcc"
#line 41 "proj.pcc"

   changed = true;
   Exp body = P == True ? exp : GUARD(P,exp);
   return GENERATOR(rev(visible_xs),rev(visible_As),body);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Transformation to recongize projections and transform them into
//  existential queries.  Assume the set comprehensions are in flatten form.
//
///////////////////////////////////////////////////////////////////////////////
#line 53 "proj.pcc"
#line 75 "proj.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_Projection
#define DEBUG_Projection(repl,redex,file,line,rule) repl
#else
static const char * Projection_file_name = "proj.pcc";
#endif

static const TreeTables::Offset Projection_accept_base [ 4 ] = {
   0, 0, 1, 3
};
static const TreeTables::ShortRule Projection_accept_vector [ 6 ] = {
   -1, 1, -1, 0, 1, -1
};
static const TreeTables::ShortState Projection_theta_8[1][1][2] = {
   { { 2, 3 } }
};


static const TreeTables::ShortState Projection_mu_8_2[4] = {
   0, 1, 0, 0
};


inline void  Projection::labeler(char const * redex,int& s__,int)
{
   {
s__ = 0;
   }
}

inline void  Projection::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Projection::labeler (Exp & redex, int& s__, int r__)
{
replacement__:
   int cached__;
   if (r__ && boxed(redex) && (cached__ = redex->get_rewrite_state()) != BURS::undefined_state)
   { s__ = cached__; return; }
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
         s__ = 1;} break;
      case a_Exp::tag_GENERATOR: { 
         int s0__;
         int s1__;
         int s2__;
         s0__ = 0; // Ids
         labeler(_GENERATOR(redex)->_2, s1__, r__);
         labeler(_GENERATOR(redex)->_3, s2__, r__);
         s__ = Projection_theta_8[0][0][Projection_mu_8_2[s2__]]; } break;
      default: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_LET(redex)->_1, s0__, r__);
         labeler(_LET(redex)->_2, s1__, r__);
         labeler(_LET(redex)->_3, s2__, r__);
         s__ = 0;} break;
   }
   const TreeTables::ShortRule * o__ = Projection_accept_vector + Projection_accept_base[s__];
accept__:
   switch (*o__) {
      case 1: if ((length(_GENERATOR(redex)->_1) == length(_GENERATOR(redex)->_2)))
      {
#line 69 "proj.pcc"
       IdSet S1;
         IdSet S2;
         free_vars(_GENERATOR(redex)->_1,S1);
         free_vars(_GENERATOR(redex)->_3,S2);
         remove_vars(S1,S2);
         if (S1.size() > 0) 
#line 74 "proj.pcc"
#line 74 "proj.pcc"
         { redex = DEBUG_Projection(make_projection(S1,_GENERATOR(redex)->_1,_GENERATOR(redex)->_2,True,_GENERATOR(redex)->_3),redex,Projection_file_name,68,"GENERATOR (xs, As, e) | (length(redex!GENERATOR.1) == length(redex!GENERATOR.2)): ...");
           r__ = 1; goto replacement__; }
#line 74 "proj.pcc"
#line 74 "proj.pcc"
         
         
#line 75 "proj.pcc"
}
      else { ++o__; goto accept__; } break;
      case 0: if ((length(_GENERATOR(redex)->_1) == length(_GENERATOR(redex)->_2)))
      {
#line 61 "proj.pcc"
       IdSet S1;
         IdSet S2;
         free_vars(_GENERATOR(redex)->_1,S1);
         free_vars(_GUARD(_GENERATOR(redex)->_3)->_2,S2);
         remove_vars(S1,S2);
         if (S1.size() > 0) 
#line 66 "proj.pcc"
#line 66 "proj.pcc"
         { redex = DEBUG_Projection(make_projection(S1,_GENERATOR(redex)->_1,_GENERATOR(redex)->_2,_GUARD(_GENERATOR(redex)->_3)->_1,_GUARD(_GENERATOR(redex)->_3)->_2),redex,Projection_file_name,60,"GENERATOR (xs, As, GUARD (p, e)) | (length(redex!GENERATOR.1) == length(redex!GENERATOR.2)): ...");
           r__ = 1; goto replacement__; }
#line 66 "proj.pcc"
#line 66 "proj.pcc"
         
         
#line 67 "proj.pcc"
}
      else { ++o__; goto accept__; } break;
   }
   if (boxed(redex)) {
      redex->set_rewrite_state(s__);
   }
   
}

void  Projection::labeler (Literal & redex, int& s__, int r__)
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

void  Projection::labeler (a_List<Exp> *  & redex, int& s__, int r__)
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

#line 76 "proj.pcc"
#line 76 "proj.pcc"

#line 77 "proj.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 3
Number of ifs generated      = 2
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
