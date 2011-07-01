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

#ifndef reference_counted_objects_h
#define reference_counted_objects_h

//////////////////////////////////////////////////////////////////////////////
//  Reference counted objects base class.
//////////////////////////////////////////////////////////////////////////////

class RefObj
{
  int _ref_count; // reference count
public:
  //////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////////////////////
  inline  RefObj() : _ref_count(1)
  {}
  virtual inline ~RefObj()
  {}

  //////////////////////////////////////////////////////////////////////////
  //  Check if the pointer is actually valid.
  //////////////////////////////////////////////////////////////////////////
  inline static int _boxed(void * obj)
  {
    return (unsigned long)obj >= 4096;
  }

  //////////////////////////////////////////////////////////////////////////
  //  Reference counting primitives.
  //////////////////////////////////////////////////////////////////////////
  inline static void _inc(RefObj * obj)
  {
    if (RefObj::_boxed(obj))
      ++obj->_ref_count;
  }
  inline static void _dec(RefObj * obj)
  {
    if (RefObj::_boxed(obj) && --obj->_ref_count == 0)
      delete obj;
  }
};

//////////////////////////////////////////////////////////////////////////////
// Ref<T> handles the reference counting of a pointer to class |T|.
// It is a smart pointer.
//////////////////////////////////////////////////////////////////////////////

template <class T>
class Ref
{
  const T&  operator * () const;  // for safety, no deferencing is allowed.

  T * obj;  // actual pointer to object (must be derived from RefObj)

public:
  ///////////////////////////////////////////////////////////////////////
  //  Constructors and destructor.
  ///////////////////////////////////////////////////////////////////////
  inline  Ref(T * x = 0) : obj(x)
  {}
  inline  Ref(Ref& r)    : obj(r.obj)
  {
    RefObj::_inc(obj);
  }
  inline ~Ref()
  {
    RefObj::_dec(obj);
  }

  ///////////////////////////////////////////////////////////////////////
  //  Conversions and pinning.
  //  Pinning increments the reference on an object and returns
  //  its raw pointer.   This raw pointer is assumed to be single
  //  threaded and placed into some other Ref<T> type.
  ///////////////////////////////////////////////////////////////////////
  inline operator int () const
  {
    return (int)obj;
  }
  inline T * _pin ()
  {
    RefObj::_inc(obj);
    return obj;
  }
  inline T * _raw ()
  {
    return obj;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Assignments.
  ///////////////////////////////////////////////////////////////////////
  inline Ref& operator = (Ref& r)
  {
    if (obj != r.obj)
    {
      RefObj::_inc(r.obj);
      RefObj::_dec(obj);
      obj = r.obj;
    }
    return *this;
  }

  inline Ref& operator = (T * x)
  {
    if (obj != x)
    {
      RefObj::_dec(obj);
      obj = x;
    }
    return *this;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Dereferencing operators.
  ///////////////////////////////////////////////////////////////////////
  inline const T * operator -> () const
  {
    return obj;
  }
  inline       T * operator -> ()
  {
    return obj;
  }
};

#endif
