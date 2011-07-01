///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.2.9),
//  last updated on Jan 21, 1997.
//  The original source file is "setl-ast.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_GARBAGE_COLLECTION_USED
#define PROP_PRINTER_USED
#include <propdefs.h>
#line 1 "setl-ast.pcc"
#include "setl-ast.h"

#line 3 "setl-ast.pcc"
#line 3 "setl-ast.pcc"
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of Exp
///////////////////////////////////////////////////////////////////////////////
void a_Exp::trace(GC * _gc_)
{
}

a_Exp::~a_Exp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::IDexp Id
///////////////////////////////////////////////////////////////////////////////
void Exp_IDexp::trace(GC * _gc_)
{
   // Id
}

inline Exp_IDexp::Exp_IDexp (Id _xIDexp)
   : a_Exp(a_Exp::tag_IDexp), IDexp(_xIDexp) {}
a_Exp * IDexp (Id _xIDexp)
   { return new Exp_IDexp (_xIDexp); }
Exp_IDexp::~Exp_IDexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::LITexp Literal
///////////////////////////////////////////////////////////////////////////////
void Exp_LITexp::trace(GC * _gc_)
{
   LITexp = (Literal )_gc_->trace(LITexp); // Literal
}

inline Exp_LITexp::Exp_LITexp (Literal _xLITexp)
   : a_Exp(a_Exp::tag_LITexp), LITexp(_xLITexp) {}
a_Exp * LITexp (Literal _xLITexp)
   { return new Exp_LITexp (_xLITexp); }
Exp_LITexp::~Exp_LITexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::APPexp (Exp, Exp)
///////////////////////////////////////////////////////////////////////////////
void Exp_APPexp::trace(GC * _gc_)
{
   _1 = (Exp )_gc_->trace(_1); // Exp
   _2 = (Exp )_gc_->trace(_2); // Exp
}

inline Exp_APPexp::Exp_APPexp (Exp _x1, Exp _x2)
   : a_Exp(a_Exp::tag_APPexp), _1(_x1), _2(_x2) {}
a_Exp * APPexp (Exp _x1, Exp _x2)
   { return new Exp_APPexp (_x1, _x2); }
Exp_APPexp::~Exp_APPexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::TUPLEexp Exps
///////////////////////////////////////////////////////////////////////////////
void Exp_TUPLEexp::trace(GC * _gc_)
{
   TUPLEexp = (List(Exp) )_gc_->trace(TUPLEexp); // Exps
}

inline Exp_TUPLEexp::Exp_TUPLEexp (Exps _xTUPLEexp)
   : a_Exp(a_Exp::tag_TUPLEexp), TUPLEexp(_xTUPLEexp) {}
a_Exp * TUPLEexp (Exps _xTUPLEexp)
   { return new Exp_TUPLEexp (_xTUPLEexp); }
Exp_TUPLEexp::~Exp_TUPLEexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::RECORDexp LabeledExps
///////////////////////////////////////////////////////////////////////////////
void Exp_RECORDexp::trace(GC * _gc_)
{
   RECORDexp = (List(LabeledExp) )_gc_->trace(RECORDexp); // LabeledExps
}

inline Exp_RECORDexp::Exp_RECORDexp (LabeledExps _xRECORDexp)
   : a_Exp(a_Exp::tag_RECORDexp), RECORDexp(_xRECORDexp) {}
a_Exp * RECORDexp (LabeledExps _xRECORDexp)
   { return new Exp_RECORDexp (_xRECORDexp); }
Exp_RECORDexp::~Exp_RECORDexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::SETexp Exps
///////////////////////////////////////////////////////////////////////////////
void Exp_SETexp::trace(GC * _gc_)
{
   SETexp = (List(Exp) )_gc_->trace(SETexp); // Exps
}

inline Exp_SETexp::Exp_SETexp (Exps _xSETexp)
   : a_Exp(a_Exp::tag_SETexp), SETexp(_xSETexp) {}
