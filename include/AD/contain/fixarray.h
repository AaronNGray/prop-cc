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

#ifndef fix_sized_array_h
#define fix_sized_array_h

///////////////////////////////////////////////////////////////////////////
//  Class FixArray<T> is a simple array type whose size is fixed
//  at compile time.  The array is allocated in a contiguious chunk.
///////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>   // Generic definitions

template<class T, int Capacity>
class FixArray
{

  T array[Capacity];      // array of elements

  //////////////////////////////////////////////////////////
  // Constructor and destructors
  //////////////////////////////////////////////////////////

public:
  FixArray()
  {}
  ~FixArray()
  {}

  //////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////

  inline int lo() const
  {
    return 0;
  }

  inline int hi() const
  {
    return Capacity-1;
  }

  inline operator const T * () const
  {
    return array;
  }

  inline operator T * ()
  {
    return array;
  }

  inline int length() const
  {
    return Capacity;
  }

  inline int capacity() const
  {
    return Capacity;
  }

  inline const T& operator [] (int i) const
  {
    return array[i];
  }

  inline T& operator [] (int i)
  {
    return array[i];
  }

  //////////////////////////////////////////////////////////
  // Iteration
  //////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return Capacity == 0 ? 0 : (Ix)array;
  }

  inline Ix last() const
  {
    return Capacity == 0 ? 0 : array + Capacity - 1;
  }

  inline Ix next(Ix i) const
  {
    return i >= (Ix)(array + Capacity) ? 0 :
           (((T*)i)+1);
  }

  inline Ix prev(Ix i) const
  {
    return i <= (Ix)array ? 0 : (((T*)i)-1);
  }

  inline const T& operator () (Ix i) const
  {
    return *(T*)i;
  }

  inline T& operator () (Ix i)
  {
    return *(T*)i;
  }
};

#endif
