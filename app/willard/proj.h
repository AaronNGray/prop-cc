///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "proj.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "proj.ph"
#ifndef projection_recognition_h
#define projection_recognition_h

#include "paige.h"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the projection recognition phase 
//
///////////////////////////////////////////////////////////////////////////////
#line 11 "proj.ph"
#line 20 "proj.ph"
class Projection : public BURS, virtual public PaigeGoyal {
private:
   Projection(const Projection&);               // no copy constructor
   void operator = (const Projection&); // no assignment
public:
   struct Projection_StateRec * stack__, * stack_top__;
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
#line 12 "proj.ph"
 
   public:
               Projection();
      virtual ~Projection();
   
      virtual Exp projection_recognition(Exp);
   protected:   
      Exp make_projection(const IdSet&, Ids xs, Exps Xs, Exp pred, Exp exp);
#line 20 "proj.ph"
};
#line 20 "proj.ph"
#line 20 "proj.ph"


#endif
#line 23 "proj.ph"
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
