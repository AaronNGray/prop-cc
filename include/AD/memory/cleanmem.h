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

#ifndef memory_manager_that_zeros_memory_when_freeing_h
#define memory_manager_that_zeros_memory_when_freeing_h

#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  The class |CleanMem| is a decorator that zeros memory that are
//  freed.  This can be used in conjunction with our conservative
//  GC to avoid false pointer identification.
//////////////////////////////////////////////////////////////////////////////

class CleanMem : public Mem
{
  CleanMem(const CleanMem&);          // no copy constructor
  void operator = (const CleanMem&);  // no assignment

protected:
  Mem& mem;  // internal memory manager

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  CleanMem();
  CleanMem(Mem&);
  virtual ~CleanMem();

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
};

#endif
