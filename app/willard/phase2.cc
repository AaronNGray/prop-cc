///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "phase2.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "phase2.pcc"
#include <AD/pretty/postream.h>
#include "phase2.h"
#include "list.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for phase2 
//
///////////////////////////////////////////////////////////////////////////////
Phase2::Phase2() {}
Phase2::~Phase2() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to invoke phase2 
//
///////////////////////////////////////////////////////////////////////////////
Exp Phase2::phase2(Exp e) 
{  message("Quantifier elimination phase", e); 
   (*this)(e); 
   return collect_subqueries(e);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Transformation to eliminate existential quantifiers 
//  by transforming them into count queries.
//
///////////////////////////////////////////////////////////////////////////////
#line 30 "phase2.pcc"
#line 109 "phase2.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_Phase2
#define DEBUG_Phase2(repl,redex,file,line,rule) repl
#else
static const char * Phase2_file_name = "phase2.pcc";
#endif

static const TreeTables::Offset Phase2_accept_base [ 73 ] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 
   2, 2, 2, 2, 3, 5, 6, 6, 6, 7, 8, 8, 9, 10, 11, 12, 
   12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 15, 16, 17, 18, 18, 18, 
   18, 18, 18, 18, 18, 18, 18, 19, 21, 23, 25, 26, 26, 26, 27, 29, 
   31, 33, 35, 37, 39, 41, 43, 45, 48
};
static const TreeTables::ShortRule Phase2_accept_vector [ 50 ] = {
   -1, 0, -1, 18, -1, 13, -1, 17, -1, 18, -1, 18, -1, 16, -1, 14, 
   -1, 11, -1, 18, -1, 12, -1, 7, -1, 10, -1, 9, -1, 6, -1, 5, 
   -1, 4, -1, 3, -1, 2, -1, 1, -1, 15, -1, 8, -1, 7, 8, -1, 
   8, -1
};
static const TreeTables::ShortState Phase2_theta_1[1][2] = {
   { 0, 18 }
};


static const TreeTables::ShortState Phase2_theta_2[11][17] = {
   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0 },
   { 0, 24, 0, 0, 44, 0, 58, 62, 63, 64, 65, 66, 67, 68, 0, 0, 
   0 },
   { 0, 0, 40, 40, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 40, 40, 
   40 },
   { 0, 0, 39, 39, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 39, 39, 
   39 },
   { 0, 0, 38, 38, 0, 38, 0, 0, 0, 0, 0, 0, 0, 0, 38, 38, 
   38 },
   { 0, 0, 37, 37, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 37, 37, 
   37 },
   { 0, 0, 36, 36, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 36, 36, 
   36 },
   { 0, 0, 35, 35, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 35, 35, 
   35 },
   { 0, 0, 34, 43, 0, 57, 0, 0, 0, 0, 0, 0, 0, 0, 70, 71, 
   72 },
   { 0, 0, 33, 33, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 33, 56, 
   33 },
   { 0, 23, 0, 0, 23, 0, 23, 23, 23, 23, 23, 23, 23, 23, 0, 0, 
   0 }
};


static const TreeTables::ShortState Phase2_theta_4[2] = {
   0, 22
};


static const TreeTables::ShortState Phase2_theta_9[5][2] = {
   { 15, 20 },
   { 27, 28 },
   { 29, 30 },
   { 54, 55 },
   { 54, 55 }
};


static const TreeTables::ShortState Phase2_theta_10[2][2][9] = {
   { { 16, 16, 21, 41, 41, 42, 42, 69, 69 },
   { 16, 16, 21, 41, 41, 42, 42, 69, 69 } },
   { { 16, 16, 21, 41, 41, 42, 42, 69, 69 },
   { 16, 25, 21, 41, 41, 42, 42, 69, 69 } }
};


