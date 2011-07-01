//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string.h>
#include <AD/contain/fbitset.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Print a fast bit set
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& out, const FastBitSet& set)
{
  Bool comma = false;
  out << '[';
  switch (set.kind)
  {
  case FastBitSet::EMPTY:
    out << "empty";
    break;
  case FastBitSet::SINGLETON:
    out << "singleton ";
    break;
  case FastBitSet::SPARSE:
    out << "sparse ";
    break;
  case FastBitSet::DENSE:
    out << "dense ";
    break;
  }
  FastBitSet::Iter iter(set
                       );
  while (1)
  {
    int i;
    if ((i = iter.next()) < 0)
      break;
    if (comma)
      out << ", ";
    out << i;
    comma = true;
  }
  return out << ']';
}

//////////////////////////////////////////////////////////////////////////////
//
//  Initialize a set
//
//////////////////////////////////////////////////////////////////////////////

void FastBitSet::init_sparse( const FastBitSet& s)
{
  kind = SPARSE;
  if (sparse_set == 0)
    sparse_set = (short *)mem.m_alloc(MAX_SPARSE * sizeof(short));
  count = s.count;
  memcpy(sparse_set, s.sparse_set, (count + 1) * sizeof(short));
}

void FastBitSet::init_dense( const FastBitSet& s)
{
  kind = DENSE;
  if (dense_set == 0)
    dense_set = new (mem, capacity) BitSet;
  dense_set->copy(*s.dense_set);
}

void FastBitSet::init_dense( const BitSet& s)
{
  kind = DENSE;
  if (dense_set == 0)
    dense_set = new (mem, capacity) BitSet;
  dense_set->copy(s);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Copy a set
//
//////////////////////////////////////////////////////////////////////////////

void FastBitSet::copy_sparse( const FastBitSet& s)
{
  count = s.count;
  memcpy(sparse_set, s.sparse_set, (count + 1) * sizeof(short));
}

void FastBitSet::copy_dense( const FastBitSet& s)
{
  kind = DENSE;
  dense_set->copy(*s.dense_set);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Create a sparse set starting from a singleton
//
//////////////////////////////////////////////////////////////////////////////

void FastBitSet::create_sparse( int bit2)
{
  kind = SPARSE;
  if (sparse_set == 0)
    sparse_set = (short *)mem.m_alloc(MAX_SPARSE * sizeof(short));
  if (bit2 > one_bit)
  {
    sparse_set[0] = one_bit;
    sparse_set[1] = bit2;
  }
  else
  {
    sparse_set[0] = bit2;
    sparse_set[1] = one_bit;
  }
  sparse_set[2] = -1;
  count = 2;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Find an element in the sparse set
//
//////////////////////////////////////////////////////////////////////////////

Bool FastBitSet::find_sparse( int bit) const
{
  for (const short * p = sparse_set; ; p++)
  {
    int e = *p;
    if (e == -1)
      return false;
    if (e == bit)
      return true;
    if (e > bit)
      return false;
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Convert sparse set to a dense set
//
//////////////////////////////////////////////////////////////////////////////

inline void FastBitSet::basic_sparse_to_dense()
{
  kind = DENSE;
  if (dense_set)
    dense_set->clear();
  else
    dense_set = new (mem,capacity) BitSet;
  int e;
  for (const short * p = sparse_set; (e = *p) >= 0; p++)
    dense_set->add
    (e);
}

void FastBitSet::sparse_to_dense()
{
  basic_sparse_to_dense();
}

//////////////////////////////////////////////////////////////////////////////
//
//  Add an element to the sparse set
//
//////////////////////////////////////////////////////////////////////////////

Bool FastBitSet::add_sparse( int bit)
{
  short * p;
  for (p = sparse_set; ; p++)
  {
    if (*p == bit)
      return false;
    if (*p == -1)
    {
      if (count >= MAX_SPARSE - 1)
        break;
      p[0] = bit;
      p[1] = -1;
      count++;
      return true;
    }
    if (*p > bit)
    {
      if (count >= MAX_SPARSE - 1)
        break;
      for (short * q = sparse_set + count; q != p; q--)
        q[0] = q[-1];
      *p = bit;
      sparse_set[++count] = -1;
      return true;
    }
  }
  basic_sparse_to_dense();
  dense_set->add
  (bit);
  return true;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Complement
//
//////////////////////////////////////////////////////////////////////////////

void FastBitSet::complement()
{
  if (kind != DENSE)
    if (dense_set)
      dense_set->clear();
    else
      dense_set = new (mem, capacity) BitSet;
  switch (kind)
  {
  case SINGLETON:
    dense_set->add
    (one_bit);
    break;
  case SPARSE:
    {
      for(const short * p = sparse_set; *p >= 0; p++)
        dense_set->add
        (*p);
    }
    break;
  default:
    break;
  }
  kind = DENSE;
  dense_set->complement();
}

#if 0
//////////////////////////////////////////////////////////////////////////////
//
//  Union
//
//////////////////////////////////////////////////////////////////////////////

void FastBitSet::Union( const FastBitSet& f)
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
            basic_sparse_to_dense();
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
        basic_sparse_to_dense();
        dense_set->Union(*f.dense_set);
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
      }
    }
    break;
  }
}
#endif
