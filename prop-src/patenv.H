#ifndef interface_to_the_scanner_h
#define interface_to_the_scanner_h

#include <AD/generic/generic.h>
#include "ir.h"
#include "ast.h"

/////////////////////////////////////////////////////////////////////////////
// An environment of pattern variables is implemented as a pair of
// stacks, one caching the current set of bindings and one registering
// the lexical scope boundaries.
/////////////////////////////////////////////////////////////////////////////
class PatternVarEnv
{
  PatternVarEnv( const PatternVarEnv&);     // no copy constructor
  void operator = ( const PatternVarEnv&);  // no assignment

protected:

  //////////////////////////////////////////////////////////////////////////
  // The environment is implemented as two stacks, one storing
  // the bindings and the other storing the highwater mark of each scope.
  //////////////////////////////////////////////////////////////////////////

  class PatternVarEnv_Impl * impl;

public:

  //////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  //////////////////////////////////////////////////////////////////////////
  PatternVarEnv( int max_size = 256, int max_levels = 256);
  ~PatternVarEnv ();

  //////////////////////////////////////////////////////////////////////////
  // Add binding and lookup binding
  //////////////////////////////////////////////////////////////////////////
  Exp  add
    ( Id,                    // name of pattern variable
        Exp,                   // binding expression
        Ty,                    // type of pattern variable
        Polarity = ISpositive  // polarity of the pattern
    );
  Exp  lookup(Id, Bool * = 0);  // lookup old binding, returns NIL if not found.
  // returns true as second argument iff the
  // binding is from the current scope.
  Exp  guard ();                // current guard expression
  Exp  guard (Exp);             // current guard expression
  void add_guard (Exp);
  Bool separate_guard ();
  Bool tree_grammar   ();
  //////////////////////////////////////////////////////////////////////////
  // Enter and leave scope.
  // As a default, we allow only linear patterns.
  //////////////////////////////////////////////////////////////////////////
  void new_scope( Bool linear_patterns = true,    // enters new scope
                  Bool separate_guard  = false,   // separate the guard
                  Bool treegrammar     = false ); // tree grammar mode
  void old_scope();                               // returns to old scope
};

extern PatternVarEnv pv_env;

#endif
