//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef basic_tree_operations_h
#define basic_tree_operations_h

///////////////////////////////////////////////////////////////////////////
//  This file factors out some of the most common operations on trees
///////////////////////////////////////////////////////////////////////////

#include <AD/generic/ordering.h>

///////////////////////////////////////////////////////////////////////////
//  Class |BinaryNode| is not useful by itself but is used to encapsulate
//  some of the node pointer manipulations.
//  All binary tree nodes are ``threaded'' to make iteration easy.
//  Threading refers to the practice of adding ``threading'' links from
//  leaf nodes to internal nodes that are adjacent in an inorder traversal.
///////////////////////////////////////////////////////////////////////////

struct BinaryNode
{

  BinaryNode * L, * R;  // Left and right child of tree
  enum Status { // Needed for threading
    No_thread      = 0,
    Left_thread    = 1,
    Right_thread   = 2,
    Both_threads   = 3,
    Thread_mask    = 3,
    // Needed for AVL trees, not used in others
    Balanced       = 0,
    Left_skewed    = 4,
    Right_skewed   = 8,
    Balance_mask   = 12,
    // Needed for red-black trees, not used in others
    Red            = 4,
    Black          = 0
  };
  short status;

  ///////////////////////////////////////////////////////////////////////
  // Constructor and destructors
  ///////////////////////////////////////////////////////////////////////

public:
  inline BinaryNode
  (BinaryNode * l = 0, BinaryNode * r = 0, int st = Both_threads)
      : L(l), R(r), status(st)
  {}
  inline virtual ~BinaryNode() {}

  ///////////////////////////////////////////////////////////////////////
  // Threading and tree traversal operations.
  ///////////////////////////////////////////////////////////////////////
  inline Bool is_left_threaded()  const
  {
    return status & Left_thread;
  }
  inline Bool is_right_threaded() const
  {
    return status & Right_thread;
  }
  inline Status thread()          const
  {
    return (Status)(status & Thread_mask);
  }
  inline void set_lthread()
  {
    status |= Left_thread;
  }
  inline void set_rthread()
  {
    status |= Right_thread;
  }
  inline void clear_lthread()
  {
    status &= ~Left_thread;
  }
  inline void clear_rthread()
  {
    status &= ~Right_thread;
  }

  ///////////////////////////////////////////////////////////////////////
  // Tree balancing operations
  ///////////////////////////////////////////////////////////////////////
  inline Status balance() const
  {
    return (Status)(status & Balance_mask);
  }
  inline Bool   is_balanced() const
  {
    return (status & Balance_mask) == 0;
  }
  inline Bool   is_left_skewed() const
  {
    return status & Left_skewed;
  }
  inline Bool   is_right_skewed() const
  {
    return status & Right_skewed;
  }
  inline void   set_balanced()
  {
    status = (status&~Balance_mask) | Balanced;
  }
  inline void   set_left_skewed()
  {
    status = (status&~Balance_mask) | Left_skewed;
  }
  inline void   set_right_skewed()
  {
    status = (status&~Balance_mask) | Right_skewed;
  }

  inline Bool   is_red() const
  {
    return (status & Red);
  }
  inline void   set_red()
  {
    status |= Red;
  }
  inline void   set_black()
  {
    status &= ~Red;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Tree rotation
  ///////////////////////////////////////////////////////////////////////
  friend BinaryNode * lrot(BinaryNode *);
  friend BinaryNode * rrot(BinaryNode *);
};

///////////////////////////////////////////////////////////////////////
// Class |TrNode| is similarly nonusefully by itself.  This class is
// used to enscapsulated some of the node operations involving key
// comparisons
///////////////////////////////////////////////////////////////////////
template <class K, class V>
struct TrNode : public BinaryNode
{

  K key;
  V value;  // Keys and values

public:

