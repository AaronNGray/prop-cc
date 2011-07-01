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

#ifndef red_black_tree_based_bag_h
#define red_black_tree_based_bag_h

///////////////////////////////////////////////////////////////////////////
//  Class RBBag<T> is a multiset of type T
//  implemented using a red_black tree.
///////////////////////////////////////////////////////////////////////////

#include <AD/contain/treebag.h>
#include <AD/trees/redblack.h>

template <class T>
class RBBag : public TreeBag< T, RBTree<T,int> >
{
public:
  RBBag()
  {}
  RBBag(const Bag<T>& b) : TreeBag<T,RBTree<T,int> >(b)
  {}
  RBBag(const RBBag<T>& b) : TreeBag<T,RBTree<T,int> >(b)
  {}
  ~RBBag()
  {}

  typedef TreeBag<T, RBTree<T,int> > Super;
  typedef Super::Element             Element;
};

#endif
