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

#ifndef byte_array_h
#define byte_array_h

#include <AD/generic/generic.h>   // Generic definitions

class ByteArray
{
protected:
  int size;          // number of bytes, logically from clients view
  int units;         // number of long words allocated
  LongWord * array;  // The actual byte array, in 4-byte units

  ////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  ////////////////////////////////////////////////////////////////////

public:
  ByteArray(int length = 0);
  ByteArray(const Byte [], int size);
  ByteArray(const char []);
  ByteArray(const ByteArray&);
  ~ByteArray()
  {
    delete [] array;
  }

  ////////////////////////////////////////////////////////////////////
  // Assignment
  ////////////////////////////////////////////////////////////////////

  void operator = (const ByteArray&);

  ////////////////////////////////////////////////////////////////////
  // Selectors
  ////////////////////////////////////////////////////////////////////

  int length() const
  {
    return size;
  }
  operator Byte * () const
  {
    return (Byte*)array;
  }
  Byte& operator [] (int i) const
  {
    return ((Byte*)array)[i];
  }
  LongWord& operator () (int i) const
  {
    return array[i];
  }
  int bit(unsigned int nth) const
  {
    return bitOf((Byte*)array, nth);
  }

  ////////////////////////////////////////////////////////////////////
  // Concatenation between two byte arrays
  ////////////////////////////////////////////////////////////////////

  ByteArray operator || (const ByteArray&) const;

  ////////////////////////////////////////////////////////////////////
  // Destructive arithmetic and logical operations
  ////////////////////////////////////////////////////////////////////

  void operator <<= (int shift);
  void operator >>= (int shift);
  void operator |= (const ByteArray&);
  void operator &= (const ByteArray&);
  void operator ^= (const ByteArray&);
  void operator += (const ByteArray&);
  void operator -= (const ByteArray&);
  void onesComplement();
  void twosComplement();

  Bool operator ! ();  // is it all zeros??

  ////////////////////////////////////////////////////////////////////
  // Arithmetic and logical operations
  ////////////////////////////////////////////////////////////////////

  ByteArray operator ~ () const;
  ByteArray operator - () const;
  friend ByteArray operator << (const ByteArray&, int shift);
  friend ByteArray operator >> (const ByteArray&, int shift);
  friend ByteArray operator | (const ByteArray&, const ByteArray&);
  friend ByteArray operator & (const ByteArray&, const ByteArray&);
  friend ByteArray operator + (const ByteArray&, const ByteArray&);
  friend ByteArray operator - (const ByteArray&, const ByteArray&);

  friend Bool operator == (const ByteArray& A, const ByteArray& B);
  friend Bool operator != (const ByteArray& A, const ByteArray& B)
  {
    return ! (A == B);
  }
  friend Bool operator >= (const ByteArray& A, const ByteArray& B);
  friend Bool operator <= (const ByteArray& A, const ByteArray& B);
  friend Bool operator >  (const ByteArray& A, const ByteArray& B)
  {
    return ! (A <= B);
  }
  friend Bool operator <  (const ByteArray& A, const ByteArray& B)
  {
    return ! (A >= B);
  }
};


////////////////////////////////////////////////////////////////////
// Inlined functions for efficiency
////////////////////////////////////////////////////////////////////

inline ByteArray ByteArray :: operator ~ () const
{
  ByteArray A = *this;
  A.onesComplement();
  return A;
}

inline ByteArray operator << (const ByteArray& A, int shift)
{
  ByteArray B = A;
  B <<= shift;
  return B;
}

inline ByteArray operator >> (const ByteArray& A, int shift)
{
  ByteArray B = A;
  B >>= shift;
  return B;
}

inline ByteArray operator | (const ByteArray& A, const ByteArray& B)
{
  ByteArray C = A;
  C |= B;
  return C;
}

inline ByteArray operator & (const ByteArray& A, const ByteArray& B)
{
  ByteArray C = A;
  C &= B;
  return C;
}

inline ByteArray operator + (const ByteArray& A, const ByteArray& B)
{
  ByteArray C = A;
  C += B;
  return C;
}

inline ByteArray operator - (const ByteArray& A, const ByteArray& B)
{
  ByteArray C = A;
  C -= B;
  return C;
}

#endif
