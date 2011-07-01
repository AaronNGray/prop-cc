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

#ifndef hash_table_with_ordered_hashing_h
#define hash_table_with_ordered_hashing_h

////////////////////////////////////////////////////////////////////////////
// Class OHashTable implements a hash table using an ordered hashing
// scheme\cite{Algorithms}.  Ordered hashing simulates the effect
// of insertion in increasing order by reordering keys in a probe sequence
// if it is found that they are out of order.   It helps unsuccessful
// searches to terminate faster by eliminating unnecessary probes
// once the next key proves to be smaller that the current one.
////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <AD/generic/ordering.h>

////////////////////////////////////////////////////////////////////////////
//  Class |OHashTable| is parameterized with the class of the
//  key and the class of the value.  Furthermore, the functions
//      unsigned int hash(const K&);          and
//      int      compare(const K&, const K&)
//  must be defined by the client that uses this template.
////////////////////////////////////////////////////////////////////////////

template <class K, class V>
class OHashTable
{

  K *     keys;           // the array of keys
  V *     values;         // the array of values
  char *  status;         // status of cell
  int     table_size;     // size of the array
  int     elem_count;     // number of elements
  double  max_load_ratio; // maximum load ratio (> 0 && < 1)
  double  growth_ratio;   // amount to expand when resizing
  int     max_load;       // maximum elements before resizing

public:
  ////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////
  OHashTable(int    initial_size   = 32,
             double max_load_ratio = 0.0,
             double growth_ratio   = 2.0);
  ~OHashTable();

  ////////////////////////////////////////////////////////////////////
  //  Assignment
  ////////////////////////////////////////////////////////////////////
  void operator = (const OHashTable&);

  ////////////////////////////////////////////////////////////////////
  //  Selectors
  ////////////////////////////////////////////////////////////////////
  inline int  capacity() const
  {
    return table_size;
  }   // current capacity
  inline int  size()     const
  {
    return elem_count;
  }   // number of elements
  inline Bool is_empty() const
  {
    return elem_count == 0;
  }
  inline Bool is_full()  const
  {
    return elem_count == table_size;
  }
  inline Bool contains(const K& k) const
  {
    return lookup(k) != 0;
  }
  inline const V& operator [] (const K& k) const
  {
    return value(lookup(k));
  }
  inline       V& operator [] (const K& k)
  {
    return value(lookup(k));
  }

  ////////////////////////////////////////////////////////////////////
  // Insertion and deletion.
  ////////////////////////////////////////////////////////////////////
  void clear();                      // clears out the hash table
  Ix   lookup(const K&) const;       // lookup entry by key
  Ix   insert(const K, const V);     // insert a new entry
  Bool remove
    (const K&);             // remove an old entry

  ////////////////////////////////////////////////////////////////////
  // Iteration:
  //    first()  start the iteration
  //    next()   get index to the next element; or 0 if none
  //    key()    get the key on index
  //    value()  get the value on index
  // Implementation note: Ix's are represented internally as 1-based
  // array index.
  ////////////////////////////////////////////////////////////////////
  inline Ix first()           const
  {
    return find_next(0);
  }
  inline Ix next(Ix i)        const
  {
    return find_next((int)i);
  }
  inline const K& key(Ix i)   const
  {
    return keys[(int)i-1];
  }
  inline const V& value(Ix i) const
  {
    return values[(int)i-1];
  }
  inline       V& value(Ix i)
  {
    return values[(int)i-1];
  }

  ////////////////////////////////////////////////////////////////////
  // Resizing the table
  ////////////////////////////////////////////////////////////////////
  void resize(int new_size = 0);

private:
  ////////////////////////////////////////////////////////////////////
  //  Addition implementation methods
  ////////////////////////////////////////////////////////////////////
  inline Ix find_next(int i) const;  // locate the next used entry
};

//////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//  Locate the next used cell; called by the iterator functions
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
inline Ix OHashTable<K,V>::find_next(register int i) const
{
  while (i < table_size)
    if (status[i++] == Cell_used)
      return (Ix)i;
  return (Ix)0;
}

