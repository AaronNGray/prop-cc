///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\ast.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/ast.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the abstract syntax tree definitions for the
//  Prop language.  For simplicity, C++ statements are currently not
//  handled directly in the AST.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef abstract_syntax_tree_h
#define abstract_syntax_tree_h

#include "basics.h"
#include "ir.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Options to the pattern matching compiler.
//
///////////////////////////////////////////////////////////////////////////////

enum {
  MATCHnone            = 0,     // no option (select first matching rule)
  MATCHall             = 1<<0,  // select all matching rules
  MATCHwhile           = 1<<1,  // loop back
  MATCHnocheck         = 1<<2,  // no checking
  MATCHwithcost        = 1<<3,  // with cost minimization
  MATCHwithintcost     = 1<<4,  // with integer costs
  MATCHwithexpcost     = 1<<5,  // with expression costs
  MATCHwithtreecost    = 1<<6,  // use cumulative cost
  MATCHrefutable       = 1<<7,  // pattern is refutable
  MATCHscanner         = 1<<8,  // lexical scanner
  MATCHcaseinsensitive = 1<<9,  // insensitive case during string matching
  MATCHlexemepat       = 1<<10, // with lexeme pattern
  MATCHnotrace         = 1<<11, // no tracing
  MATCHunification     = 1<<12  // unification mode
};

///////////////////////////////////////////////////////////////////////////////
//
//  Forward type declarations.
//  These are defined in other places.
//
///////////////////////////////////////////////////////////////////////////////

#line 45 "../../prop-src/ast.ph"
#line 57 "../../prop-src/ast.ph"
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
// Forward class definition for GramExp
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_GramExp_defined
#define datatype_GramExp_defined
  class a_GramExp;
  typedef a_GramExp * GramExp;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for FieldDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_FieldDef_defined
#define datatype_FieldDef_defined
  class a_FieldDef;
  typedef a_FieldDef * FieldDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for FieldLaw
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_FieldLaw_defined
#define datatype_FieldLaw_defined
  class a_FieldLaw;
  typedef a_FieldLaw * FieldLaw;
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
// Forward class definition for Def
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Def_defined
#define datatype_Def_defined
  class a_Def;
  typedef a_Def * Def;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Cost
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Cost_defined
#define datatype_Cost_defined
  class a_Cost;
  typedef a_Cost * Cost;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for ConstraintSet
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_ConstraintSet_defined
#define datatype_ConstraintSet_defined
  class a_ConstraintSet;
  typedef a_ConstraintSet * ConstraintSet;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for GraphRewritingRule
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_GraphRewritingRule_defined
#define datatype_GraphRewritingRule_defined
  class a_GraphRewritingRule;
  typedef a_GraphRewritingRule * GraphRewritingRule;
#endif

#line 57 "../../prop-src/ast.ph"
#line 57 "../../prop-src/ast.ph"


class ClassDefinition;
class RewriteIndexing;

///////////////////////////////////////////////////////////////////////////////
//
//  Information on a match rule.
//
///////////////////////////////////////////////////////////////////////////////

class MatchRuleInfo : public Loc
{
  MatchRuleInfo   (const MatchRuleInfo&);  // no copy constructor
  void operator = (const MatchRuleInfo&);  // no assignment

public:
  Bool used;           // is the rule being used?
  Ty   ty;             // type of pattern
  int  rule_number;    // rule number
  Bool negated;        // negation in inference?
  Bool rewriting;      // A rewriting pattern?
  Bool is_chain_rule;  // Chain rule?
  enum RewritingMode
  {
    BEFORE, PREORDER, POSTORDER, TOPDOWN, BOTTOMUP, LAST_REWRITING_MODE
  } mode;              // rewriting mode
  enum
  {
    NO_OPTIONS = 0, CUTREWRITE = 1, REPLACEMENT = 2, FAILREWRITE = 4
  };

  typedef int RewritingOption;
  RewritingOption option;

  MatchRuleInfo();
};

///////////////////////////////////////////////////////////////////////////////
//
//  Expressions.
//
///////////////////////////////////////////////////////////////////////////////

#line 101 "../../prop-src/ast.ph"
#line 433 "../../prop-src/ast.ph"
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

#  define NOexp 0

enum SETLOp {
  ARBop = 0, DOMop = 1, RANop = 2, 
  CARDop = 3, WITHop = 4, WITHASSIGNop = 5, 
  LESSop = 6, LESSASSIGNop = 7
};



///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Generator
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Generator_defined
#define datatype_Generator_defined
  class a_Generator;
  typedef a_Generator * Generator;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for MatchExp
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_MatchExp_defined
#define datatype_MatchExp_defined
  class a_MatchExp;
  typedef a_MatchExp * MatchExp;
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
// Forward class definition for Decl
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Decl_defined
#define datatype_Decl_defined
  class a_Decl;
  typedef a_Decl * Decl;
#endif

#  define NOdecl 0

enum EntryDirection {
  LEFTdirection = 0, RIGHTdirection = 1
};



///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Protocol
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Protocol_defined
#define datatype_Protocol_defined
  class a_Protocol;
  typedef a_Protocol * Protocol;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for DatatypeDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_DatatypeDef_defined
#define datatype_DatatypeDef_defined
  class a_DatatypeDef;
  typedef a_DatatypeDef * DatatypeDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for TermDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_TermDef_defined
#define datatype_TermDef_defined
  class a_TermDef;
  typedef a_TermDef * TermDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for ViewDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_ViewDef_defined
#define datatype_ViewDef_defined
  class a_ViewDef;
  typedef a_ViewDef * ViewDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for LawDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_LawDef_defined
#define datatype_LawDef_defined
  class a_LawDef;
  typedef a_LawDef * LawDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for TyDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_TyDef_defined
#define datatype_TyDef_defined
  class a_TyDef;
  typedef a_TyDef * TyDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for FunDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_FunDef_defined
#define datatype_FunDef_defined
  class a_FunDef;
  typedef a_FunDef * FunDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for QualId
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_QualId_defined
#define datatype_QualId_defined
  class a_QualId;
  typedef a_QualId * QualId;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for InferenceRule
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_InferenceRule_defined
#define datatype_InferenceRule_defined
  class a_InferenceRule;
  typedef a_InferenceRule * InferenceRule;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Conclusion
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Conclusion_defined
#define datatype_Conclusion_defined
  class a_Conclusion;
  typedef a_Conclusion * Conclusion;
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type MatchExps
///////////////////////////////////////////////////////////////////////////////
#line 409 "../../prop-src/ast.ph"
typedef a_List<MatchExp> *  MatchExps;

///////////////////////////////////////////////////////////////////////////////
// Definition of type MatchRules
///////////////////////////////////////////////////////////////////////////////
#line 410 "../../prop-src/ast.ph"
typedef a_List<MatchRule> *  MatchRules;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Decls
///////////////////////////////////////////////////////////////////////////////
#line 411 "../../prop-src/ast.ph"
typedef a_List<Decl> *  Decls;

///////////////////////////////////////////////////////////////////////////////
// Definition of type DatatypeDefs
///////////////////////////////////////////////////////////////////////////////
#line 412 "../../prop-src/ast.ph"
typedef a_List<DatatypeDef> *  DatatypeDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type ViewDefs
///////////////////////////////////////////////////////////////////////////////
#line 413 "../../prop-src/ast.ph"
typedef a_List<ViewDef> *  ViewDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LawDefs
///////////////////////////////////////////////////////////////////////////////
#line 414 "../../prop-src/ast.ph"
typedef a_List<LawDef> *  LawDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type TyDefs
///////////////////////////////////////////////////////////////////////////////
#line 415 "../../prop-src/ast.ph"
typedef a_List<TyDef> *  TyDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type TermDefs
///////////////////////////////////////////////////////////////////////////////
#line 416 "../../prop-src/ast.ph"
typedef a_List<TermDef> *  TermDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type FunDefs
///////////////////////////////////////////////////////////////////////////////
#line 417 "../../prop-src/ast.ph"
typedef a_List<FunDef> *  FunDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Protocols
///////////////////////////////////////////////////////////////////////////////
#line 418 "../../prop-src/ast.ph"
typedef a_List<Protocol> *  Protocols;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabExp
///////////////////////////////////////////////////////////////////////////////
#line 419 "../../prop-src/ast.ph"
typedef struct { Id label; Exp exp;  } LabExp;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabMatchRule
///////////////////////////////////////////////////////////////////////////////
#line 420 "../../prop-src/ast.ph"
typedef struct { QualId id; MatchRule rule; Ty return_ty;  } LabMatchRule;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabMatchRules
///////////////////////////////////////////////////////////////////////////////
#line 421 "../../prop-src/ast.ph"
typedef struct { QualId id; MatchRules rules; Ty return_ty;  } LabMatchRules;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Exps
///////////////////////////////////////////////////////////////////////////////
#line 422 "../../prop-src/ast.ph"
typedef a_List<Exp> *  Exps;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabExps
///////////////////////////////////////////////////////////////////////////////
#line 423 "../../prop-src/ast.ph"
typedef a_List<LabExp> *  LabExps;

