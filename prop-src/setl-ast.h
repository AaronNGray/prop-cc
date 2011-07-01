///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\setl-ast.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/setl-ast.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the abstract syntax tree definitions for the
//  SETL-like extension language of Prop.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef setl_extension_abstract_syntax_tree_h
#define setl_extension_abstract_syntax_tree_h

#include <iostream>
#include "basics.h"
#include "ir.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Forward AST declarations.
//
///////////////////////////////////////////////////////////////////////////////

#line 22 "../../prop-src/setl-ast.ph"
#line 26 "../../prop-src/setl-ast.ph"
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
// Forward class definition for Time
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Time_defined
#define datatype_Time_defined
  class a_Time;
  typedef a_Time * Time;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Space
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Space_defined
#define datatype_Space_defined
  class a_Space;
  typedef a_Space * Space;
#endif

#line 26 "../../prop-src/setl-ast.ph"
#line 26 "../../prop-src/setl-ast.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  AST for definitions, signatures, statements and bindings
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Type 'Def' represents definitions.
//
///////////////////////////////////////////////////////////////////////////////

#line 40 "../../prop-src/setl-ast.ph"
#line 116 "../../prop-src/setl-ast.ph"
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

#  define NOdef 0

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Sig
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Sig_defined
#define datatype_Sig_defined
  class a_Sig;
  typedef a_Sig * Sig;
#endif

#  define NOsig 0

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

#  define NOstmt 0

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabSig
///////////////////////////////////////////////////////////////////////////////
#line 110 "../../prop-src/setl-ast.ph"
typedef struct { Id id; Sig sig;  } LabSig;

