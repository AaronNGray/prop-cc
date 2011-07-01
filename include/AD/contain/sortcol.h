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

#ifndef sorted_collection_h
#define sorted_collection_h

#include <AD/contain/col.h>

template <class T>
class SortedCollection : public Collection<T>
{
public:
  /////////////////////////////////////////////////////////////////
  //  Inherit types
  /////////////////////////////////////////////////////////////////

  typedef Collection<T>  Super;
  typedef Super::Element Element;

  /////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////////////////

  SortedCollection()
  {}
  SortedCollection(const Collection<T>& C)
  {
    *this = C;
  }
  SortedCollection(const SortedCollection<T>& C)
  {
    *this = C;
  }
  ~SortedCollection()
  {}

  /////////////////////////////////////////////////////////////////
  //  Selectors
  /////////////////////////////////////////////////////////////////
  // virtual int  size()             const; // inherited
  // virtual int  capacity()         const; // inherited
  // virtual Bool is_empty()         const; // inherited
  // virtual Bool is_full()          const; // inherited
  // virtual Bool contains(const T&) const; // inherited
  // virtual Ix   lookup(const T&)   const; // inherited

  /////////////////////////////////////////////////////////////////
  //  Mutators
  /////////////////////////////////////////////////////////////////
  // virtual void clear();           // inherited
  // virtual Ix   insert(const T&);  // inherited
  // virtual Bool remove(const T&);  // inherited

  /////////////////////////////////////////////////////////////////
  //  Iteration
  /////////////////////////////////////////////////////////////////
  // virtual Ix       first()          const;  // inherited
  // virtual Ix       next(Ix)         const;  // inherited
  // virtual const T& operator () (Ix) const;  // inherited
  // virtual       T& operator () (Ix);        // inherited
};

#endif
