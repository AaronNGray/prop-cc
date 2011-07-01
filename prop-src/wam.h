///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\wam.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#include <propdefs.h>
#line 1 "../../prop-src/wam.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the internal abstract machine of the
//  constraint compiler, which is based (very) loosely on the Warren
//  Abstract Machine (WAM).   It also describes various other semantic
//  objects used in the analysis of the logic clauses.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef WAM_definitions_h
#define WAM_definitions_h

#include "basics.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward type definitions.
//
///////////////////////////////////////////////////////////////////////////////

#line 21 "../../prop-src/wam.ph"
#line 27 "../../prop-src/wam.ph"
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
// Forward class definition for Decl
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Decl_defined
#define datatype_Decl_defined
  class a_Decl;
  typedef a_Decl * Decl;
#endif

#line 27 "../../prop-src/wam.ph"
#line 27 "../../prop-src/wam.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Kind of variables.  These are characterized as follows, in order
//  of priority:
//  (a) Global variables are variables that occur as argument
//      in a structural pattern.  These may escape the life-time of
//      the clause.
//  (b) Local variables are variables that occur multiple times in a clause
//      (if they don't satisfy condition (a)).
//  (c) Void variables are variables with only one occurrence.  These
//      can be elided since they are always unifiable and never accessed.
//
///////////////////////////////////////////////////////////////////////////////

#line 43 "../../prop-src/wam.ph"
#line 137 "../../prop-src/wam.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for VarKind
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_VarKind_defined
#define datatype_VarKind_defined
  class a_VarKind;
  typedef a_VarKind * VarKind;
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

#  define NOinst 0

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

#  define UNKNOWN_DET 0
#  define DET 1
#  define SEMI_DET 2
#  define MULTI_DET 3
#  define NON_DET 4
#  define FAIL_DET 5
#  define ERROR_DET 6

enum UnificationMode {
  READ_MODE = 0, WRITE_MODE = 1
};



///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for WAM
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_WAM_defined
#define datatype_WAM_defined
  class a_WAM;
  typedef a_WAM * WAM;
#endif

