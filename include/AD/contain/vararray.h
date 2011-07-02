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

#ifndef variable_sized_array_h
#define variable_sized_array_h

///////////////////////////////////////////////////////////////////////////
//  Class VarArray<T> provides an abstraction for
//  an dense mapping from integers to type T.
//  The array will grow in size when necessary.
//  Both positive and negative indices are allowed.
//  The indices should be centered around 0.
///////////////////////////////////////////////////////////////////////////

#include <new>
#include <string>
#include <AD/generic/generic.h>   // Generic definitions


template<class T>
class VarArray
{
  T * array;       // array of elements; displaced by offset
  int low, high;   // upper and lower bound on array
  int growthRate;  // minimal number of elements for expansion

  void grow(int i);

  //////////////////////////////////////////////////////////////////
  // Constructor and destructors
  //////////////////////////////////////////////////////////////////

public:
  VarArray(int lowerBound = 0,
           int upperBound = 9, int growthFactor = 32);
  VarArray(const VarArray& A) : array(0), low(0)
  {
    *this = A;
  }
  VarArray(size_t size, const T []);
  ~VarArray();

  ////////////////////////////////////////////////////////////////////
  // Assignment
  ////////////////////////////////////////////////////////////////////

  VarArray& operator = (const VarArray&);

  ////////////////////////////////////////////////////////////////////
  // Conversion
  ////////////////////////////////////////////////////////////////////

  inline operator const T * () const
  {
    return array;
  }

  inline operator T * ()
  {
    return array;
  }

  ////////////////////////////////////////////////////////////////////
  // Selectors
  ////////////////////////////////////////////////////////////////////

  inline int hi() const
  {
    return high;
  }

  inline int lo() const
  {
    return low;
  }

  inline int size() const
  {
    return high - low + 1;
  }

  inline int capacity() const
  {
    return size();
  }

  inline bool hasKey(int i) const
  {
    return i >= low && i <= high;
  }

  inline const T& operator [] (int i) const
  {
    return array[i];
  }

  inline T& operator [] (int i)
  {
    if (! hasKey(i))
      grow(i);
    return array[i];
  }

#ifdef _MSC_VER
  inline const T& operator [] (unsigned int i) const
  {
    return array[i];
  }

  inline T& operator [] (unsigned int i)
  {
    if (! hasKey(i))
      grow(i);
    return array[i];
  }

  inline const T& operator [] (unsigned short i) const
  {
    return array[i];
  }

  inline T& operator [] (unsigned short i)
  {
    if (! hasKey(i))
      grow(i);
    return array[i];
  }

  inline const T& operator [] (short i) const
  {
    return array[i];
  }

  inline T& operator [] (short i)
  {
    if (! hasKey(i))
      grow(i);
    return array[i];
  }
#endif

  ////////////////////////////////////////////////////////////////////
  // Iteration
  ////////////////////////////////////////////////////////////////////
  inline Ix first() const
  {
    return low > high ? 0 : (Ix)&array[lo()];
  }

  inline Ix last() const
  {
    return low > high ? 0 : (Ix)&array[hi()];
  }

  inline Ix next(Ix i) const
  {
    return i >= (Ix)(array + hi()) ? 0 : (((T*)i)+1);
  }

  inline Ix prev(Ix i) const
  {
    return i <= (Ix)(array + lo()) ? 0 : (((T*)i)-1);
  }

  inline const T& operator() (Ix i) const
  {
    return *(T*)i;
  }

  inline T& operator() (Ix i)
  {
    return *(T*)i;
  }
};

////////////////////////////////////////////////////////////////////
// Implementation comes here
////////////////////////////////////////////////////////////////////

template<class T>
VarArray<T>::VarArray(int lowerBound, int upperBound, int growthFactor)
{
  long size = lowerBound <= upperBound ? upperBound - lowerBound + 1 : 0;
  high = upperBound;
  low = lowerBound;
  T * mem = size > 0 ? new T [size] : (T*)0;
  array = mem - low;
  growthRate = growthFactor;
}

template<class T>
VarArray<T>::VarArray(size_t size, const T A[])
{
  array = new T [size];
  low = 0;
  high = size - 1;
  growthRate = 32;
  for (register int i = high; i >= 0; i--)
    array[i] = A[i];
}

template<class T>
VarArray<T>::~VarArray()
{
  delete [] (array + low);
}

template<class T>
VarArray<T>& VarArray<T>::operator = (const VarArray<T>& A)
{
  if (this != &A)
  {
    delete [] (array + low);
    high = A.high;
    low = A.low;
    array = new T [high - low + 1] - A.low;
    for (int i = low; i <= high; i++)
      array[i] = A.array[i];
  }
  return *this;
}

template<class T>
void VarArray<T>::grow(int i)
{
  int newHigh, newLow;
  int growth = growthRate <= 0 ? (size() * 3 / 2 + 32) : growthRate;
  if (i > high)
    if (i < high + growth)
      newHigh = high + growth;
    else
      newHigh = i;
  else
    newHigh = high;
  if (i < low)
    if (i > low - growth)
      newLow = low - growth;
    else
      newLow = i;
  else
    newLow = low;
  register T * newArray = new T [newHigh - newLow + 1] - newLow;
  for (register int j = low; j <= high; j++)
    newArray[j] = array[j];
  delete [] (array + low);
  array = newArray;
  low = newLow;
  high = newHigh;
}

#endif
