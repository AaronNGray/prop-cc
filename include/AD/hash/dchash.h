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

#ifndef direct_chaining_hash_table_h
#define direct_chaining_hash_table_h

////////////////////////////////////////////////////////////////////////////
//  Class DCHashTable implements a hash table using direct
//  chaining.
////////////////////////////////////////////////////////////////////////////

#include <AD/generic/ordering.h>

////////////////////////////////////////////////////////////////////////////
//  Class |DCHashTable| is parameterized with the class of the
//  key and the class of the value.  Furthermore, the functions
//      unsigned int hash(const K&);          and
//      Bool     equal(const K&, const K&);
//  must be defined by the client that uses this template.
////////////////////////////////////////////////////////////////////////////

template <class K, class V>
class DCHashTable
{

  //////////////////////////////////////////////////////////////////////
  // A link in the hash chain
  //////////////////////////////////////////////////////////////////////
  struct Link
  {
    const K            key;          // key of entry
    V            value;        // value of entry
    unsigned int hashval;      // hash value
    Link *       next;         // next entry or next bucket
    Link(const K& k, const V& v, unsigned int h, Link * link)
        : key(k), value(v), hashval(h), next(link)
    {}
  }
  ;

  //////////////////////////////////////////////////////////////////////
  // Is the link really a link?
  //////////////////////////////////////////////////////////////////////
  inline friend Bool   is_link(const Link * l)
  {
    return (((unsigned long)l) & 1) == 0;
  }
  inline friend Link * make_anchor(Link ** l)
  {
    return (typename DCHashTable<K,V>::Link*)(((unsigned long)l)|1);
  }
  Ix   find_next(Ix i) const   // find next key given an index
  {
    if (i)
    {
      Link ** bucket = (Link**)(((unsigned long)i) & ~1);
      Link ** limit  = table + table_size;
      for ( ; bucket < limit; bucket++)
        if (is_link(*bucket))
          return *bucket;
    }
    return 0;
  }

  Link ** table;          // the array of hash links
  int     table_size;     // size of the array
  int     elem_count;     // number of elements
  int     max_load;       // maximum number of entries before expansion
  double  max_load_ratio; // maximum ratio between entries versus buckets
  double  growth_ratio;   // amount to expand when resizing

public:
  ////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////
  DCHashTable(int initial_size      = 32,
              double max_load_ratio = 0.0,
              double growth_ratio   = 2.0);
  ~DCHashTable();

  ////////////////////////////////////////////////////////////////////
  //  Assignment
  ////////////////////////////////////////////////////////////////////
  void operator = (const DCHashTable&);

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
  ////////////////////////////////////////////////////////////////////
  inline Ix first()     const
  {
    return find_next(table);
  }
  inline Ix next(Ix i)  const
  {
    Link * pos = ((Link*)i)->next;
    return is_link(pos) ? pos : find_next(pos);
  }
  inline const K& key(Ix i)   const
  {
    return ((Link*)i)->key;
  }
  inline const V& value(Ix i) const
  {
    return ((Link*)i)->value;
  }
  inline       V& value(Ix i)
  {
    return ((Link*)i)->value;
  }

