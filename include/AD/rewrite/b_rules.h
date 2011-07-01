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

#ifndef BURS_normalised_reduction_ruleset_h
#define BURS_normalised_reduction_ruleset_h

#include <iostream>
#include <AD/automata/treegram.h> // tree grammar
#include <AD/memory/mem.h>        // memory manager
#include <AD/contain/slnklist.h>  // singly linked lists

//////////////////////////////////////////////////////////////////////////////
//  Class BURS_RuleSet below represents a set of normalised(i.e. canonical)
//  tree rewrite rules.  This representation is computed from the tree
//  grammar form to speed up table computation in the BURS generator.
//////////////////////////////////////////////////////////////////////////////

class BURS_RuleSet
{
  BURS_RuleSet(const BURS_RuleSet&);      // no copy constructor
  void operator = (const BURS_RuleSet&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef TreeGrammar::Functor     Functor;
  typedef TreeGrammar::Arity       Arity;
  typedef TreeGrammar::NonTerminal NonTerminal;
  typedef TreeGrammar::Cost        Cost;
  typedef TreeGrammar::Rule        Rule;

  ///////////////////////////////////////////////////////////////////////////
  //  Class LeafReduction represents a normalized production of the form:
  //     lhs -> f;
  ///////////////////////////////////////////////////////////////////////////
  struct LeafReduction
  {
    NonTerminal lhs;      // left hand side non-terminal
    Functor     f;        // head functor
    Cost        cost;     // cost of reduction
    Rule        rule;     // reduction rule number
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Class Reduction represents a normalized production
  //     lhs -> f (x_1, x_2, ..., x_n);
  ///////////////////////////////////////////////////////////////////////////

  struct Reduction : public LeafReduction
  {
    Arity       n;        // arity of functor
    NonTerminal rhs[1];   // functor arguments

    ////////////////////////////////////////////////////////////////////////
    // Memory management routines
    ////////////////////////////////////////////////////////////////////////
    inline void * operator new(size_t, Mem& mem, int k)
    {
      return mem.c_alloc(sizeof(Reduction) + sizeof(NonTerminal) * (k-1));
    }
    inline void   operator delete(void *)
    {}
  }
  ;

  typedef SLinkList<Reduction *> ReductionList;

  ///////////////////////////////////////////////////////////////////////////
  //  Class ChainRule represents a chain rule:  A -> B
  ///////////////////////////////////////////////////////////////////////////
  struct ChainRule
  {
    NonTerminal lhs;    // A
    NonTerminal rhs;    // B
    Cost        cost;   // cost of the chain rule reduction
    Rule        rule;   // reduction rule number
  };

private:

  ///////////////////////////////////////////////////////////////////////////
  //  Internal representation.
  ///////////////////////////////////////////////////////////////////////////
  class BURS_RuleSet_Impl * impl;             // internal stuff
  const TreeGrammar& G;                       // the tree grammar
  LeafReduction *    leaf_reduction_table;    // A -> c
  Reduction **       reduction_table;         // A -> f(A_1, ..., A_n)
  ChainRule *        chain_rule_table;        // A -> B
  int                leaf_reduction_count;    // A -> c
  int                reduction_count;         // A -> f(A_1, ..., A_n)
  int                chain_rule_count;        // A -> B
  ReductionList **   reductions;              // list of reductions indexed by functor
  NonTerminal        non_terminal_count;      // number of non-terminals in
  // canonical grammar
  Bool               has_wild_card;           // wild cards in grammar?
  TreeTerm *         non_term_to_tree;        // mapping from non-term to tree

  ///////////////////////////////////////////////////////////////////////////
  //  Helper methods
  ///////////////////////////////////////////////////////////////////////////
  void        count_rules   (TreeTerm);
  NonTerminal add_reduction (Mem&, Rule, TreeTerm, Cost);

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor.
  ///////////////////////////////////////////////////////////////////////////
  BURS_RuleSet ( Mem&, const TreeGrammar& );
  ~BURS_RuleSet ();

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors.
  ///////////////////////////////////////////////////////////////////////////
  inline int number_of_reductions       ()      const
  {
    return reduction_count;
  }
  inline int number_of_leaf_reductions  ()      const
  {
    return leaf_reduction_count;
  }
  inline int number_of_chain_rules      ()      const
  {
    return chain_rule_count;
  }
  inline int number_of_non_terminals    ()      const
  {
    return non_terminal_count;
  }
  inline const LeafReduction& leaf      (int i) const
  {
    return leaf_reduction_table[i];
  }
  inline const Reduction&     reduction (int i) const
  {
    return *reduction_table[i];
  }
  inline const ChainRule&     chain_rule(int i) const
  {
    return chain_rule_table[i];
  }
  inline const ReductionList * reductions_of(Functor f) const
  {
    return reductions[f];
  }
  inline Bool  contains_wild_card() const
  {
    return has_wild_card;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for printing.
  ///////////////////////////////////////////////////////////////////////////
  std::ostream& print (std::ostream&, const LeafReduction&) const;
  std::ostream& print (std::ostream&, const Reduction&)     const;
  std::ostream& print (std::ostream&, const ChainRule&)     const;
  std::ostream& print (std::ostream&, NonTerminal)          const;
  friend std::ostream& operator << (std::ostream&, const BURS_RuleSet&);
};

#endif
