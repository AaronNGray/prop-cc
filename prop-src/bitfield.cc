///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\bitfield.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/bitfield.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  Bitfields and opcode encoding/decoding
//
///////////////////////////////////////////////////////////////////////////////

#include <AD/contain/bitset.h>
#include "ir.h"
#include "ast.h"
#include "bitfield.h"
#include "hashtab.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Instantiate the datatype FieldDef
//
///////////////////////////////////////////////////////////////////////////////

#line 19 "../../prop-src/bitfield.pcc"
#line 19 "../../prop-src/bitfield.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype FieldDef
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype FieldLaw
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<FieldDef>
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<FieldLaw>
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype FieldDef
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype FieldLaw
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<FieldDef>
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<FieldDef>;
template a_List<FieldDef> * list_1_(FieldLaw x_1, a_List<FieldLaw> *  x_2);
template a_List<FieldDef> * list_1_(FieldLaw x_list_1_);
template int boxed(const a_List<FieldDef> *);
template int untag(const a_List<FieldDef> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<FieldLaw>
//
///////////////////////////////////////////////////////////////////////////////
#line 19 "../../prop-src/bitfield.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<FieldLaw>;
template a_List<FieldLaw> * list_1_(FieldDef x_1, a_List<FieldDef> *  x_2);
template a_List<FieldLaw> * list_1_(FieldDef x_list_1_);
template int boxed(const a_List<FieldLaw> *);
template int untag(const a_List<FieldLaw> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

#line 19 "../../prop-src/bitfield.pcc"
#line 19 "../../prop-src/bitfield.pcc"


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

BitfieldCompiler:: BitfieldCompiler() {}
BitfieldCompiler::~BitfieldCompiler() {}

///////////////////////////////////////////////////////////////////////////////
//
//  Environment for storing bitfields.
//
///////////////////////////////////////////////////////////////////////////////

static HashTable bitfield_env(string_hash, string_equal);

///////////////////////////////////////////////////////////////////////////////
//
//  Method to insert bitfield definition into environment.
//
///////////////////////////////////////////////////////////////////////////////

void insert_bitfield( Id name, FieldDef field_def)
{
  HashTable::Entry * e = bitfield_env.lookup(name);
  if (e)
  {
    error ("%!redefinition of bitfield '%s'.\n"
            "%!this is where it is last defined.\n",
            ((FieldDef)e->v)->loc(), name, field_def->loc()
    );
  }
  else
  {
    bitfield_env.insert(name,field_def);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Check the bitfield patterns for consistency
//
///////////////////////////////////////////////////////////////////////////////

void check_bitfield_consistency (Id name, int width, FieldDefs field_defs)
{
  if (width < 0 || width >= 4096)
  {
    error ("%Lillegal width in bitfield '%s (%i)'\n", name, width);
    return;
  }

  BitSet * referred = new (mem_pool, width) BitSet;

  for_each (FieldDef, f, field_defs)
  {
    
#line 78 "../../prop-src/bitfield.pcc"
#line 93 "../../prop-src/bitfield.pcc"
{
  if (f->tag__) {
    } else {
    
    if (
#line 81 "../../prop-src/bitfield.pcc"
    (((((_FIELDdef(f)->from_bit < 0) || (_FIELDdef(f)->to_bit < 0)) || (_FIELDdef(f)->from_bit > _FIELDdef(f)->to_bit)) || (_FIELDdef(f)->from_bit >= width)) || (_FIELDdef(f)->to_bit >= width))
#line 82 "../../prop-src/bitfield.pcc"
) {
      
#line 83 "../../prop-src/bitfield.pcc"
      
      error ("%Lillegal bit range in bitfield '%s(%i)::%s (%i:%i)'\n",
                name, width, _FIELDdef(f)->field_name, _FIELDdef(f)->from_bit, _FIELDdef(f)->to_bit);
      
#line 86 "../../prop-src/bitfield.pcc"
    } else {
      
#line 88 "../../prop-src/bitfield.pcc"
      
      for (int i = _FIELDdef(f)->from_bit; i <= _FIELDdef(f)->to_bit; i++)
          referred->add(i);
      
#line 91 "../../prop-src/bitfield.pcc"
    }
  }
}
#line 93 "../../prop-src/bitfield.pcc"
#line 93 "../../prop-src/bitfield.pcc"

  }

  // Check that all the bits are covered by the bitfield declaration
  for (int i = 0; i < width; )
  {
    if (! referred->contains(i))
    {
      int j;
      for (j = i+1; j < width && ! referred->contains(j); j++);
      msg ("%L%wrange (%i:%i) missing in bitfield '%s (%i)'\n",
           i, j-1, name, width);
      i = j;
    }
    else
    {
      i++;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compile a bitfield declaration
//
///////////////////////////////////////////////////////////////////////////////

void BitfieldCompiler::define_bitfield
   (Id name, int width, FieldDefs field_defs, FieldLaws field_laws)
{
  // make sure that the bitfields are range consistent.
  check_bitfield_consistency(name, width, field_defs);

  // insert into environment
  for_each (FieldDef, f, field_defs)
  {
    
#line 129 "../../prop-src/bitfield.pcc"
#line 131 "../../prop-src/bitfield.pcc"
{
  if (f->tag__) {
    
#line 131 "../../prop-src/bitfield.pcc"
   insert_bitfield(_FIELDCONdef(f)->field_name, f); 
#line 131 "../../prop-src/bitfield.pcc"
  } else {
    
#line 130 "../../prop-src/bitfield.pcc"
   insert_bitfield(_FIELDdef(f)->field_name, f); 
#line 130 "../../prop-src/bitfield.pcc"
  }
}
#line 132 "../../prop-src/bitfield.pcc"
#line 132 "../../prop-src/bitfield.pcc"

  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate code for a bitfield declaration
//
///////////////////////////////////////////////////////////////////////////////

void BitfieldCompiler::gen_bitfield
   (Id name, int width, FieldDefs field_defs, FieldLaws laws)
{
  pr(
      "%^%/"
      "%^// Definitions for bitfield '%s (%i)'"
      "%^%/",
      name, width
      );
  for_each (FieldLaw, l, laws)
  {
    
#line 153 "../../prop-src/bitfield.pcc"
#line 159 "../../prop-src/bitfield.pcc"
{
#line 156 "../../prop-src/bitfield.pcc"
  
  (*output) << "#define " << l->id << "(" << l->args << ") |"
              << l->guard << " = " << l->exp << '\n';
  
#line 159 "../../prop-src/bitfield.pcc"
}
#line 160 "../../prop-src/bitfield.pcc"
#line 160 "../../prop-src/bitfield.pcc"

  }
}
#line 163 "../../prop-src/bitfield.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 1
Number of ifs generated      = 3
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
