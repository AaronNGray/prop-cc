///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase4.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase4.ph"
#ifndef phase4_h
#define phase4_h

#include "paige.h"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the conjunction decomposition phase
//   Conjunctions are decomposed into natural joins and 
//   projections (edge queries).
//   Edge queries are queries Q(x,y) defined on each edge (x,y) of
//   the query graph.
//
///////////////////////////////////////////////////////////////////////////////
#line 15 "phase4.ph"
#line 25 "phase4.ph"
class Phase4 : public BURS, virtual public PaigeGoyal {
private:
   Phase4(const Phase4&);               // no copy constructor
   void operator = (const Phase4&); // no assignment
public:
   struct Phase4_StateRec * stack__, * stack_top__;
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
#line 16 "phase4.ph"
 
   public:
               Phase4();
      virtual ~Phase4();
   
      virtual Exp phase4(Exp);
   protected:
      Exp make_projection(Id x, Id y, Ids xs, Exps, const IdSet&, Exp predicate);
      Exp decompose_conjunct(Exp, Ids xs, Exps, Exp predicate);
#line 25 "phase4.ph"
};
#line 25 "phase4.ph"
#line 25 "phase4.ph"


#endif
#line 28 "phase4.ph"
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
