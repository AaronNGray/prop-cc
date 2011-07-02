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

#include <string>
#include <AD/generic/generic.h>
#include <AD/contain/charset.h>

int CharSet::size() const
{
  register int count = 0;
  register int c;
  for (register int i = sizeof(array)-1; i >= 0; i--)
    for (c = array[i]; c; c &= c - 1)
      count++;
  return count;
}

void CharSet::operator += (const CharSet& s)
{
  for (register int i = sizeof(array)-1; i >= 0; i--)
    array[i] |= s.array[i];
}

void CharSet::operator -= (const CharSet& s)
{
  for (register int i = sizeof(array)-1; i >= 0; i--)
    array[i] &= ~s.array[i];
}

void CharSet::operator *= (const CharSet& s)
{
  for (register int i = sizeof(array)-1; i >= 0; i--)
    array[i] &= s.array[i];
}

CharSet operator + (const CharSet& s1, const CharSet& s2)
{
  CharSet s3 = s1;
  s3 += s2;
  return s3;
}

CharSet operator - (const CharSet& s1, const CharSet& s2)
{
  CharSet s3 = s1;
  s3 -= s2;
  return s3;
}

CharSet operator * (const CharSet& s1, const CharSet& s2)
{
  CharSet s3 = s1;
  s3 *= s2;
  return s3;
}

CharSet CharSet::operator ! () const
{
  CharSet s;
  for (register int i = sizeof(array)-1; i >= 0; i--)
    s.array[i] = ~ array[i];
  return s;
}
