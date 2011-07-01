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

#ifndef Karp_Rabin_string_matching_h
#define Karp_Rabin_string_matching_h

//
//  Karp-Rabin string match by ``finger printing''
//

#include <AD/strings/strmatch.h>

class KR : public StringMatcher
{
  KR(const KR&);                // No copy constructor
  void operator = (const KR&);  // No assignment

protected:
  unsigned int fingerPrint;  // finger printing signature of pattern
  char * pattern;            // the pattern
  int patternLength;         // length of the pattern

public:
  KR() : pattern(0) {}

  KR(const char * p) : pattern(0)
  {
    *this = p;
  }

  ~KR()
  {
    delete [] pattern;
  }

  void compile (const char * pattern, int length = -1);

  void operator = (const char * p)
  {
    compile(p);
  }

  int Match(const char * text, int length = -1) const;
};

#endif
