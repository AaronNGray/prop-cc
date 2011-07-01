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
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#define PSTREAM_IMPLEMENTATION
#include <string.h>
#include <iostream>
#include <strstream>
#include <AD/persist/pconfig.h>
#include <AD/persist/ptype.h>
#include <AD/persist/ptypeentry.h>
#include <AD/persist/pstream.h>
#include <AD/hash/lhash.h>
#include <AD/contain/vararray.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Persistent id table
//
//////////////////////////////////////////////////////////////////////////////

static P_OBJECT_TYPEID next_unique_id = 1;
typedef LHashTable<const char *, PObjectType::Entry *> PersistTypeMap;
static PersistTypeMap * persist_type_map;
VarArray <PObjectType::Entry *> * persist_type_table;

//////////////////////////////////////////////////////////////////////////////
//
//  Persistent object id constructor
//
//////////////////////////////////////////////////////////////////////////////

PObjectType::PObjectType( const char * name)
{
  if (persist_type_map == 0)
  {
    persist_type_map   = new PersistTypeMap(257);
    persist_type_table = new VarArray<PObjectType::Entry *>(0,257);
  }
  Ix e = persist_type_map->lookup(name);
  if (e)
  {  // found type entry
    entry = persist_type_map->value(e);
  }
  else
  {  // create new type entry
    entry = new PObjectType::Entry;
    entry->unique_id     = next_unique_id;
    entry->type_name     = name;
    entry->type_name_len = strlen(name);
    entry->factory       = 0;
    persist_type_map->insert(name,entry);
    (*persist_type_table)[next_unique_id] = entry;
    next_unique_id++;
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Persistent object type destructor
//
//////////////////////////////////////////////////////////////////////////////

PObjectType::~PObjectType()
{}

//////////////////////////////////////////////////////////////////////////////
//
//  Retrieve the name of a persistent type
//
//////////////////////////////////////////////////////////////////////////////

const char * PObjectType::name() const
{
  return entry ? entry->type_name : "<none>";
}

//////////////////////////////////////////////////////////////////////////////
//
//  Lookup an entry
//
//////////////////////////////////////////////////////////////////////////////

PObjectType::Entry* PObjectType::lookup_entry( const char* name)
{
  Ix e = persist_type_map->lookup(name);
  return e ? persist_type_map->value(e) : 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Return the number of entries in table
//
//////////////////////////////////////////////////////////////////////////////

int PObjectType::number_of_types ()
{
  return next_unique_id - 1;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Write an persistent type to an iostream
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, const PObjectType& id)
{
  if (id.entry)
  {
    f << "[name=" << id.entry->type_name
    << ", id=" << id.entry->unique_id;
    if (id.entry->factory)
      f << " (with factory)";
    f << " ]";
    return f;
  }
  else
  {
    return f << "[empty persistent object type]";
  }
}
