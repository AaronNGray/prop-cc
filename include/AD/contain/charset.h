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

#ifndef character_set_h
#define character_set_h

#include <string>
#include <AD/generic/generic.h>

class CharSet
{
  ///////////////////////////////////////////////////////////////////
  // CharSet is implemented simply as a bit array.
  ///////////////////////////////////////////////////////////////////

  Byte array[32];

  ///////////////////////////////////////////////////////////////////
  //  A ``CharSet'' is an abstraction for a set of ASCII characters.
  ///////////////////////////////////////////////////////////////////

public:
  // make it empty
  void clear()
  {
    memset( array, 0, sizeof(array));
  }
  // Is `c' within set?
  Bool operator [] (char c) const
  {
    return bitOf(array,(unsigned char)c);
  }
  // Number of elements.
  int size() const;
  int capacity() const
  {
    return 256;
  }

  operator const Byte * () const
  {
    return array;
  }

  ///////////////////////////////////////////////////////////////////
  // Set operations: union, intersection and complement.
  // These return a new set as result and do not alter its arguments.
  ///////////////////////////////////////////////////////////////////

  void operator += (unsigned char c)
  {
    bitSet(array,c);
  }
  void operator -= (unsigned char c)
  {
    bitClear(array,c);
  }
  void operator += (const CharSet&);
  void operator -= (const CharSet&);
  void operator *= (const CharSet&);
  CharSet operator ! () const;

  friend CharSet operator + (const CharSet&, const CharSet&);
  friend CharSet operator + (const CharSet& s, unsigned char c)
  {
    CharSet s2 = s;
    s2 -= c;
    return s2;
  }

  friend CharSet operator + (char unsigned c, const CharSet& s)
  {
    return s+c;
  }
  friend CharSet operator * (const CharSet&, const CharSet&);
  friend CharSet operator - (const CharSet&, const CharSet&);
  friend CharSet operator - (const CharSet& s, unsigned char c)
  {
    CharSet s2 = s;
    s2 += c;
    return s2;
  }
};

#endif
