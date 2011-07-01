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

#include <string.h>
#include <AD/memory/cleanmem.h>
#include <AD/memory/sysmem.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

CleanMem:: CleanMem(Mem& m) : Mem("CleanMem"), mem(m)
{}
CleanMem::~CleanMem()
{}

//////////////////////////////////////////////////////////////////////////////
//  Error reporting
//////////////////////////////////////////////////////////////////////////////

void CleanMem::error(const char message[]) const
{
  mem.error(message);
}

//////////////////////////////////////////////////////////////////////////////
//  Methods for allocation/deallocation
//////////////////////////////////////////////////////////////////////////////

void * CleanMem::m_alloc(size_t n)
{
  return mem.m_alloc(n);
}

void * CleanMem::c_alloc(size_t n)
{
  return mem.c_alloc(n);
}

void   CleanMem::clear()
{
  mem.clear();
}

void   CleanMem::free(void * p)
{
  if (p)
  {
    size_t n = mem.size(p);
    memset(p,0,n);
    mem.free(p);
  }
}

size_t CleanMem::size(const void * p) const
{
  return mem.size(p);
}

size_t CleanMem::bytes_used() const
{
  return mem.bytes_used();
}

size_t CleanMem::init_page_size(size_t n) const
{
  return mem.init_page_size(n);
}

size_t CleanMem::max_size(size_t n) const
{
  return mem.max_size(n);
}
