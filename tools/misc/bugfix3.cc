///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.0),
//  last updated on Feb 16, 1997.
//  The original source file is "bugfix3.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_QUARK_USED
#include <propdefs.h>
#line 1 "bugfix3.pcc"
//
//  Testing the rewriting features
//
#include <iostream.h>

#line 6 "bugfix3.pcc"
#line 11 "bugfix3.pcc"
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
   class EXP_add;	// subclass for 'add (EXP, EXP)'
   class EXP_sub;	// subclass for 'sub (EXP, EXP)'
   class EXP_mul;	// subclass for 'mul (EXP, EXP)'
   class EXP_div;	// subclass for 'div (EXP, EXP)'

///////////////////////////////////////////////////////////////////////////////
// Base class for datatype 'EXP'
///////////////////////////////////////////////////////////////////////////////
class a_EXP {
public:
   enum Tag_EXP {
      tag_num = 0, tag_add = 1, tag_sub = 2, tag_mul = 3, 
      tag_div = 4
   };

protected:
   const Tag_EXP _tag_;
   inline a_EXP(Tag_EXP _t_) : _tag_(_t_) {}
public:
   inline int untag() const { return _tag_; }
   inline friend int boxed(const a_EXP * x) { return 1; }
   inline friend int untag(const a_EXP * x) { return x->_tag_; }
   ////////////////////////////////////////////////////////////////////////////
   // Downcasting functions for EXP
   ////////////////////////////////////////////////////////////////////////////
   inline friend EXP_num * _num(EXP _x_) { return (EXP_num *)_x_; }
   inline friend EXP_add * _add(EXP _x_) { return (EXP_add *)_x_; }
   inline friend EXP_sub * _sub(EXP _x_) { return (EXP_sub *)_x_; }
   inline friend EXP_mul * _mul(EXP _x_) { return (EXP_mul *)_x_; }
   inline friend EXP_div * _div(EXP _x_) { return (EXP_div *)_x_; }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::num int'
///////////////////////////////////////////////////////////////////////////////
class EXP_num : public a_EXP {
public:
#line 6 "bugfix3.pcc"
   int num; 
   inline EXP_num (int _xnum)
      : a_EXP(a_EXP::tag_num), num(_xnum) {}
   inline friend a_EXP * num (int _xnum)
      { return new EXP_num (_xnum); }
};

///////////////////////////////////////////////////////////////////////////////
// class for constructor 'EXP::add (EXP, EXP)'
///////////////////////////////////////////////////////////////////////////////
class EXP_add : public a_EXP {
public:
#line 7 "bugfix3.pcc"
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
#line 8 "bugfix3.pcc"
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
#line 9 "bugfix3.pcc"
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
#line 10 "bugfix3.pcc"
   EXP _1; EXP _2; 
   inline EXP_div (EXP _x1, EXP _x2)
      : a_EXP(a_EXP::tag_div), _1(_x1), _2(_x2) {}
   inline friend a_EXP * div (EXP _x1, EXP _x2)
      { return new EXP_div (_x1, _x2); }
};

#line 11 "bugfix3.pcc"
#line 11 "bugfix3.pcc"


#line 13 "bugfix3.pcc"
#line 13 "bugfix3.pcc"
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
private:
};
#line 13 "bugfix3.pcc"
#line 13 "bugfix3.pcc"



#line 16 "bugfix3.pcc"
#line 31 "bugfix3.pcc"
static const TreeTables::Offset Simplify_accept_base [ 12 ] = {
   0, 0, 1, 3, 7, 9, 11, 14, 18, 26, 30, 32
};
static const TreeTables::Rule Simplify_accept_vector [ 35 ] = {
   -1, 1, -1, 0, 1, 10, -1, 0, -1, 2, -1, 2, 11, -1, 3, 5, 
   7, -1, 3, 4, 5, 6, 7, 8, 12, -1, 4, 6, 8, -1, 9, -1, 
   9, 13, -1
};
static const TreeTables::State Simplify_theta_1[2][2] = {
   { 0, 2 },
   { 4, 3 }
};


