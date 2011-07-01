///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\classdef.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/classdef.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the class definition mechanism of Prop.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/strings/quark.h>
#include "ir.h"
#include "ast.h"
#include "classdef.h"
#include "type.h"
#include "list.h"
#include "hashtab.h"
#include "datatype.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Names of various class types
//
///////////////////////////////////////////////////////////////////////////////

const char * ClassDefinition::class_type_name[ ClassDefinition::LAST_CLASS] =
{
  "datatype",
  "rewrite class",
  "syntax class",
  "inference class",
  "graphtype",
  "dataflow class",
  "datatype subclass",
  "attributegrammar class",
  "constraint class",
  "class"
};

///////////////////////////////////////////////////////////////////////////////
//
//  Hashtable that contains all the classes indexed by name
//
///////////////////////////////////////////////////////////////////////////////

HashTable ClassDefinition::defined_classes(string_hash, string_equal);

ClassDefinition * ClassDefinition::lookup_class(CLASS_TYPE ct, Id name)
{
  HashTable::Entry * e = defined_classes.lookup(name);

  if (e == 0)
  {
    error("%L%s %s has not been defined\n", class_type_name[ct], name);
    return 0;
  }
  else
  {
    ClassDefinition * C = (ClassDefinition *)(e->v);

    if (C->class_type != ct && ct != ANY_CLASS)
    {
      error("%Lclass %s is not a %s\n"
	      "%!this is where %s %s was previously defined\n",
             name, class_type_name[ct],
	      C->loc(), class_type_name[C->class_type], name);
	  return 0;
    }
    else
      return C;
  }
}

