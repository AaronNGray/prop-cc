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

#ifndef sequence_h
#define sequence_h

//////////////////////////////////////////////////////////////////////////
// Sequences and subsequences\cite{subseq}.
//////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>   // Generic definitions

//////////////////////////////////////////////////////////////////////////
// Forward declarations
//////////////////////////////////////////////////////////////////////////

template <class T> class Seq;
template <class T> class SubSeq;

//////////////////////////////////////////////////////////////////////////
// Class |SubSequence|
//////////////////////////////////////////////////////////////////////////

template <class T>
class SubSeq
{
  friend class Seq<T>;
  Seq<T>& base;         // The base sequence
  int left, right;      // left and right std::ends of the subsequence

  SubSeq(Seq<T>& s, int l, int r) : base(s), left(l), right(r)
  {}

  ///////////////////////////////////////////////////////////////////
  //  Conversion
  ///////////////////////////////////////////////////////////////////

public:
  operator const T * () const
  {
    return (const T *)base + left;
  }

  ///////////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////////

  int length() const
  {
    return right - left + 1;
  }
  Bool is_empty() const
  {
    return right < left;
  }

  T& head()
  {
    return base[left];
  }

  const T& head() const
  {
    return base[left];
  }

  T& tail()
  {
    return base[right];
  }

  const T& tail() const
  {
    return base[right];
  }

  const T& operator [] (int i) const
  {
    return base[left + i];
  }

  T& operator [] (int i)
  {
    return base[left + i];
  }

  SubSeq<T> operator () (int i, int j) const
  {
    return SubSeq<T>(base,left + i, left + j);
  }

  ///////////////////////////////////////////////////////////////////
  // Assignment
  ///////////////////////////////////////////////////////////////////

  Seq<T>& operator = (const T&);
  Seq<T>& operator = (const Seq<T>&);
  Seq<T>& operator = (const SubSeq&);

  Seq<T> operator += (const T&);
  Seq<T> operator += (const Seq<T>&);
  Seq<T> operator += (const SubSeq&);
};

///////////////////////////////////////////////////////////////////////////
//  Class Seq<T>
///////////////////////////////////////////////////////////////////////////

template <class T>
class Seq
{
  friend class SubSeq<T>;

  int size;      // logical length of sequence
  int capacity;  // actual capacity of sequence
  T * list;      // the array of elements

  ///////////////////////////////////////////////////////////////////
  // Constructor and destructors
  ///////////////////////////////////////////////////////////////////

public:
  Seq() : list(0), size(0), capacity(0)
  {}
  Seq(const Seq& s) : list(0)
  {
    *this = s;
  }
  Seq(const SubSeq<T>& s) : list(0)
  {
    *this = s;
  }
  Seq(const T&, int copies = 1);
  ~Seq()
  {
    delete [] list;
  }

  ///////////////////////////////////////////////////////////////////
  // Conversion
  ///////////////////////////////////////////////////////////////////

  operator const T* () const
  {
    return list;
  }

  ///////////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////////

  int length() const
  {
    return size;
  }

  Bool is_empty() const
  {
    return size == 0;
  }

  T& head() const
  {
    return list[0];
  }

  T& tail() const
  {
    return list[size-1];
  }

  const T& operator [] (int i) const
  {
    return list[i];
  }

  T& operator [] (int i)
  {
    return list[i];
  }

  SubSeq<T> operator () (int i, int j)
  {
    return SubSeq<T>(*this,i,j);
  }

  ///////////////////////////////////////////////////////////////////
  // Assigment
  ///////////////////////////////////////////////////////////////////

  Seq& operator = (const Seq&);
  Seq& operator = (const SubSeq<T>&);

  ///////////////////////////////////////////////////////////////////
  // Concatenation
  ///////////////////////////////////////////////////////////////////

  friend Seq operator + (const Seq&, const Seq&);
  friend Seq operator + (const T&, const Seq&);
  friend Seq operator + (const Seq&, const T&);
  friend Seq operator + (const Seq&, const SubSeq<T>&);
  friend Seq operator + (const SubSeq<T>&, const Seq&);
  friend Seq operator + (const SubSeq<T>&, const SubSeq<T>&);
  friend Seq operator + (const T&, const SubSeq<T>&);
  friend Seq operator + (const SubSeq<T>&, const T&);

  ///////////////////////////////////////////////////////////////////
  // Append to end
  ///////////////////////////////////////////////////////////////////

  Seq& operator += (const T&);
  Seq& operator += (const Seq&);
  Seq& operator += (const SubSeq<T>&);

  ///////////////////////////////////////////////////////////////////
  // Iterators
  ///////////////////////////////////////////////////////////////////

  Ix first() const
  {
    return Ix(size > 0 ? list : 0);
  }

  Ix last() const
  {
    return Ix(size > 0 ? list + size - 1 : 0);
  }

  Ix next(Ix i) const
  {
    return (T*)i < ((T*)list) + size
           ? ((T*)i)+1 : (T*)0;
  }

  Ix prev(Ix i) const
  {
    return i > (Ix)list ? (T*)i-1 : 0;
  }

  T& operator () (Ix i) const
  {
    return *(T*)i;
  }
};

//////////////////////////////////////////////////////////////////////////
// Implementation of the template methods
//////////////////////////////////////////////////////////////////////////

template <class T>
Seq<T>::Seq(const T& e, int copies)
    : size(copies), capacity(copies), list(new T [copies])
{
  for (register int i = copies - 1; i >= 0; i--)
    list[i] = e;
}

template <class T>
Seq<T>& Seq<T>::operator = (const Seq<T>& s)
{
  return *this;
}

template <class T>
Seq<T>& Seq<T>::operator = (const SubSeq<T>& s)
{
  return *this;
}

#endif
