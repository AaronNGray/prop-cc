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

#ifndef variable_precision_integer_h
#define variable_precision_integer_h

//////////////////////////////////////////////////////////////////////
//  Class BigInt is a variable precision integer type.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <new>
#include <AD/generic/generic.h>  // Generic definitions


class BigInt
{
public:

  //////////////////////////////////////////////////////////////////////
  //  BigInt is represented in a sign/magnitude format.
  //  For stupid reasons, we'll have to export this definition to
  //  the client.
  //////////////////////////////////////////////////////////////////////
  struct a_BigInt
  {

    typedef unsigned short Digit;  // 16 bits per digit
    typedef unsigned long  Unit;   // 32 bits for computation

    int   sign;      // sign of the number: 0, +1, or -1.
    int   len;       // number of digits currently used
    int   capacity;  // number of digits available in array
    Digit digits[1]; // array of digits; the least significant is at index 0

    //////////////////////////////////////////////////////////////////////
    // Internal memory manager
    //////////////////////////////////////////////////////////////////////
    void * operator new    (size_t, int);
    void   operator delete (void *);

    //////////////////////////////////////////////////////////////////////
    // These procedures work on the internal representation and
    // are the ones actually doing the dirty work.
    //////////////////////////////////////////////////////////////////////
    friend a_BigInt * copy(a_BigInt *, const a_BigInt *);
    friend a_BigInt * copy(a_BigInt *, long, int = 1);
    friend a_BigInt * neg(a_BigInt *, const a_BigInt *);
    friend a_BigInt * addsub(a_BigInt *, const a_BigInt *, const a_BigInt *, Bool);
    friend a_BigInt * addsub(a_BigInt *, const a_BigInt *, long, Bool);
    friend a_BigInt * addsub(a_BigInt *, long, const a_BigInt *, Bool);
    friend a_BigInt * mul(a_BigInt *, const a_BigInt *, const a_BigInt *);
    friend a_BigInt * mul(a_BigInt *, const a_BigInt *, long);
    friend a_BigInt * div(a_BigInt *, const a_BigInt *, const a_BigInt *);
    friend a_BigInt * div(a_BigInt *, const a_BigInt *, long);
    friend a_BigInt * div(a_BigInt *, long, const a_BigInt *);
    friend a_BigInt * mod(a_BigInt *, const a_BigInt *, const a_BigInt *);
    friend a_BigInt * mod(a_BigInt *, const a_BigInt *, long);
    friend a_BigInt * mod(a_BigInt *, long, const a_BigInt *);
    friend a_BigInt * andor(a_BigInt *, const a_BigInt *, const a_BigInt *,char);
    friend a_BigInt * andor(a_BigInt *, const a_BigInt *, long, char);
    friend a_BigInt * bitnot(a_BigInt *, const a_BigInt *);
    friend a_BigInt * shift(a_BigInt *, const a_BigInt *, const a_BigInt *, int);
    friend a_BigInt * shift(a_BigInt *, const a_BigInt *, long, int);
    friend a_BigInt * shift(a_BigInt *, long, const a_BigInt *, int);
    friend int       cmp(const a_BigInt *, const a_BigInt *);
    friend int       cmp(const a_BigInt *, long);
  };

private:

  //////////////////////////////////////////////////////////////////////
  //  A BigInt is just a pointer to its representation.
  //  Since zero is a common value and used for initialization
  //  a special zero value is provided.   This is hidden for
  //  your protection!
  //////////////////////////////////////////////////////////////////////
  static a_BigInt * zero;


public:
  a_BigInt * D;
  BigInt(a_BigInt * d) : D(d)
  {}  // for internal use only

  ////////////////////////////////////////////////////////////////////////
  //  Error handler
  ////////////////////////////////////////////////////////////////////////
  static void (*error_handler)(const char []);

  ////////////////////////////////////////////////////////////////////////
  // Constructors and destructors
  ////////////////////////////////////////////////////////////////////////

  inline  BigInt() : D(zero)
  { }                   // i.e. BigInt n;
  inline  BigInt(const BigInt& n)
  {
    D = copy(0,n);
  }    // i.e. BigInt n = m;
  inline  BigInt(int n)
  {
    D = copy(0,n);
  }    // i.e. BigInt n = 1;
  BigInt(const char *);          // i.e. BigInt n = "12345";
  inline ~BigInt()
  {
    delete D;
  }

  ////////////////////////////////////////////////////////////////////////
  // Conversions: double() converts a BigInt to a double
  // Conversions: long() converts a BigInt to a long with truncation
  ////////////////////////////////////////////////////////////////////////
  operator double () const;

