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

#include <iostream>
#include <assert.h>
#include <AD/automata/treeauto.h>  // tree automaton definitions
#include <AD/automata/gentable.h>  // table printer
#include <AD/contain/n_array.h>    // multi-arrays

//////////////////////////////////////////////////////////////////////////////
//
//  Make hidden types visible
//
//////////////////////////////////////////////////////////////////////////////

typedef TreeAutomaton::Functor Functor;
typedef TreeAutomaton::Arity   Arity;
typedef TreeAutomaton::State   State;
typedef TreeAutomaton::Offset  Offset;

//////////////////////////////////////////////////////////////////////////////
//
//  The delta table for one functor is actually implemented as
//  a multi-array, whose definition is in <AD/contain/n_array.h>.
//  We'll use inheritance for renaming.
//
//////////////////////////////////////////////////////////////////////////////

class DeltaTable : public MultiArray<State>
{
public:
  DeltaTable(int arity) : MultiArray<State>(arity,(State)0)
  {}
}
;

//////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
//////////////////////////////////////////////////////////////////////////////

TreeAutomaton:: TreeAutomaton(Mem& m)
    : mem(m), arity(0), mu(0), mu_equiv(0), delta(0),
    accept(0), accept1(0), accept1_cost(0),
    accept_base(0), accept_vector(0), accept_vector_size(0),
    mu_used(false), mu_index_used(false), accept_used(false),
    accept_bitmap_used(false), accept1_used(false),
    G(0), singleton_delta(0), delta_size(0), arity_size(0),
    mu_index(0), exhaustive(true)
{}

