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

#ifndef trie_h
#define trie_h

#include <AD/generic/generic.h>

template <int arity, class Type>
class Trie;

template <int arity, class Type>
class TrieNode
{
  friend class Trie<arity, Type>;

  Type       content;            // stuff that the node carries
  TrieNode * parent;             // parent of node
  TrieNode * children[arity];    // children

  TrieNode(TrieNode * p = 0) : parent(p)
  {
    for (int i = 0; i < arity; i++)
      children[i] = 0;
  }
  ~TrieNode()
  {
    for (int i = 0; i < arity; i++)
      delete children[i];
  }

public:
  Type& operator () ()
  {
    return content;
  }
};

template <int arity, class Type>
class Trie
{
  Trie(const Trie&);               // No copy constructor
  Trie& operator = (const Trie&);  // No assignment

public:
  typedef unsigned char Symbol;
  typedef TrieNode<arity, Type> * Node;

protected:
  Node trie;                       // The root of the trie

public:
  Trie() : trie(0)
  {}
  ~Trie()
  {
    delete trie;
  }

  Node root()                    const
  {
    return trie;
  }
  Bool is_empty(Node n)          const
  {
    return n == 0;
  }
  Node child(Node n, Symbol c)   const
  {
    return n->children[c];
  }
  Node parent(Node n)            const
  {
    return n->parent;
  }
  void insert(Node n, Symbol c)
  {
    n->children[c] = new TrieNode<arity, Type> (n);
  }
};

#endif