static const TreeTables::ShortState Phase2_theta_13[11][4] = {
   { 0, 19, 26, 59 },
   { 0, 19, 31, 61 },
   { 0, 32, 26, 59 },
   { 0, 46, 45, 60 },
   { 0, 47, 26, 59 },
   { 0, 48, 26, 59 },
   { 0, 49, 26, 59 },
   { 0, 50, 26, 59 },
   { 0, 51, 26, 59 },
   { 0, 52, 26, 59 },
   { 0, 53, 26, 59 }
};


static const TreeTables::ShortState Phase2_check [ 174 ] = {
   0, 2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 11, 
   0, 5, 12, 4, 11, 0, 10, 10, 0, 0, 4, 11, 11, 11, 11, 4, 
   4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 11, 11, 13, 0, 0, 4, 4, 4, 0, 14, 
   0, 0, 14, 0, 0, 13, 0, 14, 10, 0, 0, 14, 0, 14, 14, 14, 
   14, 0, 0, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 0, 0, 0, 
   15, 15, 0, 0, 0, 0, 0, 16, 14, 14, 15, 15, 15, 15, 15, 15, 
   15, 15, 0, 0, 15, 15, 0, 14, 16, 0, 0, 0, 0, 0, 0, 0, 
   0, 15, 15, 15, 0, 16, 0, 15, 15, 15, 15, 15, 15, 15, 0, 15, 
   15, 15, 0, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
TreeTables::ShortState Phase2_next [ 174 ] = {
   0, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 1, 
   0, 1, 1, 1, 1, 0, 1, 2, 0, 0, 2, 1, 1, 1, 1, 3, 
   4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 5, 6, 7, 
   8, 9, 10, 11, 12, 13, 1, 1, 1, 0, 0, 14, 15, 16, 0, 1, 
   0, 0, 2, 0, 0, 1, 0, 2, 4, 0, 0, 2, 0, 3, 4, 5, 
   6, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 
   1, 2, 0, 0, 0, 0, 0, 1, 7, 8, 3, 4, 5, 6, 7, 8, 
   9, 10, 0, 0, 4, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 
   0, 3, 4, 2, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 4, 
   4, 4, 0, 3, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
inline void  Phase2::labeler(char const * redex,int& s__,int)
{
   {
      if (_less_string(redex,">=")) {
         if (_less_string(redex,"=")) {
            if (_equal_string(redex,"/=")) {s__ = 5;}
            else if (_equal_string(redex,"<")) {s__ = 8;}
            else if (_equal_string(redex,"<=")) {s__ = 9;}
            else {s__ = 0;}
         } else {
            if (_equal_string(redex,"=")) {s__ = 4;}
            else if (_equal_string(redex,">")) {s__ = 6;}
            else {s__ = 0;}
         }
      } else {
         if (_less_string(redex,"not")) {
            if (_equal_string(redex,">=")) {s__ = 7;}
            else if (_equal_string(redex,"and")) {s__ = 10;}
            else if (_equal_string(redex,"nonempty")) {s__ = 12;}
            else {s__ = 0;}
         } else {
            if (_equal_string(redex,"not")) {s__ = 3;}
            else if (_equal_string(redex,"or")) {s__ = 11;}
            else {s__ = 0;}
         }
      }
   }
}

inline void  Phase2::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Phase2::labeler (Exp & redex, int& s__, int r__)
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
         s__ = Phase2_theta_2[Phase2_check[0 + s0__] == 3 ? Phase2_next[0 + s0__] : 0][Phase2_check[0 + s1__] == 4 ? Phase2_next[0 + s1__] : 0]; } break;
      case a_Exp::tag_APP: { 
         int s0__;
         int s1__;
         labeler(_APP(redex)->_1, s0__, r__);
         labeler(_APP(redex)->_2, s1__, r__);
         s__ = 0;} break;
      case a_Exp::tag_LIT: { 
         int s0__;
         labeler(_LIT(redex)->LIT, s0__, r__);
         s__ = Phase2_theta_4[Phase2_check[0 + s0__] == 5 ? Phase2_next[0 + s0__] : 0]; } break;
      case a_Exp::tag_ID: { 
         int s0__;
         labeler(_ID(redex)->ID, s0__, r__);
         s__ = 13;} break;
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
         s__ = 0;} break;
      case a_Exp::tag_EXISTS: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_EXISTS(redex)->_1, s0__, r__);
         labeler(_EXISTS(redex)->_2, s1__, r__);
         labeler(_EXISTS(redex)->_3, s2__, r__);
         s__ = 14;} break;
      case a_Exp::tag_GUARD: { 
         int s0__;
         int s1__;
         labeler(_GUARD(redex)->_1, s0__, r__);
         labeler(_GUARD(redex)->_2, s1__, r__);
         s__ = Phase2_theta_9[Phase2_check[0 + s0__] == 10 ? Phase2_next[0 + s0__] : 0][Phase2_check[0 + s1__] == 11 ? Phase2_next[0 + s1__] : 0]; } break;
      case a_Exp::tag_GENERATOR: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_GENERATOR(redex)->_1, s0__, r__);
         labeler(_GENERATOR(redex)->_2, s1__, r__);
         labeler(_GENERATOR(redex)->_3, s2__, r__);
         s__ = Phase2_theta_10[Phase2_check[0 + s0__] == 12 ? Phase2_next[0 + s0__] : 0][Phase2_check[37 + s1__] == 13 ? Phase2_next[37 + s1__] : 0][Phase2_check[50 + s2__] == 14 ? Phase2_next[50 + s2__] : 0]; } break;
      default: { 
         int s0__;
         int s1__;
         int s2__;
         labeler(_LET(redex)->_1, s0__, r__);
         labeler(_LET(redex)->_2, s1__, r__);
         labeler(_LET(redex)->_3, s2__, r__);
         s__ = 0;} break;
   }
   const TreeTables::ShortRule * o__ = Phase2_accept_vector + Phase2_accept_base[s__];
