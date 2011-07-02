///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\collection.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/collection.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the analysis and type inference methods for
//  SETL-style collection types.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "collection.h"
#include "type.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the collection type descriptor.
//
///////////////////////////////////////////////////////////////////////////////

#line 19 "../../prop-src/collection.pcc"
#line 19 "../../prop-src/collection.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype CollectionDesc
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/collection.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<CollectionDesc>
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/collection.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype CollectionDesc
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/collection.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<CollectionDesc>
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/collection.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<CollectionDesc>;
template a_List<CollectionDesc> * list_1_(CollectionDesc x_1, a_List<CollectionDesc> *  x_2);
template a_List<CollectionDesc> * list_1_(CollectionDesc x_list_1_);
template int boxed(const a_List<CollectionDesc> *);
template int untag(const a_List<CollectionDesc> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

#line 19 "../../prop-src/collection.pcc"
#line 19 "../../prop-src/collection.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Functions for constructing some SETL-like type constructors.
//
///////////////////////////////////////////////////////////////////////////////

Ty mklistty( Ty a)
{  return TYCONty( COLtycon( 
#line 28 "../../prop-src/collection.pcc"
#line 28 "../../prop-src/collection.pcc"
COLdesc("list", COLLECTION_NONE, REP_none)
#line 28 "../../prop-src/collection.pcc"
#line 28 "../../prop-src/collection.pcc"
), 
#line 28 "../../prop-src/collection.pcc"
#line 28 "../../prop-src/collection.pcc"
list_1_(a)
#line 28 "../../prop-src/collection.pcc"
#line 28 "../../prop-src/collection.pcc"
); }

Ty mksetty( Ty a)
{  return TYCONty( COLtycon( 
#line 31 "../../prop-src/collection.pcc"
#line 31 "../../prop-src/collection.pcc"
COLdesc("set", COLLECTION_NONE, REP_none)
#line 31 "../../prop-src/collection.pcc"
#line 31 "../../prop-src/collection.pcc"
), 
#line 31 "../../prop-src/collection.pcc"
#line 31 "../../prop-src/collection.pcc"
list_1_(a)
#line 31 "../../prop-src/collection.pcc"
#line 31 "../../prop-src/collection.pcc"
); }

Ty mkbagty( Ty a)
{  return TYCONty( COLtycon( 
#line 34 "../../prop-src/collection.pcc"
#line 34 "../../prop-src/collection.pcc"
COLdesc("bag", COLLECTION_NONE, REP_none)
#line 34 "../../prop-src/collection.pcc"
#line 34 "../../prop-src/collection.pcc"
), 
#line 34 "../../prop-src/collection.pcc"
#line 34 "../../prop-src/collection.pcc"
list_1_(a)
#line 34 "../../prop-src/collection.pcc"
#line 34 "../../prop-src/collection.pcc"
); }

Ty mkmapty( Ty a, Ty b)
{  return TYCONty( COLtycon( 
#line 37 "../../prop-src/collection.pcc"
#line 37 "../../prop-src/collection.pcc"
COLdesc("bag", COLLECTION_NONE, REP_none)
#line 37 "../../prop-src/collection.pcc"
#line 37 "../../prop-src/collection.pcc"
), 
#line 37 "../../prop-src/collection.pcc"
#line 37 "../../prop-src/collection.pcc"
list_1_(a,list_1_(b))
#line 37 "../../prop-src/collection.pcc"
#line 37 "../../prop-src/collection.pcc"
); }

Ty mkmultimapty( Ty a, Ty b)
{  return TYCONty( COLtycon( 
#line 40 "../../prop-src/collection.pcc"
#line 40 "../../prop-src/collection.pcc"
COLdesc("bag", COLLECTION_NONE, REP_none)
#line 40 "../../prop-src/collection.pcc"
#line 40 "../../prop-src/collection.pcc"
), 
#line 40 "../../prop-src/collection.pcc"
#line 40 "../../prop-src/collection.pcc"
list_1_(a,list_1_(b))
#line 40 "../../prop-src/collection.pcc"
#line 40 "../../prop-src/collection.pcc"
); }

Ty mkqueuety( Ty a)
{  return TYCONty( COLtycon( 
#line 43 "../../prop-src/collection.pcc"
#line 43 "../../prop-src/collection.pcc"
COLdesc("bag", COLLECTION_NONE, REP_none)
#line 43 "../../prop-src/collection.pcc"
#line 43 "../../prop-src/collection.pcc"
), 
#line 43 "../../prop-src/collection.pcc"
#line 43 "../../prop-src/collection.pcc"
list_1_(a)
#line 43 "../../prop-src/collection.pcc"
#line 43 "../../prop-src/collection.pcc"
); }

Ty mkpriqueuety( Ty a)
{  return TYCONty( COLtycon( 
#line 46 "../../prop-src/collection.pcc"
#line 46 "../../prop-src/collection.pcc"
COLdesc("bag", COLLECTION_NONE, REP_none)
#line 46 "../../prop-src/collection.pcc"
#line 46 "../../prop-src/collection.pcc"
), 
#line 46 "../../prop-src/collection.pcc"
#line 46 "../../prop-src/collection.pcc"
list_1_(a)
#line 46 "../../prop-src/collection.pcc"
#line 46 "../../prop-src/collection.pcc"
); }

Ty mkdequety( Ty a)
{  return TYCONty( COLtycon( 
#line 49 "../../prop-src/collection.pcc"
#line 49 "../../prop-src/collection.pcc"
COLdesc("bag", COLLECTION_NONE, REP_none)
#line 49 "../../prop-src/collection.pcc"
#line 49 "../../prop-src/collection.pcc"
), 
#line 49 "../../prop-src/collection.pcc"
#line 49 "../../prop-src/collection.pcc"
list_1_(a)
#line 49 "../../prop-src/collection.pcc"
#line 49 "../../prop-src/collection.pcc"
); }
#line 50 "../../prop-src/collection.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
