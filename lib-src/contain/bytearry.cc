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

#include <string>
#include <AD/contain/bytearry.h>

ByteArray::ByteArray( int length)
{
  size  = length;
  units = (length + sizeof(LongWord) - 1) / sizeof(LongWord);
  array = new LongWord [units];
}

ByteArray::ByteArray( const Byte A[], int len)
{
  size  = len;
  units = (len + sizeof(LongWord) - 1) / sizeof(LongWord);
  array = new LongWord [units];
  memcpy(array,A,len);
}

ByteArray::ByteArray( const char string[])
{
  size  = strlen(string) + 1;
  units = (size + sizeof(LongWord) - 1) / sizeof(LongWord);
  array = new LongWord [units];
  memcpy(array,string,size);
}

ByteArray::ByteArray( const ByteArray& A) : array(0)
{
  *this = A;
}

void ByteArray :: operator = (const ByteArray& A)
{
  if (this != &A)
  {
    delete [] array;
    size  = A.size;
    units = A.units;
    array = new LongWord [units];
    memcpy(array,A.array,units);
  }
}

// Concatenation between two byte arrays

ByteArray ByteArray :: operator || (const ByteArray&) const
{
  return *this;
}

// Destructive arithmetic and logical operations

void ByteArray :: operator <<= (int shift)
{
  if (shift == 0)
    return;
  else if (shift < 0)
    *this >>= -shift;
}

void ByteArray :: operator >>= (int shift)
{
  if (shift == 0)
    return;
  else if (shift < 0)
    *this <<= -shift;
}

void ByteArray :: operator |= (const ByteArray&)
{}

void ByteArray :: operator &= (const ByteArray&)
{}

void ByteArray :: operator ^= (const ByteArray&)
{  }

void ByteArray :: operator += (const ByteArray&)
{  }

void ByteArray :: operator -= (const ByteArray&)
{   }

void ByteArray :: onesComplement()
{
  register int i;
  for (i = units - 1; i >= 0; i--)
    array[i] ^= 0xffffffff;
}

void ByteArray :: twosComplement()
{   }

Bool ByteArray :: operator ! ()
{
  return false;
}  // is it all zeros??

// Arithmetic and logical operations


Bool operator == (const ByteArray&, const ByteArray&)
{
  return false;
}

Bool operator >= (const ByteArray&, const ByteArray&)
{
  return false;
}

Bool operator <= (const ByteArray&, const ByteArray&)
{
  return false;
}
