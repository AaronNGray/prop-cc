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

#ifndef hash_table_based_map_h
#define hash_table_based_map_h

///////////////////////////////////////////////////////////////////////////
//  Class HashMap<K,V> is an associative table from type K to type V
//  implemented as a hash table.
///////////////////////////////////////////////////////////////////////////

#include <string>
#include <AD/contain/map.h>

//////////////////////////////////////////////////////////////////////////////
//  Template for class HashMap.
//  Notice that for each type of keys a hashing function and a key comparison
//  function must be supplied.
//////////////////////////////////////////////////////////////////////////////

template<class K, class V, class HashTable>
class HashMap : public Map<K,V>
{

  HashTable table;

  ///////////////////////////////////////////////////////////////
  //  Inherit types
  ///////////////////////////////////////////////////////////////

public:
  typedef Map<K,V>       Super;
  typedef typename Map<K,V>::Key     Key;
  typedef typename Map<K,V>::Value   Value;
  typedef typename Map<K,V>::Element Element;

  ///////////////////////////////////////////////////////////////
  //  Creator and destructors
  ///////////////////////////////////////////////////////////////

  HashMap(int size = Collection_default_size, double maxLoad = 1000.0)
      : table(size,maxLoad)
  {}
  HashMap(const V& v, int size = Collection_default_size, double maxLoad = 1000.0)
      : Map<K,V>(v), table(size,maxLoad)
  {}
  ~HashMap()
  {}

  ///////////////////////////////////////////////////////////////
  //  Assignment and clear map
  ///////////////////////////////////////////////////////////////
  // void operator = (const Map<K,V>& m); // inherited

  ///////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////

  inline int size()               const
  {
    return table.size();
  }

  inline int capacity()           const
  {
    return table.capacity();
  }

  inline Bool  is_empty()           const
  {
    return table.is_empty();
  }

  inline Bool is_full()           const
  {
    return table.is_full();
  }

  inline Bool  contains(const K& k) const
  {
    return table.contains(k);
  }
  // V& defValue(); // inherited

  /////////////////////////////////////////////////////////////////////////
  // Lookup operations
  /////////////////////////////////////////////////////////////////////////
  // V& operator [] (const K& key); // inherited

  inline Ix lookup( const K& k) const
  {
    return table.lookup(k);
  }

  /////////////////////////////////////////////////////////////////////////
  // Insertion and deletion
  /////////////////////////////////////////////////////////////////////////

  inline void clear()
  {
    table.clear();
  }
  // virtual Ix insert(const K&);      // inherited
  // virtual Bool del (Ix i);          // inherited

  inline Ix   insert (const K& k, const V& v)
  {
    return table.insert(k,v);
  }

  inline Bool remove( const K& k)
  {
    return table.remove(k);
  }

  /////////////////////////////////////////////////////////////////////////
  // Iteration
  /////////////////////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return table.first();
  }

  inline Ix next(Ix i) const
  {
    return table.next(i);
  }

  inline const K& key(Ix i) const
  {
    return table.key(i);
  }

  inline const V& value(Ix i) const
  {
    return table.value(i);
  }

  inline V& value(Ix i)
  {
    return table.value(i);
  }

  /////////////////////////////////////////////////////////////////////////
  // Class name
  /////////////////////////////////////////////////////////////////////////

  const char * myName() const
  {
    return "HashMap";
  }
};

#endif
