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

#ifndef stack_h
#define stack_h

///////////////////////////////////////////////////////////////////////////
//  Class Stack<T> is a variable sized stack
//  parameterized by its element type.
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//  We'll derive a Stack from an Array
///////////////////////////////////////////////////////////////////////////

#include <AD/contain/array.h>   // Dynamic array

template<class T>
class Stack : public Array<T>
{
  int n;                          // size of the stack

  Stack(const Stack&);            // no copy constructor
  void operator = (const Stack&); // no assignment

  //////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////

public:
  Stack(int size) : Array<T>(size), n(0)
  {}
  ~Stack()
  {}

  //////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////

  inline int size() const
  {
    return n;
  }

  inline Bool is_empty() const
  {
    return n == 0;
  }

  inline Bool is_full() const
  {
    return n >= this->length();
  }

  inline const T& top() const
  {
    return (*this)[n-1];
  }

  inline T& top()
  {
    return (*this)[n-1];
  }
  // T& operator [] (int i) const; // inherited

  //////////////////////////////////////////////////////////
  //  Mutators
  //////////////////////////////////////////////////////////

  inline void clear()
  {
    n = 0;
  }

  inline void push(const T& e)
  {
    (*this)[n++] = e;
  }

  inline void set_size(int s)
  {
    n = s;
  }

  inline T& pop()
  {
    return (*this)[--n];
  }

  inline void pop(int m)
  {
    n -= m;
  }

  //////////////////////////////////////////////////////////
  //  Iterators
  //////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return Ix(n);
  }

  inline Ix last() const
  {
    return Ix(n > 0 ? 1 : 0);
  }

  inline Ix next(Ix i) const
  {
    return Ix((int)i-1);
  }

  inline Ix prev(Ix i) const
  {
    return Ix((int)i < n ? (int)i+1 : 0);
  }

  inline const T& operator () (Ix i) const
  {
    return (*this)[(int)i-1];
  }

  inline T& operator () (Ix i)
  {
    return (*this)[(int)i-1];
  }
};

#endif
