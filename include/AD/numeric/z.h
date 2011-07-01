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

#ifndef small_finite_cyclic_group_h
#define small_finite_cyclic_group_h

//
// Class Z<n> is used to simulate module arithmetic
// of a small finite cyclic group.
//

#include <AD/generic/generic.h>  // Generic definitions

template<unsigned int n>
class Z
{
  unsigned long x;

public:
  Z()
  {}
  Z(unsigned long y) : x(y)
  {}

  operator unsigned long () const
  {
    return x;
  }

  //
  // Operations
  //

  friend Z operator - (Z a)
  {
    return Z<n>(n - a);
  }
  friend Z operator + (Z a, Z b)
  {
    unsigned long sum = a.x + b.x;
    if (sum >= n)
      sum -= n;
    return Z<n>(sum);
  }
  friend Z operator * (Z a, Z b)
  {
    return Z<n>((a.x * b.x) % n);
  }
  friend Z operator - (Z a, Z b)
  {
    return Z<n>(a + (-b));
  }

  void operator += (Z a)
  {
    *this = *this + a;
  }
  void operator -= (Z a)
  {
    *this = *this - a;
  }
  void operator *= (Z a)
  {
    *this = *this * a;
  }

  //
  // Of course, division cannot be defined
  //

  //
  // Comparisons
  //
  friend Bool operator == (const Z a, const Z b)
  {
    return a.x == b.x;
  }
  friend Bool operator != (const Z a, const Z b)
  {
    return a.x != b.x;
  }
  friend Bool operator >  (const Z a, const Z b)
  {
    return a.x > b.x;
  }
  friend Bool operator <  (const Z a, const Z b)
  {
    return a.x < b.x;
  }
  friend Bool operator >= (const Z a, const Z b)
  {
    return a.x >= b.x;
  }
  friend Bool operator <= (const Z a, const Z b)
  {
    return a.x <= b.x;
  }
};

#endif
