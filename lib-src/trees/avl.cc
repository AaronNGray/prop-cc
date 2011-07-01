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

#include <AD/trees/avl.h>

//////////////////////////////////////////////////////////////////////////////
// Balance a right skewed tree: (assume h(R) - h(X) = 2)
// case (1)
//     T              R
//    / \            / \
//   X   R     =>   T   Z
//        \        / .
//         Z      X   R
//  R lthreaded   T rthreaded -> R
//
// case (2)
//     T             R
//    / \           / \           R is not lthreaded
//   X   R     =>  T   Z
//      / \       / \
//     Y   Z     X   Y
//
// case (3)
//     T                S
//    / \             /   \
//   X   R     =>    T     R
//      / \         / \   / \
//     S   Z       X   A B   Z
//    / \
//   A   B
//
// returns true if the tree has decreased in height
//////////////////////////////////////////////////////////////////////////////

BinaryNode* avl_balance_right( BinaryNode* T, Bool& b)
{
  BinaryNode * R = T->R;
  switch (R->balance())
  {
  case BinaryNode::Right_skewed:
    // do single left rotation
    if (R->is_left_threaded())
    { // R is left threaded??
      T->R = R;
      T->set_rthread();
      R->clear_lthread();
    }
    else
    {
      T->R = R->L;
    }
    T->set_balanced();
    R->set_balanced();
    R->L = T;
    T = R;
    b = true;
    return T;
  case BinaryNode::Balanced:
    // do single left rotation
    if (R->is_left_threaded())
    { // R is left threaded??
      T->R = R;
      T->set_rthread();
      R->clear_lthread();
    }
    else
    {
      T->R = R->L;
    }
    T->set_right_skewed();
    R->set_left_skewed();
    R->L = T;
    T = R;
    b = false;
    return T;
  case BinaryNode::Left_skewed:
    {
      BinaryNode * S = R->L;
      if (S->is_left_threaded())
      {
        T->R = S;
        T->set_rthread();
        S->clear_lthread();
      }
      else
      {
        T->R = S->L;
      }
      if (S->is_right_threaded())
      {
        R->L = S;
        R->set_lthread();
        S->clear_rthread();
      }
      else
      {
        R->L = S->R;
      }
      S->L = T;
      S->R = R;
      switch (S->balance())
      {
      case BinaryNode::Balanced:
        T->set_balanced();
        R->set_balanced();
        break;
      case BinaryNode::Left_skewed:
        R->set_right_skewed();
        T->set_balanced();
        break;
      case BinaryNode::Right_skewed:
        T->set_left_skewed();
        R->set_balanced();
        break;
      default:
        break;
      }
      S->set_balanced();
      T = S;
      b = true;
      return T;
    }
  default:
    break;
  }
  b =  false;
  return T;
}

//////////////////////////////////////////////////////////////////////////////
//  A symmetric case of above
//////////////////////////////////////////////////////////////////////////////

BinaryNode* avl_balance_left( BinaryNode* T, Bool& b)
{
  BinaryNode * L = T->L;
  switch (L->balance())
  {
  case BinaryNode::Left_skewed:
    // do single right rotation
    if (L->is_right_threaded())
    { // L is right threaded??
      T->L = L;
      T->set_lthread();
      L->clear_rthread();
    }
    else
    {
      T->L = L->R;
    }
    T->set_balanced();
    L->set_balanced();
    L->R = T;
    T = L;
    b = true;
    return T;
  case BinaryNode::Balanced:
    // do single right rotation
    if (L->is_right_threaded())
    { // L is right threaded??
      T->L = L;
      T->set_lthread();
      L->clear_rthread();
    }
    else
    {
      T->L = L->R;
    }
    T->set_left_skewed();
    L->set_right_skewed();
    L->R = T;
    T = L;
    b = false;
    return T;
  case BinaryNode::Right_skewed:
    {
      BinaryNode * S = L->R;
      if (S->is_right_threaded())
      {
        T->L = S;
        T->set_lthread();
        S->clear_rthread();
      }
      else
      {
        T->L = S->R;
      }
      if (S->is_left_threaded())
      {
        L->R = S;
        L->set_rthread();
        S->clear_lthread();
      }
      else
      {
        L->R = S->L;
      }
      S->R = T;
      S->L = L;
      switch (S->balance())
      {
      case BinaryNode::Balanced:
        T->set_balanced();
        L->set_balanced();
        break;
      case BinaryNode::Left_skewed:
        T->set_right_skewed();
        L->set_balanced();
        break;
      case BinaryNode::Right_skewed:
        L->set_left_skewed();
        T->set_balanced();
        break;
      default:
        break;
      }
      S->set_balanced();
      T = S;
      b = true;
      return T;
    }
  default:
    break;
  }
  b = false;
  return T;
}
