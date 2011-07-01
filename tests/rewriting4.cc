///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.3),
//  last updated on Mar 26, 1997.
//  The original source file is "rewriting4.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_PRINTER_USED
#define PROP_QUARK_USED
#include <propdefs.h>
#line 1 "rewriting4.pcc"
/////////////////////////////////////////////////////////////////////////////
//  This program demonstrates the use of attribute evaluation in Prop's
//  rewrite class.
/////////////////////////////////////////////////////////////////////////////

#include <iostream.h>

/////////////////////////////////////////////////////////////////////////////
//  The datatype EXP represents a simple expression (with pretty printing.)
/////////////////////////////////////////////////////////////////////////////
#line 11 "rewriting4.pcc"
#line 17 "rewriting4.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for EXP
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_EXP_defined
#define datatype_EXP_defined
   class a_EXP;
   typedef a_EXP * EXP;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype EXP
//
///////////////////////////////////////////////////////////////////////////////
class a_EXP : public TermObj {
public:
   enum Tag_EXP {
      tag_num = 0, tag_add = 1, tag_sub = 2, 
      tag_mul = 3, tag_div = 4
   };

public:
   const Tag_EXP tag__; // variant tag
protected:
   inline a_EXP(Tag_EXP t__) : tag__(t__) {}
public:
};
inline int boxed(const a_EXP *) { return 1; }
inline int untag(const a_EXP * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for EXP
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
extern ostream& operator<<(ostream&, EXP);
extern PrettyOStream& operator<<(PrettyOStream&, EXP);
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::num
//
///////////////////////////////////////////////////////////////////////////////
class EXP_num : public a_EXP {
public:
#line 11 "rewriting4.pcc"
   int num; 
   inline EXP_num (int x_num)
    : a_EXP(tag_num), num(x_num)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::add
//
///////////////////////////////////////////////////////////////////////////////
class EXP_add : public a_EXP {
public:
#line 12 "rewriting4.pcc"
   EXP _1; EXP _2; 
   inline EXP_add (EXP x_1, EXP x_2)
    : a_EXP(tag_add), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::sub
//
///////////////////////////////////////////////////////////////////////////////
class EXP_sub : public a_EXP {
public:
#line 13 "rewriting4.pcc"
   EXP _1; EXP _2; 
   inline EXP_sub (EXP x_1, EXP x_2)
    : a_EXP(tag_sub), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::mul
//
///////////////////////////////////////////////////////////////////////////////
class EXP_mul : public a_EXP {
public:
#line 14 "rewriting4.pcc"
   EXP _1; EXP _2; 
   inline EXP_mul (EXP x_1, EXP x_2)
    : a_EXP(tag_mul), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::div
//
///////////////////////////////////////////////////////////////////////////////
class EXP_div : public a_EXP {
public:
#line 15 "rewriting4.pcc"
   EXP _1; EXP _2; 
   inline EXP_div (EXP x_1, EXP x_2)
    : a_EXP(tag_div), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for EXP
//
///////////////////////////////////////////////////////////////////////////////
inline a_EXP * num (int x_num)
{
   return new EXP_num (x_num);
}
inline a_EXP * add (EXP x_1, EXP x_2)
{
   return new EXP_add (x_1, x_2);
}
inline a_EXP * sub (EXP x_1, EXP x_2)
{
   return new EXP_sub (x_1, x_2);
}
inline a_EXP * mul (EXP x_1, EXP x_2)
{
   return new EXP_mul (x_1, x_2);
}
inline a_EXP * div (EXP x_1, EXP x_2)
{
   return new EXP_div (x_1, x_2);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for EXP
//
///////////////////////////////////////////////////////////////////////////////
inline EXP_num * _num(const a_EXP * _x_) { return (EXP_num *)_x_; }
inline EXP_add * _add(const a_EXP * _x_) { return (EXP_add *)_x_; }
inline EXP_sub * _sub(const a_EXP * _x_) { return (EXP_sub *)_x_; }
inline EXP_mul * _mul(const a_EXP * _x_) { return (EXP_mul *)_x_; }
inline EXP_div * _div(const a_EXP * _x_) { return (EXP_div *)_x_; }

#line 17 "rewriting4.pcc"
#line 17 "rewriting4.pcc"


/////////////////////////////////////////////////////////////////////////////
//  The rewrite class Eval involves the transformation of datatype
//  EXP into integers.
/////////////////////////////////////////////////////////////////////////////
#line 23 "rewriting4.pcc"
#line 23 "rewriting4.pcc"
class Eval : public BURS {
private:
   Eval(const Eval&);               // no copy constructor
   void operator = (const Eval&); // no assignment
public:
   struct Eval_StateRec * stack__, * stack_top__;
          void labeler(EXP redex);
   inline virtual void operator () (EXP redex) { labeler(redex); }
          int  reduce(EXP redex,int lhs = 1);
private:
};
#line 23 "rewriting4.pcc"
#line 23 "rewriting4.pcc"


/////////////////////////////////////////////////////////////////////////////
//  Now, here are the rules.  Pattern variables of the form '$x' refer
//  to synthesized attributes.  (Normal pattern variables of the
//  form 'x' still refer to the components of a term.)
//
//  Notice that nested attributes and guards on attribute values 
//  are both allowed.  (The nested attribute rule is contrived.)
/////////////////////////////////////////////////////////////////////////////
#line 33 "rewriting4.pcc"
#line 40 "rewriting4.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// This macro can be redefined by the user for debugging
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DEBUG_Eval
#define DEBUG_Eval(repl,redex,file,line,rule) repl
#else
static const char * Eval_file_name = "rewriting4.pcc";
#endif


///////////////////////////////////////////////////////////////////////////////
// State record for rewrite class Eval
///////////////////////////////////////////////////////////////////////////////
struct Eval_StateRec {
   TreeTables::Cost cost[1]; // cost for each non-terminal
   struct { // accept rule number
   } rule;
};

///////////////////////////////////////////////////////////////////////////////
// Accept rules tables for rewrite class Eval
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Closure methods for rewrite class Eval
///////////////////////////////////////////////////////////////////////////////

void Eval::labeler (EXP redex)
{
   int cost__;
   Eval_StateRec * _state_rec = (Eval_StateRec *)mem[sizeof(Eval_StateRec)];
   redex->set_state_rec(_state_rec);
   _state_rec->cost[0] = 0;32767;
   {
      switch (redex->tag__) {
         case a_EXP::tag_num: {} break;
         case a_EXP::tag_add: {
            labeler(_add(redex)->_1);
            labeler(_add(redex)->_2);} break;
         case a_EXP::tag_sub: {
            labeler(_sub(redex)->_1);
            labeler(_sub(redex)->_2);} break;
         case a_EXP::tag_mul: {
            labeler(_mul(redex)->_1);
            labeler(_mul(redex)->_2);} break;
         default: {
            labeler(_div(redex)->_1);
            labeler(_div(redex)->_2);
            if (
#line 39 "rewriting4.pcc"
            (_1__ != 0)
#line 39 "rewriting4.pcc"
) {
               } else {
               }
            } break;
      }
   }
   
}

int  Eval::reduce(EXP redex,int lhs)
{
   int __;
   const Eval_StateRec * _state_rec = (const Eval_StateRec *)(redex->get_state_rec());
   int r__;
   switch (lhs) {
      default: r__ = -1; break;
   }
   switch (r__) {
      case 5: { // div (x as _, y as _)
         int  _0__ = reduce(_div(redex)->_1,0); // (none)
         int  _1__ = reduce(_div(redex)->_2,0); // (none)
         
#line 40 "rewriting4.pcc"
        cerr << "Division by zero\n"; __ = 0; 
#line 40 "rewriting4.pcc"
} break;
      case 4: { // div (x as _, y as _)
         int  _0__ = reduce(_div(redex)->_1,0); // (none)
         int  _1__ = reduce(_div(redex)->_2,0); // (none)
         
#line 39 "rewriting4.pcc"
        __ = _0__ / _1__; 
#line 39 "rewriting4.pcc"
} break;
      case 3: { // mul (x as _, y as _)
         int  _0__ = reduce(_mul(redex)->_1,0); // (none)
         int  _1__ = reduce(_mul(redex)->_2,0); // (none)
         
#line 38 "rewriting4.pcc"
        __ = _0__ * _1__; 
#line 38 "rewriting4.pcc"
} break;
      case 2: { // sub (x as _, y as _)
         int  _0__ = reduce(_sub(redex)->_1,0); // (none)
         int  _1__ = reduce(_sub(redex)->_2,0); // (none)
         
#line 36 "rewriting4.pcc"
        __ = _0__ - _1__; 
#line 36 "rewriting4.pcc"
} break;
      case 1: { // add (x as _, y as _)
         int  _0__ = reduce(_add(redex)->_1,0); // (none)
         int  _1__ = reduce(_add(redex)->_2,0); // (none)
         
#line 35 "rewriting4.pcc"
        __ = _0__ + _1__; 
#line 35 "rewriting4.pcc"
} break;
      case 0: { // num x as _
         
#line 34 "rewriting4.pcc"
        __ = _num(redex)->num; 
#line 34 "rewriting4.pcc"
} break;
   }
   return __; 
}

#line 41 "rewriting4.pcc"
#line 41 "rewriting4.pcc"


/////////////////////////////////////////////////////////////////////////////
//  Generate the implementation of the datatype. 
/////////////////////////////////////////////////////////////////////////////
#line 46 "rewriting4.pcc"
#line 46 "rewriting4.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Interface specification of datatype EXP
//
///////////////////////////////////////////////////////////////////////////////
#line 46 "rewriting4.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for EXP
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, EXP  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, EXP  obj__);

///////////////////////////////////////////////////////////////////////////////
//
// Instantiation of datatype EXP
//
///////////////////////////////////////////////////////////////////////////////
#line 46 "rewriting4.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for EXP
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, EXP  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, EXP  obj__)
{
   switch (untag(obj__))
   {
      case 0: 
         strm__ << _num(obj__)->num; // int
         break;
      case 1: 
         strm__ << '(';
         strm__ << _add(obj__)->_1; // EXP
         strm__ << " + ";
         strm__ << _add(obj__)->_2; // EXP
         strm__ << ')';
         break;
      case 2: 
         strm__ << '(';
         strm__ << _sub(obj__)->_1; // EXP
         strm__ << " - ";
         strm__ << _sub(obj__)->_2; // EXP
         strm__ << ')';
         break;
      case 3: 
         strm__ << '(';
         strm__ << _mul(obj__)->_1; // EXP
         strm__ << " * ";
         strm__ << _mul(obj__)->_2; // EXP
         strm__ << ')';
         break;
      case 4: 
         strm__ << '(';
         strm__ << _div(obj__)->_1; // EXP
         strm__ << " / ";
         strm__ << _div(obj__)->_2; // EXP
         strm__ << ')';
         break;
   }
   return strm__;
}



#line 46 "rewriting4.pcc"
#line 46 "rewriting4.pcc"


/////////////////////////////////////////////////////////////////////////////
//  Test the rewriting rules.
/////////////////////////////////////////////////////////////////////////////
int main()
{  // Instantiate a rewriting class.
   Eval eval;

   //  e = (1 + 2) * (5 - 3)
   EXP e = mul(add(num(1), num(2)), sub(num(5),num(3)));
  
   cout << e << " = " << eval(e) << '\n'; 
   return 0;
}
#line 61 "rewriting4.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 1
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
