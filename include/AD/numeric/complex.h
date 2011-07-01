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

#ifndef complex_number_h
#define complex_number_h

////////////////////////////////////////////////////////////////////
//  Complex numbers represented in Cartesian form
////////////////////////////////////////////////////////////////////

#include <math.h>
#include <iostream>
#include <AD/generic/generic.h>  // Generic definitions


#define Complex Complex_

struct Complex
{
  double real, imag;

  /////////////////////////////////////////////////////////////////
  // Constructors
  /////////////////////////////////////////////////////////////////
  inline Complex(double x = 0.0, double y = 0.0) : real(x), imag(y)
  {}
  inline Complex(Complex& c) : real(c.real), imag(c.imag)
  {}

  /////////////////////////////////////////////////////////////////
  // Assignments
  /////////////////////////////////////////////////////////////////
  void operator += (const Complex& c);
  void operator += (double r);
  void operator -= (const Complex& c);
  void operator -= (double r);
  void operator *= (const Complex& c);
  void operator *= (double r);
  void operator /= (const Complex& c);
  void operator /= (double r);

  /////////////////////////////////////////////////////////////////
  // Comparisons between complex numebers and doubles
  /////////////////////////////////////////////////////////////////
  friend Bool operator == (const Complex& a, const Complex& b)
  {
    return a.real == b.real && a.imag == b.imag;
  }
  friend Bool operator == (const Complex& a, double b)
  {
    return a.real == b && a.imag == 0.0;
  }
  friend Bool operator == (double a, const Complex& b)
  {
    return a == b.real && b.imag == 0.0;
  }

  friend Bool operator != (const Complex& a, const Complex& b)
  {
    return a.real != b.real || a.imag != b.imag;
  }
  friend Bool operator != (const Complex& a, double b)
  {
    return a.real != b || a.imag != 0.0;
  }
  friend Bool operator != (double a, const Complex& b)
  {
    return a != b.real || b.imag != 0.0;
  }

  /////////////////////////////////////////////////////////////////
  // Operations on complex numbers: conjugate, polar, norm and abs.
  /////////////////////////////////////////////////////////////////
  friend Complex operator / (const Complex&, const Complex&);
  friend Complex operator / (double, const Complex&);
  Complex operator ! () const
  {
    return Complex(real,-imag);
  }
  friend Complex polar(double r, double theta);
  friend double norm(const Complex& c);
  friend double abs(const Complex& c)
  {
    return sqrt(norm(c));
  }

  /////////////////////////////////////////////////////////////////
  // Trignometric and logarithmic functions
  /////////////////////////////////////////////////////////////////
  friend Complex sin(const Complex&);
  friend Complex cos(const Complex&);
  friend Complex tan(const Complex&);
  friend Complex sinh(const Complex&);
  friend Complex cosh(const Complex&);
  friend Complex tanh(const Complex&);
  friend Complex asin(const Complex&);
  friend Complex acos(const Complex&);
  friend Complex atan(const Complex&);
  friend Complex asinh(const Complex&);
  friend Complex acosh(const Complex&);
  friend Complex atanh(const Complex&);
  friend Complex log(const Complex&);
  friend Complex exp(const Complex&);
  friend Complex pow(const Complex&, const Complex&);
  friend Complex pow(double, const Complex&);
  friend Complex pow(const Complex&, double);

  /////////////////////////////////////////////////////////////////
  // Input and output
  /////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const Complex&);
  friend std::istream& operator >> (std::istream&, Complex&);
};

//////////////////////////////////////////////////////////////////////////
//  Gnu C++ contains a non standard syntax for returning large objects
//  that eliminates unnecessary copying.  We'll provide a version
//  of arithmetic operators using this syntax and one without
//////////////////////////////////////////////////////////////////////////

inline Complex operator - (const Complex& c)
{
  return Complex(-c.real,-c.imag);
}
inline Complex operator + (const Complex& a, const Complex& b)
{
  return Complex(a.real + b.real, a.imag + b.imag);
}
inline Complex operator + (const Complex& a, double b)
{
  return Complex(a.real + b, a.imag);
}
inline Complex operator + (double a, const Complex& b)
{
  return Complex(a + b.real, b.imag);
}
inline Complex operator - (const Complex& a, const Complex& b)
{
  return Complex(a.real - b.real, a.imag - b.imag);
}
inline Complex operator - (const Complex& a, double b)
{
  return Complex(a.real - b, a.imag);
}
inline Complex operator - (double a, const Complex& b)
{
  return Complex(a - b.real, -b.imag);
}
inline Complex operator * (const Complex& a, const Complex& b)
{
  return Complex(a.real * b.real - a.imag * b.imag,
                 a.imag * b.real + a.real * b.imag);
}
inline Complex operator * (const Complex& a, double b)
{
  return Complex(a.real * b, a.imag * b);
}
inline Complex operator * (double a, const Complex& b)
{
  return Complex(a * b.real, a * b.imag);
}
inline Complex operator / (const Complex& a, double b)
{
  return Complex(a.real / b, a.imag / b);
}

inline void Complex::operator += (const Complex& c)
{
  real += c.real;
  imag += c.imag;
}
inline void Complex::operator += (double r)
{
  real += r;
}
inline void Complex::operator -= (const Complex& c)
{
  real -= c.real;
  imag -= c.imag;
}
inline void Complex::operator -= (double r)
{
  real -= r;
}
inline void Complex::operator *= (const Complex& c)
{
  *this = *this * c;
}
inline void Complex::operator *= (double r)
{
  real *= r;
  imag *= r;
}
inline void Complex::operator /= (const Complex& c)
{
  *this = *this / c;
}
inline void Complex::operator /= (double r)
{
  real /= r;
  imag /= r;
}

#endif
