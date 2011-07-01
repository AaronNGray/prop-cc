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

/////////////////////////////////////////////////////////////////
//  This file implements the memorization and token propagation
//  routines used by the Rete matching algorithm.
/////////////////////////////////////////////////////////////////

#include <AD/rete/retenet.h>
#include <AD/memory/boundtag.h>

/////////////////////////////////////////////////////////////////
//  A description of the data structures:
//  There are 3 kinds of nodes within the network.
//  (1) And nodes: these nodes have a left and a right input.
//      A new token, computed as the concatention of the
//      two inputs, is propagate to its output node if the new
//      token satisfies the node test.
//  (2) Not nodes: these nodes also have a left and a right input.
//      The token from the left node is propagated only if
//      there is no input from the right.
//  (3) Terminal nodes: when a token arrives at these nodes it
//      will be added to the conflict set.
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Make hidden types visible at top level
/////////////////////////////////////////////////////////////////

typedef ReteNet::NodeId NodeId;
typedef ReteNet::RuleId RuleId;
typedef ReteNet::Token  Token;
typedef ReteNet::Node   Node;

/////////////////////////////////////////////////////////////////
//  Constructor for class
/////////////////////////////////////////////////////////////////

ReteNet::ReteNet( int N, const Node net[])
    : mem(* new BoundaryTag(4096)),  // create new memory manager
    number_of_nodes(N),
    network (net)
{
  // set up alpha and beta memory.
  alpha = (AlphaMemo*) mem.c_alloc(sizeof(AlphaMemo) * N);
  beta  = (BetaMemo*)  mem.c_alloc(sizeof(BetaMemo) * N);
}

/////////////////////////////////////////////////////////////////
//  Destructor for class
/////////////////////////////////////////////////////////////////

ReteNet::~ReteNet()
{
  delete (&mem);
}

/////////////////////////////////////////////////////////////////
//  Clears all alpha/beta memory
/////////////////////////////////////////////////////////////////

void ReteNet::clear()
{
  mem.clear();  // reset the memory manager
  // reallocate all alpha/beta memory
  alpha = (AlphaMemo*) mem.c_alloc(sizeof(AlphaMemo) * number_of_nodes);
  beta  = (BetaMemo*)  mem.c_alloc(sizeof(BetaMemo) * number_of_nodes);
}

/////////////////////////////////////////////////////////////////
//  Fast inlined copy
/////////////////////////////////////////////////////////////////

template<class T>
inline void copy (register T * dest, register T * src, register int n)
{
  for ( ; n > 0; n--)
    *dest++ = *src++;
}

/////////////////////////////////////////////////////////////////
//  Routines for memorization management
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//  Method: memorize_beta(...)
//    This method addes a new token ``facts'' to the beta memory
//  of a node; the beta memory is resized if necessary.
/////////////////////////////////////////////////////////////////

inline void ReteNet::memorize_beta( NodeId n, Fact** facts)
{
  register BetaMemo& memo = beta[n];
  if (memo.count == memo.capacity)
  {
    int new_capacity  = memo.capacity * 3 / 2 + 2;
    Token * new_facts = (Token *)mem.m_alloc(new_capacity * sizeof(Token));
    if (memo.tokens)
    {
      copy(new_facts,memo.tokens,memo.capacity);
      mem.free(memo.tokens);
    }
    memo.capacity = new_capacity;
    memo.tokens   = new_facts;
  }
  Fact ** new_token = (Fact **)mem.m_alloc(network[n].arity * sizeof(Fact *));
  copy(new_token,facts,(int)network[n].arity);
  memo.tokens[memo.count++] = new_token;
}

/////////////////////////////////////////////////////////////////
//  Method: memorize_alpha(...)
//    This method addes a new token ``facts'' to the alpha memory
//  of a node; the alpha memory is resized if necessary.
/////////////////////////////////////////////////////////////////

inline void ReteNet::memorize_alpha( NodeId n, Fact* fact)
{
  register AlphaMemo& memo = alpha[n];
  if (memo.count == memo.capacity)
  {
    int new_capacity  = memo.capacity * 3 / 2 + 2;
    Fact ** new_facts = (Fact **)mem.m_alloc(new_capacity * sizeof(Fact *));
    if (memo.facts)
    {
      copy(new_facts,memo.facts,memo.capacity);
      mem.free(memo.facts);
    }
    memo.capacity = new_capacity;
    memo.facts    = new_facts;
  }
  memo.facts[memo.count++] = fact;
}

/////////////////////////////////////////////////////////////////
//  Method: memorize_not_on_beta(...)
//    This method addes a new token ``facts'' to the beta memory
//  of a negation node; the beta memory is resized if necessary.
/////////////////////////////////////////////////////////////////

