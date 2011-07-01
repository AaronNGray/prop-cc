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
//  This file contains the implementation of a top-down tree parser
//  with dynamic programming.  See Aho, Tsiang, et al. for details.
//////////////////////////////////////////////////////////////////////////////

#include <AD/rewrite/twig.h>     // twig module
#include <AD/memory/boundtag.h>  // boundary tag memory maager
#include <AD/contain/bitset.h>   // bit sets

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////
typedef Twig::Symbol Symbol;
typedef Twig::State  State;
typedef Twig::Offset Offset;
typedef Twig::Rule   Rule;

//////////////////////////////////////////////////////////////////////////////
//  Internal representation of the tree matcher
//////////////////////////////////////////////////////////////////////////////
class Twig_Impl {
public:
   Twig_Impl() {}
  ~Twig_Impl() {}
};

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor for class Twig.
//////////////////////////////////////////////////////////////////////////////
Twig:: Twig( const Offset base_table  [],  
             const State  check_table [],
             const State  failure     [],
             const State  next_table  [],
             const Rule   rule_table  []
           ) : 
   Super(base_table,check_table,failure,next_table,rule_table),
   mem(* new BoundaryTag) {}
Twig::~Twig() { close(); delete (&mem); }

//////////////////////////////////////////////////////////////////////////////
//  Method to initialize the tree reducer.
//////////////////////////////////////////////////////////////////////////////
void Twig::open()
{  if (impl) delete impl;
   impl = new Twig_Impl();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to clean up the tree reducer.
//////////////////////////////////////////////////////////////////////////////
void Twig::close()
{  if (impl) delete impl; impl = 0; }

//////////////////////////////////////////////////////////////////////////////
//  Method to perform the actual reduction.
//////////////////////////////////////////////////////////////////////////////
void Twig::reduce()
{  
}
