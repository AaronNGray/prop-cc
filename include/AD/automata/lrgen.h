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

#ifndef LR_style_parser_generator_base_class_h
#define LR_style_parser_generator_base_class_h

#include <iostream>
#include <AD/automata/grammar.h>  // Parser grammar
#include <AD/automata/sparsdfa.h> // Compressed sparse dfa
#include <AD/automata/densedfa.h> // Compressed dense dfa


//////////////////////////////////////////////////////////////////////////////
//  Class LRGen represents the base class for all LR-style parser generator.
//  Since all LR-style parser utilize the same table representation,
//  this class implements some of the necessary operations.
//////////////////////////////////////////////////////////////////////////////

class LRGen : public DenseDFA
{
  LRGen( const LRGen&);              // no copy constructor
  void operator = ( const LRGen&);   // no assignment

public:

  /////////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  /////////////////////////////////////////////////////////////////////////
  // typedef SparseDFA               Super;
  typedef DenseDFA                Super;
  typedef Super::Symbol           Symbol;
  typedef Super::State            State;
  typedef Super::Rule             Rule;
  typedef Super::Offset           Offset;
  typedef Super::ProductionLength ProductionLength;
  typedef Super::EquivMap         EquivMap;

protected:

  /////////////////////////////////////////////////////////////////////////
  //  Error count
  /////////////////////////////////////////////////////////////////////////
  int shift_reduce_error_count;  // number of shift/reduce conflicts
  int reduce_reduce_error_count; // number of reduce/reduce conflicts

  void clear_errors()
  {
    shift_reduce_error_count = reduce_reduce_error_count = 0;
  }

  /////////////////////////////////////////////////////////////////////////
  //  Tables
  /////////////////////////////////////////////////////////////////////////
  int number_of_productions; // number of rules in the grammar
  int equiv_classes_size;    // size of the equivalance class table

  ProductionLength * len;    // mapping from rule number to production length
  ProductionLength * ncount; // number of non-terminals
  ShortSymbol      * lhs;    // left hand side non-terminal
  EquivMap         * equiv;  // mapping from symbols to equiv class number
  State            * defact; // mapping from state to default action
  State              final;  // final state

  /////////////////////////////////////////////////////////////////////////
  //  Redefine the state growth function
  /////////////////////////////////////////////////////////////////////////
  virtual void grow_states( int increment);

public:

  /////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////////////////////////

  LRGen();
  ~LRGen();

  /////////////////////////////////////////////////////////////////////////
  //  Get the final state
  /////////////////////////////////////////////////////////////////////////

  inline State final_state() const
  {
    return final;
  }

  /////////////////////////////////////////////////////////////////////////
  //  Table creation
  /////////////////////////////////////////////////////////////////////////

  virtual void create_tables( int size, int states, Symbol min, Symbol max);

  /////////////////////////////////////////////////////////////////////////
  //  Equivalence mapping
  /////////////////////////////////////////////////////////////////////////

  virtual void create_map( const Grammar&);
  inline int map_size() const
  {
    return equiv_classes_size;
  }

  /////////////////////////////////////////////////////////////////////////
  //  Table compilation and code generation
  /////////////////////////////////////////////////////////////////////////

  virtual void compile( const Grammar&);
  virtual std::ostream& gen_code( std::ostream&, const char []) const;

  /////////////////////////////////////////////////////////////////////////
  //  Error reporting
  /////////////////////////////////////////////////////////////////////////

  inline int shift_reduce_conflicts() const
  {
    return shift_reduce_error_count;
  }

  inline int reduce_reduce_conflicts() const
  {
    return reduce_reduce_error_count;
  }

  inline int conflicts() const
  {
    return shift_reduce_conflicts() + reduce_reduce_conflicts();
  }

  /////////////////////////////////////////////////////////////////////////
  //  Reporting
  /////////////////////////////////////////////////////////////////////////
  virtual std::ostream& print_report( std::ostream&, int verbosity = 0 ) = 0;
};

#endif
