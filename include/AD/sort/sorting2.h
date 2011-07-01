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

#ifndef sorting_base_class2_h
#define sorting_base_class2_h

#include <AD/generic/ordering.h>

/////////////////////////////////////////////////////////////////////////////
//  This abstract class represents a sorting algorithm parameterized by the
//  ordering and the array type.
/////////////////////////////////////////////////////////////////////////////

template <class K, class V, class Ord>
class Sorting2
{
public:
  Sorting2()
  {}
  virtual ~Sorting2()
  {}
  virtual void sort(int, K [], V []) = 0;
};

#endif
