///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\graphtype.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/graphtype.ph"
///////////////////////////////////////////////////////////////////////////////
//
// This file implements the graph type generator
//
///////////////////////////////////////////////////////////////////////////////

#ifndef graph_type_generator_h
#define graph_type_generator_h

#include "basics.h"
#include "ir.h"
#include "ast.h"
#include "codegen.h"
#include "classdef.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward type definitions
//
///////////////////////////////////////////////////////////////////////////////

class NodeDef;
class EdgeDef;
class GraphTypeDef;

#line 26 "../../prop-src/graphtype.ph"
#line 28 "../../prop-src/graphtype.ph"
///////////////////////////////////////////////////////////////////////////////
// Definition of type NodeDefs
///////////////////////////////////////////////////////////////////////////////
#line 26 "../../prop-src/graphtype.ph"
typedef a_List<NodeDef *> *  NodeDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type EdgeDefs
///////////////////////////////////////////////////////////////////////////////
#line 27 "../../prop-src/graphtype.ph"
typedef a_List<EdgeDef *> *  EdgeDefs;

#line 28 "../../prop-src/graphtype.ph"
#line 28 "../../prop-src/graphtype.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Indexing options of graph types
//
///////////////////////////////////////////////////////////////////////////////

enum
{
  NOindex        = 0,
  DOMindex       = 1<<0,   // index on domain
  RANindex       = 1<<1,   // index on range
  COUNTindex     = 1<<2,   // counting index
  FORWARDindex   = 1<<3,   // map from domain to range
  INVERSEindex   = 1<<4,   // map from range to domain
  BITMAPindex    = 1<<5,   // use bitmaps to represent index
  UNIONFINDindex = 1<<6    // use union/find to represent index
};

enum
{
  UNBASEDrep       = 0,    // unbased
  WEAKLYBASEDrep   = 1<<1, // weakly based
  STRONGLYBASEDrep = 1<<2, // strongly based
  TABLEDrep        = 1<<3  // also allow address arithmetic on base
};

enum
{
  NOgop          = 0,      // no operations
  SIZEgop        = 1<<0,   // # f
  DOMgop         = 1<<1,   // dom f
  RANgop         = 1<<2,   // ran f
  DOMSIZEgop     = 1<<3,   // # dom f
  RANSIZEgop     = 1<<4,   // # ran f
  IMAGEgop       = 1<<5,   // f(x)
  IMAGESETgop    = 1<<6,   // f{x}
  REVIMAGEgop    = 1<<7,   // (inv f)(x)
  REVIMAGEMAPgop = 1<<8,   // (inv f){x}
  UNIONgop       = 1<<9,   // f union := g
  BITSETgop      = 1<<10,  // bitvector operations
  UNIONFINDgop   = 1<<11,  // union find operations
  INDOMgop       = 1<<12,  // x in dom f
  INRANgop       = 1<<13,  // x in ran f
  INgop          = 1<<14,  // x in f
  UPDATEIMAGEgop = 1<<15   // f(x) := y or f{x} with := y
};

#line 77 "../../prop-src/graphtype.ph"
#line 77 "../../prop-src/graphtype.ph"
///////////////////////////////////////////////////////////////////////////////
// Definition of type GraphIndexing
///////////////////////////////////////////////////////////////////////////////
#line 77 "../../prop-src/graphtype.ph"
typedef int GraphIndexing;

#line 77 "../../prop-src/graphtype.ph"
#line 77 "../../prop-src/graphtype.ph"

#line 78 "../../prop-src/graphtype.ph"
#line 78 "../../prop-src/graphtype.ph"
///////////////////////////////////////////////////////////////////////////////
// Definition of type GraphOps
///////////////////////////////////////////////////////////////////////////////
#line 78 "../../prop-src/graphtype.ph"
typedef int GraphOps;

#line 78 "../../prop-src/graphtype.ph"
#line 78 "../../prop-src/graphtype.ph"

#line 79 "../../prop-src/graphtype.ph"
#line 79 "../../prop-src/graphtype.ph"
///////////////////////////////////////////////////////////////////////////////
// Definition of type GraphRep
///////////////////////////////////////////////////////////////////////////////
#line 79 "../../prop-src/graphtype.ph"
typedef int GraphRep;

#line 79 "../../prop-src/graphtype.ph"
#line 79 "../../prop-src/graphtype.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent a graph type definition.
//
///////////////////////////////////////////////////////////////////////////////

class GraphTypeDef : public ClassDefinition
{
  GraphTypeDef(const GraphTypeDef&);
  void operator = (const GraphTypeDef&);
protected:
  friend class NodeDef;
  friend class EdgeDef;
  NodeDefs node_defs;
  EdgeDefs edge_defs;
public:
  GraphTypeDef( Id name, Inherits, TyQual, NodeDefs=
#line 97 "../../prop-src/graphtype.ph"
#line 97 "../../prop-src/graphtype.ph"
nil_1_
#line 97 "../../prop-src/graphtype.ph"
#line 97 "../../prop-src/graphtype.ph"
, EdgeDefs=
#line 97 "../../prop-src/graphtype.ph"
#line 97 "../../prop-src/graphtype.ph"
nil_1_
#line 97 "../../prop-src/graphtype.ph"
#line 97 "../../prop-src/graphtype.ph"
, Decls=
#line 97 "../../prop-src/graphtype.ph"
#line 97 "../../prop-src/graphtype.ph"
nil_1_
#line 97 "../../prop-src/graphtype.ph"
#line 97 "../../prop-src/graphtype.ph"
);
  virtual ~GraphTypeDef();

