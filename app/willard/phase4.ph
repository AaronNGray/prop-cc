#ifndef phase4_h
#define phase4_h

#include "paige.ph"

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the conjunction decomposition phase
//   Conjunctions are decomposed into natural joins and 
//   projections (edge queries).
//   Edge queries are queries Q(x,y) defined on each edge (x,y) of
//   the query graph.
//
///////////////////////////////////////////////////////////////////////////////
rewrite class Phase4 (Exp, List<Exp>, Literal) : virtual public PaigeGoyal
{  
public:
            Phase4();
   virtual ~Phase4();

   virtual Exp phase4(Exp);
protected:
   Exp make_projection(Id x, Id y, Ids xs, Exps, const IdSet&, Exp predicate);
   Exp decompose_conjunct(Exp, Ids xs, Exps, Exp predicate);
};

#endif
