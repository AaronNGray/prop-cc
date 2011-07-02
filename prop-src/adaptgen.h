///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\adaptgen.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/adaptgen.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file defines the adaptive traversal class generator
//
///////////////////////////////////////////////////////////////////////////////

#ifndef adaptive_class_h
#define adaptive_class_h

#include "basics.h"
#include "ir.h"
#include "codegen.h"
#include "classdef.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of an adaptive class
//
///////////////////////////////////////////////////////////////////////////////

class AdaptiveClass : public ClassDefinition
{
  AdaptiveClass(const AdaptiveClass&);
  void operator = (const AdaptiveClass&);
public:
  AdaptiveClass(Id, Inherits, TyQual, Decls);
  ~AdaptiveClass();
};

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of the adaptive class compiler
//
///////////////////////////////////////////////////////////////////////////////

class AdaptiveClassCompiler : public virtual CodeGen
{
  AdaptiveClassCompiler(const AdaptiveClassCompiler&);
  void operator = (const AdaptiveClassCompiler&);
public:
  AdaptiveClassCompiler();
  ~AdaptiveClassCompiler();
};

#endif
#line 46 "../../prop-src/adaptgen.ph"
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
