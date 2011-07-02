///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\graphreport.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/graphreport.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file generates a readable report of the graph type representation.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "graphtype.h"
#include "graphedges.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Print a report on a graph type definition
//
///////////////////////////////////////////////////////////////////////////////

void GraphTypeDef::print_report(CodeGen& f)
{
  for_each ( NodeDef *, n, node_defs)
    n->print_report(f);
  for_each ( EdgeDef *, e, edge_defs)
    e->print_report(f);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Describe the node
//
///////////////////////////////////////////////////////////////////////////////

void NodeDef::print_report( CodeGen& f)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Describe the edge
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::print_report( CodeGen& f)
{
}

void MapEdge::print_report( CodeGen& f)
{  Super::print_report(f);
}

void MultiMapEdge::print_report( CodeGen& f)
{  Super::print_report(f);
}

void BijectionEdge::print_report( CodeGen& f)
{  Super::print_report(f);
}

void EquivRelationEdge::print_report( CodeGen& f)
{  Super::print_report(f);
}
#line 61 "../../prop-src/graphreport.pcc"
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
