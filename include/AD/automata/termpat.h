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

#ifndef term_patterns_h
#define term_patterns_h

#include <AD/generic/generic.h>   // Generic definitions

typedef class a_TermPat * TermPat;

class a_TermPat
{
  a_TermPat( const a_TermPat&);         // no copy constructor
  void operator = ( const a_TermPat&);  // no assignment

public:

  typedef short Symbol;        // Functor or variable is a symbol
  typedef short Functor;       // A functor (i.e. constructor)
  typedef unsigned char Arity; // Arity of a functor

  Functor f;           // functor
  Arity   n;           // arity
  TermPat subterms[1]; // array of subterms, if any

public:

  a_TermPat()
  {}
  a_TermPat( Functor g, Arity k = 0) : f(g), n(k)
  {}

  Functor tag() const
  {
    return f;
  }
  int     arity() const
  {
    return n;
  }
  TermPat nth(int i)
  {
    return subterms[i];
  }
  friend Bool isWild( const TermPat p)
  {
    return p == 0;
  }
};

#endif
