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
#include <AD/tries/hashtrie.h>

HashTrie::HashTrie() : slots(0), symbol(0), back(0) {}

inline int log2(register long n)
{
  register int m;
  for (m = 0, n--; n > 0; m++)
    n >>= 1;
  return m;
}

void HashTrie::clear()
{
  memset(back,-1,slots * sizeof(Node));
  back[0] = 0;  // the root is always occupied
  count = 0;
}

void HashTrie::init(long n)
{
  n = 1 << log2(n);
  slots  = n;
  mask   = n - 1;
  symbol = new Symbol [n];
  back   = new Node [n];
}

HashTrie::HashTrie(long n)
{
  init(n);
  clear();
}

HashTrie::HashTrie(const HashTrie& trie)
    : symbol(0), back(0)
{
  *this = trie;
}

HashTrie::~HashTrie()
{
  delete [] symbol;
  delete [] back;
}

HashTrie& HashTrie :: operator = (const HashTrie& trie)
{
  if (this != &trie)
  {
    delete [] symbol;
    delete [] back;
    init(trie.slots);
    count = trie.count;
    memcpy(symbol,trie.symbol,trie.slots * sizeof(Symbol));
    memcpy(back,trie.back,trie.slots * sizeof(Node));
  }
  return *this;
}
