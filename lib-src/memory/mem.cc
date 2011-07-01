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

#include <iostream>
#include <string.h>
#include <AD/memory/mem.h>
#include <AD/memory/sysmem.h>

//////////////////////////////////////////////////////////////////////////////
//  The default manager
//////////////////////////////////////////////////////////////////////////////
static SysMem * default_sysmem = 0;

Mem& Mem::system_mem()
{
  if (default_sysmem == 0)
    default_sysmem = new SysMem;
  return *default_sysmem;
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

Mem:: Mem()
{
  memory_manager_name = "Mem";
  manager_mem = &system_mem();
}

Mem:: Mem(const char manager_name[])
{
  memory_manager_name = manager_name;
  manager_mem = &system_mem();
}

Mem:: Mem(Mem& m, const char manager_name[])
{
  memory_manager_name = manager_name;
  manager_mem = &m;
}

Mem::~Mem()
{}

//////////////////////////////////////////////////////////////////////////////
//  Error reporting
//////////////////////////////////////////////////////////////////////////////

void Mem::error(const char message[]) const
{
  std::cerr << "Bug! [ " << memory_manager_name << "::" << message << "]\n";
}

//////////////////////////////////////////////////////////////////////////////
//  Set/get the manager
//////////////////////////////////////////////////////////////////////////////

void Mem::set_manager(Mem& mem)
{
  manager_mem = &mem;
}

Mem& Mem::get_manager()
{
  return *manager_mem;
}

//////////////////////////////////////////////////////////////////////////////
//  Default methods for allocation/deallocation
//////////////////////////////////////////////////////////////////////////////

void * Mem::m_alloc(size_t)
{
  error("m_alloc() is unimplemented");
  return 0;
}

void * Mem::c_alloc(size_t n)
{
  void * m = m_alloc(n);
  if (m)
    memset(m,0,n);
  return m;
}

void   Mem::clear()
{
  error("clear() is unimplemented");
}
void   Mem::free(void *)
{
  error("free() is unimplemented");
}
size_t Mem::size(const void *) const
{
  error("size() is unimplemented");
  return 0;
}

size_t Mem::bytes_used()       const
{
  error("bytes_used() is unimplemented");
  return 0;
}

size_t Mem::init_page_size(size_t n)   const
{
  size_t pages = 4096/n;
  return pages > 1 ? pages : 1;
}

size_t Mem::max_size(size_t n)         const
{
  return size_t(~0)/n;
}
