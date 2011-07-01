//////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.0.6),
//  last updated on Apr 5th, 1995.  Please be sure not to alter this file
//  directly.  Instead, refer to the original source file "hashcons2.pcc".
//////////////////////////////////////////////////////////////////////////////
#define PROP_REFERENCE_COUNTING_USED
#define PROP_HASH_CONSING_USED
#include <propinc.h>

#line 1 "hashcons2.pcc"
//
//  This is a simple (and useless) example for testing the hash cons feature
//  in Prop.
//
#include <iostream.h>
#include <new.h>

int balance = 0;

#line 10 "hashcons2.pcc"
////////////////////////////////////////////////////////////////////////
// Forward declarations for datatype EXP
////////////////////////////////////////////////////////////////////////
#ifndef datatype_EXP_defined
#define datatype_EXP_defined
   class a_EXP;
   typedef ConstRef<a_EXP> EXP;
#endif
class EXP_num;
class EXP_add;
class EXP_sub;
class EXP_mul;
class EXP_div;
////////////////////////////////////////////////////////////////////////
// Forward declarations for datatype LIST
////////////////////////////////////////////////////////////////////////
#ifndef datatype_LIST_defined
#define datatype_LIST_defined
   class a_LIST;
   typedef ConstRef<a_LIST> LIST;
#endif
////////////////////////////////////////////////////////////////////////
// Definition of datatype EXP
////////////////////////////////////////////////////////////////////////
class a_EXP : public RefObj  {
public:
   /////////////////////////////////////////////////////////////////
   //  Variant tags for datatype EXP
   /////////////////////////////////////////////////////////////////
#line 10 "hashcons2.pcc"
   enum Tag_EXP {
      tag_num = 0, tag_add = 1, tag_sub = 2, tag_mul = 3, tag_div = 4
   };

protected:
   /////////////////////////////////////////////////////////////////
   //  The variant tag and its constructor
   /////////////////////////////////////////////////////////////////
   const Tag_EXP tag;
   inline a_EXP(Tag_EXP t) : tag(t) {}
public:
   /////////////////////////////////////////////////////////////////
   //  Untagging and variant testing functions
   /////////////////////////////////////////////////////////////////
   inline int untag() const { return tag; }
   inline friend int boxed(EXP& x) { return 1; }
   inline friend int untag(EXP& x) { return x->tag; }
   /////////////////////////////////////////////////////////////////
   // Downcasting functions for datatype EXP
   /////////////////////////////////////////////////////////////////
   inline friend const EXP_num * _num(EXP& _x_) { return (const EXP_num *)_x_._raw(); }
   inline friend const EXP_add * _add(EXP& _x_) { return (const EXP_add *)_x_._raw(); }
   inline friend const EXP_sub * _sub(EXP& _x_) { return (const EXP_sub *)_x_._raw(); }
   inline friend const EXP_mul * _mul(EXP& _x_) { return (const EXP_mul *)_x_._raw(); }
   inline friend const EXP_div * _div(EXP& _x_) { return (const EXP_div *)_x_._raw(); }
public:
 
#line 15 "hashcons2.pcc"
  inline void * operator new    (size_t n) { balance++; cerr << '+'; return new char [n]; }
           inline void   operator delete (void * x) { balance--; cerr << '-'; delete [] ((char*)x); }
           ///////////////////////////////////////////////////////////////////////////
   //  Interface for hash consing
   ///////////////////////////////////////////////////////////////////////////
   friend Bool         equal(EXP, EXP);
   friend unsigned int hash (EXP);
   static a_EXP * make_hash_cons(a_EXP *);

   /////////////////////////////////////////////////////////////////
   //  Destructor
   /////////////////////////////////////////////////////////////////
   virtual ~a_EXP();
};


////////////////////////////////////////////////////////////////////////
// Subclass for implementing constructor 'num int ' of EXP 
////////////////////////////////////////////////////////////////////////
class EXP_num : public a_EXP {
public:
#line 10 "hashcons2.pcc"
   int num;
public:
   inline EXP_num(int _x_) 
      : a_EXP(a_EXP::tag_num), num(_x_) {}
   inline friend EXP num(int _x_) 
      { return a_EXP::make_hash_cons(new EXP_num (_x_)); }
   /////////////////////////////////////////////////////////////////
   //  Destructor
   /////////////////////////////////////////////////////////////////
   virtual ~EXP_num();
};