  ///////////////////////////////////////////////////////////////////////
  // Constructor and destructors
  ///////////////////////////////////////////////////////////////////////
  TrNode(const K& k, const V& v,
         BinaryNode * l = 0, BinaryNode * r = 0, int st = Both_threads)
      : key(k), value(v), BinaryNode(l,r,st)
  {}
}
;

///////////////////////////////////////////////////////////////////////
//  Base class for binary trees
///////////////////////////////////////////////////////////////////////
class BasicTree
{
protected:

  typedef BinaryNode::Status Status; // import type

  BinaryNode * tree_root;            // root of the tree
  int          count;                // number of nodes within the tree
  Bool         duplicates_allowed;   // do we allow duplicated keys?

  void clear2();

public:
  ///////////////////////////////////////////////////////////////
  // Constructors and destructor
  ///////////////////////////////////////////////////////////////
  inline BasicTree() : tree_root(0), count(0), duplicates_allowed(false)
  {}
  inline virtual ~BasicTree()
  {
    clear();
  }

  ///////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////
  inline int  size()      const
  {
    return count;
  }
  inline int  capacity()  const
  {
    return count;
  }
  inline Bool is_empty()  const
  {
    return count == 0;
  }
  inline Bool is_full()   const
  {
    return false;
  }

  ///////////////////////////////////////////////////////////////
  // Mutators
  ///////////////////////////////////////////////////////////////
  virtual void clear();

  ///////////////////////////////////////////////////////////////
  // Iterators
  ///////////////////////////////////////////////////////////////
  BinaryNode * first()       const; // get leftmost node, if any
  BinaryNode * last()        const; // get rightmost node, if any
  BinaryNode * nth(int i)    const; // get nth node from the left
  BinaryNode * mth(int i)    const; // get mth node from the right
  BinaryNode * next(Ix i)    const; // get next inorder node
  BinaryNode * prev(Ix i)    const; // get previous inorder node
  BinaryNode * root()        const
  {
    return tree_root;
  } // get root of tree
  BinaryNode * presucc(Ix i) const; // preorder successor
  BinaryNode * prepred(Ix i) const; // preorder predecessor
  BinaryNode * left(Ix i)    const; // left branch
  BinaryNode * right(Ix i)   const; // right branch

  ///////////////////////////////////////////////////////////////
  // Invariant checking
  ///////////////////////////////////////////////////////////////
  Bool avl_balanced() const; // Is it an AVL tree?

protected:

  void error(const char []) const;  // error reporting
};

///////////////////////////////////////////////////////////////////////
//  Class |BinaryTree| encapsulates some of the common operations
//  on binary search trees: for example, operations such as searching
//  and traversal are the same on all binary trees; only operations
//  such as insertion and deletion differ.
///////////////////////////////////////////////////////////////////////

template <class K, class V>
class BinaryTree : public BasicTree
{
  BinaryTree(const BinaryTree&);
public:

  ///////////////////////////////////////////////////////////////
  // Constructors and destructor
  ///////////////////////////////////////////////////////////////
  inline  BinaryTree()
  {}
  //       BinaryTree(const BinaryTree&);
  inline ~BinaryTree()
  {}

  ///////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////
  // int  size()      const; // inherited
  // int  capacity()  const; // inherited
  // Bool is_empty()   const; // inherited
  // Bool is_full()    const; // inherited
  virtual BinaryNode * lookup(const K& k) const;
  inline Bool contains(const K& k) const
  {
    return lookup(k) != 0;
  }

  ///////////////////////////////////////////////////////////////
  // Mutators
  ///////////////////////////////////////////////////////////////
  // void      clear(); // inherited
  virtual BinaryNode * insert(const K&, const V&) = 0;
  virtual Bool remove
    (const K&) = 0;
  inline virtual Bool delete_min()
  {
    Ix i;
    return (i = first()) ? remove
             (key(i)) : false;
  }
  void operator = (const BinaryTree<K,V>& t);

