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

#include <AD/automata/operprec.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Import types
//
//////////////////////////////////////////////////////////////////////////////

typedef Grammar::Production         Production;
typedef OpPrecedence::Fixity        Fixity;
typedef OpPrecedence::Associativity Associativity;
typedef OpPrecedence::Precedence    Precedence;

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

OpPrecedence:: OpPrecedence( const Grammar& g) : G(g)
{
  int max = G.max_terminal() + 1;
  fixity_table        = new Fixity        [ max ];
  associativity_table = new Associativity [ max ];
  precedence_table    = new int           [ max ];
  fixity_map          = new Fixity        [ G.size() ];
  associativity_map   = new Associativity [ G.size() ];
  precedence_map      = new int           [ G.size() ];

  for (int i = 0; i < max; i++)
  {
    fixity_table       [i] = Nonfix;
    associativity_table[i] = None;
    precedence_table   [i] = 32767;
  }
  for (int j = G.size() - 1; j >= 0; j--)
  {
    fixity_map       [j] = Nonfix;
    associativity_map[j] = None;
    precedence_map   [j] = 32767;
  }
}

OpPrecedence::~OpPrecedence()
{
  delete [] fixity_table;
  delete [] associativity_table;
  delete [] precedence_table;
  delete [] fixity_map;
  delete [] associativity_map;
  delete [] precedence_map;
}
