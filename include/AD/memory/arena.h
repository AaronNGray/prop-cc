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

#ifndef memory_arena_h
#define memory_arena_h

#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  An arena keeps track of elements of a fixed size determined at
//  creation time.   The elements are kept in a single free list.
//  All allocated storage is freed when an arena is destroyed.
//////////////////////////////////////////////////////////////////////////////

class Arena : public Mem
{

  Arena (const Arena&);             // No copy constructor
  void operator = (const Arena&);   // No assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type alias
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef Mem Super;

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////

protected:
  struct FreeList
  {
    FreeList * next;
  };

  FreeList * free_list;  // linked list of free elements
  FreeList * pages;      // linked list of allocated pages

  int element_size;      // rounded size of each element in sizeof(FreeList).
  int elements_per_page; // elements per page

  void * alloc();        // allocation method

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  Arena(int byte_size, int elements_per_page = 256);
  Arena(Mem&, int byte_size, int elements_per_page = 256);
  ~Arena();

  ///////////////////////////////////////////////////////////////////////////
  //  Fast allocation/deallocation methods
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator () ()
  {
    if (free_list)
    {
      register FreeList * cell = free_list;
      free_list = free_list->next;
      return cell;
    }
    else
      return alloc();
  }

  inline void basic_free (void * cell)
  {
    FreeList * chunk = (FreeList *)cell;
    chunk->next = free_list;
    free_list = chunk;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Virtual methods for the Mem protocol
  ///////////////////////////////////////////////////////////////////////////
  virtual void   clear  ();
  inline virtual void * m_alloc (size_t)
  {
    return (*this)();
  }
  inline virtual void free(void * cell)
  {
    basic_free(cell);
  }
  inline virtual size_t size  (const void *) const
  {
    return element_size * sizeof(FreeList);
  }
};

#endif
