///////////////////////////////////////////////////////////////////////////////
//
//  This file describe the collection datatypes in Prop.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef collection_datatypes_h
#define collection_datatypes_h

#include "basics.ph"

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

datatype CollectionDesc : MEM =
    COLdesc
    {
    name   : Id,
    attrib : CollectionAttrib = COLLECTION_NONE,
    rep    : CollectionRep = REP_none
    }
where type CollectionOp  = int
    and CollectionAttrib = int
    and CollectionDescs  = List<CollectionDesc>
;

#endif
