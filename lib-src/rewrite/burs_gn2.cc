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

#include <AD/rewrite/burs_gn2.h>  // BURS generator

//////////////////////////////////////////////////////////////////////////////
//
// The class New_BURS_Gen improves upon the class BURS_Gen
// by compressing the index maps using a sparse DFA compression
// algorithm.
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////

New_BURS_Gen:: New_BURS_Gen( Mem& m) : BURS_Gen(m) {}
New_BURS_Gen:: New_BURS_Gen( Mem& m, TreeGrammar& g) : BURS_Gen(m,g) {}
New_BURS_Gen::~New_BURS_Gen() {}

//////////////////////////////////////////////////////////////////////////////
//  Compilation and table emission methods.
//////////////////////////////////////////////////////////////////////////////

void New_BURS_Gen::compile (TreeGrammar& g)
{
  ///////////////////////////////////////////////////////////////////////////
  //  Generate the tree automaton tables.
  ///////////////////////////////////////////////////////////////////////////
  Super::compile(g);

  ///////////////////////////////////////////////////////////////////////////
  //  Compress the index maps.
  ///////////////////////////////////////////////////////////////////////////
  int index = 1;
  mu_index = (int**)mem.c_alloc(sizeof(int) * (g.functors()+1));

  ///////////////////////////////////////////////////////////////////////////
  //  Temporary buffers
  ///////////////////////////////////////////////////////////////////////////

  SparseDFA::State * delta =
    (SparseDFA::State *)mem.c_alloc
    (sizeof(SparseDFA::State) * number_of_states());

  SparseDFA::Symbol * symbols =
    (SparseDFA::Symbol *)mem.c_alloc
    (sizeof(SparseDFA::Symbol) * number_of_states());

  ///////////////////////////////////////////////////////////////////////////
  //  Start the compression process
  ///////////////////////////////////////////////////////////////////////////

  dfa_compiler.create_tables( 64, 8, 0, number_of_states()-1);
  dfa_compiler.start();

  ///////////////////////////////////////////////////////////////////////////
  //  Compress all index maps.
  ///////////////////////////////////////////////////////////////////////////

  total_index_entries = 0;
  for (Functor f = g.min_functor(); f <= g.max_functor(); f++)
  {
    mu_index[f] = (int*)mem.c_alloc(sizeof(int) * g.arity(f));
    for (int i = 0; i < g.arity(f); i++)
    {
      int fan_out = 0;
      for (int s = number_of_states() - 1; s >= 0; s--)
      {
        if (index_map(f,i,s) != 0)
        {
          symbols[fan_out] = s;
          delta  [fan_out] = index_map(f,i,s);
          fan_out++;
        }
      }
      dfa_compiler.add_state(index, fan_out, symbols, delta);
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

void New_BURS_Gen::clear ()
{
  Super::clear();
}

//////////////////////////////////////////////////////////////////////////////
//  Check for completeness.
//////////////////////////////////////////////////////////////////////////////

Bool New_BURS_Gen::is_complete() const
{
  return Super::is_complete();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the compression rate.
//  The compressed form in the base/check/next format.
//////////////////////////////////////////////////////////////////////////////

double New_BURS_Gen::compression_rate() const
{
  double original = total_index_entries;
  double now      = dfa_compiler.size() * 2 + dfa_compiler.states();

  return (original - now) / now;
}

//////////////////////////////////////////////////////////////////////////////
//  Methods for code generation and report generation.
//////////////////////////////////////////////////////////////////////////////

std::ostream& New_BURS_Gen::print_report( std::ostream& f) const
{
  Super::print_report(f);

  // Print other statistics
  f << "Index compression statistics:\n"
  << "   Uncompressed index entries = " << total_index_entries     << '\n'
  << "   Non-empty index entries    = " << non_error_index_entries << '\n'
  << "   Compressed table entries   = "
  << (dfa_compiler.size() * 2 + dfa_compiler.states()) << '\n'
  << "   Compression rate           = "
  << int(compression_rate() * 100.0 + .5) << "%\n"
  ;

  return f;
}

std::ostream& New_BURS_Gen::gen_compressed_index( std::ostream& out, const char name[]) const
{
  return dfa_compiler.gen_code( out, name);
}
