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

#ifndef vector_h
#define vector_h

#include <iostream>
#include <AD/generic/generic.h>


template <class T>
class Vector
{
  int len;      // length of the vector
  T * V;        // the vector array

  //
  // Constructors and destructor
  //

public:
  Vector() : len(0), V(0)
  {}
  Vector(int arity) : len(arity), V(new T [arity])
  {}
  Vector(T&);
  Vector(T&, T&);
  Vector(T&, T&, T&);
  Vector(const T [], int arity);
  Vector(const Vector&);
  ~Vector()
  {
    delete [] V;
  }

  //
  // Assignment
  //

  Vector& operator = (const Vector&);

  //
  // Selectors
  //
  int length() const
  {
    return len;
  }
  T& operator [] (int i) const
  {
    return V[i];
  }
  T abs() const;

  //
  // In place vector operations
  //
  Vector operator - ();
  Vector& operator += (const T&);
  Vector& operator -= (const T&);
  Vector& operator *= (const T&);
  Vector& operator /= (const T&);
  Vector& operator += (const Vector&);
  Vector& operator -= (const Vector&);

  //
  // Arithmetic operators
  //

  friend Vector operator + (const Vector&, const Vector&);
  friend Vector operator + (const Vector&, const T&);
  friend Vector operator + (const T&, const Vector&);
  friend Vector operator - (const Vector&, const Vector&);
  friend Vector operator - (const Vector&, const T&);
  friend Vector operator - (const T&, const Vector&);
  friend T operator * (const Vector&, const Vector&); // dot product
  friend Vector operator * (const Vector&, const T&);
  friend Vector operator * (const T&, const Vector&);
  friend Vector operator / (const Vector&, const T&);
  Vector cross(const Vector&) const;  // cross product

  //
  // Comparisons
  //

  friend Bool operator == (const Vector&, const Vector&);
  friend Bool operator != (const Vector& a, const Vector& b)
  {
    return ! (a == b);
  }

  //
  // Input and output
  //
  friend std::ostream& operator << (std::ostream&, const Vector&);
  friend std::istream& operator >> (std::istream&, Vector&);
};

#endif
