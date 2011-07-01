//////////////////////////////////////////////////////////////////////////////
//
//  The following classes are used to generate C++ class definitions
//  for algebraic datatypes.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef datatype_class_definition
#define datatype_class_definition

#include "classdef.h"
#include "ast.ph"
#include "basics.ph"

//////////////////////////////////////////////////////////////////////////////
//
//  Forward type definitions.
//
//////////////////////////////////////////////////////////////////////////////

class DatatypeClass;
class DatatypeHierarchy;

//////////////////////////////////////////////////////////////////////////////
//
//  This class represents one subclass in an algebraic datatype class
//  hierarchy.
//
//////////////////////////////////////////////////////////////////////////////

class DatatypeClass : public ClassDefinition
{
  DatatypeClass();
  DatatypeClass(const DatatypeClass&);
  void operator = (const DatatypeClass&);

protected:
  Id                  constructor_name; // name of constructor
  Id                  is_const;         // a const type?
  Cons                cons;             // the constructor descriptor
  DatatypeHierarchy * root;             // root of the hierarchy
  Bool                generating_list_special_forms;
  Ty                  cons_arg_ty;      // current constructor argument type
  Bool                is_list;          // is it a list
  Bool                is_array;         // is it an array
  Bool                has_destructor;
public:
  ///////////////////////////////////////////////////////////////////////////
  //
  //  Constructors and destructors
  //
  ///////////////////////////////////////////////////////////////////////////

  DatatypeClass( CLASS_TYPE,
      Id, Id, TyVars, Inherits, TyQual, Decls, Cons, DatatypeHierarchy *);
  virtual ~DatatypeClass();

  void instantiate_datatype(CodeGen&, TyVars);
  void generate_forward_declarations(CodeGen&);
  void generate_datatype_constructor(CodeGen&,
  Tys, DefKind = INLINE_IMPLEMENTATION);

  virtual void visualize(PropVisualizer&);

protected:

  friend class DatatypeHierarchy;

  // Methods that adhere to the ClassDefinition protocol
  virtual void gen_class_destructor_body( CodeGen&, Tys, DefKind);

  virtual void gen_class_predefinition( CodeGen&);
  virtual void gen_class_interface( CodeGen&);
  virtual void gen_class_postdefinition( CodeGen&);
  virtual void gen_class_implementation( CodeGen&, Tys, DefKind);

  virtual void gen_class_instantiation( CodeGen&, Tys, DefKind);

  // Methods for generating the functionality for various features
  void generate_persistence_interface( CodeGen&);
  void generate_logic_interface( CodeGen&);
  void generate_gc_interface( CodeGen&);
  void generate_inference_interface( CodeGen&);
  virtual void generate_print_interface( CodeGen&);

  void generate_persistence_implementation( CodeGen&, Tys, DefKind);
  void generate_logic_implementation( CodeGen&, Tys, DefKind);
  void generate_gc_implementation( CodeGen&, Tys, DefKind);
  void generate_inference_implementation( CodeGen&, Tys, DefKind);
  virtual void generate_print_implementation( CodeGen&, Tys, DefKind);

private:
  //
  // Methods for generating class constructor code.
  //
  virtual void gen_class_constructor( CodeGen&, Tys, DefKind);
  virtual void gen_class_constructor_parameters( CodeGen&, Tys, DefKind);
  virtual void gen_class_constructor_initializers( CodeGen&, Tys, DefKind);
  virtual void gen_class_constructor_body( CodeGen&, Tys, DefKind);
  void gen_constructor_initializers( CodeGen&, Tys, DefKind, Ty, Id, Id);
  void gen_array_initializer( CodeGen&, Tys, DefKind, Id, Ty, Id);

  //
  // Methods for generating garbage collection code
  //
  void gen_super_class_tracing_methods( CodeGen&, Tys, DefKind);
  void gen_field_tracing_methods( CodeGen&, Exp, Ty, Tys, DefKind, Bool=false);

  //
  // Methods for generating persistence I/O code
  //
  void gen_super_class_persist_IO( CodeGen&, Tys, DefKind, Id);
  void gen_field_persist_IO( CodeGen&, Exp, Ty, Tys, DefKind, Id, Bool=false);
};

//////////////////////////////////////////////////////////////////////////////
//
//  This class is responsible for generating a class hierarchy for a
//  algebraic datatype.
//
//////////////////////////////////////////////////////////////////////////////
class DatatypeHierarchy : public DatatypeClass
{
  DatatypeHierarchy(const DatatypeHierarchy&);
  void operator = (const DatatypeHierarchy&);

protected:
  friend class DatatypeClass;
  const Id         datatype_name; // name of datatype
  const TermDefs   term_defs;     // datatype terms
  DatatypeClass ** subclasses;    // subclasses of the hierarchy
  int              number_of_subclasses;
  int              arity;             // total number of constructors
  int              unit_constructors; // number of unit constructors
  int              arg_constructors;  // number of argument constructors
  Cons *           constructor_terms; // constructor descriptors
  TyOpt            optimizations;     // optimizations?
  Bool             inline_methods;    // should be inline the methods?
  Bool             has_variant_tag;   // do we have a variant tag?
  Bool             use_gc_base;       // do we need to trace base class?
  Bool             use_persist_base;  // do we need to print base class?
  Ty               datatype_ty;       // type of the datatype
  Bool             got_info;

  void get_info();
public:
  DatatypeHierarchy( Id, TyVars, Inherits, TyQual, TermDefs, Decls);
  virtual ~DatatypeHierarchy();

  void generate_forward_declarations( CodeGen&);
  void generate_datatype_definitions( CodeGen&);
  void generate_datatype_instantiations( CodeGen&, Tys, Bool);

  virtual void gen_class_instantiation( CodeGen&, Tys, DefKind);

  virtual void visualize( PropVisualizer&);

protected:

  // Methods to generate code
  void generate_forward_class_declarations( CodeGen&);
  void generate_forward_constructor_declarations( CodeGen&);
  void generate_unit_constructors( CodeGen&);
  void generate_constructor_tags( CodeGen&, Id, Id, int, Cons []);
  void generate_define_tags( CodeGen&, int, Cons []);
  void generate_untagging_member_functions( CodeGen&);
  void generate_untagging_functions( CodeGen&);
  void generate_downcasting_functions( CodeGen&);
  void generate_datatype_constructors( CodeGen&, Tys, DefKind);

  // Methods to instantiate templates
  void gen_untagging_function_instantiation( CodeGen&, Tys, DefKind);
  void gen_downcasting_function_instantiation( CodeGen&, Tys, DefKind);

  // Methods that adhere to the ClassDefinition protocol
  virtual void gen_class_interface( CodeGen&);
  virtual void gen_class_implementation( CodeGen&, Tys, DefKind);
  virtual void gen_class_postdefinition( CodeGen&);

private:

  // Methods to constructor the class hierarchy
  void build_class_hierarchy();
  DatatypeClass * build_one_subclass( Cons);
  void build_inheritance_list();

  // Methods for generating pretty printers
  virtual void generate_print_interface( CodeGen&);
  virtual void generate_print_implementation( CodeGen&, Tys, DefKind);
  void generate_printer( CodeGen&, Tys, DefKind, Ty, Cons);
  void generate_default_printer( CodeGen&, Tys, DefKind, Ty, Cons, Ty);
  void generate_formatted_printer( CodeGen&, Tys, DefKind, Ty, Cons, Ty,
			   PrintFormats);
  void gen_print_field( CodeGen&, Exp, Ty);
};

#endif
