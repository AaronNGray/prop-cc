///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.6),
//  last updated on Nov 2, 1999.
//  The original source file is "topdowng.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "topdowng.pcc"
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

//////////////////////////////////////////////////////////////////////////////
//  This file implements a top-down tree matcher generator using the algorithm
//  described by O'Donnell et al.  It basically reduces tree matching
//  to the problem of string matching using the Aho-Corasick algorithm.
//  The generator is really simple since most of the complexity of
//  top-down style matching is at runtime.
//////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <assert.h>
#include <AD/automata/treegram.h>
#include <AD/automata/topdowng.h>

//////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////////
typedef TreeGrammar::TreeProduction TreeProduction;

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructor
//////////////////////////////////////////////////////////////////////////////
TopDownGen:: TopDownGen() {}
TopDownGen:: TopDownGen(const TreeGrammar& Gram) { compile(Gram); }
TopDownGen::~TopDownGen() {}

//////////////////////////////////////////////////////////////////////////////
//  Compile a set of tree patterns
//////////////////////////////////////////////////////////////////////////////
void TopDownGen::compile(const TreeGrammar& g)
{
   ///////////////////////////////////////////////////////////////////////////
   //  Set the tree grammar
   ///////////////////////////////////////////////////////////////////////////
   G = &g;

   ///////////////////////////////////////////////////////////////////////////
   //  A temporary buffer for the path string.  You won't have 
   //  patterns with such deep nesting (512).
   ///////////////////////////////////////////////////////////////////////////
   Symbol path[ 1024 ];

   ///////////////////////////////////////////////////////////////////////////
   //  Get the minimum and maximum functor coding within the grammar.
   ///////////////////////////////////////////////////////////////////////////
   Symbol min = g.min_functor();
   Symbol max = g.max_functor();

   ///////////////////////////////////////////////////////////////////////////
   //  Min and max are the symbol value range for the path strings.
   //  Since the arities are also part of the path string, make sure
   //  the range covers them.
   ///////////////////////////////////////////////////////////////////////////
   if (min > 0) min = 0;
   if (max < g.max_arity()) max = g.max_arity();

   ///////////////////////////////////////////////////////////////////////////
   //  Start creating the compressed tables.
   ///////////////////////////////////////////////////////////////////////////
   start(min,max);

   ///////////////////////////////////////////////////////////////////////////
   //  Now compile the path strings, one for each pattern in the grammar.
   ///////////////////////////////////////////////////////////////////////////
   for (int i = 0; i < g.size(); i++) 
      add_path(i, g[i].term, 0, path);

   ///////////////////////////////////////////////////////////////////////////
   //  Finish up the table compression process.
   ///////////////////////////////////////////////////////////////////////////
   finish();
}

//////////////////////////////////////////////////////////////////////////////
//  Compile a tree pattern as a set of path strings, one for each
//  possible branch of the tree.
//  E.g.  a pattern such as  f(g(X,a), b)  is compiled into the path strings
//     f 0 g
//     f 0 g 1 a
//     f 1 b
//////////////////////////////////////////////////////////////////////////////
void TopDownGen::add_path(int rule, const TreeTerm term, int len, Symbol path[])
{
   
#line 107 "topdowng.pcc"
#line 120 "topdowng.pcc"
{
   if (term) {
      switch (term->tag__) {
         case a_TreeTerm::tag_tree_term: {
#line 109 "topdowng.pcc"
            
            path[len] = _tree_term(term)->_1;
            if (_tree_term(term)->_2 > 0) {  // a non-terminal ?
               for (int i = 0; i < _tree_term(term)->_2; i++) {
                  path[len + 1] = i; 
                  add_path(rule,_tree_term(term)->_3[i],len+2,path);
               }
            } else {  // a terminal
               add_string(rule, len + 1, path);
            }
            
#line 119 "topdowng.pcc"
            } break;
         default: {
#line 119 "topdowng.pcc"
           assert("Bug in TopDownGen::add_path()");
            
#line 120 "topdowng.pcc"
            } break;
      }
   } else {
#line 108 "topdowng.pcc"
   add_string(rule, len, path);
      
#line 109 "topdowng.pcc"
   }
}
#line 120 "topdowng.pcc"
#line 120 "topdowng.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Emit C++ code for the tables.
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& TopDownGen::gen_code(std::ostream& out, const char name[]) const
{  
   Super::gen_code(out,name);
   return out;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Print report
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& TopDownGen::print_report(std::ostream& f) const
{  
   f << "\nCanonical grammar:\n" << *G << '\n';
   return f;
}
#line 144 "topdowng.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 5
Number of ifs generated      = 1
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
