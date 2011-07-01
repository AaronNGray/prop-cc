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

#ifndef integer_set_array_h
#define integer_set_array_h

//////////////////////////////////////////////////////////////////////////
//  Fixed bounds integer set arrays
//////////////////////////////////////////////////////////////////////////
#include <AD/generic/generic.h>

class IntSetArray
{
  IntSetArray(const IntSetArray&);         // no copy constructor
  void operator = (const IntSetArray&);    // no assignment

  Byte * sets;        // bit vector representing the array of sets
  int min_index;      // minimal index of array
  int byte_offset;    // minimal integer within the set
  int shift;          // ceiling of log_2 of the size of the sets

public:
  IntSetArray() : sets(0)
  {}
  ~IntSetArray();

  void create( int min_index, int max_index, int min_value, int max_value);
  void destroy();

  int set_size() const
  {
    return 1 << shift;
  }

  Byte * operator [] (int i) const
  {
    return sets + (i << shift);
  }

  Byte * operator () (int i) const
  {
    return (*this)[i] + byte_offset;
  }

  Bool has( int i, int j) const
  {
    return bitOf((*this)[i], j);
  }

  void insert( int i, int j)
  {
    bitSet((*this)[i], j);
  }

  void remove(int i, int j)
  {
    bitClear((*this)[i], j);
  }
};

#endif
