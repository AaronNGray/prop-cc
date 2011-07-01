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

#ifndef basic_collection_h
#define basic_collection_h

///////////////////////////////////////////////////////////////////////////
//  Collection is the base class at the root of the collection hierarchy.
//  Its purpose is to factor out some of the common method and implement
//  them once.
///////////////////////////////////////////////////////////////////////////
#include <AD/generic/generic.h>

////////////////////////////////////////////////////////////////////////////
//  Collection class
////////////////////////////////////////////////////////////////////////////
class BasicCollection
{
public:

  /////////////////////////////////////////////////////
  // Parameters used by all subclasses
  /////////////////////////////////////////////////////
  // const int default_size   = 32;
  // const int default_growth = 64;

#define Collection_default_size   32
#define Collection_default_growth 64

  /////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////

  BasicCollection()
  {}  // do nothing
  virtual ~BasicCollection()
  {}  // do nothing

  ////////////////////////////////////////////////////////
  //  Selectors:
  //     size()     --- number of elements in collection
  //     capacity() --- current capacity(may change)
  //     is_empty()  --- is it empty??
  //     is_full()   --- is it full??
  //     contains() --- does it contain a specific element
  /////////////////////////////////////////////////////////

  virtual int  size()     const;
  virtual int  capacity() const = 0;
  virtual Bool is_empty() const
  {
    return first() == 0;
  }
  virtual Bool is_full()  const
  {
    return capacity() == size();
  }

  ////////////////////////////////////////////////////////
  //  Mutators:
  //     empties the collection
  ////////////////////////////////////////////////////////

  virtual void clear() = 0; // empties the collection

  ////////////////////////////////////////////////////////
  //  Iteration:
  //     first() --- returns the index of the first
  //                 element(notice the position maybe
  //                 arbitrary).
  //     next()  --- get the next element.
  //  These two functions will return 0 if we have
  //  exhausted the elements.
  ////////////////////////////////////////////////////////

  virtual Ix first()  const = 0;
  virtual Ix next(Ix) const = 0;

  ////////////////////////////////////////////////////////
  // Each concrete subclass should define this method
  ////////////////////////////////////////////////////////

  virtual const char * myName() const = 0;

  /////////////////////////////////////////////////////
  //  Miscellaneous
  /////////////////////////////////////////////////////

protected:
  void should_not_implement(const char method_name[]) const;
};

#endif
