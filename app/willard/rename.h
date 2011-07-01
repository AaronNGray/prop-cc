///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "rename.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "rename.ph"
#ifndef renaming_h
#define renaming_h

#include "willard-ast.h"
#include "paige.h"
#include "smap.h"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the variable renaming phase.
//   Also for each variable, we collects it range.
//
///////////////////////////////////////////////////////////////////////////////
#line 14 "rename.ph"
#line 29 "rename.ph"
class RemoveDuplicateNames : public BURS, virtual public PaigeGoyal {
private:
   RemoveDuplicateNames(const RemoveDuplicateNames&);               // no copy constructor
   void operator = (const RemoveDuplicateNames&); // no assignment
public:
   struct RemoveDuplicateNames_StateRec * stack__, * stack_top__;
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
#line 16 "rename.ph"
 
   SMap<Id, Ids> env;
   public:
            RemoveDuplicateNames();
   virtual ~RemoveDuplicateNames();
   
   virtual Exp remove_duplicate_names(Exp);
   
   void new_binding(Id&);
   void new_binding(Ids);
   void rename(Id&);
   void old_binding(Id&);
   void old_binding(Ids);
#line 29 "rename.ph"
};
#line 29 "rename.ph"
#line 29 "rename.ph"


#endif
#line 32 "rename.ph"
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
