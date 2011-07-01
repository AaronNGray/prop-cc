///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\env.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/env.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  Environment
//
///////////////////////////////////////////////////////////////////////////////

#include "env.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

Env::Env() : env( string_hash, string_equal) {}

Env::Env(const Env& E) : env( string_hash, string_equal)
{
  foreach_entry( i, E.env)
    env.insert(i->k,i->v);
}

Env::~Env() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Type lookup
//
///////////////////////////////////////////////////////////////////////////////

Ty Env::operator () (Id id) const
{
  HashTable::Entry * e = env.lookup(id);
  if (e)
    return (Ty)(e->v);
  else
    return NOty;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Insert a new entry to the environment
//
///////////////////////////////////////////////////////////////////////////////
void Env::bind( Id id, Ty ty)
{
  env.insert( id, ty);
}
#line 49 "../../prop-src/env.pcc"
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
