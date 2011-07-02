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
#include <stdlib.h>
#include <iostream.h>
#include <AD/contain/variset.h>

VarIntSet::VarIntSet( size_t init_size, size_t g)
{
  limit  = (init_size + sizeof(Glob) * 8 - 1) / (sizeof(Glob) * 8);
  growth = g;
  array  = new Glob [limit];
  memset(array,0,limit * sizeof(Glob));
}

VarIntSet::~VarIntSet()
{
  delete [] array;
}

void VarIntSet::grow( size_t new_limit)
{
  if (new_limit >= 8*1024*1024)
  {
    std::cerr << "Limit exceeded in VarIntSet::grow(): " << new_limit << '\n';
    exit(1);
  }
  Glob * a = new Glob [ new_limit ];
  memcpy(a,array,limit * sizeof(Glob));
  memset(a+limit, 0, (new_limit - limit) * sizeof(Glob));
  delete [] array;
  array = a;
  limit = new_limit;
}
