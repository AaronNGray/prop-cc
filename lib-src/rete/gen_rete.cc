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

#include <iostream>
#include <AD/rete/gen_rete.h>    // generalised Rete network
#include <AD/rete/alphamem.h>    // alpha memory
#include <AD/rete/betamem.h>     // beta memory
#include <AD/memory/boundtag.h>  // generic memory manager
#include <AD/memory/arena.h>     // free list memory manager

//////////////////////////////////////////////////////////////////////////////
//  Class Constructor
//////////////////////////////////////////////////////////////////////////////

ReteInterp:: ReteInterp(int N, const Node net[], const NodeId chain[])
    : mem             (* new BoundaryTag(4096)),
    alpha_mem       (new AlphaMem [ N ]),
    beta_mem        (new BetaMem  [ N ]),
    network         (net),
    chain_table     (chain),
    number_of_nodes (N),
    number_of_facts (0),
    max_token_arity (0)
{}

//////////////////////////////////////////////////////////////////////////////
//  Class Destructor
//////////////////////////////////////////////////////////////////////////////

ReteInterp::~ReteInterp()
{
  delete (&mem);
  delete [] alpha_mem;
  delete [] beta_mem;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to return the name of the rete network.
//////////////////////////////////////////////////////////////////////////////

const char * ReteInterp::name_of() const
{
  return "ReteInterp";
}

//////////////////////////////////////////////////////////////////////////////
//  Method to clear all the database, alpha and beta memory
//////////////////////////////////////////////////////////////////////////////

void ReteInterp::clear()
{  //
  // Since all the memory is allocated from the our memory manager,
  // we'll simply reset of the manager and reallocate all the alpha
  // and beta memory.
  //
  mem.clear();
  delete [] alpha_mem;
  delete [] beta_mem;
  alpha_mem = new AlphaMem [ number_of_nodes ];
  beta_mem  = new BetaMem  [ number_of_nodes ];
  number_of_facts = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to run the inference engine until equilibrium.
//////////////////////////////////////////////////////////////////////////////

void ReteInterp::infer()
{
  while (! is_stable())
    fire();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to insert a fact into the right side of a node
//////////////////////////////////////////////////////////////////////////////

void ReteInterp::insert_right( NodeId n, Fact* fact)
{
  const Node& node = network[n];
  switch (node.kind)
  {
    ////////////////////////////////////////////////////////////////////////
    // Memorize fact in alpha memory and distribute the fact to the
    // sub-network.
    ////////////////////////////////////////////////////////////////////////
  case Node::ENTRY:
    alpha_mem[n].add_fact(mem, fact);

    ////////////////////////////////////////////////////////////////////////
    // Propagate fact into the sub-network
    ////////////////////////////////////////////////////////////////////////
  case Node::FORK:
    {
      for (int i = node.child; chain_table[i] >= 0; i++)
        insert_right(chain_table[i], fact);
    }
    break;

    ////////////////////////////////////////////////////////////////////////
    // Compute join using linear search
    ////////////////////////////////////////////////////////////////////////
  case Node::JOIN:
    {
      BetaMem& b = beta_mem [node.left_input];
      for (int i = b.size() - 1; i >= 0; i--)
      {
        Fact ** token = b[i];
        token [ node.left_arity ] = fact;
        if (node.join == 0 || beta_test(node.join, token))
          insert_left (node.child, token);
      }
    }
    break;

    ////////////////////////////////////////////////////////////////////////
    // Compute negation using linear search
    ////////////////////////////////////////////////////////////////////////
  case Node::NOT:
    {
      BetaMem& b = beta_mem [node.left_input];
      for (int i = b.size() - 1; i >= 0; i--)
      {
        Fact ** token = b[i];
        token [ node.left_arity ] = fact;
        if (node.join == 0 || beta_test(node.join, token))
          if (b.inc_neg(i))
            remove_left(node.child, token);
      }
    }
    break;

    ////////////////////////////////////////////////////////////////////////
    // Insert token into the conflict set
    ////////////////////////////////////////////////////////////////////////
  case Node::BOT:
    activate(node.child, 1, &fact);
    break;
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to insert a fact into the left side of a node
//////////////////////////////////////////////////////////////////////////////

void ReteInterp::insert_left( NodeId n, Fact* token[])
{
  const Node& node = network[n];
  switch (node.kind)
  {
  case Node::ENTRY:
    break;

    ////////////////////////////////////////////////////////////////////////
    // Propagate fact into the sub-network
    ////////////////////////////////////////////////////////////////////////
  case Node::FORK:
    {
      for (int i = node.child; chain_table[i] >= 0; i++)
        insert_left(chain_table[i], token);
    }
    break;

    ////////////////////////////////////////////////////////////////////////
    // Compute join using linear search
    ////////////////////////////////////////////////////////////////////////
  case Node::JOIN:
    {
      AlphaMem& a = alpha_mem[ node.right_input ];
      for (int i = a.size() - 1; i >= 0; i--)
      {
        token[ node.left_arity ] = a[i];
        if (node.join == 0 || beta_test(node.join, token))
          insert_left (node.child, token);
      }
    }
    break;

    ////////////////////////////////////////////////////////////////////////
    // Compute negation using linear search
    ////////////////////////////////////////////////////////////////////////
  case Node::NOT:
    {
      AlphaMem& a = alpha_mem[ node.right_input ];
    }
    break;

  case Node::BOT:
    activate(node.child, node.arity, token);
    break;
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to removes a fact
//////////////////////////////////////////////////////////////////////////////

void ReteInterp::remove_right( NodeId n, Fact* fact)
{
  const Node& node = network[n];
  switch (node.kind)
  {
  case Node::ENTRY:
  case Node::FORK:
  case Node::JOIN:
  case Node::BOT:
  case Node::NOT:
    deactivate(node.child, 1, &fact);
    break;
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to removes a fact from the left
//////////////////////////////////////////////////////////////////////////////

void ReteInterp::remove_left( NodeId n, Fact* token[])
{
  const Node& node = network[n];
  switch (node.kind)
  {
  case Node::ENTRY:
  case Node::FORK:
  case Node::JOIN:
  case Node::BOT:
  case Node::NOT:
    deactivate(node.child, node.arity, token);
    break;
  default:
    break;
  }
}