////////////////////////////////////////////////////////////////////////
// Subclass for implementing constructor 'add (EXP , EXP ) ' of EXP 
////////////////////////////////////////////////////////////////////////
class EXP_add : public a_EXP {
public:
#line 11 "hashcons2.pcc"
   EXP _1; EXP _2; 
public:
   inline EXP_add(EXP& _x_1, EXP& _x_2) 
      : a_EXP(a_EXP::tag_add), _1(_x_1), _2(_x_2) {}
   inline friend EXP add(EXP& _x_1, EXP& _x_2) 
      { return a_EXP::make_hash_cons(new EXP_add (_x_1, _x_2)); }
   /////////////////////////////////////////////////////////////////
   //  Destructor
   /////////////////////////////////////////////////////////////////
   virtual ~EXP_add();
};


////////////////////////////////////////////////////////////////////////
// Subclass for implementing constructor 'sub (EXP , EXP ) ' of EXP 
////////////////////////////////////////////////////////////////////////
class EXP_sub : public a_EXP {
public:
#line 12 "hashcons2.pcc"
   EXP _1; EXP _2; 
public:
   inline EXP_sub(EXP& _x_1, EXP& _x_2) 
      : a_EXP(a_EXP::tag_sub), _1(_x_1), _2(_x_2) {}
   inline friend EXP sub(EXP& _x_1, EXP& _x_2) 
      { return a_EXP::make_hash_cons(new EXP_sub (_x_1, _x_2)); }
   /////////////////////////////////////////////////////////////////
   //  Destructor
   /////////////////////////////////////////////////////////////////
   virtual ~EXP_sub();
};


////////////////////////////////////////////////////////////////////////
// Subclass for implementing constructor 'mul (EXP , EXP ) ' of EXP 
////////////////////////////////////////////////////////////////////////
class EXP_mul : public a_EXP {
public:
#line 13 "hashcons2.pcc"
   EXP _1; EXP _2; 
public:
   inline EXP_mul(EXP& _x_1, EXP& _x_2) 
      : a_EXP(a_EXP::tag_mul), _1(_x_1), _2(_x_2) {}
   inline friend EXP mul(EXP& _x_1, EXP& _x_2) 
      { return a_EXP::make_hash_cons(new EXP_mul (_x_1, _x_2)); }
   /////////////////////////////////////////////////////////////////
   //  Destructor
   /////////////////////////////////////////////////////////////////
   virtual ~EXP_mul();
};


////////////////////////////////////////////////////////////////////////
// Subclass for implementing constructor 'div (EXP , EXP ) ' of EXP 
////////////////////////////////////////////////////////////////////////
class EXP_div : public a_EXP {
public:
#line 14 "hashcons2.pcc"
   EXP _1; EXP _2; 
public:
   inline EXP_div(EXP& _x_1, EXP& _x_2) 
      : a_EXP(a_EXP::tag_div), _1(_x_1), _2(_x_2) {}
   inline friend EXP div(EXP& _x_1, EXP& _x_2) 
      { return a_EXP::make_hash_cons(new EXP_div (_x_1, _x_2)); }
   /////////////////////////////////////////////////////////////////
   //  Destructor
   /////////////////////////////////////////////////////////////////
   virtual ~EXP_div();
};

////////////////////////////////////////////////////////////////////////
// Definition of datatype LIST
////////////////////////////////////////////////////////////////////////
class a_LIST : public RefObj  {
public:
   /////////////////////////////////////////////////////////////////
   //  Untagging and variant testing functions
   /////////////////////////////////////////////////////////////////
   inline friend int boxed(LIST& x) { return x != 0; }
   inline friend int untag(LIST& x) { return x ? 1 : 0; }
#  define nil (LIST)0
#line 20 "hashcons2.pcc"
   EXP _1; LIST _2; 
public:
   inline a_LIST(EXP& _x_1, LIST& _x_2) : _1(_x_1), _2(_x_2) {}
   inline friend LIST list(EXP& _x_1, LIST& _x_2) 
      { return a_LIST::make_hash_cons(new a_LIST (_x_1, _x_2)); }
public:
 
#line 21 "hashcons2.pcc"
  inline void * operator new    (size_t n) { balance++; cerr << '>'; return new char [n]; }
           inline void   operator delete (void * x) { balance--; cerr << '<'; delete [] ((char*)x); }
           ///////////////////////////////////////////////////////////////////////////
   //  Interface for hash consing
   ///////////////////////////////////////////////////////////////////////////
   friend Bool         equal(LIST, LIST);
   friend unsigned int hash (LIST);
   static a_LIST * make_hash_cons(a_LIST *);

