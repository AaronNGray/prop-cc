///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\..\app\willard\willard-ast.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../../app/willard/willard-ast.pcc"
#include "willard-ast.h"
#include <AD/pretty/postream.h>

#line 4 "../../../app/willard/willard-ast.pcc"
#line 4 "../../../app/willard/willard-ast.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Exp>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Id>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype List<Tuple2<Ids, Exps> >
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Exp
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"


///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Exp>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Exp>;
template a_List<Exp> * list_1_(Tuple2<Ids, Exps>  x_1, a_List<Tuple2<Ids, Exps> > *  x_2);
template a_List<Exp> * list_1_(Tuple2<Ids, Exps>  x_list_1_);
template int boxed(const a_List<Exp> *);
template int untag(const a_List<Exp> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Id>
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Id>;
template a_List<Id> * list_1_(Exp x_1, a_List<Exp> *  x_2);
template a_List<Id> * list_1_(Exp x_list_1_);
template int boxed(const a_List<Id> *);
template int untag(const a_List<Id> *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype List<Tuple2<Ids, Exps> >
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"
#ifdef PROP_EXPLICIT_TEMPLATE_INSTANTIATION
template class a_List<Tuple2<Ids, Exps> >;
template a_List<Tuple2<Ids, Exps> > * list_1_(Id x_1, a_List<Id> *  x_2);
template a_List<Tuple2<Ids, Exps> > * list_1_(Id x_list_1_);
template int boxed(const a_List<Tuple2<Ids, Exps> > *);
template int untag(const a_List<Tuple2<Ids, Exps> > *);
#endif /* PROP_EXPLICIT_TEMPLATE_INSTANTIATION */

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype Literal
//
///////////////////////////////////////////////////////////////////////////////
#line 4 "../../../app/willard/willard-ast.pcc"


#line 4 "../../../app/willard/willard-ast.pcc"
#line 4 "../../../app/willard/willard-ast.pcc"
 
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
   
#line 20 "../../../app/willard/willard-ast.pcc"
#line 22 "../../../app/willard/willard-ast.pcc"
{
  for (;;) {
    switch (root->tag__) {
      case a_Exp::tag_GUARD: {
#line 22 "../../../app/willard/willard-ast.pcc"
       guard = _GUARD(root)->_1; has_guard = true; root = _GUARD(root)->_2; 
#line 22 "../../../app/willard/willard-ast.pcc"
        } break;
      case a_Exp::tag_GENERATOR: {
#line 21 "../../../app/willard/willard-ast.pcc"
       root = _GENERATOR(root)->_3; 
#line 21 "../../../app/willard/willard-ast.pcc"
        } break;
      default: { goto L1; } break;
    }
  }
  L1:;
}
#line 23 "../../../app/willard/willard-ast.pcc"
#line 23 "../../../app/willard/willard-ast.pcc"

   S << root << ':';
   char comma = '\0';

   // print the generators
   
#line 28 "../../../app/willard/willard-ast.pcc"
#line 37 "../../../app/willard/willard-ast.pcc"
{
  for (;;) {
    switch (exp->tag__) {
      case a_Exp::tag_GENERATOR: {
        if (_GENERATOR(exp)->_1) {
          if (_GENERATOR(exp)->_1->_2) {
            L3:; 
#line 33 "../../../app/willard/willard-ast.pcc"
           if (comma) S << comma << space;
            			        S << '[' << _GENERATOR(exp)->_1 << ']' << "in" << space
            				  << '[' << _GENERATOR(exp)->_2 << ']'; 
                                            comma = ','; exp = _GENERATOR(exp)->_3; 
            			      
#line 37 "../../../app/willard/willard-ast.pcc"
          } else {
            if (_GENERATOR(exp)->_2) {
              if (_GENERATOR(exp)->_2->_2) { goto L3; } else {
#line 29 "../../../app/willard/willard-ast.pcc"
               if (comma) S << comma << space;
                			        S << _GENERATOR(exp)->_1->_1 << "in" << _GENERATOR(exp)->_2->_1; 
                                                comma = ','; exp = _GENERATOR(exp)->_3; 
                			      
#line 32 "../../../app/willard/willard-ast.pcc"
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
#line 38 "../../../app/willard/willard-ast.pcc"
#line 38 "../../../app/willard/willard-ast.pcc"


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
   
#line 53 "../../../app/willard/willard-ast.pcc"
#line 55 "../../../app/willard/willard-ast.pcc"
{
  for (;;) {
    switch (e->tag__) {
      case a_Exp::tag_LET: {
#line 55 "../../../app/willard/willard-ast.pcc"
       S << tab << _LET(e)->_1 << '=' << _LET(e)->_2 << newline; e = _LET(e)->_3; 
#line 55 "../../../app/willard/willard-ast.pcc"
        } break;
      default: { goto L4; } break;
    }
  }
  L4:;
}
#line 56 "../../../app/willard/willard-ast.pcc"
#line 56 "../../../app/willard/willard-ast.pcc"

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
#line 68 "../../../app/willard/willard-ast.pcc"
#line 82 "../../../app/willard/willard-ast.pcc"
{
  switch (e->tag__) {
    case a_Exp::tag_OP: {
      if (_OP(e)->_2) {
        if (_OP(e)->_2->_2) {
          if (_OP(e)->_2->_2->_2) {
            L5:; 
#line 71 "../../../app/willard/willard-ast.pcc"
           return S << _OP(e)->_1 << '(' << _OP(e)->_2 << ')'; 
#line 71 "../../../app/willard/willard-ast.pcc"
          } else {
#line 69 "../../../app/willard/willard-ast.pcc"
           return S << '(' << _OP(e)->_2->_1 << _OP(e)->_1 << _OP(e)->_2->_2->_1 << ')'; 
#line 69 "../../../app/willard/willard-ast.pcc"
          }
        } else {
#line 70 "../../../app/willard/willard-ast.pcc"
         return S << '(' << _OP(e)->_1 << _OP(e)->_2->_1 << ')'; 
#line 70 "../../../app/willard/willard-ast.pcc"
        }
      } else { goto L5; }
      } break;
    case a_Exp::tag_APP: {
#line 72 "../../../app/willard/willard-ast.pcc"
     return S << _APP(e)->_1 << '(' << _APP(e)->_2 << ')'; 
#line 72 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Exp::tag_LIT: {
#line 73 "../../../app/willard/willard-ast.pcc"
     return S << _LIT(e)->LIT; 
#line 73 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Exp::tag_ID: {
#line 74 "../../../app/willard/willard-ast.pcc"
     return S << _ID(e)->ID; 
#line 74 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Exp::tag_TUPLE: {
#line 75 "../../../app/willard/willard-ast.pcc"
     return S << '[' << _TUPLE(e)->TUPLE << ']'; 
#line 75 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Exp::tag_FORALL: {
#line 76 "../../../app/willard/willard-ast.pcc"
     return S << "(forall"<<_FORALL(e)->_1<<"in"<<_FORALL(e)->_2<<'.'<<_FORALL(e)->_3<<')'; 
#line 76 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Exp::tag_EXISTS: {
#line 77 "../../../app/willard/willard-ast.pcc"
     return S << "(exists"<<_EXISTS(e)->_1<<"in"<<_EXISTS(e)->_2<<'.'<<_EXISTS(e)->_3<<')'; 
#line 77 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Exp::tag_GUARD: {
#line 81 "../../../app/willard/willard-ast.pcc"
     return S << "if" << _GUARD(e)->_1 << "then" << _GUARD(e)->_2 
      				   << "else" << "{}"; 
#line 82 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Exp::tag_GENERATOR: {
      if (_GENERATOR(e)->_1) {
#line 79 "../../../app/willard/willard-ast.pcc"
       S << '{'; print_set_comp(S,e); return S << '}'; 
#line 79 "../../../app/willard/willard-ast.pcc"
      } else {
#line 78 "../../../app/willard/willard-ast.pcc"
       return S << "{}"; 
#line 78 "../../../app/willard/willard-ast.pcc"
      }
      } break;
    default: {
#line 80 "../../../app/willard/willard-ast.pcc"
     return print_let(S,e); 
#line 80 "../../../app/willard/willard-ast.pcc"
      } break;
  }
}
#line 84 "../../../app/willard/willard-ast.pcc"
#line 84 "../../../app/willard/willard-ast.pcc"

}

PrettyOStream& operator << (PrettyOStream& S, Exps es)
{  
#line 88 "../../../app/willard/willard-ast.pcc"
#line 90 "../../../app/willard/willard-ast.pcc"
{
  for (;;) {
    if (es) {
      if (es->_2) {
#line 90 "../../../app/willard/willard-ast.pcc"
       S << es->_1 << ','; es = es->_2; 
#line 90 "../../../app/willard/willard-ast.pcc"
      } else {
#line 89 "../../../app/willard/willard-ast.pcc"
       return S << es->_1; 
#line 89 "../../../app/willard/willard-ast.pcc"
      }
    } else { goto L6; }
  }
  L6:;
}
#line 91 "../../../app/willard/willard-ast.pcc"
#line 91 "../../../app/willard/willard-ast.pcc"

   return S;
} 

PrettyOStream& operator << (PrettyOStream& S, Literal l)
{  
#line 96 "../../../app/willard/willard-ast.pcc"
#line 99 "../../../app/willard/willard-ast.pcc"
{
  switch (l->tag__) {
    case a_Literal::tag_INT: {
#line 97 "../../../app/willard/willard-ast.pcc"
     return S << _INT(l)->INT; 
#line 97 "../../../app/willard/willard-ast.pcc"
      } break;
    case a_Literal::tag_STRING: {
#line 98 "../../../app/willard/willard-ast.pcc"
     return S << _STRING(l)->STRING; 
#line 98 "../../../app/willard/willard-ast.pcc"
      } break;
    default: {
#line 99 "../../../app/willard/willard-ast.pcc"
     return S << (_BOOL(l)->BOOL ? "true" : "false"); 
#line 99 "../../../app/willard/willard-ast.pcc"
      } break;
  }
}
#line 100 "../../../app/willard/willard-ast.pcc"
#line 100 "../../../app/willard/willard-ast.pcc"

}

PrettyOStream& operator << (PrettyOStream& S, Ids ids)
{  
#line 104 "../../../app/willard/willard-ast.pcc"
#line 106 "../../../app/willard/willard-ast.pcc"
{
  for (;;) {
    if (ids) {
      if (ids->_2) {
#line 106 "../../../app/willard/willard-ast.pcc"
       S << ids->_1 << ','; ids = ids->_2; 
#line 106 "../../../app/willard/willard-ast.pcc"
      } else {
#line 105 "../../../app/willard/willard-ast.pcc"
       return S << ids->_1; 
#line 105 "../../../app/willard/willard-ast.pcc"
      }
    } else { goto L7; }
  }
  L7:;
}
#line 107 "../../../app/willard/willard-ast.pcc"
#line 107 "../../../app/willard/willard-ast.pcc"

   return S;
} 
#line 110 "../../../app/willard/willard-ast.pcc"
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
