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

#ifndef LR0_finite_state_machine_h
#define LR0_finite_state_machine_h

#include <AD/automata/grammar.h>
#include <AD/automata/item.h>
#include <AD/automata/dfatable.h>
#include <AD/automata/operprec.h>
#include <AD/contain/bitset.h>
#include <AD/memory/mem.h>
#include <AD/contain/slnklist.h>

//////////////////////////////////////////////////////////////////////////////
//  Class |LR0| represents the LR(0) finite state machine
//  of a grammar.  It is used in the shift/reduce parser generators.
//////////////////////////////////////////////////////////////////////////////
class LR0 : private DFATables
{
  LR0 (const LR0&);              // no copying constructor
  void operator = (const LR0&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////
  typedef DFATables            Super;
  typedef Super::State         State;
  typedef Super::Rule          Rule;
  typedef Grammar::Symbol      Symbol;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Terminal    Terminal;
  typedef Grammar::EquivMap    EquivMap;
  typedef int                  ItemNum;
  typedef BitSet               ItemSet;

  ///////////////////////////////////////////////////////////////////////////
  //  Iterator macro for ItemSet
  ///////////////////////////////////////////////////////////////////////////
#  define foreach_item(i,set) foreach_bit_fast(i,set)

protected:

  Mem& mem;                      // a memory manager

  class LR0_Impl * impl;         // implementation is hidden

  ///////////////////////////////////////////////////////////////////////////
  //  Well mostly.  For efficiency some things are cached.
  ///////////////////////////////////////////////////////////////////////////
  int item_count;            // number of items within the machine
  int state_count;           // number of states within the machine
  ItemSet ** all_item_sets;  // mapping from state to item sets
  LRItem ** all_items;       // mapping from item number to item
  State  ** all_transitions; // mapping from state to transitions fn's.
  SLinkList<ItemNum> ** all_reducing_items;
  // mapping from state to list of reducing items
  const SLinkList<State> * const * all_predecessors;
  char * all_singleton_states;     // does the state has only one item?

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////

  LR0( Mem& );
  LR0( const Grammar&, const OpPrecedence&, Mem& );
  virtual ~LR0();

  ///////////////////////////////////////////////////////////////////////////
  //  Build the LR(0) dfa from a grammar
  ///////////////////////////////////////////////////////////////////////////

  virtual void build( const Grammar&, const OpPrecedence&);

  ///////////////////////////////////////////////////////////////////////////
  //  Count the states and items
  ///////////////////////////////////////////////////////////////////////////

  inline int number_of_states() const
  {
    return state_count;
  }
  inline int number_of_items()  const
  {
    return item_count;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////

  inline const ItemSet& state_items( State s) const
  {
    return *all_item_sets[s];
  }

  inline const LRItem * operator [] ( ItemNum i) const
  {
    return all_items[i];
  }

  inline const State * transitions( State s) const
  {
    return all_transitions[s];
  }

  inline const SLinkList<ItemNum>* reducing_items( State s) const
  {
    return all_reducing_items[s];
  }

  inline const SLinkList<State>* predecessors( State s) const
  {
    return all_predecessors[s];
  }

  ItemNum item_number( const LRItem& ) const;

  inline Bool is_singleton_state( State s) const
  {
    return all_singleton_states[s];
  }

  ///////////////////////////////////////////////////////////////////////////
  // Miscellaneous
  ///////////////////////////////////////////////////////////////////////////
  inline Mem& memOf() const
  {
    return mem;
  }
};

#endif
