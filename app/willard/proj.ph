#ifndef projection_recognition_h
#define projection_recognition_h

#include "paige.ph"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the projection recognition phase 
//
///////////////////////////////////////////////////////////////////////////////
rewrite class Projection (Exp, List<Exp>, Literal) : virtual public PaigeGoyal
{  
public:
            Projection();
   virtual ~Projection();

   virtual Exp projection_recognition(Exp);
protected:   
   Exp make_projection(const IdSet&, Ids xs, Exps Xs, Exp pred, Exp exp);
};

#endif