  virtual NodeDef * lookup_node (Id);
  virtual EdgeDef * lookup_edge (Id);
  virtual void choose_representation();
  virtual void print_report( CodeGen&);
  void    set_nodes( NodeDefs);
  void    set_edges( EdgeDefs);
  void    set_body( Decls);
protected:
  virtual void gen_class_predefinition( CodeGen&);
  virtual void gen_class_interface( CodeGen&);
  virtual void gen_class_implementation( CodeGen&);
  void gen_init_graph( CodeGen&);
  void gen_lookup_node( CodeGen&);
  void gen_insert_node( CodeGen&);
  void gen_remove_node( CodeGen&);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent a node definition.
//
///////////////////////////////////////////////////////////////////////////////

class NodeDef : public Loc
{
  NodeDef(const NodeDef&);
  void operator = (const NodeDef&);
protected:
  friend class GraphTypeDef;
  friend class EdgeDef;
  GraphTypeDef * G;       // the parent graph
  Id       node_name;     // name of this node
  Ty       node_type;     // node label is a value from this type
  Id       hash_fun;      // hash function
  Id       eq_fun;        // equality function
  LabTys   attributes;    // additional attributes
  GraphRep rep;           // representation of this domain
public:
  NodeDef(GraphTypeDef *, Id, Ty = NOty, Id = 0, Id = 0, LabTys = 
#line 138 "../../prop-src/graphtype.ph"
#line 138 "../../prop-src/graphtype.ph"
nil_1_
#line 138 "../../prop-src/graphtype.ph"
#line 138 "../../prop-src/graphtype.ph"
);
  virtual ~NodeDef();

  inline  Id name () const { return node_name; }
  inline  GraphTypeDef * graph () const { return G; }
  virtual void choose_representation();
  virtual void generate_forward_decls( CodeGen&);
  virtual void generate_representation( CodeGen&);
  virtual void generate_interface( CodeGen&);
  virtual void generate_implementation( CodeGen&);
  virtual void print_report( CodeGen&);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent an edge definition.
//
///////////////////////////////////////////////////////////////////////////////

class EdgeDef : public Loc
{
  EdgeDef(const EdgeDef&);
  void operator = (const EdgeDef&);
protected:
  friend class GraphTypeDef;
  friend class NodeDef;
  GraphTypeDef * graph;       // our graph
  Id             edge_name;   // name of this edge
  NodeDef*       domain_type; // domain of this type
  NodeDef*       range_type;  // range of this type
  GraphIndexing  indexing;    // indexing information
  LabTys         attributes;  // additional attributes
  GraphOps       ops;         // defined operations

protected:
  EdgeDef( GraphTypeDef *, Id, NodeDef*, NodeDef*,
           GraphIndexing, LabTys = 
#line 174 "../../prop-src/graphtype.ph"
#line 174 "../../prop-src/graphtype.ph"
nil_1_
#line 174 "../../prop-src/graphtype.ph"
#line 174 "../../prop-src/graphtype.ph"
);
  virtual ~EdgeDef();
public:

  inline  Id name () const { return edge_name; }
  virtual void choose_representation ();
  virtual void generate_node_representation( CodeGen&, NodeDef *);
  virtual void generate_edge_representation( CodeGen&);
  virtual void generate_interface( CodeGen&);
  virtual void generate_implementation( CodeGen&);
  virtual void print_report( CodeGen&);

protected:

  virtual void generate_edge_rep( CodeGen&);
  virtual void generate_dom_rep ( CodeGen&);
  virtual void generate_ran_rep ( CodeGen&);
  virtual void generate_interf  ( CodeGen&);
  virtual void generate_impl    ( CodeGen&);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to generate various methods to implement various set operations
  //
  ////////////////////////////////////////////////////////////////////////////
  virtual void gen_dom         ( CodeGen&); // dom f
  virtual void gen_ran         ( CodeGen&); // ran f
  virtual void gen_in_dom      ( CodeGen&); // x in dom f
  virtual void gen_in_ran      ( CodeGen&); // x in ran f
  virtual void gen_in          ( CodeGen&) = 0; // x in f
  virtual void gen_size        ( CodeGen&); // # f
  virtual void gen_dom_size    ( CodeGen&); // # dom f
  virtual void gen_ran_size    ( CodeGen&); // # ran f
  virtual void gen_image       ( CodeGen&); // f(x)  or f{x}
  virtual void gen_update_image( CodeGen&); // f(x) := y or f{x} with := y
};

#endif
#line 212 "../../prop-src/graphtype.ph"
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
