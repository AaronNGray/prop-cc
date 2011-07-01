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

#ifndef compressed_tree_automaton_h
#define compressed_tree_automaton_h

/////////////////////////////////////////////////////////////////////////////
// Class |TreeAutomaton| represents a compressed tree automaton
// using a flattened multidimensional transition table\cite{Chase}.
//
// Three tables are used to represent the transition tables:
// "arity", "base", and "index".  The table "arity" is a mapping
// from functors to their arities.  The table "base" maps each functor
// to the starting offset of the index table.  Each functor |A|'s index table
// is comprised of two components: the first is a list of index tables
// $\mu_Ai$ for each arity $i$; followed by the compressed transition
// table $\theta_A$.   The multidimensional transition table is
// "flattened" into linear form so that multiplication is unnecessary
// when computing the indices.
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/automata/treetab.h>   // tree automata tables
#include <AD/automata/treegram.h>  // tree grammar
#include <AD/automata/sparsdfa.h>  // DFA compression
#include <AD/memory/mem.h>         // memory managers
#include <AD/contain/bitset.h>     // bit sets


/////////////////////////////////////////////////////////////////////////////
//  Class TreeAutomaton is the base class of the tree parser/matcher
//  generators.  Algorithms are based on bottomup techniques, phrased
//  in terms of tree-automata(or equivalently, non-unary multisorted
//  algebra.)
/////////////////////////////////////////////////////////////////////////////

class TreeAutomaton : public TreeTables
{

  TreeAutomaton( const TreeAutomaton&);     // no copy constructor
  void operator = ( const TreeAutomaton&);  // no assignment

public:

  //////////////////////////////////////////////////////////////////////////
  // Make inherited types visible.
  //////////////////////////////////////////////////////////////////////////
  typedef TreeTables         Super;
  typedef Super::Offset      Offset;      // table offsets
  typedef Super::State       State;       // a state in the tree automaton
  typedef Super::Functor     Functor;     // constructor of a term
  typedef Super::Variable    Variable;    // pattern variables
  typedef Super::NonTerminal NonTerminal; // non-terminals
  typedef Super::Cost        Cost;        // reduction cost
  typedef Super::Arity       Arity;       // arity of a functor
  typedef Super::Rule        Rule;        // rule number
  typedef Super::State       Equiv;       // equivalence class

protected:

  //////////////////////////////////////////////////////////////////////////
  // A memory pool
  //////////////////////////////////////////////////////////////////////////
  Mem&                mem;  // internal memory pool
  const TreeGrammar * G;    // supplied tree grammar

  //////////////////////////////////////////////////////////////////////////
  // Uncompressed tables.
  //    The transition map (as per David Chase) for each functor is
  // actually represented by a set of tables:
  //    (1) An index equivalence class map 'mu' for each arity.   I.e. two
  //        states that'll have the same effect on that arity are mapped
  //        into the same equivalence class.
  //    (2) A multidimensional array representing the transition.
  // The transition function for each functor is computed as
  //
  //     f(a_1, ..., a_n) = delta[mu_1[a_1]] ... [mu_n[a_n]]
  //////////////////////////////////////////////////////////////////////////
  State ***           mu;       // mapping from state x functor x arity -> equivclass
  Equiv **            mu_equiv; // mapping from functor x arity -> next equivclass #
  class DeltaTable ** delta;    // transition table is an n-dimensional array
  // indexed by functor.  The actual definition
  // of this array type is hidden in the
  // implementation.
  State *     singleton_delta;  // transition table for unit functors
  int         delta_size;       // size of this table.

  //////////////////////////////////////////////////////////////////////////
  // Tables
  //////////////////////////////////////////////////////////////////////////
  Arity  *  arity;         // functor to arity mapping
  BitSet ** accept;        // state -> accepted rules set mapping
  Rule   *  accept1;       // state -> *first* accepted rule mapping
  Cost   *  accept1_cost;  // state -> *first* minimal cost rule mapping
  Offset *  accept_base;   // state -> accept offset
  Rule   *  accept_vector; // offset -> accept vector
  int       accept_vector_size;   // size of the accept vector

  //////////////////////////////////////////////////////////////////////////
  // Flags to keep track of which things are used
  //////////////////////////////////////////////////////////////////////////
  Bool mu_used, mu_index_used, accept_used, accept_bitmap_used, accept1_used;

  //////////////////////////////////////////////////////////////////////////
  // Sizes of these tables
  //////////////////////////////////////////////////////////////////////////
  int arity_size;       // size of the arity table
  int max_state;        // current maximum state

  //////////////////////////////////////////////////////////////////////////
  // Compressed tables
  //////////////////////////////////////////////////////////////////////////
  SparseDFA dfa_compiler;             // DFA compression object
  int **    mu_index;                 // mapping from functor x arity -> compressed index
  int       total_index_entries;      // size of all index maps together
  int       non_error_index_entries;  // size of all non-empty index maps

