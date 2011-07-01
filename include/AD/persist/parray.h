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
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef persistent_arrays_h
#define persistent_arrays_h

#include <new.h>
#include <AD/persist/pstream.h>

//////////////////////////////////////////////////////////////////////////////
//  Method to write an array to the persistent stream.
//////////////////////////////////////////////////////////////////////////////

template <class T>
Postream& write( Postream& s, const T array[], size_t n)
{
  P_int32 len = n;
  s << len;
  for (int i = 0; i < n; i++)
    s << array[i];
  return s;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to read an array from a persistent stream.
//  Returns the number of elements actually read.
//  If the given array is too small then the extra elements are discarded.
//////////////////////////////////////////////////////////////////////////////

template <class T>
int read( Pistream& s, T array[], size_t max)
{
  P_int32 len = 0;
  int i, j;
  s >> len;
  j = len < max ? len : max;
  for (i = 0; i < j; i++)
    s >> array[i];
  T dummy;
  for ( ; j < len; j++)
    s >> dummy;
  return i;
}

#endif
