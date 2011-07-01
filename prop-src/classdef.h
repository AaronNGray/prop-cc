//////////////////////////////////////////////////////////////////////////////
//
//  The following class is the base class of all strategies to 
//  generate a special Prop class definition.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef class_definition
#define class_definition

#include "codegen.h"
#include "ir.h"
#include "ast.h"
#include "hashtab.h"

//////////////////////////////////////////////////////////////////////////////
//
//  Forward definitions
//
//////////////////////////////////////////////////////////////////////////////
class PropVisualizer;

//////////////////////////////////////////////////////////////////////////////
//
//  This class represents a basic class definition
//
//////////////////////////////////////////////////////////////////////////////
class ClassDefinition : public Loc
{  
   ClassDefinition();
   ClassDefinition(const ClassDefinition&);
   void operator = (const ClassDefinition&);
public:
   ///////////////////////////////////////////////////////////////////////////
   //
   //  Types of various subclasses.  For matters of convenience, we'll
   //  break the encapsulation and let the base class knows its own
   //  identity.
   //
   ///////////////////////////////////////////////////////////////////////////
   enum CLASS_TYPE { DATATYPE_CLASS,
                     REWRITE_CLASS,
		     SYNTAX_CLASS,
		     INFERENCE_CLASS,
		     GRAPHTYPE_CLASS,
		     DATAFLOW_CLASS,
		     DATATYPE_SUBCLASS,
		     ATTRIBUTE_GRAMMAR_CLASS,
		     CONSTRAINT_CLASS,
		     ANY_CLASS,
		     LAST_CLASS
                   };
   static const char * class_type_name[LAST_CLASS];
   static HashTable defined_classes;
public:
   ///////////////////////////////////////////////////////////////////////////
   //
   //  All classes definition include the following information
   //
   ///////////////////////////////////////////////////////////////////////////
   const CLASS_TYPE class_type;    //
   Id           class_name;        // name of class
   TyVars       parameters;        // type parameters
   Inherits     inherited_classes; // all inherited classes
   TyQual       qualifiers;        // all qualifiers
   Decls        class_body;        // class body 
   Protocols    protocols;         // protocols
   Decls        constructor_code;  // code for constructor
   Decls        destructor_code;   // code for destructor

   enum DefKind { INTERFACE_DEFINITION,    // interface in a class
		  INLINE_IMPLEMENTATION,   // interface + implementation 
		  EXTERNAL_IMPLEMENTATION, // external implementation
		  EXTERNAL_INSTANTIATION,  // external (per instance)
		  EXTERNAL_DEFINITION
                };

public:
   ///////////////////////////////////////////////////////////////////////////
   //
   //  Constructors and destructors  
   //
   ///////////////////////////////////////////////////////////////////////////
            ClassDefinition(CLASS_TYPE, Id, TyVars, Inherits, TyQual, Decls);
   virtual ~ClassDefinition();

   ///////////////////////////////////////////////////////////////////////////
   //
   //  Useful methods
   //
   ///////////////////////////////////////////////////////////////////////////
   Id   mangled_name() const;    // name of class mangled
   Bool is_polymorphic() const;  // polymorphic type?
   Bool is_view() const;         // is it a view?
   void add_base_class (Id, Scope = PUBLICscope, TyQual = QUALnone);
   void append_base_class (Id, Scope = PUBLICscope, TyQual = QUALnone);

   ///////////////////////////////////////////////////////////////////////////
   //
   //  Method to generate a class definition
   //
   ///////////////////////////////////////////////////////////////////////////
   virtual void gen_class_predefinition(CodeGen&);
   virtual void gen_class_definition(CodeGen&);
   virtual void gen_class_postdefinition(CodeGen&);
   virtual void gen_class_implementation(CodeGen&, Tys, DefKind);

   ///////////////////////////////////////////////////////////////////////////
   //
   //  Methods to generate code for a class
   //
   ///////////////////////////////////////////////////////////////////////////
   virtual void gen_class_constructor(CodeGen&,Tys,DefKind);
   virtual void gen_class_destructor(CodeGen&,Tys,DefKind);

   ///////////////////////////////////////////////////////////////////////////
   //
   //  Method for visualizing the class
   //
   ///////////////////////////////////////////////////////////////////////////
   virtual void visualize (PropVisualizer&);

   ///////////////////////////////////////////////////////////////////////////
   //
   //  Retrieve information from class
   //
   ///////////////////////////////////////////////////////////////////////////
   static ClassDefinition * lookup_class (CLASS_TYPE, Id name);
   static ClassDefinition * lookup_class_or_datatype(Id name, Id constr);
   static void  insert_class (ClassDefinition *);

   ///////////////////////////////////////////////////////////////////////////
   //
   //  Methods to update constructor/destructor information 
   //
   ///////////////////////////////////////////////////////////////////////////
   static void add_constructor_code(Id name, Id constr, Decls);
   static void add_destructor_code(Id name, Id destr, Decls);

protected:
   virtual void gen_class_interface(CodeGen&);
   virtual void gen_class_constructor_parameters(CodeGen&,Tys,DefKind);
   virtual void gen_class_constructor_initializers(CodeGen&,Tys,DefKind);
   virtual void gen_class_constructor_body(CodeGen&,Tys,DefKind);
   virtual void gen_class_destructor_body(CodeGen&,Tys,DefKind);
};

#endif
