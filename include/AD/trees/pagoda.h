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

#ifndef pagodas_h
#define pagodas_h

///////////////////////////////////////////////////////////////////////////
// Class |Pagodas|.
// The algorithm implemented here is in Gonnet's\cite{Algorithms}.
///////////////////////////////////////////////////////////////////////////

#include <AD/trees/trees.h>

template <class K, class V>
class Pagoda : public BinaryTree<K,V>
{
  Pagoda(const Pagoda& p);

  TrNode<K,V> * merge_tree(TrNode<K,V> *, TrNode<K,V> *);

  ///////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////

public:
  Pagoda()
  {}
  ~Pagoda()
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
    BinaryTree<K,V>::error("Pagoda::remove");
  }
};

////////////////////////////////////////////////////////////////////////
// Implementation of the template methods
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//  The most basic operation of pagodas is merging two trees
/////////////////////////////////////////////////////////////////////////

template <class K, class V>
TrNode<K,V> * Pagoda<K,V>::merge_tree(TrNode<K,V> * a, TrNode<K,V> * b)
{
  if (a == 0)
    return b;
  if (b == 0)
    return a;
  TrNode<K,V> * bot_a, * bot_b, * r, * temp;
  bot_a = (TrNode<K,V>*)a->R;
  a->R = 0;
  bot_b = (TrNode<K,V>*)b->L;
  b->L = 0;
  r = 0;
  while (bot_a != 0 && bot_b != 0)
  {
    if (compare(bot_a->key, bot_b->key) > 0)
    {
      temp = (TrNode<K,V>*)bot_a->R;
      if (r == 0)
        bot_a->R = bot_a;
      else
      {
        bot_a->R = r->R;
        r->R = bot_a;
      }
      r = bot_a;
      bot_a = temp;
    }
    else
    {
      temp = (TrNode<K,V>*)bot_b->L;
      if (r == 0)
        bot_b->L = bot_b;
      else
      {
        bot_b->L = r->L;
        r->L = bot_b;
      }
      r = bot_b;
      bot_b = temp;
    }
  }
  if (bot_b == 0)
  {
    a->R = r->R;
    r->R = bot_a;
    return a;
  }
  else
  {
    b->L = r->L;
    r->L = bot_b;
    return b;
  }
}

/////////////////////////////////////////////////////////////////////////
// Pagoda insertion
/////////////////////////////////////////////////////////////////////////

template <class K, class V>
BinaryNode * Pagoda<K,V>::insert(const K& key, const V& value)
{
  TrNode<K,V> * P = new TrNode<K,V>(key,value);
  P->L = P;
  P->R = P;
  BinaryTree<K,V>::count++;
  BinaryTree<K,V>::tree_root = merge_tree((TrNode<K,V>*)BinaryTree<K,V>::tree_root,P);
  return P;
}

/////////////////////////////////////////////////////////////////////////
// Pagoda deletion
/////////////////////////////////////////////////////////////////////////

template <class K, class V>
Bool Pagoda<K,V>::delete_min()
{
  if (BinaryTree<K,V>::tree_root)
  {
    TrNode<K,V> * P = (TrNode<K,V>*)BinaryTree<K,V>::tree_root;
    BinaryNode * l, * r;
    if (P->L == P)
      l = 0;
    else
    {
      for (l = P->L; l->L != P; l = l->L)
        ;
      l->L = P->L;
    }
    if (P->R == P)
      r = 0;
    else
    {
      for (r = P->R; r->R != P; r = r->R)
        ;
      r->R = P->R;
    }
    BinaryTree<K,V>::tree_root = merge_tree((TrNode<K,V>*)l,(TrNode<K,V>*)r);
    BinaryTree<K,V>::count--;
    delete P;
    return true;
  }
  else
    return false;
}

#endif
