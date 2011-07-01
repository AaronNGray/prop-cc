///////////////////////////////////////////////////////////////////////////////
//  A very simple hash table class.
///////////////////////////////////////////////////////////////////////////////

#ifndef functor_hash_table_h
#define functor_hash_table_h

#include "hashtab.h"
#include <AD/automata/treegram.h>

class FunctorTable : private HashTable
{
  FunctorTable(const FunctorTable&); // no copy constructor
  void operator = (const FunctorTable&); // no assignment

public:
  typedef TreeGrammar::Functor Functor;
  typedef HashTable::Entry Entry;

public:

  ////////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////////
  FunctorTable(HashFunction, Equality, int = 32);
  ~FunctorTable();

  ////////////////////////////////////////////////////////////////////////////
  //  Operations.
  ////////////////////////////////////////////////////////////////////////////
  inline Functor  value(const Entry * e) const
  {
    return (Functor)(long)(e->v);
  }
  Functor  operator [] (Key k) const;
  inline void     insert   (Key key, Functor value)
  {
    HashTable::insert(key,(Value)((long)value));
  }
  inline Bool  contains (Key k) const
  {
    return HashTable::contains(k);
  }
  inline Entry * lookup (Key k) const
  {
    return HashTable::lookup(k);
  }
  inline Key      key (Entry * e)
  {
    return e->k;
  }
  inline Entry *  first ()
  {
    return HashTable::first();
  }
  inline Entry *  next  (Entry * e)
  {
    return HashTable::next(e);
  }
  inline int size  () const
  {
    return HashTable::size();
  }
};

#endif
