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

#ifndef rete_tokens_h
#define rete_tokens_h

#include <AD/rete/fact.h>    // database facts
#include <AD/memory/arena.h> // free list manager

/////////////////////////////////////////////////////////////////////////
// A Rete network token
/////////////////////////////////////////////////////////////////////////

class ReteToken
{
  //////////////////////////////////////////////////////////////////////
  // Import types
  //////////////////////////////////////////////////////////////////////

public:
  typedef Fact::Age    Age;
  typedef Fact::RuleId RuleId;

protected:
  RuleId rule_id;   // rule id
  int    arity;     // length of the token
  Age    _age;      // age
  Fact * token[1];  // the token


  //////////////////////////////////////////////////////////////////////
  //  Method to allocate a new token
  //////////////////////////////////////////////////////////////////////

public:
  inline void * operator new
  (size_t, Arena& arena, int n, RuleId id, Fact * f[], Age a)
  {
    ReteToken * t = (ReteToken*) arena();
    t->arity = n;
    t->rule_id = id;
    t->_age = a;
    for (int i = n - 1; i >= 0; i--)
      t->token[i] = f[i];
    return t;
  }

  //////////////////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////////////////
  // inline         operator Fact ** ()       { return token; }
  inline         Fact ** get_token ()
  {
    return token;
  }
  inline int     size()              const
  {
    return arity;
  }
  inline Fact *  operator [] (int i) const
  {
    return token[i];
  }
  inline void    update (int i, Fact * f)
  {
    token[i] = f;
  }
  inline RuleId  rule()              const
  {
    return rule_id;
  }
  inline Age     age()               const
  {
    return _age;
  }

  //////////////////////////////////////////////////////////////////////
  //  Equality and hashing
  //////////////////////////////////////////////////////////////////////
  inline friend Bool equal(ReteToken * a, ReteToken * b)
  {
    if (a->rule_id != b->rule_id || a->arity != b->arity)
      return false;
    for (int i = a->arity - 1; i >= 0; i--)
      if (a->token[i] != b->token[i])
        return false;
    return true;
  }

  inline friend unsigned hash(ReteToken * a)
  {
    unsigned int h = a->rule_id + a->arity;
    for (int i = a->arity - 1; i >= 0; i--)
      h += (unsigned int)a->token[i];
    return h;
  }
};

#endif
