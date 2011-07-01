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

#include <AD/memory/arena.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

Arena::Arena(int byte_size, int n) : Mem("Arena")
{
  element_size      = (byte_size + sizeof(FreeList) - 1)/ sizeof(FreeList);
  elements_per_page = n;
  pages             = free_list = 0;
}

Arena::Arena(Mem& m, int byte_size, int n) : Mem(m, "Arena")
{
  element_size      = (byte_size + sizeof(FreeList) - 1)/ sizeof(FreeList);
  elements_per_page = n;
  pages             = free_list = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

Arena::~Arena()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
// Allocate a new page when the free list is empty.
//////////////////////////////////////////////////////////////////////////////

void * Arena::alloc()
{  //
  // Allocate a new page.  We need one more element than used for
  // the anchor in the page list.
  //
  FreeList * new_page =
    (FreeList *) manager_mem->m_alloc
    (sizeof(FreeList) * element_size * (elements_per_page + 2));
  //
  // Chain this page into the page list
  //
  new_page->next = pages;
  pages = new_page;

  //
  // Now construct new a free list.
  //
  register FreeList * ptr, * limit;
  for ( ptr   = new_page + 2 * element_size,
        limit = new_page + elements_per_page * element_size;
        ptr <= limit; ptr += element_size)
    ptr->next = ptr + element_size;
  ptr->next = free_list;
  free_list = new_page + 2 * element_size;

  //
  // Return the first element of the list.
  //
  return new_page + element_size;
}

//////////////////////////////////////////////////////////////////////////////
// Basic Mem protocol methods
//////////////////////////////////////////////////////////////////////////////

void Arena::clear()
{
  FreeList * this_page = pages;
  while (this_page)
  {
    FreeList * next_page = this_page->next;
    manager_mem->free(this_page);
    this_page = next_page;
  }
  pages = free_list = 0;
}
