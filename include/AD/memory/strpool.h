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

#ifndef string_pool_h
#define string_pool_h

#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  Class StringPool is similar to a MemPool, except that the objects
//  allocated are assumed to be strings, within alignment restrictions
//////////////////////////////////////////////////////////////////////////////

class StringPool : public Mem
{
  StringPool(const StringPool&);        // no copy constructor
  void operator = (const StringPool&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  // Type alias
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef Mem Super;

  ///////////////////////////////////////////////////////////////////////////
  // Internals
  ///////////////////////////////////////////////////////////////////////////

protected:
  struct Page
  {
    Page * next;    // link to next page
    char data[1];   // the real storage
  };

  Page * pages;

  size_t pageSize;             // size of a page
  char * next;                 // next available location in pool
  char * limit;                // limit to current page
  long   bytes_reserved;       // bytes allocated

  virtual void grow(size_t);

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  StringPool(size_t pageSize = 4096);
  StringPool(Mem&, size_t pageSize = 4096);
  ~StringPool();

  ///////////////////////////////////////////////////////////////////////////
  //  Fast method to allocate
  ///////////////////////////////////////////////////////////////////////////
  inline char * operator[] (register long len)
  {
    if (next + len >= limit)
      this->grow(len);
    register char * last = next;
    next += len;
    return last;
  }

  char * operator () (const char *, int);
  char * operator [] (const char *);

  ///////////////////////////////////////////////////////////////////////////
  //  Virtual methods for the basic protocol
  ///////////////////////////////////////////////////////////////////////////
  virtual void   clear   ();
  virtual void * m_alloc (size_t n)
  {
    return (*this)[n];
  }
  virtual void   free    (void *);
  virtual size_t bytes_used () const;
};

#endif
