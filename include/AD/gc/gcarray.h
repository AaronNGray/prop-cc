//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef garbage_collectable_arrays_h
#define garbage_collectable_arrays_h

#include <AD/gc/gcobject.h>

//////////////////////////////////////////////////////////////////////////////
//  Arrays of GCObject (or subclass)
//  allocated from the collectable heaps should be encapsulated in
//  this template.
//////////////////////////////////////////////////////////////////////////////

template <class T>
class GCArray : public GCObject
{
public:
  typedef GCObject Super;

protected:
  T    _array[1];  // actual array.

  ////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ////////////////////////////////////////////////////////////////////////

public:
  GCArray();
  GCArray(const GCArray<T>&);  // no copy constructor
  ~GCArray();

  ////////////////////////////////////////////////////////////////////////
  //  Assignment
  ////////////////////////////////////////////////////////////////////////
  GCArray<T>& operator = (const GCArray<T>&);

  ////////////////////////////////////////////////////////////////////////
  //  Selectors
  ////////////////////////////////////////////////////////////////////////
  inline int size() const
  {
    return (basic_size() - sizeof(GCHeader)) / sizeof(T);
  }
  inline const T * operator [] (int i) const
  {
    return _array[i];
  }
  inline       T * operator [] (int i)
  {
    return _array[i];
  }

  ////////////////////////////////////////////////////////////////////////
  //  Allocation and deallocation
  ////////////////////////////////////////////////////////////////////////
  void * operator new    (size_t n, int length, GC& = *GC::default_gc);

  ////////////////////////////////////////////////////////////////////////
  //  Tracing method
  ////////////////////////////////////////////////////////////////////////
  virtual void trace(GC *);
};

//////////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Default Constructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
GCArray<T>::GCArray() : _array(0)
{}

//////////////////////////////////////////////////////////////////////////////
//  Copy Constructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
GCArray<T>::GCArray(const GCArray<T>& A) : _array(0)
{
  *this = A;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

template <class T>
GCArray<T>::~GCArray()
{  // finalize the rest of the array properly.
  for (int i = 1; i < size(); i++)
    _array[i].~T();
}

//////////////////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////////////////

template <class T>
GCArray<T>& GCArray<T>::operator = (const GCArray<T>& A)
{
  if (this != &A)
  {
    for (register int i = (size() < A.size() ? size() : A.size()) - 1;
         i >= 0; i--)
      _array[i] = A._array[i];
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Allocation
//////////////////////////////////////////////////////////////////////////////

template <class T>
void * GCArray<T>::operator new(size_t n, int length, GC& gc)
{  // Allocate a new array from the collectable heap
  size_t len                = n + (length - 1) * sizeof(T);
  register GCArray<T> * obj = (GCArray<T> *)gc.m_alloc(len);
  // Initialize the rest of array properly:
  //    (a) Create an instance of object T.
  //        This object will have the proper virtual tables.
  //    (b) Copy the initializer to the rest of the array.
  T initializer;
  for (register int i = 1; i < length; i++)
  {
    for (register long * p = (long*)(obj->_array + i),
         * q = p + sizeof(T) / sizeof(long),
         * r = (long*)&initializer; p < q; )
    {
      *p++ = *r++;
    }
  }
  return obj;
}

//////////////////////////////////////////////////////////////////////////////
//  Tracing method.
//////////////////////////////////////////////////////////////////////////////

template <class T>
void GCArray<T>::trace (GC * gc)
{
  for (int i = 0; i < size(); i++)
    _array[i].trace(gc);
}

#endif
