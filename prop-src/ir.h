///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\ir.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/ir.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the definitions for the intermediate data structures
//  used within the Prop -> C++ translator.  Definitions for types, patterns,
//  decision trees, and pretty printing formats are located here.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef intermediate_representations_h
#define intermediate_representations_h

#include "basics.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward datatype declarations
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/ir.ph"
#line 20 "../../prop-src/ir.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Exp
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Exp_defined
#define datatype_Exp_defined
  class a_Exp;
  typedef a_Exp * Exp;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Stmt
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Stmt_defined
#define datatype_Stmt_defined
  class a_Stmt;
  typedef a_Stmt * Stmt;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Decl
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Decl_defined
#define datatype_Decl_defined
  class a_Decl;
  typedef a_Decl * Decl;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for MatchRule
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_MatchRule_defined
#define datatype_MatchRule_defined
  class a_MatchRule;
  typedef a_MatchRule * MatchRule;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for CollectionDesc
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_CollectionDesc_defined
#define datatype_CollectionDesc_defined
  class a_CollectionDesc;
  typedef a_CollectionDesc * CollectionDesc;
#endif

#line 20 "../../prop-src/ir.ph"
#line 20 "../../prop-src/ir.ph"


class GraphTypeDef;
class EdgeDef;
class NodeDef;
class DatatypeHierarchy;
class DatatypeClass;

///////////////////////////////////////////////////////////////////////////////
//
//  Qualifiers determines various implementation characteristics
//  of the type.
//
///////////////////////////////////////////////////////////////////////////////

enum
{
  QUALnone          = 0,      // no qualifiers
  QUALprintable     = 1<<0,   // pretty printable
  QUALtracable      = 1<<1,   // reference countable
  QUALcollectable   = 1<<2,   // garbage collectable
  QUALrewritable    = 1<<3,   // rewritable
  QUALrelation      = 1<<4,   // a relation
  QUALpersistent    = 1<<5,   // persistent type
  QUALclass         = 1<<6,   // class type
  QUALconst         = 1<<7,   // const
  QUALunsigned      = 1<<8,   // unsigned
  QUALsigned        = 1<<9,   // signed
  QUALvirtual       = 1<<10,  // virtual inheritance
  QUALextensible    = 1<<11,  // extensible type
  QUALview          = 1<<12,  // a view
  QUALunifiable     = 1<<13,  // an unifiable term
  QUALtaggedpointer = 1<<14,  // use tagged pointers for representation
  QUALunboxed       = 1<<15,  // use unboxed presentation if possible
  QUALfinalizable   = 1<<16,  // object should be finalized
  QUALapplicative   = 1<<17,  // applicative rewrite
  QUALtreeparser    = 1<<18,  // tree parsing
  QUALparser        = 1<<19,  // parser class
  QUALlexeme        = 1<<20,  // usable as tokens
  QUALbitfield      = 1<<21,  // an opcode or opcode bitfield
  QUALtopdown       = 1<<22,  // use topdown tree matching in rewriting
  QUALvariable      = 1<<23,  // unifiable variable
  QUALgraphtype     = 1<<24,  // a graph type
  QUALgraphnode     = 1<<25,  // a graph node
  QUALgraphedge     = 1<<26,  // a graph edge
  QUALvirtualdestr  = 1<<27,  // virtual destructor
  QUALinline        = 1<<28,  // inline methods
  QUALextern        = 1<<29   // noninline methods
};

///////////////////////////////////////////////////////////////////////////////
//
//  Optimization options
//
///////////////////////////////////////////////////////////////////////////////

enum
{
  OPTnone          = 0,     // no optimization
  OPTtagless       = 1<<0,  // omit the embedded variant tag
  OPTsubclassless  = 1<<1,  // omit the subclass hierarchy
  OPTbaseclassless = 1<<2,  // omit inheritance from base class
  OPTtaggedpointer = 1<<3,  // embedded the variant tag in lower bits
                            // of the pointer.
  OPTunboxed       = 1<<4,  // use unboxed representation if possible
  OPTtaggedvar     = 1<<5   // tagged variables
};

///////////////////////////////////////////////////////////////////////////////
//
//  Scoping
//
///////////////////////////////////////////////////////////////////////////////

#line 94 "../../prop-src/ir.ph"
#line 377 "../../prop-src/ir.ph"
enum Scope {
  PRIVATEscope = 0, PROTECTEDscope = 1, PUBLICscope = 2
};



enum Parameter {
  TYbody = 0, TYformal = 1, TYsimpleformal = 2, 
  TYactual = 3
};



enum Polarity {
  ISpositive = 0, ISnegative = 1, ISneither = 2
};



///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Ty
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Ty_defined
#define datatype_Ty_defined
  class a_Ty;
  typedef a_Ty * Ty;
#endif

#  define v_NOty 0

#  define NOty (Ty)v_NOty

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for TyCon
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_TyCon_defined
#define datatype_TyCon_defined
  class a_TyCon;
  typedef a_TyCon * TyCon;
#endif

#  define v_POINTERtycon 0
#  define v_REFtycon 1
#  define v_TUPLEtycon 2
#  define v_EXTUPLEtycon 3
#  define v_FUNtycon 4
#  define v_TYPEtycon 5

#  define POINTERtycon (TyCon)v_POINTERtycon
#  define REFtycon (TyCon)v_REFtycon
#  define TUPLEtycon (TyCon)v_TUPLEtycon
#  define EXTUPLEtycon (TyCon)v_EXTUPLEtycon
#  define FUNtycon (TyCon)v_FUNtycon
#  define TYPEtycon (TyCon)v_TYPEtycon

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Pat
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Pat_defined
#define datatype_Pat_defined
  class a_Pat;
  typedef a_Pat * Pat;
#endif

#  define v_NOpat 0

#  define NOpat (Pat)v_NOpat

enum LogicalPat {
  NOTpat = 0, ANDpat = 1, ORpat = 2, 
  EQUIVpat = 3, XORpat = 4, IMPLIESpat = 5
};



///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Literal
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Literal_defined
#define datatype_Literal_defined
  class a_Literal;
  typedef a_Literal * Literal;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Cons
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Cons_defined
#define datatype_Cons_defined
  class a_Cons;
  typedef a_Cons * Cons;
#endif

#  define v_NOcons 0

#  define NOcons (Cons)v_NOcons

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for ProductionSymbol
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_ProductionSymbol_defined
#define datatype_ProductionSymbol_defined
  class a_ProductionSymbol;
  typedef a_ProductionSymbol * ProductionSymbol;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Pid
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Pid_defined
#define datatype_Pid_defined
  class a_Pid;
  typedef a_Pid * Pid;
#endif

#  define v_PERSISTnone 0

#  define PERSISTnone (Pid)v_PERSISTnone

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Inherit
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Inherit_defined
#define datatype_Inherit_defined
  class a_Inherit;
  typedef a_Inherit * Inherit;
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type TyQual
///////////////////////////////////////////////////////////////////////////////
#line 364 "../../prop-src/ir.ph"
typedef int TyQual;

