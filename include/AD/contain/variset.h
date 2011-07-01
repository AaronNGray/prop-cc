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

#ifndef variable_length_integer_sets_h
#define variable_length_integer_sets_h

////////////////////////////////////////////////////////////////////////////
//  Class VarIntSet is used to represent a set of positive integers
//  from 0 to some ``small'' n.  The integer set can grow if necessary
////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>
#include <AD/generic/generic.h>  // Generic definitions

class VarIntSet
{
  typedef unsigned long Glob;

  Glob * array;    // A bit array representing the integer set
  size_t limit;    // The size of this array in 4-bytes glob
  size_t growth;   // Amount to grow when necessary

  void grow(size_t new_limit);

public:
  VarIntSet(size_t init_size = 0, size_t g = 8);
  ~VarIntSet();

  ///////////////////////////////////////////////////////////////////////
  // Set operations
  ///////////////////////////////////////////////////////////////////////

  void clear ()
  {
    memset(array,0,limit * sizeof(Glob));
  }

  void setUnion( size_t i)
  {
    register size_t index = i / (8 * sizeof(Glob));
    if (index >= limit)
      grow(index > limit + growth ? index : limit + growth);
    array[index] |= (1 << (i & (8 * sizeof(Glob) - 1)));
  }

  void setRemove( size_t i)
  {
    register size_t index = i / (8 * sizeof(Glob));
    if (index >= limit)
      grow(index > limit + growth ? index : limit + growth);
    array[index] &= ~(1 << (i & (8 * sizeof(Glob) - 1)));
  }

  void setUnion( const VarIntSet& a)
  {
    if (a.limit >= limit)
      grow(a.limit);
    register long i;
    register Glob * p;
    register const Glob * q;
    for (i = limit - 1, p = array, q = a.array; i >= 0; i--)
      *p++ |= *q++;
  }

  void setIntersection( const VarIntSet& a)
  {
    register long i;
    register Glob * p;
    register const Glob * q;
    for (i = (limit < a.limit ? limit : a.limit) - 1,
         p = array, q = a.array; i >= 0; i--)
      *p++ &= *q++;
  }

  void setDiff(const VarIntSet& a)
  {
    register long i;
    register Glob * p;
    register const Glob * q;
    for (i = (limit < a.limit ? limit : a.limit) - 1,
         p = array, q = a.array; i >= 0; i--)
      *p++ &= ~ *q++;
  }

  Bool isDisjoint(const VarIntSet& a) const
  {
    register long i;
    register const Glob * p, * q;
    for (i = (limit < a.limit ? limit : a.limit) - 1,
         p = array, q = a.array; i >= 0; i--)
      if (*p++ & *q++)
        return false;
    return true;
  }

  ///////////////////////////////////////////////////////////////////////
  // Set membership and cardinality
  ///////////////////////////////////////////////////////////////////////

  Bool operator [] (size_t i) const
  {
    register size_t index = i/(8*sizeof(Glob));
    return index < limit ?
           (array[index] & (1 << (i & (8 * sizeof(Glob)-1)))) : false;
  }

  size_t capacity() const
  {
    return limit * (8*sizeof(Glob));
  }

  ///////////////////////////////////////////////////////////////////////
  // Iteration
  ///////////////////////////////////////////////////////////////////////

  int next( int& i, int& j) const
  {
    if (j == (8*sizeof(Glob)))
      goto next_glob;
next:
    while ((array[i] & (1 << j)) == 0)
      if (++j == (8*sizeof(Glob)))
        goto next_glob;
    return i * (8*sizeof(Glob)) + j++;
next_glob:
    while (array[i] == 0)
    {
      if (++i == (int)limit)
        return -1;
    }
    j = 0;
    goto next;
  }
};

#endif
