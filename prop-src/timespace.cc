///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\timespace.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_QUARK_USED
#include <propdefs.h>
#line 1 "../../prop-src/timespace.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the time and space complexity
//  datatypes.  These datatypes are used to represent time and space
//  complexity in the SETL-like extension language.
//
///////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <iostream>
#include "basics.h"
#include "timespace.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the time and space datatypes
//
///////////////////////////////////////////////////////////////////////////////

#line 21 "../../prop-src/timespace.pcc"
#line 21 "../../prop-src/timespace.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Complexity
//
///////////////////////////////////////////////////////////////////////////////
#line 21 "../../prop-src/timespace.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Time
//
///////////////////////////////////////////////////////////////////////////////
#line 21 "../../prop-src/timespace.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Space
//
///////////////////////////////////////////////////////////////////////////////
#line 21 "../../prop-src/timespace.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Complexity
//
///////////////////////////////////////////////////////////////////////////////
#line 21 "../../prop-src/timespace.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Time
//
///////////////////////////////////////////////////////////////////////////////
#line 21 "../../prop-src/timespace.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Space
//
///////////////////////////////////////////////////////////////////////////////
#line 21 "../../prop-src/timespace.pcc"


#line 21 "../../prop-src/timespace.pcc"
#line 21 "../../prop-src/timespace.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print the complexity
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Complexity c)
{
  
#line 31 "../../prop-src/timespace.pcc"
#line 42 "../../prop-src/timespace.pcc"
{
  switch (c->tag__) {
    case a_Complexity::tag_Var: {
#line 33 "../../prop-src/timespace.pcc"
     f << _Var(c)->Var; 
#line 33 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_Add: {
#line 34 "../../prop-src/timespace.pcc"
     f << '(' << _Add(c)->_1 << " + " << _Add(c)->_2 << ')'; 
#line 34 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_Mul: {
#line 35 "../../prop-src/timespace.pcc"
     f << '(' << _Mul(c)->_1 << " * " << _Mul(c)->_2 << ')'; 
#line 35 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_Div: {
#line 36 "../../prop-src/timespace.pcc"
     f << '(' << _Div(c)->_1 << " / " << _Div(c)->_2 << ')'; 
#line 36 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_Power: {
#line 37 "../../prop-src/timespace.pcc"
     f << '(' << _Power(c)->_1 << " ^ " << _Power(c)->_2 << ')'; 
#line 37 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_Log: {
#line 38 "../../prop-src/timespace.pcc"
     f << "log " << _Log(c)->Log; 
#line 38 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_Const: {
#line 39 "../../prop-src/timespace.pcc"
     f << _Const(c)->Const; 
#line 39 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_BigOh: {
#line 40 "../../prop-src/timespace.pcc"
     f << "O(" << _BigOh(c)->BigOh << ')'; 
#line 40 "../../prop-src/timespace.pcc"
      } break;
    case a_Complexity::tag_Omega: {
#line 41 "../../prop-src/timespace.pcc"
     f << "Omega(" << _Omega(c)->Omega << ')'; 
#line 41 "../../prop-src/timespace.pcc"
      } break;
    default: {
#line 42 "../../prop-src/timespace.pcc"
     f << "o(" << _LittleOh(c)->LittleOh << ')'; 
#line 42 "../../prop-src/timespace.pcc"
      } break;
  }
}
#line 43 "../../prop-src/timespace.pcc"
#line 43 "../../prop-src/timespace.pcc"

  return f;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print the time complexity
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Time t)
{  return f << "Time(" << t << ")"; }

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty print the space complexity
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, Space s)
{  return f << "Space(" << s << ")"; }

///////////////////////////////////////////////////////////////////////////////
//
//  Function to simplify a complexity expression
//
///////////////////////////////////////////////////////////////////////////////

Complexity simplify (Complexity c)
{
  
#line 73 "../../prop-src/timespace.pcc"
#line 79 "../../prop-src/timespace.pcc"
  extern void  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_rewrite(Complexity & );
  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_rewrite(c);
#line 79 "../../prop-src/timespace.pcc"
#line 79 "../../prop-src/timespace.pcc"

  return c;
}
#line 82 "../../prop-src/timespace.pcc"
class cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1 : public BURS {
private:
  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1(const cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1&);               // no copy constructor
  void operator = (const cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1&); // no assignment
public:
  struct cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_StateRec * stack__, * stack_top__;
public:
  void labeler(const char *, int&, int);
  void labeler(Quark, int&, int);
         void  labeler(Complexity & redex, int&, int);
  inline virtual void  operator () (Complexity & redex) { int s; labeler(redex,s,0); }
private: 
  public:
    inline cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1() {}
};
void  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_rewrite(Complexity &  _x_) 
{  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1 _r_;
   _r_(_x_);
}

///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1
#define DEBUG_cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1(repl,redex,file,line,rule) repl
#else
static const char * cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_file_name = "..\..\prop-src\timespace.pcc";
#endif

