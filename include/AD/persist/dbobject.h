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

#ifndef database_objects_h
#define database_objects_h

#include <AD/persist/pobject.h>

class OODB;

//////////////////////////////////////////////////////////////////////////////
//  Persistent objects in ADLib must be declared as a subclass of
//  class PObject, and implement the following virtual methods
//////////////////////////////////////////////////////////////////////////////

class DBObject : public PObject
{
public:
  virtual const PObjectType& persist_type() const;
  virtual void persist_read( Pistream&);
  virtual void persist_write( Postream&);
};

#endif
