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

#ifndef primes_and_primality_checking_h
#define primes_and_primality_checking_h

#include <AD/numeric/bigint.h>

/////////////////////////////////////////////////////////////////////////
// These two are randomized algorithms of the Monte Carlo variety.
/////////////////////////////////////////////////////////////////////////

extern Bool Rabin_isPrime            (const BigInt& n, int trials);
extern Bool Solovay_Strassen_isPrime (const BigInt& n, int trials);

#endif
