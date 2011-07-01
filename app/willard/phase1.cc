///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase1.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase1.pcc"
#include <AD/pretty/postream.h>
#include "phase1.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for phase1 
//
///////////////////////////////////////////////////////////////////////////////
Phase1::Phase1() {}
Phase1::~Phase1() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to invoke phase1 
//
///////////////////////////////////////////////////////////////////////////////
Exp Phase1::phase1(Exp e) 
{  message("DNF construction and simplification phase", e); 
   (*this)(e); return e; 
}

///////////////////////////////////////////////////////////////////////////////
//
//  Transformation rules
//
///////////////////////////////////////////////////////////////////////////////
#line 27 "phase1.pcc"
#line 95 "phase1.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_Phase1
#define DEBUG_Phase1(repl,redex,file,line,rule) repl
#else
static const char * Phase1_file_name = "phase1.pcc";
#endif

static const TreeTables::Offset Phase1_accept_base [ 86 ] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 
   2, 2, 3, 4, 4, 4, 4, 5, 6, 6, 6, 7, 9, 9, 9, 9, 
   9, 10, 12, 14, 16, 18, 20, 21, 22, 25, 28, 29, 29, 30, 32, 33, 
   33, 33, 34, 36, 36, 36, 37, 39, 41, 43, 45, 47, 49, 52, 55, 61, 
   67, 69, 71, 73, 75, 77, 79, 83, 87, 89, 91, 92, 92, 92, 92, 93, 
   97, 99, 101, 103, 106, 109
};
static const TreeTables::ShortRule Phase1_accept_vector [ 113 ] = {
   -1, 38, -1, 32, -1, 33, -1, 30, 31, -1, 29, -1, 28, -1, 27, -1, 
   26, -1, 25, -1, 24, -1, 19, 21, -1, 15, 17, -1, 8, -1, 23, -1, 
   41, -1, 42, 43, -1, 5, -1, 4, -1, 3, -1, 2, -1, 1, -1, 0, 
   -1, 20, 22, -1, 16, 18, -1, 7, 19, 20, 21, 22, -1, 6, 15, 16, 
   17, 18, -1, 14, -1, 13, -1, 12, -1, 11, -1, 10, -1, 9, -1, 39, 
   20, 22, -1, 34, 16, 18, -1, 39, -1, 34, -1, 37, -1, 40, 16, 18, 
   -1, 40, -1, 36, -1, 35, -1, 35, 40, -1, 34, 35, -1, 35, 15, 17, 
   -1
};
static const TreeTables::ShortState Phase1_theta_1[1][2] = {
   { 0, 16 }
};


static const TreeTables::ShortState Phase1_theta_2[10][20] = {
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0 },
   { 0, 0, 0, 38, 0, 0, 0, 59, 0, 69, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0 },
   { 0, 0, 0, 37, 0, 0, 0, 58, 0, 68, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0 },
   { 0, 0, 0, 36, 0, 0, 0, 57, 0, 67, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0 },
   { 0, 0, 0, 35, 0, 0, 0, 56, 0, 66, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0 },
   { 0, 0, 0, 34, 0, 0, 0, 55, 0, 65, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0 },
   { 0, 0, 0, 33, 0, 0, 0, 54, 0, 64, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0 },
   { 0, 0, 32, 32, 41, 0, 0, 32, 61, 63, 71, 73, 0, 79, 80, 0, 
   82, 83, 84, 85 },
   { 0, 0, 31, 31, 40, 0, 0, 31, 60, 62, 70, 72, 0, 60, 31, 0, 
   31, 31, 72, 40 },
   { 0, 22, 0, 0, 0, 42, 45, 0, 0, 0, 0, 0, 74, 0, 0, 81, 
   0, 0, 0, 0 }
};


static const TreeTables::ShortState Phase1_theta_4[3] = {
   0, 20, 21
};


static const TreeTables::ShortState Phase1_theta_8[1][1][4] = {
   { { 0, 27, 46, 50 } }
};


static const TreeTables::ShortState Phase1_theta_10[2][2][2] = {
   { { 0, 0 },
   { 0, 0 } },
   { { 0, 0 },
   { 0, 23 } }
};


static const TreeTables::ShortState Phase1_theta_11[1][1][2] = {
   { { 0, 18 } }
};


static const TreeTables::ShortState Phase1_theta_13[7][7] = {
   { 0, 17, 24, 24, 24, 43, 75 },
   { 0, 19, 24, 25, 24, 43, 75 },
   { 0, 26, 24, 24, 39, 43, 75 },
   { 0, 29, 28, 28, 28, 44, 78 },
   { 0, 30, 24, 24, 24, 43, 75 },
   { 0, 49, 48, 48, 48, 47, 77 },
   { 0, 53, 52, 52, 52, 51, 76 }
};


