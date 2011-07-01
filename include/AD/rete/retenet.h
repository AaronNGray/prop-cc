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

#ifndef Rete_based_network_h
#define Rete_based_network_h

////////////////////////////////////////////////////////////////////////////
//  The base class |ReteNet| represents a discriminent network used within
//  the Rete algorithm.   It is an abstract class: the conflict resolution
//  strategy and the agenda data structure is not implemented here
//  but is assumed to be implemented in derived classes.
//
//  Instead, this class handles the filtering within the network
//  and manages the alpha/beta memory.
////////////////////////////////////////////////////////////////////////////

#include <AD/rete/fact.h>   // a fact
#include <AD/memory/mem.h>  // memory manager

class ReteNet
{
  ReteNet(const ReteNet&);            // no copy constructor
  void operator = (const ReteNet&);   // no assignment

  ////////////////////////////////////////////////////////////////////////
  // Internal types
  ////////////////////////////////////////////////////////////////////////

public:
  typedef int          RuleId;          // identifier for a rule
  typedef int          NodeId;          // identifier for a node
  typedef int          Priority;        // rule priority
  typedef Fact::Age    Age;             // age of fact
  typedef Fact::RelTag RelTag;          // a relation tag
  typedef Fact **      Token;           // a token
  typedef int          Join;            // a join test

  ////////////////////////////////////////////////////////////////////////
  // Alpha and beta memory.
  ////////////////////////////////////////////////////////////////////////

  struct AlphaMemo
  {
    int count;
    int capacity;
    Fact ** facts;
  };
  struct BetaMemo
  {
    int count;
    int capacity;
    int * matches;
    Token * tokens;
  };

  ////////////////////////////////////////////////////////////////////////
  //  Network structure
  ////////////////////////////////////////////////////////////////////////
  struct Node
  {
    short  beta_arity,   // length of token up to this point.
    arity;        // length of the entire token
    enum { Alpha,        // network entry node
           Test,         // predicate test
           And,          // join test
           Not,          // non-existence test
           Fork,         // distribute token into branches
           Bot           // bottom of network.
         } kind;
    Join   join;         // join test, if any
    NodeId child;        // child of node, or rule id
  };

  ////////////////////////////////////////////////////////////////////////
  //  Internal data structure
  ////////////////////////////////////////////////////////////////////////

protected:
  Mem&         mem;              // Internal memory manager
  int          number_of_nodes;  // number of nodes within the net
  const Node * network;          // a table of nodes indexed by node number
  AlphaMemo  * alpha;            // alpha memory array
  BetaMemo   * beta;             // beta memory array

  /////////////////////////////////////////////////////////////////////
  // Functions for memorization.
  /////////////////////////////////////////////////////////////////////

private:
  void memorize_beta        (NodeId, Fact * []);
  void memorize_not_on_beta (NodeId, int, Fact * []);
  void memorize_alpha       (NodeId, Fact *);

  /////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  /////////////////////////////////////////////////////////////////////

public:
  ReteNet(int nodes, const Node []);
  virtual ~ReteNet();

  /////////////////////////////////////////////////////////////////////
  //  Method to clears all alpha/beta memory
  /////////////////////////////////////////////////////////////////////
  virtual void clear();

  /////////////////////////////////////////////////////////////////////
  // Conflict resolution.  These are to be implemented in derived
  // classes.
  /////////////////////////////////////////////////////////////////////
  virtual void activate   (RuleId, int, Fact * []) = 0;
  virtual void deactivate (RuleId, int, Fact * []) = 0;
  virtual void fire       () = 0;
  virtual Bool is_stable  () const = 0;
  virtual void infer      () = 0;

  /////////////////////////////////////////////////////////////////////
  // Functions to assert/retract facts from the database.
  /////////////////////////////////////////////////////////////////////
  virtual ReteNet& assert_fact  (Fact * fact) = 0;
  virtual ReteNet& retract_fact (Fact * fact) = 0;
  inline ReteNet& operator << (Fact * f)
  {
    return assert_fact(f);
  }
  inline ReteNet& operator += (Fact * f)
  {
    return assert_fact(f);
  }
  inline ReteNet& operator -= (Fact * f)
  {
    return retract_fact(f);
  }

  /////////////////////////////////////////////////////////////////////
  // Functions for token propagation between nodes.
  /////////////////////////////////////////////////////////////////////
  void insert_beta  (NodeId, Fact * []);
  void insert_alpha (NodeId, Fact *);
  void remove_beta  (NodeId, Fact * []);
  void remove_alpha (NodeId, Fact *);
  virtual int  beta_test    (Join, Fact * []) = 0;
  virtual void alpha_test   (int, int, Fact *) = 0;
};

#endif
