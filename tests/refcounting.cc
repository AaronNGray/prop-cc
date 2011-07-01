///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.1.4),
//  last updated on September 8, 1995.
//  The original source file is "refcounting.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REFCOUNT_USED
#include <propdefs.h>
#line 1 "refcounting.pcc"
//
//  Simple example to test reference counting.
//

#include <new.h>
#include <iostream.h>

int balance = 0;

//
//  Define an algebraic datatype.
//
#line 13 "refcounting.pcc"
#line 28 "refcounting.pcc"
///////////////////////////////////////////////////////////////////////////////
// Forward class definition for EXP
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_EXP_defined
#define datatype_EXP_defined
   typedef class a_EXP * EXP;
#endif

///////////////////////////////////////////////////////////////////////////////
// Class hierarchy for datatype EXP
///////////////////////////////////////////////////////////////////////////////
class a_EXP; // base class for datatype EXP
   class EXP_num;	// subclass for 'num int'
   class EXP_var;	// subclass for 'var char'
   class EXP_add;	// subclass for 'add (EXP, EXP)'
   class EXP_sub;	// subclass for 'sub (EXP, EXP)'
   class EXP_mul;	// subclass for 'mul (EXP, EXP)'
   class EXP_div;	// subclass for 'div (EXP, EXP)'

///////////////////////////////////////////////////////////////////////////////
// Base class for datatype 'EXP'
///////////////////////////////////////////////////////////////////////////////
class a_EXP {
public:
#  define om (EXP)0
   enum Tag_EXP {
      tag_num = 0, tag_var = 1, tag_add = 2, tag_sub = 3, 
      tag_mul = 4, tag_div = 5
   };

protected:
   const Tag_EXP _tag_;
   inline a_EXP(Tag_EXP _t_) : _tag_(_t_) {}
public:
   inline int untag() const { return _tag_; }
   inline friend int boxed(const a_EXP * x) { return x != 0; }
   inline friend int untag(const a_EXP * x) { return x ? (x->_tag_+1) : 0; }
   ////////////////////////////////////////////////////////////////////////////
   // Downcasting functions for EXP
   ////////////////////////////////////////////////////////////////////////////
   inline friend EXP_num * _num(EXP _x_) { return (EXP_num *)_x_; }
   inline friend EXP_var * _var(EXP _x_) { return (EXP_var *)_x_; }
   inline friend EXP_add * _add(EXP _x_) { return (EXP_add *)_x_; }
   inline friend EXP_sub * _sub(EXP _x_) { return (EXP_sub *)_x_; }
   inline friend EXP_mul * _mul(EXP _x_) { return (EXP_mul *)_x_; }
   inline friend EXP_div * _div(EXP _x_) { return (EXP_div *)_x_; }
#line 21 "refcounting.pcc"
 