inline void ReteNet::memorize_not_on_beta( NodeId n, int matches, Fact** facts)
{
  register BetaMemo& memo = beta[n];
  if (memo.count == memo.capacity)
  {
    int new_capacity  = memo.capacity * 3 / 2 + 2;
    Token * new_facts = (Token *)mem.m_alloc(new_capacity * sizeof(Token));
    int * new_matches = (int *)mem.c_alloc(new_capacity * sizeof(int));
    if (memo.tokens)
    {
      copy(new_facts,memo.tokens,memo.capacity);
      copy(new_matches,memo.matches,memo.capacity);
      mem.free(memo.tokens);
      mem.free(memo.matches);
    }
    memo.capacity = new_capacity;
    memo.tokens   = new_facts;
    memo.matches  = new_matches;
  }
  Fact ** new_token = (Fact **)mem.m_alloc(network[n].arity * sizeof(Fact *));
  copy(new_token,facts,(int)network[n].arity);
  memo.matches[memo.count]  = matches;
  memo.tokens[memo.count++] = new_token;
}

//////////////////////////////////////////////////////////////////////////
//  Insert a partially constructed token into a node from the beta side
//////////////////////////////////////////////////////////////////////////

void ReteNet::insert_beta( NodeId n, Fact* facts[])
{
  register const Node& node = network[n];
  register int i;

  switch (node.kind)
  {
    ////////////////////////////////////////////////////////////////////
    // Testing node; just apply the test and propagate the token
    //   if the test is satisfied.
    ////////////////////////////////////////////////////////////////////
  case Node::Fork:
    insert_beta(node.child,facts);
    insert_beta(n+1,facts);
    break;
  case Node::Test:
    if (node.join == 0 || beta_test(node.join,facts))
      insert_beta(node.child,facts);
    break;
    ////////////////////////////////////////////////////////////////////
    // Conjunctive node:
    //   Concatenate the new fact with every alpha input memorized;
    //   apply the join on this new token, and propagate the token
    //   if it is satisfied.   Also, memorize the new beta input.
    ////////////////////////////////////////////////////////////////////
  case Node::And:
    {
      register AlphaMemo& memo = alpha[n];
      for (i = memo.count - 1; i >= 0; i--)
      {
        facts[node.beta_arity] = memo.facts[i];
        if (node.join == 0 || beta_test(node.join,facts))
          insert_beta(node.child,facts);
      }
      memorize_beta(n,facts);
    }
    break;
    ////////////////////////////////////////////////////////////////////
    // Negation node:
    //   Concatenate the new fact with every alpha input memorized;
    //   apply the join on this new token, and propagate the token
    //   if *none* of the join is satisfied.
    //   Also, memorize the new beta input.
    ////////////////////////////////////////////////////////////////////
  case Node::Not:
    {
      register AlphaMemo& memo = alpha[n];
      int match_count;
      for (match_count = 0, i = memo.count - 1; i >= 0; i--)
      {
        facts[node.beta_arity] = memo.facts[i];
        if (node.join == 0 || beta_test(node.join,facts))
          match_count++;
      }
      memorize_not_on_beta(n,match_count,facts);
      if (match_count == 0)
        insert_beta(node.child,facts);
    }
    break;
    ////////////////////////////////////////////////////////////////////
    //  Terminal node: when we get here we call activate(...)
    //  to add the token into the conflict set.
    ////////////////////////////////////////////////////////////////////
  case Node::Bot:
    activate(node.child,node.arity,facts);
    break;
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////
//  Insert a partially constructed token into a node from the alpha side
//////////////////////////////////////////////////////////////////////////

void ReteNet::insert_alpha( NodeId n, Fact* fact)
{
  register const Node& node = network[n];
  register int i;

  switch (node.kind)
  {
  case Node::Alpha:
    memorize_alpha(n,fact);
    insert_alpha(node.child, fact);
    break;
    ////////////////////////////////////////////////////////////////////
    // Conjunctive node:
    //   Concatenate the new fact with every beta input memorized;
    //   apply the join on this new token, and propagate the token
    //   if it is satisfied.   Also, memorize the new alpha input.
    ////////////////////////////////////////////////////////////////////
  case Node::And:
    {
      register BetaMemo& memo = beta[n];
      for (i = memo.count - 1; i >= 0; i--)
      {
        Fact ** facts = memo.tokens[i];
        facts[node.beta_arity] = fact;
        if (node.join == 0 || beta_test(node.join,facts))
          insert_beta(node.child,facts);
      }
      memorize_alpha(n,fact);
    }
    break;
    ////////////////////////////////////////////////////////////////////
    // Negation node:
    //   Concatenate the new fact with every beta input memorized;
    //   apply the join on this new token, and propagate the token
    //   to be removed if the join is not satisfied when previously
    //   none was.
    //   Also, memorize the new alpha input.
    ////////////////////////////////////////////////////////////////////
  case Node::Not:
    {
      register BetaMemo& memo = beta[n];
      for (i = memo.count - 1; i >= 0; i--)
      {
        Fact ** facts = memo.tokens[i];
        facts[node.beta_arity] = fact;
        if (node.join == 0 || beta_test(node.join,facts))
          if (memo.matches[i]++ == 0)
            remove_beta(node.child,facts);
      }
      memorize_alpha(n,fact);
    }
    break;
    ////////////////////////////////////////////////////////////////////
    // Terminal node.
    ////////////////////////////////////////////////////////////////////
  case Node::Bot:
    {
      Fact * facts[1];
      facts[0] = fact;
      activate(node.child,1,facts);
    }
    break;
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////
//  Remove a token from a node from the beta side
//////////////////////////////////////////////////////////////////////////

void ReteNet::remove_beta( NodeId n, Fact* facts[])
{
  register const Node& node = network[n];
  register int i;

  switch (node.kind)
  {
    ////////////////////////////////////////////////////////////////////
    //  Testing node: apply the join and if it is satisfied
    //    propagate the token to be removed.
    ////////////////////////////////////////////////////////////////////
  case Node::Fork:
    remove_beta(node.child,facts);
    remove_beta(n+1,facts);
    break;
  case Node::Test:
    if (node.join == 0 || beta_test(node.join,facts))
      remove_beta(node.child,facts);
    break;
    ////////////////////////////////////////////////////////////////////
    // Conjunctive, Negation node:
    //   Concatenate the new fact with every beta input memorized;
    //   apply the join on this new token, and propagate the token
    //   to be removed if it is satisfied.   Also, remove the token
    //   from the beta memory.
    ////////////////////////////////////////////////////////////////////
  case Node::And:
  case Node::Not:
    {
      register BetaMemo&  l = beta[n];
      register AlphaMemo& r = alpha[n];
      for (i = l.count - 1; i >= 0; i--)
      {
        int j;
        for (j = node.beta_arity - 1; j >= 0; j--)
          if (l.tokens[i][j] != facts[j])
            goto next;
        for (j = r.count - 1; j >= 0; j--)
        {
          facts[node.beta_arity] = r.facts[j];
          if (node.join == 0 || beta_test(node.join,facts))
            remove_beta(node.child,facts);
        }
        l.tokens[i] = l.tokens[--l.count];
        l.matches[i] = l.matches[l.count];
        mem.free(l.tokens[i]);
next:
        ;
      }
    }
    break;
  case Node::Bot:
    deactivate(node.child,node.arity,facts);
    break;
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////
//  Remove a token from a node from the alpha side
//////////////////////////////////////////////////////////////////////////

void ReteNet::remove_alpha(NodeId n, Fact* fact)
{
  register const Node& node = network[n];
  register int i;

  switch (node.kind)
  {
  case Node::Alpha:
    {
      register AlphaMemo& r = alpha[n];
      for (i = r.count - 1; i >= 0; i--)
      {
        if (r.facts[i] == fact)
        {
          remove_alpha(node.child, fact);
          mem.free(r.facts[i]);
          r.facts[i] = r.facts[--r.count];
        }
      }
      break;
    }
    ////////////////////////////////////////////////////////////////////
    // Conjunctive node:
    //   Concatenate the new fact with every alpha input memorized;
    //   apply the join on this new token, and propagate the token
    //   to be removed if it is satisfied.   Also, remove the token
    //   from the alpha memory.
    ////////////////////////////////////////////////////////////////////
  case Node::And:
    {
      register AlphaMemo& r = alpha[n];
      register BetaMemo&  l = beta[n];
      for (i = r.count - 1; i >= 0; i--)
      {
        if (r.facts[i] == fact)
        {
          for (int j = l.count - 1; j >= 0; j--)
          {
            Fact ** facts = l.tokens[j];
            facts[node.beta_arity] = fact;
            if (node.join == 0 || beta_test(node.join,facts))
              remove_beta(node.child,facts);
          }
          mem.free(r.facts[i]);
          r.facts[i] = r.facts[--r.count];
        }
      }
    }
    break;
    ////////////////////////////////////////////////////////////////////
    // Negation node:
    //   Concatenate the new fact with every beta input memorized;
    //   apply the join on this new token, and propagate the token
    //   to be removed if it is satisfied.   Also, remove the token
    //   from the alpha memory.
    ////////////////////////////////////////////////////////////////////
  case Node::Not:
    {
      register AlphaMemo& r = alpha[n];
      /////////////////////////////////////////////////////////////////
      // Search for the given fact from the alpha side.  If it is found,
      // we'll run the join with the beta side.
      /////////////////////////////////////////////////////////////////
      for (i = r.count - 1; i >= 0; i--)
      {
        if (r.facts[i] == fact)
        {
          register BetaMemo& l = beta[n];
          for (int j = l.count - 1; j >= 0; j--)
          {
            Fact ** facts = l.tokens[j];
            facts[node.beta_arity] = fact;
            ///////////////////////////////////////////////////////////
            // If the join is good, we'll decrement the matching count.
            // When this count reaches 0, the beta token is propagated.
            ///////////////////////////////////////////////////////////
            if (node.join == 0 || beta_test(node.join,facts))
            {
              if (--l.matches[j] == 0)
              {
                insert_beta(node.child,facts);
                mem.free(facts);
                l.tokens[j] = l.tokens[--l.count];
                l.matches[j] = l.matches[l.count];
              }
            }
          }
          r.facts[i] = r.facts[--r.count];
        }
      }
    }
    break;
  default:
    break;
  }
}
