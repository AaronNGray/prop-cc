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

#ifndef binary_decision_diagrams_h
#define binary_decision_diagrams_h

//////////////////////////////////////////////////////////////////////////////
// Binary Decision Diagrams (BDD)\cite{bool-diag}
// for computing boolean functions.   BDDs are maximally reduced
// binary dag structure used to represent boolean functions.  A
// BDD is characterized as follows:
//   (a) A finite linear ordered set of boolean variable names $x_i$ are
//       used to label each non-leaf node such that given two nodes
//       $a$ and $b$, if $a$ is a descendent of $b$ then, $var(a) > var(b)$.
//   (b) A leaf node is labeled either 0 or 1.
//   (c) No node points to the same dag on both its branches.
//   (d) No two subdags are isomorphic.  That is, all isomorphic
//       subdags are merged.
//
// Class |BDDSet| represents a set of boolean functions, each one
// is of type |BDDSet::BDD|.
//////////////////////////////////////////////////////////////////////////////

#include <new.h>
#include <AD/generic/generic.h>  // Generic definitions

//////////////////////////////////////////////////////////////////////////////
//  Class BDDSet actually implements a collection of BDD's.  All BDD's
//  must be allocated from the same system and operations are assumed to
//  be performed on BDD's in the same system.
//
//  An BDDSet object manages the storage used during the BDDs computation.
//  It performs internal garbage collection and compaction transparently
//  from the client program.
//////////////////////////////////////////////////////////////////////////////

class BDDSet
{
  BDDSet(const BDDSet&);            // no copy constructor
  void operator = (const BDDSet&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions.
  ///////////////////////////////////////////////////////////////////////////

public:
  enum Op {                           // Binary boolean operations
    Not,                             // negation
    And,                             // conjunction
    Or,                              // disjunction
    Nor,                             //
    Nand,                            //
    Xor,                             // exclusive or
    Xnor,                            // exclusive nor
    Restrict
  };
  typedef int  Var;   // Function variable names
  typedef long BDD;   // a BDD

  //  A BDD node.
  struct BDDNode
  {
    Var var;                  // name of variable
    BDD branches[2];          // the two branches
    inline BDDNode()
    {}
    inline BDDNode(Var v, BDD l, BDD r)
        : var(v)
    {
      branches[0] = l;
      branches[1] = r;
    }
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Given an BDD, we'll use 0 to denote the fixed encoding for the zero
  //  function and 1 to denote the one function.  This means that
  //  it is not possible to negate a function in constant time (but in
  //  linear time).  However,  with less sharing it is easier to
  //  perform garbage collection.
  //
  //  Allen.
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //  Internal definitions.
  ///////////////////////////////////////////////////////////////////////////

protected:
  BDDNode  * bdds;            // array of bdds
  BDDNode  * bdd_next;        // next available node
  BDDNode  * bdd_limit;       // limit
  BDDNode  * bdd_highwater;   // highwater
  BDDNode  * bdd_last;        //
  BDD *      bdd_roots;       // roots
  int        bdd_count;       // number of bdds used
  int        bdd_capacity;    // capacity of the bdds array.
  class BDDTable * table;     // internal hash table.
  class BDDMemo  * memo;      // for memorization during computation.

  ////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor.
  ////////////////////////////////////////////////////////////////////////

public:
  BDDSet(size_t default_nodes = 1024);
  virtual ~BDDSet();

  ////////////////////////////////////////////////////////////////////////
  //  Initialization
  ////////////////////////////////////////////////////////////////////////
  virtual void clear();

  ////////////////////////////////////////////////////////////////////////
  //  Selectors
  ////////////////////////////////////////////////////////////////////////
  inline int size     () const
  {
    return bdd_count;
  }
  inline int capacity () const
  {
    return bdd_capacity;
  }
  inline Var var_of   (BDD f) const
  {
    return bdds[f].var;
  }
  inline const BDD * operator () (BDD f) const
  {
    return bdds[f].branches;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Roots in the set
  ////////////////////////////////////////////////////////////////////////
  inline BDD operator [] (int i) const
  {
    return bdd_roots[i];
  }
  void kill (BDD f);  // delete f from the set

  ////////////////////////////////////////////////////////////////////////
  //  Operations
  ////////////////////////////////////////////////////////////////////////
  virtual BDD apply    (Op op, BDD f, BDD g);
  virtual BDD restrict (BDD f, Var var, BDD value);
  virtual BDD negate   (BDD f);

  ///////////////////////////////////////////////////////////////////////////
  //  Garbage collection
  ///////////////////////////////////////////////////////////////////////////
  virtual void collect(); // invoke garbage collection

  ///////////////////////////////////////////////////////////////////////////
  //  Internals methods
  ///////////////////////////////////////////////////////////////////////////

private:
  BDD  hash_cons   (Var v, BDD f, BDD g); // create a node
  BDD  do_apply    (Op op, BDD f, BDD g);
  BDD  do_restrict (BDD f, Var var, BDD value);
  BDD  do_negate   (BDD f);
  virtual void do_collect (); // garbage collection
  void add_root    (BDD f);
};

#endif
