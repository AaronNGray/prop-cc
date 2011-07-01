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

#ifndef De_la_Briandais_tries_h
#define De_la_Briandais_tries_h

/////////////////////////////////////////////////////////////////////////////
//  De la Briandais tries
//
//  In this data structure, sibling branches are linked together as
//  a linked list.   The implementation allocates all nodes together
//  as an array for efficiency.
/////////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>   // Generic definitions

class Briandais
{
  Briandais(const Briandais&);                // No initialization is allowed
  Briandais& operator = (const Briandais&);   // No assignment is allowed

public:
  typedef int Symbol;
  typedef int Node;

protected:
  struct Trie
  {
    Symbol c;          // the symbol
    Node   sibling;    // pointer to sibling
    Node   child;      // pointer to child
  };

  Trie * nodes;         // elements of the trie
  int capacity;         // maximum capacity of the array
  int node_count;       // number of elements
  int grow_size;        // extra nodes to allocate per expansion

public:
  Briandais(int initial_size = 16, int grow_size = 32);
  ~Briandais()
  {
    delete [] nodes;
  }

  inline Bool   is_empty(Node n) const
  {
    return n < 0;
  }
  inline Node   root() const
  {
    return 0;
  }
  inline int    size() const
  {
    return node_count;
  }
  inline Symbol operator [] (Node n) const
  {
    return nodes[n].c;
  }
  inline Node   sibling(Node n) const
  {
    return nodes[n].sibling;
  }
  inline Node   child(Node n) const
  {
    return nodes[n].child;
  }

  inline Node   child(register Node n, register Symbol c) const
  {
    for (n = nodes[n].child; n >= 0; n = nodes[n].sibling)
      if (nodes[n].c == c)
        return n;
    return -1;
  }

  void   grow(int size);
  Node   insert(Node node, Symbol c);
};

#endif