a_Exp * SETexp (Exps _xSETexp)
   { return new Exp_SETexp (_xSETexp); }
Exp_SETexp::~Exp_SETexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::CASEexp (Exp, Exps)
///////////////////////////////////////////////////////////////////////////////
void Exp_CASEexp::trace(GC * _gc_)
{
   _1 = (Exp )_gc_->trace(_1); // Exp
   _2 = (List(Exp) )_gc_->trace(_2); // Exps
}

inline Exp_CASEexp::Exp_CASEexp (Exp _x1, Exps _x2)
   : a_Exp(a_Exp::tag_CASEexp), _1(_x1), _2(_x2) {}
a_Exp * CASEexp (Exp _x1, Exps _x2)
   { return new Exp_CASEexp (_x1, _x2); }
Exp_CASEexp::~Exp_CASEexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::IFexp (Exp, Exp, Exp)
///////////////////////////////////////////////////////////////////////////////
void Exp_IFexp::trace(GC * _gc_)
{
   _1 = (Exp )_gc_->trace(_1); // Exp
   _2 = (Exp )_gc_->trace(_2); // Exp
   _3 = (Exp )_gc_->trace(_3); // Exp
}

inline Exp_IFexp::Exp_IFexp (Exp _x1, Exp _x2, Exp _x3)
   : a_Exp(a_Exp::tag_IFexp), _1(_x1), _2(_x2), _3(_x3) {}
a_Exp * IFexp (Exp _x1, Exp _x2, Exp _x3)
   { return new Exp_IFexp (_x1, _x2, _x3); }
Exp_IFexp::~Exp_IFexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::WHILEexp (Exp, Exp)
///////////////////////////////////////////////////////////////////////////////
void Exp_WHILEexp::trace(GC * _gc_)
{
   _1 = (Exp )_gc_->trace(_1); // Exp
   _2 = (Exp )_gc_->trace(_2); // Exp
}

inline Exp_WHILEexp::Exp_WHILEexp (Exp _x1, Exp _x2)
   : a_Exp(a_Exp::tag_WHILEexp), _1(_x1), _2(_x2) {}
a_Exp * WHILEexp (Exp _x1, Exp _x2)
   { return new Exp_WHILEexp (_x1, _x2); }
Exp_WHILEexp::~Exp_WHILEexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::SEQexp Exps
///////////////////////////////////////////////////////////////////////////////
void Exp_SEQexp::trace(GC * _gc_)
{
   SEQexp = (List(Exp) )_gc_->trace(SEQexp); // Exps
}

inline Exp_SEQexp::Exp_SEQexp (Exps _xSEQexp)
   : a_Exp(a_Exp::tag_SEQexp), SEQexp(_xSEQexp) {}
a_Exp * SEQexp (Exps _xSEQexp)
   { return new Exp_SEQexp (_xSEQexp); }
Exp_SEQexp::~Exp_SEQexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::LETexp (Decls, Exp)
///////////////////////////////////////////////////////////////////////////////
void Exp_LETexp::trace(GC * _gc_)
{
   _1 = (List(Decl) )_gc_->trace(_1); // Decls
   _2 = (Exp )_gc_->trace(_2); // Exp
}

inline Exp_LETexp::Exp_LETexp (Decls _x1, Exp _x2)
   : a_Exp(a_Exp::tag_LETexp), _1(_x1), _2(_x2) {}
a_Exp * LETexp (Decls _x1, Exp _x2)
   { return new Exp_LETexp (_x1, _x2); }
Exp_LETexp::~Exp_LETexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Exp::PRIMexp Prim
///////////////////////////////////////////////////////////////////////////////
void Exp_PRIMexp::trace(GC * _gc_)
{
   // Prim
}

inline Exp_PRIMexp::Exp_PRIMexp (Prim _xPRIMexp)
   : a_Exp(a_Exp::tag_PRIMexp), PRIMexp(_xPRIMexp) {}
