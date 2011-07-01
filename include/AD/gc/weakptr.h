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

#ifndef weak_pointer_h
#define weak_pointer_h

//////////////////////////////////////////////////////////////////////////////
//  This file defines the interface to weakpointers into garbage collectable
//  objects.   Our implementation is based on John Ellis' proposal in:
//   ``Safe, Eifficient Garbage Collection for C++''
//////////////////////////////////////////////////////////////////////////////

#include <AD/gc/gc.h>          // Garbage collection base class
#include <AD/gc/gcobject.h>    // Collectable object base class

//////////////////////////////////////////////////////////////////////////////
//  Forward template declaration
//////////////////////////////////////////////////////////////////////////////

template <class T> class WeakPointer;

//////////////////////////////////////////////////////////////////////////////
//  Class to manage all the weakpointers into the collectable heap.
//////////////////////////////////////////////////////////////////////////////

class WeakPointerManager
{
  WeakPointerManager(const WeakPointerManager&); // no copy constructor
  void operator = (const WeakPointerManager&);   // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Some type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef long WP_TimeStamp;   // weak pointer timestamp
  typedef long WP_Index;       // weak pointer index
  struct WP_Entry
  {            // weak pointer entry in table.
    GCObject     * object;    // actual collectable object
    WP_TimeStamp   timestamp; // timestamp of this entry
    WP_Entry *     next;      // next free entry
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Private data
  ///////////////////////////////////////////////////////////////////////////

private:
  static WP_TimeStamp wp_timestamp;       // Next available timestamp
  static WP_Entry *   wp_table;           // A table of weakpointers
  static WP_Entry *   wp_next_free;       // Next free entry
  static void *       wp_table_core;      // The actual table
  static size_t       wp_table_capacity;  // Capacity of current table
  static size_t       wp_table_size;      // Number of entries

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  WeakPointerManager();
  ~WeakPointerManager();

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline static int size()
  {
    return wp_table_size;
  }
  inline static int capacity()
  {
    return wp_table_capacity;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to
  //    (1) add a new pointer into the weakpointer table,
  //    (2) expand the table, and
  //    (3) scavenge dead entries in the table.
  ///////////////////////////////////////////////////////////////////////////
  static WP_Index add_pointer(GCObject *,WP_TimeStamp&);
  static void     grow_wp_table();
  static void     scavenge_wp_table(GC *);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to index into the wp table
  ///////////////////////////////////////////////////////////////////////////
  inline static WP_Entry * get
    (WP_Index i)
  {
    return wp_table + i;
  }
};

//////////////////////////////////////////////////////////////////////////////
//  Okay, this is the weakpointer template that the user actual uses.
//////////////////////////////////////////////////////////////////////////////

template <class T>
class WeakPointer
{
public:
  ////////////////////////////////////////////////////////////////////////
  //  Import some types from the manager class
  ////////////////////////////////////////////////////////////////////////
  typedef WeakPointerManager::WP_TimeStamp WP_TimeStamp;
  typedef WeakPointerManager::WP_Index     WP_Index;
  typedef WeakPointerManager::WP_Entry     WP_Entry;

private:
  ////////////////////////////////////////////////////////////////////////
  //  A weakpointer is actually stored as an index + a timestamp.
  ////////////////////////////////////////////////////////////////////////

  WP_Index     _index;      // index into with weakpointer table
  WP_TimeStamp _timestamp;  // timestamp of object

public:
  ////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////
  inline WeakPointer()
      : _index(0), _timestamp(0)
  {}
  inline WeakPointer(const WeakPointer<T>& wp)
      : _index(wp._index), _timestamp(wp._timestamp)
  {}
  inline WeakPointer(T * ptr)
  {
    _index = WeakPointerManager::add_pointer(ptr,_timestamp);
  }

  ////////////////////////////////////////////////////////////////////////
  //  Retrieve the pointer.
  ////////////////////////////////////////////////////////////////////////
  inline const GCObject * _get_pointer() const
  {
    return (WeakPointerManager::get
              (_index)->timestamp == _timestamp)
             ? (WeakPointerManager::get
                  (_index)->object) : 0;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Assignments
  ////////////////////////////////////////////////////////////////////////
  inline WeakPointer<T>& operator = (const WeakPointer<T>& wp)
  {
    _index = wp._index;
    _timestamp = wp._timestamp;
    return *this;
  }
  inline WeakPointer<T>& operator = (T * ptr)
  {
    _index = WeakPointerManager::add_pointer(ptr,_timestamp);
    return *this;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Test whether the weakpointer is dead.
  ////////////////////////////////////////////////////////////////////////
  inline Bool is_null() const
  {
    return _get_pointer() == 0;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Conversions
  ////////////////////////////////////////////////////////////////////////
  inline operator const T * () const
  {
    return (const T*)_get_pointer();
  }
  inline operator       T * ()
  {
    return (T*)_get_pointer();
  }

  ////////////////////////////////////////////////////////////////////////
  //   Dereferencing with -> and *
  ////////////////////////////////////////////////////////////////////////
  inline const T * operator -> () const
  {
    return (const T*)_get_pointer();
  }
  inline       T * operator -> ()
  {
    return (T*)_get_pointer();
  }
  inline const T&  operator *  () const
  {
    return *(const T*)_get_pointer();
  }
  inline       T&  operator *  ()
  {
    return *(T*)_get_pointer();
  }
};

#endif
