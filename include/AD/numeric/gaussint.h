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

#ifndef Gaussian_integers_h
#define Gaussian_integers_h

#include <math.h>
#include <iostream>
#include <AD/generic/generic.h>  // Generic definitions


struct GaussInt
{
  int real, imag;

  /////////////////////////////////////////////////////////////////////
  // Constructor and initializer
  /////////////////////////////////////////////////////////////////////

  GaussInt(int x = 0, int y = 0) : real(x), imag(y)
  {}
  GaussInt(GaussInt& c) : real(c.real), imag(c.imag)
  {}

  /////////////////////////////////////////////////////////////////////
  // In place arithmetic
  /////////////////////////////////////////////////////////////////////

  void operator += (const GaussInt& c)
  {
    real += c.real;
    imag += c.imag;
  }
  void operator -= (const GaussInt& c)
  {
    real -= c.real;
    imag -= c.imag;
  }
  void operator *= (const GaussInt& c)
  {
    *this = *this * c;
  }
  void operator /= (const GaussInt& c)
  {
    *this = *this / c;
  }
  void operator += (int r)
  {
    real += r;
  }
  void operator -= (int r)
  {
    real -= r;
  }
  void operator *= (int r)
  {
    real *= r;
    imag *= r;
  }
  void operator /= (int r)
  {
    real /= r;
    imag /= r;
  }

  //
  // GaussInt arithmetic
  //
  friend GaussInt operator - (const GaussInt& c)
  {
    return GaussInt(-c.real,-c.imag);
  }

  friend GaussInt operator + (const GaussInt& a, const GaussInt& b)
  {
    return GaussInt(a.real + b.real, a.imag + b.imag);
  }
  friend GaussInt operator + (const GaussInt& a, int b)
  {
    return GaussInt(a.real + b, a.imag);
  }
  friend GaussInt operator + (int a, const GaussInt& b)
  {
    return GaussInt(a + b.real, b.imag);
  }

  friend GaussInt operator - (const GaussInt& a, const GaussInt& b)
  {
    return GaussInt(a.real - b.real, a.imag - b.imag);
  }
  friend GaussInt operator - (const GaussInt& a, int b)
  {
    return GaussInt(a.real - b, a.imag);
  }
  friend GaussInt operator - (int a, const GaussInt& b)
  {
    return GaussInt(a - b.real, -b.imag);
  }

  friend GaussInt operator * (const GaussInt& a, const GaussInt& b)
  {
    return GaussInt(a.real * b.real - a.imag * b.imag,
                    a.imag * b.real + a.real * b.imag);
  }
  friend GaussInt operator * (const GaussInt& a, int b)
  {
    return GaussInt(a.real * b, a.imag * b);
  }
  friend GaussInt operator * (int a, const GaussInt& b)
  {
    return GaussInt(a * b.real, a * b.imag);
  }

  friend GaussInt operator / (const GaussInt& a, const GaussInt& b);
  friend GaussInt operator / (const GaussInt& a, int b)
  {
    return GaussInt(a.real / b, a.imag / b);
  }
  friend GaussInt operator / (int a, const GaussInt& b);

  //////////////////////////////////////////////////////////////////////
  // Comparisons between Gaussian integers and int
  //////////////////////////////////////////////////////////////////////
  friend Bool operator == (const GaussInt& a, const GaussInt& b)
  {
    return a.real == b.real && a.imag == b.imag;
  }
  friend Bool operator == (const GaussInt& a, int b)
  {
    return a.real == b && a.imag == 0.0;
  }
  friend Bool operator == (int a, const GaussInt& b)
  {
    return a == b.real && b.imag == 0.0;
  }

  friend Bool operator != (const GaussInt& a, const GaussInt& b)
  {
    return a.real != b.real || a.imag != b.imag;
  }
  friend Bool operator != (const GaussInt& a, int b)
  {
    return a.real != b || a.imag != 0.0;
  }
  friend Bool operator != (int a, const GaussInt& b)
  {
    return a != b.real || b.imag != 0.0;
  }

  //////////////////////////////////////////////////////////////////////
  // Operations on complex numbers: conjugate, polar, norm and abs.
  //////////////////////////////////////////////////////////////////////
  GaussInt operator ! () const
  {
    return GaussInt(real,-imag);
  }
  friend int norm(const GaussInt& c)
  {
    return c.real * c.real + c.imag * c.imag;
  }
  friend double abs(const GaussInt& c)
  {
    return sqrt(norm(c));
  }

  ////////////////////////////////////////////////////////////////
  // Input and output
  ////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const GaussInt&);
  friend std::istream& operator >> (std::istream&, GaussInt&);
};

#endif
