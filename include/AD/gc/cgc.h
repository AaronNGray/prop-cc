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

#ifndef conservative_gc_base_class_h
#define conservative_gc_base_class_h

#include <AD/generic/generic.h>  // generic definitions
#include <AD/gc/gc.h>            // garbage collector base class
#include <AD/gc/gcobject.h>      // garbage collectable objects
#include <AD/gc/gcmacros.h>      // useful macros

//////////////////////////////////////////////////////////////////////////////
//  Base class for conservative garbage collectors.
//  This class contains methods for locating the stack, heap, and
//  static data areas.
//////////////////////////////////////////////////////////////////////////////
class CGC : public GC
{
  CGC(const CGC&);                // no copy constructor
  void operator = (const CGC&);   // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef GC                Super;
  typedef Super::Statistics Statistics;

  static void * global_heap_bottom;

  ///////////////////////////////////////////////////////////////////////////
  //  Stack frame and static data info.
  ///////////////////////////////////////////////////////////////////////////

protected:
  Bool    is_downward_stack;   // does the stack grows downward
  void ** stack_bottom;        // logical bottom of the system stack
  void ** stack_top;           // logical top of the system stack
  void ** data_bottom;         // logical bottom of the static area
  void ** data_top;            // logical top of the static area
  void ** heap_bottom;         // logical bottom of the system heap
  void ** heap_top;            // logical top of the system heap

  ///////////////////////////////////////////////////////////////////////////
  // Initial heap size and the amount to expand during heap expansion.
  ///////////////////////////////////////////////////////////////////////////
  size_t initial_heap_size;
  size_t min_heap_growth;

  ///////////////////////////////////////////////////////////////////////////
  // Queue for recording new pages used during tracing.
  // Promoted pages are added into this queue during scanning.
  ///////////////////////////////////////////////////////////////////////////
  size_t   * scan_queue;
  size_t   * scan_limit_queue;
  size_t     scan_queue_size;
  size_t     number_of_pages_to_scan;

  ///////////////////////////////////////////////////////////////////////////
  //  Statistics during collection.
  ///////////////////////////////////////////////////////////////////////////
  size_t pages_promoted;    // pages promoted after marking
  size_t objects_promoted;  // objects promoted after marking

  Statistics stat;          // current statistics

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  CGC();
  virtual ~CGC();

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for manipulating the initial heap size and heap growth
  ///////////////////////////////////////////////////////////////////////////
  virtual void set_initial_heap_size (size_t);
  virtual void set_min_heap_growth   (size_t);

  ///////////////////////////////////////////////////////////////////////////
  //  Returns the size of an allocated object.
  ///////////////////////////////////////////////////////////////////////////
  virtual size_t size(const void *) const;

  ///////////////////////////////////////////////////////////////////////////
  //  Locate the current heap top.
  ///////////////////////////////////////////////////////////////////////////

protected:
  static void * get_heap_bottom();
  static void * get_address_limit(void *, void *, int);
  virtual void get_heap_top();    // locate the current top of heap
  virtual void verify_heap_top(); // check the heap top for consistency
  virtual void flush_registers(); // flush register windows

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for manipulating the scanning queue.
  ///////////////////////////////////////////////////////////////////////////
  inline void clear_scan_queue()
  {
    pages_promoted          = 0;
    objects_promoted        = 0;
    number_of_pages_to_scan = 0;
  }
  inline void enqueue_pages_to_scan(void * start, void * limit)
  {
    scan_queue      [number_of_pages_to_scan] = GC_PAGE_ID(start);
    scan_limit_queue[number_of_pages_to_scan] = GC_PAGE_ID(limit);
    number_of_pages_to_scan++;
  }
  void grow_scan_queue(size_t pages);

  ///////////////////////////////////////////////////////////////////////////
  //  Miscellaneous scanning messages methods.
  ///////////////////////////////////////////////////////////////////////////
  virtual void initialization_message   () const;
  virtual void cleanup_message          () const;
  virtual void scanning_message         (const char *, void *, void *) const;

  virtual void do_weak_pointer_collection ();
};

#endif