   // Redefine the new/delete operators to keep track of 
   // allocation and deallocation.
   inline void * operator new    (size_t n) 
      { balance++; return new char [n]; }
   inline void   operator delete (void * x) 
      { balance--; delete [] ((char*)x); }
   
#line 28 "refcounting.pcc"
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::num int'
///////////////////////////////////////////////////////////////////////////////
class EXP_num : public a_EXP {
public:
#line 14 "refcounting.pcc"
   int num; 
   inline EXP_num (int _xnum)
      : a_EXP(a_EXP::tag_num), num(_xnum) {}
   inline friend a_EXP * num (int _xnum)
      { return new EXP_num (_xnum); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::var char'
///////////////////////////////////////////////////////////////////////////////
class EXP_var : public a_EXP {
public:
#line 15 "refcounting.pcc"
   char var; 
   inline EXP_var (char _xvar)
      : a_EXP(a_EXP::tag_var), var(_xvar) {}
   inline friend a_EXP * var (char _xvar)
      { return new EXP_var (_xvar); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::add (EXP, EXP)'
///////////////////////////////////////////////////////////////////////////////
class EXP_add : public a_EXP {
public:
#line 16 "refcounting.pcc"
   EXP _1; EXP _2; 
   inline EXP_add (EXP _x1, EXP _x2)
      : a_EXP(a_EXP::tag_add), _1(_x1), _2(_x2) {}
   inline friend a_EXP * add (EXP _x1, EXP _x2)
      { return new EXP_add (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::sub (EXP, EXP)'
///////////////////////////////////////////////////////////////////////////////
class EXP_sub : public a_EXP {
public:
#line 17 "refcounting.pcc"
   EXP _1; EXP _2; 
   inline EXP_sub (EXP _x1, EXP _x2)
      : a_EXP(a_EXP::tag_sub), _1(_x1), _2(_x2) {}
   inline friend a_EXP * sub (EXP _x1, EXP _x2)
      { return new EXP_sub (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::mul (EXP, EXP)'
///////////////////////////////////////////////////////////////////////////////
class EXP_mul : public a_EXP {
public:
#line 18 "refcounting.pcc"
   EXP _1; EXP _2; 
   inline EXP_mul (EXP _x1, EXP _x2)
      : a_EXP(a_EXP::tag_mul), _1(_x1), _2(_x2) {}
   inline friend a_EXP * mul (EXP _x1, EXP _x2)
      { return new EXP_mul (_x1, _x2); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::div (EXP, EXP)'
///////////////////////////////////////////////////////////////////////////////
class EXP_div : public a_EXP {
public:
#line 19 "refcounting.pcc"
   EXP _1; EXP _2; 
   inline EXP_div (EXP _x1, EXP _x2)
      : a_EXP(a_EXP::tag_div), _1(_x1), _2(_x2) {}
   inline friend a_EXP * div (EXP _x1, EXP _x2)
      { return new EXP_div (_x1, _x2); }
};

#line 28 "refcounting.pcc"
#line 28 "refcounting.pcc"


//
//  Define a method that prints an expression.  This is simple
//  inductive definition
//
ostream& operator << (ostream& f, EXP e)
{  
#line 35 "refcounting.pcc"
#line 42 "refcounting.pcc"
{
   if (e) {
      switch (e->untag()) {
         case a_EXP::tag_num: {
#line 37 "refcounting.pcc"
           return f << _num(e)->num; 
#line 37 "refcounting.pcc"
            } break;
         case a_EXP::tag_var: {
#line 38 "refcounting.pcc"
           return f << _var(e)->var; 
#line 38 "refcounting.pcc"
            } break;
         case a_EXP::tag_add: {
#line 39 "refcounting.pcc"
           return f << '(' << _add(e)->_1 << " + " << _add(e)->_2 << ')'; 
#line 39 "refcounting.pcc"
            } break;
         case a_EXP::tag_sub: {
#line 40 "refcounting.pcc"
           return f << '(' << _sub(e)->_1 << " - " << _sub(e)->_2 << ')'; 
#line 40 "refcounting.pcc"
            } break;
         case a_EXP::tag_mul: {
#line 41 "refcounting.pcc"
           return f << '(' << _mul(e)->_1 << " * " << _mul(e)->_2 << ')'; 
#line 41 "refcounting.pcc"
            } break;
         default: {
#line 42 "refcounting.pcc"
           return f << '(' << _div(e)->_1 << " / " << _div(e)->_2 << ')'; 
#line 42 "refcounting.pcc"
            } break;
      }
   } else {
#line 36 "refcounting.pcc"
     return f << "om"; 
#line 36 "refcounting.pcc"
   }
}
#line 43 "refcounting.pcc"
#line 43 "refcounting.pcc"

}

//
//  Change all occurance of var(...) to t
//
void change (EXP& e, EXP t)
{  
#line 50 "refcounting.pcc"
#line 57 "refcounting.pcc"
{
   if (e) {
      switch (e->untag()) {
         case a_EXP::tag_num: {
#line 52 "refcounting.pcc"
           e = add(e,add(e,e)); 
#line 52 "refcounting.pcc"
            } break;
         case a_EXP::tag_var: {
#line 53 "refcounting.pcc"
           e = t; 
#line 53 "refcounting.pcc"
            } break;
         case a_EXP::tag_add: {
#line 54 "refcounting.pcc"
           change(_add(e)->_1,t); change(_add(e)->_2,t); 
#line 54 "refcounting.pcc"
            } break;
         case a_EXP::tag_sub: {
#line 55 "refcounting.pcc"
           change(_sub(e)->_1,t); change(_sub(e)->_2,t); 
#line 55 "refcounting.pcc"
            } break;
         case a_EXP::tag_mul: {
#line 56 "refcounting.pcc"
           change(_mul(e)->_1,t); change(_mul(e)->_2,t); 
#line 56 "refcounting.pcc"
            } break;
         default: {
#line 57 "refcounting.pcc"
           change(_div(e)->_1,t); change(_div(e)->_2,t); 
#line 57 "refcounting.pcc"
            } break;
      }
   } else {}
}
#line 58 "refcounting.pcc"
#line 58 "refcounting.pcc"

}

//
// Instantiate the datatype EXP
//
#line 64 "refcounting.pcc"
#line 64 "refcounting.pcc"
#line 64 "refcounting.pcc"
#line 64 "refcounting.pcc"


//
//  Now defines the main program that uses all this stuff.
//
int main()
{
   //
   // (0 + x * 2) / (1 * 5 + 1 * 3) / (0 / y);
   //
   EXP t1   = div(div(add(num(0), mul(var('x'),num(2))), 
                      add(mul(num(1), num(5)),mul(num(1),num(3)))),
                  div(num(0),var('y')));
   EXP t2   = add(t1,t1);
   EXP term = div(mul(t2,t2),t2);
   t2       = om;

   cout << "[1] " << term << '\n';
   cout << "Balance = " << balance << '\n';

   change(term,num(-2));
   cout << "[2] " << term << '\n';
   cout << "Balance = " << balance << '\n';

   term = t1; t1 = num(-1);
   cout << "[3] " << term << '\n';
   cout << "Balance = " << balance << '\n';

   if (balance != 5597) {
      cerr << "Bug in reference counting.\n";
      return 1;
   }

   term = om; t1 = om;
   cout << "[4] " << term << '\n';
   cout << "Balance = " << balance << '\n';

   if (balance != 0) {
      cerr << "Bug in reference counting.\n";
      return 1;
   } else {
      cerr << "Reference counting is OK.\n";
      return 0;
   }
}
#line 109 "refcounting.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 2
Number of switches generated = 2
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
