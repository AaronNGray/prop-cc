///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "willard.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "willard.ph"
#ifndef willard_decomposition_h
#define willard_decomposition_h

#include "paige.h"
#include "rename.h"
#include "querygraph.h"
#include "proj.h"
#include "phase1.h"
#include "phase2.h"
#include "phase3.h"
#include "phase4.h"
#include "phase5.h"

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
#line 36 "willard.ph"
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
