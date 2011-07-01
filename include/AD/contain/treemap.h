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

#ifndef tree_based_map_h
#define tree_based_map_h

///////////////////////////////////////////////////////////////////////////
//  Class TreeMap<K,V> is an associative table from type K to type V
//  implemented as a search tree.
///////////////////////////////////////////////////////////////////////////

#include <AD/contain/map.h>

//////////////////////////////////////////////////////////////////////////////
//  Template for class TreeMap.
//  Notice that for each type of keys a key comparison function
//  must be supplied.
//////////////////////////////////////////////////////////////////////////////

template<class K, class V, class Tree>
class TreeMap : public Map<K,V>
{
  Tree tree;

  ///////////////////////////////////////////////////////////////
  //  Inherit types
  ///////////////////////////////////////////////////////////////

public:
  typedef Map<K,V>       Super;
  typedef Super::Key     Key;
  typedef Super::Value   Value;
  typedef Super::Element Element;

  ///////////////////////////////////////////////////////////////
  //  Creator and destructors
  ///////////////////////////////////////////////////////////////
  TreeMap()
  {}
  TreeMap(const TreeMap& t)
  {
    tree = t;
  }
  TreeMap(const Map<K,V>& m)
  {
    *this = m;
  }
  ~TreeMap()
  {}

  ///////////////////////////////////////////////////////////////
  //  Assignment and clear map
  ///////////////////////////////////////////////////////////////
  // void operator = (const Map<K,V>& m); // inherited

  ///////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////
  inline int size() const
  {
    return tree.size();
  }

  inline int capacity() const
  {
    return tree.capacity();
  }

  inline Bool is_empty() const
  {
    return tree.is_empty();
  }

  inline Bool is_full() const
  {
    return tree.is_full();
  }

  inline Bool contains(const K& k) const
  {
    return tree.contains(k);
  }
  // V& defValue(); // inherited

  /////////////////////////////////////////////////////////////////////////
  // Lookup operations
  /////////////////////////////////////////////////////////////////////////
  // V& operator [] (const K& key); // inherited

  inline Ix lookup (const K& k) const
  {
    return tree.lookup(k);
  }

  /////////////////////////////////////////////////////////////////////////
  // Insertion and deletion
  /////////////////////////////////////////////////////////////////////////

  inline void clear()
  {
    tree.clear();
  }

  // virtual Ix insert(const K&);      // inherited

  inline Ix   insert (const K& k, const V& v)
  {
    return tree.insert(k,v);
  }

  inline Bool remove(const K& k)
  {
    return tree.remove(k);
  }

  /////////////////////////////////////////////////////////////////////////
  // Iteration
  /////////////////////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return tree.first();
  }

  inline Ix next(Ix i) const
  {
    return tree.next(i);
  }

  inline const K& key(Ix i) const
  {
    return tree.key(i);
  }

  inline const V& value(Ix i) const
  {
    return tree.value(i);
  }

  inline V&       value(Ix i)
  {
    return tree.value(i);
  }

  /////////////////////////////////////////////////////////////////////////
  // Class name
  /////////////////////////////////////////////////////////////////////////

  const char * myName() const
  {
    return "TreeMap";
  }
};

#endif
