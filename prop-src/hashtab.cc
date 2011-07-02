///////////////////////////////////////////////////////////////////////////////
//  Hash Tables
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <AD/generic/ordering.h>
#include "hashtab.h"

///////////////////////////////////////////////////////////////////////////////
//  Import some type definitions
///////////////////////////////////////////////////////////////////////////////

typedef HashTable::Key          Key;
typedef HashTable::Value        Value;
typedef HashTable::Entry        Entry;
typedef HashTable::HashFunction HashFunction;
typedef HashTable::Equality     Equality;

///////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
///////////////////////////////////////////////////////////////////////////////

HashTable:: HashTable(HashFunction h, Equality e, int n)
        : hash(h), eq(e), count(0), table(0), capacity(0), growth_limit(0)
{ grow(n); }

HashTable::~HashTable() { delete [] table; }

///////////////////////////////////////////////////////////////////////////////
//  Check if a key is in the table.
///////////////////////////////////////////////////////////////////////////////

Bool HashTable::contains (Key key) const
{
  return lookup(key) != 0;
}

///////////////////////////////////////////////////////////////////////////////
//  Empties the table.
///////////////////////////////////////////////////////////////////////////////

void HashTable::clear()
{
  for (Entry * p = table, * q = p + capacity; p < q; p++)
    p->hash_val = -1;
  count = 0;
}

///////////////////////////////////////////////////////////////////////////////
//  Increase the size of a table.
///////////////////////////////////////////////////////////////////////////////

void HashTable::grow( int n)
{
  if (n < capacity)
    return;
  Entry * new_table = new Entry [n];
  int i;
  for (i = 0; i < n; i++) new_table[i].hash_val = -1;
  if (count > 0) {
    for (i = 0; i < capacity; i++)
    {
      if (table[i].hash_val >= 0)
      {
        unsigned int j, h = (*hash)(table[i].k) % n;
        for (j = h;;)
        {
          if (new_table[j].hash_val < 0)
          {
            new_table[j].k        = table[i].k;
            new_table[j].v        = table[i].v;
            new_table[j].hash_val = h;
            break;
          }
          if (++j >= n) j = 0;
        }
      }
    }
  }
  if (table) delete [] table;
  table = new_table;
  capacity = n;
  growth_limit = n * 6 / 10;
}

///////////////////////////////////////////////////////////////////////////////
//  Lookup a key from the table.  Use linear probing.  I'm lazy.
///////////////////////////////////////////////////////////////////////////////

const Entry * HashTable::private_lookup( unsigned int h, Key k) const
{
  register unsigned int i = h;

  for (;;)
      {  if (table[i].hash_val < 0 ||
              table[i].hash_val == h && (*eq)(table[i].k,k))
          return table + i;
      if (++i >= capacity) i = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////
//  Lookup an entry from a key
///////////////////////////////////////////////////////////////////////////////

Entry * HashTable::lookup( Key k) const
{
  unsigned int h = (*hash)(k) % capacity;
  Entry * e = (Entry *)private_lookup(h,k);
  return e->hash_val >= 0 ? e : 0;
}

///////////////////////////////////////////////////////////////////////////////
//  Insert a new element into the table.
///////////////////////////////////////////////////////////////////////////////

void HashTable::insert( Key k, Value v)
{
  if (count >= growth_limit)
    grow(capacity * 7 / 4 + 32);
  unsigned int h = (*hash)(k) % capacity;
  Entry * e = (Entry*)private_lookup(h,k);
  if (e->hash_val >= 0)
    e->v = v;
  else
    { e->k = k; e->v = v; e->hash_val = h; count++; }
}

///////////////////////////////////////////////////////////////////////////////
//  Returns the first element of the table.
///////////////////////////////////////////////////////////////////////////////

Entry * HashTable::first() const
{
  if (count == 0)
    return 0;
  register const Entry * p, * q;
  for (p = table, q = table + capacity; p < q; p++)
    if (p->hash_val >= 0) return (Entry*)p;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//  Returns the next element from the table.
///////////////////////////////////////////////////////////////////////////////

Entry * HashTable::next( Entry * p) const
{
  register const Entry * q;
  for (q = table + capacity, p++; p < q; p++)
    if (p->hash_val >= 0)
      return (Entry*)p;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//  Hashing and equality functions
///////////////////////////////////////////////////////////////////////////////

unsigned int string_hash( Key k)
{
  return hash((const char *)k);
}

Bool string_equal( Key a, Key b)
{
  return strcmp((const char *)a, (const char *)b) == 0;
}

unsigned int integer_hash( Key k)
{
  return (unsigned int)k;
}

Bool integer_equal( Key a, Key b)
{
  return a == b;
}
