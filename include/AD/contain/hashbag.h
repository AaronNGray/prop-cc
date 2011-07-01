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

#ifndef hash_table_based_bag_h
#define hash_table_based_bag_h

////////////////////////////////////////////////////////////////////////////
// Bag (or Multisets) derived from a hash table
////////////////////////////////////////////////////////////////////////////

#include <AD/contain/bag.h>  // Generic bags

template<class T, class H>
class HashBag : public Bag<T>
{
  H bag;

  //////////////////////////////////////////////////////////////////////
  // Inherit types
  //////////////////////////////////////////////////////////////////////

public:
  typedef Bag<T>         Super;
  typedef Super::Element Element;

  //////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  //////////////////////////////////////////////////////////////////////

  HashBag(int size = Collection_default_size) : bag(size)
  {}
  HashBag(const HashBag& b) : Bag<T>(b.size()), bag(b.bag)
  {}
  HashBag(const Bag<T>& b) : bag(b.size())
  {
    *this = b;
  }
  ~HashBag()
  {}

  //////////////////////////////////////////////////////////////////////
  // Assignment
  //////////////////////////////////////////////////////////////////////
  // void operator = (const Bag<T>& b); // inherit

  void operator = (const HashBag<T,H>& b)
  {
    *this = (Bag<T>&)b;
  }

  //////////////////////////////////////////////////////////////////////
  // Selectors:
  //    size()       return the number of elements within the bag.
  //    capacity()   return the current capacity.
  //    is_empty()   is the bag empty?
  //    contains()   does the bag contains the said element
  //    count()      returns the number of occurance of an element.
  //////////////////////////////////////////////////////////////////////
  // int  size() const;    // inherited
  // Bool is_empty() const; // inherited

  inline int  capacity() const
  {
    return bag.capacity();
  }

  inline Ix lookup(const T& e) const
  {
    return bag.lookup(e);
  }

  inline Bool contains(const T& e) const
  {
    return bag.contains(e);
  }

  inline int count(const T& e) const
  {
    Ix i;
    return (i = bag.lookup(e)) ? 0 : bag.value(i);
  }

  //////////////////////////////////////////////////////////////////////
  // In place multiset operations
  //////////////////////////////////////////////////////////////////////

  inline void clear()
  {
    bag.clear();
    tally = 0;
  }

  Ix insert( const T& e, int count);
  Bool remove( const T& e, int count);

  // Ix   insert(const T& e);      // inherited
  // Bool remove(const T& e);      // inherited
  // void Union      (const Bag<T>&); // inherited
  // void Difference (const Bag<T>&); // inherited

  //////////////////////////////////////////////////////////////////////
  //  Iteration
  //////////////////////////////////////////////////////////////////////

  inline Ix first()                 const
  {
    return bag.first();
  }

  inline Ix next(Ix i)              const
  {
    return bag.next(i);
  }

  inline const T& operator () (Ix i) const
  {
    return (T&)bag.key(i);
  }

  inline T& operator () (Ix i)
  {
    return (T&)bag.key(i);
  }

  inline int occurrence(Ix i)        const
  {
    return bag.value(i);
  }

  //////////////////////////////////////////////////////////////////////
  //  Class name
  //////////////////////////////////////////////////////////////////////

  const char* myName() const
  {
    return "HashBag";
  }
};

//////////////////////////////////////////////////////////////////////
// Insert a new element into the bag
//////////////////////////////////////////////////////////////////////

template <class T, class H>
Ix HashBag<T, H>::insert( const T& e, int n)
{
  Ix total = bag.lookup(e);
  if (total)
    bag.value(total) += n;
  else
    total = bag.insert(e,n);
  tally += n;
  return total;
}

//////////////////////////////////////////////////////////////////////
// Remove an element
//////////////////////////////////////////////////////////////////////

template <class T, class H>
Bool HashBag<T, H>::remove( const T& e, int n)
{
  Ix total = bag.lookup(e);
  if (total)
  {
    if (bag.value(total) > n)
    {
      bag.value(total) -= n;
      tally -= n;
    }
    else
    {
      tally -= bag.value(total);
      bag.remove(e);
    }
    return true;
  }
  else
    return false;
}

#endif
