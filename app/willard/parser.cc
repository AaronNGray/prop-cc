///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "parser.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_PRINTER_USED
#define PROP_REGEXP_MATCHING_USED
#define PROP_STRCMP_USED
#define PROP_PARSER_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "parser.pcc"
#include "willard-ast.h"
#include "parser.h"
#include "paige.h"
#include <AD/strings/quark.h>

#line 6 "parser.pcc"
#line 14 "parser.pcc"
enum Tokens {
   XX_t_r_u_eXX = 256, XX_f_a_l_s_eXX = 257, XX_i_nXX = 258, 
   XX_a_n_dXX = 259, XX_o_rXX = 260, XX_n_o_tXX = 261, 
   XX_f_o_r_a_l_lXX = 262, XX_e_x_i_s_t_sXX = 263, XX_l_e_tXX = 264, 
   XX_e_n_dXX = 265, XXhlXX = 266, XXhnXX = 267, 
   XXcpXX = 268, XXckXX = 269, XXclXX = 270, 
   XXcnXX = 271, XXciXX = 272, XXcjXX = 273, 
   XXflXX = 274, XXfnXX = 275, XXdnXX = 276, 
   XXcpdnXX = 277, XXdmXX = 278, XXdoXX = 279, 
   XXdmdnXX = 280, XXdodnXX = 281, XXhmXX = 282, 
   XXcdXX = 283, XXcmXX = 284, XXdlXX = 285, 
   XXdkXX = 286, XXcoXX = 287, INTEGER = 288, 
   IDENT = 289
};




///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for Tokens
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, Tokens);
extern PrettyOStream& operator<<(PrettyOStream&, Tokens);
#line 14 "parser.pcc"
#line 14 "parser.pcc"