static const TreeTables::State Simplify_theta_2[2][2] = {
   { 0, 5 },
   { 0, 6 }
};


static const TreeTables::State Simplify_theta_3[2][2] = {
   { 0, 7 },
   { 9, 8 }
};


static const TreeTables::State Simplify_theta_4[2][2] = {
   { 0, 10 },
   { 0, 11 }
};


static const TreeTables::State Simplify_mu_1_0[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_1_1[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_2_0[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_2_1[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_3_0[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_3_1[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_4_0[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Simplify_mu_4_1[12] = {
   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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
   switch(redex->untag()) {
      case a_EXP::tag_num: { 
         int s0__;
         s0__ = 0; // int
         s__ = 1;} break;
      case a_EXP::tag_add: { 
         int s0__;
         int s1__;
         labeler(_add(redex)->_1, s0__, r__);
         labeler(_add(redex)->_2, s1__, r__);
         s__ = Simplify_theta_1[Simplify_mu_1_0[s0__]][Simplify_mu_1_1[s1__]]; } break;
      case a_EXP::tag_sub: { 
         int s0__;
         int s1__;
         labeler(_sub(redex)->_1, s0__, r__);
         labeler(_sub(redex)->_2, s1__, r__);
         s__ = Simplify_theta_2[Simplify_mu_2_0[s0__]][Simplify_mu_2_1[s1__]]; } break;
      case a_EXP::tag_mul: { 
         int s0__;
         int s1__;
         labeler(_mul(redex)->_1, s0__, r__);
         labeler(_mul(redex)->_2, s1__, r__);
         s__ = Simplify_theta_3[Simplify_mu_3_0[s0__]][Simplify_mu_3_1[s1__]]; } break;
      default: { 
         int s0__;
         int s1__;
         labeler(_div(redex)->_1, s0__, r__);
         labeler(_div(redex)->_2, s1__, r__);
         s__ = Simplify_theta_4[Simplify_mu_4_0[s0__]][Simplify_mu_4_1[s1__]]; } break;
   }
   const TreeTables::Rule * o__ = Simplify_accept_vector + Simplify_accept_base[s__];
accept__:
   switch (*o__) {
      case 13: {
#line 30 "bugfix3.pcc"
        num(_num(_div(redex)->_1)->num / _num(_div(redex)->_2)->num);
#line 31 "bugfix3.pcc"
} break;
      case 12: {
#line 29 "bugfix3.pcc"
        num(_num(_mul(redex)->_1)->num * _num(_mul(redex)->_2)->num);
         
#line 30 "bugfix3.pcc"
} break;
      case 11: {
#line 28 "bugfix3.pcc"
        num(_num(_sub(redex)->_1)->num - _num(_sub(redex)->_2)->num);
         
#line 29 "bugfix3.pcc"
} break;
      case 10: {
#line 27 "bugfix3.pcc"
        num(_num(_add(redex)->_1)->num + _num(_add(redex)->_2)->num);
         
#line 28 "bugfix3.pcc"
} break;
      case 9: if ((_num(_div(redex)->_2)->num == 1))
      {
#line 26 "bugfix3.pcc"
    _div(redex)->_1; 
         
#line 27 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 8: if ((_num(_mul(redex)->_1)->num == 2))
      {
#line 25 "bugfix3.pcc"
    add(_mul(redex)->_2,_mul(redex)->_2);
         
#line 26 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 7: if ((_num(_mul(redex)->_2)->num == 2))
      {
#line 24 "bugfix3.pcc"
    add(_mul(redex)->_1,_mul(redex)->_1);
         
#line 25 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 6: if ((_num(_mul(redex)->_1)->num == 1))
      {
#line 23 "bugfix3.pcc"
    _mul(redex)->_2;
         
#line 24 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 5: if ((_num(_mul(redex)->_2)->num == 1))
      {
#line 22 "bugfix3.pcc"
    _mul(redex)->_1;
         
#line 23 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 4: if ((_num(_mul(redex)->_1)->num == 0))
      {
#line 21 "bugfix3.pcc"
    num(0); 
         
#line 22 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 3: if ((_num(_mul(redex)->_2)->num == 0))
      {
#line 20 "bugfix3.pcc"
    num(0); 
         
#line 21 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 2: if ((_num(_sub(redex)->_2)->num == 0))
      {
#line 19 "bugfix3.pcc"
    _sub(redex)->_1; 
         
#line 20 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 1: if ((_num(_add(redex)->_2)->num == 0))
      {
#line 18 "bugfix3.pcc"
    _add(redex)->_1; 
         
#line 19 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
      case 0: if ((_num(_add(redex)->_1)->num == 0))
      {
#line 17 "bugfix3.pcc"
    _add(redex)->_2;
         
#line 18 "bugfix3.pcc"
}
      else { ++o__; goto accept__; } break;
   }
   
}

#line 31 "bugfix3.pcc"
#line 31 "bugfix3.pcc"


#line 33 "bugfix3.pcc"
#line 35 "bugfix3.pcc"
///////////////////////////////////////////////////////////////////////////////
// Forward class definition for NAT
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_NAT_defined
#define datatype_NAT_defined
   typedef class a_NAT * NAT;
#endif

///////////////////////////////////////////////////////////////////////////////
// Class hierarchy for datatype NAT
///////////////////////////////////////////////////////////////////////////////
class a_NAT; // base class for datatype NAT

///////////////////////////////////////////////////////////////////////////////
// Base class for datatype 'NAT'
///////////////////////////////////////////////////////////////////////////////
class a_NAT {
public:
#  define zero (NAT)0
   inline friend int boxed(const a_NAT * x) { return x != 0; }
   inline friend int untag(const a_NAT * x) { return x ? 1 : 0; }
#line 34 "bugfix3.pcc"
   NAT succ; 
   inline a_NAT (NAT _xsucc)
      : succ(_xsucc) {}
   inline friend a_NAT * succ (NAT _xsucc)
      { return new a_NAT (_xsucc); }
};

#line 35 "bugfix3.pcc"
#line 35 "bugfix3.pcc"


#line 37 "bugfix3.pcc"
#line 39 "bugfix3.pcc"
class Number : public BURS {
private:
   Number(const Number&);               // no copy constructor
   void operator = (const Number&); // no assignment
public:
   struct Number_StateRec * stack__, * stack_top__;
public:
   void labeler(const char *, int&, int);
   void labeler(Quark, int&, int);
          void  labeler(NAT & redex, int&, int);
   inline virtual void  operator () (NAT & redex) { int s; labeler(redex,s,0); }
          void  labeler(EXP & redex, int&, int);
   inline virtual void  operator () (EXP & redex) { int s; labeler(redex,s,0); }
private:
#line 38 "bugfix3.pcc"
 
#line 39 "bugfix3.pcc"
};
#line 39 "bugfix3.pcc"
#line 39 "bugfix3.pcc"


#line 41 "bugfix3.pcc"
#line 51 "bugfix3.pcc"
static const TreeTables::State Number_theta_1[6] = {
   2, 4, 5, 10, 11, 12
};


static const TreeTables::State Number_theta_3[2][2] = {
   { 0, 0 },
   { 0, 6 }
};


static const TreeTables::State Number_theta_4[2][2] = {
   { 0, 0 },
   { 0, 7 }
};


static const TreeTables::State Number_theta_5[2][2] = {
   { 0, 0 },
   { 0, 8 }
};


static const TreeTables::State Number_theta_6[2][2] = {
   { 0, 0 },
   { 0, 9 }
};


static const TreeTables::State Number_mu_1_0[13] = {
   0, 1, 2, 0, 3, 4, 0, 0, 0, 0, 4, 5, 5
};


static const TreeTables::State Number_mu_3_0[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Number_mu_3_1[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Number_mu_4_0[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Number_mu_4_1[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Number_mu_5_0[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Number_mu_5_1[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Number_mu_6_0[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


static const TreeTables::State Number_mu_6_1[13] = {
   0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


inline void  Number::labeler(char const * redex,int& s__,int)
{
   {
s__ = 0;
   }
}

inline void  Number::labeler(Quark redex,int& s__,int)
{
   {
s__ = 0;
   }
}

void  Number::labeler (EXP & redex, int& s__, int r__)
{
replacement__:
   switch(redex->untag()) {
      case a_EXP::tag_num: { 
         int s0__;
         s0__ = 0; // int
         s__ = 3;} break;
      case a_EXP::tag_add: { 
         int s0__;
         int s1__;
         labeler(_add(redex)->_1, s0__, r__);
         labeler(_add(redex)->_2, s1__, r__);
         s__ = Number_theta_3[Number_mu_3_0[s0__]][Number_mu_3_1[s1__]]; } break;
      case a_EXP::tag_sub: { 
         int s0__;
         int s1__;
         labeler(_sub(redex)->_1, s0__, r__);
         labeler(_sub(redex)->_2, s1__, r__);
         s__ = Number_theta_4[Number_mu_4_0[s0__]][Number_mu_4_1[s1__]]; } break;
      case a_EXP::tag_mul: { 
         int s0__;
         int s1__;
         labeler(_mul(redex)->_1, s0__, r__);
         labeler(_mul(redex)->_2, s1__, r__);
         s__ = Number_theta_5[Number_mu_5_0[s0__]][Number_mu_5_1[s1__]]; } break;
      default: { 
         int s0__;
         int s1__;
         labeler(_div(redex)->_1, s0__, r__);
         labeler(_div(redex)->_2, s1__, r__);
         s__ = Number_theta_6[Number_mu_6_0[s0__]][Number_mu_6_1[s1__]]; } break;
   }
   switch (s__) {
      case 9: {
#line 50 "bugfix3.pcc"
        num(_num(_div(redex)->_1)->num / _num(_div(redex)->_2)->num);
#line 51 "bugfix3.pcc"
} break;
      case 8: {
#line 49 "bugfix3.pcc"
        num(_num(_mul(redex)->_1)->num * _num(_mul(redex)->_2)->num);
         
#line 50 "bugfix3.pcc"
} break;
      case 7: {
#line 48 "bugfix3.pcc"
        num(_num(_sub(redex)->_1)->num - _num(_sub(redex)->_2)->num);
         
#line 49 "bugfix3.pcc"
} break;
      case 6: {
#line 47 "bugfix3.pcc"
        num(_num(_add(redex)->_1)->num + _num(_add(redex)->_2)->num);
         
#line 48 "bugfix3.pcc"
} break;
   }
   
}

void  Number::labeler (NAT & redex, int& s__, int r__)
{
replacement__:
   if ((redex)) {
      int s0__;
      labeler(redex->succ, s0__, r__);
      s__ = Number_theta_1[Number_mu_1_0[s0__]]; 
   } else {s__ = 1;
   }
   switch (s__) {
      case 12: 
      case 11: 
      case 10: 
      case 5: {
#line 44 "bugfix3.pcc"
        
         
#line 45 "bugfix3.pcc"
} break;
      case 4: {
#line 43 "bugfix3.pcc"
        
         
#line 44 "bugfix3.pcc"
} break;
      case 1: {
#line 42 "bugfix3.pcc"
         
         
#line 43 "bugfix3.pcc"
} break;
   }
   
}

#line 51 "bugfix3.pcc"
#line 51 "bugfix3.pcc"

#line 52 "bugfix3.pcc"
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
