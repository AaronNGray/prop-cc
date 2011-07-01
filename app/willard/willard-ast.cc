///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "willard-ast.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "willard-ast.pcc"
#include "willard-ast.h"
#include <AD/pretty/postream.h>

#line 4 "willard-ast.pcc"
#line 4 "willard-ast.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Exp>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
a_List<Exp>::a_List (Exp x_1, a_List<Exp> *  x_2);
a_List<Exp>::a_List (Exp x_1);
extern a_List<Exp> * list_1_ (Exp x_1, a_List<Exp> *  x_2);
extern a_List<Exp> * list_1_ (Exp x_1);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Id>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
a_List<Id>::a_List (Id x_1, a_List<Id> *  x_2);
a_List<Id>::a_List (Id x_1);
extern a_List<Id> * list_1_ (Id x_1, a_List<Id> *  x_2);
extern a_List<Id> * list_1_ (Id x_1);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Tuple2<Ids, Exps> >
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
a_List<Tuple2<Ids, Exps> >::a_List (Tuple2<Ids, Exps>  x_1, a_List<Tuple2<Ids, Exps> > *  x_2);
a_List<Tuple2<Ids, Exps> >::a_List (Tuple2<Ids, Exps>  x_1);
extern a_List<Tuple2<Ids, Exps> > * list_1_ (Tuple2<Ids, Exps>  x_1, a_List<Tuple2<Ids, Exps> > *  x_2);
extern a_List<Tuple2<Ids, Exps> > * list_1_ (Tuple2<Ids, Exps>  x_1);