static const TreeTables::ShortState Phase1_check [ 228 ] = {
   0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 18, 15, 5, 5, 
   2, 4, 13, 4, 0, 12, 0, 0, 4, 4, 4, 0, 4, 4, 4, 12, 
   12, 14, 0, 14, 0, 0, 0, 4, 12, 12, 14, 4, 4, 14, 14, 4, 
   4, 4, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 12, 12, 12, 12, 
   0, 14, 0, 0, 0, 14, 12, 12, 12, 12, 0, 4, 4, 4, 4, 12, 
   12, 19, 12, 12, 12, 12, 0, 0, 0, 19, 19, 19, 0, 0, 0, 0, 
   0, 0, 0, 0, 19, 19, 0, 0, 0, 0, 0, 0, 0, 19, 19, 19, 
   0, 0, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 19, 19, 19, 19, 0, 0, 0, 0, 0, 0, 19, 19, 19, 19, 19, 
   20, 0, 0, 0, 19, 19, 19, 19, 19, 19, 19, 0, 0, 0, 0, 20, 
   0, 20, 0, 0, 0, 0, 0, 0, 20, 0, 0, 20, 20, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 
   0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0
};
TreeTables::ShortState Phase1_next [ 228 ] = {
   0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1, 1, 2, 
   1, 1, 1, 1, 0, 1, 0, 0, 2, 3, 1, 0, 4, 5, 6, 2, 
   3, 1, 0, 1, 0, 0, 0, 7, 2, 3, 1, 8, 9, 1, 1, 10, 
   11, 12, 0, 13, 14, 15, 0, 0, 0, 0, 0, 0, 2, 3, 2, 3, 
   0, 1, 0, 0, 0, 1, 2, 3, 2, 3, 0, 16, 17, 18, 19, 3, 
   3, 1, 3, 3, 3, 3, 0, 0, 0, 2, 3, 4, 0, 0, 0, 0, 
   0, 0, 0, 0, 5, 6, 0, 0, 0, 0, 0, 0, 0, 5, 6, 4, 
   0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 5, 6, 5, 6, 0, 0, 0, 0, 0, 0, 5, 6, 5, 6, 4, 
   1, 0, 0, 0, 6, 6, 4, 6, 6, 6, 6, 0, 0, 0, 0, 2, 
   0, 3, 0, 0, 0, 0, 0, 0, 4, 0, 0, 5, 2, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 
   0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0
};
inline void  Phase1::labeler(char const * redex,int& s__,int)
{
   {
      if (_less_string(redex,">=")) {
         if (_less_string(redex,"=")) {
            if (_equal_string(redex,"/=")) {s__ = 4;}
            else if (_equal_string(redex,"<")) {s__ = 7;}
            else if (_equal_string(redex,"<=")) {s__ = 8;}
            else {s__ = 0;}
         } else {
            if (_equal_string(redex,"=")) {s__ = 3;}
            else if (_equal_string(redex,">")) {s__ = 5;}
            else {s__ = 0;}
         }
      } else {
         if (_equal_string(redex,">=")) {s__ = 6;}
         else if (_equal_string(redex,"and")) {s__ = 9;}
         else if (_equal_string(redex,"not")) {s__ = 11;}
         else if (_equal_string(redex,"or")) {s__ = 10;}
         else {s__ = 0;}
      }
   }
}

