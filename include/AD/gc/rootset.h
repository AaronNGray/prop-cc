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
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef garbage_collector_root_set_h
#define garbage_collector_root_set_h

#include <AD/gc/gcintern.h>

//////////////////////////////////////////////////////////////////////////////
//  Garbage collector root set.
//////////////////////////////////////////////////////////////////////////////

class GCRootSet
{
  ///////////////////////////////////////////////////////////////////////////
  //  Root set objects
  ///////////////////////////////////////////////////////////////////////////

protected:
  GCObject **   root_objects;
  int           root_object_count;
  int           root_object_capacity;

  ///////////////////////////////////////////////////////////////////////////
  //  Root set pointers
  ///////////////////////////////////////////////////////////////////////////
  GCObject ***  root_pointers;
  int           root_pointer_count;
  int           root_pointer_capacity;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor.
  ///////////////////////////////////////////////////////////////////////////

public:
  GCRootSet();
  GCRootSet(const GCRootSet&);
  virtual ~GCRootSet();

  ///////////////////////////////////////////////////////////////////////////
  //  Assignment.
  ///////////////////////////////////////////////////////////////////////////
  GCRootSet& operator = (const GCRootSet&);

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to access the root set.
  ///////////////////////////////////////////////////////////////////////////
  inline int        number_of_objects () const
  {
    return root_object_count;
  }
  inline int        number_of_pointers() const
  {
    return root_pointer_count;
  }
  inline GCObject & operator [] (int i)  const
  {
    return *root_objects[i];
  }
  inline GCObject * operator () (int i)  const
  {
    return *root_pointers[i];
  }
  inline GCObject & root_obj (int i)     const
  {
    return *root_objects[i];
  }
  inline GCObject * root_ptr (int i)     const
  {
    return *root_pointers[i];
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to add or remove objects/pointer from the root set
  ///////////////////////////////////////////////////////////////////////////
  virtual GCRootSet& clear_roots ();
  virtual GCRootSet& add_root    (GCObject&);
  virtual GCRootSet& add_root    (GCObject*&);
  virtual GCRootSet& remove_root (GCObject&);
  virtual GCRootSet& remove_root (GCObject*&);
};

#endif
