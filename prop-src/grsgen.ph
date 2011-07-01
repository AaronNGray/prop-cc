///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the graph rewriting system compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef graph_rewriting_system_compiler_h
#define graph_rewriting_system_compiler_h

#include "basics.ph"
#include "codegen.h"
#include "matchcom.ph"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward type declarations
//
///////////////////////////////////////////////////////////////////////////////

datatype Pat and Exp and Decl;

///////////////////////////////////////////////////////////////////////////////
//
//  Abstract syntax for graph rewriting rules
//
///////////////////////////////////////////////////////////////////////////////

datatype
    GraphRewritingRule : Loc =         // a graph rewriting rule
        GRSrule
          {
            lhs : GRSPat,         // antecedent
            rhs : GRSConclusions  // conclusions
          }

and GRSPat : Loc =                 // antecedent of a rule
       EDGEgpat  (Id, List<Pat>)   // edge pattern, i.e. pattern on a relation
    |  GUARDgpat (Exp)             // guard expressions
    |  NOTgpat   (GRSPat)          // negation
    |  ANDgpat   (GRSPat, GRSPat)  // conjunction
    |  ORgpat    (GRSPat, GRSPat)  // disjunction
    |  FORALLgpat(Id, GRSPat)      // universal quantification

and GRSConclusion : Loc =
       ADDEDGEaction     (Id, List<Exp>)  // add a new edge
    |  DELETEEDGEaction  (Id, List<Exp>)  // delete an edge
    |  ADDNODEaction     (Exp)            // add a node
    |  DELETENODEaction  (Exp)            // delete a node
    |  EMBEDDEDaction    (List<Decl>)     // any embedded action

where type GRSConclusions = List<GRSConclusion>
;

///////////////////////////////////////////////////////////////////////////////
//
//  The interface to the graph rewriting system compiler
//
///////////////////////////////////////////////////////////////////////////////

class GraphRewritingCompiler : virtual public CodeGen,
                               virtual public MatchCompiler
{
  GraphRewritingCompiler(const GraphRewritingCompiler&);
  void operator = (const GraphRewritingCompiler&);
public:
  GraphRewritingCompiler();
  ~GraphRewritingCompiler();

  void gen_graph_rewriting_system (Id, LabTys, List<GraphRewritingRule>);
};

#endif