  ///////////////////////////////////////////////////////////////
  // Iterators
  ///////////////////////////////////////////////////////////////
  // BinaryNode * first()     const; // inherited
  // BinaryNode * last()      const; // inherited
  // BinaryNode * nth(int i)  const; // inherited
  // BinaryNode * mth(int i)  const; // inherited
  // BinaryNode * next(Ix i)  const; // inherited
  // BinaryNode * prev(Ix i)  const; // inherited
  inline const K& key(Ix i)   const
  {
    return ((TrNode<K,V>*)i)->key;
  }
  inline       K& key(Ix i)
  {
    return ((TrNode<K,V>*)i)->key;
  }
  inline const V& value(Ix i) const
  {
    return ((TrNode<K,V>*)i)->value;
  }
  inline       V& value(Ix i)
  {
    return ((TrNode<K,V>*)i)->value;
  }
};

///////////////////////////////////////////////////////////////////////
// Iterator macros:
//
//    foreach_inorder(i,T)           --- inorder traversal
//    foreach_reverse_inorder(i,T)   --- inorder traversal but in reverse
//    foreach_preorder(i,T)          --- preorder traversal
//    foreach_reverse_preorder(i,T)  --- preorder traversal but in reverse
//
///////////////////////////////////////////////////////////////////////

#define foreach_inorder(i,T)          for(i = (T).first(); i; i = (T).next(i))
#define foreach_reverse_inorder(i,T)  for(i = (T).last(); i; i = (T).prev(i))
#define foreach_preorder(i,T)         for(i = (T).root(); i; i = (T).presucc(i))
#define foreach_reverse_preorder(i,T) for(i = (T).root(); i; i = (T).prepred(i))

///////////////////////////////////////////////////////////////////////
// Implementation of template methods
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  Tree rotation
///////////////////////////////////////////////////////////////////////

inline BinaryNode * lrot(register BinaryNode * T)
{
  BinaryNode * R = T->R;
  if (R->is_left_threaded())
  {
    T->R = R;
    T->set_rthread();
    R->clear_lthread();
  }
  else
  {
    T->R = R->L;
  }
  R->L = T;
  T = R;
  return T;
}

inline BinaryNode * rrot(BinaryNode * T)
{
  BinaryNode * L = T->L;
  if (L->is_right_threaded())
  {
    T->L = L;
    T->set_lthread();
    L->clear_rthread();
  }
  else
  {
    T->L = L->R;
  }
  L->R = T;
  T = L;
  return T;
}

///////////////////////////////////////////////////////////////////////
//  Left and right branches of a tree
///////////////////////////////////////////////////////////////////////

inline BinaryNode * BasicTree::left(Ix i) const
{
  return ((BinaryNode*)i)->is_left_threaded() ? 0 : ((BinaryNode*)i)->L;
}
inline BinaryNode * BasicTree::right(Ix i) const
{
  return ((BinaryNode*)i)->is_right_threaded() ? 0 : ((BinaryNode*)i)->R;
}

///////////////////////////////////////////////////////////////////////
// Assignment
///////////////////////////////////////////////////////////////////////

template <class K, class V>
void BinaryTree<K,V>::operator = (const BinaryTree<K,V>& T)
{
  if (&T != this)
  {
    clear();
    for (Ix ix = T.first(); ix; ix = T.next(ix))
      insert(T.key(ix), T.value(ix));
  }
}

///////////////////////////////////////////////////////////////////////
//  Searching for a key
///////////////////////////////////////////////////////////////////////

template <class K, class V>
BinaryNode * BinaryTree<K,V>::lookup(const K& key) const
{
  register TrNode<K,V> * tree = (TrNode<K,V>*)tree_root;
  while (tree)
  {
    int r = compare(key,tree->key);
    if (r == 0)
      return tree;
    if (r < 0)
      if (tree->is_left_threaded())
        return 0;
      else
        tree = (TrNode<K,V>*)tree->L;
    else
      if (tree->is_right_threaded())
        return 0;
      else
        tree = (TrNode<K,V>*)tree->R;
  }
  return 0;
}

#endif
