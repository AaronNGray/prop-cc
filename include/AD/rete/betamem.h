//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef beta_memory_h
#define beta_memory_h

#include <AD/rete/token.h>  // network tokens

class BetaMem
{
  int         count;     // number of tokens in the list.
  int         capacity;  // number of tokens that we can hold.
  Fact ***    tokens;    // list of tokens.
  int  *      matches;   // negated matches.

  ///////////////////////////////////////////////////////////////////////////
  //  Conversion.
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////

public:
  inline int size() const
  {
    return count;
  }
  inline Fact ** operator [] (int i) const
  {
    return tokens[i];
  }
  inline Bool inc_neg(int i) const
  {
    return matches[i]++ == 0;
  }
  inline Bool dec_neg(int i) const
  {
    return --matches[i] == 0;
  }
};

#endif
