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

#include <string>
#include <AD/tries/briandai.h>   // De la briandais tries

typedef Briandais::Node   Node;
typedef Briandais::Symbol Symbol;

Briandais::Briandais(int initial_size, int growth)
    : nodes(new Trie [initial_size]),
    capacity(initial_size), node_count(1),
    grow_size(growth)
{
  nodes[0].sibling = -1;
  nodes[0].child   = -1;
}

void Briandais::grow(int size)
{
  if (size > capacity)
  {
    Trie * new_nodes = new Trie [ size ];
    memcpy(new_nodes, nodes, sizeof(Trie) * capacity);
    delete [] nodes;
    nodes = new_nodes;
    capacity = size;
  }
}

Node Briandais::insert(Node parent, Symbol c)
{
  Node n;
  if ((n = node_count++) >= capacity)
  {
    if (capacity < grow_size)
      grow(capacity + grow_size);
    else
      grow(capacity * 2);
  }
  nodes[n].c          = c;
  nodes[n].child      = -1;
  nodes[n].sibling    = nodes[parent].child;
  nodes[parent].child = n;
  return n;
}
