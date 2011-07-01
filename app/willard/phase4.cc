///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase4.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase4.pcc"
#include <AD/pretty/postream.h>
#include "list.h"
#include "phase4.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for phase4 
//
///////////////////////////////////////////////////////////////////////////////
Phase4::Phase4() {}
Phase4::~Phase4() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to invoke phase4 
//
///////////////////////////////////////////////////////////////////////////////
Exp Phase4::phase4(Exp e) 
{ message("Conjunctive query decomposition phase", e);
  (*this)(e); 
  print_query_graph();
  return collect_subqueries(e); 
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to construct a projection query Q(x,y) given (x,y)
//
///////////////////////////////////////////////////////////////////////////////
Exp Phase4::make_projection(Id x, Id y, Ids xs, Exps As,
			    const IdSet& fv, Exp predicate)
{  Exp exp = predicate;
   
#line 33 "phase4.pcc"
#line 41 "phase4.pcc"
{
   for (;;) {
      if (xs) {
         if (As) {
#line 35 "phase4.pcc"
          // Make projections.
            	 // If a new existential quantifier is introduced, set
            	 // change to true so that we'll reiterate the process.
            	 if (! fv.contains(xs->_1)) 
            	 { exp = EXISTS(xs->_1,As->_1,exp); changed = true; }
            	 xs = xs->_2; As = As->_2;
                  
#line 41 "phase4.pcc"
         } else { goto L1; }
      } else { goto L1; }
   }
   L1:;
}
#line 42 "phase4.pcc"
#line 42 "phase4.pcc"

   exp = GENERATOR(
#line 43 "phase4.pcc"
#line 43 "phase4.pcc"
list_1_(x,list_1_(y))
#line 43 "phase4.pcc"
#line 43 "phase4.pcc"
,
#line 43 "phase4.pcc"
#line 43 "phase4.pcc"
list_1_(range_of(x),list_1_(range_of(y)))
#line 43 "phase4.pcc"
#line 43 "phase4.pcc"
,
	    GUARD(exp,TUPLE(
#line 44 "phase4.pcc"
#line 44 "phase4.pcc"
list_1_(ID(x),list_1_(ID(y)))
#line 44 "phase4.pcc"
#line 44 "phase4.pcc"
)));
   add_edge_query(x,y,exp);
   Id Q = gensym();
   add_subquery(Q,exp);
   return ID(Q);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to decompose a conjunctive query into projections and joins
//
///////////////////////////////////////////////////////////////////////////////
Exp Phase4::decompose_conjunct(Exp E, Ids xs, Exps As, Exp P)
{  
#line 57 "phase4.pcc"
#line 82 "phase4.pcc"
{
   switch (P->tag__) {
      case a_Exp::tag_OP: {
         if (_less_string(_OP(P)->_1,"=")) {
            if (_equal_string(_OP(P)->_1,"#")) {
            L2:; 
#line 64 "phase4.pcc"
          
            // Collect all free variables in this expression.
            IdSet S;
            free_vars(_OP(P)->_2,S);   
            
            // Now add edges to the query graph.
            foreach(i,S)
            {  Id x = S.value(i);
            	    foreach(j,S)
            	    {  Id y = S.value(j);
            	       if (has_edge(x,y)) 
            		  return make_projection(x,y,xs,As,S,P);
            	    }
            }
            	 Id Q = gensym();
            	 add_subquery(Q, GENERATOR(xs,As,GUARD(P,E)));
            	 return ID(Q);
            
#line 81 "phase4.pcc"
}
            else if (_equal_string(_OP(P)->_1,"/=")) { goto L2; }
            else if (_equal_string(_OP(P)->_1,"<")) { goto L2; }
            else if (_equal_string(_OP(P)->_1,"<=")) { goto L2; }
            else {
            L3:; 
#line 82 "phase4.pcc"
           error("Can't decompose conjunct", P); return P; 
#line 82 "phase4.pcc"
}
         } else {
            if (_equal_string(_OP(P)->_1,"=")) { goto L2; }
            else if (_equal_string(_OP(P)->_1,">")) { goto L2; }
            else if (_equal_string(_OP(P)->_1,">=")) { goto L2; }
            else if (_equal_string(_OP(P)->_1,"and")) {
            if (_OP(P)->_2) {
               if (_OP(P)->_2->_2) {
                  if (_OP(P)->_2->_2->_2) { goto L3; } else {
#line 59 "phase4.pcc"
                   Exp x = decompose_conjunct(E,xs,As,_OP(P)->_2->_1);
                     Exp y = decompose_conjunct(E,xs,As,_OP(P)->_2->_2->_1);
                     	 return OP("join",
#line 61 "phase4.pcc"
#line 61 "phase4.pcc"
                     list_1_(x,list_1_(y))
#line 61 "phase4.pcc"
#line 61 "phase4.pcc"
                     );
                     
#line 62 "phase4.pcc"
                  }
               } else { goto L3; }
            } else { goto L3; }
}
            else { goto L3; }
         }
         } break;
      default: { goto L3; } break;
   }
}
#line 83 "phase4.pcc"
#line 83 "phase4.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to construct a natural join queries given edges (x,y) and (y,z)
//
///////////////////////////////////////////////////////////////////////////////
//Exps Phase4::make_natural_join(Id x, Id y, Id z, Exps queries)
//{  Exp a = find_edge_query(x,y);
//   Exp b = find_edge_query(y,z);
//}

///////////////////////////////////////////////////////////////////////////////
//
//  Transformation rules to construct edge queries.
//
///////////////////////////////////////////////////////////////////////////////
#line 101 "phase4.pcc"
#line 133 "phase4.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_Phase4
#define DEBUG_Phase4(repl,redex,file,line,rule) repl
#else
static const char * Phase4_file_name = "phase4.pcc";
#endif

static const TreeTables::ShortState Phase4_theta_0[2][2] = {
   { 0, 0 },
   { 4, 10 }
};


static const TreeTables::ShortState Phase4_theta_7[2][1] = {
   { 0 },
   { 6 }
};


static const TreeTables::ShortState Phase4_theta_8[1][1][2] = {
   { { 0, 8 } }
};


static const TreeTables::ShortState Phase4_theta_9[1][2][1] = {
   { { 3 },
   { 5 } }
};


static const TreeTables::ShortState Phase4_theta_11[2][3] = {
   { 0, 0, 9 },
   { 0, 7, 9 }
};


static const TreeTables::ShortState Phase4_mu_0_0[11] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState Phase4_mu_0_1[11] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
};


static const TreeTables::ShortState Phase4_mu_7_0[11] = {
   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
};


static const TreeTables::ShortState Phase4_mu_8_2[11] = {
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
};


static const TreeTables::ShortState Phase4_mu_9_1[11] = {
   0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState Phase4_mu_11_0[11] = {
   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
};


static const TreeTables::ShortState Phase4_mu_11_1[11] = {
   0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0
};


inline void  Phase4::labeler(char const * redex,int& s__,int)
{
   {
      if (_equal_string(redex,"and")) {s__ = 2;}
      else {s__ = 0;}
   }
}

inline void  Phase4::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Phase4::labeler (Exp & redex, int& s__, int r__)
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
         s__ = Phase4_theta_0[Phase4_mu_0_0[s0__]][Phase4_mu_0_1[s1__]]; } break;
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
         s__ = Phase4_theta_7[Phase4_mu_7_0[s0__]][0]; } break;
      case a_Exp::tag_GENERATOR: { 
         int s0__;
         int s1__;
         int s2__;
         s0__ = 0; // Ids
         labeler(_GENERATOR(redex)->_2, s1__, r__);
         labeler(_GENERATOR(redex)->_3, s2__, r__);
         s__ = Phase4_theta_8[0][0][Phase4_mu_8_2[s2__]]; } break;
      default: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_LET(redex)->_1, s0__, r__);
         labeler(_LET(redex)->_2, s1__, r__);
         labeler(_LET(redex)->_3, s2__, r__);
         s__ = Phase4_theta_9[0][Phase4_mu_9_1[s1__]][0]; } break;
   }
   switch (s__) {
      case 5: {
#line 131 "phase4.pcc"
         Exp  repl__;
         int _X1 = _LET(_LET(redex)->_2)->_3->get_rewrite_state();
         switch (_X1) {
            case 3: repl__ = LET(_LET(_LET(redex)->_2)->_1,_LET(_LET(redex)->_2)->_2,LET(_LET(_LET(_LET(redex)->_2)->_3)->_1,_LET(_LET(_LET(redex)->_2)->_3)->_2,LET(_LET(redex)->_1,_LET(_LET(_LET(redex)->_2)->_3)->_3,_LET(redex)->_3))); break;
            default: 
            repl__ = LET(_LET(_LET(redex)->_2)->_1,_LET(_LET(redex)->_2)->_2,LET(_LET(redex)->_1,_LET(_LET(redex)->_2)->_3,_LET(redex)->_3)); break;
         }
         { redex = DEBUG_Phase4(repl__,redex,Phase4_file_name,131,"LET (x, LET (y, b, a), e): ...");
           r__ = 1; goto replacement__; }
#line 133 "phase4.pcc"
} break;
      case 8: {
#line 111 "phase4.pcc"
       Ids  xs   = 
#line 111 "phase4.pcc"
#line 111 "phase4.pcc"
         nil_1_
#line 111 "phase4.pcc"
#line 111 "phase4.pcc"
         ;
         Exps Qs   = 
#line 112 "phase4.pcc"
#line 112 "phase4.pcc"
         nil_1_
#line 112 "phase4.pcc"
#line 112 "phase4.pcc"
         ;
         Exps exps = 
#line 113 "phase4.pcc"
#line 113 "phase4.pcc"
         nil_1_
#line 113 "phase4.pcc"
#line 113 "phase4.pcc"
         ;
         Exps conjuncts = _OP(_GUARD(_GENERATOR(redex)->_3)->_1)->_2;
         
#line 115 "phase4.pcc"
#line 124 "phase4.pcc"
         {
            for (;;) {
               if (conjuncts) {
#line 117 "phase4.pcc"
                IdSet S;
                  	   free_vars(conjuncts->_1,S);
                  	   Id Q = gensym();
                  	   xs   = 
#line 120 "phase4.pcc"
#line 120 "phase4.pcc"
                  list_1_(Q,xs)
#line 120 "phase4.pcc"
#line 120 "phase4.pcc"
                  ;
                  	   Qs   = 
#line 121 "phase4.pcc"
#line 121 "phase4.pcc"
                  list_1_(GENERATOR(_GENERATOR(redex)->_1,_GENERATOR(redex)->_2,GUARD(conjuncts->_1,_GUARD(_GENERATOR(redex)->_3)->_2)),Qs)
#line 121 "phase4.pcc"
#line 121 "phase4.pcc"
                  ;
                  exps = 
#line 122 "phase4.pcc"
#line 122 "phase4.pcc"
                  list_1_(ID(Q),exps)
#line 122 "phase4.pcc"
#line 122 "phase4.pcc"
                  ;
                  	   conjuncts = conjuncts->_2;
                  	
#line 124 "phase4.pcc"
               } else { goto L4; }
            }
            L4:;
         }
#line 125 "phase4.pcc"
#line 125 "phase4.pcc"
         
         
              
#line 127 "phase4.pcc"
#line 127 "phase4.pcc"
         { redex = DEBUG_Phase4(make_let(xs,Qs,OP("join",exps)),redex,Phase4_file_name,110,"GENERATOR (vs, As, GUARD (OP (\"and\", es), E)): ...");
           r__ = 1; goto replacement__; }
#line 127 "phase4.pcc"
#line 127 "phase4.pcc"
         
         
#line 128 "phase4.pcc"
} break;
      case 10: {
#line 105 "phase4.pcc"
         { redex = DEBUG_Phase4(OP("and",list_1_(_OP(redex)->_2->_1,_OP(_OP(redex)->_2->_2->_1)->_2)),redex,Phase4_file_name,105,"OP (\"and\", #[a, OP (\"and\", es)]): ...");
           r__ = 1; goto replacement__; }
#line 110 "phase4.pcc"
} break;
   }
   if (boxed(redex)) {
      redex->set_rewrite_state(s__);
   }
   
}

void  Phase4::labeler (Literal & redex, int& s__, int r__)
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

void  Phase4::labeler (a_List<Exp> *  & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = Phase4_theta_11[Phase4_mu_11_0[s0__]][Phase4_mu_11_1[s1__]]; 
   } else {s__ = 1;
   }
   
}

#line 133 "phase4.pcc"
#line 133 "phase4.pcc"

#line 134 "phase4.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 26
Number of ifs generated      = 16
Number of switches generated = 1
Number of labels             = 2
Number of gotos              = 11
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
