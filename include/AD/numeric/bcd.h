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

#ifndef binary_coded_decimal_h
#define binary_coded_decimal_h

#include <iostream>
#include <AD/generic/generic.h>


///////////////////////////////////////////////////////////////////////////
//  Class BCD
///////////////////////////////////////////////////////////////////////////

class BCD
{
  char * digits;

public:

  ////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////
  BCD();               // e.g. BCD n;
  BCD(long);           // e.g. BCD n = 1234;
  BCD(const BCD&);     // e.g. BCD n = m;
  ~BCD();

  ////////////////////////////////////////////////////////////////////////
  //  Conversion
  ////////////////////////////////////////////////////////////////////////
  operator const char * () const
  {
    return digits;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Assignment
  ////////////////////////////////////////////////////////////////////////
  BCD& operator = (long);
  BCD& operator = (const BCD&);

  ////////////////////////////////////////////////////////////////////////
  //  Selectors
  ////////////////////////////////////////////////////////////////////////
  char operator [] (int i) const
  {
    return digits[i+1];
  }

  ////////////////////////////////////////////////////////////////////////
  //  Arithmetic
  ////////////////////////////////////////////////////////////////////////
  BCD operator - ();
  friend BCD operator + (const BCD&, const BCD&);
  friend BCD operator - (const BCD&, const BCD&);
  friend BCD operator * (const BCD&, const BCD&);
  friend BCD operator / (const BCD&, const BCD&);

  ////////////////////////////////////////////////////////////////////////
  //  Comparison
  ////////////////////////////////////////////////////////////////////////
  friend Bool operator == (const BCD&, const BCD&);
  friend Bool operator != (const BCD&, const BCD&);
  friend Bool operator >  (const BCD&, const BCD&);
  friend Bool operator <  (const BCD&, const BCD&);
  friend Bool operator >= (const BCD&, const BCD&);
  friend Bool operator <= (const BCD&, const BCD&);

  ////////////////////////////////////////////////////////////////////////
  //  I/O
  ////////////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const BCD&);
  friend std::istream& operator >> (std::istream&, BCD&);
};

#endif
