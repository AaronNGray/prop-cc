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

#include <new.h>
#include <string.h>
#include <AD/memory/sysmem.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

SysMem:: SysMem() : Mem(*this,"SysMem")
{}
SysMem::~SysMem()
{}

//////////////////////////////////////////////////////////////////////////////
//  Allocation/deallocation
//////////////////////////////////////////////////////////////////////////////

void   SysMem::clear  ()
{
  error("clear() is unimplemented");
}

void * SysMem::m_alloc (size_t n)
{
  return new char [n];
}

void * SysMem::c_alloc (size_t n)
{
  void * t = new char [n];
  memset(t,0,n);
  return t;
}

void   SysMem::free   (void * p)
{
  delete [] ((char*)p);
}

size_t SysMem::size   (const void *) const
{
  error("size() is unimplemented");
  return 0;
}

size_t SysMem::bytes_used () const
{
  error("bytes_used() is unimplemented");
  return 0;
}