inline void  Phase1::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Phase1::labeler (Exp & redex, int& s__, int r__)
{
replacement__:
   int cached__;
   if (r__ && boxed(redex) && (cached__ = redex->get_rewrite_state()) != BURS::undefined_state)
   { s__ = cached__; return; }
   switch(redex->tag__) {
      case a_Exp::tag_OP: { 
         int s0__;
         int s1__;
         labeler(_OP(redex)->_1, s0__, r__);
         labeler(_OP(redex)->_2, s1__, r__);
         s__ = Phase1_theta_2[Phase1_check[0 + s0__] == 3 ? Phase1_next[0 + s0__] : 0][Phase1_check[0 + s1__] == 4 ? Phase1_next[0 + s1__] : 0]; } break;
      case a_Exp::tag_APP: { 
         int s0__;
         int s1__;
         labeler(_APP(redex)->_1, s0__, r__);
         labeler(_APP(redex)->_2, s1__, r__);
         s__ = 0;} break;
      case a_Exp::tag_LIT: { 
         int s0__;
         labeler(_LIT(redex)->LIT, s0__, r__);
         s__ = Phase1_theta_4[Phase1_check[0 + s0__] == 5 ? Phase1_next[0 + s0__] : 0]; } break;
      case a_Exp::tag_ID: { 
         int s0__;
         labeler(_ID(redex)->ID, s0__, r__);
         s__ = 12;} break;
      case a_Exp::tag_TUPLE: { 
         int s0__;
         labeler(_TUPLE(redex)->TUPLE, s0__, r__);
         s__ = 0;} break;
      case a_Exp::tag_FORALL: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_FORALL(redex)->_1, s0__, r__);
         labeler(_FORALL(redex)->_2, s1__, r__);
         labeler(_FORALL(redex)->_3, s2__, r__);
         s__ = 13;} break;
      case a_Exp::tag_EXISTS: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_EXISTS(redex)->_1, s0__, r__);
         labeler(_EXISTS(redex)->_2, s1__, r__);
         labeler(_EXISTS(redex)->_3, s2__, r__);
         s__ = Phase1_theta_8[0][0][Phase1_check[0 + s2__] == 12 ? Phase1_next[0 + s2__] : 0]; } break;
      case a_Exp::tag_GUARD: { 
         int s0__;
         int s1__;
         labeler(_GUARD(redex)->_1, s0__, r__);
         labeler(_GUARD(redex)->_2, s1__, r__);
         s__ = 0;} break;
      case a_Exp::tag_GENERATOR: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_GENERATOR(redex)->_1, s0__, r__);
         labeler(_GENERATOR(redex)->_2, s1__, r__);
         labeler(_GENERATOR(redex)->_3, s2__, r__);
         s__ = Phase1_theta_10[Phase1_check[2 + s0__] == 13 ? Phase1_next[2 + s0__] : 0][Phase1_check[16 + s1__] == 14 ? Phase1_next[16 + s1__] : 0][Phase1_check[1 + s2__] == 15 ? Phase1_next[1 + s2__] : 0]; } break;
      default: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_LET(redex)->_1, s0__, r__);
         labeler(_LET(redex)->_2, s1__, r__);
         labeler(_LET(redex)->_3, s2__, r__);
         s__ = Phase1_theta_11[0][0][Phase1_check[0 + s2__] == 18 ? Phase1_next[0 + s2__] : 0]; } break;
   }
   const TreeTables::ShortRule * o__ = Phase1_accept_vector + Phase1_accept_base[s__];
accept__:
   switch (*o__) {
      case 43: if (is_free(_EXISTS(redex)->_1,_OP(_EXISTS(redex)->_3)->_2->_1))
      {
#line 95 "phase1.pcc"
         { redex = DEBUG_Phase1(And(_OP(_EXISTS(redex)->_3)->_2->_1,EXISTS(_EXISTS(redex)->_1,_EXISTS(redex)->_2,_OP(_EXISTS(redex)->_3)->_2->_2->_1)),redex,Phase1_file_name,95,"EXISTS (x, S, OP (\"and\", #[f, g])) | is_free(redex!EXISTS.1,redex!EXISTS.3!OP.2!#[...].1): ...");
           r__ = 1; goto replacement__; }
#line 95 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 42: if (is_free(_EXISTS(redex)->_1,_OP(_EXISTS(redex)->_3)->_2->_2->_1))
      {
#line 94 "phase1.pcc"
         { redex = DEBUG_Phase1(And(EXISTS(_EXISTS(redex)->_1,_EXISTS(redex)->_2,_OP(_EXISTS(redex)->_3)->_2->_1),_OP(_EXISTS(redex)->_3)->_2->_2->_1),redex,Phase1_file_name,94,"EXISTS (x, S, OP (\"and\", #[f, g])) | is_free(redex!EXISTS.1,redex!EXISTS.3!OP.2!#[...].2!#[...].1): ...");
           r__ = 1; goto replacement__; }
#line 94 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 41: {
#line 93 "phase1.pcc"
         Exp  repl__;
         int _X1 = _OP(_EXISTS(redex)->_3)->_2->_2->_1->get_rewrite_state();
         switch (_X1) {
            case 31: repl__ = OP("or",list_1_(EXISTS(_EXISTS(redex)->_1,_EXISTS(redex)->_2,_OP(_EXISTS(redex)->_3)->_2->_1),list_1_(OP("or",list_1_(EXISTS(_EXISTS(redex)->_1,_EXISTS(redex)->_2,_OP(_OP(_EXISTS(redex)->_3)->_2->_2->_1)->_2->_1),list_1_(EXISTS(_EXISTS(redex)->_1,_EXISTS(redex)->_2,_OP(_OP(_EXISTS(redex)->_3)->_2->_2->_1)->_2->_2->_1))))))); break;
            default: 
            repl__ = Or(EXISTS(_EXISTS(redex)->_1,_EXISTS(redex)->_2,_OP(_EXISTS(redex)->_3)->_2->_1),EXISTS(_EXISTS(redex)->_1,_EXISTS(redex)->_2,_OP(_EXISTS(redex)->_3)->_2->_2->_1)); break;
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,93,"EXISTS (x, S, OP (\"or\", #[f, g])): ...");
           r__ = 1; goto replacement__; }
#line 93 "phase1.pcc"
} break;
      case 40: {
#line 88 "phase1.pcc"
         Exp  repl__;
         int _X2 = _OP(_OP(redex)->_2->_1)->_2->_2->_1->get_rewrite_state();
         switch (_X2) {
            case 32: repl__ = OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1,list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_2->_1,list_1_(_OP(redex)->_2->_2->_1))))))))); break;
            default: 
            repl__ = And(_OP(_OP(redex)->_2->_1)->_2->_1,And(_OP(_OP(redex)->_2->_1)->_2->_2->_1,_OP(redex)->_2->_2->_1)); break;
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,88,"OP (\"and\", #[OP (\"and\", #[a, b]), c]): ...");
           r__ = 1; goto replacement__; }
