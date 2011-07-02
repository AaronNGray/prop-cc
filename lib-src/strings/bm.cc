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

#include <stddef.h>
#include <string>
#include <AD/strings/bm.h>

BoyerMoore::~BoyerMoore()
{
  delete [] ps;
  delete [] pat;
}

BoyerMoore::BoyerMoore(const char* pattern) : ps(0), pat(0)
{
  *this = pattern;
}

void BoyerMoore::compile( const char* pattern, int len)
{
  delete [] ps;
  delete [] pat;
  ps = NULL;
  pat = NULL;
  if (len < 0)
    len = strlen(pattern);
  if ( (patternLength = len) > 0)
  {
    register int i, w, c;

    pat = new char [patternLength];
    memcpy(pat,pattern,patternLength);
    ps = new int [patternLength];

    //
    // ps[i] = let p = pattern[i ... n-1]
    //         the length of the largest proper nonempty prefix of p that
    //             is also the proper nonempty suffix of p.
    ps[patternLength-1] = 0;
    for (i = patternLength - 2; i >= 0; i--)
    {
      for (w = ps[i+1]; ; w = ps[patternLength-w])
      {
        if (ps[i] == pattern[patternLength - w - 1])
        {
          ps[i] = w + 1;
          break;
        }
        if (w == 0)
        {
          ps[i] = 0;
          break;
        }
      }
    }
    for (i = patternLength - 2; i >= 0; i--)
      ps[i] = patternLength - ps[i];


    //
    // last[c] = the last offset(from right) of c in pattern
    //           or the length of the pattern if none such c exists.
    //
    for (c = 0; c < 256; c++)
      last[c] = patternLength;
    for (i = 0; i < patternLength - 1; i++)
      for (c = 0; c < 256; c++)
        if (pattern[i] == c)
          last[c] = patternLength - 1 - i;
  }
}

int BoyerMoore::Match( register const char* text, int length) const
{
  if (length < 0)
    length = strlen(text);
  register int limit = length - patternLength;
  register int pos;
  for ( pos = 0; pos <= limit; )
  {
    register int i;
    for (i = patternLength - 1; i >= 0 && pat[i] == text[pos + i]; i--)
      ;
    if (i < 0)
      return pos;
    register int x = last[text[pos+i]];
    register int y = ps[i];
    if (x > y)
      pos += x;
    else
      pos += y;
  }
  return -1;
}
