#include <string>
#include <AD/graph/graph.h>
#include <AD/graph/node.h>
#include <AD/graph/edge.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Node set implementation
//
//////////////////////////////////////////////////////////////////////////////

NodeSet::NodeSet() : my_nodes(0), my_capacity(0), my_size(0)
{}

NodeSet::NodeSet(const NodeSet& S) : my_nodes(0)
{
  *this = S;
}

NodeSet::~NodeSet()
{
  delete [] my_nodes;
}

void NodeSet::grow( int k)
{
  int N = k+1;
  if (N < 10)
    N = 10;
  if (N < my_capacity * 2)
    N = my_capacity * 2;
  NodeObject ** new_nodes = new NodeObject * [N];
  memcpy(new_nodes, my_nodes, my_size * sizeof(NodeObject *));
  memset(new_nodes + my_size * sizeof(NodeObject*), 0,
         (N - my_size) * sizeof(NodeObject*));
  delete [] my_nodes;
  my_capacity = N;
  my_nodes    = new_nodes;
}

void NodeSet::operator = (const NodeSet& S)
{
  if (this == &S)
    return;
  if (my_nodes)
    delete [] my_nodes;
  my_capacity = my_size = S.my_size;
  my_nodes = new NodeObject * [my_capacity];
  memcpy(my_nodes,S.my_nodes,my_capacity * sizeof(NodeObject*));
}

//////////////////////////////////////////////////////////////////////////////
//
//  Edge set implementation
//
//////////////////////////////////////////////////////////////////////////////

EdgeSet::EdgeSet() : my_edges(0), my_capacity(0), my_size(0)
{}

EdgeSet::EdgeSet(const EdgeSet& S) : my_edges(0)
{
  *this = S;
}

EdgeSet::~EdgeSet()
{
  delete [] my_edges;
}

void EdgeSet::grow(int k)
{
  int N = k+1;
  int limit = my_capacity * 3 / 2;
  if (N < 4)
    N = 4;
  if (N < limit)
    N = limit;
  EdgeObject ** new_edges = new EdgeObject * [N];
  memcpy(new_edges, my_edges, my_size * sizeof(EdgeObject *));
  memset(new_edges + my_size * sizeof(EdgeObject*), 0,
         (N - my_size) * sizeof(EdgeObject*));
  delete [] my_edges;
  my_capacity = N;
  my_edges    = new_edges;
}

void EdgeSet::operator = (const EdgeSet& S)
{
  if (this == &S)
    return;
  if (my_edges)
    delete [] my_edges;
  my_capacity = my_size = S.my_size;
  my_edges = new EdgeObject * [my_capacity];
  memcpy(my_edges,S.my_edges,my_capacity * sizeof(EdgeObject*));
}

//////////////////////////////////////////////////////////////////////////////
//
//  AdjList implementation
//
//////////////////////////////////////////////////////////////////////////////

AdjList::AdjList() : my_edge_sets(0), my_capacity(0), my_size(0)
{}

AdjList::~AdjList()
{
  for (int i = 0; i < my_size; i++)
    if (my_edge_sets[i])
      delete my_edge_sets[i];
  delete [] my_edge_sets;
}

void AdjList::grow(int k)
{
  int N = k+1;
  if (N < 10)
    N = 10;
  if (N < my_capacity * 2)
    N = my_capacity * 2;
  EdgeSet ** new_edge_sets;
  new_edge_sets = new EdgeSet * [N];
  memcpy(new_edge_sets, my_edge_sets, my_size * sizeof(EdgeSet*));
  memset(new_edge_sets + my_size * sizeof(EdgeSet*), 0,
         (N - my_size) * sizeof(EdgeSet*));
  delete [] my_edge_sets;
  my_capacity  = N;
  my_edge_sets = new_edge_sets;
}