static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_1[2][2] = {
   { 0, 0 },
   { 0, 2 }
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_2[2][2] = {
   { 0, 0 },
   { 0, 3 }
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_3[2][2] = {
   { 0, 0 },
   { 0, 4 }
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_4[2][2] = {
   { 0, 0 },
   { 0, 5 }
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_5[2] = {
   0, 6
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_1_0[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_1_1[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_2_0[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_2_1[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_3_0[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_3_1[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_4_0[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_4_1[7] = {
   0, 1, 0, 0, 0, 0, 0
};


static const TreeTables::ShortState cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_5_0[7] = {
   0, 1, 0, 0, 0, 0, 0
};


inline void  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1::labeler(char const * redex,int& s__,int)
{
  {
s__ = 0;
  }
}

inline void  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1::labeler(Quark redex,int& s__,int)
{
  {
s__ = 0;
  }
}

void  cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1::labeler (Complexity & redex, int& s__, int r__)
{
replacement__:
  switch(redex->tag__) {
    case a_Complexity::tag_Var: { 
      int s0__;
      labeler(_Var(redex)->Var, s0__, r__);
      s__ = 0;} break;
    case a_Complexity::tag_Add: { 
      int s0__;
      int s1__;
      labeler(_Add(redex)->_1, s0__, r__);
      labeler(_Add(redex)->_2, s1__, r__);
      s__ = cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_1[cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_1_0[s0__]][cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_1_1[s1__]]; } break;
    case a_Complexity::tag_Mul: { 
      int s0__;
      int s1__;
      labeler(_Mul(redex)->_1, s0__, r__);
      labeler(_Mul(redex)->_2, s1__, r__);
      s__ = cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_2[cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_2_0[s0__]][cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_2_1[s1__]]; } break;
    case a_Complexity::tag_Div: { 
      int s0__;
      int s1__;
      labeler(_Div(redex)->_1, s0__, r__);
      labeler(_Div(redex)->_2, s1__, r__);
      s__ = cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_3[cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_3_0[s0__]][cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_3_1[s1__]]; } break;
    case a_Complexity::tag_Power: { 
      int s0__;
      int s1__;
      labeler(_Power(redex)->_1, s0__, r__);
      labeler(_Power(redex)->_2, s1__, r__);
      s__ = cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_4[cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_4_0[s0__]][cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_4_1[s1__]]; } break;
    case a_Complexity::tag_Log: { 
      int s0__;
      labeler(_Log(redex)->Log, s0__, r__);
      s__ = cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_theta_5[cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_mu_5_0[s0__]]; } break;
    case a_Complexity::tag_Const: { 
      int s0__;
      s0__ = 0; // double
      s__ = 1;} break;
    case a_Complexity::tag_BigOh: { 
      int s0__;
      labeler(_BigOh(redex)->BigOh, s0__, r__);
      s__ = 0;} break;
    case a_Complexity::tag_Omega: { 
      int s0__;
      labeler(_Omega(redex)->Omega, s0__, r__);
      s__ = 0;} break;
    default: { 
      int s0__;
      labeler(_LittleOh(redex)->LittleOh, s0__, r__);
      s__ = 0;} break;
  }
  switch (s__) {
    case 6: {
#line 78 "../../prop-src/timespace.pcc"
      { redex = DEBUG_cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1(Const(log(_Const(_Log(redex)->Log)->Const)),redex,cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_file_name,78,"Log Const i: ...");
        r__ = 1; goto replacement__; }
#line 79 "../../prop-src/timespace.pcc"
} break;
    case 5: {
#line 77 "../../prop-src/timespace.pcc"
      { redex = DEBUG_cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1(Const(exp((log(_Const(_Power(redex)->_1)->Const) * _Const(_Power(redex)->_2)->Const))),redex,cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_file_name,77,"Power (Const i, Const j): ...");
        r__ = 1; goto replacement__; }
#line 78 "../../prop-src/timespace.pcc"
} break;
    case 4: {
#line 76 "../../prop-src/timespace.pcc"
      { redex = DEBUG_cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1(Const((_Const(_Div(redex)->_1)->Const / _Const(_Div(redex)->_2)->Const)),redex,cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_file_name,76,"Div (Const i, Const j): ...");
        r__ = 1; goto replacement__; }
#line 77 "../../prop-src/timespace.pcc"
} break;
    case 3: {
#line 75 "../../prop-src/timespace.pcc"
      { redex = DEBUG_cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1(Const((_Const(_Mul(redex)->_1)->Const * _Const(_Mul(redex)->_2)->Const)),redex,cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_file_name,75,"Mul (Const i, Const j): ...");
        r__ = 1; goto replacement__; }
#line 76 "../../prop-src/timespace.pcc"
} break;
    case 2: {
#line 74 "../../prop-src/timespace.pcc"
      { redex = DEBUG_cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1(Const((_Const(_Add(redex)->_1)->Const + _Const(_Add(redex)->_2)->Const)),redex,cocofmcocofm_p_r_o_pcn_s_r_cfm_t_i_m_e_s_p_a_c_eco_X1_file_name,74,"Add (Const i, Const j): ...");
        r__ = 1; goto replacement__; }
#line 75 "../../prop-src/timespace.pcc"
} break;
  }
  
}

/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
