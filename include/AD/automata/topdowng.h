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

#ifndef top_down_tree_matching_automata_generator_h
#define top_down_tree_matching_automata_generator_h

#include <AD/automata/acgen.h>    // Aho-Corasick string matching generator
#include <AD/automata/treegram.h> // Tree grammars

//////////////////////////////////////////////////////////////////////////////
//
//  The top-down tree matching algorithm\cite{tree-matching, AC}
// reduces the problem of tree matching to the problem of string matching
// a set of path strings.
//
//////////////////////////////////////////////////////////////////////////////

class TopDownGen : public ACGen
{
  TopDownGen( const TopDownGen&);           // no copy constructor
  void operator = ( const TopDownGen&);     // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  // Inherit some types
  ///////////////////////////////////////////////////////////////////////////
  typedef ACGen                       Super;
  typedef Super::Symbol               Symbol;
  typedef Super::Rule                 Rule;
  typedef Super::Offset               Offset;
  typedef Super::State                State;
  typedef TreeGrammar::TreeProduction TreeProduction;

private:
  ///////////////////////////////////////////////////////////////////////////
  //  The current tree grammar
  ///////////////////////////////////////////////////////////////////////////
  const TreeGrammar* G;

  ///////////////////////////////////////////////////////////////////////////
  //  Private method to add a path string to the trie
  ///////////////////////////////////////////////////////////////////////////
  void add_path( int, const TreeTerm, int, Symbol []);

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////
  TopDownGen();
  TopDownGen(const TreeGrammar&);
  ~TopDownGen();

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline int size() const
  {
    return Super::size();
  }
  inline State start_state() const
  {
    return 0;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Compilation and code emission
  ///////////////////////////////////////////////////////////////////////////
  void compile( const TreeGrammar&);
  virtual std::ostream& gen_code( std::ostream&, const char name[]) const;
  virtual std::ostream& print_report( std::ostream&) const;

  ///////////////////////////////////////////////////////////////////////////
  // Advance one state within the tree matching automaton
  ///////////////////////////////////////////////////////////////////////////
  inline State go( register State s, register int branch, register Symbol c) const
  {
    return Super::go( Super::go( s, branch), c);
  }
};

#endif
