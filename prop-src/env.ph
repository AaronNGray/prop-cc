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
