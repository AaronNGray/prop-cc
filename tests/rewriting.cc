///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.2),
//  last updated on Mar 14, 1997.
//  The original source file is "rewriting.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_REFCOUNT_USED
#define PROP_QUARK_USED
#include <propdefs.h>
#line 1 "rewriting.pcc"
//////////////////////////////////////////////////////////////////////////////
//  Testing the rewriting features.
//////////////////////////////////////////////////////////////////////////////
#include <new.h>
#include <iostream.h>

int balance;     // number of allocation - number of deallocation
int div_by_zero; // number of division by zeros

//////////////////////////////////////////////////////////////////////////////
// We'll use reference counting with rewriting.
// The operators new and delete are redefined to keep track of   
// the number of allocations and deallocation.
// This is for demonstration use only.  In practice, it is
// unnecessary to redefine these operators if the normal ones
// suffice.
//////////////////////////////////////////////////////////////////////////////
class MEM {
public:
   inline void * operator new (size_t n) 
      { balance++; return new char [n]; }
   inline void   operator delete (void * x)
      { balance--; delete [] ((char*)x); }
};

//////////////////////////////////////////////////////////////////////////////
//  Define the datatypes EXP and EXP_LIST.  Currently, rewriting can only be 
//  performed on datatypes(and not views) in Prop.  If replacement is 
//  to be performed on a datatype, then it should be declared using 
//  the ``rewrite'' qualifier.
//
//  We'll extend these datatypes from class MEM so that it'll inherit
//  MEM's operator new and delete.
//////////////////////////////////////////////////////////////////////////////
#line 35 "rewriting.pcc"
#line 48 "rewriting.pcc"
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

#  define om (EXP)0

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for EXP_LIST
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_EXP_LIST_defined
#define datatype_EXP_LIST_defined
   class a_EXP_LIST;
   typedef a_EXP_LIST * EXP_LIST;
#endif