///////////////////////////////////////////////////////////////////////////////
// Definition of type TyOpt
///////////////////////////////////////////////////////////////////////////////
#line 365 "../../prop-src/ir.ph"
typedef int TyOpt;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabTy
///////////////////////////////////////////////////////////////////////////////
#line 366 "../../prop-src/ir.ph"
typedef struct { Id label; Ty ty;  } LabTy;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabPat
///////////////////////////////////////////////////////////////////////////////
#line 367 "../../prop-src/ir.ph"
typedef struct { Id label; Pat pat;  } LabPat;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Inherits
///////////////////////////////////////////////////////////////////////////////
#line 368 "../../prop-src/ir.ph"
typedef a_List<Inherit> *  Inherits;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Conses
///////////////////////////////////////////////////////////////////////////////
#line 369 "../../prop-src/ir.ph"
typedef a_List<Cons> *  Conses;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Tys
///////////////////////////////////////////////////////////////////////////////
#line 370 "../../prop-src/ir.ph"
typedef a_List<Ty> *  Tys;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabTys
///////////////////////////////////////////////////////////////////////////////
#line 371 "../../prop-src/ir.ph"
typedef a_List<LabTy> *  LabTys;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Pats
///////////////////////////////////////////////////////////////////////////////
#line 372 "../../prop-src/ir.ph"
typedef a_List<Pat> *  Pats;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabPats
///////////////////////////////////////////////////////////////////////////////
#line 373 "../../prop-src/ir.ph"
typedef a_List<LabPat> *  LabPats;

///////////////////////////////////////////////////////////////////////////////
// Definition of type TyVar
///////////////////////////////////////////////////////////////////////////////
#line 374 "../../prop-src/ir.ph"
typedef Id TyVar;

///////////////////////////////////////////////////////////////////////////////
// Definition of type TyVars
///////////////////////////////////////////////////////////////////////////////
#line 375 "../../prop-src/ir.ph"
typedef a_List<TyVar> *  TyVars;

///////////////////////////////////////////////////////////////////////////////
// Definition of type PrintFormats
///////////////////////////////////////////////////////////////////////////////
#line 376 "../../prop-src/ir.ph"
typedef a_List<ProductionSymbol> *  PrintFormats;




