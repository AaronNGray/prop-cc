///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.2),
//  last updated on Mar 14, 1997.
//  The original source file is "setl-lexer.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#define PROP_REGEXP_MATCHING_USED
#define PROP_PARSER_USED
#include <propdefs.h>
#line 1 "setl-lexer.pcc"
#include <iostream.h>
#include "setl-lexeme.h"
#include "setl-syntax.h"

///////////////////////////////////////////////////////////////////////////////
//
// Instantiate the token type
//
///////////////////////////////////////////////////////////////////////////////
#line 10 "setl-lexer.pcc"
#line 10 "setl-lexer.pcc"
///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype SETL_Token
///////////////////////////////////////////////////////////////////////////////
#line 10 "setl-lexer.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for SETL_Token
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, SETL_Token  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, SETL_Token  obj__)
{
   switch ((obj__))
   {
      case XX_i_fXX: 
         strm__ << "if";
         break;
      case XX_t_h_e_nXX: 
         strm__ << "then";
         break;
      case XX_e_l_s_eXX: 
         strm__ << "else";
         break;
      case XX_w_h_i_l_eXX: 
         strm__ << "while";
         break;
      case XX_d_oXX: 
         strm__ << "do";
         break;
      case XX_f_o_rXX: 
         strm__ << "for";
         break;
      case XX_l_o_o_pXX: 
         strm__ << "loop";
         break;
      case XX_c_a_s_eXX: 
         strm__ << "case";
         break;
      case XX_o_fXX: 
         strm__ << "of";
         break;
      case XX_b_e_g_i_nXX: 
         strm__ << "begin";
         break;
      case XX_e_n_dXX: 
         strm__ << "end";
         break;
      case XX_e_x_c_e_p_t_i_o_nXX: 
         strm__ << "exception";
         break;
      case XX_r_a_i_s_eXX: 
         strm__ << "raise";
         break;
      case XX_h_a_n_d_l_eXX: 
         strm__ << "handle";
         break;
      case XX_d_a_t_a_t_y_p_eXX: 
         strm__ << "datatype";
         break;
      case XX_t_y_p_eXX: 
         strm__ << "type";
         break;
      case XX_s_t_r_u_c_t_u_r_eXX: 
         strm__ << "structure";
         break;
      case XX_s_t_r_u_c_tXX: 
         strm__ << "struct";
         break;
      case XX_s_i_g_n_a_t_u_r_eXX: 
         strm__ << "signature";
         break;
      case XX_s_i_gXX: 
         strm__ << "sig";
         break;
      case XX_f_u_n_c_t_o_rXX: 
         strm__ << "functor";
         break;
      case XX_i_n_c_l_u_d_eXX: 
         strm__ << "include";
         break;
      case XX_o_p_e_nXX: 
         strm__ << "open";
         break;
      case XX_v_a_lXX: 
         strm__ << "val";
         break;
      case XX_f_u_nXX: 
         strm__ << "fun";
         break;
      case XX_s_h_a_r_i_n_gXX: 
         strm__ << "sharing";
         break;
      case XX_l_e_tXX: 
         strm__ << "let";
         break;
      case XX_l_o_c_a_lXX: 
         strm__ << "local";
         break;
      case XX_i_nXX: 
         strm__ << "in";
         break;
      case MOD: 
         strm__ << "MOD";
         break;
      case DIV: 
         strm__ << "DIV";
         break;
      case ARB: 
         strm__ << "ARB";
         break;
      case ARROW: 
         strm__ << "ARROW";
         break;
      case ASSIGN: 
         strm__ << "ASSIGN";
         break;
      case GE: 
         strm__ << "GE";
         break;
      case LE: 
         strm__ << "LE";
         break;
      case NE: 
         strm__ << "NE";
         break;
      case WITH: 
         strm__ << "WITH";
         break;
      case LESS: 
         strm__ << "LESS";
         break;
      case INTEGER: 
         strm__ << "<int>";
         break;
      case REAL: 
         strm__ << "<real>";
         break;
      case IDENTIFIER: 
         strm__ << "<id>";
         break;
      case STRING: 
         strm__ << "<string>";
         break;
      case CHARACTER: 
         strm__ << "<character>";
         break;
   }
   return strm__;
}



