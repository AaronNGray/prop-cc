///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\constraint.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/constraint.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the interface of the constraint compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef constraint_compiler_h
#define constraint_compiler_h

#include "basics.h"
#include "codegen.h"
#include "matchcom.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward datatype declarations
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/constraint.ph"
#line 28 "../../prop-src/constraint.ph"
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
// Forward class definition for Instness
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Instness_defined
#define datatype_Instness_defined
  class a_Instness;
  typedef a_Instness * Instness;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Determinism
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Determinism_defined
#define datatype_Determinism_defined
  class a_Determinism;
  typedef a_Determinism * Determinism;
#endif

#line 28 "../../prop-src/constraint.ph"
#line 28 "../../prop-src/constraint.ph"


class HashTable;

///////////////////////////////////////////////////////////////////////////////
//
//  The grammar of the constraint rules is defined as follows:
//
///////////////////////////////////////////////////////////////////////////////

#line 38 "../../prop-src/constraint.ph"
#line 66 "../../prop-src/constraint.ph"
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
// Forward class definition for ConstraintDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_ConstraintDef_defined
#define datatype_ConstraintDef_defined
  class a_ConstraintDef;
  typedef a_ConstraintDef * ConstraintDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for ConstraintRule
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_ConstraintRule_defined
#define datatype_ConstraintRule_defined
  class a_ConstraintRule;
  typedef a_ConstraintRule * ConstraintRule;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for ConstraintBody
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_ConstraintBody_defined
#define datatype_ConstraintBody_defined
  class a_ConstraintBody;
  typedef a_ConstraintBody * ConstraintBody;
#endif

#  define CONSTRAINTnone 0
#  define CONSTRAINTcut 1

