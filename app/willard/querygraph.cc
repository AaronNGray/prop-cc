///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "querygraph.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "querygraph.pcc"
#include <AD/pretty/postream.h>
#include "querygraph.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for query graph construction 
//
///////////////////////////////////////////////////////////////////////////////
QueryGraphConstruction::QueryGraphConstruction() {}
QueryGraphConstruction::~QueryGraphConstruction() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to invoke the query graph construction phase 
//
///////////////////////////////////////////////////////////////////////////////
Exp QueryGraphConstruction::construct_query_graph(Exp e) 
{  message("Constructing the query graph", e); 
   parent.clear();               // clears the query graph
   (*this)(e);                   // construct the graph
   compute_transitive_closure(); // compute the transitive closure
   print_query_graph();
   return e; 
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to check whether a variable preceeds another in the quantifier 
//  ordering.
//
///////////////////////////////////////////////////////////////////////////////
Bool QueryGraphConstruction::preceeds(Id x, Id y) const
{  for (int i = 0; i < quantifier_vars.size(); i++)
   {  if (quantifier_vars[i] == x)
      {  for (int j = i+1; j < quantifier_vars.size(); j++)
            if (quantifier_vars[j] == y) return true;
         return false;
      }
   }
   return false;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Transformation rules
//
///////////////////////////////////////////////////////////////////////////////
#line 48 "querygraph.pcc"
#line 80 "querygraph.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_QueryGraphConstruction
#define DEBUG_QueryGraphConstruction(repl,redex,file,line,rule) repl
#else
static const char * QueryGraphConstruction_file_name = "querygraph.pcc";
#endif

inline void  QueryGraphConstruction::labeler(char const * redex,int& s__,int)
{
   {
s__ = 0;
   }
}

inline void  QueryGraphConstruction::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  QueryGraphConstruction::labeler (Exp & redex, int& s__, int r__)
{
replacement__:
   {
      switch (redex->tag__) {
         case a_Exp::tag_OP: {
            if (_less_string(_OP(redex)->_1,"=")) {
               if (_equal_string(_OP(redex)->_1,"#")) {
               L1:; 
#line 67 "querygraph.pcc"
             
               // Collect all free variables in this expression.
               IdSet S;
               free_vars(_OP(redex)->_2,S);   
               
               // Now add edges to the query graph.
               foreach(i,S)
               {  Id x = S.value(i);
               	foreach(j,S)
               	{  Id y = S.value(j);
               	   if (x != y && preceeds(x,y)) add_edge(x,y);
               	}
               }
               
#line 80 "querygraph.pcc"
}
               else if (_equal_string(_OP(redex)->_1,"/=")) { goto L1; }
               else if (_equal_string(_OP(redex)->_1,"<")) { goto L1; }
               else if (_equal_string(_OP(redex)->_1,"<=")) { goto L1; }
            } else {
               if (_equal_string(_OP(redex)->_1,"=")) { goto L1; }
               else if (_equal_string(_OP(redex)->_1,">")) { goto L1; }
               else if (_equal_string(_OP(redex)->_1,">=")) { goto L1; }
            }
            } break;
         case a_Exp::tag_FORALL: {
#line 55 "querygraph.pcc"
           push_quantifier(_FORALL(redex)->_1); 
#line 55 "querygraph.pcc"
            } break;
         case a_Exp::tag_EXISTS: {
#line 56 "querygraph.pcc"
           push_quantifier(_EXISTS(redex)->_1); 
#line 56 "querygraph.pcc"
            } break;
         case a_Exp::tag_GENERATOR: {
#line 57 "querygraph.pcc"
           push_quantifier(_GENERATOR(redex)->_1); 
#line 57 "querygraph.pcc"
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
#line 60 "querygraph.pcc"
           pop_quantifier(_FORALL(redex)->_1); 
#line 60 "querygraph.pcc"
            } break;
         case a_Exp::tag_EXISTS: {
#line 61 "querygraph.pcc"
           pop_quantifier(_EXISTS(redex)->_1); 
#line 61 "querygraph.pcc"
            } break;
         case a_Exp::tag_GENERATOR: {
#line 62 "querygraph.pcc"
           pop_quantifier(_GENERATOR(redex)->_1); 
#line 62 "querygraph.pcc"
            } break;
         default: {} break;
      }
   }
   
}

void  QueryGraphConstruction::labeler (Literal & redex, int& s__, int r__)
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

void  QueryGraphConstruction::labeler (a_List<Exp> *  & redex, int& s__, int r__)
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

#line 81 "querygraph.pcc"
#line 81 "querygraph.pcc"

#line 82 "querygraph.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 20
Number of ifs generated      = 8
Number of switches generated = 2
Number of labels             = 1
Number of gotos              = 6
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