//
//  Method to get a token from the lexer stream
//
int QueryParser::get_token()
{  
#line 20 "parser.pcc"
#line 23 "parser.pcc"
{
   for (;;) {
      {
static const DFATables::Offset _X1_base [ 66 ] = {
   0, 0, 0, 0, 0, 0, 34, 164, 163, 163, 163, 163, 18, 7, 162, 0, 
   0, 162, 0, 160, 0, 0, 160, 37, 0, 11, 0, 0, 0, 0, 0, 0, 
   49, 0, 145, 0, 145, 144, 0, 144, 144, 144, 144, 142, 0, 0, 0, 77, 
   124, 142, 0, 0, 142, 132, 88, 0, 0, 0, 57, 27, 21, 21, 0, 14, 
   0, 0
};
static const DFATables::State _X1_check [ 211 ] = {
   0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 
   1, 0, 1, 1, 1, 1, 1, 1, 25, 1, 1, 25, 1, 1, 1, 1, 
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 13, 1, 1, 1, 6, 
   12, 13, 6, 32, 23, 63, 32, 12, 61, 6, 23, 59, 0, 60, 6, 6, 
   6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 47, 47, 47, 
   47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 58, 47, 47, 47, 
   47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 
   47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 54, 
   48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
   48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
   48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 53, 52, 43, 49, 42, 
   22, 0, 41, 40, 0, 19, 39, 17, 37, 36, 34, 0, 0, 0, 0, 0, 
   0, 0, 0, 10, 0, 0, 14, 11, 9, 8, 7, 0, 0, 0, 0, 0, 
   0, 0, 0
};
static const DFATables::State _X1_next [ 211 ] = {
   0, 0, 32, 33, 0, 32, 31, 30, 29, 28, 27, 26, 0, 25, 24, 23, 
   22, 0, 21, 20, 19, 18, 17, 6, 48, 16, 15, 22, 6, 6, 14, 6, 
   13, 12, 11, 10, 9, 8, 6, 6, 7, 6, 6, 42, 5, 4, 3, 6, 
   40, 41, 6, 32, 47, 65, 32, 39, 64, 6, 46, 62, 0, 63, 6, 6, 
   6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 47, 47, 47, 
   33, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 61, 47, 47, 47, 
   47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 
   47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 60, 
   48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
   48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 
   48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 59, 58, 56, 57, 55, 
   22, 0, 54, 53, 0, 45, 52, 44, 51, 50, 49, 0, 0, 0, 0, 0, 
   0, 0, 0, 37, 0, 0, 43, 38, 36, 35, 34, 0, 0, 0, 0, 0, 
   0, 0, 0
};
static const DFATables::State _X1_def [ 66 ] = {
   0, 0, 1, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 23, 
   47, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 
   6, 6
};
static const unsigned char _X1_equiv_classes [ 256 ] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 1, 1, 1, 
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
   5, 4, 4, 6, 4, 4, 4, 4, 7, 8, 9, 10, 11, 13, 14, 15, 
   16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 18, 19, 20, 21, 22, 17, 
   17, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 
   23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 25, 24, 26, 24, 28, 
   27, 30, 29, 29, 31, 32, 33, 29, 29, 34, 29, 29, 35, 29, 36, 37, 
   29, 29, 38, 39, 40, 41, 29, 29, 42, 29, 29, 44, 45, 46, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
   43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43
   };
static const DFATables::Rule _X1_accept_rule [ 66 ] = {
   -1, 0, 0, -13, -28, -12, 34, 34, 34, 34, 34, 34, 34, 34, 34, -21, 
   -20, 24, -22, 23, -31, -32, 33, 13, -33, 16, -30, -16, -15, -19, -18, -29, 
   35, -37, 34, 5, 34, 34, 3, 34, 34, 34, 34, 34, -27, -26, -23, 0, 
   0, 34, 6, 9, 34, 34, 34, 10, 4, 1, 34, 34, 34, 34, 2, 34, 
   7, 8
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
         switch(rule__ = _X1.MatchText(RegexMatch::start_state,lexbuf,next)) {
            case 1: {
               L2:; 
#line 21 "parser.pcc"
              return ((Tokens)(rule__ + 255)); 
#line 21 "parser.pcc"
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
            case 35: {} break;
            case 36: {
#line 23 "parser.pcc"
              line_no++; 
#line 23 "parser.pcc"
            } break;
            default: { goto L1; }
         }
      }
   }
   L1:;
}
#line 24 "parser.pcc"
#line 24 "parser.pcc"

   return EOF;
}

//
//  Method to create a nested definition
//
Exp make_defs (Exp (*f)(Ids,Exps,Exp), 
#line 31 "parser.pcc"
a_List<Tuple2<Ids, Exps> > *  
#line 31 "parser.pcc"
 defs, Exp e)
{  
#line 34 "parser.pcc"
{
   if (defs) {
#line 34 "parser.pcc"
     return f(defs->_1._1,defs->_1._2,make_defs(f,defs->_2,e)); 
#line 34 "parser.pcc"
   } else {
#line 33 "parser.pcc"
     return e; 
#line 33 "parser.pcc"
   }
}
#line 35 "parser.pcc"
#line 35 "parser.pcc"

}

//
//
//  This is our parser
//
#line 42 "parser.pcc"
#line 134 "parser.pcc"
///////////////////////////////////////////////////////////////////////////////
// Encoded parser tables for syntax class QueryParser
///////////////////////////////////////////////////////////////////////////////
static const DFATables::Offset QueryParser_base [ 104 ] = {
   0, 0, 4, 6, 8, 13, 15, 21, 142, 12, 0, 0, 0, 0, 142, 0, 
   0, 0, 0, 142, 142, 41, 0, 140, 131, 126, 126, 125, 124, 123, 0, 25, 
   27, 29, 31, 34, 36, 122, 121, 120, 119, 118, 117, 116, 37, 37, 0, 42, 
   0, 116, 115, 115, 114, 21, 0, 0, 0, 29, 76, 78, 81, 83, 85, 77, 
   79, 114, 112, 55, 0, 112, 0, 0, 112, 111, 111, 81, 0, 111, 111, 0, 
   111, 77, 110, 109, 0, 57, 0, 59, 109, 61, 73, 0, 0, 0, 0, 0, 
   0, 53, 9, 82, 0, 63, 0, 0
};
static const DFATables::State QueryParser_check [ 192 ] = {
   0, 1, 0, 68, 68, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
   15, 15, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 53, 53, 1, 1, 
   1, 1, 57, 57, 1, 1, 98, 1, 2, 2, 3, 3, 4, 4, 1, 1, 
   1, 5, 5, 6, 6, 6, 7, 9, 21, 21, 21, 45, 9, 31, 31, 32, 
   32, 33, 33, 34, 34, 7, 35, 35, 36, 36, 44, 44, 97, 45, 45, 47, 
   47, 58, 58, 59, 59, 45, 60, 60, 61, 61, 62, 62, 63, 63, 63, 64, 
   64, 67, 75, 81, 85, 87, 90, 67, 99, 85, 89, 87, 101, 89, 75, 101, 
   88, 0, 0, 0, 0, 0, 0, 0, 0, 81, 99, 99, 0, 81, 0, 0, 
   0, 69, 99, 65, 29, 66, 77, 0, 73, 72, 0, 74, 78, 28, 27, 26, 
   20, 0, 83, 82, 80, 25, 0, 52, 51, 43, 42, 41, 40, 39, 38, 37, 
   24, 23, 19, 50, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0
   };
static const DFATables::State QueryParser_next [ 192 ] = {
   0, 2, 0, 16463, 80, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
   42, 43, 3, 4, 5, 0, 6, 0, 7, 0, 8, 9, 33, 34, 16394, 16395, 
   16396, 16397, 31, 32, 14, 15, 101, 16400, 0, 20, 0, 21, 0, 16406, 16401, 16402, 
   19, 0, 23, 0, 24, 25, 16397, 28, 0, 0, 0, 67, 29, 0, 53, 0, 
   54, 0, 16439, 0, 16440, 26, 0, 57, 0, 58, 24, 66, 16484, 68, 69, 24, 
   16455, 31, 32, 31, 32, 16454, 31, 32, 31, 32, 31, 32, 0, 0, 0, 0, 
   0, 77, 0, 89, 16478, 16479, 99, 78, 67, 29, 97, 78, 16487, 98, 85, 98, 
   16480, 0, 0, 0, 0, 0, 0, 0, 0, 90, 16486, 69, 0, 16475, 0, 0, 
   0, 81, 16454, 0, 52, 16460, 16470, 0, 83, 82, 0, 16468, 87, 51, 50, 49, 
   45, 0, 93, 92, 88, 16432, 0, 75, 74, 65, 64, 63, 62, 61, 60, 59, 
   47, 16430, 44, 73, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 0
   };
static const DFATables::State QueryParser_def [ 104 ] = {
   0, 0, 1, 1, 1, 1, 1, 0, 7, 7, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 15, 15, 0, 15, 15, 0, 0, 0, 0, 0, 0, 1, 
   1, 1, 1, 1, 1, 36, 36, 36, 36, 36, 36, 36, 36, 7, 0, 36, 
   0, 7, 7, 36, 36, 0, 53, 0, 0, 53, 53, 53, 53, 53, 53, 15, 
   15, 15, 0, 7, 0, 0, 0, 0, 0, 0, 15, 15, 0, 0, 0, 0, 
   36, 7, 36, 36, 0, 7, 0, 7, 15, 7, 0, 0, 15, 15, 0, 0, 
   0, 0, 0, 7, 0, 7, 0, 0
};
static const DFATables::State QueryParser_defact [ 104 ] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32810, 32811, 32812, 32813, 0, 32768, 
   32787, 32796, 32797, 32788, 0, 32784, 32785, 0, 32794, 0, 0, 0, 0, 0, 32814, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32786, 0, 
   32790, 0, 0, 0, 0, 32771, 32772, 32773, 32774, 32775, 32776, 32777, 32778, 32779, 32780, 32781, 
   32782, 32783, 0, 0, 0, 0, 32800, 32795, 0, 0, 0, 32804, 32789, 0, 32802, 32769, 
   0, 0, 0, 0, 32793, 0, 32801, 0, 0, 0, 32798, 32806, 32791, 32792, 32805, 32803, 
   32770, 0, 32808, 0, 32807, 0, 32799, 32809
};
static const DFATables::ProductionLength QueryParser_len [ 47 ] = {
   1, 5, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
   2, 2, 3, 1, 1, 4, 3, 6, 6, 5, 1, 3, 1, 1, 3, 5, 
   1, 3, 1, 3, 3, 5, 1, 3, 1, 3, 1, 1, 1, 1, 2
};
static const DFATables::ProductionLength QueryParser_ncount [ 47 ] = {
   1, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
   1, 1, 1, 1, 1, 2, 1, 3, 3, 2, 1, 2, 1, 1, 2, 3, 
   1, 1, 1, 2, 2, 3, 1, 1, 1, 2, 0, 0, 0, 0, 1
};
static const DFATables::ShortSymbol QueryParser_lhs [ 47 ] = {
   36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 
   37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 39, 39, 40, 40, 
   41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 47, 47, 48, 49
};
static const DFATables::EquivMap QueryParser_equiv [ 307 ] = {
   35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 31, 32, 17, 15, 16, 18, 24, 26, 27, 28, 1, 3, 8, 7, 5, 
   6, 20, 21, 22, 23, 9, 10, 11, 12, 13, 14, 4, 19, 29, 0, 2, 
   25, 30, 33, 0, 0, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 
   47, 48, 49
};
///////////////////////////////////////////////////////////////////////////////
// Debugging tables for syntax class QueryParser
///////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG_QueryParser
static const int QueryParser_line[] =
{
   55, 60, 62, 63, 64, 65, 66, 67, 
   68, 69, 70, 71, 72, 73, 74, 75, 
   76, 77, 78, 79, 80, 81, 82, 83, 
   84, 85, 88, 89, 92, 93, 97, 98, 
   101, 102, 105, 106, 110, 113, 116, 117, 
   120, 121, 124, 127, 128, 131, 0
};