#line 93 "phase1.pcc"
} break;
      case 39: {
#line 87 "phase1.pcc"
         Exp  repl__;
         int _X3 = _OP(_OP(redex)->_2->_1)->_2->_2->_1->get_rewrite_state();
         switch (_X3) {
            case 31: repl__ = OP("or",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(OP("or",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1,list_1_(OP("or",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_2->_1,list_1_(_OP(redex)->_2->_2->_1))))))))); break;
            default: 
            repl__ = Or(_OP(_OP(redex)->_2->_1)->_2->_1,Or(_OP(_OP(redex)->_2->_1)->_2->_2->_1,_OP(redex)->_2->_2->_1)); break;
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,87,"OP (\"or\", #[OP (\"or\", #[a, b]), c]): ...");
           r__ = 1; goto replacement__; }
#line 88 "phase1.pcc"
} break;
      case 38: {
#line 82 "phase1.pcc"
         Exp  repl__;
         int _X4 = _FORALL(redex)->_3->get_rewrite_state();
         switch (_X4) {
            case 32: repl__ = OP("and",list_1_(OP("not",list_1_(EXISTS(_FORALL(redex)->_1,_FORALL(redex)->_2,OP("not",list_1_(_OP(_FORALL(redex)->_3)->_2->_1))))),list_1_(OP("not",list_1_(EXISTS(_FORALL(redex)->_1,_FORALL(redex)->_2,OP("not",list_1_(_OP(_FORALL(redex)->_3)->_2->_2->_1)))))))); break;
            case 31: repl__ = OP("not",list_1_(EXISTS(_FORALL(redex)->_1,_FORALL(redex)->_2,OP("and",list_1_(OP("not",list_1_(_OP(_FORALL(redex)->_3)->_2->_1)),list_1_(OP("not",list_1_(_OP(_FORALL(redex)->_3)->_2->_2->_1)))))))); break;
            case 22: repl__ = OP("not",list_1_(EXISTS(_FORALL(redex)->_1,_FORALL(redex)->_2,_OP(_FORALL(redex)->_3)->_2->_1))); break;
            default: 
            repl__ = Not(EXISTS(_FORALL(redex)->_1,_FORALL(redex)->_2,Not(_FORALL(redex)->_3))); break;
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,82,"FORALL (x, A, B): ...");
           r__ = 1; goto replacement__; }
