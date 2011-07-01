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

#ifndef persistent_objects_type_h
#define persistent_objects_type_h

//////////////////////////////////////////////////////////////////////////////
//  This file describes the class PObjectType, which describes the type
//  of a persistent object.
//////////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>
#include <AD/persist/pconfig.h>
#include <iostream>


//////////////////////////////////////////////////////////////////////////////
//
//  Opaque definitions
//
//////////////////////////////////////////////////////////////////////////////

class Pistream;
class Postream;
class PBaseFactory;

//////////////////////////////////////////////////////////////////////////////
//
//  Persistent objects types.
//
//////////////////////////////////////////////////////////////////////////////

class PObjectType
{
  PObjectType (const PObjectType&);
  void operator = (const PObjectType&);

public:
  struct Entry
  {
    P_OBJECT_TYPEID unique_id;     // unique id for each type
    const char *    type_name;     // name of object type
    int             type_name_len; // length of type name
    PBaseFactory *  factory;       // object factory
  };

protected:
  // index into a table of unique id during execution
  friend class PBaseFactory;
  Entry * entry;

  static Entry * lookup_entry (const char *);
public:

  //////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////////////////////
  inline   PObjectType (Entry * e = 0) : entry(e)
  {}
  PObjectType (const char * name);
  virtual ~PObjectType ();

  friend std::ostream&  operator << ( std::ostream&, const PObjectType& );
  inline Bool operator == (const PObjectType& id) const
  {
    return entry == id.entry;
  }
  inline Bool operator != (const PObjectType& id) const
  {
    return entry != id.entry;
  }
  const char * name () const;
  static int number_of_types ();

  //////////////////////////////////////////////////////////////////////////
  //
  //  Interface to the persistent object classes
  //
  //////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////
  //
  //  Read and write methods.  We can't read and write PObjectType
  //  arbitrarily from and to the persistent streams.
  //
  //////////////////////////////////////////////////////////////////////////
  void write ( Postream& ) const;
  void read  ( Pistream& );
};

#endif
