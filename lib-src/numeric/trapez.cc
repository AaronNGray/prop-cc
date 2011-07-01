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

#include <AD/numeric/trapez.h>

double trapezoidal_integral
( double (*f)(double), double a, double b, long samples )
{
  register double delta = (b - a) / samples;
  register double x, y = 0.0;
  register int i;

  //
  // I'm real tired; could've gotten even this wrong!!!
  //

  for (i = 2, x = a + delta; i < samples; i++, x += delta)
    y += f(x);
  return (f(a) + f(b) + y * 2.0) * delta;
}
