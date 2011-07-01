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

#ifndef two_dimensional_array_h
#define two_dimensional_array_h

#include <AD/generic/generic.h>

template <class T>
class Array2
{
protected:

  int M, N;   // rows and columns
  int len;    // M * N
  T * array;  // array in flatten form

  ///////////////////////////////////////////////////////////////////////
  // Constructor and destructors
  ///////////////////////////////////////////////////////////////////////

public:
  Array2() : M(0), N(0), len(0), array(0)
  {}
  Array2(int m, int n);
  Array2(int m, int n, const T&);
  Array2(const Array2&);
  ~Array2()
  {
    delete [] array;
  }

  ///////////////////////////////////////////////////////////////////////
  // Assignment
  ///////////////////////////////////////////////////////////////////////

  Array2& operator = (const Array2&);
  Array2& operator = (const T&);

  ///////////////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////////////

  int rows()    const
  {
    return M;
  }
  int columns() const
  {
    return N;
  }
  int length()  const
  {
    return len;
  }
  const T * operator [] (int i) const
  {
    return array + i * N;
  }
  T * operator [] (int i)
  {
    return array + i * N;
  }
  const T   operator () (int i) const
  {
    return array[i];
  }
  T&  operator () (int i)
  {
    return array[i];
  }
};

/////////////////////////////////////////////////////////////////////////////
//  Implementation of additional template methods
/////////////////////////////////////////////////////////////////////////////

template <class T>
Array2<T>::Array2(int m, int n)
    : M(m), N(n), len(m * n), array(new T [len])
{}

template <class T>
Array2<T>::Array2(int m, int n, const T& e)
    : M(m), N(n), len(m * n), array(new T [len])
{
  *this = e;
}

template <class T>
Array2<T>::Array2(const Array2<T>& A) : M(0), N(0), array(0)
{
  *this = A;
}

template <class T>
Array2<T>& Array2<T>::operator = (const Array2<T>& A)
{
  if (this != &A)
  {
    if (M != A.M || N != A.N)
    {
      if (array)
        delete [] array;
      M = A.M;
      N = A.N;
      len = A.len;
      array = new T [len];
    }
    register const T * p;
    register T * q;
    register int i;
    for (i = len, q = array, p = A.array; i > 0; i--)
      *q++ = *p++;
  }
  return *this;
}

template <class T>
Array2<T>& Array2<T>::operator = (const T& e)
{
  register T * p, * q;
  for (p = array, q = array + len; p < q; )
    *p++ = e;
  return *this;
}

#endif
