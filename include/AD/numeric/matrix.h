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

#ifndef floating_point_matrix_h
#define floating_point_matrix_h

#include <iostream>
#include <AD/contain/array2.h>  // two dimensional arrays


//////////////////////////////////////////////////////////////////////
// Class Matrix is inherited from the two dimensional array class
// |Array2<double>|.
//////////////////////////////////////////////////////////////////////

class Matrix : public Array2<double>
{
  void can_add(const Matrix&) const;   // check whether addition is defined.
  void can_mult(const Matrix&) const;  // check whether multiplication is defined.

  //////////////////////////////////////////////////////////////////
  // Default error handler
  //////////////////////////////////////////////////////////////////

public:
  static void (*error)(const char [], ...);

  //////////////////////////////////////////////////////////////////
  // Constructor and destructors
  //////////////////////////////////////////////////////////////////
  Matrix()
  {}
  Matrix(int m, int n)           : Array2<double>(m,n)
  {}
  Matrix(int m, int n, double e) : Array2<double>(m,n,e)
  {}
  Matrix(const Matrix& m)        : Array2<double>(m)
  {}
  ~Matrix()
  {}

  //////////////////////////////////////////////////////////////////
  //  Assignment
  //////////////////////////////////////////////////////////////////
  Matrix& operator = (const Matrix& a)
  {
    Array2<double>::operator = (a);
    return *this;
  }
  Matrix& operator = (double e)
  {
    Array2<double>::operator = (e);
    return *this;
  }

  //////////////////////////////////////////////////////////////////
  //  Selectors, indexing etc.
  //  Inherited from base class
  //////////////////////////////////////////////////////////////////
  // int rows()    const;
  // int columns() const;
  // const double * operator [] (int i) const;
  //       double * operator [] (int i);

  //////////////////////////////////////////////////////////////////
  // Scalar operations
  //////////////////////////////////////////////////////////////////
  Matrix operator - ();
  friend Matrix operator + (double, const Matrix&);
  friend Matrix operator + (const Matrix&, double);
  friend Matrix operator - (double, const Matrix&);
  friend Matrix operator - (const Matrix&, double);
  friend Matrix operator * (double, const Matrix&);
  friend Matrix operator * (const Matrix&, double);
  friend Matrix operator / (const Matrix&, double);

  //////////////////////////////////////////////////////////////////
  // In place scalar operations
  //////////////////////////////////////////////////////////////////
  Matrix& negate();
  Matrix& operator += (double);
  Matrix& operator -= (double);
  Matrix& operator *= (double);
  Matrix& operator /= (double);

  //////////////////////////////////////////////////////////////////
  // Matrix operations
  //////////////////////////////////////////////////////////////////
  friend Matrix operator + (const Matrix&, const Matrix&);
  friend Matrix operator - (const Matrix&, const Matrix&);
  friend Matrix operator * (const Matrix&, const Matrix&);
  double det() const;
  Matrix inverse() const;

  //////////////////////////////////////////////////////////////////
  // In place matrix operations
  //////////////////////////////////////////////////////////////////
  Matrix& operator += (const Matrix& m);
  Matrix& operator -= (const Matrix& m);
  Matrix& operator *= (const Matrix& m);
  Matrix& invert();

  //////////////////////////////////////////////////////////////////
  //  Linear algebra stuff
  //////////////////////////////////////////////////////////////////
  Matrix& LU (const Matrix&);
  Matrix& simplex();
  Matrix& ellipsoid();

  //////////////////////////////////////////////////////////////////
  // Comparisons
  //////////////////////////////////////////////////////////////////
  friend Bool operator == (const Matrix& a, const Matrix& b);
  friend Bool operator != (const Matrix& a, const Matrix& b)
  {
    return ! (a == b);
  }

  //////////////////////////////////////////////////////////////////
  // Submatrices and slicing
  //////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////
  // I/O
  //////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const Matrix&);
  friend std::istream& operator >> (std::istream&, Matrix&);
};

#endif
