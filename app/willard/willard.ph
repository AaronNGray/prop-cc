#ifndef willard_decomposition_h
#define willard_decomposition_h

#include "paige.ph"
#include "rename.ph"
#include "querygraph.ph"
#include "proj.ph"
#include "phase1.ph"
#include "phase2.ph"
#include "phase3.ph"
#include "phase4.ph"
#include "phase5.ph"

///////////////////////////////////////////////////////////////////////////////
//
//  This class combines all the phases together into one module.
//
///////////////////////////////////////////////////////////////////////////////
class Willard : virtual public PaigeGoyal,
                virtual public RemoveDuplicateNames,
                virtual public QueryGraphConstruction,
                virtual public Projection,
                virtual public Phase1,
                virtual public Phase2,
                virtual public Phase3,
                virtual public Phase4,
                virtual public Phase5
{   Willard(const Willard&);
    void operator = (const Willard&);
public:
    Willard();
   ~Willard();
};

#endif
