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

#ifndef faster_bit_set_h
#define faster_bit_set_h

//////////////////////////////////////////////////////////////////////////////
//  Faster bitsets which changes its internal representation according
//  to need.
//////////////////////////////////////////////////////////////////////////////

#include <string>
#include <AD/contain/bitset.h>
#include <iostream>

class FastBitSet
{
protected:
  Mem& mem;
  enum { EMPTY, SINGLETON, SPARSE, DENSE } kind;
  enum { MAX_SPARSE = 8 };
  int      capacity;   // maximum number of elements
  short *  sparse_set; // place to store the sparse set
  BitSet * dense_set;  // place to store the dense set
  union {
    int one_bit;      // place to store one bit
    int count;        // number of elements stored
  };

public:
  class Iter
  {
    const short  * cursor;
    int            index;
    const BitSet * bitset;
    union {
      short tmp[2];
      int   size;
    };
  public:
    inline Iter() : cursor(tmp)
    {
      tmp[0] = -1;
    }
    inline Iter(const Iter& i)
    {
      *this = i;
    }
    inline Iter(const FastBitSet& s);
    inline int next()
    {
      if (cursor)
        return *cursor++;
      for (int i = index;i < size; i++)
        if (bitset->contains(i))
        {
          index = i+1;
          return i;
        }
      return -1;
    }
  };

  friend class Iter;

private:

  void copy_sparse   (const FastBitSet&);
  void copy_dense    (const FastBitSet&);
  void init_sparse   (const FastBitSet&);
  void init_dense    (const FastBitSet&);
  void init_dense    (const BitSet&);
  void create_sparse (int bit);
  Bool add_sparse    (int bit);
  Bool find_sparse   (int bit) const;
  void basic_sparse_to_dense ();
  void sparse_to_dense ();

public:
  inline FastBitSet(Mem& m, int number_of_bits);
  inline FastBitSet(const FastBitSet& s);

  inline int  size       ()        const
  {
    return capacity;
  }
  inline Bool contains   (int bit) const;
  inline Bool operator[] (int bit) const;
  inline void clear      ();
  inline void add
    (int bit);
  inline int  first_bit  () const;
  void complement ();
  void Union      (const FastBitSet&);
  inline FastBitSet& operator = (const FastBitSet&);

  friend std::ostream& operator << (std::ostream&, const FastBitSet&);
  inline friend unsigned int hash (const FastBitSet *);
  inline friend Bool equal (const FastBitSet *, const FastBitSet *);
};

//////////////////////////////////////////////////////////////////////////////
//
//  Inlined member functions.
//
//////////////////////////////////////////////////////////////////////////////

inline FastBitSet::Iter::Iter( const FastBitSet& s)
{
  switch (s.kind)
  {
  case EMPTY:
    tmp[0] = -1;
    cursor = tmp;
    break;
  case SINGLETON:
    tmp[0] = s.one_bit;
    tmp[1] = -1;
    cursor = tmp;
    break;
  case SPARSE:
    cursor = s.sparse_set;
    break;
  case DENSE:
    cursor = 0;
    bitset = s.dense_set;
    index = 0;
    size = bitset->size();
    break;
  }
}

inline FastBitSet::FastBitSet(Mem& m, int number_of_bits)
    : mem(m),
    kind(EMPTY),
    capacity(number_of_bits),
    sparse_set(0), dense_set(0)
{}

inline FastBitSet::FastBitSet(const FastBitSet& s)
    : mem(s.mem), capacity(s.capacity), sparse_set(0), dense_set(0)
{
  switch (kind = s.kind)
  {
  case SINGLETON:
    one_bit = s.one_bit;
    break;
  case SPARSE:
    init_sparse(s);
    break;
  case DENSE:
    init_dense(s);
    break;
  case EMPTY:
    break;
  }
}

inline FastBitSet& FastBitSet::operator = (const FastBitSet& s)
{
  if (kind == s.kind)
  {
    switch (kind)
    {
    case SINGLETON:
      one_bit = s.one_bit;
      break;
    case SPARSE:
      copy_sparse(s);
      break;
    case DENSE:
      copy_dense(s);
      break;
    case EMPTY:
      break;
    }
  }
  else
  {
    switch (kind = s.kind)
    {
    case SINGLETON:
      one_bit = s.one_bit;
      break;
    case SPARSE:
      init_sparse(s);
      break;
    case DENSE:
      init_dense(s);
      break;
    case EMPTY:
      break;
    }
  }
  return *this;
}

inline Bool FastBitSet::contains (int bit) const
{
  switch (kind)
  {
  case EMPTY:
    return false;
  case SINGLETON:
    return bit == one_bit;
  case SPARSE:
    return find_sparse(bit);
  default:
    return dense_set->contains(bit);
  }
}

