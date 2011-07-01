//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef finite_domain_ranges_h
#define finite_domain_ranges_h

#include <AD/contain/bitset.h>
#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  Class FD_Range represents a finite set.
//////////////////////////////////////////////////////////////////////////////

class FD_Range
{
protected:
  int      min_elm, max_elm;  // minimal and maximum element.
  BitSet * chi;               // additional characteristic function.

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor.
  ///////////////////////////////////////////////////////////////////////////

public:
  inline  FD_Range (int a, int b) : min_elm(a), max_elm(b), chi(0)
  {}
  inline ~FD_Range ()
  {}

  ///////////////////////////////////////////////////////////////////////////
  //  Predicates.
  ///////////////////////////////////////////////////////////////////////////
  inline Bool is_empty() const
  {
    return min_elm > max_elm;
  }
  inline Bool contains (int i) const
  {
    return min_elm <= i && i <= max_elm && (chi == 0 || chi->contains(i));
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline int min() const
  {
    return min_elm;
  }
  inline int max() const
  {
    return max_elm;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Initialize range
  ///////////////////////////////////////////////////////////////////////////
  inline void init_range(int a, int b)
  {
    min_elm = a;
    max_elm = b;
    chi = 0;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Unification operations.
  ///////////////////////////////////////////////////////////////////////////
  inline Bool unify(int i);
  inline Bool unify(FD_Range&);

  ///////////////////////////////////////////////////////////////////////////
  //  Disunification
  ///////////////////////////////////////////////////////////////////////////
  inline Bool disunify(int i);
  inline Bool disunify(FD_Range&);
};

//////////////////////////////////////////////////////////////////////////////
//  Unification operation
//////////////////////////////////////////////////////////////////////////////
inline Bool FD_Range::unify(int i)
{
  return contains(i);
}

inline Bool FD_Range::unify(FD_Range& r)
{}

inline Bool FD_Range::disunify(int i)
{
  if (i < min_elm || i > max_elm)
    return true;
}

#endif
