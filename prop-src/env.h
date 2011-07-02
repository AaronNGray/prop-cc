///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\env.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/env.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the environment class
//
///////////////////////////////////////////////////////////////////////////////

#ifndef environment_h
#define environment_h

#include "basics.h"
#include "ir.h"
#include "hashtab.h"

class Env
{
  void operator = (const Env&);
  HashTable env;
public:
  Env();
  Env(const Env&);
  ~Env();

  Ty operator () (Id) const;
  void bind (Id, Ty);
};

#endif
#line 28 "../../prop-src/env.ph"
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
