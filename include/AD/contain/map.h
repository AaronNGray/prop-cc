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

#ifndef map_h
#define map_h

///////////////////////////////////////////////////////////////////////////
//  Class Map<K,V> is an associative table from type K to type V.
//  This is an abstract class.
///////////////////////////////////////////////////////////////////////////

#include <AD/contain/col.h>   // collection base class

/////////////////////////////////////////////////////////////////////////////
//  Template for class Map.
/////////////////////////////////////////////////////////////////////////////

template<class K, class V>
class Map : public Collection< K >
{
  V defaultValue;  // default element value;

public:
  ///////////////////////////////////////////////////////////////
  //  Inherit types
  ///////////////////////////////////////////////////////////////

  typedef K                            Key;
  typedef V                            Value;
  typedef K                            Element;
  typedef Collection<Element>          Super;

  ///////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////

  Map()
  {}
  Map(const V& v) : defaultValue(v)
  {}
  ~Map()
  {}

  ///////////////////////////////////////////////////////////////
  //  Assignment and clear map
  ///////////////////////////////////////////////////////////////
  // virtual void operator = (const Collection<Element>& m); // inherit

  virtual void operator = (const Map<K,V>& m);

  ///////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////
  // virtual int  size()             const; // inherited
  // virtual int  capacity()         const; // inherited
  // virtual Bool is_empty()          const; // inherited
  // virtual Bool is_full ()          const; // inherited
  // virtual Bool contains(const K&) const; // inherited

  inline V& def_value()
  {
    return defaultValue;
  }

  inline const V& def_value() const
  {
    return defaultValue;
  }

  /////////////////////////////////////////////////////////////////////////
  // Lookup operations
  /////////////////////////////////////////////////////////////////////////

  inline V& operator [] (const K& key) // lookup; insert default if not found
  {
    Ix i;
    return value ((i = lookup(key)) ? i : insert(key,defaultValue));
  }

  inline const V& operator [] (const K& key) const
  {
    return value(lookup(key));
  }
  // virtual Ix lookup (const K& k) const;   // inherited

  /////////////////////////////////////////////////////////////////////////
  // Mutators
  /////////////////////////////////////////////////////////////////////////
  // virtual void clear  ();                   // inherited
  // virtual Bool del (Ix i);                  // inherited

  inline virtual Bool remove(const K&)  = 0;
  virtual Ix insert (const K&, const V&) = 0;
  inline virtual Ix insert (const Key& k)
  {
    return insert(k,defaultValue);
  }

  /////////////////////////////////////////////////////////////////////////
  // Iteration
  /////////////////////////////////////////////////////////////////////////
  // virtual Ix       first()   const; // inherited
  // virtual Ix       next(Ix)  const; // inherited
  virtual const K& key(Ix)   const = 0;
  virtual const V& value(Ix) const = 0;
  virtual       V& value(Ix)       = 0;
  inline virtual const Element& operator () (Ix i) const
  {
    return key(i);
  }

  // hack to get SUN C++ working
  inline virtual Element& operator () (Ix i)
  { /* should_not_implement("Map::operator ()"); */
    return *(Element*)(&key(i));
  }
};

/////////////////////////////////////////////////////////////////////////
// Assign a map to another
/////////////////////////////////////////////////////////////////////////

template <class K, class V>
void Map<K,V>::operator = (const Map<K,V>& m)
{
  this->clear();
  for (Ix i = m.first(); i; i = m.next(i))
    insert(m.key(i), m.value(i));
}

#endif
