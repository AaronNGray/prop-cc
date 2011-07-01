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

#ifndef BURS_item_set_h
#define BURS_item_set_h

#include <iostream>
#include <new>
#include <AD/rewrite/b_item.h>  // Item set
#include <AD/memory/mem.h>      // Memory manager
#include <AD/contain/bitset.h>  // Bit sets

//////////////////////////////////////////////////////////////////////////////
//  A state in the BURS tree automata is represented as a set of items.
//  We represent an item set simply as a vector of BURS_item's indexed
//  by the non-terminal.
//////////////////////////////////////////////////////////////////////////////

class BURS_ItemSet
{
  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef BURS_Item::State       State;
  typedef BURS_Item::Functor     Functor;
  typedef BURS_Item::NonTerminal NonTerminal;
  typedef BURS_Item::Arity       Arity;
  typedef BURS_Item::Cost        Cost;
  typedef BURS_Item::Rule        Rule;

  ///////////////////////////////////////////////////////////////////////////
  //   We'll implement a set of non-terminals as a bitset.
  //   The bitset iterator is given more readable alias.
  ///////////////////////////////////////////////////////////////////////////
  typedef BitSet NonTerminalSet;
#  define foreach_nonterminal(n,set) foreach_bit(n,set)

  ///////////////////////////////////////////////////////////////////////////
  //  Import some constants
  ///////////////////////////////////////////////////////////////////////////
  enum BURS_ItemSet_constants
  {  infinite_cost = TreeGrammar::infinite_cost,
     zero_cost     = TreeGrammar::zero_cost
  };

private:

  int          n;         // number of non-terminals
  BURS_Item    items[1];  // a vector of items, indexed by non-terminal.

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Memory management routines.
  //  We'll redefine `new' and `delete' since item sets are to be allocated
  //  using our own memory pools for efficiency.
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator new    (size_t, Mem& mem, int k);
  inline void   operator delete (void *)
  {}

  ///////////////////////////////////////////////////////////////////////////
  //  Some selectors.
  ///////////////////////////////////////////////////////////////////////////
  inline int              size()                      const
  {
    return n;
  }
  inline const BURS_Item& operator [] (NonTerminal A) const
  {
    return items[A];
  }
  inline       BURS_Item& operator [] (NonTerminal A)
  {
    return items[A];
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Operations on an item set.
  ///////////////////////////////////////////////////////////////////////////
  inline void clear           ();
  inline void normalise_costs ();

  ///////////////////////////////////////////////////////////////////////////
  //  Hashing and equality
  ///////////////////////////////////////////////////////////////////////////
  inline friend unsigned int hash  (const BURS_ItemSet *);
  inline friend Bool         equal (const BURS_ItemSet *, const BURS_ItemSet *);

  ///////////////////////////////////////////////////////////////////////////
  //  Printing method
  ///////////////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream&, const BURS_Item&);
};

//////////////////////////////////////////////////////////////////////////////
//  Clears out an item set
//////////////////////////////////////////////////////////////////////////////

inline void BURS_ItemSet::clear()
{
  for (register int i = n - 1; i > 0; i--)
  {
    items[i].cost = infinite_cost;
    items[i].rule = 0;
  }
  items[0].cost = 0;
  items[0].rule = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Inlined member functions
//////////////////////////////////////////////////////////////////////////////

inline void * BURS_ItemSet::operator new(size_t, Mem& mem, int k)
{
  BURS_ItemSet * set
    =
      (BURS_ItemSet*)mem.m_alloc
      (sizeof(BURS_ItemSet) + (k-1)* sizeof(BURS_Item));
  set
    ->n        = k;
  set
    ->clear();
  return set
           ;
}

//////////////////////////////////////////////////////////////////////////////
//  Hashing function for an item set.
//////////////////////////////////////////////////////////////////////////////

inline unsigned int hash(register const BURS_ItemSet* set)
{
  register unsigned int h = 23;
  for (register int i = set->n - 1; i > 0; i--)
    h += h * 16 + set->items[i].cost;
  return h;
}

//////////////////////////////////////////////////////////////////////////////
//  Equality between two item sets.
//////////////////////////////////////////////////////////////////////////////

inline Bool equal(register const BURS_ItemSet * a,
                  register const BURS_ItemSet * b)
{
  for (register int i = 1; i < a->n; i++)
    if (a->items[i].cost != b->items[i].cost)
      return false;
  return true;
  //|| a->items[i].rule != b->items[i].rule)
}

//////////////////////////////////////////////////////////////////////////////
//  Method to normalise the cost of a state.
//////////////////////////////////////////////////////////////////////////////

inline void BURS_ItemSet::normalise_costs()
{
  ///////////////////////////////////////////////////////////////////////////
  // Find the minimal cost of the item set
  ///////////////////////////////////////////////////////////////////////////
  Cost min_cost = infinite_cost;
  for (int i = n - 1; i > 0; i--)
    if (items[i].cost < min_cost)
      min_cost = items[i].cost;

  ///////////////////////////////////////////////////////////////////////////
  // Subtract the minimal cost from the rest
  ///////////////////////////////////////////////////////////////////////////
  for (int j = n - 1; j > 0; j--)
    if (items[j].cost != infinite_cost)
      items[j].cost -= min_cost;
}

#endif
