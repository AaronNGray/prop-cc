///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.2),
//  last updated on Mar 14, 1997.
//  The original source file is "setl-lexeme.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#define PROP_REGEXP_MATCHING_USED
#include <propdefs.h>
#line 1 "setl-lexeme.ph"
#ifndef SETL_lexemes_h
#define SETL_lexemes_h

///////////////////////////////////////////////////////////////////////////////
//  Common lexical aliases are defined as follows.
///////////////////////////////////////////////////////////////////////////////
#line 7 "setl-lexeme.ph"
#line 7 "setl-lexeme.ph"


///////////////////////////////////////////////////////////////////////////////
//  The lexemes of SETL are defined as follows as part of the characteristic
//  of the datatype SETL_Token.  Single character lexemes have been omitted 
//  from the following list since these are implicitly assumed.
///////////////////////////////////////////////////////////////////////////////
#line 23 "setl-lexeme.ph"
#line 38 "setl-lexeme.ph"
enum SETL_Token {
   XX_i_fXX = 256, XX_t_h_e_nXX = 257, XX_e_l_s_eXX = 258, 
   XX_w_h_i_l_eXX = 259, XX_d_oXX = 260, XX_f_o_rXX = 261, 
   XX_l_o_o_pXX = 262, XX_c_a_s_eXX = 263, XX_o_fXX = 264, 
   XX_b_e_g_i_nXX = 265, XX_e_n_dXX = 266, XX_e_x_c_e_p_t_i_o_nXX = 267, 
   XX_r_a_i_s_eXX = 268, XX_h_a_n_d_l_eXX = 269, XX_d_a_t_a_t_y_p_eXX = 270, 
   XX_t_y_p_eXX = 271, XX_s_t_r_u_c_t_u_r_eXX = 272, XX_s_t_r_u_c_tXX = 273, 
   XX_s_i_g_n_a_t_u_r_eXX = 274, XX_s_i_gXX = 275, XX_f_u_n_c_t_o_rXX = 276, 
   XX_i_n_c_l_u_d_eXX = 277, XX_o_p_e_nXX = 278, XX_v_a_lXX = 279, 
   XX_f_u_nXX = 280, XX_s_h_a_r_i_n_gXX = 281, XX_l_e_tXX = 282, 
   XX_l_o_c_a_lXX = 283, XX_i_nXX = 284, MOD = 285, 
   DIV = 286, ARB = 287, ARROW = 288, 
   ASSIGN = 289, GE = 290, LE = 291, 
   NE = 292, WITH = 293, LESS = 294, 
   INTEGER = 295, REAL = 296, IDENTIFIER = 297, 
   STRING = 298, CHARACTER = 299
};




///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for SETL_Token
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, SETL_Token);
extern PrettyOStream& operator<<(PrettyOStream&, SETL_Token);
#line 38 "setl-lexeme.ph"
#line 38 "setl-lexeme.ph"


#endif
#line 41 "setl-lexeme.ph"
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