a_Exp * PRIMexp (Prim _xPRIMexp)
   { return new Exp_PRIMexp (_xPRIMexp); }
Exp_PRIMexp::~Exp_PRIMexp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of LabeledExp
///////////////////////////////////////////////////////////////////////////////
void a_LabeledExp::trace(GC * _gc_)
{
   // Id
   exp = (Exp )_gc_->trace(exp); // Exp
}

inline a_LabeledExp::a_LabeledExp (Id _xid, Exp _xexp)
   : id(_xid), exp(_xexp) {}
a_LabeledExp * LABELEDexp (Id _xid, Exp _xexp)
   { return new a_LabeledExp (_xid, _xexp); }
a_LabeledExp::~a_LabeledExp() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of Decl
///////////////////////////////////////////////////////////////////////////////
void a_Decl::trace(GC * _gc_)
{
}

a_Decl::~a_Decl() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Decl::TYPEdecl (Id, Ids, Ty)
///////////////////////////////////////////////////////////////////////////////
void Decl_TYPEdecl::trace(GC * _gc_)
{
   // Id
   _2 = (List(Id) )_gc_->trace(_2); // Ids
   _3 = (Ty )_gc_->trace(_3); // Ty
}

inline Decl_TYPEdecl::Decl_TYPEdecl (Id _x1, Ids _x2, Ty _x3)
   : a_Decl(a_Decl::tag_TYPEdecl), _1(_x1), _2(_x2), _3(_x3) {}
a_Decl * TYPEdecl (Id _x1, Ids _x2, Ty _x3)
   { return new Decl_TYPEdecl (_x1, _x2, _x3); }
Decl_TYPEdecl::~Decl_TYPEdecl() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Decl::DATATYPEdecl (Id, Ids, Terms)
///////////////////////////////////////////////////////////////////////////////
void Decl_DATATYPEdecl::trace(GC * _gc_)
{
   // Id
   _2 = (List(Id) )_gc_->trace(_2); // Ids
   _3 = (List(Term) )_gc_->trace(_3); // Terms
}

inline Decl_DATATYPEdecl::Decl_DATATYPEdecl (Id _x1, Ids _x2, Terms _x3)
   : a_Decl(a_Decl::tag_DATATYPEdecl), _1(_x1), _2(_x2), _3(_x3) {}
a_Decl * DATATYPEdecl (Id _x1, Ids _x2, Terms _x3)
   { return new Decl_DATATYPEdecl (_x1, _x2, _x3); }
Decl_DATATYPEdecl::~Decl_DATATYPEdecl() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of Literal
///////////////////////////////////////////////////////////////////////////////
void a_Literal::trace(GC * _gc_)
{
}

a_Literal::~a_Literal() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Literal::INTlit int
///////////////////////////////////////////////////////////////////////////////
void Literal_INTlit::trace(GC * _gc_)
{
   // int
}

inline Literal_INTlit::Literal_INTlit (int _xINTlit)
   : a_Literal(a_Literal::tag_INTlit), INTlit(_xINTlit) {}
a_Literal * INTlit (int _xINTlit)
   { return new Literal_INTlit (_xINTlit); }
Literal_INTlit::~Literal_INTlit() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Literal::REALlit double
///////////////////////////////////////////////////////////////////////////////
void Literal_REALlit::trace(GC * _gc_)
{
   // double
}

inline Literal_REALlit::Literal_REALlit (double _xREALlit)
   : a_Literal(a_Literal::tag_REALlit), REALlit(_xREALlit) {}
a_Literal * REALlit (double _xREALlit)
   { return new Literal_REALlit (_xREALlit); }
Literal_REALlit::~Literal_REALlit() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Literal::STRINGlit char const *
///////////////////////////////////////////////////////////////////////////////
void Literal_STRINGlit::trace(GC * _gc_)
{
   // char const *
}

inline Literal_STRINGlit::Literal_STRINGlit (char const * _xSTRINGlit)
   : a_Literal(a_Literal::tag_STRINGlit), STRINGlit(_xSTRINGlit) {}
