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

#ifndef red_black_trees_h
#define red_black_trees_h

//////////////////////////////////////////////////////////////////////////////
//  Invariants:
//     (1) the number of black links from each path from the root to
//         a leaf is the same.
//     (2) no red links may be followed by another red link.
//////////////////////////////////////////////////////////////////////////////

#include <AD/trees/trees.h>

template <class K, class V>
class RBTree : public BinaryTree<K,V>
{

  TrNode<K,V> * split(const K&, TrNode<K,V> *, TrNode<K,V> *,
                      TrNode<K,V> *, TrNode<K,V> *);
  TrNode<K,V> * rotate(const K&, TrNode<K,V> *);

  ///////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////

public:
  RBTree()
  {}
  RBTree(RBTree& t)
  {
    *this = t;
  }
  ~RBTree()
  {}

  ///////////////////////////////////////////////////////////////////////
  // Assignment
  ///////////////////////////////////////////////////////////////////////
  // void operator = (RBTree&); // inherited

  ///////////////////////////////////////////////////////////////////////
  // Mutators
  ///////////////////////////////////////////////////////////////////////
  Ix   insert(const K&, const V&);
  Bool remove
    (const K&);

  ///////////////////////////////////////////////////////////////////////
  // Iterators
  ///////////////////////////////////////////////////////////////////////
  // inherited
};

/////////////////////////////////////////////////////////////////////////////
// Implementation of the template methods
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Tree insertion.
/////////////////////////////////////////////////////////////////////////////

template <class K, class V>
Ix RBTree<K,V>::insert(const K& key, const V& value)
{
  TrNode<K,V> * gg, * g, * p, * x;
  p = g = x = (TrNode<K,V>*)tree_root;
  for(;;)
  {
    gg = g;
    g = p;
    p = x;
    int r = compare(key,x->key);
    if (r == 0 && ! duplicates_allowed)
    {
      x->value = value;
      return;
    }
    if (r < 0)
      if (x->is_left_threaded())
        break;
      else
        x = (TrNode<K,V>*)x->L;
    else       if (x->is_right_threaded())
      break;
    else
      x = (TrNode<K,V>*)x->R;
    if (x == 0)
      break;
    if (x->thread() == No_thread && x->L->is_red() && x->R->is_red())
      x = split(key,gg,g,p,x);
  }
  count++;
  x = new TrNode<K,V> (key,value);
  if (r < 0)
    p->L = x;
  else
    p->R = x;
  x = split(key,gg,g,p,x);
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

template <class K, class V>
Bool RBTree<K,V>::remove
  (const K& key)
{}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

template <class K, class V>
TrNode<K,V> * RBTree<K,V>::split
(const K& key, TrNode<K,V> * gg,
 TrNode<K,V> * g, TrNode<K,V> * p, TrNode<K,V> * x)
{}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

template <class K, class V>
TrNode<K,V> * RBTree<K,V>::rotate(const K&, TrNode<K,V> *)
{
  TrNode<K,V> * c, * gc;
}

#endif