#line 10 "setl-lexer.pcc"
#line 10 "setl-lexer.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  This is the lexical scanner routine for our typed-SETL language
//
///////////////////////////////////////////////////////////////////////////////
int SETLSyntax::get_token()
{  
#line 18 "setl-lexer.pcc"
#line 22 "setl-lexer.pcc"
{
   for (;;) {
      {
static const DFATables::Offset _X1_base [ 159 ] = {
   0, 0, 0, 0, 46, 19, 370, 17, 21, 365, 26, 364, 32, 30, 364, 56, 
   60, 71, 363, 363, 363, 363, 362, 362, 361, 99, 359, 357, 1, 158, 243, 1, 
   357, 357, 357, 357, 357, 354, 354, 351, 351, 347, 0, 347, 73, 61, 347, 0, 
   347, 346, 342, 339, 339, 339, 0, 337, 337, 337, 337, 337, 0, 0, 0, 0, 
   115, 337, 0, 8, 336, 336, 0, 326, 0, 322, 318, 0, 315, 315, 311, 311, 
   310, 310, 310, 0, 310, 310, 0, 305, 305, 305, 302, 0, 302, 0, 301, 0, 
   301, 300, 300, 0, 300, 299, 16, 0, 0, 0, 295, 0, 0, 295, 295, 284, 
   277, 0, 0, 277, 0, 276, 276, 275, 274, 0, 274, 0, 273, 0, 273, 272, 
   272, 0, 0, 272, 268, 259, 254, 252, 0, 252, 171, 90, 90, 0, 81, 81, 
   80, 78, 76, 0, 0, 0, 76, 74, 38, 36, 19, 0, 0, 0, 0
};
static const DFATables::State _X1_check [ 455 ] = {
   0, 0, 1, 31, 1, 31, 1, 31, 1, 0, 1, 0, 1, 0, 1, 0, 
   1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 
   1, 28, 1, 1, 28, 1, 0, 1, 67, 1, 1, 67, 1, 1, 1, 1, 
   102, 1, 0, 102, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
   1, 4, 1, 7, 1, 5, 5, 8, 8, 154, 10, 4, 4, 4, 13, 12, 
   8, 7, 10, 153, 13, 152, 4, 12, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 15, 
   16, 17, 16, 25, 15, 44, 25, 45, 45, 151, 17, 16, 0, 64, 17, 0, 
   44, 64, 25, 150, 143, 146, 64, 145, 144, 140, 142, 139, 0, 0, 29, 29, 
   29, 29, 25, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 30, 30, 30, 30, 138, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 137, 134, 133, 132, 135, 131, 101, 100, 
   71, 0, 0, 0, 112, 0, 128, 124, 118, 115, 120, 127, 126, 122, 119, 111, 
   117, 110, 69, 109, 0, 0, 106, 96, 0, 0, 90, 97, 94, 92, 89, 98, 
   85, 0, 0, 68, 65, 88, 0, 0, 0, 0, 76, 87, 82, 79, 84, 80, 
   81, 77, 74, 78, 73, 0, 0, 0, 27, 0, 0, 0, 59, 0, 0, 51, 
   52, 26, 58, 24, 23, 21, 22, 46, 43, 39, 41, 57, 56, 53, 55, 50, 
   49, 48, 40, 38, 36, 18, 14, 9, 33, 34, 19, 37, 6, 35, 0, 0, 
   32, 0, 0, 11, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0
};
static const DFATables::State _X1_next [ 455 ] = {
   0, 0, 31, 31, 31, 31, 31, 31, 3, 0, 30, 0, 3, 0, 3, 0, 
   3, 0, 29, 0, 3, 0, 3, 0, 3, 0, 28, 0, 3, 0, 28, 0, 
   27, 68, 26, 25, 25, 24, 0, 3, 0, 23, 22, 67, 21, 4, 4, 4, 
   0, 3, 0, 102, 3, 0, 3, 0, 4, 0, 20, 19, 18, 17, 4, 16, 
   15, 4, 14, 13, 12, 11, 4, 10, 4, 9, 8, 7, 4, 6, 5, 4, 
   4, 4, 3, 36, 3, 33, 32, 39, 38, 158, 42, 4, 4, 4, 47, 45, 
   37, 35, 41, 157, 46, 156, 4, 44, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 50, 
   53, 56, 52, 65, 49, 85, 25, 87, 86, 155, 55, 51, 0, 101, 54, 0, 
   84, 101, 64, 154, 150, 153, 100, 152, 151, 148, 149, 147, 0, 0, 29, 29, 
   29, 29, 64, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   70, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   69, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 
   29, 29, 29, 30, 30, 30, 30, 146, 30, 30, 30, 30, 30, 72, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 71, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 
   30, 30, 30, 30, 30, 30, 30, 30, 145, 143, 142, 141, 144, 140, 100, 100, 
   104, 0, 0, 0, 129, 0, 139, 136, 132, 130, 134, 138, 137, 135, 133, 128, 
   131, 127, 103, 126, 0, 0, 125, 122, 0, 0, 119, 123, 121, 120, 118, 124, 
   115, 0, 0, 67, 102, 117, 0, 0, 0, 0, 107, 116, 113, 110, 114, 111, 
   112, 108, 106, 109, 105, 0, 0, 0, 67, 0, 0, 0, 99, 0, 0, 92, 
   93, 66, 98, 63, 62, 60, 61, 88, 83, 80, 82, 97, 96, 94, 95, 91, 
   90, 89, 81, 79, 77, 57, 48, 40, 74, 75, 58, 78, 34, 76, 0, 0, 
   73, 0, 0, 43, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0
};
static const DFATables::State _X1_def [ 159 ] = {
   0, 0, 1, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 28, 29, 0, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 
   0, 0, 0, 25, 0, 29, 0, 30, 0, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 0, 0, 25, 29, 30, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
};
static const unsigned char _X1_equiv_classes [ 256 ] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 3, 3, 3, 3, 3, 
   3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
   6, 8, 10, 12, 11, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 
   35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 37, 39, 41, 42, 44, 43, 
   43, 45, 45, 45, 45, 47, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 
   46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49, 50, 52, 54, 56, 
   55, 58, 59, 60, 61, 63, 64, 65, 66, 67, 62, 62, 68, 69, 70, 71, 
   72, 62, 73, 74, 75, 76, 77, 78, 79, 80, 62, 82, 81, 84, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 
   83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83
   };
static const DFATables::Rule _X1_accept_rule [ 159 ] = {
   -1, 0, 0, -46, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 
   42, 42, 42, 42, 42, 45, 0, 45, 0, 40, 45, 45, 45, 0, 0, 46, 
   42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 9, 42, 42, 42, 29, 1, 
   42, 42, 42, 42, 42, 42, 5, 42, 42, 42, 42, 42, -36, -34, -37, -35, 
   0, 0, -38, 41, 0, 0, -45, 0, -44, 42, 42, 24, 42, 42, 42, 20, 
   42, 42, 42, 30, 42, 42, 27, 42, 42, 42, 25, 6, 42, 11, 42, 31, 
   42, 42, 42, 32, 41, 0, 41, 44, 43, 38, 42, 16, 2, 42, 42, 42, 
   42, 23, 7, 42, 39, 42, 42, 42, 42, 3, 42, 8, 42, 4, 42, 42, 
   42, 13, 28, 42, 42, 42, 42, 42, 10, 18, 42, 42, 42, 14, 42, 42, 
   42, 42, 42, 26, 22, 21, 42, 42, 42, 42, 42, 15, 17, 19, 12
};
         static const RegexMatch _X1
                          ( _X1_base,
                            _X1_check,
                            _X1_def,
                            _X1_next,
                            _X1_accept_rule,
                            _X1_equiv_classes );
         int rule__;
         const char * next;
         switch(rule__ = _X1.MatchText(RegexMatch::start_state,lexer_buf,next)) {
            case 1: {
               L2:; 
#line 19 "setl-lexer.pcc"
              return ((SETL_Token)(rule__ + 255)); 
#line 19 "setl-lexer.pcc"
            } break;
            case 2: { goto L2; } break;
            case 3: { goto L2; } break;
            case 4: { goto L2; } break;
            case 5: { goto L2; } break;
            case 6: { goto L2; } break;
            case 7: { goto L2; } break;
            case 8: { goto L2; } break;
            case 9: { goto L2; } break;
            case 10: { goto L2; } break;
            case 11: { goto L2; } break;
            case 12: { goto L2; } break;
            case 13: { goto L2; } break;
            case 14: { goto L2; } break;
            case 15: { goto L2; } break;
            case 16: { goto L2; } break;
            case 17: { goto L2; } break;
            case 18: { goto L2; } break;
            case 19: { goto L2; } break;
            case 20: { goto L2; } break;
            case 21: { goto L2; } break;
            case 22: { goto L2; } break;
            case 23: { goto L2; } break;
            case 24: { goto L2; } break;
            case 25: { goto L2; } break;
            case 26: { goto L2; } break;
            case 27: { goto L2; } break;
            case 28: { goto L2; } break;
            case 29: { goto L2; } break;
            case 30: { goto L2; } break;
            case 31: { goto L2; } break;
            case 32: { goto L2; } break;
            case 33: { goto L2; } break;
            case 34: { goto L2; } break;
            case 35: { goto L2; } break;
            case 36: { goto L2; } break;
            case 37: { goto L2; } break;
            case 38: { goto L2; } break;
            case 39: { goto L2; } break;
            case 40: { goto L2; } break;
            case 41: { goto L2; } break;
            case 42: { goto L2; } break;
            case 43: { goto L2; } break;
            case 44: { goto L2; } break;
            case 45: {
#line 20 "setl-lexer.pcc"
              return lexer_buf[0]; 
#line 20 "setl-lexer.pcc"
            } break;
            case 46: {} break;
            default: { goto L1; }
         }
      }
   }
   L1:;
}
#line 22 "setl-lexer.pcc"
#line 22 "setl-lexer.pcc"

   return EOF;
}
#line 25 "setl-lexer.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 43
Number of ifs generated      = 0
Number of switches generated = 1
Number of labels             = 1
Number of gotos              = 43
Adaptive matching            = enabled
Fast string matching         = enabled
Inline downcasts             = enabled
--------------------------------------------------------------------------
*/
