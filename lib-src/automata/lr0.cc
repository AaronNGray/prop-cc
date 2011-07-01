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

//////////////////////////////////////////////////////////////////////////////
//
//  This file contains the implementation of class |LR0|, which computes
//  the characteristic LR(0) finite state automata when given a context-free
//  grammar.
//
//  We'll use a ``textbook'' implementation for simplicity.
//
//////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <new>
#include <AD/automata/item.h>    // LR Items
#include <AD/automata/lr0.h>     // LR(0) finite state machine
#include <AD/contain/bitset.h>   // bitsets
#include <AD/contain/vararray.h> // variable sized arrays
#include <AD/contain/slnklist.h> // Linked lists
#include <AD/contain/stack.h>    // generic stack
#include <AD/memory/mem.h>       // memory manager
#include <AD/hash/dchash.h>      // direct chaining hash table


//////////////////////////////////////////////////////////////////////////////
//
//  Make hidden types visible
//
//////////////////////////////////////////////////////////////////////////////

typedef Grammar::Symbol      Symbol;
typedef Grammar::Production  Production;
typedef Grammar::Terminal    Terminal;
typedef Grammar::NonTerminal NonTerminal;
typedef Grammar::EquivMap    EquivMap;
typedef LR0::State           State;
typedef LR0::ItemNum         ItemNum;
typedef LR0::ItemSet         ItemSet;

//////////////////////////////////////////////////////////////////////////////
//
//  Internal representation of class LR0.
//  This is hidden from the interface to make it easier to
//  alter the implementation of LR0.
//
//////////////////////////////////////////////////////////////////////////////

class LR0_Impl
{
private:
  LR0_Impl(const LR0_Impl&);         // no copy constructor
  void operator = (const LR0_Impl&); // no assignment

public:
  const Grammar& G;                          // the grammar
  DCHashTable <LRItem *, int>    item_to_num; // mapping from items to item numbers
  DCHashTable <ItemSet *, State> item_sets;   // mapping from item set to state numbers
  VarArray <ItemSet *>           new_states;  // Mapping from states to item sets
  LRItem **                      num_to_items;// mapping from item numbers to items
  VarArray <State *>             trans;       // transition map indexed by state
  VarArray <SLinkList<State> *>  pred;

  LR0_Impl(const Grammar& g, int N) : G(g), item_to_num(N), item_sets(N)
  {}
  ~LR0_Impl()
  {}
}
;

//////////////////////////////////////////////////////////////////////////////
//
//  Constructors and destructor
//
//////////////////////////////////////////////////////////////////////////////

LR0:: LR0(Mem& m) : mem(m), impl(0)
{}

LR0:: LR0(const Grammar& G, const OpPrecedence& P, Mem& m)
    : mem(m), impl(0)
{
  build(G,P);
}

