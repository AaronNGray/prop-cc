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

#ifndef avl_trees_h
#define avl_trees_h

//////////////////////////////////////////////////////////////////////////
//  Class |AVLTree| implements AVL tree\cite{AVL, Algorithms, LD-19988},
//  a binary height balanced tree such that the difference in height
//  between left and right branches is at most 1.
//////////////////////////////////////////////////////////////////////////

#include <AD/trees/trees.h>

//////////////////////////////////////////////////////////////////////////////
//  Class |AVLTree|
//////////////////////////////////////////////////////////////////////////////

template <class K, class V>
class AVLTree : public BinaryTree<K,V>
{
  AVLTree (const AVLTree& avl);

  enum { N, L, R };
  Bool ins(TrNode<K,V> * &, const K&, const V&);
  Bool rmv(int, BinaryNode *, TrNode<K,V> * &, const K *);

  TrNode<K,V> * target;

  /////////////////////////////////////////////////////////////////////
  // Auxiliary height balancing routines
  /////////////////////////////////////////////////////////////////////
  friend BinaryNode * avl_balance_right(BinaryNode * T, Bool&);
  friend BinaryNode * avl_balance_left(BinaryNode * T, Bool&);

  /////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  /////////////////////////////////////////////////////////////////////

public:
  AVLTree ()
  {}
  //AVLTree (const AVLTree& avl) : BinaryTree<K,V>(avl) {}
  ~AVLTree ()
  {}

  /////////////////////////////////////////////////////////////////////
  // New mutators
  /////////////////////////////////////////////////////////////////////
  inline BinaryNode * insert(const K& k, const V& v)
  {
    ins((TrNode<K,V> * &)BinaryTree<K,V>::tree_root,k,v);
    return target;
  }
  inline Bool remove
    (const K& k)
  {
    int cnt = BinaryTree<K,V>::count;
    rmv(N,0,(TrNode<K,V> * &)BinaryTree<K,V>::tree_root,&k);
    return cnt != BinaryTree<K,V>::count;
  }
};

//////////////////////////////////////////////////////////////////////////////
// Implementation of the template methods
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Insertion procedure.
// Comment: although AVL trees are theoretically important, they are really not
// that practical since the overhead for balancing is, in practice, quite
// high, and perhaps more importantly, it is not trivial to code.
//
// \cite{LD-1988} describes a technique in which only constant rather
// than $O(\log n)$ space overhead is needed.  But the technique requires
// in the worst case twice the key comparisons.  I judge this to be
// unreasonable, since we may have complex keys.
//
// Note: as a result; the routine returns true if the height of the
// subtree has increased.
//////////////////////////////////////////////////////////////////////////////

