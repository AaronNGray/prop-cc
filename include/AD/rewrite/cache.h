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
#ifndef rewrite_cache_h
#define rewrite_cache_h

#include <AD/generic/generic.h>
#include <AD/rewrite/burs.h>

//////////////////////////////////////////////////////////////////////////////
//
//  This class implements a simple external index for rewriting.
//  The (non-associative) cache has fixed capacity.
//
//////////////////////////////////////////////////////////////////////////////

class RewriteCache
{
  RewriteCache(const RewriteCache&);
  void operator = (const RewriteCache&);

  typedef const void * Term;

  struct Table
  {
    const void * t;
    BURS::State s;
  } *the_cache;

  int the_capacity;

public:
  RewriteCache();
  RewriteCache(int capacity);
  ~RewriteCache();

  void clear();                   // after rewriting
  void initialize();              // before rewriting
  void initialize(int capacity);  // before rewriting/also set capacity

  int capacity() const
  {
    return the_capacity;
  }

  void set_state(Term t, int s)
  {
    int i = (unsigned long)t % the_capacity;
    the_cache[i].t = t;
    the_cache[i].s = s;
  }

  int get_state(Term t) const
  {
    int i = (unsigned long)t % the_capacity;
    return (the_cache[i].t == t) ? (int)the_cache[i].s
           : (int)BURS::undefined_state;
  }

  void invalidate(Term t)
  {
    int i = (unsigned long)t % the_capacity;
    if (the_cache[i].t == t)
      the_cache[i].t = 0;
  }
};

#endif
