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

#ifndef reference_counting_variant_h
#define reference_counting_variant_h

#include <AD/generic/generic.h>
#include <AD/memory/ref.h>

//
// Variant<Obj> handled the reference counting of class |Obj|
//

template <class Obj, long number_of_tags>
class Variant
{
protected:
  Obj * obj;

public:
  Bool boxed(Obj * obj) const
  {
    return ((long)obj) >= number_of_tags;
  }

  Variant(Obj * ob) : obj(ob)
  {}
  Variant(Ptr& r) : obj(r.obj)
  {
    if (boxed(obj))
      obj->reference_count++;
  }
  ~Variant()
  {
    if (boxed(obj) && --obj->reference_count == 0)
      delete obj;
  }

  void operator = (Variant& r)
  {
    if (boxed(r.obj))
      r.obj->reference_count++;
    if (boxed(obj) && --obj->reference_count == 0)
      delete obj;
    obj = r.obj;
  }
  Obj * operator -> ()
  {
    return obj;
  }
};

#endif
