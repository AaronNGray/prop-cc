///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\instance.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/instance.pcc"
//////////////////////////////////////////////////////////////////////////////
//
//  This file implements datatype instantiations
//
//////////////////////////////////////////////////////////////////////////////

#include "datatype.h"
#include "ast.h"
#include "ir.h"
#include "type.h"
#include "datagen.h"
#include "options.h"

//////////////////////////////////////////////////////////////////////////////
//
//  Method to instantiate a list of datatypes
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeCompiler::instantiate_datatypes( Bool external, Tys tys)
{
   if ( !external)
     {  for_each (Ty, ty, tys) instantiate_datatypes( true,ty); }
   {  for_each (Ty, ty, tys) instantiate_datatypes( external,ty); }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to instantiate one datatype
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeCompiler::instantiate_datatypes( Bool e, Ty ty)
{
  
#line 35 "../../prop-src/instance.pcc"
#line 51 "../../prop-src/instance.pcc"
{
  Ty _V1 = deref_all(ty);
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 38 "../../prop-src/instance.pcc"
            if (_DATATYPEtycon(_TYCONty(_V1)->_1)->hierarchy == 0)
              	      {
              	        error ( "%Ldefinition of datatype %T is unknown\n", ty);
              	      }
              	      else
              	      {
              	        if ( !is_ground( _V1))
              	          error( "%Lmissing parameters in instantiation of datatype %T\n", ty);
              
              	        _DATATYPEtycon(_TYCONty(_V1)->_1)->hierarchy->generate_datatype_instantiations( *this, _TYCONty(_V1)->_2, e);
              	      }
                      
#line 49 "../../prop-src/instance.pcc"
              } break;
            default: {
              L1:; 
#line 51 "../../prop-src/instance.pcc"
             error( "%Ldefinition of %T is not found\n", _V1); 
#line 51 "../../prop-src/instance.pcc"
              } break;
          }
        } else { goto L1; }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 52 "../../prop-src/instance.pcc"
