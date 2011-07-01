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

#ifndef array_h
#define array_h

///////////////////////////////////////////////////////////////////////////
//  Class Array<T> is a simple array type whose size is fixed
//  at creation time.  The array is allocated in a contiguious chunk.
///////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>   // Generic definitions

template<class T>
class Array
{
  int len;        // length of array
  T * array;      // array of elements

  //////////////////////////////////////////////////////////
  // Constructor and destructors
  //////////////////////////////////////////////////////////

public:
  Array(int size) : len(size), array(new T [size])
  {}
  Array(const Array& a) : array(0)
  {
    *this = a;
  }
  ~Array()
  {
    delete [] array;
  }

  //////////////////////////////////////////////////////////
  //  Assignment
  //////////////////////////////////////////////////////////

  Array& operator = (const Array&);

  //////////////////////////////////////////////////////////
  //  Conversion
  //////////////////////////////////////////////////////////

  inline operator const T * () const
  {
    return array;
  }
  inline operator       T * ()
  {
    return array;
  }

  //////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////

  inline int      size()              const
  {
    return len;
  }
  inline int      length()            const
  {
    return len;
  }
  inline int      capacity()          const
  {
    return len;
  }
  inline int      lo()                const
  {
    return 0;
  }
  inline int      hi()                const
  {
    return len;
  }
  inline       T& operator [] (int i)
  {
    return array[i];
  }
  inline const T& operator [] (int i) const
  {
    return array[i];
  }

  //////////////////////////////////////////////////////////
  // Resizing the array
  //////////////////////////////////////////////////////////

  void resize(int n);

  //////////////////////////////////////////////////////////
  // Iteration
  //////////////////////////////////////////////////////////

  inline Ix first()    const
  {
    return len == 0 ? 0 : array;
  }
  inline Ix last()     const
  {
    return len == 0 ? 0 : array + len - 1;
  }
  inline Ix next(Ix i) const
  {
    return i >= (Ix)(array+len) ? 0 : (((T*)i)+1);
  }
  inline Ix prev(Ix i) const
  {
    return i <= (Ix)(array) ? 0 : (((T*)i)-1);
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

//////////////////////////////////////////////////////////////////
//  Implementation of additional methods
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////

template <class T>
Array<T>& Array<T>::operator = (const Array<T>& a)
{
  if (this != &a)
  {
    delete [] array;
    array = new T [len = a.len];
    for (int i = 0; i < len; i++)
      array[i] = a.array[i];
  }
  return *this;
}

//////////////////////////////////////////////////////////////////
//  Resizing an array
//////////////////////////////////////////////////////////////////

template <class T>
void Array<T>::resize(int n)
{
  if (n != len)
  {
    T * new_array = new T [n];
    for (int i = (len < n ? len : n) - 1; i >= 0; i--)
      new_array[i] = array[i];
    len = n;
    delete [] array;
    array = new_array;
  }
}

#endif
