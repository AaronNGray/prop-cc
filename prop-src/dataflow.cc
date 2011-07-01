///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\dataflow.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/dataflow.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the dataflow analyzer generator.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "basics.h"
#include "dataflow.h"
#include "type.h"
#include "ir.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the Prop datatypes.
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/dataflow.pcc"
#line 20 "../../prop-src/dataflow.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Domain
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/dataflow.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Domain>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/dataflow.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Domain
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/dataflow.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Domain>
//
///////////////////////////////////////////////////////////////////////////////
#line 20 "../../prop-src/dataflow.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Domain>;
template a_List<Domain> * list_1_(Domain x_1, a_List<Domain> *  x_2);
template a_List<Domain> * list_1_(Domain x_list_1_);
template int boxed(const a_List<Domain> *);
template int untag(const a_List<Domain> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

#line 20 "../../prop-src/dataflow.pcc"
#line 20 "../../prop-src/dataflow.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printer for a sequence of domains.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& print_domains( std::ostream& f, Id sep, Domains d)
{
  
#line 30 "../../prop-src/dataflow.pcc"
#line 33 "../../prop-src/dataflow.pcc"
{
  for (;;) {
    if (d) {
      if (d->_2) {
#line 33 "../../prop-src/dataflow.pcc"
       f << d->_1 << sep; d = d->_2; 
#line 33 "../../prop-src/dataflow.pcc"
      } else {
#line 32 "../../prop-src/dataflow.pcc"
       return f << d->_1; 
#line 32 "../../prop-src/dataflow.pcc"
      }
    } else {
#line 31 "../../prop-src/dataflow.pcc"
     return f; 
#line 31 "../../prop-src/dataflow.pcc"
    }
  }
}
#line 34 "../../prop-src/dataflow.pcc"
#line 34 "../../prop-src/dataflow.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printer for domains.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Domain d)
{
  
#line 45 "../../prop-src/dataflow.pcc"
#line 50 "../../prop-src/dataflow.pcc"
{
  if (d) {
    switch (d->tag__) {
      case a_Domain::tag_FINSETdom: {
#line 47 "../../prop-src/dataflow.pcc"
       f << "setof<" << _FINSETdom(d)->FINSETdom << ">"; 
#line 47 "../../prop-src/dataflow.pcc"
        } break;
      case a_Domain::tag_LIFTdom: {
#line 48 "../../prop-src/dataflow.pcc"
       f << "lift<" << _LIFTdom(d)->LIFTdom << ">"; 
#line 48 "../../prop-src/dataflow.pcc"
        } break;
      case a_Domain::tag_SUMdom: {
#line 49 "../../prop-src/dataflow.pcc"
       print_domains(f," + ",_SUMdom(d)->SUMdom); 
#line 49 "../../prop-src/dataflow.pcc"
        } break;
      default: {
#line 50 "../../prop-src/dataflow.pcc"
       print_domains(f," * ",_PRODUCTdom(d)->PRODUCTdom); 
#line 50 "../../prop-src/dataflow.pcc"
        } break;
    }
  } else {
#line 46 "../../prop-src/dataflow.pcc"
   f << "unit"; 
#line 46 "../../prop-src/dataflow.pcc"
  }
}
#line 51 "../../prop-src/dataflow.pcc"
#line 51 "../../prop-src/dataflow.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  The dataflow class
//
///////////////////////////////////////////////////////////////////////////////

DataflowClass::DataflowClass( Id id, Inherits i, TyQual q, Decls d)
    : ClassDefinition( DATAFLOW_CLASS,
	    id, 
#line 63 "../../prop-src/dataflow.pcc"
#line 63 "../../prop-src/dataflow.pcc"
nil_1_
#line 63 "../../prop-src/dataflow.pcc"
#line 63 "../../prop-src/dataflow.pcc"
, add_inherit( "DataflowBase", 
#line 63 "../../prop-src/dataflow.pcc"
#line 63 "../../prop-src/dataflow.pcc"
nil_1_
#line 63 "../../prop-src/dataflow.pcc"
#line 63 "../../prop-src/dataflow.pcc"
, i), q, d) {}
DataflowClass::~DataflowClass() {}

void DataflowClass::gen_class_interface( CodeGen& C)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for the dataflow compiler.
//
///////////////////////////////////////////////////////////////////////////////

DataflowCompiler:: DataflowCompiler () {}
DataflowCompiler::~DataflowCompiler () {}
#line 78 "../../prop-src/dataflow.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 1
Number of ifs generated      = 3
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
