///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\..\app\setl-pe\setl-ast.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_GARBAGE_COLLECTION_USED
#define PROP_PRINTER_USED
#include <propdefs.h>
#line 1 "../../../app/setl-pe/setl-ast.pcc"
#include "setl-ast.h"

#line 3 "../../../app/setl-pe/setl-ast.pcc"
#line 3 "../../../app/setl-pe/setl-ast.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype LabeledExp
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Decl
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Term
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Ty
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Id>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Exp>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<LabeledExp>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Literal>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Term>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Ty>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
void a_Exp::trace(GC * gc__)
{
}

void Exp_IDexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  // omitted Id
}

void Exp_LITexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->LITexp = (Literal )gc__->trace(this->LITexp); // Literal
}

void Exp_APPexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->_1 = (Exp )gc__->trace(this->_1); // Exp
  this->_2 = (Exp )gc__->trace(this->_2); // Exp
}

void Exp_TUPLEexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->TUPLEexp = (Exps )gc__->trace(this->TUPLEexp); // Exps
}

void Exp_RECORDexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->RECORDexp = (LabeledExps )gc__->trace(this->RECORDexp); // LabeledExps
}

void Exp_SETexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->SETexp = (Exps )gc__->trace(this->SETexp); // Exps
}

void Exp_CASEexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->_1 = (Exp )gc__->trace(this->_1); // Exp
  this->_2 = (Exps )gc__->trace(this->_2); // Exps
}

void Exp_IFexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->_1 = (Exp )gc__->trace(this->_1); // Exp
  this->_2 = (Exp )gc__->trace(this->_2); // Exp
  this->_3 = (Exp )gc__->trace(this->_3); // Exp
}

void Exp_WHILEexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->_1 = (Exp )gc__->trace(this->_1); // Exp
  this->_2 = (Exp )gc__->trace(this->_2); // Exp
}

void Exp_SEQexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->SEQexp = (Exps )gc__->trace(this->SEQexp); // Exps
}

void Exp_LETexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  this->_1 = (Decls )gc__->trace(this->_1); // Decls
  this->_2 = (Exp )gc__->trace(this->_2); // Exp
}

