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

#include <stdlib.h>
#include <iostream.h>
#include <AD/contain/basiccol.h>

//////////////////////////////////////////////////////////////////////////
//  Default implementation of size() iterates through the collection
//  and count the number of elements.
//  Subclasses of Collection should override this inefficient(but correct)
//  implementation if possible.
//////////////////////////////////////////////////////////////////////////

int BasicCollection::size() const
{
  int count;
  Ix  i;
  for (count = 0, i = first(); i; i = next(i))
    count++;
  return count;
}

//////////////////////////////////////////////////////////////////////////
//  The following methods are used by subclasses to report errors
//////////////////////////////////////////////////////////////////////////

void BasicCollection::should_not_implement(const char method_name[]) const
{
  std::cerr << "\n[Class " << myName()
  << " does not understand method " << method_name << "]\n";
  exit(1);
}
