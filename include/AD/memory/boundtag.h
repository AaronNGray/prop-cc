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

#ifndef boundary_tag_memory_manager_h
#define boundary_tag_memory_manager_h

//////////////////////////////////////////////////////////////////////////////
// Class |BoundaryTag| is a generic purpose memory manager based
// on the boundary tag algorithm.  In this algorithm, a free list
// of free memory blocks are kept.  The list is {\em not} sorted
// by address order, but rather, two {\bf tags} are kept in the
// the header of each allocated block, one denoting the size of
// the current block, and one denoting the size of the last block
// in address order.  Notice that the size of each block is actually
// duplicated within this scheme: one in the current header, and one
// in the header of the last block in the address order.  This way,
// it is possible to free a block and merge adjacent blocks in contant
// time.  Allocation, however, is accomplished using a roving first fit
// strategy.  Simulation results have shown that this algorithm
// performs efficiently if the pool of memory is not close to being
// exhausted\cite{LD-1991}
//////////////////////////////////////////////////////////////////////////////

#include <AD/memory/mem.h>

class BoundaryTag : public Mem
{
  BoundaryTag(const BoundaryTag&);      // no copy constructor
  void operator = (const BoundaryTag&); // no assignment

  ///////////////////////////////////////////////////////////////////////////
  // Type alias
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef Mem Super;

  ///////////////////////////////////////////////////////////////////////////
  // Internals
  ///////////////////////////////////////////////////////////////////////////

protected:
  //
  // A block header.
  //
  struct Block
  {
    LongWord last_size;    // Size of last block
    LongWord size;         // Size of current block
    Block * next, * last;  // Link to next and last block on the free list

    enum Block_constant {
      USED_BIT = 0xF0000000
    };
  };

  Block * freeList;        // Doubly linked circular free list
  Block stub;              // A dummy free block, not allocatable.

  struct Page
  {
    Page * next;                   // next page in the linked list of pages
    BoundaryTag::Block blocks[1];  // actual storage
  }
  * pages;                        // A linked list of pages allocated

  long pageSize;           // default size of a page
  long allocated;          // bytes allocated

  virtual void grow(long size);

  enum BoundaryTag_constant {
    MY_PAGE_SIZE = 1024  // Default page size is 1K bytes
  };

public:

  struct Statistics
  {
    long bytes_allocated;    // bytes allocated from system
    long bytes_available;    // bytes available in manager
    long free_block_count;   // number of free blocks within free list
    long page_count;         // number of pages allocated
  };

  ///////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  BoundaryTag(long defaultPageSize = MY_PAGE_SIZE);
  BoundaryTag(Mem&, long defaultPageSize = MY_PAGE_SIZE);
  ~BoundaryTag();

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for allocation
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator [] (long size)
  {
    return m_alloc(size);
  }
  char * operator [] (const char *);

  ///////////////////////////////////////////////////////////////////////////
  //  Get statistics
  ///////////////////////////////////////////////////////////////////////////
  Statistics statistics() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Virtual methods for the Mem protocol
  ///////////////////////////////////////////////////////////////////////////
  virtual void   clear  ();
  virtual void * m_alloc (size_t);
  virtual void   free   (void *);
  virtual size_t size   (const void *) const;
};

#endif
