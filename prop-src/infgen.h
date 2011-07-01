///////////////////////////////////////////////////////////////////////////////
//  The inference compiler
///////////////////////////////////////////////////////////////////////////////
#ifndef inference_compiler_h
#define inference_compiler_h

#include "rwgen.h"
#include "classdef.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent an inference class. 
//
///////////////////////////////////////////////////////////////////////////////
class InferenceClass : public ClassDefinition
{  InferenceClass(const InferenceClass&);
   void operator = (const InferenceClass&);
public:
   InferenceClass(Id, Inherits, TyQual, Decls);
  ~InferenceClass();
   virtual void gen_class_interface(CodeGen&);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Inference compiler. 
//
///////////////////////////////////////////////////////////////////////////////
class InferenceCompiler : virtual public RewritingCompiler {

   InferenceCompiler(const InferenceCompiler&); // no copy constructor
   void operator = (const InferenceCompiler&); // no assignment

public:
   ////////////////////////////////////////////////////////////////////////////
   //  Constructor and destructor
   ////////////////////////////////////////////////////////////////////////////
   InferenceCompiler();
  ~InferenceCompiler();

protected:
   ////////////////////////////////////////////////////////////////////////////
   //  Methods for compiling inference rules
   ////////////////////////////////////////////////////////////////////////////
   void gen_inference_rules       (Id, InferenceRules);
   void gen_alpha_tests           (Id, int, class HashTable&);
   void gen_beta_tests            (Id, int, InferenceRule[], class HashTable&);
   void gen_inference_axioms      (Id, InferenceRules);
   void gen_inference_actions     (Id, InferenceRules);
   void gen_dispatch_table        (Id, class HashTable&);
   int  gen_network_table         (Id, int, InferenceRule[], class HashTable&);
   void gen_inference_constructor (Id, int, class HashTable&);
   void gen_conclusions           (Conclusions);
   void gen_conclusion            (Conclusion);
};

#endif
