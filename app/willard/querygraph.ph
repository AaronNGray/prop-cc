#ifndef query_graph_h
#define query_graph_h

#include "paige.ph"
#include <AD/contain/varstack.h>

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the query graph construction phase
//
///////////////////////////////////////////////////////////////////////////////
rewrite class QueryGraphConstruction (Exp, List<Exp>, Literal) 
   : virtual public PaigeGoyal
{   
   Bool     preceeds(Id x, Id y) const; // check if x preceeds y in the
					// quantifier ordering.
public:
            QueryGraphConstruction();
   virtual ~QueryGraphConstruction();

   virtual Exp construct_query_graph(Exp);
};

#endif
