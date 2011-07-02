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

#ifndef atomic_strings_h
#define atomic_strings_h

//////////////////////////////////////////////////////////////////////////////
//
//  Class |Quark| represents atomic strings that
//  adhere to the following identity:
//      Quark(s1) == Quark(s2)   iff    strcmp(s1,s2)
//
//  This means that we can use pointer comparison on
//  quarks where character comparison is necessary on
//  strings.
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <AD/generic/generic.h>   // Generic definitions


class Quark
{
  const char * name;          // internally a Quark is represented by a string
  // to a global table
  void intern(const char *);  // method to intern a string

  //////////////////////////////////////////////////////////////////////
  // Type Quark::Id can be used as a proxy for Quark when we have
  // to pass pointers around.
  //////////////////////////////////////////////////////////////////////

public:
  typedef const class QuarkId * Id;

  //////////////////////////////////////////////////////////////////////
  // Various forms of constructors.
  //////////////////////////////////////////////////////////////////////
  inline Quark() : name(0)
  {}
  inline Quark(const Quark& q) : name(q.name)
  {}
  inline Quark(const Id id) : name((const char *)((const void *)id))
  {}
  Quark( const char [] );
  Quark( const unsigned char [] );
  Quark( char );
  Quark( unsigned char );
  Quark( short );
  Quark( unsigned short );
  Quark( int );
  Quark( unsigned int );
  Quark( long );
  Quark( unsigned long );
  Quark( double );
  Quark( const char [], int );
  Quark( const char [], const char [] );
  Quark( const char [], const char [], const char [] );
  Quark( const char [], const char [], const char [], const char [] );

  //////////////////////////////////////////////////////////////////////
  // Conversion to string or Quark::Id
  //////////////////////////////////////////////////////////////////////
  inline operator const char * () const
  {
    return name;
  }
  inline const char * string   () const
  {
    return name;
  }
  inline operator Id           () const
  {
    return (Id)name;
  }

  //////////////////////////////////////////////////////////////////////
  // Indexing
  //////////////////////////////////////////////////////////////////////
  inline char operator [] (int i) const
  {
    return name[i];
  }

  //////////////////////////////////////////////////////////////////////
  // Various selectors
  //////////////////////////////////////////////////////////////////////
  inline int length() const
  {
    return strlen(name);
  }
  static int entries();

  //////////////////////////////////////////////////////////////////////
  // Comparisons
  //////////////////////////////////////////////////////////////////////
  inline friend Bool operator == (const Quark& x, const Quark& y)
  {
    return x.name == y.name;
  }
  inline friend Bool operator == (const Quark& x, const char * y)
  {
    return strcmp(x.name,y) == 0;
  }
  inline friend Bool operator == (const char * x, const Quark& y)
  {
    return strcmp(x,y.name) == 0;
  }
  inline friend Bool operator != (const Quark& x, const Quark& y)
  {
    return x.name != y.name;
  }
  inline friend Bool operator != (const Quark& x, const char * y)
  {
    return strcmp(x.name,y) != 0;
  }
  inline friend Bool operator != (const char * x, const Quark& y)
  {
    return strcmp(x,y.name) != 0;
  }

  inline friend Bool operator < (const Quark& x, const Quark& y)
  {
    return strcmp(x.name,y.name) < 0;
  }
  inline friend Bool operator > (const Quark& x, const Quark& y)
  {
    return strcmp(x.name,y.name) > 0;
  }
  inline friend Bool operator <= (const Quark& x, const Quark& y)
  {
    return strcmp(x.name,y.name) <= 0;
  }
  inline friend Bool operator >= (const Quark& x, const Quark& y)
  {
    return strcmp(x.name,y.name) >= 0;
  }

  //////////////////////////////////////////////////////////////////////
  // Hashing and equality
  //////////////////////////////////////////////////////////////////////
  inline friend unsigned int hash (const Quark& q)
  {
    return (unsigned int)q.name;
  }
  friend unsigned int hash_nocase (const Quark& q);
  inline friend Bool equal (const Quark& a, const Quark& b)
  {
    return a == b;
  }
  friend Bool equal_nocase (const Quark& a, const Quark& b);

  //////////////////////////////////////////////////////////////////////
  // I/O
  //////////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const Quark&);
  friend std::istream& operator >> (std::istream&, Quark&);
};

/////////////////////////////////////////////////////////////////////////
// Concatenation
/////////////////////////////////////////////////////////////////////////
inline Quark operator + (Quark a, Quark b)
{
  return Quark(a,b);
}
inline Quark operator + (Quark a, const char * b)
{
  return Quark(a,b);
}
inline Quark operator + (const char * a, Quark b)
{
  return Quark(a,b);
}
inline Quark operator + (Quark a, int b)
{
  return Quark(a,b);
}
inline Quark operator + (int a, Quark b)
{
  return Quark(Quark(a),b);
}

#endif
