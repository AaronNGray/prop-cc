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

#include <iostream>
#include <stdlib.h>
#include <AD/trees/trees.h>


////////////////////////////////////////////////////////////////////////////
// Deallocate all cells
////////////////////////////////////////////////////////////////////////////

void BasicTree::clear()
{
  Ix i, j;
  for (i = first(); i; i = j)
  {
    j = next(i);
    delete (BinaryNode*)i;
  }
  tree_root = 0;
  count = 0;
}

static void kill( BinaryNode* t)
{
  if (t->L)
    kill(t->L);
  if (t->R)
    kill(t->R);
  delete t;
}

void BasicTree::clear2()
{
  if (tree_root)
    kill(tree_root);
  tree_root = 0;
  count = 0;
}

////////////////////////////////////////////////////////////////////////////
//  Search for the leftmost and rightmost node of a tree, if any
////////////////////////////////////////////////////////////////////////////

BinaryNode* BasicTree::first() const
{
  register BinaryNode * tree = tree_root;
  if (tree)
    while (tree->L)
      tree = tree->L;
  return tree;
}

BinaryNode* BasicTree::last() const
{
  register BinaryNode * tree = tree_root;
  if (tree)
    while (tree->R)
      tree = tree->R;
  return tree;
}

////////////////////////////////////////////////////////////////////////////
//  Traverse the tree through threaded links
////////////////////////////////////////////////////////////////////////////

BinaryNode* BasicTree::next(Ix i) const
{
  register BinaryNode * A = (BinaryNode *)i;
  if (A->is_right_threaded())
    return A->R;
  for (A = A->R; ! A->is_left_threaded(); A = A->L)
    ;
  return A;
}

BinaryNode* BasicTree::prev(Ix i) const
{
  register BinaryNode * A = (BinaryNode *)i;
  if (A->is_left_threaded())
    return A->L;
  for (A = A->L; ! A->is_right_threaded(); A = A->R)
    ;
  return A;
}

////////////////////////////////////////////////////////////////////////////
//  Preorder successor and predecessor
////////////////////////////////////////////////////////////////////////////

BinaryNode* BasicTree::presucc(Ix i) const
{
  register BinaryNode * A = (BinaryNode *)i;
  if (! A->is_left_threaded())
    return A->L;
  while (A->is_right_threaded())
    A = A->R;
  return A ? A->R : 0;
}

BinaryNode* BasicTree::prepred(Ix i) const
{
  register BinaryNode * A = (BinaryNode *)i;
  if (! A->is_right_threaded())
    return A->R;
  while (A->is_left_threaded())
    A = A->L;
  return A ? A->L : 0;
}

////////////////////////////////////////////////////////////////////////////
//  Error reporting
////////////////////////////////////////////////////////////////////////////

void BasicTree::error( const char method[]) const
{
  std::cerr << "Invalid operation: " << method << '\n';
  exit(1);
}

////////////////////////////////////////////////////////////////////////////
//  Returns the nth element( from the left) or mth( from the right )
////////////////////////////////////////////////////////////////////////////

BinaryNode* BasicTree::nth(int i) const
{
  if (i < 0 || i >= count)
    return 0;
  if (i > count / 2)
    return mth(count - i - 1);
  BinaryNode * t;
  for (t = first(); t && i > 0; i--)
    t = next(t);
  return t;
}

BinaryNode* BasicTree::mth(int i) const
{
  if (i < 0 || i >= count)
    return 0;
  if (i > count / 2)
    return nth(count - i - 1);
  BinaryNode * t;
  for (t = last(); t && i > 0; i--)
    t = prev(t);
  return t;
}

////////////////////////////////////////////////////////////////////////////
//  Invariant checking
////////////////////////////////////////////////////////////////////////////

static int avl_check( const BinaryNode* n, Bool &ok)
{
  if (n == 0)
    return 0;
  int l_height = n->is_left_threaded() ? 0 : avl_check(n->L,ok);
  int r_height = n->is_right_threaded() ? 0 : avl_check(n->R,ok);
  int diff = l_height - r_height;
  if (diff > 1 || diff < -1 ||
      diff == 0  && ! n->is_balanced() ||
      diff == 1  && ! n->is_left_skewed() ||
      diff == -1 && ! n->is_right_skewed())
    ok = false;
  return 1 + (l_height > r_height ? l_height : r_height);
}

Bool BasicTree::avl_balanced() const
{
  Bool ok = true;
  avl_check(tree_root,ok);
  return ok;
}
