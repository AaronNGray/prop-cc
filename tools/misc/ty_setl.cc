//////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.0 (pre-beta)),
//  last updated on Jan 4th, 1995.  Please be sure not to alter this file
//  directly.  Instead, refer to the original source file "ty_setl.pcc".
//////////////////////////////////////////////////////////////////////////////
#line 1 "ty_setl.pcc"
//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the 
// public domain.   The author(s) of this software reserve no copyrights on 
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that 
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in 
// your programs, and that this notice be preserved intact in all the source 
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung 
// 1994
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  This file implements the type analysis methods for the SETL sublanguage.
//  Type analysis is used to:
//     (a) Check for valid typing of the soruce program.
//     (b) Select implementations of the set-theoretic data structures.
//
//  For details, see Paige, Schwartz, Cai, et al.
//////////////////////////////////////////////////////////////////////////////

#include "irdef.h"  //  intermediate representations
#include "setl.h"   //  SETL abstract syntax

//////////////////////////////////////////////////////////////////////////////
// Method to infer the type a SETL expression when given an expression
// and an type binding environment.
//////////////////////////////////////////////////////////////////////////////
TY InferSETL::infer(EXPR e, Map<ID,TY>& env)
{  
#line 42 "ty_setl.pcc"
{ if (e) {
switch (e->untag()) {
case a_EXPR::tag_typed_exp: {
#line 44 "ty_setl.pcc"

      } break;
case a_EXPR::tag_ident_exp: {
#line 45 "ty_setl.pcc"
      return env[(_ident_exp(e)->ident_exp)];
      } break;
case a_EXPR::tag_int_exp: {
#line 46 "ty_setl.pcc"
       return Infer::integer_ty;
      } break;
case a_EXPR::tag_real_exp: {
#line 47 "ty_setl.pcc"
       return Infer::real_ty;
      } break;
case a_EXPR::tag_string_exp: {
#line 48 "ty_setl.pcc"
       return Infer::string_ty;
      } break;
case a_EXPR::tag_char_exp: {
#line 49 "ty_setl.pcc"
       return Infer::character_ty;
      } break;
case a_EXPR::tag_app_exp: {
#line 50 "ty_setl.pcc"
  
      } break;
case a_EXPR::tag_set_exp: {
#line 51 "ty_setl.pcc"
      return set_ty(infer((_set_exp(e)->set_exp),env));
      } break;
case a_EXPR::tag_multiset_exp: {
#line 52 "ty_setl.pcc"
      return multiset_ty(infer((_multiset_exp(e)->multiset_exp),env));
      } break;
case a_EXPR::tag_cons_exp:  break;
case a_EXPR::tag_tuple_exp: {
#line 53 "ty_setl.pcc"
      return tuple_ty(infer((_tuple_exp(e)->tuple_exp),env));
      } break;
case a_EXPR::tag_map_exp: {
#line 54 "ty_setl.pcc"
      return map_ty(infer((_map_exp(e)->map_exp),env));
      } break;
case a_EXPR::tag_multimap_exp: {
#line 55 "ty_setl.pcc"
      return multimap_ty(infer((_multimap_exp(e)->multimap_exp),env));
      } break;
case a_EXPR::tag_record_exp: {
#line 56 "ty_setl.pcc"
      return record_ty(infer((_record_exp(e)->record_exp),env));
      } break;
case a_EXPR::tag_c_exp: {
#line 57 "ty_setl.pcc"
       return var_ty(no_ty);
   } break;
default: 
} } else {
{
#line 42 "ty_setl.pcc"
               return var_ty(no_ty);
      }}
}

#line 58 "ty_setl.pcc"

}
/*
----------------------------- Statistics -------------------------------
Number of decision nodes merged = 0
Number of switches generated    = 1
Number of ifs      generated    = 1
Number of labels   generated    = 0
Number of gotos    generated    = 0
Number of temporary variables   = 0
------------------------------------------------------------------------
*/
