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

//////////////////////////////////////////////////////////////////////////////
//  This file contains the generator for the top-down tree parser
//  with dynamic programming.  See Aho, Tsiang, et al. for details.
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/rewrite/twig_gen.h>   // twig module

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////

TwigGen:: TwigGen() {}
TwigGen:: TwigGen(const TreeGrammar& Gram) { compile(Gram); }
TwigGen::~TwigGen() {}

//////////////////////////////////////////////////////////////////////////////
//  Method to compile a tree grammar into internal tables form
//////////////////////////////////////////////////////////////////////////////

void TwigGen::compile (const TreeGrammar& Gram)
{
  Super::compile(Gram);
}

//////////////////////////////////////////////////////////////////////////////
//  Method to print the tables
//////////////////////////////////////////////////////////////////////////////

std::ostream& TwigGen::gen_code( std::ostream& f, const char name[]) const
{
  Super::gen_code( f, name);
  return f;
}