#  define nil_1_ (EXP_LIST)0

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype EXP
//
///////////////////////////////////////////////////////////////////////////////
class a_EXP : public MEM, public TermObj {
public:
   enum Tag_EXP {
      tag_num = 0, tag_var = 1, tag_add = 2, 
      tag_sub = 3, tag_mul = 4, tag_div = 5, 
      tag_exp_list = 6
   };

public:
   const Tag_EXP tag__; // variant tag
protected:
   inline a_EXP(Tag_EXP t__) : tag__(t__) {}
public:
};
inline int boxed(const a_EXP * x) { return x != 0; }
inline int untag(const a_EXP * x) { return x ? (x->tag__+1) : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::num
//
///////////////////////////////////////////////////////////////////////////////
class EXP_num : public a_EXP {
public:
#line 36 "rewriting.pcc"
   int num; 
   inline EXP_num (int x_num)
    : a_EXP(tag_num), num(x_num)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::var
//
///////////////////////////////////////////////////////////////////////////////
class EXP_var : public a_EXP {
public:
#line 37 "rewriting.pcc"
   char var; 
   inline EXP_var (char x_var)
    : a_EXP(tag_var), var(x_var)
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
#line 38 "rewriting.pcc"
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
#line 39 "rewriting.pcc"
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
#line 40 "rewriting.pcc"
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
#line 41 "rewriting.pcc"
   EXP _1; EXP _2; 
   inline EXP_div (EXP x_1, EXP x_2)
    : a_EXP(tag_div), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::exp_list
//
///////////////////////////////////////////////////////////////////////////////
class EXP_exp_list : public a_EXP {
public:
#line 42 "rewriting.pcc"
   EXP_LIST exp_list; 
   inline EXP_exp_list (EXP_LIST x_exp_list)
    : a_EXP(tag_exp_list), exp_list(x_exp_list)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for EXP
//
///////////////////////////////////////////////////////////////////////////////
inline a_EXP * num (int x_num)
{ return new EXP_num (x_num); }
inline a_EXP * var (char x_var)
{ return new EXP_var (x_var); }
inline a_EXP * add (EXP x_1, EXP x_2)
{ return new EXP_add (x_1, x_2); }
inline a_EXP * sub (EXP x_1, EXP x_2)
{ return new EXP_sub (x_1, x_2); }
inline a_EXP * mul (EXP x_1, EXP x_2)
{ return new EXP_mul (x_1, x_2); }
inline a_EXP * div (EXP x_1, EXP x_2)
{ return new EXP_div (x_1, x_2); }
inline a_EXP * exp_list (EXP_LIST x_exp_list)
{ return new EXP_exp_list (x_exp_list); }
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for EXP
//
///////////////////////////////////////////////////////////////////////////////
inline EXP_num * _num(const a_EXP * _x_) { return (EXP_num *)_x_; }
inline EXP_var * _var(const a_EXP * _x_) { return (EXP_var *)_x_; }
inline EXP_add * _add(const a_EXP * _x_) { return (EXP_add *)_x_; }
inline EXP_sub * _sub(const a_EXP * _x_) { return (EXP_sub *)_x_; }
inline EXP_mul * _mul(const a_EXP * _x_) { return (EXP_mul *)_x_; }
inline EXP_div * _div(const a_EXP * _x_) { return (EXP_div *)_x_; }
inline EXP_exp_list * _exp_list(const a_EXP * _x_) { return (EXP_exp_list *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP_LIST::#[...]
//
///////////////////////////////////////////////////////////////////////////////
class a_EXP_LIST : public MEM, public TermObj {
public:
#line 46 "rewriting.pcc"
   EXP _1; EXP_LIST _2; 
   inline a_EXP_LIST (EXP x_1, EXP_LIST x_2)
    : _1(x_1), _2(x_2)
   {
   }
   inline a_EXP_LIST (EXP x_1, int x_2)
    : _1(x_1), _2((a_EXP_LIST *)x_2)
   {
   }
};
inline int boxed(const a_EXP_LIST * x) { return x != 0; }
inline int untag(const a_EXP_LIST * x) { return x ? 1 : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for EXP_LIST
//
///////////////////////////////////////////////////////////////////////////////
inline a_EXP_LIST * list_1_ (EXP x_1, EXP_LIST x_2)
{ return new a_EXP_LIST (x_1, x_2); }
inline a_EXP_LIST * list_1_ (EXP x_1, int x_2)
{ return new a_EXP_LIST (x_1, x_2); }
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for EXP_LIST
//
///////////////////////////////////////////////////////////////////////////////


#line 48 "rewriting.pcc"
#line 48 "rewriting.pcc"


//////////////////////////////////////////////////////////////////////////////
//  Define a method that prints an expression.  This is a simple
//  inductive definition
//////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& f, EXP_LIST l);
ostream& operator << (ostream& f, EXP e)
{  
#line 56 "rewriting.pcc"
#line 64 "rewriting.pcc"
{
   if (e) {
      switch (e->tag__) {
         case a_EXP::tag_num: {
#line 58 "rewriting.pcc"
           return f << _num(e)->num; 
#line 58 "rewriting.pcc"
            } break;
         case a_EXP::tag_var: {
#line 59 "rewriting.pcc"
           return f << _var(e)->var; 
#line 59 "rewriting.pcc"
            } break;
         case a_EXP::tag_add: {
#line 60 "rewriting.pcc"
           return f << '(' << _add(e)->_1 << " + " << _add(e)->_2 << ')'; 
#line 60 "rewriting.pcc"
            } break;
         case a_EXP::tag_sub: {
#line 61 "rewriting.pcc"
           return f << '(' << _sub(e)->_1 << " - " << _sub(e)->_2 << ')'; 
#line 61 "rewriting.pcc"
            } break;
         case a_EXP::tag_mul: {
#line 62 "rewriting.pcc"
           return f << '(' << _mul(e)->_1 << " * " << _mul(e)->_2 << ')'; 
#line 62 "rewriting.pcc"
            } break;
         case a_EXP::tag_div: {
#line 63 "rewriting.pcc"
           return f << '(' << _div(e)->_1 << " / " << _div(e)->_2 << ')'; 
#line 63 "rewriting.pcc"
            } break;
         default: {
#line 64 "rewriting.pcc"
           return f << '[' << _exp_list(e)->exp_list << ']'; 
#line 64 "rewriting.pcc"
            } break;
      }
   } else {
#line 57 "rewriting.pcc"
     return f << "om"; 
#line 57 "rewriting.pcc"
   }
}
#line 65 "rewriting.pcc"
#line 65 "rewriting.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//  This prints an expression list
//////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& f, EXP_LIST l)
{  
#line 72 "rewriting.pcc"
#line 75 "rewriting.pcc"
{
   if (l) {
      if (l->_2) {
#line 75 "rewriting.pcc"
        return f << l->_1 << ", " << l->_2; 
#line 75 "rewriting.pcc"
      } else {
#line 74 "rewriting.pcc"
        return f << l->_1; 
#line 74 "rewriting.pcc"
      }
   } else {
#line 73 "rewriting.pcc"
     return f; 
#line 73 "rewriting.pcc"
   }
}
#line 76 "rewriting.pcc"
#line 76 "rewriting.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//  Define the interface to a ``rewriting class.''  A rewriting class 
//  is simply a C++ class with rewriting rules attached.  In real programs
//  this definition should be placed in some definition (i.e. .ph) files.
//  
//  In parenthesis, we must list all datatypes involved.   Unlike
//  simple pattern matching, rewriting can involve a set of mutually
//  recursive (or mutually exclusive, if desired) datatype definitions.
//  So in general this is a comma delimited list.   
//
//  In this example it involves only the datatypes EXP and EXP_LIST.
//////////////////////////////////////////////////////////////////////////////
#line 91 "rewriting.pcc"
#line 95 "rewriting.pcc"
class Simplify : public BURS {
private:
   Simplify(const Simplify&);               // no copy constructor
   void operator = (const Simplify&); // no assignment
public:
   struct Simplify_StateRec * stack__, * stack_top__;
public:
   void labeler(const char *, int&, int);
   void labeler(Quark, int&, int);
          void  labeler(EXP & redex, int&, int);
   inline virtual void  operator () (EXP & redex) { int s; labeler(redex,s,0); }
          void  labeler(EXP_LIST & redex, int&, int);
   inline virtual void  operator () (EXP_LIST & redex) { int s; labeler(redex,s,0); }
private:
#line 92 "rewriting.pcc"
 // nothing here for now.
   public:
      Simplify() {}
#line 95 "rewriting.pcc"
};
#line 95 "rewriting.pcc"
#line 95 "rewriting.pcc"


//////////////////////////////////////////////////////////////////////////////
//  Now we define the rewriting rules in the rewriting class Simplify.  These
//  rules should be placed in an implementation file (.pcc, .pC, .pc++ etc).
//
//  In this brief sample class we have some rules that perform 
//  simple constant folding and strength reduction.
//
//  Currently, all the rules for a rewrite class must be placed in
//  the same rewrite construct.  This will probably change in the future
//  once I work out the details on incremental tree automata compilation.
//////////////////////////////////////////////////////////////////////////////
#line 108 "rewriting.pcc"
#line 128 "rewriting.pcc"
static const TreeTables::Offset Simplify_accept_base [ 15 ] = {
   0, 1, 2, 3, 5, 7, 11, 13, 15, 18, 22, 30, 34, 37, 42
};
static const TreeTables::Rule Simplify_accept_vector [ 44 ] = {
   -1, 17, -1, 16, -1, 1, -1, 0, 1, 10, -1, 0, -1, 2, -1, 2, 
   11, -1, 3, 5, 7, -1, 3, 4, 5, 6, 7, 8, 12, -1, 4, 6, 
   8, -1, 9, 14, -1, 9, 13, 14, 15, -1, 15, -1
};
static const TreeTables::State Simplify_theta_3[2][2] = {
   { 0, 4 },
   { 6, 5 }
};


static const TreeTables::State Simplify_theta_4[2][2] = {
   { 0, 7 },
   { 0, 8 }
};


static const TreeTables::State Simplify_theta_5[2][2] = {
   { 0, 9 },
   { 11, 10 }
};


static const TreeTables::State Simplify_theta_6[2][2] = {
   { 0, 12 },
   { 14, 13 }
};


static const TreeTables::State Simplify_mu_3_0[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_3_1[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_4_0[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_4_1[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_5_0[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_5_1[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_6_0[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_6_1[15] = {
   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


inline void  Simplify::labeler(char const * redex,int& s__,int)
{
   {
s__ = 0;
   }
}

inline void  Simplify::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Simplify::labeler (EXP & redex, int& s__, int r__)
{
replacement__:
   int cached__;
   if (r__ && boxed(redex) && (cached__ = redex->get_rewrite_state()) != BURS::undefined_state)
   { s__ = cached__; return; }
   if ((redex)) {
      switch(redex->tag__) {
         case a_EXP::tag_num: { 
            int s0__;
            s0__ = 0; // int
            s__ = 2;} break;
         case a_EXP::tag_var: { 
            int s0__;
            s0__ = 0; // char
            s__ = 0;} break;
         case a_EXP::tag_add: { 
            int s0__;
            int s1__;
            labeler(_add(redex)->_1, s0__, r__);
            labeler(_add(redex)->_2, s1__, r__);
            s__ = Simplify_theta_3[Simplify_mu_3_0[s0__]][Simplify_mu_3_1[s1__]]; } break;
         case a_EXP::tag_sub: { 
            int s0__;
            int s1__;
            labeler(_sub(redex)->_1, s0__, r__);
            labeler(_sub(redex)->_2, s1__, r__);
            s__ = Simplify_theta_4[Simplify_mu_4_0[s0__]][Simplify_mu_4_1[s1__]]; } break;
         case a_EXP::tag_mul: { 
            int s0__;
            int s1__;
            labeler(_mul(redex)->_1, s0__, r__);
            labeler(_mul(redex)->_2, s1__, r__);
            s__ = Simplify_theta_5[Simplify_mu_5_0[s0__]][Simplify_mu_5_1[s1__]]; } break;
         case a_EXP::tag_div: { 
            int s0__;
            int s1__;
            labeler(_div(redex)->_1, s0__, r__);
            labeler(_div(redex)->_2, s1__, r__);
            s__ = Simplify_theta_6[Simplify_mu_6_0[s0__]][Simplify_mu_6_1[s1__]]; } break;
         default: { 
            int s0__;
            labeler(_exp_list(redex)->exp_list, s0__, r__);
            s__ = 0;} break;
      }
   } else {s__ = 0;
   }
   const TreeTables::Rule * o__ = Simplify_accept_vector + Simplify_accept_base[s__];
accept__:
   switch (*o__) {
      case 15: if ((_num(_div(redex)->_1)->num == 0))
      {
#line 126 "rewriting.pcc"
         { redex = _div(redex)->_1; r__ = 1; goto replacement__; }
#line 126 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 14: if ((_num(_div(redex)->_2)->num == 0))
      {
#line 123 "rewriting.pcc"
       cout << "Division by zero!\n"; 
         div_by_zero++; 
         
#line 125 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 13: if ((_num(_div(redex)->_2)->num != 0))
      {
#line 122 "rewriting.pcc"
         { redex = num((_num(_div(redex)->_1)->num / _num(_div(redex)->_2)->num)); r__ = 1; goto replacement__; }
#line 122 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 12: {
#line 121 "rewriting.pcc"
         { redex = num((_num(_mul(redex)->_1)->num * _num(_mul(redex)->_2)->num)); r__ = 1; goto replacement__; }
#line 121 "rewriting.pcc"
} break;
      case 11: {
#line 120 "rewriting.pcc"
         { redex = num((_num(_sub(redex)->_1)->num - _num(_sub(redex)->_2)->num)); r__ = 1; goto replacement__; }
#line 120 "rewriting.pcc"
} break;
      case 10: {
#line 119 "rewriting.pcc"
         { redex = num((_num(_add(redex)->_1)->num + _num(_add(redex)->_2)->num)); r__ = 1; goto replacement__; }
#line 119 "rewriting.pcc"
} break;
      case 9: if ((_num(_div(redex)->_2)->num == 1))
      {
#line 118 "rewriting.pcc"
         { redex = _div(redex)->_1; r__ = 1; goto replacement__; }
#line 118 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 8: if ((_num(_mul(redex)->_1)->num == 2))
      {
#line 117 "rewriting.pcc"
         { redex = add(_mul(redex)->_2,_mul(redex)->_2); r__ = 1; goto replacement__; }
#line 117 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 7: if ((_num(_mul(redex)->_2)->num == 2))
      {
#line 116 "rewriting.pcc"
         { redex = add(_mul(redex)->_1,_mul(redex)->_1); r__ = 1; goto replacement__; }
#line 116 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 6: if ((_num(_mul(redex)->_1)->num == 1))
      {
#line 115 "rewriting.pcc"
         { redex = _mul(redex)->_2; r__ = 1; goto replacement__; }
#line 115 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 5: if ((_num(_mul(redex)->_2)->num == 1))
      {
#line 114 "rewriting.pcc"
         { redex = _mul(redex)->_1; r__ = 1; goto replacement__; }
#line 114 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 4: if ((_num(_mul(redex)->_1)->num == 0))
      {
#line 113 "rewriting.pcc"
         { redex = num(0); r__ = 1; goto replacement__; }
#line 113 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 3: if ((_num(_mul(redex)->_2)->num == 0))
      {
#line 112 "rewriting.pcc"
         { redex = num(0); r__ = 1; goto replacement__; }
#line 112 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 2: if ((_num(_sub(redex)->_2)->num == 0))
      {
#line 111 "rewriting.pcc"
         { redex = _sub(redex)->_1; r__ = 1; goto replacement__; }
#line 111 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 1: if ((_num(_add(redex)->_2)->num == 0))
      {
#line 110 "rewriting.pcc"
         { redex = _add(redex)->_1; r__ = 1; goto replacement__; }
#line 110 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
      case 0: if ((_num(_add(redex)->_1)->num == 0))
      {
#line 109 "rewriting.pcc"
         { redex = _add(redex)->_2; r__ = 1; goto replacement__; }
#line 109 "rewriting.pcc"
}
      else { ++o__; goto accept__; } break;
   }
   if (boxed(redex)) {
      redex->set_rewrite_state(s__);
   }
   
}

void  Simplify::labeler (EXP_LIST & redex, int& s__, int r__)
{
replacement__:
   int cached__;
   if (r__ && boxed(redex) && (cached__ = redex->get_rewrite_state()) != BURS::undefined_state)
   { s__ = cached__; return; }
   if ((redex)) {
      int s0__;
      int s1__;
      labeler(redex->_1, s0__, r__);
      labeler(redex->_2, s1__, r__);
      s__ = 3;
   } else {s__ = 1;
   }
   switch (s__) {
      case 1: {
#line 128 "rewriting.pcc"
        cout << "nil found\n"; 
#line 128 "rewriting.pcc"
} break;
      case 3: {
#line 127 "rewriting.pcc"
        cout << "list found\n"; 
#line 127 "rewriting.pcc"
} break;
   }
   if (boxed(redex)) {
      redex->set_rewrite_state(s__);
   }
   
}

#line 129 "rewriting.pcc"
#line 129 "rewriting.pcc"


//////////////////////////////////////////////////////////////////////////////
//  Instantiate the datatypes
//////////////////////////////////////////////////////////////////////////////
#line 134 "rewriting.pcc"
#line 134 "rewriting.pcc"
///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype EXP
///////////////////////////////////////////////////////////////////////////////
#line 134 "rewriting.pcc"


///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype EXP_LIST
///////////////////////////////////////////////////////////////////////////////
#line 134 "rewriting.pcc"


#line 134 "rewriting.pcc"
#line 134 "rewriting.pcc"


//////////////////////////////////////////////////////////////////////////////
//  Now defines the main program that uses all this stuff.
//////////////////////////////////////////////////////////////////////////////
int main()
{
   //
   // Instantiate a rewriting class 
   //
   Simplify sim;

   //
   // (0 + x * 2) / (1 * 5 + 1 * 3) / (0 / y);
   //
   EXP t1 = div(div(add(num(0), mul(var('x'),num(2))), 
                    add(mul(num(1), num(5)),mul(num(1),num(3)))),
                div(num(0),var('y')));
   EXP term = mul(t1,t1);

   //
   //  Rewrite the big term above.
   // 
   cout << "Before: " << term << '\n';
   sim(term);
   cout << "After: " << term << '\n';

   //
   //  Rewrite it again.  It should have no effect since the term
   //  is already in normal form.
   //
   sim(term);
   cout << "Again (should have no effect): " << term << '\n';

   //
   //  Rewrite some other term.
   //
   EXP term2 = add(sub(num(3),num(3)), var('z'));
   cout << "Before: " << term2 << '\n';
   sim(term2);
   cout << "After: " << term2 << '\n';

   //
   //  Rewrite some other term.
   //
   EXP term3 = div(num(1),num(0));
   sim(term3);

   //
   //  Rewrite some other term.
   //  Notice that even though the patterns do not involve `exp_list'
   //  directly the internal components of `exp_list' are still candidates
   //  for rewrites: rewriting operates on the entire tree, and not just
   //  on the cover like vanilla pattern matching.
   //
   EXP term4 = exp_list(
#line 189 "rewriting.pcc"
#line 189 "rewriting.pcc"
list_1_(div(num(1),num(0)),list_1_(var('x'),nil_1_))
#line 189 "rewriting.pcc"
#line 189 "rewriting.pcc"
);
   sim(term4);

   //
   //
   //  Set the terms to 'om' so that their storage is released.
   //
   t1 = term = term2 = term3 = term4 = om;
   if (div_by_zero != 6) { cerr << "BUG in rewriting!\n"; return 1; }
   if (balance != 0)     { cerr << "BUG in reference counting!\n"; return 1; }
   return 0;
}
#line 201 "rewriting.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 1
Number of ifs generated      = 3
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