///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Ty
//
///////////////////////////////////////////////////////////////////////////////
class a_Ty : public MEM {
public:
  enum Tag_Ty {
    tag_VARty = 0, tag_INDty = 1, tag_QUALty = 2, 
    tag_TYCONty = 3, tag_POLYty = 4, tag_DEFVALty = 5, 
    tag_NESTEDty = 6
  };

public:
  const Tag_Ty tag__; // variant tag
protected:
  inline a_Ty(Tag_Ty t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Ty * x) { return x != 0; }
inline int untag(const a_Ty * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Ty::VARty
//
///////////////////////////////////////////////////////////////////////////////
class Ty_VARty : public a_Ty {
public:
#line 131 "../../prop-src/ir.ph"
  Ty VARty; 
  inline Ty_VARty (Ty x_VARty)
   : a_Ty(tag_VARty), VARty(x_VARty)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Ty::INDty
//
///////////////////////////////////////////////////////////////////////////////
class Ty_INDty : public a_Ty {
public:
#line 132 "../../prop-src/ir.ph"
  Id _1; int _2; 
  inline Ty_INDty (Id x_1, int x_2)
   : a_Ty(tag_INDty), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Ty::QUALty
//
///////////////////////////////////////////////////////////////////////////////
class Ty_QUALty : public a_Ty {
public:
#line 133 "../../prop-src/ir.ph"
  TyQual _1; Ty _2; 
  inline Ty_QUALty (TyQual x_1, Ty x_2)
   : a_Ty(tag_QUALty), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Ty::TYCONty
//
///////////////////////////////////////////////////////////////////////////////
class Ty_TYCONty : public a_Ty {
public:
#line 134 "../../prop-src/ir.ph"
  TyCon _1; a_List<Ty> *  _2; 
  inline Ty_TYCONty (TyCon x_1, a_List<Ty> *  x_2)
   : a_Ty(tag_TYCONty), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Ty::POLYty
//
///////////////////////////////////////////////////////////////////////////////
class Ty_POLYty : public a_Ty {
public:
#line 135 "../../prop-src/ir.ph"
  Ty _1; int _2; TyVar * _3; 
  inline Ty_POLYty (Ty x_1, int x_2, TyVar * x_3)
   : a_Ty(tag_POLYty), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Ty::DEFVALty
//
///////////////////////////////////////////////////////////////////////////////
class Ty_DEFVALty : public a_Ty {
public:
#line 136 "../../prop-src/ir.ph"
  Ty _1; Exp _2; 
  inline Ty_DEFVALty (Ty x_1, Exp x_2)
   : a_Ty(tag_DEFVALty), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Ty::NESTEDty
//
///////////////////////////////////////////////////////////////////////////////
class Ty_NESTEDty : public a_Ty {
public:
#line 137 "../../prop-src/ir.ph"
  Ty _1; Ty _2; 
  inline Ty_NESTEDty (Ty x_1, Ty x_2)
   : a_Ty(tag_NESTEDty), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Ty
//
///////////////////////////////////////////////////////////////////////////////
inline a_Ty * VARty (Ty x_VARty)
{
  return new Ty_VARty (x_VARty);
}
inline a_Ty * INDty (Id x_1, int x_2)
{
  return new Ty_INDty (x_1, x_2);
}
inline a_Ty * QUALty (TyQual x_1, Ty x_2)
{
  return new Ty_QUALty (x_1, x_2);
}
inline a_Ty * TYCONty (TyCon x_1, a_List<Ty> *  x_2)
{
  return new Ty_TYCONty (x_1, x_2);
}
inline a_Ty * POLYty (Ty x_1, int x_2, TyVar * x_3)
{
  return new Ty_POLYty (x_1, x_2, x_3);
}
inline a_Ty * DEFVALty (Ty x_1, Exp x_2)
{
  return new Ty_DEFVALty (x_1, x_2);
}
inline a_Ty * NESTEDty (Ty x_1, Ty x_2)
{
  return new Ty_NESTEDty (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Ty
//
///////////////////////////////////////////////////////////////////////////////
inline Ty_VARty * _VARty(const a_Ty * _x_) { return (Ty_VARty *)_x_; }
inline Ty_INDty * _INDty(const a_Ty * _x_) { return (Ty_INDty *)_x_; }
inline Ty_QUALty * _QUALty(const a_Ty * _x_) { return (Ty_QUALty *)_x_; }
inline Ty_TYCONty * _TYCONty(const a_Ty * _x_) { return (Ty_TYCONty *)_x_; }
inline Ty_POLYty * _POLYty(const a_Ty * _x_) { return (Ty_POLYty *)_x_; }
inline Ty_DEFVALty * _DEFVALty(const a_Ty * _x_) { return (Ty_DEFVALty *)_x_; }
inline Ty_NESTEDty * _NESTEDty(const a_Ty * _x_) { return (Ty_NESTEDty *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype TyCon
//
///////////////////////////////////////////////////////////////////////////////
class a_TyCon : public MEM {
public:
  enum Tag_TyCon {
    tag_IDtycon = 0, tag_RECORDtycon = 1, tag_ARRAYtycon = 2, 
    tag_BITFIELDtycon = 3, tag_DATATYPEtycon = 4, tag_COLtycon = 5, 
    tag_GRAPHtycon = 6, tag_NODEtycon = 7, tag_EDGEtycon = 8
  };

public:
  const Tag_TyCon tag__; // variant tag
protected:
  inline a_TyCon(Tag_TyCon t__) : tag__(t__) {}
public:
};
inline int boxed(const a_TyCon * x) { return (unsigned long)x >= 6; }
inline int untag(const a_TyCon * x) { return boxed(x) ? x->tag__ + 6 : (int)x; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::IDtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_IDtycon : public a_TyCon {
public:
#line 148 "../../prop-src/ir.ph"
  Id IDtycon; 
  inline TyCon_IDtycon (Id x_IDtycon)
   : a_TyCon(tag_IDtycon), IDtycon(x_IDtycon)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::RECORDtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_RECORDtycon : public a_TyCon {
public:
#line 153 "../../prop-src/ir.ph"
  a_List<Id> *  _1; Bool _2; 
  inline TyCon_RECORDtycon (a_List<Id> *  x_1, Bool x_2)
   : a_TyCon(tag_RECORDtycon), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::ARRAYtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_ARRAYtycon : public a_TyCon {
public:
#line 154 "../../prop-src/ir.ph"
  Exp ARRAYtycon; 
  inline TyCon_ARRAYtycon (Exp x_ARRAYtycon)
   : a_TyCon(tag_ARRAYtycon), ARRAYtycon(x_ARRAYtycon)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::BITFIELDtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_BITFIELDtycon : public a_TyCon {
public:
#line 155 "../../prop-src/ir.ph"
  int width; Bool is_signed; 
  inline TyCon_BITFIELDtycon (int x_width, Bool x_is_signed = false)
   : a_TyCon(tag_BITFIELDtycon), width(x_width), is_signed(x_is_signed)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::DATATYPEtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_DATATYPEtycon : public a_TyCon {
public:
#line 160 "../../prop-src/ir.ph"
  Id id; int unit; int arg; Cons * terms; TyVars tyvars; Ty polyty; a_List<Inherit> *  inherit; TyQual qualifiers; TyOpt opt; a_List<Decl> *  body; Exp view_match; Loc const * location; DatatypeHierarchy * hierarchy; 
  inline TyCon_DATATYPEtycon (Id x_id, int x_unit, int x_arg, Cons * x_terms, TyVars x_tyvars, Ty x_polyty, a_List<Inherit> *  x_inherit, TyQual x_qualifiers, TyOpt x_opt, a_List<Decl> *  x_body, Exp x_view_match, Loc const * x_location, DatatypeHierarchy * x_hierarchy = 0)
   : a_TyCon(tag_DATATYPEtycon), id(x_id), unit(x_unit), arg(x_arg), terms(x_terms), tyvars(x_tyvars), polyty(x_polyty), inherit(x_inherit), qualifiers(x_qualifiers), opt(x_opt), body(x_body), view_match(x_view_match), location(x_location), hierarchy(x_hierarchy)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::COLtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_COLtycon : public a_TyCon {
public:
#line 176 "../../prop-src/ir.ph"
  CollectionDesc COLtycon; 
  inline TyCon_COLtycon (CollectionDesc x_COLtycon)
   : a_TyCon(tag_COLtycon), COLtycon(x_COLtycon)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::GRAPHtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_GRAPHtycon : public a_TyCon {
public:
#line 177 "../../prop-src/ir.ph"
  GraphTypeDef * GRAPHtycon; 
  inline TyCon_GRAPHtycon (GraphTypeDef * x_GRAPHtycon)
   : a_TyCon(tag_GRAPHtycon), GRAPHtycon(x_GRAPHtycon)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::NODEtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_NODEtycon : public a_TyCon {
public:
#line 178 "../../prop-src/ir.ph"
  NodeDef * NODEtycon; 
  inline TyCon_NODEtycon (NodeDef * x_NODEtycon)
   : a_TyCon(tag_NODEtycon), NODEtycon(x_NODEtycon)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyCon::EDGEtycon
//
///////////////////////////////////////////////////////////////////////////////
class TyCon_EDGEtycon : public a_TyCon {
public:
#line 179 "../../prop-src/ir.ph"
  EdgeDef * EDGEtycon; 
  inline TyCon_EDGEtycon (EdgeDef * x_EDGEtycon)
   : a_TyCon(tag_EDGEtycon), EDGEtycon(x_EDGEtycon)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for TyCon
//
///////////////////////////////////////////////////////////////////////////////
inline a_TyCon * IDtycon (Id x_IDtycon)
{
  return new TyCon_IDtycon (x_IDtycon);
}
inline a_TyCon * RECORDtycon (a_List<Id> *  x_1, Bool x_2)
{
  return new TyCon_RECORDtycon (x_1, x_2);
}
inline a_TyCon * ARRAYtycon (Exp x_ARRAYtycon)
{
  return new TyCon_ARRAYtycon (x_ARRAYtycon);
}
inline a_TyCon * BITFIELDtycon (int x_width, Bool x_is_signed = false)
{
  return new TyCon_BITFIELDtycon (x_width, x_is_signed);
}
inline a_TyCon * DATATYPEtycon (Id x_id, int x_unit, int x_arg, Cons * x_terms, TyVars x_tyvars, Ty x_polyty, a_List<Inherit> *  x_inherit, TyQual x_qualifiers, TyOpt x_opt, a_List<Decl> *  x_body, Exp x_view_match, Loc const * x_location, DatatypeHierarchy * x_hierarchy = 0)
{
  return new TyCon_DATATYPEtycon (x_id, x_unit, x_arg, x_terms, x_tyvars, x_polyty, x_inherit, x_qualifiers, x_opt, x_body, x_view_match, x_location, x_hierarchy);
}
inline a_TyCon * COLtycon (CollectionDesc x_COLtycon)
{
  return new TyCon_COLtycon (x_COLtycon);
}
inline a_TyCon * GRAPHtycon (GraphTypeDef * x_GRAPHtycon)
{
  return new TyCon_GRAPHtycon (x_GRAPHtycon);
}
inline a_TyCon * NODEtycon (NodeDef * x_NODEtycon)
{
  return new TyCon_NODEtycon (x_NODEtycon);
}
inline a_TyCon * EDGEtycon (EdgeDef * x_EDGEtycon)
{
  return new TyCon_EDGEtycon (x_EDGEtycon);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for TyCon
//
///////////////////////////////////////////////////////////////////////////////
inline TyCon_IDtycon * _IDtycon(const a_TyCon * _x_) { return (TyCon_IDtycon *)_x_; }
inline TyCon_RECORDtycon * _RECORDtycon(const a_TyCon * _x_) { return (TyCon_RECORDtycon *)_x_; }
inline TyCon_ARRAYtycon * _ARRAYtycon(const a_TyCon * _x_) { return (TyCon_ARRAYtycon *)_x_; }
inline TyCon_BITFIELDtycon * _BITFIELDtycon(const a_TyCon * _x_) { return (TyCon_BITFIELDtycon *)_x_; }
inline TyCon_DATATYPEtycon * _DATATYPEtycon(const a_TyCon * _x_) { return (TyCon_DATATYPEtycon *)_x_; }
inline TyCon_COLtycon * _COLtycon(const a_TyCon * _x_) { return (TyCon_COLtycon *)_x_; }
inline TyCon_GRAPHtycon * _GRAPHtycon(const a_TyCon * _x_) { return (TyCon_GRAPHtycon *)_x_; }
inline TyCon_NODEtycon * _NODEtycon(const a_TyCon * _x_) { return (TyCon_NODEtycon *)_x_; }
inline TyCon_EDGEtycon * _EDGEtycon(const a_TyCon * _x_) { return (TyCon_EDGEtycon *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Pat
//
///////////////////////////////////////////////////////////////////////////////
class a_Pat : public MEM {
public:
  enum Tag_Pat {
    tag_WILDpat = 0, tag_INDpat = 1, tag_POLYpat = 2, 
    tag_IDpat = 3, tag_CONSpat = 4, tag_APPpat = 5, 
    tag_TYPEDpat = 6, tag_ASpat = 7, tag_LITERALpat = 8, 
    tag_CONTEXTpat = 9, tag_LEXEMEpat = 10, tag_ARRAYpat = 11, 
    tag_TUPLEpat = 12, tag_EXTUPLEpat = 13, tag_RECORDpat = 14, 
    tag_LISTpat = 15, tag_VECTORpat = 16, tag_APPENDpat = 17, 
    tag_GUARDpat = 18, tag_LOGICALpat = 19, tag_BACKEDGEpat = 20, 
    tag_UNIFYpat = 21, tag_MARKEDpat = 22
  };

public:
  const Tag_Pat tag__; // variant tag
protected:
  inline a_Pat(Tag_Pat t__) : tag__(t__) {}
public:
#line 226 "../../prop-src/ir.ph"
 Exp selector; Ty ty; 
#line 226 "../../prop-src/ir.ph"
};
inline int boxed(const a_Pat * x) { return x != 0; }
inline int untag(const a_Pat * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::WILDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_WILDpat : public a_Pat {
public:
#line 189 "../../prop-src/ir.ph"
  
  inline Pat_WILDpat ()
   : a_Pat(tag_WILDpat)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::INDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_INDpat : public a_Pat {
public:
#line 190 "../../prop-src/ir.ph"
  Id _1; int _2; Ty _3; 
  inline Pat_INDpat (Id x_1, int x_2, Ty x_3)
   : a_Pat(tag_INDpat), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::POLYpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_POLYpat : public a_Pat {
public:
#line 191 "../../prop-src/ir.ph"
  Id _1; int _2; Ids _3; Pat _4; Exp _5; Bool _6; 
  inline Pat_POLYpat (Id x_1, int x_2, Ids x_3, Pat x_4, Exp x_5, Bool x_6)
   : a_Pat(tag_POLYpat), _1(x_1), _2(x_2), _3(x_3), _4(x_4), _5(x_5), _6(x_6)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::IDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_IDpat : public a_Pat {
public:
#line 192 "../../prop-src/ir.ph"
  Id _1; Ty _2; Exp _3; 
  inline Pat_IDpat (Id x_1, Ty x_2, Exp x_3)
   : a_Pat(tag_IDpat), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::CONSpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_CONSpat : public a_Pat {
public:
#line 193 "../../prop-src/ir.ph"
  Cons CONSpat; 
  inline Pat_CONSpat (Cons x_CONSpat)
   : a_Pat(tag_CONSpat), CONSpat(x_CONSpat)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::APPpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_APPpat : public a_Pat {
public:
#line 194 "../../prop-src/ir.ph"
  Pat _1; Pat _2; 
  inline Pat_APPpat (Pat x_1, Pat x_2)
   : a_Pat(tag_APPpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::TYPEDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_TYPEDpat : public a_Pat {
public:
#line 195 "../../prop-src/ir.ph"
  Pat _1; Ty _2; 
  inline Pat_TYPEDpat (Pat x_1, Ty x_2)
   : a_Pat(tag_TYPEDpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::ASpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_ASpat : public a_Pat {
public:
#line 196 "../../prop-src/ir.ph"
  Id _1; Pat _2; Ty _3; Exp _4; 
  inline Pat_ASpat (Id x_1, Pat x_2, Ty x_3, Exp x_4)
   : a_Pat(tag_ASpat), _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::LITERALpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_LITERALpat : public a_Pat {
public:
#line 197 "../../prop-src/ir.ph"
  Literal LITERALpat; 
  inline Pat_LITERALpat (Literal x_LITERALpat)
   : a_Pat(tag_LITERALpat), LITERALpat(x_LITERALpat)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::CONTEXTpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_CONTEXTpat : public a_Pat {
public:
#line 198 "../../prop-src/ir.ph"
  Conses _1; Pat _2; 
  inline Pat_CONTEXTpat (Conses x_1, Pat x_2)
   : a_Pat(tag_CONTEXTpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::LEXEMEpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_LEXEMEpat : public a_Pat {
public:
#line 199 "../../prop-src/ir.ph"
  Id _1; Ty _2; int _3; Cons * _4; 
  inline Pat_LEXEMEpat (Id x_1, Ty x_2, int x_3, Cons * x_4)
   : a_Pat(tag_LEXEMEpat), _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::ARRAYpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_ARRAYpat : public a_Pat {
public:
#line 200 "../../prop-src/ir.ph"
  a_List<Pat> *  _1; Bool _2; 
  inline Pat_ARRAYpat (a_List<Pat> *  x_1, Bool x_2)
   : a_Pat(tag_ARRAYpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::TUPLEpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_TUPLEpat : public a_Pat {
public:
#line 201 "../../prop-src/ir.ph"
  a_List<Pat> *  TUPLEpat; 
  inline Pat_TUPLEpat (a_List<Pat> *  x_TUPLEpat)
   : a_Pat(tag_TUPLEpat), TUPLEpat(x_TUPLEpat)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::EXTUPLEpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_EXTUPLEpat : public a_Pat {
public:
#line 202 "../../prop-src/ir.ph"
  a_List<Pat> *  EXTUPLEpat; 
  inline Pat_EXTUPLEpat (a_List<Pat> *  x_EXTUPLEpat)
   : a_Pat(tag_EXTUPLEpat), EXTUPLEpat(x_EXTUPLEpat)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::RECORDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_RECORDpat : public a_Pat {
public:
#line 203 "../../prop-src/ir.ph"
  a_List<LabPat> *  _1; Bool _2; 
  inline Pat_RECORDpat (a_List<LabPat> *  x_1, Bool x_2)
   : a_Pat(tag_RECORDpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::LISTpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_LISTpat : public a_Pat {
public:
#line 204 "../../prop-src/ir.ph"
  Cons cons; Cons nil; a_List<Pat> *  head; Pat tail; 
  inline Pat_LISTpat (Cons x_cons, Cons x_nil, a_List<Pat> *  x_head, Pat x_tail)
   : a_Pat(tag_LISTpat), cons(x_cons), nil(x_nil), head(x_head), tail(x_tail)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::VECTORpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_VECTORpat : public a_Pat {
public:
#line 211 "../../prop-src/ir.ph"
  Cons cons; Pat len; Pat array; a_List<Pat> *  elements; Bool head_flex; Bool tail_flex; 
  inline Pat_VECTORpat (Cons x_cons, Pat x_len, Pat x_array, a_List<Pat> *  x_elements, Bool x_head_flex, Bool x_tail_flex)
   : a_Pat(tag_VECTORpat), cons(x_cons), len(x_len), array(x_array), elements(x_elements), head_flex(x_head_flex), tail_flex(x_tail_flex)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::APPENDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_APPENDpat : public a_Pat {
public:
#line 220 "../../prop-src/ir.ph"
  Pat _1; Pat _2; Ty _3; 
  inline Pat_APPENDpat (Pat x_1, Pat x_2, Ty x_3)
   : a_Pat(tag_APPENDpat), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::GUARDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_GUARDpat : public a_Pat {
public:
#line 221 "../../prop-src/ir.ph"
  Pat _1; Exp _2; 
  inline Pat_GUARDpat (Pat x_1, Exp x_2)
   : a_Pat(tag_GUARDpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::LOGICALpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_LOGICALpat : public a_Pat {
public:
#line 222 "../../prop-src/ir.ph"
  LogicalPat _1; Pat _2; Pat _3; 
  inline Pat_LOGICALpat (LogicalPat x_1, Pat x_2, Pat x_3 = NOpat)
   : a_Pat(tag_LOGICALpat), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::BACKEDGEpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_BACKEDGEpat : public a_Pat {
public:
#line 223 "../../prop-src/ir.ph"
  int _1; Id _2; Pat _3; 
  inline Pat_BACKEDGEpat (int x_1, Id x_2, Pat x_3)
   : a_Pat(tag_BACKEDGEpat), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::UNIFYpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_UNIFYpat : public a_Pat {
public:
#line 224 "../../prop-src/ir.ph"
  Pat _1; Exp _2; 
  inline Pat_UNIFYpat (Pat x_1, Exp x_2)
   : a_Pat(tag_UNIFYpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pat::MARKEDpat
//
///////////////////////////////////////////////////////////////////////////////
class Pat_MARKEDpat : public a_Pat {
public:
#line 225 "../../prop-src/ir.ph"
  Loc _1; Pat _2; 
  inline Pat_MARKEDpat (Loc x_1, Pat x_2)
   : a_Pat(tag_MARKEDpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Pat
//
///////////////////////////////////////////////////////////////////////////////
inline a_Pat * WILDpat ()
{
  return new Pat_WILDpat ;
}
inline a_Pat * INDpat (Id x_1, int x_2, Ty x_3)
{
  return new Pat_INDpat (x_1, x_2, x_3);
}
inline a_Pat * POLYpat (Id x_1, int x_2, Ids x_3, Pat x_4, Exp x_5, Bool x_6)
{
  return new Pat_POLYpat (x_1, x_2, x_3, x_4, x_5, x_6);
}
inline a_Pat * IDpat (Id x_1, Ty x_2, Exp x_3)
{
  return new Pat_IDpat (x_1, x_2, x_3);
}
inline a_Pat * CONSpat (Cons x_CONSpat)
{
  return new Pat_CONSpat (x_CONSpat);
}
inline a_Pat * APPpat (Pat x_1, Pat x_2)
{
  return new Pat_APPpat (x_1, x_2);
}
inline a_Pat * TYPEDpat (Pat x_1, Ty x_2)
{
  return new Pat_TYPEDpat (x_1, x_2);
}
inline a_Pat * ASpat (Id x_1, Pat x_2, Ty x_3, Exp x_4)
{
  return new Pat_ASpat (x_1, x_2, x_3, x_4);
}
inline a_Pat * LITERALpat (Literal x_LITERALpat)
{
  return new Pat_LITERALpat (x_LITERALpat);
}
inline a_Pat * CONTEXTpat (Conses x_1, Pat x_2)
{
  return new Pat_CONTEXTpat (x_1, x_2);
}
inline a_Pat * LEXEMEpat (Id x_1, Ty x_2, int x_3, Cons * x_4)
{
  return new Pat_LEXEMEpat (x_1, x_2, x_3, x_4);
}
inline a_Pat * ARRAYpat (a_List<Pat> *  x_1, Bool x_2)
{
  return new Pat_ARRAYpat (x_1, x_2);
}
inline a_Pat * TUPLEpat (a_List<Pat> *  x_TUPLEpat)
{
  return new Pat_TUPLEpat (x_TUPLEpat);
}
inline a_Pat * EXTUPLEpat (a_List<Pat> *  x_EXTUPLEpat)
{
  return new Pat_EXTUPLEpat (x_EXTUPLEpat);
}
inline a_Pat * RECORDpat (a_List<LabPat> *  x_1, Bool x_2)
{
  return new Pat_RECORDpat (x_1, x_2);
}
inline a_Pat * LISTpat (Cons x_cons, Cons x_nil, a_List<Pat> *  x_head, Pat x_tail)
{
  return new Pat_LISTpat (x_cons, x_nil, x_head, x_tail);
}
inline a_Pat * VECTORpat (Cons x_cons, Pat x_len, Pat x_array, a_List<Pat> *  x_elements, Bool x_head_flex, Bool x_tail_flex)
{
  return new Pat_VECTORpat (x_cons, x_len, x_array, x_elements, x_head_flex, x_tail_flex);
}
inline a_Pat * APPENDpat (Pat x_1, Pat x_2, Ty x_3)
{
  return new Pat_APPENDpat (x_1, x_2, x_3);
}
inline a_Pat * GUARDpat (Pat x_1, Exp x_2)
{
  return new Pat_GUARDpat (x_1, x_2);
}
inline a_Pat * LOGICALpat (LogicalPat x_1, Pat x_2, Pat x_3 = NOpat)
{
  return new Pat_LOGICALpat (x_1, x_2, x_3);
}
inline a_Pat * BACKEDGEpat (int x_1, Id x_2, Pat x_3)
{
  return new Pat_BACKEDGEpat (x_1, x_2, x_3);
}
inline a_Pat * UNIFYpat (Pat x_1, Exp x_2)
{
  return new Pat_UNIFYpat (x_1, x_2);
}
inline a_Pat * MARKEDpat (Loc x_1, Pat x_2)
{
  return new Pat_MARKEDpat (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Pat
//
///////////////////////////////////////////////////////////////////////////////
inline Pat_WILDpat * _WILDpat(const a_Pat * _x_) { return (Pat_WILDpat *)_x_; }
inline Pat_INDpat * _INDpat(const a_Pat * _x_) { return (Pat_INDpat *)_x_; }
inline Pat_POLYpat * _POLYpat(const a_Pat * _x_) { return (Pat_POLYpat *)_x_; }
inline Pat_IDpat * _IDpat(const a_Pat * _x_) { return (Pat_IDpat *)_x_; }
inline Pat_CONSpat * _CONSpat(const a_Pat * _x_) { return (Pat_CONSpat *)_x_; }
inline Pat_APPpat * _APPpat(const a_Pat * _x_) { return (Pat_APPpat *)_x_; }
inline Pat_TYPEDpat * _TYPEDpat(const a_Pat * _x_) { return (Pat_TYPEDpat *)_x_; }
inline Pat_ASpat * _ASpat(const a_Pat * _x_) { return (Pat_ASpat *)_x_; }
inline Pat_LITERALpat * _LITERALpat(const a_Pat * _x_) { return (Pat_LITERALpat *)_x_; }
inline Pat_CONTEXTpat * _CONTEXTpat(const a_Pat * _x_) { return (Pat_CONTEXTpat *)_x_; }
inline Pat_LEXEMEpat * _LEXEMEpat(const a_Pat * _x_) { return (Pat_LEXEMEpat *)_x_; }
inline Pat_ARRAYpat * _ARRAYpat(const a_Pat * _x_) { return (Pat_ARRAYpat *)_x_; }
inline Pat_TUPLEpat * _TUPLEpat(const a_Pat * _x_) { return (Pat_TUPLEpat *)_x_; }
inline Pat_EXTUPLEpat * _EXTUPLEpat(const a_Pat * _x_) { return (Pat_EXTUPLEpat *)_x_; }
inline Pat_RECORDpat * _RECORDpat(const a_Pat * _x_) { return (Pat_RECORDpat *)_x_; }
inline Pat_LISTpat * _LISTpat(const a_Pat * _x_) { return (Pat_LISTpat *)_x_; }
inline Pat_VECTORpat * _VECTORpat(const a_Pat * _x_) { return (Pat_VECTORpat *)_x_; }
inline Pat_APPENDpat * _APPENDpat(const a_Pat * _x_) { return (Pat_APPENDpat *)_x_; }
inline Pat_GUARDpat * _GUARDpat(const a_Pat * _x_) { return (Pat_GUARDpat *)_x_; }
inline Pat_LOGICALpat * _LOGICALpat(const a_Pat * _x_) { return (Pat_LOGICALpat *)_x_; }
inline Pat_BACKEDGEpat * _BACKEDGEpat(const a_Pat * _x_) { return (Pat_BACKEDGEpat *)_x_; }
inline Pat_UNIFYpat * _UNIFYpat(const a_Pat * _x_) { return (Pat_UNIFYpat *)_x_; }
inline Pat_MARKEDpat * _MARKEDpat(const a_Pat * _x_) { return (Pat_MARKEDpat *)_x_; }


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
class a_Literal : public MEM {
public:
  enum Tag_Literal {
    tag_INTlit = 0, tag_BOOLlit = 1, tag_CHARlit = 2, 
    tag_REALlit = 3, tag_STRINGlit = 4, tag_REGEXPlit = 5, 
    tag_QUARKlit = 6, tag_BIGINTlit = 7
  };

public:
  const Tag_Literal tag__; // variant tag
protected:
  inline a_Literal(Tag_Literal t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Literal *) { return 1; }
inline int untag(const a_Literal * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::INTlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_INTlit : public a_Literal {
public:
#line 250 "../../prop-src/ir.ph"
  int INTlit; 
  inline Literal_INTlit (int x_INTlit)
   : a_Literal(tag_INTlit), INTlit(x_INTlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::BOOLlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_BOOLlit : public a_Literal {
public:
#line 251 "../../prop-src/ir.ph"
  Bool BOOLlit; 
  inline Literal_BOOLlit (Bool x_BOOLlit)
   : a_Literal(tag_BOOLlit), BOOLlit(x_BOOLlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::CHARlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_CHARlit : public a_Literal {
public:
#line 252 "../../prop-src/ir.ph"
  char CHARlit; 
  inline Literal_CHARlit (char x_CHARlit)
   : a_Literal(tag_CHARlit), CHARlit(x_CHARlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::REALlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_REALlit : public a_Literal {
public:
#line 253 "../../prop-src/ir.ph"
  double REALlit; 
  inline Literal_REALlit (double x_REALlit)
   : a_Literal(tag_REALlit), REALlit(x_REALlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::STRINGlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_STRINGlit : public a_Literal {
public:
#line 254 "../../prop-src/ir.ph"
  char const * STRINGlit; 
  inline Literal_STRINGlit (char const * x_STRINGlit)
   : a_Literal(tag_STRINGlit), STRINGlit(x_STRINGlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::REGEXPlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_REGEXPlit : public a_Literal {
public:
#line 255 "../../prop-src/ir.ph"
  char const * REGEXPlit; 
  inline Literal_REGEXPlit (char const * x_REGEXPlit)
   : a_Literal(tag_REGEXPlit), REGEXPlit(x_REGEXPlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::QUARKlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_QUARKlit : public a_Literal {
public:
#line 256 "../../prop-src/ir.ph"
  char const * QUARKlit; 
  inline Literal_QUARKlit (char const * x_QUARKlit)
   : a_Literal(tag_QUARKlit), QUARKlit(x_QUARKlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::BIGINTlit
//
///////////////////////////////////////////////////////////////////////////////
class Literal_BIGINTlit : public a_Literal {
public:
#line 257 "../../prop-src/ir.ph"
  char const * BIGINTlit; 
  inline Literal_BIGINTlit (char const * x_BIGINTlit)
   : a_Literal(tag_BIGINTlit), BIGINTlit(x_BIGINTlit)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Literal
//
///////////////////////////////////////////////////////////////////////////////
inline a_Literal * INTlit (int x_INTlit)
{
  return new Literal_INTlit (x_INTlit);
}
inline a_Literal * BOOLlit (Bool x_BOOLlit)
{
  return new Literal_BOOLlit (x_BOOLlit);
}
inline a_Literal * CHARlit (char x_CHARlit)
{
  return new Literal_CHARlit (x_CHARlit);
}
inline a_Literal * REALlit (double x_REALlit)
{
  return new Literal_REALlit (x_REALlit);
}
inline a_Literal * STRINGlit (char const * x_STRINGlit)
{
  return new Literal_STRINGlit (x_STRINGlit);
}
inline a_Literal * REGEXPlit (char const * x_REGEXPlit)
{
  return new Literal_REGEXPlit (x_REGEXPlit);
}
inline a_Literal * QUARKlit (char const * x_QUARKlit)
{
  return new Literal_QUARKlit (x_QUARKlit);
}
inline a_Literal * BIGINTlit (char const * x_BIGINTlit)
{
  return new Literal_BIGINTlit (x_BIGINTlit);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Literal
//
///////////////////////////////////////////////////////////////////////////////
inline Literal_INTlit * _INTlit(const a_Literal * _x_) { return (Literal_INTlit *)_x_; }
inline Literal_BOOLlit * _BOOLlit(const a_Literal * _x_) { return (Literal_BOOLlit *)_x_; }
inline Literal_CHARlit * _CHARlit(const a_Literal * _x_) { return (Literal_CHARlit *)_x_; }
inline Literal_REALlit * _REALlit(const a_Literal * _x_) { return (Literal_REALlit *)_x_; }
inline Literal_STRINGlit * _STRINGlit(const a_Literal * _x_) { return (Literal_STRINGlit *)_x_; }
inline Literal_REGEXPlit * _REGEXPlit(const a_Literal * _x_) { return (Literal_REGEXPlit *)_x_; }
inline Literal_QUARKlit * _QUARKlit(const a_Literal * _x_) { return (Literal_QUARKlit *)_x_; }
inline Literal_BIGINTlit * _BIGINTlit(const a_Literal * _x_) { return (Literal_BIGINTlit *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Cons::ONEcons
//
///////////////////////////////////////////////////////////////////////////////
class a_Cons : public MEM {
public:
#line 267 "../../prop-src/ir.ph"
  Id name; Ty alg_ty; Ty cons_ty; Ty ty; int tag; PrintFormats print_formats; Loc const * location; a_List<Inherit> *  inherit; a_List<Decl> *  body; TyOpt opt; TyQual qual; Exp view_predicate; Exp * view_selectors; Pat lexeme_pattern; DatatypeClass * class_def; 
  inline a_Cons (Id x_name, Ty x_alg_ty, Ty x_cons_ty, Ty x_ty, int x_tag, PrintFormats x_print_formats, Loc const * x_location, a_List<Inherit> *  x_inherit, a_List<Decl> *  x_body, TyOpt x_opt, TyQual x_qual, Exp x_view_predicate, Exp * x_view_selectors, Pat x_lexeme_pattern, DatatypeClass * x_class_def = 0)
   : name(x_name), alg_ty(x_alg_ty), cons_ty(x_cons_ty), ty(x_ty), tag(x_tag), print_formats(x_print_formats), location(x_location), inherit(x_inherit), body(x_body), opt(x_opt), qual(x_qual), view_predicate(x_view_predicate), view_selectors(x_view_selectors), lexeme_pattern(x_lexeme_pattern), class_def(x_class_def)
  {
  }
};
inline int boxed(const a_Cons * x) { return x != 0; }
inline int untag(const a_Cons * x) { return x ? 1 : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Cons
//
///////////////////////////////////////////////////////////////////////////////
inline a_Cons * ONEcons (Id x_name, Ty x_alg_ty, Ty x_cons_ty, Ty x_ty, int x_tag, PrintFormats x_print_formats, Loc const * x_location, a_List<Inherit> *  x_inherit, a_List<Decl> *  x_body, TyOpt x_opt, TyQual x_qual, Exp x_view_predicate, Exp * x_view_selectors, Pat x_lexeme_pattern, DatatypeClass * x_class_def = 0)
{
  return new a_Cons (x_name, x_alg_ty, x_cons_ty, x_ty, x_tag, x_print_formats, x_location, x_inherit, x_body, x_opt, x_qual, x_view_predicate, x_view_selectors, x_lexeme_pattern, x_class_def);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Cons
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype ProductionSymbol
//
///////////////////////////////////////////////////////////////////////////////
class a_ProductionSymbol : public Loc {
public:
  enum Tag_ProductionSymbol {
    tag_TERMsym = 0, tag_TERMSTRINGsym = 1, tag_TERMREGEXPsym = 2, 
    tag_TOKENsym = 3, tag_NONTERMsym = 4, tag_POSNONTERMsym = 5, 
    tag_ACTIONsym = 6, tag_PREDICATEsym = 7, tag_PRECsym = 8, 
    tag_ERRORsym = 9, tag_SPECIALsym = 10
  };

public:
  const Tag_ProductionSymbol tag__; // variant tag
protected:
  inline a_ProductionSymbol(Tag_ProductionSymbol t__) : tag__(t__) {}
public:
};
inline int boxed(const a_ProductionSymbol *) { return 1; }
inline int untag(const a_ProductionSymbol * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::TERMsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_TERMsym : public a_ProductionSymbol {
public:
#line 293 "../../prop-src/ir.ph"
  char TERMsym; 
  inline ProductionSymbol_TERMsym (char x_TERMsym)
   : a_ProductionSymbol(tag_TERMsym), TERMsym(x_TERMsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::TERMSTRINGsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_TERMSTRINGsym : public a_ProductionSymbol {
public:
#line 294 "../../prop-src/ir.ph"
  char const * TERMSTRINGsym; 
  inline ProductionSymbol_TERMSTRINGsym (char const * x_TERMSTRINGsym)
   : a_ProductionSymbol(tag_TERMSTRINGsym), TERMSTRINGsym(x_TERMSTRINGsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::TERMREGEXPsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_TERMREGEXPsym : public a_ProductionSymbol {
public:
#line 295 "../../prop-src/ir.ph"
  char const * TERMREGEXPsym; 
  inline ProductionSymbol_TERMREGEXPsym (char const * x_TERMREGEXPsym)
   : a_ProductionSymbol(tag_TERMREGEXPsym), TERMREGEXPsym(x_TERMREGEXPsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::TOKENsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_TOKENsym : public a_ProductionSymbol {
public:
#line 296 "../../prop-src/ir.ph"
  Cons TOKENsym; 
  inline ProductionSymbol_TOKENsym (Cons x_TOKENsym)
   : a_ProductionSymbol(tag_TOKENsym), TOKENsym(x_TOKENsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::NONTERMsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_NONTERMsym : public a_ProductionSymbol {
public:
#line 297 "../../prop-src/ir.ph"
  Id NONTERMsym; 
  inline ProductionSymbol_NONTERMsym (Id x_NONTERMsym)
   : a_ProductionSymbol(tag_NONTERMsym), NONTERMsym(x_NONTERMsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::POSNONTERMsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_POSNONTERMsym : public a_ProductionSymbol {
public:
#line 298 "../../prop-src/ir.ph"
  int POSNONTERMsym; 
  inline ProductionSymbol_POSNONTERMsym (int x_POSNONTERMsym)
   : a_ProductionSymbol(tag_POSNONTERMsym), POSNONTERMsym(x_POSNONTERMsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::ACTIONsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_ACTIONsym : public a_ProductionSymbol {
public:
#line 299 "../../prop-src/ir.ph"
  a_List<Decl> *  ACTIONsym; 
  inline ProductionSymbol_ACTIONsym (a_List<Decl> *  x_ACTIONsym)
   : a_ProductionSymbol(tag_ACTIONsym), ACTIONsym(x_ACTIONsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::PREDICATEsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_PREDICATEsym : public a_ProductionSymbol {
public:
#line 300 "../../prop-src/ir.ph"
  Exp PREDICATEsym; 
  inline ProductionSymbol_PREDICATEsym (Exp x_PREDICATEsym)
   : a_ProductionSymbol(tag_PREDICATEsym), PREDICATEsym(x_PREDICATEsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::PRECsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_PRECsym : public a_ProductionSymbol {
public:
#line 301 "../../prop-src/ir.ph"
  Cons PRECsym; 
  inline ProductionSymbol_PRECsym (Cons x_PRECsym)
   : a_ProductionSymbol(tag_PRECsym), PRECsym(x_PRECsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::ERRORsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_ERRORsym : public a_ProductionSymbol {
public:
#line 302 "../../prop-src/ir.ph"
  
  inline ProductionSymbol_ERRORsym ()
   : a_ProductionSymbol(tag_ERRORsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ProductionSymbol::SPECIALsym
//
///////////////////////////////////////////////////////////////////////////////
class ProductionSymbol_SPECIALsym : public a_ProductionSymbol {
public:
#line 303 "../../prop-src/ir.ph"
  char SPECIALsym; 
  inline ProductionSymbol_SPECIALsym (char x_SPECIALsym)
   : a_ProductionSymbol(tag_SPECIALsym), SPECIALsym(x_SPECIALsym)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for ProductionSymbol
//
///////////////////////////////////////////////////////////////////////////////
inline a_ProductionSymbol * TERMsym (char x_TERMsym)
{
  return new ProductionSymbol_TERMsym (x_TERMsym);
}
inline a_ProductionSymbol * TERMSTRINGsym (char const * x_TERMSTRINGsym)
{
  return new ProductionSymbol_TERMSTRINGsym (x_TERMSTRINGsym);
}
inline a_ProductionSymbol * TERMREGEXPsym (char const * x_TERMREGEXPsym)
{
  return new ProductionSymbol_TERMREGEXPsym (x_TERMREGEXPsym);
}
inline a_ProductionSymbol * TOKENsym (Cons x_TOKENsym)
{
  return new ProductionSymbol_TOKENsym (x_TOKENsym);
}
inline a_ProductionSymbol * NONTERMsym (Id x_NONTERMsym)
{
  return new ProductionSymbol_NONTERMsym (x_NONTERMsym);
}
inline a_ProductionSymbol * POSNONTERMsym (int x_POSNONTERMsym)
{
  return new ProductionSymbol_POSNONTERMsym (x_POSNONTERMsym);
}
inline a_ProductionSymbol * ACTIONsym (a_List<Decl> *  x_ACTIONsym)
{
  return new ProductionSymbol_ACTIONsym (x_ACTIONsym);
}
inline a_ProductionSymbol * PREDICATEsym (Exp x_PREDICATEsym)
{
  return new ProductionSymbol_PREDICATEsym (x_PREDICATEsym);
}
inline a_ProductionSymbol * PRECsym (Cons x_PRECsym)
{
  return new ProductionSymbol_PRECsym (x_PRECsym);
}
inline a_ProductionSymbol * ERRORsym ()
{
  return new ProductionSymbol_ERRORsym ;
}
inline a_ProductionSymbol * SPECIALsym (char x_SPECIALsym)
{
  return new ProductionSymbol_SPECIALsym (x_SPECIALsym);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for ProductionSymbol
//
///////////////////////////////////////////////////////////////////////////////
inline ProductionSymbol_TERMsym * _TERMsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_TERMsym *)_x_; }
inline ProductionSymbol_TERMSTRINGsym * _TERMSTRINGsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_TERMSTRINGsym *)_x_; }
inline ProductionSymbol_TERMREGEXPsym * _TERMREGEXPsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_TERMREGEXPsym *)_x_; }
inline ProductionSymbol_TOKENsym * _TOKENsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_TOKENsym *)_x_; }
inline ProductionSymbol_NONTERMsym * _NONTERMsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_NONTERMsym *)_x_; }
inline ProductionSymbol_POSNONTERMsym * _POSNONTERMsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_POSNONTERMsym *)_x_; }
inline ProductionSymbol_ACTIONsym * _ACTIONsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_ACTIONsym *)_x_; }
inline ProductionSymbol_PREDICATEsym * _PREDICATEsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_PREDICATEsym *)_x_; }
inline ProductionSymbol_PRECsym * _PRECsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_PRECsym *)_x_; }
inline ProductionSymbol_ERRORsym * _ERRORsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_ERRORsym *)_x_; }
inline ProductionSymbol_SPECIALsym * _SPECIALsym(const a_ProductionSymbol * _x_) { return (ProductionSymbol_SPECIALsym *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pid::PERSISTid
//
///////////////////////////////////////////////////////////////////////////////
class a_Pid : public MEM {
public:
#line 311 "../../prop-src/ir.ph"
  char const * PERSISTid; 
  inline a_Pid (char const * x_PERSISTid)
   : PERSISTid(x_PERSISTid)
  {
  }
};
inline int boxed(const a_Pid * x) { return x != 0; }
inline int untag(const a_Pid * x) { return x ? 1 : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Pid
//
///////////////////////////////////////////////////////////////////////////////
inline a_Pid * PERSISTid (char const * x_PERSISTid)
{
  return new a_Pid (x_PERSISTid);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Pid
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Inherit::INHERIT
//
///////////////////////////////////////////////////////////////////////////////
class a_Inherit : public Loc {
public:
#line 320 "../../prop-src/ir.ph"
  Ty super_class; Scope scope; TyQual qualifiers; 
  inline a_Inherit (Ty x_super_class, Scope x_scope = PUBLICscope, TyQual x_qualifiers = QUALnone)
   : super_class(x_super_class), scope(x_scope), qualifiers(x_qualifiers)
  {
  }
};
inline int boxed(const a_Inherit *) { return 1; }
inline int untag(const a_Inherit *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Inherit
//
///////////////////////////////////////////////////////////////////////////////
inline a_Inherit * INHERIT (Ty x_super_class, Scope x_scope = PUBLICscope, TyQual x_qualifiers = QUALnone)
{
  return new a_Inherit (x_super_class, x_scope, x_qualifiers);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Inherit
//
///////////////////////////////////////////////////////////////////////////////


#line 377 "../../prop-src/ir.ph"
#line 377 "../../prop-src/ir.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, Ids);
extern std::ostream& operator << (std::ostream&, Scope);
extern std::ostream& operator << (std::ostream&, Ty);
extern std::ostream& operator << (std::ostream&, 
#line 388 "../../prop-src/ir.ph"
a_List<Ty> *  
#line 388 "../../prop-src/ir.ph"
);
extern std::ostream& operator << (std::ostream&, Pat);
extern std::ostream& operator << (std::ostream&, LabPat);
extern std::ostream& operator << (std::ostream&, a_List<Pat> *  
#line 391 "../../prop-src/ir.ph"
);
extern std::ostream& operator << (std::ostream&, a_List<LabPat> *  
#line 392 "../../prop-src/ir.ph"
);
extern std::ostream& operator << (std::ostream&, Literal);
extern std::ostream& operator << (std::ostream&, Inherit);
extern std::ostream& operator << (std::ostream&, a_List<Inherit> *  
#line 395 "../../prop-src/ir.ph"
);
extern std::ostream& operator << (std::ostream&, Pid);

extern std::ostream& print_cons (std::ostream&, Cons);
extern void     print_parameter (std::ostream&, Ty, Id, Parameter);
extern void     print_tyvars    (std::ostream&, TyVars, char, char, Bool);
extern Id       index_of (int, Id = 0);

#endif
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
