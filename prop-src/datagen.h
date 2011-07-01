///////////////////////////////////////////////////////////////////////////////
//
//  The Datatype compiler
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_compiler_h
#define datatype_compiler_h

#include "codegen.h"
#include "labelgen.h"
#include "ir.h"
#include "ast.h"
#include "hashtab.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward class declarations
//
///////////////////////////////////////////////////////////////////////////////
class DatatypeClass;
class DatatypeHierarchy;

///////////////////////////////////////////////////////////////////////////////
//
//  This class implements the datatype compiler.
//
///////////////////////////////////////////////////////////////////////////////
class DatatypeCompiler : virtual public CodeGen {
   DatatypeCompiler(const DatatypeCompiler&);  // no copy constructor
   void operator = (const DatatypeCompiler&);  // no assignment
public:
   ////////////////////////////////////////////////////////////////////////////
   //  Constructor and destructor
   ////////////////////////////////////////////////////////////////////////////
            DatatypeCompiler(TyOpt opt, int embedded_tags);
   virtual ~DatatypeCompiler();

   void preprocess_def (DatatypeDef);

   ////////////////////////////////////////////////////////////////////////////
   //
   //  Methods to enter and lookup a pattern constructor.
   //  These interact with the pattern/constructor environment.
   //  Called from the parser.
   //
   ////////////////////////////////////////////////////////////////////////////
   static void add_law    (LawDef);
   static Pat  lookup_pat (Id);
   static Exp  lookup_law (Id, Exps);

private:

   friend class DatatypeClass;
   friend class DatatypeHierarchy;
   TyOpt optimizations;            // optimizations in place
   static int   max_embedded_tags; // maximum number of tags that 
				   // can be embedded into the
                                   // lower bits of a pointer. 
   static int   max_embedded_bits;
   static LabelGen temp_vars;
   static HashTable law_env;

protected:

   ////////////////////////////////////////////////////////////////////////////
   //  Methods for mapping datatypes into C++ classes. 
   ////////////////////////////////////////////////////////////////////////////
   void gen_datatype(DatatypeDefs, ViewDefs, LawDefs, TyDefs);
   void gen_type_def(TyDef);
   void gen_law_defs    (LawDefs);
   void gen_law_inverse (const Loc *, Id, Ids, Exp, Ty);

   ////////////////////////////////////////////////////////////////////////////
   //  Methods for generating datatype instantiation code.
   ////////////////////////////////////////////////////////////////////////////
   void instantiate_datatypes (Bool external, Tys);
   void instantiate_datatypes (Bool external, Ty);
};

#endif
