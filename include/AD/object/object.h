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

#ifndef ADLib_object_hierarchy_h
#define ADLib_object_hierarchy_h

#include <iostream.h>
#include <AD/object/obintern.h>

/////////////////////////////////////////////////////////////////////////////
//  (Opaque) forward declarations
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
//
//
/////////////////////////////////////////////////////////////////////////////

class Object : public ObjIntern
{
  //////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////////////////////

public:
  Object() {}
  virtual ~Object();

  //////////////////////////////////////////////////////////////////////////
  //  Name of class; each class should have this redefined
  //////////////////////////////////////////////////////////////////////////
  virtual const char * className() const;

  //////////////////////////////////////////////////////////////////////////
  //  Object dependency:
  //
  //     changed(Object& obj) --- invoked if obj is changed and `this' is
  //                              dependent on obj.
  //     deleled(Object& obj) --- invoked if obj is about to die and `this'
  //                              is dependent on obj.
  //////////////////////////////////////////////////////////////////////////
  virtual void changed(Object&);         // default is an nop
  virtual void deleted(Object&);         // default is an nop
  virtual void dependsOn(Object&);
  virtual Bool isDependedOn(const Object&);
  virtual void removeDependencyOn(Object&);
  virtual void removeAllDependency();

  //////////////////////////////////////////////////////////////////////////
  //  Miscellaneous operations
  //////////////////////////////////////////////////////////////////////////
  virtual unsigned int hash()         const
  {
    return (unsigned int)this;
  }
  Bool eq(const Object& o)    const
  {
    return this == &o;
  }
  virtual Bool equal(const Object& o) const
  {
    return this == &o;
  }

  //////////////////////////////////////////////////////////////////////////
  //  Debugging and tracing
  //////////////////////////////////////////////////////////////////////////
  virtual std::ostream& dump(std::ostream&) const;         // print contents
  virtual Bool     ok() const
  {
    return true;
  }   // invariants satisfied??
};

#endif
