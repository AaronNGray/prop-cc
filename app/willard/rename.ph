#ifndef renaming_h
#define renaming_h

#include "willard-ast.ph"
#include "paige.ph"
#include "smap.h"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the variable renaming phase.
//   Also for each variable, we collects it range.
//
///////////////////////////////////////////////////////////////////////////////
rewrite class RemoveDuplicateNames (Exp, List<Exp>, Literal)
   : virtual public PaigeGoyal
{  
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
};

#endif
