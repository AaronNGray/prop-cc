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
#include <string>
#include <AD/rewrite/cache.h>

RewriteCache::RewriteCache() : the_cache(0), the_capacity(0) {}
RewriteCache::RewriteCache(int c) : the_cache(0), the_capacity(c) {}

RewriteCache::~RewriteCache()
{
  clear();
}

void RewriteCache::clear()
{
  if (the_cache)
  {  // for the benefit of the GC
    memset(the_cache,0,sizeof(Table) * the_capacity);
    delete [] the_cache;
  }
}

void RewriteCache::initialize()
{
  if (the_cache == 0)
  {
    if (the_capacity <= 0)
      the_capacity = 1023;
    the_cache = new Table [the_capacity];
  }
  memset(the_cache,0,sizeof(Table) * the_capacity);
}

void RewriteCache::initialize(int c)
{
  if (the_cache && the_capacity != c)
    clear();
  the_capacity = c;
  initialize();
}