#line 87 "phase1.pcc"
} break;
      case 37: {
#line 79 "phase1.pcc"
         Exp  repl__;
         int _X5 = _OP(_OP(redex)->_2->_1)->_2->_1->get_rewrite_state();
         switch (_X5) {
            case 32: repl__ = OP("or",list_1_(OP("and",list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_1)->_2->_1)),list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1))))),list_1_(OP("and",list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_1)->_2->_2->_1)),list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1)))))))); break;
            case 22: repl__ = OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_1)->_2->_1,list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1))))); break;
            default: 
            int _X6 = _OP(_OP(redex)->_2->_1)->_2->_2->_1->get_rewrite_state();
            switch (_X6) {
               case 32: repl__ = OP("or",list_1_(OP("and",list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1)),list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1))))),list_1_(OP("and",list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1)),list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_2->_1)))))))); break;
               case 31: repl__ = OP("and",list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1)),list_1_(OP("and",list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1)),list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_2->_1)))))))); break;
               case 22: repl__ = OP("and",list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1)),list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1))); break;
               default: 
               repl__ = And(Not(_OP(_OP(redex)->_2->_1)->_2->_1),Not(_OP(_OP(redex)->_2->_1)->_2->_2->_1)); break;
            }
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,79,"OP (\"not\", #[OP (\"or\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 82 "phase1.pcc"
} break;
      case 36: {
#line 78 "phase1.pcc"
         Exp  repl__;
         int _X7 = _OP(_OP(redex)->_2->_1)->_2->_1->get_rewrite_state();
         switch (_X7) {
            case 22: repl__ = OP("or",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_1)->_2->_1,list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1))))); break;
            default: 
            int _X8 = _OP(_OP(redex)->_2->_1)->_2->_2->_1->get_rewrite_state();
            switch (_X8) {
               case 32: repl__ = OP("or",list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1)),list_1_(OP("or",list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1)),list_1_(OP("not",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_2->_1)))))))); break;
               case 22: repl__ = OP("or",list_1_(OP("not",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1)),list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1))); break;
               default: 
               repl__ = Or(Not(_OP(_OP(redex)->_2->_1)->_2->_1),Not(_OP(_OP(redex)->_2->_1)->_2->_2->_1)); break;
            }
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,78,"OP (\"not\", #[OP (\"and\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 79 "phase1.pcc"
} break;
      case 35: {
#line 77 "phase1.pcc"
         Exp  repl__;
         int _X9 = _OP(redex)->_2->_1->get_rewrite_state();
         switch (_X9) {
            case 32: repl__ = OP("or",list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1,list_1_(_OP(_OP(redex)->_2->_2->_1)->_2->_1)))))),list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1,list_1_(_OP(_OP(redex)->_2->_2->_1)->_2->_2->_1))))))))); break;
            default: 
            int _X10 = _OP(_OP(redex)->_2->_2->_1)->_2->_2->_1->get_rewrite_state();
            switch (_X10) {
               case 31: repl__ = OP("or",list_1_(OP("and",list_1_(_OP(redex)->_2->_1,list_1_(_OP(_OP(redex)->_2->_2->_1)->_2->_1))),list_1_(OP("or",list_1_(OP("and",list_1_(_OP(redex)->_2->_1,list_1_(_OP(_OP(_OP(redex)->_2->_2->_1)->_2->_2->_1)->_2->_1))),list_1_(OP("and",list_1_(_OP(redex)->_2->_1,list_1_(_OP(_OP(_OP(redex)->_2->_2->_1)->_2->_2->_1)->_2->_2->_1))))))))); break;
               default: 
               repl__ = Or(And(_OP(redex)->_2->_1,_OP(_OP(redex)->_2->_2->_1)->_2->_1),And(_OP(redex)->_2->_1,_OP(_OP(redex)->_2->_2->_1)->_2->_2->_1)); break;
            }
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,77,"OP (\"and\", #[a, OP (\"or\", #[b, c])]): ...");
           r__ = 1; goto replacement__; }
#line 78 "phase1.pcc"
} break;
      case 34: {
#line 76 "phase1.pcc"
         Exp  repl__;
         int _X11 = _OP(_OP(redex)->_2->_1)->_2->_1->get_rewrite_state();
         switch (_X11) {
            case 32: repl__ = OP("or",list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_1)->_2->_1,list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_1)->_2->_2->_1,list_1_(_OP(redex)->_2->_2->_1)))))),list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1,list_1_(_OP(redex)->_2->_2->_1)))))); break;
            default: 
            int _X12 = _OP(_OP(redex)->_2->_1)->_2->_2->_1->get_rewrite_state();
            switch (_X12) {
               case 32: repl__ = OP("or",list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(_OP(redex)->_2->_2->_1))),list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1,list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_2->_1,list_1_(_OP(redex)->_2->_2->_1))))))))); break;
               case 31: repl__ = OP("or",list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(_OP(redex)->_2->_2->_1))),list_1_(OP("or",list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_1,list_1_(_OP(redex)->_2->_2->_1))),list_1_(OP("and",list_1_(_OP(_OP(_OP(redex)->_2->_1)->_2->_2->_1)->_2->_2->_1,list_1_(_OP(redex)->_2->_2->_1))))))))); break;
               default: 
               int _X13 = _OP(redex)->_2->_2->_1->get_rewrite_state();
               switch (_X13) {
                  case 31: repl__ = OP("or",list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(_OP(_OP(redex)->_2->_2->_1)->_2->_1))),list_1_(OP("or",list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_1,list_1_(_OP(_OP(redex)->_2->_2->_1)->_2->_2->_1))),list_1_(OP("or",list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1,list_1_(_OP(_OP(redex)->_2->_2->_1)->_2->_1))),list_1_(OP("and",list_1_(_OP(_OP(redex)->_2->_1)->_2->_2->_1,list_1_(_OP(_OP(redex)->_2->_2->_1)->_2->_2->_1)))))))))))); break;
                  default: 
                  repl__ = Or(And(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(redex)->_2->_2->_1),And(_OP(_OP(redex)->_2->_1)->_2->_2->_1,_OP(redex)->_2->_2->_1)); break;
               }
            }
         }
         { redex = DEBUG_Phase1(repl__,redex,Phase1_file_name,76,"OP (\"and\", #[OP (\"or\", #[a, b]), c]): ...");
           r__ = 1; goto replacement__; }