a_Literal * STRINGlit (char const * _xSTRINGlit)
   { return new Literal_STRINGlit (_xSTRINGlit); }
Literal_STRINGlit::~Literal_STRINGlit() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for Literal::CHARlit char
///////////////////////////////////////////////////////////////////////////////
void Literal_CHARlit::trace(GC * _gc_)
{
   // char
}

inline Literal_CHARlit::Literal_CHARlit (char _xCHARlit)
   : a_Literal(a_Literal::tag_CHARlit), CHARlit(_xCHARlit) {}
a_Literal * CHARlit (char _xCHARlit)
   { return new Literal_CHARlit (_xCHARlit); }
Literal_CHARlit::~Literal_CHARlit() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of Term
///////////////////////////////////////////////////////////////////////////////
void a_Term::trace(GC * _gc_)
{
   // Id
   _2 = (Ty )_gc_->trace(_2); // Ty
}

inline a_Term::a_Term (Id _x1, Ty _x2)
   : _1(_x1), _2(_x2) {}
a_Term * TERM (Id _x1, Ty _x2)
   { return new a_Term (_x1, _x2); }
a_Term::~a_Term() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of Ty
///////////////////////////////////////////////////////////////////////////////
void a_Ty::trace(GC * _gc_)
{
   VARty = (Ty )_gc_->trace(VARty); // Ty
}

inline a_Ty::a_Ty (Ty _xVARty)
   : VARty(_xVARty) {}
a_Ty * VARty (Ty _xVARty)
   { return new a_Ty (_xVARty); }
a_Ty::~a_Ty() {}
///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of List<Id>
///////////////////////////////////////////////////////////////////////////////
void a_List<Id>::trace(GC * _gc_)
{
   // Id
   _2 = (List(Id) )_gc_->trace(_2); // List<Id> 
}

///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of List<Exp>
///////////////////////////////////////////////////////////////////////////////
void a_List<Exp>::trace(GC * _gc_)
{
   _1 = (Exp )_gc_->trace(_1); // Exp
   _2 = (List(Exp) )_gc_->trace(_2); // List<Exp> 
}

///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of List<LabeledExp>
///////////////////////////////////////////////////////////////////////////////
void a_List<LabeledExp>::trace(GC * _gc_)
{
   _1 = (LabeledExp )_gc_->trace(_1); // LabeledExp
   _2 = (List(LabeledExp) )_gc_->trace(_2); // List<LabeledExp> 
}

///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of List<Decl>
///////////////////////////////////////////////////////////////////////////////
void a_List<Decl>::trace(GC * _gc_)
{
   _1 = (Decl )_gc_->trace(_1); // Decl
   _2 = (List(Decl) )_gc_->trace(_2); // List<Decl> 
}

///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of List<Literal>
///////////////////////////////////////////////////////////////////////////////
void a_List<Literal>::trace(GC * _gc_)
{
   _1 = (Literal )_gc_->trace(_1); // Literal
   _2 = (List(Literal) )_gc_->trace(_2); // List<Literal> 
}

///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of List<Term>
///////////////////////////////////////////////////////////////////////////////
void a_List<Term>::trace(GC * _gc_)
{
   _1 = (Term )_gc_->trace(_1); // Term
   _2 = (List(Term) )_gc_->trace(_2); // List<Term> 
}

///////////////////////////////////////////////////////////////////////////////
// GC tracing method for base class of List<Ty>
///////////////////////////////////////////////////////////////////////////////
void a_List<Ty>::trace(GC * _gc_)
{
   _1 = (Ty )_gc_->trace(_1); // Ty
   _2 = (List(Ty) )_gc_->trace(_2); // List<Ty> 
}

#line 7 "setl-ast.pcc"
#line 7 "setl-ast.pcc"

#line 8 "setl-ast.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = enabled
Fast string matching         = enabled
Inline downcasts             = enabled
--------------------------------------------------------------------------
*/
