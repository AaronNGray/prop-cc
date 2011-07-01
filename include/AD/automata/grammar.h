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

#ifndef grammar_for_parsers_h
#define grammar_for_parsers_h

#include <iostream>
#include <AD/generic/generic.h>   // Generic definitions
#include <AD/automata/dfatable.h> // DFA tables


//////////////////////////////////////////////////////////////////////////////
//  This class is used to represent a context free grammar.
//
//  The representation is very simple:  each symbol (terminal, non-terminal,
//  or action symbols) are represented as the type |Symbol|.
//  A production is simply an array of Symbol's terminated with the
//  unique constant |Grammar::END_PRODUCTION|.   A grammar is just an
//  array of productions.
//
//  Most simple operations are inline'd for efficiency.
//////////////////////////////////////////////////////////////////////////////

class Grammar : public DFATables
{
public:

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////
  typedef DFATables       Super;
  typedef Super::State    State;
  typedef Super::Rule     Rule;
  typedef Super::Offset   Offset;
  typedef Super::Symbol   Symbol;      // a terminal, non-terminal or action symbol
  typedef Symbol          Terminal;    // a terminal
  typedef Symbol          NonTerminal; // a non-terminal
  typedef Symbol          Action;      // an action symbol
  typedef Symbol *        Production;  // a production
  typedef Super::EquivMap EquivMap;    // equivalence mapping

  ///////////////////////////////////////////////////////////////////////////
  //  Manifest constants
  ///////////////////////////////////////////////////////////////////////////
  enum Grammar_constants
  {  END_PRODUCTION = EOF - 1, // end-of-production marker
     First_action   = END_PRODUCTION - 1
  };

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////

  Production *  productions;           // an array of productions
  Bool          persistent;            // is the array persistent?
  int           number_of_productions; // size of the array
  Terminal      minTerminal;           // minimal terminal
  Terminal      maxTerminal;           // maximal terminal
  NonTerminal   minNonTerminal;        // minimal non-terminal
  NonTerminal   maxNonTerminal;        // maximal non-terminal
  NonTerminal   maxNormalNonTerminal;  // maximal (normal) non-terminal
  NonTerminal   startSymbol;           // the start symbol
  Production    startProduction;       // the start production
  const char ** symbol_names;          // symbol names mapping
  int           equiv_classes_size;    // equivalence class size
  EquivMap   *  equiv_classes;         // equivalence class mapping
  EquivMap   *  equiv_map;
  Rule       *  action_map;            // mapping from action to rule
  int           action_map_size;

  ///////////////////////////////////////////////////////////////////////////
  // Private cleaning method
  ///////////////////////////////////////////////////////////////////////////
  void clean_up();

public:

  //////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  //////////////////////////////////////////////////////////////////////////
  Grammar();
  Grammar( const Grammar&);
  Grammar( Production P[], int n, Symbol min, Symbol max,
           NonTerminal start,
           const char * names[] = 0,
           int = 0, EquivMap [] = 0, EquivMap [] = 0,
           Rule [] = 0, int = 0, NonTerminal maxNormal = -1,
           Bool persist = true);
  virtual ~Grammar();

  //////////////////////////////////////////////////////////////////////////
  // Assignment
  //////////////////////////////////////////////////////////////////////////
  Grammar& operator = (const Grammar&);

  //////////////////////////////////////////////////////////////////////////
  // Testing for symbol type
  //////////////////////////////////////////////////////////////////////////

  inline Bool isTerminal( Symbol s) const
  {
    return s > END_PRODUCTION && s <= maxTerminal;
  }
  inline Bool isNonTerminal( Symbol s) const
  {
    return s > maxTerminal;
  }
  inline Bool isAction( Symbol s) const
  {
    return s < END_PRODUCTION;
  }

  //////////////////////////////////////////////////////////////////////////
  //  Productions
  //////////////////////////////////////////////////////////////////////////

  inline int size() const
  {
    return number_of_productions;
  }

  int size(Production) const;   // length
  int length(Production) const; // length without action symbols

  inline Production operator [] (int i) const
  {
    return productions[i];
  }

  inline NonTerminal lhs(int i) const
  {
    return productions[i][0];
  }

  inline Production rhs(int i) const
  {
    return productions[i] + 1;
  }

  inline NonTerminal start() const
  {
    return startSymbol;
  }

  inline Production start_production () const
  {
    return startProduction;
  }

  //////////////////////////////////////////////////////////////////////////
  //  Symbols ranges
  //////////////////////////////////////////////////////////////////////////

  inline int number_of_terminals() const
  {
    return maxTerminal - minTerminal + 1;
  }

  inline int number_of_non_terminals() const
  {
    return maxNonTerminal - minNonTerminal + 1;
  }

  inline int number_of_symbols() const
  {
    return maxNonTerminal - minTerminal + 1;
  }

  inline Terminal min_terminal() const
  {
    return minTerminal;
  }

  inline Terminal max_terminal() const
  {
    return maxTerminal;
  }

  inline NonTerminal min_non_terminal() const
  {
    return minNonTerminal;
  }

  inline NonTerminal max_non_terminal() const
  {
    return maxNonTerminal;
  }

  inline NonTerminal max_normal_non_terminal() const
  {
    return maxNormalNonTerminal;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Shift/reduce encoding
  ///////////////////////////////////////////////////////////////////////////

  inline Bool isShift( State s) const
  {
    return s < 0x4000;
  }

  inline Bool isReduce( State s) const
  {
    return s >= 0x8000;
  }

  inline Bool isSingleReduce( State s) const
  {
    return s >= 0xc000;
  }

  inline Bool isShiftReduce( State s) const
  {
    return s & 0x4000;
  }

  inline State makeReduce( State s) const
  {
    return s | 0x8000;
  }

  inline State makeSingleReduce( State s) const
  {
    return s | 0xc000;
  }

  inline State makeShiftReduce( State s) const
  {
    return s | 0x4000;
  }

  inline Rule reduceRule( State s) const
  {
    return s & 0x3fff;
  }

  //////////////////////////////////////////////////////////////////////////
  //  Conversion
  //////////////////////////////////////////////////////////////////////////

  Grammar makeCanonical() const;

  //////////////////////////////////////////////////////////////////////////
  //  Equivalence class mapping
  //////////////////////////////////////////////////////////////////////////

  inline EquivMap map( Symbol A) const
  {
    return equiv_map[A];
  }

  inline const EquivMap* map() const
  {
    return equiv_classes;
  }

  inline int map_size() const
  {
    return equiv_classes_size;
  }

  inline Rule rule_of( Action a) const
  {
    return action_map[First_action - a];
  }

  //////////////////////////////////////////////////////////////////////////
  //  Printing
  //////////////////////////////////////////////////////////////////////////
  std::ostream& print( std::ostream&, Symbol)                  const; // Print a symbol
  std::ostream& print( std::ostream&, Production, Bool = true) const; // Print a production
  std::ostream& print( std::ostream&, int, Production)         const; // Print an item
  friend std::ostream& operator << (std::ostream&, const Grammar&);   // Print a grammar
};

#endif
