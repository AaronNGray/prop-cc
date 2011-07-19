///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\persistgen.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_p_e_r_s_i_s_t_g_e_nco_c_c_Q2("i__");
static const Quark cocofmcocofm_p_r_o_pcn_s_r_cfm_p_e_r_s_i_s_t_g_e_nco_c_c_Q1("this");
#line 1 "../../prop-src/persistgen.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file handles persistent datatypes processing.
//
///////////////////////////////////////////////////////////////////////////////

#include <AD/strings/quark.h>
#include "basics.h"
#include "ir.h"
#include "ast.h"
#include "datagen.h"
#include "type.h"
#include "hashtab.h"
#include "options.h"
#include "datatype.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Equality and hashing on cons/tys pairs
//
///////////////////////////////////////////////////////////////////////////////

unsigned int id_tys_hash( HashTable::Key a)
{
  
#line 25 "../../prop-src/persistgen.pcc"
a_Pair<Id, Tys> *  
#line 25 "../../prop-src/persistgen.pcc"
 key = (a_Pair<Id, Tys> *  
#line 25 "../../prop-src/persistgen.pcc"
)a;
  return (unsigned int)key->fst + tys_hash(key->snd);
}

Bool id_tys_equal( HashTable::Key a, HashTable::Key b)
{
  a_Pair<Id, Tys> *  
#line 31 "../../prop-src/persistgen.pcc"
 x = (a_Pair<Id, Tys> *  
#line 31 "../../prop-src/persistgen.pcc"
)a;
  a_Pair<Id, Tys> *  
#line 32 "../../prop-src/persistgen.pcc"
 y = (a_Pair<Id, Tys> *  
#line 32 "../../prop-src/persistgen.pcc"
)b;
  return x->fst == y->fst && tys_equal(x->snd,y->snd);
}

unsigned int pid_hash( HashTable::Key pid)
{
  
#line 41 "../../prop-src/persistgen.pcc"
{
  Pid _V1 = Pid(pid);
  if (_V1) {
#line 40 "../../prop-src/persistgen.pcc"
   return string_hash(_V1->PERSISTid); 
#line 40 "../../prop-src/persistgen.pcc"
  } else {
#line 41 "../../prop-src/persistgen.pcc"
   return 1235; 
#line 41 "../../prop-src/persistgen.pcc"
  }
}
#line 42 "../../prop-src/persistgen.pcc"
#line 42 "../../prop-src/persistgen.pcc"

}

Bool pid_equal( HashTable::Key a, HashTable::Key b)
{
  
#line 47 "../../prop-src/persistgen.pcc"
#line 50 "../../prop-src/persistgen.pcc"
{
  Pid _V2 = Pid(a);
  Pid _V3 = Pid(b);
  if (_V2) {
    if (_V3) {
#line 49 "../../prop-src/persistgen.pcc"
     return string_equal( _V2->PERSISTid, _V3->PERSISTid); 
#line 49 "../../prop-src/persistgen.pcc"
    } else {
      L1:; 
#line 50 "../../prop-src/persistgen.pcc"
     return false; 
#line 50 "../../prop-src/persistgen.pcc"
    }
  } else { goto L1; }
}
#line 51 "../../prop-src/persistgen.pcc"
#line 51 "../../prop-src/persistgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Global hashtables to store mapping from types to persistent Id's
//  and vice versa.
//
///////////////////////////////////////////////////////////////////////////////

HashTable type_pid_map( id_tys_hash, id_tys_equal);
HashTable pid_type_map( pid_hash, pid_equal);

///////////////////////////////////////////////////////////////////////////////
//
//  Enter a new persistent id entry
//
///////////////////////////////////////////////////////////////////////////////

void update_persistent( Id id, Tys tys, Pid pid)
{
  
#line 72 "../../prop-src/persistgen.pcc"
a_Pair<Id, Tys> *  
#line 72 "../../prop-src/persistgen.pcc"
 key = makepair( id, tys);
  HashTable::Entry * e1 = type_pid_map.lookup((HashTable::Key)key);
  HashTable::Entry * e2 = pid_type_map.lookup((HashTable::Key)pid);
  if (e1)
    error ("%Lpersistence redefined for type %s%P\n",id,tys);
  if (e2)
  {
    a_Pair<Id, Tys> *  
#line 79 "../../prop-src/persistgen.pcc"
 previous = (a_Pair<Id, Tys> *  
#line 79 "../../prop-src/persistgen.pcc"
)(e2->v);
    error( "%Lpersistence pid %Q already allocated for type %s%P\n",
           pid, previous->fst, previous->snd);
  }
  if (e1 == 0 && e2 == 0)
  {
    type_pid_map.insert( key, (HashTable::Value) pid);
    pid_type_map.insert( (HashTable::Key) pid, key);
  }

  // add persistent qualifier to the constructor's type

  
#line 96 "../../prop-src/persistgen.pcc"
{
  Ty _V4 = lookup_ty(id);
  if (_V4) {
    switch (_V4->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V4)->_1)) {
          switch (_TYCONty(_V4)->_1->tag__) {
            case a_TyCon::tag_DATATYPEtycon: {
              if (
#line 93 "../../prop-src/persistgen.pcc"
              (_DATATYPEtycon(_TYCONty(_V4)->_1)->hierarchy != 0)
#line 93 "../../prop-src/persistgen.pcc"
) {
                
#line 94 "../../prop-src/persistgen.pcc"
               _DATATYPEtycon(_TYCONty(_V4)->_1)->hierarchy->qualifiers |= QUALpersistent; 
#line 94 "../../prop-src/persistgen.pcc"
              } else {
                
                L2:; 
#line 96 "../../prop-src/persistgen.pcc"
               error("%Ltype %s%P is not a datatype\n",id,tys); 
#line 96 "../../prop-src/persistgen.pcc"
              }
              } break;
            default: { goto L2; } break;
          }
        } else { goto L2; }
        } break;
      default: { goto L2; } break;
    }
  } else { goto L2; }
}
#line 97 "../../prop-src/persistgen.pcc"
#line 97 "../../prop-src/persistgen.pcc"

}

