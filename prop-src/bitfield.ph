///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the definitions used in the bitfield and bitfield
//  pattern matcher/constraint solver.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef bitfields_and_bit_patterns_h
#define bitfields_and_bit_patterns_h

#include "ast.ph"
#include "codegen.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of a field declaration
//
///////////////////////////////////////////////////////////////////////////////

datatype FieldDef : Loc =
  FIELDdef
  {
    field_name : Id,        // bitfield declaration
    from_bit   : int,
    to_bit     : int,
    is_signed  : Bool = false
  }
| FIELDCONdef
  {
    field_name : Id,        // bitfield constructor
    ty         : Ty
  }
and FieldLaw : Loc =
  FIELDlaw
  {
    id    : Id,
    args  : Ids,
    guard : Exp,
    exp   : Exp
  }
;

///////////////////////////////////////////////////////////////////////////////
//  The bitfield compiler is used to compile bitfield constructors
//  and patterns.
///////////////////////////////////////////////////////////////////////////////

class BitfieldCompiler : virtual public CodeGen {
  BitfieldCompiler (const BitfieldCompiler&);
  void operator = (const BitfieldCompiler&);
public:
           BitfieldCompiler();
  virtual ~BitfieldCompiler();

  ////////////////////////////////////////////////////////////////////////////
  //  Methods to define and generate bitfield declarations.
  ////////////////////////////////////////////////////////////////////////////
  void define_bitfield( Id name, int width, FieldDefs, FieldLaws);
  void gen_bitfield( Id name, int width, FieldDefs, FieldLaws);
};

#endif
