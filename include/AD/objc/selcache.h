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

#ifndef method_selector_cache_h
#define method_selector_cache_h

#include <AD/objc/objc.h>
#include <AD/hash/lhash.h>

//////////////////////////////////////////////////////////////////////////////
//  Class O_SelectorCache performs caching of methods based on the
//  selectors.  We'll use an non-virtual implementation of hash table
//  for efficiency.
//////////////////////////////////////////////////////////////////////////////

class O_SelectorCache
{
  O_SelectorCache(const O_SelectorCache&);   // no copy constructor
  void operator = (const O_SelectorCache&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////
public:
  typedef O_Object::ObjectMethod ObjectMethod;
  typedef O_Object::O_SEL        O_SEL;

  ///////////////////////////////////////////////////////////////////////////
  //  The actual table is a hash table with linear hashing.
  //  Due to a bug in the gcc compiler, I'm unable to parametrize the
  //  template directly with ObjectMethod.  Thus the funny wrapper business.
  ///////////////////////////////////////////////////////////////////////////

private:
  struct Wrapper
  {
    ObjectMethod m;
    inline Wrapper ()
    {}
    inline Wrapper (ObjectMethod meth) : m(meth)
    {}
  }
  ;
  LHashTable<O_Object::O_SEL,Wrapper> table;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  O_SelectorCache(int initial_size) : table(initial_size)
  {}
  ~O_SelectorCache()
  {}

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for manipulating the cache
  ///////////////////////////////////////////////////////////////////////////
  inline void flush_cache     ()
  {
    table.clear();
  }
  inline void update_cache    (O_SEL s, ObjectMethod m)
  {
    table.insert(s,m);
  }
  inline void invalidate_cache(O_SEL s)
  {
    table.remove(s);
  }
  inline Ix   lookup_cache(O_SEL s)   const
  {
    return table.lookup(s);
  }
  inline ObjectMethod method_of(Ix i) const
  {
    return table.value(i).m;
  }
  inline int cache_size()             const
  {
    return table.size();
  }
};

#endif