///////////////////////////////////////////////////////////////////////////////
//
//  Lookup a new persistent id entry
//
///////////////////////////////////////////////////////////////////////////////

Pid lookup_persistent( Id id, Tys tys)
{  
#line 107 "../../prop-src/persistgen.pcc"
a_Pair<Id, Tys> *  
#line 107 "../../prop-src/persistgen.pcc"
 key = makepair( id, tys);
   HashTable::Entry * e1 = type_pid_map.lookup( (HashTable::Key) key);
   if (e1)
     return value_of( Pid, type_pid_map, e1);
   else
     return PERSISTnone;
}

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates the class interface of a persistence object
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeClass::generate_persistence_interface( CodeGen& C)
{
  C.pr(
        "%^%/"
        "%^//"
        "%^// Methods for persistence and object serialization"
        "%^//"
        "%^%/"
        "%-%^protected:%+"
        "%^virtual const PObjectType& persist_type_id () const;"
        "%^virtual Pistream&          persist_read    (Pistream&);"
        "%^virtual Postream&          persist_write   (Postream&) const;"
        "%-%^public:%+"
      );

  C.pr(
        "%^// Default constructor for persistence object factory"
        "%^%s();",
        class_name
      );
}

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates the implementation of the persistent I/O functions
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeClass::generate_persistence_implementation
   (CodeGen& C, Tys tys, DefKind k)
{
  Id obj_type = DatatypeCompiler::temp_vars.new_label();

  //
  // Generate a PObjectType object for this class.
  //

  Pid pid  = lookup_persistent( root->datatype_name, tys);

  if (pid == PERSISTnone)
    error( "%Lpersist object id is undefined for %s%P\n",
           root->datatype_name, tys);

  //
  // Generate a default constructor for this class
  //

  C.pr( "%^%s%P::%s()", class_name, tys, class_name);

  if (this != root && root->has_variant_tag)
    C.pr( " : %s%P(tag_%S)", root->class_name, tys, constructor_name);
  C.pr( "%^{%+");
  gen_class_constructor_body( C, tys, k);
  C.pr( "%-%^}");

  //
  // Generate the object type for this class
  //

  C.pr(
        "%^static PObjectType %s(%Q \"(%s%P::%s)\");"
        "%^const PObjectType& %s%P::persist_type_id() const { return %s; }",
        obj_type, pid, root->datatype_name, tys,
        (cons == NOcons ? "base_class" : constructor_name),
        class_name, tys, obj_type
      );

  if (cons != NOcons)
  {
    //
    //  Generate an object factory for this class if it is creatable.
    //
    C.pr( "%^static PObjectFactory< %s%P > %s(%s);\n",
          class_name, tys, DatatypeCompiler::temp_vars.new_label(), obj_type);
  }

  //
  // Generate the read method
  //
  Exp self_exp = DEREFexp( IDexp( 
#line 200 "../../prop-src/persistgen.pcc"
cocofmcocofm_p_r_o_pcn_s_r_cfm_p_e_r_s_i_s_t_g_e_nco_c_c_Q1
#line 200 "../../prop-src/persistgen.pcc"
#line 200 "../../prop-src/persistgen.pcc"
));
  C.pr( "%^Pistream& %s%P::persist_read(Pistream& strm__)"
        "%^{%+",
        class_name, tys);

  gen_super_class_persist_IO( C, tys, k, ">>");

  if (cons != NOcons)
    gen_field_persist_IO( C, self_exp, cons_arg_ty, tys, k, ">>", true);

  C.pr( "%^return strm__;%-%^}");

  //
  // Generate the write method
  //
  C.pr( "%^Postream& %s%P::persist_write(Postream& strm__) const"
        "%^{%+",
        class_name, tys);
  gen_super_class_persist_IO( C, tys, k, "<<");
  if (cons != NOcons)
     gen_field_persist_IO( C, self_exp, cons_arg_ty, tys, k, "<<", true);
  C.pr( "%^return strm__;%-%^}");
}

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates the persistence calls I/O for superclasses
//
///////////////////////////////////////////////////////////////////////////////
void DatatypeClass::gen_super_class_persist_IO
   (CodeGen& C, Tys tys, DefKind k, Id io_op)
{
  // Generate a call to the superclass
  Id rw = io_op[0] == '>' ? "read" : "write";
  if (this != root)
    C.pr( "%^%s%P::persist_%s(strm__);", root->class_name, tys, rw);

  // Generate a call to all the persistent superclasses

  for_each (Inherit, inh, inherited_classes)
  {
    if ((inh->qualifiers & QUALpersistent) ||
    has_qual(QUALpersistent,inh->super_class))
    {
      C.pr( "%t::trace(strm__);",
          apply_ty( mkpolyty( inh->super_class, parameters), tys), "");
      if (this == root)
        root->use_persist_base = true;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  This method generates the persistence calls I/O for individual
//  fields of the datatype
//
///////////////////////////////////////////////////////////////////////////////

void DatatypeClass::gen_field_persist_IO
   (CodeGen& C, Exp exp, Ty ty, Tys tys, DefKind k, Id io, Bool toplevel)
{
  Bool is_reading = io[0] == '>';

  
#line 264 "../../prop-src/persistgen.pcc"
#line 309 "../../prop-src/persistgen.pcc"
{
  Ty _V5 = deref(ty);
  if (_V5) {
    switch (_V5->tag__) {
      case a_Ty::tag_TYCONty: {
        if (boxed(_TYCONty(_V5)->_1)) {
          switch (_TYCONty(_V5)->_1->tag__) {
            case a_TyCon::tag_RECORDtycon: {
#line 279 "../../prop-src/persistgen.pcc"
              
              Ids ls; Tys ts;
              for( ls = _RECORDtycon(_TYCONty(_V5)->_1)->_1, ts = _TYCONty(_V5)->_2; ls && ts; ls = ls->_2, ts = ts->_2)
                gen_field_persist_IO( C, DOTexp( exp, ls->_1), ts->_1, tys, k, io);
              
#line 283 "../../prop-src/persistgen.pcc"
              } break;
            case a_TyCon::tag_ARRAYtycon: {
              if (_TYCONty(_V5)->_2) {
                if (_TYCONty(_V5)->_2->_2) {
                  L3:; 
#line 299 "../../prop-src/persistgen.pcc"
                  
                  if (toplevel)
                    exp = DOTexp( exp, mangle(cons->name));
                  
                  if (is_reading && is_datatype(_V5))
                    C.pr( "%^%e = (%t)read_object(strm__);", exp, _V5, "");
                  else
                    C.pr( "%^strm__ %s %e;",io, exp, _V5);
                  
                  C.pr( " // %T", _V5);
                  
#line 309 "../../prop-src/persistgen.pcc"
                } else {
#line 285 "../../prop-src/persistgen.pcc"
                  
                  C.pr(
                        "%^{%+"
                        "%^for (int i__ = 0; i__ < %e; i__++)"
                        "%^{%+",
                        _ARRAYtycon(_TYCONty(_V5)->_1)->ARRAYtycon
                      );
                  gen_field_persist_IO( C, INDEXexp( exp, IDexp( 
#line 292 "../../prop-src/persistgen.pcc"
#line 292 "../../prop-src/persistgen.pcc"
                  cocofmcocofm_p_r_o_pcn_s_r_cfm_p_e_r_s_i_s_t_g_e_nco_c_c_Q2
#line 292 "../../prop-src/persistgen.pcc"
#line 292 "../../prop-src/persistgen.pcc"
                  )), _TYCONty(_V5)->_2->_1, tys, k, io);
                  C.pr(
                        "%-%^}"
                        "%-%^}"
                      );
                  
#line 297 "../../prop-src/persistgen.pcc"
                }
              } else { goto L3; }
              } break;
            default: { goto L3; } break;
          }
        } else {
          switch ((int)_TYCONty(_V5)->_1) {
            case ((int)v_TUPLEtycon): {
#line 267 "../../prop-src/persistgen.pcc"
              
              int i = 1;
              for_each ( Ty, ty, _TYCONty(_V5)->_2)
                gen_field_persist_IO( C, DOTexp( exp, index_of(i++)), ty, tys, k, io);
              
#line 271 "../../prop-src/persistgen.pcc"
              } break;
            case ((int)v_EXTUPLEtycon): {
#line 273 "../../prop-src/persistgen.pcc"
              
              int i = 1;
              for_each ( Ty, ty, _TYCONty(_V5)->_2)
                gen_field_persist_IO( C, DOTexp( exp, index_of(i++)), ty, tys, k, io);
              
#line 277 "../../prop-src/persistgen.pcc"
              } break;
            default: { goto L3; } break;
          }
        }
        } break;
      default: { goto L3; } break;
    }
  } else { goto L3; }
}
#line 310 "../../prop-src/persistgen.pcc"
#line 310 "../../prop-src/persistgen.pcc"

}
#line 312 "../../prop-src/persistgen.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 50
Number of ifs generated      = 10
Number of switches generated = 5
Number of labels             = 3
Number of gotos              = 10
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