///////////////////////////////////////////////////////////////////////////////
// Definition of type InferenceRules
///////////////////////////////////////////////////////////////////////////////
#line 424 "../../prop-src/ast.ph"
typedef a_List<InferenceRule> *  InferenceRules;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Conclusions
///////////////////////////////////////////////////////////////////////////////
#line 425 "../../prop-src/ast.ph"
typedef a_List<Conclusion> *  Conclusions;

///////////////////////////////////////////////////////////////////////////////
// Definition of type GraphRewritingRules
///////////////////////////////////////////////////////////////////////////////
#line 426 "../../prop-src/ast.ph"
typedef a_List<GraphRewritingRule> *  GraphRewritingRules;

///////////////////////////////////////////////////////////////////////////////
// Definition of type FieldDefs
///////////////////////////////////////////////////////////////////////////////
#line 427 "../../prop-src/ast.ph"
typedef a_List<FieldDef> *  FieldDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type FieldLaws
///////////////////////////////////////////////////////////////////////////////
#line 428 "../../prop-src/ast.ph"
typedef a_List<FieldLaw> *  FieldLaws;

///////////////////////////////////////////////////////////////////////////////
// Definition of type ChildNo
///////////////////////////////////////////////////////////////////////////////
#line 429 "../../prop-src/ast.ph"
typedef int ChildNo;

///////////////////////////////////////////////////////////////////////////////
// Definition of type RuleNo
///////////////////////////////////////////////////////////////////////////////
#line 430 "../../prop-src/ast.ph"
typedef int RuleNo;

///////////////////////////////////////////////////////////////////////////////
// Definition of type MatchOptions
///////////////////////////////////////////////////////////////////////////////
#line 431 "../../prop-src/ast.ph"
typedef int MatchOptions;

///////////////////////////////////////////////////////////////////////////////
// Definition of type RewriteIndexings
///////////////////////////////////////////////////////////////////////////////
#line 432 "../../prop-src/ast.ph"
typedef a_List<RewriteIndexing *> *  RewriteIndexings;

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
class a_Exp : public MEM {
public:
  enum Tag_Exp {
    tag_LITERALexp = 0, tag_IDexp = 1, tag_RELexp = 2, 
    tag_DOTexp = 3, tag_SELECTORexp = 4, tag_DEREFexp = 5, 
    tag_ARROWexp = 6, tag_INDEXexp = 7, tag_BINOPexp = 8, 
    tag_PREFIXexp = 9, tag_POSTFIXexp = 10, tag_APPexp = 11, 
    tag_ASSIGNexp = 12, tag_IFexp = 13, tag_TUPLEexp = 14, 
    tag_EXTUPLEexp = 15, tag_RECORDexp = 16, tag_LISTexp = 17, 
    tag_VECTORexp = 18, tag_CONSexp = 19, tag_CASTexp = 20, 
    tag_QUALexp = 21, tag_EQexp = 22, tag_UNIFYexp = 23, 
    tag_LTexp = 24, tag_HASHexp = 25, tag_THISCOSTexp = 26, 
    tag_COSTexp = 27, tag_THISSYNexp = 28, tag_SYNexp = 29, 
    tag_SENDexp = 30, tag_SETLexp = 31, tag_LISTCOMPexp = 32, 
    tag_FORALLexp = 33, tag_EXISTSexp = 34, tag_MARKEDexp = 35
  };

public:
  const Tag_Exp tag__; // variant tag
protected:
  inline a_Exp(Tag_Exp t__) : tag__(t__) {}
public:
#line 167 "../../prop-src/ast.ph"
  
