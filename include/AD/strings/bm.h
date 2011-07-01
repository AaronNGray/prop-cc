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

#ifndef Boyer_Moore_string_matching_h
#define Boyer_Moore_string_matching_h

//
//  String matching with the Boyer-Moore algorithm\cite{BM}
//

#include <AD/strings/strmatch.h>

class BoyerMoore : public StringMatcher
{
  BoyerMoore(const BoyerMoore&);               // No copy constructor
  BoyerMoore& operator = (const BoyerMoore&);  // No assigment

protected:
  int last[256];
  int * ps;
  int patternLength;
  char * pat;

public:
  BoyerMoore() : ps(0), pat(0)
  {}
  BoyerMoore(const char * pattern);
  ~BoyerMoore();

  void compile (const char * pattern, int length = -1);
  void operator = (const char * pattern)
  {
    compile(pattern);
  }
  int Match(const char * text, int length = -1) const;
};

#endif
