///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\graphrep.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/graphrep.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This file implements data structure mapping for graph nodes and edges.
//
///////////////////////////////////////////////////////////////////////////////

#include "graphedges.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the nodes and edges datatypes
//
///////////////////////////////////////////////////////////////////////////////

#line 15 "../../prop-src/graphrep.pcc"
#line 15 "../../prop-src/graphrep.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<NodeDef *>
//
///////////////////////////////////////////////////////////////////////////////
#line 15 "../../prop-src/graphrep.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<EdgeDef *>
//
///////////////////////////////////////////////////////////////////////////////
#line 15 "../../prop-src/graphrep.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<NodeDef *>
//
///////////////////////////////////////////////////////////////////////////////
#line 15 "../../prop-src/graphrep.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<NodeDef *>;
template a_List<NodeDef *> * list_1_(EdgeDef * x_1, a_List<EdgeDef *> *  x_2);
template a_List<NodeDef *> * list_1_(EdgeDef * x_list_1_);
template int boxed(const a_List<NodeDef *> *);
template int untag(const a_List<NodeDef *> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<EdgeDef *>
//
///////////////////////////////////////////////////////////////////////////////
#line 15 "../../prop-src/graphrep.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<EdgeDef *>;
template a_List<EdgeDef *> * list_1_(NodeDef * x_1, a_List<NodeDef *> *  x_2);
template a_List<EdgeDef *> * list_1_(NodeDef * x_list_1_);
template int boxed(const a_List<EdgeDef *> *);
template int untag(const a_List<EdgeDef *> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

#line 15 "../../prop-src/graphrep.pcc"
#line 15 "../../prop-src/graphrep.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Constructors for all edge classes
//
///////////////////////////////////////////////////////////////////////////////

MapEdge::MapEdge
  ( GraphTypeDef * G, Id id, NodeDef* a, NodeDef* b, GraphIndexing i, LabTys attribs)
  : EdgeDef( G, id, a, b, i, attribs) {}

MultiMapEdge::MultiMapEdge
  (GraphTypeDef * G, Id id, NodeDef* a, NodeDef* b, GraphIndexing i, LabTys attribs)
  : EdgeDef( G, id, a, b, i, attribs) {}

BijectionEdge::BijectionEdge
  (GraphTypeDef * G, Id id, NodeDef* a, NodeDef* b, GraphIndexing i, LabTys attribs)
  : MapEdge( G, id, a, b, i, attribs) {}

EquivRelationEdge::EquivRelationEdge
  (GraphTypeDef * G, Id id, NodeDef* a, NodeDef* b, GraphIndexing i, LabTys attribs)
  : MapEdge( G, id, a, b, i, attribs) {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to computing the proper representation for a node
//
///////////////////////////////////////////////////////////////////////////////

void NodeDef::choose_representation()
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to computing the proper representation for an edge
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::choose_representation()
{  // If we have f(x) or f{x} then we also have 'x in dom f' for free
  if (ops & (IMAGEgop | IMAGESETgop))
    ops |= INDOMgop;
  if (ops & INDOMgop)
    ops |= INgop; // x in f
}

void MapEdge::choose_representation()
{
  ops |= IMAGEgop;       // f(x)
  ops |= DOMgop;         // dom f
  ops |= RANgop;         // ran f
  ops |= DOMSIZEgop;     // #dom f
  ops |= RANSIZEgop;     // #ran f
  ops |= UPDATEIMAGEgop; // f(x) := y
  ops |= SIZEgop;        // # f
  Super::choose_representation();
}

void MultiMapEdge::choose_representation()
{
  ops |= IMAGESETgop;    // f{x}
  ops |= DOMgop;         // dom f
  ops |= DOMSIZEgop;     // #dom f
  ops |= RANSIZEgop;     // #ran f
  ops |= UPDATEIMAGEgop; // f{x} with := y
  ops |= SIZEgop;        // # f
  Super::choose_representation();
}

void BijectionEdge::choose_representation()
{
  Super::choose_representation();
}

void EquivRelationEdge::choose_representation()
{
  Super::choose_representation();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic method to generate forward declarations for a node object
//
///////////////////////////////////////////////////////////////////////////////

void NodeDef::generate_forward_decls( CodeGen& C)
{
  C.pr( "%^class %s_%s_node;", graph()->class_name, node_name);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic method to generate representation for a node object class.
//
///////////////////////////////////////////////////////////////////////////////
void NodeDef::generate_representation( CodeGen& C)
{
  C.pr(
        "\n"
        "%^%/"
        "%^//"
        "%^//  Representation of node %s::%s(%T)"
        "%^//"
        "%^%/",
        graph()->class_name, node_name, node_type
      );

  C.pr(
        "%^class %s_%s_node {%+"
        "%^// no copy constructor or assignment"
        "%^%s_%s_node(const %s_%s_node&);"
        "%^void operator = (const %s_%s_node&);"
        "%^%T the_label;"
        "%-%^public:%+"
        "%^%T label() const { return the_label; }"
        "%^operator %T () const { return the_label; }"
        "%^friend class %s;",
        graph()->class_name, node_name,
        graph()->class_name, node_name, graph()->class_name, node_name,
        graph()->class_name, node_name,
        node_type, node_type, node_type, graph()->class_name
      );

  for_each (EdgeDef *, e, graph()->edge_defs)
  {
    e->generate_node_representation( C, this);
  }

  C.pr(
        "%-%^public:%+"
        "%^%s_%s_node();"
        "%^~%s_%s_node();"
        "%-%^};",
        graph()->class_name, node_name,
        graph()->class_name, node_name
      );

  C.pr( "\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic method to generate interface for a node object
//
///////////////////////////////////////////////////////////////////////////////

void NodeDef::generate_interface (CodeGen& C)
{
  C.pr(
        "%-%^public:%+"
        "%^%/"
        "%^//"
        "%^// Interface to node %s(%T)"
        "%^//"
        "%^%/",
        node_name, node_type
      );

  if (node_type == NOty)
  {
    C.pr(
          "%^// Create a new node; the new node is unique."
          "%^// The new node is now attached to the graph."
          "%^virtual %s create_%s();",
          node_name, node_name
        );
  }
  else
  {
    C.pr(
          "%-%^protected:%+"
          "%^// HashTable< %T, %s, %s< %T >, %s< %T > > %s_table;"
          "%-%^public:%+",
          node_type, node_name, hash_fun, node_type,
          eq_fun, node_type, node_name
        );

    C.pr(
          "%^// Create a new node, or lookup an existing node."
          "%^// The node is now attached to the graph."
          "%^virtual %s create_%s(%T);"
          "%^\n"
          "%^// Lookup a node by its label."
          "%^// Returns nil if no such node exists."
          "%^%s lookup_%s(%T) const;"
          "%^\n"
          "%^// Does a node of a certain label exists?"
          "%^Bool has_%s(%T l) const { return lookup_%s(l) != 0; }"
          "%^\n"
          "%^// Insert a new node into the graph by label."
          "%^// A no-op if the graph with the label already exists"
          "%^%s insert_%s(%T l) { return create_%s(l); }"
          "%^\n"
          "%^// Remove a node by label."
          "%^// Returns true if the graph is changed."
          "%^Bool remove_%s(%T l) { return remove(lookup_%s(l)); }",
          node_name, node_name, node_type,
          node_name, node_name, node_type,
          node_name, node_type, node_name,
          node_name, node_name, node_type, node_name,
          node_name, node_type, node_name
        );
  }

  C.pr(
        "%^\n"
        "%^// Insert a node into the graph."
        "%^// Returns true if the graph is changed."
        "%^virtual Bool insert(%s);"
        "%^\n"
        "%^// Remove a node from the graph."
        "%^// The node is destroyed."
        "%^// Returns true if the graph is changed."
        "%^virtual Bool remove(%s);",
        node_name, node_name
      );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic method to generate the implementation for a node object
//
///////////////////////////////////////////////////////////////////////////////

void NodeDef::generate_implementation (CodeGen& C)
{
  C.pr(
        "%^%/"
        "%^// Implementation of node %s::%s(%T)"
        "%^%/",
        graph()->class_name, node_name, node_type
      );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic method to generate representation for an edge within a node
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_node_representation( CodeGen& C, NodeDef * n)
{
  if (n != domain_type && n != range_type)
    return;
  C.pr( "%^struct {%+");
  if (n == domain_type)
    generate_dom_rep(C);
  if (n == range_type)
    generate_ran_rep(C);
  C.pr( "%-%^} %s;", edge_name);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic method to generate representation for an edge within the graph
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_edge_representation( CodeGen& C)
{
  generate_edge_rep(C);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic method to generate representation for an edge within the graph
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_edge_rep( CodeGen& C)
{
  if (ops & SIZEgop)    C.pr( "%^int count;              // number of edges ");
  if (ops & DOMgop)     C.pr( "%^GraphType::Link domset; // the domain");
  if (ops & DOMSIZEgop) C.pr( "%^int dom_count;          // size of domain");
  if (ops & RANgop)     C.pr( "%^GraphType::Link ranset; // the range");
  if (ops & RANSIZEgop) C.pr( "%^int ran_count;          // size of range");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to compute the representation
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_dom_rep( CodeGen& C)
{
  if (ops & DOMgop) C.pr( "%^GraphType::Link dom_link;");
}

void EdgeDef::generate_ran_rep( CodeGen& C)
{
  if (ops & RANgop)
    C.pr(
          "%^GraphType::Link ran_link;"
          "%^int ran_count;"
        );
}

void MapEdge::generate_dom_rep( CodeGen& C)
{
  Super::generate_dom_rep(C);
  if (ops & IMAGEgop)
    C.pr( "%^%s_%s_node * image;", graph->class_name, range_type->name());
}

void MapEdge::generate_ran_rep( CodeGen& C)
{
  Super::generate_ran_rep(C);
}

void MultiMapEdge::generate_dom_rep( CodeGen& C)
{
  Super::generate_dom_rep(C);
  if (ops & IMAGESETgop)
    C.pr( "%^GraphType::Link image;");
}

void MultiMapEdge::generate_ran_rep( CodeGen& C)
{
  Super::generate_ran_rep(C);
}

void BijectionEdge::generate_dom_rep( CodeGen& C)
{
  Super::generate_dom_rep(C);
}

void BijectionEdge::generate_ran_rep( CodeGen& C)
{
  Super::generate_ran_rep(C);
}

void EquivRelationEdge::generate_dom_rep( CodeGen& C)
{
  Super::generate_dom_rep(C);
}

void EquivRelationEdge::generate_ran_rep( CodeGen& C)
{
  Super::generate_ran_rep(C);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic methods to generate the interface of an edge
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_interface( CodeGen& C)
{
   if (domain_type == 0 || range_type == 0)
     return;

   //
   // Encapsulate all methods to manipulate this edge into an edge record
   //

   C.pr(
         "%^class %s_record {"
         "%^protected:%+"
         "%^friend class %s;",
         edge_name, graph->class_name
       );
   generate_edge_representation(C);  // how to represent this edge
   C.pr( "%-%^public:%+");
   generate_interf(C);               // the methods
   C.pr(
         "%-%^} %s;"
         "%^",
         edge_name
       );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to generate the interface of an edge
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_interf (CodeGen& C)
{
  if (ops & DOMgop)     gen_dom(C);          // dom f
  if (ops & RANgop)     gen_ran(C);          // ran f
  if (ops & INDOMgop)   gen_in_dom(C);       // x in dom f
  if (ops & INRANgop)   gen_in_ran(C);       // x in ran f
  if (ops & INgop)      gen_in(C);           // x in f
  if (ops & SIZEgop)    gen_size(C);         // size of relation
  if (ops & DOMSIZEgop) gen_dom_size(C);     // size of domain
  if (ops & RANSIZEgop) gen_ran_size(C);     // size of range
  if (ops & (IMAGEgop | IMAGESETgop)) gen_image(C); // f(x) or f{x}
  if (ops & UPDATEIMAGEgop) gen_update_image(C); // f(x) := y or f{x} with := y
}

void MapEdge::generate_interf( CodeGen& C)
{
  Super::generate_interf(C);
}

void MultiMapEdge::generate_interf( CodeGen& C)
{
  Super::generate_interf(C);
}

void BijectionEdge::generate_interf( CodeGen& C)
{
  Super::generate_interf(C);
}

void EquivRelationEdge::generate_interf( CodeGen& C)
{
  Super::generate_interf(C);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Generic methods to generate the implementation of an edge
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_implementation( CodeGen& C)
{
  generate_impl(C);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to generate the implementation
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::generate_impl( CodeGen& C)
{
}

void MapEdge::generate_impl( CodeGen& C)
{
  Super::generate_impl(C);
}

void MultiMapEdge::generate_impl( CodeGen& C)
{
  Super::generate_impl(C);
}

void BijectionEdge::generate_impl( CodeGen& C)
{
  Super::generate_impl(C);
}

void EquivRelationEdge::generate_impl( CodeGen& C)
{
  Super::generate_impl(C);
}
#line 470 "../../prop-src/graphrep.pcc"
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