  Ty ty;
  
#line 169 "../../prop-src/ast.ph"
};
inline int boxed(const a_Exp * x) { return x != 0; }
inline int untag(const a_Exp * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::LITERALexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_LITERALexp : public a_Exp {
public:
#line 108 "../../prop-src/ast.ph"
  Literal LITERALexp; 
  inline Exp_LITERALexp (Literal x_LITERALexp)
   : a_Exp(tag_LITERALexp), LITERALexp(x_LITERALexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::IDexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_IDexp : public a_Exp {
public:
#line 109 "../../prop-src/ast.ph"
  Id IDexp; 
  inline Exp_IDexp (Id x_IDexp)
   : a_Exp(tag_IDexp), IDexp(x_IDexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::RELexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_RELexp : public a_Exp {
public:
#line 110 "../../prop-src/ast.ph"
  int RELexp; 
  inline Exp_RELexp (int x_RELexp)
   : a_Exp(tag_RELexp), RELexp(x_RELexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::DOTexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_DOTexp : public a_Exp {
public:
#line 111 "../../prop-src/ast.ph"
  Exp _1; Id _2; 
  inline Exp_DOTexp (Exp x_1, Id x_2)
   : a_Exp(tag_DOTexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::SELECTORexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_SELECTORexp : public a_Exp {
public:
#line 112 "../../prop-src/ast.ph"
  Exp _1; Cons _2; Ty _3; 
  inline Exp_SELECTORexp (Exp x_1, Cons x_2, Ty x_3)
   : a_Exp(tag_SELECTORexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::DEREFexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_DEREFexp : public a_Exp {
public:
#line 113 "../../prop-src/ast.ph"
  Exp DEREFexp; 
  inline Exp_DEREFexp (Exp x_DEREFexp)
   : a_Exp(tag_DEREFexp), DEREFexp(x_DEREFexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::ARROWexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_ARROWexp : public a_Exp {
public:
#line 114 "../../prop-src/ast.ph"
  Exp _1; Id _2; 
  inline Exp_ARROWexp (Exp x_1, Id x_2)
   : a_Exp(tag_ARROWexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::INDEXexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_INDEXexp : public a_Exp {
public:
#line 115 "../../prop-src/ast.ph"
  Exp _1; Exp _2; 
  inline Exp_INDEXexp (Exp x_1, Exp x_2)
   : a_Exp(tag_INDEXexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::BINOPexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_BINOPexp : public a_Exp {
public:
#line 116 "../../prop-src/ast.ph"
  Id _1; Exp _2; Exp _3; 
  inline Exp_BINOPexp (Id x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_BINOPexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::PREFIXexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_PREFIXexp : public a_Exp {
public:
#line 117 "../../prop-src/ast.ph"
  Id _1; Exp _2; 
  inline Exp_PREFIXexp (Id x_1, Exp x_2)
   : a_Exp(tag_PREFIXexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::POSTFIXexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_POSTFIXexp : public a_Exp {
public:
#line 118 "../../prop-src/ast.ph"
  Id _1; Exp _2; 
  inline Exp_POSTFIXexp (Id x_1, Exp x_2)
   : a_Exp(tag_POSTFIXexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::APPexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_APPexp : public a_Exp {
public:
#line 119 "../../prop-src/ast.ph"
  Exp _1; Exp _2; 
  inline Exp_APPexp (Exp x_1, Exp x_2)
   : a_Exp(tag_APPexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::ASSIGNexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_ASSIGNexp : public a_Exp {
public:
#line 120 "../../prop-src/ast.ph"
  Exp _1; Exp _2; 
  inline Exp_ASSIGNexp (Exp x_1, Exp x_2)
   : a_Exp(tag_ASSIGNexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::IFexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_IFexp : public a_Exp {
public:
#line 121 "../../prop-src/ast.ph"
  Exp _1; Exp _2; Exp _3; 
  inline Exp_IFexp (Exp x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_IFexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::TUPLEexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_TUPLEexp : public a_Exp {
public:
#line 122 "../../prop-src/ast.ph"
  a_List<Exp> *  TUPLEexp; 
  inline Exp_TUPLEexp (a_List<Exp> *  x_TUPLEexp)
   : a_Exp(tag_TUPLEexp), TUPLEexp(x_TUPLEexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::EXTUPLEexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_EXTUPLEexp : public a_Exp {
public:
#line 123 "../../prop-src/ast.ph"
  a_List<Exp> *  EXTUPLEexp; 
  inline Exp_EXTUPLEexp (a_List<Exp> *  x_EXTUPLEexp)
   : a_Exp(tag_EXTUPLEexp), EXTUPLEexp(x_EXTUPLEexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::RECORDexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_RECORDexp : public a_Exp {
public:
#line 124 "../../prop-src/ast.ph"
  a_List<LabExp> *  RECORDexp; 
  inline Exp_RECORDexp (a_List<LabExp> *  x_RECORDexp)
   : a_Exp(tag_RECORDexp), RECORDexp(x_RECORDexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::LISTexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_LISTexp : public a_Exp {
public:
#line 125 "../../prop-src/ast.ph"
  Cons _1; Cons _2; a_List<Exp> *  _3; Exp _4; 
  inline Exp_LISTexp (Cons x_1, Cons x_2, a_List<Exp> *  x_3, Exp x_4)
   : a_Exp(tag_LISTexp), _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::VECTORexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_VECTORexp : public a_Exp {
public:
#line 126 "../../prop-src/ast.ph"
  Cons _1; a_List<Exp> *  _2; 
  inline Exp_VECTORexp (Cons x_1, a_List<Exp> *  x_2)
   : a_Exp(tag_VECTORexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::CONSexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_CONSexp : public a_Exp {
public:
#line 127 "../../prop-src/ast.ph"
  Cons _1; a_List<Exp> *  _2; Exp _3; 
  inline Exp_CONSexp (Cons x_1, a_List<Exp> *  x_2, Exp x_3)
   : a_Exp(tag_CONSexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::CASTexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_CASTexp : public a_Exp {
public:
#line 128 "../../prop-src/ast.ph"
  Ty _1; Exp _2; 
  inline Exp_CASTexp (Ty x_1, Exp x_2)
   : a_Exp(tag_CASTexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::QUALexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_QUALexp : public a_Exp {
public:
#line 129 "../../prop-src/ast.ph"
  Ty _1; Id _2; 
  inline Exp_QUALexp (Ty x_1, Id x_2)
   : a_Exp(tag_QUALexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::EQexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_EQexp : public a_Exp {
public:
#line 137 "../../prop-src/ast.ph"
  Ty _1; Exp _2; Exp _3; 
  inline Exp_EQexp (Ty x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_EQexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::UNIFYexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_UNIFYexp : public a_Exp {
public:
#line 138 "../../prop-src/ast.ph"
  Ty _1; Exp _2; Exp _3; 
  inline Exp_UNIFYexp (Ty x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_UNIFYexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::LTexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_LTexp : public a_Exp {
public:
#line 139 "../../prop-src/ast.ph"
  Ty _1; Exp _2; Exp _3; 
  inline Exp_LTexp (Ty x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_LTexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::HASHexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_HASHexp : public a_Exp {
public:
#line 140 "../../prop-src/ast.ph"
  Ty _1; Exp _2; 
  inline Exp_HASHexp (Ty x_1, Exp x_2)
   : a_Exp(tag_HASHexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::THISCOSTexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_THISCOSTexp : public a_Exp {
public:
#line 141 "../../prop-src/ast.ph"
  
  inline Exp_THISCOSTexp ()
   : a_Exp(tag_THISCOSTexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::COSTexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_COSTexp : public a_Exp {
public:
#line 142 "../../prop-src/ast.ph"
  ChildNo COSTexp; 
  inline Exp_COSTexp (ChildNo x_COSTexp)
   : a_Exp(tag_COSTexp), COSTexp(x_COSTexp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::THISSYNexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_THISSYNexp : public a_Exp {
public:
#line 143 "../../prop-src/ast.ph"
  RuleNo _1; Ty _2; Bool _3; 
  inline Exp_THISSYNexp (RuleNo x_1, Ty x_2, Bool x_3)
   : a_Exp(tag_THISSYNexp), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::SYNexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_SYNexp : public a_Exp {
public:
#line 144 "../../prop-src/ast.ph"
  ChildNo _1; RuleNo _2; Ty _3; Bool _4; 
  inline Exp_SYNexp (ChildNo x_1, RuleNo x_2, Ty x_3, Bool x_4)
   : a_Exp(tag_SYNexp), _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::SENDexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_SENDexp : public a_Exp {
public:
#line 145 "../../prop-src/ast.ph"
  Id _1; a_List<Exp> *  _2; 
  inline Exp_SENDexp (Id x_1, a_List<Exp> *  x_2)
   : a_Exp(tag_SENDexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::SETLexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_SETLexp : public a_Exp {
public:
#line 152 "../../prop-src/ast.ph"
  SETLOp _1; Exps _2; 
  inline Exp_SETLexp (SETLOp x_1, Exps x_2)
   : a_Exp(tag_SETLexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::LISTCOMPexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_LISTCOMPexp : public a_Exp {
public:
#line 153 "../../prop-src/ast.ph"
  Exp exp; a_List<Generator> *  generators; Exp guard; 
  inline Exp_LISTCOMPexp (Exp x_exp, a_List<Generator> *  x_generators, Exp x_guard)
   : a_Exp(tag_LISTCOMPexp), exp(x_exp), generators(x_generators), guard(x_guard)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::FORALLexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_FORALLexp : public a_Exp {
public:
#line 157 "../../prop-src/ast.ph"
  Id _1; Exp _2; 
  inline Exp_FORALLexp (Id x_1, Exp x_2)
   : a_Exp(tag_FORALLexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::EXISTSexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_EXISTSexp : public a_Exp {
public:
#line 158 "../../prop-src/ast.ph"
  Id _1; Exp _2; 
  inline Exp_EXISTSexp (Id x_1, Exp x_2)
   : a_Exp(tag_EXISTSexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::MARKEDexp
//
///////////////////////////////////////////////////////////////////////////////
class Exp_MARKEDexp : public a_Exp {
public:
#line 165 "../../prop-src/ast.ph"
  Loc _1; Exp _2; 
  inline Exp_MARKEDexp (Loc x_1, Exp x_2)
   : a_Exp(tag_MARKEDexp), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Exp
//
///////////////////////////////////////////////////////////////////////////////
inline a_Exp * LITERALexp (Literal x_LITERALexp)
{
  return new Exp_LITERALexp (x_LITERALexp);
}
inline a_Exp * IDexp (Id x_IDexp)
{
  return new Exp_IDexp (x_IDexp);
}
inline a_Exp * RELexp (int x_RELexp)
{
  return new Exp_RELexp (x_RELexp);
}
inline a_Exp * DOTexp (Exp x_1, Id x_2)
{
  return new Exp_DOTexp (x_1, x_2);
}
inline a_Exp * SELECTORexp (Exp x_1, Cons x_2, Ty x_3)
{
  return new Exp_SELECTORexp (x_1, x_2, x_3);
}
inline a_Exp * DEREFexp (Exp x_DEREFexp)
{
  return new Exp_DEREFexp (x_DEREFexp);
}
inline a_Exp * ARROWexp (Exp x_1, Id x_2)
{
  return new Exp_ARROWexp (x_1, x_2);
}
inline a_Exp * INDEXexp (Exp x_1, Exp x_2)
{
  return new Exp_INDEXexp (x_1, x_2);
}
inline a_Exp * BINOPexp (Id x_1, Exp x_2, Exp x_3)
{
  return new Exp_BINOPexp (x_1, x_2, x_3);
}
inline a_Exp * PREFIXexp (Id x_1, Exp x_2)
{
  return new Exp_PREFIXexp (x_1, x_2);
}
inline a_Exp * POSTFIXexp (Id x_1, Exp x_2)
{
  return new Exp_POSTFIXexp (x_1, x_2);
}
inline a_Exp * APPexp (Exp x_1, Exp x_2)
{
  return new Exp_APPexp (x_1, x_2);
}
inline a_Exp * ASSIGNexp (Exp x_1, Exp x_2)
{
  return new Exp_ASSIGNexp (x_1, x_2);
}
inline a_Exp * IFexp (Exp x_1, Exp x_2, Exp x_3)
{
  return new Exp_IFexp (x_1, x_2, x_3);
}
inline a_Exp * TUPLEexp (a_List<Exp> *  x_TUPLEexp)
{
  return new Exp_TUPLEexp (x_TUPLEexp);
}
inline a_Exp * EXTUPLEexp (a_List<Exp> *  x_EXTUPLEexp)
{
  return new Exp_EXTUPLEexp (x_EXTUPLEexp);
}
inline a_Exp * RECORDexp (a_List<LabExp> *  x_RECORDexp)
{
  return new Exp_RECORDexp (x_RECORDexp);
}
inline a_Exp * LISTexp (Cons x_1, Cons x_2, a_List<Exp> *  x_3, Exp x_4)
{
  return new Exp_LISTexp (x_1, x_2, x_3, x_4);
}
inline a_Exp * VECTORexp (Cons x_1, a_List<Exp> *  x_2)
{
  return new Exp_VECTORexp (x_1, x_2);
}
inline a_Exp * CONSexp (Cons x_1, a_List<Exp> *  x_2, Exp x_3)
{
  return new Exp_CONSexp (x_1, x_2, x_3);
}
inline a_Exp * CASTexp (Ty x_1, Exp x_2)
{
  return new Exp_CASTexp (x_1, x_2);
}
inline a_Exp * QUALexp (Ty x_1, Id x_2)
{
  return new Exp_QUALexp (x_1, x_2);
}
inline a_Exp * EQexp (Ty x_1, Exp x_2, Exp x_3)
{
  return new Exp_EQexp (x_1, x_2, x_3);
}
inline a_Exp * UNIFYexp (Ty x_1, Exp x_2, Exp x_3)
{
  return new Exp_UNIFYexp (x_1, x_2, x_3);
}
inline a_Exp * LTexp (Ty x_1, Exp x_2, Exp x_3)
{
  return new Exp_LTexp (x_1, x_2, x_3);
}
inline a_Exp * HASHexp (Ty x_1, Exp x_2)
{
  return new Exp_HASHexp (x_1, x_2);
}
inline a_Exp * THISCOSTexp ()
{
  return new Exp_THISCOSTexp ;
}
inline a_Exp * COSTexp (ChildNo x_COSTexp)
{
  return new Exp_COSTexp (x_COSTexp);
}
inline a_Exp * THISSYNexp (RuleNo x_1, Ty x_2, Bool x_3)
{
  return new Exp_THISSYNexp (x_1, x_2, x_3);
}
inline a_Exp * SYNexp (ChildNo x_1, RuleNo x_2, Ty x_3, Bool x_4)
{
  return new Exp_SYNexp (x_1, x_2, x_3, x_4);
}
inline a_Exp * SENDexp (Id x_1, a_List<Exp> *  x_2)
{
  return new Exp_SENDexp (x_1, x_2);
}
inline a_Exp * SETLexp (SETLOp x_1, Exps x_2)
{
  return new Exp_SETLexp (x_1, x_2);
}
inline a_Exp * LISTCOMPexp (Exp x_exp, a_List<Generator> *  x_generators, Exp x_guard)
{
  return new Exp_LISTCOMPexp (x_exp, x_generators, x_guard);
}
inline a_Exp * FORALLexp (Id x_1, Exp x_2)
{
  return new Exp_FORALLexp (x_1, x_2);
}
inline a_Exp * EXISTSexp (Id x_1, Exp x_2)
{
  return new Exp_EXISTSexp (x_1, x_2);
}
inline a_Exp * MARKEDexp (Loc x_1, Exp x_2)
{
  return new Exp_MARKEDexp (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Exp
//
///////////////////////////////////////////////////////////////////////////////
inline Exp_LITERALexp * _LITERALexp(const a_Exp * _x_) { return (Exp_LITERALexp *)_x_; }
inline Exp_IDexp * _IDexp(const a_Exp * _x_) { return (Exp_IDexp *)_x_; }
inline Exp_RELexp * _RELexp(const a_Exp * _x_) { return (Exp_RELexp *)_x_; }
inline Exp_DOTexp * _DOTexp(const a_Exp * _x_) { return (Exp_DOTexp *)_x_; }
inline Exp_SELECTORexp * _SELECTORexp(const a_Exp * _x_) { return (Exp_SELECTORexp *)_x_; }
inline Exp_DEREFexp * _DEREFexp(const a_Exp * _x_) { return (Exp_DEREFexp *)_x_; }
inline Exp_ARROWexp * _ARROWexp(const a_Exp * _x_) { return (Exp_ARROWexp *)_x_; }
inline Exp_INDEXexp * _INDEXexp(const a_Exp * _x_) { return (Exp_INDEXexp *)_x_; }
inline Exp_BINOPexp * _BINOPexp(const a_Exp * _x_) { return (Exp_BINOPexp *)_x_; }
inline Exp_PREFIXexp * _PREFIXexp(const a_Exp * _x_) { return (Exp_PREFIXexp *)_x_; }
inline Exp_POSTFIXexp * _POSTFIXexp(const a_Exp * _x_) { return (Exp_POSTFIXexp *)_x_; }
inline Exp_APPexp * _APPexp(const a_Exp * _x_) { return (Exp_APPexp *)_x_; }
inline Exp_ASSIGNexp * _ASSIGNexp(const a_Exp * _x_) { return (Exp_ASSIGNexp *)_x_; }
inline Exp_IFexp * _IFexp(const a_Exp * _x_) { return (Exp_IFexp *)_x_; }
inline Exp_TUPLEexp * _TUPLEexp(const a_Exp * _x_) { return (Exp_TUPLEexp *)_x_; }
inline Exp_EXTUPLEexp * _EXTUPLEexp(const a_Exp * _x_) { return (Exp_EXTUPLEexp *)_x_; }
inline Exp_RECORDexp * _RECORDexp(const a_Exp * _x_) { return (Exp_RECORDexp *)_x_; }
inline Exp_LISTexp * _LISTexp(const a_Exp * _x_) { return (Exp_LISTexp *)_x_; }
inline Exp_VECTORexp * _VECTORexp(const a_Exp * _x_) { return (Exp_VECTORexp *)_x_; }
inline Exp_CONSexp * _CONSexp(const a_Exp * _x_) { return (Exp_CONSexp *)_x_; }
inline Exp_CASTexp * _CASTexp(const a_Exp * _x_) { return (Exp_CASTexp *)_x_; }
inline Exp_QUALexp * _QUALexp(const a_Exp * _x_) { return (Exp_QUALexp *)_x_; }
inline Exp_EQexp * _EQexp(const a_Exp * _x_) { return (Exp_EQexp *)_x_; }
inline Exp_UNIFYexp * _UNIFYexp(const a_Exp * _x_) { return (Exp_UNIFYexp *)_x_; }
inline Exp_LTexp * _LTexp(const a_Exp * _x_) { return (Exp_LTexp *)_x_; }
inline Exp_HASHexp * _HASHexp(const a_Exp * _x_) { return (Exp_HASHexp *)_x_; }
inline Exp_THISCOSTexp * _THISCOSTexp(const a_Exp * _x_) { return (Exp_THISCOSTexp *)_x_; }
inline Exp_COSTexp * _COSTexp(const a_Exp * _x_) { return (Exp_COSTexp *)_x_; }
inline Exp_THISSYNexp * _THISSYNexp(const a_Exp * _x_) { return (Exp_THISSYNexp *)_x_; }
inline Exp_SYNexp * _SYNexp(const a_Exp * _x_) { return (Exp_SYNexp *)_x_; }
inline Exp_SENDexp * _SENDexp(const a_Exp * _x_) { return (Exp_SENDexp *)_x_; }
inline Exp_SETLexp * _SETLexp(const a_Exp * _x_) { return (Exp_SETLexp *)_x_; }
inline Exp_LISTCOMPexp * _LISTCOMPexp(const a_Exp * _x_) { return (Exp_LISTCOMPexp *)_x_; }
inline Exp_FORALLexp * _FORALLexp(const a_Exp * _x_) { return (Exp_FORALLexp *)_x_; }
inline Exp_EXISTSexp * _EXISTSexp(const a_Exp * _x_) { return (Exp_EXISTSexp *)_x_; }
inline Exp_MARKEDexp * _MARKEDexp(const a_Exp * _x_) { return (Exp_MARKEDexp *)_x_; }


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Generator::GENERATOR
//
///////////////////////////////////////////////////////////////////////////////
class a_Generator : public Loc {
public:
#line 193 "../../prop-src/ast.ph"
  Pat pat; Exp guard; Exp exp; 
  inline a_Generator (Pat x_pat, Exp x_guard, Exp x_exp)
   : pat(x_pat), guard(x_guard), exp(x_exp)
  {
  }
};
inline int boxed(const a_Generator *) { return 1; }
inline int untag(const a_Generator *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Generator
//
///////////////////////////////////////////////////////////////////////////////
inline a_Generator * GENERATOR (Pat x_pat, Exp x_guard, Exp x_exp)
{
  return new a_Generator (x_pat, x_guard, x_exp);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Generator
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor MatchExp::MATCHexp
//
///////////////////////////////////////////////////////////////////////////////
class a_MatchExp : public Loc {
public:
#line 207 "../../prop-src/ast.ph"
  Exp _1; Id _2; 
  inline a_MatchExp (Exp x_1, Id x_2)
   : _1(x_1), _2(x_2)
  {
  }
};
inline int boxed(const a_MatchExp *) { return 1; }
inline int untag(const a_MatchExp *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for MatchExp
//
///////////////////////////////////////////////////////////////////////////////
inline a_MatchExp * MATCHexp (Exp x_1, Id x_2)
{
  return new a_MatchExp (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for MatchExp
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor MatchRule::MATCHrule
//
///////////////////////////////////////////////////////////////////////////////
class a_MatchRule : public MatchRuleInfo {
public:
#line 215 "../../prop-src/ast.ph"
  Id _1; Pat _2; Exp _3; Cost _4; a_List<Decl> *  _5; 
  inline a_MatchRule (Id x_1, Pat x_2, Exp x_3, Cost x_4, a_List<Decl> *  x_5)
   : _1(x_1), _2(x_2), _3(x_3), _4(x_4), _5(x_5)
  {
  }
};
inline int boxed(const a_MatchRule *) { return 1; }
inline int untag(const a_MatchRule *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for MatchRule
//
///////////////////////////////////////////////////////////////////////////////
inline a_MatchRule * MATCHrule (Id x_1, Pat x_2, Exp x_3, Cost x_4, a_List<Decl> *  x_5)
{
  return new a_MatchRule (x_1, x_2, x_3, x_4, x_5);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for MatchRule
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Decl
//
///////////////////////////////////////////////////////////////////////////////
class a_Decl : public MEM {
public:
  enum Tag_Decl {
    tag_OPAQUEdecl = 0, tag_DATATYPEdecl = 1, tag_INSTANTIATEdecl = 2, 
    tag_CLASSDEFdecl = 3, tag_INFERENCEdecl = 4, tag_REWRITEdecl = 5, 
    tag_REWRITINGdecl = 6, tag_REPLACEMENTdecl = 7, tag_CUTREWRITEdecl = 8, 
    tag_FAILREWRITEdecl = 9, tag_INJECTdecl = 10, tag_GOTOdecl = 11, 
    tag_SETSTATEdecl = 12, tag_CONSTRAINTdecl = 13, tag_SYNTAXdecl = 14, 
    tag_ATTRIBUTEGRAMMARdecl = 15, tag_FUNdecl = 16, tag_MATCHdecl = 17, 
    tag_BITFIELDdecl = 18, tag_SETLSTMTdecl = 19, tag_SETLDEFdecl = 20, 
    tag_GRAPHREWRITEdecl = 21, tag_DATAFLOWdecl = 22, tag_CLASSOFdecl = 23, 
    tag_TYPEEXPdecl = 24, tag_EXPdecl = 25, tag_MARKEDdecl = 26
  };

public:
  const Tag_Decl tag__; // variant tag
protected:
  inline a_Decl(Tag_Decl t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Decl * x) { return x != 0; }
inline int untag(const a_Decl * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::OPAQUEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_OPAQUEdecl : public a_Decl {
public:
#line 227 "../../prop-src/ast.ph"
  char const * OPAQUEdecl; 
  inline Decl_OPAQUEdecl (char const * x_OPAQUEdecl)
   : a_Decl(tag_OPAQUEdecl), OPAQUEdecl(x_OPAQUEdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::DATATYPEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_DATATYPEdecl : public a_Decl {
public:
#line 230 "../../prop-src/ast.ph"
  DatatypeDefs _1; ViewDefs _2; LawDefs _3; TyDefs _4; 
  inline Decl_DATATYPEdecl (DatatypeDefs x_1, ViewDefs x_2, LawDefs x_3, TyDefs x_4)
   : a_Decl(tag_DATATYPEdecl), _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::INSTANTIATEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_INSTANTIATEdecl : public a_Decl {
public:
#line 231 "../../prop-src/ast.ph"
  Bool _1; Tys _2; 
  inline Decl_INSTANTIATEdecl (Bool x_1, Tys x_2)
   : a_Decl(tag_INSTANTIATEdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::CLASSDEFdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_CLASSDEFdecl : public a_Decl {
public:
#line 234 "../../prop-src/ast.ph"
  ClassDefinition * CLASSDEFdecl; 
  inline Decl_CLASSDEFdecl (ClassDefinition * x_CLASSDEFdecl)
   : a_Decl(tag_CLASSDEFdecl), CLASSDEFdecl(x_CLASSDEFdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::INFERENCEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_INFERENCEdecl : public a_Decl {
public:
#line 237 "../../prop-src/ast.ph"
  Id _1; InferenceRules _2; 
  inline Decl_INFERENCEdecl (Id x_1, InferenceRules x_2)
   : a_Decl(tag_INFERENCEdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::REWRITEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_REWRITEdecl : public a_Decl {
public:
#line 240 "../../prop-src/ast.ph"
  Id _1; RewriteIndexings _2; MatchRules _3; 
  inline Decl_REWRITEdecl (Id x_1, RewriteIndexings x_2, MatchRules x_3)
   : a_Decl(tag_REWRITEdecl), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::REWRITINGdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_REWRITINGdecl : public a_Decl {
public:
#line 241 "../../prop-src/ast.ph"
  Protocols _1; Exp _2; Exp _3; RewriteIndexings _4; MatchRules _5; TyQual _6; 
  inline Decl_REWRITINGdecl (Protocols x_1, Exp x_2, Exp x_3, RewriteIndexings x_4, MatchRules x_5, TyQual x_6)
   : a_Decl(tag_REWRITINGdecl), _1(x_1), _2(x_2), _3(x_3), _4(x_4), _5(x_5), _6(x_6)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::REPLACEMENTdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_REPLACEMENTdecl : public a_Decl {
public:
#line 243 "../../prop-src/ast.ph"
  Exp _1; MatchRuleInfo::RewritingMode _2; 
  inline Decl_REPLACEMENTdecl (Exp x_1, MatchRuleInfo::RewritingMode x_2)
   : a_Decl(tag_REPLACEMENTdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::CUTREWRITEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_CUTREWRITEdecl : public a_Decl {
public:
#line 244 "../../prop-src/ast.ph"
  Exp _1; MatchRuleInfo::RewritingMode _2; 
  inline Decl_CUTREWRITEdecl (Exp x_1, MatchRuleInfo::RewritingMode x_2)
   : a_Decl(tag_CUTREWRITEdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::FAILREWRITEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_FAILREWRITEdecl : public a_Decl {
public:
#line 245 "../../prop-src/ast.ph"
  MatchRuleInfo::RewritingMode FAILREWRITEdecl; 
  inline Decl_FAILREWRITEdecl (MatchRuleInfo::RewritingMode x_FAILREWRITEdecl)
   : a_Decl(tag_FAILREWRITEdecl), FAILREWRITEdecl(x_FAILREWRITEdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::INJECTdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_INJECTdecl : public a_Decl {
public:
#line 246 "../../prop-src/ast.ph"
  int node_number; EntryDirection direction; 
  inline Decl_INJECTdecl (int x_node_number, EntryDirection x_direction)
   : a_Decl(tag_INJECTdecl), node_number(x_node_number), direction(x_direction)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::GOTOdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_GOTOdecl : public a_Decl {
public:
#line 249 "../../prop-src/ast.ph"
  Id GOTOdecl; 
  inline Decl_GOTOdecl (Id x_GOTOdecl)
   : a_Decl(tag_GOTOdecl), GOTOdecl(x_GOTOdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::SETSTATEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_SETSTATEdecl : public a_Decl {
public:
#line 250 "../../prop-src/ast.ph"
  int SETSTATEdecl; 
  inline Decl_SETSTATEdecl (int x_SETSTATEdecl)
   : a_Decl(tag_SETSTATEdecl), SETSTATEdecl(x_SETSTATEdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::CONSTRAINTdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_CONSTRAINTdecl : public a_Decl {
public:
#line 253 "../../prop-src/ast.ph"
  Id _1; ConstraintSet _2; 
  inline Decl_CONSTRAINTdecl (Id x_1, ConstraintSet x_2)
   : a_Decl(tag_CONSTRAINTdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::SYNTAXdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_SYNTAXdecl : public a_Decl {
public:
#line 256 "../../prop-src/ast.ph"
  Id _1; GramExp _2; 
  inline Decl_SYNTAXdecl (Id x_1, GramExp x_2)
   : a_Decl(tag_SYNTAXdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::ATTRIBUTEGRAMMARdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_ATTRIBUTEGRAMMARdecl : public a_Decl {
public:
#line 257 "../../prop-src/ast.ph"
  Id _1; GramExp _2; 
  inline Decl_ATTRIBUTEGRAMMARdecl (Id x_1, GramExp x_2)
   : a_Decl(tag_ATTRIBUTEGRAMMARdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::FUNdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_FUNdecl : public a_Decl {
public:
#line 260 "../../prop-src/ast.ph"
  FunDefs FUNdecl; 
  inline Decl_FUNdecl (FunDefs x_FUNdecl)
   : a_Decl(tag_FUNdecl), FUNdecl(x_FUNdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::MATCHdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_MATCHdecl : public a_Decl {
public:
#line 261 "../../prop-src/ast.ph"
  MatchExps _1; MatchRules _2; MatchOptions _3; Ty _4; 
  inline Decl_MATCHdecl (MatchExps x_1, MatchRules x_2, MatchOptions x_3, Ty x_4)
   : a_Decl(tag_MATCHdecl), _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::BITFIELDdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_BITFIELDdecl : public a_Decl {
public:
#line 264 "../../prop-src/ast.ph"
  Id name; int width; FieldDefs field_names; FieldLaws laws; 
  inline Decl_BITFIELDdecl (Id x_name, int x_width, FieldDefs x_field_names, FieldLaws x_laws)
   : a_Decl(tag_BITFIELDdecl), name(x_name), width(x_width), field_names(x_field_names), laws(x_laws)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::SETLSTMTdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_SETLSTMTdecl : public a_Decl {
public:
#line 271 "../../prop-src/ast.ph"
  Stmt SETLSTMTdecl; 
  inline Decl_SETLSTMTdecl (Stmt x_SETLSTMTdecl)
   : a_Decl(tag_SETLSTMTdecl), SETLSTMTdecl(x_SETLSTMTdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::SETLDEFdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_SETLDEFdecl : public a_Decl {
public:
#line 272 "../../prop-src/ast.ph"
  Def SETLDEFdecl; 
  inline Decl_SETLDEFdecl (Def x_SETLDEFdecl)
   : a_Decl(tag_SETLDEFdecl), SETLDEFdecl(x_SETLDEFdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::GRAPHREWRITEdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_GRAPHREWRITEdecl : public a_Decl {
public:
#line 275 "../../prop-src/ast.ph"
  Id name; LabTys args; GraphRewritingRules rules; 
  inline Decl_GRAPHREWRITEdecl (Id x_name, LabTys x_args, GraphRewritingRules x_rules)
   : a_Decl(tag_GRAPHREWRITEdecl), name(x_name), args(x_args), rules(x_rules)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::DATAFLOWdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_DATAFLOWdecl : public a_Decl {
public:
#line 281 "../../prop-src/ast.ph"
  Id name; 
  inline Decl_DATAFLOWdecl (Id x_name)
   : a_Decl(tag_DATAFLOWdecl), name(x_name)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::CLASSOFdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_CLASSOFdecl : public a_Decl {
public:
#line 284 "../../prop-src/ast.ph"
  Id CLASSOFdecl; 
  inline Decl_CLASSOFdecl (Id x_CLASSOFdecl)
   : a_Decl(tag_CLASSOFdecl), CLASSOFdecl(x_CLASSOFdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::TYPEEXPdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_TYPEEXPdecl : public a_Decl {
public:
#line 285 "../../prop-src/ast.ph"
  Ty TYPEEXPdecl; 
  inline Decl_TYPEEXPdecl (Ty x_TYPEEXPdecl)
   : a_Decl(tag_TYPEEXPdecl), TYPEEXPdecl(x_TYPEEXPdecl)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::EXPdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_EXPdecl : public a_Decl {
public:
#line 286 "../../prop-src/ast.ph"
  Exp exp; char const * prefix; char const * suffix; 
  inline Decl_EXPdecl (Exp x_exp, char const * x_prefix = 0, char const * x_suffix = 0)
   : a_Decl(tag_EXPdecl), exp(x_exp), prefix(x_prefix), suffix(x_suffix)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::MARKEDdecl
//
///////////////////////////////////////////////////////////////////////////////
class Decl_MARKEDdecl : public a_Decl {
public:
#line 292 "../../prop-src/ast.ph"
  Loc _1; Decl _2; 
  inline Decl_MARKEDdecl (Loc x_1, Decl x_2)
   : a_Decl(tag_MARKEDdecl), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Decl
//
///////////////////////////////////////////////////////////////////////////////
inline a_Decl * OPAQUEdecl (char const * x_OPAQUEdecl)
{
  return new Decl_OPAQUEdecl (x_OPAQUEdecl);
}
inline a_Decl * DATATYPEdecl (DatatypeDefs x_1, ViewDefs x_2, LawDefs x_3, TyDefs x_4)
{
  return new Decl_DATATYPEdecl (x_1, x_2, x_3, x_4);
}
inline a_Decl * INSTANTIATEdecl (Bool x_1, Tys x_2)
{
  return new Decl_INSTANTIATEdecl (x_1, x_2);
}
inline a_Decl * CLASSDEFdecl (ClassDefinition * x_CLASSDEFdecl)
{
  return new Decl_CLASSDEFdecl (x_CLASSDEFdecl);
}
inline a_Decl * INFERENCEdecl (Id x_1, InferenceRules x_2)
{
  return new Decl_INFERENCEdecl (x_1, x_2);
}
inline a_Decl * REWRITEdecl (Id x_1, RewriteIndexings x_2, MatchRules x_3)
{
  return new Decl_REWRITEdecl (x_1, x_2, x_3);
}
inline a_Decl * REWRITINGdecl (Protocols x_1, Exp x_2, Exp x_3, RewriteIndexings x_4, MatchRules x_5, TyQual x_6)
{
  return new Decl_REWRITINGdecl (x_1, x_2, x_3, x_4, x_5, x_6);
}
inline a_Decl * REPLACEMENTdecl (Exp x_1, MatchRuleInfo::RewritingMode x_2)
{
  return new Decl_REPLACEMENTdecl (x_1, x_2);
}
inline a_Decl * CUTREWRITEdecl (Exp x_1, MatchRuleInfo::RewritingMode x_2)
{
  return new Decl_CUTREWRITEdecl (x_1, x_2);
}
inline a_Decl * FAILREWRITEdecl (MatchRuleInfo::RewritingMode x_FAILREWRITEdecl)
{
  return new Decl_FAILREWRITEdecl (x_FAILREWRITEdecl);
}
inline a_Decl * INJECTdecl (int x_node_number, EntryDirection x_direction)
{
  return new Decl_INJECTdecl (x_node_number, x_direction);
}
inline a_Decl * GOTOdecl (Id x_GOTOdecl)
{
  return new Decl_GOTOdecl (x_GOTOdecl);
}
inline a_Decl * SETSTATEdecl (int x_SETSTATEdecl)
{
  return new Decl_SETSTATEdecl (x_SETSTATEdecl);
}
inline a_Decl * CONSTRAINTdecl (Id x_1, ConstraintSet x_2)
{
  return new Decl_CONSTRAINTdecl (x_1, x_2);
}
inline a_Decl * SYNTAXdecl (Id x_1, GramExp x_2)
{
  return new Decl_SYNTAXdecl (x_1, x_2);
}
inline a_Decl * ATTRIBUTEGRAMMARdecl (Id x_1, GramExp x_2)
{
  return new Decl_ATTRIBUTEGRAMMARdecl (x_1, x_2);
}
inline a_Decl * FUNdecl (FunDefs x_FUNdecl)
{
  return new Decl_FUNdecl (x_FUNdecl);
}
inline a_Decl * MATCHdecl (MatchExps x_1, MatchRules x_2, MatchOptions x_3, Ty x_4)
{
  return new Decl_MATCHdecl (x_1, x_2, x_3, x_4);
}
inline a_Decl * BITFIELDdecl (Id x_name, int x_width, FieldDefs x_field_names, FieldLaws x_laws)
{
  return new Decl_BITFIELDdecl (x_name, x_width, x_field_names, x_laws);
}
inline a_Decl * SETLSTMTdecl (Stmt x_SETLSTMTdecl)
{
  return new Decl_SETLSTMTdecl (x_SETLSTMTdecl);
}
inline a_Decl * SETLDEFdecl (Def x_SETLDEFdecl)
{
  return new Decl_SETLDEFdecl (x_SETLDEFdecl);
}
inline a_Decl * GRAPHREWRITEdecl (Id x_name, LabTys x_args, GraphRewritingRules x_rules)
{
  return new Decl_GRAPHREWRITEdecl (x_name, x_args, x_rules);
}
inline a_Decl * DATAFLOWdecl (Id x_name)
{
  return new Decl_DATAFLOWdecl (x_name);
}
inline a_Decl * CLASSOFdecl (Id x_CLASSOFdecl)
{
  return new Decl_CLASSOFdecl (x_CLASSOFdecl);
}
inline a_Decl * TYPEEXPdecl (Ty x_TYPEEXPdecl)
{
  return new Decl_TYPEEXPdecl (x_TYPEEXPdecl);
}
inline a_Decl * EXPdecl (Exp x_exp, char const * x_prefix = 0, char const * x_suffix = 0)
{
  return new Decl_EXPdecl (x_exp, x_prefix, x_suffix);
}
inline a_Decl * MARKEDdecl (Loc x_1, Decl x_2)
{
  return new Decl_MARKEDdecl (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Decl
//
///////////////////////////////////////////////////////////////////////////////
inline Decl_OPAQUEdecl * _OPAQUEdecl(const a_Decl * _x_) { return (Decl_OPAQUEdecl *)_x_; }
inline Decl_DATATYPEdecl * _DATATYPEdecl(const a_Decl * _x_) { return (Decl_DATATYPEdecl *)_x_; }
inline Decl_INSTANTIATEdecl * _INSTANTIATEdecl(const a_Decl * _x_) { return (Decl_INSTANTIATEdecl *)_x_; }
inline Decl_CLASSDEFdecl * _CLASSDEFdecl(const a_Decl * _x_) { return (Decl_CLASSDEFdecl *)_x_; }
inline Decl_INFERENCEdecl * _INFERENCEdecl(const a_Decl * _x_) { return (Decl_INFERENCEdecl *)_x_; }
inline Decl_REWRITEdecl * _REWRITEdecl(const a_Decl * _x_) { return (Decl_REWRITEdecl *)_x_; }
inline Decl_REWRITINGdecl * _REWRITINGdecl(const a_Decl * _x_) { return (Decl_REWRITINGdecl *)_x_; }
inline Decl_REPLACEMENTdecl * _REPLACEMENTdecl(const a_Decl * _x_) { return (Decl_REPLACEMENTdecl *)_x_; }
inline Decl_CUTREWRITEdecl * _CUTREWRITEdecl(const a_Decl * _x_) { return (Decl_CUTREWRITEdecl *)_x_; }
inline Decl_FAILREWRITEdecl * _FAILREWRITEdecl(const a_Decl * _x_) { return (Decl_FAILREWRITEdecl *)_x_; }
inline Decl_INJECTdecl * _INJECTdecl(const a_Decl * _x_) { return (Decl_INJECTdecl *)_x_; }
inline Decl_GOTOdecl * _GOTOdecl(const a_Decl * _x_) { return (Decl_GOTOdecl *)_x_; }
inline Decl_SETSTATEdecl * _SETSTATEdecl(const a_Decl * _x_) { return (Decl_SETSTATEdecl *)_x_; }
inline Decl_CONSTRAINTdecl * _CONSTRAINTdecl(const a_Decl * _x_) { return (Decl_CONSTRAINTdecl *)_x_; }
inline Decl_SYNTAXdecl * _SYNTAXdecl(const a_Decl * _x_) { return (Decl_SYNTAXdecl *)_x_; }
inline Decl_ATTRIBUTEGRAMMARdecl * _ATTRIBUTEGRAMMARdecl(const a_Decl * _x_) { return (Decl_ATTRIBUTEGRAMMARdecl *)_x_; }
inline Decl_FUNdecl * _FUNdecl(const a_Decl * _x_) { return (Decl_FUNdecl *)_x_; }
inline Decl_MATCHdecl * _MATCHdecl(const a_Decl * _x_) { return (Decl_MATCHdecl *)_x_; }
inline Decl_BITFIELDdecl * _BITFIELDdecl(const a_Decl * _x_) { return (Decl_BITFIELDdecl *)_x_; }
inline Decl_SETLSTMTdecl * _SETLSTMTdecl(const a_Decl * _x_) { return (Decl_SETLSTMTdecl *)_x_; }
inline Decl_SETLDEFdecl * _SETLDEFdecl(const a_Decl * _x_) { return (Decl_SETLDEFdecl *)_x_; }
inline Decl_GRAPHREWRITEdecl * _GRAPHREWRITEdecl(const a_Decl * _x_) { return (Decl_GRAPHREWRITEdecl *)_x_; }
inline Decl_DATAFLOWdecl * _DATAFLOWdecl(const a_Decl * _x_) { return (Decl_DATAFLOWdecl *)_x_; }
inline Decl_CLASSOFdecl * _CLASSOFdecl(const a_Decl * _x_) { return (Decl_CLASSOFdecl *)_x_; }
inline Decl_TYPEEXPdecl * _TYPEEXPdecl(const a_Decl * _x_) { return (Decl_TYPEEXPdecl *)_x_; }
inline Decl_EXPdecl * _EXPdecl(const a_Decl * _x_) { return (Decl_EXPdecl *)_x_; }
inline Decl_MARKEDdecl * _MARKEDdecl(const a_Decl * _x_) { return (Decl_MARKEDdecl *)_x_; }


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Protocol::PROTOCOL
//
///////////////////////////////////////////////////////////////////////////////
class a_Protocol : public Loc {
public:
#line 309 "../../prop-src/ast.ph"
  Ty ty; Ty inh; Ty syn; 
  inline a_Protocol (Ty x_ty, Ty x_inh, Ty x_syn)
   : ty(x_ty), inh(x_inh), syn(x_syn)
  {
  }
};
inline int boxed(const a_Protocol *) { return 1; }
inline int untag(const a_Protocol *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Protocol
//
///////////////////////////////////////////////////////////////////////////////
inline a_Protocol * PROTOCOL (Ty x_ty, Ty x_inh, Ty x_syn)
{
  return new a_Protocol (x_ty, x_inh, x_syn);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Protocol
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor DatatypeDef::DATATYPEdef
//
///////////////////////////////////////////////////////////////////////////////
class a_DatatypeDef : public Loc {
public:
#line 317 "../../prop-src/ast.ph"
  Id _1; TyVars _2; Inherits _3; TyQual _4; TermDefs _5; Decls _6; 
  inline a_DatatypeDef (Id x_1, TyVars x_2, Inherits x_3, TyQual x_4, TermDefs x_5, Decls x_6)
   : _1(x_1), _2(x_2), _3(x_3), _4(x_4), _5(x_5), _6(x_6)
  {
  }
};
inline int boxed(const a_DatatypeDef *) { return 1; }
inline int untag(const a_DatatypeDef *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for DatatypeDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_DatatypeDef * DATATYPEdef (Id x_1, TyVars x_2, Inherits x_3, TyQual x_4, TermDefs x_5, Decls x_6)
{
  return new a_DatatypeDef (x_1, x_2, x_3, x_4, x_5, x_6);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for DatatypeDef
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TermDef::TERMdef
//
///////////////////////////////////////////////////////////////////////////////
class a_TermDef : public Loc {
public:
#line 326 "../../prop-src/ast.ph"
  Id id; Ty ty; Decls decls; Inherits inherits; Pat pat; PrintFormats print_formats; TyOpt opt; TyQual qual; Exp view_predicate; 
  inline a_TermDef (Id x_id, Ty x_ty, Decls x_decls = nil_1_, Inherits x_inherits = nil_1_, Pat x_pat = NOpat, PrintFormats x_print_formats = nil_1_, TyOpt x_opt = OPTnone, TyQual x_qual = QUALnone, Exp x_view_predicate = NOexp)
   : id(x_id), ty(x_ty), decls(x_decls), inherits(x_inherits), pat(x_pat), print_formats(x_print_formats), opt(x_opt), qual(x_qual), view_predicate(x_view_predicate)
  {
  }
};
inline int boxed(const a_TermDef *) { return 1; }
inline int untag(const a_TermDef *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for TermDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_TermDef * TERMdef (Id x_id, Ty x_ty, Decls x_decls = nil_1_, Inherits x_inherits = nil_1_, Pat x_pat = NOpat, PrintFormats x_print_formats = nil_1_, TyOpt x_opt = OPTnone, TyQual x_qual = QUALnone, Exp x_view_predicate = NOexp)
{
  return new a_TermDef (x_id, x_ty, x_decls, x_inherits, x_pat, x_print_formats, x_opt, x_qual, x_view_predicate);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for TermDef
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ViewDef::VIEWdef
//
///////////////////////////////////////////////////////////////////////////////
class a_ViewDef : public Loc {
public:
#line 346 "../../prop-src/ast.ph"
  Pat _1; Exp _2; a_List<LabExp> *  _3; 
  inline a_ViewDef (Pat x_1, Exp x_2, a_List<LabExp> *  x_3)
   : _1(x_1), _2(x_2), _3(x_3)
  {
  }
};
inline int boxed(const a_ViewDef *) { return 1; }
inline int untag(const a_ViewDef *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for ViewDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_ViewDef * VIEWdef (Pat x_1, Exp x_2, a_List<LabExp> *  x_3)
{
  return new a_ViewDef (x_1, x_2, x_3);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for ViewDef
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor LawDef::LAWdef
//
///////////////////////////////////////////////////////////////////////////////
class a_LawDef : public Loc {
public:
#line 354 "../../prop-src/ast.ph"
  Id id; Ids args; Exp guard; Pat pat; Bool invert; Ty ty; 
  inline a_LawDef (Id x_id, Ids x_args, Exp x_guard, Pat x_pat, Bool x_invert, Ty x_ty = NOty)
   : id(x_id), args(x_args), guard(x_guard), pat(x_pat), invert(x_invert), ty(x_ty)
  {
  }
};
inline int boxed(const a_LawDef *) { return 1; }
inline int untag(const a_LawDef *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for LawDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_LawDef * LAWdef (Id x_id, Ids x_args, Exp x_guard, Pat x_pat, Bool x_invert, Ty x_ty = NOty)
{
  return new a_LawDef (x_id, x_args, x_guard, x_pat, x_invert, x_ty);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for LawDef
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TyDef::TYdef
//
///////////////////////////////////////////////////////////////////////////////
class a_TyDef : public Loc {
public:
#line 371 "../../prop-src/ast.ph"
  Id _1; TyVars _2; Ty _3; Bool _4; 
  inline a_TyDef (Id x_1, TyVars x_2, Ty x_3, Bool x_4)
   : _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};
inline int boxed(const a_TyDef *) { return 1; }
inline int untag(const a_TyDef *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for TyDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_TyDef * TYdef (Id x_1, TyVars x_2, Ty x_3, Bool x_4)
{
  return new a_TyDef (x_1, x_2, x_3, x_4);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for TyDef
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor FunDef::FUNdef
//
///////////////////////////////////////////////////////////////////////////////
class a_FunDef : public Loc {
public:
#line 379 "../../prop-src/ast.ph"
  QualId _1; Ty _2; Ty _3; MatchRules _4; 
  inline a_FunDef (QualId x_1, Ty x_2, Ty x_3, MatchRules x_4)
   : _1(x_1), _2(x_2), _3(x_3), _4(x_4)
  {
  }
};
inline int boxed(const a_FunDef *) { return 1; }
inline int untag(const a_FunDef *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for FunDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_FunDef * FUNdef (QualId x_1, Ty x_2, Ty x_3, MatchRules x_4)
{
  return new a_FunDef (x_1, x_2, x_3, x_4);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for FunDef
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype QualId
//
///////////////////////////////////////////////////////////////////////////////
class a_QualId : public MEM {
public:
  enum Tag_QualId {
    tag_NESTEDid = 0, tag_SIMPLEid = 1
  };

public:
  const Tag_QualId tag__; // variant tag
protected:
  inline a_QualId(Tag_QualId t__) : tag__(t__) {}
public:
};
inline int boxed(const a_QualId *) { return 1; }
inline int untag(const a_QualId * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor QualId::NESTEDid
//
///////////////////////////////////////////////////////////////////////////////
class QualId_NESTEDid : public a_QualId {
public:
#line 387 "../../prop-src/ast.ph"
  Ty _1; QualId _2; 
  inline QualId_NESTEDid (Ty x_1, QualId x_2)
   : a_QualId(tag_NESTEDid), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor QualId::SIMPLEid
//
///////////////////////////////////////////////////////////////////////////////
class QualId_SIMPLEid : public a_QualId {
public:
#line 388 "../../prop-src/ast.ph"
  Id SIMPLEid; 
  inline QualId_SIMPLEid (Id x_SIMPLEid)
   : a_QualId(tag_SIMPLEid), SIMPLEid(x_SIMPLEid)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for QualId
//
///////////////////////////////////////////////////////////////////////////////
inline a_QualId * NESTEDid (Ty x_1, QualId x_2)
{
  return new QualId_NESTEDid (x_1, x_2);
}
inline a_QualId * SIMPLEid (Id x_SIMPLEid)
{
  return new QualId_SIMPLEid (x_SIMPLEid);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for QualId
//
///////////////////////////////////////////////////////////////////////////////
inline QualId_NESTEDid * _NESTEDid(const a_QualId * _x_) { return (QualId_NESTEDid *)_x_; }
inline QualId_SIMPLEid * _SIMPLEid(const a_QualId * _x_) { return (QualId_SIMPLEid *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor InferenceRule::INFERENCErule
//
///////////////////////////////////////////////////////////////////////////////
class a_InferenceRule : public Loc {
public:
#line 396 "../../prop-src/ast.ph"
  MatchRules _1; Exp _2; Conclusions _3; 
  inline a_InferenceRule (MatchRules x_1, Exp x_2, Conclusions x_3)
   : _1(x_1), _2(x_2), _3(x_3)
  {
  }
};
inline int boxed(const a_InferenceRule *) { return 1; }
inline int untag(const a_InferenceRule *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for InferenceRule
//
///////////////////////////////////////////////////////////////////////////////
inline a_InferenceRule * INFERENCErule (MatchRules x_1, Exp x_2, Conclusions x_3)
{
  return new a_InferenceRule (x_1, x_2, x_3);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for InferenceRule
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Conclusion
//
///////////////////////////////////////////////////////////////////////////////
class a_Conclusion : public Loc {
public:
  enum Tag_Conclusion {
    tag_ASSERTaction = 0, tag_RETRACTaction = 1, tag_STMTaction = 2
  };

public:
  const Tag_Conclusion tag__; // variant tag
protected:
  inline a_Conclusion(Tag_Conclusion t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Conclusion *) { return 1; }
inline int untag(const a_Conclusion * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Conclusion::ASSERTaction
//
///////////////////////////////////////////////////////////////////////////////
class Conclusion_ASSERTaction : public a_Conclusion {
public:
#line 399 "../../prop-src/ast.ph"
  Exp ASSERTaction; 
  inline Conclusion_ASSERTaction (Exp x_ASSERTaction)
   : a_Conclusion(tag_ASSERTaction), ASSERTaction(x_ASSERTaction)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Conclusion::RETRACTaction
//
///////////////////////////////////////////////////////////////////////////////
class Conclusion_RETRACTaction : public a_Conclusion {
public:
#line 400 "../../prop-src/ast.ph"
  Exp RETRACTaction; 
  inline Conclusion_RETRACTaction (Exp x_RETRACTaction)
   : a_Conclusion(tag_RETRACTaction), RETRACTaction(x_RETRACTaction)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Conclusion::STMTaction
//
///////////////////////////////////////////////////////////////////////////////
class Conclusion_STMTaction : public a_Conclusion {
public:
#line 401 "../../prop-src/ast.ph"
  Decls STMTaction; 
  inline Conclusion_STMTaction (Decls x_STMTaction)
   : a_Conclusion(tag_STMTaction), STMTaction(x_STMTaction)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Conclusion
//
///////////////////////////////////////////////////////////////////////////////
inline a_Conclusion * ASSERTaction (Exp x_ASSERTaction)
{
  return new Conclusion_ASSERTaction (x_ASSERTaction);
}
inline a_Conclusion * RETRACTaction (Exp x_RETRACTaction)
{
  return new Conclusion_RETRACTaction (x_RETRACTaction);
}
inline a_Conclusion * STMTaction (Decls x_STMTaction)
{
  return new Conclusion_STMTaction (x_STMTaction);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Conclusion
//
///////////////////////////////////////////////////////////////////////////////
inline Conclusion_ASSERTaction * _ASSERTaction(const a_Conclusion * _x_) { return (Conclusion_ASSERTaction *)_x_; }
inline Conclusion_RETRACTaction * _RETRACTaction(const a_Conclusion * _x_) { return (Conclusion_RETRACTaction *)_x_; }
inline Conclusion_STMTaction * _STMTaction(const a_Conclusion * _x_) { return (Conclusion_STMTaction *)_x_; }

#line 433 "../../prop-src/ast.ph"
#line 433 "../../prop-src/ast.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  AST manipulation methods.
//
///////////////////////////////////////////////////////////////////////////////

extern Exp component_exp(Exps, int);
extern Exp component_exp(Exps, Id);
extern Exp component_exp(LabExps, Id);

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, Exp);
extern std::ostream& operator << (std::ostream&, 
#line 452 "../../prop-src/ast.ph"
a_List<Exp> *  
#line 452 "../../prop-src/ast.ph"
);
extern std::ostream& operator << (std::ostream&, LabExp);
extern std::ostream& operator << (std::ostream&, a_List<LabExp> *  
#line 454 "../../prop-src/ast.ph"
);
extern std::ostream& operator << (std::ostream&, Cost);
extern std::ostream& operator << (std::ostream&, MatchRule);
extern std::ostream& operator << (std::ostream&, QualId);

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
