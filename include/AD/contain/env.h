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

#ifndef environment_h
#define environment_h

/////////////////////////////////////////////////////////////////////////////
// Class Env<Key,NameSpace,Value> represents a mapping from <Key,NameSpace>
// to Value.  All operations are functional.
/////////////////////////////////////////////////////////////////////////////

#include <AD/contain/map.h>

template <class Key, class NameSpace, class Value>
class Env
{
protected:

  struct Pair
  {
    const Key       key;
    const NameSpace nameSpace;
    Pair(const Key& k, const NameSpace& n) : key(k), nameSpace(n)
    {}
  };

  friend unsigned int hash (const Pair& p)
  {
    return hash(p.key) + hash(p.nameSpace);
  }
  friend Bool equal (const Pair& a, const Pair& b)
  {
    return equal(a.nameSpace,b.nameSpace) && equal(a.key, b.key);
  }

  struct Binding
  {
    enum { LIST, MAP, OVERRIDE } tag;
    union {
      struct
      {
        const Key       key;
        const NameSpace nameSpace;
        Value           value;
        Binding *       next;
      }
      list;
      struct
      {
        Binding * fst;
        Binding * snd;
      }
      override;
      Map<Pair,Value> * map;
    }
    Binding(const Key& k, const NameSpace& n,
            Value& v, Binding * link = 0)
        : tag(LIST), key(k), nameSpace(n), value(v), next(link)
    {}
    Binding(Map<Pair,Value> * m) : tag(MAP), map(m)
    {}
    Binding(Binding * a, Binding * b)
        : tag(OVERRIDE), override.fst(a), override.snd(b)
    {}
  };

public:

  Env();
  Env(const Env&);
  ~Env();

  Env& operator = (const Env&);

  ////////////////////////////////////////////////////////////////
  // empty       - the empty environment
  // lookup      - lookups a value within a name space
  // insert      - returns a new environment with the new binding
  // consolidate - compress environment for faster access
  // e1 + e2     - compute the union of two environments.
  ////////////////////////////////////////////////////////////////

  const Env empty;
  Value * operator () (const Key&, const NameSpace&) const;
  Value * lookup      (const Key&, const NameSpace&) const;
  Env     insert      (const Key&, const NameSpace&, Value&) const;
  Env     consolidate () const;
  friend Env operator + (const Env&, const Env&);

  ////////////////////////////////////////////////////////////////
  // Iterators
  ////////////////////////////////////////////////////////////////

  Ix first()  const;
  Ix last()   const;
  Ix next(Ix) const;
  Ix prev(Ix) const;
  T& operator () (Ix) const;
};

#endif
