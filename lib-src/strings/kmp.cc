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
#include <AD/strings/kmp.h>

void KMP::compile( register const char* pattern, int len)
{
  delete [] skip;
  skip = NULL;
  if (len < 0)
    len = strlen(pattern);
  if ( (patternLength = len) > 0)
  {
    register int i, w, c;

    //
    //  ps[i] = Given a prefix |w| of pattern with length i,
    //          the length of the proper prefix of |w|
    //          that is also a suffix of |w|
    //
    skip = new Skip [patternLength];
    register int * ps = new int [patternLength];

    ps[0] = 0;
    for (i = 1; i < patternLength; i++)
    {
      for (w = ps[i-1]; ; w = ps[w-1] )
      {
        if (pattern[i] == pattern[w])
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

    for (c = 0; c < 256; c++)
      skip[0][c] = 1;
    skip[0][(unsigned char)pattern[0]] = 0;

    //
    // skip[i][c] = 0   if  pattern[i] == c
    // skip[i][c] = i + 1 - ps( pattern[0 ... i-1] . c )
    //
    for (i = 1; i < patternLength; i++)
    {
      for (c = 0; c < 256; c++)
      {
        if (c == pattern[i])
          skip[i][c] = 0;
        else
        {
          w = ps[i-1];
          skip[i][c] = i - w + skip[w][c];
        }
      }
    }

    delete [] ps;
  }
}

int KMP::Match(register const char * text, int textLength) const
{
  if (textLength < 0)
    textLength = strlen(text);
  register int m, p;  // characters matched and text position
  register int patLen = patternLength;
  register int limit = textLength - patLen;
  for (m = 0, p = 0; p <= limit; )
  {
    if (m == patLen)
      return p;
    register int d = skip [ m ] [ text [m + p] ];
    p += d;
    m += 1 - d;
  }
  return -1;
}