inline Bool FastBitSet::operator[] (int bit) const
{
  return contains(bit);
}

inline void FastBitSet::add
  (int bit)
{
  switch (kind)
  {
  case EMPTY:
    {
      kind = SINGLETON;
      one_bit = bit;
    }
  case SINGLETON:
    if (bit != one_bit)
      create_sparse(bit);
    break;
  case SPARSE:
    add_sparse(bit);
    break;
  default:
    dense_set->add
    (bit);
    break;
  }
}

inline void FastBitSet::clear ()
{
  kind = EMPTY;
}

inline unsigned hash( const FastBitSet* set)
{
  switch (set
          ->kind)
  {
  case FastBitSet::EMPTY:
    return 257;
  case FastBitSet::SINGLETON:
    return 8 * set
             ->one_bit;
  case FastBitSet::SPARSE:
    {
      unsigned int h = 0;
      for (const short * p = set->sparse_set; *p >= 0; p++)
          h += *p;
      return h;
    }
  default:
    return hash(set->dense_set);
  }
}

inline Bool equal( const FastBitSet * a, const FastBitSet * b)
{
  if (a->kind != b->kind)
    return false;
  switch (a->kind)
  {
  case FastBitSet::EMPTY:
    return true;
  case FastBitSet::SINGLETON:
    return a->one_bit == b->one_bit;
  case FastBitSet::SPARSE:
    {
      const short * p, * q;
      for (p = a->sparse_set, q = b->sparse_set; ; p++, q++)
      {
        if (*p != *q)
          return false;
        if (*p < 0)
          return true;
      }
      return false;
    }
  default:
    return equal(a->dense_set, b->dense_set);
  }
}

inline int FastBitSet::first_bit() const
{
  switch (kind)
  {
  case SINGLETON:
    return one_bit;
  case SPARSE:
    return sparse_set[0];
  case DENSE:
    {
      for (int i = 0, j = dense_set->size(); i < j; i++)
        if (dense_set->contains(i))
          return i;
    }
  default:
    break;
  }
  return 32767*65536; // not found
}

//////////////////////////////////////////////////////////////////////////////
//
//  Union
//
//////////////////////////////////////////////////////////////////////////////

inline void FastBitSet::Union( const FastBitSet& f)
{
  if (this == &f)
    return;
  switch (kind)
  {
  case EMPTY:
    *this = f;
    break;
  case SINGLETON:
    {
      switch (f.kind)
      {
      case SINGLETON:
        if (one_bit != f.one_bit)
          create_sparse(f.one_bit);
        break;
      case SPARSE:
        {
          int b = one_bit;
          init_sparse(f);
          add_sparse(b);
        }
        break;
      case DENSE:
        {
          int b = one_bit;
          init_dense(f);
          dense_set->add
          (b);
        }
        break;
      default:
        break;
      }
    }
    break;
  case SPARSE:
    {
      switch (f.kind)
      {
      case SINGLETON:
        add_sparse(f.one_bit);
        break;
      case SPARSE:
        {
          short buf[MAX_SPARSE*3];
          const short * p = sparse_set, * q = f.sparse_set;
          short * r = buf;
          while (1)
          {
            if (*p < 0)
            {
              while (*q >= 0)
                *r++ = *q++;
              goto DONE;
            }
            if (*q < 0)
            {
              while (*p >= 0)
                *r++ = *p++;
              goto DONE;
            }
            if (*p == *q)
            {
              *r++ = *p++;
              q++;
            }
            else if (*p < *q)
            {
              *r++ = *p++;
            }
            else
            {
              *r++ = *q++;
            }
          }
DONE:
          count = r - buf;
          if (count >= MAX_SPARSE)
          {
            sparse_to_dense();
            for (const short * pp = f.sparse_set; *pp >= 0; pp++)
              dense_set->add
              (*pp);
          }
          else
          {
            *r = -1;
            memcpy(sparse_set,buf,sizeof(short)*(count+1));
          }
        }
        break;
      case DENSE:
        sparse_to_dense();
        dense_set->Union(*f.dense_set);
        break;
      default:
        break;
      }
    }
    break;
  default:
    {
      switch (f.kind)
      {
      case SINGLETON:
        dense_set->add
        (f.one_bit);
        break;
      case SPARSE:
        {
          for (const short * p = f.sparse_set; *p >= 0; p++)
            dense_set->add
            (*p);
        }
        break;
      case DENSE:
        dense_set->Union(*f.dense_set);
        break;
      default:
        break;
      }
    }
    break;
  }
}

#endif
