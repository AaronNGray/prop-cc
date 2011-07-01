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

#ifndef generic_collection_h
#define generic_collection_h

///////////////////////////////////////////////////////////////////////////
//  Collection
///////////////////////////////////////////////////////////////////////////

#include <AD/contain/basiccol.h>

////////////////////////////////////////////////////////////////////////////
//  Collection class
////////////////////////////////////////////////////////////////////////////

template <class T>
class Collection : public BasicCollection
{
public:
  /////////////////////////////////////////////////////
  //  Type definitions
  /////////////////////////////////////////////////////

  typedef BasicCollection Super;
  typedef T               Element;

  /////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////

  Collection()
  {}
  virtual ~Collection()
  {}

  ////////////////////////////////////////////////////////
  //  Assignment and merging
  ////////////////////////////////////////////////////////

  virtual void operator = (const Collection&);

  ////////////////////////////////////////////////////////
  //  Selectors:
  //     size()     --- number of elements in collection
  //     capacity() --- current capacity(may change)
  //     is_empty() --- is it empty??
  //     is_full()  --- is it full??
  //     contains() --- does it contain a specific element
  /////////////////////////////////////////////////////////
  // virtual int  size()     const; // inherited
  // virtual int  capacity() const; // inherited
  // virtual Bool is_empty() const; // inherited
  // virtual Bool is_full()  const; // inherited

  virtual Ix   lookup(const T&)     const;
  virtual Bool contains(const T& e) const
  {
    return lookup(e) != 0;
  }

  ////////////////////////////////////////////////////////
  //  Mutators:
  //     clear()  --- empties the collection
  //     insert() --- insert a new element and return its
  //                  index within the collection.
  //     remove() --- remove the element; returns true
  //                  if the element was within the
  //                  collection.
  //     del()    --- removes the element at the specified
  //                  index.
  //  Notice that the definitions for remove() and del()
  //  are phrased in terms of one another.  To be useful,
  //  a derived class *must* redefine at least one of
  //  these methods.
  ////////////////////////////////////////////////////////

  virtual void clear();              // empties the collection
  virtual Ix   insert(const T&) = 0; // insert an element
  virtual Bool remove
    (const T&);     // removes an element
  virtual Bool del(Ix i)             // removes an element at index
  {
    if (i)
      return remove
               ((*this)(i));
    else
      return false;
  }

  ////////////////////////////////////////////////////////
  //  Iteration:
  //     first() --- returns the index of the first
  //                 element(notice the position maybe
  //                 arbitrary).
  //     next()  --- get the next element.
  //  These two functions will return 0 if we have
  //  exhausted the elements.
  ////////////////////////////////////////////////////////
  //      Ix first()  const; // inherited
  //      Ix next(Ix) const; // inherited

  virtual const T& operator () (Ix) const = 0;
  virtual       T& operator () (Ix)       = 0;
};

////////////////////////////////////////////////////////////////////////////
//  Template methods
////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//  Default implementation of assignment is implemented
//  by iterating over the elements of a collection.
//////////////////////////////////////////////////////////////////////////

template <class T>
void Collection<T>::operator = (const Collection<T>& C)
{
  clear();   // empties self first
  // then insert elements from C
  for (Ix i = C.first(); i; i = C.next(i))
    insert(C(i));
}

//////////////////////////////////////////////////////////////////////////
// Default implementation of remove() lookups the element in
// question and removes it using del()
//////////////////////////////////////////////////////////////////////////

template <class T>
Bool Collection<T>::remove
  (const T& e)
{
  Ix i;
  if ((i = lookup(e)))
  {
    del(i);
    return true;
  }
  else
    return false;
}

//////////////////////////////////////////////////////////////////////////
// Default implementation of clear() iterately through the collection
// and empties the elements
//////////////////////////////////////////////////////////////////////////

template <class T>
void Collection<T>::clear()
{
  Ix i, j;
  for (i = first(); i; i = j)
  {
    j = next(i);
    del(i);
  }
}

//////////////////////////////////////////////////////////////////////////
// Default lookup method for a collection uses a linear search.
//////////////////////////////////////////////////////////////////////////

template <class T>
Ix Collection<T>::lookup(const T& e) const
{
  for (Ix i = first(); i; i = next(i))
    if (equal(e,(*this)(i)))
      return i;
  return 0;
}

#endif
