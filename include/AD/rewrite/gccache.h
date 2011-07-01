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
// 1994-1997
//////////////////////////////////////////////////////////////////////////////

#ifndef rewrite_cache_for_gc_object_h
#define rewrite_cache_for_gc_object_h

#include <string.h>
#include <AD/generic/generic.h>
#include <AD/rewrite/burs.h>
#include <AD/gc/weakptr.h>

//////////////////////////////////////////////////////////////////////////////
//
//  This class implements a simple external index for rewriting GCObject.
//  The (non-associative) cache has fixed capacity.
//
//////////////////////////////////////////////////////////////////////////////

template <class T>
class GCRewriteCache
{
  GCRewriteCache(const GCRewriteCache&);
  void operator = (const GCRewriteCache&);

  struct Table
  {
    WeakPointer<T> t;
    unsigned short s;
  } *the_cache;
  int the_capacity;

public:
  GCRewriteCache();
  GCRewriteCache(int capacity);
  ~GCRewriteCache();

  void clear();                   // after rewriting
  void initialize();              // before rewriting
  void initialize(int capacity);  // before rewriting/also set capacity

  int capacity() const
  {
    return the_capacity;
  }
  void set_state(T * t, int s);
  int get_state(T * t) const;
  void invalidate(T * t);
};

template <class T>
GCRewriteCache<T>::GCRewriteCache() : the_cache(0), the_capacity(0)
{}

template <class T>
GCRewriteCache<T>::GCRewriteCache(int c) : the_cache(0), the_capacity(c)
{}

template <class T>
GCRewriteCache<T>::~GCRewriteCache()
{
  clear();
}

template <class T>
void GCRewriteCache<T>::clear()
{
  delete [] the_cache;
}

template <class T>
void GCRewriteCache<T>::initialize()
{
  if (the_cache == 0)
  {
    if (the_capacity <= 0)
      the_capacity = 1023;
    the_cache = new Table [the_capacity];
  }
  for (int i = 0; i < the_capacity; i++)
    the_cache[i].t = 0;
}

template <class T>
void GCRewriteCache<T>::initialize(int c)
{
  if (the_cache && the_capacity != c)
    clear();
  the_capacity = c;
  initialize();
}

template <class T>
void GCRewriteCache<T>::set_state(T * t, int s)
{
  int i = (unsigned long)t % the_capacity;
  the_cache[i].t = t;
  the_cache[i].s = s;
}

template <class T>
int GCRewriteCache<T>::get_state(T * t) const
{
  int i = (unsigned long)t % the_capacity;
  return ((T*)the_cache[i].t == t) ? the_cache[i].s : BURS::undefined_state;
}

template <class T>
void GCRewriteCache<T>::invalidate(T * t)
{
  int i = (unsigned long)t % the_capacity;
  if ((T*)the_cache[i].t == t)
    the_cache[i].t = 0;
}
#endif
