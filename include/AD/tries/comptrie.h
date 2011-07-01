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

#ifndef compressed_trie_h
#define compressed_trie_h

//
// Compressed trie (well, actually a dfa).
//

#include <AD/generic/generic.h>

class CompressedTrie
{
  CompressedTrie(const CompressedTrie&);      // no copy constructor
  void operator = (const CompressedTrie&);    // no assignment

public:
  typedef short Symbol;
  typedef int Node;

protected:
  Node   * next;       //  Transition function indexed by node
  Node   * base;       //  base pointer
  Node   * check;      //  back pointer
  Symbol * symbol;     //  Symbol at node
  int      size;       //  length of these arrays

  Symbol   min_symbol; //  minimal value of symbol
  Symbol   max_symbol; //  maximal value of symbol

  Node     start;      //  root of the trie

public:
  CompressedTrie();
  CompressedTrie(Symbol min_symbol, Symbol max_symbol, int size);
  ~CompressedTrie();

  Node root() const
  {
    return start;
  }

  Node lookup(Node node, Symbol c) const
  {
    register Node offset = base[node] + c;
    if (check[offset] == node)
      return next[offset];
    else
      return -1;
  }
};

#endif