   /////////////////////////////////////////////////////////////////
   //  Destructor
   /////////////////////////////////////////////////////////////////
   virtual ~a_LIST();
};

#line 24 "hashcons2.pcc"


//
//  implement the datatypes.
//
#line 29 "hashcons2.pcc"
//////////////////////////////////////////////////////////////////////////////
//  Equality function for EXP
//  Shallow equality is assumed
//////////////////////////////////////////////////////////////////////////////
Bool equal(EXP _x_, EXP _y_)
{
   int _x_tag_ = untag(_x_);
   int _y_tag_ = untag(_y_);
   if (_x_tag_ != _y_tag_) return false;
   switch (_x_tag_) {
      case 0:
         if (_num(_x_)->num != _num(_y_)->num) return false;
      break;
      case 1:
         if (_add(_x_)->_2 != _add(_y_)->_2) return false;
         if (_add(_x_)->_1 != _add(_y_)->_1) return false;
      break;
      case 2:
         if (_sub(_x_)->_2 != _sub(_y_)->_2) return false;
         if (_sub(_x_)->_1 != _sub(_y_)->_1) return false;
      break;
      case 3:
         if (_mul(_x_)->_2 != _mul(_y_)->_2) return false;
         if (_mul(_x_)->_1 != _mul(_y_)->_1) return false;
      break;
      case 4:
         if (_div(_x_)->_2 != _div(_y_)->_2) return false;
         if (_div(_x_)->_1 != _div(_y_)->_1) return false;
      break;
   }
   return true;
}

//////////////////////////////////////////////////////////////////////////////
//  Hashing function for EXP
//  Shallow hashing is used
//////////////////////////////////////////////////////////////////////////////
unsigned int hash(EXP _x_)
{
   unsigned int _h_;
   switch (_h_ = untag(_x_)) {
      case 0:
         _h_ = hash(_num(_x_)->num);
      break;
      case 1:
         _h_ += (unsigned int)(_add(_x_)->_1);
         _h_ += (unsigned int)(_add(_x_)->_2);
      break;
      case 2:
         _h_ += (unsigned int)(_sub(_x_)->_1);
         _h_ += (unsigned int)(_sub(_x_)->_2);
      break;
      case 3:
         _h_ += (unsigned int)(_mul(_x_)->_1);
         _h_ += (unsigned int)(_mul(_x_)->_2);
      break;
      case 4:
         _h_ += (unsigned int)(_div(_x_)->_1);
         _h_ += (unsigned int)(_div(_x_)->_2);
      break;
   }
   return _h_;
}

//////////////////////////////////////////////////////////////////////////////
//  Hash consing implementation for EXP
//////////////////////////////////////////////////////////////////////////////
static LHashTable<EXP, EXP> EXP_universe;
a_EXP * a_EXP::make_hash_cons(a_EXP * _x_)
{  EXP _r_(_x_);
   Ix i = EXP_universe.lookup(_r_);
   if (i == 0) { EXP_universe.insert(_r_,_r_); return _x_; }
   else        { return EXP_universe.value(i)._pin(); }
}

////////////////////////////////////////////////////////////////////
//  Destructor(s) for class EXP
////////////////////////////////////////////////////////////////////
#line 29 "hashcons2.pcc"
a_EXP::~a_EXP() {}
EXP_num::~EXP_num() {}
EXP_add::~EXP_add() {}
EXP_sub::~EXP_sub() {}
EXP_mul::~EXP_mul() {}
EXP_div::~EXP_div() {}
//////////////////////////////////////////////////////////////////////////////
//  Equality function for LIST
//  Shallow equality is assumed
//////////////////////////////////////////////////////////////////////////////
Bool equal(LIST _x_, LIST _y_)
{
   int _x_tag_ = untag(_x_);
   int _y_tag_ = untag(_y_);
   if (_x_tag_ != _y_tag_) return false;
   switch (_x_tag_) {
      case 0:
      break;
      case 1:
         if ((_x_)->_2 != (_y_)->_2) return false;
         if ((_x_)->_1 != (_y_)->_1) return false;
      break;
   }
   return true;
}

