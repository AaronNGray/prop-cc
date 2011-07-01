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
#include <string.h>
#include <AD/strings/kr.h>

void KR::compile (const char* pat, int len)
{
  if (len < 0)
    len = strlen(pat);
  patternLength = len;
  delete [] pattern;
  pattern = new char [len];
  memcpy(pattern,pat,len);
  fingerPrint = 0;
  for (register int i = len-1; i >= 0; i--)
    fingerPrint += pat[i];
}

int KR::Match( register const char * text, register int length) const
{
  if (length < 0)
    length = strlen(text);
  if (length < patternLength)
    return -1;
  register int i, j;
  register unsigned int chi = 0;
  for (i = 0; i < patternLength; i++)
    chi += text[i];
  for (j = 0; ; i++, j++)
  {
    if (chi == fingerPrint &&
        memcmp(pattern,text+j,patternLength) == 0)
      return j;
    if (i >= length)
      break;
    chi += text[i] - text[j];
  }
  return -1;
}
