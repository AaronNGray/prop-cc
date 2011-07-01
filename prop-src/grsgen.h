///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\grsgen.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/grsgen.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the graph rewriting system compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef graph_rewriting_system_compiler_h
#define graph_rewriting_system_compiler_h

#include "basics.h"
#include "codegen.h"
#include "matchcom.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward type declarations
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/grsgen.ph"
#line 20 "../../prop-src/grsgen.ph"
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

#line 20 "../../prop-src/grsgen.ph"
#line 20 "../../prop-src/grsgen.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Abstract syntax for graph rewriting rules
//
///////////////////////////////////////////////////////////////////////////////

#line 28 "../../prop-src/grsgen.ph"
#line 52 "../../prop-src/grsgen.ph"
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

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for GRSPat
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_GRSPat_defined
#define datatype_GRSPat_defined
  class a_GRSPat;
  typedef a_GRSPat * GRSPat;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for GRSConclusion
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_GRSConclusion_defined
#define datatype_GRSConclusion_defined
  class a_GRSConclusion;
  typedef a_GRSConclusion * GRSConclusion;
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type GRSConclusions
///////////////////////////////////////////////////////////////////////////////
#line 51 "../../prop-src/grsgen.ph"
typedef a_List<GRSConclusion> *  GRSConclusions;

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GraphRewritingRule::GRSrule
//
///////////////////////////////////////////////////////////////////////////////
class a_GraphRewritingRule : public Loc {
public:
#line 29 "../../prop-src/grsgen.ph"
  GRSPat lhs; GRSConclusions rhs; 
  inline a_GraphRewritingRule (GRSPat x_lhs, GRSConclusions x_rhs)
   : lhs(x_lhs), rhs(x_rhs)
  {
  }
};
inline int boxed(const a_GraphRewritingRule *) { return 1; }
inline int untag(const a_GraphRewritingRule *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for GraphRewritingRule
//
///////////////////////////////////////////////////////////////////////////////
inline a_GraphRewritingRule * GRSrule (GRSPat x_lhs, GRSConclusions x_rhs)
{
  return new a_GraphRewritingRule (x_lhs, x_rhs);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for GraphRewritingRule
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype GRSPat
//
///////////////////////////////////////////////////////////////////////////////
class a_GRSPat : public Loc {
public:
  enum Tag_GRSPat {
    tag_EDGEgpat = 0, tag_GUARDgpat = 1, tag_NOTgpat = 2, 
    tag_ANDgpat = 3, tag_ORgpat = 4, tag_FORALLgpat = 5
  };

public:
  const Tag_GRSPat tag__; // variant tag
protected:
  inline a_GRSPat(Tag_GRSPat t__) : tag__(t__) {}
public:
};
inline int boxed(const a_GRSPat *) { return 1; }
inline int untag(const a_GRSPat * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSPat::EDGEgpat
//
///////////////////////////////////////////////////////////////////////////////
class GRSPat_EDGEgpat : public a_GRSPat {
public:
#line 36 "../../prop-src/grsgen.ph"
  Id _1; a_List<Pat> *  _2; 
  inline GRSPat_EDGEgpat (Id x_1, a_List<Pat> *  x_2)
   : a_GRSPat(tag_EDGEgpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSPat::GUARDgpat
//
///////////////////////////////////////////////////////////////////////////////
class GRSPat_GUARDgpat : public a_GRSPat {
public:
#line 38 "../../prop-src/grsgen.ph"
  Exp GUARDgpat; 
  inline GRSPat_GUARDgpat (Exp x_GUARDgpat)
   : a_GRSPat(tag_GUARDgpat), GUARDgpat(x_GUARDgpat)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSPat::NOTgpat
//
///////////////////////////////////////////////////////////////////////////////
class GRSPat_NOTgpat : public a_GRSPat {
public:
#line 39 "../../prop-src/grsgen.ph"
  GRSPat NOTgpat; 
  inline GRSPat_NOTgpat (GRSPat x_NOTgpat)
   : a_GRSPat(tag_NOTgpat), NOTgpat(x_NOTgpat)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSPat::ANDgpat
//
///////////////////////////////////////////////////////////////////////////////
class GRSPat_ANDgpat : public a_GRSPat {
public:
#line 40 "../../prop-src/grsgen.ph"
  GRSPat _1; GRSPat _2; 
  inline GRSPat_ANDgpat (GRSPat x_1, GRSPat x_2)
   : a_GRSPat(tag_ANDgpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSPat::ORgpat
//
///////////////////////////////////////////////////////////////////////////////
class GRSPat_ORgpat : public a_GRSPat {
public:
#line 41 "../../prop-src/grsgen.ph"
  GRSPat _1; GRSPat _2; 
  inline GRSPat_ORgpat (GRSPat x_1, GRSPat x_2)
   : a_GRSPat(tag_ORgpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSPat::FORALLgpat
//
///////////////////////////////////////////////////////////////////////////////
class GRSPat_FORALLgpat : public a_GRSPat {
public:
#line 42 "../../prop-src/grsgen.ph"
  Id _1; GRSPat _2; 
  inline GRSPat_FORALLgpat (Id x_1, GRSPat x_2)
   : a_GRSPat(tag_FORALLgpat), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for GRSPat
//
///////////////////////////////////////////////////////////////////////////////
inline a_GRSPat * EDGEgpat (Id x_1, a_List<Pat> *  x_2)
{
  return new GRSPat_EDGEgpat (x_1, x_2);
}
inline a_GRSPat * GUARDgpat (Exp x_GUARDgpat)
{
  return new GRSPat_GUARDgpat (x_GUARDgpat);
}
inline a_GRSPat * NOTgpat (GRSPat x_NOTgpat)
{
  return new GRSPat_NOTgpat (x_NOTgpat);
}
inline a_GRSPat * ANDgpat (GRSPat x_1, GRSPat x_2)
{
  return new GRSPat_ANDgpat (x_1, x_2);
}
inline a_GRSPat * ORgpat (GRSPat x_1, GRSPat x_2)
{
  return new GRSPat_ORgpat (x_1, x_2);
}
inline a_GRSPat * FORALLgpat (Id x_1, GRSPat x_2)
{
  return new GRSPat_FORALLgpat (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for GRSPat
//
///////////////////////////////////////////////////////////////////////////////
inline GRSPat_EDGEgpat * _EDGEgpat(const a_GRSPat * _x_) { return (GRSPat_EDGEgpat *)_x_; }
inline GRSPat_GUARDgpat * _GUARDgpat(const a_GRSPat * _x_) { return (GRSPat_GUARDgpat *)_x_; }
inline GRSPat_NOTgpat * _NOTgpat(const a_GRSPat * _x_) { return (GRSPat_NOTgpat *)_x_; }
inline GRSPat_ANDgpat * _ANDgpat(const a_GRSPat * _x_) { return (GRSPat_ANDgpat *)_x_; }
inline GRSPat_ORgpat * _ORgpat(const a_GRSPat * _x_) { return (GRSPat_ORgpat *)_x_; }
inline GRSPat_FORALLgpat * _FORALLgpat(const a_GRSPat * _x_) { return (GRSPat_FORALLgpat *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype GRSConclusion
//
///////////////////////////////////////////////////////////////////////////////
class a_GRSConclusion : public Loc {
public:
  enum Tag_GRSConclusion {
    tag_ADDEDGEaction = 0, tag_DELETEEDGEaction = 1, tag_ADDNODEaction = 2, 
    tag_DELETENODEaction = 3, tag_EMBEDDEDaction = 4
  };

public:
  const Tag_GRSConclusion tag__; // variant tag
protected:
  inline a_GRSConclusion(Tag_GRSConclusion t__) : tag__(t__) {}
public:
};
inline int boxed(const a_GRSConclusion *) { return 1; }
inline int untag(const a_GRSConclusion * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSConclusion::ADDEDGEaction
//
///////////////////////////////////////////////////////////////////////////////
class GRSConclusion_ADDEDGEaction : public a_GRSConclusion {
public:
#line 44 "../../prop-src/grsgen.ph"
  Id _1; a_List<Exp> *  _2; 
  inline GRSConclusion_ADDEDGEaction (Id x_1, a_List<Exp> *  x_2)
   : a_GRSConclusion(tag_ADDEDGEaction), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSConclusion::DELETEEDGEaction
//
///////////////////////////////////////////////////////////////////////////////
class GRSConclusion_DELETEEDGEaction : public a_GRSConclusion {
public:
#line 46 "../../prop-src/grsgen.ph"
  Id _1; a_List<Exp> *  _2; 
  inline GRSConclusion_DELETEEDGEaction (Id x_1, a_List<Exp> *  x_2)
   : a_GRSConclusion(tag_DELETEEDGEaction), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSConclusion::ADDNODEaction
//
///////////////////////////////////////////////////////////////////////////////
class GRSConclusion_ADDNODEaction : public a_GRSConclusion {
public:
#line 47 "../../prop-src/grsgen.ph"
  Exp ADDNODEaction; 
  inline GRSConclusion_ADDNODEaction (Exp x_ADDNODEaction)
   : a_GRSConclusion(tag_ADDNODEaction), ADDNODEaction(x_ADDNODEaction)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSConclusion::DELETENODEaction
//
///////////////////////////////////////////////////////////////////////////////
class GRSConclusion_DELETENODEaction : public a_GRSConclusion {
public:
#line 48 "../../prop-src/grsgen.ph"
  Exp DELETENODEaction; 
  inline GRSConclusion_DELETENODEaction (Exp x_DELETENODEaction)
   : a_GRSConclusion(tag_DELETENODEaction), DELETENODEaction(x_DELETENODEaction)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor GRSConclusion::EMBEDDEDaction
//
///////////////////////////////////////////////////////////////////////////////
class GRSConclusion_EMBEDDEDaction : public a_GRSConclusion {
public:
#line 49 "../../prop-src/grsgen.ph"
  a_List<Decl> *  EMBEDDEDaction; 
  inline GRSConclusion_EMBEDDEDaction (a_List<Decl> *  x_EMBEDDEDaction)
   : a_GRSConclusion(tag_EMBEDDEDaction), EMBEDDEDaction(x_EMBEDDEDaction)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for GRSConclusion
//
///////////////////////////////////////////////////////////////////////////////
inline a_GRSConclusion * ADDEDGEaction (Id x_1, a_List<Exp> *  x_2)
{
  return new GRSConclusion_ADDEDGEaction (x_1, x_2);
}
inline a_GRSConclusion * DELETEEDGEaction (Id x_1, a_List<Exp> *  x_2)
{
  return new GRSConclusion_DELETEEDGEaction (x_1, x_2);
}
inline a_GRSConclusion * ADDNODEaction (Exp x_ADDNODEaction)
{
  return new GRSConclusion_ADDNODEaction (x_ADDNODEaction);
}
inline a_GRSConclusion * DELETENODEaction (Exp x_DELETENODEaction)
{
  return new GRSConclusion_DELETENODEaction (x_DELETENODEaction);
}
inline a_GRSConclusion * EMBEDDEDaction (a_List<Decl> *  x_EMBEDDEDaction)
{
  return new GRSConclusion_EMBEDDEDaction (x_EMBEDDEDaction);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for GRSConclusion
//
///////////////////////////////////////////////////////////////////////////////
inline GRSConclusion_ADDEDGEaction * _ADDEDGEaction(const a_GRSConclusion * _x_) { return (GRSConclusion_ADDEDGEaction *)_x_; }
inline GRSConclusion_DELETEEDGEaction * _DELETEEDGEaction(const a_GRSConclusion * _x_) { return (GRSConclusion_DELETEEDGEaction *)_x_; }
inline GRSConclusion_ADDNODEaction * _ADDNODEaction(const a_GRSConclusion * _x_) { return (GRSConclusion_ADDNODEaction *)_x_; }
inline GRSConclusion_DELETENODEaction * _DELETENODEaction(const a_GRSConclusion * _x_) { return (GRSConclusion_DELETENODEaction *)_x_; }
inline GRSConclusion_EMBEDDEDaction * _EMBEDDEDaction(const a_GRSConclusion * _x_) { return (GRSConclusion_EMBEDDEDaction *)_x_; }

#line 52 "../../prop-src/grsgen.ph"
#line 52 "../../prop-src/grsgen.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  The interface to the graph rewriting system compiler
//
///////////////////////////////////////////////////////////////////////////////

class GraphRewritingCompiler : virtual public CodeGen,
                               virtual public MatchCompiler
{
  GraphRewritingCompiler(const GraphRewritingCompiler&);
  void operator = (const GraphRewritingCompiler&);
public:
  GraphRewritingCompiler();
  ~GraphRewritingCompiler();

  void gen_graph_rewriting_system (Id, LabTys, 
#line 69 "../../prop-src/grsgen.ph"
a_List<GraphRewritingRule> *  
#line 69 "../../prop-src/grsgen.ph"
);
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
