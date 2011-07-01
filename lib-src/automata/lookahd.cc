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

#include <iomanip>
#include <AD/automata/lookahd.h>    // Lookahead set computation
#include <AD/automata/firstset.h>   // Grammar analysis
#include <AD/contain/varstack.h>    // Generic stack
#include <AD/hash/lhash.h>          // Linear probing hash table
#include <AD/contain/slnklist.h>    // Singly linked lists

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////

typedef LookaheadSets::Symbol       Symbol;
typedef LookaheadSets::NonTerminal  NonTerminal;
typedef LookaheadSets::Terminal     Terminal;
typedef LookaheadSets::Production   Production;
typedef LookaheadSets::ShiftReduce  ShiftReduce;
typedef LR0::State                  State;
typedef LR0::ItemNum                ItemNum;
typedef LR0::Rule                   Rule;
typedef LR0::ItemSet                ItemSet;
typedef OpPrecedence::Associativity Associativity;
typedef OpPrecedence::Fixity        Fixity;
typedef OpPrecedence::Precedence    Precedence;

//////////////////////////////////////////////////////////////////////////////
//  A state / item number pair
//  Assume we have a maximum of 65535 states and 65535 items.
//  Should be enough unless you have some huge grammars.
//////////////////////////////////////////////////////////////////////////////

typedef unsigned long SI;
#define S_I(state, item) (((state) << 16) | (item))

//////////////////////////////////////////////////////////////////////////////
// Hashing and equality functions for productions
//////////////////////////////////////////////////////////////////////////////

inline Bool equal (Production a, Production b)
{
  return a == b;
}

inline unsigned int hash(Production P)
{
  return (unsigned int)P;
}

//////////////////////////////////////////////////////////////////////////////
//  Internal implementation of class LookaheadSets.
//////////////////////////////////////////////////////////////////////////////

struct LookaheadSets_Impl
{

  // Hash table storing the lookahead symbols of each item in each state
  LHashTable <SI, BitSet *>                  reduction_lookaheads;
  LHashTable <Production, Rule>              rule_map;
  State *                                    reduced;
  int   *                                    slot;

  LookaheadSets_Impl()
      : reduction_lookaheads(1003), rule_map(257)
  {}
}
;

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the reduction lookaheads.
//
//  While the method is based on backward lookahead search by
//  DeRemer and Pennello, I haven't had the chance to read their paper
//  in full.   What we have here is HomeGrown(tm), and may not be
//  correct!
//
//  Note on Allen's HomeGrown Lookahead Set Backward Search Algorithm
//  (pat. pending):
//      The basic idea is just to search backward by need from one state
//  to its predecessors (due to shifts) and closures (within the same state).
//  As a time-saving heuristic, we also memorize the lookaheads of items
//  of the form
//       A -> u . X v  (X non-terminal and |u| > 0)
//  in hope that it will be needed again.   In general, this seems to be
//  true when the non-terminal X has a lot of different derivation.
//  Of course, this means more space is needed.
//
//  In any case, this still seems to be better than naive algorithms that
//  forward propagate the lookaheads until reaching fix-point.
//////////////////////////////////////////////////////////////////////////////

