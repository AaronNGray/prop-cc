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

//////////////////////////////////////////////////////////////////////////////
//  In the following we'll implement a bottom up rewrite system (BURS)
//  generator using Proebsting's algorithm(see. PLDI '92).
//  Our implementation is rather by the book, aside from the use of
//  slightly different data structures.
//
//  Here are some of the data structures that we'll be using
//
//  VarArray<T>      --- variable sized array that grows itself automatically.
//  LHashTable<K,V>  --- Hash table with linear probing.
//  BURS_Item        --- an item in the tree grammar.
//  BURS_ItemSet     --- a set of items.
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#define TreeGrammar_Iterators
#include <AD/rewrite/burs_gen.h>   // the BURS generator definition
#include <AD/rewrite/b_items.h>    // the BURS item sets
#include <AD/rewrite/b_rules.h>    // the BURS rule set
#include <AD/contain/vararray.h>   // dynamic arrays
#include <AD/contain/slnklist.h>   // very simple singly linked list
#include <AD/hash/lhash.h>         // linear probing hash tables


//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible for our use.
//////////////////////////////////////////////////////////////////////////////

typedef BURS_Gen::State              State;          // states in tree automata
typedef BURS_Gen::Functor            Functor;        // functors
typedef BURS_Gen::NonTerminal        NonTerminal;    // nonterminals
typedef BURS_Gen::Arity              Arity;          // functor arities
typedef BURS_Gen::Rule               Rule;           // reduction rules
typedef BURS_Gen::Cost               Cost;           // reduction cost
typedef BURS_ItemSet::NonTerminalSet NonTerminalSet; // a set of non-terminals
typedef BURS_RuleSet::Reduction      Reduction;      // reduction rule
typedef BURS_RuleSet::ReductionList  ReductionList;  // a list of reductions
typedef SLinkList<State>             Reps;           // representer list

//////////////////////////////////////////////////////////////////////////////
//  Internal representation of class BURS_Gen
//////////////////////////////////////////////////////////////////////////////

class BURS_Generator
{

  BURS_Generator(const BURS_Generator&);   // no copy constructor
  void operator = (const BURS_Generator&); // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Internal data structures.
  ///////////////////////////////////////////////////////////////////////////

private:
  Mem&                               mem;       // The memory pool
  const TreeGrammar&                 G;         // The tree grammar
  const BURS_RuleSet                 R;         // The rule set
  BURS_Gen&                          gen;       // The BURS generator
  VarArray<const BURS_ItemSet *>     states;    // State -> BURS_ItemSet
  LHashTable<BURS_ItemSet *, State>  state_map; // BURS_ItemSet -> State
  NonTerminalSet **                  closure;   // NonTerminal -> NonTerminalSet
  NonTerminalSet ***                 proj;      // Functor x Arity -> NonTerminalSet
  State                      number_of_states;  // number of states
  int                 number_of_non_terminals;  // number of non-terminals
  Reps ***                       representers;  // Functor x Arity -> Reps
  BURS_ItemSet *                     item_set;  // current item set
  BURS_ItemSet *                    delta_set;  // current delta set
  int                             inputs[256];  // current input states
  int                               mu_s[256];  // current input mu
  Bool                               complete;  // rules are complete?

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  BURS_Generator(Mem& m, const TreeGrammar& g, BURS_Gen& gn)
      : mem(m),
      G(g),
      R(m,g),
      gen(gn),
      state_map(4097,0.4),
      number_of_states(0),
      number_of_non_terminals(R.number_of_non_terminals()),
      item_set(0),
      delta_set(0)
  {}
  ~BURS_Generator()
  {}

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for table generation.
  ///////////////////////////////////////////////////////////////////////////

  void compute_closures        ();
  void compute_projections     ();
  void allocate_representers   ();
  void compute_closure         ( BURS_ItemSet& );
  void compute_projection      ( BURS_ItemSet&, Functor, Arity, State);
  void compute_accept_rules    ( State, const BURS_ItemSet& );
  void compute_leaf_states     ();
  void compute_non_leaf_states ();
  void compute_transitions     (State);
  void compute_transitions     (Functor, Arity, Arity, Arity);
  void compute_delta           (Functor, Arity, Arity);
  Cost triangular_cost         (Functor, Functor) const;
  void trim                    ( BURS_ItemSet& );

