///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "willard.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_PARSER_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "willard.pcc"
#include <iostream.h>
#include <AD/pretty/postream.h>
#include "willard-ast.h"
#include "parser.h"
#include "willard.h"

Willard::Willard() {}
Willard::~Willard() {}

int main()
{  QueryParser P;
   
   Exp q = P.read();

   PrettyOStream S;

   Willard W;

   W.set_log(cout);

   S << "Input:" << newline << q << newline;
  
   q = W.decompose(q);

   S << "Output:" << newline << q << newline;

   cerr << "Cons = " << ConsCounter::count << '\n';
   return 0;
}
#line 30 "willard.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
