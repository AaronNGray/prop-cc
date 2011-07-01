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

#ifndef Bartletts_mostly_copying_conservative_garbage_collector_h
#define Bartletts_mostly_copying_conservative_garbage_collector_h

#include <AD/generic/generic.h>  // generic definitions
#include <AD/gc/gc.h>            // garbage collector base class
#include <AD/gc/cgc.h>           // conservative collector
#include <AD/gc/gcobject.h>      // garbage collectable objects
#include <AD/gc/gcbitmap.h>      // bitmaps

//////////////////////////////////////////////////////////////////////////////
//  Barlett's mostly copying conservative garbage collector class.
//////////////////////////////////////////////////////////////////////////////

class BGC : public CGC
{
  BGC(const BGC&);                // no copy constructor
  void operator = (const BGC&);   // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef CGC               Super;
  typedef Super::Statistics Statistics;
  enum Phase { mutation_phase,
               marking_phase,
               copying_phase
             };

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internal members.
  //
  //  We keep a chunk of the heap at a time delimited by `heap_pointer'
  //  and `heap_limit'.  Allocation is fast since all we have to do
  //  is to check the size, make an object header, and update the heap
  //  pointer.
  //
  //  To make it possible to invoke garbage collection before the hard
  //  limit is reached, we also keep around the pointer `gc_limit.'  A
  //  collection is invoked if we reach this limit.
  //
  //  The variables `heap_used' and `heap_size' keep track of how much
  //  memory is used and what the total heap size is.  Notice that
  //  the heap size is only the number of pages owned by this instance of
  //  the collector, not the total heap size managed by the heap manager.
  //  (That's another layer of abstraction.)
  ///////////////////////////////////////////////////////////////////////////
  Byte * heap_start;        // start of the current fragment
  Byte * heap_pointer;      // next available space in current fragment
  Byte * heap_limit;        // hard limit of this fragment
  Byte * gc_limit;          // invoke garbage collection when this is reached.
  Bool   should_collect;    // should we garbage collect?
  Phase  phase;             // current phase of collection
  size_t heap_size;         // current heap size that we own.
  size_t heap_used;         // bytes currently used in heap

  ///////////////////////////////////////////////////////////////////////////
  //  Statistics during collection.
  ///////////////////////////////////////////////////////////////////////////
  size_t bytes_copied;     // bytes copied during a collection phase
  size_t pages_removed;    // pages removed after a collection

  Statistics stat;         // current statistics

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  BGC();
  virtual ~BGC();

  ///////////////////////////////////////////////////////////////////////////
  //  Name of class
  ///////////////////////////////////////////////////////////////////////////
  virtual const char * my_name() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to allocate and deallocate storage.
  ///////////////////////////////////////////////////////////////////////////
  virtual void * m_alloc (size_t);
  virtual void   free    (void *);
  inline  size_t immed_avail() const
  {
    return heap_limit - heap_pointer;
  }
  void * operator [] (size_t);

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
  //  Methods for invoking garbage collection.
  //     clear     --- release all the memory (UNSAFE!)
  //     collect   --- forces a garbage collection
  //     grow_heap --- increase the heap size manually
  ///////////////////////////////////////////////////////////////////////////
  virtual void clear     ();
  virtual void collect   (int level = 0);
  virtual void grow_heap (size_t);

  ///////////////////////////////////////////////////////////////////////////
  //  Accounting method
  ///////////////////////////////////////////////////////////////////////////
  virtual Statistics statistics();

protected:
  ///////////////////////////////////////////////////////////////////////////
  //  Various phases of the collection process
  ///////////////////////////////////////////////////////////////////////////
  virtual void do_collect          (int level);
  virtual void copy_promoted_pages ();

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for scanning the stack, heap, and static data areas.
  //  Used only by subclasses.
  ///////////////////////////////////////////////////////////////////////////
  virtual void scan_stack_area     ();
  virtual void scan_static_area    ();
  virtual void scan_heap_area      ();
  inline  void scan_for_roots      (void **, void **);
  virtual void do_finalization     ();

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for printing messages during various phases of the collection
  //  process.
  ///////////////////////////////////////////////////////////////////////////
  virtual void heap_growth_message      (size_t, size_t) const;
  virtual void start_collection_message () const;
  virtual void end_collection_message   () const;
};

//////////////////////////////////////////////////////////////////////////////
//  The default instance of this collector is called bgc;
//////////////////////////////////////////////////////////////////////////////
extern BGC bgc;

#endif
