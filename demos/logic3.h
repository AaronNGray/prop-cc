///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.6),
//  last updated on Nov 2, 1999.
//  The original source file is "logic3.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_PRINTER_USED
#define PROP_QUARK_USED
#include <propdefs.h>
///////////////////////////////////////////////////////////////////////////////
//  Quark literals
///////////////////////////////////////////////////////////////////////////////
static const Quark _l_o_g_i_c_3co_h_Q3("->");
static const Quark _l_o_g_i_c_3co_h_Q4("xor");
static const Quark _l_o_g_i_c_3co_h_Q1("and");
static const Quark _l_o_g_i_c_3co_h_Q2("or");
static const Quark _l_o_g_i_c_3co_h_Q5("<->");
#line 1 "logic3.ph"
#ifndef logic3_demo_h
#define logic3_demo_h

#include <stdlib.h>
#include <AD/strings/quark.h>

#line 7 "logic3.ph"
#line 20 "logic3.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Wff
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Wff_defined
#define datatype_Wff_defined
   class a_Wff;
   typedef a_Wff * Wff;
#endif

#  define True (Wff)0
#  define False (Wff)1

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Wff
//
///////////////////////////////////////////////////////////////////////////////
class a_Wff : public TermObj {
public:
   enum Tag_Wff {
      tag_Var = 0, tag_Op = 1, tag_Not = 2
   };

public:
   const Tag_Wff tag__; // variant tag
protected:
   inline a_Wff(Tag_Wff t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Wff * x) { return (unsigned long)x >= 2; }
inline int untag(const a_Wff * x) { return boxed(x) ? x->tag__ + 2 : (int)x; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for Wff
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, Wff);
extern PrettyOStream& operator<<(PrettyOStream&, Wff);
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Wff::Var
//
///////////////////////////////////////////////////////////////////////////////
class Wff_Var : public a_Wff {
public:
#line 10 "logic3.ph"
   Quark Var; 
   inline Wff_Var (Quark const & x_Var)
    : a_Wff(tag_Var), Var(x_Var)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Wff::Op
//
///////////////////////////////////////////////////////////////////////////////
class Wff_Op : public a_Wff {
public:
#line 10 "logic3.ph"
   Quark _1; Wff _2; Wff _3; 
   inline Wff_Op (Quark const & x_1, Wff x_2, Wff x_3)
    : a_Wff(tag_Op), _1(x_1), _2(x_2), _3(x_3)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Wff::Not
//
///////////////////////////////////////////////////////////////////////////////
class Wff_Not : public a_Wff {
public:
#line 11 "logic3.ph"
   Wff Not; 
   inline Wff_Not (Wff x_Not)
    : a_Wff(tag_Not), Not(x_Not)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Wff
//
///////////////////////////////////////////////////////////////////////////////
inline a_Wff * Var (Quark const & x_Var)
{
   return new Wff_Var (x_Var);
}
inline a_Wff * Op (Quark const & x_1, Wff x_2, Wff x_3)
{
   return new Wff_Op (x_1, x_2, x_3);
}
inline a_Wff * Not (Wff x_Not)
{
   return new Wff_Not (x_Not);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Wff
//
///////////////////////////////////////////////////////////////////////////////
inline Wff_Var * _Var(const a_Wff * _x_) { return (Wff_Var *)_x_; }
inline Wff_Op * _Op(const a_Wff * _x_) { return (Wff_Op *)_x_; }
inline Wff_Not * _Not(const a_Wff * _x_) { return (Wff_Not *)_x_; }

///////////////////////////////////////////////////////////////////////////////
// Definition of law And
///////////////////////////////////////////////////////////////////////////////
#line 14 "logic3.ph"
inline Wff And(Wff a, Wff b)
{ return Op(_l_o_g_i_c_3co_h_Q1,a,b); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Or
///////////////////////////////////////////////////////////////////////////////
#line 16 "logic3.ph"
inline Wff Or(Wff a, Wff b)
{ return Op(_l_o_g_i_c_3co_h_Q2,a,b); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Implies
///////////////////////////////////////////////////////////////////////////////
#line 17 "logic3.ph"
inline Wff Implies(Wff a, Wff b)
{ return Op(_l_o_g_i_c_3co_h_Q3,a,b); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Xor
///////////////////////////////////////////////////////////////////////////////
#line 18 "logic3.ph"
inline Wff Xor(Wff a, Wff b)
{ return Op(_l_o_g_i_c_3co_h_Q4,a,b); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Equiv
///////////////////////////////////////////////////////////////////////////////
#line 19 "logic3.ph"
inline Wff Equiv(Wff a, Wff b)
{ return Op(_l_o_g_i_c_3co_h_Q5,a,b); }

#line 20 "logic3.ph"
#line 20 "logic3.ph"


#endif
#line 23 "logic3.ph"
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
