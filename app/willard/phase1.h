///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase1.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase1.ph"
#ifndef phase1_h
#define phase1_h

#include "paige.h"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the DNF construction and simplification phase
//
///////////////////////////////////////////////////////////////////////////////
#line 11 "phase1.ph"
#line 19 "phase1.ph"
class Phase1 : public BURS, virtual public PaigeGoyal {
private:
   Phase1(const Phase1&);               // no copy constructor
   void operator = (const Phase1&); // no assignment
public:
   struct Phase1_StateRec * stack__, * stack_top__;
public:
   void labeler(const char *, int&, int);
   void labeler(Quark, int&, int);
          void  labeler(a_List<Id> *  & redex, int&, int);
   inline virtual void  operator () (a_List<Id> *  & redex) { int s; labeler(redex,s,0); }
          void  labeler(Exp & redex, int&, int);
   inline virtual void  operator () (Exp & redex) { int s; labeler(redex,s,0); }
          void  labeler(a_List<Exp> *  & redex, int&, int);
   inline virtual void  operator () (a_List<Exp> *  & redex) { int s; labeler(redex,s,0); }
          void  labeler(Literal & redex, int&, int);
   inline virtual void  operator () (Literal & redex) { int s; labeler(redex,s,0); }
private:
#line 13 "phase1.ph"
 
   public:
               Phase1();
      virtual ~Phase1();
   
      virtual Exp phase1(Exp);
#line 19 "phase1.ph"
};
#line 19 "phase1.ph"
#line 19 "phase1.ph"


#endif
#line 22 "phase1.ph"
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
