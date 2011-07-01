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

#ifndef integer_set_h
#define integer_set_h

///////////////////////////////////////////////////////////////////////////
//  Class IntSet is used to represent a set of positive integers
//  from 0 to some ``small'' n.
///////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>  // Generic definitions

class IntSet
{
  Byte * array;    // A bit array representing the integer set
  int limit;       // The size of this array in bytes

  //////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  //////////////////////////////////////////////////////////////////////

public:
  IntSet();
  IntSet(int limit);
  IntSet(const IntSet&);
  ~IntSet();

  //////////////////////////////////////////////////////////////////////
  // Initialization, assignment and growth
  //////////////////////////////////////////////////////////////////////

  IntSet& clear();
  IntSet& operator = (const IntSet&);
  IntSet& grow(int);

  //////////////////////////////////////////////////////////////////////
  // Insert/delete an integer from the set
  //////////////////////////////////////////////////////////////////////

  inline IntSet& add(int i)
  {
    bitSet(array,i);
    return *this;
  }

  inline IntSet& remove(int i)
  {
    bitClear(array,i);
    return *this;
  }

  inline IntSet& operator += (int i)
  {
    bitSet(array,i);
    return *this;
  }

  inline IntSet& operator -= (int i)
  {
    bitClear(array,i);
    return *this;
  }

  //////////////////////////////////////////////////////////////////////
  // Set membership and cardinality
  //////////////////////////////////////////////////////////////////////

  inline Bool operator [] (int i) const
  {
    return bitOf(array,i);
  }

  inline Bool contains(int i) const
  {
    return (*this)[i];
  }

  inline int count(int i) const
  {
    return contains(i) ? 1 : 0;
  }

  inline int capacity() const
  {
    return limit * 8;
  }

  inline int size() const;

  //////////////////////////////////////////////////////////////////////
  // Union, intersection and difference
  //////////////////////////////////////////////////////////////////////

  friend IntSet operator + (const IntSet&, const IntSet&);
  friend IntSet operator * (const IntSet&, const IntSet&);
  friend IntSet operator - (const IntSet&, const IntSet&);

  //////////////////////////////////////////////////////////////////////
  // Destructive union, intersection and difference
  //////////////////////////////////////////////////////////////////////

  IntSet& operator += (const IntSet&);
  IntSet& operator *= (const IntSet&);
  IntSet& operator -= (const IntSet&);

  //////////////////////////////////////////////////////////////////////
  // Equality and hashing
  //////////////////////////////////////////////////////////////////////

  friend unsigned int hash (const IntSet&);
  friend Bool         equal(const IntSet&, const IntSet&);

  inline friend Bool operator == (const IntSet& a, const IntSet& b)
  {
    return equal(a,b);
  }

  inline friend Bool operator != (const IntSet& a, const IntSet& b)
  {
    return ! equal(a,b);
  }
};

#endif