  //////////////////////////////////////////////////////////////////////////
  // Error checking;
  //////////////////////////////////////////////////////////////////////////
  Bool exhaustive;   // set of patterns are exhaustive?

  //////////////////////////////////////////////////////////////////////////
  // Others
  //////////////////////////////////////////////////////////////////////////
  int state_count;      // number of states

  //////////////////////////////////////////////////////////////////////////
  // State expansion
  //////////////////////////////////////////////////////////////////////////
  virtual void grow_states( int increment);

public:

  //////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  //////////////////////////////////////////////////////////////////////////
  TreeAutomaton( Mem& );
  virtual ~TreeAutomaton();

  //////////////////////////////////////////////////////////////////////////
  // Table compilation
  //////////////////////////////////////////////////////////////////////////
  virtual void compile( TreeGrammar&);
  virtual void compile_compression_index ();

  //////////////////////////////////////////////////////////////////////////
  // Selectors
  //////////////////////////////////////////////////////////////////////////

  inline int number_of_states() const
  {
    return state_count;
  }

  inline Arity arity_of( Functor f) const
  {
    return arity[f];
  }

  inline int index_range( Functor f, Arity i) const
  {
    return mu_equiv[f][i];
  }

  inline Equiv index_map( Functor f, Arity i, State s) const
  {
    return mu[s][f][i];
  }

  State get_delta( Functor f, const int []) const;

  inline const BitSet& accept_rules( State s) const
  {
    return *accept[s];
  }

  inline BitSet& accept_rules( State s)
  {
    return *accept[s];
  }

  inline Rule accept1_rule( State s) const
  {
    return accept1[s];
  }

  inline Bool is_accept_state( State s) const
  {
    return accept1[s] >= 0;
  }

  inline Cost min_accept_cost( State s) const
  {
    return accept1_cost[s];
  }

  inline Bool is_exhaustive () const
  {
    return exhaustive;
  }

  //////////////////////////////////////////////////////////////////////////
  // Methods to add a new state.
  //////////////////////////////////////////////////////////////////////////

  void new_state(State);

  inline void add_mu( Functor f, int i, State s0, State s1)
  {
    if (s0 > s1)
      mu[s0][f][i] = mu[s1][f][i];
    else
      mu[s0][f][i] = mu_equiv[f][i]++;
  }

  inline void add_delta( Functor f, State s)
  {
    singleton_delta[f] = s;
  }

  void add_delta( Functor, const int [], State);

  inline void set_accept1( State s, Rule r)
  {
    accept1[s] = r;
  }

  inline void set_accept1( State s, Rule r, Cost c)
  {
    accept1[s] = r;
    accept1_cost[s] = c;
  }

  //////////////////////////////////////////////////////////////////////////
  //  Methods dealing with mu-compression.
  //////////////////////////////////////////////////////////////////////////
  inline int compressed_index( Functor f, Arity i) const
  {
    return mu_index[f][i];
  }

  inline Offset compressed_offset( Functor f, Arity i) const
  {
    return dfa_compiler.state_offset( mu_index[f][i]);
  }

  virtual double compression_rate() const;

  //////////////////////////////////////////////////////////////////////////
  // Code emission methods.
  //    gen_code  -- generate compressed tables.
  //    gen_index -- generate index table for one arity of a functor.
  //    gen_theta -- generate transition table for one functor.
  //////////////////////////////////////////////////////////////////////////

  const char * get_state_type() const;
  const char * get_rule_type() const;
  virtual std::ostream& gen_index( std::ostream&, Functor, Arity, const char []) const;
  virtual std::ostream& gen_theta( std::ostream&, Functor, const char []) const;
  virtual std::ostream& gen_accept( std::ostream&, const char name[]) const;
  virtual std::ostream& gen_bitmap_accept( std::ostream&, const char name[]) const;
  virtual std::ostream& gen_accept1( std::ostream&, const char name[]) const;
  virtual std::ostream& gen_compressed_index( std::ostream&, const char name[]) const;

  //////////////////////////////////////////////////////////////////////////
  // Advance one state within the tree automaton.
  //    The first go() function is an optimized form for a unit functor--
  // i.e. a functor with 0 arity.  The second go() function is the general
  // form which looks up all three tables.
  //////////////////////////////////////////////////////////////////////////

  inline State go(Functor f) const
  {
    return singleton_delta[f];
  }

  //////////////////////////////////////////////////////////////////////////
  //  Method for printing a report
  //////////////////////////////////////////////////////////////////////////
  virtual std::ostream& print_report( std::ostream&) const;
  virtual std::ostream& print_state( std::ostream&, State) const;

  //////////////////////////////////////////////////////////////////////////
  //  Name of algorithm
  //////////////////////////////////////////////////////////////////////////
  virtual const char* algorithm() const = 0;

protected:
  virtual void compute_accept_tables();
};

#endif
