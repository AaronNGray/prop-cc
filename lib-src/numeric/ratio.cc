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

#include <AD/numeric/ratio.h>

static int gcd(int m, int n)
{
  if (n > m)
  {
    int temp = m;
    m = n;
    n = temp;
  }
  register int q = 0;
  // Unimplemented yet.
  return q;
}

Ratio::Ratio(int m, int n)
{
  int factor = gcd(m,n);
  p = m/factor;
  q = n/factor;
}

Ratio::Ratio(const BigInt& m, const BigInt& n)
{
  BigInt factor = gcd(m,n);
  p = m/factor;
  q = m/factor;
}

///////////////////////////////////////////////////////////////////////
// Arithmetic operations
///////////////////////////////////////////////////////////////////////

Ratio operator + (const Ratio& a, const Ratio& b)
{
  return Ratio(a.p * b.q + a.q * b.p, a.q * b.q);
}
Ratio operator + (const Ratio& a, const BigInt& b)
{
  return Ratio(a.p + b * a.q,a.q);
}
Ratio operator + (const Ratio& a, int b)
{
  return Ratio(a.p + b * a.q,a.q);
}
Ratio operator + (const BigInt& a, const Ratio& b)
{
  return Ratio(a * b.q + b.p,b.q);
}
Ratio operator + (int a, const Ratio& b)
{
  return Ratio(a * b.q + b.p,b.q);
}
Ratio operator - (const Ratio& a, const Ratio& b)
{
  return Ratio(a.p * b.q - a.q * b.p, a.q * b.q);
}
Ratio operator - (const Ratio& a, const BigInt& b)
{
  return Ratio(a.p - b * a.q,a.q);
}
Ratio operator - (const Ratio& a, int b)
{
  return Ratio(a.p - b * a.q,a.q);
}
Ratio operator - (const BigInt& a, const Ratio& b)
{
  return Ratio(a * b.q - b.p,b.q);
}
Ratio operator - (int a, const Ratio& b)
{
  return Ratio(a * b.q - b.p,b.q);
}
Ratio operator * (const Ratio& a, const Ratio& b)
{
  return Ratio(a.p * b.p, a.q * b.q);
}
Ratio operator * (const Ratio& a, const BigInt& b)
{
  return Ratio(a.p * b, a.q);
}
Ratio operator * (const Ratio& a, int b)
{
  return Ratio(a.p * b, a.q);
}
Ratio operator * (const BigInt& a, const Ratio& b)
{
  return Ratio(a * b.p, b.q);
}
Ratio operator * (int a, const Ratio& b)
{
  return Ratio(a * b.p, b.q);
}
Ratio operator / (const Ratio& a, const Ratio& b)
{
  return Ratio(a.p * b.q, b.q * b.p);
}
Ratio operator / (const Ratio& a, const BigInt& b)
{
  return Ratio(a.p, a.q * b);
}
Ratio operator / (const Ratio& a, int b)
{
  return Ratio(a.p, a.q * b);
}
Ratio operator / (const BigInt& a, const Ratio& b)
{
  return Ratio(a * b.q, b.p);
}
Ratio operator / (int a, const Ratio& b)
{
  return Ratio(a * b.q, b.p);
}

///////////////////////////////////////////////////////////////////////
// In place arithmetic
///////////////////////////////////////////////////////////////////////

void Ratio::operator += (const Ratio&)
{ }
void Ratio::operator += (const BigInt& n)
{
  p += n * q;
}
void Ratio::operator += (int n)
{
  p += n * q;
}
void Ratio::operator -= (const Ratio&)
{ }
void Ratio::operator -= (const BigInt& n)
{
  p -= n * q;
}
void Ratio::operator -= (int n)
{
  p -= n * q;
}
void Ratio::operator *= (const Ratio&)
{ }
void Ratio::operator *= (const BigInt& n)
{
  p *= n;
}
void Ratio::operator *= (int n)
{
  p *= n;
}
void Ratio::operator /= (const Ratio&)
{ }
void Ratio::operator /= (const BigInt& n)
{
  q *= n;
}
void Ratio::operator /= (int n)
{
  q *= n;
}

/////////////////////////////////////////////////////////////////////////
// Comparisons
/////////////////////////////////////////////////////////////////////////

Bool operator == (const Ratio& a, const Ratio& b)
{
  return a.p == b.p && a.q == b.q;
}
Bool operator != (const Ratio& a, const Ratio& b)
{
  return a.p != b.p || a.q != b.q;
}
Bool operator > (const Ratio& a, const Ratio& b)
{
  return a.p * b.q > a.q * b.p;
}
Bool operator < (const Ratio& a, const Ratio& b)
{
  return a.p * b.q < a.q * b.p;
}
Bool operator >= (const Ratio& a, const Ratio& b)
{
  return a.p * b.q >= a.q * b.p;
}
Bool operator <= (const Ratio& a, const Ratio& b)
{
  return a.p * b.q <= a.q * b.p;
}