TreeAutomaton::~TreeAutomaton()
{
  for (int i = 0; i < delta_size; i++)
    delete (delta[i]);
  delete [] accept;
  delete [] accept1;
  delete [] accept1_cost;
  delete [] accept_base;
  delete [] accept_vector;
  delete [] mu;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to allocate the tables given a tree grammar.
//
//////////////////////////////////////////////////////////////////////////////

void TreeAutomaton::compile( TreeGrammar& g)
{
  ///////////////////////////////////////////////////////////////////////////
  //  Compute the arity of each functor.
  ///////////////////////////////////////////////////////////////////////////
  arity    = (Arity*) mem.c_alloc(sizeof(Arity) * (arity_size = g.max_functor() + 1));
  mu_equiv = (Equiv**)mem.c_alloc((g.max_functor() + 1) * sizeof(Equiv*));
  {
    for (Functor f = g.min_functor(); f <= g.max_functor(); f++)
    {
      arity[f]    = g.arity(f);
      mu_equiv[f] = (Equiv*)mem.c_alloc(g.arity(f) * sizeof(Equiv));
      // for (int i = g.arity(f) - 1; i >= 0; i--)
      //    mu_equiv[f][i] = 1;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate the delta map for non-unit functors.
  ///////////////////////////////////////////////////////////////////////////
  delta = (DeltaTable **)mem.c_alloc(sizeof(DeltaTable*) * (delta_size = g.max_functor() + 1));
  {
    for (Functor f = g.min_functor(); f <= g.max_functor(); f++)
    {
      if (arity[f] == 0)
        continue;
      delta[f] = new DeltaTable(arity[f]);
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate the delta map for unit functors.
  ///////////////////////////////////////////////////////////////////////////
  singleton_delta = (State*)mem.c_alloc(sizeof(State) * delta_size);

  ///////////////////////////////////////////////////////////////////////////
  //  Set the number of states to zero initially.
  ///////////////////////////////////////////////////////////////////////////
  state_count = max_state = 0;
  G = &g;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to increase the number of states
//
//////////////////////////////////////////////////////////////////////////////
void TreeAutomaton::grow_states( int increment)
{
  int s;

  // grow the mu[] array
  {  State *** new_mu = new State ** [ max_state + increment ];
    for (s = 0; s < max_state; s++)
      new_mu[s] = mu[s];
    for ( ; s < max_state + increment; s++)
    {
      new_mu[s] = (State**)mem.c_alloc(
                    sizeof(State*) * (G->max_functor() + 1));
      for (Functor f = G->min_functor(); f <= G->max_functor(); f++)
      {
        new_mu[s][f] = (State*)mem.c_alloc(sizeof(State) * G->arity(f));
      }
    }
    delete [] mu;
    mu = new_mu;
  }

  // grow the accept[] array
  {  BitSet ** new_accept = new BitSet * [ max_state + increment ];
    for (s = 0; s < max_state; s++)
      new_accept[s] = accept[s];
    for ( ; s < max_state + increment; s++)
    {
      new_accept[s] = new (mem, G->size()) BitSet;
    }
    delete [] accept;
    accept = new_accept;
  }

  // grow the accept1[] array
  {  Rule * new_accept1 = new Rule [ max_state + increment ];
    for (s = 0; s < max_state; s++)
      new_accept1[s] = accept1[s];
    for ( ; s < max_state + increment; s++)
      new_accept1[s] = -1;
    delete [] accept1;
    accept1 = new_accept1;
  }

  // grow the accept1_cost[] array
  {  Cost * new_accept1_cost = new Cost [ max_state + increment ];
    for (s = 0; s < max_state; s++)
      new_accept1_cost[s] = accept1_cost[s];
    for ( ; s < max_state + increment; s++)
      new_accept1_cost[s] = 0;
    delete [] accept1_cost;
    accept1_cost = new_accept1_cost;
  }

  // update the state limit
  max_state += increment;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to add a new state to the tables
//
//////////////////////////////////////////////////////////////////////////////

void TreeAutomaton::new_state( State s)
{
  if (s >= max_state)
  {
    int increment = 2 * (max_state + 1) - s;
    if (increment < 256)
      increment = 256;
    grow_states(increment);
  }
  if (s >= state_count)
    state_count = s + 1;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to add a transition to the automaton.
//
//////////////////////////////////////////////////////////////////////////////

void TreeAutomaton::add_delta( Functor f, const int inputs[], State s)
{
  (*delta[f])[inputs] = s;
  singleton_delta[f]  = s;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to return a transition of the automaton.
//
//////////////////////////////////////////////////////////////////////////////

State TreeAutomaton::get_delta( Functor f, const int inputs[]) const
{
  return arity[f] == 0 ? singleton_delta[f] : (*delta[f])[inputs];
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the accept table in
//
//////////////////////////////////////////////////////////////////////////////

void TreeAutomaton::compute_accept_tables()
{
  if (accept_base)
    return; // already computed.

  // Allocate the base
  accept_base = new Offset [ number_of_states() ];

  // Compute the length of the vector
  int vector_len = number_of_states();
  {
    for (State s = 0; s < number_of_states(); s++)
      vector_len += accept_rules(s).count();
  }
  // Allocate the vector
  accept_vector_size = vector_len;
  accept_vector      = new Rule [vector_len];

  // Copy the vectors
  {  Offset offset = 0;
    for (State s = 0; s < number_of_states(); s++)
    {
      if (offset > 0 && accept1_rule(s) < 0) // no accept rules
      {  accept_base[s] = offset-1;
      } else                        // some accept rules
      {
        accept_base[s] = offset;
        const BitSet& set
          = accept_rules(s);
        int i;
        foreach_bit_fast (i, set
                           )
        {
          accept_vector[offset++] = i;
        }
        accept_vector[offset++] = -1; // sentinel
      }
    }
    assert(offset <= accept_vector_size);
    accept_vector_size = offset;
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code for the accept table.
//  All accepted rules are printed in base/vector format in two arrays.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& TreeAutomaton::gen_accept( std::ostream& out, const char name[]) const
{
  TablePrinter P;
  ((TreeAutomaton *)this)->compute_accept_tables();
  P.print(out, (const char *)accept_base,
          number_of_states(), sizeof(Offset),
          "static const TreeTables::Offset ", name, "accept_base");
  out << "static const ";
  P.print(out, (const char *)accept_vector,
          accept_vector_size, sizeof(Rule),
          get_rule_type(),
          name, "accept_vector");
  ((TreeAutomaton *)this)->accept_used = true;
  return out;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Another method to generate code for the accept table.
//  The first accepted rules (or -1) are printed in array format.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& TreeAutomaton::gen_accept1( std::ostream& out, const char name[]) const
{
  out << "static const " << get_rule_type() << name
  << "_accept1[" << number_of_states() << "] = \n{  ";
  Bool comma = false;
  for (State s = 0; s < number_of_states(); s++)
  {
    if (comma)
      out << ", ";
    if (s != 0 && s % 16 == 0)
      out << "\n  ";
    out << accept1[s];
    comma = true;
  }
  ((TreeAutomaton*)this)->accept1_used = true;
  return out << "\n};\n";
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code for the accept table.
//  All accepted rules are printed in bitmap format.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& TreeAutomaton::gen_bitmap_accept( std::ostream& out, const char name[]) const
{
  int bytes = (number_of_states() + sizeof(unsigned char) * 8 - 1)/
              (8 * sizeof(unsigned char));
  assert(sizeof(unsigned char) == 1);
  out << "static const unsigned char " << name
  << "_accept[" << number_of_states() << "]["
  << bytes << "] = \n{  ";
  for (State s = 0; s < number_of_states(); s++)
  {
    Bool comma = false;
    out << "\n   { ";
    for (int i = 0; i < bytes; i++)
    {
      if (comma)
        out << ", ";
      out << accept[s]->byte(i);
      comma = true;
    }
    out << " }";
    if (s != number_of_states() - 1)
      out << ", ";
  }
  out << "\n};\n";
  ((TreeAutomaton *)this)->accept_bitmap_used = false;
  return out;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the index table for one functor.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& TreeAutomaton::gen_index
(std::ostream& out, Functor f, Arity i, const char name[]) const
{
  if (arity[f] != 0)
  {
    out << "static const " << get_state_type()
    << name << "_mu_" << (int)f << "_" << (int)i;
    out << '[' << state_count << "] = {";
    Bool comma = false;
    for (State s = 0; s < state_count; s++)
    {
      if (comma)
        out << ", ";
      if ((s & 15) == 0)
        out << "\n   ";
      out << mu[s][f][i];
      comma = true;
    }
    out << "\n};\n";
  }
  ((TreeAutomaton *)this)->mu_used = true;
  return out;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the type for a state.
//
//////////////////////////////////////////////////////////////////////////////

const char * TreeAutomaton::get_state_type() const
{
  return number_of_states() <= 256 ? "TreeTables::ShortState " :
         "TreeTables::State ";
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the type for a rule.
//
//////////////////////////////////////////////////////////////////////////////

const char * TreeAutomaton::get_rule_type() const
{
  return G->size() < 128 ? "TreeTables::ShortRule " :
         "TreeTables::Rule ";
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the transition table for one functor.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& TreeAutomaton::gen_theta
(std::ostream& out, Functor f, const char name[]) const
{
  if (arity[f] != 0)
  {
    int n = arity[f];
    const DeltaTable& delta_table = *delta[f];
    out << "static const " << get_state_type() << name << "_theta_" << f;
    {
      for (int i = 0; i < n; i++)
        out << '[' << index_range(f,i) << ']';
    }
    Bool comma = false;
    out << " = {\n   ";
    int indices[256];
    int bounds [256];
    int total = 1;
    {
      for (int i = 0; i < n; i++)
      {
        indices[i] = 0;
        total *= bounds[i] = index_range(f,i);
        if (i > 0)
          out << "{ ";
      }
    }
    {
      int  tab = 0;
      int  i, j;
      do
      {
        if (comma)
          out << ", ";
        if ((tab & 15) == 0 && comma)
          out << "\n   ";
        out << delta_table[indices];
        comma = true;
        total--;
        tab++;
        for (i = j = n - 1; i >= 0; i--)
        {
          if (++indices[i] < bounds[i])
          {
            if (total > 0 && i != j)
            {
              out << ",\n   ";
              tab = 0;
              comma = false;
            }
            break;
          }
          if (total > 0 || i > 0)
            out << " }";
          //if (total > 0) { if (comma) out << ",";
          //                 out << "\n   "; tab = 0; }
          indices[i] = 0;
          comma = false;
        }
        if (i >= 0)
          for ( ; j > i; j--)
            out << "{ ";
      }
      while (i >= 0);
    }
    out << "\n};\n";
  }
  return out;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Compilation and table emission methods.
//
//////////////////////////////////////////////////////////////////////////////

void TreeAutomaton::compile_compression_index()
{
  ///////////////////////////////////////////////////////////////////////////
  //  Compress the index maps.
  ///////////////////////////////////////////////////////////////////////////
  int index = 1;
  mu_index = (int**)mem.c_alloc(sizeof(int) * (G->functors()+1));

  ///////////////////////////////////////////////////////////////////////////
  //  Temporary buffers
  ///////////////////////////////////////////////////////////////////////////
  SparseDFA::State * deltas =
    (SparseDFA::State *)mem.c_alloc
    (sizeof(SparseDFA::State) * number_of_states());
  SparseDFA::Symbol * symbols =
    (SparseDFA::Symbol *)mem.c_alloc
    (sizeof(SparseDFA::Symbol) * number_of_states());

  ///////////////////////////////////////////////////////////////////////////
  //  Start the compression process
  ///////////////////////////////////////////////////////////////////////////
  dfa_compiler.create_tables(64,8,0,number_of_states()-1);
  dfa_compiler.start();

  ///////////////////////////////////////////////////////////////////////////
  //  Compress all index maps.
  ///////////////////////////////////////////////////////////////////////////
  total_index_entries = 0;
  for (Functor f = G->min_functor(); f <= G->max_functor(); f++)
  {
    mu_index[f] = (int*)mem.c_alloc(sizeof(int) * G->arity(f));
    for (int i = 0; i < G->arity(f); i++)
    {
      int fan_out = 0;
      for (int s = number_of_states() - 1; s >= 0; s--)
      {
        if (index_map(f,i,s) != 0)
        {
          symbols[fan_out] = s;
          deltas [fan_out] = index_map(f,i,s);
          fan_out++;
        }
      }
      dfa_compiler.add_state(index, fan_out, symbols, deltas);
      mu_index[f][i] = index++;
      total_index_entries += number_of_states();
    }
  }
  ///////////////////////////////////////////////////////////////////////////
  //  Finish the compression.
  ///////////////////////////////////////////////////////////////////////////
  dfa_compiler.finish();
  non_error_index_entries = dfa_compiler.size();
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the compression rate.
//  The compressed form in the base/check/next format.
//
//////////////////////////////////////////////////////////////////////////////

double TreeAutomaton::compression_rate() const
{
  double original = total_index_entries;
  double now      = dfa_compiler.size() * 2 + dfa_compiler.states();

  return (original - now) / now;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method for report generation.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& TreeAutomaton::print_report( std::ostream& f) const
{
  // Print the canonical grammar
  f << "\nCanonical grammar:\n" << *G << '\n';

  // Print other statistics
  f << "\nStatistics of the tree automaton:\n"
  << "   Number of functors      = " << G->functors() << '\n'
  << "   Number of non-terminals = " << G->variables() << '\n'
  << "   Number of states        = " << number_of_states() << '\n'
  << "   Memory used             = "
  << (mem.bytes_used() + 512)/1024 << " k-bytes\n";

  // Print compression statistics
  unsigned long total_mu_index_size = 0;
  if (mu_index)
  {
    total_mu_index_size = dfa_compiler.size() * 2;
    f << "\n"
    "Index compression statistics:\n"
    << "   Uncompressed index entries = " << total_index_entries     << '\n'
    << "   Non-empty index entries    = " << non_error_index_entries << '\n'
    << "   Compressed table entries   = " << total_mu_index_size << '\n'
    << "   Compression rate           = "
    << int(compression_rate() * 100.0 + .5) << "%\n"
    ;
  }

  // Print mu/theta table statistics
  unsigned long total_theta_size = 0;
  unsigned long total_mu_size    = 0;
  {
    for (Functor f = G->min_functor(); f <= G->max_functor(); f++)
    {
      if (arity[f] != 0)
      {
        int n = arity[f];
        int theta_size = 1;

        for (int i = 0; i < n; i++)
        {
          int dimension_size = index_range(f,i);
          theta_size *= dimension_size;
          if (dimension_size > 1)
            total_mu_size += number_of_states();
        }
        total_theta_size += theta_size;
      }
    }
  }

  // Compute the table sizes
  size_t state_size = number_of_states() <= 256 ?
                      sizeof(ShortState) : sizeof(State);
  size_t rule_size  = G->size() < 128 ? sizeof(ShortRule) : sizeof(Rule);
  unsigned long total_theta_bytes    = total_theta_size * state_size;
  unsigned long total_mu_bytes       = total_mu_size * state_size;
  unsigned long total_mu_index_bytes = total_mu_index_size * state_size;
  unsigned long total_accept_bytes   =
    accept_vector_size * rule_size +
    number_of_states() * sizeof(Offset);
  unsigned long total_accept_bitmap_bytes   =
    number_of_states() * (number_of_states() + 7/8);
  unsigned long total_accept1_bytes   =
    number_of_states() * rule_size;
  unsigned total_table_bytes = total_theta_bytes;


  // Print various table size
  f << "\n"
  "Table sizes:\n";
  f << "   Using " << state_size << "-byte state representation\n";
  f << "   Using " << rule_size << "-byte rule representation\n";
  f << "   Theta tables entries = " << total_theta_size
  << " (" << total_theta_bytes << " bytes)\n";
  if (mu_used)
  {
    f << "   Mu table entries     = " << total_mu_size
    << " (" << total_mu_bytes << " bytes)\n";
    total_table_bytes += total_mu_bytes;
  }

  if (mu_index_used)
  {
    f << "   Mu index entries     = " << total_mu_index_size
    << " (" << total_mu_index_bytes << " bytes)\n";
    total_table_bytes += total_mu_index_bytes;
  }

  if (accept_used)
  {
    f << "   Accept table entries = "
    <<  (accept_vector_size + number_of_states())
    << " (" <<  total_accept_bytes << " bytes)\n";
    total_table_bytes += total_accept_bytes;
  }

  if (accept_bitmap_used)
  {
    f << "   Accept bitmap size   = "
    << total_accept_bitmap_bytes << " bytes\n";
    total_table_bytes += total_accept_bitmap_bytes;
  }

  if (accept1_used)
  {
    f << "   Accept1 table size   = "
    << total_accept1_bytes << " bytes\n";
    total_table_bytes += total_accept1_bytes;
  }

  f << "   Total table size     = " << total_table_bytes << " bytes\n";

  return f;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method for printing a state.
//
//////////////////////////////////////////////////////////////////////////////

std::ostream& TreeAutomaton::print_state( std::ostream& f, State) const
{
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Methods for emitting the compressed index in C++ form.
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& TreeAutomaton::gen_compressed_index
(std::ostream& out, const char name[]) const
{
  ((TreeAutomaton *)this)->mu_index_used = true;
  out << "static const ";
  dfa_compiler.gen_check_next_tables(out, name, get_state_type());
  return out;
}
