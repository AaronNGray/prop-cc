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

#include <math.h>
#include <AD/numeric/complex.h>

inline double sgn2(double x)
{
  return x >= 0.0 ? 0.5 : -0.5;
}

const double pi2 = 3.1415926535 / 2.0;

Complex operator / (const Complex& a, const Complex& b)
{
  double r = norm(b);
  return Complex((a.real * b.real + a.imag * b.imag) / r,
                 (a.imag * b.real - a.real * b.imag) / r);
}

Complex operator / (double a, const Complex& b)
{
  double r = norm(b);
  return Complex((a * b.real) / r, (-a * b.imag) / r);
}

////////////////////////////////////////////////////////////////////
// The following trignometric and logarithmic functions
// probably have very bad numerically properties---assuming
// that they are correct in the first place.  Use at your
// own risk.
////////////////////////////////////////////////////////////////////

Complex sin( const Complex& c)
{
  return Complex( sin(c.real) * cosh(c.imag), cos(c.real) * sinh(c.imag));
}

Complex cos( const Complex& c)
{
  return Complex( cos(c.real) * sinh(c.imag), -sin(c.real) * cosh(c.imag));
}

Complex tan( const Complex& c)
{
  double real2      = c.real * 2.0;
  double imag2      = c.imag * 2.0;
  double cos_real2  = cos(real2);
  double cosh_imag2 = cosh(imag2);
  return Complex(sin(real2) / (cos_real2 + cosh_imag2),
                 tanh(imag2) / (1 + cos_real2/cosh_imag2));
}

Complex sinh( const Complex& c)
{
  return Complex( sinh(c.real) * cos(c.imag), cosh(c.real) * sin(c.imag));
}

Complex cosh( const Complex& c)
{
  return Complex( cosh(c.real) * cos(c.imag), sinh(c.real) * sin(c.imag));
}

Complex tanh( const Complex& c)
{
  double real2      = 2.0 * c.real;
  double imag2      = 2.0 * c.imag;
  double cos_imag2  = cos(imag2);
  double cosh_real2 = cosh(real2);
  return Complex(tanh(real2)/(1 + cos_imag2/cosh_real2),
                 sin(imag2)/(cosh_real2 + cos_imag2));
}

/*
Complex asin(const Complex& c)
{  double n  = norm(c);
   double n1 = n - 1.0;
   double d  = sqrt(n1 * n1 + 4 * c.imag * c.imag) - n;
   return Complex(sgn2(c.real) * acos(d),
                  sgn2(c.imag) * acosh(d));
}

Complex acos(const Complex& c)
{  double n  = norm(c);
   double n1 = n - 1.0;
   double d  = sqrt(n1 * n1 + 4 * c.imag * c.imag) - n;
   return Complex(pi2 - sgn2(c.real) * acos(d),
                  -sgn2(c.imag) * acosh(d));
}
*/

Complex log( const Complex& c)
{
  double n = norm(c);
  return Complex(log(n)/2.0, atan2(c.imag,c.real));
}

Complex exp( const Complex& c)
{
  double e_x = exp(c.real);
  return Complex(e_x * cos(c.imag), e_x * sin(c.imag));
}

Complex pow( const Complex& e, const Complex& x)
{
  return exp(log(e) * x);
}

Complex pow( const Complex& e, double x)
{
  return exp(log(e) * x);
}

Complex pow( double e, const Complex& x)
{
  return exp(log(e) * x);
}

Complex polar( double r, double theta)
{
  return Complex(r * sin(theta), r * cos(theta));
}

double norm( const Complex& c)
{
  return c.real * c.real + c.imag * c.imag;
}

std::ostream& operator << (std::ostream& out, const Complex& a)
{
  return out << '(' << a.real << ',' << a.imag << ')';
}
