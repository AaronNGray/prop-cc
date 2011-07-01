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

#ifndef fibonacci_buddy_system_h
#define fibonacci_buddy_system_h

#include <AD/memory/mem.h>

/////////////////////////////////////////////////////////////////////////////
// Buddy system based memory manager\cite{LD-1991}.
/////////////////////////////////////////////////////////////////////////////

class Buddy : public Mem
{
  Buddy(const Buddy&);             // No copy constructor
  void operator = (const Buddy&);  // No assignment

  //////////////////////////////////////////////////////////////////////////
  //  Type alias
  //////////////////////////////////////////////////////////////////////////

public:
  typedef Mem Super;

  //////////////////////////////////////////////////////////////////////////
  //  Internals
  //////////////////////////////////////////////////////////////////////////

protected:
  struct Block
  {
    long  allocated;        //
    short right_buddies;    // Number of merges with right buddies before
    // becoming one.
    short fib_number;       // fibonacci number of block
    Block * next, * last;   // links to blocks of the same size
  };

  void *  my_pool;           // the starting address of the user supplied pool
  size_t  my_pool_size;      // size of this pool
  Block * begin, * end;      // beginning and end of the arena
  Block ** free_lists;       // an array of free lists arranged in sizes
  enum { levels = 32 };      // number of free lists

  virtual void init_pool(void *, size_t);

  //////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////////////////////

public:
  Buddy(void * pool, size_t poolSize);
  ~Buddy();

  //////////////////////////////////////////////////////////////////////////
  //  Methods to allocate/deallocate memory
  //////////////////////////////////////////////////////////////////////////
  void * operator [] (size_t n)
  {
    return m_alloc(n);
  }

  //////////////////////////////////////////////////////////////////////////
  //  Virtual methods for the basic protocol
  //////////////////////////////////////////////////////////////////////////
  virtual void   clear   ();
  virtual void * m_alloc (size_t);
  virtual void * c_alloc (size_t);
  virtual void   free    (void *);
  virtual size_t size    (const void *) const;
};

#endif
