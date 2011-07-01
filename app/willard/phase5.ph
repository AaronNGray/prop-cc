#ifndef phase5_h
#define phase5_h

#include "paige.ph"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the simple find/count query decomposition phase
//
///////////////////////////////////////////////////////////////////////////////
rewrite class Phase5 (Exp, List<Exp>, Literal) : virtual public PaigeGoyal
{  
public:
            Phase5();
   virtual ~Phase5();

   virtual Exp phase5(Exp);
};

#endif