void ClassDefinition::insert_class( ClassDefinition * C)
{
  HashTable::Entry * e = defined_classes.lookup( C->class_name);

  if (e)
  {
    ClassDefinition * old_def = (ClassDefinition*)(e->v);

    error("%Lredefinition of %s %s\n"
           "%!this is where it was previously defined.\n",
	    class_type_name[C->class_type], C->class_name,
	    old_def->loc());
  }
  else
  {
    defined_classes.insert( C->class_name,C);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructors for datatype compiler
//
///////////////////////////////////////////////////////////////////////////////

ClassDefinition::ClassDefinition
  ( CLASS_TYPE ct, Id id, TyVars p, Inherits subclasses, TyQual qual, Decls body)
  : class_type(ct),
    class_name(id), parameters(p), inherited_classes(subclasses),
    qualifiers(qual), class_body(body)
{
  constructor_code = 
#line 103 "../../prop-src/classdef.pcc"
#line 103 "../../prop-src/classdef.pcc"
nil_1_
#line 103 "../../prop-src/classdef.pcc"
#line 103 "../../prop-src/classdef.pcc"
;
  destructor_code  = 
#line 104 "../../prop-src/classdef.pcc"
#line 104 "../../prop-src/classdef.pcc"
nil_1_
#line 104 "../../prop-src/classdef.pcc"
#line 104 "../../prop-src/classdef.pcc"
;
  insert_class(this);
}

ClassDefinition::~ClassDefinition() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a class definition
//
///////////////////////////////////////////////////////////////////////////////

void ClassDefinition::gen_class_definition( CodeGen& C)
{
  gen_class_predefinition( C);
  C.pr( "%^%Hclass %s", parameters, class_name);
  if ( inherited_classes != 
#line 120 "../../prop-src/classdef.pcc"
#line 120 "../../prop-src/classdef.pcc"
nil_1_
#line 120 "../../prop-src/classdef.pcc"
#line 120 "../../prop-src/classdef.pcc"
) C.pr ( " : %I", inherited_classes);
  C.pr( " {%+\n");
  gen_class_interface( C);
  C.pr( "%&%-%^};\n", class_body);
  gen_class_postdefinition( C);
}

///////////////////////////////////////////////////////////////////////////////
//
//  The default is to generate nothing for the following
//
///////////////////////////////////////////////////////////////////////////////

void ClassDefinition::gen_class_predefinition( CodeGen& C) {}
void ClassDefinition::gen_class_interface( CodeGen& C) {}
void ClassDefinition::gen_class_postdefinition( CodeGen& C) {}
void ClassDefinition::gen_class_implementation( CodeGen& C, Tys, DefKind) {}

///////////////////////////////////////////////////////////////////////////////
//
//  Useful methods
//
///////////////////////////////////////////////////////////////////////////////

Id ClassDefinition::mangled_name() const { return mangle(class_name); }
Bool ClassDefinition::is_polymorphic() const { return parameters != 
#line 145 "../../prop-src/classdef.pcc"
#line 145 "../../prop-src/classdef.pcc"
nil_1_
#line 145 "../../prop-src/classdef.pcc"
#line 145 "../../prop-src/classdef.pcc"
; }
Bool ClassDefinition::is_view() const { return qualifiers & QUALview; }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to add a base class to the inheritance list
//
///////////////////////////////////////////////////////////////////////////////

void ClassDefinition::add_base_class( Id name, Scope s, TyQual q)
{
  inherited_classes = add_inherit( name, 
#line 156 "../../prop-src/classdef.pcc"
#line 156 "../../prop-src/classdef.pcc"
nil_1_
#line 156 "../../prop-src/classdef.pcc"
#line 156 "../../prop-src/classdef.pcc"
, inherited_classes, s, q);
}

void ClassDefinition::append_base_class( Id name, Scope s, TyQual q)
{
  inherited_classes = append( inherited_classes,
			  add_inherit( name, 
#line 162 "../../prop-src/classdef.pcc"
#line 162 "../../prop-src/classdef.pcc"
nil_1_
#line 162 "../../prop-src/classdef.pcc"
#line 162 "../../prop-src/classdef.pcc"
, 
#line 162 "../../prop-src/classdef.pcc"
#line 162 "../../prop-src/classdef.pcc"
nil_1_
#line 162 "../../prop-src/classdef.pcc"
#line 162 "../../prop-src/classdef.pcc"
, s, q));
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a constructor
//
///////////////////////////////////////////////////////////////////////////////
void ClassDefinition::gen_class_constructor( CodeGen& C, Tys tys, DefKind k)
{
  switch( k)
  {
  case INTERFACE_DEFINITION:
      C.pr( "%^%s ", class_name); break;
  case INLINE_IMPLEMENTATION:
      C.pr( "%^inline %s ", class_name); break;
  case EXTERNAL_IMPLEMENTATION:
      C.pr( "%^%H %s%V::%s ", parameters, class_name, parameters, class_name);
	  break;
  case EXTERNAL_INSTANTIATION:
  case EXTERNAL_DEFINITION:
      C.pr( "%^%s%P::%s ", class_name, tys, class_name);
	  break;
  }

  gen_class_constructor_parameters( C, tys, k);

  switch( k)
  {
  case INLINE_IMPLEMENTATION:
  case EXTERNAL_IMPLEMENTATION:
  case EXTERNAL_INSTANTIATION:
      gen_class_constructor_initializers( C, tys, k);
	  C.pr( "%^{%+");
      gen_class_constructor_body( C, tys, k);
	  if ( constructor_code) C.pr( "%^%&", constructor_code);
	  C.pr( "%-%^}");
	  break;
  case INTERFACE_DEFINITION:
  case EXTERNAL_DEFINITION:
	  C.pr( ";");
	  break;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a destructor
//
///////////////////////////////////////////////////////////////////////////////
void ClassDefinition::gen_class_destructor(CodeGen& C, Tys tys, DefKind k)
{
  Id v = (qualifiers & QUALvirtualdestr) ? "virtual " : "";
  switch (k)
  {
  case INTERFACE_DEFINITION:
      C.pr( "%^%s~%s()", v, class_name);
      break;
  case INLINE_IMPLEMENTATION:
      C.pr("%^inline %s~%s()", v, class_name);
      break;
  case EXTERNAL_IMPLEMENTATION:
      C.pr("%^%H %s%V::~%s()",
	     parameters, class_name, parameters, class_name);
	  break;
  case EXTERNAL_INSTANTIATION:
  case EXTERNAL_DEFINITION:
      C.pr("%^%s%P::~%s()", class_name, tys, class_name);
	  break;
  }

  switch (k)
  {
  case INLINE_IMPLEMENTATION:
  case EXTERNAL_IMPLEMENTATION:
  case EXTERNAL_INSTANTIATION:
	  C.pr( "%^{%+");
	  gen_class_destructor_body( C, tys, k);
	  if ( destructor_code) C.pr( "%^%&", destructor_code);
	  C.pr( "%-%^}");
	  break;
  case INTERFACE_DEFINITION:
  case EXTERNAL_DEFINITION:
	  C.pr( ";");
	  break;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Defaults method to generate various parts of the constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

void ClassDefinition::gen_class_constructor_parameters( CodeGen& C, Tys, DefKind)
{
  C.pr("()");
}

void ClassDefinition::gen_class_constructor_initializers( CodeGen&, Tys, DefKind)
{
}
void ClassDefinition::gen_class_constructor_body( CodeGen&, Tys, DefKind)
{
}
void ClassDefinition::gen_class_destructor_body( CodeGen&, Tys, DefKind)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to add constructor code to a class
//
///////////////////////////////////////////////////////////////////////////////

ClassDefinition * ClassDefinition::lookup_class_or_datatype
   (Id class_name, Id constructor)
{
  
#line 280 "../../prop-src/classdef.pcc"
#line 290 "../../prop-src/classdef.pcc"
{
  Ty _V1 = lookup_ty(class_name);
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
              if (
#line 282 "../../prop-src/classdef.pcc"
              (class_name == constructor)
#line 282 "../../prop-src/classdef.pcc"
) {
                
#line 283 "../../prop-src/classdef.pcc"
               return _DATATYPEtycon(_TYCONty(_V1)->_1)->hierarchy; 
#line 283 "../../prop-src/classdef.pcc"
              } else {
                
#line 285 "../../prop-src/classdef.pcc"
                
                Cons cons = lookup_cons( constructor);
                if (cons)
                  return cons->class_def;
                
#line 289 "../../prop-src/classdef.pcc"
              }
              } break;
            default: {
              L1:; 
#line 290 "../../prop-src/classdef.pcc"
             return lookup_class( ANY_CLASS,class_name); 
#line 290 "../../prop-src/classdef.pcc"
              } break;
          }
        } else { goto L1; }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 291 "../../prop-src/classdef.pcc"
#line 291 "../../prop-src/classdef.pcc"

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to add constructor code to a class
//
///////////////////////////////////////////////////////////////////////////////

void ClassDefinition::add_constructor_code
   (Id class_name, Id constructor, Decls body)
{
  ClassDefinition * C = lookup_class_or_datatype( class_name, constructor);
  if (C)
    C->constructor_code = append( C->constructor_code, body);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to add destructor code to a class
//
///////////////////////////////////////////////////////////////////////////////

void ClassDefinition::add_destructor_code
   (Id class_name, Id destructor, Decls body)
{
  ClassDefinition * C = lookup_class_or_datatype( class_name,destructor);
  if (C)
    C->destructor_code = append( C->destructor_code, body);
}
#line 322 "../../prop-src/classdef.pcc"
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
