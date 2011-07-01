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

#ifndef hash_trie_h
#define hash_trie_h

//
//  \section{Class |HashTrie|}
//
//     The most difficult problem with implementing tries efficiently
//  is minimizing the amount of storaged used.  Traditional approach
//  that use multiway trees suffer from large storage requirements;
//  while approachs that eliminate skinny branches(Patricia tries) or
//  simulating mulitway branches with linked lists (De la Briandias) suffer
//  from time and/or programming complexity.
//
//     In this simple class I'm trying to simulate a trie structure using
//  an open addressing hash table.   The ``root'' of the trie is at
//  index 0 of the table.  Now given a trie node at index |i|
//  of the hash table, the branch of character 'c' is calculated by
//  some suitable hash function $f(i,c)$.   Collison is resolved by rehashing
//  into the table, using a secondary probing function $g$.  Thus
//  traversing a trie from the root of the trie to the leaf amounts
//  to repeated hashing.
//
//     Notice that branch pointers are not stored explicitly
//  in the table since they are represented implicitly by the function
//  $f$.  If the table is not kept too full, repeated probing should not be
//  a big problem\cite{Algorithms}.
//
//     There is, however, one major catch to this scheme!!
//  Deletion and growing the table are difficult operations and are
//  not directly supported.
//
//     A hash trie is similar to a compressed trie.
//
//  Allen Leung
//  May, 1994
//

#include <AD/generic/generic.h>   // Generic definitions

class HashTrie
{
  void init(long n);       // initialize trie to empty state

public:
  typedef long Node;             // Trie node
  typedef unsigned short Symbol; // Trie symbol

protected:
  long     slots;  // number of slots in the hash table, a power of 2.
  long     count;  // number of elements within the table.
  long     mask;   // $slots - 1$.
  Symbol * symbol; // the character at current node.
  Node  *  back;   // the index of the parent; -1 if slot is unused.

  //
  // Two very simple hashing functions are used.  Since probing
  // an entry is very fast, it is perhaps better to trust a simple
  // hashing function using no multiplication and division instead
  // of a more sophisticated strategy that reduce the possibility
  // of primary and secondary clustering.
  //
  // Some strategies:  It is rather important that the primary hash
  // function scatters the hash indices through out the hash table.
  //

  inline Node f(Node i, Symbol c) const  // primary hashing function
  {
    return (i + 37 + (c << (c & 3))) & mask;
  }

  inline long g(Node i, Symbol c) const  // secondary hashing function
  {
    long inc = (i ^ c) & mask;               // xor hashing
    return inc == 0 ? 11 : inc;              // increment must be non-zero
  }

  // Constructors and destructor

public:
  HashTrie();
  HashTrie(long number_of_nodes);
  HashTrie(const HashTrie&);
  ~HashTrie();

  HashTrie& operator = (const HashTrie&);

  //  Operations:
  //     clear()    -- empties the trie.
  //     size()     -- returns the number of nodes currently used.
  //     capacity() -- returns the overall capacity.
  //     isFull()   -- can the trie accept more nodes?
  //     isFree()   -- returns true if the current node is free.
  //     root()     -- returns the root node of the trie.
  //     trie[node] -- returns the character at a node.
  //     parent()   -- returns the parent of a node.
  //     child()    -- returns a child of a node.
  //

  void clear();
  long size() const
  {
    return count;
  }
  long capacity() const
  {
    return slots - 1;
  }
  Bool isFull() const
  {
    return count - 1 >= slots;
  }
  Bool isFree(Node node) const
  {
    return back[node] < 0;
  }
  Node root() const
  {
    return 0;
  }
  Symbol operator [] (Node node) const
  {
    return symbol[node];
  }
  Node parent(Node node) const
  {
    return back[node];
  }
  Node child(Node node, Symbol c) const;

  //
  // Insert character 'c' at 'child' with 'node' as parent.
  //
  void insert(Node parent, Node child, Symbol c)
  {
    count++;
    symbol[child] = c;
    back[child] = parent;
  }
};


//
// Implementation of the child lookup function.
// Notice that this function will loop if (and only if) the hash table is full.
// Also, if the load factor of the table is high, many probes
// will be needed to locate an element.  However, the algorithm will guarantee
// that if the table is not full it will terminate correctly either
// with the child node found or, if the node does not exist, return
// the index of an empty node.
//

inline HashTrie::Node HashTrie::child
(HashTrie::Node node, HashTrie::Symbol c) const
{
  register HashTrie::Node i = f(node,c);  // possible index of child node

  //
  // Primary probe.
  //

  if ( i != 0 &&                             // The root cannot be a child
       ( back[i] < 0 ||                      // slot is empty??
         back[i] == node && symbol[i] == c)) // found child??
    return i;

  //
  // If the primary probe fails, secondary probing with double hashing is
  // used to resolve the collison.  Since the size of the hash table, $N$, is
  // a power of two(i.e. not a prime), we have to make sure that the
  // secondary probe sequence indexes all the slots.  This is accomplished
  // by noting that if the order of the cyclic subgroup $[inc]$ generated
  // by $inc$ is $M$, then the cosets
  //    \( [inc], [inc] + 1, [inc] + 2 ... [inc] + |N|/M - 1 \)
  // form a partition of the elements from $0$ to $N - 1$.
  // Each of these cosets are visited in turn.
  //

  register HashTrie::Node start = i; // starting element of probing sequence
  register long inc = g(node,c);     // increment used in secondary probes
  for (;;)
  {
    if ( i != 0 &&                             // The root cannot be a child
         ( back[i] < 0 ||                      // slot is empty??
           back[i] == node && symbol[i] == c)) // found child??
      return i;
    i = (i + inc) & mask;                      // try next element
    if (i == start)
      i = start = (start+1) & mask;           // try next coset
  };
}

#endif
