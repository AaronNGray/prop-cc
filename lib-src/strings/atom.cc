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
#include <AD/strings/atom.h>
#include <AD/hash/dchash.h>

static DCHashTable<const char *, Atom::Matter *> universe(256);

Atom::Atom( const char * string)
{
  Ix m = universe.lookup(string);
  if (m)
  {
    matter = universe.value(m);
    matter->refCount++;
  }
  else
  {
    matter = (Matter *)malloc(sizeof(Matter) + strlen(string));
    strcpy(matter->name,string);
    matter->refCount = 1;
    const char * name = matter->name;
    universe.insert(name,matter);
  }
}

Atom::~Atom()
{
  if (matter && --(matter->refCount) <= 0)
  {
    const char * name = matter->name;
    universe.remove(name);
    free(matter);
  }
}

Atom& Atom::operator = (const Atom& atom)
{
  if (this != &atom)
  {
    if (matter && --(matter->refCount) <= 0)
    {
      const char * name = matter->name;
      universe.remove(name);
      free(matter);
    }
    if ((matter = atom.matter))
      matter->refCount++;
  }
  return *this;
}

unsigned int hash( const Atom& atom)
{
  register unsigned int h;
  register char * p;
  for (h = 0, p = atom.matter->name; *p; p++)
    h += h + *p;
  return h;
}
