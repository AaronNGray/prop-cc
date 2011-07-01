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

#include <AD/memory/blacklistmem.h>
#include <AD/gc/gcheaps.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

BlacklistMem:: BlacklistMem(Mem& m) : Mem("BlacklistMem"), mem(m)
{}

BlacklistMem::~BlacklistMem()
{}

//////////////////////////////////////////////////////////////////////////////
//  Error reporting
//////////////////////////////////////////////////////////////////////////////

void BlacklistMem::error(const char message[]) const
{
  mem.error(message);
}

//////////////////////////////////////////////////////////////////////////////
//  Methods for allocation/deallocation
//////////////////////////////////////////////////////////////////////////////

void * BlacklistMem::m_alloc(size_t n)
{
  void * p = mem.m_alloc(n);
  HM::blacklist(p,n);
  return p;
}

void * BlacklistMem::c_alloc(size_t n)
{
  void * p = mem.c_alloc(n);
  HM::blacklist(p,n);
  return p;
}

void   BlacklistMem::clear()
{
  mem.clear();
}

void   BlacklistMem::free(void * p)
{
  if (p)
  {
    size_t n = mem.size(p);
    memset(p,0,n);
    mem.free(p);
    HM::unblacklist(p,n);
  }
}

size_t BlacklistMem::size(const void * p) const
{
  return mem.size(p);
}

size_t BlacklistMem::bytes_used() const
{
  return mem.bytes_used();
}

size_t BlacklistMem::init_page_size(size_t n) const
{
  return mem.init_page_size(n);
}

size_t BlacklistMem::max_size(size_t n) const
{
  return mem.max_size(n);
}
