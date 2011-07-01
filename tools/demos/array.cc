///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.2),
//  last updated on Mar 14, 1997.
//  The original source file is "array.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "array.pcc"
//
// Test the generation of datatypes with array arguments
//

#include <AD/strings/string.h>

#line 7 "array.pcc"
#line 10 "array.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for BTree
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_BTree_defined
#define datatype_BTree_defined
   class a_BTree;
   typedef a_BTree * BTree;
#endif

#  define empty (BTree)0

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype BTree
//
///////////////////////////////////////////////////////////////////////////////
class a_BTree {
public:
   enum Tag_BTree {
      tag_leaf = 0, tag_node = 1
   };

public:
   const Tag_BTree tag__; // variant tag
protected:
   inline a_BTree(Tag_BTree t__) : tag__(t__) {}
public:
};
inline int boxed(const a_BTree * x) { return x != 0; }
inline int untag(const a_BTree * x) { return x ? (x->tag__+1) : 0; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor BTree::leaf
//
///////////////////////////////////////////////////////////////////////////////
class BTree_leaf : public a_BTree {
public:
#line 8 "array.pcc"
   String leaf; 
   inline BTree_leaf (String const & x_leaf)
    : a_BTree(tag_leaf), leaf(x_leaf)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor BTree::node
//
///////////////////////////////////////////////////////////////////////////////
class BTree_node : public a_BTree {
public:
#line 9 "array.pcc"
   int _1; int _2; BTree _3[10]; 
   inline BTree_node (int x_1, int x_2, BTree x_3[10])
    : a_BTree(tag_node), _1(x_1), _2(x_2), _3(x_3)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for BTree
//
///////////////////////////////////////////////////////////////////////////////
inline a_BTree * leaf (String const & x_leaf)
{ return new BTree_leaf (x_leaf); }
inline a_BTree * node (int x_1, int x_2, BTree x_3[10])
{ return new BTree_node (x_1, x_2, x_3); }
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for BTree
//
///////////////////////////////////////////////////////////////////////////////
inline BTree_leaf * _leaf(const a_BTree * _x_) { return (BTree_leaf *)_x_; }
inline BTree_node * _node(const a_BTree * _x_) { return (BTree_node *)_x_; }

#line 10 "array.pcc"
#line 10 "array.pcc"

#line 11 "array.pcc"
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
