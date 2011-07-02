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

#include <iostream.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <AD/gc/gcconfig.h>  // system configuration
#include <AD/gc/gc.h>        // garbage collector base class
#include <AD/gc/gcobject.h>  // garbage collectable objects
#include <AD/gc/gctimer.h>   // timer stuff
#include <AD/gc/gcmacros.h>  // useful macros

//////////////////////////////////////////////////////////////////////////////
//  Static data
//////////////////////////////////////////////////////////////////////////////

GC * GC::collectors[ GC_MAX_NUMBER_OF_COLLECTORS ];
int  GC::number_of_collectors = 0;

//////////////////////////////////////////////////////////////////////////////
//  Method that returns a name for the collector
//////////////////////////////////////////////////////////////////////////////

const char * GC::my_name() const
{
  return "GC";
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

GC:: GC()
    : Mem("GC"),
    verbosity_level( GC::gc_notify_minor_collection |
                     GC::gc_notify_major_collection |
                     GC::gc_notify_weak_pointer_collection |
                     GC::gc_notify_heap_expansion   |
                     GC::gc_notify_heap_info        |
                     GC::gc_print_collection_time
                   ),
    gc_ratio(75),
    console(&std::cerr),
    should_finalize(false),
    should_collect_weak_pointers(true)
{
  //
  // Assign a gc ID number to each collector.
  // It must be non-zero.
  //
  if (number_of_collectors >= GC_MAX_NUMBER_OF_COLLECTORS)
  {
    error ("Number of collectors exceeded the hard limit");
    exit(1);
  }
  for (id = 1; id < GC_MAX_NUMBER_OF_COLLECTORS; id++)
  {
    if (collectors[id] == 0)
    {
      collectors[id] = this;
      break;
    }
  }
  number_of_collectors++;
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

GC::~GC()
{
  collectors[id] = 0;
  number_of_collectors--;
}

//////////////////////////////////////////////////////////////////////////////
//  The default method for free doesn't do anything.
//////////////////////////////////////////////////////////////////////////////

void GC::free(void * /* obj */)
{}

//////////////////////////////////////////////////////////////////////////////
//  The default method for c_alloc just calls the m_alloc routine.
//  We assume all subclasses already initialize memory to zeros.
//////////////////////////////////////////////////////////////////////////////

void * GC::c_alloc(size_t n)
{
  return m_alloc(n);
}

void * GC::m_alloc(size_t)
{
  error("m_alloc() is unimplemented");
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Methods that deal the verbosity and console messages.
//////////////////////////////////////////////////////////////////////////////

int  GC::verbosity() const
{
  return verbosity_level;
}

Bool GC::is_verbose() const
{
  return verbosity_level &
         (gc_notify_minor_collection | gc_notify_major_collection);
}

Bool GC::is_debugging() const
{
  return verbosity_level & gc_print_debugging_info;
}

void GC::set_verbosity( int v)
{
  verbosity_level = v;
}

void GC::set_console( std::ostream& f)
{
  console = &f;
}
void GC::set_console( std::ostream * f)
{
  set_console (*f);
}
std::ostream& GC::get_console() const
{
  return *console;
}
Bool GC::has_console() const
{
  return console != 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Default set gc ratio method does nothing
//////////////////////////////////////////////////////////////////////////////

void GC::set_gc_ratio( int r)
{
  gc_ratio = r;
}

void GC::set_initial_heap_size( size_t)
{}

void GC::set_min_heap_growth( size_t)
{}

//////////////////////////////////////////////////////////////////////////////
//  Method to set/reset the finalization flag
//////////////////////////////////////////////////////////////////////////////

Bool GC::set_finalization( Bool f)
{
  Bool old_flag = should_finalize;
  should_finalize = f;
  return old_flag;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to set/reset the weak pointer collection flag
//////////////////////////////////////////////////////////////////////////////

Bool GC::set_weak_pointer_collection( Bool f)
{
  Bool old_flag = should_collect_weak_pointers;
  should_collect_weak_pointers = f;
  return old_flag;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for printing an error message
//////////////////////////////////////////////////////////////////////////////

void GC::error( const char * message) const
{
  std::ostream * f;
  if (has_console())
    f = &get_console();
  else
    f = &std::cerr;
  (*f) << '[' << my_name() << ": " << message << "]\n" << flush;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to reset statistics
//////////////////////////////////////////////////////////////////////////////

void GC::reset_statistics( GC::Statistics& stat)
{
  stat.bytes_used                = 0;
  stat.bytes_managed             = 0;
  stat.bytes_free                = 0;
  stat.number_of_collections     = 0;
  stat.number_of_heap_expansions = 0;
  stat.gc_user_time.clear();
  stat.gc_system_time.clear();
  stat.total_gc_user_time.clear();
  stat.total_gc_system_time.clear();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to print the statistics
//////////////////////////////////////////////////////////////////////////////

std::ostream& GC::print_statistics( std::ostream& f)
{
  Statistics s = statistics();
  f << "[ Algorithm:                 " << s.algorithm                 << '\n'
  << "  Version:                   " << s.version                   << '\n'
  << "  Bytes used:                " << s.bytes_used                << '\n'
  << "  Bytes in heap:             " << s.bytes_managed             << '\n'
  << "  Bytes available:           " << s.bytes_free                << '\n'
  << "  Number of collections:     " << s.number_of_collections     << '\n'
  << "  Number of heap expansions: " << s.number_of_heap_expansions << '\n'
#ifdef GC_USE_TIMER
  << "  Total GC time:             "
  << (s.total_gc_system_time + s.total_gc_user_time)
  << " (user: " << s.total_gc_user_time
  << ", system: " << s.total_gc_system_time << ")\n"
#endif
  << "]\n"
  ;
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//  Method for scanning user roots
//////////////////////////////////////////////////////////////////////////////

void GC::scan_user_roots()
{
  int i;

  // scan root objects.
  for (i = 0; i < number_of_objects(); i++)
  {
    root_obj(i).trace(this);
  }

  // scan root pointers
  for (i = 0; i < number_of_pointers(); i++)
  {
    GCObject * ptr = root_ptr(i);
    if (ptr)
      ptr->trace(this);
  }
}
