///////////////////////////////////////////////////////////////////////////////
//  A very simple hash table class.
///////////////////////////////////////////////////////////////////////////////

#ifndef hash_table_h
#define hash_table_h

#include <AD/generic/generic.h>

class HashTable
{
  HashTable(const HashTable&); // no copy constructor
  void operator = (const HashTable&); // no assignment
public:

  ////////////////////////////////////////////////////////////////////////////
  //  Type definitions.
  ////////////////////////////////////////////////////////////////////////////
  typedef const void * Key;
  typedef const void * Value;
  typedef unsigned int (*HashFunction)(Key);
  typedef Bool         (*Equality)(Key, Key);
  struct Entry
  {
    Key k;
    Value v;
    long hash_val;
  };

protected:

  ////////////////////////////////////////////////////////////////////////////
  //  Internals.
  ////////////////////////////////////////////////////////////////////////////
  HashFunction hash;         // hash function
  Equality     eq;           // equality function
  int          count;        // number of elements
  int          growth_limit; // expand when this limit is reached
  int          capacity;     // capacity of the table
  Entry *      table;        // the hash table itself.

public:

  ////////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////////
  HashTable(HashFunction, Equality, int = 32);
  ~HashTable();

  ////////////////////////////////////////////////////////////////////////////
  //  Operations.
  ////////////////////////////////////////////////////////////////////////////
  inline int    size()                 const
  {
    return count;
  }
  inline Bool   is_empty()             const
  {
    return count == 0;
  }
  inline Key    key  (const Entry * e) const
  {
    return e->k;
  }
  inline Value  value(const Entry * e) const
  {
    return e->v;
  }
  inline Value  operator [] (Key k)    const
  {
    return lookup(k)->v;
  }
  Bool          contains (Key key) const;
  Entry *       lookup   (Key key) const;
  void          clear    ();
  void          insert   (Key key, Value value);
  Entry * first ()        const;
  Entry * next  (Entry *) const;
  void          grow     (int);
private:
  const Entry * private_lookup (unsigned int h, Key key) const;
};

///////////////////////////////////////////////////////////////////////////////
//  Useful macros
///////////////////////////////////////////////////////////////////////////////

#define foreach_entry(i,h) \
   for (HashTable::Entry * i = (h).first(); i; i = (h).next(i))
#define key_of(T,h,i)   (T)(long)((h).key(i))
#define value_of(T,h,i) (T)(long)((h).value(i))

///////////////////////////////////////////////////////////////////////////////
//  Some common hashing and equality functions.
///////////////////////////////////////////////////////////////////////////////

unsigned int string_hash   (HashTable::Key);
Bool         string_equal  (HashTable::Key, HashTable::Key);
unsigned int integer_hash  (HashTable::Key);
Bool         integer_equal (HashTable::Key, HashTable::Key);

#endif
