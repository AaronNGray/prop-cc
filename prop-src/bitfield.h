///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\bitfield.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/bitfield.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the definitions used in the bitfield and bitfield
//  pattern matcher/constraint solver.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef bitfields_and_bit_patterns_h
#define bitfields_and_bit_patterns_h

#include "ast.h"
#include "codegen.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of a field declaration
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/bitfield.ph"
#line 41 "../../prop-src/bitfield.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for FieldDef
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_FieldDef_defined
#define datatype_FieldDef_defined
  class a_FieldDef;
  typedef a_FieldDef * FieldDef;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for FieldLaw
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_FieldLaw_defined
#define datatype_FieldLaw_defined
  class a_FieldLaw;
  typedef a_FieldLaw * FieldLaw;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype FieldDef
//
///////////////////////////////////////////////////////////////////////////////
class a_FieldDef : public Loc {
public:
  enum Tag_FieldDef {
    tag_FIELDdef = 0, tag_FIELDCONdef = 1
  };

public:
  const Tag_FieldDef tag__; // variant tag
protected:
  inline a_FieldDef(Tag_FieldDef t__) : tag__(t__) {}
public:
};
inline int boxed(const a_FieldDef *) { return 1; }
inline int untag(const a_FieldDef * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor FieldDef::FIELDdef
//
///////////////////////////////////////////////////////////////////////////////
class FieldDef_FIELDdef : public a_FieldDef {
public:
#line 20 "../../prop-src/bitfield.ph"
  Id field_name; int from_bit; int to_bit; Bool is_signed; 
  inline FieldDef_FIELDdef (Id x_field_name, int x_from_bit, int x_to_bit, Bool x_is_signed = false)
   : a_FieldDef(tag_FIELDdef), field_name(x_field_name), from_bit(x_from_bit), to_bit(x_to_bit), is_signed(x_is_signed)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor FieldDef::FIELDCONdef
//
///////////////////////////////////////////////////////////////////////////////
class FieldDef_FIELDCONdef : public a_FieldDef {
public:
#line 28 "../../prop-src/bitfield.ph"
  Id field_name; Ty ty; 
  inline FieldDef_FIELDCONdef (Id x_field_name, Ty x_ty)
   : a_FieldDef(tag_FIELDCONdef), field_name(x_field_name), ty(x_ty)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for FieldDef
//
///////////////////////////////////////////////////////////////////////////////
inline a_FieldDef * FIELDdef (Id x_field_name, int x_from_bit, int x_to_bit, Bool x_is_signed = false)
{
  return new FieldDef_FIELDdef (x_field_name, x_from_bit, x_to_bit, x_is_signed);
}
inline a_FieldDef * FIELDCONdef (Id x_field_name, Ty x_ty)
{
  return new FieldDef_FIELDCONdef (x_field_name, x_ty);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for FieldDef
//
///////////////////////////////////////////////////////////////////////////////
inline FieldDef_FIELDdef * _FIELDdef(const a_FieldDef * _x_) { return (FieldDef_FIELDdef *)_x_; }
inline FieldDef_FIELDCONdef * _FIELDCONdef(const a_FieldDef * _x_) { return (FieldDef_FIELDCONdef *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor FieldLaw::FIELDlaw
//
///////////////////////////////////////////////////////////////////////////////
class a_FieldLaw : public Loc {
public:
#line 33 "../../prop-src/bitfield.ph"
  Id id; Ids args; Exp guard; Exp exp; 
  inline a_FieldLaw (Id x_id, Ids x_args, Exp x_guard, Exp x_exp)
   : id(x_id), args(x_args), guard(x_guard), exp(x_exp)
  {
  }
};
inline int boxed(const a_FieldLaw *) { return 1; }
inline int untag(const a_FieldLaw *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for FieldLaw
//
///////////////////////////////////////////////////////////////////////////////
inline a_FieldLaw * FIELDlaw (Id x_id, Ids x_args, Exp x_guard, Exp x_exp)
{
  return new a_FieldLaw (x_id, x_args, x_guard, x_exp);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for FieldLaw
//
///////////////////////////////////////////////////////////////////////////////


#line 41 "../../prop-src/bitfield.ph"
#line 41 "../../prop-src/bitfield.ph"


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
#line 63 "../../prop-src/bitfield.ph"
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
