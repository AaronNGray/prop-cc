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

#ifndef reference_counting_pointer_h
#define reference_counting_pointer_h

//
//  Class Ref<Type> takes a pointer to an object and
//  performs transparent reference counting on it.
//  Assignment and initialization will change its reference.
//  When the reference count of the object reaches 0, it
//  will be automatically deleted.
//
//  Warning: circular objects built from this type will be not
//  be reference counted correctly and space leak will result.
//

template<class Type>
class Ref
{
  Type * object;    // The object itself
  int * refCount;   // number of Ref's in existence

public:
  Ref(const Ref & r) : object(r.object), refCount(r.refCount)
  {
    ++*refCount;
  }
  Ref(Type* obj) : object(obj), refCount(new int)
  {}
  ~Ref()
  {
    if (--(*refCount) == 0)
    {
      delete object;
      delete refCount;
    }
  }

  Type* operator -> ()
  {
    return object;
  }
  Type* operator * ()
  {
    return object;
  }

  Ref& operator = (const Ref& r);
};

template<class Type>
Ref<Type>& Ref<Type>::operator = (const Ref<Type>& r)
{
  if (this != &r)
  {
    if (--*refCount == 0)
    {
      delete object;
      delete refCount;
    }
    object = r.object;
    refCount = r.refCount;
    ++*refCount;
  }
  return *this;
}

#endif
