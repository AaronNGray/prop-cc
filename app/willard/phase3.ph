#ifndef phase3_h
#define phase3_h

#include "paige.ph"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the disjunction removal phase 
//
///////////////////////////////////////////////////////////////////////////////
rewrite class Phase3 (Exp, List<Exp>, Literal) : virtual public PaigeGoyal
{  
public:
            Phase3();
   virtual ~Phase3();

   virtual Exp phase3(Exp);
};

#endif
