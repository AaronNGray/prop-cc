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

#include <AD/automata/sparsdfa.h>
#include <AD/contain/varstack.h>

//////////////////////////////////////////////////////////////////////////////
// Since optimal compression of the sparse table is equivalent to the
// problem of prune trie space minimization and is
// NP-complete(\cite{NP}, page 226), we'll use a simple first-fit
// strategy instead.
//
// The first-fit compression algorithm treats singleton states
// (i.e. states with only one out transition) specially.  Singleton states
// transitions are saved on the stack |singletons| and are processed at
// the end of the run to fill up the remaining gaps.
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
////////////////////////////////////////////////////////////////////////

typedef SparseDFA::Symbol Symbol;
typedef SparseDFA::State  State;

//////////////////////////////////////////////////////////////////////////
//  Internally, class SparseDFA contains a stack of states with
//  single non-error transition.  These types of states are treated
//  as a special case to during table compression.
//////////////////////////////////////////////////////////////////////////

struct SingleTrans
{
  State state;
  Symbol c;
  State dest;
  SingleTrans()
  {}
  SingleTrans(State s, Symbol a, State d) : state(s), c(a), dest(d)
  {}
}
;

//////////////////////////////////////////////////////////////////////////
// Stack of states with only 1 out transition
//////////////////////////////////////////////////////////////////////////

struct SparseDFA_Impl
{
  VarStack <SingleTrans> singletons;
};

////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////

SparseDFA:: SparseDFA () : impl(0)
{}

SparseDFA::~SparseDFA ()
{
  delete impl;
}

////////////////////////////////////////////////////////////////////////
//  Start generating tables; just clear the stack that memorize
//  singleton transitions
////////////////////////////////////////////////////////////////////////

void SparseDFA::start()
{
  delete impl;
  impl = new SparseDFA_Impl;
  impl->singletons.clear();
  offset_base = 0;
}

////////////////////////////////////////////////////////////////////////
//  Finish generating tables.  We'll go thru the singletons transitions
//  emit them at this point
////////////////////////////////////////////////////////////////////////

void SparseDFA::finish()
{  //
  // Fit all singleton transitions into the gaps.  O(n) complexity.
  //
  register int offset, limit;
  VarStack <SingleTrans>& singletons = impl->singletons;
  for (offset = - min_symbol; ! singletons.is_empty(); )
  {
    SingleTrans& t = singletons.pop();
    for (;;)
    {
      for (limit = table_size - max_symbol - 1; offset < limit; offset++)
      {
        if (check[offset + t.c] == error_state)
        {
          base[t.state]       = offset;
          check[offset + t.c] = t.state;
          next[offset + t.c]  = t.dest;
          if (offset + max_symbol > max_check)
            max_check = offset + max_symbol;
          goto next_symbol;
        }
      }
      //
      // All available gaps are filled.  We'll have to increase
      // the table size to fit in the rest.  We'll have a perfect fit.
      //
      grow_tables( singletons.size() + max_symbol - min_symbol + 1);
      limit = table_size;
      max_check = table_size - 1;
    }
next_symbol:
    ;
  }

  /////////////////////////////////////////////////////////////////////
  // Clean up
  /////////////////////////////////////////////////////////////////////
  delete impl;
  impl = 0;
}

////////////////////////////////////////////////////////////////////////
//  Add a new state to the automaton
////////////////////////////////////////////////////////////////////////

void SparseDFA::add_state
( State s, int fan_out, const Symbol symbols[], const State delta[] )
{
  register int i, offset;

  //
  // Increase the size of the state to base offset table if necessary.
  //
  if (s > max_state)
    max_state = s;
  if (s - error_state + 1 > number_of_states)
  {
    grow_states(states() * 3 / 2 + 8);
  }

  //
  // Singletons are saved onto a stack and processed at the end of the run.
  //
  if (fan_out == 0)
    return;
  if (fan_out == 1)
  {
    impl->singletons.push(SingleTrans(s,symbols[0],delta[0]));
    return;
  }

  //
  // Now fit in the rest using a simple first fit strategy.  Worst case
  // complexity is O(n^2).  However, since the transitions are sparse
  // we expect the average complexity to be better.
  //
  {  register int i, limit;
    for (i = offset_base, limit = table_size; i < limit; i++)
    {
      if (check[i] == error_state)
        break;
    }
    offset_base = i;
  }

  for (offset = - min_symbol + offset_base;; )
  {
    register int limit = table_size - max_symbol - 1;
    if (limit <= offset)
      grow_tables(table_size * 3 / 2 + offset - limit);

    //
    // Use linear search on the tables
    //

    for ( ; offset < limit; offset++)
    {
      for (i = fan_out - 1; i >= 0; i--)
        if (check[offset + symbols[i]] != error_state)
          goto try_again;
      //
      // Found the right spot
      //
      for (i = fan_out - 1; i >= 0; i--)
      {
        check[offset + symbols[i]] = s;
        next[offset + symbols[i]]  = delta[i];
      }
      base[s] = offset;
      if (offset + max_symbol > max_check)
        max_check = offset + max_symbol;
      return;
try_again:
      ;
    }
  }
}