  ///////////////////////////////////////////////////////////////////////////
  //  Check for completeness
  ///////////////////////////////////////////////////////////////////////////

  inline Bool is_complete() const
  {
    return complete;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for printing a report
  ///////////////////////////////////////////////////////////////////////////
  std::ostream& print( std::ostream&, const BURS_ItemSet&) const;
  friend std::ostream& operator << (std::ostream&, const BURS_Generator&);
  std::ostream& print_state( std::ostream&, State) const;
};

//////////////////////////////////////////////////////////////////////////////
//  Method to compute closures on all nonterminals.
//  i.e.  for each non-terminal X, compute closure(X).
//  closure(X) = { X } + { A | A -> X in G }
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_closures()
{
  ///////////////////////////////////////////////////////////////////////////
  //  First, allocate the closure table.
  //  One for each non-terminal in the grammar.
  ///////////////////////////////////////////////////////////////////////////
  {
    closure = (NonTerminalSet **)
               mem.c_alloc(sizeof(NonTerminalSet *) * number_of_non_terminals);
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Now, compute the non-terminals closure iteratively over the chain rules
  //  until the least fixed point is reached.
  ///////////////////////////////////////////////////////////////////////////
  {
    Bool changed;
    do
    {
      changed = false;
      for (int r = R.number_of_chain_rules() - 1; r >= 0; r--)
      {
        NonTerminal lhs = R.chain_rule(r).lhs;
        NonTerminal rhs = R.chain_rule(r).rhs;
        if (closure[rhs] == 0)
        {
          closure[rhs] = new (mem, number_of_non_terminals) NonTerminalSet;
          closure[rhs]->add
          (0);   // the wild card
          closure[rhs]->add
          (rhs); // and itself (duh!)
        }
        if (closure[lhs])
        {
          if (closure[rhs]->Union_if_changed(*closure[lhs]))
            changed = true;
        }
        else
        {
          if (closure[rhs]->add_if_changed(lhs))
            changed = true;
        }
      }
    }
    while (changed);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute projections on all arities of all functors.
//  For each functor f and arity i, compute
//       closure( { x_i | f ( ...., x_i, .... ) } )
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_projections()
{
  ///////////////////////////////////////////////////////////////////////////
  //  First, allocate the projection table.
  ///////////////////////////////////////////////////////////////////////////

  proj = (NonTerminalSet ***)
         mem.c_alloc(sizeof(NonTerminalSet **) * (G.max_functor() + 1));

  foreach_non_unit_functor (f,G)
  {
    proj[f] = (NonTerminalSet**)
              mem.c_alloc(sizeof(NonTerminalSet*) * G.arity(f));

    foreach_arity (i, f, G)
    {
      proj[f][i] = new(mem,number_of_non_terminals) NonTerminalSet;
      proj[f][i]->add(0);
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Now compute the projection map.
  ///////////////////////////////////////////////////////////////////////////

  for (int r = R.number_of_reductions() - 1; r >= 0; r--)
  {
    Functor f = R.reduction(r).f;
    for (int i = R.reduction(r).n - 1; i >= 0; i--)
    {
      NonTerminal n = R.reduction(r).rhs[i];
      //
      //  We may have to take the closure of a non-terminal.
      //  Notice that if the non-terminal 'n' is in the projection, we
      //  don't bother to take the closure of that since it must be already
      //  in the set.
      //
      if (closure[n] && ! proj[f][i]->contains(n))
        proj[f][i]->Union (*closure[n]);
      else
        proj[f][i]->add
        (n);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to allocate storage for representer lists, one for
//  each non-unit functor at each arity position.
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::allocate_representers()
{
  representers = (Reps ***)mem.c_alloc(sizeof(Reps**) * (G.max_functor() + 1));

  foreach_non_unit_functor (f,G)
  {
    representers[f] = (Reps**)mem.c_alloc(sizeof(Reps*) * G.arity(f));
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the closure of a state and its least cost reduction
//  using a dynamic programming algorithm.
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_closure( register BURS_ItemSet& state)
{
  Bool changed;
  do
  {
    changed = false;
    for (int r = 0; r < R.number_of_chain_rules(); r++)
    {
      ////////////////////////////////////////////////////////////////////
      // Given a chain rule ``A -> B'' with cost c, we try to
      // find a less expensive reduction going back to A from B.
      ////////////////////////////////////////////////////////////////////
      NonTerminal A = R.chain_rule(r).lhs;
      NonTerminal B = R.chain_rule(r).rhs;
      Cost cost = R.chain_rule(r).cost + state[ B ].cost;
      if (cost < state[ A ].cost)
      {
        state[ A ].cost = cost;
        state[ A ].rule = R.chain_rule(r).rule;
        changed = true;
      }
    }
  }
  while (changed);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute a projection on a state
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_projection
( register BURS_ItemSet& projected, Functor f, Arity i, State s)
{
  register const BURS_ItemSet& state = *states[s];
  register const NonTerminalSet& set = *proj[f][i];

  for (register NonTerminal n = state.size() - 1; n >= 0; n--)
  {
    if (set[n])
      projected[n] = state[n];
    else
      projected[n].cost = BURS_ItemSet::infinite_cost;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the set of accept rules for each state
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_accept_rules( State s, const BURS_ItemSet& items)
{
  Rule min_cost_rule  = G.size();  // first rule with the minimal cost
  Cost min_cost       = BURS_ItemSet::infinite_cost;

  BitSet& rules = gen.accept_rules(s);
  for (register NonTerminal A = items.size() - 1; A > 0; A--)
  {
    if (items[A].cost != BURS_ItemSet::infinite_cost &&
        items[A].rule >= 0)
    {
      rules.add (items[A].rule);
      if (items[A].cost <= min_cost && items[A].rule < min_cost_rule)
      {
        min_cost_rule  = items[A].rule;
        min_cost       = items[A].cost;
      }
    }
  }

  if (min_cost_rule == G.size())
    min_cost_rule = -1;

  gen.set_accept1(s, min_cost_rule, min_cost);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to generate the initial leaf states.
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_leaf_states()
{
  ///////////////////////////////////////////////////////////////////////////
  //  Enter the default error state
  ///////////////////////////////////////////////////////////////////////////
  {
    BURS_ItemSet * error_state = new (mem, number_of_non_terminals) BURS_ItemSet;
    gen.new_state(number_of_states);
    compute_closure(*error_state);
    states[ number_of_states ] = error_state;
    state_map.insert(error_state, number_of_states);
    compute_accept_rules(number_of_states, *error_state);
    number_of_states++;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Generate all states corresponding to the unit functors
  //  (i.e. leaves) in the tree grammar.
  ///////////////////////////////////////////////////////////////////////////
  foreach_unit_functor (f, G)
  {
    gen.new_state(number_of_states);
    BURS_ItemSet * s = new (mem, number_of_non_terminals) BURS_ItemSet;
    Bool found = false;
    for (int r = R.number_of_leaf_reductions() - 1; r >= 0; r--)
    {
      if (R.leaf(r).f != f)
        continue;
      NonTerminal lhs = R.leaf(r).lhs;
      (*s)[lhs].cost = R.leaf(r).cost;
      (*s)[lhs].rule = R.leaf(r).rule;
      found = true;
    }
    if (found)
    {
      s->normalise_costs();
      compute_closure(*s);
      states[ number_of_states ] = s;
      state_map.insert(s, number_of_states);
      gen.add_delta(f, number_of_states);
      compute_accept_rules(number_of_states, *s);
      number_of_states++;
    }
    else
      gen.add_delta(f, 0);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the rest of the states
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_non_leaf_states()
{
  ///////////////////////////////////////////////////////////////////////////
  //  First, compute the set of states.
  ///////////////////////////////////////////////////////////////////////////
  for (State s = 0; s < number_of_states; s++)
  {
    // std::cerr << "At state " << s << ":\t"; print(std::cerr,*states[s]);
    compute_transitions(s);
  }
  ///////////////////////////////////////////////////////////////////////////
  //  Then check for completeness: i.e. there isn't an empty state item set.
  ///////////////////////////////////////////////////////////////////////////
  // BURS_ItemSet * empty_set = new (mem, number_of_non_terminals) BURS_ItemSet;
  // complete = ! state_map.contains(empty_set);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the transitions from a state.
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_transitions( State s)
{
  // Lookup the item set for the current state
  // const BURS_ItemSet& state = *states[s];

  //////////////////////////////////////////////////////////////////////////
  // Allocate a new item set if we don't already have one.
  //////////////////////////////////////////////////////////////////////////

  if (item_set == 0)
    item_set = new (mem, number_of_non_terminals) BURS_ItemSet;
  else
    item_set->clear();

  foreach_functor (f, G)
  {
    int n = G.arity(f);   // arity of f
    for (int i = 0; i < n; i++)
    {
      ////////////////////////////////////////////////////////////////////
      // Compute the projection on functor f on arity i
      ////////////////////////////////////////////////////////////////////
      compute_projection(*item_set, f, i, s);

      ////////////////////////////////////////////////////////////////////
      // Update the representer states if the projection is
      // not found to be in our list.
      ////////////////////////////////////////////////////////////////////
      State d = s;  // delta state
      Ix old = state_map.lookup(item_set);
      // if (old == 0 || (d = state_map.value(old)) >= s) {
      if (old == 0 || (d = state_map.value(old)) == s)
      {
        gen.add_mu(f, i, s, d);
        //
        // This is an interesting state; update representer list
        // and compute transition info.
        //
        representers[f][i] = new (mem, s, representers[f][i]) Reps;

        inputs[i] = s;                      // input state of arity i
        mu_s[i]   = gen.index_map(f, i, s); // input state of arity i
        compute_transitions(f, i, 0, n);
      }
      else
        gen.add_mu(f, i, s, d);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the transitions of a functor on a state
//  when one of the arity is fixed.
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_transitions
( Functor        f,        // functor f
  Arity          fixed,    // arity of f to be fixed
  Arity          i,        // arity index from 0 to n - 1
  Arity          n         // arity of f
)
{
  if (i == fixed)
    i++;

  if (i < n)
  {
    for (Reps * l = representers[f][i]; l; l = l->tail)
    {
      mu_s[i] = gen.index_map( f, i, inputs[i] = l->head);
      compute_transitions( f, fixed, i + 1, n);
    }
  }
  else
    compute_delta( f, fixed, n);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the transition state of one input configuration
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::compute_delta( Functor f, Arity fixed, Arity n)
{
  if (delta_set)
    delta_set->clear();
  else
    delta_set = new (mem, number_of_non_terminals) BURS_ItemSet;

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the transition state of f, and its associated cost.
  ///////////////////////////////////////////////////////////////////////////

  for (const ReductionList * rs = R.reductions_of(f); rs; rs = rs->tail)
  {
    const Reduction * r = rs->head;
    long cost = r->cost + (*item_set)[ r->rhs[fixed]].cost;
    for (int i = 0; i < n; i++)
    {
      if (i != fixed)
          cost += (*states[ inputs[i] ])[r->rhs[i]].cost;
    }
    if (cost < (*delta_set)[r->lhs].cost)
    {
      (*delta_set)[r->lhs].cost = cost;
      (*delta_set)[r->lhs].rule = r->rule;
    }
  }
  // std::cerr << "Delta (" << f << ", " << n << "):\t"; print(std::cerr,*delta_set);

  ///////////////////////////////////////////////////////////////////////////
  //  Use triangle trimming to eliminate unnecessary non-terminals.
  //  Normalise the cost.
  ///////////////////////////////////////////////////////////////////////////

  trim( *delta_set );                     // trim unnecessary non-terminals
  delta_set->normalise_costs();           // normalise costs
  // std::cerr << "Delta[1] (" << f << ", " << n << "):\t"; print(std::cerr,*delta_set);
  compute_closure( *delta_set );          // compute closure
  // std::cerr << "Delta[2] (" << f << ", " << n << "):\t"; print(std::cerr,*delta_set);
  Ix found = state_map.lookup(delta_set);
  State d;

  ///////////////////////////////////////////////////////////////////////////
  //  If the delta set is not found in the state map, we have a new state
  //  to consider.
  ///////////////////////////////////////////////////////////////////////////

  if ( !found)
  {
    // compute_closure( *delta_set );
    gen.new_state (number_of_states);
    compute_accept_rules(number_of_states, *delta_set);
    states[ number_of_states ] = delta_set;
    state_map.insert(delta_set, number_of_states);
    d = number_of_states++;
    // std::cerr << "State " << d << ":\t"; print(std::cerr,*delta_set);
    delta_set = 0;  // remove it, so that we'll won't accidentally reuse it
  }
  else
    d = state_map.value( found);

  ///////////////////////////////////////////////////////////////////////////
  // Update the delta table
  ///////////////////////////////////////////////////////////////////////////
  gen.add_delta( f, mu_s, d);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to trim an item set to remove unnecessary non-terminals.
//////////////////////////////////////////////////////////////////////////////

void BURS_Generator::trim( BURS_ItemSet& /*set*/)
{  // optimization (currently unimplemented)
}

//////////////////////////////////////////////////////////////////////////////
//  Method to print an item set.
//  e.g. in format such as:
//    [ A : 1, B : 2, C : 5 ]
//////////////////////////////////////////////////////////////////////////////

std::ostream& BURS_Generator::print( std::ostream& f, const BURS_ItemSet& set) const
{
  Bool first = true;
  for (NonTerminal n = 0; n < set.size(); n++)
  {
    if (set
        [n].cost != BURS_ItemSet::infinite_cost)
    {
      if (! first)
        f << '\t';
      R.print(f,n);
      if (set
          [n].cost > 0) f << "\t(cost " << set
          [n].cost << ")";
      if (n > 0 && set
            [n].rule >= 0) f << "\t[rule " << set
            [n].rule << "]";
      f << "\n";
      first = false;
    }
  }
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to print a report on a stream.
//////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, const BURS_Generator& g)
{
  // Print the set of states
  f << "Canonical rules:\n" << g.R << '\n'
  << "States:\n";
  for (State s = 0; s < g.number_of_states; s++)
  {
    g.print_state(f,s);
  }
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to print a state on a stream.
//////////////////////////////////////////////////////////////////////////////

std::ostream& BURS_Generator::print_state( std::ostream& f, State s) const
{
  f << '[' << s << "]\t";
  print(f,*states[s]);
  if (gen.is_accept_state(s))
    f << "\t[accept " << gen.accept1_rule(s) << "]\n";
  return f;
}

//////////////////////////////////////////////////////////////////////////////
// In the following section we'll implement the class BURS_Gen.
// Methods within this class just invoke BURS_Generator's methods
// to do the dirty work.  Basically this class just ties all the
// methods things together and check for errors.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////

BURS_Gen:: BURS_Gen( Mem& m ) : Super(m), impl(0)
{}

BURS_Gen:: BURS_Gen( Mem& m, TreeGrammar& g) : Super(m), impl(0)
{
  compile(g);
}

BURS_Gen::~BURS_Gen()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to clean up by deleting the internal representation.
//////////////////////////////////////////////////////////////////////////////

void BURS_Gen::clear()
{
  delete impl;
  impl = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compile a tree grammar
//////////////////////////////////////////////////////////////////////////////

void BURS_Gen::compile(TreeGrammar& g)
{
  ///////////////////////////////////////////////////////////////////////////
  //  Create a new implementation of the generator.
  //  Make sure that if compile() is used again we'll recycle the old
  //  implementation..
  ///////////////////////////////////////////////////////////////////////////

  clear();
  impl = new BURS_Generator( mem, g, *this);

  ///////////////////////////////////////////////////////////////////////////
  //  Call our super class to so that it can do its own work generating
  //  the arity and other tables.
  ///////////////////////////////////////////////////////////////////////////

  Super::compile(g);

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the states and generate the tables.
  ///////////////////////////////////////////////////////////////////////////

  impl->compute_closures();        // compute closures of all non-terminals
  impl->compute_projections();     // compute projections of all functors
  impl->allocate_representers();   // allocate the representer lists
  impl->compute_leaf_states();     // compute the leaf states
  impl->compute_non_leaf_states(); // now compute the rest
}

//////////////////////////////////////////////////////////////////////////////
//  Method to check whether the set of rewrite rules is complete.
//////////////////////////////////////////////////////////////////////////////

Bool BURS_Gen::is_complete() const
{
  return impl && impl->is_complete();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to generate a new report
//////////////////////////////////////////////////////////////////////////////

std::ostream& BURS_Gen::print_report( std::ostream& log) const
{
  if (impl)
  {
    Super::print_report(log);
    log << *impl;
  }
  return log;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to generate a state
//////////////////////////////////////////////////////////////////////////////

std::ostream& BURS_Gen::print_state( std::ostream& log, State s) const
{
  if (impl)
    impl->print_state(log,s);
  return log;
}

//////////////////////////////////////////////////////////////////////////////
//  Algorithm name
//////////////////////////////////////////////////////////////////////////////

const char * BURS_Gen::algorithm () const
{
  return "BURS_Gen";
}
