///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\dataflow.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/dataflow.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the interface of the dataflow analyzer generator.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef dataflow_analyzer_generator_h
#define dataflow_analyzer_generator_h

#include "basics.h"
#include "codegen.h"
#include "classdef.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward type definitions
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/dataflow.ph"
#line 20 "../../prop-src/dataflow.ph"
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
// Forward class definition for Exp
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Exp_defined
#define datatype_Exp_defined
  class a_Exp;
  typedef a_Exp * Exp;
#endif

#line 20 "../../prop-src/dataflow.ph"
#line 20 "../../prop-src/dataflow.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Datatype 'Domain' is denotes the structure of an abstract domain.
//
///////////////////////////////////////////////////////////////////////////////

#line 28 "../../prop-src/dataflow.ph"
#line 36 "../../prop-src/dataflow.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Domain
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Domain_defined
#define datatype_Domain_defined
  class a_Domain;
  typedef a_Domain * Domain;
#endif

#  define v_UNITdom 0

#  define UNITdom (Domain)v_UNITdom

///////////////////////////////////////////////////////////////////////////////
// Definition of type Domains
///////////////////////////////////////////////////////////////////////////////
#line 35 "../../prop-src/dataflow.ph"
typedef a_List<Domain> *  Domains;

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Domain
//
///////////////////////////////////////////////////////////////////////////////
class a_Domain : public Loc {
public:
  enum Tag_Domain {
    tag_FINSETdom = 0, tag_LIFTdom = 1, tag_SUMdom = 2, 
    tag_PRODUCTdom = 3
  };

public:
  const Tag_Domain tag__; // variant tag
protected:
  inline a_Domain(Tag_Domain t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Domain * x) { return x != 0; }
inline int untag(const a_Domain * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Domain::FINSETdom
//
///////////////////////////////////////////////////////////////////////////////
class Domain_FINSETdom : public a_Domain {
public:
#line 30 "../../prop-src/dataflow.ph"
  Ty FINSETdom; 
  inline Domain_FINSETdom (Ty x_FINSETdom)
   : a_Domain(tag_FINSETdom), FINSETdom(x_FINSETdom)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Domain::LIFTdom
//
///////////////////////////////////////////////////////////////////////////////
class Domain_LIFTdom : public a_Domain {
public:
#line 31 "../../prop-src/dataflow.ph"
  Domain LIFTdom; 
  inline Domain_LIFTdom (Domain x_LIFTdom)
   : a_Domain(tag_LIFTdom), LIFTdom(x_LIFTdom)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Domain::SUMdom
//
///////////////////////////////////////////////////////////////////////////////
class Domain_SUMdom : public a_Domain {
public:
#line 32 "../../prop-src/dataflow.ph"
  Domains SUMdom; 
  inline Domain_SUMdom (Domains x_SUMdom)
   : a_Domain(tag_SUMdom), SUMdom(x_SUMdom)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Domain::PRODUCTdom
//
///////////////////////////////////////////////////////////////////////////////
class Domain_PRODUCTdom : public a_Domain {
public:
#line 33 "../../prop-src/dataflow.ph"
  Domains PRODUCTdom; 
  inline Domain_PRODUCTdom (Domains x_PRODUCTdom)
   : a_Domain(tag_PRODUCTdom), PRODUCTdom(x_PRODUCTdom)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Domain
//
///////////////////////////////////////////////////////////////////////////////
inline a_Domain * FINSETdom (Ty x_FINSETdom)
{
  return new Domain_FINSETdom (x_FINSETdom);
}
inline a_Domain * LIFTdom (Domain x_LIFTdom)
{
  return new Domain_LIFTdom (x_LIFTdom);
}
inline a_Domain * SUMdom (Domains x_SUMdom)
{
  return new Domain_SUMdom (x_SUMdom);
}
inline a_Domain * PRODUCTdom (Domains x_PRODUCTdom)
{
  return new Domain_PRODUCTdom (x_PRODUCTdom);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Domain
//
///////////////////////////////////////////////////////////////////////////////
inline Domain_FINSETdom * _FINSETdom(const a_Domain * _x_) { return (Domain_FINSETdom *)_x_; }
inline Domain_LIFTdom * _LIFTdom(const a_Domain * _x_) { return (Domain_LIFTdom *)_x_; }
inline Domain_SUMdom * _SUMdom(const a_Domain * _x_) { return (Domain_SUMdom *)_x_; }
inline Domain_PRODUCTdom * _PRODUCTdom(const a_Domain * _x_) { return (Domain_PRODUCTdom *)_x_; }

#line 36 "../../prop-src/dataflow.ph"
#line 36 "../../prop-src/dataflow.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, Domain);

///////////////////////////////////////////////////////////////////////////////
//
//  Dataflow class definitions
//
///////////////////////////////////////////////////////////////////////////////

class DataflowClass : public ClassDefinition
{
  DataflowClass(const DataflowClass&);
  void operator = (const DataflowClass&);
public:
  DataflowClass(Id, Inherits, TyQual, Decls);
  ~DataflowClass();
  virtual void gen_class_interface(CodeGen&);
};

///////////////////////////////////////////////////////////////////////////////
//
//  The interface of the dataflow analyzer compiler.
//
///////////////////////////////////////////////////////////////////////////////

class DataflowCompiler : public virtual CodeGen
{
  DataflowCompiler(const DataflowCompiler&);
  void operator = (const DataflowCompiler&);
public:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor and destructor
  //
  ////////////////////////////////////////////////////////////////////////////
  DataflowCompiler ();
  virtual ~DataflowCompiler ();
};

#endif
#line 83 "../../prop-src/dataflow.ph"
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