void Exp_PRIMexp::trace(GC * gc__)
{
  // call to method a_Exp::trace() has been optimized out
  // omitted Prim
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype LabeledExp
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
void a_LabeledExp::trace(GC * gc__)
{
  // omitted Id
  this->exp = (Exp )gc__->trace(this->exp); // Exp
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Decl
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
void a_Decl::trace(GC * gc__)
{
}

void Decl_TYPEdecl::trace(GC * gc__)
{
  // call to method a_Decl::trace() has been optimized out
  // omitted Id
  this->_2 = (Ids )gc__->trace(this->_2); // Ids
  this->_3 = (Ty )gc__->trace(this->_3); // Ty
}

void Decl_DATATYPEdecl::trace(GC * gc__)
{
  // call to method a_Decl::trace() has been optimized out
  // omitted Id
  this->_2 = (Ids )gc__->trace(this->_2); // Ids
  this->_3 = (Terms )gc__->trace(this->_3); // Terms
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
void a_Literal::trace(GC * gc__)
{
}

void Literal_INTlit::trace(GC * gc__)
{
  // call to method a_Literal::trace() has been optimized out
  // omitted int
}

void Literal_REALlit::trace(GC * gc__)
{
  // call to method a_Literal::trace() has been optimized out
  // omitted double
}

void Literal_STRINGlit::trace(GC * gc__)
{
  // call to method a_Literal::trace() has been optimized out
  // omitted char const *
}

void Literal_CHARlit::trace(GC * gc__)
{
  // call to method a_Literal::trace() has been optimized out
  // omitted char
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Term
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
void a_Term::trace(GC * gc__)
{
  // omitted Id
  this->_2 = (Ty )gc__->trace(this->_2); // Ty
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Ty
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
void a_Ty::trace(GC * gc__)
{
  this->VARty = (Ty )gc__->trace(this->VARty); // Ty
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Id>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Id>;
template a_List<Id> * list_1_(Ty x_1, a_List<Ty> *  x_2);
template a_List<Id> * list_1_(Ty x_list_1_);
template int boxed(const a_List<Id> *);
template int untag(const a_List<Id> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_List<Id>::trace(GC * gc__)
{
  // omitted Id
  this->_2 = (a_List<Id> *  )gc__->trace(this->_2); // List<Id> 
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Exp>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Exp>;
template a_List<Exp> * list_1_(Id x_1, a_List<Id> *  x_2);
template a_List<Exp> * list_1_(Id x_list_1_);
template int boxed(const a_List<Exp> *);
template int untag(const a_List<Exp> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_List<Exp>::trace(GC * gc__)
{
  this->_1 = (Exp )gc__->trace(this->_1); // Exp
  this->_2 = (a_List<Exp> *  )gc__->trace(this->_2); // List<Exp> 
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<LabeledExp>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<LabeledExp>;
template a_List<LabeledExp> * list_1_(Exp x_1, a_List<Exp> *  x_2);
template a_List<LabeledExp> * list_1_(Exp x_list_1_);
template int boxed(const a_List<LabeledExp> *);
template int untag(const a_List<LabeledExp> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_List<LabeledExp>::trace(GC * gc__)
{
  this->_1 = (LabeledExp )gc__->trace(this->_1); // LabeledExp
  this->_2 = (a_List<LabeledExp> *  )gc__->trace(this->_2); // List<LabeledExp> 
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Decl>;
template a_List<Decl> * list_1_(LabeledExp x_1, a_List<LabeledExp> *  x_2);
template a_List<Decl> * list_1_(LabeledExp x_list_1_);
template int boxed(const a_List<Decl> *);
template int untag(const a_List<Decl> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_List<Decl>::trace(GC * gc__)
{
  this->_1 = (Decl )gc__->trace(this->_1); // Decl
  this->_2 = (a_List<Decl> *  )gc__->trace(this->_2); // List<Decl> 
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Literal>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Literal>;
template a_List<Literal> * list_1_(Decl x_1, a_List<Decl> *  x_2);
template a_List<Literal> * list_1_(Decl x_list_1_);
template int boxed(const a_List<Literal> *);
template int untag(const a_List<Literal> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_List<Literal>::trace(GC * gc__)
{
  this->_1 = (Literal )gc__->trace(this->_1); // Literal
  this->_2 = (a_List<Literal> *  )gc__->trace(this->_2); // List<Literal> 
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Term>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Term>;
template a_List<Term> * list_1_(Literal x_1, a_List<Literal> *  x_2);
template a_List<Term> * list_1_(Literal x_list_1_);
template int boxed(const a_List<Term> *);
template int untag(const a_List<Term> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_List<Term>::trace(GC * gc__)
{
  this->_1 = (Term )gc__->trace(this->_1); // Term
  this->_2 = (a_List<Term> *  )gc__->trace(this->_2); // List<Term> 
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Ty>
//
///////////////////////////////////////////////////////////////////////////////
#line 3 "../../../app/setl-pe/setl-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Ty>;
template a_List<Ty> * list_1_(Term x_1, a_List<Term> *  x_2);
template a_List<Ty> * list_1_(Term x_list_1_);
template int boxed(const a_List<Ty> *);
template int untag(const a_List<Ty> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
void a_List<Ty>::trace(GC * gc__)
{
  this->_1 = (Ty )gc__->trace(this->_1); // Ty
  this->_2 = (a_List<Ty> *  )gc__->trace(this->_2); // List<Ty> 
}



#line 7 "../../../app/setl-pe/setl-ast.pcc"
#line 7 "../../../app/setl-pe/setl-ast.pcc"

#line 8 "../../../app/setl-pe/setl-ast.pcc"
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
