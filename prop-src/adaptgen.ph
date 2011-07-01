///////////////////////////////////////////////////////////////////////////////
//
//  This file defines the adaptive traversal class generator
//
///////////////////////////////////////////////////////////////////////////////

#ifndef adaptive_class_h
#define adaptive_class_h

#include "basics.ph"
#include "ir.ph"
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
