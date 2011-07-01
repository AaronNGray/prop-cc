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

#ifndef indexable_h
#define indexable_h

//////////////////////////////////////////////////////////////////////////
//  Indexable<T> is a type of array-like objects that can grow or shrink.
//////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>  // generic definitions
#include <AD/generic/tables.h>   // tables of Fibonacci numbers

////////////////////////////////////////////////////////////////////////
// Class Indexable<T> is actually implemented as a bi-level table.
// The first level is an index into a second level tables.
// The second level tables are allocated only if needed.
////////////////////////////////////////////////////////////////////////

template <class T>
class Indexable
{
protected:

  T **      table;             // a bi-level index.
  int       segments;          // number of segments currently allocated.
  int       limit;             // current limit
  const int Max_segments = 32;

  /////////////////////////////////////////////////////////////////
  // Constructors and destructor
  /////////////////////////////////////////////////////////////////

public:
  Indexable();
  Indexable(const Indexable&);
  Indexable(int n, const T []);
  ~Indexable();

  /////////////////////////////////////////////////////////////////
  // Assignment
  /////////////////////////////////////////////////////////////////

  Indexable& operator = (const Indexable&);

  /////////////////////////////////////////////////////////////////
  // Selectors
  /////////////////////////////////////////////////////////////////

  inline int size() const
  {
    return limit;
  }

  inline int length() const
  {
    return limit;
  }

  inline int capacity() const
  {
    return limit;
  }

  inline int lo() const
  {
    return 0;
  }

  inline int hi() const
  {
    return limit - 1;
  }

  const T& operator [] (int i) const;
  T& operator [] (int i);

  /////////////////////////////////////////////////////////////////
  // Mutators
  /////////////////////////////////////////////////////////////////

  void clear();
  void resize( int n);

  /////////////////////////////////////////////////////////////////
  // Iterators(active):
  //    Since indexing with operator [] is not the fastest way
  //    to get to the data, we provide an iterator service to the
  //    client.
  /////////////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return Ix(1);
  }

  inline Ix last() const
  {
    return Ix(limit + 1);
  }

  inline Ix next(Ix i) const
  {
    return Ix((int)i+1);
  }

  inline Ix prev(Ix i) const
  {
    return Ix((int)i-1);
  }

  inline const T& operator () (Ix i) const
  {
    return (*this)[(int)i];
  }

  inline T& operator () (Ix i)
  {
    return (*this)[(int)i];
  }
};

//////////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
Indexable<T>::Indexable()
{
  table = new T * [ Max_segments ];
  segments = limit = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Copy constructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
Indexable<T>::Indexable( const Indexable<T>& I)
{
  table = new T * [ Max_segments ];
  segments = limit = 0;
  *this = I;
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
Indexable<T>::Indexable( int n, const T t[])
{
  table = new T * [ Max_segments ];
  segments = limit = 0;
  resize(n);
  register const T * a = t;
  for (int i = 0; i < segments; i++)
  {
    register T * b = tables[i];
    for (register int j = fibnacci[i+5] - 1; j >= 0; j--)
      *b++ = *a++;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
Indexable<T>::~Indexable()
{
  clear();
  delete [] table;
}

//////////////////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////////////////

template <class T>
Indexable<T>& Indexable<T>::operator = (const Indexable<T>& t)
{
  if (this != &t)
  {
    resize(t.length());
    for (int i = 0; i < segments; i++)
    {
      register const T * a = t.tables[i];
      register T * b = tables[i];
      for (register int j = fibnacci[i+5] - 1; j >= 0; j--)
        *b++ = *a++;
    }
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Clear
//////////////////////////////////////////////////////////////////////////////

template <class T>
void Indexable<T>::clear()
{
  for (int i = segments - 1; i >= 0; i--)
    delete [] table[i];
  limit = segments = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Indexing
//////////////////////////////////////////////////////////////////////////////

template <class T>
const T& Indexable<T>::operator [] (int i) const
{
  for (int j = 0; j < Max_segments; j++)
    if (fibonacci[j+6] > i)
      break;
  return tables[j][ i - fibonacci[j+5] ];
}

//////////////////////////////////////////////////////////////////////////////
//  Indexing
//////////////////////////////////////////////////////////////////////////////

template <class T>
T& Indexable<T>::operator [] (int i)
{
  if (i >= limit)
    resize(i);
  for (int j = 0; j < Max_segments; j++)
    if (fibonacci[j+6] > i)
      break;
  return tables[j][ i - fibonacci[j+5] ];
}

//////////////////////////////////////////////////////////////////////////////
//  Resizing
//////////////////////////////////////////////////////////////////////////////

template <class T>
void Indexable<T>::resize(int n)
{
  if (n < limit)
    return;
  while (fibonacci[segments+6] < n)
  {
    table[segments] = new T fibonacci[segments+5];
    segments++;
  }
  limit = fibonacci[segments+6];
}

#endif
