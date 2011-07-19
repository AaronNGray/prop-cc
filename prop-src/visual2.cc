///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\visual2.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/visual2.pcc"
//////////////////////////////////////////////////////////////////////////////
//
//  This file implements the datatype definitions layout generator
//  for visualizing datatype definitions using vcg.
//
//////////////////////////////////////////////////////////////////////////////

#include <AD/strings/quark.h>
#include "ir.h"
#include "type.h"
#include "classdef.h"
#include "datatype.h"
#include "hashtab.h"
#include "visualize.h"

//////////////////////////////////////////////////////////////////////////////
//
//  This method visualizes all the class definitions.
//
//////////////////////////////////////////////////////////////////////////////

void PropVisualizer::visualize_datatype_definitions()
{
  const char * Datatypes = "All datatypes definitions";

  begin_node(Datatypes);
  label     (Datatypes);
  end_node  (Datatypes);

  for ( HashTable::Entry * e = ClassDefinition::defined_classes.first();
        e != 0; e = ClassDefinition::defined_classes.next(e))
  {
    ClassDefinition * C = (ClassDefinition *)(e->v);
    C->visualize(*this);
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  This method a particular class definitions.
//
//////////////////////////////////////////////////////////////////////////////

void ClassDefinition::visualize(PropVisualizer& v)
{
  v . begin_node (class_name);
  v . add_label  ("%s %s", class_type_name[class_type], class_name);
  v . make_label ();
  v . end_node   (class_name);
}

//////////////////////////////////////////////////////////////////////////////
//
//  This method visualizes a datatype hierarchy.
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeHierarchy::visualize(PropVisualizer& v)
{
  v . begin_node (datatype_name);
  v . add_label  ("datatype %s%V\n", datatype_name, parameters);
  v . add_label  ("(\"%s\" line %i)\n", file_name, begin_line);
  for (int i = 0; i < arity; i++)
  {
    Cons c = constructor_terms[i];
    v . add_label(" %s\n", constructor_terms[i]->name);
  }
  v . make_label ();

  int offset = 2;

  // Make a node for each of the constructors.
  for (int i = 0; i < arity; i++)
  {
    Cons c = constructor_terms[i];
    if (c->ty == NOty) // unit constructors
    {
      v . begin_node(c->name);
      v . label(c->name);
      v . end_node(c->name);
    }
    v . begin_edge(datatype_name, c->name);
    v . color (VCG::darkblue);
    v . arrowcolor (VCG::red);
    v . thickness (4);
    //v . anchor(offset + i + 1);
    v . end_edge(datatype_name, c->name);
  }

  v . end_node (datatype_name);

  // Argument constructors

  // Generate the only argument
  if (cons != NOcons)
    DatatypeClass::visualize(v);
}

//////////////////////////////////////////////////////////////////////////////
//
//  This method visualizes a datatype subclass
//
//////////////////////////////////////////////////////////////////////////////

void DatatypeClass::visualize( PropVisualizer& v)
{
  v . begin_node (constructor_name);
  v . add_label  ("%s\n", constructor_name);

  // Print each type on a single line
  int anchor = 2;

  
#line 113 "../../prop-src/visual2.pcc"
#line 128 "../../prop-src/visual2.pcc"
{
  Ty _V1 = cons->ty;
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_RECORDtycon: {
#line 121 "../../prop-src/visual2.pcc"
              
              Ids ls; Tys ts;
              for(ls = _RECORDtycon(_TYCONty(_V1)->_1)->_1, ts = _TYCONty(_V1)->_2; ls && ts; ls = ls->_2, ts = ts->_2)
              {
                v . add_type(constructor_name,ls->_1, ts->_1,anchor++); }
              
#line 126 "../../prop-src/visual2.pcc"
              } break;
            default: {
              L1:; 
#line 128 "../../prop-src/visual2.pcc"
             v . add_type(constructor_name,0,_V1,anchor); 
#line 128 "../../prop-src/visual2.pcc"
              } break;
          }
        } else {
          switch ((int)_TYCONty(_V1)->_1) {
            case ((int)v_TUPLEtycon): {
#line 116 "../../prop-src/visual2.pcc"
              
              for_each(Ty, t, _TYCONty(_V1)->_2)
                { v . add_type(constructor_name,0,t,anchor++); }
              
#line 119 "../../prop-src/visual2.pcc"
              } break;
            default: { goto L1; } break;
          }
        }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 129 "../../prop-src/visual2.pcc"
#line 129 "../../prop-src/visual2.pcc"


  v . make_label ();
  v . end_node   (constructor_name);
}

//////////////////////////////////////////////////////////////////////////////
//
//  This method adds a type component for a datatype constructor
//
//////////////////////////////////////////////////////////////////////////////

void PropVisualizer::add_type( Id cons_name, Id label, Ty ty, int anch)
{
  add_label("  ");
  if (label != 0) add_label("%s : ", label);
  add_label("%T\n", ty);

  // Create a has-a edge
  
#line 148 "../../prop-src/visual2.pcc"
#line 158 "../../prop-src/visual2.pcc"
{
  Ty _V2 = deref_all(ty);
  if (_V2) {
    switch (_V2->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V2)->_1)) {
          switch (_TYCONty(_V2)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 151 "../../prop-src/visual2.pcc"
              
              // begin_edge(cons_name,id);
              // color (lightgreen);
              // anchor(anch);
              // end_edge(cons_name,id);
              
#line 156 "../../prop-src/visual2.pcc"
              } break;
            default: {
              L2:; } break;
          }
        } else { goto L2; }
        } break;
      default: { goto L2; } break;
    }
  } else { goto L2; }
}
#line 158 "../../prop-src/visual2.pcc"
#line 158 "../../prop-src/visual2.pcc"

}
#line 160 "../../prop-src/visual2.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 44
Number of ifs generated      = 4
Number of switches generated = 5
Number of labels             = 2
Number of gotos              = 6
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
