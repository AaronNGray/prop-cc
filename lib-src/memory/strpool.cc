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
#include <AD/memory/strpool.h>

//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////

StringPool::StringPool(size_t page_size) : Mem("StringPool")
{
  next = limit = 0;
  pages = 0;
  pageSize = page_size;
  bytes_reserved = 0;
}

StringPool::StringPool(Mem& m, size_t page_size) : Mem(m,"StringPool")
{
  next = limit = 0;
  pages = 0;
  pageSize = page_size;
  bytes_reserved = 0;
}

//////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////

StringPool::~StringPool()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
// Method to increase the size of the pool
//////////////////////////////////////////////////////////////////////////////

void StringPool::grow(size_t len)
{
  size_t size = len > pageSize ? len : pageSize;
  Page * newPage = (Page*)manager_mem->m_alloc(sizeof(Page) + size - 1);
  newPage->next = pages;
  pages = newPage;
  next = pages->data;
  limit = next + size;
  bytes_reserved += size;
}

//////////////////////////////////////////////////////////////////////////////
// Acquire a string of length $len$ from the pool and initialize it
//////////////////////////////////////////////////////////////////////////////

char * StringPool::operator () (const char * str, int len)
{
  char * newStr = (*this)[len + 1];
  memcpy(newStr,str,len);
  newStr[len] = '\0';
  return newStr;
}

//////////////////////////////////////////////////////////////////////////////
// Acquire a string from the pool and initialize it
//////////////////////////////////////////////////////////////////////////////

char * StringPool::operator [] (const char * str)
{
  char * newStr = (*this)[strlen(str)+1];
  strcpy(newStr,str);
  return newStr;
}

//////////////////////////////////////////////////////////////////////////////
// Mem protocol methods
//////////////////////////////////////////////////////////////////////////////

void StringPool::free(void *)
{}

size_t StringPool::bytes_used() const
{
  return bytes_reserved;
}

//////////////////////////////////////////////////////////////////////////////
// Clear the pool
//////////////////////////////////////////////////////////////////////////////

void StringPool::clear()
{
  Page * next_page;
  for (Page * p = pages; p; p = next_page)
  {
    next_page = p->next;
    manager_mem->free(p);
  }
  next = limit = 0;
  pages = 0;
}
