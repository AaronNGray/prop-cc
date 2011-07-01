///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\datagen.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/datagen.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the datatype compiler of Prop.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/strings/quark.h>
#include "ir.h"
#include "ast.h"
#include "type.h"
#include "datagen.h"
#include "options.h"
#include "datatype.h"
#include "list.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructors for datatype compiler
//
///////////////////////////////////////////////////////////////////////////////

int DatatypeCompiler::max_embedded_tags = 0;
int DatatypeCompiler::max_embedded_bits = 0;
LabelGen DatatypeCompiler::temp_vars("_T");

DatatypeCompiler::DatatypeCompiler( TyOpt opt, int embedded_tags)
    : optimizations(opt)
{
  max_embedded_tags = embedded_tags;
  max_embedded_bits = 0;
  for (int i = embedded_tags - 1; i > 0; i >>= 1)
    max_embedded_bits++;
}

DatatypeCompiler::~DatatypeCompiler() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to create a datatype hierarchy
//
///////////////////////////////////////////////////////////////////////////////

static DatatypeHierarchy *create_datatype_hierarchy
   (Id name, TyVars parameters, Inherits inhs, TyQual qual,
    TermDefs terms, Decls body)
{
  
#line 49 "../../prop-src/datagen.pcc"
#line 54 "../../prop-src/datagen.pcc"
{
  Ty _V1 = lookup_ty(name);
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
#line 52 "../../prop-src/datagen.pcc"
             return _DATATYPEtycon(_TYCONty(_V1)->_1)->hierarchy; 
#line 52 "../../prop-src/datagen.pcc"
              } break;
            default: {
              L1:; 
#line 54 "../../prop-src/datagen.pcc"
             return new DatatypeHierarchy( name, parameters, inhs, qual, terms, body); 
#line 54 "../../prop-src/datagen.pcc"
              } break;
          }
        } else { goto L1; }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 55 "../../prop-src/datagen.pcc"
#line 55 "../../prop-src/datagen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Top level method to map datatype and type definitions into
//  a C++ class hierarchy.
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeCompiler::gen_datatype
  (
    DatatypeDefs data_defs,   // datatype definitions
    ViewDefs     view_defs,   // view definitions
    LawDefs      law_defs,    // law definitions
    TyDefs       ty_defs      // type definitions
  )
{
  // Build the classes hierarchies

  int N = length(data_defs);
  DatatypeHierarchy ** H = new DatatypeHierarchy * [N];
  {
    int i = 0;
    for_each (DatatypeDef, d, data_defs)
    {
      
#line 81 "../../prop-src/datagen.pcc"
#line 87 "../../prop-src/datagen.pcc"
{
#line 84 "../../prop-src/datagen.pcc"
  
  H[i] = create_datatype_hierarchy(d->_1,d->_2,d->_3,d->_4,d->_5,d->_6);
  i++;
  
#line 87 "../../prop-src/datagen.pcc"
}
#line 88 "../../prop-src/datagen.pcc"
#line 88 "../../prop-src/datagen.pcc"

    }
  }

  // Generate forward datatype definitions

    for (int i = 0; i < N; i++)
      if (H[i])
        H[i]->generate_forward_declarations(*this);

  //  Generate type definitions

    for_each (TyDef, t, ty_defs)
      gen_type_def(t);

  //  Generate the class hierarchies

    for (int i = 0; i < N; i++)
      if (H[i])
        H[i]->generate_datatype_definitions(*this);

  //  Compile the pattern laws
  gen_law_defs(law_defs);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a type definition
//
///////////////////////////////////////////////////////////////////////////////
void DatatypeCompiler::gen_type_def( TyDef ty_def)
{
  
#line 120 "../../prop-src/datagen.pcc"
#line 131 "../../prop-src/datagen.pcc"
{
  if (
#line 122 "../../prop-src/datagen.pcc"
  ty_def->_4
#line 122 "../../prop-src/datagen.pcc"
) {
    
#line 123 "../../prop-src/datagen.pcc"
    
    pr(
        "%^%/%^// Definition of type %s%V%^%/"
        "%#"
        "%^%^typedef %t;\n\n",
        ty_def->_1, ty_def->_2, ty_def->begin_line, ty_def->file_name, ty_def->_3, ty_def->_1);
    
#line 129 "../../prop-src/datagen.pcc"
  } else {
    }
}
#line 131 "../../prop-src/datagen.pcc"
#line 131 "../../prop-src/datagen.pcc"
/* skip */
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to preprocess a datatype (for constraints)
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeCompiler::preprocess_def( DatatypeDef def)
{
  
#line 142 "../../prop-src/datagen.pcc"
#line 156 "../../prop-src/datagen.pcc"
{
  if (
#line 143 "../../prop-src/datagen.pcc"
  (def->_4 & QUALunifiable)
#line 143 "../../prop-src/datagen.pcc"
) {
    
#line 144 "../../prop-src/datagen.pcc"
    
    Id      var_term_name = Quark(def->_1,"_var");
    TermDef var_term = 
#line 146 "../../prop-src/datagen.pcc"
#line 146 "../../prop-src/datagen.pcc"
    TERMdef(var_term_name, mkidvarty(def->_1,def->_2), nil_1_, nil_1_, NOpat, nil_1_, OPTnone, QUALvariable, NOexp)
#line 151 "../../prop-src/datagen.pcc"
#line 151 "../../prop-src/datagen.pcc"
    ;
    def->_5 = 
#line 152 "../../prop-src/datagen.pcc"
#line 152 "../../prop-src/datagen.pcc"
    list_1_(var_term,def->_5)
#line 152 "../../prop-src/datagen.pcc"
#line 152 "../../prop-src/datagen.pcc"
    ;
    // msg("[Unifiable datatype %s]\n", id);
    
#line 154 "../../prop-src/datagen.pcc"
  } else {
    }
}
#line 156 "../../prop-src/datagen.pcc"
#line 156 "../../prop-src/datagen.pcc"

}
#line 158 "../../prop-src/datagen.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 25
Number of ifs generated      = 4
Number of switches generated = 2
Number of labels             = 1
Number of gotos              = 3
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
