///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\collection.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/collection.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describe the collection datatypes in Prop.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef collection_datatypes_h
#define collection_datatypes_h

#include "basics.h"

///////////////////////////////////////////////////////////////////////////////
//
//  CollectionAttrib describes the set of extension properties that
//  a collection may have.
//
///////////////////////////////////////////////////////////////////////////////

enum
{
  COLLECTION_NONE            = 0,
  COLLECTION_ORDERED         = 1, // is it ordered?
  COLLECTION_IDEMPOTENT      = 2, // no duplicates?
  COLLECTION_SINGLE_VALUED   = 4, // single valued map?
  COLLECTION_EXTERNAL_KEYED  = 8  // external ordering function?
};

///////////////////////////////////////////////////////////////////////////////
//
//  Operations that can be performed on a collection.
//
///////////////////////////////////////////////////////////////////////////////

enum
{
  OP_size       = 1<<1,   // cardinality
  OP_capacity   = 1<<2,   // maximum capacity
  OP_growth     = 1<<3,   // dynamic expansion
  OP_copy       = 1<<4,   // copy
  OP_move       = 1<<5,   // destructive copy
  OP_merge      = 1<<6,   // destructive merge
  OP_with       = 1<<7,   // insert an element by key
  OP_less       = 1<<8,   // delete an element by key
  OP_union      = 1<<9,   // union
  OP_intersect  = 1<<10,  // intersection
  OP_arb        = 1<<11,  // choose an arbitrary element
  OP_delete     = 1<<12,  // self deletion
  OP_forall     = 1<<13,  // iteration
  OP_minkey     = 1<<14,  // find min element by key
  OP_maxkey     = 1<<15,  // find max element by key
  OP_deletemin  = 1<<16,  // delete min element by key
  OP_deletemax  = 1<<17,  // delete max element by key
  OP_count      = 1<<18,  // count element by key
  OP_map        = 1<<19,  // f(x)
  OP_mapall     = 1<<20,  // f{x}
  OP_inverse    = 1<<21,  // f^{-1}{x}
  OP_dom        = 1<<22,  // dom f
  OP_ran        = 1<<23   // ran f
};

///////////////////////////////////////////////////////////////////////////////
//
//  Intensional properties are described by CollectionRep.
//
///////////////////////////////////////////////////////////////////////////////

enum CollectionRep
{
  REP_none           = 0,
  REP_unbased        = 1<<1,           // linked list representation
  REP_weakly_based   = 1<<2,           // linked list representation
  REP_strongly_based = 1<<3,           // linked list representation
  REP_array          = 1<<4,           // array representation
  REP_based          = 1<<5,           // based set representation
  REP_bitmap         = 1<<6,           // bitmap representation
  REP_hash           = 1<<7,           // hash table representation
  REP_heap           = 1<<8            // binary heap representation
};

///////////////////////////////////////////////////////////////////////////////
//
//  The collection type descriptor is described as follows.  All collection
//  types are generative.
//
///////////////////////////////////////////////////////////////////////////////

#line 87 "../../prop-src/collection.ph"
#line 97 "../../prop-src/collection.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for CollectionDesc
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_CollectionDesc_defined
#define datatype_CollectionDesc_defined
  class a_CollectionDesc;
  typedef a_CollectionDesc * CollectionDesc;
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type CollectionOp
///////////////////////////////////////////////////////////////////////////////
#line 94 "../../prop-src/collection.ph"
typedef int CollectionOp;

///////////////////////////////////////////////////////////////////////////////
// Definition of type CollectionAttrib
///////////////////////////////////////////////////////////////////////////////
#line 95 "../../prop-src/collection.ph"
typedef int CollectionAttrib;

///////////////////////////////////////////////////////////////////////////////
// Definition of type CollectionDescs
///////////////////////////////////////////////////////////////////////////////
#line 96 "../../prop-src/collection.ph"
typedef a_List<CollectionDesc> *  CollectionDescs;

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor CollectionDesc::COLdesc
//
///////////////////////////////////////////////////////////////////////////////
class a_CollectionDesc : public MEM {
public:
#line 87 "../../prop-src/collection.ph"
  Id name; CollectionAttrib attrib; CollectionRep rep; 
  inline a_CollectionDesc (Id x_name, CollectionAttrib x_attrib = COLLECTION_NONE, CollectionRep x_rep = REP_none)
   : name(x_name), attrib(x_attrib), rep(x_rep)
  {
  }
};
inline int boxed(const a_CollectionDesc *) { return 1; }
inline int untag(const a_CollectionDesc *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for CollectionDesc
//
///////////////////////////////////////////////////////////////////////////////
inline a_CollectionDesc * COLdesc (Id x_name, CollectionAttrib x_attrib = COLLECTION_NONE, CollectionRep x_rep = REP_none)
{
  return new a_CollectionDesc (x_name, x_attrib, x_rep);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for CollectionDesc
//
///////////////////////////////////////////////////////////////////////////////


#line 97 "../../prop-src/collection.ph"
#line 97 "../../prop-src/collection.ph"


#endif
#line 100 "../../prop-src/collection.ph"
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
