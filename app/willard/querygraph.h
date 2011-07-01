///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "querygraph.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "querygraph.ph"
#ifndef query_graph_h
#define query_graph_h

#include "paige.h"
#include <AD/contain/varstack.h>

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the query graph construction phase
//
///////////////////////////////////////////////////////////////////////////////
#line 12 "querygraph.ph"
#line 22 "querygraph.ph"
class QueryGraphConstruction : public BURS, virtual public PaigeGoyal {
private:
   QueryGraphConstruction(const QueryGraphConstruction&);               // no copy constructor
   void operator = (const QueryGraphConstruction&); // no assignment
public:
   struct QueryGraphConstruction_StateRec * stack__, * stack_top__;
public:
   void labeler(const char *, int&, int);
   void labeler(Quark, int&, int);
          void  labeler(Exp & redex, int&, int);
   inline virtual void  operator () (Exp & redex) { int s; labeler(redex,s,0); }
          void  labeler(a_List<Exp> *  & redex, int&, int);
   inline virtual void  operator () (a_List<Exp> *  & redex) { int s; labeler(redex,s,0); }
          void  labeler(Literal & redex, int&, int);
   inline virtual void  operator () (Literal & redex) { int s; labeler(redex,s,0); }
private:
#line 14 "querygraph.ph"

   Bool     preceeds(Id x, Id y) const; // check if x preceeds y in the
   					// quantifier ordering.
   public:
            QueryGraphConstruction();
   virtual ~QueryGraphConstruction();
   
   virtual Exp construct_query_graph(Exp);
#line 22 "querygraph.ph"
};
#line 22 "querygraph.ph"
#line 22 "querygraph.ph"


#endif
#line 25 "querygraph.ph"
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
