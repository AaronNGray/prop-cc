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

#include <AD/automata/acgen.h>
#include <AD/tries/briandai.h>
#include <AD/contain/queue.h>  // generic queues

///////////////////////////////////////////////////////////////////////////
//   Make hidden types visible
///////////////////////////////////////////////////////////////////////////

typedef ACGen::Symbol Symbol;
typedef ACGen::Rule   Rule;
typedef ACGen::Node   Node;

///////////////////////////////////////////////////////////////////////////
//   Constructor and destructor
///////////////////////////////////////////////////////////////////////////

ACGen::ACGen() : trie(0), number_of_states(0), epsilon(0), matched_rule(0)
{}
ACGen::~ACGen()
{
  delete [] epsilon;
  delete [] matched_rule;
}

void ACGen::start (Symbol min, Symbol max)
{
  min_symbol = min;        // initial estimate of the minimal symbol
  max_symbol = max;        // initial estimate of the maximal symbol
  trie = new Briandais;    // Make a new trie
}

///////////////////////////////////////////////////////////////////////////
// Insert a new string into the trie
///////////////////////////////////////////////////////////////////////////

void ACGen::add_string( Rule rule, int length, const Symbol string [])
{
  int i;
  Node n = trie->root();
  for (i = 0; i < length; i++)
  {
    register Symbol c = string[i];
    Node child = trie->child(n,c);
    if (trie->is_empty(child))
      n = trie->insert(n,c);
    else
      n = child;
  }
}

void ACGen::generate_goto
(Node node, int number_of_symbols, Symbol symbols[], State delta[])
{
  register int i;
  register Node n;

  if (node == trie->root())
  {
    for (i = 0; i < number_of_symbols; i++)
    {
      symbols[i] = i + min_symbol;
      delta[i] = trie->root() + 1;
    }
    for (n = trie->child(trie->root());
         ! trie->is_empty(n); n = trie->sibling(n))
    {
      delta[(*trie)[n] - min_symbol] = n + 1;
    }
  }
  else
  {
    for (i = 0, n = trie->child(node);
         ! trie->is_empty(n); n = trie->sibling(n), i++)
    {
      symbols[i] = (*trie)[n];
      delta[i] = n + 1;
    }
  }

  add_state((State)node + 1, i, symbols, delta);

  for (n = trie->child(node); ! trie->is_empty(n); n = trie->sibling(n))
    generate_goto(n, number_of_symbols, symbols, delta);
}


void ACGen::finish()
{
  int number_of_symbols = max_symbol - min_symbol + 1;

  ///////////////////////////////////////////////////////////////////////////
  // Allocate space for all tables
  ///////////////////////////////////////////////////////////////////////////

  number_of_states = trie->size() + 1;
  epsilon          = new State  [ number_of_states ];
  matched_rule     = new Rule   [ number_of_states ];
  create_tables(4*number_of_symbols, number_of_states, min_symbol, max_symbol);

  ///////////////////////////////////////////////////////////////////////////
  // Traverse the trie in depth first manner and generate the state
  // transition tables.
  ///////////////////////////////////////////////////////////////////////////

  Symbol * symbols = new Symbol [ number_of_symbols ];
  State *  delta   = new State  [ number_of_symbols ];
  Super::start();

  generate_goto(trie->root(), number_of_symbols, symbols, delta);

  Super::finish();
  delete [] symbols;
  delete [] delta;

  ///////////////////////////////////////////////////////////////////////////
  // Traverse the trie in breath first manner(using a queue for help)
  // and generate the failure function.
  ///////////////////////////////////////////////////////////////////////////

  epsilon[0] = 0;
  epsilon[1] = 1;

  Queue <Node> Q(number_of_states);
  for ( Q.insert_tail(trie->root()); ! Q.is_empty(); )
  {
    Node parent = Q.remove_head();
    Node n;
    for (n = trie->child(parent); ! trie->is_empty(n); n = trie->sibling(n))
    {
      Q.insert_tail(n);
      if (parent == trie->root())
        epsilon[n+1] = 1;
      else
        epsilon[n+1] = go( epsilon[parent + 1], (*trie)[n] );
    }
  }

  delete trie;
}

std::ostream& ACGen::gen_code( std::ostream& out, const char name[]) const
{
  Super::gen_code(out,name);
  gen_state_table(out,name,"fail",epsilon,number_of_states);
  return out;
}
