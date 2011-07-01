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

#ifndef memory_pool_h
#define memory_pool_h

#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  Each instance of class |MemPool| maintains a private pool of
//  memory that can be allocated in stack like fashion.  Destroying
//  a |MemPool| will free all the memory managed.
//
//  Memory allocated is guaranteed to be properly aligned for all
//  datatypes.
//////////////////////////////////////////////////////////////////////////////

class MemPool : public Mem
{
  MemPool(const MemPool&);          // no copy constructor
  void operator = (const MemPool&); // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type alias
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef Mem          Super;
  typedef Super::Align Align;

  ///////////////////////////////////////////////////////////////////////////
  //  Internal data structures
  ///////////////////////////////////////////////////////////////////////////

protected:
  struct Page
  {
    Page * lastPage;   // Last page in the linked list, if any
    Align data[1];     // The rest are the actual storage
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  long defaultPageSize; // default size of a page
  Page  * pages;        // a singly linked list of allocated pages
  Align * next;         // next available chunk from the current page
  Align * limit;        // high water mark of the current page

  friend class MemPoolMark;

  ///////////////////////////////////////////////////////////////////////////
  // Method to grow a page
  ///////////////////////////////////////////////////////////////////////////
  virtual void grow(long size);   // grow the memory pool

  ///////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  // Default page size of a pool is 1K bytes
  ///////////////////////////////////////////////////////////////////////////

public:
  MemPool(long pageSize = 1024);
  MemPool(Mem&, long pageSize = 1024);
  virtual ~MemPool();

  ///////////////////////////////////////////////////////////////////////////
  //  Fast method to allocate a block of memory
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator [] (size_t n)
  {
    register long elements = (n + sizeof(Align) - 1) / sizeof(Align);
    if (next + elements >= limit)
      grow(n);
    register void * core = next;
    next += elements;
    return core;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to get and set a mark
  ///////////////////////////////////////////////////////////////////////////
  virtual MemPoolMark getMark () const;
  virtual void        setMark (const MemPoolMark&);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to merge two memory pools(destructively)
  ///////////////////////////////////////////////////////////////////////////
  virtual void merge (MemPool&);

  ///////////////////////////////////////////////////////////////////////////
  //  Virtual methods for the basic Mem protocol
  ///////////////////////////////////////////////////////////////////////////
  virtual void   clear      ();
  virtual void * m_alloc    (size_t n)
  {
    return (*this)[n];
  }
  virtual void * c_alloc    (size_t);
  virtual void   free       (void *);
  virtual size_t bytes_used () const;
};

//////////////////////////////////////////////////////////////////////////////
//  A marker for a MemPool
//////////////////////////////////////////////////////////////////////////////

class MemPoolMark
{
  friend class MemPool;
  MemPool::Page * pages;
  MemPool::Align * next;
  MemPool::Align * limit;
};

//////////////////////////////////////////////////////////////////////////////
//  Overloaded new
//////////////////////////////////////////////////////////////////////////////

inline void* operator new (size_t n, MemPool& m)
{
  return m[n];
}

inline void* operator new (size_t, MemPool& m, size_t n)
{
  return m[n];
}

#endif
