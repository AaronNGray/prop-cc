#include "basics.h"
#include "functortab.h"

FunctorTable::FunctorTable(HashFunction f, Equality e, int sz)
    : HashTable(f,e,sz)
{}
FunctorTable::~FunctorTable()
{}

FunctorTable::Functor FunctorTable::operator [] (Key k) const
{
  HashTable::Entry * e = lookup(k);
  if (e)
    return (Functor)(long)(e->v);
  else
  {
    bug("FunctorTable::operator []\n");
    return 0;
  }
}
