///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\datatype.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_d_a_t_a_t_y_p_eco_c_c_Q1("a_");
#line 1 "../../prop-src/datatype.pcc"
/////////////////////////////////////////////////////////////////////////////
//
//  This file implements the DatatypeClass
//
//////////////////////////////////////////////////////////////////////////////

#include <AD/strings/quark.h>
#include "datatype.h"
#include "ast.h"
#include "ir.h"
#include "type.h"
#include "options.h"
#include "list.h"
#include "datagen.h"

//////////////////////////////////////////////////////////////////////////////
//
//  Constructor for DatatypeClass
//
//////////////////////////////////////////////////////////////////////////////

DatatypeClass::DatatypeClass
    (CLASS_TYPE my_class_type,
        Id cid, Id id, TyVars p, Inherits i, TyQual q, Decls d, Cons c,
        DatatypeHierarchy * r)
    : ClassDefinition(my_class_type,id,p,i,q,d),
      constructor_name(cid), cons(c), root(r),
      generating_list_special_forms(false),
      cons_arg_ty(NOty), has_destructor(false)
{
  is_const = (qualifiers & QUALconst) ? "const " : "";
  is_list  = is_list_constructor(constructor_name);
  is_array = is_array_constructor(constructor_name);
}

DatatypeClass::~DatatypeClass() {}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to update the qualifiers and other
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::get_info()
{
  if (got_info) return;

  got_info = true;

/*
  match (lookup_ty(datatype_name))
  {
  DATATYPEty({ qualifiers = q, body = b, unit, arg, terms ... },_):
    {
      qualifiers = q;
      class_body = b;
      for (int i = 0; i < number_of_subclasses; i++)
      {
        match (subclasses[i]->cons)
        {
        ONEcons { inherit, qual, body ... }:
          {  // subclasses[i]->inherited_classes = inherit;
	      subclasses[i]->qualifiers |= qual;
	      subclasses[i]->class_body = body;
          }
        |  _: // skip
        }
      }
    }
  | _: // skip
  }
*/


  //
  //  Construct the inheritance list and fix it up if necessary
  //
  build_inheritance_list();

  //
  //  Use inline methods if we are not in space saving mode
  //  or if the user specificately specified the inline qualifier
  //
  Bool must_inline     = (qualifiers & QUALinline);
  Bool must_not_inline = (qualifiers & QUALextern);
  if (must_inline && must_not_inline)
  {
    error( "%Ldatatype %s%V cannot be inline and external at the same time",
           datatype_name, parameters
         );
  }
  if (must_inline)
    inline_methods = true;
  else if (must_not_inline)
    inline_methods = false;
  else
    inline_methods = !options.save_space;

  //
  //  Use a variant tag if we have subclasses in our hierarchy
  //  and if the tag is not embedded into the pointer representation
  //

  has_variant_tag = ((optimizations & OPTtagless) == 0);

  has_destructor = (qualifiers & QUALvirtualdestr) || (cons && is_array);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Constructor for DatatypeHierarchy
//
//////////////////////////////////////////////////////////////////////////////

DatatypeHierarchy::DatatypeHierarchy
    (Id id, TyVars p, Inherits i, TyQual q, TermDefs t, Decls d)
    : DatatypeClass(DATATYPE_CLASS,id,
#line 117 "../../prop-src/datatype.pcc"
#line 117 "../../prop-src/datatype.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_d_a_t_a_t_y_p_eco_c_c_Q1
#line 117 "../../prop-src/datatype.pcc"
#line 117 "../../prop-src/datatype.pcc"
 + id,p,i,q,d,NOcons,this),
      datatype_name(id), term_defs(t), subclasses(0),
      number_of_subclasses(0), datatype_ty(NOty)
{
  unit_constructors = 0;
  arg_constructors  = 0;
  constructor_terms = 0;
  use_persist_base  = false;
  use_gc_base       = false;
  got_info          = false;

  //
  //  Build the class hierarchy
  //
  build_class_hierarchy();
}

DatatypeHierarchy::~DatatypeHierarchy()
{
  delete [] subclasses;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to build the class hierarchy given a datatype.
//  We'll create a DatatypeClass object for each subclass.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::build_class_hierarchy()
{
  // don't bother building the class hierarchy for views

  if (is_view()) return;

  // construct class hierarchy

  
#line 154 "../../prop-src/datatype.pcc"
#line 197 "../../prop-src/datatype.pcc"
{
  Ty _V1 = lookup_ty(datatype_name);
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 157 "../../prop-src/datatype.pcc"
              
              arity = _DATATYPEtycon(_TYCONty(_V1)->_1)->unit + _DATATYPEtycon(_TYCONty(_V1)->_1)->arg;
              unit_constructors = _DATATYPEtycon(_TYCONty(_V1)->_1)->unit;
              arg_constructors  = _DATATYPEtycon(_TYCONty(_V1)->_1)->arg;
              constructor_terms = _DATATYPEtycon(_TYCONty(_V1)->_1)->terms;
              optimizations     = _DATATYPEtycon(_TYCONty(_V1)->_1)->opt;
              datatype_ty       = _V1;
              _DATATYPEtycon(_TYCONty(_V1)->_1)->hierarchy         = this;
              
              if (_DATATYPEtycon(_TYCONty(_V1)->_1)->arg > 0) // build class hierarchy only if we have more than
              	      // one variants
              {
                if (_DATATYPEtycon(_TYCONty(_V1)->_1)->opt & OPTsubclassless) // no subclass
                {
                  number_of_subclasses = 0;
                  for (int i = 0; i < arity; i++)
                  {
                    if (_DATATYPEtycon(_TYCONty(_V1)->_1)->terms[i]->ty != NOty)
                    {
                      cons = _DATATYPEtycon(_TYCONty(_V1)->_1)->terms[i];
                      constructor_name = cons->name;
                      is_list  = is_list_constructor(constructor_name);
                      is_array = is_array_constructor(constructor_name);
                      class_body = append(class_body, _DATATYPEtycon(_TYCONty(_V1)->_1)->terms[i]->body);
                    }
                  }
                }
              else // use subclass
                {
                  number_of_subclasses = _DATATYPEtycon(_TYCONty(_V1)->_1)->arg;
                  subclasses = new DatatypeClass * [number_of_subclasses];
                  for (int i = 0, j = 0; i < arity; i++)
                  {
                    if (_DATATYPEtycon(_TYCONty(_V1)->_1)->terms[i]->ty != NOty)
                      subclasses[j++] = build_one_subclass(_DATATYPEtycon(_TYCONty(_V1)->_1)->terms[i]);
                  }
                }
              }
              
#line 195 "../../prop-src/datatype.pcc"
              } break;
            default: {
              L1:; } break;
          }
        } else { goto L1; }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 197 "../../prop-src/datatype.pcc"
#line 197 "../../prop-src/datatype.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to build one subclass in the hierarchy.
//
//////////////////////////////////////////////////////////////////////////////

DatatypeClass *DatatypeHierarchy::build_one_subclass( Cons cons)
{
  
#line 208 "../../prop-src/datatype.pcc"
#line 223 "../../prop-src/datatype.pcc"
{
  if (cons) {
#line 211 "../../prop-src/datatype.pcc"
    
    return cons->class_def = new DatatypeClass(
    	      DATATYPE_SUBCLASS,
    	      cons->name,
    	      Quark(mangle(datatype_name),"_",mangle(cons->name)),
    	      parameters,
    	      add_inherit(class_name,parameters,cons->inherit),
    	      cons->qual,
    	      cons->body,
    	      cons,
    	      this);
    
#line 222 "../../prop-src/datatype.pcc"
  } else {
#line 223 "../../prop-src/datatype.pcc"
   return 0; 
#line 223 "../../prop-src/datatype.pcc"
  }
}
#line 224 "../../prop-src/datatype.pcc"
#line 224 "../../prop-src/datatype.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to build the inheritance list of the class hierachy.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::build_inheritance_list()
{
  if (qualifiers & QUALrelation)    append_base_class("Fact");
  if (qualifiers & QUALrewritable)  append_base_class("TermObj");
  if (qualifiers & QUALpersistent)  append_base_class("PObject");

  if (qualifiers & QUALcollectable)
  {
    // Make sure we are only inheriting from one collectable object
    // Make sure virtual inheritance is not used.
    // Make sure that the collectable object is the first base class.

    int pos       = 0;
    int count     = 0;
    for_each (Inherit, inh, inherited_classes)
    {
      if((inh->qualifiers & QUALcollectable) || is_gc_ty(inh->super_class))
      {
        count++;
        if (pos != 0)
        {
          msg("%!%wcollectable object %T must be first base class\n",
          inh->loc(), inh->super_class);
        }
      }
      if (inh->qualifiers & QUALvirtual)
      {
        msg( "%!%wvirtual inheritance of %T may fail"
	         " with garbage collection\n",
             inh->loc(), inh->super_class
           );
      }
      pos++;
    }
    if (count >= 2)
      error("%Linheritance of multiple collectable object will fail\n");
    if (count == 0)
      add_base_class("GCObject");
  }
}

//////////////////////////////////////////////////////////////////////////////
//
// Method to generate a class constructor
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_constructor( CodeGen& C, Tys tys, DefKind k)
{
  ClassDefinition::gen_class_constructor( C, tys, k);

  if (is_list)
  {
    generating_list_special_forms = true;
    ClassDefinition::gen_class_constructor( C, tys, k);
    generating_list_special_forms = false;
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the constructor parameters.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_constructor_parameters
   (CodeGen& C, Tys tys, DefKind k)
{
  Ty arg_ty = cons_arg_ty;
  
#line 302 "../../prop-src/datatype.pcc"
#line 307 "../../prop-src/datatype.pcc"
{
  Ty _V2 = deref(arg_ty);
  if (_V2) {
    switch (_V2->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V2)->_1)) {
          L2:; } else {
          switch ((int)_TYCONty(_V2)->_1) {
            case ((int)TUPLEtycon): {
              if (_TYCONty(_V2)->_2) {
                if (_TYCONty(_V2)->_2->_2) {
                  if (_TYCONty(_V2)->_2->_2->_2) { goto L2; } else {
                    if (
#line 304 "../../prop-src/datatype.pcc"
                    generating_list_special_forms
#line 304 "../../prop-src/datatype.pcc"
) {
                      
#line 305 "../../prop-src/datatype.pcc"
                     arg_ty = mktuplety(
#line 305 "../../prop-src/datatype.pcc"
#line 305 "../../prop-src/datatype.pcc"
                      list_1_(_TYCONty(_V2)->_2->_1)
#line 305 "../../prop-src/datatype.pcc"
#line 305 "../../prop-src/datatype.pcc"
                      ); 
#line 305 "../../prop-src/datatype.pcc"
                    } else {
                       goto L2; }
                  }
                } else { goto L2; }
              } else { goto L2; }
              } break;
            default: { goto L2; } break;
          }
        }
        } break;
      default: { goto L2; } break;
    }
  } else { goto L2; }
}
#line 307 "../../prop-src/datatype.pcc"
#line 307 "../../prop-src/datatype.pcc"

  Parameter param;
  switch (k)
  {
  case EXTERNAL_IMPLEMENTATION:
  case EXTERNAL_INSTANTIATION:
    param = TYsimpleformal; break;
  default:
    param = TYformal; break;
  }
  C.pr( "%b", arg_ty, cons->name, param);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the constructor initializers.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_constructor_initializers
   (CodeGen& C, Tys tys, DefKind k)
{
  
#line 329 "../../prop-src/datatype.pcc"
#line 351 "../../prop-src/datatype.pcc"
{
  if (cons) {
#line 332 "../../prop-src/datatype.pcc"
    
    Id colon = " : ";
    Id comma = "";
    C.pr( "%^");
    
    // First generate the tag initializer
    if (root->has_variant_tag)
    {
      if (k == EXTERNAL_INSTANTIATION)
        C.pr( " : %s%P(tag_%S)", root->class_name, tys, constructor_name);
      else
        C.pr( " : %s%V(tag_%S)", root->class_name, parameters, constructor_name);
      colon = ""; comma = ", ";
    }
    
    // Now generate the initializers for the arguments
    gen_constructor_initializers( C, tys, k, cons_arg_ty, colon, comma);
    
#line 349 "../../prop-src/datatype.pcc"
  } else {}
}
#line 351 "../../prop-src/datatype.pcc"
#line 351 "../../prop-src/datatype.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the constructor initializers.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_constructor_initializers
   (CodeGen& C, Tys tys, DefKind k, Ty ty, Id colon, Id comma)
{
  if (is_array)
  {
    C.pr( "%s%slen_(x__len_)", colon, comma);
    colon = "";
    comma = ", ";
    ty = mkarrayty( ty, IDexp( "len_"));
  }

  
#line 371 "../../prop-src/datatype.pcc"
#line 423 "../../prop-src/datatype.pcc"
{
  Ty _V3 = deref(ty);
  if (_V3) {
    switch (_V3->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V3)->_1)) {
          switch (_TYCONty(_V3)->_1->tag__) {
            case a_TyCon::tag_RECORDtycon: {
#line 403 "../../prop-src/datatype.pcc"
              
              Ids l; Tys t;
              for (l = _RECORDtycon(_TYCONty(_V3)->_1)->_1, t = _TYCONty(_V3)->_2; l && t; l = l->_2, t = t->_2)
              {
                if (! is_array_ty(t->_1))
                {
                  C.pr( "%s%s%s(x_%s)", colon, comma, l->_1, l->_1);
                  colon = "";
                  comma = ", ";
                }
              }
              
#line 414 "../../prop-src/datatype.pcc"
              } break;
            default: {
              L3:; 
#line 416 "../../prop-src/datatype.pcc"
              
              if (! is_array_ty(_V3))
              {
                C.pr( "%s%s%S(x_%S)",
                      colon, comma, constructor_name, constructor_name);
                colon = ""; comma = ", ";
              }
              
#line 423 "../../prop-src/datatype.pcc"
              } break;
          }
        } else {
          switch ((int)_TYCONty(_V3)->_1) {
            case ((int)TUPLEtycon): {
              if (_TYCONty(_V3)->_2) {
#line 375 "../../prop-src/datatype.pcc"
                
                int i = 1;
                for_each(Ty, t, _TYCONty(_V3)->_2)
                {
                  if (generating_list_special_forms && i == 2)
                  {
                    if (k == EXTERNAL_INSTANTIATION)
                       C.pr( "%s%s_%i((%s%P *)0)", colon, comma,
                              i, root->class_name, tys, i);
                    else
                       C.pr("%s%s_%i((%s%V *)0)", colon, comma,
                              i, root->class_name, parameters, i);
                    colon = "";
                    comma = ", ";
                  }
                  else
                  {
                    if (! is_array_ty(t))
                    {
                      C.pr("%s%s_%i(x_%i)", colon, comma, i, i);
                      colon = "";
                      comma = ", ";
                    }
                  }
                  i++;
                }
                
#line 401 "../../prop-src/datatype.pcc"
              } else {}
              } break;
            default: { goto L3; } break;
          }
        }
        } break;
      default: { goto L3; } break;
    }
  } else { goto L3; }
}
#line 424 "../../prop-src/datatype.pcc"
#line 424 "../../prop-src/datatype.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Methods to generate body of a constructor
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_constructor_body( CodeGen& C, Tys tys, DefKind k)
{
  if (cons == NOcons) return;

  Ty ty = cons_arg_ty;
  if (is_array)
    ty = mkarrayty( ty, IDexp( "len_"));

  // Now generate the initializers for array arguments

  
#line 443 "../../prop-src/datatype.pcc"
#line 464 "../../prop-src/datatype.pcc"
{
  Ty _V4 = deref(ty);
  if (_V4) {
    switch (_V4->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V4)->_1)) {
          switch (_TYCONty(_V4)->_1->tag__) {
            case a_TyCon::tag_RECORDtycon: {
#line 456 "../../prop-src/datatype.pcc"
              
              Ids ls; Tys ts;
              for(ls = _RECORDtycon(_TYCONty(_V4)->_1)->_1, ts = _TYCONty(_V4)->_2; ls && ts; ls = ls->_2, ts = ts->_2)
              {
                gen_array_initializer( C, _TYCONty(_V4)->_2, k, ls->_1, ts->_1, "x_");
              }
              
#line 462 "../../prop-src/datatype.pcc"
              } break;
            default: {
              L4:; 
#line 464 "../../prop-src/datatype.pcc"
             gen_array_initializer( C, tys, k, mangle( cons->name), _V4, "x_"); 
#line 464 "../../prop-src/datatype.pcc"
              } break;
          }
        } else {
          switch ((int)_TYCONty(_V4)->_1) {
            case ((int)TUPLEtycon): {
              if (_TYCONty(_V4)->_2) {
#line 447 "../../prop-src/datatype.pcc"
                
                int i = 1;
                for_each(Ty, t, _TYCONty(_V4)->_2)
                {
                  gen_array_initializer( C, tys, k, index_of(i), t, "x");
                  i++;
                }
                
#line 454 "../../prop-src/datatype.pcc"
              } else {}
              } break;
            default: { goto L4; } break;
          }
        }
        } break;
      default: { goto L4; } break;
    }
  } else { goto L4; }
}
#line 465 "../../prop-src/datatype.pcc"
#line 465 "../../prop-src/datatype.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Methods to generate body of a constructor
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_array_initializer
   (CodeGen& C, Tys tys, DefKind k, Id exp, Ty ty, Id prefix)
{
  
#line 477 "../../prop-src/datatype.pcc"
#line 498 "../../prop-src/datatype.pcc"
{
  Ty _V5 = deref(ty);
  if (_V5) {
    switch (_V5->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V5)->_1)) {
          switch (_TYCONty(_V5)->_1->tag__) {
            case a_TyCon::tag_ARRAYtycon: {
              if (_TYCONty(_V5)->_2) {
                if (_TYCONty(_V5)->_2->_2) {
                  L5:; } else {
#line 480 "../../prop-src/datatype.pcc"
                  
                  C.pr( "%^{%+"
                        "%^for (int i__ = 0; i__ < (%e); i__++)"
                        "%^{%+",
                        _ARRAYtycon(_TYCONty(_V5)->_1)->ARRAYtycon);
                  if (is_array)
                  {
                    C.pr( "%^typedef %t ELEMENT_TYPE__;"
                          "%^new (%S + i__) ELEMENT_TYPE__ (%s%S[i__]);",
                          _TYCONty(_V5)->_2->_1, "", exp, prefix, exp);
                  }
                  else
                  {
                    C.pr( "%^%S[i__] = %s%S[i__];", exp, prefix, exp);
                  }
                  C.pr("%-%^}" "%-%^}");
                  
#line 496 "../../prop-src/datatype.pcc"
                }
              } else { goto L5; }
              } break;
            default: { goto L5; } break;
          }
        } else { goto L5; }
        } break;
      default: { goto L5; } break;
    }
  } else { goto L5; }
}
#line 498 "../../prop-src/datatype.pcc"
#line 498 "../../prop-src/datatype.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Methods to generate array initialization code.
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//  Methods to generate destructor code.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_destructor_body( CodeGen& C, Tys tys, DefKind)
{
  if (is_array && cons)
  {
    C.pr( "%^{%+"
          "%^for (int i__; i__ < len_; i__++)"
          "%^{%+"
          "%^typedef %t ELEMENT_TYPE;"
          "%^(%S+i__)->~ELEMENT_TYPE();"
          "%-%^}"
          "%-%^}",
          cons_arg_ty, "", constructor_name
        );
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Methods to generate the forward declarations for a datatype.
//  These include unit constructors for the class.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_forward_declarations( CodeGen& C)
{
  // don't generate code for views
  if (is_view()) return;

  get_info();
  generate_forward_class_declarations(C);
  generate_forward_constructor_declarations(C);

  // don't generate code for forward definitions
  if (term_defs == 
#line 546 "../../prop-src/datatype.pcc"
#line 546 "../../prop-src/datatype.pcc"
nil_1_
#line 546 "../../prop-src/datatype.pcc"
#line 546 "../../prop-src/datatype.pcc"
) return;

  generate_unit_constructors(C);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate forward class declarations.
//  If the datatype is monomorphic, generate a typedef.
//  Otherwise, generate a forward template declaration
//  and a #define.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_forward_class_declarations( CodeGen& C)
{  // Generate forward declarations only if we have at least one variant
  if (arg_constructors == 0 && term_defs != 
#line 562 "../../prop-src/datatype.pcc"
#line 562 "../../prop-src/datatype.pcc"
nil_1_
#line 562 "../../prop-src/datatype.pcc"
#line 562 "../../prop-src/datatype.pcc"
) return;

  C.pr(
        "%^%/"
        "%^//"
        "%^// Forward class definition for %s%V"
        "%^//"
        "%^%/"
        "%n#ifndef datatype_%S_defined"
        "%n#define datatype_%S_defined",
        datatype_name, parameters, datatype_name, datatype_name
      );

  if (is_polymorphic())
  {  // Polymorphic datatypes
    C.pr( "%^%Hclass %s;", parameters, class_name);
    C.pr( "%n#define %s%v %s%s%V *\n",
          datatype_name, parameters, is_const, class_name, parameters);
  }
  else
  {  // Monomorphic datatypes
     C.pr( "%^  class %s;", class_name);
     C.pr( "%^  typedef %s%s * %s;", is_const, class_name, datatype_name);
  }

  C.pr( "%n#endif\n\n");
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate forward declarations for datatype constructors.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_forward_constructor_declarations( CodeGen& C)
{
}


//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code for the definition of a datatype
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_datatype_definitions( CodeGen& C)
{
  // don't generate code for views
  if (is_view()) return;

  // don't generate code for forward definitions
  if (term_defs == 
#line 613 "../../prop-src/datatype.pcc"
#line 613 "../../prop-src/datatype.pcc"
nil_1_
#line 613 "../../prop-src/datatype.pcc"
#line 613 "../../prop-src/datatype.pcc"
) return;

  // If there are no argument constructors, don't generate code
  get_info();

  if (arg_constructors == 0)
    gen_class_postdefinition(C);
  else
  {
    // Otherwise generate code for all the classes.
    gen_class_definition(C);
    for (int i = 0; i < number_of_subclasses; i++)
      subclasses[i]->gen_class_definition(C);

    // Generate datatype constructors
    DefKind kind = inline_methods
        ? INLINE_IMPLEMENTATION : INTERFACE_DEFINITION;

    generate_datatype_constructors(C,
#line 631 "../../prop-src/datatype.pcc"
#line 631 "../../prop-src/datatype.pcc"
nil_1_
#line 631 "../../prop-src/datatype.pcc"
#line 631 "../../prop-src/datatype.pcc"
,kind);

    if (options.inline_casts == false || parameters != 
#line 633 "../../prop-src/datatype.pcc"
#line 633 "../../prop-src/datatype.pcc"
nil_1_
#line 633 "../../prop-src/datatype.pcc"
#line 633 "../../prop-src/datatype.pcc"
)
      generate_downcasting_functions(C);
    C.pr("\n\n");
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the unit constructor names.
//  If there are no argument constructors, represent the constructors as
//  enum's.   Otherwise, represent them as #define constants.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_unit_constructors( CodeGen& C)
{
  if (unit_constructors == 0) return;
  if (arg_constructors == 0)
    generate_constructor_tags( C, "", "", unit_constructors, constructor_terms);
  else
    generate_define_tags( C, unit_constructors, constructor_terms);
  C.pr( "\n\n");
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the constructor tags as enum's.
//  Constructor tags are used to represent unit constructors
//  and variant tags.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_constructor_tags
  (CodeGen& C, Id enum_prefix, Id tag_prefix, int n, Cons terms[])
{
  C.pr("%^enum %s%s {%+", enum_prefix, datatype_name);
  Bool comma = false;
  for (int i = 0; i < n; i++)
  {
    if (comma) C.pr
      ( ", ");
    if (i % 3 == 0)
      C.pr( "%^");
    C.pr( "%s%S = %i", tag_prefix, terms[i]->name, tag_of(terms[i]));
    comma = true;
  }
  C.pr( "%-%^};\n\n");
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate the unit constructor tags as #define constants.
//  This is necessary if we have both unit and argument constructors
//  for a type.  If polymorphic types are used, the #define constants
//  are not given a type.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_define_tags( CodeGen& C, int n, Cons terms[])
{
  for (int i = 0; i < n; i++)
    C.pr("%n#  define %S %i", terms[i]->name, tag_of(terms[i]));
/*
   {  if (is_polymorphic())
     C.pr("%n#  define %S %i", terms[i]->name, tag_of(terms[i]));
      else
     C.pr("%n#  define %S (%s)%i",
        terms[i]->name, datatype_name, tag_of(terms[i]));
   }
*/
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate datatype constructor functions for a datatype.
//  Datatype constructor functions are just external functions.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_datatype_constructors
   (CodeGen& C, Tys tys, DefKind kind)
{
  C.pr(
        "%^%/"
        "%^//"
        "%^// Datatype constructor functions for %s%V"
        "%^//"
        "%^%/",
        datatype_name, parameters
      );

  generate_datatype_constructor( C, tys, kind);
  for (int i = 0; i < number_of_subclasses; i++)
    subclasses[i]->generate_datatype_constructor( C, tys, kind);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a datatype constructor function.
//
//////////////////////////////////////////////////////////////////////////////
void DatatypeClass::generate_datatype_constructor
   (CodeGen& C, Tys tys, DefKind kind)
{
  // No datatype descriptor, then no datatype constructor function
  if (cons == NOcons) return;

  Id prefix = "";

  switch (kind)
  {
  case INLINE_IMPLEMENTATION:   prefix = "inline "; break;
  case INTERFACE_DEFINITION:
  case EXTERNAL_DEFINITION:     prefix = "extern "; break;
  case EXTERNAL_IMPLEMENTATION:
  case EXTERNAL_INSTANTIATION:  prefix = ""; break;
  }

  // Generate special form constructors for lists and vectors
  int special_forms = 1;
  if (is_list)
    special_forms = 2;
  else if (is_array)
    special_forms = options.max_vector_len + 2;
  Tys params = 
#line 757 "../../prop-src/datatype.pcc"
#line 757 "../../prop-src/datatype.pcc"
nil_1_
#line 757 "../../prop-src/datatype.pcc"
#line 757 "../../prop-src/datatype.pcc"
;
  Ids labels = 
#line 758 "../../prop-src/datatype.pcc"
#line 758 "../../prop-src/datatype.pcc"
nil_1_
#line 758 "../../prop-src/datatype.pcc"
#line 758 "../../prop-src/datatype.pcc"
;

  for (int form = 1; form <= special_forms; form++)
  {
    Ty formals_ty = cons_arg_ty;
    Ty actuals_ty = cons_arg_ty;
    Id formals_name = constructor_name;

    // If it is a list special form, fake the second argument

    if (is_list && form == 2)
    {
      
#line 770 "../../prop-src/datatype.pcc"
#line 775 "../../prop-src/datatype.pcc"
{
  Ty _V6 = deref(formals_ty);
  if (_V6) {
    switch (_V6->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V6)->_1)) {
          L6:; 
#line 775 "../../prop-src/datatype.pcc"
         bug("%LDatatypeClass::generate_datatype_constructor: %T\n", _V6); 
#line 775 "../../prop-src/datatype.pcc"
        } else {
          switch ((int)_TYCONty(_V6)->_1) {
            case ((int)TUPLEtycon): {
              if (_TYCONty(_V6)->_2) {
                if (_TYCONty(_V6)->_2->_2) {
                  if (_TYCONty(_V6)->_2->_2->_2) { goto L6; } else {
#line 773 "../../prop-src/datatype.pcc"
                   formals_ty = actuals_ty = mktuplety(
#line 773 "../../prop-src/datatype.pcc"
#line 773 "../../prop-src/datatype.pcc"
                    list_1_(_TYCONty(_V6)->_2->_1)
#line 773 "../../prop-src/datatype.pcc"
#line 773 "../../prop-src/datatype.pcc"
                    ); 
#line 773 "../../prop-src/datatype.pcc"
                  }
                } else { goto L6; }
              } else { goto L6; }
              } break;
            default: { goto L6; } break;
          }
        }
        } break;
      default: { goto L6; } break;
    }
  } else { goto L6; }
}
#line 776 "../../prop-src/datatype.pcc"
#line 776 "../../prop-src/datatype.pcc"

    }

    // If it is an array special form, fake the parameter arguments

    if (is_array && form >= 2)
    {
      if (form >= 3)
      {
        params = 
#line 785 "../../prop-src/datatype.pcc"
#line 785 "../../prop-src/datatype.pcc"
list_1_(cons_arg_ty,params)
#line 785 "../../prop-src/datatype.pcc"
#line 785 "../../prop-src/datatype.pcc"
;
        labels = append( labels, 
#line 786 "../../prop-src/datatype.pcc"
#line 786 "../../prop-src/datatype.pcc"
list_1_(index_of((form - 2)))
#line 786 "../../prop-src/datatype.pcc"
#line 786 "../../prop-src/datatype.pcc"
);
      }
      formals_ty = mkrecordty( labels, params, false);
      formals_name = mangle( constructor_name);
    }

    switch (kind)
    {
    case EXTERNAL_INSTANTIATION:
    case EXTERNAL_DEFINITION:
          C.pr(
                "%^%s%s%P * %S %b",
                prefix, root->class_name, tys, constructor_name,
                formals_ty, formals_name, TYsimpleformal
              );
          break;
    default:
          C.pr(
                "%^%H%s%s%V * %S %b",
                parameters,
                prefix, root->class_name, parameters, constructor_name,
                formals_ty, formals_name, TYformal
              );
          break;
    }

    //  Don't generate code for interface definitions

    if (kind == INTERFACE_DEFINITION ||
        kind == EXTERNAL_DEFINITION)
      { C.pr( ";"); continue; }

    C.pr( "%^{%+");

    //
    // Generate a temporary array
    //
    if (is_array && form >= 2)
    {
      C.pr( "%^const int x__len_ = %i;", form - 2);
      C.pr( "%^%t x_%S[%i];", cons_arg_ty, "", constructor_name, form - 2);
      for (int i = 0; i < form - 2; i++)
        C.pr( "%^x_%S[%i] = x__%i;", constructor_name, i, i+1);
    }

    C.pr( "%^return ");

    //
    // In the tagged pointer representation, the variant tag is embedded
    // within the data address.
    //
    if (root->optimizations & OPTtaggedpointer)
    {
    switch (kind)
      {
      case EXTERNAL_INSTANTIATION:
            C.pr ( "(%s%P*)((unsigned long)(", root->class_name, tys);
            break;
      default:
            C.pr ( "(%s%V*)((unsigned long)(", root->class_name, parameters);
            break;
      }
    }

    //
    // In the unboxed representation, the argument is embedded within
    // the address.
    //
    if (root->optimizations & OPTunboxed)
    {
       int tag_bits = DatatypeCompiler::max_embedded_bits;
       for (int i = root->unit_constructors;
            i >= DatatypeCompiler::max_embedded_tags; i >>= 1) tag_bits++;
         C.pr(
               "(%s *)(((unsigned long)%b<<(%i+1))|%i)",
               root->class_name, actuals_ty, constructor_name, TYactual,
               tag_bits, (1 << tag_bits)
             );
    }

    //
    // The usual boxed implementation
    //
    else
    {
      C.pr ("new ");
      switch (kind)
      {
      case EXTERNAL_INSTANTIATION:
            if (is_array)
              C.pr( "(sizeof(%s%P)+sizeof(%t)*x__len_) ",
                    class_name, tys, cons_arg_ty, "");
                    C.pr ("%s%P %b", class_name, tys, actuals_ty,
                    constructor_name, TYactual);
            break;
      default:
            if (is_array)
              C.pr( "(sizeof(%s%V)+sizeof(%t)*x__len_) ",
                    class_name, parameters, cons_arg_ty, "");
            C.pr( "%s%V %b", class_name, parameters, actuals_ty,
                  constructor_name, TYactual);
            break;
      }
    }

    if (root->optimizations & OPTtaggedpointer)
    {
      switch (kind)
      {
      case EXTERNAL_INSTANTIATION:
            C.pr( ")|%s%P::tag_%S)",
   	              root->class_name, tys, constructor_name);
   	        break;
      default:
            C.pr( ")|%s%V::tag_%S)",
   	              root->class_name, parameters, constructor_name);
   	        break;
      }
    }

    C.pr( ";%-%^}\n");
  }
}


//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code before the interface
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_predefinition( CodeGen& C)
{
  
#line 919 "../../prop-src/datatype.pcc"
#line 943 "../../prop-src/datatype.pcc"
{
  if (cons) {
#line 922 "../../prop-src/datatype.pcc"
    
    cons_arg_ty = cons->ty;
    C.pr(
          "%^%/"
          "%^//"
          "%^// Class for datatype constructor %s%V::%s"
          "%^//"
          "%^%/",
          root->datatype_name, parameters, cons->name
        );
    
#line 932 "../../prop-src/datatype.pcc"
  } else {
#line 934 "../../prop-src/datatype.pcc"
    
    cons_arg_ty = NOty;
    C.pr(
          "%^%/"
          "%^//"
          "%^// Base class for datatype %s%V"
          "%^//"
          "%^%/",
          root->datatype_name, parameters);
    
#line 943 "../../prop-src/datatype.pcc"
  }
}
#line 944 "../../prop-src/datatype.pcc"
#line 944 "../../prop-src/datatype.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
// Method to generate the interface of a class
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_interface( CodeGen& C)
{
   // Generate the internal representation
   // if there is a constructor descripter and the
   // argument is not represented in unboxed form.

   C.pr( "%-%^public:%+");

   
#line 961 "../../prop-src/datatype.pcc"
#line 972 "../../prop-src/datatype.pcc"
{
  if (cons) {
#line 964 "../../prop-src/datatype.pcc"
    
    if ((cons->opt & OPTunboxed) == 0)
    {
      C.pr( "%#%^%b\n", cons->location->begin_line, cons->location->file_name,
            cons->ty, cons->name, TYbody);
    }
    
#line 970 "../../prop-src/datatype.pcc"
  } else {}
}
#line 972 "../../prop-src/datatype.pcc"
#line 972 "../../prop-src/datatype.pcc"


   DefKind kind = root->inline_methods
     ? INLINE_IMPLEMENTATION : INTERFACE_DEFINITION;

   // Generate the constructor of the class
   if (cons != NOcons)
     gen_class_constructor( C, 
#line 979 "../../prop-src/datatype.pcc"
#line 979 "../../prop-src/datatype.pcc"
nil_1_
#line 979 "../../prop-src/datatype.pcc"
#line 979 "../../prop-src/datatype.pcc"
, kind);

   // Generate the destructor of the class

   if ((root->qualifiers & QUALvirtualdestr) ||
       (qualifiers & QUALvirtualdestr) ||
       (cons && is_array))
     gen_class_destructor( C, 
#line 986 "../../prop-src/datatype.pcc"
#line 986 "../../prop-src/datatype.pcc"
nil_1_
#line 986 "../../prop-src/datatype.pcc"
#line 986 "../../prop-src/datatype.pcc"
, kind);

   // Generate the method declarations for all different types
   // of extra functionality
   if (root->qualifiers & QUALpersistent)
     generate_persistence_interface(C);
   //if (root->qualifiers & QUALvariable)    generate_logic_interface(C);
   if (root->qualifiers & QUALcollectable)
     generate_gc_interface(C);
   if (root->qualifiers & QUALrelation)
     generate_inference_interface(C);
}

//////////////////////////////////////////////////////////////////////////////
//
// Method to generate the interface of a base class
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::gen_class_interface( CodeGen& C)
{
  // Generate tags for arg constructors

  if (arg_constructors > 1)
  {
    C.pr( "%-%^public:%+");
    generate_constructor_tags( C, "Tag_", "tag_",
        arg_constructors, constructor_terms + unit_constructors);
  }

  // Generate a variant tag and a base class constructor for it
  // only if we have a variant_tag representation.

  if (has_variant_tag)
  {
    C.pr(
          "%-%^public:%+"
          "%^const Tag_%s tag__; // variant tag"
          "%-%^protected:%+"
          "%^inline %s(Tag_%s t__) : tag__(t__) {%&}",
          datatype_name, class_name, datatype_name, constructor_code
        );
  }

  // Generate the untagging functions
  generate_untagging_member_functions(C);

  DatatypeClass::gen_class_interface(C);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate untagging functions for a datatype class.
//  Three untagging functions are generated:
//      int untag() const  --- returns the variant tag of the class
//      friend int untag(type * x) -- return a tag for the object x
//                                    so that each variant (boxed or unboxed)
//                                    gets a unique tag.
//      friend int boxed(type * x) -- returns true if object is boxed.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_untagging_member_functions( CodeGen& C)
{
   ///////////////////////////////////////////////////////////////////////////
   // Generate untagger
   ///////////////////////////////////////////////////////////////////////////
   // if (has_variant_tag)
   //    C.pr("%^inline int untag() const { return tag__; }");
}

void DatatypeHierarchy::generate_untagging_functions( CodeGen& C)
{
  if (arg_constructors == 0) return;

  ///////////////////////////////////////////////////////////////////////////
  // Generate boxed() predicate
  ///////////////////////////////////////////////////////////////////////////

  if (unit_constructors == 0)
    C.pr( "%^%Hinline int boxed(const %s%V *) { return 1; }",
 	      parameters, class_name, parameters);
  else if (unit_constructors == 1)
    C.pr( "%^%Hinline int boxed(const %s%V * x) { return x != 0; }",
 	      parameters, class_name, parameters);
  else
     C.pr( "%^%Hinline int boxed(const %s%V * x)"
           " { return (unsigned long)x >= %i; }",
 	       parameters, class_name, parameters, unit_constructors);

  ///////////////////////////////////////////////////////////////////////////
  // Generate function that untags the pointer if
  // the tags are embedded into a pointer.
  ///////////////////////////////////////////////////////////////////////////

  if (optimizations & OPTtaggedpointer)
  {
  C.pr(
        "%^%/"
        "%^//"
        "%^// Embbeded tag extraction functions"
        "%^//"
        "%^%/"
        "%^%Hinline int untagp(const %s%V * x)"
        "%^  { return (unsigned long)x & %i; }"
        "%^%Hinline %s%s%V * derefp(const %s%V * x)"
        "%^  { return (%s%s%V*)((unsigned long)x & ~%i); }",
        parameters, class_name, parameters,
        DatatypeCompiler::max_embedded_tags - 1,
        parameters,is_const,class_name, parameters, class_name, parameters,
        is_const, class_name, parameters,
        DatatypeCompiler::max_embedded_tags - 1
      );
  }

  ///////////////////////////////////////////////////////////////////////////
  // Generate a generic untag function that works on all boxed
  // and unboxed variants.
  ///////////////////////////////////////////////////////////////////////////

  if (unit_constructors == 0)
  {
    // No unboxed variants.
    if (optimizations & OPTtaggedpointer)
      C.pr( "%^%Hinline int untag(const %s%V * x) { return untagp(x); }",
            parameters, class_name, parameters);
    else if (arg_constructors == 1)
      C.pr( "%^%Hinline int untag(const %s%V *) { return 0; }",
            parameters, class_name, parameters);
    else
      C.pr( "%^%Hinline int untag(const %s%V * x) { return x->tag__; }",
            parameters, class_name, parameters);
  }
  else if (unit_constructors == 1)
  {
    // Only one unboxed variants.
    if (optimizations & OPTtaggedpointer)
      C.pr( "%^%Hinline int untag(const %s%V * x) "
            "{ return x ? untagp(x)+1 : 0; }",
            parameters, class_name, parameters);
    else if (arg_constructors == 1)
      C.pr( "%^%Hinline int untag(const %s%V * x) { return x ? 1 : 0; }",
            parameters, class_name, parameters);
    else
      C.pr( "%^%Hinline int untag(const %s%V * x)"
            " { return x ? (x->tag__+1) : 0; }",
            parameters, class_name, parameters);
  }
  else
  {
    // More than one unboxed variants.
    if (optimizations & OPTtaggedpointer)
      C.pr( "%^%Hinline int untag(const %s%V * x)"
            " { return boxed(x) ? untagp(x) + %i : (int)x; }",
            parameters, class_name, parameters, unit_constructors);
    else if (arg_constructors == 1)
      C.pr( "%^%Hinline int untag(const %s%V * x)"
            " { return boxed(x) ? %i : (int)x; }",
            parameters, class_name, parameters, 1 + unit_constructors);
    else
      C.pr( "%^%Hinline int untag(const %s%V * x)"
            " { return boxed(x) ? x->tag__ + %i : (int)x; }",
            parameters, class_name, parameters, unit_constructors);
  }
}

//////////////////////////////////////////////////////////////////////////////
//
// Method to generate downcasting functions
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::generate_downcasting_functions( CodeGen& C)
{
  C.pr(
        "%^%/"
        "%^//"
        "%^// Downcasting functions for %s%V"
        "%^//"
        "%^%/",
        datatype_name, parameters
      );
  for (int i = 0; i < number_of_subclasses; i++)
  {
    DatatypeClass * D = subclasses[i];
    C.pr( "%^%Hinline %s%V * _%S(const %s%V * _x_) { return (%s%V *)_x_; }",
          parameters, D->class_name, parameters, D->constructor_name,
          class_name, parameters, D->class_name, parameters);
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code right after the main class definition.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_class_postdefinition( CodeGen& C)
{
   C.pr( "\n");

   // Interfaces for extra features
   if (root->qualifiers & QUALprintable) generate_print_interface(C);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code right after the main class definition.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::gen_class_postdefinition( CodeGen& C)
{
   generate_untagging_functions(C);
   DatatypeClass::gen_class_postdefinition(C);
}
#line 1202 "../../prop-src/datatype.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 156
Number of ifs generated      = 27
Number of switches generated = 14
Number of labels             = 6
Number of gotos              = 27
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
