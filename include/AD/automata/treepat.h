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

#ifndef tree_patterns_h
#define tree_patterns_h

//////////////////////////////////////////////////////////////////////////
//  Class |TreePatterns| represents a set of linear term patterns used
// for tree matching.
//////////////////////////////////////////////////////////////////////////

#include <new>
#include <AD/generic/generic.h>
#include <AD/memory/mempool.h>
#include <AD/automata/treeauto.h>


struct TreePat
{
  typedef TreeAutomaton::Functor Functor;   // A functor (i.e. constructor)
  typedef TreeAutomaton::Arity   Arity;     // Arity of a functor

  Functor   f;                     // functor
  Arity     n;                     // arity
  TreePat * subterms[1];           // array of subterms, if any

  Functor tag() const
  {
    return f;
  }

  int arity() const
  {
    return n;
  }

  TreePat* nth( int i) const
  {
    return subterms[i];
  }

  Bool isVar() const
  {
    return f < 0;
  }

  friend Bool isWild( const TreePat * p)
  {
    return p == 0;
  }

  void * operator new
  (size_t, MemPool& p, Functor f, Arity n = 0, TreePat * s[] = 0)
  {
    TreePat * t =
      (TreePat*)p.m_alloc(sizeof(TreePat) + (n-1) * sizeof(TreePat*));
    t->f = f;
    t->n = n;
    for (register int i = n - 1; i >= 0; i--)
      t->subterms[i] = s[i];
    return t;
  }

  void operator delete (void *)
  {}
}
;

struct TreePatBuf
{
  TreePat p;
  TreePat * s[256];
};

class TreePatterns
{

  TreePatterns(const TreePatterns&);        // no copy constructor
  void operator = (const TreePatterns&);   // no assignment

public:

  typedef TreePat::Functor  Functor;
  typedef TreePat::Arity    Arity;

protected:

  Arity *    rank;                 // functor to arity mapping
  TreePat ** patterns;             // a set of patterns
  int        number_of_patterns;   // number of patterns
  Functor    maximum_functor;      // maximum functor value
  Functor    minimum_functor;      // minimum functor value
  Arity      maximum_arity;        // maximum arity of all functors
  int        maximum_nodes;        // maximum number of nodes in a pattern
  Functor    minimum_variable;     // minimum code of variables
  Functor    maximum_variable;     // maximum code of variables

  int  tabulate_limits  (TreePat *);
  void tabulate_arities (TreePat *);

public:

  TreePatterns();
  ~TreePatterns();

  void compile( int n, TreePat * []);

  Arity max_arity() const
  {
    return maximum_arity;
  }

  Functor min_functor() const
  {
    return minimum_functor;
  }

  Functor max_functor() const
  {
    return maximum_functor;
  }

  Functor min_variable() const
  {
    return minimum_variable;
  }

  Functor max_variable() const
  {
    return maximum_variable;
  }

  int max_nodes() const
  {
    return maximum_nodes;
  }

  int functors() const
  {
    return max_functor() - min_functor() + 1;
  }

  int variables() const
  {
    return max_variable() - min_variable() + 1;
  }

  int size() const
  {
    return number_of_patterns;
  }

  TreePat* operator [] ( int i) const
  {
    return patterns[i];
  }

  Arity arity( Functor f) const
  {
    return rank[f];
  }

  void update( int i, TreePat * p)
  {
    patterns[i] = p;
  }
};

#endif
