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

#include <AD/tries/comptrie.h>

typedef CompressedTrie::Symbol Symbol;

CompressedTrie::CompressedTrie()
  : next(0), base(0), check(0), symbol(0), size(0) {}

CompressedTrie::CompressedTrie(Symbol min, Symbol max, int n)
  : next(new Node [n]),
    base(new Node [n]),
    check(new Node [n]),
    symbol(new Symbol [n]),
    size(n),
    min_symbol(min),
    max_symbol(max)
  {}

CompressedTrie::~CompressedTrie()
{
  delete [] next;
  delete [] base;
  delete [] check;
  delete [] symbol;
}