LR0::~LR0()
{
  delete impl;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Compute the transitive closure of an item set.
//  My [insert your favorate diety here], this algorithm is as naive as
//  you can get.
//
//  Returns true if the set has been changed.
//
//////////////////////////////////////////////////////////////////////////////

inline Bool closure0
( const Grammar&  G,             // The grammar
  LRItem *  num_to_items[],      // Maps item number to items
  ItemSet * non_term_to_item[],  // Maps non-terminal to item set
  register ItemSet& set          // The current item set
  )
{
  ///////////////////////////////////////////////////////////////////////////
  // Repeat until fixed point is reached.
  ///////////////////////////////////////////////////////////////////////////
  Bool altered = false;
  Bool changed;
  do
  {
    changed = false;
    register int i;
    foreach_item (i,set
                 )
    {
      const LRItem * item = num_to_items[i];
      Symbol A = item->P[item->pos+1];
      if (G.isNonTerminal(A))
      {
        if (set.Union_if_changed(*non_term_to_item[A]))
          changed = true;
      }
    }
    if (changed)
      altered = true;
  }
  while (changed);
  return altered;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Function to compute the transition function from one item set
//
//////////////////////////////////////////////////////////////////////////////

inline void goto0
( register ItemSet& s,                    // The item set
  const Grammar& G,                       // The grammar
  LRItem * num_to_items[],                // Maps item number to items
  ItemSet * non_term_to_item[],           // Maps non-terminal to item set
  const ItemNum non_term_to_one_item[],   // Maps non-terminal to one item
  ItemSet ** is_used,                     // is the entry used??
  ItemSet ** s0                           // The output item set
)
{
  //////////////////////////////////////////////////////////////
  // Compute the transition sets $s_0$ from $s$:
  //   \[ s_0 = closure0 { A -> a X . b | A -> a . X b \in s } \]
  //////////////////////////////////////////////////////////////
  register int i;
  foreach_item (i, s)
  {
    const LRItem * item = num_to_items[i];
    register Symbol X   = item->P[item->pos+1];
    if (X > Grammar::END_PRODUCTION)
    { // terminals and non-terminals only
      register ItemSet& set
        = *s0[X];
      //
      // the shifted item (on symbol X) must be $i+1$ according to
      // our item numbering scheme.
      //
      if (is_used[X] != &s)
        set.clear(); // clear it first
      is_used[X] = &s; // mark it as a non-error transition
      set.add( i + 1 );
      Symbol A = item->P[item->pos + 2];
      //
      // Avoid recomputing the closure of the shifted item,
      // which is an expensive operation.  We'll compute the closure only
      // if a representative of the closure cannot be found.
      //
      if (G.isNonTerminal(A) && ! set
            [non_term_to_one_item[A]])
          set.Union(*non_term_to_item[A]);
      // if (G.isNonTerminal(A))
      //    set.Union(*non_term_to_item[A]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Build a characteristic finite state machine from a grammar.
//  The grammar must be in a canonical form without action symbols,
//  except on the right hand sides.
//
//////////////////////////////////////////////////////////////////////////////

void LR0::build(const Grammar& G, const OpPrecedence& prec)
{
  ///////////////////////////////////////////////////////////////////////
  //  Allocate the new implementation and initialize a few local
  //  variables.
  ///////////////////////////////////////////////////////////////////////
  delete impl;
  impl                                      = new LR0_Impl(G,1003);
  DCHashTable <LRItem *, int>& item_to_num  = impl->item_to_num;
  DCHashTable <ItemSet *, State>& item_sets = impl->item_sets;
  VarArray <State *>& trans                 = impl->trans;
  VarArray <SLinkList<State> *>& pred       = impl->pred;

  ///////////////////////////////////////////////////////////////////////
  //  Enumerate all possible items and insert them into the items
  //  mapping.  After this all items will be given its own unique number.
  ///////////////////////////////////////////////////////////////////////
  {  for (int i = 0; i < G.size(); i++)
    {
      Production P = G[i];
      int j = 0;
      for (;;)
      {
        LRItem * item = new(mem,G,i,P,j,prec) LRItem;
        item_to_num.insert(item, item_to_num.size());
        j++;
        if (G.isAction(P[j]) || P[j] == Grammar::END_PRODUCTION)
          break;
      }
    }
  }

  ///////////////////////////////////////////////////////////////////////
  // Compute the inverse mapping of above.
  ///////////////////////////////////////////////////////////////////////
  int number_of_items = item_to_num.size();
  LRItem ** num_to_items = impl->num_to_items =
                             (LRItem **)mem.m_alloc(sizeof(LRItem*) * number_of_items);
  {
    foreach (i,item_to_num)
    num_to_items[item_to_num.value(i)] = item_to_num.key(i);
  }

  ///////////////////////////////////////////////////////////////////////
  //  Precompute a map, mapping all lhs non-terminal A to the set of
  //  items of the form:
  //
  //         A -> . X Y Z
  //
  //  This map is used subsequently to compute the transitive closures
  //  of the item sets.
  ///////////////////////////////////////////////////////////////////////
  int max_non_term = G.max_non_terminal();
  ItemSet ** non_term_to_item     = new ItemSet * [ max_non_term + 1];
  ItemNum *  non_term_to_one_item = new ItemNum   [ max_non_term + 1];
  {
    LRItem item;
    item.pos = 0;
    for (int j = max_non_term; j >= 0; j--)
      non_term_to_item[j] = 0;
    for (int i = 0; i < G.size(); i++)
    {
      item.P        = G[i];
      NonTerminal A = item.P[0];
      if (non_term_to_item[A] == 0)
        non_term_to_item[A] = new (mem,number_of_items) ItemSet;
      ItemNum itm = item_to_num[&item];
      non_term_to_item[A]->add
      (itm);
      non_term_to_one_item[A] = itm;
    }
  }

  ///////////////////////////////////////////////////////////////////////
  //  Precompute the closures of each item of the form
  //       A -> . X Y Z
  //
  //  This is done by iterating over the closure computation of all
  //  non-terminals until the least fixed point is reached.
  ///////////////////////////////////////////////////////////////////////
  {  Bool again;
    do
    {
      again = false;
      register NonTerminal A;
      for (A = G.min_non_terminal(); A <= G.max_non_terminal(); A++)
      {
        if (non_term_to_item[A] &&
            closure0(G, num_to_items, non_term_to_item, *non_term_to_item[A]))
          again = true;
      }
    }
    while (again);
  }

  ///////////////////////////////////////////////////////////////////////
  //  The first state is the error state represented by an empty
  //  item set.  By default, this is state 0;
  ///////////////////////////////////////////////////////////////////////
  VarArray<ItemSet *>& new_states = impl->new_states;
  {
    ItemSet * error_item_set = new (mem,number_of_items) ItemSet;
    item_sets.insert(error_item_set, 0);
    new_states [ 0 ] = error_item_set;
    trans[ 0 ] = (State *) mem.c_alloc(sizeof(State) * (G.max_non_terminal() + 1));
  }

  ///////////////////////////////////////////////////////////////////////
  //  The second state is the start state of the input grammar.
  //  This is state number 1.
  ///////////////////////////////////////////////////////////////////////
  {  ItemSet * start_state = non_term_to_item[ G.start() ];
    if (start_state)
    {
      item_sets.insert(start_state, 1);
      new_states [ 1 ] = start_state;
    }
  }

  ///////////////////////////////////////////////////////////////////////
  //  Compute the rest of the states using the good ol' subset
  //  construction:
  //  For each item $i$, we compute its transitive closure and transition
  //  function, then insert them into the map $item_sets$.  Each unique
  //  item set is given an unique LR(0) state number.
  //
  //  This is where we spend most of our time.
  ///////////////////////////////////////////////////////////////////////
  {  ItemSet ** new_s;     // an array of new item sets
    ItemSet ** is_used;   // is this entry used?
    State state;          // start at state 1
    int max_state = 1;    // limit

    //
    // Allocate the item set array
    //
    new_s    = new ItemSet * [ G.max_non_terminal() + 1 ];
    is_used  = new ItemSet * [ G.max_non_terminal() + 1 ];
    {
      for (int ii = G.min_terminal(); ii <= G.max_non_terminal(); ii++)
      {
        new_s[ii] = new (mem, number_of_items) ItemSet;
        is_used[ii] = 0;
      }
    }

    //
    // Compute the states
    //
    for (state = 1; state <= max_state; state++)
    {
      ItemSet& s = *new_states[state];

      //
      // Compute the goto function
      //
      State * delta = (State *) mem.m_alloc(sizeof(State) * (G.max_non_terminal() + 1));
      trans[ state ] = delta;
      goto0(s, G, num_to_items,
            non_term_to_item, non_term_to_one_item,
            is_used, new_s);

      //
      // Compute the transition state numbers
      //
      for (Symbol X = G.min_terminal(); X <= G.max_non_terminal(); X++)
      {
        if (is_used[X] != &s)
        {
          //
          // Going to the error state; we'll just reuse the set
          //
          delta[X] = 0;
        }
        else
        {
          // Going to some other state
          Ix new_state = item_sets.lookup(new_s[X]);
          State new_state_num;
          if (new_state == 0)
          {
            // state is new
            new_state_num = ++max_state;
            item_sets.insert( new_s[X], new_state_num );
            new_states[ new_state_num ] = new_s[X];
            new_s[X] = new (mem, number_of_items) ItemSet;
            pred[new_state_num] = 0;
          }
          else
          {
            // state is old; reuse it
            new_state_num = item_sets.value(new_state);
          }
          delta[X] = new_state_num;
          pred[new_state_num] =
            new (mem, state, pred[new_state_num]) SLinkList<State>;
        }
      }
    }
    delete [] new_s;
    delete [] is_used;
  }

  ////////////////////////////////////////////////////////////////////////
  // Set cached values
  ////////////////////////////////////////////////////////////////////////
  item_count               = item_to_num.size();
  state_count              = item_sets.size();
  all_items                = num_to_items;
  all_item_sets            = new_states;
  all_transitions          = trans;
  all_predecessors         = &pred[0];
  all_singleton_states     = (char*)mem.c_alloc(sizeof(char) * state_count);

  ////////////////////////////////////////////////////////////////////////
  // Now compute the mapping from state number to reducing items
  ////////////////////////////////////////////////////////////////////////
  all_reducing_items =
    (SLinkList<ItemNum> **)mem.c_alloc(sizeof(SLinkList<ItemNum>*) * state_count);
  {
    for (State s = 0; s < state_count; s++)
    {
      register const ItemSet& set
        = *all_item_sets[s];
      ItemNum i;
      SLinkList<ItemNum> * l = 0;
      int items_tally = 0;
      foreach_item (i, set
                     )
      {
        const LRItem * item = all_items[i];
        if (item->P[item->pos + 1] <= Grammar::END_PRODUCTION)
          l = new (mem, i, l) SLinkList<ItemNum>;
        items_tally++;
      }
      all_reducing_items[s]   = l;
      // all_singleton_states[s] = items_tally == 1;

      // True if there is only one item or if all items are shifts.
      all_singleton_states[s] = items_tally == 1 || l == 0;
    }
  }

  ////////////////////////////////////////////////////////////////////////
  // Clean up properly
  ////////////////////////////////////////////////////////////////////////
  delete [] non_term_to_item;
  delete [] non_term_to_one_item;
}

///////////////////////////////////////////////////////////////////////////
//  Return the item number when given an item
///////////////////////////////////////////////////////////////////////////

LR0::ItemNum LR0::item_number( const LRItem& item) const
{
  return impl->item_to_num[ (LRItem*const)&item ];
}
