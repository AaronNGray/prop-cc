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

#ifndef bag_h
#define bag_h

////////////////////////////////////////////////////////////////////////////
// Bag (or Multisets)
////////////////////////////////////////////////////////////////////////////
#include <AD/contain/col.h>

template<class T>
class Bag : public Collection<T>
{
protected:

  int tally;       // total number of elements

  //////////////////////////////////////////////////////////////////////
  //  Import types
  //////////////////////////////////////////////////////////////////////

public:
  typedef Collection<T>  Super;
  typedef Super::Element Element;

  //////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  //////////////////////////////////////////////////////////////////////

  Bag(int count = 0) : tally(count)
  {}        // make an empty bag
  ~Bag()
  {}                                    // destroy a bag

  //////////////////////////////////////////////////////////////////////
  // Assignment
  //////////////////////////////////////////////////////////////////////
  // virtual void operator = (const Collection<T>& b); // inherited

  //////////////////////////////////////////////////////////////////////
  // Selectors:
  //    size()       return the number of elements within the bag.
  //    capacity()   return the current capacity.
  //    is_empty()   is the bag empty?
  //    contains()   does the bag contains the said element
  //    count()      returns the number of occurance of an element.
  //////////////////////////////////////////////////////////////////////

  inline virtual int  size()     const
  {
    return tally;
  }
  inline virtual Bool is_empty()  const
  {
    return tally == 0;
  }
  inline virtual Bool is_full()   const
  {
    return tally == capacity();
  }
  // virtual int capacity() const;  // inherited
  // virtual Bool contains(const T& e) const; // inherited
  virtual int count(const T& e) const = 0;

  //////////////////////////////////////////////////////////////////////
  // In place multiset operations
  //////////////////////////////////////////////////////////////////////
  // virtual void clear();            // inherited

  inline virtual Ix   insert(const T& e)
  {
    return insert(e,1);
  }
  inline virtual Bool remove
    (const T& e)
  {
    return remove
             (e,1);
  }
  virtual Ix   insert(const T& e, int count) = 0;
  virtual Bool remove
    (const T& e, int count) = 0;
  Bag& Union      (const Bag&);
  Bag& Difference (const Bag&);

  //////////////////////////////////////////////////////////////////////
  //  Iteration
  //////////////////////////////////////////////////////////////////////
  // virtual Ix  first();              // inherited
  // virtual Ix  next(Ix i);           // inherited
  // virtual T&  operator () (Ix i);   // inherited
  // virtual const T&  operator () (Ix i) const;   // inherited

  virtual int occurrence(Ix i) const = 0;
};

//////////////////////////////////////////////////////////////////////
// In place bag union
//////////////////////////////////////////////////////////////////////

template <class T>
Bag<T>& Bag<T>::Union (const Bag<T>& b)
{
  for (Ix i = b.first(); i; i = b.next(i))
    insert(b(i), b.occurrence(i));
  return *this;
}

//////////////////////////////////////////////////////////////////////
// In place bag difference
//////////////////////////////////////////////////////////////////////

template <class T>
Bag<T>& Bag<T>::Difference (const Bag<T>& b)
{
  for (Ix i = b.first(); i; i = b.next(i))
    remove
      (b(i), b.occurrence(i));
  return *this;
}

#endif
