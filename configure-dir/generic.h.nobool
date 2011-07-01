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

#ifndef generic_definitions_h
#define generic_definitions_h

////////////////////////////////////////////////////////////////////////////
//  This file contains all the generic definitions that are used
//  in the rest of the library.
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//  Integer and boolean types. 
////////////////////////////////////////////////////////////////////////////
typedef unsigned long Cardinal;
typedef long Integer;
typedef int Bool;
#define false (Bool)0
#define true  (Bool)1
typedef unsigned char Byte;

////////////////////////////////////////////////////////////////////////////
//  Bit operations.
////////////////////////////////////////////////////////////////////////////
#define bitSet(A,bit) \
   ((A)[((unsigned int)(bit))>>3] |= (1 << ((unsigned int)(bit)&7)))
#define bitClear(A,bit) \
   ((A)[((unsigned int)(bit))>>3] &= ~(1 << ((unsigned int)(bit)&7)))
#define bitOf(A,bit) \
   ((A)[((unsigned int)(bit))>>3] & (1 << ((unsigned int)(bit)&7)))

typedef unsigned short ShortWord;
typedef unsigned long LongWord;

////////////////////////////////////////////////////////////////////////////
//  Type Ix is a generic index used by all the container and collection
//  classes.
////////////////////////////////////////////////////////////////////////////
typedef void * Ix;

////////////////////////////////////////////////////////////////////////////
//  Iterator macros.  These are provided for those who like more meaningful
//  iterator construct.   For example, 
//
//  void print(Set<Person>& employees) 
//  {  foreach(e,employees) {
//        cout << employees(e) << '\n';
//     }
//  }
////////////////////////////////////////////////////////////////////////////
#define foreach(i,C)             for(Ix i = (C).first(); i; i = (C).next(i))
#define foreach_in_reverse(i,C)  for(Ix i = (C).last(); i; i = (C).prev(i))

extern void raise_exn(const char *);
#define __STR(x) __VAL(x)
#define __VAL(x) #x
#define throw(exception) raise_exn("%s" #exception)

#endif
