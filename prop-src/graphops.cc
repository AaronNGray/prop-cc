///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\graphops.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/graphops.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the low level graph operators.
//  We assume that these functions are called only if the appropriate
//  representations are defined.
//
///////////////////////////////////////////////////////////////////////////////

#include "graphtype.h"
#include "graphedges.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Return the domain set as a doubly linked list
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_dom( CodeGen& C) // dom f
{
  C.pr( "%^%s_set domain() const { return %s_set(domset); }",
	    domain_type->name(), domain_type->name());
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return the range set as a doubly linked list
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_ran( CodeGen& C) // ran f
{
  C.pr( "%^%s_set range() const { return %s_set(ranset); }",
	    range_type->name(), range_type->name());
}

///////////////////////////////////////////////////////////////////////////////
//
//  Test if an element is defined in the domain
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_in_dom( CodeGen& C) // x in dom f
{
  C.pr(
        "%^Bool domain_has (%s x) const"
	    "%^  { return x->%s.dom_link.non_nil(); }",
	    domain_type->name(), edge_name
      );
}

void MapEdge::gen_in_dom( CodeGen& C) // x in dom f
{
  if (ops & DOMgop)
  {
    Super::gen_in_dom(C);
    return;
  }

  C.pr(
        "%^Bool domain_has (%s x) const"
        "%^  { return x->%s.image != 0; }",
        domain_type->name(), edge_name
      );
}

void MultiMapEdge::gen_in_dom(CodeGen& C) // x in dom f
{
  if (ops & DOMgop)
  {
    Super::gen_in_dom(C);
    return;
  }

  C.pr(
        "%^Bool domain_has (%s x) const"
	    "%^  { return ! x->%s.image.is_empty(); }",
        domain_type->name(), edge_name
       );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Test if an element is defined in the range
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_in_ran( CodeGen& C) // x in ran f
{
   C.pr(
         "%^Bool range_has (%s x) const"
	     "%^  { return x->%s.coimage != 0; }",
         range_type->name(), edge_name
       );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Test if a pair is defined
//
///////////////////////////////////////////////////////////////////////////////

void MapEdge::gen_in( CodeGen& C) // x in f
{
  C.pr(
        "%^Bool has (%s x, %s y) const"
        "%^   { return x->%s.image && x->%s.image == y; }",
	    domain_type->name(), range_type->name(),
	    edge_name, edge_name
      );
}

void MultiMapEdge::gen_in (CodeGen& C) // x in f
{
  C.pr(
        "%^Bool has (%s x, %s y) const"
        "%^  { return false; }",
	    domain_type->name(), range_type->name()
      );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return the cardinality of a relation
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_size( CodeGen& C) // # f
{
  C.pr( "%^int size () const { return count; }");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return the cardinality of the domain
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_dom_size( CodeGen& C) // # dom f
{
  C.pr( "%^int domain_size () const { return dom_count; }");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return the cardinality of the range
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_ran_size( CodeGen& C) // # ran f
{
  C.pr( "%^int range_size () const { return ran_count; }");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return the image or image set
//
///////////////////////////////////////////////////////////////////////////////

void EdgeDef::gen_image( CodeGen& C) // f(x) or f{x}
{
  bug( "%Limage operation is undefined for edge %s", edge_name);
}

void MapEdge::gen_image( CodeGen& C) // f(x)
{
  C.pr(
        "%^%s operator () (%s x) const"
	    "%^  { return x->%s.image; }",
	    range_type->name(), domain_type->name(), edge_name
      );
}

void MultiMapEdge::gen_image( CodeGen& C) // f{x}
{
  C.pr(
        "%^%s_set operator () (%s x) const"
	    "%^  { return %s_set(x->%s.image); }",
	    range_type->name(), domain_type->name(),
	    range_type->name(), edge_name
      );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Update the image or image set
//
///////////////////////////////////////////////////////////////////////////////
void EdgeDef::gen_update_image( CodeGen& C) // f(x) or f{x}
{
  bug( "%Limage operation is undefined for edge %s", edge_name);
}

void MapEdge::gen_update_image( CodeGen& C) // f(x)
{
  C.pr(
        "%^Bool update(%s x, %s y)%^{%+",
        domain_type->name(), range_type->name()
      );

   // If the edge is already there do nothing
  C.pr(
        "%^%s z = x->%s.image;"
        "%^if (z == y) return false;",
        range_type->name(), edge_name
      );

  C.pr( "%^if (z)" "%^{%+");

  // f(x) was defined

  if (ops & RANgop)
  {
    // Update the range set; remove the old element
    C.pr(
          "%^if(--z->%s.ran_count == 0)"
          "%^{  z->%s.ran_link.unlink();",
          edge_name, edge_name
        );
    if (ops & RANSIZEgop)
      C.pr( "%^  --ran_count;");
    C.pr( "%^}");
  }

  C.pr( "%-%^}%^else%^{%+");

  // f(x) was undefined

  if (ops & SIZEgop) C.pr( "%^++count;");        // a new edge is added
  if (ops & DOMSIZEgop) C.pr( "%^++dom_count;"); // a new domain element
  if (ops & DOMgop)                              // link the new element
     C.pr( "%^domset.link(x->%s.dom_link);", edge_name);

  C.pr( "%-%^}");

  // f(x) := y

  C.pr( "%^x->%s.image = y;", edge_name);

  if (ops & RANgop)
  { // Update the new range set
    C.pr(
          "%^if (++y->%s.ran_count == 1)"
          "%^{  ranset.link(y->%s.ran_link);",
          edge_name, edge_name
        );
    if (ops & RANSIZEgop)
      C.pr( "%^   ++ran_count;");
    C.pr( "%^}");
  }

  // The graph has changed

  C.pr( "%^return true;" "%-%^}");
}

void MultiMapEdge::gen_update_image( CodeGen& C) // f(x)
{
  C.pr(
        "%^Bool update(%s x, const %s_set& y)"
        "%^   { x->%s.image = y.link; }",
        domain_type->name(), range_type->name(), edge_name
      );
}
#line 265 "../../prop-src/graphops.pcc"
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
