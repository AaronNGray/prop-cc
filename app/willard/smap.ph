#ifndef smap_h
#define smap_h

#include <AD/hash/lhash.h>

//
//  Single valued map
//
template <class K, class V>
class SMap : public LHashTable<K, V>
{  
};

template <class A, class B>
   inline int hash (const .[A,B]& x) { return hash(x.#1) + hash(x.#2); }

template <class A, class B>
   inline int equal (const .[A,B]& x, const .[A,B]& y) 
      { return equal(x.#1,y.#1) && equal(x.#2,y.#2); }

#endif