accept__:
   switch (*o__) {
      case 18: {
#line 102 "phase2.pcc"
         { redex = DEBUG_Phase2(GUARD(And(_GUARD(redex)->_1,_GUARD(_GUARD(redex)->_2)->_1),_GUARD(_GUARD(redex)->_2)->_2),redex,Phase2_file_name,102,"GUARD (p1, GUARD (p2, E)): ...");
           r__ = 1; goto replacement__; }
#line 107 "phase2.pcc"
} break;
      case 17: if ((_GENERATOR(redex)->_1->_1 == _ID(_GENERATOR(redex)->_3)->ID))
      {
#line 101 "phase2.pcc"
         { redex = DEBUG_Phase2(_GENERATOR(redex)->_2->_1,redex,Phase2_file_name,101,"GENERATOR (#[x], #[A], ID y) | (redex!GENERATOR.1!#[...].1 == redex!GENERATOR.3!ID): ...");
           r__ = 1; goto replacement__; }
#line 102 "phase2.pcc"
}
      else { ++o__; goto accept__; } break;
      case 16: if ((_BOOL(_LIT(_GUARD(_GENERATOR(redex)->_3)->_1)->LIT)->BOOL == true))
      {
#line 100 "phase2.pcc"
         { redex = DEBUG_Phase2(GENERATOR(_GENERATOR(redex)->_1,_GENERATOR(redex)->_2,_GUARD(_GENERATOR(redex)->_3)->_2),redex,Phase2_file_name,100,"GENERATOR (x, A, GUARD (LIT BOOL _, E)) | (redex!GENERATOR.3!GUARD.1!LIT!BOOL == true): ...");
           r__ = 1; goto replacement__; }
#line 101 "phase2.pcc"
}
      else { ++o__; goto accept__; } break;
      case 15: {
#line 98 "phase2.pcc"
         { redex = DEBUG_Phase2(GUARD(_OP(_GUARD(_GENERATOR(redex)->_3)->_1)->_2->_1,GENERATOR(_GENERATOR(redex)->_1,_GENERATOR(redex)->_2,GUARD(_OP(_GUARD(_GENERATOR(redex)->_3)->_1)->_2->_2->_1,_GUARD(_GENERATOR(redex)->_3)->_2))),redex,Phase2_file_name,98,"GENERATOR (x, A, GUARD (OP (\"and\", #[p1 as OP (\"nonempty\", #[C]), p2]), E)): ...");
           r__ = 1; goto replacement__; }
#line 100 "phase2.pcc"
} break;
      case 14: {
#line 96 "phase2.pcc"
         { redex = DEBUG_Phase2(GUARD(_GUARD(_GENERATOR(redex)->_3)->_1,GENERATOR(_GENERATOR(redex)->_1,_GENERATOR(redex)->_2,_GUARD(_GENERATOR(redex)->_3)->_2)),redex,Phase2_file_name,96,"GENERATOR (x, A, GUARD (p as OP (\"nonempty\", #[C]), E)): ...");
           r__ = 1; goto replacement__; }
#line 98 "phase2.pcc"
} break;
      case 13: {
#line 95 "phase2.pcc"
         { redex = DEBUG_Phase2(GENERATOR(append(_GENERATOR(redex)->_1,_GENERATOR(_GENERATOR(redex)->_3)->_1),append(_GENERATOR(redex)->_2,_GENERATOR(_GENERATOR(redex)->_3)->_2),_GENERATOR(_GENERATOR(redex)->_3)->_3),redex,Phase2_file_name,95,"GENERATOR (x, A, GENERATOR (y, B, C)): ...");
           r__ = 1; goto replacement__; }
#line 96 "phase2.pcc"
} break;
      case 12: {
#line 93 "phase2.pcc"
         { redex = DEBUG_Phase2(Or(_OP(_OP(redex)->_2->_1)->_2->_1,Or(_OP(_OP(redex)->_2->_1)->_2->_2->_1,_OP(redex)->_2->_2->_1)),redex,Phase2_file_name,93,"OP (\"or\", #[OP (\"or\", #[a, b]), c]): ...");
           r__ = 1; goto replacement__; }
#line 95 "phase2.pcc"
} break;
      case 11: {
#line 92 "phase2.pcc"
         { redex = DEBUG_Phase2(_OP(_OP(redex)->_2->_1)->_2->_1,redex,Phase2_file_name,92,"OP (\"not\", #[OP (\"not\", #[a])]): ...");
           r__ = 1; goto replacement__; }
#line 93 "phase2.pcc"
} break;
      case 10: {
#line 91 "phase2.pcc"
         { redex = DEBUG_Phase2(And(Not(_OP(_OP(redex)->_2->_1)->_2->_1),Not(_OP(_OP(redex)->_2->_1)->_2->_2->_1)),redex,Phase2_file_name,91,"OP (\"not\", #[OP (\"or\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 92 "phase2.pcc"
} break;
      case 9: {
#line 90 "phase2.pcc"
         { redex = DEBUG_Phase2(Or(Not(_OP(_OP(redex)->_2->_1)->_2->_1),Not(_OP(_OP(redex)->_2->_1)->_2->_2->_1)),redex,Phase2_file_name,90,"OP (\"not\", #[OP (\"and\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 91 "phase2.pcc"
} break;
      case 8: {
#line 89 "phase2.pcc"
         { redex = DEBUG_Phase2(Or(And(_OP(redex)->_2->_1,_OP(_OP(redex)->_2->_2->_1)->_2->_1),And(_OP(redex)->_2->_1,_OP(_OP(redex)->_2->_2->_1)->_2->_2->_1)),redex,Phase2_file_name,89,"OP (\"and\", #[a, OP (\"or\", #[b, c])]): ...");
           r__ = 1; goto replacement__; }
#line 90 "phase2.pcc"
} break;
      case 7: {
#line 88 "phase2.pcc"
         { redex = DEBUG_Phase2(Or(And(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(redex)->_2->_2->_1),And(_OP(_OP(redex)->_2->_1)->_2->_2->_1,_OP(redex)->_2->_2->_1)),redex,Phase2_file_name,88,"OP (\"and\", #[OP (\"or\", #[a, b]), c]): ...");
           r__ = 1; goto replacement__; }
#line 89 "phase2.pcc"
} break;
      case 6: {
#line 83 "phase2.pcc"
         { redex = DEBUG_Phase2(Gt(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(_OP(redex)->_2->_1)->_2->_2->_1),redex,Phase2_file_name,83,"OP (\"not\", #[OP (\"<=\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 88 "phase2.pcc"
} break;
      case 5: {
#line 82 "phase2.pcc"
         { redex = DEBUG_Phase2(Ge(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(_OP(redex)->_2->_1)->_2->_2->_1),redex,Phase2_file_name,82,"OP (\"not\", #[OP (\"<\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 83 "phase2.pcc"
} break;
      case 4: {
#line 81 "phase2.pcc"
         { redex = DEBUG_Phase2(Lt(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(_OP(redex)->_2->_1)->_2->_2->_1),redex,Phase2_file_name,81,"OP (\"not\", #[OP (\">=\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 82 "phase2.pcc"
} break;
      case 3: {
#line 80 "phase2.pcc"
         { redex = DEBUG_Phase2(Le(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(_OP(redex)->_2->_1)->_2->_2->_1),redex,Phase2_file_name,80,"OP (\"not\", #[OP (\">\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 81 "phase2.pcc"
} break;
      case 2: {
#line 79 "phase2.pcc"
         { redex = DEBUG_Phase2(Eq(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(_OP(redex)->_2->_1)->_2->_2->_1),redex,Phase2_file_name,79,"OP (\"not\", #[OP (\"/=\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 80 "phase2.pcc"
} break;
      case 1: {
#line 78 "phase2.pcc"
         { redex = DEBUG_Phase2(Ne(_OP(_OP(redex)->_2->_1)->_2->_1,_OP(_OP(redex)->_2->_1)->_2->_2->_1),redex,Phase2_file_name,78,"OP (\"not\", #[OP (\"=\", #[a, b])]): ...");
           r__ = 1; goto replacement__; }
#line 79 "phase2.pcc"
} break;
      case 0: {
#line 36 "phase2.pcc"
       IdSet S;
         free_vars(_EXISTS(redex)->_3,S);
         
         // Transform: exists x : A . p  where x does not occur in p
         // into:      #A > 0 and p
         if (! S.contains(_EXISTS(redex)->_1)) { 
#line 41 "phase2.pcc"
#line 41 "phase2.pcc"
         { redex = DEBUG_Phase2(And(Nonempty(_EXISTS(redex)->_2),_EXISTS(redex)->_3),redex,Phase2_file_name,35,"EXISTS (x, A, p): ...");
           r__ = 1; goto replacement__; }
#line 41 "phase2.pcc"
#line 41 "phase2.pcc"
        }
         
               // Transform: exists x : A . p(x) 
               // into: #C > 0
               //       where C = { x : A | p(x) }
               if (S.size() == 1)
               {  Id C = gensym("C");
         	 Exp find_query = GENERATOR(
#line 48 "phase2.pcc"
#line 48 "phase2.pcc"
         list_1_(_EXISTS(redex)->_1)
#line 48 "phase2.pcc"
#line 48 "phase2.pcc"
         ,
#line 48 "phase2.pcc"
#line 48 "phase2.pcc"
         list_1_(_EXISTS(redex)->_2)
#line 48 "phase2.pcc"
#line 48 "phase2.pcc"
         ,GUARD(_EXISTS(redex)->_3,ID(_EXISTS(redex)->_1)));
         	 add_subquery(C,find_query);
         	 
#line 50 "phase2.pcc"
#line 50 "phase2.pcc"
         { redex = DEBUG_Phase2(Nonempty(ID(C)),redex,Phase2_file_name,35,"EXISTS (x, A, p): ...");
           r__ = 1; goto replacement__; }
#line 50 "phase2.pcc"
#line 50 "phase2.pcc"
         
         }
         
         //  Transform: exists x : A . p(x,y) 
         //  into:   C(y)
         //          where C = { [y, #{ [y,x] : x in A | p(x,y)}] : y in B }
         if (S.size() == 2)
         {  Id C = gensym("C");
         	 Id y = "???";
         	 foreach(i,S) if (S.value(i) != _EXISTS(redex)->_1) y = S.value(i);
         	 Exp B = range_of(y);
            Exp count_query = 
         	    GENERATOR(
#line 62 "phase2.pcc"
#line 62 "phase2.pcc"
         list_1_(y)
#line 62 "phase2.pcc"
#line 62 "phase2.pcc"
         ,
#line 62 "phase2.pcc"
#line 62 "phase2.pcc"
         list_1_(B)
#line 62 "phase2.pcc"
#line 62 "phase2.pcc"
         ,
         	       TUPLE(
#line 63 "phase2.pcc"
#line 63 "phase2.pcc"
         list_1_(ID(y),list_1_(Count(GENERATOR(list_1_(_EXISTS(redex)->_1),list_1_(_EXISTS(redex)->_2),GUARD(_EXISTS(redex)->_3,TUPLE(list_1_(ID(y),list_1_(ID(_EXISTS(redex)->_1)))))))))
#line 66 "phase2.pcc"
#line 66 "phase2.pcc"
         ));
         add_subquery(C,count_query);
         	 
#line 68 "phase2.pcc"
#line 68 "phase2.pcc"
         { redex = DEBUG_Phase2(Gt(APP(C,list_1_(ID(y))),Zero),redex,Phase2_file_name,35,"EXISTS (x, A, p): ...");
           r__ = 1; goto replacement__; }
#line 68 "phase2.pcc"
#line 68 "phase2.pcc"
         
         } 
         
         // Arity is not zero or one
         error("Cannot simplify quantifier",redex); 
         
#line 73 "phase2.pcc"
} break;
   }
   if (boxed(redex)) {
      redex->set_rewrite_state(s__);
   }
   {
      switch (redex->tag__) {
         case a_Exp::tag_LET: {
            if (
#line 108 "phase2.pcc"
            has_subqueries()
#line 108 "phase2.pcc"
) {
               
#line 108 "phase2.pcc"
               { redex = DEBUG_Phase2(collect_subqueries(redex),redex,Phase2_file_name,108,"LET (x, A, B) | has_subqueries(): ...");
                 r__ = 1; goto replacement__; }
#line 109 "phase2.pcc"
            } else {
               }
            } break;
         default: {} break;
      }
   }
   
}

void  Phase2::labeler (Literal & redex, int& s__, int r__)
{
replacement__:
   switch(redex->tag__) {
      case a_Literal::tag_INT: { 
         int s0__;
         s0__ = 0; // int
         s__ = 0;} break;
      case a_Literal::tag_STRING: { 
         int s0__;
         labeler(_STRING(redex)->STRING, s0__, r__);
         s__ = 0;} break;
      default: { 
         int s0__;
         s0__ = 0; // Bool
         s__ = 17;} break;
   }
   
}

void  Phase2::labeler (a_List<Exp> *  & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = Phase2_theta_13[Phase2_check[73 + s0__] == 15 ? Phase2_next[73 + s0__] : 0][Phase2_check[101 + s1__] == 16 ? Phase2_next[101 + s1__] : 0]; 
   } else {s__ = 2;
   }
   
}

void  Phase2::labeler (a_List<Id> *  & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = Phase2_theta_1[0][Phase2_check[0 + s1__] == 2 ? Phase2_next[0 + s1__] : 0]; 
   } else {s__ = 1;
   }
   
}

#line 109 "phase2.pcc"
#line 109 "phase2.pcc"

#line 110 "phase2.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 10
Number of ifs generated      = 14
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
