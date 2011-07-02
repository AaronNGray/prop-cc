///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\wam.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#include <propdefs.h>
#line 1 "../../prop-src/wam.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the helper routines for the
//  constraint compiler, which is based (very, very, I mean, very)
//  loosely on the Warren Abstract Machine (WAM).
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "basics.h"
#include "wam.h"
#include "type.h"
#include "ir.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the datatypes
//
///////////////////////////////////////////////////////////////////////////////

#line 22 "../../prop-src/wam.pcc"
#line 22 "../../prop-src/wam.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype VarKind
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype WAM
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for WAM
//
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& strm__, WAM  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, WAM  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Label
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Label
//
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& strm__, Label  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, Label  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<WAM>
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Label>
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Instness
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Determinism
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype VarKind
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype WAM
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for WAM
//
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& strm__, WAM  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, WAM  obj__)
{
  switch (untag(obj__))
  {
    case ((int)XX_g_e_t___xXX): 
      strm__ << "get_x";
      break;
    case ((int)XX_g_e_t___yXX): 
      strm__ << "get_y";
      break;
    case ((int)XX_p_r_o_c_e_e_dXX): 
      strm__ << "proceed";
      break;
    case ((int)XX_f_a_i_lXX): 
      strm__ << "fail";
      break;
    case ((int)XX_d_e_r_e_fXX): 
      strm__ << "deref";
      break;
    case ((int)XX_u_n_i_f_yXX): 
      strm__ << "unify";
      break;
    case ((int)XX_u_n_i_f_y___v_a_r_i_a_b_l_eXX): 
      strm__ << "unify_variable";
      break;
    case ((int)XX_t_r_u_s_t___m_e___e_l_s_e___f_a_i_lXX): 
      strm__ << "trust_me_else_fail";
      break;
    case 8: 
      strm__ << "unify_term";
      strm__ << '(';
      strm__.stream() << _XX_u_n_i_f_y___t_e_r_mXX(obj__)->_1; // Ty
      strm__ << ',';
      strm__.stream() << _XX_u_n_i_f_y___t_e_r_mXX(obj__)->_2; // Cons
      strm__ << ')';
      break;
    case 9: 
      strm__ << "try";
      strm__ << '(';
      strm__ << _XX_t_r_yXX(obj__)->XX_t_r_yXX; // Label
      strm__ << ')';
      break;
    case 10: 
      strm__ << "retry";
      strm__ << '(';
      strm__ << _XX_r_e_t_r_yXX(obj__)->XX_r_e_t_r_yXX; // Label
      strm__ << ')';
      break;
    case 11: 
      strm__ << "trust";
      strm__ << '(';
      strm__ << _XX_t_r_u_s_tXX(obj__)->XX_t_r_u_s_tXX; // Label
      strm__ << ')';
      break;
    case 12: 
      strm__ << "try_me_else";
      strm__ << '(';
      strm__ << _XX_t_r_y___m_e___e_l_s_eXX(obj__)->XX_t_r_y___m_e___e_l_s_eXX; // Label
      strm__ << ')';
      break;
    case 13: 
      strm__ << "retry_me_else";
      strm__ << '(';
      strm__ << _XX_r_e_t_r_y___m_e___e_l_s_eXX(obj__)->XX_r_e_t_r_y___m_e___e_l_s_eXX; // Label
      strm__ << ')';
      break;
    case 14: 
      strm__ << "label";
      strm__ << '(';
      strm__ << _XX_l_a_b_e_lXX(obj__)->XX_l_a_b_e_lXX; // Label
      strm__ << ')';
      break;
  }
  return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Label
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Label
//
///////////////////////////////////////////////////////////////////////////////
std::ostream& operator << (std::ostream& strm__, Label  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, Label  obj__)
{
  strm__ << obj__->LABEL; // char const *
  return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<WAM>
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<WAM>;
template a_List<WAM> * list_1_(Label x_1, a_List<Label> *  x_2);
template a_List<WAM> * list_1_(Label x_list_1_);
template int boxed(const a_List<WAM> *);
template int untag(const a_List<WAM> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Label>
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Label>;
template a_List<Label> * list_1_(WAM x_1, a_List<WAM> *  x_2);
template a_List<Label> * list_1_(WAM x_list_1_);
template int boxed(const a_List<Label> *);
template int untag(const a_List<Label> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Instness
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Determinism
//
///////////////////////////////////////////////////////////////////////////////
#line 22 "../../prop-src/wam.pcc"


#line 23 "../../prop-src/wam.pcc"
#line 23 "../../prop-src/wam.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Utility routines.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Dereference a determinism variable.
//
///////////////////////////////////////////////////////////////////////////////

Determinism deref (Determinism det)
{
  
#line 39 "../../prop-src/wam.pcc"
#line 39 "../../prop-src/wam.pcc"
{
  for (;;) {
    if (boxed(det)) {
      if (boxed(det->VAR_DET)) {
        L2:; 
#line 39 "../../prop-src/wam.pcc"
       det = det->VAR_DET; 
#line 39 "../../prop-src/wam.pcc"
      } else {
        switch ((int)det->VAR_DET) {
          case ((int)UNKNOWN_DET): { goto L1; } break;
          default: { goto L2; } break;
        }
      }
    } else { goto L1; }
  }
  L1:;
}
#line 39 "../../prop-src/wam.pcc"
#line 39 "../../prop-src/wam.pcc"

  return det;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Dereference an instantiatedness variable.
//
///////////////////////////////////////////////////////////////////////////////

Instness deref (Instness inst)
{
  
#line 51 "../../prop-src/wam.pcc"
#line 51 "../../prop-src/wam.pcc"
{
  for (;;) {
    if (inst) {
      switch (inst->tag__) {
        case a_Instness::tag_VARinst: {
          if (_VARinst(inst)->VARinst) {
#line 51 "../../prop-src/wam.pcc"
           inst = _VARinst(inst)->VARinst; 
#line 51 "../../prop-src/wam.pcc"
          } else { goto L3; }
          } break;
        default: { goto L3; } break;
      }
    } else { goto L3; }
  }
  L3:;
}
#line 51 "../../prop-src/wam.pcc"
#line 51 "../../prop-src/wam.pcc"

  return inst;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print the determinism.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Determinism d)
{
  
#line 63 "../../prop-src/wam.pcc"
#line 72 "../../prop-src/wam.pcc"
{
  Determinism _V1 = deref(d);
  if (boxed(_V1)) {
#line 72 "../../prop-src/wam.pcc"
   f << "???"; 
#line 72 "../../prop-src/wam.pcc"
  } else {
    switch ((int)_V1) {
      case ((int)UNKNOWN_DET): {
#line 65 "../../prop-src/wam.pcc"
       f << "unknown"; 
#line 65 "../../prop-src/wam.pcc"
        } break;
      case ((int)DET): {
#line 66 "../../prop-src/wam.pcc"
       f << "det"; 
#line 66 "../../prop-src/wam.pcc"
        } break;
      case ((int)SEMI_DET): {
#line 67 "../../prop-src/wam.pcc"
       f << "semidet"; 
#line 67 "../../prop-src/wam.pcc"
        } break;
      case ((int)MULTI_DET): {
#line 68 "../../prop-src/wam.pcc"
       f << "multidet"; 
#line 68 "../../prop-src/wam.pcc"
        } break;
      case ((int)NON_DET): {
#line 69 "../../prop-src/wam.pcc"
       f << "nondet"; 
#line 69 "../../prop-src/wam.pcc"
        } break;
      case ((int)FAIL_DET): {
#line 70 "../../prop-src/wam.pcc"
       f << "fail"; 
#line 70 "../../prop-src/wam.pcc"
        } break;
      default: {
#line 71 "../../prop-src/wam.pcc"
       f << "error"; 
#line 71 "../../prop-src/wam.pcc"
        } break;
    }
  }
}
#line 73 "../../prop-src/wam.pcc"
#line 73 "../../prop-src/wam.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Instantiateness analysis.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Determinism analysis.
//
///////////////////////////////////////////////////////////////////////////////
#line 88 "../../prop-src/wam.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 32
Number of ifs generated      = 5
Number of switches generated = 3
Number of labels             = 1
Number of gotos              = 1
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
