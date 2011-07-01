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

#ifndef memory_manager_base_class_h
#define memory_manager_base_class_h

#include <new>
#include <stdlib.h>
#include <AD/generic/generic.h>


//////////////////////////////////////////////////////////////////////////////
//  The class |Mem| represents the basic protocol of a memory manager
//  with at least a method to acquire memory.  Most memory managers in this
//  library are subclasses.
//
//  Some subclasses, however, define their own inlined methods to
//  perform allocation/deallocation.  The user can choose to fix the
//  class to use those methods, or use the protocol defined in
//  this class for generality.  In general, this protocol should be
//  used.
//////////////////////////////////////////////////////////////////////////////

class Mem
{
  Mem(const Mem&);               // no copy constructor
  void operator = (const Mem&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  A simple type for memory alignment needs
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef union
  {
    long a;
    double b;
    void * c;
  } Align;

  ///////////////////////////////////////////////////////////////////////////
  //  STL style type definitions
  ///////////////////////////////////////////////////////////////////////////

  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;

  ///////////////////////////////////////////////////////////////////////////
  //  Name of the memory manager
  ///////////////////////////////////////////////////////////////////////////

protected:
  const char * memory_manager_name;
  Mem *        manager_mem;

  ///////////////////////////////////////////////////////////////////////////
  //  Get/set the manager of this class
  ///////////////////////////////////////////////////////////////////////////
  void   set_manager(Mem&);
  Mem&   get_manager();

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  Mem();
  Mem(const char manager_name[]);
  Mem(Mem&, const char manager_name[]);
  virtual ~Mem();

  ///////////////////////////////////////////////////////////////////////////
  //  Memory allocation/deallocation.
  //    The names malloc() and calloc() have been changed to
  //    m_alloc() and c_alloc() respectively to avoid name conflict with
  //    GNU <stdlib.h> macros definitions.
  ///////////////////////////////////////////////////////////////////////////

  virtual void   clear   ();                   // release all the memory within
  virtual void * m_alloc (size_t);             // acquire a block of memory of size n
  virtual void * c_alloc (size_t);             // acquire and initialize to 0's
  virtual void   free    (void *);             // release the memory
  virtual size_t size    (const void *) const; // returns the size of a block
  virtual size_t bytes_used () const;          // returns the amount of storage used

  ///////////////////////////////////////////////////////////////////////////
  //  Additional STL style protocol
  ///////////////////////////////////////////////////////////////////////////
  // optimal buffer(page) size for an object of size n
  virtual size_t init_page_size(size_t n) const;
  // maximum capacity for an object of size n
  virtual size_t max_size(size_t n)       const;

  ///////////////////////////////////////////////////////////////////////////
  //   Miscellaneous
  ///////////////////////////////////////////////////////////////////////////
  virtual void   error   (const char message[]) const; // report an error

  static Mem& system_mem();
};

//////////////////////////////////////////////////////////////////////////////
//  Allocate memory from mem using the operator new.
//////////////////////////////////////////////////////////////////////////////

inline void* operator new (size_t n, Mem& mem)
{
  return mem.m_alloc(n);
}

inline void* operator new (size_t n, Mem& mem, size_t m)
{
  return mem.m_alloc(n * m);
}

inline void* operator new (size_t n, Mem * mem)
{
  return mem->m_alloc(n);
}

inline void* operator new (size_t n, Mem * mem, size_t m)
{
  return mem->m_alloc(n * m);
}

#endif
