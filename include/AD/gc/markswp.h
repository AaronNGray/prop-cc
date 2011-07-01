//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef Mark_sweep_garbage_collector_h
#define Mark_sweep_garbage_collector_h

#include <AD/generic/generic.h>  // generic definitions
#include <AD/gc/gc.h>            // garbage collector base class
#include <AD/gc/cgc.h>           // conservative gc
#include <AD/gc/gcobject.h>      // garbage collectable objects
#include <AD/gc/gcbitmap.h>      // bitmaps

//////////////////////////////////////////////////////////////////////////////
//  Conservative mark sweep garbage collector class.
//  It is derived from the class CGC (conservative gc class).
//////////////////////////////////////////////////////////////////////////////

class MarkSweepGC : public CGC
{
  MarkSweepGC(const MarkSweepGC&);        // no copy constructor
  void operator = (const MarkSweepGC&);   // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef CGC               Super;
  typedef Super::Statistics Statistics;
  struct FreeList
  {
    FreeList * next;
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Internal members
  ///////////////////////////////////////////////////////////////////////////

protected:
  Statistics stat;           // statistics

  ///////////////////////////////////////////////////////////////////////////
  //  The free lists and related info.
  ///////////////////////////////////////////////////////////////////////////
  size_t      heap_size;       // bytes we own
  size_t      heap_used;       // bytes used by the application
  size_t      heap_free;       // bytes we have left
  Byte *      heap_pointer;    // a block of free memory
  Byte *      heap_limit;      // limit of this free block
  FreeList ** free_lists;      // free lists partitioned by object size
  size_t      free_list_size;  // size of the free lists array

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  MarkSweepGC();
  virtual ~MarkSweepGC();

  ///////////////////////////////////////////////////////////////////////////
  //  Name of class
  ///////////////////////////////////////////////////////////////////////////
  virtual const char * my_name() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to allocate and deallocate storage.
  ///////////////////////////////////////////////////////////////////////////
  virtual void * m_alloc (size_t);
  virtual void   free    (void *);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to compute the minimal number of bytes to expand during
  //  a heap growth.
  ///////////////////////////////////////////////////////////////////////////
  virtual size_t min_growth();

  ///////////////////////////////////////////////////////////////////////////
  //  Method to trace and scavenge objects.
  ///////////////////////////////////////////////////////////////////////////
  virtual GCObject * trace (GCObject *);

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for invoking garbage collection
  ///////////////////////////////////////////////////////////////////////////
  virtual void clear     ();
  virtual void collect   (int level = 0);
  virtual void grow_heap (size_t);

  ///////////////////////////////////////////////////////////////////////////
  //  Accounting method
  ///////////////////////////////////////////////////////////////////////////
  virtual Statistics statistics();

  ///////////////////////////////////////////////////////////////////////////
  //  Internal methods
  ///////////////////////////////////////////////////////////////////////////

protected:
  virtual void do_collect               (int level);
  virtual void scan_stack_area          ();
  virtual void scan_static_area         ();
  virtual void scan_heap_area           ();
  inline  void scan_for_roots           (void **, void **);
  virtual void sweep_pages              ();
  virtual void start_collection_message ();
  virtual void end_collection_message   ();
  virtual void heap_expansion_message   ();
};

#endif