  ////////////////////////////////////////////////////////////////////////
  // Assignments
  ////////////////////////////////////////////////////////////////////////
  inline BigInt& operator = (const BigInt& n)
  {
    D = copy(D,n.D);
    return *this;
  }
  inline BigInt& operator = (const int n)
  {
    D = copy(D,n);
    return *this;
  }
  BigInt& operator = (const char *);

  ////////////////////////////////////////////////////////////////////////
  // Attributes of a BigInt
  ////////////////////////////////////////////////////////////////////////
  inline int  sign   () const
  {
    return D->sign;
  }
  inline Bool isEven () const
  {
    return (D->digits[0] & 1) == 0;
  }
  inline Bool isOdd  () const
  {
    return D->digits[0] & 1;
  }
  inline int  operator [] (int i) const
  {
    return D->digits[i/16] & (1 << (i & 15));
  }
  inline int  radix  () const
  {
    return 1 << (8 * sizeof(a_BigInt::Digit));
  }
  inline int  length () const;

  ////////////////////////////////////////////////////////////////////////
  // Arithmetic operators
  ////////////////////////////////////////////////////////////////////////
  friend BigInt abs         (const BigInt&);
  friend BigInt operator -  (const BigInt&);
  friend BigInt operator +  (const BigInt&, const BigInt&);
  friend BigInt operator +  (int, const BigInt&);
  friend BigInt operator +  (const BigInt&, int);
  friend BigInt operator -  (const BigInt&, const BigInt&);
  friend BigInt operator -  (int, const BigInt&);
  friend BigInt operator -  (const BigInt&, int);
  friend BigInt operator *  (const BigInt&, const BigInt&);
  friend BigInt operator *  (int, const BigInt&);
  friend BigInt operator *  (const BigInt&, int);
  friend BigInt operator /  (const BigInt&, const BigInt&);
  friend BigInt operator /  (int, const BigInt&);
  friend BigInt operator /  (const BigInt&, int);
  friend BigInt operator %  (const BigInt&, const BigInt&);
  friend BigInt operator %  (int, const BigInt&);
  friend BigInt operator %  (const BigInt&, int);
  friend void   div_mod     (const BigInt&, const BigInt&, BigInt&, BigInt&);
  friend BigInt operator << (const BigInt&, const BigInt&);
  friend BigInt operator << (int, const BigInt&);
  friend BigInt operator << (const BigInt&, int);
  friend BigInt operator >> (const BigInt&, const BigInt&);
  friend BigInt operator >> (int, const BigInt&);
  friend BigInt operator >> (const BigInt&, int);
  friend BigInt operator |  (const BigInt&, const BigInt&);
  friend BigInt operator |  (int, const BigInt&);
  friend BigInt operator |  (const BigInt&, int);
  friend BigInt operator &  (const BigInt&, const BigInt&);
  friend BigInt operator &  (int, const BigInt&);
  friend BigInt operator &  (const BigInt&, int);
  friend BigInt operator ^  (const BigInt&, const BigInt&);
  friend BigInt operator ^  (int, const BigInt&);
  friend BigInt operator ^  (const BigInt&, int);
  //   friend BigInt not         (const BigInt&);
  friend BigInt complement  (const BigInt&);
  friend unsigned int hash  (const BigInt&);

  ///////////////////////////////////////////////////////////
  // Single bit operations
  ///////////////////////////////////////////////////////////
  inline int nthBit(int nth) const
  {
    return D->digits[nth/16] & (1 << (nth & 15));
  }
  inline void setBit(int nth)
  {
    D->digits[nth/16] |= (1 << (nth & 15));
  }
  inline void clearBit(int nth)
  {
    D->digits[nth/16] &= ~(1 << (nth & 15));
  }

  ///////////////////////////////////////////////////////////
  // In place operations are inlined for efficiency
  ///////////////////////////////////////////////////////////
  inline void operator ++ (int)
  {
    D = addsub(D,D,1,false);
  }
  inline void operator -- (int)
  {
    D = addsub(D,D,1,true);
  }
  inline void operator ++  ()
  {
    D = addsub(D,D,1,false);
  }
  inline void operator --  ()
  {
    D = addsub(D,D,1,true);
  }