static const char * const QueryParser_symbolname[] =
{
   "?", "\"{\"", "\":\"", "\"}\"", "\"|\"", "\"+\"", "\"-\"", "\"*\"", 
   "\"/\"", "\"=\"", "\"/=\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"and\"", 
   "\"or\"", "\"in\"", "\"not\"", "\"#\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", 
   "\"forall\"", "\".\"", "\"exists\"", "\"let\"", "\"end\"", "\",\"", "INTEGER", "\"true\"", 
   "\"false\"", "IDENT", "???", "???", "top", "exp", "exps", "literal", 
   "generators", "rvar", "ids", "defs", "range", "ranges", "integer", "boolean", 
   "id", "???"
};

static const DFATables::ShortSymbol QueryParser_rhs_0[] = { 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_1[] = { 1, 37, 2, 40, 3,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_2[] = { 1, 37, 2, 40, 4, 37, 3,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_3[] = { 37, 5, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_4[] = { 37, 6, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_5[] = { 37, 7, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_6[] = { 37, 8, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_7[] = { 37, 9, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_8[] = { 37, 10, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_9[] = { 37, 11, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_10[] = { 37, 12, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_11[] = { 37, 13, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_12[] = { 37, 14, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_13[] = { 37, 15, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_14[] = { 37, 16, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_15[] = { 37, 17, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_16[] = { 18, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_17[] = { 19, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_18[] = { 20, 37, 21,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_19[] = { 39,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_20[] = { 48,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_21[] = { 48, 20, 38, 21,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_22[] = { 22, 38, 23,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_23[] = { 24, 48, 17, 48, 25, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_24[] = { 26, 48, 17, 48, 25, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_25[] = { 27, 43, 17, 37, 28,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_26[] = { 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_27[] = { 37, 29, 38,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_28[] = { 46,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_29[] = { 47,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_30[] = { 41, 17, 44,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_31[] = { 41, 17, 44, 29, 40,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_32[] = { 48,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_33[] = { 22, 42, 23,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_34[] = { 48,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_35[] = { 48, 29, 42,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_36[] = { 48, 9, 37,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_37[] = { 48, 9, 37, 29, 43,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_38[] = { 48,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_39[] = { 22, 45, 23,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_40[] = { 48,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_41[] = { 48, 29, 45,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_42[] = { 30,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_43[] = { 31,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_44[] = { 32,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_45[] = { 33,  -1 };
static const DFATables::ShortSymbol QueryParser_rhs_46[] = { 36, 35,  -1 };
static const DFATables::ShortSymbol * QueryParser_rhs[] =
{
   QueryParser_rhs_0, 
   QueryParser_rhs_1, 
   QueryParser_rhs_2, 
   QueryParser_rhs_3, 
   QueryParser_rhs_4, 
   QueryParser_rhs_5, 
   QueryParser_rhs_6, 
   QueryParser_rhs_7, 
   QueryParser_rhs_8, 
   QueryParser_rhs_9, 
   QueryParser_rhs_10, 
   QueryParser_rhs_11, 
   QueryParser_rhs_12, 
   QueryParser_rhs_13, 
   QueryParser_rhs_14, 
   QueryParser_rhs_15, 
   QueryParser_rhs_16, 
   QueryParser_rhs_17, 
   QueryParser_rhs_18, 
   QueryParser_rhs_19, 
   QueryParser_rhs_20, 
   QueryParser_rhs_21, 
   QueryParser_rhs_22, 
   QueryParser_rhs_23, 
   QueryParser_rhs_24, 
   QueryParser_rhs_25, 
   QueryParser_rhs_26, 
   QueryParser_rhs_27, 
   QueryParser_rhs_28, 
   QueryParser_rhs_29, 
   QueryParser_rhs_30, 
   QueryParser_rhs_31, 
   QueryParser_rhs_32, 
   QueryParser_rhs_33, 
   QueryParser_rhs_34, 
   QueryParser_rhs_35, 
   QueryParser_rhs_36, 
   QueryParser_rhs_37, 
   QueryParser_rhs_38, 
   QueryParser_rhs_39, 
   QueryParser_rhs_40, 
   QueryParser_rhs_41, 
   QueryParser_rhs_42, 
   QueryParser_rhs_43, 
   QueryParser_rhs_44, 
   QueryParser_rhs_45, 
   QueryParser_rhs_46
};


#endif

///////////////////////////////////////////////////////////////////////////////
// Semantic value stack for syntax class QueryParser
///////////////////////////////////////////////////////////////////////////////
union QueryParser_semantic_stack_type {
   int dummy;
#line 58 "parser.pcc"
   typedef Exp ATTRIBUTE_0;
   ATTRIBUTE_0 _188, _183, _142, _139, _135, _131, _129, _123, _121, _115, _110, _104, _101, _98, _95, _93, _91, _89, _87, _85, _83, _81, _80, _78, _76, _75, _73, _71, _70, _68, _66, _65, _63, _61, _60, _58, _56, _55, _53, _51, _50, _48, _46, _45, _43, _41, _40, _38, _36, _35, _33, _31, _30, _28, _26, _25, _23, _21, _20, _17, _13, _11, _6, _4, _2;
#line 88 "parser.pcc"
   typedef Exps ATTRIBUTE_1;
   ATTRIBUTE_1 _144, _141, _138, _112, _107;
#line 92 "parser.pcc"
   typedef Literal ATTRIBUTE_2;
   ATTRIBUTE_2 _149, _146, _99;
#line 96 "parser.pcc"
   typedef a_List<Tuple2<Ids, Exps> > *  ATTRIBUTE_3;
   ATTRIBUTE_3 _162, _157, _152, _15, _8;
#line 101 "parser.pcc"
   typedef Ids ATTRIBUTE_4;
   ATTRIBUTE_4 _167, _164, _158, _153;
#line 105 "parser.pcc"
   typedef Ids ATTRIBUTE_5;
   ATTRIBUTE_5 _178, _175, _172, _169;
#line 109 "parser.pcc"
   typedef struct { Ids ids; Exps exps;  } ATTRIBUTE_6;
   ATTRIBUTE_6 _190, _185, _180, _133;
#line 116 "parser.pcc"
   typedef Exps ATTRIBUTE_7;
   ATTRIBUTE_7 _195, _192, _160, _155;
#line 120 "parser.pcc"
   typedef Exps ATTRIBUTE_8;
   ATTRIBUTE_8 _206, _203, _200, _197;
#line 124 "parser.pcc"
   typedef int ATTRIBUTE_9;
   ATTRIBUTE_9 _208, _147;
#line 127 "parser.pcc"
   typedef Bool ATTRIBUTE_10;
   ATTRIBUTE_10 _214, _211, _150;
#line 131 "parser.pcc"
   typedef Id ATTRIBUTE_11;
   ATTRIBUTE_11 _217, _204, _201, _193, _186, _181, _176, _173, _165, _127, _125, _119, _117, _105, _102;
};


///////////////////////////////////////////////////////////////////////////////
// Parser driver for syntax class QueryParser
///////////////////////////////////////////////////////////////////////////////
inline void QueryParser::action_driver(const Rule _r_)
{
   QueryParser_semantic_stack_type syn_;
   ////////////////////////////////////////////////////////////////////////////
   // Tracing code for syntax class QueryParser
   ////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_QueryParser
   {  cerr << "Reducing via rule " << _r_ << " at line "
           << QueryParser_line[_r_] << ", "
           << QueryParser_symbolname[QueryParser_lhs[_r_]] << " <- ";
      for (const DFATables::ShortSymbol * _p_ = QueryParser_rhs[_r_]; *_p_ >= 0; _p_++)
         cerr << QueryParser_symbolname[*_p_] << ' ';
      cerr << '\n';
   }
#endif

   ////////////////////////////////////////////////////////////////////////////
   // Actions for syntax class QueryParser
   ////////////////////////////////////////////////////////////////////////////
   t__ -= QueryParser_ncount[_r_];
   switch (_r_) {

#undef to__
#define to__ 0
      case 0: {
#line 55 "parser.pcc"
        query = t__[1+to__]._2; 
#line 55 "parser.pcc"
} break;
      case 1: {
#line 60 "parser.pcc"
        syn_._4 = make_defs(GENERATOR,t__[2+to__]._8,t__[1+to__]._6); 
#line 60 "parser.pcc"
} break;
      case 2: {
#line 62 "parser.pcc"
        syn_._11 = make_defs(GENERATOR,t__[2+to__]._15,GUARD(t__[3+to__]._17,t__[1+to__]._13)); 
#line 62 "parser.pcc"
} break;
      case 3: {
#line 63 "parser.pcc"
        syn_._20 = OP("+",
#line 63 "parser.pcc"
#line 63 "parser.pcc"
         list_1_(t__[1+to__]._21,list_1_(t__[2+to__]._23))
#line 63 "parser.pcc"
#line 63 "parser.pcc"
         ); 
#line 63 "parser.pcc"
} break;
      case 4: {
#line 64 "parser.pcc"
        syn_._25 = OP("-",
#line 64 "parser.pcc"
#line 64 "parser.pcc"
         list_1_(t__[1+to__]._26,list_1_(t__[2+to__]._28))
#line 64 "parser.pcc"
#line 64 "parser.pcc"
         ); 
#line 64 "parser.pcc"
} break;
      case 5: {
#line 65 "parser.pcc"
        syn_._30 = OP("*",
#line 65 "parser.pcc"
#line 65 "parser.pcc"
         list_1_(t__[1+to__]._31,list_1_(t__[2+to__]._33))
#line 65 "parser.pcc"
#line 65 "parser.pcc"
         ); 
#line 65 "parser.pcc"
} break;
      case 6: {
#line 66 "parser.pcc"
        syn_._35 = OP("/",
#line 66 "parser.pcc"
#line 66 "parser.pcc"
         list_1_(t__[1+to__]._36,list_1_(t__[2+to__]._38))
#line 66 "parser.pcc"
#line 66 "parser.pcc"
         ); 
#line 66 "parser.pcc"
} break;
      case 7: {
#line 67 "parser.pcc"
        syn_._40 = OP("=",
#line 67 "parser.pcc"
#line 67 "parser.pcc"
         list_1_(t__[1+to__]._41,list_1_(t__[2+to__]._43))
#line 67 "parser.pcc"
#line 67 "parser.pcc"
         ); 
#line 67 "parser.pcc"
} break;
      case 8: {
#line 68 "parser.pcc"
        syn_._45 = OP("/=",
#line 68 "parser.pcc"
#line 68 "parser.pcc"
         list_1_(t__[1+to__]._46,list_1_(t__[2+to__]._48))
#line 68 "parser.pcc"
#line 68 "parser.pcc"
         ); 
#line 68 "parser.pcc"
} break;
      case 9: {
#line 69 "parser.pcc"
        syn_._50 = OP("<",
#line 69 "parser.pcc"
#line 69 "parser.pcc"
         list_1_(t__[1+to__]._51,list_1_(t__[2+to__]._53))
#line 69 "parser.pcc"
#line 69 "parser.pcc"
         ); 
#line 69 "parser.pcc"
} break;
      case 10: {
#line 70 "parser.pcc"
        syn_._55 = OP(">",
#line 70 "parser.pcc"
#line 70 "parser.pcc"
         list_1_(t__[1+to__]._56,list_1_(t__[2+to__]._58))
#line 70 "parser.pcc"
#line 70 "parser.pcc"
         ); 
#line 70 "parser.pcc"
} break;
      case 11: {
#line 71 "parser.pcc"
        syn_._60 = OP("<=",
#line 71 "parser.pcc"
#line 71 "parser.pcc"
         list_1_(t__[1+to__]._61,list_1_(t__[2+to__]._63))
#line 71 "parser.pcc"
#line 71 "parser.pcc"
         ); 
#line 71 "parser.pcc"
} break;
      case 12: {
#line 72 "parser.pcc"
        syn_._65 = OP(">=",
#line 72 "parser.pcc"
#line 72 "parser.pcc"
         list_1_(t__[1+to__]._66,list_1_(t__[2+to__]._68))
#line 72 "parser.pcc"
#line 72 "parser.pcc"
         ); 
#line 72 "parser.pcc"
} break;
      case 13: {
#line 73 "parser.pcc"
        syn_._70 = OP("and",
#line 73 "parser.pcc"
#line 73 "parser.pcc"
         list_1_(t__[1+to__]._71,list_1_(t__[2+to__]._73))
#line 73 "parser.pcc"
#line 73 "parser.pcc"
         ); 
#line 73 "parser.pcc"
} break;
      case 14: {
#line 74 "parser.pcc"
        syn_._75 = OP("or",
#line 74 "parser.pcc"
#line 74 "parser.pcc"
         list_1_(t__[1+to__]._76,list_1_(t__[2+to__]._78))
#line 74 "parser.pcc"
#line 74 "parser.pcc"
         ); 
#line 74 "parser.pcc"
} break;
      case 15: {
#line 75 "parser.pcc"
        syn_._80 = OP("in",
#line 75 "parser.pcc"
#line 75 "parser.pcc"
         list_1_(t__[1+to__]._81,list_1_(t__[2+to__]._83))
#line 75 "parser.pcc"
#line 75 "parser.pcc"
         ); 
#line 75 "parser.pcc"
} break;
      case 16: {
#line 76 "parser.pcc"
        syn_._85 = OP("not",
#line 76 "parser.pcc"
#line 76 "parser.pcc"
         list_1_(t__[1+to__]._87)
#line 76 "parser.pcc"
#line 76 "parser.pcc"
         ); 
#line 76 "parser.pcc"
} break;
      case 17: {
#line 77 "parser.pcc"
        syn_._89 = Count(t__[1+to__]._91); 
#line 77 "parser.pcc"
} break;
      case 18: {
#line 78 "parser.pcc"
        syn_._93 = t__[1+to__]._95; 
#line 78 "parser.pcc"
} break;
      case 19: {
#line 79 "parser.pcc"
        syn_._98 = LIT(t__[1+to__]._99); 
#line 79 "parser.pcc"
} break;
      case 20: {
#line 80 "parser.pcc"
        syn_._101 = ID(t__[1+to__]._102); 
#line 80 "parser.pcc"
} break;
      case 21: {
#line 81 "parser.pcc"
        syn_._104 = APP(t__[1+to__]._105,t__[2+to__]._107); 
#line 81 "parser.pcc"
} break;
      case 22: {
#line 82 "parser.pcc"
        syn_._110 = TUPLE(t__[1+to__]._112); 
#line 82 "parser.pcc"
} break;
      case 23: {
#line 83 "parser.pcc"
        syn_._115 = FORALL(t__[1+to__]._117,ID(t__[2+to__]._119),t__[3+to__]._121); 
#line 83 "parser.pcc"
} break;
      case 24: {
#line 84 "parser.pcc"
        syn_._123 = EXISTS(t__[1+to__]._125,ID(t__[2+to__]._127),t__[3+to__]._129); 
#line 84 "parser.pcc"
} break;
      case 25: {
#line 85 "parser.pcc"
        syn_._131 = PaigeGoyal::make_let(t__[1+to__]._133.ids,t__[1+to__]._133.exps,t__[2+to__]._135); 
#line 85 "parser.pcc"
} break;
      case 26: {
#line 88 "parser.pcc"
        syn_._138 = 
#line 88 "parser.pcc"
#line 88 "parser.pcc"
         list_1_(t__[1+to__]._139)
#line 88 "parser.pcc"
#line 88 "parser.pcc"
         ; 
#line 88 "parser.pcc"
} break;
      case 27: {
#line 89 "parser.pcc"
        syn_._141 = 
#line 89 "parser.pcc"
#line 89 "parser.pcc"
         list_1_(t__[1+to__]._142,t__[2+to__]._144)
#line 89 "parser.pcc"
#line 89 "parser.pcc"
         ; 
#line 89 "parser.pcc"
} break;
      case 28: {
#line 92 "parser.pcc"
        syn_._146 = INT(t__[1+to__]._147); 
#line 92 "parser.pcc"
} break;
      case 29: {
#line 93 "parser.pcc"
        syn_._149 = BOOL(t__[1+to__]._150); 
#line 93 "parser.pcc"
} break;
      case 30: {
#line 97 "parser.pcc"
        syn_._152 = 
#line 97 "parser.pcc"
#line 97 "parser.pcc"
         list_1_(mkTuple2(t__[1+to__]._153,t__[2+to__]._155))
#line 97 "parser.pcc"
#line 97 "parser.pcc"
         ; 
#line 97 "parser.pcc"
} break;
      case 31: {
#line 98 "parser.pcc"
        syn_._157 = 
#line 98 "parser.pcc"
#line 98 "parser.pcc"
         list_1_(mkTuple2(t__[1+to__]._158,t__[2+to__]._160),t__[3+to__]._162)
#line 98 "parser.pcc"
#line 98 "parser.pcc"
         ; 
#line 98 "parser.pcc"
} break;
      case 32: {
#line 101 "parser.pcc"
        syn_._164 = 
#line 101 "parser.pcc"
#line 101 "parser.pcc"
         list_1_(t__[1+to__]._165)
#line 101 "parser.pcc"
#line 101 "parser.pcc"
         ; 
#line 101 "parser.pcc"
} break;
      case 33: {
#line 102 "parser.pcc"
        syn_._167 = t__[1+to__]._169; 
#line 102 "parser.pcc"
} break;
      case 34: {
#line 105 "parser.pcc"
        syn_._172 = 
#line 105 "parser.pcc"
#line 105 "parser.pcc"
         list_1_(t__[1+to__]._173)
#line 105 "parser.pcc"
#line 105 "parser.pcc"
         ; 
#line 105 "parser.pcc"
} break;
      case 35: {
#line 106 "parser.pcc"
        syn_._175 = 
#line 106 "parser.pcc"
#line 106 "parser.pcc"
         list_1_(t__[1+to__]._176,t__[2+to__]._178)
#line 106 "parser.pcc"
#line 106 "parser.pcc"
         ; 
#line 106 "parser.pcc"
} break;
      case 36: {
#line 110 "parser.pcc"
        syn_._180.ids = 
#line 110 "parser.pcc"
#line 110 "parser.pcc"
         list_1_(t__[1+to__]._181)
#line 110 "parser.pcc"
#line 110 "parser.pcc"
         ; syn_._180.exps =
#line 110 "parser.pcc"
#line 110 "parser.pcc"
         list_1_(t__[2+to__]._183)
#line 110 "parser.pcc"
#line 110 "parser.pcc"
         ; 
#line 110 "parser.pcc"
} break;
      case 37: {
#line 111 "parser.pcc"
        syn_._185.ids  = 
#line 111 "parser.pcc"
#line 111 "parser.pcc"
         list_1_(t__[1+to__]._186,t__[3+to__]._190.ids)
#line 111 "parser.pcc"
#line 111 "parser.pcc"
         ; 
         					  syn_._185.exps = 
#line 112 "parser.pcc"
#line 112 "parser.pcc"
         list_1_(t__[2+to__]._188,t__[3+to__]._190.exps)
#line 112 "parser.pcc"
#line 112 "parser.pcc"
         ; 
         					
#line 113 "parser.pcc"
} break;
      case 38: {
#line 116 "parser.pcc"
        syn_._192 = 
#line 116 "parser.pcc"
#line 116 "parser.pcc"
         list_1_(ID(t__[1+to__]._193))
#line 116 "parser.pcc"
#line 116 "parser.pcc"
         ; 
#line 116 "parser.pcc"
} break;
      case 39: {
#line 117 "parser.pcc"
        syn_._195 = t__[1+to__]._197; 
#line 117 "parser.pcc"
} break;
      case 40: {
#line 120 "parser.pcc"
        syn_._200 = 
#line 120 "parser.pcc"
#line 120 "parser.pcc"
         list_1_(ID(t__[1+to__]._201))
#line 120 "parser.pcc"
#line 120 "parser.pcc"
         ; 
#line 120 "parser.pcc"
} break;
      case 41: {
#line 121 "parser.pcc"
        syn_._203 = 
#line 121 "parser.pcc"
#line 121 "parser.pcc"
         list_1_(ID(t__[1+to__]._204),t__[2+to__]._206)
#line 121 "parser.pcc"
#line 121 "parser.pcc"
         ; 
#line 121 "parser.pcc"
} break;
      case 42: {
#line 124 "parser.pcc"
        syn_._208 = atol(lexbuf.text()); 
#line 124 "parser.pcc"
} break;
      case 43: {
#line 127 "parser.pcc"
        syn_._211 = true; 
#line 127 "parser.pcc"
} break;
      case 44: {
#line 128 "parser.pcc"
        syn_._214 = false; 
#line 128 "parser.pcc"
} break;
      case 45: {
#line 131 "parser.pcc"
        syn_._217 = Quark(lexbuf.text()); 
#line 131 "parser.pcc"
} break;
   }
   if (t__ >= bot__ + stack_size__) grow_semantic_stack();
   *++t__ = syn_;
}

///////////////////////////////////////////////////////////////////////////////
// Parsing method for parser class QueryParser
///////////////////////////////////////////////////////////////////////////////
void QueryParser::parse()
{
   QueryParser_semantic_stack_type stack__[INITIAL_STACK_SIZE_];
   t__ = bot__ = stack__;
   stack_size__ = sizeof(stack__)/sizeof(stack__[0]) - 1;
   heap_allocated__ = 0;
   parser_prefix();
   LR1ParserDriver<QueryParser,(LR1Parser::State)30> drv;
   drv.driver(*this);
   parser_suffix();
   if (bot__ != stack__) delete [] bot__;
}

void QueryParser::adjust_stack(int offset) { t__ += offset; }

void QueryParser::grow_semantic_stack()
{
   int N = (stack_size__ + 1) * 2;
   QueryParser_semantic_stack_type * S = new QueryParser_semantic_stack_type [N];
   if (N >= LR1Parser::SEMANTIC_STACK_SIZE) 
      error_report("Warning: semantic stack overflow");
   memcpy(S, bot__, sizeof(QueryParser_semantic_stack_type) * (stack_size__ + 1));
   if (heap_allocated__) delete [] bot__;
   t__ = S + (t__ - bot__);
   bot__ = S;
   stack_size__ = N - 1;
   heap_allocated__ = 1;
}

QueryParser::QueryParser ()
  : Super(QueryParser_base,QueryParser_check,QueryParser_def,QueryParser_defact,QueryParser_next,
          QueryParser_len,QueryParser_ncount,QueryParser_lhs,QueryParser_equiv,290,290,304)
{
}
#line 134 "parser.pcc"
#line 134 "parser.pcc"



//
//  This is our parser driver routine
//
Exp QueryParser::read()
{  query = ID("x");
   line_no = 1;
   parse();
   return query;
}

//
//  This is the parser error handler
//
QueryParser::ErrorAction QueryParser::error_report(const char message[])
{  cerr << line_no << ": " << message << " near: " << lexbuf.text() << '\n';
   return Retry;
}
#line 154 "parser.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 33
Number of ifs generated      = 1
Number of switches generated = 1
Number of labels             = 1
Number of gotos              = 33
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
