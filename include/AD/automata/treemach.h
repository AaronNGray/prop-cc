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

#ifndef compressed_tree_automaton_driver_h
#define compressed_tree_automaton_driver_h

#include <AD/automata/treetab.h>

/////////////////////////////////////////////////////////////////////////////
// Class |TreeMach| represents a compressed tree automaton
// using a flattened multidimensional transition table\cite{Chase}.
//
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

class TreeMach : public TreeTables
{
  TreeMach( const TreeMach&);          // no copy constructor
  void operator = ( const TreeMach&);  // no assignment

public:

  //////////////////////////////////////////////////////////////////////////
  // Make inherited types visible
  //////////////////////////////////////////////////////////////////////////
  typedef TreeTables      Super;
  typedef Super::Offset   Offset;   // table offsets
  typedef Super::State    State;    // a state in the tree automaton
  typedef Super::Functor  Functor;  // constructor of a term
  typedef Super::Arity    Arity;    // arity of a functor
  typedef Super::Rule     Rule;     // rule number

protected:

  //////////////////////////////////////////////////////////////////////////
  // The compressed tables
  //////////////////////////////////////////////////////////////////////////
  const Arity  * const arity;       // functor to arity mapping
  const Offset * const base;        // functor to base offset mapping
  const State  * const index;       // offset to offset mapping

public:

  //////////////////////////////////////////////////////////////////////////
  //  Constructor
  //////////////////////////////////////////////////////////////////////////
  TreeMach(
      const Arity  arity_table [],
      const Offset base_table  [],
      const State  index_table []
      ) : arity(arity_table), base(base_table), index(index_table)
  {}

  //////////////////////////////////////////////////////////////////////////
  // Advance one state within the tree automaton.
  //    The first go() function is an optimized form for a unit functor--
  // i.e. a functor with 0 arity.  The second go() function is the general
  // form which looks up all three tables.
  //////////////////////////////////////////////////////////////////////////

  inline State go( Functor f) const
  {
    return (State) base[f];
  }
  inline State go( Functor f, const State * inputs) const
  {
    register Offset  offset;  // current offset
    register State * indices; // indices;
    register int i;
    for (i = arity[f], offset = base[f], indices = index + offset + 1;
         i > 0; i--, indices += indices[-1])
      offset += indices[ *inputs++ ];
    return index[offset];
  }
};

#endif
