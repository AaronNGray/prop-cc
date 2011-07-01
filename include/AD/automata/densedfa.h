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

#ifndef prop_dense_compressed_dfa_table_h
#define prop_dense_compressed_dfa_table_h

//////////////////////////////////////////////////////////////////////////////
// Dense DFA table achieve better compressing rates than the sparse DFA
// table by merging ``similar'' states.  Each state has a ``default'' to
// fall back on.
//////////////////////////////////////////////////////////////////////////////

#include <AD/automata/sparsdfa.h>  // sparse dfa tables

class DenseDFA : public SparseDFA
{

  DenseDFA(const DenseDFA&);           // no copy constructor
  void operator = (const DenseDFA&);   // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  ///////////////////////////////////////////////////////////////////////////
  typedef SparseDFA               Super;
  typedef Super::State            State;
  typedef Super::Symbol           Symbol;
  typedef Super::Offset           Offset;
  typedef Super::Rule             Rule;
  typedef Super::ProductionLength ProductionLength;
  typedef Super::EquivMap         EquivMap;

private:

  ///////////////////////////////////////////////////////////////////////////
  // The following tables are used by the compression algorithm
  // and do not concern our subclasses or clients.
  // Briefly, states with reuse potential are stored as ``templates'' in
  // a template table.  When a new state is added, we first check whether
  // it is similar any of the templates; if so, only the different between
  // the new state and the template is stored, and the template state is
  // used as the default state.
  ///////////////////////////////////////////////////////////////////////////

  State  * diffs[2];     // buffer for caching the difference between states
  State  * transitions;  // transition buffer
  Symbol * symbols;      // symbols of transitions
  State  * my_delta;     // a temporary buffer for the transition function
  int max_template_diff; // maximum allowable difference for a template
  int number_of_symbols;

  struct Template
  {
    State * delta;
    State state;
    int uses;
    int age;
  };
  enum densedfa_constants { Max_templates = 12 };
  Template templates[ Max_templates ];
  int      number_of_templates;
  int      current_age;
  int      misses;
  Bool     empty_slots;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Additional tables
  ///////////////////////////////////////////////////////////////////////////
  State * def;          // indexed by state

  ///////////////////////////////////////////////////////////////////////////
  //  This is refined to take care of growing the ``def'' table above.
  ///////////////////////////////////////////////////////////////////////////
  void grow_states(int increment);

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  DenseDFA ();
  ~DenseDFA ();

  ///////////////////////////////////////////////////////////////////////////
  //  Method to create a new table
  ///////////////////////////////////////////////////////////////////////////
  virtual void create_tables
  (
    int    table_size = 256,   // default table size; grow if necessary
    int    states = 8,         // default number of states; grow if necessary
    Symbol min = EOF,          // the minimum symbol of the character set
    Symbol max = 255           // the maximum symbol of the character set
  );

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to insert states into the table
  ///////////////////////////////////////////////////////////////////////////
  virtual void start();                                  // start generating tables
  virtual void add_state( State s, const State delta[]); // insert a new state
  virtual void add_state( State, int, const Symbol[], const State[]);
  virtual void finish();                                 // finish generating tables

  ///////////////////////////////////////////////////////////////////////////
  //  Method to advance thru the automaton.
  ///////////////////////////////////////////////////////////////////////////
  inline State go( register State s, register Symbol c) const
  {
    register State offset;
    while (check[offset = base[s] + c] != s)
      if ((s = def[s]) == 0)
        return 0;
    return next[offset];
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Emit the tables as C++ code.
  ///////////////////////////////////////////////////////////////////////////
  virtual std::ostream& gen_code( std::ostream&, const char []) const;
  virtual std::ostream& gen_check_next_tables( std::ostream&, const char [],
                                          const char * mytype = 0) const;
};

#endif
