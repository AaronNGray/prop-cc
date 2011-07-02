///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\gcgen.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_g_c_g_e_nco_c_c_Q2("i__");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_g_c_g_e_nco_c_c_Q1("this");
#line 1 "../../prop-src/gcgen.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the garbage collection interface generation
//
///////////////////////////////////////////////////////////////////////////////

#include "ir.h"
#include "datatype.h"
#include "type.h"

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates the interface method declarations
//  for the garbage collector.
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeClass::generate_gc_interface( CodeGen& C)
{
  C.pr(
        "%^%/"
        "%^//"
        "%^// Method for garbage collection tracing"
        "%^//"
        "%^%/"
        "%-%^protected:%+"
        "%^virtual void trace(GC *);"
        "%-%^public:%+"
      );
}

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates an implementation for the trace method
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeClass::generate_gc_implementation( CodeGen& C, Tys tys, DefKind k)
{
  // Unit constructors do not need gc methods

  if (root->arg_constructors == 0)
    return;

  if (k == INTERFACE_DEFINITION)
  {
    C.pr( "%^extern void %s%P::trace(GC *);", class_name, tys);
    return;
  }

  C.pr( "%^void %s%P::trace(GC * gc__)" "%^{%+", class_name, tys);

  // Invoke base class tracing methods

  gen_super_class_tracing_methods(C,tys,k);

  // Invoke tracing functions for each collectable fields.

  if (cons != NOcons)
  {
    Ty arg_ty = cons_arg_ty;
    if (is_array)
      arg_ty = mkarrayty( arg_ty, IDexp( "len_"));
    gen_field_tracing_methods( C, DEREFexp( IDexp( 
#line 64 "../../prop-src/gcgen.pcc"
#line 64 "../../prop-src/gcgen.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_g_c_g_e_nco_c_c_Q1
#line 64 "../../prop-src/gcgen.pcc"
#line 64 "../../prop-src/gcgen.pcc"
)),
                               arg_ty, tys, k, true);
  }

  C.pr( "%-%^}\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates a tracing method for each base class
//  that is collectable.
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_super_class_tracing_methods
   (CodeGen& C, Tys tys, DefKind k)
{
  // Generate a call to the superclass
  if (this != root)
  {
    if (root->use_gc_base)
      C.pr( "%^%s%P::trace(gc__);", root->class_name, tys);
    else
      C.pr( "%^// call to method %s%P::trace() has been optimized out",
            root->class_name, tys);
  }

  for_each ( Inherit, inh, inherited_classes)
  {
    if((inh->qualifiers & QUALcollectable) || is_gc_ty(inh->super_class))
    {
      C.pr("%^%t::trace(gc__);",
      apply_ty( mkpolyty( inh->super_class,parameters), tys), "");
      if (this == root)
        root->use_gc_base = true;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates a tracing method for each field
//  that is collectable.
//
///////////////////////////////////////////////////////////////////////////////
void DatatypeClass::gen_field_tracing_methods
   (CodeGen& C, Exp exp, Ty ty, Tys tys, DefKind k, Bool toplevel)
{
  
#line 112 "../../prop-src/gcgen.pcc"
#line 160 "../../prop-src/gcgen.pcc"
{
  Ty _V1 = deref_all(ty);
  if (_V1) {
    switch (_V1->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V1)->_1)) {
          switch (_TYCONty(_V1)->_1->tag__) {
            case a_TyCon::tag_RECORDtycon: {
#line 127 "../../prop-src/gcgen.pcc"
              
              Ids ls;
              Tys ts;
              for( ls = _RECORDtycon(_TYCONty(_V1)->_1)->_1, ts = _TYCONty(_V1)->_2; ls && ts; ls = ls->_2, ts = ts->_2)
                gen_field_tracing_methods( C, DOTexp( exp, ls->_1), ts->_1, tys,k);
              
#line 132 "../../prop-src/gcgen.pcc"
              } break;
            case a_TyCon::tag_ARRAYtycon: {
              if (_TYCONty(_V1)->_2) {
                if (_TYCONty(_V1)->_2->_2) {
                  L1:; 
#line 148 "../../prop-src/gcgen.pcc"
                  
                  if (is_gc_ty(ty))
                  {
                    if (toplevel)
                      exp = DOTexp( exp, mangle( cons->name));
                    if (is_pointer_ty(ty))
                      C.pr( "%^%e = (%t)gc__->trace(%e);", exp, ty, "", exp);
                    else
                      C.pr( "%^gc__->trace(%e);",exp);
                    C.pr( " // %T", ty);
                  }
                  else
                    C.pr( "%^// omitted %T", ty); 
#line 160 "../../prop-src/gcgen.pcc"
                } else {
#line 134 "../../prop-src/gcgen.pcc"
                  
                  C.pr(
                        "%^{%+"
                        "%^for (int i__ = 0; i__ < %e; i__++)"
                        "%^{%+",
                        _ARRAYtycon(_TYCONty(_V1)->_1)->ARRAYtycon
                      );
                  gen_field_tracing_methods( C, INDEXexp( exp, IDexp( 
#line 141 "../../prop-src/gcgen.pcc"
#line 141 "../../prop-src/gcgen.pcc"
                  cocofmcocofm_p_r_o_pcn_s_r_cfm_g_c_g_e_nco_c_c_Q2
#line 141 "../../prop-src/gcgen.pcc"
#line 141 "../../prop-src/gcgen.pcc"
                  )), _TYCONty(_V1)->_2->_1, tys, k);
                  C.pr(
                        "%-%^}"
                        "%-%^}"
                      );
                  
#line 146 "../../prop-src/gcgen.pcc"
                }
              } else { goto L1; }
              } break;
            default: { goto L1; } break;
          }
        } else {
          switch ((int)_TYCONty(_V1)->_1) {
            case ((int)TUPLEtycon): {
#line 115 "../../prop-src/gcgen.pcc"
              
              int i = 1;
              for_each ( Ty, ty, _TYCONty(_V1)->_2)
                gen_field_tracing_methods( C, DOTexp( exp, index_of(i++)), ty, tys, k);
              
#line 119 "../../prop-src/gcgen.pcc"
              } break;
            case ((int)EXTUPLEtycon): {
#line 121 "../../prop-src/gcgen.pcc"
              
              int i = 1;
              for_each ( Ty, ty, _TYCONty(_V1)->_2)
                gen_field_tracing_methods( C, DOTexp( exp, index_of(i++)), ty, tys, k);
              
#line 125 "../../prop-src/gcgen.pcc"
              } break;
            default: { goto L1; } break;
          }
        }
        } break;
      default: { goto L1; } break;
    }
  } else { goto L1; }
}
#line 161 "../../prop-src/gcgen.pcc"
#line 161 "../../prop-src/gcgen.pcc"

}
#line 163 "../../prop-src/gcgen.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 23
Number of ifs generated      = 4
Number of switches generated = 3
Number of labels             = 1
Number of gotos              = 5
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
