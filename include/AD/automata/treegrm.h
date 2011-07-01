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

#ifndef regular_tree_grammar_h
#define regular_tree_grammar_h

#include <iostream>
#include <new>
#include <AD/generic/generic.h>
#include <AD/automata/treetab.h>
#include <AD/memory/mem.h>


//////////////////////////////////////////////////////////////////////////////
//  Tree grammar
//////////////////////////////////////////////////////////////////////////////

class TreeGrammar : public TreeTables
{

  TreeGrammar( const TreeGrammar&);       // no copy constructor
  void operator = ( const TreeGrammar&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Inport inherited types
  ///////////////////////////////////////////////////////////////////////////
  typedef TreeTables     Super;
  typedef Super::Functor Functor;
  typedef Super::Functor Variable;
  typedef Super::Arity   Arity;
  typedef Super::State   State;

  const int Max_arity = 256;

  ///////////////////////////////////////////////////////////////////////////
  //  Definition of a tree term
  ///////////////////////////////////////////////////////////////////////////
  class TreeTerm
  {
  public:
    ////////////////////////////////////////////////////////////////////////
    //  Internal representation
    ////////////////////////////////////////////////////////////////////////
    enum { Var, Or, And, Not, Term, Set } tag;
    union {
      struct TERM
      {
        Functor f;
        Arity n;
        TreeTerm * subterms[1];
      } term;
      Variable var;
      struct AND
      {
        TreeTerm * x;
        TreeTerm * y;
      } and;
      struct OR
      {
        TreeTerm * x;
        TreeTerm * y;
      } or;
      TreeTerm* not;
      class BitSet* set;
    };

    ////////////////////////////////////////////////////////////////////////
    //  Memory management
    ////////////////////////////////////////////////////////////////////////
    inline void * operator new( size_t s, Mem& m)
    {
      return m.m_alloc(s);
    }
    inline void * operator new(size_t s, Mem& m, Variable v)
    {
      TreeTerm * t = (TreeTerm *)m.m_alloc(s);
      t->tag = Var;
      t->var = v;
      return t;
    }
    inline void * operator new(size_t s, Mem& m, TreeTerm * x, TreeTerm * y)
    {
      TreeTerm * t = (TreeTerm *)m.m_alloc(s);
      t->tag = And;
      t->and.x = x;
      t->and.y = y;
      return t;
    }
    inline void * operator new(size_t s, Mem& m, TreeTerm * x, TreeTerm * y, int)
    {
      TreeTerm * t = (TreeTerm *)m.m_alloc(s);
      t->tag = Or;
      t->or.x = x;
      t->or.y = y;
      return t;
    }
    inline void * operator new(size_t s, Mem& m, TreeTerm * x)
    {
      TreeTerm * t = (TreeTerm *)m.m_alloc(s);
      t->tag = Or;
      t->not = x;
      return t;
    }
    inline void * operator new(size_t s, Mem& m, class BitSet * set
                                )
    {
      TreeTerm * t = (TreeTerm *)m.m_alloc(s);
      t->tag = Set;
      t->set
      = set
          ;
      return t;
    }
    inline void * operator new(size_t s, Mem& m, Functor f, Arity n, TreeTerm * subterms[])
    {
      TreeTerm * t = (TreeTerm *)m.m_alloc(s + (n-1) * sizeof(TreeTerm*));
      t->tag = Term;
      t->term.f = f;
      t->term.n = n;
      for (int i = n - 1; i >= 0; i--)
        t->term.subterms[i] = subterms[i];
      return t;
    }
    inline void * operator new(size_t s, Mem& m, Functor f, Arity n)
    {
      TreeTerm * t = (TreeTerm *)m.m_alloc(s + (n-1) * sizeof(TreeTerm*));
      t->tag = Term;
      t->term.f = f;
      t->term.n = n;
      return t;
    }
    inline void   operator delete(void *)
    { }

    ////////////////////////////////////////////////////////////////////////
    //  Equality and hashing
    ////////////////////////////////////////////////////////////////////////
    friend Bool equal(const TreeTerm *, const TreeTerm *);
    friend unsigned int hash(const TreeTerm *);
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Definition of a tree production
  ///////////////////////////////////////////////////////////////////////////
  struct TreeProduction
  {
    Variable   var;
    TreeTerm * term;
    TreeProduction()
      {}
    TreeProduction(Variable v, TreeTerm * t) : var(v), term(t)
      {}
  }
  ;

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Internals
  ///////////////////////////////////////////////////////////////////////////
  Arity          * arities;                // mapping from functors to arity
  TreeProduction * productions;
  int              number_of_productions;
  int              number_of_functors;
  int              number_of_variables;
  Functor          maximum_functor;
  Functor          minimum_functor;
  Variable         minimum_variable;
  Variable         maximum_variable;
  int              maximum_arity;

  void tabulate(const TreeTerm *);
  void tabulate_arity(const TreeTerm *);

private:

  void init();  // method to initialize the class

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  TreeGrammar();
  TreeGrammar( int n, TreeProduction []);
  virtual ~TreeGrammar();

  ///////////////////////////////////////////////////////////////////////////
  //  Compile a set of tree productions
  ///////////////////////////////////////////////////////////////////////////
  void compile( int n, TreeProduction []);

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline TreeProduction& operator [] (int i)
  {
    return productions[i];
  }

  inline const TreeProduction& operator [] (int i) const
  {
    return productions[i];
  }

  inline void update( int i, TreeTerm * t)
  {
    productions[i].term = t;
  }

  inline int size() const
  {
    return number_of_productions;
  }

  inline Arity arity( Functor f) const
  {
    return arities[f];
  }

  inline Functor min_functor() const
  {
    return minimum_functor;
  }

  inline Functor max_functor() const
  {
    return maximum_functor;
  }

  inline Variable min_variable() const
  {
    return minimum_variable;
  }

  inline Variable max_variable() const
  {
    return maximum_variable;
  }

  inline int max_arity() const
  {
    return maximum_arity;
  }

  inline int functors() const
  {
    return number_of_functors;
  }

  inline int variables() const
  {
    return number_of_variables;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Printing
  ///////////////////////////////////////////////////////////////////////////
  std::ostream& print( std::ostream& out,
                  const TreeTerm * term,
                  const char * functor_names[],
                  const char * variable_names[] ) const;
};

#endif