//////////////////////////////////////////////////////////////////////////
//  Create a new table.
//  Implementation note: each end of each chain of the buckets are
//  linked to the next.  This makes it possible to find the next entry
//  during iteration quickly.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
OHashTable<K,V>::OHashTable
(int size, double maximum_load_ratio, double growth)
    : keys(new K [size]), values(new V [size]),
    status(new char [size]),
    table_size(size)
{
  clear();
  if (maximum_load_ratio >= 0.9 || maximum_load_ratio <= 0.1)
    max_load_ratio = .7;
  else
    max_load_ratio = maximum_load_ratio;
  max_load = (int)(max_load_ratio * size);
  if (max_load >= size)
    max_load = size - 1;
  if (growth <= 1.2 || growth >= 5.0)
    growth_ratio = 2.0;
  else
    growth_ratio = growth;
}

//////////////////////////////////////////////////////////////////////////
//  Destroy a table
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
OHashTable<K,V>::~OHashTable()
{
  delete [] keys;
  delete [] values;
  delete [] status;
}

//////////////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void OHashTable<K,V>::operator = (const OHashTable<K,V>& t)
{
  if (this != &t)
  {
    delete [] keys;
    delete [] values;
    delete [] status;
    elem_count = t.elem_count;
    table_size = t.table_size;
    keys   = new K    [table_size];
    values = new V    [table_size];
    status = new char [table_size];
    for (int i = 0; i < table_size; i++)
    {
      if ((status[i] = t.status[i]) == Cell_used)
      {
        keys[i] = t.keys[i];
        values[i] = t.values[i];
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
//  Clear a table.
//  We'll traverse thru all the buckets and delete each one iteratively.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void OHashTable<K,V>::clear()
{
  memset(status,0,table_size);
  elem_count = 0;
}

//////////////////////////////////////////////////////////////////////////
//  Lookup an entry by key; if the entry is not found, return (Ix)0.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
Ix OHashTable<K,V>::lookup(const K& key) const
{
  unsigned int h    = hash(key);
  unsigned int i    = h % table_size;
  unsigned int inc  = 0;  // increment
  unsigned int last;

  ////////////////////////////////////////////////////////////////////
  // Since the size of the hash table is not necessary a prime,
  // care must be taken so that each probing sequence covers the
  // entire table.  The simple strategy of computing new location as
  //        i = (i + inc) % table_size
  // cannot be used.
  ////////////////////////////////////////////////////////////////////
  for (;;)
  {
    switch (status[i])
    {
    case Cell_unused:
      return (Ix)0;
    case Cell_used:
      int r = compare(keys[i],key);
      if (r == 0)
        return (Ix)(i+1);
      if (r >  0)
        return (Ix)0;
    }
    ////////////////////////////////////////////////////////////////////
    // Compute increment only if the initial probe fails.
    ////////////////////////////////////////////////////////////////////
    if (inc == 0)
    {
      // recycle those higher order bits of hash value
      inc = ( h / table_size ) % table_size;
      if (inc == 0)
        inc = 1; // use linear probing if all else fails
      last = i;
    }
    i += inc;
    if (i >= table_size)
      i -= table_size;
    if (i == last)
    {
      last = ++i;
    }
  }
}

//////////////////////////////////////////////////////////////////////////
//  Insert a new entry; there are two different cases of behavior:
//  (1) If the key doesn't already exists, new key/value pair will be
//      inserted into the table.
//  (2) If the key already exists, then the old value will be overwritten
//      by the new value.
//  Also, if the number of elements have exceeded the maximum load,
//  the table will be automatically resized.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
Ix OHashTable<K,V>::insert(const K key, const V value)
{  /////////////////////////////////////////////////////////////////////
  // Make sure we have at least one unused cell.
  /////////////////////////////////////////////////////////////////////
  if (elem_count >= max_load)
    resize();
  unsigned int h   = hash(key);
  unsigned int i   = h % table_size;
  unsigned int inc = 0;
  unsigned int last;
  int count;

  /////////////////////////////////////////////////////////////////////
  //  Loop until one of the following:
  //    (1) The key is found; in which case the value is updated.
  //    (2) An unused cell is found, or a deleted cell is found
  //        and we have looped over all the entries once around.
  /////////////////////////////////////////////////////////////////////
  for (count = table_size ;; count--)
  {
    switch (status[i])
    {
    case Cell_deleted:
      if (count > 0)
        break;
    case Cell_unused:
      elem_count++;
      keys[i] = key;
      values[i] = value;
      status[i] = Cell_used;
      return (Ix)(i+1);
    case Cell_used:
      int r = compare(keys[i],key);
      if (r == 0)
      {
        values[i] = value;
        return (Ix)(i+1);
      }
      if (r > 0)
      { // exchange entries and continue
        K k = key;
        key = keys[i];
        keys[i] = k;
        V v = value;
        value = values[i];
        values[i] = v;
        h = hash(key);
        inc = 0;
      }
    }
    if (inc == 0)
    {
      // recycle those higher order bits of hash value
      inc = ( h / table_size ) % table_size;
      if (inc == 0)
        inc = 1; // use linear probing if all else fails
      last = i;
    }
    i += inc;
    if (i >= table_size)
      i -= table_size;
    if (i == last)
    {
      last = ++i;
    }
  }
}

//////////////////////////////////////////////////////////////////////////
//  Resizing the hash table.  All entries are completed rehashed.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void OHashTable<K,V>::resize(int new_size)
{
  if (new_size <= elem_count)
    new_size = (int)(table_size * growth_ratio);

  //////////////////////////////////////////////////////////////////
  // Just making sure the new size makes sense.
  //////////////////////////////////////////////////////////////////
  if (new_size <= table_size)
    new_size = table_size + 32;
  char * new_status = new char [ new_size ];
  K    * new_keys   = new K    [ new_size ];
  V    * new_values = new V    [ new_size ];
  memset(new_status,0,new_size);

  //////////////////////////////////////////////////////////////////
  //  Rehash all used cells one by one.  Notice that since all keys
  //  are unique, we don't have to do any comparison.
  //////////////////////////////////////////////////////////////////
  for (int i = 0; i < table_size; i++)
  {
    if (status[i] == Cell_used)
    {
      unsigned int h = hash(keys[i]);
      unsigned int j = h % new_size;
      unsigned int inc = 0, last;
      for (;;)
      {
        if (new_status[j] != Cell_used)
        {
          new_keys[j] = keys[i];
          new_values[j] = values[i];
          new_status[j] = Cell_used;
          break;
        }
        int r = compare(new_keys[j],keys[i]);
        if (r > 0)
        { // exchange entries and continue
          K k = new_keys[j];
          new_keys[j] = keys[i];
          keys[i] = k;
          V v = new_values[j];
          new_values[j] = values[i];
          values[i] = v;
          h = hash(k);
          inc = 0;
        }
        if (inc == 0)
        {
          inc = ( h / new_size ) % new_size;
          if (inc == 0)
            inc = 1;
          last = j;
        }
        j += inc;
        if (j >= new_size)
          j -= new_size;
        if (j == last)
        {
          last = ++j;
        }
      }
    }
  }
  delete [] keys;
  delete [] values;
  delete [] status;
  keys = new_keys;
  values = new_values;
  status = new_status;
  table_size = new_size;
  max_load = (int)(max_load_ratio * table_size);
}

//////////////////////////////////////////////////////////////////////////
//  Remove an entry from the table; there are two different cases:
//  (1) If the key exists within the table, the key/value pair will be
//      removed; otherwise
//  (2) The table will be unaltered.
//      If the removal operation successfully deletes the entry,
//      we'll also return true to the client.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
Bool OHashTable<K,V>::remove
  (const K& key)
{
  Ix i;
  ///////////////////////////////////////////////////////////////////
  // We'll just call lookup() to do the dirty work of locating the
  // appropriate entry.
  ///////////////////////////////////////////////////////////////////
  if ((i = lookup(key)))
  {
    elem_count--;
    status[(int)i-1] = Cell_deleted;
    return true;
  }
  else
    return false;
}

#endif
