//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <AD/automata/gla.h>  // general lookahead automaton
#include <AD/hash/dchash.h>   // direct chaining hash table

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////

GLA:: GLA( Mem& m ) : mem(m)
{}
GLA:: GLA( const Grammar& g, Mem& m ) : mem(m)
{
  build(g);
}
GLA::~GLA()
{
  clean_up();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to clean up.  We just destroy the internals.
//////////////////////////////////////////////////////////////////////////////

void GLA::clean_up()
{}

//////////////////////////////////////////////////////////////////////////////
//  Build method.
//////////////////////////////////////////////////////////////////////////////

void GLA::build(const Grammar& G)
{
  ///////////////////////////////////////////////////////////////////////////
  //  (II) Construct the GLA from the grammar.
  ///////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < G.size(); i++)
  {}
}