static void lookback
( BitSet&                        lookaheads, // lookahead sets
  State                                   s, // current state number
  ItemNum                                 n, // the item number
  const Grammar&                          G, // Grammar
  const FirstSet&                         F, // first/null set info
  const LR0&                            lr0, // LR(0) machine
  LHashTable <SI, int>&             visited, // set of visited states
  LHashTable <SI, BitSet * >&      la_table, // already computed lookaheads
  Bool                  cache_result = true  // memorize result?
)
{
  ///////////////////////////////////////////////////////////////////////////
  //  The current item is A -> w X . y
  ///////////////////////////////////////////////////////////////////////////
  const LRItem * item = lr0[n];    // the item

  SI sn = S_I(s,n);

  ///////////////////////////////////////////////////////////////////////////
  // If the lookaheads of this state/item has already been computed,
  // use it and cut short the search.
  ///////////////////////////////////////////////////////////////////////////
  if (cache_result && item->pos > 0 && G.isNonTerminal(item->P[item->pos+1]))
  {
    ////////////////////////////////////////////////////////////////////////
    //  We save only items that predicts a non-terminal
    //  i.e. items of the form
    //     A -> u . X v    where X is a non-terminal and |u| > 0
    ////////////////////////////////////////////////////////////////////////
    Ix ix;
    if ((ix = la_table.lookup(sn)))
    {
      /////////////////////////////////////////////////////////////////////
      // If we have already computed this state/item's lookahead,
      // use it!
      /////////////////////////////////////////////////////////////////////
      const BitSet * la = la_table.value(ix);
      if (la)
      {
        lookaheads.Union(*la);
      }
      return;
    }
    else
    {
      /////////////////////////////////////////////////////////////////////
      // Otherwise, start a new thread starting from this state/item.
      // When it is finished, add the result to our lookahead.
      // This particular s/n result is cached for reuse.
      /////////////////////////////////////////////////////////////////////
      LHashTable <SI, int> new_visited(4);  // set of visited states
      la_table.insert(sn,(BitSet*)0);     // mark it as being computed
      BitSet * new_lookaheads = new (lr0.memOf(), lookaheads.size()) BitSet;
      lookback(*new_lookaheads,s,n,G,F,lr0,new_visited,la_table,false);
      la_table.insert(sn,new_lookaheads); // mark it as computed
      lookaheads.Union(*new_lookaheads);  // add it to the previous lookaheads
      return;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Mark state s with item n as visited
  // so that it won't be revisited again for the computation
  // of state s's lookaheads.
  ///////////////////////////////////////////////////////////////////////////
  visited.insert(sn,0);

  ///////////////////////////////////////////////////////////////////////////
  // The current item is A -> w X . y
  // Look back at items A -> w . X y at all previous states.
  // These are the lookaheads due to a shift operation
  ///////////////////////////////////////////////////////////////////////////
  if (item->pos > 0)
  {
    const SLinkList<State> * pred = lr0.predecessors(s);
    for ( ; pred; pred = pred->tail )
    {
      State s1 = pred->head;  // previous state
      if (! visited.contains(S_I(s1,n-1)))
      {
        lookback(lookaheads,s1,n-1,G,F,lr0,visited,la_table);
      }
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Look at items that predict A within the same state.
  // These are the lookaheads due to a closure operation.
  ///////////////////////////////////////////////////////////////////////////
  {  const ItemSet& items = lr0.state_items(s);
    NonTerminal    A     = item->P[0]; // the lhs non-terminal
    ItemNum i;
    foreach_item (i, items)
    {
      const LRItem * itm = lr0[i];
      if (A == itm->P[itm->pos + 1])
      {
        Symbol Y = itm->P[itm->pos + 2];
        if (G.isTerminal(Y))
        {
          lookaheads.add(Y);
        }
        else if (Y <= Grammar::END_PRODUCTION ||
                 F.first(lookaheads, itm->P + itm->pos + 2))
        {  //
          //  Also try all items that predict A in the same state
          //  i.e.  B -> x . A y  nullable(y)
          //
          if (! visited.contains(S_I(s,i)))
          {
            lookback(lookaheads,s,i,G,F,lr0,visited,la_table);
          }
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor.
//
//     This routine computes the LALR(1) lookahead sets of a grammar.
//  The algorithm used is based on backward lookahead propagation due
//  to DeRemer and Pennello(ACM TOPLAS 1982).
//
//////////////////////////////////////////////////////////////////////////////

LookaheadSets::LookaheadSets
( const Grammar&      g,   // the grammar
  const OpPrecedence& P,   // operator precedence
  LR0&                c,   // the LR(0) finite state automata
  Mem&                m,   // working memory manager
  Bool              //lazy  // should we save unnecessary work?
) : G(g), prec(P), lr0(c), mem(m)
{
  ///////////////////////////////////////////////////////////////////////////
  //  Compute the function first() and nullable()
  ///////////////////////////////////////////////////////////////////////////
  FirstSet firstSet(G, mem);

  ///////////////////////////////////////////////////////////////////////////
  //  Reset error counts
  ///////////////////////////////////////////////////////////////////////////
  shift_reduce_error_count  = 0;
  reduce_reduce_error_count = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate the implementation
  ///////////////////////////////////////////////////////////////////////////
  impl                  = new LookaheadSets_Impl;
  //int max_non_term      = G.max_non_terminal();
  //int number_of_symbols = G.number_of_symbols();

  ///////////////////////////////////////////////////////////////////////////
  //  Compute a mapping from production to rule number
  ///////////////////////////////////////////////////////////////////////////
  {  for (Rule r = 0; r < G.size(); r++)
      impl->rule_map.insert(G[r], r);
  }

  ///////////////////////////////////////////////////////////////////////////
  // Allocate a buffer for marking reduced symbols
  ///////////////////////////////////////////////////////////////////////////
  impl->reduced = (State*)mem.c_alloc(sizeof(State) * G.number_of_symbols());
  impl->slot    = (int*)  mem.c_alloc(sizeof(int) * G.number_of_symbols());

  ///////////////////////////////////////////////////////////////////////////
  //  `reduction_lookaheads' is a hash table mapping a (state/item) pair
  //  to a set of lookahead symbols for a reducing item.
  ///////////////////////////////////////////////////////////////////////////
  LHashTable <SI, BitSet * >& reduction_lookaheads = impl->reduction_lookaheads;

  ///////////////////////////////////////////////////////////////////////////
  //  For each non-terminal A, compute
  //      Union first(P) for all productions A -> P
  ///////////////////////////////////////////////////////////////////////////
  //LHashTable <NonTerminal, BitSet *> first_of_A;
  //{  for (int i = G.size() - 1; i >= 0; i--)
  //   {
  //   }
  //}

  ///////////////////////////////////////////////////////////////////////////
  //  Compute reduction lookaheads for each reducing item of each state.
  //  A reducing item is an item of the form
  //       A -> xyz .
  ///////////////////////////////////////////////////////////////////////////
  {  int   number_of_terminals = G.number_of_terminals();
    LHashTable <SI, int> visited;
    for (int s = lr0.number_of_states() - 1; s >= 0; s--)
    {
      //////////////////////////////////////////////////////////////////////
      //  We can omit computing lookahead infor for a state
      //  with only a single reducing item, like this
      //
      //      A -> xyz .
      //////////////////////////////////////////////////////////////////////
      // if (lazy && lr0.is_singleton_state(s)) continue;
      if (lr0.is_singleton_state(s))
        continue;

      //const ItemSet& item_set       = lr0.state_items(s);
      const SLinkList <ItemNum> * l = lr0.reducing_items(s);

      for ( ; l; l = l->tail )
      {
        ItemNum i = l->head;
        visited.clear();
        BitSet * lookaheads = new (mem, number_of_terminals) BitSet;
        lookback( *lookaheads, s, i, G, firstSet,
                  lr0, visited, reduction_lookaheads );
        reduction_lookaheads.insert(S_I(s,i),lookaheads);
      }
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Clean up properly
  ///////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor
//////////////////////////////////////////////////////////////////////////////

LookaheadSets :: ~LookaheadSets()
{
  delete impl;
}

//////////////////////////////////////////////////////////////////////////////
//  Compute the transition state.
//  Test for shift/reduce, reduce/reduce conflicts and resolve them
//  if possible.
//////////////////////////////////////////////////////////////////////////////

int LookaheadSets::transitions
(State s, Symbol symbols [], State delta[], State& def, std::ostream * log)
{
  const  LHashTable <SI, BitSet * >& LA      = impl->reduction_lookaheads;
  const  SLinkList<ItemNum> * reducing_items = lr0.reducing_items(s);
  const  State * trans                       = lr0.transitions(s);
  State  * reduced                           = impl->reduced;
  int    * slot                              = impl->slot;
  Symbol A;
  int    fan_out = 0;

  ///////////////////////////////////////////////////////////////////////////
  // Default reduction computation.
  // Notice that if a state has one (and only one) reducing item that it
  // will be returned separately from the transition function.
  ///////////////////////////////////////////////////////////////////////////
  Bool  one_reduction = reducing_items && reducing_items->tail == 0;
  State default_reduction = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Compute reductions
  ///////////////////////////////////////////////////////////////////////////
  for ( ; reducing_items; reducing_items = reducing_items->tail)
  {
    ItemNum       i   = reducing_items->head;
    default_reduction = G.makeReduce(impl->rule_map[lr0[i]->P]);
    Ix ix;
    if ((ix = LA.lookup(S_I(s,i))))
    {
      const BitSet& lookaheads = *LA.value(ix);
      foreach_bit(A,lookaheads)
      {
        ShiftReduce sr;
        Bool conflict;

        if (trans[A] != 0)
        {          // shift/reduce conflict found!
          sr = resolve_shift_reduce_conflict(i,A,log);
          conflict = true;
        }
        else if (reduced[A] == s)
        { // reduce/reduce conflict found!
          sr = resolve_reduce_reduce_conflict(i,A,log);
          conflict = true;
        }
        else
        {                     // no error found.
          sr = REDUCE;
          conflict = false;
        }

        if (sr == REDUCE)
        {
          reduced[A] = s;         // mark this symbol as reduced
          if (! one_reduction)
          {
            if (conflict)
            {
              delta  [ slot [A] ] = default_reduction;
            }
            else
            {
              symbols[ fan_out ] = A;
              delta  [ fan_out ] = default_reduction;
              slot   [ A ]       = fan_out;
              fan_out++;
            }
          }
        }
      }
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Compute shifts.  These are all the transitions that occur in the
  //  LR(0) machine that do not occur in the reduced set.
  ///////////////////////////////////////////////////////////////////////////
  for (A = G.max_non_terminal(); A >= 0; A--)
  {
    if (trans[A] && reduced[A] != s)
    {
      symbols[fan_out] = A;
      delta  [fan_out] = trans[A];
      fan_out++;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Return the single reduction if it is there.
  ///////////////////////////////////////////////////////////////////////////
  def = one_reduction ? default_reduction : 0;
  return fan_out;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to log a message on shift/reduce conflict.
//////////////////////////////////////////////////////////////////////////////

static std::ostream&
log_shift_reduce_conflict
( std::ostream& log, const Grammar& G,
  ItemNum i, const LRItem& reducing_item, Terminal A,
  const char * resolved, const char * shift_reduce
)
{
  log << "\tshift/reduce conflict with item {" << i << "} ";
  G.print(log, reducing_item.P[0]);
  log << " -> ";
  G.print(log, reducing_item.P + 1, false);
  log << ". and ";
  G.print(log,A);
  log << " " << resolved << " " << shift_reduce << ".\n";
  return log;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to resolve shift/reduce conflicts using operator precedence
//  information.
//////////////////////////////////////////////////////////////////////////////

ShiftReduce LookaheadSets::resolve_shift_reduce_conflict
( ItemNum i, Terminal A, std::ostream * log)
{
  ///////////////////////////////////////////////////////////////////////////
  //  Check for specific forms of reducing items, like
  //      (a)  E op E .         or
  //      (b)  op E .           or
  //      (c)  E op .
  ///////////////////////////////////////////////////////////////////////////
  const LRItem& reducing_item = *lr0[i];

  ///////////////////////////////////////////////////////////////////////////
  //  First scan backward on the item and find the operator symbol.
  ///////////////////////////////////////////////////////////////////////////
  //Terminal X = Grammar::END_PRODUCTION;
  //{  for (int pos = reducing_item.pos; pos > 0; pos--) {
  //      if (G.isTerminal(reducing_item.P[pos]))
  //         { X = reducing_item.P[pos]; break; }
  //   }
  //}
  // Terminal X = reducing_item.operator_symbol;
  Precedence X_prec = reducing_item.precedence;

  ///////////////////////////////////////////////////////////////////////////
  // Found the sucker, now check on the offending symbol A
  // and resolve our differences.
  ///////////////////////////////////////////////////////////////////////////

  if (X_prec < 10000)
  {
    Precedence A_prec = prec.precedence(A);
    if (X_prec < A_prec)
    {
      /////////////////////////////////////////////////////////////////////
      //  case a:  E X E . A     X < A    resolve as reduce
      /////////////////////////////////////////////////////////////////////
      if (log)
        log_shift_reduce_conflict(*log,G,i,reducing_item,A,"resolved as","reduce");
      return REDUCE;

    }
    else if (X_prec > A_prec)
    {
      /////////////////////////////////////////////////////////////////////
      //  case b:  E X E . A     X > A     resolve as shift
      /////////////////////////////////////////////////////////////////////
      if (log)
        log_shift_reduce_conflict(*log,G,i,reducing_item,A,"resolved as","shift");
      return SHIFT;
    }
  }
  ////////////////////////////////////////////////////////////////////////
  //  case b:  E X E . A     X == A
  //        X is left associative, resolve as reduce
  //        X is right associative, resolve as shift
  //        otherwise it is an error
  ////////////////////////////////////////////////////////////////////////
  switch (X_prec < 10000 ? reducing_item.associativity : OpPrecedence::None)
  {
  case OpPrecedence::Left:
    if (log)
      log_shift_reduce_conflict(*log,G,i,reducing_item,A,"resolved as","reduce(left)");
    return REDUCE;
  case OpPrecedence::Right:
    if (log)
      log_shift_reduce_conflict(*log,G,i,reducing_item,A,"resolved as","shift(right)");
    return SHIFT;
  case OpPrecedence::None:
    // shift/reduce conflict,  resolve as shift
    if (log == 0)
    {
      shift_reduce_error_count++;
    }
    else
    {
      log_shift_reduce_conflict
      (*log,G,i,reducing_item,A,"defaulted to","shift");
    }
    return SHIFT;
  }
  return SHIFT;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to resolve reduce/reduce conflicts using operator precedence
//  information.
//////////////////////////////////////////////////////////////////////////////

ShiftReduce LookaheadSets::resolve_reduce_reduce_conflict
( ItemNum i, Terminal A, std::ostream * log)
{
  if (log)
  {
    const LRItem& reducing_item = *lr0[i];
    *log << "\treduce/reduce conflict with item {" << i << "} ";
    G.print(*log, reducing_item.P[0]);
    *log << " -> ";
    G.print(*log, reducing_item.P + 1, false);
    *log << ". on ";
    G.print(*log,A);
    *log << ".\n";
  }
  else
  {
    reduce_reduce_error_count++;
  }
  return REDUCE;
}

//////////////////////////////////////////////////////////////////////////////
//  Print a report of the lookahead sets
//////////////////////////////////////////////////////////////////////////////

std::ostream& LookaheadSets::print_report
(std::ostream& out, Bool print_closures, Bool print_lookaheads)
{
  const LHashTable <SI, BitSet * >& reduction_lookaheads = impl->reduction_lookaheads;

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate some arrays for temporary use
  ///////////////////////////////////////////////////////////////////////////
  Symbol * symbols = new Symbol [ G.number_of_symbols() ];
  State  * delta   = new State  [ G.number_of_symbols() ];
  {
    for (Symbol A = G.number_of_symbols() - 1; A >= 0; A--)
      impl->reduced[A] = 0;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Print the items (don't bother, it's useless)
  ///////////////////////////////////////////////////////////////////////////
  // out << "Items (" << lr0.number_of_items() << "):\n";
  // for (int i = 0; i < lr0.number_of_items(); i++) {
  //    out << '[' << i << "]\t";
  //    const LRItem * item = lr0[i];
  //    G.print(out, item->pos, item->P) << '\n';
  // }

  ///////////////////////////////////////////////////////////////////////////
  //  Print the states and their corresponding item sets
  ///////////////////////////////////////////////////////////////////////////
  out << "\nStates (" << lr0.number_of_states() << "):\n";
  for (State s = 0; s < lr0.number_of_states(); s++)
  {
    out << '<' << s << ">";
    const ItemSet& items = lr0.state_items(s);
    int i;

    ////////////////////////////////////////////////////////////////////////
    //  Print the items within this state
    ////////////////////////////////////////////////////////////////////////
    foreach_item (i, items)
    {
      const LRItem * item = lr0[i];
      //
      //  Print predicting items only in full listing mode.
      //  The unique start item is immuned to this treatment.
      //
      if (! print_closures                     &&
          item->isPredicting()                 &&
          item->P[1] > Grammar::END_PRODUCTION &&
          item->P[0] != G.start())
        continue;
      G.print(out << '\t', item->pos, item->P);

      //
      // Print the lookahead sets of reducing items if available
      //
      if ( print_lookaheads && item->isReducing())
      {
        Ix ix = reduction_lookaheads.lookup( S_I(s, i) );
        if (ix)
        {
          out << "\t{ ";
          const BitSet& set
            = *reduction_lookaheads.value(ix);
          Symbol X;
          foreach_bit (X, set
                        ) G.print(out, X) << ' ';
          out << "}";
        }
      }
      out << '\n';
    }

    ////////////////////////////////////////////////////////////////////////
    //  Print the transition function from this state.
    ////////////////////////////////////////////////////////////////////////
    out << '\n';
    State reduction;
    int fan_out = transitions(s, symbols, delta, reduction, &out);
    for (int k = fan_out - 1; k >= 0; k--)
    {
      Symbol X = symbols[k];
      State  d = delta[k];
      if (G.isShift(d))
      {
        out << '\t' << std::setw(16);
        G.print(out, X);
        if (G.isTerminal(X))
          out << "\tshift, and ";
        else
          out << "\t";
        out << "goto state <" << d << ">\n";
      }
      else if (G.isShiftReduce(d))
      {
        int r = G.reduceRule(d);
        out << '\t' << std::setw(16);
        G.print(out, X);
        out << "\tshift and reduce using rule {"
        << r << "}\n";
      }
      else if (reduction == 0)
      {
        int r = G.reduceRule(d);
        out << '\t' << std::setw(16);
        G.print(out, X);
        out << "\treduce using rule {" << r << "} (";
        G.print(out, G.lhs(r)) << ')';
        //
        // also print "accept" if we are reducing the start rule
        //
        if (G.lhs(r) == G.start())
          out << " and accept";
        out << "\n";
      }
    }

    ////////////////////////////////////////////////////////////////////////
    // Print default reduction
    ////////////////////////////////////////////////////////////////////////
    if (reduction != 0)
    {
      int r = G.reduceRule(reduction);
      out << '\t' << std::setw(16) << "<default>"
      << "\treduce using rule {" << r << "} (";
      G.print(out, G.lhs(r)) << ')';
      if (G.lhs(r) == G.start())
        out << " and accept";
      out << '\n';
    }
    out << '\n';
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Print other statistics
  ///////////////////////////////////////////////////////////////////////////
  out << "\nNumber of productions              = " << G.size()
  << "\nNumber of terminals                = " << G.number_of_terminals()
  << "\nNumber of non-terminals            = " << G.number_of_non_terminals()
  << "\nNumber of max normal non-terminals = " << G.max_normal_non_terminal()
  << "\nNumber of max non-terminals        = " << G.max_non_terminal()
  << "\nNumber of states                   = " << lr0.number_of_states()
  << "\nNumber of items                    = " << lr0.number_of_items()
  << "\nNumber of shift/reduce conflicts   = " << shift_reduce_conflicts()
  << "\nNumber of reduce/reduce conflicts  = " << reduce_reduce_conflicts()
  << "\nLookaheads table size              = " << impl->reduction_lookaheads.size()
  << "\nRule map size                      = " << impl->rule_map.size()
  << '\n'
  ;

  ///////////////////////////////////////////////////////////////////////////
  //  Clean up properly
  ///////////////////////////////////////////////////////////////////////////
  delete [] symbols;
  delete [] delta;
  return out;
}