///////////////////////////////////////////////////////////////////////////////
// Definition of type ConstraintDefs
///////////////////////////////////////////////////////////////////////////////
#line 64 "../../prop-src/constraint.ph"
typedef a_List<ConstraintDef> *  ConstraintDefs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type ConstraintRules
///////////////////////////////////////////////////////////////////////////////
#line 65 "../../prop-src/constraint.ph"
typedef a_List<ConstraintRule> *  ConstraintRules;

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintSet::CONSTRAINTset
//
///////////////////////////////////////////////////////////////////////////////
class a_ConstraintSet : public Loc {
public:
#line 38 "../../prop-src/constraint.ph"
  ConstraintDefs CONSTRAINTset; 
  inline a_ConstraintSet (ConstraintDefs x_CONSTRAINTset)
   : CONSTRAINTset(x_CONSTRAINTset)
  {
  }
};
inline int boxed(const a_ConstraintSet *) { return 1; }
inline int untag(const a_ConstraintSet *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for ConstraintSet
//
///////////////////////////////////////////////////////////////////////////////
inline a_ConstraintSet * CONSTRAINTset (ConstraintDefs x_CONSTRAINTset)
{
  return new a_ConstraintSet (x_CONSTRAINTset);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for ConstraintSet
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype ConstraintDef
//
///////////////////////////////////////////////////////////////////////////////
class a_ConstraintDef : public Loc {
public:
  enum Tag_ConstraintDef {
    tag_CONSTRAINTruledef = 0, tag_CONSTRAINTtype = 1, tag_CONSTRAINTinstness = 2, 
    tag_CONSTRAINTdet = 3
  };

public:
  const Tag_ConstraintDef tag__; // variant tag
protected:
  inline a_ConstraintDef(Tag_ConstraintDef t__) : tag__(t__) {}
public:
};
inline int boxed(const a_ConstraintDef *) { return 1; }
inline int untag(const a_ConstraintDef * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintDef::CONSTRAINTruledef
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintDef_CONSTRAINTruledef : public a_ConstraintDef {
public:
#line 41 "../../prop-src/constraint.ph"
  ConstraintRule CONSTRAINTruledef; 
  inline ConstraintDef_CONSTRAINTruledef (ConstraintRule x_CONSTRAINTruledef)
   : a_ConstraintDef(tag_CONSTRAINTruledef), CONSTRAINTruledef(x_CONSTRAINTruledef)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintDef::CONSTRAINTtype
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintDef_CONSTRAINTtype : public a_ConstraintDef {
public:
#line 43 "../../prop-src/constraint.ph"
  Id _1; Ty _2; 
  inline ConstraintDef_CONSTRAINTtype (Id x_1, Ty x_2)
   : a_ConstraintDef(tag_CONSTRAINTtype), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintDef::CONSTRAINTinstness
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintDef_CONSTRAINTinstness : public a_ConstraintDef {
public:
#line 44 "../../prop-src/constraint.ph"
  Id _1; Pat _2; 
  inline ConstraintDef_CONSTRAINTinstness (Id x_1, Pat x_2)
   : a_ConstraintDef(tag_CONSTRAINTinstness), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintDef::CONSTRAINTdet
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintDef_CONSTRAINTdet : public a_ConstraintDef {
public:
#line 45 "../../prop-src/constraint.ph"
  Id _1; Pats _2; Determinism _3; 
  inline ConstraintDef_CONSTRAINTdet (Id x_1, Pats x_2, Determinism x_3)
   : a_ConstraintDef(tag_CONSTRAINTdet), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for ConstraintDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_ConstraintDef * CONSTRAINTruledef (ConstraintRule x_CONSTRAINTruledef)
{
  return new ConstraintDef_CONSTRAINTruledef (x_CONSTRAINTruledef);
}
inline a_ConstraintDef * CONSTRAINTtype (Id x_1, Ty x_2)
{
  return new ConstraintDef_CONSTRAINTtype (x_1, x_2);
}
inline a_ConstraintDef * CONSTRAINTinstness (Id x_1, Pat x_2)
{
  return new ConstraintDef_CONSTRAINTinstness (x_1, x_2);
}
inline a_ConstraintDef * CONSTRAINTdet (Id x_1, Pats x_2, Determinism x_3)
{
  return new ConstraintDef_CONSTRAINTdet (x_1, x_2, x_3);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for ConstraintDef
//
///////////////////////////////////////////////////////////////////////////////
inline ConstraintDef_CONSTRAINTruledef * _CONSTRAINTruledef(const a_ConstraintDef * _x_) { return (ConstraintDef_CONSTRAINTruledef *)_x_; }
inline ConstraintDef_CONSTRAINTtype * _CONSTRAINTtype(const a_ConstraintDef * _x_) { return (ConstraintDef_CONSTRAINTtype *)_x_; }
inline ConstraintDef_CONSTRAINTinstness * _CONSTRAINTinstness(const a_ConstraintDef * _x_) { return (ConstraintDef_CONSTRAINTinstness *)_x_; }
inline ConstraintDef_CONSTRAINTdet * _CONSTRAINTdet(const a_ConstraintDef * _x_) { return (ConstraintDef_CONSTRAINTdet *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintRule::CONSTRAINTrule
//
///////////////////////////////////////////////////////////////////////////////
class a_ConstraintRule : public Loc {
public:
#line 47 "../../prop-src/constraint.ph"
  Id id; Pat pat; ConstraintBody body; Ty ty; 
  inline a_ConstraintRule (Id x_id, Pat x_pat, ConstraintBody x_body, Ty x_ty = NOty)
   : id(x_id), pat(x_pat), body(x_body), ty(x_ty)
  {
  }
};
inline int boxed(const a_ConstraintRule *) { return 1; }
inline int untag(const a_ConstraintRule *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for ConstraintRule
//
///////////////////////////////////////////////////////////////////////////////
inline a_ConstraintRule * CONSTRAINTrule (Id x_id, Pat x_pat, ConstraintBody x_body, Ty x_ty = NOty)
{
  return new a_ConstraintRule (x_id, x_pat, x_body, x_ty);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for ConstraintRule
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype ConstraintBody
//
///////////////////////////////////////////////////////////////////////////////
class a_ConstraintBody : public Loc {
public:
  enum Tag_ConstraintBody {
    tag_CONSTRAINTand = 0, tag_CONSTRAINTif = 1, tag_CONSTRAINTbody = 2, 
    tag_CONSTRAINTcall = 3
  };

public:
  const Tag_ConstraintBody tag__; // variant tag
protected:
  inline a_ConstraintBody(Tag_ConstraintBody t__) : tag__(t__) {}
public:
};
inline int boxed(const a_ConstraintBody * x) { return (unsigned long)x >= 2; }
inline int untag(const a_ConstraintBody * x) { return boxed(x) ? x->tag__ + 2 : (int)x; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintBody::CONSTRAINTand
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintBody_CONSTRAINTand : public a_ConstraintBody {
public:
#line 59 "../../prop-src/constraint.ph"
  ConstraintBody _1; ConstraintBody _2; 
  inline ConstraintBody_CONSTRAINTand (ConstraintBody x_1, ConstraintBody x_2)
   : a_ConstraintBody(tag_CONSTRAINTand), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintBody::CONSTRAINTif
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintBody_CONSTRAINTif : public a_ConstraintBody {
public:
#line 60 "../../prop-src/constraint.ph"
  ConstraintBody _1; ConstraintBody _2; ConstraintBody _3; 
  inline ConstraintBody_CONSTRAINTif (ConstraintBody x_1, ConstraintBody x_2, ConstraintBody x_3)
   : a_ConstraintBody(tag_CONSTRAINTif), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintBody::CONSTRAINTbody
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintBody_CONSTRAINTbody : public a_ConstraintBody {
public:
#line 61 "../../prop-src/constraint.ph"
  a_List<Decl> *  CONSTRAINTbody; 
  inline ConstraintBody_CONSTRAINTbody (a_List<Decl> *  x_CONSTRAINTbody)
   : a_ConstraintBody(tag_CONSTRAINTbody), CONSTRAINTbody(x_CONSTRAINTbody)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor ConstraintBody::CONSTRAINTcall
//
///////////////////////////////////////////////////////////////////////////////
class ConstraintBody_CONSTRAINTcall : public a_ConstraintBody {
public:
#line 62 "../../prop-src/constraint.ph"
  Exp CONSTRAINTcall; 
  inline ConstraintBody_CONSTRAINTcall (Exp x_CONSTRAINTcall)
   : a_ConstraintBody(tag_CONSTRAINTcall), CONSTRAINTcall(x_CONSTRAINTcall)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for ConstraintBody
//
///////////////////////////////////////////////////////////////////////////////
inline a_ConstraintBody * CONSTRAINTand (ConstraintBody x_1, ConstraintBody x_2)
{
  return new ConstraintBody_CONSTRAINTand (x_1, x_2);
}
inline a_ConstraintBody * CONSTRAINTif (ConstraintBody x_1, ConstraintBody x_2, ConstraintBody x_3)
{
  return new ConstraintBody_CONSTRAINTif (x_1, x_2, x_3);
}
inline a_ConstraintBody * CONSTRAINTbody (a_List<Decl> *  x_CONSTRAINTbody)
{
  return new ConstraintBody_CONSTRAINTbody (x_CONSTRAINTbody);
}
inline a_ConstraintBody * CONSTRAINTcall (Exp x_CONSTRAINTcall)
{
  return new ConstraintBody_CONSTRAINTcall (x_CONSTRAINTcall);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for ConstraintBody
//
///////////////////////////////////////////////////////////////////////////////
inline ConstraintBody_CONSTRAINTand * _CONSTRAINTand(const a_ConstraintBody * _x_) { return (ConstraintBody_CONSTRAINTand *)_x_; }
inline ConstraintBody_CONSTRAINTif * _CONSTRAINTif(const a_ConstraintBody * _x_) { return (ConstraintBody_CONSTRAINTif *)_x_; }
inline ConstraintBody_CONSTRAINTbody * _CONSTRAINTbody(const a_ConstraintBody * _x_) { return (ConstraintBody_CONSTRAINTbody *)_x_; }
inline ConstraintBody_CONSTRAINTcall * _CONSTRAINTcall(const a_ConstraintBody * _x_) { return (ConstraintBody_CONSTRAINTcall *)_x_; }

#line 66 "../../prop-src/constraint.ph"
#line 66 "../../prop-src/constraint.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing routines.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, ConstraintSet);
extern std::ostream& operator << (std::ostream&, ConstraintDef);
extern std::ostream& operator << (std::ostream&, ConstraintDefs);
extern std::ostream& operator << (std::ostream&, ConstraintRule);
extern std::ostream& operator << (std::ostream&, ConstraintRules);
extern std::ostream& operator << (std::ostream&, ConstraintBody);

///////////////////////////////////////////////////////////////////////////////
//
//  Forward declaration.
//
///////////////////////////////////////////////////////////////////////////////

class ConstraintCompilerInternal;

///////////////////////////////////////////////////////////////////////////////
//
//  The constraint compiler is inherited from the code generator.
//
///////////////////////////////////////////////////////////////////////////////

class ConstraintCompiler : virtual public CodeGen,
                           virtual public MatchCompiler
{
  ConstraintCompiler(const ConstraintCompiler&); // no copy constructor
  void operator = (const ConstraintCompiler&);   // no assignment

protected:

  ConstraintCompilerInternal * internal;  // internal implementation

public:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor and destructor
  //
  ////////////////////////////////////////////////////////////////////////////
           ConstraintCompiler();
  virtual ~ConstraintCompiler();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods for compiling a set of constraint rules.
  //
  ////////////////////////////////////////////////////////////////////////////
  void compile_ruleset( Id class_name, ConstraintSet rule_set);

private:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Private implementation methods.
  //
  ////////////////////////////////////////////////////////////////////////////
  void process_typing_rules( Id, 
#line 127 "../../prop-src/constraint.ph"
a_List<Tuple2<Id, Ty> > *  
#line 127 "../../prop-src/constraint.ph"
);
  void process_ruleset( Id, ConstraintRules);
  void add_predicate_type( Id, Ty);
  void analyze_rule( ConstraintBody);
};


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
