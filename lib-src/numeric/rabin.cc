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

#include <AD/numeric/primes.h>

////////////////////////////////////////////////////////////////////////////
// Rabin primality checking\cite{RSA, random-algorithms, number-theory}
////////////////////////////////////////////////////////////////////////////

Bool Rabin_isPrime(const BigInt& n, int trials)
{
  BigInt n_minus_1 = n - 1;

  //////////////////////////////////////////////////////////////////////
  // First, try some small primes to prune out blatant composites.
  //////////////////////////////////////////////////////////////////////

  if (pow_mod(2 * 3 * 5 * 7 * 11 * 13 * 17 * 23 * 31,n_minus_1,n) != 1)
    return false;


  for ( ; trials > 0; trials--)
  {
    BigInt x = make_random(n_minus_1) + 1; // get a random number from 1 to n-1

    //
    // Try testing for composite using Fermat's(Euler's) theorem:
    //    x^(phi(n)) = 1 (mod n) iff n is relatively prime to x.
    //  where phi(n) is the number of elements relatively prime to
    //  n from 1 to n.
    //

    if (pow_mod(x,n_minus_1,n) != 1)
      return false;

    //
    // Then try Lehmer's heuristics:
    //  n is prime iff
    //        (1) x^(n-1)     =  1 (mod n) and
    //        (2) x^((n-1)/p) <> 1 (mod n) for each prime factor p of n-1
    //
  }

  /////////////////////////////////////////////////////////////////////
  //  N is a prime with probability >= 1 - 1/(2^trials)
  /////////////////////////////////////////////////////////////////////

  return true;
}
