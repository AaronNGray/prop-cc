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

#include <AD/gc/rootset.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor for class GCRootSet
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Default constructor
//////////////////////////////////////////////////////////////////////////////

GCRootSet:: GCRootSet()
    : root_objects(0),  root_object_count(0),  root_object_capacity(0),
    root_pointers(0), root_pointer_count(0), root_pointer_capacity(0)
{}

//////////////////////////////////////////////////////////////////////////////
//  Copy constructor
//////////////////////////////////////////////////////////////////////////////

GCRootSet:: GCRootSet(const GCRootSet& root_set)
    : root_objects(0), root_pointers(0)
{
  *this = root_set;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

GCRootSet::~GCRootSet()
{
  delete [] root_objects;
  delete [] root_pointers;
}

//////////////////////////////////////////////////////////////////////////////
//  Assignment.
//////////////////////////////////////////////////////////////////////////////

GCRootSet& GCRootSet::operator = (const GCRootSet& root_set)
{
  if (this != &root_set)
  {
    int i;

    delete [] root_objects;
    delete [] root_pointers;

    root_objects  = new GCObject *  [ root_set.number_of_objects() ];
    root_pointers = new GCObject ** [ root_set.number_of_pointers() ];
    root_object_count  = root_object_capacity  = root_set.number_of_objects();
    root_pointer_count = root_pointer_capacity = root_set.number_of_pointers();

    for (i = 0; i < root_object_count; i++)
      root_objects[i] = root_set.root_objects[i];
    for (i = 0; i < root_pointer_count; i++)
      root_pointers[i] = root_set.root_pointers[i];
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Clear a root set
//////////////////////////////////////////////////////////////////////////////

GCRootSet& GCRootSet::clear_roots()
{
  root_object_count = 0;
  root_pointer_count = 0;
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to add a new object to a root set
//////////////////////////////////////////////////////////////////////////////

GCRootSet& GCRootSet::add_root( GCObject& obj)
{
  // Make sure object is not already in the set
  for (int i = 0; i < root_object_count; i++)
  {
    if (root_objects[i] == &obj)
      return *this;
  }
  // Grow set if necessary
  if (root_object_count == root_object_capacity)
  {
    root_object_capacity = root_object_capacity * 3 / 2 + 4;
    GCObject ** new_root_objects = new GCObject * [ root_object_capacity ];
    for (int i = 0; i < root_object_count; i++)
      new_root_objects[i] = root_objects[i];
    delete [] root_objects;
    root_objects = new_root_objects;
  }
  root_objects[root_object_count++] = &obj;

  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to add a new pointer to a root set
//////////////////////////////////////////////////////////////////////////////

GCRootSet& GCRootSet::add_root( GCObject*& ptr)
{
  // Make sure pointer is not already in the set
  for (int i = 0; i < root_pointer_count; i++)
  {
    if (root_pointers[i] == &ptr)
      return *this;
  }
  // Grow set if necessary
  if (root_pointer_count == root_pointer_capacity)
  {
    root_pointer_capacity = root_pointer_capacity * 3 / 2 + 4;
    GCObject *** new_root_pointers = new GCObject ** [ root_pointer_capacity ];
    for (int i = 0; i < root_pointer_count; i++)
      new_root_pointers[i] = root_pointers[i];
    delete [] root_pointers;
    root_pointers = new_root_pointers;
  }
  root_pointers[root_pointer_count++] = &ptr;

  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to remove an object from a root set
//////////////////////////////////////////////////////////////////////////////

GCRootSet& GCRootSet::remove_root( GCObject& obj)
{
  for (int i = 0; i < root_object_count; i++)
  {
    if (root_objects[i] == &obj)
    {
      root_objects[i] = root_objects[--root_object_count];
      break;
    }
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to remove an object from a root set
//////////////////////////////////////////////////////////////////////////////

GCRootSet& GCRootSet::remove_root( GCObject*& ptr)
{
  for (int i = 0; i < root_pointer_count; i++)
  {
    if (root_pointers[i] == &ptr)
    {
      root_pointers[i] = root_pointers[--root_pointer_count];
      break;
    }
  }
  return *this;
}
