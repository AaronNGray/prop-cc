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

#ifndef AVL_tree_based_set_h
#define AVL_tree_based_set_h

///////////////////////////////////////////////////////////////////////////
//  Class AVLSet<T> is a set of type T
//  implemented using an AVL tree.
///////////////////////////////////////////////////////////////////////////

#include <AD/contain/treeset.h>
#include <AD/trees/avl.h>

template <class T>
class AVLSet : public TreeSet< T, AVLTree<T,char> >
{
public:
  AVLSet()
  {}
  AVLSet(const Collection<T>& C) : TreeSet<T,AVLTree<T,char> >(C)
  {}
  AVLSet(const AVLSet<T>& s) : TreeSet<T,AVLTree<T,char> >(s)
  {}
  ~AVLSet()
  {}

  typedef TreeSet< T, AVLTree<T,char> > Super;
  typedef Super::Element                Element;
};

#endif
