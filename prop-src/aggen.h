///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\aggen.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/aggen.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the definitions used in the attribute
//  grammar generator.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef attribute_grammar_h
#define attribute_grammar_h

#include "basics.h"
#include "ir.h"
#include "codegen.h"
#include "classdef.h"
#include "parsegen.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent an attribute grammar class
//
///////////////////////////////////////////////////////////////////////////////

class AttributeGrammarClass : public SyntaxClass
{
  AttributeGrammarClass(const AttributeGrammarClass&);
  void operator = (const AttributeGrammarClass&);

public:
  AttributeGrammarClass( Id, Inherits, TyQual, Decls);
  ~AttributeGrammarClass();

  virtual void gen_class_interface( CodeGen&);
  virtual void gen_class_implementation( CodeGen&, Tys, DefKind);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of the attribute grammar compiler
//
///////////////////////////////////////////////////////////////////////////////

class AttributeGrammarCompiler : virtual public ParserCompiler
{
  // no copy constructor
  AttributeGrammarCompiler(const AttributeGrammarCompiler&);
  void operator = (const AttributeGrammarCompiler&); // no assignment

public:
  AttributeGrammarCompiler();
  ~AttributeGrammarCompiler();

  void gen_attribute_grammar( Id, GramExp);
};

#endif
#line 56 "../../prop-src/aggen.ph"
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
