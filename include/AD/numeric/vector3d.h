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

#ifndef vector_of_3_dimensions_h
#define vector_of_3_dimensions_h

#include <math.h>
#include <iostream>
#include <AD/generic/generic.h>


struct Vector3D
{
  double x, y, z;

  Vector3D(double i = 0, double j = 0, double k = 0) : x(i), y(j), z(k)
  {}

  Vector3D operator - () const
  {
    return Vector3D(-x,-y,-z);
  }
  Vector3D& operator += (const Vector3D& v)
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3D& operator -= (const Vector3D& v)
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  Vector3D& operator *= (double n)
  {
    x *= n;
    y *= n;
    z *= n;
    return *this;
  }
  Vector3D& operator /= (double n)
  {
    x /= n;
    y /= n;
    z /= n;
    return *this;
  }
  friend Vector3D operator + (const Vector3D& a, const Vector3D& b)
  {
    return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
  }
  friend Vector3D operator - (const Vector3D& a, const Vector3D& b)
  {
    return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
  }
  friend Vector3D operator * (const Vector3D& a, double n)
  {
    return Vector3D(a.x * n, a.y * n, a.z * n);
  }
  friend Vector3D operator * (double n, const Vector3D& a)
  {
    return Vector3D(a.x * n, a.y * n, a.z * n);
  }
  friend Vector3D operator / (const Vector3D& a, double n)
  {
    return Vector3D(a.x / n, a.y / n, a.z / n);
  }
  friend double operator * (const Vector3D& a, const Vector3D& b)
  {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }
  double norm() const
  {
    return (*this) * (*this);
  }
  double abs() const
  {
    return sqrt(this->norm());
  }

  friend std::ostream& operator << (std::ostream&, const Vector3D&);
  friend std::istream& operator >> (std::istream&, Vector3D&);
};

#endif
