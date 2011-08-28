///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\..\app\willard\willard-ast.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#include <propdefs.h>
#line 1 "../../../app/willard/willard-ast.ph"
#ifndef willard_ast_h 
#define willard_ast_h

#include <AD/generic/generic.h>
class PrettyOStream;


struct ConsCounter { static int count; ConsCounter() { count++; } };

#line 10 "../../../app/willard/willard-ast.ph"
#line 10 "../../../app/willard/willard-ast.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for List<T>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_List_defined
#define datatype_List_defined
template <class T> class a_List;
#define List(T) a_List<T> *
#endif

#  define v_nil_1_ 0

#  define nil_1_ v_nil_1_

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor List<T>::#[...]
//
///////////////////////////////////////////////////////////////////////////////
template <class T> class a_List : public ConsCounter {
public:
#line 10 "../../../app/willard/willard-ast.ph"
  T _1; a_List<T> *  _2; 
  inline a_List (T x_1, a_List<T> *  x_2)
   : _1(x_1), _2(x_2)
  {
  }
  inline a_List (T x_1)
   : _1(x_1), _2((a_List<T> *)0)
  {
  }
};
template <class T> inline int boxed(const a_List<T> * x) { return x != 0; }
template <class T> inline int untag(const a_List<T> * x) { return x ? 1 : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for List<T>
//
///////////////////////////////////////////////////////////////////////////////
template <class T> inline a_List<T> * list_1_ (T x_1, a_List<T> *  x_2)
{
  return new a_List<T> (x_1, x_2);
}
template <class T> inline a_List<T> * list_1_ (T x_1)
{
  return new a_List<T> (x_1);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for List<T>
//
///////////////////////////////////////////////////////////////////////////////


#line 10 "../../../app/willard/willard-ast.ph"
#line 10 "../../../app/willard/willard-ast.ph"

#line 11 "../../../app/willard/willard-ast.ph"
#line 11 "../../../app/willard/willard-ast.ph"
#line 11 "../../../app/willard/willard-ast.ph"
#line 11 "../../../app/willard/willard-ast.ph"


//
//  This is the abstract syntax of the query language
//
#line 16 "../../../app/willard/willard-ast.ph"
#line 52 "../../../app/willard/willard-ast.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Literal
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Literal_defined
#define datatype_Literal_defined
  class a_Literal;
  typedef a_Literal * Literal;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Exp
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Exp_defined
#define datatype_Exp_defined
  class a_Exp;
  typedef a_Exp * Exp;
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type Id
///////////////////////////////////////////////////////////////////////////////
#line 49 "../../../app/willard/willard-ast.ph"
typedef char const * Id;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Ids
///////////////////////////////////////////////////////////////////////////////
#line 50 "../../../app/willard/willard-ast.ph"
typedef a_List<Id> *  Ids;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Exps
///////////////////////////////////////////////////////////////////////////////
#line 51 "../../../app/willard/willard-ast.ph"
typedef a_List<Exp> *  Exps;

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
class a_Literal : public ConsCounter {
public:
  enum Tag_Literal {
    tag_INT = 0, tag_STRING = 1, tag_BOOL = 2
  };

public:
  const Tag_Literal tag__; // variant tag
protected:
  inline a_Literal(Tag_Literal t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Literal *) { return 1; }
inline int untag(const a_Literal * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::INT
//
///////////////////////////////////////////////////////////////////////////////
class Literal_INT : public a_Literal {
public:
#line 16 "../../../app/willard/willard-ast.ph"
  int INT; 
  inline Literal_INT (int x_INT)
   : a_Literal(tag_INT), INT(x_INT)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::STRING
//
///////////////////////////////////////////////////////////////////////////////
class Literal_STRING : public a_Literal {
public:
#line 17 "../../../app/willard/willard-ast.ph"
  char const * STRING; 
  inline Literal_STRING (char const * x_STRING)
   : a_Literal(tag_STRING), STRING(x_STRING)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Literal::BOOL
//
///////////////////////////////////////////////////////////////////////////////
class Literal_BOOL : public a_Literal {
public:
#line 18 "../../../app/willard/willard-ast.ph"
  Bool BOOL; 
  inline Literal_BOOL (Bool x_BOOL)
   : a_Literal(tag_BOOL), BOOL(x_BOOL)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Literal
//
///////////////////////////////////////////////////////////////////////////////
inline a_Literal * INT (int x_INT)
{
  return new Literal_INT (x_INT);
}
inline a_Literal * STRING (char const * x_STRING)
{
  return new Literal_STRING (x_STRING);
}
inline a_Literal * BOOL (Bool x_BOOL)
{
  return new Literal_BOOL (x_BOOL);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Literal
//
///////////////////////////////////////////////////////////////////////////////
inline Literal_INT * _INT(const a_Literal * _x_) { return (Literal_INT *)_x_; }
inline Literal_STRING * _STRING(const a_Literal * _x_) { return (Literal_STRING *)_x_; }
inline Literal_BOOL * _BOOL(const a_Literal * _x_) { return (Literal_BOOL *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
class a_Exp : public ConsCounter, public TermObj {
public:
  enum Tag_Exp {
    tag_OP = 0, tag_APP = 1, tag_LIT = 2, 
    tag_ID = 3, tag_TUPLE = 4, tag_FORALL = 5, 
    tag_EXISTS = 6, tag_GUARD = 7, tag_GENERATOR = 8, 
    tag_LET = 9
  };

public:
  const Tag_Exp tag__; // variant tag
protected:
  inline a_Exp(Tag_Exp t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Exp *) { return 1; }
inline int untag(const a_Exp * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::OP
//
///////////////////////////////////////////////////////////////////////////////
class Exp_OP : public a_Exp {
public:
#line 20 "../../../app/willard/willard-ast.ph"
  Id _1; Exps _2; 
  inline Exp_OP (Id x_1, Exps x_2)
   : a_Exp(tag_OP), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::APP
//
///////////////////////////////////////////////////////////////////////////////
class Exp_APP : public a_Exp {
public:
#line 21 "../../../app/willard/willard-ast.ph"
  Id _1; Exps _2; 
  inline Exp_APP (Id x_1, Exps x_2)
   : a_Exp(tag_APP), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::LIT
//
///////////////////////////////////////////////////////////////////////////////
class Exp_LIT : public a_Exp {
public:
#line 22 "../../../app/willard/willard-ast.ph"
  Literal LIT; 
  inline Exp_LIT (Literal x_LIT)
   : a_Exp(tag_LIT), LIT(x_LIT)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::ID
//
///////////////////////////////////////////////////////////////////////////////
class Exp_ID : public a_Exp {
public:
#line 23 "../../../app/willard/willard-ast.ph"
  Id ID; 
  inline Exp_ID (Id x_ID)
   : a_Exp(tag_ID), ID(x_ID)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::TUPLE
//
///////////////////////////////////////////////////////////////////////////////
class Exp_TUPLE : public a_Exp {
public:
#line 24 "../../../app/willard/willard-ast.ph"
  Exps TUPLE; 
  inline Exp_TUPLE (Exps x_TUPLE)
   : a_Exp(tag_TUPLE), TUPLE(x_TUPLE)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::FORALL
//
///////////////////////////////////////////////////////////////////////////////
class Exp_FORALL : public a_Exp {
public:
#line 25 "../../../app/willard/willard-ast.ph"
  Id _1; Exp _2; Exp _3; 
  inline Exp_FORALL (Id x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_FORALL), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::EXISTS
//
///////////////////////////////////////////////////////////////////////////////
class Exp_EXISTS : public a_Exp {
public:
#line 26 "../../../app/willard/willard-ast.ph"
  Id _1; Exp _2; Exp _3; 
  inline Exp_EXISTS (Id x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_EXISTS), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::GUARD
//
///////////////////////////////////////////////////////////////////////////////
class Exp_GUARD : public a_Exp {
public:
#line 27 "../../../app/willard/willard-ast.ph"
  Exp _1; Exp _2; 
  inline Exp_GUARD (Exp x_1, Exp x_2)
   : a_Exp(tag_GUARD), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::GENERATOR
//
///////////////////////////////////////////////////////////////////////////////
class Exp_GENERATOR : public a_Exp {
public:
#line 28 "../../../app/willard/willard-ast.ph"
  Ids _1; Exps _2; Exp _3; 
  inline Exp_GENERATOR (Ids x_1, Exps x_2, Exp x_3)
   : a_Exp(tag_GENERATOR), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::LET
//
///////////////////////////////////////////////////////////////////////////////
class Exp_LET : public a_Exp {
public:
#line 29 "../../../app/willard/willard-ast.ph"
  Id _1; Exp _2; Exp _3; 
  inline Exp_LET (Id x_1, Exp x_2, Exp x_3)
   : a_Exp(tag_LET), _1(x_1), _2(x_2), _3(x_3)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Exp
//
///////////////////////////////////////////////////////////////////////////////
inline a_Exp * OP (Id x_1, Exps x_2)
{
  return new Exp_OP (x_1, x_2);
}
inline a_Exp * APP (Id x_1, Exps x_2)
{
  return new Exp_APP (x_1, x_2);
}
inline a_Exp * LIT (Literal x_LIT)
{
  return new Exp_LIT (x_LIT);
}
inline a_Exp * ID (Id x_ID)
{
  return new Exp_ID (x_ID);
}
inline a_Exp * TUPLE (Exps x_TUPLE)
{
  return new Exp_TUPLE (x_TUPLE);
}
inline a_Exp * FORALL (Id x_1, Exp x_2, Exp x_3)
{
  return new Exp_FORALL (x_1, x_2, x_3);
}
inline a_Exp * EXISTS (Id x_1, Exp x_2, Exp x_3)
{
  return new Exp_EXISTS (x_1, x_2, x_3);
}
inline a_Exp * GUARD (Exp x_1, Exp x_2)
{
  return new Exp_GUARD (x_1, x_2);
}
inline a_Exp * GENERATOR (Ids x_1, Exps x_2, Exp x_3)
{
  return new Exp_GENERATOR (x_1, x_2, x_3);
}
inline a_Exp * LET (Id x_1, Exp x_2, Exp x_3)
{
  return new Exp_LET (x_1, x_2, x_3);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Exp
//
///////////////////////////////////////////////////////////////////////////////
inline Exp_OP * _OP(const a_Exp * _x_) { return (Exp_OP *)_x_; }
inline Exp_APP * _APP(const a_Exp * _x_) { return (Exp_APP *)_x_; }
inline Exp_LIT * _LIT(const a_Exp * _x_) { return (Exp_LIT *)_x_; }
inline Exp_ID * _ID(const a_Exp * _x_) { return (Exp_ID *)_x_; }
inline Exp_TUPLE * _TUPLE(const a_Exp * _x_) { return (Exp_TUPLE *)_x_; }
inline Exp_FORALL * _FORALL(const a_Exp * _x_) { return (Exp_FORALL *)_x_; }
inline Exp_EXISTS * _EXISTS(const a_Exp * _x_) { return (Exp_EXISTS *)_x_; }
inline Exp_GUARD * _GUARD(const a_Exp * _x_) { return (Exp_GUARD *)_x_; }
inline Exp_GENERATOR * _GENERATOR(const a_Exp * _x_) { return (Exp_GENERATOR *)_x_; }
inline Exp_LET * _LET(const a_Exp * _x_) { return (Exp_LET *)_x_; }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Int
///////////////////////////////////////////////////////////////////////////////
#line 31 "../../../app/willard/willard-ast.ph"
inline Exp Int(int i)
{ return LIT(INT(i)); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Boolean
///////////////////////////////////////////////////////////////////////////////
#line 32 "../../../app/willard/willard-ast.ph"
inline Exp Boolean(Bool b)
{ return LIT(BOOL(b)); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law And
///////////////////////////////////////////////////////////////////////////////
#line 35 "../../../app/willard/willard-ast.ph"
inline Exp And(Exp a, Exp b)
{ return OP("and",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Or
///////////////////////////////////////////////////////////////////////////////
#line 36 "../../../app/willard/willard-ast.ph"
inline Exp Or(Exp a, Exp b)
{ return OP("or",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Not
///////////////////////////////////////////////////////////////////////////////
#line 37 "../../../app/willard/willard-ast.ph"
inline Exp Not(Exp a)
{ return OP("not",list_1_(a)); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Eq
///////////////////////////////////////////////////////////////////////////////
#line 38 "../../../app/willard/willard-ast.ph"
inline Exp Eq(Exp a, Exp b)
{ return OP("=",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Ne
///////////////////////////////////////////////////////////////////////////////
#line 39 "../../../app/willard/willard-ast.ph"
inline Exp Ne(Exp a, Exp b)
{ return OP("/=",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Gt
///////////////////////////////////////////////////////////////////////////////
#line 40 "../../../app/willard/willard-ast.ph"
inline Exp Gt(Exp a, Exp b)
{ return OP(">",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Ge
///////////////////////////////////////////////////////////////////////////////
#line 41 "../../../app/willard/willard-ast.ph"
inline Exp Ge(Exp a, Exp b)
{ return OP(">=",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Lt
///////////////////////////////////////////////////////////////////////////////
#line 42 "../../../app/willard/willard-ast.ph"
inline Exp Lt(Exp a, Exp b)
{ return OP("<",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Le
///////////////////////////////////////////////////////////////////////////////
#line 43 "../../../app/willard/willard-ast.ph"
inline Exp Le(Exp a, Exp b)
{ return OP("<=",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law In
///////////////////////////////////////////////////////////////////////////////
#line 44 "../../../app/willard/willard-ast.ph"
inline Exp In(Exp a, Exp b)
{ return OP("in",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Union
///////////////////////////////////////////////////////////////////////////////
#line 45 "../../../app/willard/willard-ast.ph"
inline Exp Union(Exp a, Exp b)
{ return OP("union",list_1_(a,list_1_(b))); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Count
///////////////////////////////////////////////////////////////////////////////
#line 46 "../../../app/willard/willard-ast.ph"
inline Exp Count(Exp a)
{ return OP("#",list_1_(a)); }

///////////////////////////////////////////////////////////////////////////////
// Definition of law Nonempty
///////////////////////////////////////////////////////////////////////////////
#line 47 "../../../app/willard/willard-ast.ph"
inline Exp Nonempty(Exp a)
{ return OP("nonempty",list_1_(a)); }

#line 52 "../../../app/willard/willard-ast.ph"
#line 52 "../../../app/willard/willard-ast.ph"


#line 54 "../../../app/willard/willard-ast.ph"
#line 54 "../../../app/willard/willard-ast.ph"


#line 56 "../../../app/willard/willard-ast.ph"
#line 56 "../../../app/willard/willard-ast.ph"

#line 57 "../../../app/willard/willard-ast.ph"
#line 57 "../../../app/willard/willard-ast.ph"

#line 58 "../../../app/willard/willard-ast.ph"
#line 58 "../../../app/willard/willard-ast.ph"


// Avoid portability problems for now.

// refine Exp :: collectable;
// refine Literal :: collectable;
// refine List<T> :: collectable;

//
//  These are the pretty printing methods
//
extern PrettyOStream& operator << (PrettyOStream&, Exp);
extern PrettyOStream& operator << (PrettyOStream&, Ids);
extern PrettyOStream& operator << (PrettyOStream&, Exps);
extern PrettyOStream& operator << (PrettyOStream&, Literal);

#endif
#line 75 "../../../app/willard/willard-ast.ph"
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
