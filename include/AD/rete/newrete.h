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

#ifndef RETE_matching_network_h
#define RETE_matching_network_h

#include <AD/rete/fact.h>
#include <AD/memory/mem.h>

//////////////////////////////////////////////////////////////////////////////
//  Class Rete represents a RETE matching network.
//////////////////////////////////////////////////////////////////////////////

class Rete
{
  Rete(const Rete&);              // no copy constructor
  void operator = (const Rete&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Various types.
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef int    NodeId;                // node number
  typedef int    RuleId;                // rule number
  typedef int    Priority;              // rule priority
  typedef Fact * Token;                 // a token is an array of facts
  typedef int (*Join)(const Fact * []); // join test

  ///////////////////////////////////////////////////////////////////////////
  //  A network node.
  ///////////////////////////////////////////////////////////////////////////
  struct Node
  {
    enum { And, Not, Bot } kind;       // kind of node
    NodeId                 child;      // child node (or rule id)
    Join                   join;       // join test (if any)
    int                    left_arity; // length of token formed so far.
    int                    arity;      // length of the whole token.
  };

  ///////////////////////////////////////////////////////////////////////////
  //  Internal data structure
  ///////////////////////////////////////////////////////////////////////////

protected:
  Mem&                mem;              // internal memory manager
  int                 number_of_nodes;  // network nodes count
  const Node        * network;          // the network in array form
  class AlphaMemory * alpha_mem;        // alpha memory in array form
  class BetaMemory  * beta_mem;         // beta memory in array form

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  Rete(int N, const Node net[]); // create the network
  virtual ~Rete();                        // destroy the network

  ///////////////////////////////////////////////////////////////////////////
  //  Method to clears the method of facts and alpha/beta memories.
  ///////////////////////////////////////////////////////////////////////////
  virtual void clear();

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to assert and retract facts from the network
  ///////////////////////////////////////////////////////////////////////////
  inline void assert_fact  (Fact & fact)
  {
    fact.assert_fact(*this);
  }
  inline void assert_fact  (Fact * fact)
  {
    fact->assert_fact(*this);
  }
  inline void retract_fact (Fact & fact)
  {
    fact.retract_fact(*this);
  }
  inline void retract_fact (Fact * fact)
  {
    fact->retract_fact(*this);
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods to insert tokens into the left and right sides of the net.
  ///////////////////////////////////////////////////////////////////////////
  void insert_left  (NodeId, Fact * []);
  void insert_right (NodeId, Fact *);
  void remove_left  (NodeId, Fact * []);
  void remove_right (NodeId, Fact *);

  ///////////////////////////////////////////////////////////////////////////
  //  Method to execute a rule, must be defined by derive class.
  ///////////////////////////////////////////////////////////////////////////
  virtual void fire (Fact * []) = 0;
};
