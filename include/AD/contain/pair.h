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

#ifndef pair_h
#define pair_h

#include <AD/generic/ordering.h>

//////////////////////////////////////////////////////////////////////////////
//  This is a simple type to represent a pair of objects.
//////////////////////////////////////////////////////////////////////////////

template <class A, class B>
class Pair
{
  A x;
  B y;

  ////////////////////////////////////////////////////////////////////////
  // Constructors
  ////////////////////////////////////////////////////////////////////////

public:
  Pair()
  {}
  Pair(const A& a, const B& b) : x(a), y(b)
  {}

  ////////////////////////////////////////////////////////////////////////
  // Selectors
  ////////////////////////////////////////////////////////////////////////

  inline const A& first() const
  {
    return x;
  }

  inline A& first()
  {
    return x;
  }

  inline const B& second() const
  {
    return y;
  }

  inline B& second()
  {
    return y;
  }

  inline const A& fst() const
  {
    return x;
  }

  inline A& fst()
  {
    return x;
  }

  inline const B& snd() const
  {
    return y;
  }

  inline B& snd()
  {
    return y;
  }

  ////////////////////////////////////////////////////////////////////////
  // Equality and hashing functions
  ////////////////////////////////////////////////////////////////////////

  inline friend Bool equal( const Pair<A,B>& a, const Pair<A,B>& b)
  {
    return equal(a.x,b.x) && equal(a.y,b.y);
  }

  inline friend unsigned int hash( const Pair<A,B>& a)
  {
    return hash(a.x) + hash(a.y);
  }

  inline friend Bool operator == (const Pair<A,B>& a, const Pair<A,B>& b)
  {
    return equal(a,b);
  }

  inline friend Bool operator != (const Pair<A,B>& a, const Pair<A,B>& b)
  {
    return ! equal(a,b);
  }
};

#endif
