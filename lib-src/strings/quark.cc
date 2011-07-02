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

#include <string>
#include <ctype.h>
#include <iostream>
#include <strstream>
#include <AD/strings/quark.h>   //  Atomic strings
#include <AD/strings/charesc.h> //  Escape characters
#include <AD/hash/lhash.h>      //  Hash table
#include <AD/memory/strpool.h>  //  String pools


class QuarkMap
{
  QuarkMap(const QuarkMap&);         // no copy constructor
  void operator = (const QuarkMap&); // no assignment

public:
  // A table of all strings encountered
  LHashTable<char *,char> universe;
  // A string pool to store the strings
  StringPool pool;

  inline QuarkMap() : universe(397), pool(8196)
  {}
}
;

static QuarkMap * map = 0;

int Quark::entries()
{
  return map ? map->universe.size() : 0;
}

void Quark::intern( const char* string)
{
  if (map == 0)
    map = new QuarkMap;
  Ix key = map->universe.lookup( (char* const) string);

  //
  // If the string is already in the universe, use the old copy.
  // Otherwise, allocate a new string and put it into the map.
  //
  if (key)
  {
    name = map->universe.key(key);
  }
  else
  {
    char * newName = map->pool[string]; // allocate the string from the pool
    map->universe.insert(newName,' ');  // add the new key into the map
    name = newName;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Constructors
//////////////////////////////////////////////////////////////////////////////

Quark::Quark( const char string[])
{
  intern(string);
}

Quark::Quark( const unsigned char string[])
{
  intern((const char *)string);
}

Quark::Quark( short n)
{
  char buf[32];
  std::ostrstream S(buf,sizeof(buf));
  std::ostream& S2 = S;
  S2 << n << std::ends;
  intern(buf);
}

Quark::Quark( unsigned short n)
{
  char buf[32];
  std::ostrstream S(buf,sizeof(buf));
  std::ostream& S2 = S;
  S2 << n << std::ends;
  intern(buf);
}

Quark::Quark( int n)
{
  char buf[32];
  std::ostrstream S(buf,sizeof(buf));
  std::ostream& S2 = S;
  S2 << n << std::ends;
  intern(buf);
}

Quark::Quark( const char string[], int n)
{
  std::ostrstream S;
  std::ostream& S2 = S;
  S2 << string << n << std::ends;
  intern(S.str());
  S.rdbuf()->freeze(0);
}

Quark::Quark( unsigned int n)
{
  char buf[32];
  std::ostrstream S(buf,sizeof(buf));
  std::ostream& S2 = S;
  S2 << n << std::ends;
  intern(buf);
}

Quark::Quark( long n)
{
  char buf[32];
  std::ostrstream S(buf,sizeof(buf));
  std::ostream& S2 = S;
  S2 << n << std::ends;
  intern(buf);
}

Quark::Quark( unsigned long n)
{
  char buf[32];
  std::ostrstream S(buf,sizeof(buf));
  std::ostream& S2 = S;
  S2 << n << std::ends;
  intern(buf);
}

Quark::Quark( double n)
{
  char buf[64];
  std::ostrstream S(buf,sizeof(buf));
  std::ostream& S2 = S;
  S2 << n << std::ends;
  intern(buf);
}

Quark::Quark( char c)
{
  char buf[32];
  buf[0] = '\'';
  char * p = print_char(buf+1,c);
  *p++ = '\'';
  *p = '\0';
  intern(buf);
}

Quark::Quark( const char s1[], const char s2[])
{
  std::ostrstream S;
  std::ostream& S2 = S;
  S2 << s1 << s2 << std::ends;
  intern(S.str());
  S.rdbuf()->freeze(0);
}

Quark::Quark( const char s1[], const char s2[], const char s3[])
{
  std::ostrstream S;
  std::ostream& S2 = S;
  S2 << s1 << s2 << s3 << std::ends;
  intern(S.str());
  S.rdbuf()->freeze(0);
}
Quark::Quark( const char s1[], const char s2[], const char s3[], const char s4[])
{
  std::ostrstream S;
  std::ostream& S2 = S;
  S2 << s1 << s2 << s3 << s4 << std::ends;
  intern(S.str());
  S.rdbuf()->freeze(0);
}

std::ostream& operator << (std::ostream& f, const Quark& q)
{
  return f << q.name;
}

std::istream& operator >> (std::istream& f, Quark& q)
{
  char buf[4096];
  f >> buf;
  q = Quark(buf);
  return f;
}

unsigned int hash_nocase( const Quark& q)
{
  unsigned int h = 0;
  for (const char * p = q.name; *p; p++)
  {
    if (isupper(*p))
      h += h + (*p - 'A') + 'a';
    else
      h += h + *p;
  }
  return h;
}

int compare_nocase( const Quark& a, const Quark& b)
{
#if defined(linux)
  return strcasecmp(a.string(),b.string());
#else

  return stricmp(a.string(),b.string());
#endif
}
