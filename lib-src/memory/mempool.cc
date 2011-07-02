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
#include <AD/memory/mempool.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

MemPool::MemPool(long pageSize) : Mem("MemPool"),
    defaultPageSize(pageSize), pages(0), next(0), limit(0)
{}

MemPool::MemPool(Mem& m, long pageSize) : Mem(m,"MemPool"),
    defaultPageSize(pageSize), pages(0), next(0), limit(0)
{}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

MemPool::~MemPool()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
// Returns the total number of bytes used
//////////////////////////////////////////////////////////////////////////////

size_t MemPool::bytes_used() const
{
  Page * P;
  size_t bytes;
  for (bytes = 0, P = pages; P; P = P->lastPage)
    bytes += defaultPageSize;
  return bytes;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to increase the memory manager size
//////////////////////////////////////////////////////////////////////////////

void MemPool::grow(long size)
{
  if (defaultPageSize > size)
    size = defaultPageSize;
  long elements = (size + sizeof(Align) - 1) / sizeof(Align);
  long my_size  = sizeof(Page) + (elements-1) * sizeof(Align);
  Page * newPage = (Page*)manager_mem->m_alloc(my_size);
  newPage->lastPage = pages;
  pages = newPage;
  next = pages->data;
  limit = pages->data + elements;
}

//////////////////////////////////////////////////////////////////////////////
// Allocate some memory
//////////////////////////////////////////////////////////////////////////////

void * MemPool::c_alloc(size_t n)
{
  void * core = (*this)[n];
  memset(core,0,n);
  return core;
}

//////////////////////////////////////////////////////////////////////////////
// Get a memory pool mark
//////////////////////////////////////////////////////////////////////////////

MemPoolMark MemPool::getMark() const
{
  MemPoolMark M;
  M.pages  = pages;
  M.next   = next;
  M.limit  = limit;
  return M;
}

//////////////////////////////////////////////////////////////////////////////
// Reset memory manager to previous mark
//////////////////////////////////////////////////////////////////////////////

void MemPool::setMark(const MemPoolMark& mark)
{
  while (mark.pages != pages)
  {
    if (pages == NULL)
      return;
    Page * last = pages->lastPage;
    manager_mem->free(pages);
    pages = last;
  }
  next = mark.next;
  limit = mark.limit;
}

//////////////////////////////////////////////////////////////////////////////
//  Merge mempool M
//////////////////////////////////////////////////////////////////////////////

void MemPool::merge(MemPool& M)
{
  while (M.pages)
  {
    Page * last = M.pages->lastPage;
    if (pages)
    {
      M.pages->lastPage = pages;
      pages = M.pages;
    }
    else
    {
      pages = M.pages;
      M.pages = NULL;
      break;
    }
    M.pages = last;
  }

  M.next = M.limit = next = limit = NULL;
}

//////////////////////////////////////////////////////////////////////////////
// Mem protocol methods
//////////////////////////////////////////////////////////////////////////////

void MemPool::free(void *)
{ }

//////////////////////////////////////////////////////////////////////////////
// Clear the memory manager
//////////////////////////////////////////////////////////////////////////////

void MemPool::clear()
{
  Page * P = pages;
  while (P)
  {
    Page * last = P->lastPage;
    manager_mem->free(P);
    P = last;
  }
  pages = 0;
  next = 0;
  limit = 0;
}