//////////////////////////////////////////////////////////////////////////////
//  Hashing function for LIST
//  Shallow hashing is used
//////////////////////////////////////////////////////////////////////////////
unsigned int hash(LIST _x_)
{
   unsigned int _h_;
   switch (_h_ = untag(_x_)) {
      case 0:
         _h_ = (unsigned int)_x_;
      break;
      case 1:
         _h_ += (unsigned int)((_x_)->_1);
         _h_ += (unsigned int)((_x_)->_2);
      break;
   }
   return _h_;
}

//////////////////////////////////////////////////////////////////////////////
//  Hash consing implementation for LIST
//////////////////////////////////////////////////////////////////////////////
static LHashTable<LIST, LIST> LIST_universe;
a_LIST * a_LIST::make_hash_cons(a_LIST * _x_)
{  LIST _r_(_x_);
   Ix i = LIST_universe.lookup(_r_);
   if (i == 0) { LIST_universe.insert(_r_,_r_); return _x_; }
   else        { return LIST_universe.value(i)._pin(); }
}

////////////////////////////////////////////////////////////////////
//  Destructor(s) for class LIST
////////////////////////////////////////////////////////////////////
#line 29 "hashcons2.pcc"
a_LIST::~a_LIST() {}
#line 29 "hashcons2.pcc"
 

ostream& operator << (ostream& f, EXP e)
{
   
#line 33 "hashcons2.pcc"
{ switch (e->untag()) {
case a_EXP::tag_num: {
#line 34 "hashcons2.pcc"
 return f << (_num(e)->num); } break;
case a_EXP::tag_add: {
#line 35 "hashcons2.pcc"
 return f << '(' << (_add(e))->_1 << " + " << (_add(e))->_2 << ')'; } break;
case a_EXP::tag_sub: {
#line 36 "hashcons2.pcc"
 return f << '(' << (_sub(e))->_1 << " - " << (_sub(e))->_2 << ')'; } break;
case a_EXP::tag_mul: {
#line 37 "hashcons2.pcc"
 return f << '(' << (_mul(e))->_1 << " * " << (_mul(e))->_2 << ')'; } break;
default:; {
#line 38 "hashcons2.pcc"
 return f << '(' << (_div(e))->_1 << " / " << (_div(e))->_2 << ')'; }
} }

#line 39 "hashcons2.pcc"

}

ostream& operator << (ostream& f, LIST l)
{
   
#line 44 "hashcons2.pcc"
{ if (l) {
if ((l)->_2) {
{
#line 47 "hashcons2.pcc"
     return f << (l)->_1 << ',' << (l)->_2;
   }} else {
{
#line 46 "hashcons2.pcc"
   return f << (l)->_1;
      }}
} else {
{
#line 45 "hashcons2.pcc"
           return f;
      }}
}

#line 48 "hashcons2.pcc"

}

void do_something()
{
   cout << "Balance = " << balance << '\n'
        << "EXP  hash table size = " << EXP_universe.size() << '\n'
        << "LIST hash table size = " << LIST_universe.size() << '\n';
   EXP e1 = mul(add(num(1),num(2)), add(num(2), num(3)));
   EXP e2 = mul(add(num(1),num(2)), add(num(2), num(3)));
   LIST l1 = list(e1, list(e2, nil));
   cout << l1 << '\n';
   cout << ((e1 == e2) ? "Good!\n" : "Bad boy! Naughty, naughty boy!\n");
   cout << ((num(1) == num(1)) ? "Good!\n" : "Bad boy! Naughty, naughty boy!\n");
   cout << ((num(1) != num(2)) ? "Good!\n" : "Bad boy! Naughty, naughty boy!\n");
   cout << ((add(e1,e2) == add(e1,e2)) ? "Good!\n" : "Bad boy! Naughty, naughty boy!\n");
   cout << ((add(e1,e2) != add(e1,num(2))) ? "Good!\n" : "Bad boy! Naughty, naughty boy!\n");
   cout << "Balance = " << balance << '\n'
        << "EXP  hash table size = " << EXP_universe.size() << '\n'
        << "LIST hash table size = " << LIST_universe.size() << '\n';
}

int main() 
{
   do_something();
   cout << "Balance = " << balance << '\n'
        << "EXP  hash table size = " << EXP_universe.size() << '\n'
        << "LIST hash table size = " << LIST_universe.size() << '\n';
   return 0;
}
/*
----------------------------- Statistics -------------------------------
Number of decision nodes merged = 0
Number of switches generated    = 1
Number of ifs      generated    = 2
Number of labels   generated    = 0
Number of gotos    generated    = 0
Number of temporary variables   = 0
------------------------------------------------------------------------
*/
