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

#include <string.h>
#include <stdlib.h>
#include <AD/automata/lrgen.h>
#include <AD/automata/gentable.h>

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////

typedef Grammar::Symbol      Symbol;
typedef Grammar::ShortSymbol ShortSymbol;
typedef Grammar::Production  Production;
typedef Grammar::NonTerminal NonTerminal;

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

LRGen:: LRGen()
    : len(0), ncount(0), lhs(0), equiv(0), defact(0), final(0)
{
  clear_errors();
}

LRGen::~LRGen()
{
  delete [] len;
  delete [] ncount;
  delete [] equiv;
  delete [] defact;
  delete [] lhs;
}

//////////////////////////////////////////////////////////////////////////////
//  Equivalence map creation
//////////////////////////////////////////////////////////////////////////////

void LRGen::create_map( const Grammar& G)
{
  number_of_productions = G.size();

  ///////////////////////////////////////////////////////////////////////////
  // Compute the equiv classes table
  ///////////////////////////////////////////////////////////////////////////
  {
    if (equiv)
      delete [] equiv;
    equiv = new EquivMap [ equiv_classes_size = G.map_size() ];
    memcpy(equiv, G.map(), G.map_size() * sizeof(EquivMap));
  }

  ///////////////////////////////////////////////////////////////////////////
  // Compute the production length table; each entry is the number of
  // non-terminals in a production.
  ///////////////////////////////////////////////////////////////////////////
  {
    if (len)
      delete [] len;
    len = new ProductionLength [number_of_productions = G.size()];
    for (int i = G.size() - 1; i >= 0; i--)
      len[i] = G.length(G.rhs(i));
  }

  {
    if (ncount)
      delete [] ncount;
    ncount = new ProductionLength [G.size()];
    for (int i = G.size() - 1; i >= 0; i--)
    {
      int c = 0;
      for (const Symbol * P = G.rhs(i); *P != Grammar::END_PRODUCTION; P++)
        if (G.isNonTerminal(*P))
          c++;
      ncount[i] = c;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Compute the left hand side non-terminal
  ///////////////////////////////////////////////////////////////////////////
  {
    if (lhs)
      delete [] lhs;
    lhs = new ShortSymbol [ number_of_productions ];
    for (int i = G.size() - 1; i >= 0; i--)
      lhs[i] = G.lhs(i);
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Compilation
//////////////////////////////////////////////////////////////////////////////

void LRGen::compile( const Grammar& G)
{
  create_map(G);
}

//////////////////////////////////////////////////////////////////////////////
//  Table creation
//////////////////////////////////////////////////////////////////////////////

void LRGen::create_tables( int size, int states, Symbol min, Symbol max)
{
  ///////////////////////////////////////////////////////////////////////////
  // Create the rest of the tables
  ///////////////////////////////////////////////////////////////////////////
  Super::create_tables(size, states, min, max);

  ///////////////////////////////////////////////////////////////////////////
  // Create the default action table
  ///////////////////////////////////////////////////////////////////////////
  defact = new State [number_of_states];
  //   len    = new ProductionLength [number_of_states];
  //   ncount = new ProductionLength [number_of_states];
  //   if (number_of_states > 0)
  //   {  defact[0] = 0; len[0] = 0; ncount[0] = 0; }
  if (number_of_states > 0)
    defact[0] = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  State growth
//////////////////////////////////////////////////////////////////////////////

void LRGen::grow_states( int increment)
{
  {
    State * new_defact = new State [ number_of_states + increment ];
    memcpy(new_defact, defact, number_of_states * sizeof(State));
    delete [] defact;
    defact = new_defact;
  }
#if 0
  {  ProductionLength * new_len =
      new ProductionLength [ number_of_states + increment ];
    memcpy(new_len, len, number_of_states * sizeof(ProductionLength));
    delete [] len;
    len = new_len;
  }
  {  ProductionLength * new_ncount =
      new ProductionLength [ number_of_states + increment ];
    memcpy(new_ncount, ncount, number_of_states * sizeof(ProductionLength));
    delete [] ncount;
    ncount = new_ncount;
  }
#endif
  Super::grow_states(increment);
}

//////////////////////////////////////////////////////////////////////////////
//  Code generation
//////////////////////////////////////////////////////////////////////////////

std::ostream& LRGen::gen_code( std::ostream& out, const char name[]) const
{
  Super::gen_code(out,name);
  gen_state_table(out, name, "defact", defact, max_state + 1);
  TablePrinter pr;
  pr.print(out, (const char *)len, number_of_productions,
           sizeof(ProductionLength), "static const DFATables::ProductionLength ",
           name, "len", true);
  pr.print(out, (const char *)ncount, number_of_productions,
           sizeof(ProductionLength), "static const DFATables::ProductionLength ",
           name, "ncount", true);
  pr.print(out, (const char *)lhs, number_of_productions,
           sizeof(ShortSymbol), "static const DFATables::ShortSymbol ",
           name, "lhs", true);
  pr.print(out, (const char *)equiv, equiv_classes_size,
           sizeof(EquivMap), "static const DFATables::EquivMap ",
           name, "equiv", true);
  return out;
}