#line 77 "phase1.pcc"
} break;
      case 33: if ((_GENERATOR(redex)->_1->_1 == _ID(_GENERATOR(redex)->_3)->ID))
      {
#line 71 "phase1.pcc"
         { redex = DEBUG_Phase1(_GENERATOR(redex)->_2->_1,redex,Phase1_file_name,71,"GENERATOR (#[x], #[S], ID y) | (redex!GENERATOR.1!#[...].1 == redex!GENERATOR.3!ID): ...");
           r__ = 1; goto replacement__; }
#line 76 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 32: if ((_LET(redex)->_1 == _ID(_LET(redex)->_3)->ID))
      {
#line 70 "phase1.pcc"
         { redex = DEBUG_Phase1(_LET(redex)->_2,redex,Phase1_file_name,70,"LET (x, e, ID y) | (redex!LET.1 == redex!LET.3!ID): ...");
           r__ = 1; goto replacement__; }
#line 71 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 31: if ((_BOOL(_LIT(_EXISTS(redex)->_3)->LIT)->BOOL == false))
      {
#line 65 "phase1.pcc"
         { redex = DEBUG_Phase1(Not(Nonempty(_EXISTS(redex)->_2)),redex,Phase1_file_name,65,"EXISTS (x, A, LIT BOOL _) | (redex!EXISTS.3!LIT!BOOL == false): ...");
           r__ = 1; goto replacement__; }
#line 70 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 30: if ((_BOOL(_LIT(_EXISTS(redex)->_3)->LIT)->BOOL == true))
      {
#line 64 "phase1.pcc"
         { redex = DEBUG_Phase1(Nonempty(_EXISTS(redex)->_2),redex,Phase1_file_name,64,"EXISTS (x, A, LIT BOOL _) | (redex!EXISTS.3!LIT!BOOL == true): ...");
           r__ = 1; goto replacement__; }
#line 65 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 29: if ((_ID(_OP(redex)->_2->_1)->ID == _ID(_OP(redex)->_2->_2->_1)->ID))
      {
#line 62 "phase1.pcc"
         { redex = DEBUG_Phase1(True,redex,Phase1_file_name,62,"OP (\"<=\", #[ID x, ID y]) | (redex!OP.2!#[...].1!ID == redex!OP.2!#[...].2!#[...].1!ID): ...");
           r__ = 1; goto replacement__; }
#line 64 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 28: if ((_ID(_OP(redex)->_2->_1)->ID == _ID(_OP(redex)->_2->_2->_1)->ID))
      {
#line 61 "phase1.pcc"
         { redex = DEBUG_Phase1(False,redex,Phase1_file_name,61,"OP (\"<\", #[ID x, ID y]) | (redex!OP.2!#[...].1!ID == redex!OP.2!#[...].2!#[...].1!ID): ...");
           r__ = 1; goto replacement__; }
#line 62 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 27: if ((_ID(_OP(redex)->_2->_1)->ID == _ID(_OP(redex)->_2->_2->_1)->ID))
      {
#line 60 "phase1.pcc"
         { redex = DEBUG_Phase1(True,redex,Phase1_file_name,60,"OP (\">=\", #[ID x, ID y]) | (redex!OP.2!#[...].1!ID == redex!OP.2!#[...].2!#[...].1!ID): ...");
           r__ = 1; goto replacement__; }
#line 61 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 26: if ((_ID(_OP(redex)->_2->_1)->ID == _ID(_OP(redex)->_2->_2->_1)->ID))
      {
#line 59 "phase1.pcc"
         { redex = DEBUG_Phase1(False,redex,Phase1_file_name,59,"OP (\">\", #[ID x, ID y]) | (redex!OP.2!#[...].1!ID == redex!OP.2!#[...].2!#[...].1!ID): ...");
           r__ = 1; goto replacement__; }
#line 60 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 25: if ((_ID(_OP(redex)->_2->_1)->ID == _ID(_OP(redex)->_2->_2->_1)->ID))
      {
#line 58 "phase1.pcc"
         { redex = DEBUG_Phase1(False,redex,Phase1_file_name,58,"OP (\"/=\", #[ID x, ID y]) | (redex!OP.2!#[...].1!ID == redex!OP.2!#[...].2!#[...].1!ID): ...");
           r__ = 1; goto replacement__; }
#line 59 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 24: if ((_ID(_OP(redex)->_2->_1)->ID == _ID(_OP(redex)->_2->_2->_1)->ID))
      {
#line 57 "phase1.pcc"
         { redex = DEBUG_Phase1(True,redex,Phase1_file_name,57,"OP (\"=\", #[ID x, ID y]) | (redex!OP.2!#[...].1!ID == redex!OP.2!#[...].2!#[...].1!ID): ...");
           r__ = 1; goto replacement__; }
#line 58 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 23: {
#line 55 "phase1.pcc"
         { redex = DEBUG_Phase1(_OP(_OP(redex)->_2->_1)->_2->_1,redex,Phase1_file_name,55,"OP (\"not\", #[OP (\"not\", #[X])]): ...");
           r__ = 1; goto replacement__; }
#line 57 "phase1.pcc"
} break;
      case 22: if ((_BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL == false))
      {
#line 54 "phase1.pcc"
         { redex = DEBUG_Phase1(_OP(redex)->_2->_1,redex,Phase1_file_name,54,"OP (\"or\", #[X, LIT BOOL _]) | (redex!OP.2!#[...].2!#[...].1!LIT!BOOL == false): ...");
           r__ = 1; goto replacement__; }
#line 55 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 21: if ((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL == false))
      {
#line 53 "phase1.pcc"
         { redex = DEBUG_Phase1(_OP(redex)->_2->_2->_1,redex,Phase1_file_name,53,"OP (\"or\", #[LIT BOOL _, X]) | (redex!OP.2!#[...].1!LIT!BOOL == false): ...");
           r__ = 1; goto replacement__; }
#line 54 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 20: if ((_BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL == true))
      {
#line 52 "phase1.pcc"
         { redex = DEBUG_Phase1(True,redex,Phase1_file_name,52,"OP (\"or\", #[X, LIT BOOL _]) | (redex!OP.2!#[...].2!#[...].1!LIT!BOOL == true): ...");
           r__ = 1; goto replacement__; }
#line 53 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 19: if ((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL == true))
      {
#line 51 "phase1.pcc"
         { redex = DEBUG_Phase1(True,redex,Phase1_file_name,51,"OP (\"or\", #[LIT BOOL _, X]) | (redex!OP.2!#[...].1!LIT!BOOL == true): ...");
           r__ = 1; goto replacement__; }
#line 52 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 18: if ((_BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL == false))
      {
#line 50 "phase1.pcc"
         { redex = DEBUG_Phase1(False,redex,Phase1_file_name,50,"OP (\"and\", #[X, LIT BOOL _]) | (redex!OP.2!#[...].2!#[...].1!LIT!BOOL == false): ...");
           r__ = 1; goto replacement__; }
#line 51 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 17: if ((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL == false))
      {
#line 49 "phase1.pcc"
         { redex = DEBUG_Phase1(False,redex,Phase1_file_name,49,"OP (\"and\", #[LIT BOOL _, X]) | (redex!OP.2!#[...].1!LIT!BOOL == false): ...");
           r__ = 1; goto replacement__; }
#line 50 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 16: if ((_BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL == true))
      {
#line 48 "phase1.pcc"
         { redex = DEBUG_Phase1(_OP(redex)->_2->_1,redex,Phase1_file_name,48,"OP (\"and\", #[X, LIT BOOL _]) | (redex!OP.2!#[...].2!#[...].1!LIT!BOOL == true): ...");
           r__ = 1; goto replacement__; }
#line 49 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 15: if ((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL == true))
      {
#line 47 "phase1.pcc"
         { redex = DEBUG_Phase1(_OP(redex)->_2->_2->_1,redex,Phase1_file_name,47,"OP (\"and\", #[LIT BOOL _, X]) | (redex!OP.2!#[...].1!LIT!BOOL == true): ...");
           r__ = 1; goto replacement__; }
#line 48 "phase1.pcc"
}
      else { ++o__; goto accept__; } break;
      case 14: {
#line 45 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL <= _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,45,"OP (\"<=\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 47 "phase1.pcc"
} break;
      case 13: {
#line 44 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL < _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,44,"OP (\"<\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 45 "phase1.pcc"
} break;
      case 12: {
#line 43 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL >= _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,43,"OP (\">=\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 44 "phase1.pcc"
} break;
      case 11: {
#line 42 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL > _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,42,"OP (\">\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 43 "phase1.pcc"
} break;
      case 10: {
#line 41 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL != _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,41,"OP (\"/=\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 42 "phase1.pcc"
} break;
      case 9: {
#line 40 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL == _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,40,"OP (\"=\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 41 "phase1.pcc"
} break;
      case 8: {
#line 38 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((! _BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,38,"OP (\"not\", #[LIT BOOL i]): ...");
           r__ = 1; goto replacement__; }
#line 40 "phase1.pcc"
} break;
      case 7: {
#line 37 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL || _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,37,"OP (\"or\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 38 "phase1.pcc"
} break;
      case 6: {
#line 36 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_BOOL(_LIT(_OP(redex)->_2->_1)->LIT)->BOOL && _BOOL(_LIT(_OP(redex)->_2->_2->_1)->LIT)->BOOL)),redex,Phase1_file_name,36,"OP (\"and\", #[LIT BOOL i, LIT BOOL j]): ...");
           r__ = 1; goto replacement__; }
#line 37 "phase1.pcc"
} break;
      case 5: {
#line 34 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_INT(_LIT(_OP(redex)->_2->_1)->LIT)->INT <= _INT(_LIT(_OP(redex)->_2->_2->_1)->LIT)->INT)),redex,Phase1_file_name,34,"OP (\"<=\", #[LIT INT i, LIT INT j]): ...");
           r__ = 1; goto replacement__; }
#line 36 "phase1.pcc"
} break;
      case 4: {
#line 33 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_INT(_LIT(_OP(redex)->_2->_1)->LIT)->INT < _INT(_LIT(_OP(redex)->_2->_2->_1)->LIT)->INT)),redex,Phase1_file_name,33,"OP (\"<\", #[LIT INT i, LIT INT j]): ...");
           r__ = 1; goto replacement__; }
#line 34 "phase1.pcc"
} break;
      case 3: {
#line 32 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_INT(_LIT(_OP(redex)->_2->_1)->LIT)->INT >= _INT(_LIT(_OP(redex)->_2->_2->_1)->LIT)->INT)),redex,Phase1_file_name,32,"OP (\">=\", #[LIT INT i, LIT INT j]): ...");
           r__ = 1; goto replacement__; }
#line 33 "phase1.pcc"
} break;
      case 2: {
#line 31 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_INT(_LIT(_OP(redex)->_2->_1)->LIT)->INT > _INT(_LIT(_OP(redex)->_2->_2->_1)->LIT)->INT)),redex,Phase1_file_name,31,"OP (\">\", #[LIT INT i, LIT INT j]): ...");
           r__ = 1; goto replacement__; }
#line 32 "phase1.pcc"
} break;
      case 1: {
#line 30 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_INT(_LIT(_OP(redex)->_2->_1)->LIT)->INT != _INT(_LIT(_OP(redex)->_2->_2->_1)->LIT)->INT)),redex,Phase1_file_name,30,"OP (\"/=\", #[LIT INT i, LIT INT j]): ...");
           r__ = 1; goto replacement__; }
#line 31 "phase1.pcc"
} break;
      case 0: {
#line 29 "phase1.pcc"
         { redex = DEBUG_Phase1(Boolean((_INT(_LIT(_OP(redex)->_2->_1)->LIT)->INT == _INT(_LIT(_OP(redex)->_2->_2->_1)->LIT)->INT)),redex,Phase1_file_name,29,"OP (\"=\", #[LIT INT i, LIT INT j]): ...");
           r__ = 1; goto replacement__; }
#line 30 "phase1.pcc"
} break;
   }
   if (boxed(redex)) {
      redex->set_rewrite_state(s__);
   }
   
}

void  Phase1::labeler (Literal & redex, int& s__, int r__)
{
replacement__:
   switch(redex->tag__) {
      case a_Literal::tag_INT: { 
         int s0__;
         s0__ = 0; // int
         s__ = 14;} break;
      case a_Literal::tag_STRING: { 
         int s0__;
         labeler(_STRING(redex)->STRING, s0__, r__);
         s__ = 0;} break;
      default: { 
         int s0__;
         s0__ = 0; // Bool
         s__ = 15;} break;
   }
   
}

void  Phase1::labeler (a_List<Exp> *  & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = Phase1_theta_13[Phase1_check[69 + s0__] == 19 ? Phase1_next[69 + s0__] : 0][Phase1_check[142 + s1__] == 20 ? Phase1_next[142 + s1__] : 0]; 
   } else {s__ = 2;
   }
   
}

void  Phase1::labeler (a_List<Id> *  & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = Phase1_theta_1[0][Phase1_check[15 + s1__] == 2 ? Phase1_next[15 + s1__] : 0]; 
   } else {s__ = 1;
   }
   
}

#line 97 "phase1.pcc"
#line 97 "phase1.pcc"
/* 1  *//* 2  *//* 2' */
#line 98 "phase1.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 11
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
