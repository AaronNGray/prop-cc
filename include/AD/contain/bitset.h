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

#ifndef bit_set_h
#define bit_set_h

//////////////////////////////////////////////////////////////////////////////
//  BitSets allocated from a Mem.  Hmmm... perhaps this should be
//  merged with class IntSet.  Oh well...
//////////////////////////////////////////////////////////////////////////////

#include <new>
#include <iostream>
#include <AD/generic/generic.h>
#include <AD/memory/mem.h>


class BitSet
{
public:
  typedef unsigned long Blob; // We'll assume this is 32 bits

  int  n;                     // size of array
  Blob set
    [1];                // the actual bitset

  //////////////////////////////////////////////////////////////////////////
  //  Allocation/deallocation.  Notice that a BitSet must be created
  //  thru `operator new'.
  //////////////////////////////////////////////////////////////////////////

  inline void * operator new    (size_t sz, Mem& pool, int bits);
  inline void   operator delete (void *);

  //////////////////////////////////////////////////////////////////////////
  //  Size of set
  //////////////////////////////////////////////////////////////////////////

  inline int    byte_len() const;  // size in bytes
  inline int    size()     const;  // size in bits
  inline int    count()    const;  // number of one bits

  //////////////////////////////////////////////////////////////////////////
  //  Indexing
  //////////////////////////////////////////////////////////////////////////

  inline int    byte(int i) const;         // by byte
  inline Bool   operator [] (int i) const; // by bit
  inline Bool   contains (int i) const;    // by bit

  //////////////////////////////////////////////////////////////////////////
  //  Insertion/deletion/set operations
  //////////////////////////////////////////////////////////////////////////

  inline void   add
    (int i);            // insert one bit
  inline Bool   add_if_changed(int i); // insert one bit, returns true if self is changed
  inline void   remove
    (int i);         // remove one bit
  inline void   clear();               // clear all bits

  inline void   Union(const BitSet&);                // union with a set
  inline void   Union(const BitSet&, const BitSet&); // union two sets and assign
  inline Bool   Union_if_changed(const BitSet&);     // union with a set, returns true if self is changed
  inline void   copy (const BitSet&);

  inline void   Intersect(const BitSet&);                // intersect with a set
  inline void   Intersect(const BitSet&, const BitSet&); // intersect two sets and assign
  inline void   Difference(const BitSet&);               // difference with a set
  inline void   complement();                            // complement self [ good boy, self ]

  //////////////////////////////////////////////////////////////////////////
  //  Test for intersection and containment
  //////////////////////////////////////////////////////////////////////////

  inline Bool   intersects(const BitSet&);  // do we intersect with a set?
  inline Bool   contains(const BitSet&);    // do we contain a set?

  //////////////////////////////////////////////////////////////////////////
  //  Equality and hashing
  //////////////////////////////////////////////////////////////////////////

  inline friend Bool equal(const BitSet *, const BitSet *);
  inline friend unsigned int hash (const BitSet *);

  //////////////////////////////////////////////////////////////////////////
  //  Iterator macro for BitSet
  //////////////////////////////////////////////////////////////////////////

  #define foreach_bit(i,set) \
   for (i = (set).size() - 1; i >= 0; i--) if ((set)[i])
#define foreach_bit_fast(i,S)                            \
   register const BitSet::Blob * _p_;                    \
   register int _i_, _j_;                                \
   register BitSet::Blob _mask_;                         \
   for (_p_ = (S).set + (S).n - 1,                       \
        _i_ = ((S).n - 1) * sizeof(BitSet::Blob) * 8;    \
        _i_ >= 0;                                        \
        _i_ -= sizeof(BitSet::Blob) * 8, _p_--)          \
      for (_mask_ = *_p_, _j_ = 0;                       \
           _mask_; _j_++, _mask_ >>= 1)                  \
         if ((_mask_ & 1) && ((i = _i_ + _j_) || 1))

  //////////////////////////////////////////////////////////////////////////
  //  Printing
  //////////////////////////////////////////////////////////////////////////

  friend std::ostream& operator << (std::ostream&, const BitSet&);
};

//////////////////////////////////////////////////////////////////////////////
//  Implementation of all the inlined methods
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Memory management
//////////////////////////////////////////////////////////////////////////////

inline void * BitSet::operator new (size_t sz, Mem& pool, int bits)
{
  int blobs = (bits + sizeof(Blob)*8-1)/(sizeof(Blob)*8);
  BitSet * b = (BitSet*)pool.c_alloc(sz + (blobs - 1) * sizeof(Blob));
  b->n = blobs;
  return b;
}

inline void BitSet::operator delete (void *)
{} // do nothing

