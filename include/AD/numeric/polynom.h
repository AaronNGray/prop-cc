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

#ifndef polynomial_h
#define polynomial_h

////////////////////////////////////////////////////////////////////
// Class Polynomial<X> represents a polynomial of type X.  Type X
// must be a field(in the mathematical sense, not C).
////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>

template <class X>
class Polynomial
{
  ////////////////////////////////////////////////////////////////////
  //  We use a simple array representation storing the coeficients
  // of the polynomial.   More storage is needed may be preallocated
  // to allow for future expansion.
  ////////////////////////////////////////////////////////////////////
  int max_degree;  // maximum degree currently allowed
  int degree;      // degree of polynomial
  X * coef;        // array of coefficients

  void norm();     // normalize result

  friend int max(int i,int j)
  {
    return i > j ? i : j;
  }
  friend int min(int i,int j)
  {
    return i < j ? i : j;
  }
  Polynomial(int deg) : degree(deg), coef(new X [deg + 1])
  {}

  ////////////////////////////////////////////////////////////////
  // constructor and destructor
  ////////////////////////////////////////////////////////////////

public:
  Polynomial() : degree(-1), coef(0) {}

  Polynomial(const X& x) : degree(0), coef(new X [1])
  {
    coef[0] = x;
  }

  Polynomial(const Polynomial& p) : coef(0)
  {
    *this = p;
  }

  ~Polynomial()
  {
    delete [] coef;
  }

  ////////////////////////////////////////////////////////////////
  // Assignment
  ////////////////////////////////////////////////////////////////
  void operator = (const Polynomial&);

  ////////////////////////////////////////////////////////////////
  // operator () -- evaluate the polynomial at a point
  // operator [] -- returns the coefficient of a certain degree
  // degree()    -- returns the maximum degree
  ////////////////////////////////////////////////////////////////
  X operator () (const X&) const;
  X& operator [] (int i) const
  {
    return coef[i];
  }
  int deg() const
  {
    return degree;
  }

  void negate();
  void operator += (const X&);
  void operator -= (const X&);
  void operator *= (const X&);
  void operator /= (const X&);
  void operator += (const Polynomial&);
  void operator -= (const Polynomial&);
  void operator *= (const Polynomial&);
  void operator /= (const Polynomial&);

  Polynomial operator - () const;
  friend Polynomial operator + (const Polynomial&, const Polynomial&);
  friend Polynomial operator - (const Polynomial&, const Polynomial&);
  friend Polynomial operator * (const Polynomial&, const Polynomial&);
  friend Polynomial operator / (const Polynomial&, const Polynomial&);
  friend Polynomial operator % (const Polynomial&, const Polynomial&);
  friend Polynomial operator + (const Polynomial&, const X&);
  friend Polynomial operator - (const Polynomial&, const X&);
  friend Polynomial operator * (const Polynomial&, const X&);
  friend Polynomial operator / (const Polynomial&, const X&);
  friend Polynomial operator + (const X&, const Polynomial&);
  friend Polynomial operator - (const X&, const Polynomial&);
  friend Polynomial operator * (const X&, const Polynomial&);

  friend Bool operator == (const Polynomial&, const Polynomial&);
  friend Bool operator != (const Polynomial&, const Polynomial&);
  friend Bool operator == (const Polynomial&, const X&);
  friend Bool operator != (const Polynomial&, const X&);
  friend Bool operator == (const X&, const Polynomial&);
  friend Bool operator != (const X&, const Polynomial&);
};

//////////////////////////////////////////////////////////////////////////
// Implementation of the template methods
//////////////////////////////////////////////////////////////////////////

template <class X>
void Polynomial<X>::norm()
{
  while (degree > 0 && coef[degree] == 0)
    --degree;
}

template <class X>
void Polynomial<X>::negate()
{
  for (int i = degree; i >= 0; i--)
    coef[i] = -coef[i];
}
template <class X>
void Polynomial<X>::operator += (const X& x)
{
  for (int i = degree; i >= 0; i--)
    coef[i] += x;
  norm();
}
template <class X>
void Polynomial<X>::operator -= (const X& x)
{
  for (int i = degree; i >= 0; i--)
    coef[i] -= x;
  norm();
}
template <class X>
void Polynomial<X>::operator *= (const X& x)
{
  for (int i = degree; i >= 0; i--)
    coef[i] *= x;
  norm();
}
template <class X>
void Polynomial<X>::operator /= (const X& x)
{
  for (int i = degree; i >= 0; i--)
    coef[i] /= x;
  norm();
}

template <class X>
void Polynomial<X>::operator += (const Polynomial<X>& p)
{ }

template <class X>
void Polynomial<X>::operator -= (const Polynomial<X>& p)
{
  for (int i = degree; i >= 0; i--)
    coef[i] -= p[i];
  norm();
}

template <class X>
void Polynomial<X>::operator *= (const Polynomial<X>& p)
{
  Polynomial<X> r(this->deg() + p.deg());
  {
    for (int i = r.deg(); i >= 0; i--)
      r[i] = 0;
  }
  {
    for (int i = degree; i >= 0; i--)
      for (int j = p.deg(); j >= 0; j--)
        coef[i+j] += (*this)[i] * p[j];
  }
  *this = r;
  norm();
}

template <class X>
Polynomial<X> Polynomial<X>::operator - () const
{
  Polynomial<X> r(degree);
  for (int i = degree; i >= 0; i--)
    r[i] = -coef[i];
  return r;
}
template <class X>
Polynomial<X> operator + (const Polynomial<X>& p, const Polynomial<X>& q)
{
  Polynomial<X> r(max(p.deg(),q.deg()));
}
template <class X>
Polynomial<X> operator - (const Polynomial<X>& p, const Polynomial<X>& q)
{}
template <class X>
Polynomial<X> operator * (const Polynomial<X>& p, const Polynomial<X>& q)
{}
template <class X>
Polynomial<X> operator + (const Polynomial<X>& p, const X& x)
{}
template <class X>
Polynomial<X> operator - (const Polynomial<X>& p, const X& x)
{}
template <class X>
Polynomial<X> operator * (const Polynomial<X>& p, const X& x)
{}
template <class X>
Polynomial<X> operator / (const Polynomial<X>& p, const X& x)
{}
template <class X>
Polynomial<X> operator + (const X& x, const Polynomial<X>& p)
{}
template <class X>
Polynomial<X> operator - (const X& x, const Polynomial<X>& p)
{}

#endif
