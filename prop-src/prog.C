///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.3),
//  last updated on Mar 27, 1997.
//  The original source file is "prog.pC".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_PRINTER_USED
#define PROP_QUARK_USED
#include <propdefs.h>
#line 1 "prog.pC"
/////////////////////////////////////////////////////////////////////////////
//  This test implements a rewrite based simplifier for the abstract
//  syntax of a toy imperative language.
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
//  The following recursive type equations define the abstract syntax
//  of our small language.
//  ( Note: we define our own boolean type because not all C++ compilers
//    have bool built-in yet. )
/////////////////////////////////////////////////////////////////////////////
#line 13 "prog.pC"
#line 50 "prog.pC"
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

#  define nil_1_ 0

enum BOOL {
   False = 0, True = 1
};



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

enum BinOp {
   add = 0, sub = 1, mul = 2,
   divide = 3, mod = 4, logical_and = 5,
   logical_or = 6, eq = 7, ge = 8,
   le = 9, lt = 10, gt = 11,
   ne = 12
};



enum UnaryOp {
   uminus = 0, logical_not = 1
};



///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Stmt
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Stmt_defined
#define datatype_Stmt_defined
   class a_Stmt;
   typedef a_Stmt * Stmt;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Type
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Type_defined
#define datatype_Type_defined
   class a_Type;
   typedef a_Type * Type;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Decl
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Decl_defined
#define datatype_Decl_defined
   class a_Decl;
   typedef a_Decl * Decl;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for LabeledType
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_LabeledType_defined
#define datatype_LabeledType_defined
   class a_LabeledType;
   typedef a_LabeledType * LabeledType;
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type Id
///////////////////////////////////////////////////////////////////////////////
#line 49 "prog.pC"
typedef char const * Id;

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor List<T>::#[...]
//
///////////////////////////////////////////////////////////////////////////////
template <class T> class a_List : public TermObj {
public:
#line 13 "prog.pC"
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
//  Pretty printing methods for List<T>
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
template <class T> extern ostream& operator<<(ostream&, List(T));
template <class T> extern PrettyOStream& operator<<(PrettyOStream&, List(T));
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



///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for BOOL
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, BOOL);
extern PrettyOStream& operator<<(PrettyOStream&, BOOL);
///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
class a_Exp : public TermObj {
public:
   enum Tag_Exp {
      tag_integer = 0, tag_real = 1, tag_string = 2,
      tag_boolean = 3, tag_binop = 4, tag_unaryop = 5,
      tag_var = 6
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
//  Pretty printing methods for Exp
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, Exp);
extern PrettyOStream& operator<<(PrettyOStream&, Exp);
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::integer
//
///////////////////////////////////////////////////////////////////////////////
class Exp_integer : public a_Exp {
public:
#line 18 "prog.pC"
   int integer;
   inline Exp_integer (int x_integer)
    : a_Exp(tag_integer), integer(x_integer)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::real
//
///////////////////////////////////////////////////////////////////////////////
class Exp_real : public a_Exp {
public:
#line 19 "prog.pC"
   double real;
   inline Exp_real (double x_real)
    : a_Exp(tag_real), real(x_real)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::string
//
///////////////////////////////////////////////////////////////////////////////
class Exp_string : public a_Exp {
public:
#line 20 "prog.pC"
   char * string;
   inline Exp_string (char * x_string)
    : a_Exp(tag_string), string(x_string)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::boolean
//
///////////////////////////////////////////////////////////////////////////////
class Exp_boolean : public a_Exp {
public:
#line 21 "prog.pC"
   BOOL boolean;
   inline Exp_boolean (BOOL x_boolean)
    : a_Exp(tag_boolean), boolean(x_boolean)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::binop
//
///////////////////////////////////////////////////////////////////////////////
class Exp_binop : public a_Exp {
public:
#line 22 "prog.pC"
   BinOp _1; Exp _2; Exp _3;
   inline Exp_binop (BinOp x_1, Exp x_2, Exp x_3)
    : a_Exp(tag_binop), _1(x_1), _2(x_2), _3(x_3)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::unaryop
//
///////////////////////////////////////////////////////////////////////////////
class Exp_unaryop : public a_Exp {
public:
#line 23 "prog.pC"
   UnaryOp _1; Exp _2;
   inline Exp_unaryop (UnaryOp x_1, Exp x_2)
    : a_Exp(tag_unaryop), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Exp::var
//
///////////////////////////////////////////////////////////////////////////////
class Exp_var : public a_Exp {
public:
#line 24 "prog.pC"
   Id var;
   inline Exp_var (Id x_var)
    : a_Exp(tag_var), var(x_var)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Exp
//
///////////////////////////////////////////////////////////////////////////////
inline a_Exp * integer (int x_integer)
{
   return new Exp_integer (x_integer);
}
inline a_Exp * real (double x_real)
{
   return new Exp_real (x_real);
}
inline a_Exp * string (char * x_string)
{
   return new Exp_string (x_string);
}
inline a_Exp * boolean (BOOL x_boolean)
{
   return new Exp_boolean (x_boolean);
}
inline a_Exp * binop (BinOp x_1, Exp x_2, Exp x_3)
{
   return new Exp_binop (x_1, x_2, x_3);
}
inline a_Exp * unaryop (UnaryOp x_1, Exp x_2)
{
   return new Exp_unaryop (x_1, x_2);
}
inline a_Exp * var (Id x_var)
{
   return new Exp_var (x_var);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Exp
//
///////////////////////////////////////////////////////////////////////////////
inline Exp_integer * _integer(const a_Exp * _x_) { return (Exp_integer *)_x_; }
inline Exp_real * _real(const a_Exp * _x_) { return (Exp_real *)_x_; }
inline Exp_string * _string(const a_Exp * _x_) { return (Exp_string *)_x_; }
inline Exp_boolean * _boolean(const a_Exp * _x_) { return (Exp_boolean *)_x_; }
inline Exp_binop * _binop(const a_Exp * _x_) { return (Exp_binop *)_x_; }
inline Exp_unaryop * _unaryop(const a_Exp * _x_) { return (Exp_unaryop *)_x_; }
inline Exp_var * _var(const a_Exp * _x_) { return (Exp_var *)_x_; }


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for BinOp
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, BinOp);
extern PrettyOStream& operator<<(PrettyOStream&, BinOp);
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for UnaryOp
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, UnaryOp);
extern PrettyOStream& operator<<(PrettyOStream&, UnaryOp);
///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Stmt
//
///////////////////////////////////////////////////////////////////////////////
class a_Stmt : public TermObj {
public:
   enum Tag_Stmt {
      tag_assign_stmt = 0, tag_while_stmt = 1, tag_if_stmt = 2,
      tag_print_stmt = 3, tag_block_stmt = 4
   };

public:
   const Tag_Stmt tag__; // variant tag
protected:
   inline a_Stmt(Tag_Stmt t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Stmt *) { return 1; }
inline int untag(const a_Stmt * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for Stmt
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, Stmt);
extern PrettyOStream& operator<<(PrettyOStream&, Stmt);
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::assign_stmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_assign_stmt : public a_Stmt {
public:
#line 32 "prog.pC"
   Id _1; Exp _2;
   inline Stmt_assign_stmt (Id x_1, Exp x_2)
    : a_Stmt(tag_assign_stmt), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::while_stmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_while_stmt : public a_Stmt {
public:
#line 33 "prog.pC"
   Exp _1; Stmt _2;
   inline Stmt_while_stmt (Exp x_1, Stmt x_2)
    : a_Stmt(tag_while_stmt), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::if_stmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_if_stmt : public a_Stmt {
public:
#line 34 "prog.pC"
   Exp _1; Stmt _2; Stmt _3;
   inline Stmt_if_stmt (Exp x_1, Stmt x_2, Stmt x_3)
    : a_Stmt(tag_if_stmt), _1(x_1), _2(x_2), _3(x_3)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::print_stmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_print_stmt : public a_Stmt {
public:
#line 35 "prog.pC"
   Exp print_stmt;
   inline Stmt_print_stmt (Exp x_print_stmt)
    : a_Stmt(tag_print_stmt), print_stmt(x_print_stmt)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Stmt::block_stmt
//
///////////////////////////////////////////////////////////////////////////////
class Stmt_block_stmt : public a_Stmt {
public:
#line 36 "prog.pC"
   a_List<Decl> *  _1; a_List<Stmt> *  _2;
   inline Stmt_block_stmt (a_List<Decl> *  x_1, a_List<Stmt> *  x_2)
    : a_Stmt(tag_block_stmt), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Stmt
//
///////////////////////////////////////////////////////////////////////////////
inline a_Stmt * assign_stmt (Id x_1, Exp x_2)
{
   return new Stmt_assign_stmt (x_1, x_2);
}
inline a_Stmt * while_stmt (Exp x_1, Stmt x_2)
{
   return new Stmt_while_stmt (x_1, x_2);
}
inline a_Stmt * if_stmt (Exp x_1, Stmt x_2, Stmt x_3)
{
   return new Stmt_if_stmt (x_1, x_2, x_3);
}
inline a_Stmt * print_stmt (Exp x_print_stmt)
{
   return new Stmt_print_stmt (x_print_stmt);
}
inline a_Stmt * block_stmt (a_List<Decl> *  x_1, a_List<Stmt> *  x_2)
{
   return new Stmt_block_stmt (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Stmt
//
///////////////////////////////////////////////////////////////////////////////
inline Stmt_assign_stmt * _assign_stmt(const a_Stmt * _x_) { return (Stmt_assign_stmt *)_x_; }
inline Stmt_while_stmt * _while_stmt(const a_Stmt * _x_) { return (Stmt_while_stmt *)_x_; }
inline Stmt_if_stmt * _if_stmt(const a_Stmt * _x_) { return (Stmt_if_stmt *)_x_; }
inline Stmt_print_stmt * _print_stmt(const a_Stmt * _x_) { return (Stmt_print_stmt *)_x_; }
inline Stmt_block_stmt * _block_stmt(const a_Stmt * _x_) { return (Stmt_block_stmt *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Type
//
///////////////////////////////////////////////////////////////////////////////
class a_Type : public TermObj {
public:
   enum Tag_Type {
      tag_primitive_type = 0, tag_pointer_type = 1, tag_array_type = 2,
      tag_function_type = 3, tag_tuple_type = 4, tag_record_type = 5
   };

public:
   const Tag_Type tag__; // variant tag
protected:
   inline a_Type(Tag_Type t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Type *) { return 1; }
inline int untag(const a_Type * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for Type
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, Type);
extern PrettyOStream& operator<<(PrettyOStream&, Type);
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Type::primitive_type
//
///////////////////////////////////////////////////////////////////////////////
class Type_primitive_type : public a_Type {
public:
#line 38 "prog.pC"
   Id primitive_type;
   inline Type_primitive_type (Id x_primitive_type)
    : a_Type(tag_primitive_type), primitive_type(x_primitive_type)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Type::pointer_type
//
///////////////////////////////////////////////////////////////////////////////
class Type_pointer_type : public a_Type {
public:
#line 39 "prog.pC"
   Type pointer_type;
   inline Type_pointer_type (Type x_pointer_type)
    : a_Type(tag_pointer_type), pointer_type(x_pointer_type)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Type::array_type
//
///////////////////////////////////////////////////////////////////////////////
class Type_array_type : public a_Type {
public:
#line 40 "prog.pC"
   Type element; Exp bound;
   inline Type_array_type (Type x_element, Exp x_bound)
    : a_Type(tag_array_type), element(x_element), bound(x_bound)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Type::function_type
//
///////////////////////////////////////////////////////////////////////////////
class Type_function_type : public a_Type {
public:
#line 41 "prog.pC"
   Type arg; Type ret;
   inline Type_function_type (Type x_arg, Type x_ret)
    : a_Type(tag_function_type), arg(x_arg), ret(x_ret)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Type::tuple_type
//
///////////////////////////////////////////////////////////////////////////////
class Type_tuple_type : public a_Type {
public:
#line 42 "prog.pC"
   a_List<Type> *  tuple_type;
   inline Type_tuple_type (a_List<Type> *  x_tuple_type)
    : a_Type(tag_tuple_type), tuple_type(x_tuple_type)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Type::record_type
//
///////////////////////////////////////////////////////////////////////////////
class Type_record_type : public a_Type {
public:
#line 43 "prog.pC"
   a_List<LabeledType> *  record_type;
   inline Type_record_type (a_List<LabeledType> *  x_record_type)
    : a_Type(tag_record_type), record_type(x_record_type)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Type
//
///////////////////////////////////////////////////////////////////////////////
inline a_Type * primitive_type (Id x_primitive_type)
{
   return new Type_primitive_type (x_primitive_type);
}
inline a_Type * pointer_type (Type x_pointer_type)
{
   return new Type_pointer_type (x_pointer_type);
}
inline a_Type * array_type (Type x_element, Exp x_bound)
{
   return new Type_array_type (x_element, x_bound);
}
inline a_Type * function_type (Type x_arg, Type x_ret)
{
   return new Type_function_type (x_arg, x_ret);
}
inline a_Type * tuple_type (a_List<Type> *  x_tuple_type)
{
   return new Type_tuple_type (x_tuple_type);
}
inline a_Type * record_type (a_List<LabeledType> *  x_record_type)
{
   return new Type_record_type (x_record_type);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Type
//
///////////////////////////////////////////////////////////////////////////////
inline Type_primitive_type * _primitive_type(const a_Type * _x_) { return (Type_primitive_type *)_x_; }
inline Type_pointer_type * _pointer_type(const a_Type * _x_) { return (Type_pointer_type *)_x_; }
inline Type_array_type * _array_type(const a_Type * _x_) { return (Type_array_type *)_x_; }
inline Type_function_type * _function_type(const a_Type * _x_) { return (Type_function_type *)_x_; }
inline Type_tuple_type * _tuple_type(const a_Type * _x_) { return (Type_tuple_type *)_x_; }
inline Type_record_type * _record_type(const a_Type * _x_) { return (Type_record_type *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Decl::decl
//
///////////////////////////////////////////////////////////////////////////////
class a_Decl : public TermObj {
public:
#line 45 "prog.pC"
   Id name; Type typ;
   inline a_Decl (Id x_name, Type x_typ)
    : name(x_name), typ(x_typ)
   {
   }
};
inline int boxed(const a_Decl *) { return 1; }
inline int untag(const a_Decl *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for Decl
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, Decl);
extern PrettyOStream& operator<<(PrettyOStream&, Decl);
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Decl
//
///////////////////////////////////////////////////////////////////////////////
inline a_Decl * decl (Id x_name, Type x_typ)
{
   return new a_Decl (x_name, x_typ);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Decl
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor LabeledType::labeled_type
//
///////////////////////////////////////////////////////////////////////////////
class a_LabeledType : public TermObj {
public:
#line 47 "prog.pC"
   Id _1; Type _2;
   inline a_LabeledType (Id x_1, Type x_2)
    : _1(x_1), _2(x_2)
   {
   }
};
inline int boxed(const a_LabeledType *) { return 1; }
inline int untag(const a_LabeledType *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for LabeledType
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, LabeledType);
extern PrettyOStream& operator<<(PrettyOStream&, LabeledType);
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for LabeledType
//
///////////////////////////////////////////////////////////////////////////////
inline a_LabeledType * labeled_type (Id x_1, Type x_2)
{
   return new a_LabeledType (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for LabeledType
//
///////////////////////////////////////////////////////////////////////////////


#line 50 "prog.pC"
#line 50 "prog.pC"


/////////////////////////////////////////////////////////////////////////////
//  Refine the implementation of the datatypes.
//  The qualifiers may be also declared in the datatype definition.
//  We qualify the datatypes here so that they won't clutter up
//  the equations above.
//
//  All types are declared to be printable by
//  the printer method and rewritable.
/////////////////////////////////////////////////////////////////////////////
#line 61 "prog.pC"
#line 111 "prog.pC"


/////////////////////////////////////////////////////////////////////////////
//  Generate the interfaces to instantiated polymorphic datatypes.
//  These are not strictly necessary since the instantiation is in the
//  same file below.  However, in general the 'instantiate extern' declaration
//  must be placed in the .h files for each instance of a polymorphic
//  datatype.
/////////////////////////////////////////////////////////////////////////////
#line 121 "prog.pC"
#line 121 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Type>
//
///////////////////////////////////////////////////////////////////////////////
#line 121 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Type>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Type> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<Type> *   obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
#line 121 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Stmt> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<Stmt> *   obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<LabeledType>
//
///////////////////////////////////////////////////////////////////////////////
#line 121 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<LabeledType>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<LabeledType> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<LabeledType> *   obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
#line 121 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Decl> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<Decl> *   obj__);

#line 122 "prog.pC"
#line 122 "prog.pC"


/////////////////////////////////////////////////////////////////////////////
//  Now instantiate all the datatypes.
/////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Exp
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Exp  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, Exp  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype BOOL
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for BOOL
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, BOOL  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, BOOL  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype BinOp
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for BinOp
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, BinOp  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, BinOp  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype UnaryOp
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for UnaryOp
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, UnaryOp  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, UnaryOp  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Stmt
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Stmt
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Stmt  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, Stmt  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Type
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Type
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Type  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, Type  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Decl
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Decl
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Decl  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, Decl  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype LabeledType
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for LabeledType
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, LabeledType  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, LabeledType  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Type>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Type>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Type> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<Type> *   obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Stmt> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<Stmt> *   obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<LabeledType>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<LabeledType>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<LabeledType> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<LabeledType> *   obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Decl> *   obj__);
PrettyOStream& operator << (PrettyOStream& strm__, a_List<Decl> *   obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Exp
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Exp  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, Exp  obj__)
{
   switch (untag(obj__))
   {
      case 0:
         strm__ << _integer(obj__)->integer; // int
         break;
      case 1:
         strm__ << _real(obj__)->real; // double
         break;
      case 2:
         strm__ << "\"";
         strm__ << _string(obj__)->string; // char *
         strm__ << "\"";
         break;
      case 3:
         strm__ << _boolean(obj__)->boolean; // BOOL
         break;
      case 4:
         strm__ << '(';
         strm__ << _binop(obj__)->_2;
         strm__ << _binop(obj__)->_1;
         strm__ << _binop(obj__)->_3;
         strm__ << ')';
         break;
      case 5:
         strm__ << '(';
         strm__ << _unaryop(obj__)->_1; // UnaryOp
         strm__ << _unaryop(obj__)->_2; // Exp
         strm__ << ')';
         break;
      case 6:
         strm__ << _var(obj__)->var; // char const *
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype BOOL
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for BOOL
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, BOOL  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, BOOL  obj__)
{
   switch (obj__)
   {
      case False:
         strm__ << "false";
         break;
      case True:
         strm__ << "true";
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype BinOp
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for BinOp
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, BinOp  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, BinOp  obj__)
{
   switch (obj__)
   {
      case add:
         strm__ << '+';
         break;
      case sub:
         strm__ << '-';
         break;
      case mul:
         strm__ << '*';
         break;
      case divide:
         strm__ << '/';
         break;
      case mod:
         strm__ << "mod";
         break;
      case logical_and:
         strm__ << "and";
         break;
      case logical_or:
         strm__ << "or";
         break;
      case eq:
         strm__ << '=';
         break;
      case ge:
         strm__ << ">=";
         break;
      case le:
         strm__ << "<=";
         break;
      case lt:
         strm__ << '<';
         break;
      case gt:
         strm__ << '>';
         break;
      case ne:
         strm__ << "<>";
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype UnaryOp
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for UnaryOp
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, UnaryOp  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, UnaryOp  obj__)
{
   switch (obj__)
   {
      case uminus:
         strm__ << '-';
         break;
      case logical_not:
         strm__ << "not";
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Stmt
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Stmt
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Stmt  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, Stmt  obj__)
{
   switch (untag(obj__))
   {
      case 0:
         strm__ << _assign_stmt(obj__)->_1; // Id
         strm__ << ":=";
         strm__ << _assign_stmt(obj__)->_2; // Exp
         strm__ << ';';
         break;
      case 1:
         strm__ << "while";
         strm__ << _while_stmt(obj__)->_1; // Exp
         strm__ << "do";
         strm__.indent().newline().tab();
         strm__ << _while_stmt(obj__)->_2; // Stmt
         strm__.unindent().newline().tab();
         strm__ << "end while;";
         break;
      case 2:
         strm__ << "if";
         strm__ << _if_stmt(obj__)->_1; // Exp
         strm__ << "then";
         strm__.indent().newline().tab();
         strm__ << _if_stmt(obj__)->_2; // Stmt
         strm__.unindent().newline().tab();
         strm__ << "else";
         strm__.indent().newline().tab();
         strm__ << _if_stmt(obj__)->_3; // Stmt
         strm__.unindent().newline().tab();
         strm__ << "endif;";
         break;
      case 3:
         strm__ << "print";
         strm__ << _print_stmt(obj__)->print_stmt; // Exp
         strm__ << ';';
         break;
      case 4:
         strm__ << "begin";
         strm__.indent().newline().tab();
         strm__ << _block_stmt(obj__)->_1; // List<Decl>
         strm__.newline().tab();
         strm__ << _block_stmt(obj__)->_2; // List<Stmt>
         strm__.unindent().newline().tab();
         strm__ << "end";
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Type
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Type
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Type  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, Type  obj__)
{
   switch (untag(obj__))
   {
      case 0:
         strm__ << _primitive_type(obj__)->primitive_type; // char const *
         break;
      case 1:
         strm__ << _pointer_type(obj__)->pointer_type; // Type
         strm__ << '^';
         break;
      case 2:
         strm__ << "array";
         strm__ << _array_type(obj__)->bound;
         strm__ << "of";
         strm__ << _array_type(obj__)->element;
         break;
      case 3:
         strm__ << _function_type(obj__)->arg;
         strm__ << "->";
         strm__ << _function_type(obj__)->ret;
         break;
      case 4:
         strm__ << "tuple_type";
         strm__ << '(';
         strm__ << _tuple_type(obj__)->tuple_type; // List<Type>
         strm__ << ')';
         break;
      case 5:
         strm__ << "record_type";
         strm__ << '(';
         strm__ << _record_type(obj__)->record_type; // List<LabeledType>
         strm__ << ')';
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Decl
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for Decl
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, Decl  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, Decl  obj__)
{
   strm__ << "var";
   strm__ << obj__->name;
   strm__ << ':';
   strm__ << obj__->typ;
   strm__ << ';';
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype LabeledType
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for LabeledType
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, LabeledType  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, LabeledType  obj__)
{
   strm__ << obj__->_1; // Id
   strm__ << ':';
   strm__ << obj__->_2; // Type
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Type>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Type>;
template a_List<Type> * list_1_(Decl x_1, a_List<Decl> *  x_2);
template a_List<Type> * list_1_(Decl x_list_1_);
template int boxed(const a_List<Type> *);
template int untag(const a_List<Type> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Type>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Type> *   obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, a_List<Type> *   obj__)
{
   switch (untag(obj__))
   {
      case ((int)nil_1_):
         strm__ << "";
         break;
      case 1:
         strm__ << obj__->_1; // Type
         strm__.newline().tab();
         strm__ << obj__->_2; // List<Type>
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Stmt>;
template a_List<Stmt> * list_1_(Type x_1, a_List<Type> *  x_2);
template a_List<Stmt> * list_1_(Type x_list_1_);
template int boxed(const a_List<Stmt> *);
template int untag(const a_List<Stmt> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Stmt>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Stmt> *   obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, a_List<Stmt> *   obj__)
{
   switch (untag(obj__))
   {
      case ((int)nil_1_):
         strm__ << "";
         break;
      case 1:
         strm__ << obj__->_1; // Stmt
         strm__.newline().tab();
         strm__ << obj__->_2; // List<Stmt>
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<LabeledType>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<LabeledType>;
template a_List<LabeledType> * list_1_(Stmt x_1, a_List<Stmt> *  x_2);
template a_List<LabeledType> * list_1_(Stmt x_list_1_);
template int boxed(const a_List<LabeledType> *);
template int untag(const a_List<LabeledType> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<LabeledType>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<LabeledType> *   obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, a_List<LabeledType> *   obj__)
{
   switch (untag(obj__))
   {
      case ((int)nil_1_):
         strm__ << "";
         break;
      case 1:
         strm__ << obj__->_1; // LabeledType
         strm__.newline().tab();
         strm__ << obj__->_2; // List<LabeledType>
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
#line 127 "prog.pC"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Decl>;
template a_List<Decl> * list_1_(LabeledType x_1, a_List<LabeledType> *  x_2);
template a_List<Decl> * list_1_(LabeledType x_list_1_);
template int boxed(const a_List<Decl> *);
template int untag(const a_List<Decl> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for List<Decl>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, a_List<Decl> *   obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, a_List<Decl> *   obj__)
{
   switch (untag(obj__))
   {
      case ((int)nil_1_):
         strm__ << "";
         break;
      case 1:
         strm__ << obj__->_1; // Decl
         strm__.newline().tab();
         strm__ << obj__->_2; // List<Decl>
         break;
   }
   return strm__;
}



#line 128 "prog.pC"
#line 128 "prog.pC"


/////////////////////////////////////////////////////////////////////////////
//  Defines the interface of a rewrite class Simplify.
//  All types that are referenced (directly or indirectly) should be
//  declared in the interface.
/////////////////////////////////////////////////////////////////////////////
#line 135 "prog.pC"
#line 144 "prog.pC"
class Simplify : public BURS {
private:
   Simplify(const Simplify&);
