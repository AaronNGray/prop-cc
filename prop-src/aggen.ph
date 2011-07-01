///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the definitions used in the attribute
//  grammar generator.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef attribute_grammar_h
#define attribute_grammar_h

#include "basics.ph"
#include "ir.ph"
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