template <class K, class V>
Bool AVLTree<K,V>::ins(TrNode<K,V> *& T, const K& key, const V& value)
{
  if (T == 0)
  {
    //////////////////////////////////////////////////////////
    //  Trivial case
    //////////////////////////////////////////////////////////
    BinaryTree<K,V>::count++;
    T = target = new TrNode<K,V>(key,value);
    return true;
  }
  else
  {
    //////////////////////////////////////////////////////////
    // Compare key and recurse if necessary
    //////////////////////////////////////////////////////////
    int r = compare(key,T->key);
    if (r == 0 && ! BinaryTree<K,V>::duplicates_allowed)
    {
      target = T;
      T->value = value;
      return false;
    }
    Bool rebalance;
    if (r >= 0)
    {
      ///////////////////////////////////////////////////////
      // recurse on the right
      ///////////////////////////////////////////////////////
      if (T->is_right_threaded())
      {
        T->R = target = new TrNode<K,V>(key,value,T,T->R);
        T->clear_rthread();
        BinaryTree<K,V>::count++;
        rebalance = true;
      }
      else
      {
        rebalance = ins((TrNode<K,V> *&)T->R,key,value);
      }
      ///////////////////////////////////////////////////////
      // Rebalance tree if necessary
      ///////////////////////////////////////////////////////
      if (rebalance)
      {
        switch (T->balance())
        {
        case BinaryNode::Balanced:
          T->set_right_skewed();
          return true;
        case BinaryNode::Left_skewed:
          T->set_balanced();
          return false;
        case BinaryNode::Right_skewed:
          {
            Bool b;
            T = (TrNode<K,V>*)avl_balance_right(T,b);
            return false;
          }
        }
      }
      return false;
    }
    else
    {
      ///////////////////////////////////////////////////////
      // recurse on the left
      ///////////////////////////////////////////////////////
      if (T->is_left_threaded())
      {
        T->L = target = new TrNode<K,V>(key,value,T->L,T);
        T->clear_lthread();
        BinaryTree<K,V>::count++;
        rebalance = true;
      }
      else
      {
        rebalance = ins((TrNode<K,V> *&)T->L,key,value);
      }
      ///////////////////////////////////////////////////////
      // Rebalance tree if necessary
      ///////////////////////////////////////////////////////
      if (rebalance)
      {
        switch (T->balance())
        {
        case BinaryNode::Balanced:
          T->set_left_skewed();
          return true;
        case BinaryNode::Right_skewed:
          T->set_balanced();
          return false;
        case BinaryNode::Left_skewed:
          {
            Bool b;
            T = (TrNode<K,V>*)avl_balance_left(T,b);
            return false;
          }
        }
      }
      return false;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
// Deletion:
// Routine rmv() will return true if the the subtree has shrunk in height.
//////////////////////////////////////////////////////////////////////////////

template <class K, class V>
Bool AVLTree<K,V>::rmv
(int dir, BinaryNode * S, TrNode<K,V> *& T, const K * key)
{
  if (T == 0)
    return false;
  int r = compare(*key,T->key);
  if (r == 0)
  { // found key
    //////////////////////////////////////////////////////////////////
    // Node deletion strategy:
    //   If at least one of the child is empty, just adjust the
    // the thread links.   Otherwise, we move the inorder successor
    // over and delete the inorder successor instead.
    //////////////////////////////////////////////////////////////////
    BinaryNode * t = T;
    TrNode<K,V> * r = (TrNode<K,V>*)BinaryTree<K,V>::next(t);
    switch (T->thread())
    {
    case BinaryNode::No_thread:
      {
        T->key = r->key;
        T->value = r->value;
        key = &r->key;
        goto delete_right_side;
      }
    case BinaryNode::Left_thread:
      T = (TrNode<K,V>*)T->R;
      break;
    case BinaryNode::Right_thread:
      T = (TrNode<K,V>*)T->L;
      break;
    case BinaryNode::Both_threads:
      if (dir == L)
      {
        S->set_lthread();
        T = (TrNode<K,V>*)T->L;
      }
      else if (dir == R)
      {
        S->set_rthread();
        T = (TrNode<K,V>*)T->R;
      }
      else
      {
        T = 0;
      }
      break;
    }
    //////////////////////////////////////////////////////////////////
    // Unlink threads
    //////////////////////////////////////////////////////////////////
    BinaryNode * l = (BinaryNode*)BinaryTree<K,V>::prev(t);
    if (l)
      l->R = r;
    if (r)
      r->L = l;
    BinaryTree<K,V>::count--;
    delete t;
    return true;
  }
  else if (r > 0)
  { // try right branch
    if (T->is_right_threaded())
      return false;
delete_right_side:
    if (rmv(R,T,(TrNode<K,V>*&)T->R, key)
       )
    {
      switch (T->balance())
      {
      case BinaryNode::Balanced:
        T->set_left_skewed();
        break;
      case BinaryNode::Right_skewed:
        T->set_balanced();
        return true;
      case BinaryNode::Left_skewed:
        {
          Bool b;
          T = (TrNode<K,V>*)avl_balance_left(T,b);
          return b;
        }
      }
    }
    return false;
  }
  else
  {            // try left branch
    if (T->is_left_threaded())
      return false;
    if (rmv(L,T,(TrNode<K,V>*&)T->L, key)
       )
    {
      switch (T->balance())
      {
      case BinaryNode::Balanced:
        T->set_right_skewed();
        break;
      case BinaryNode::Left_skewed:
        T->set_balanced();
        return true;
      case BinaryNode::Right_skewed:
        {
          Bool b;
          T = (TrNode<K,V>*)avl_balance_right(T,b);
          return b;
        }
      }
    }
    return false;
  }
}

#endif
