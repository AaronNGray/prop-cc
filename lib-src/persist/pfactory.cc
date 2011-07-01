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
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <AD/persist/ptype.h>
#include <AD/persist/ptypeentry.h>
#include <AD/persist/pfactory.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

PBaseFactory::PBaseFactory(const PObjectType& id)
{
  register_factory(id);
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

PBaseFactory::~PBaseFactory()
{}

//////////////////////////////////////////////////////////////////////////////
//   Register a new object factory
//////////////////////////////////////////////////////////////////////////////

void PBaseFactory::register_factory(const PObjectType& id)
{
  id.entry->factory = this;
}

//////////////////////////////////////////////////////////////////////////////
//  Given a type id, lookup the associate factory and create the new object.
//  If the id is not found, return nil.
//////////////////////////////////////////////////////////////////////////////

PObject* PBaseFactory::create_object( const PObjectType& id)
{
  PBaseFactory * f = id.entry->factory;
  if (f)
    return f->create_object();
  else
  {
    std::cerr << "Object factory for typeid " << id << " is undefined\n";
    exit(1);
  }
  return 0;
}
