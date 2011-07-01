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

#ifndef persistent_object_factory_h
#define persistent_object_factory_h

#include <AD/persist/pobject.h>
#include <AD/persist/ptype.h>

//////////////////////////////////////////////////////////////////////////////
//  The base class
//////////////////////////////////////////////////////////////////////////////

class PBaseFactory
{
  PBaseFactory(const PBaseFactory&);      // no copy constructor
  void operator = (const PBaseFactory&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  PBaseFactory(const PObjectType&);
  virtual ~PBaseFactory();

  ///////////////////////////////////////////////////////////////////////////
  //  Method to create a new object.
  //  Method to register itself into the global factory.
  ///////////////////////////////////////////////////////////////////////////
  static  PObject *create_object( const PObjectType&);
  void      register_factory( const PObjectType&);
  virtual PObject *create_object() = 0;
};

//////////////////////////////////////////////////////////////////////////////
//  Object factory for each type
//////////////////////////////////////////////////////////////////////////////

template <class T>
class PObjectFactory : public PBaseFactory
{
  PObjectFactory(const PObjectFactory&);    // no copy constructor
  void operator = (const PObjectFactory&);  // no assignment

public:
  PObjectFactory(const PObjectType& id) : PBaseFactory(id)
  {}
  virtual ~PObjectFactory()
  {}
  virtual  PObject * create_object ()
  {
    return new T;
  }
};

#endif
