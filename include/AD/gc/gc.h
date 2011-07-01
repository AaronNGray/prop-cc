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
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef garbage_collector_base_class_h
#define garbage_collector_base_class_h

#include <iostream>
#include <AD/memory/mem.h>          // memory manager base class
#include <AD/generic/generic.h>     // generic definitions
#include <AD/gc/gcintern.h>         // internal definitions
#include <AD/gc/rootset.h>          // root set base class
#include <AD/gc/gcconfig.h>         // configuration
#include <AD/gc/gctimer.h>          // timer stuff


//////////////////////////////////////////////////////////////////////////////
//  All garbage collectors must be derived from the class GC.
//////////////////////////////////////////////////////////////////////////////

class GC : public Mem, public GCRootSet
{
  GC(const GC&);                 // no copy constructor
  void operator = (const GC&);   // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  The default garbage collector can be set and reset with these
  //  static methods.  If placement syntax is not used with operator new,
  //  then the default garbage collector is used.
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef unsigned int GC_ID;
  static GC * default_gc;
  inline static void set_default_gc (GC& gc)
  {
    default_gc = &gc;
  }
  inline static void set_default_gc (GC* gc)
  {
    default_gc = gc;
  }
  inline static GC&  get_default_gc ()
  {
    return *default_gc;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Flag for things to print during gc.
  ///////////////////////////////////////////////////////////////////////////
  enum GCNotify {
    gc_no_notify                      = 0,
    gc_notify_minor_collection        = 1<<0,
    gc_notify_major_collection        = 1<<1,
    gc_notify_heap_expansion          = 1<<2,
    gc_notify_heap_info               = 1<<3,
    gc_notify_weak_pointer_collection = 1<<4,
    gc_print_collection_time          = 1<<10,
    gc_print_debugging_info           = 1<<15
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Garbage collection statistics.
  ///////////////////////////////////////////////////////////////////////////
  struct Statistics
  {
    const char * algorithm;       // garbage collection algorithm
    const char * version;         // version of algorithm
    size_t bytes_used;            // number of bytes used by application
    size_t bytes_managed;         // number of bytes managed by the collector
    size_t bytes_free;            // number of bytes free in heap
    size_t number_of_collections;     // number of collections
    size_t number_of_heap_expansions; // number of heap expansions
    GCTimer gc_user_time;           // user time used in gc
    GCTimer gc_system_time;         // system time used in gc
    GCTimer total_gc_user_time;     // total user time used in gc
    GCTimer total_gc_system_time;   // total system time used in gc
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Internal members
  ///////////////////////////////////////////////////////////////////////////

protected:
  int verbosity_level;   // how many messages should be printed?

  ///////////////////////////////////////////////////////////////////////////
  //  Ratio between used and total heap size before garbage collection
  //  is invoked.
  ///////////////////////////////////////////////////////////////////////////
  int gc_ratio;  // (in percentage)

  ///////////////////////////////////////////////////////////////////////////
  //  Console is where the messages go.
  ///////////////////////////////////////////////////////////////////////////
  std::ostream * console;

  ///////////////////////////////////////////////////////////////////////////
  //  Each method is given it's own id for identification
  ///////////////////////////////////////////////////////////////////////////
  GC_ID id;
  friend class GCHeapManager;
  static GC * collectors[256];
  static int  number_of_collectors;

  ///////////////////////////////////////////////////////////////////////////
  //  Should we perform finalization?   Default is off.
  ///////////////////////////////////////////////////////////////////////////
  Bool should_finalize;

  ///////////////////////////////////////////////////////////////////////////
  //  Should we perform weak pointer collection?   Default is on.
  ///////////////////////////////////////////////////////////////////////////
  Bool should_collect_weak_pointers;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  GC();
  virtual ~GC();

  ///////////////////////////////////////////////////////////////////////////
  //  Method that returns a name for the gc class
  ///////////////////////////////////////////////////////////////////////////
  virtual const char * my_name() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to deal with the ID number of a collector.
  ///////////////////////////////////////////////////////////////////////////
  inline GC_ID       gc_id () const
  {
    return id;
  }
  inline static GC * get_gc(GC_ID id)
  {
    return collectors[id];
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods that deals with the verbosity and messages
  ///////////////////////////////////////////////////////////////////////////
  virtual int      verbosity     () const;
  virtual Bool     is_verbose    () const;
  virtual Bool     is_debugging  () const;
  virtual void     set_verbosity (int);
  virtual void     set_console   (std::ostream&);
  virtual void     set_console   (std::ostream *);
  virtual std::ostream& get_console   () const;
  virtual Bool     has_console   () const;

  ///////////////////////////////////////////////////////////////////////////
  //  Returns the minimal heap growth required.
  ///////////////////////////////////////////////////////////////////////////
  virtual size_t min_growth() = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Method to set the ratio (in percentage) between used and total memory
  //  before garbage collection occurs.  Recommended value is between
  //  50 (collect more often) - 90 (collect when almost full).
  ///////////////////////////////////////////////////////////////////////////
  virtual void set_gc_ratio(int);

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to set the initial heap size and growth size.
  //  These may be ignored by the collectors
  ///////////////////////////////////////////////////////////////////////////
  virtual void set_initial_heap_size (size_t n);
  virtual void set_min_heap_growth   (size_t n);

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to allocate and deallocate storage.  These are to be
  //  implemented in derived classes.
  ///////////////////////////////////////////////////////////////////////////
  virtual void * m_alloc (size_t);
  virtual void * c_alloc (size_t);
  virtual void   free    (void *);

  ///////////////////////////////////////////////////////////////////////////
  //  Sets the finalization flag.  Returns the old flag.
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool set_finalization (Bool);

  ///////////////////////////////////////////////////////////////////////////
  //  Sets the weakpointer collection flag.  Returns the old flag.
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool set_weak_pointer_collection (Bool);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to trace and scavenge objects.  This should be defined in
  //  subclasses.
  ///////////////////////////////////////////////////////////////////////////
  virtual GCObject * trace (GCObject *) = 0;
  inline  void       trace (GCObject &);

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to invoke garbage collection manually.
  ///////////////////////////////////////////////////////////////////////////
  virtual       void collect         (int level = 0) = 0;
  virtual       void grow_heap       (size_t bytes)  = 0;
  inline static void garbage_collect (int level = 0)
  {
    GC::get_default_gc().collect(level);
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Accounting methods.
  ///////////////////////////////////////////////////////////////////////////
  static  void       reset_statistics(Statistics&);
  virtual Statistics statistics() = 0;
  virtual std::ostream&   print_statistics( std::ostream& );

  ///////////////////////////////////////////////////////////////////////////
  //  Auxiliary methods
  ///////////////////////////////////////////////////////////////////////////

protected:
  virtual void scan_user_roots ();
  virtual void error (const char *) const;  // error reporting
};

class GC_Initializer
{
public:
  GC_Initializer();
};

static GC_Initializer __initialize_gc__;

#endif
