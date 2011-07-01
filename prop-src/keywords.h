///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\keywords.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#define PROP_REGEXP_MATCHING_USED
#include <propdefs.h>
#line 1 "../../prop-src/keywords.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file defines the lexical structure of the Prop language.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef prop_lexemes_h
#define prop_lexemes_h

///////////////////////////////////////////////////////////////////////////////
//
//  Here are some regular expression abbreviations.
//
///////////////////////////////////////////////////////////////////////////////

#line 16 "../../prop-src/keywords.ph"
#line 16 "../../prop-src/keywords.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Main keywords are keywords that can start Prop constructs.
//
///////////////////////////////////////////////////////////////////////////////

#line 37 "../../prop-src/keywords.ph"
#line 109 "../../prop-src/keywords.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  PropToken is the class of all terminals in Prop.
//
///////////////////////////////////////////////////////////////////////////////

#line 118 "../../prop-src/keywords.ph"
#line 130 "../../prop-src/keywords.ph"
enum PropToken {
  XX_r_e_w_r_i_t_eXX = 256, XX_i_n_f_e_r_e_n_c_eXX = 257, XX_m_a_t_c_hXX = 258, 
  XX_m_a_t_c_h_a_l_lXX = 259, XX_m_a_t_c_h_s_c_a_nXX = 260, XX_r_e_f_i_n_eXX = 261, 
  XX_c_l_a_s_s_o_fXX = 262, XX_t_y_p_eXX = 263, XX_d_a_t_a_t_y_p_eXX = 264, 
  XX_i_n_s_t_a_n_t_i_a_t_eXX = 265, XX_l_e_x_e_m_eXX = 266, XX_b_i_t_f_i_e_l_dXX = 267, 
  XX_b_e_g_i_nXX = 268, XX_s_y_n_t_a_xXX = 269, XX_d_a_t_a_f_l_o_wXX = 270, 
  XX_m_o_d_u_l_eXX = 271, XX_s_i_g_n_a_t_u_r_eXX = 272, XX_c_o_n_s_t_r_a_i_n_tXX = 273, 
  XX_d_e_c_l_a_r_eXX = 274, XX_p_r_o_c_e_d_u_r_eXX = 275, XX_f_u_nXX = 276, 
  XX_f_u_n_c_t_i_o_nXX = 277, XX_g_r_a_p_h_t_y_p_eXX = 278, XX_g_r_a_p_h_r_e_w_r_i_t_eXX = 279, 
  XX_c_u_t_r_e_w_r_i_t_eXX = 280, XX_f_a_i_l_r_e_w_r_i_t_eXX = 281, XX_a_t_t_r_i_b_u_t_e_g_r_a_m_m_a_rXX = 282, 
  XX_i_fXX = 283, XX_t_h_e_nXX = 284, XX_e_l_s_eXX = 285, 
  XX_e_l_s_i_fXX = 286, XX_w_h_i_l_eXX = 287, XX_l_o_o_pXX = 288, 
  XX_i_sXX = 289, XX_c_l_a_s_sXX = 290, XX_u_n_i_f_i_a_b_l_eXX = 291, 
  XX_o_fXX = 292, XX_d_oXX = 293, XX_b_r_e_a_kXX = 294, 
  XX_c_o_n_t_i_n_u_eXX = 295, XX_g_o_t_oXX = 296, XX_w_h_e_r_eXX = 297, 
  XX_a_sXX = 298, XX_p_u_b_l_i_cXX = 299, XX_p_r_o_t_e_c_t_e_dXX = 300, 
  XX_p_r_i_v_a_t_eXX = 301, XX_c_o_n_s_tXX = 302, XX_e_x_t_e_r_nXX = 303, 
  XX_m_u_t_a_b_l_eXX = 304, XX_a_p_p_l_i_c_a_t_i_v_eXX = 305, XX_v_i_r_t_u_a_lXX = 306, 
  XX_t_r_u_eXX = 307, XX_f_a_l_s_eXX = 308, XX_c_o_l_l_e_c_t_a_b_l_eXX = 309, 
  XX_f_i_n_a_l_i_z_a_b_l_eXX = 310, XX_p_r_i_n_t_a_b_l_eXX = 311, XX_t_r_a_c_e_dXX = 312, 
  XX_p_e_r_s_i_s_t_e_n_tXX = 313, XX_t_r_e_e_p_a_r_s_e_rXX = 314, XX_i_n_l_i_n_eXX = 315, 
  XX_w_i_t_hXX = 316, XX_s_w_i_t_c_hXX = 317, XX_u_n_s_i_g_n_e_dXX = 318, 
  XX_s_i_g_n_e_dXX = 319, XX_f_o_rXX = 320, XX_c_a_t_e_g_o_r_yXX = 321, 
  XX_f_u_n_c_t_o_rXX = 322, XX_f_e_a_t_u_r_eXX = 323, XX_s_h_a_r_i_n_gXX = 324, 
  XX_r_e_l_a_t_i_o_nXX = 325, XX_v_i_e_wXX = 326, XX_i_n_h_e_r_i_t_e_dXX = 327, 
  XX_r_e_t_u_r_nXX = 328, XX_s_y_n_t_h_e_s_i_z_e_dXX = 329, XX_l_a_wXX = 330, 
  XX_l_e_f_tdkXX = 331, XX_r_i_g_h_tdkXX = 332, XX_e_x_p_e_c_tdkXX = 333, 
  XX_p_r_e_cdkXX = 334, XX_m_a_p_o_fXX = 335, XX_s_e_t_o_fXX = 336, 
  XX_b_a_g_o_fXX = 337, XX_m_u_l_t_i_m_a_p_o_fXX = 338, XX_l_i_s_t_o_fXX = 339, 
  XX_p_r_i_q_u_e_u_e_o_fXX = 340, XX_q_u_e_u_e_o_fXX = 341, XX_d_e_q_u_e_o_fXX = 342, 
  XX_t_u_p_l_e_o_fXX = 343, XX_f_o_r_a_l_lXX = 344, XX_e_x_i_s_t_sXX = 345, 
  XX_d_o_mXX = 346, XX_r_a_nXX = 347, XX_a_r_bXX = 348, 
  XX_l_e_s_sXX = 349, XX_i_n_c_l_u_d_eXX = 350, XX_l_f_pXX = 351, 
  XX_g_f_pXX = 352, XX_h_o_mXX = 353, XX_i_m_p_l_i_e_sdkXX = 354, 
  XX_x_o_rdkXX = 355, XX_e_q_u_i_vdkXX = 356, XX_t_i_m_edkXX = 357, 
  XX_s_p_a_c_edkXX = 358, XX_n_o_d_e_sdkXX = 359, XX_e_d_g_e_sdkXX = 360, 
  XX_i_n_d_e_xdkXX = 361, XX_h_a_s_hdkXX = 362, XX_e_q_u_a_l_i_t_ydkXX = 363, 
  XX_p_r_e_o_r_d_e_rdkXX = 364, XX_p_o_s_t_o_r_d_e_rdkXX = 365, XX_b_e_f_o_r_edkXX = 366, 
  XX_t_o_p_d_o_w_ndkXX = 367, XX_b_o_t_t_o_m_u_pdkXX = 368, XX_s_t_r_a_t_e_g_ydkXX = 369, 
  XX_o_r_d_e_rdkXX = 370, XX_p_r_a_g_m_adkXX = 371, XX_c_a_s_eXX = 372, 
  XX_a_n_dXX = 373, XX_e_n_dXX = 374, XXcocoXX = 375, 
  XXcococoXX = 376, XXdmcndoXX = 377, XXdkdkXX = 378, 
  XXcgcgXX = 379, XXhmhmXX = 380, XXclclXX = 381, 
  XXcncnXX = 382, XXcndoXX = 383, XXdmdmXX = 384, 
  XXdodoXX = 385, XXdodnXX = 386, XXdmdnXX = 387, 
  XXcldnXX = 388, XXcndnXX = 389, XXckdnXX = 390, 
  XXcpdnXX = 391, XXcfdnXX = 392, XXdndnXX = 393, 
  XXcbdnXX = 394, XXdmdmdnXX = 395, XXdododnXX = 396, 
  XXcgdnXX = 397, XXhmdnXX = 398, XXfodnXX = 399, 
  XXdndoXX = 400, XXdmcnXX = 401, XXdmdndoXX = 402, 
  XXdkdnXX = 403, XXdkcnXX = 404, LONG_BAR = 405, 
  CONS_TOK = 406, DOMAIN_TOK = 407, CONS_EXP = 408, 
  META_QUOTE = 409, POLY_DATATYPE = 410, ATTRIB_ID = 411, 
  XXcihmXX = 412, XXhmcjXX = 413, XXflhmXX = 414, 
  XXhmfnXX = 415, XXhlhmXX = 416, XXhmhnXX = 417, 
  XXcociXX = 418, XXcoflXX = 419, XXgagaXX = 420, 
  XXchchXX = 421, INT_TOK = 422, REAL_TOK = 423, 
  CHAR_TOK = 424, STRING_TOK = 425, ID_TOK = 426, 
  REGEXP_TOK = 427, QUARK_TOK = 428, BIGINT_TOK = 429, 
  PUNCTUATIONS = 430
};




///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for PropToken
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern std::ostream& operator<<(std::ostream&, PropToken);
extern PrettyOStream& operator<<(PrettyOStream&, PropToken);
#line 130 "../../prop-src/keywords.ph"
#line 130 "../../prop-src/keywords.ph"


#endif
#line 133 "../../prop-src/keywords.ph"
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
