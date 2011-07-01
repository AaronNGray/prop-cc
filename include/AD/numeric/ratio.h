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

#ifndef big_ratios_h
#define big_ratios_h

/////////////////////////////////////////////////////////////////////
//  Class |Ratio| represents rationals.
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/numeric/bigint.h>  // Unlimited precision integers


class Ratio
{

  /////////////////////////////////////////////////////////////////////
  // A Ratio is represented by the ratio between BigInt p and q.
  // We'll make sure that p and q are always relatively prime.
  /////////////////////////////////////////////////////////////////////

  BigInt p, q;

  ////////////////////////////////////////////////////////////////
  // Constructors and destructors
  ////////////////////////////////////////////////////////////////

public:
  Ratio() : p(0), q(1) {}
  Ratio(int n) : p(n), q(1) {}
  Ratio(const BigInt& m) : p(m), q(1) {}
  Ratio(const Ratio& r) : p(r.p), q(r.q) {}
  Ratio(int, int);
  Ratio(const BigInt&, const BigInt&);

  ////////////////////////////////////////////////////////////////
  // Assignments
  ////////////////////////////////////////////////////////////////
  void operator = (const Ratio& r)
  {
    p = r.p;
    q = r.q;
  }
  void operator = (const BigInt& n)
  {
    p = n;
    q = 1;
  }

  ////////////////////////////////////////////////////////////////
  // Querying the factors
  ////////////////////////////////////////////////////////////////
  const BigInt& nominator() const
  {
    return p;
  }
  const BigInt& denominator() const
  {
    return q;
  }

  ////////////////////////////////////////////////////////////////
  // Arithmetic operations
  ////////////////////////////////////////////////////////////////
  friend Ratio operator - (const Ratio&);
  friend Ratio operator + (const Ratio&, const Ratio&);
  friend Ratio operator + (const Ratio&, const BigInt&);
  friend Ratio operator + (const Ratio&, int);
  friend Ratio operator + (const BigInt&, const Ratio&);
  friend Ratio operator + (int, const Ratio&);
  friend Ratio operator - (const Ratio&, const Ratio&);
  friend Ratio operator - (const Ratio&, const BigInt&);
  friend Ratio operator - (const Ratio&, int);
  friend Ratio operator - (const BigInt&, const Ratio&);
  friend Ratio operator - (int, const Ratio&);
  friend Ratio operator * (const Ratio&, const Ratio&);
  friend Ratio operator * (const Ratio&, const BigInt&);
  friend Ratio operator * (const Ratio&, int);
  friend Ratio operator * (const BigInt&, const Ratio&);
  friend Ratio operator * (int, const Ratio&);
  friend Ratio operator / (const Ratio&, const Ratio&);
  friend Ratio operator / (const Ratio&, const BigInt&);
  friend Ratio operator / (const Ratio&, int);
  friend Ratio operator / (const BigInt&, const Ratio&);
  friend Ratio operator / (int, const Ratio&);

  ////////////////////////////////////////////////////////////////
  // In place arithmetic
  ////////////////////////////////////////////////////////////////
  void operator += (const Ratio&);
  void operator += (const BigInt&);
  void operator += (int);
  void operator -= (const Ratio&);
  void operator -= (const BigInt&);
  void operator -= (int);
  void operator *= (const Ratio&);
  void operator *= (const BigInt&);
  void operator *= (int);
  void operator /= (const Ratio&);
  void operator /= (const BigInt&);
  void operator /= (int);

  ////////////////////////////////////////////////////////////////
  // Comparisons
  ////////////////////////////////////////////////////////////////
  friend Bool operator == (const Ratio&, const Ratio&);
  friend Bool operator != (const Ratio&, const Ratio&);
  friend Bool operator >  (const Ratio&, const Ratio&);
  friend Bool operator <  (const Ratio&, const Ratio&);
  friend Bool operator >= (const Ratio&, const Ratio&);
  friend Bool operator <= (const Ratio&, const Ratio&);

  ////////////////////////////////////////////////////////////////
  // Conversion
  ////////////////////////////////////////////////////////////////
  void makeString(char buffer[], int length, int base = 10);
  void parseString(char buffer[], int length, int base = 10);

  ////////////////////////////////////////////////////////////////
  // I/O
  ////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const Ratio&);
  friend std::istream& operator >> (std::istream&, Ratio&);
};

#endif
