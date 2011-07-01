///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase3.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase3.ph"
#ifndef phase3_h
#define phase3_h

#include "paige.h"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the disjunction removal phase 
//
///////////////////////////////////////////////////////////////////////////////
#line 11 "phase3.ph"
#line 18 "phase3.ph"
class Phase3 : public BURS, virtual public PaigeGoyal {
private:
   Phase3(const Phase3&);               // no copy constructor
   void operator = (const Phase3&); // no assignment
public:
   struct Phase3_StateRec * stack__, * stack_top__;
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
#line 12 "phase3.ph"
 
   public:
               Phase3();
      virtual ~Phase3();
   
      virtual Exp phase3(Exp);
#line 18 "phase3.ph"
};
#line 18 "phase3.ph"
#line 18 "phase3.ph"


#endif
#line 21 "phase3.ph"
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
