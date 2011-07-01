//////////////////////////////////////////////////////////////////////////////
//  Implementation of the pattern variable environment
//////////////////////////////////////////////////////////////////////////////

#include <strstream>
#include <AD/contain/stack.h>
#include "patenv.h"
#include "type.h"
#include "ast.h"
#include "options.h"


/////////////////////////////////////////////////////////////////////////////
//  A binding between a pattern variable and a binding expression.
/////////////////////////////////////////////////////////////////////////////

struct BINDING
{
  Id       var;      // Name of the pattern variable
  Ty       ty;       // type of pattern variable
  Exp      exp;      // The expression
  Polarity polarity; // polarity of the pattern variable
  BINDING()
  {}
  BINDING(Id v, Exp e, Ty t, Polarity p)
      : var(v), exp(e), ty(t), polarity(p)
  {}
}
;

/////////////////////////////////////////////////////////////////////////////
// An environment of pattern variables is implemented as a pair of
// stacks, one caching the current set of bindings and one registering
// the lexical scope boundaries.
/////////////////////////////////////////////////////////////////////////////

class PatternVarEnv_Impl
{
  PatternVarEnv_Impl(const PatternVarEnv_Impl&);  // no copy constructor
  void operator = (const PatternVarEnv_Impl&);    // no assignment

public:

  Stack<BINDING> env;              // bindings stack
  Stack<int>     levels;           // scope levels stack
  Stack<Bool>    linear;           // is current scope linear?
  Stack<Bool>    separate_guards;  // separate the guards
  Stack<Bool>    tree_grammar;     // tree grammar mode
  Stack<Exp>     guards;           // guard expressions

  //////////////////////////////////////////////////////////////////////////
  // Constructor
  //////////////////////////////////////////////////////////////////////////
  PatternVarEnv_Impl( int max_size, int max_levels)
      : env( max_size), levels( max_levels), linear( max_levels),
      separate_guards( max_levels), tree_grammar( max_levels),
      guards( max_levels)
  {}
};

///////////////////////////////////////////////////////////////////////////
//  Pattern variable environment routines.
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//  Constructor
///////////////////////////////////////////////////////////////////////////

PatternVarEnv::PatternVarEnv( int max_size, int max_levels)
    : impl( new PatternVarEnv_Impl( max_size, max_levels))
{}

///////////////////////////////////////////////////////////////////////////
//  Destructor
///////////////////////////////////////////////////////////////////////////

PatternVarEnv::~PatternVarEnv ()
{
  delete impl;
}

///////////////////////////////////////////////////////////////////////////
//  Method to add a new binding to the current scope.
//  If the current scope allows only linear patterns, we'll search the
//  scope to make sure that the new pattern variable is not a duplicate.
//  Otherwise, the check is omitted.
///////////////////////////////////////////////////////////////////////////

Exp PatternVarEnv::add( Id v, Exp e, Ty ty, Polarity polarity)
{
  register const BINDING * top   = &impl->env.top();
  register const BINDING * limit = &impl->env[impl->levels.top()];
  for ( ;top >= limit; top--)
  {
    if (top->var == v)
    {
      if (polarity == ISneither)
      {
        error("%Lmultiple mixed polarity pattern variable '%s'\n",v);
      }
      else if (impl->linear.top())
      {
        error("%Lduplicated pattern variable '%s'.  Use option -non_linear.\n", v);
      }
      else
      {
        Used::equality = true;
        if (! unify(ty, top->ty))
        {
          error("%Lexpecting type %T but found %T in pattern variable '%s'\n",
                top->ty, ty, v);
        }
        if (tree_grammar())
          break;
        return top->exp;
      }
    }
  }
  impl->env.push(BINDING(v,e,ty,polarity));
  return NOexp;
}

///////////////////////////////////////////////////////////////////////////
//  Method to lookup a binding from all the scopes.
//  This is implemented as a naive linear search.  Sorry!
///////////////////////////////////////////////////////////////////////////

Exp PatternVarEnv::lookup( Id v, Bool * from_current)
{
  register const BINDING * top   = &impl->env.top();
  register const BINDING * limit = &impl->env[0];
  for ( ;top >= limit; top--)
    if (top->var == v)
    {
      if (from_current)
      {  // check whether it is from the current scope
        if (impl->levels.size() == 0)
          *from_current = true;
        else
          *from_current = top >= &impl->env[impl->levels.top()];
      }
      return top->exp;
    }
  return NOexp;
}

///////////////////////////////////////////////////////////////////////////
//  Tell whether we need to generate separate guard expressions
///////////////////////////////////////////////////////////////////////////

Bool PatternVarEnv::separate_guard()
{
  return impl->separate_guards.top();
}

Bool PatternVarEnv::tree_grammar()
{
  return impl->tree_grammar.top();
}

Exp  PatternVarEnv::guard()
{
  return impl->guards.top();
}

Exp  PatternVarEnv::guard( Exp e)
{
  Exp e2 = guard();
  if (e == NOexp)
    return e2;
  if (e2 == NOexp)
    return e;
  return BINOPexp("&&",e2,e);
}

void PatternVarEnv::add_guard( Exp e)
{
  if (e != NOexp)
  {
    Exp& g = impl->guards.top();
    if (g != NOexp)
      g = BINOPexp("&&",g,e);
    else
      g = e;
    if (options.debug)
      msg("%Lnew guard expression: %e\n", g);
  }
}

///////////////////////////////////////////////////////////////////////////
//  Method to insert a new scope
///////////////////////////////////////////////////////////////////////////

void PatternVarEnv::new_scope( Bool is_linear, Bool guard_sep, Bool treegram)
{
  if (impl->levels.is_full())
  {
    error("%Lpattern scope stack overflows\n");
  }
  else
  {
    impl->levels.push(impl->env.size());
    impl->linear.push(is_linear);
    impl->separate_guards.push(guard_sep);
    impl->tree_grammar.push(treegram);
    impl->guards.push(NOexp);
  }
}

///////////////////////////////////////////////////////////////////////////
//  Method to leave a scope.
///////////////////////////////////////////////////////////////////////////

void PatternVarEnv::old_scope()
{
  if (impl->levels.is_empty())
  {
    error("%Lpattern scope stack underflows\n");
  }
  else
  {
    impl->env.set_size(impl->levels.pop());
    impl->linear.pop();
    impl->separate_guards.pop();
    impl->tree_grammar.pop();
    impl->guards.pop();
  }
}
