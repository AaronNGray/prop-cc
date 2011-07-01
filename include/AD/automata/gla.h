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

#ifndef general_lookahead_automata_h
#define general_lookahead_automata_h

#include <AD/automata/grammar.h>     // grammars
#include <AD/memory/mem.h>           // memory manager
#include <AD/contain/bitset.h>       // bit sets

//////////////////////////////////////////////////////////////////////////////
//  Class GLA represents a ``general_lookahead_automaton'' (see Terrance
//  Parr's PhD thesis at Purdue U.)
//////////////////////////////////////////////////////////////////////////////

class GLA : public DFATables
{
  GLA( const GLA&);               // no copy constructor
  void operator = ( const GLA&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types from superclass.
  ///////////////////////////////////////////////////////////////////////////
  typedef DFATables            Super;
  typedef Super::State         State;
  typedef Super::Rule          Rule;
  typedef Super::Symbol        Symbol;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Terminal    Terminal;
  typedef Grammar::EquivMap    EquivMap;
  typedef BitSet               NonTerminalSet;

  ///////////////////////////////////////////////////////////////////////////
  //  Define the GLA internals:
  //     A GLA node is represented by the following class.
  //     It is basically a labeled graph represented in child-sibling
  //     format.
  ///////////////////////////////////////////////////////////////////////////
  class Node
  {

    Node( const Node&);               // no copy constructor
    void operator = ( const Node&);   // no assignment

  public:

    Node();
    ~Node();
  };

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  The internals of this class is hidden.
  ///////////////////////////////////////////////////////////////////////////
  Mem&             mem;      // internal memory manager
  class GLA_Impl * intern;   // internal rep.
  virtual void clean_up();   // method to clean up internal rep.

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////
  GLA( Mem& );
  GLA( const Grammar&, Mem& );
  virtual ~GLA();

  ///////////////////////////////////////////////////////////////////////////
  //  Method to construct the LR(0) automaton and compute the GLA
  //  from the grammar.
  ///////////////////////////////////////////////////////////////////////////
  virtual void build( const Grammar&);

  ///////////////////////////////////////////////////////////////////////////
  //  Operations on a GLA:
  //     `look()' -- compute the linear lookahead approximation from a
  //                 node of the GLA, where 'k' is the lookahead count.
  ///////////////////////////////////////////////////////////////////////////
  const NonTerminalSet& look( const Node *, int k);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to print a report.
  ///////////////////////////////////////////////////////////////////////////
  virtual std::ostream& print_report( std::ostream&, Bool, Bool);
};

#endif
