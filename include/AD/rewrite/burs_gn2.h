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

#ifndef improved_bottom_up_rewrite_system_generator_h
#define improved_bottom_up_rewrite_system_generator_h

#include <AD/rewrite/burs_gen.h>  // BURS generator
#include <AD/automata/sparsdfa.h> // sparse DFA compression

//////////////////////////////////////////////////////////////////////////////
//
// The class New_BURS_Gen improves upon the class BURS_Gen
// by compressing the index maps using a sparse DFA compression
// algorithm.
//
//////////////////////////////////////////////////////////////////////////////

class New_BURS_Gen : public BURS_Gen
{
  New_BURS_Gen(const New_BURS_Gen&);        // no copy constructor
  void operator = (const New_BURS_Gen&);    // no assignment

  ///////////////////////////////////////////////////////////////////////////
  // Inherit some types from superclass and make them visible.
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef BURS_Gen           Super;
  typedef Super::Functor     Functor;     // functor
  typedef Super::Variable    Variable;    // pattern variable
  typedef Super::NonTerminal NonTerminal; // non-terminal in automata
  typedef Super::Arity       Arity;       // arity of functor
  typedef Super::State       State;       // state in tree automata
  typedef Super::Cost        Cost;        // reduction cost
  typedef Super::Rule        Rule;        // reduction rule number

  ///////////////////////////////////////////////////////////////////////////
  //  Internal members
  ///////////////////////////////////////////////////////////////////////////

protected:
  SparseDFA dfa_compiler;  // dfa table compression object
  int **    mu_index;      // mapping from functor x arity -> compressed index
  int       total_index_entries;     // size of all index maps together
  int       non_error_index_entries; // size of all non-empty index maps

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  New_BURS_Gen( Mem& );
  New_BURS_Gen( Mem&, TreeGrammar& );
  virtual ~New_BURS_Gen();

  ///////////////////////////////////////////////////////////////////////////
  //  Compilation and table emission methods.
  ///////////////////////////////////////////////////////////////////////////
  virtual void compile (TreeGrammar&);
  virtual void clear   ();

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the compressed index
  ///////////////////////////////////////////////////////////////////////////
  inline int compressed_index( Functor f, Arity i) const
  {
    return mu_index[f][i];
  }
  inline Offset compressed_offset( Functor f, Arity i) const
  {
    return dfa_compiler.state_offset(mu_index[f][i]);
  }
  virtual double compression_rate () const;

  ///////////////////////////////////////////////////////////////////////////
  //  Check for completeness.
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool   is_complete() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for code generation and report generation.
  ///////////////////////////////////////////////////////////////////////////
  virtual std::ostream& print_report (std::ostream& out) const;
  virtual std::ostream& gen_compressed_index (std::ostream& out, const char name[]) const;
};

#endif