#  define XX_g_e_t___xXX 0
#  define XX_g_e_t___yXX 1
#  define XX_p_r_o_c_e_e_dXX 2
#  define XX_f_a_i_lXX 3
#  define XX_d_e_r_e_fXX 4
#  define XX_u_n_i_f_yXX 5
#  define XX_u_n_i_f_y___v_a_r_i_a_b_l_eXX 6
#  define XX_t_r_u_s_t___m_e___e_l_s_e___f_a_i_lXX 7

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Label
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Label_defined
#define datatype_Label_defined
  class a_Label;
  typedef a_Label * Label;
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type WAMs
///////////////////////////////////////////////////////////////////////////////
#line 135 "../../prop-src/wam.ph"
typedef a_List<WAM> *  WAMs;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Labels
///////////////////////////////////////////////////////////////////////////////
#line 136 "../../prop-src/wam.ph"
typedef a_List<Label> *  Labels;

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype VarKind
//
///////////////////////////////////////////////////////////////////////////////
class a_VarKind : public MEM {
public:
  enum Tag_VarKind {
    tag_VOIDvar = 0, tag_LOCALvar = 1, tag_TEMPvar = 2, 
    tag_GLOBALvar = 3
  };

public:
  const Tag_VarKind tag__; // variant tag
protected:
  inline a_VarKind(Tag_VarKind t__) : tag__(t__) {}
public:
};
inline int boxed(const a_VarKind *) { return 1; }
inline int untag(const a_VarKind * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor VarKind::VOIDvar
//
///////////////////////////////////////////////////////////////////////////////
class VarKind_VOIDvar : public a_VarKind {
public:
#line 44 "../../prop-src/wam.ph"
  Ty VOIDvar; 
  inline VarKind_VOIDvar (Ty x_VOIDvar)
   : a_VarKind(tag_VOIDvar), VOIDvar(x_VOIDvar)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor VarKind::LOCALvar
//
///////////////////////////////////////////////////////////////////////////////
class VarKind_LOCALvar : public a_VarKind {
public:
#line 45 "../../prop-src/wam.ph"
  Ty LOCALvar; 
  inline VarKind_LOCALvar (Ty x_LOCALvar)
   : a_VarKind(tag_LOCALvar), LOCALvar(x_LOCALvar)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor VarKind::TEMPvar
//
///////////////////////////////////////////////////////////////////////////////
class VarKind_TEMPvar : public a_VarKind {
public:
#line 46 "../../prop-src/wam.ph"
  Ty TEMPvar; 
  inline VarKind_TEMPvar (Ty x_TEMPvar)
   : a_VarKind(tag_TEMPvar), TEMPvar(x_TEMPvar)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor VarKind::GLOBALvar
//
///////////////////////////////////////////////////////////////////////////////
class VarKind_GLOBALvar : public a_VarKind {
public:
#line 47 "../../prop-src/wam.ph"
  Ty GLOBALvar; 
  inline VarKind_GLOBALvar (Ty x_GLOBALvar)
   : a_VarKind(tag_GLOBALvar), GLOBALvar(x_GLOBALvar)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for VarKind
//
///////////////////////////////////////////////////////////////////////////////
inline a_VarKind * VOIDvar (Ty x_VOIDvar)
{
  return new VarKind_VOIDvar (x_VOIDvar);
}
inline a_VarKind * LOCALvar (Ty x_LOCALvar)
{
  return new VarKind_LOCALvar (x_LOCALvar);
}
inline a_VarKind * TEMPvar (Ty x_TEMPvar)
{
  return new VarKind_TEMPvar (x_TEMPvar);
}
inline a_VarKind * GLOBALvar (Ty x_GLOBALvar)
{
  return new VarKind_GLOBALvar (x_GLOBALvar);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for VarKind
//
///////////////////////////////////////////////////////////////////////////////
inline VarKind_VOIDvar * _VOIDvar(const a_VarKind * _x_) { return (VarKind_VOIDvar *)_x_; }
inline VarKind_LOCALvar * _LOCALvar(const a_VarKind * _x_) { return (VarKind_LOCALvar *)_x_; }
inline VarKind_TEMPvar * _TEMPvar(const a_VarKind * _x_) { return (VarKind_TEMPvar *)_x_; }
inline VarKind_GLOBALvar * _GLOBALvar(const a_VarKind * _x_) { return (VarKind_GLOBALvar *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Instness
//
///////////////////////////////////////////////////////////////////////////////
class a_Instness : public MEM {
public:
  enum Tag_Instness {
    tag_IDinst = 0, tag_FREEinst = 1, tag_GROUNDinst = 2, 
    tag_BOUNDinst = 3, tag_APPinst = 4, tag_FUNinst = 5, 
    tag_VARinst = 6
  };

public:
  const Tag_Instness tag__; // variant tag
protected:
  inline a_Instness(Tag_Instness t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Instness * x) { return x != 0; }
inline int untag(const a_Instness * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Instness::IDinst
//
///////////////////////////////////////////////////////////////////////////////
class Instness_IDinst : public a_Instness {
public:
#line 57 "../../prop-src/wam.ph"
  Id IDinst; 
  inline Instness_IDinst (Id x_IDinst)
   : a_Instness(tag_IDinst), IDinst(x_IDinst)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Instness::FREEinst
//
///////////////////////////////////////////////////////////////////////////////
class Instness_FREEinst : public a_Instness {
public:
#line 58 "../../prop-src/wam.ph"
  Ty FREEinst; 
  inline Instness_FREEinst (Ty x_FREEinst)
   : a_Instness(tag_FREEinst), FREEinst(x_FREEinst)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Instness::GROUNDinst
//
///////////////////////////////////////////////////////////////////////////////
class Instness_GROUNDinst : public a_Instness {
public:
#line 59 "../../prop-src/wam.ph"
  Ty GROUNDinst; 
  inline Instness_GROUNDinst (Ty x_GROUNDinst)
   : a_Instness(tag_GROUNDinst), GROUNDinst(x_GROUNDinst)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Instness::BOUNDinst
//
///////////////////////////////////////////////////////////////////////////////
class Instness_BOUNDinst : public a_Instness {
public:
#line 60 "../../prop-src/wam.ph"
  Ty _1; a_List<Instness> *  _2; 
  inline Instness_BOUNDinst (Ty x_1, a_List<Instness> *  x_2)
   : a_Instness(tag_BOUNDinst), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Instness::APPinst
//
///////////////////////////////////////////////////////////////////////////////
class Instness_APPinst : public a_Instness {
public:
#line 61 "../../prop-src/wam.ph"
  Cons _1; a_List<Instness> *  _2; 
  inline Instness_APPinst (Cons x_1, a_List<Instness> *  x_2)
   : a_Instness(tag_APPinst), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Instness::FUNinst
//
///////////////////////////////////////////////////////////////////////////////
class Instness_FUNinst : public a_Instness {
public:
#line 62 "../../prop-src/wam.ph"
  Instness _1; Instness _2; 
  inline Instness_FUNinst (Instness x_1, Instness x_2)
   : a_Instness(tag_FUNinst), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Instness::VARinst
//
///////////////////////////////////////////////////////////////////////////////
class Instness_VARinst : public a_Instness {
public:
#line 63 "../../prop-src/wam.ph"
  Instness VARinst; 
  inline Instness_VARinst (Instness x_VARinst)
   : a_Instness(tag_VARinst), VARinst(x_VARinst)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Instness
//
///////////////////////////////////////////////////////////////////////////////
inline a_Instness * IDinst (Id x_IDinst)
{
  return new Instness_IDinst (x_IDinst);
}
inline a_Instness * FREEinst (Ty x_FREEinst)
{
  return new Instness_FREEinst (x_FREEinst);
}
inline a_Instness * GROUNDinst (Ty x_GROUNDinst)
{
  return new Instness_GROUNDinst (x_GROUNDinst);
}
inline a_Instness * BOUNDinst (Ty x_1, a_List<Instness> *  x_2)
{
  return new Instness_BOUNDinst (x_1, x_2);
}
inline a_Instness * APPinst (Cons x_1, a_List<Instness> *  x_2)
{
  return new Instness_APPinst (x_1, x_2);
}
inline a_Instness * FUNinst (Instness x_1, Instness x_2)
{
  return new Instness_FUNinst (x_1, x_2);
}
inline a_Instness * VARinst (Instness x_VARinst)
{
  return new Instness_VARinst (x_VARinst);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Instness
//
///////////////////////////////////////////////////////////////////////////////
inline Instness_IDinst * _IDinst(const a_Instness * _x_) { return (Instness_IDinst *)_x_; }
inline Instness_FREEinst * _FREEinst(const a_Instness * _x_) { return (Instness_FREEinst *)_x_; }
inline Instness_GROUNDinst * _GROUNDinst(const a_Instness * _x_) { return (Instness_GROUNDinst *)_x_; }
inline Instness_BOUNDinst * _BOUNDinst(const a_Instness * _x_) { return (Instness_BOUNDinst *)_x_; }
inline Instness_APPinst * _APPinst(const a_Instness * _x_) { return (Instness_APPinst *)_x_; }
inline Instness_FUNinst * _FUNinst(const a_Instness * _x_) { return (Instness_FUNinst *)_x_; }
inline Instness_VARinst * _VARinst(const a_Instness * _x_) { return (Instness_VARinst *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Determinism::VAR_DET
//
///////////////////////////////////////////////////////////////////////////////
class a_Determinism : public MEM {
public:
#line 79 "../../prop-src/wam.ph"
  Determinism VAR_DET; 
  inline a_Determinism (Determinism x_VAR_DET)
   : VAR_DET(x_VAR_DET)
  {
  }
};
inline int boxed(const a_Determinism * x) { return (unsigned long)x >= 7; }
inline int untag(const a_Determinism * x) { return boxed(x) ? 8 : (int)x; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Determinism
//
///////////////////////////////////////////////////////////////////////////////
inline a_Determinism * VAR_DET (Determinism x_VAR_DET)
{
  return new a_Determinism (x_VAR_DET);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Determinism
//
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype WAM
//
///////////////////////////////////////////////////////////////////////////////
class a_WAM : public MEM {
public:
  enum Tag_WAM {
    tag_XX_u_n_i_f_y___t_e_r_mXX = 0, tag_XX_t_r_yXX = 1, tag_XX_r_e_t_r_yXX = 2, 
    tag_XX_t_r_u_s_tXX = 3, tag_XX_t_r_y___m_e___e_l_s_eXX = 4, tag_XX_r_e_t_r_y___m_e___e_l_s_eXX = 5, 
    tag_XX_l_a_b_e_lXX = 6
  };

public:
  const Tag_WAM tag__; // variant tag
protected:
  inline a_WAM(Tag_WAM t__) : tag__(t__) {}
public:
};
inline int boxed(const a_WAM * x) { return (unsigned long)x >= 8; }
inline int untag(const a_WAM * x) { return boxed(x) ? x->tag__ + 8 : (int)x; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for WAM
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern std::ostream& operator<<(std::ostream&, WAM);
extern PrettyOStream& operator<<(PrettyOStream&, WAM);
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor WAM::"unify_term"
//
///////////////////////////////////////////////////////////////////////////////
class WAM_XX_u_n_i_f_y___t_e_r_mXX : public a_WAM {
public:
#line 112 "../../prop-src/wam.ph"
  Ty _1; Cons _2; 
  inline WAM_XX_u_n_i_f_y___t_e_r_mXX (Ty x_1, Cons x_2)
   : a_WAM(tag_XX_u_n_i_f_y___t_e_r_mXX), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor WAM::"try"
//
///////////////////////////////////////////////////////////////////////////////
class WAM_XX_t_r_yXX : public a_WAM {
public:
#line 113 "../../prop-src/wam.ph"
  Label XX_t_r_yXX; 
  inline WAM_XX_t_r_yXX (Label x_XX_t_r_yXX)
   : a_WAM(tag_XX_t_r_yXX), XX_t_r_yXX(x_XX_t_r_yXX)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor WAM::"retry"
//
///////////////////////////////////////////////////////////////////////////////
class WAM_XX_r_e_t_r_yXX : public a_WAM {
public:
#line 114 "../../prop-src/wam.ph"
  Label XX_r_e_t_r_yXX; 
  inline WAM_XX_r_e_t_r_yXX (Label x_XX_r_e_t_r_yXX)
   : a_WAM(tag_XX_r_e_t_r_yXX), XX_r_e_t_r_yXX(x_XX_r_e_t_r_yXX)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor WAM::"trust"
//
///////////////////////////////////////////////////////////////////////////////
class WAM_XX_t_r_u_s_tXX : public a_WAM {
public:
#line 115 "../../prop-src/wam.ph"
  Label XX_t_r_u_s_tXX; 
  inline WAM_XX_t_r_u_s_tXX (Label x_XX_t_r_u_s_tXX)
   : a_WAM(tag_XX_t_r_u_s_tXX), XX_t_r_u_s_tXX(x_XX_t_r_u_s_tXX)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor WAM::"try_me_else"
//
///////////////////////////////////////////////////////////////////////////////
class WAM_XX_t_r_y___m_e___e_l_s_eXX : public a_WAM {
public:
#line 116 "../../prop-src/wam.ph"
  Label XX_t_r_y___m_e___e_l_s_eXX; 
  inline WAM_XX_t_r_y___m_e___e_l_s_eXX (Label x_XX_t_r_y___m_e___e_l_s_eXX)
   : a_WAM(tag_XX_t_r_y___m_e___e_l_s_eXX), XX_t_r_y___m_e___e_l_s_eXX(x_XX_t_r_y___m_e___e_l_s_eXX)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor WAM::"retry_me_else"
//
///////////////////////////////////////////////////////////////////////////////
class WAM_XX_r_e_t_r_y___m_e___e_l_s_eXX : public a_WAM {
public:
#line 117 "../../prop-src/wam.ph"
  Label XX_r_e_t_r_y___m_e___e_l_s_eXX; 
  inline WAM_XX_r_e_t_r_y___m_e___e_l_s_eXX (Label x_XX_r_e_t_r_y___m_e___e_l_s_eXX)
   : a_WAM(tag_XX_r_e_t_r_y___m_e___e_l_s_eXX), XX_r_e_t_r_y___m_e___e_l_s_eXX(x_XX_r_e_t_r_y___m_e___e_l_s_eXX)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor WAM::"label"
//
///////////////////////////////////////////////////////////////////////////////
class WAM_XX_l_a_b_e_lXX : public a_WAM {
public:
#line 119 "../../prop-src/wam.ph"
  Label XX_l_a_b_e_lXX; 
  inline WAM_XX_l_a_b_e_lXX (Label x_XX_l_a_b_e_lXX)
   : a_WAM(tag_XX_l_a_b_e_lXX), XX_l_a_b_e_lXX(x_XX_l_a_b_e_lXX)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for WAM
//
///////////////////////////////////////////////////////////////////////////////
inline a_WAM * XX_u_n_i_f_y___t_e_r_mXX (Ty x_1, Cons x_2)
{
  return new WAM_XX_u_n_i_f_y___t_e_r_mXX (x_1, x_2);
}
inline a_WAM * XX_t_r_yXX (Label x_XX_t_r_yXX)
{
  return new WAM_XX_t_r_yXX (x_XX_t_r_yXX);
}
inline a_WAM * XX_r_e_t_r_yXX (Label x_XX_r_e_t_r_yXX)
{
  return new WAM_XX_r_e_t_r_yXX (x_XX_r_e_t_r_yXX);
}
inline a_WAM * XX_t_r_u_s_tXX (Label x_XX_t_r_u_s_tXX)
{
  return new WAM_XX_t_r_u_s_tXX (x_XX_t_r_u_s_tXX);
}
inline a_WAM * XX_t_r_y___m_e___e_l_s_eXX (Label x_XX_t_r_y___m_e___e_l_s_eXX)
{
  return new WAM_XX_t_r_y___m_e___e_l_s_eXX (x_XX_t_r_y___m_e___e_l_s_eXX);
}
inline a_WAM * XX_r_e_t_r_y___m_e___e_l_s_eXX (Label x_XX_r_e_t_r_y___m_e___e_l_s_eXX)
{
  return new WAM_XX_r_e_t_r_y___m_e___e_l_s_eXX (x_XX_r_e_t_r_y___m_e___e_l_s_eXX);
}
inline a_WAM * XX_l_a_b_e_lXX (Label x_XX_l_a_b_e_lXX)
{
  return new WAM_XX_l_a_b_e_lXX (x_XX_l_a_b_e_lXX);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for WAM
//
///////////////////////////////////////////////////////////////////////////////
inline WAM_XX_u_n_i_f_y___t_e_r_mXX * _XX_u_n_i_f_y___t_e_r_mXX(const a_WAM * _x_) { return (WAM_XX_u_n_i_f_y___t_e_r_mXX *)_x_; }
inline WAM_XX_t_r_yXX * _XX_t_r_yXX(const a_WAM * _x_) { return (WAM_XX_t_r_yXX *)_x_; }
inline WAM_XX_r_e_t_r_yXX * _XX_r_e_t_r_yXX(const a_WAM * _x_) { return (WAM_XX_r_e_t_r_yXX *)_x_; }
inline WAM_XX_t_r_u_s_tXX * _XX_t_r_u_s_tXX(const a_WAM * _x_) { return (WAM_XX_t_r_u_s_tXX *)_x_; }
inline WAM_XX_t_r_y___m_e___e_l_s_eXX * _XX_t_r_y___m_e___e_l_s_eXX(const a_WAM * _x_) { return (WAM_XX_t_r_y___m_e___e_l_s_eXX *)_x_; }
inline WAM_XX_r_e_t_r_y___m_e___e_l_s_eXX * _XX_r_e_t_r_y___m_e___e_l_s_eXX(const a_WAM * _x_) { return (WAM_XX_r_e_t_r_y___m_e___e_l_s_eXX *)_x_; }
inline WAM_XX_l_a_b_e_lXX * _XX_l_a_b_e_lXX(const a_WAM * _x_) { return (WAM_XX_l_a_b_e_lXX *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Label::LABEL
//
///////////////////////////////////////////////////////////////////////////////
class a_Label : public MEM {
public:
#line 127 "../../prop-src/wam.ph"
  Id LABEL; 
  inline a_Label (Id x_LABEL)
   : LABEL(x_LABEL)
  {
  }
};
inline int boxed(const a_Label *) { return 1; }
inline int untag(const a_Label *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for Label
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern std::ostream& operator<<(std::ostream&, Label);
extern PrettyOStream& operator<<(PrettyOStream&, Label);
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Label
//
///////////////////////////////////////////////////////////////////////////////
inline a_Label * LABEL (Id x_LABEL)
{
  return new a_Label (x_LABEL);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Label
//
///////////////////////////////////////////////////////////////////////////////


#line 137 "../../prop-src/wam.ph"
#line 137 "../../prop-src/wam.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Optimization and manipulation of WAM code.
//
///////////////////////////////////////////////////////////////////////////////

extern WAMs peep_hole (WAMs); // peep hole optimizer.

///////////////////////////////////////////////////////////////////////////////
//
//  Manipulation routines.
//
///////////////////////////////////////////////////////////////////////////////

extern Instness    deref( Instness);
extern Determinism deref( Determinism);

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printers.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, WAM);
extern std::ostream& operator << (std::ostream&, WAMs);
extern std::ostream& operator << (std::ostream&, Label);
extern std::ostream& operator << (std::ostream&, Labels);
extern std::ostream& operator << (std::ostream&, Instness);
extern std::ostream& operator << (std::ostream&, Determinism);

#endif
#line 170 "../../prop-src/wam.ph"
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