  inline void abs ()
  {
    if (D->sign == -1)
      D = neg(D,D);
  }
  inline void negate ()
  {
    D = neg(D,D);
  }
  //   inline void not()       { D = bitnot(D,D); }
  inline void complement()
  {
    D = bitnot(D,D);
  }
  inline void operator += (const BigInt& n)
  {
    D = addsub(D,D,n.D,false);
  }
  inline void operator -= (const BigInt& n)
  {
    D = addsub(D,D,n.D,true);
  }
  inline void operator *= (const BigInt& n)
  {
    D = mul(D,D,n.D);
  }
  inline void operator /= (const BigInt& n)
  {
    D = div(D,D,n.D);
  }
  inline void operator %= (const BigInt& n)
  {
    D = mod(D,D,n.D);
  }
  inline void operator <<=(const BigInt& n)
  {
    D = shift(D,D,n.D,1);
  }
  inline void operator >>=(const BigInt& n)
  {
    D = shift(D,D,n.D,-1);
  }
  inline void operator |= (const BigInt& n)
  {
    D = andor(D,D,n.D,'|');
  }
  inline void operator &= (const BigInt& n)
  {
    D = andor(D,D,n.D,'&');
  }
  inline void operator ^= (const BigInt& n)
  {
    D = andor(D,D,n.D,'^');
  }
  inline void operator += (int n)
  {
    D = addsub(D,D,n,false);
  }
  inline void operator -= (int n)
  {
    D = addsub(D,D,n,true);
  }
  inline void operator *= (int n)
  {
    D = mul(D,D,n);
  }
  inline void operator /= (int n)
  {
    D = div(D,D,n);
  }
  inline void operator %= (int n)
  {
    D = mod(D,D,n);
  }
  inline void operator <<=(int n)
  {
    D = shift(D,D,n,1);
  }
  inline void operator >>=(int n)
  {
    D = shift(D,D,n,-1);
  }
  inline void operator |= (int n)
  {
    D = andor(D,D,n,'|');
  }
  inline void operator &= (int n)
  {
    D = andor(D,D,n,'&');
  }
  inline void operator ^= (int n)
  {
    D = andor(D,D,n,'^');
  }

  ///////////////////////////////////////////////////////////
  // Comparisons are inlined for efficiency
  ///////////////////////////////////////////////////////////
  inline friend Bool operator == (const BigInt& a, const BigInt& b)
  {
    return cmp(a.D,b.D) == 0;
  }
  inline friend Bool operator == (const BigInt& a, int b)
  {
    return cmp(a.D,b) == 0;
  }
  inline friend Bool operator == (int a, const BigInt& b)
  {
    return cmp(b.D,a) == 0;
  }
  inline friend Bool operator != (const BigInt& a, const BigInt& b)
  {
    return cmp(a.D,b.D) != 0;
  }
  inline friend Bool operator != (const BigInt& a, int b)
  {
    return cmp(a.D,b) != 0;
  }
  inline friend Bool operator != (int a, const BigInt& b)
  {
    return cmp(b.D,a) != 0;
  }
  inline friend Bool operator > (const BigInt& a, const BigInt& b)
  {
    return cmp(a.D,b.D) > 0;
  }
  inline friend Bool operator > (const BigInt& a, int b)
  {
    return cmp(a.D,b) > 0;
  }
  inline friend Bool operator > (int a, const BigInt& b)
  {
    return cmp(b.D,a) <= 0;
  }
  inline friend Bool operator < (const BigInt& a, const BigInt& b)
  {
    return cmp(a.D,b.D) < 0;
  }
  inline friend Bool operator < (const BigInt& a, int b)
  {
    return cmp(a.D,b) < 0;
  }
  inline friend Bool operator < (int a, const BigInt& b)
  {
    return cmp(b.D,a) >= 0;
  }
  inline friend Bool operator >= (const BigInt& a, const BigInt& b)
  {
    return cmp(a.D,b.D) >= 0;
  }
  inline friend Bool operator >= (const BigInt& a, int b)
  {
    return cmp(a.D,b) >= 0;
  }
  inline friend Bool operator >= (int a, const BigInt& b)
  {
    return cmp(b.D,a) < 0;
  }
  inline friend Bool operator <= (const BigInt& a, const BigInt& b)
  {
    return cmp(a.D,b.D) <= 0;
  }
  inline friend Bool operator <= (const BigInt& a, int b)
  {
    return cmp(a.D,b) <= 0;
  }
  inline friend Bool operator <= (int a, const BigInt& b)
  {
    return cmp(b.D,a) > 0;
  }

  ///////////////////////////////////////////////////////////
  //  Miscellaneous arithmetic
  ///////////////////////////////////////////////////////////
  friend BigInt gcd         (BigInt, BigInt);
  friend BigInt sqrt        (const BigInt&);
  friend BigInt pow         (const BigInt&, const BigInt&);
  friend BigInt pow_mod     (const BigInt&, const BigInt&, const BigInt&);
  friend BigInt make_random (const BigInt& limit);

  ///////////////////////////////////////////////////////////
  // I/O and string conversion
  ///////////////////////////////////////////////////////////
  char * makeString (char [], size_t length = 1024,
                     unsigned int base = 10) const;
  int parseString (const char *, unsigned int base = 10);
  friend std::ostream& operator << (std::ostream&, const BigInt&);
  friend std::istream& operator >> (std::istream&, BigInt&);
};