  ////////////////////////////////////////////////////////////////////
  //  Resize the table
  ////////////////////////////////////////////////////////////////////
  void resize(int new_size = 0);
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
DCHashTable<K,V>::DCHashTable
(int size, double maximum_load_ratio, double growth)
    : table(new Link * [size]), table_size(size), elem_count(0)
{
  register int i;
  for (i = 1; i < size; i++)
    table[i-1] = make_anchor(table+i);
  if (size > 0)
    table[i-1] = 0;
  if (maximum_load_ratio <= 1.0)
  {
    max_load_ratio = 100000;
    max_load = 10000000;
  }
  else
  {
    max_load_ratio = maximum_load_ratio;
    max_load = (int)(size * maximum_load_ratio);
  }
  if (growth <= 1.2 || growth >= 5.0)
    growth_ratio = 2.0;
  else
    growth_ratio = growth;
}

//////////////////////////////////////////////////////////////////////////
//  Destroy a table
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
DCHashTable<K,V>::~DCHashTable()
{
  clear();
  delete [] table;
}

//////////////////////////////////////////////////////////////////////////
//  Assignment
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void DCHashTable<K,V>::operator = (const DCHashTable<K,V>& t)
{
  if (this != &t)
  {
    clear();
    delete [] table;
    elem_count = 0;
    table      = new Link * [table_size = t.table_size];
    for (Ix i = t.first(); i; i = t.next(i))
      insert(t.key(i), t.value(i));
  }
}

//////////////////////////////////////////////////////////////////////////
//  Clear a table.
//  We'll traverse thru all the buckets and delete each one iteratively.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void DCHashTable<K,V>::clear()
{
  int i;
  for (i = 0; i < table_size; i++)
  {
    Link * l, * next;
    for (l = table[i]; l && is_link(l); l = next)
    {
      next = l->next;
      delete l;
    }
  }
  for (i = 1; i < table_size; i++)
    table[i-1] = make_anchor(table+i);
  if (table_size > 0)
    table[i-1] = 0;
  elem_count = 0;
}

//////////////////////////////////////////////////////////////////////////
//  Lookup an entry by key; if the entry is not found, return (Ix)0.
//  A simple linear search is used.
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
Ix DCHashTable<K,V>::lookup(const K& key) const
{
  unsigned int h = hash(key);
  unsigned int index = h % table_size;
  Link * link  = table[index];
  for ( ;link && is_link(link); link = link->next)
    if (link->hashval == h && equal(key, link->key))
      return (Ix)link;
  return (Ix)0;
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
Ix DCHashTable<K,V>::insert(const K& key, const V& value)
{
  unsigned int h = hash(key);
  unsigned int index = h % table_size;
  Link * link  = table[index];
  for ( ;link && is_link(link); link = link->next)
    if (link->hashval == h && equal(key, link->key))
    {
      link->value = value;
      return link;
    }
  table[index] = new Link (key,value,h,table[index]);
  if (++elem_count > max_load)
    resize();
  return table[index];
}

//////////////////////////////////////////////////////////////////////////
//  Resizing the hash table
//////////////////////////////////////////////////////////////////////////

template <class K, class V>
void DCHashTable<K,V>::resize(int new_size)
{
  if (new_size <= max_load)
    new_size = (int)(max_load * growth_ratio);

  Link ** new_table = new Link * [new_size];
  register int i;

  ////////////////////////////////////////////////////////////////////
  // Set up the anchor links of new table first
  ////////////////////////////////////////////////////////////////////
  for (i = 1; i < new_size; i++)
    new_table[i-1] = make_anchor(new_table+i);
  if (new_size > 0)
    new_table[i-1] = 0;

  ////////////////////////////////////////////////////////////////////
  // Then traverse the old table and move the links to the new one
  ////////////////////////////////////////////////////////////////////
  for (i = 0; i < table_size; i++)
  {
    Link * l, * next;
    for (l = table[i]; l && is_link(l); l = next)
    {
      unsigned int new_index = l->hashval % new_size;
      next = l->next;
      l->next = new_table[new_index];
      new_table[new_index] = l;
    }
  }
  delete [] table;
  table      = new_table;
  max_load   = (int)(new_size * max_load_ratio);
  table_size = new_size;
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
Bool DCHashTable<K,V>::remove
  (const K& key)
{
  unsigned int h = hash(key);
  unsigned int index = h % table_size;
  Link * link = table[index];
  Link * last = 0;
  for ( ;link && is_link(link); last = link, link = link->next)
    if (link->hashval == h && equal(key, link->key))
    {
      if (last)
        last->next = link->next;
      else
        table[index] = link->next;
      delete link;            // frees the old entry
      elem_count--;
      return true;
    }
  return false;
}

#endif
