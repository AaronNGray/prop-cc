#ifndef phase1_h
#define phase1_h

#include "paige.ph"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the DNF construction and simplification phase
//
///////////////////////////////////////////////////////////////////////////////
rewrite class Phase1 (List<Id>, Exp, List<Exp>, Literal) 
   : virtual public PaigeGoyal
{  
public:
            Phase1();
   virtual ~Phase1();

   virtual Exp phase1(Exp);
};

#endif
