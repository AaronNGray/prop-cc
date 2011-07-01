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

#ifndef union_find_h
#define union_find_h

//////////////////////////////////////////////////////////////////////////
//  Union/find data structure with straight forward path compression
//  Amortized cost O(log* n).
//////////////////////////////////////////////////////////////////////////

class UnionFind
{
  short * upTree;  // A upside down tree array; -1 represents leaf
  int size;        // number of elements in the upTree;

public:

  ////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  ////////////////////////////////////////////////////////////////////

  UnionFind(int capacity);        // create a new union/find structure
  UnionFind(const UnionFind&);    // create and initialize
  ~UnionFind();                    // destructor

  ////////////////////////////////////////////////////////////////////
  // Assignment
  ////////////////////////////////////////////////////////////////////

  UnionFind& operator = (const UnionFind&); // copy

  ////////////////////////////////////////////////////////////////////
  // Union and find
  ////////////////////////////////////////////////////////////////////

  int  operator [] (int) const;   // the ``find'' operation
  void operator () (int, int);    // the ``union'' operation
};

#endif
