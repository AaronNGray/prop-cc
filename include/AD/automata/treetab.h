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

#ifndef compressed_tree_automaton_tables_h
#define compressed_tree_automaton_tables_h

/////////////////////////////////////////////////////////////////////////////
// Three tables are used to represent the transition tables:
// ``arity'', ``base'', and ``index''.  The table ``arity'' is a mapping
// from functors to their arities.  The table ``base'' maps each functor
// to the starting offset of the index table.  Each functor |A|'s index table
// is comprised of two components: the first is a list of index tables
// $\mu_Ai$ for each arity $i$; followed by the compressed transition
// table $\theta_A$.   The multidimensional transition table is
// ``flattened'' into linear form so that multiplication is unnecessary
// when computing the indices.
/////////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>   // Generic definitions

class TreeTables
{
public:
  //////////////////////////////////////////////////////////////////////////
  // Types that are used to encode the tables
  //////////////////////////////////////////////////////////////////////////

  typedef short           Offset;      // table offsets
  typedef unsigned short  State;       // a state in the tree automaton
  typedef unsigned char   ShortState;  // a state in the tree automaton
  typedef short           Functor;     // constructor of a term
  typedef Functor         Variable;    // pattern variables
  typedef Functor         NonTerminal; // non-terminals
  typedef unsigned char   Arity;       // arity of a functor
  typedef short           Rule;        // rule number
  typedef signed char     ShortRule;   // rule number
  typedef short           Cost;        // reduction cost

  //////////////////////////////////////////////////////////////////////////
  //  Constants for reduction costs
  //////////////////////////////////////////////////////////////////////////
  enum TreeTables_constants
  {  infinite_cost = 32767,
     zero_cost     = 0
  };
};

#endif
