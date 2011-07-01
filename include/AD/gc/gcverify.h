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

#ifndef gc_verifier_h
#define gc_verifier_h

#include <AD/gc/gc.h>            // garbage collector base class
#include <AD/gc/gcobject.h>      // garbage collectable objects

//////////////////////////////////////////////////////////////////////////////
//  Forward declaration.
//////////////////////////////////////////////////////////////////////////////

class GCBitMap;

//////////////////////////////////////////////////////////////////////////////
//  This class is used to check for integrity of an GCObject.
//  It uses the same interface as the collector so it is derived from
//  class GC.
//////////////////////////////////////////////////////////////////////////////

class GCVerifier : public GC
{
  GCVerifier(const GCVerifier&);        //  no copy constructor
  void operator = (const GCVerifier&);  //  no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef GC             Super;
  typedef GC::Statistics Statistics;

  ///////////////////////////////////////////////////////////////////////////
  //  Internal members cached during checking
  ///////////////////////////////////////////////////////////////////////////

protected:
  Bool       ok;         // okay flag (reset if error is found)
  GC *       testing_gc; // the collector to test.
  GCBitMap * traversed;  // marks all objects that have been traversed
  // so that circular structures can be correctly
  // traced.
  size_t     nodes;      // number of cons cells traced.

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  GCVerifier();
  ~GCVerifier();

  ///////////////////////////////////////////////////////////////////////////
  //  Statistics
  ///////////////////////////////////////////////////////////////////////////
  inline size_t number_of_nodes() const
  {
    return nodes;
  }
  inline Bool   is_okay()         const
  {
    return ok;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Name of object
  ///////////////////////////////////////////////////////////////////////////
  virtual const char * my_name() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Some methods for verification.
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool is_valid_pointer          (GCObject *, GC *);
  virtual Bool is_valid_interior_pointer (GCObject *, GC *);
  virtual Bool is_valid_structure        (GCObject *, GC *);

  inline  Bool is_valid_pointer          (GCObject * obj, GC& gc)
  {
    return is_valid_pointer (obj, &gc);
  }
  inline  Bool is_valid_interior_pointer (GCObject * obj, GC& gc)
  {
    return is_valid_interior_pointer (obj, &gc);
  }
  inline  Bool is_valid_structure        (GCObject * obj, GC& gc)
  {
    return is_valid_structure (obj, &gc);
  }
  inline  Bool is_valid_pointer          (GCObject * obj)
  {
    return is_valid_pointer (obj, GC::get_default_gc());
  }
  inline  Bool is_valid_interior_pointer (GCObject * obj)
  {
    return is_valid_interior_pointer (obj, GC::get_default_gc());
  }
  inline  Bool is_valid_structure        (GCObject * obj)
  {
    return is_valid_structure (obj, GC::get_default_gc());
  }

  ///////////////////////////////////////////////////////////////////////////
  //  This is the tracing method used by the protocol.
  ///////////////////////////////////////////////////////////////////////////
  virtual GCObject * trace (GCObject *);

  ///////////////////////////////////////////////////////////////////////////
  //  Redefine the following methods to report errors.  They are unused.
  //  Furthurmore, mark them private.
  ///////////////////////////////////////////////////////////////////////////
private:
  virtual void * m_alloc    (size_t);
  virtual void   free       (void *);
  virtual void   grow_heap  (size_t);
  virtual void   collect    (int);
  virtual size_t min_growth ();
  virtual Statistics statistics ();
};

#endif
