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

#include <string.h>
#include <AD/generic/generic.h>
#include <AD/contain/intset.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructors
//////////////////////////////////////////////////////////////////////////////

IntSet::IntSet( int lim)
{
  limit = (lim + 7)/8;
  array = new Byte [limit];
  clear();
}

//////////////////////////////////////////////////////////////////////////////
//  Copy constructor
//////////////////////////////////////////////////////////////////////////////

IntSet::IntSet( const IntSet& s) : array(0)
{
  *this = s;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

IntSet::~IntSet()
{
  delete [] array;
}

//////////////////////////////////////////////////////////////////////////////
//  Initialization
//////////////////////////////////////////////////////////////////////////////

IntSet& IntSet::clear()
{
  for (int i = limit - 1; i >= 0; i--)
    array[i] = 0;
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////////////////

IntSet& IntSet::operator = (const IntSet& s)
{
  if (this != &s)
  {
    if (array)
      delete [] array;
    array = new Byte[limit = s.limit];
    memcpy(array,s.array,limit);
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Count the number of 1 bits.
//////////////////////////////////////////////////////////////////////////////

int IntSet::size() const
{
  register int count = 0, c;
  for (register int i = limit-1; i >= 0; i--)
    for (c = array[i]; c; c &= c - 1)
      count++;
  return count;
}

//////////////////////////////////////////////////////////////////////////////
//  Set union
//////////////////////////////////////////////////////////////////////////////

IntSet operator + (const IntSet& s1, const IntSet& s2)
{
  int size = s1.limit > s2.limit ? s1.limit : s2.limit;
  IntSet result(size * 8);
  for (register int i = size-1; i >= 0; i--)
    result.array[i] = s1.array[i] | s2.array[i];
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Set intersection
//////////////////////////////////////////////////////////////////////////////

IntSet operator * (const IntSet& s1, const IntSet& s2)
{
  int size = s1.limit > s2.limit ? s1.limit : s2.limit;
  IntSet result(size * 8);
  for (register int i = size-1; i >= 0; i--)
    result.array[i] = s1.array[i] & s2.array[i];
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  Set difference
//////////////////////////////////////////////////////////////////////////////

IntSet operator - (const IntSet& s1, const IntSet& s2)
{
  int size = s1.limit > s2.limit ? s1.limit : s2.limit;
  IntSet result(size * 8);
  for (register int i = size-1; i >= 0; i--)
    result.array[i] = s1.array[i] & ~s2.array[i];
  return result;
}

//////////////////////////////////////////////////////////////////////////////
//  In place union
//////////////////////////////////////////////////////////////////////////////

IntSet& IntSet::operator += (const IntSet& s)
{
  for (register int i = limit-1; i >= 0; i--)
    array[i] |= s.array[i];
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  In place intersection
//////////////////////////////////////////////////////////////////////////////

IntSet& IntSet::operator *= (const IntSet& s)
{
  for (register int i = limit-1; i >= 0; i--)
    array[i] &= s.array[i];
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  In place difference
//////////////////////////////////////////////////////////////////////////////

IntSet& IntSet::operator -= (const IntSet& s)
{
  for (register int i = limit-1; i >= 0; i--)
    array[i] &= ~s.array[i];
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Growing an integer set
//////////////////////////////////////////////////////////////////////////////

IntSet& IntSet::grow (int new_capacity)
{
  int new_size  = (new_capacity + 7) / 8;
  if (new_size > limit)
  {
    Byte * new_array = new Byte [new_size];
    int i;
    for (i = 0; i < limit; i++)
      new_array[i] = array[i];
    for ( ; i < new_size; i++)
      new_array[i] = 0;
    delete [] array;
    array = new_array;
    limit = new_size;
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Hashing function
//////////////////////////////////////////////////////////////////////////////

unsigned int hash(const IntSet& a)
{
  unsigned int h = 0;
  for (int i = a.limit - 1; i >= 0; i--)
    h += a.array[i];
  return h;
}

//////////////////////////////////////////////////////////////////////////////
//  Equality function
//////////////////////////////////////////////////////////////////////////////

Bool equal(const IntSet& a, const IntSet& b)
{
  int limit = a.limit < b.limit ? a.limit : b.limit;
  int i;
  for (i = limit - 1; i >= 0; i--)
    if (a.array[i] != b.array[i])
      return false;
  for (i = limit; i <= a.limit; i++)
    if (a.array[i] != 0)
      return false;
  for (i = limit; i <= b.limit; i++)
    if (b.array[i] != 0)
      return false;
  return true;
}