///////////////////////////////////////////////////////////////////////////////
// Definition of type LabSigs
///////////////////////////////////////////////////////////////////////////////
#line 111 "../../prop-src/setl-ast.ph"
typedef a_List<LabSig> *  LabSigs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Defs
///////////////////////////////////////////////////////////////////////////////
#line 112 "../../prop-src/setl-ast.ph"
typedef a_List<Def> *  Defs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Sigs
///////////////////////////////////////////////////////////////////////////////
#line 113 "../../prop-src/setl-ast.ph"
typedef a_List<Sig> *  Sigs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Stmts
///////////////////////////////////////////////////////////////////////////////
#line 114 "../../prop-src/setl-ast.ph"
typedef a_List<Stmt> *  Stmts;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Generators
///////////////////////////////////////////////////////////////////////////////
#line 115 "../../prop-src/setl-ast.ph"
typedef a_List<Generator> *  Generators;

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Def
//
///////////////////////////////////////////////////////////////////////////////
class a_Def : public Loc {
public:
  enum Tag_Def {
    tag_VARdef = 0, tag_FUNCTIONdef = 1, tag_MODULEdef = 2, 
    tag_SIGNATUREdef = 3, tag_TYPEdef = 4, tag_LAMBDAdef = 5
  };

public:
  const Tag_Def tag__; // variant tag
protected:
  inline a_Def(Tag_Def t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Def * x) { return x != 0; }
inline int untag(const a_Def * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Def::VARdef
//
///////////////////////////////////////////////////////////////////////////////
class Def_VARdef : public a_Def {
public:
#line 42 "../../prop-src/setl-ast.ph"
  Id id; Ty ty; Exp init_exp; 
  inline Def_VARdef (Id x_id, Ty x_ty, Exp x_init_exp = NOexp)
   : a_Def(tag_VARdef), id(x_id), ty(x_ty), init_exp(x_init_exp)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Def::FUNCTIONdef
//
///////////////////////////////////////////////////////////////////////////////
class Def_FUNCTIONdef : public a_Def {
public:
#line 48 "../../prop-src/setl-ast.ph"
  Id id; LabTys args; Ty return_ty; Defs local_defs; Stmts body; 
  inline Def_FUNCTIONdef (Id x_id, LabTys x_args, Ty x_return_ty, Defs x_local_defs, Stmts x_body)
   : a_Def(tag_FUNCTIONdef), id(x_id), args(x_args), return_ty(x_return_ty), local_defs(x_local_defs), body(x_body)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Def::MODULEdef
//
///////////////////////////////////////////////////////////////////////////////
class Def_MODULEdef : public a_Def {
public:
#line 56 "../../prop-src/setl-ast.ph"
  Id id; LabSigs args; Sig sig; Defs body; 
  inline Def_MODULEdef (Id x_id, LabSigs x_args, Sig x_sig, Defs x_body)
   : a_Def(tag_MODULEdef), id(x_id), args(x_args), sig(x_sig), body(x_body)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Def::SIGNATUREdef
//
///////////////////////////////////////////////////////////////////////////////
class Def_SIGNATUREdef : public a_Def {
public:
#line 63 "../../prop-src/setl-ast.ph"
  Id id; LabSigs args; Sig sig; 
  inline Def_SIGNATUREdef (Id x_id, LabSigs x_args, Sig x_sig)
   : a_Def(tag_SIGNATUREdef), id(x_id), args(x_args), sig(x_sig)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Def::TYPEdef
//
///////////////////////////////////////////////////////////////////////////////
class Def_TYPEdef : public a_Def {
public:
#line 69 "../../prop-src/setl-ast.ph"
  Decl TYPEdef; 
  inline Def_TYPEdef (Decl x_TYPEdef)
   : a_Def(tag_TYPEdef), TYPEdef(x_TYPEdef)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Def::LAMBDAdef
//
///////////////////////////////////////////////////////////////////////////////
class Def_LAMBDAdef : public a_Def {
public:
#line 70 "../../prop-src/setl-ast.ph"
  LabTys _1; Defs _2; 
  inline Def_LAMBDAdef (LabTys x_1, Defs x_2)
   : a_Def(tag_LAMBDAdef), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Def
//
///////////////////////////////////////////////////////////////////////////////
inline a_Def * VARdef (Id x_id, Ty x_ty, Exp x_init_exp = NOexp)
{
  return new Def_VARdef (x_id, x_ty, x_init_exp);
}
inline a_Def * FUNCTIONdef (Id x_id, LabTys x_args, Ty x_return_ty, Defs x_local_defs, Stmts x_body)
{
  return new Def_FUNCTIONdef (x_id, x_args, x_return_ty, x_local_defs, x_body);
}
inline a_Def * MODULEdef (Id x_id, LabSigs x_args, Sig x_sig, Defs x_body)
{
  return new Def_MODULEdef (x_id, x_args, x_sig, x_body);
}
inline a_Def * SIGNATUREdef (Id x_id, LabSigs x_args, Sig x_sig)
{
  return new Def_SIGNATUREdef (x_id, x_args, x_sig);
}
inline a_Def * TYPEdef (Decl x_TYPEdef)
{
  return new Def_TYPEdef (x_TYPEdef);
}
inline a_Def * LAMBDAdef (LabTys x_1, Defs x_2)
{
  return new Def_LAMBDAdef (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Def
//
///////////////////////////////////////////////////////////////////////////////
inline Def_VARdef * _VARdef(const a_Def * _x_) { return (Def_VARdef *)_x_; }
inline Def_FUNCTIONdef * _FUNCTIONdef(const a_Def * _x_) { return (Def_FUNCTIONdef *)_x_; }
inline Def_MODULEdef * _MODULEdef(const a_Def * _x_) { return (Def_MODULEdef *)_x_; }
inline Def_SIGNATUREdef * _SIGNATUREdef(const a_Def * _x_) { return (Def_SIGNATUREdef *)_x_; }
inline Def_TYPEdef * _TYPEdef(const a_Def * _x_) { return (Def_TYPEdef *)_x_; }
inline Def_LAMBDAdef * _LAMBDAdef(const a_Def * _x_) { return (Def_LAMBDAdef *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Sig
//
///////////////////////////////////////////////////////////////////////////////
class a_Sig : public Loc {
public:
  enum Tag_Sig {
    tag_IDsig = 0, tag_DOTsig = 1, tag_APPsig = 2, 
    tag_DEFsig = 3, tag_LAMBDAsig = 4
  };

public:
  const Tag_Sig tag__; // variant tag
protected:
  inline a_Sig(Tag_Sig t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Sig * x) { return x != 0; }
inline int untag(const a_Sig * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Sig::IDsig
//
///////////////////////////////////////////////////////////////////////////////
class Sig_IDsig : public a_Sig {
public:
#line 80 "../../prop-src/setl-ast.ph"
  Id IDsig; 
  inline Sig_IDsig (Id x_IDsig)
   : a_Sig(tag_IDsig), IDsig(x_IDsig)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Sig::DOTsig
//
///////////////////////////////////////////////////////////////////////////////
class Sig_DOTsig : public a_Sig {
public:
#line 81 "../../prop-src/setl-ast.ph"
  Sig _1; Id _2; 
  inline Sig_DOTsig (Sig x_1, Id x_2)
   : a_Sig(tag_DOTsig), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Sig::APPsig
//
///////////////////////////////////////////////////////////////////////////////
class Sig_APPsig : public a_Sig {
public:
#line 82 "../../prop-src/setl-ast.ph"
  Sig _1; Sigs _2; 
  inline Sig_APPsig (Sig x_1, Sigs x_2)
   : a_Sig(tag_APPsig), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Sig::DEFsig
//
///////////////////////////////////////////////////////////////////////////////
class Sig_DEFsig : public a_Sig {
public:
#line 83 "../../prop-src/setl-ast.ph"
  Defs DEFsig; 
  inline Sig_DEFsig (Defs x_DEFsig)
   : a_Sig(tag_DEFsig), DEFsig(x_DEFsig)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Sig::LAMBDAsig
//
///////////////////////////////////////////////////////////////////////////////
class Sig_LAMBDAsig : public a_Sig {
public:
#line 84 "../../prop-src/setl-ast.ph"
  LabSigs _1; Sig _2; 
  inline Sig_LAMBDAsig (LabSigs x_1, Sig x_2)
   : a_Sig(tag_LAMBDAsig), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Sig
//
///////////////////////////////////////////////////////////////////////////////
inline a_Sig * IDsig (Id x_IDsig)
{
  return new Sig_IDsig (x_IDsig);
}
inline a_Sig * DOTsig (Sig x_1, Id x_2)
{
  return new Sig_DOTsig (x_1, x_2);
}
inline a_Sig * APPsig (Sig x_1, Sigs x_2)
{
  return new Sig_APPsig (x_1, x_2);
}
inline a_Sig * DEFsig (Defs x_DEFsig)
{
  return new Sig_DEFsig (x_DEFsig);
}
inline a_Sig * LAMBDAsig (LabSigs x_1, Sig x_2)
{
  return new Sig_LAMBDAsig (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Sig
//
///////////////////////////////////////////////////////////////////////////////
inline Sig_IDsig * _IDsig(const a_Sig * _x_) { return (Sig_IDsig *)_x_; }
inline Sig_DOTsig * _DOTsig(const a_Sig * _x_) { return (Sig_DOTsig *)_x_; }
inline Sig_APPsig * _APPsig(const a_Sig * _x_) { return (Sig_APPsig *)_x_; }
inline Sig_DEFsig * _DEFsig(const a_Sig * _x_) { return (Sig_DEFsig *)_x_; }
inline Sig_LAMBDAsig * _LAMBDAsig(const a_Sig * _x_) { return (Sig_LAMBDAsig *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Stmt
//
///////////////////////////////////////////////////////////////////////////////
class a_Stmt : public Loc {
public:
  enum Tag_Stmt {
    tag_ASSIGNstmt = 0, tag_BLOCKstmt = 1, tag_WHILEstmt = 2, 
    tag_IFstmt = 3, tag_MATCHstmt = 4, tag_REWRITEstmt = 5, 
    tag_REPLACEMENTstmt = 6, tag_FORALLstmt = 7, tag_RETURNstmt = 8
  };

public:
  const Tag_Stmt tag__; // variant tag
protected:
  inline a_Stmt(Tag_Stmt t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Stmt * x) { return x != 0; }
inline int untag(const a_Stmt * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::ASSIGNstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_ASSIGNstmt : public a_Stmt {
public:
#line 94 "../../prop-src/setl-ast.ph"
  Exp _1; Exp _2; 
  inline Stmt_ASSIGNstmt (Exp x_1, Exp x_2)
   : a_Stmt(tag_ASSIGNstmt), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::BLOCKstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_BLOCKstmt : public a_Stmt {
public:
#line 95 "../../prop-src/setl-ast.ph"
  Defs _1; Stmts _2; 
  inline Stmt_BLOCKstmt (Defs x_1, Stmts x_2)
   : a_Stmt(tag_BLOCKstmt), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::WHILEstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_WHILEstmt : public a_Stmt {
public:
#line 96 "../../prop-src/setl-ast.ph"
  Exp _1; Stmt _2; 
  inline Stmt_WHILEstmt (Exp x_1, Stmt x_2)
   : a_Stmt(tag_WHILEstmt), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::IFstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_IFstmt : public a_Stmt {
public:
#line 97 "../../prop-src/setl-ast.ph"
  Exp _1; Stmt _2; Stmt _3; 
  inline Stmt_IFstmt (Exp x_1, Stmt x_2, Stmt x_3)
   : a_Stmt(tag_IFstmt), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::MATCHstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_MATCHstmt : public a_Stmt {
public:
#line 98 "../../prop-src/setl-ast.ph"
  Decl MATCHstmt; 
  inline Stmt_MATCHstmt (Decl x_MATCHstmt)
   : a_Stmt(tag_MATCHstmt), MATCHstmt(x_MATCHstmt)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::REWRITEstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_REWRITEstmt : public a_Stmt {
public:
#line 99 "../../prop-src/setl-ast.ph"
  Decl REWRITEstmt; 
  inline Stmt_REWRITEstmt (Decl x_REWRITEstmt)
   : a_Stmt(tag_REWRITEstmt), REWRITEstmt(x_REWRITEstmt)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::REPLACEMENTstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_REPLACEMENTstmt : public a_Stmt {
public:
#line 100 "../../prop-src/setl-ast.ph"
  Decl REPLACEMENTstmt; 
  inline Stmt_REPLACEMENTstmt (Decl x_REPLACEMENTstmt)
   : a_Stmt(tag_REPLACEMENTstmt), REPLACEMENTstmt(x_REPLACEMENTstmt)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::FORALLstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_FORALLstmt : public a_Stmt {
public:
#line 101 "../../prop-src/setl-ast.ph"
  Generators _1; Stmt _2; 
  inline Stmt_FORALLstmt (Generators x_1, Stmt x_2)
   : a_Stmt(tag_FORALLstmt), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::RETURNstmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_RETURNstmt : public a_Stmt {
public:
#line 102 "../../prop-src/setl-ast.ph"
  Exp RETURNstmt; 
  inline Stmt_RETURNstmt (Exp x_RETURNstmt)
   : a_Stmt(tag_RETURNstmt), RETURNstmt(x_RETURNstmt)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Stmt
//
///////////////////////////////////////////////////////////////////////////////
inline a_Stmt * ASSIGNstmt (Exp x_1, Exp x_2)
{
  return new Stmt_ASSIGNstmt (x_1, x_2);
}
inline a_Stmt * BLOCKstmt (Defs x_1, Stmts x_2)
{
  return new Stmt_BLOCKstmt (x_1, x_2);
}
inline a_Stmt * WHILEstmt (Exp x_1, Stmt x_2)
{
  return new Stmt_WHILEstmt (x_1, x_2);
}
inline a_Stmt * IFstmt (Exp x_1, Stmt x_2, Stmt x_3)
{
  return new Stmt_IFstmt (x_1, x_2, x_3);
}
inline a_Stmt * MATCHstmt (Decl x_MATCHstmt)
{
  return new Stmt_MATCHstmt (x_MATCHstmt);
}
inline a_Stmt * REWRITEstmt (Decl x_REWRITEstmt)
{
  return new Stmt_REWRITEstmt (x_REWRITEstmt);
}
inline a_Stmt * REPLACEMENTstmt (Decl x_REPLACEMENTstmt)
{
  return new Stmt_REPLACEMENTstmt (x_REPLACEMENTstmt);
}
inline a_Stmt * FORALLstmt (Generators x_1, Stmt x_2)
{
  return new Stmt_FORALLstmt (x_1, x_2);
}
inline a_Stmt * RETURNstmt (Exp x_RETURNstmt)
{
  return new Stmt_RETURNstmt (x_RETURNstmt);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Stmt
//
///////////////////////////////////////////////////////////////////////////////
inline Stmt_ASSIGNstmt * _ASSIGNstmt(const a_Stmt * _x_) { return (Stmt_ASSIGNstmt *)_x_; }
inline Stmt_BLOCKstmt * _BLOCKstmt(const a_Stmt * _x_) { return (Stmt_BLOCKstmt *)_x_; }
inline Stmt_WHILEstmt * _WHILEstmt(const a_Stmt * _x_) { return (Stmt_WHILEstmt *)_x_; }
inline Stmt_IFstmt * _IFstmt(const a_Stmt * _x_) { return (Stmt_IFstmt *)_x_; }
inline Stmt_MATCHstmt * _MATCHstmt(const a_Stmt * _x_) { return (Stmt_MATCHstmt *)_x_; }
inline Stmt_REWRITEstmt * _REWRITEstmt(const a_Stmt * _x_) { return (Stmt_REWRITEstmt *)_x_; }
inline Stmt_REPLACEMENTstmt * _REPLACEMENTstmt(const a_Stmt * _x_) { return (Stmt_REPLACEMENTstmt *)_x_; }
inline Stmt_FORALLstmt * _FORALLstmt(const a_Stmt * _x_) { return (Stmt_FORALLstmt *)_x_; }
inline Stmt_RETURNstmt * _RETURNstmt(const a_Stmt * _x_) { return (Stmt_RETURNstmt *)_x_; }

#line 116 "../../prop-src/setl-ast.ph"
#line 116 "../../prop-src/setl-ast.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing routines for definitions, statements and generators
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, Def);
extern std::ostream& operator << (std::ostream&, Defs);
extern std::ostream& operator << (std::ostream&, Sig);
extern std::ostream& operator << (std::ostream&, Sigs);
extern std::ostream& operator << (std::ostream&, Stmt);
extern std::ostream& operator << (std::ostream&, Stmts);
extern std::ostream& operator << (std::ostream&, LabSig);
extern std::ostream& operator << (std::ostream&, LabSigs);
extern std::ostream& operator << (std::ostream&, Generator);
extern std::ostream& operator << (std::ostream&, Generators);

#endif
#line 136 "../../prop-src/setl-ast.ph"
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
