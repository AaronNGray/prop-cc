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

#ifndef splay_trees_h
#define splay_trees_h

/////////////////////////////////////////////////////////////////////////////
//  Class |SplayTree| implements, of course, splay trees.  Splay trees
//  are due to Sleator and Tarjan (JACM 1985.)
/////////////////////////////////////////////////////////////////////////////
#include <AD/trees/trees.h>

template <class K, class V>
class SplayTree : public BinaryTree<K,V>
{
  SplayTree(const SplayTree& t);

  Bool found;         // have we found the key???
  int  last_compare;  // last comparison result
  TrNode<K,V> * P;    // target of splaying

  enum Direction { N, L, R };
  int           splay (int, TrNode<K,V> *&, const K&, Bool inf = false);
  TrNode<K,V> * concat(TrNode<K,V> *, TrNode<K,V> *);

public:

  ////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  ////////////////////////////////////////////////////////////////////
  inline  SplayTree()
  {}
  inline ~SplayTree()
  {}

  ////////////////////////////////////////////////////////////////////
  // New mutators
  ////////////////////////////////////////////////////////////////////
  BinaryNode * lookup(const K&) const;
  BinaryNode * insert(const K&, const V&);
  Bool remove
    (const K&);
};

//////////////////////////////////////////////////////////////////////////
//  Implemetation of the template methods
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//  Lookup a key
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
BinaryNode * SplayTree<K,V>::lookup(const K& key) const
{  ////////////////////////////////////////////////////////////////////
  // Get around the fact that lookup() is a const member function
  ////////////////////////////////////////////////////////////////////
  SplayTree<K,V> * self = (SplayTree<K,V> *)this;

  self->found = false;
  self->splay(N,(TrNode<K,V>*&)self->tree_root,key);
  self->tree_root = P;
  return found ? BinaryTree<K,V>::tree_root : 0;
}

//////////////////////////////////////////////////////////////////////////
//  Insert a key
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
BinaryNode * SplayTree<K,V>::insert(const K& key, const V& value)
{
  found = false;
  splay(N,(TrNode<K,V> *&)BinaryTree<K,V>::tree_root,key);
  if (found)
  {
    P->value = value;
    BinaryTree<K,V>::tree_root = P;
    return P;
  }
  else
  {
    TrNode<K,V> * T = new TrNode<K,V>(key,value);
    if (P)
    {
      if (last_compare > 0)
      {  // new cell to the right
        if (! P->is_right_threaded())
        {
          T->R = P->R;
          T->clear_rthread();
          P->set_rthread();
          BinaryNode * R;
          for (R = P->R; ! R->is_left_threaded(); R = R->L)
            ;
          R->set_lthread();
          R->L = T;
        }
        T->clear_lthread();
        T->L = P;
        P->R = T;
      }
      else
      {                 // new cell to the left
        if (! P->is_left_threaded())
        {
          T->L = P->L;
          T->clear_lthread();
          P->set_lthread();
          BinaryNode * L;
          for (L = P->L; ! L->is_right_threaded(); L = L->R)
            ;
          L->set_rthread();
          L->R = T;
        }
        T->clear_rthread();
        T->R = P;
        P->L = T;
      }
    }
    BinaryTree<K,V>::tree_root = T;
    BinaryTree<K,V>::count++;
    return T;
  }
}

//////////////////////////////////////////////////////////////////////////
// Delete a key
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
Bool SplayTree<K,V>::remove
  (const K& key)
{
  found = false;
  splay(N,(TrNode<K,V>*&)BinaryTree<K,V>::tree_root,key);
  if (! found)
    return false;
  //////////////////////////////////////////////////////////
  // Unlink threads
  //////////////////////////////////////////////////////////
  BinaryNode * L = (BinaryNode*)prev(P);
  BinaryNode * R = (BinaryNode*)next(P);
  if (L)
    L->R = R;
  if (R)
    R->L = L;
  //////////////////////////////////////////////////////////
  // remove node
  //////////////////////////////////////////////////////////
  L = P->L;
  R = P->R;
  delete P;
  //////////////////////////////////////////////////////////
  // Splay left side to make right child nil
  //////////////////////////////////////////////////////////
  if (L == 0)
    BinaryTree<K,V>::tree_root = R;
  else if (R == 0)
    BinaryTree<K,V>::tree_root = L;
  else
  {
    splay(N,(TrNode<K,V>*&)L,key,true);
    L->clear_rthread();
    L->R = R;
    BinaryTree<K,V>::tree_root = L;
  }
  BinaryTree<K,V>::count--;
  return true;
}

//////////////////////////////////////////////////////////////////////////
//  Splay a tree.
//
//  As usually, the bookkeeping due to threading makes things a bit more
//  complicated.  But it is still a lot simpler than height balanced trees.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
int SplayTree<K,V>::splay(int d, TrNode<K,V> *& T, const K& key, Bool inf)
{
  if (T == 0)
  {
    P = T;
    return N;
  }
  int r = inf ? 1 : compare(key,T->key);
  if (r == 0)
  {
    found = true;
    last_compare = r;
    P = T;
    return N;
  }
  if (r > 0)
  {
    if (T->is_right_threaded())
    {
      last_compare = r;
      P = T;
      return N;
    }
    switch (splay(R,(TrNode<K,V>*&)T->R,key,inf)
           )
    {
    case N:
      if (d == N)
      {
        T = (TrNode<K,V>*)lrot(T);
        return N;
      }
      else
        return R;
    case R:
      T = (TrNode<K,V>*)lrot(T);
      T = (TrNode<K,V>*)lrot(T);
      return N;
    case L:
      T->R = (TrNode<K,V> *)rrot(T->R);
      T = (TrNode<K,V> *)lrot(T);
      return N;
    }
  }
  else
  {
    if (T->is_left_threaded())
    {
      last_compare = r;
      P = T;
      return N;
    }
    switch (splay(L,(TrNode<K,V>*&)T->L,key,inf)
           )
    {
    case N:
      if (d == N)
      {
        T = (TrNode<K,V>*)rrot(T);
        return N;
      }
      else
        return L;
    case L:
      T = (TrNode<K,V>*)rrot(T);
      T = (TrNode<K,V>*)rrot(T);
      return N;
    case R:
      T->L = (TrNode<K,V>*)lrot(T->L);
      T = (TrNode<K,V>*)rrot(T);
      return N;
    }
  }
  return d;
}

#endif
