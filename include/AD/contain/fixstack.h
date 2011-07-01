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

#ifndef fixed_sized_stack_h
#define fixed_sized_stack_h

////////////////////////////////////////////////////////////////////////
//  Class FixStack<T> parameterized by
//  the element type and the maximum capacity.
//  This class should be used in place of class Stack<T>
//  if the maximum size is known in advanced, since
//  this class has been optimized.
////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>  // Generic definitions

template<class T,int Capacity>
class FixStack
{

  T elements[Capacity];
  T * stackTop;

  FixStack(const FixStack&);
  FixStack& operator = (const FixStack&);

  ///////////////////////////////////////////////////////////////////
  // Constructor and destructor
  ///////////////////////////////////////////////////////////////////

public:
  FixStack() : stackTop(elements)
  {}

  ///////////////////////////////////////////////////////////////////
  //  Conversion
  ///////////////////////////////////////////////////////////////////

  inline operator const T* () const
  {
    return elements;
  }

  inline operator T* ()
  {
    return elements;
  }

  ///////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////

  inline int size() const
  {
    return stackTop - elements;
  }

  inline int capacity() const
  {
    return Capacity;
  }

  inline Bool is_empty() const
  {
    return stackTop == elements;
  }

  inline Bool is_full() const
  {
    return this->size() == Capacity;
  }

  inline const T& top() const
  {
    return *stackTop;
  }

  inline T& top()
  {
    return *stackTop;
  }

  inline T& operator [] (int i)
  {
    return elements[i];
  }

  inline const T& operator [] (int i) const
  {
    return elements[i];
  }

  ///////////////////////////////////////////////////////////////////
  //  Mutators
  ///////////////////////////////////////////////////////////////////

  inline void clear()
  {
    stackTop = elements;
  }

  inline void push( const T& e)
  {
    *stackTop++ = e;
  }

  inline T& pop()
  {
    return *--stackTop;
  }

  inline void pop( int m)
  {
    stackTop -= m;
  }

  ///////////////////////////////////////////////////////////////////
  //  Iterators
  ///////////////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return Ix(stackTop > elements ? stackTop : 0);
  }

  inline Ix last() const
  {
    return Ix(stackTop > elements ? elements : 0);
  }

  inline Ix next(Ix i) const
  {
    return Ix(i > (Ix)elements ? (T*)i-1 : 0);
  }

  inline Ix prev(Ix i) const
  {
    return Ix(i < (Ix)stackTop ? (T*)i+1 : 0);
  }

  inline const T& operator () (Ix i) const
  {
    return *(T*)i;
  }

  inline T& operator () (Ix i)
  {
    return *(T*)i;
  }
};

#endif
