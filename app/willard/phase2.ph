#ifndef phase2_h
#define phase2_h

#include "paige.ph"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the quantifier elimination phase
//
///////////////////////////////////////////////////////////////////////////////
rewrite class Phase2 (List<Id>, Exp, List<Exp>, Literal) 
   : virtual public PaigeGoyal
{  
public:
            Phase2();
   virtual ~Phase2();

   virtual Exp phase2(Exp);
};

#endif
