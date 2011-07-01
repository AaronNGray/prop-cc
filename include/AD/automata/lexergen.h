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

#ifndef lexical_scanner_generator_h
#define lexical_scanner_generator_h

//////////////////////////////////////////////////////////////////////////////
// Lexer scanner and lexer scanner generator. \cite{Dragon-book}
//////////////////////////////////////////////////////////////////////////////

#include <AD/automata/densedfa.h>  // compressed dense dfa

class LexerGen : public DenseDFA
{
  LexerGen( const LexerGen&);           // no copy constructor
  void operator = ( const LexerGen&);   // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  ///////////////////////////////////////////////////////////////////////////
  typedef DenseDFA      Super;
  typedef Super::Symbol Symbol; // An input symbol
  typedef Super::State  State;  // A state in the automaton
  typedef Super::Offset Offset; // Table offset
  typedef Super::Rule   Rule;   // Rule number of regular expressions

  ///////////////////////////////////////////////////////////////////////////
  //  We allow up to 256 level of nesting in a regular expression and
  //  up to 256 different lexical contexts.  These can be increased by
  //  altering the constants below.
  ///////////////////////////////////////////////////////////////////////////
  enum Lexergen_constants
  {  Max_star_height = 256,
     Max_contexts    = 256
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Options for the lexer generator
  ///////////////////////////////////////////////////////////////////////////
  enum Options {
    None            = 0,  // no options
    Backtracking    = 1,  // recognize the longest token, not the first
    CaseInsensitive = 2   // fold upper case and lower case
  };

protected:
  //////////////////////////////////////////////////////////////////////////
  //  Miscellaneous statistics
  //////////////////////////////////////////////////////////////////////////
  int bytes_used;        // memory used
  int equiv_class_count; // number of equivalence classes used

  ///////////////////////////////////////////////////////////////////////////
  //  Current state
  ///////////////////////////////////////////////////////////////////////////
  State state;       // current DFA state.

  ///////////////////////////////////////////////////////////////////////////
  //  This stores the bad rule number if one is found during compilation.
  //  Set to -1 otherwise.
  ///////////////////////////////////////////////////////////////////////////
  Rule         bad_rule;
  const char * error_msg;

  //////////////////////////////////////////////////////////////////////////
  // The lexical scanner tables, compressed.  See Aho et al. for details.
  // State 0, as always is reserved to be the unique error state.
  //////////////////////////////////////////////////////////////////////////

  Symbol   max_char;       // maximum character value of the character set
  Rule *   rule;           // accepting rule number of state, if any
  Symbol * equiv_classes;  // equivalence class table

  void create_tables( int table_size, int states, Symbol min, Symbol max);
  void grow_states( int increment);

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  LexerGen();
  ~LexerGen();

  ///////////////////////////////////////////////////////////////////////////
  //  Compile a set of lexical rules
  ///////////////////////////////////////////////////////////////////////////
  virtual void compile
  (
    int n,                              // number of regular expressions
    const char * const * regexp,        // regular expressions
    const char * const * contexts = 0,  // starting contexts, null terminated
    int max_char    = 255,              // maximum character
    int options = Backtracking          // options to the compiler
  );

  ///////////////////////////////////////////////////////////////////////////
  //  Emit the tables as C++ code
  ///////////////////////////////////////////////////////////////////////////
  virtual std::ostream& gen_code( std::ostream&, const char name[]) const;
  virtual std::ostream& print_report( std::ostream&) const;

  //////////////////////////////////////////////////////////////////////////
  //  Note: if there are $n$ start conditions then state number
  //  1 to $n*2+3$ are used as start states.  i.e. start condition $0$
  //  is the ``normal'' lexical context.  Each start condition occupies
  //  two state numbers, one corresponding to the case in which the
  //  input is anchored at the beginning of the line and one in which
  //  it is not necessarily so.
  //
  //  The client can switch between contexts with the method begin(...).
  //  Notice that no checking is performed.
  //////////////////////////////////////////////////////////////////////////
  inline void begin( int c)  // start at context c
  {
    state = c;
  }

  inline Bool ok() const  // Compilation succeeded??
  {
    return bad_rule < 0;
  }

  inline Rule bad() const  // bad rule number, if any
  {
    return bad_rule;
  }

  inline const char* error_message() const
  {
    return error_msg;
  }

  inline Rule accept() const  // accept rule of current state
  {
    return rule[state];
  }

  inline State go( State s, Symbol c) const  // advance to the next state
  {
    register Offset offset;
    while (check[ offset = base[s] + equiv_classes[c] ] != s)
      if ((s = def[ s ]) == 0)
        return 0;
    return next[ offset ];
  }
};

#endif
