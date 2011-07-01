///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase2.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase2.ph"
#ifndef phase2_h
#define phase2_h

#include "paige.h"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the quantifier elimination phase
//
///////////////////////////////////////////////////////////////////////////////
#line 11 "phase2.ph"
#line 19 "phase2.ph"
class Phase2 : public BURS, virtual public PaigeGoyal {
private:
   Phase2(const Phase2&);               // no copy constructor
   void operator = (const Phase2&); // no assignment
public:
   struct Phase2_StateRec * stack__, * stack_top__;
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
#line 13 "phase2.ph"
 
   public:
               Phase2();
      virtual ~Phase2();
   
      virtual Exp phase2(Exp);
#line 19 "phase2.ph"
};
#line 19 "phase2.ph"
#line 19 "phase2.ph"


#endif
#line 22 "phase2.ph"
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
