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

#ifndef hashing_and_ordering_functions_h
#define hashing_and_ordering_functions_h

#include <string.h>
#include <AD/generic/generic.h>

////////////////////////////////////////////////////////////////////////////
//  Some default hashing functions
////////////////////////////////////////////////////////////////////////////

inline unsigned int hash(char c)           { return c; }
inline unsigned int hash(unsigned char c)  { return c; }
inline unsigned int hash(int i)            { return i; }
inline unsigned int hash(unsigned int i)   { return i; }
inline unsigned int hash(short i)          { return i; }
inline unsigned int hash(unsigned short i) { return i; }
inline unsigned int hash(long i)           { return i; }
inline unsigned int hash(unsigned long i)  { return i; }
inline unsigned int hash(float d)          { return (unsigned int)d; }
inline unsigned int hash(double d)         { return (unsigned int)d; }
extern unsigned int hash(const char *);

////////////////////////////////////////////////////////////////////////////
//  Some default equality functions
////////////////////////////////////////////////////////////////////////////

inline Bool equal(char i, char j)                     { return i == j; }
inline Bool equal(unsigned char i, unsigned char j)   { return i == j; }
inline Bool equal(short i, short j)                   { return i == j; }
inline Bool equal(unsigned short i, unsigned short j) { return i == j; }
inline Bool equal(int i, int j)                       { return i == j; }
inline Bool equal(unsigned int i, unsigned int j)     { return i == j; }
inline Bool equal(long i, long j)                     { return i == j; }
inline Bool equal(unsigned long i, unsigned long j)   { return i == j; }
inline Bool equal(float a, float b)                   { return a == b; }
inline Bool equal(double a, double b)                 { return a == b; }
inline Bool equal(const char * a, const char * b) { return strcmp(a,b) == 0; }

////////////////////////////////////////////////////////////////////////////
//  Some default ordering functions
////////////////////////////////////////////////////////////////////////////

inline Bool less(long i, long j)                   { return i < j; }
inline Bool less(short i, short j)                 { return i < j; }
inline Bool less(int i, int j)                     { return i < j; }
inline Bool less(double a, double b)               { return a < b; }
inline Bool less(const char * a, const char * b)   { return strcmp(a,b) < 0; }
inline Bool lesseq(long i, long j)                 { return i <= j; }
inline Bool lesseq(double a, double b)             { return a <= b; }
inline Bool lesseq(const char * a, const char * b) { return strcmp(a,b) <= 0; }
inline int compare(int i, int j)                   { return i - j; }
inline int compare(short i, short j)               { return i - j; }
inline int compare(long i, long j)                 { return i - j; }
inline int compare(double a, double b)
    { return a == b ? 0 : (a > b ? 1 : 0); }
inline int compare(float a, float b)
    { return a == b ? 0 : (a > b ? 1 : 0); }
inline int compare(const char * a, const char * b) { return strcmp(a,b); }

////////////////////////////////////////////////////////////////////////////
//  Constants used by hash table implementations.
////////////////////////////////////////////////////////////////////////////

#define Cell_unused  0
#define Cell_used    1
#define Cell_deleted 2

/////////////////////////////////////////////////////////////////////////////
// This class represents a linear ordering parameterized by the type.
/////////////////////////////////////////////////////////////////////////////

template <class T>
class Ordering
{
public:
  Ordering() {}
  ~Ordering() {}
  int compare(const T&, const T&)        const;  // user defined
  Bool less(const T& a, const T& b)      const { return compare(a,b) < 0; }
  Bool greater(const T& a, const T& b)   const { return compare(a,b) > 0; }
  Bool lesseq(const T& a, const T& b)    const { return compare(a,b) <= 0; }
  Bool greatereq(const T& a, const T& b) const { return compare(a,b) >= 0; }
};

/////////////////////////////////////////////////////////////////////////////
//  A macro to generate an ordering.  Inlined to allow multiple definition.
/////////////////////////////////////////////////////////////////////////////

#define MakeOrdering(TYPE, comparison_expression) \
  inline int Ordering<TYPE>::compare(const TYPE& a, const TYPE& b) const \
    { return (comparison_expression); }

#endif
