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

#ifndef AVL_tree_based_map_h
#define AVL_tree_based_map_h

///////////////////////////////////////////////////////////////////////////
//  Class AVLMap<K,V> is an associative table from type K to type V
//  implemented using an AVL tree.
///////////////////////////////////////////////////////////////////////////

#include <AD/contain/treemap.h>
#include <AD/trees/avl.h>

template <class K, class V>
class AVLMap : public TreeMap< K, V, AVLTree<K,V> >
{
public:
  AVLMap()
  {}
  AVLMap(const Map<K,V>& m) : TreeMap<K,V,AVLTree<K,V> >(m)
  {}
  AVLMap(const AVLMap<K,V>& m) : TreeMap<K,V,AVLTree<K,V> >(m)
  {}
  ~AVLMap()
  {}

  typedef TreeMap< K, V, AVLTree<K,V> > Super;
  typedef Super::Key                    Key;
  typedef Super::Value                  Value;
  typedef Super::Element                Element;
};

#endif
