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

#ifndef patricia_tries_h
#define patricia_tries_h

//
// Patricia (Practical Algorithm To Retrieve Information
//    Coded In Alphanumeric) tries.
//

class Patricia
{
  Patricia(const Patricia&);               // No initialization allowed
  Patricia& operator = (const Patricia&);  // No assignment allowed

protected:
  typedef unsigned char Symbol;

  struct Trie
  {
    unsigned char * keys;
    Trie ** children;
  };

  typedef Trie * Node;
  Node trie;

public:
  Patricia();
  ~Patricia();

  Node root() const
  {
    return trie;
  }
  Node child(Node n, Symbol c) const
  {
    return n->children[c];
  }
};

#endif