#line 52 "../../prop-src/instance.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to instantiate a datatype
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_datatype_instantiations
   (CodeGen& C, Tys argument_types, Bool interface)
{
  if (is_view()) return;

  get_info();
  Id msg = interface ? "Interface specification" : "Instantiation";
  C.pr(
        "%^%/"
        "%^//"
        "%^// %s of datatype %s%P"
        "%^//"
        "%^%/"
        "%#",
        msg, datatype_name, argument_types, line, file
      );
  DefKind k = interface ? EXTERNAL_DEFINITION : EXTERNAL_INSTANTIATION;

  gen_class_instantiation(C, argument_types, k);
  gen_class_implementation(C, argument_types, k);
  for (int i = 0; i < number_of_subclasses; i++)
     subclasses[i]->gen_class_implementation(C, argument_types, k);
  C.pr( "\n\n");
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the implementation of a class
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_implementation(CodeGen& C, Tys tys, DefKind k)
{
  ///////////////////////////////////////////////////////////////////////////
  //
  // Compute the new argument types of the constructors
  //
  ///////////////////////////////////////////////////////////////////////////
  
#line 99 "../../prop-src/instance.pcc"
#line 113 "../../prop-src/instance.pcc"
{
  if (cons) {
#line 102 "../../prop-src/instance.pcc"
    
    switch (k)
    {
    case EXTERNAL_INSTANTIATION:
    case EXTERNAL_DEFINITION:
          cons_arg_ty = apply_ty(cons->cons_ty,tys); break;
    default:
          cons_arg_ty = cons->ty; break;
    }
    
#line 111 "../../prop-src/instance.pcc"
  } else {
#line 113 "../../prop-src/instance.pcc"
  cons_arg_ty = NOty; 
#line 113 "../../prop-src/instance.pcc"
  }
}
#line 114 "../../prop-src/instance.pcc"
#line 114 "../../prop-src/instance.pcc"


  ///////////////////////////////////////////////////////////////////////////
  //
  // Generate the constructors, destructors, and datatype constructor
  // function if inline methods are not used.
  //
  ///////////////////////////////////////////////////////////////////////////

  if ( !root->inline_methods)
  {
    // Generate the constructor of the class
    if (cons != NOcons && (k != EXTERNAL_DEFINITION || tys != 
#line 126 "../../prop-src/instance.pcc"
#line 126 "../../prop-src/instance.pcc"
nil_1_
#line 126 "../../prop-src/instance.pcc"
#line 126 "../../prop-src/instance.pcc"
))
      gen_class_constructor( C, tys, k);

    // Generate the destructor of the class
    if ((k != EXTERNAL_DEFINITION || tys != 
#line 130 "../../prop-src/instance.pcc"
#line 130 "../../prop-src/instance.pcc"
nil_1_
#line 130 "../../prop-src/instance.pcc"
#line 130 "../../prop-src/instance.pcc"
) &&
        ((root->qualifiers & QUALvirtualdestr) ||
        (qualifiers & QUALvirtualdestr) ||
        (cons && is_array)))
      gen_class_destructor( C, tys, k);

    if (cons != NOcons && (k != EXTERNAL_DEFINITION || tys != 
#line 136 "../../prop-src/instance.pcc"
#line 136 "../../prop-src/instance.pcc"
nil_1_
#line 136 "../../prop-src/instance.pcc"
#line 136 "../../prop-src/instance.pcc"
))
      generate_datatype_constructor( C, tys, k);
  }

  ///////////////////////////////////////////////////////////////////////////
  //
  // Generate the implementation methods for various features
  //
  ///////////////////////////////////////////////////////////////////////////
  if (root->qualifiers & QUALpersistent && k == EXTERNAL_INSTANTIATION)
    generate_persistence_implementation( C, tys, k);
  //if (root->qualifiers & QUALvariable && k == EXTERNAL_INSTANTIATION)
  //    generate_logic_implementation( C, tys, k);
  if (root->qualifiers & QUALcollectable && k == EXTERNAL_INSTANTIATION)
    generate_gc_implementation( C, tys, k);
  if (root->qualifiers & QUALrelation && k == EXTERNAL_INSTANTIATION)
    generate_inference_implementation( C, tys, k);
  if (root->qualifiers & QUALprintable)
    generate_print_implementation( C, tys, k);
}

void DatatypeHierarchy::gen_class_implementation( CodeGen& C, Tys tys,DefKind k)
{
  DatatypeClass::gen_class_implementation( C, tys, k);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate template instantiation of a class
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_instantiation( CodeGen& C, Tys tys, DefKind k)
{
  C.pr( "%^template class %S%P;", class_name, tys);

  if (cons != NOcons && root->inline_methods)
  {  // Constructor function
    C.pr(
          "%^template %S%P * %S%b;",
          root->class_name, tys,
          constructor_name, cons_arg_ty, cons->name, TYsimpleformal
        );
    // List constructor
    if (is_list)
    {
    C.pr(
          "%^template %S%P * %S%b;",
          root->class_name, tys, constructor_name,
          component_ty(cons_arg_ty,1), cons->name, TYsimpleformal
        );
    }
    // Array constructor
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate template instantiation of a class hierarchy
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::gen_class_instantiation( CodeGen& C, Tys tys, DefKind k)
{
  if (tys != 
#line 200 "../../prop-src/instance.pcc"
#line 200 "../../prop-src/instance.pcc"
nil_1_
#line 200 "../../prop-src/instance.pcc"
#line 200 "../../prop-src/instance.pcc"
 && k == EXTERNAL_INSTANTIATION && arg_constructors > 0)
  {
    C.pr( "%n#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION");
    DatatypeClass::gen_class_instantiation( C, tys, k);
    for (int i = 0; i < number_of_subclasses; i++)
    {
      subclasses[i]->gen_class_instantiation( C, tys, k);
    }
    gen_untagging_function_instantiation( C, tys, k);
    gen_downcasting_function_instantiation( C, tys, k);
    C.pr( "%n#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */");
   }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate template instantiation of untagging functions.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::gen_untagging_function_instantiation
   (CodeGen& C, Tys tys, DefKind k)
{
  C.pr(
        "%^template int boxed(const %S%P *);"
        "%^template int untag(const %S%P *);",
        class_name, tys, class_name, tys
      );
  if (optimizations & OPTtaggedpointer)
  {
    C.pr(
          "%^template int untagp(const %S%P *);"
          "%^template %S%P * derefp(const %S%P *);",
          class_name, tys, class_name, tys, class_name, tys
        );
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate template instantiation of downcasting functions.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::gen_downcasting_function_instantiation
   (CodeGen& C, Tys tys, DefKind k)
{
  if (options.inline_casts == false || parameters != 
#line 247 "../../prop-src/instance.pcc"
#line 247 "../../prop-src/instance.pcc"
nil_1_
#line 247 "../../prop-src/instance.pcc"
#line 247 "../../prop-src/instance.pcc"
)
  {
    for (int i = 0; i < number_of_subclasses; i++)
    {
      DatatypeClass * D = subclasses[i];
      C.pr(
            "%^template %S%P * _%S(const %S%P *);",
            root->class_name, tys, D->constructor_name, class_name, tys
          );
    }
  }
}
#line 259 "../../prop-src/instance.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 23
Number of ifs generated      = 3
Number of switches generated = 2
Number of labels             = 1
Number of gotos              = 3
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
