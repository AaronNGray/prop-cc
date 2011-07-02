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

#ifndef linear_probing_hash_table_h
#define linear_probing_hash_table_h

////////////////////////////////////////////////////////////////////////////
//  Class LHashTable implements a hash table using a simple
//  linear hashing scheme\cite{Algorithms}.
////////////////////////////////////////////////////////////////////////////

#include <string>
#include <AD/generic/ordering.h>

////////////////////////////////////////////////////////////////////////////
//  Class |LHashTable| is parameterized with the class of the
//  key and the class of the value.  Furthermore, the functions
//      unsigned int hash(const K&);          and
//      Bool     equal(const K&, const K&);
//  must be defined by the client that uses this template.
////////////////////////////////////////////////////////////////////////////

template <class K, class V>
class LHashTable
{

  K *            keys;           // the array of keys
  V *            values;         // the array of values
  unsigned int * hashvals;       // hash values
  char *         status;         // status of cell
  int            table_size;     // size of the array
  int            elem_count;     // number of elements
  int            delete_count;   // number of elements deleted
  double         max_load_ratio; // maximum load ratio (> 0 && < 1)
  double         growth_ratio;   // amount to grow when expanding
  int            max_load;       // maximum elements before resizing

public:
  ////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////
  LHashTable(int initial_size      = 32,
             double max_load_ratio = 0.0,
             double growth_ratio   = 2.0);
  ~LHashTable();

  ////////////////////////////////////////////////////////////////////
  //  Assignment
  ////////////////////////////////////////////////////////////////////
  void operator = (const LHashTable&);

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
  Ix   insert(const K&, const V&);   // insert a new entry
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
  // Resize the table
  ////////////////////////////////////////////////////////////////////
  void resize(int new_size = 0);

private:
  ////////////////////////////////////////////////////////////////////
  //  Addition implementation methods
  ////////////////////////////////////////////////////////////////////
  inline Ix find_next(int i) const  // locate the next used entry
  {
    while (i < table_size)
      if (status[i++] == Cell_used)
        return (Ix)i;
    return (Ix)0;
  }
};

//////////////////////////////////////////////////////////////////////////
//  Implementation of the template methods
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//  Create a new table.
//  Implementation note: each end of each chain of the buckets are
//  linked to the next.  This makes it possible to find the next entry
//  during iteration quickly.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
LHashTable<K,V>::LHashTable
(int size, double maximum_load_ratio, double growth)
    : keys(new K [size]), values(new V [size]),
    hashvals(new unsigned int [size]), status(new char [size]),
    table_size(size)
{
  clear();
  if (maximum_load_ratio >= 0.9 || maximum_load_ratio <= 0.1)
    max_load_ratio = .7;
  else
    max_load_ratio = maximum_load_ratio;
  if (growth <= 1.2 || growth >= 5.0)
    growth_ratio = 2.0;
  else
    growth_ratio = growth;
  max_load = (int)(max_load_ratio * size);
  if (max_load >= size)
    max_load = size - 1;
}

//////////////////////////////////////////////////////////////////////////
//  Destroy a table
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
LHashTable<K,V>::~LHashTable()
{
  delete [] keys;
  delete [] values;
  delete [] hashvals;
  delete [] status;
}

