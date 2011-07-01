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

#include <stdlib.h>
#include <string.h>
#include <iostream>
#define PSTREAM_IMPLEMENTATION
#include <AD/persist/pconfig.h>
#include <AD/persist/pstream.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Input manipulator function
//
//////////////////////////////////////////////////////////////////////////////

Pistream& operator >> (Pistream& s, void (*f)(Pistream&))
{
  (*f)(s);
  return s;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Output manipulator function
//
//////////////////////////////////////////////////////////////////////////////

Postream& operator << (Postream& s, void (*f)(Postream&))
{
  (*f)(s);
  return s;
}

//////////////////////////////////////////////////////////////////////////////
//
//  A string identifying the current version
//
//////////////////////////////////////////////////////////////////////////////

const char * const PROP_PERSISTENT_VERSION = P_VERSION_STRING;

//////////////////////////////////////////////////////////////////////////////
//
//  Function to write out the persistence library version string
//
//////////////////////////////////////////////////////////////////////////////

void version (Postream& f)
{
  f << PROP_PERSISTENT_VERSION;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Function to read in the version string and verify that it is
//  compactible with the current version
//
//////////////////////////////////////////////////////////////////////////////

void version( Pistream& f)
{
  char version[256];
  int len = f.read(version,sizeof(version)-1);
  version[len >= 0 ? len : 0] = '\0';

  // Simple minded check for now
  if (strcmp(version,PROP_PERSISTENT_VERSION))
  {
    std::cerr << "Persistent library version mismatch:\n"
    << "Version of persistent data: " << version << '\n'
    << "Version of library: " << PROP_PERSISTENT_VERSION << '\n'
    << "Aborting program...\n";
    exit(1);
  }
}
