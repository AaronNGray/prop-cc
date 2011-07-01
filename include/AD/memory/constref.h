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

#ifndef constant_reference_counted_objects_h
#define constant_reference_counted_objects_h

#include <AD/memory/ref.h>

//////////////////////////////////////////////////////////////////////////////
// ConstRef<T> handles the reference counting of a pointer to class |T|.
// The is const and cannot be changed. It is a smart pointer.
//////////////////////////////////////////////////////////////////////////////

template <class T>
class ConstRef
{
  const T& operator * () const; // for safety, no deferencing is allowed.
  T * obj;  // actual pointer to object (must be derived from RefObj)

public:
  ///////////////////////////////////////////////////////////////////////
  //  Constructors and destructor.
  ///////////////////////////////////////////////////////////////////////
  inline  ConstRef(T * x = 0)         : obj(x)
  {}
  inline  ConstRef(const ConstRef& r)
      : obj(((ConstRef *)(&r))->obj)
  {
    RefObj::_inc(obj);
  }
  inline ~ConstRef()
  {
    RefObj::_dec(obj);
  }

  ///////////////////////////////////////////////////////////////////////
  //  Conversions and pinning.
  //  Pinning increments the reference on an object and returns
  //  its raw pointer.   This raw pointer is assumed to be single
  //  threaded and placed into some other Ref<T> type.
  ///////////////////////////////////////////////////////////////////////
  inline operator int ()   const
  {
    return (int)obj;
  }
  inline T * _pin ()
  {
    RefObj::_inc(obj);
    return obj;
  }
  inline const T * _raw () const
  {
    return obj;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Assignments.
  ///////////////////////////////////////////////////////////////////////
  inline ConstRef& operator = (const ConstRef& r)
  {
    if (obj != ((ConstRef*)(&r))->obj)
    {
      RefObj::_inc(((ConstRef*)(&r))->obj);
      RefObj::_dec(obj);
      obj = ((ConstRef*)(&r))->obj;
    }
    return *this;
  }

  inline ConstRef& operator = (T * x)
  {
    if (obj != x)
    {
      RefObj::_dec(obj);
      obj = x;
    }
    return *this;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Dereferencing operator.
  ///////////////////////////////////////////////////////////////////////
  inline const T * operator -> () const
  {
    return obj;
  }
  inline const T * operator -> ()
  {
    return obj;
  }
};

#endif
