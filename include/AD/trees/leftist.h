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

#ifndef leftist_trees_h
#define leftist_trees_h

///////////////////////////////////////////////////////////////////////////
// Class |LeftistTree| can be used to implement priority queues
///////////////////////////////////////////////////////////////////////////

#include <AD/trees/trees.h>

///////////////////////////////////////////////////////////////////////////
//  Forward class declarations
///////////////////////////////////////////////////////////////////////////

template <class K, class V>
class LeftistNode;

template <class K, class V>
class LeftistTree;

///////////////////////////////////////////////////////////////////////////
//  A leftist node also holds the node distance
///////////////////////////////////////////////////////////////////////////

template <class K, class V>
class LeftistNode : public TrNode<K,V>
{
  int dist;
  friend class LeftistTree<K,V>;
public:
  LeftistNode(const K& k, const V& v) : dist(1), TrNode<K,V>(k,v)
  {}
  ~LeftistNode()
  {}
}
;

///////////////////////////////////////////////////////////////////////////
//  The tree class
///////////////////////////////////////////////////////////////////////////

template <class K, class V>
class LeftistTree : public BinaryTree<K,V>
{
  LeftistTree(const LeftistTree& p);
  LeftistNode<K,V> * leftist_union(LeftistNode<K,V> *, LeftistNode<K,V> *);

  ///////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////

public:
  LeftistTree()
  {}
  ~LeftistTree()
  {}

  ///////////////////////////////////////////////////////////////////
  //  New mutators
  ///////////////////////////////////////////////////////////////////
  void clear()
  {
    BinaryTree<K,V>::clear2();
  }
  BinaryNode * insert(const K&, const V&);
  BinaryNode * min() const
  {
    return BinaryTree<K,V>::tree_root;
  }
  Bool delete_min();
  Bool remove
    (const K&)
  {
    BinaryTree<K,V>::error("LeftistTree<K,V>::remove");
  }
};

////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//  Merge two leftist trees together
////////////////////////////////////////////////////////////////////////

template <class K, class V>
LeftistNode<K,V> *
LeftistTree<K,V>::leftist_union(LeftistNode<K,V>* A, LeftistNode<K,V>* B)
{
  /////////////////////////////////////////////////////////////////////
  // Base conditions
  /////////////////////////////////////////////////////////////////////
  if (A == 0)
    return B;
  if (B == 0)
    return A;
  /////////////////////////////////////////////////////////////////////
  //  Make sure the root is the smaller element
  /////////////////////////////////////////////////////////////////////
  if (compare(A->key, B->key) > 0)
  {
    LeftistNode<K,V> * C = A;
    A = B;
    B = C;
  }

  /////////////////////////////////////////////////////////////////////
  //  Now merge recursively
  /////////////////////////////////////////////////////////////////////
  A->R = leftist_union((LeftistNode<K,V>*)(A->R),B);

  /////////////////////////////////////////////////////////////////////
  //  Make sure the left side is taller; we're leftists.
  /////////////////////////////////////////////////////////////////////
  if (A == 0 || A->dist < ((LeftistNode<K,V>*)(A->R)
                          )->dist)
  {
    BinaryNode * t = A->L;
    A->L = A->R;
    A->R = t;
  }

  /////////////////////////////////////////////////////////////////////
  //  Finally, update the distance
  /////////////////////////////////////////////////////////////////////
  if (A->L == 0) A->dist = 1;
  else
  {
    int m = ((LeftistNode<K,V>*)A->L)->dist;
    int n = ((LeftistNode<K,V>*)A->R)->dist;
    A->dist = 1 + (m < n ? m : n);
  }
  return A;
}

////////////////////////////////////////////////////////////////////////
//  Tree insertion
////////////////////////////////////////////////////////////////////////

template <class K, class V>
BinaryNode * LeftistTree<K,V>::insert(const K& key, const V& value)
{
  LeftistNode<K,V> * P = new LeftistNode<K,V>(key,value);
  BinaryTree<K,V>::tree_root = leftist_union((LeftistNode<K,V>*)BinaryTree<K,V>::tree_root,P);
  BinaryTree<K,V>::count++;
  return P;
}

////////////////////////////////////////////////////////////////////////
//  Tree deletion
////////////////////////////////////////////////////////////////////////

template <class K, class V>
Bool LeftistTree<K,V>::delete_min()
{
  LeftistNode<K,V> * T = (LeftistNode<K,V>*)BinaryTree<K,V>::tree_root;
  if (T)
  {
    BinaryTree<K,V>::tree_root = leftist_union((LeftistNode<K,V>*)(T->L),
                                 (LeftistNode<K,V>*)(T->R));
    BinaryTree<K,V>::count--;
    delete T;
    return true;
  }
  else return false;
}

#endif
