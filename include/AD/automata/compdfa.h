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

#ifndef prop_compressed_dfa_tables_h
#define prop_compressed_dfa_tables_h

//////////////////////////////////////////////////////////////////////////////
// Compressed DFA table representations
//
// Class |CompressedDFA| and its subclasses represent
// deterministic finite state automata using a two level
// array indexing scheme originally proprosed by Tarjan and Yao.
//
// This base class handles some of the memory management logic.
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/generic/generic.h>
#include <AD/automata/dfatable.h>


class CompressedDFA : public DFATables
{

  CompressedDFA(const CompressedDFA&);    // no copy constructor
  void operator = (const CompressedDFA&); // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Inherit the types
  ///////////////////////////////////////////////////////////////////////////
  typedef DFATables               Super;
  typedef Super::Rule             Rule;   // A rule number
  typedef Super::Symbol           Symbol; // an input symbol
  typedef Super::Offset           Offset; // offset in state tables
  typedef Super::State            State;  // a DFA state (maximum states = 65535)
  typedef Super::ProductionLength ProductionLength;  // length of productions (max 255)
  typedef Super::EquivMap         EquivMap;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Table representation
  ///////////////////////////////////////////////////////////////////////////
  Offset * base;        // indexed by state
  State  * check;       // indexed by offset
  State  * next;        // indexed by offset

  int number_of_states; // length of the table |base|
  int table_size;       // length of the tables |check| and |next|
  int max_check;
  int max_state;

  Symbol min_symbol;    // minimum symbol value
  Symbol max_symbol;    // maximum symbol value

  ///////////////////////////////////////////////////////////////////////////
  // Internal functions to expand the tables and states
  ///////////////////////////////////////////////////////////////////////////

  virtual void grow_tables(int increment);
  virtual void grow_states(int increment);

  ///////////////////////////////////////////////////////////////////////////
  // Code emitters
  ///////////////////////////////////////////////////////////////////////////
  std::ostream& gen_state_table
  (std::ostream&, const char [], const char [], const State [], int size,
   const char * mytype = 0) const;
  std::ostream& gen_offset_table
  (std::ostream&, const char [], const char [], const Offset [], int size) const;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  CompressedDFA();
  virtual ~CompressedDFA();

  ///////////////////////////////////////////////////////////////////////////
  //  Method to create a table and give it some estimate.
  ///////////////////////////////////////////////////////////////////////////
  virtual void create_tables
  (
    int    table_size = 256,   // default table size; grow if necessary
    int    states = 8,         // default number of states; grow if necessary
    Symbol min = EOF,          // the minimum symbol of the character set
    Symbol max = 255           // the maximum symbol of the character set
  );

  ///////////////////////////////////////////////////////////////////////////
  // Return the number of states and the current table size.
  ///////////////////////////////////////////////////////////////////////////
  inline int states() const
  {
    return max_state - error_state;
  }
  inline int size()   const
  {
    return max_check + 1;
  }

  ///////////////////////////////////////////////////////////////////////////
  // Misc. selectors
  ///////////////////////////////////////////////////////////////////////////
  inline Offset state_offset(State s) const
  {
    return base[s];
  }

  ///////////////////////////////////////////////////////////////////////////
  // Emit the compressed tables as C++ code.
  ///////////////////////////////////////////////////////////////////////////
  virtual std::ostream& gen_code              (std::ostream&, const char []) const;
  virtual std::ostream& gen_check_next_tables (std::ostream&, const char [],
                                          const char * mytype = 0) const;
};

#endif