///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
Exp_OP::Exp_OP (Id x_1, Exps x_2)
 : a_Exp(tag_OP), _1(x_1), _2(x_2)
{
}
a_Exp * OP (Id x_1, Exps x_2)
{
   return new Exp_OP (x_1, x_2);
}
Exp_APP::Exp_APP (Id x_1, Exps x_2)
 : a_Exp(tag_APP), _1(x_1), _2(x_2)
{
}
a_Exp * APP (Id x_1, Exps x_2)
{
   return new Exp_APP (x_1, x_2);
}
Exp_LIT::Exp_LIT (Literal x_LIT)
 : a_Exp(tag_LIT), LIT(x_LIT)
{
}
a_Exp * LIT (Literal x_LIT)
{
   return new Exp_LIT (x_LIT);
}
Exp_ID::Exp_ID (Id x_ID)
 : a_Exp(tag_ID), ID(x_ID)
{
}
a_Exp * ID (Id x_ID)
{
   return new Exp_ID (x_ID);
}
Exp_TUPLE::Exp_TUPLE (Exps x_TUPLE)
 : a_Exp(tag_TUPLE), TUPLE(x_TUPLE)
{
}
a_Exp * TUPLE (Exps x_TUPLE)
{
   return new Exp_TUPLE (x_TUPLE);
}
Exp_FORALL::Exp_FORALL (Id x_1, Exp x_2, Exp x_3)
 : a_Exp(tag_FORALL), _1(x_1), _2(x_2), _3(x_3)
{
}
a_Exp * FORALL (Id x_1, Exp x_2, Exp x_3)
{
   return new Exp_FORALL (x_1, x_2, x_3);
}
Exp_EXISTS::Exp_EXISTS (Id x_1, Exp x_2, Exp x_3)
 : a_Exp(tag_EXISTS), _1(x_1), _2(x_2), _3(x_3)
{
}
a_Exp * EXISTS (Id x_1, Exp x_2, Exp x_3)
{
   return new Exp_EXISTS (x_1, x_2, x_3);
}
Exp_GUARD::Exp_GUARD (Exp x_1, Exp x_2)
 : a_Exp(tag_GUARD), _1(x_1), _2(x_2)
{
}
a_Exp * GUARD (Exp x_1, Exp x_2)
{
   return new Exp_GUARD (x_1, x_2);
}
Exp_GENERATOR::Exp_GENERATOR (Ids x_1, Exps x_2, Exp x_3)
 : a_Exp(tag_GENERATOR), _1(x_1), _2(x_2), _3(x_3)
{
}
a_Exp * GENERATOR (Ids x_1, Exps x_2, Exp x_3)
{
   return new Exp_GENERATOR (x_1, x_2, x_3);
}
Exp_LET::Exp_LET (Id x_1, Exp x_2, Exp x_3)
 : a_Exp(tag_LET), _1(x_1), _2(x_2), _3(x_3)
{
}
a_Exp * LET (Id x_1, Exp x_2, Exp x_3)
{
   return new Exp_LET (x_1, x_2, x_3);
}


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Exp>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Exp>;
template int boxed(const a_List<Exp> *);
template int untag(const a_List<Exp> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
a_List<Exp>::a_List (Exp x_1, a_List<Exp> *  x_2)
 : _1(x_1), _2(x_2)
{
}
a_List<Exp>::a_List (Exp x_1)
 : _1(x_1), _2((a_List<Exp> *)0)
{
}
a_List<Exp> * list_1_ (Exp x_1, a_List<Exp> *  x_2)
{
   return new a_List<Exp> (x_1, x_2);
}
a_List<Exp> * list_1_ (Exp x_1)
{
   return new a_List<Exp> (x_1);
}


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Id>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Id>;
template int boxed(const a_List<Id> *);
template int untag(const a_List<Id> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
a_List<Id>::a_List (Id x_1, a_List<Id> *  x_2)
 : _1(x_1), _2(x_2)
{
}
a_List<Id>::a_List (Id x_1)
 : _1(x_1), _2((a_List<Id> *)0)
{
}
a_List<Id> * list_1_ (Id x_1, a_List<Id> *  x_2)
{
   return new a_List<Id> (x_1, x_2);
}
a_List<Id> * list_1_ (Id x_1)
{
   return new a_List<Id> (x_1);
}


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Tuple2<Ids, Exps> >
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Tuple2<Ids, Exps> >;
template int boxed(const a_List<Tuple2<Ids, Exps> > *);
template int untag(const a_List<Tuple2<Ids, Exps> > *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */
a_List<Tuple2<Ids, Exps> >::a_List (Tuple2<Ids, Exps>  x_1, a_List<Tuple2<Ids, Exps> > *  x_2)
 : _1(x_1), _2(x_2)
{
}
a_List<Tuple2<Ids, Exps> >::a_List (Tuple2<Ids, Exps>  x_1)
 : _1(x_1), _2((a_List<Tuple2<Ids, Exps> > *)0)
{
}
a_List<Tuple2<Ids, Exps> > * list_1_ (Tuple2<Ids, Exps>  x_1, a_List<Tuple2<Ids, Exps> > *  x_2)
{
   return new a_List<Tuple2<Ids, Exps> > (x_1, x_2);
}
a_List<Tuple2<Ids, Exps> > * list_1_ (Tuple2<Ids, Exps>  x_1)
{
   return new a_List<Tuple2<Ids, Exps> > (x_1);
}


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "willard-ast.pcc"
Literal_INT::Literal_INT (int x_INT)
 : a_Literal(tag_INT), INT(x_INT)
{
}
a_Literal * INT (int x_INT)
{
   return new Literal_INT (x_INT);
}
Literal_STRING::Literal_STRING (char const * x_STRING)
 : a_Literal(tag_STRING), STRING(x_STRING)
{
}
a_Literal * STRING (char const * x_STRING)
{
   return new Literal_STRING (x_STRING);
}
Literal_BOOL::Literal_BOOL (Bool x_BOOL)
 : a_Literal(tag_BOOL), BOOL(x_BOOL)
{
}
a_Literal * BOOL (Bool x_BOOL)
{
   return new Literal_BOOL (x_BOOL);
}


#line 4 "willard-ast.pcc"
#line 4 "willard-ast.pcc"
 
;

int ConsCounter::count = 0;

///////////////////////////////////////////////////////////////////////////////
//
//  Auxiliary method to pretty print set comprehensions.
//
///////////////////////////////////////////////////////////////////////////////
static PrettyOStream& print_set_comp(PrettyOStream& S, Exp exp)
{  Exp root = exp;
   Bool has_guard = false;
   Exp guard;

   // print the root expression first
   
#line 20 "willard-ast.pcc"
#line 22 "willard-ast.pcc"
{
   for (;;) {
      switch (root->tag__) {
         case a_Exp::tag_GUARD: {
#line 22 "willard-ast.pcc"
           guard = _GUARD(root)->_1; has_guard = true; root = _GUARD(root)->_2; 
#line 22 "willard-ast.pcc"
            } break;
         case a_Exp::tag_GENERATOR: {
#line 21 "willard-ast.pcc"
           root = _GENERATOR(root)->_3; 
#line 21 "willard-ast.pcc"
            } break;
         default: { goto L1; } break;
      }
   }
   L1:;
}
#line 23 "willard-ast.pcc"
#line 23 "willard-ast.pcc"

   S << root << ':';
   char comma = '\0';

   // print the generators
   
#line 28 "willard-ast.pcc"
#line 37 "willard-ast.pcc"
{
   for (;;) {
      switch (exp->tag__) {
         case a_Exp::tag_GENERATOR: {
            if (_GENERATOR(exp)->_1) {
               if (_GENERATOR(exp)->_1->_2) {
                  L3:; 
#line 33 "willard-ast.pcc"
                 if (comma) S << comma << space;
                  			        S << '[' << _GENERATOR(exp)->_1 << ']' << "in" << space
                  				  << '[' << _GENERATOR(exp)->_2 << ']'; 
                                                  comma = ','; exp = _GENERATOR(exp)->_3; 
                  			      
#line 37 "willard-ast.pcc"
               } else {
                  if (_GENERATOR(exp)->_2) {
                     if (_GENERATOR(exp)->_2->_2) { goto L3; } else {
#line 29 "willard-ast.pcc"
                       if (comma) S << comma << space;
                        			        S << _GENERATOR(exp)->_1->_1 << "in" << _GENERATOR(exp)->_2->_1; 
                                                        comma = ','; exp = _GENERATOR(exp)->_3; 
                        			      
#line 32 "willard-ast.pcc"
                     }
                  } else { goto L3; }
               }
            } else { goto L3; }
            } break;
         default: { goto L2; } break;
      }
   }
   L2:;
}
#line 38 "willard-ast.pcc"
#line 38 "willard-ast.pcc"


   // print guard
   if (has_guard) S << space << '|' << space << guard; 
   return S;
}


///////////////////////////////////////////////////////////////////////////////
// 
//  Auxiliary method to pretty print let expressions.  
// 
///////////////////////////////////////////////////////////////////////////////
static PrettyOStream& print_let(PrettyOStream& S, Exp e)
{  S << tab << "let" << newline << indent;
   
#line 53 "willard-ast.pcc"
#line 55 "willard-ast.pcc"
{
   for (;;) {
      switch (e->tag__) {
         case a_Exp::tag_LET: {
#line 55 "willard-ast.pcc"
           S << tab << _LET(e)->_1 << '=' << _LET(e)->_2 << newline; e = _LET(e)->_3; 
#line 55 "willard-ast.pcc"
            } break;
         default: { goto L4; } break;
      }
   }
   L4:;
}
#line 56 "willard-ast.pcc"
#line 56 "willard-ast.pcc"

   return S << unindent << tab << "in" << newline << indent
            << tab << e << newline << unindent
            << tab << "end" << newline;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Main method to pretty print an expression.
//
///////////////////////////////////////////////////////////////////////////////
PrettyOStream& operator << (PrettyOStream& S, Exp e)
{  
#line 68 "willard-ast.pcc"
#line 82 "willard-ast.pcc"
{
   switch (e->tag__) {
      case a_Exp::tag_OP: {
         if (_OP(e)->_2) {
            if (_OP(e)->_2->_2) {
               if (_OP(e)->_2->_2->_2) {
                  L5:; 
#line 71 "willard-ast.pcc"
                 return S << _OP(e)->_1 << '(' << _OP(e)->_2 << ')'; 
#line 71 "willard-ast.pcc"
               } else {
#line 69 "willard-ast.pcc"
                 return S << '(' << _OP(e)->_2->_1 << _OP(e)->_1 << _OP(e)->_2->_2->_1 << ')'; 
#line 69 "willard-ast.pcc"
               }
            } else {
#line 70 "willard-ast.pcc"
              return S << '(' << _OP(e)->_1 << _OP(e)->_2->_1 << ')'; 
#line 70 "willard-ast.pcc"
            }
         } else { goto L5; }
         } break;
      case a_Exp::tag_APP: {
#line 72 "willard-ast.pcc"
        return S << _APP(e)->_1 << '(' << _APP(e)->_2 << ')'; 
#line 72 "willard-ast.pcc"
         } break;
      case a_Exp::tag_LIT: {
#line 73 "willard-ast.pcc"
        return S << _LIT(e)->LIT; 
#line 73 "willard-ast.pcc"
         } break;
      case a_Exp::tag_ID: {
#line 74 "willard-ast.pcc"
        return S << _ID(e)->ID; 
#line 74 "willard-ast.pcc"
         } break;
      case a_Exp::tag_TUPLE: {
#line 75 "willard-ast.pcc"
        return S << '[' << _TUPLE(e)->TUPLE << ']'; 
#line 75 "willard-ast.pcc"
         } break;
      case a_Exp::tag_FORALL: {
#line 76 "willard-ast.pcc"
        return S << "(forall"<<_FORALL(e)->_1<<"in"<<_FORALL(e)->_2<<'.'<<_FORALL(e)->_3<<')'; 
#line 76 "willard-ast.pcc"
         } break;
      case a_Exp::tag_EXISTS: {
#line 77 "willard-ast.pcc"
        return S << "(exists"<<_EXISTS(e)->_1<<"in"<<_EXISTS(e)->_2<<'.'<<_EXISTS(e)->_3<<')'; 
#line 77 "willard-ast.pcc"
         } break;
      case a_Exp::tag_GUARD: {
#line 81 "willard-ast.pcc"
        return S << "if" << _GUARD(e)->_1 << "then" << _GUARD(e)->_2 
         				   << "else" << "{}"; 
#line 82 "willard-ast.pcc"
         } break;
      case a_Exp::tag_GENERATOR: {
         if (_GENERATOR(e)->_1) {
#line 79 "willard-ast.pcc"
           S << '{'; print_set_comp(S,e); return S << '}'; 
#line 79 "willard-ast.pcc"
         } else {
#line 78 "willard-ast.pcc"
           return S << "{}"; 
#line 78 "willard-ast.pcc"
         }
         } break;
      default: {
#line 80 "willard-ast.pcc"
        return print_let(S,e); 
#line 80 "willard-ast.pcc"
         } break;
   }
}
#line 84 "willard-ast.pcc"
#line 84 "willard-ast.pcc"

}

PrettyOStream& operator << (PrettyOStream& S, Exps es)
{  
#line 88 "willard-ast.pcc"
#line 90 "willard-ast.pcc"
{
   for (;;) {
      if (es) {
         if (es->_2) {
#line 90 "willard-ast.pcc"
           S << es->_1 << ','; es = es->_2; 
#line 90 "willard-ast.pcc"
         } else {
#line 89 "willard-ast.pcc"
           return S << es->_1; 
#line 89 "willard-ast.pcc"
         }
      } else { goto L6; }
   }
   L6:;
}
#line 91 "willard-ast.pcc"
#line 91 "willard-ast.pcc"

   return S;
} 

PrettyOStream& operator << (PrettyOStream& S, Literal l)
{  
#line 96 "willard-ast.pcc"
#line 99 "willard-ast.pcc"
{
   switch (l->tag__) {
      case a_Literal::tag_INT: {
#line 97 "willard-ast.pcc"
        return S << _INT(l)->INT; 
#line 97 "willard-ast.pcc"
         } break;
      case a_Literal::tag_STRING: {
#line 98 "willard-ast.pcc"
        return S << _STRING(l)->STRING; 
#line 98 "willard-ast.pcc"
         } break;
      default: {
#line 99 "willard-ast.pcc"
        return S << (_BOOL(l)->BOOL ? "true" : "false"); 
#line 99 "willard-ast.pcc"
         } break;
   }
}
#line 100 "willard-ast.pcc"
#line 100 "willard-ast.pcc"

}

PrettyOStream& operator << (PrettyOStream& S, Ids ids)
{  
#line 104 "willard-ast.pcc"
#line 106 "willard-ast.pcc"
{
   for (;;) {
      if (ids) {
         if (ids->_2) {
#line 106 "willard-ast.pcc"
           S << ids->_1 << ','; ids = ids->_2; 
#line 106 "willard-ast.pcc"
         } else {
#line 105 "willard-ast.pcc"
           return S << ids->_1; 
#line 105 "willard-ast.pcc"
         }
      } else { goto L7; }
   }
   L7:;
}
#line 107 "willard-ast.pcc"
#line 107 "willard-ast.pcc"

   return S;
} 
#line 110 "willard-ast.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 42
Number of ifs generated      = 12
Number of switches generated = 5
Number of labels             = 2
Number of gotos              = 4
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
