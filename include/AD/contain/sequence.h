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

#ifndef applicative_sequence_h
#define applicative_sequence_h

////////////////////////////////////////////////////////////////////////////
//  Class Sequence<T> allows the user to construct lists of a homogeneous
//  type.  These lists are all applicative in nature and concatenation
//  can be accomplished in O(1) time.   The lists are also symetric
//  in nature and is not biased toward one end as is in the traditional
//  representation.
////////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>

template <class T>
class Sequence
{
  struct SeqRep
  {
    int              ref_count;  // reference count
    int              len;        // length of the array
    const Sequence * left;       // left link
    const Sequence * right;      // right link
    const T        * array;      // array of elements
  };

  SeqRep * list;            // pointer to actual representation

public:

  /////////////////////////////////////////////////////////////
  // Constructor and destructor
  /////////////////////////////////////////////////////////////
  Sequence();
  Sequence(const Sequence&);
  Sequence(const T&);
  Sequence(const T[]);
  ~Sequence();

  /////////////////////////////////////////////////////////////
  // Subsequence:
  /////////////////////////////////////////////////////////////

  Sequence operator () (int i, int j) const;

  /////////////////////////////////////////////////////////////
  // Selectors
  /////////////////////////////////////////////////////////////

  const T& operator [] (int i) const;
  int      length() const;

  /////////////////////////////////////////////////////////////
  // Concatenation
  /////////////////////////////////////////////////////////////

  friend Sequence operator + (const Sequence&, const Sequence&);
  friend Sequence operator + (const T&,        const Sequence&);
  friend Sequence operator + (const Sequence&, const T&);
  friend Sequence operator + (const T[],       const Sequence&);
  friend Sequence operator + (const Sequence&, const T[]);
};

///////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
///////////////////////////////////////////////////////////////////////

template <class T>
Sequence<T>::Sequence()
{}

template <class T>
Sequence<T>::Sequence(const Sequence<T>&)
{}

template <class T>
Sequence<T>::Sequence(const T&)
{}

template <class T>
Sequence<T>::Sequence(const T[])
{}

template <class T>
Sequence<T>::~Sequence()
{}

template <class T>
Sequence<T> operator + (const Sequence<T>&, const Sequence<T>&)
{}

template <class T>
Sequence<T> operator + (const Sequence<T>&, const T&)
{}

template <class T>
Sequence<T> operator + (const T&, const Sequence<T>&)
{}

template <class T>
Sequence<T> operator + (const Sequence<T>&, const T[])
{}

template <class T>
Sequence<T> operator + (const T[], const Sequence<T>&)
{}

#endif
