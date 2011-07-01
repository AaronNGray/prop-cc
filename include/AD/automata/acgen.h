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

#ifndef prop_Aho_Corasick_string_matcher_generator_h
#define prop_Aho_Corasick_string_matcher_generator_h

//////////////////////////////////////////////////////////////////////////////
// The Aho-Corasick keyword matching algorithm\cite{AC}.  The resulting
// automaton is represented as a sparse DFA table.  This data structure
// makes it possible to use this algorithm for matching large sets
// of keys with large character sets while utilizing memory efficiently.
//////////////////////////////////////////////////////////////////////////////

#include <AD/automata/sparsdfa.h>  // sparse compressed dfa
#include <AD/tries/briandai.h>

class ACGen : public SparseDFA
{
  ACGen(const ACGen&);             // no copy constructor
  void operator = (const ACGen&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  ///////////////////////////////////////////////////////////////////////////
  typedef SparseDFA       Super;
  typedef Super::Rule     Rule;
  typedef Super::State    State;
  typedef Super::Symbol   Symbol;
  typedef Super::Offset   Offset;
  typedef Briandais::Node Node;

  enum ACGen_constants { Empty_Rule = -1 };

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  Briandais * trie;     // De la Briandais trie
  int number_of_states; // number of states within the automata
  State * epsilon;      // the failure function computes epsilon transitions
  Rule  * matched_rule;

  void generate_goto(Node, int, Symbol [], State []);

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  ACGen();
  ~ACGen();

  ///////////////////////////////////////////////////////////////////////////
  //  Return the number of states
  ///////////////////////////////////////////////////////////////////////////
  int size() const
  {
    return number_of_states;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to build the compressed tables
  ///////////////////////////////////////////////////////////////////////////
  virtual void start( Symbol min = Max_Symbol, Symbol max = Min_Symbol);
  virtual void add_string( Rule rule, int length, const Symbol string []);
  virtual void finish();

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to emit C++ code
  ///////////////////////////////////////////////////////////////////////////
  virtual std::ostream& gen_code( std::ostream&, const char []) const;
  void     gen_fast_automaton( std::ostream&, const char []) const;

  ///////////////////////////////////////////////////////////////////////////
  //  Return the start state
  ///////////////////////////////////////////////////////////////////////////
  State start_state() const
  {
    return 1;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Advance one state within the Aho-Corasick automaton.
  ///////////////////////////////////////////////////////////////////////////
  inline State go( register State s, register Symbol c) const
  {
    register Offset offset;
    while (check[offset = base[s] + c] != s)
      s = epsilon[s];
    return next[offset];
  }
};

#endif
