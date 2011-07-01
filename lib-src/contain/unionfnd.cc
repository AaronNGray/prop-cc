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

#include <AD/contain/unionfnd.h>

UnionFind::UnionFind( int capacity)
{
  register int i;
  for (i = capacity-1, upTree = new short [size = capacity]; i >= 0; i--)
    upTree[i] = -1;
}

UnionFind::UnionFind( const UnionFind& u) : upTree(0)
{
  *this = u;
}

UnionFind& UnionFind::operator = (const UnionFind& u)
{
  if (this != &u)
  {
    delete [] upTree;
    upTree = new short [ size = u.size ];
    for (int i = size - 1; i >= 0; i--)
      upTree[i] = u.upTree[i];
  }
  return *this;
}

UnionFind::~UnionFind()
{
  delete [] upTree;
}

int UnionFind::operator [] (int i) const
{
  register int j, k;
  for (j = i; (k = upTree[j]) >= 0; j = k)
    ;
  for ( ; (k = upTree[i]) >= 0; i = k)
    upTree[i] = j;
  return j;
}

void UnionFind::operator () (int i, int j)
{
  upTree[i] = j;
}