//////////////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void LHashTable<K,V>::operator = (const LHashTable<K,V>& t)
{
  if (this != &t)
  {
    delete [] keys;
    delete [] values;
    delete [] hashvals;
    delete [] status;
    elem_count = t.elem_count;
    table_size = t.table_size;
    keys     = new K            [table_size];
    values   = new V            [table_size];
    status   = new char         [table_size];
    hashvals = new unsigned int [table_size];
    for (int i = 0; i < table_size; i++)
    {
      if ((status[i] = t.status[i]) == Cell_used)
      {
        keys[i]     = t.keys[i];
        values[i]   = t.values[i];
        hashvals[i] = t.hashvals[i];
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
//  Clear a table.
//  We'll traverse thru all the buckets and delete each one iteratively.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void LHashTable<K,V>::clear()
{
  memset(status,0,table_size);
  elem_count = 0;
  delete_count = 0;
}

//////////////////////////////////////////////////////////////////////////
//  Lookup an entry by key; if the entry is not found, return (Ix)0.
//  A simple linear search is used.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
Ix LHashTable<K,V>::lookup(const K& key) const
{
  unsigned int h = ::hash(key);
  unsigned int i = h % table_size;
  for (;;)
  {
    switch (status[i])
    {
    case Cell_unused:
      return (Ix)0;
    case Cell_used:
      if (h == hashvals[i] && equal(key,keys[i]))
        return (Ix)(i+1);
    }
    if (++i == (unsigned int)table_size)
      i = 0;
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
Ix LHashTable<K,V>::insert(const K& key, const V& value)
{
  /////////////////////////////////////////////////////////////////////
  // Make sure we have at least one unused cell.
  /////////////////////////////////////////////////////////////////////
  if (elem_count + delete_count >= max_load)
    resize();
  unsigned int h = ::hash(key);
  register unsigned int i = h % table_size;
  register int deleted;

  /////////////////////////////////////////////////////////////////////
  //  Loop until one of the following:
  //    (1) The key is found; in which case the value is updated.
  //    (2) An unused cell is found; then we'll use the first
  //        deleted cell found along the way.  If there is none,
  //        we'll use the unused cell.   This is done to minimize
  //        the effect of contamination.
  /////////////////////////////////////////////////////////////////////
  for (deleted = -1;;)
  {
    switch (status[i])
    {
    case Cell_deleted:
      if (deleted < 0)
        deleted = i;
      break;
    case Cell_unused:
      goto found;
    case Cell_used:
      if (h == hashvals[i] && equal(key,keys[i]))
      {
        values[i] = value;
        return (Ix)(i+1);
      }
    }
    if (++i == (unsigned int)table_size)
      i = 0;
  }
found:
  if (deleted >= 0)
  {
    i = deleted;
    delete_count--;
  }
  elem_count++;
  keys[i] = key;
  values[i] = value;
  hashvals[i] = h;
  status[i] = Cell_used;
  return (Ix)(i+1);
}

//////////////////////////////////////////////////////////////////////////
//  Resizing the hash table.  All entries are completed rehashed.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void LHashTable<K,V>::resize(int new_size)
{
  if (new_size <= elem_count)
    new_size = (int)(table_size * growth_ratio);

  char *         new_status   = new char [ new_size ];
  K    *         new_keys     = new K    [ new_size ];
  V    *         new_values   = new V    [ new_size ];
  unsigned int * new_hashvals = new unsigned int [ new_size ];
  memset(new_status,0,new_size);

  //////////////////////////////////////////////////////////////////
  //  Rehash all used cells one by one.  Notice that since all keys
  //  are unique, we don't have to do any comparison.
  //////////////////////////////////////////////////////////////////
  for (int i = 0; i < table_size; i++)
  {
    if (status[i] == Cell_used)
    {
      register int j = hashvals[i] % new_size;
      for (;;)
      {
        if (new_status[j] != Cell_used)
        {
          new_keys[j]     = keys[i];
          new_values[j]   = values[i];
          new_hashvals[j] = hashvals[i];
          new_status[j]   = Cell_used;
          break;
        }
        if (++j == new_size)
          j = 0;
      }
    }
  }
  delete [] keys;
  delete [] values;
  delete [] hashvals;
  delete [] status;
  keys = new_keys;
  values = new_values;
  hashvals = new_hashvals;
  status = new_status;
  table_size = new_size;
  delete_count = 0;
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
Bool LHashTable<K,V>::remove
  (const K& key)
{
  Ix i;
  ///////////////////////////////////////////////////////////////////
  // We'll just call lookup() to do the dirty work of locating the
  // appropriate entry.
  ///////////////////////////////////////////////////////////////////
  if ((i = lookup(key)))
  {
    delete_count++;
    elem_count--;
    status[(int)i-1] = Cell_deleted;
    return true;
  }
  else
    return false;
}

#endif
