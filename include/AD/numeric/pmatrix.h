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

#ifndef matrix_template_interface_h
#define matrix_template_interface_h

//
// Class AMatrix<Element> is the usual matrix data type
// parametrized by the type of the element.  Thus it is
// possible to have matrices with elements something other
// than float's or double's---in fact, as long as the
// class Element is a field(in the algebraic sense)
// this class can be utilized.
//
// For example, we can have AMatrix<Complex>, or AMatrix<int>, etc.
//

#include <iostream>
#include <AD/contain/array2.h>  // two dimensional arrays


//////////////////////////////////////////////////////////////////////
// Class AMatrix<T> is inherited from the two dimensional array class
// |Array2<T>|.
//////////////////////////////////////////////////////////////////////

template <class T>
class AMatrix : public Array2<T>
{
  void can_add(const AMatrix&) const;   // check whether addition is defined.
  void can_mult(const AMatrix&) const;  // check whether multiplication is defined.

  //////////////////////////////////////////////////////////////////
  // Default error handler
  //////////////////////////////////////////////////////////////////

public:
  static void (*error)(const char [], ...);

  //////////////////////////////////////////////////////////////////
  // Constructor and destructors
  //////////////////////////////////////////////////////////////////
  AMatrix()
  {}
  AMatrix(int m, int n) : Array2<T>(m,n)
  {}
  AMatrix(int m, int n, T e) : Array2<T>(m,n,e)
  {}
  AMatrix(const AMatrix& m) : Array2<T>(m)
  {}
  ~AMatrix()
  {}

  //////////////////////////////////////////////////////////////////
  //  Assignment
  //////////////////////////////////////////////////////////////////
  // inherited

  //////////////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////////////
  // inherited

  //////////////////////////////////////////////////////////////////
  // Scalar operations
  //////////////////////////////////////////////////////////////////
  AMatrix operator - ();
  friend AMatrix operator + (T, const AMatrix&);
  friend AMatrix operator + (const AMatrix&, T);
  friend AMatrix operator - (T, const AMatrix&);
  friend AMatrix operator - (const AMatrix&, T);
  friend AMatrix operator * (T, const AMatrix&);
  friend AMatrix operator * (const AMatrix&, T);
  friend AMatrix operator / (const AMatrix&, T);

  //////////////////////////////////////////////////////////////////
  // In place scalar operations
  //////////////////////////////////////////////////////////////////
  AMatrix& negate();
  AMatrix& operator += (T);
  AMatrix& operator -= (T);
  AMatrix& operator *= (T);
  AMatrix& operator /= (T);

  //////////////////////////////////////////////////////////////////
  // AMatrix operations
  //////////////////////////////////////////////////////////////////
  friend AMatrix operator + (const AMatrix&, const AMatrix&);
  friend AMatrix operator - (const AMatrix&, const AMatrix&);
  friend AMatrix operator * (const AMatrix&, const AMatrix&);
  T det() const;
  AMatrix inverse() const;

  //////////////////////////////////////////////////////////////////
  // In place matrix operations
  //////////////////////////////////////////////////////////////////
  AMatrix& operator += (const AMatrix& m);
  AMatrix& operator -= (const AMatrix& m);
  AMatrix& operator *= (const AMatrix& m);
  AMatrix& invert();

  //////////////////////////////////////////////////////////////////
  // Comparisons
  //////////////////////////////////////////////////////////////////
  friend Bool operator == (const AMatrix& a, const AMatrix& b);
  friend Bool operator != (const AMatrix& a, const AMatrix& b)
  {
    return ! (a == b);
  }

  //////////////////////////////////////////////////////////////////
  // Submatrices and slicing
  //////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////
  // I/O
  //////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const AMatrix&);
  friend std::istream& operator >> (std::istream&, AMatrix&);
};

#endif
