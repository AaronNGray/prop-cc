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

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <iostream.h>
#include <AD/numeric/matrix.h>

////////////////////////////////////////////////////////////////////////////
// Default handler
////////////////////////////////////////////////////////////////////////////

static void error_handler( const char format[], ...)
{
  va_list args;
  va_start(args,format);
  fprintf  (stderr, "[ Matrix error: ");
  vfprintf (stderr, format, args);
  fprintf  (stderr, "]\n");
  va_end(args);
  exit(1);
}

void (*Matrix::error)( const char [], ...) = error_handler;

////////////////////////////////////////////////////////////////////////////
// Bounds checking
////////////////////////////////////////////////////////////////////////////

void Matrix::can_add( const Matrix& m) const
{
  if (m.rows() != rows() || m.columns() != columns())
    Matrix::error(
      "Can't add/subtract/compare matrices with different dimensions [%d,%d], [%d,%d]",
      rows(), columns(), m.rows(), m.columns());

}

void Matrix::can_mult( const Matrix& m) const
{
  if (columns() != m.rows())
    Matrix::error(
      "Can't multiply matrices with incompatible dimensions [%d,%d], [%d,%d]",
      rows(), columns(), m.rows(), m.columns());
}

////////////////////////////////////////////////////////////////////////////
// Negate
////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator - ()
{
  Matrix r(M,N);
  for (int i = len - 1; i >= 0; i--)
    r.array[i] = -array[i];
  return r;
}

////////////////////////////////////////////////////////////////////////////
// Matrix operations with scalars
////////////////////////////////////////////////////////////////////////////

Matrix operator + (double a, const Matrix& m)
{
  Matrix r(m.M,m.N);
  for (int i = m.len - 1; i >= 0; i--)
    r.array[i] = a + m.array[i];
  return r;
}

Matrix operator + (const Matrix& m, double a)
{
  Matrix r(m.M,m.N);
  for (int i = m.len - 1; i >= 0; i--)
    r.array[i] = m.array[i] + a;
  return r;
}

Matrix operator - (double a, const Matrix& m)
{
  Matrix r(m.M,m.N);
  for (int i = m.len - 1; i >= 0; i--)
    r.array[i] = a - m.array[i];
  return r;
}

Matrix operator - (const Matrix& m, double a)
{
  Matrix r(m.M,m.N);
  for (int i = m.len - 1; i >= 0; i--)
    r.array[i] = m.array[i] - a;
  return r;
}

Matrix operator * (double a, const Matrix& m)
{
  Matrix r(m.M,m.N);
  for (int i = m.len - 1; i >= 0; i--)
    r.array[i] = a * m.array[i];
  return r;
}

Matrix operator * (const Matrix& m, double a)
{
  Matrix r(m.M,m.N);
  for (int i = m.len - 1; i >= 0; i--)
    r.array[i] = m.array[i] * a;
  return r;
}

Matrix operator / (const Matrix& m, double a)
{
  Matrix r(m.M,m.N);
  for (int i = m.len - 1; i >= 0; i--)
    r.array[i] = m.array[i] / a;
  return r;
}

//////////////////////////////////////////////////////////////////////////
//  In place operations with scalars
//////////////////////////////////////////////////////////////////////////

Matrix& Matrix::negate()
{
  for (int i = len - 1; i >= 0; i--)
    array[i] = -array[i];
  return *this;
}

Matrix& Matrix::operator += (double a)
{
  for (int i = len - 1; i >= 0; i--)
    array[i] += a;
  return *this;
}

Matrix& Matrix::operator -= (double a)
{
  for (int i = len - 1; i >= 0; i--)
    array[i] -= a;
  return *this;
}

Matrix& Matrix::operator *= (double a)
{
  for (int i = len - 1; i >= 0; i--)
    array[i] *= a;
  return *this;
}

Matrix& Matrix::operator /= (double a)
{
  for (int i = len - 1; i >= 0; i--)
    array[i] /= a;
  return *this;
}

//////////////////////////////////////////////////////////////////////////
//  Matrix/Matrix operations
//////////////////////////////////////////////////////////////////////////

Matrix operator + (const Matrix& a, const Matrix& b)
{
  a.can_add(b);
  Matrix r(a.M,a.N);
  for (int i = a.len - 1; i >= 0; i--)
    r.array[i] = a.array[i] + b.array[i];
  return r;
}

Matrix operator - (const Matrix& a, const Matrix& b)
{
  a.can_add(b);
  Matrix r(a.M,a.N);
  for (int i = a.len - 1; i >= 0; i--)
    r.array[i] = a.array[i] - b.array[i];
  return r;
}

Matrix operator * (const Matrix& a, const Matrix& b)
{
  a.can_mult(b);
  Matrix r(a.N,b.M);
  for (int i = 0; i < a.N; i++)
  {
    int j;
    double sum = 0;
    for (j = 0; j < b.M; j++)
      for (int k = 0; k < a.M; k++)
        sum += a[i][k] * b[k][j];
    r[i][j] = sum;
  }
  return r;
}

//////////////////////////////////////////////////////////////////////////
//  In place matrix operations
//////////////////////////////////////////////////////////////////////////

double Matrix::det() const
{
  can_mult(*this);
  return 0;
}

Matrix Matrix::inverse() const
{
  can_mult(*this);
  return *this;
}

Matrix& Matrix::operator += (const Matrix& m)
{
  can_add(m);
  for (int i = len - 1; i >= 0; i--)
    array[i] += m.array[i];
  return *this;
}

Matrix& Matrix::operator -= (const Matrix& m)
{
  can_add(m);
  for (int i = len - 1; i >= 0; i--)
    array[i] -= m.array[i];
  return *this;
}

Matrix& Matrix::operator *= (const Matrix& m)
{
  *this = *this * m;
  return *this;
}

////////////////////////////////////////////////////////////////////////////
//  Comparison
////////////////////////////////////////////////////////////////////////////

Bool operator == (const Matrix& a, const Matrix& b)
{
  a.can_add(b);
  for (int i = a.len - 1; i >= 0; i--)
    if (a.array[i] != b.array[i])
      return false;
  return true;
}
