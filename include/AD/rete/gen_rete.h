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

#ifndef generalized_rete_network_h
#define generalized_rete_network_h

#include <AD/rete/fact.h>   // database facts
#include <AD/memory/mem.h>  // memory manager

//////////////////////////////////////////////////////////////////////////////
//
//  Class ReteInterp is an interpreter for a generalized Rete network.
//
//////////////////////////////////////////////////////////////////////////////

class ReteInterp
{
  ReteInterp      (const ReteInterp&);     // no copy constructor
  void operator = (const ReteInterp&);     // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Import types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef Fact::Age    Age;       // timestamp
  typedef Fact::RuleId RuleId;    // rule id
  typedef int          NodeId;    // node number;
  typedef int          JoinId;    // join id

  ///////////////////////////////////////////////////////////////////////////
  //  Definition of the network nodes.
  ///////////////////////////////////////////////////////////////////////////

  struct Node
  {
    enum Kind {
      ENTRY,      // network entry node
      HASH_ENTRY, // network entry node for hashed key entry
      SORT_ENTRY, // network entry node for sorted key entry
      FORK,       // fork node
      JOIN,       // linear join node
      HASH_JOIN,  // hashed join node
      SORT_JOIN,  // sorted key join node
      NOT,        // negation node
      HASH_NOT,   // hashed negation node
      SORT_NOT,   // sorted key negation node
      BOT         // bottom node
    } kind;
    NodeId left_input;   // left input node
    NodeId right_input;  // right input node
    NodeId child;        // child node
    JoinId join;         // join number(if any)
    short  left_arity;   // left arity
    short  arity;        // arity of token
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Internal members.
  ///////////////////////////////////////////////////////////////////////////

protected:
  Mem&             mem;              // internal memory manager.
  class AlphaMem * alpha_mem;        // alpha memory indexed by node number.
  class BetaMem  * beta_mem;         // beta memory indexed by node number.
  const Node *     network;          // the rete network in table format.
  const NodeId *   chain_table;      // tables of chains
  int              number_of_nodes;  // number of nodes in the network.
  int              number_of_facts;  // number of facts in the database.
  int              max_token_arity;  // maximum arity of tokens.

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for propagating tokens within the node.
  ///////////////////////////////////////////////////////////////////////////
  void insert_right (NodeId, Fact *);
  void insert_left  (NodeId, Fact **);
  void remove_right (NodeId, Fact *);
  void remove_left  (NodeId, Fact **);

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  ReteInterp(int N, const Node net[], const NodeId chain[]);
  virtual ~ReteInterp();

  ///////////////////////////////////////////////////////////////////////////
  //  Method to return the name of the rete network class.
  ///////////////////////////////////////////////////////////////////////////
  virtual const char * name_of() const;

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to enter/remove tokens from the conflict set.
  ///////////////////////////////////////////////////////////////////////////
  virtual void activate   (RuleId, int, Fact * []);
  virtual void deactivate (RuleId, int, Fact * []);

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to assert and retract facts from the network.
  ///////////////////////////////////////////////////////////////////////////
  virtual void clear        ();
  virtual void assert_fact  (Fact *);
  virtual void retract_fact (Fact *);
  inline ReteInterp& operator << (Fact * f)
  {
    assert_fact(f);
    return *this;
  }
  inline ReteInterp& operator =  (Fact * f)
  {
    assert_fact(f);
    return *this;
  }
  inline ReteInterp& operator ,  (Fact * f)
  {
    assert_fact(f);
    return *this;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for driving the inference.
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool is_stable() = 0; // is the conflict set empty?
  virtual void fire     ();     // fire one rule
  virtual void infer    ();     // fire all rules

  ///////////////////////////////////////////////////////////////////////////
  //  The following methods can be (re)defined by the clients.
  ///////////////////////////////////////////////////////////////////////////

protected:
  virtual void alpha_test        ( Fact * ) = 0;
  virtual int  beta_test         ( JoinId, Fact * [] ) = 0;
  virtual void action            ( RuleId, Fact * [] ) = 0;
  virtual void initialise_axioms () = 0;
};

#endif
