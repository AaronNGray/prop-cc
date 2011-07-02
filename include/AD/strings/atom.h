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

#ifndef atomic_strings_with_garbage_collection_h
#define atomic_strings_with_garbage_collection_h

//
//  Like a |Quark|, class |Atom| represents atomic strings that
//  adhere to the following identity:
//      Atom(s1) == Atom(s2)   iff  strcmp(s1,s2)
//
//  This means that we can use pointer comparison on
//  quarks where character comparison is necessary on
//  strings.
//
//  Unlike, |Quark|'s however, the storage used for an @|Atom|
//  is reclaimed whenever it is not longer needed; reference counting
//  is used to accomplish this.
//

#include <string>
#include <AD/generic/generic.h>

class Atom
{
public:
  struct Matter
  {
    long refCount;   // reference count
    char name[1];    // name
  };
private:
  Matter * matter;
public:
  Atom() : matter(0)
  {}
  Atom(const char *);
  Atom(const Atom& atom) : matter(atom.matter)
  {
    if (matter)
      matter->refCount++;
  }
  ~Atom();

  Atom& operator = (const Atom&);

  operator const char * () const
  {
    return matter->name;
  }
  char operator [] (int i) const
  {
    return matter->name[i];
  }

  friend Bool operator == (const Atom& x, const Atom& y)
  {
    return x.matter == y.matter;
  }
  friend Bool operator == (const Atom& x, const char * y)
  {
    return strcmp(x.matter->name,y) == 0;
  }
  friend Bool operator == (const char * x, const Atom& y)
  {
    return strcmp(x,y.matter->name) == 0;
  }
  friend Bool operator != (const Atom& x, const Atom& y)
  {
    return x.matter != y.matter;
  }
  friend Bool operator != (const Atom& x, const char * y)
  {
    return strcmp(x.matter->name,y) != 0;
  }
  friend Bool operator != (const char * x, const Atom& y)
  {
    return strcmp(x,y.matter->name) != 0;
  }

  friend unsigned int hash (const Atom&);
  friend Bool equal (const Atom& a, const Atom& b)
  {
    return a == b;
  }
};


#endif
