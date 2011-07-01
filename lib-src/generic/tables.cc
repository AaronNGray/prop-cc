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

#include <AD/generic/tables.h>

const Byte one_bits[] = { 1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7 };
const Byte zero_bits[] = { 255-1, 253-2, 255-4, 255-8,
                           255-16, 255-32, 255-64, 255-128 };
const long fibonacci[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 
                           144, 233, 377, 610, 987, 1597, 2584, 4181, 
                           6765, 10946, 17711, 28657, 46368, 75025, 
                           121393, 196418, 317811, 514229, 832040, 
                           1346269, 2178309, 3524578, 5702887, 9227465, 
                           14930352, 24157817, 39088169, 63245986, 102334155, 
                           165580141, 267914296, 433494437, 701408733, 
                           1134903170, 1836311903
                         };
const long tens[] = { 1, 10, 100, 1000, 10000, 100000, 
                      1000000, 10000000, 100000000 };