///////////////////////////////////////////////////////////////////////////
//  Binary and unary operators are inlined for efficiency.
//  G++ has a non-standard syntax for faster returning of inline values
//  that eliminate unnecessary copying.  We'll provided a version with this
//  special optimization and one without for non G++ compilers.
///////////////////////////////////////////////////////////////////////////
inline BigInt abs         (const BigInt& a)
{
  return BigInt(a.D->sign == -1 ? neg(0,a.D) : copy(0,a.D));
}
inline BigInt operator -  (const BigInt& a)
{
  return BigInt(neg(0,a.D));
}
inline BigInt operator +  (const BigInt& a, const BigInt& b)
{
  return BigInt(addsub(0,a.D,b.D,false));
}
inline BigInt operator +  (long a, const BigInt& b)
{
  return BigInt(addsub(0,b.D,a,false));
}
inline BigInt operator +  (const BigInt& a, long b)
{
  return BigInt(addsub(0,a.D,b,false));
}
inline BigInt operator -  (const BigInt& a, const BigInt& b)
{
  return BigInt(addsub(0,a.D,b.D,true));
}
inline BigInt operator -  (int a, const BigInt& b)
{
  return BigInt(addsub(0,a,b.D,true));
}
inline BigInt operator -  (const BigInt& a, int b)
{
  return BigInt(addsub(0,a.D,b,true));
}
inline BigInt operator *  (const BigInt& a, const BigInt& b)
{
  return BigInt(mul(0,a.D,b.D));
}
inline BigInt operator *  (long a, const BigInt& b)
{
  return BigInt(mul(0,b.D,a));
}
inline BigInt operator *  (const BigInt& a, int b)
{
  return BigInt(mul(0,a.D,b));
}
inline BigInt operator /  (const BigInt& a, const BigInt& b)
{
  return BigInt(div(0,a.D,b.D));
}
inline BigInt operator /  (int a, const BigInt& b)
{
  return BigInt(div(0,a,b.D));
}
inline BigInt operator /  (const BigInt& a, long b)
{
  return BigInt(div(0,a.D,b));
}
inline BigInt operator %  (const BigInt& a, const BigInt& b)
{
  return BigInt(mod(0,a.D,b.D));
}
inline BigInt operator %  (int a, const BigInt& b)
{
  return BigInt(mod(0,a,b.D));
}
inline BigInt operator %  (const BigInt& a, int b)
{
  return BigInt(mod(0,a.D,b));
}
inline BigInt operator << (const BigInt& a, const BigInt& b)
{
  return BigInt(shift(0,a.D,b.D,1));
}
inline BigInt operator << (int a, const BigInt& b)
{
  return BigInt(shift(0,a,b.D,1));
}
inline BigInt operator << (const BigInt& a, int b)
{
  return BigInt(shift(0,a.D,b,1));
}
inline BigInt operator >> (const BigInt& a, const BigInt& b)
{
  return BigInt(shift(0,a.D,b.D,-1));
}
inline BigInt operator >> (int a, const BigInt& b)
{
  return BigInt(shift(0,a,b.D,-1));
}
inline BigInt operator >> (const BigInt& a, int b)
{
  return BigInt(shift(0,a.D,b,-1));
}
inline BigInt operator |  (const BigInt& a, const BigInt& b)
{
  return BigInt(andor(0,a.D,b.D,'|'));
}
inline BigInt operator |  (long a, const BigInt& b)
{
  return BigInt(andor(0,b.D,a,'|'));
}
inline BigInt operator |  (const BigInt& a, long b)
{
  return BigInt(andor(0,a.D,b,'|'));
}
inline BigInt operator &  (const BigInt& a, const BigInt& b)
{
  return BigInt(andor(0,a.D,b.D,'&'));
}
inline BigInt operator &  (long a, const BigInt& b)
{
  return BigInt(andor(0,b.D,a,'&'));
}
inline BigInt operator &  (const BigInt& a, long b)
{
  return BigInt(andor(0,a.D,b,'&'));
}
inline BigInt operator ^  (const BigInt& a, const BigInt& b)
{
  return BigInt(andor(0,a.D,b.D,'^'));
}
inline BigInt operator ^  (long a, const BigInt& b)
{
  return BigInt(andor(0,b.D,a,'^'));
}
inline BigInt operator ^  (const BigInt& a, long b)
{
  return BigInt(andor(0,a.D,b,'^'));
}
//   inline BigInt not         (const BigInt& a)  { return BigInt(bitnot(0,a.D)); }
inline BigInt complement  (const BigInt& a)
{
  return BigInt(bitnot(0,a.D));
}

#endif
