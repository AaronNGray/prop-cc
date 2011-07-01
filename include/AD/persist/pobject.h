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

#ifndef persistent_objects_h
#define persistent_objects_h

//////////////////////////////////////////////////////////////////////////////
//  This file describes the base class PObject, or persistent object.
//  Persistent objects can be serialized so that it can be written into
//  external storage, with the help of the class Pstream and its subclasses.
//////////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>
#include <AD/persist/pconfig.h>

//////////////////////////////////////////////////////////////////////////////
//  Opaque Forward declarations
//////////////////////////////////////////////////////////////////////////////

class Pistream;    // persistent input stream
class Postream;    // persistent output stream
class PObjectType; // persistent object type

//////////////////////////////////////////////////////////////////////////////
//  Persistent objects in ADLib must be declared as a subclass of
//  class PObject, and implement the following virtual methods
//////////////////////////////////////////////////////////////////////////////

class PObject
{
public:

  //////////////////////////////////////////////////////////////////////////
  //  Default destructor
  //////////////////////////////////////////////////////////////////////////
  virtual ~PObject()
  {}

  //////////////////////////////////////////////////////////////////////////
  //  Each concrete persistent object class must redefine the following
  //  methods.
  //      type_id       (...) --- returns the unique type id of the class.
  //      persist_read  (...) --- reading from a persistent stream.
  //      persist_write (...) --- writing to a persistent stream.
  //////////////////////////////////////////////////////////////////////////
  const char *       persist_type_name() const;
  virtual const PObjectType& persist_type_id()   const        = 0;
  virtual Pistream&          persist_read ( Pistream& )       = 0;
  virtual Postream&          persist_write( Postream& ) const = 0;

  //////////////////////////////////////////////////////////////////////////
  //  Macros to declare the above methods.
  //  This macro should be used within the class definition, in
  //  the public section.
  //////////////////////////////////////////////////////////////////////////
#define DEFINE_PERSISTENT_CLASS(NAME)                         \
   virtual const PObjectType& persist_type_id() const;        \
   virtual Pistream&          persist_read ( Pistream& );     \
   virtual Postream&          persist_write( Postream& ) const
};

#endif
