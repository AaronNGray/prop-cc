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

#ifndef tree_based_container_class_h
#define tree_based_container_class_h

///////////////////////////////////////////////////////////////////////////
//  TreeContainer<K,V,T>:
//
//     A ``higher order'' class template to create a self-sufficient
//     container class from a tree datatype.
//
//  E.g.  TreeContainer<const char *, int, AVL<const char *, int> >
//        is a container type that implements a mapping from string
//        to integers using an AVL tree.
///////////////////////////////////////////////////////////////////////////

#include <AD/trees/trees.h>

//
// Main template
//

template <class K, class V, class T>
class TreeContainer : public T
{
  V def;     // Default value

public:
  TreeContainer(const V& v) : def(v)
  {}
  TreeContainer()
  {}

  V& min()
  {
    return T::min()->value();
  }
  V& max()
  {
    return T::max()->value();
  }
  const K& minKey()
  {
    return T::min()->key();
  }
  const K& maxKey()
  {
    return T::max()->key();
  }

  V& operator [] (const K& k);        // Looks up a value

  V * lookup (const K& k)             // Looks up a value
  {
    Node<K,V> * node = T::lookup(k);
    return node ? &node->value() : 0;
  }

  const K * lookupKey(const K& k)     // Looks up a key
  {
    Node<K,V> * node = T::lookup(k);
    return node ? &node->key() : 0;
  }
};

///////////////////////////////////////////////////////////////////////////
//
// Implementation of template methods
//
///////////////////////////////////////////////////////////////////////////

//
// Lookup a value, inserts default value if key does not exist
//

template <class K, class V, class T>
V& TreeContainer<K,V,T>::operator [] (const K& k)
{
  Node<K,V> * node = T::lookup(k);
  if (node)
    return node->value();
  else
  {
    insert(k,def);
    return T::lookup(k)->value();
  }
}

#endif
