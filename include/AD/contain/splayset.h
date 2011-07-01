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

#ifndef splay_tree_based_set_h
#define splay_tree_based_set_h

///////////////////////////////////////////////////////////////////////////
//  Class SplaySet<T> is a set of type T
//  implemented using a splay tree.
///////////////////////////////////////////////////////////////////////////
#include <AD/contain/treeset.h>
#include <AD/trees/splay.h>

template <class T>
class SplaySet : public TreeSet< T, SplayTree<T,char> >
{
public:
  SplaySet()
  {}
  SplaySet(const Collection<T>& C) : TreeSet<T,SplayTree<T,char> >(C)
  {}
  SplaySet(const SplaySet<T>& C) : TreeSet<T,SplayTree<T,char> >(C)
  {}
  ~SplaySet()
  {}

  typedef TreeSet< T, SplayTree<T, char> > Super;
  typedef Super::Element                   Element;
};

#endif