//////////////////////////////////////////////////////////////////////////
// Set operations; inline'd for a self deceiving sense of efficiency.
//////////////////////////////////////////////////////////////////////////

inline Bool BitSet::operator [] (int i) const
{
  return set
           [i/(sizeof(Blob)*8)] & (1 << (i & (sizeof(Blob)*8-1)));
}

inline Bool BitSet::contains (int i) const
{
  return set
           [i/(sizeof(Blob)*8)] & (1 << (i & (sizeof(Blob)*8-1)));
}

inline int  BitSet::size() const
{
  return n * sizeof(Blob) * 8;
}

inline int  BitSet::count() const
{
  int m = 0;
  int i;
  foreach_bit_fast(i,*this)
    m++;
  return m;
}

inline void BitSet::add
  (int i)
{
  set[i/(sizeof(Blob)*8)] |= (1 << (i & (sizeof(Blob)*8-1)));
}

inline Bool BitSet::add_if_changed(int i)
{
  return (*this)[i] ? false : (add
                               (i), true);
}

inline void BitSet::remove
  (int i)
{
  set[i/(sizeof(Blob)*8)] &= ~(1 << (i & (sizeof(Blob)*8-1)));
}

inline int  BitSet::byte_len()  const
{
  return n * sizeof(Blob);
}

inline int  BitSet::byte(int i) const
{
  return (set[i/sizeof(Blob)] >> ((i % sizeof(Blob)) * 8)) & 0xff;
}

inline void BitSet::clear()
{
  for (register Blob * p = set, *q = p + n; p < q; *p++ = 0);
}

inline void BitSet::copy(const BitSet& b)
{
  register Blob * p       = set
                              ;
  register Blob * q       = p + n;
  register const Blob * r = b.set;
  while (p < q)
    *p++ = *r++;
}

inline void BitSet::Union(const BitSet& b)
{
  register Blob * p       = set
                              ;
  register Blob * q       = p + n;
  register const Blob * r = b.set;
  while (p < q)
    *p++ |= *r++;
}

inline void BitSet::Union(const BitSet& a, const BitSet& b)
{
  register Blob * p       = set
                              ;
  register Blob * q       = p + n;
  register const Blob * r = a.set;
  register const Blob * s = b.set;
  while (p < q)
    *p++ = *r++ | *s++;
}

inline Bool BitSet::Union_if_changed(const BitSet& b)
{
  Blob changed = 0;
  register Blob * p       = set
                              ;
  register Blob * q       = p + n;
  register const Blob * r = b.set;
  while (p < q)
  {
    changed |= ((~ *p) & *r);
    *p++ |= *r++;
  }
  return (Bool)changed;
}

inline void BitSet::Intersect(const BitSet& b)
{
  register Blob * p       = set
                              ;
  register Blob * q       = p + n;
  register const Blob * r = b.set;
  while (p < q)
    *p++ &= *r++;
}

inline void BitSet::Intersect(const BitSet& a, const BitSet& b)
{
  register Blob * p       = set
                              ;
  register Blob * q       = p + n;
  register const Blob * r = a.set;
  register const Blob * s = b.set;
  while (p < q)
    *p++ = *r++ & *s++;
}

inline void BitSet::Difference(const BitSet& b)
{
  register Blob * p       = set
                              ;
  register Blob * q       = p + n;
  register const Blob * r = b.set;
  while (p < q)
    *p++ &= ~*r++;
}

inline void BitSet::complement()
{
  for (register Blob * p = set, * q = p + n; p < q; p++) *p = ~ *p;
}

//////////////////////////////////////////////////////////////////////////
//  Containment operations
//////////////////////////////////////////////////////////////////////////

inline Bool BitSet::intersects(const BitSet& b)
{
  for (register const Blob * p = set, * q = p + n, * r = b.set; p < q;)
    if (*p++ & *r++)
      return true;
  return false;
}

inline Bool BitSet::contains(const BitSet& b)
{
  for (register const Blob * p = set
                                   , * q = p + n, * r = b.set; p < q;)
      if (~ *p++ & *r++)
        return false;
  return true;
}

//////////////////////////////////////////////////////////////////////////
// Comparison and hashing
//////////////////////////////////////////////////////////////////////////

inline Bool equal(const BitSet * a, const BitSet * b)
{
  for (register const BitSet::Blob * p = a->set, * q = p + a->n, * r = b->set;
       p < q; p++, r++)
    if (*p != *r)
      return false;
  return true;
}

inline unsigned int hash(const BitSet * a)
{
  register unsigned int h = 4783;
  for (register const BitSet::Blob * p = a->set, * q = p + a->n; p < q; p++)
    h += *p;
  return h;
}

#endif
