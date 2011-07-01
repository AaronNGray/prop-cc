//////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.0 (pre-beta)),
//  last updated on Jan 4th, 1995.  Please be sure not to alter this file
//  directly.  Instead, refer to the original source file "tri.pcc".
//////////////////////////////////////////////////////////////////////////////
#define PROP_RETE_USED
#include <propinc.h>
#line 1 "tri.pcc"
//////////////////////////////////////////////////////////////////////////////
//  This is a simple self-contained test to benchmark the speed of
//  naive inferencing in Prop.
//
//  To compile on Unix:
//
//     prop triangle.pcc
//     gcc -I<prop-include-dir> triangle.cc -o triangle -L<ADLib-library-dir>
//         -lad -liostream -lg++
//////////////////////////////////////////////////////////////////////////////

#include <iostream.h>

#line 14 "tri.pcc"
////////////////////////////////////////////////////////////////////////
// Forward declarations for datatype Number
////////////////////////////////////////////////////////////////////////
#ifndef datatype_Number_defined
#define datatype_Number_defined
   class a_Number;
   typedef a_Number * Number;
#endif
class Number_num;
class Number_limit;
////////////////////////////////////////////////////////////////////////
// Definition of datatype Number
////////////////////////////////////////////////////////////////////////
class a_Number : public Fact {
public:
   /////////////////////////////////////////////////////////////////
   //  Variant tags for datatype Number
   /////////////////////////////////////////////////////////////////
   enum Tag_Number {
      tag_num = 0, tag_limit = 1
   };

protected:
   /////////////////////////////////////////////////////////////////
   //  The variant tag and its constructor
   /////////////////////////////////////////////////////////////////
   const Tag_Number tag;
   inline a_Number(Tag_Number t) : tag(t) {}
public:
   /////////////////////////////////////////////////////////////////
   //  Untagging and variant testing functions
   /////////////////////////////////////////////////////////////////
   inline int untag() const { return tag; }
   inline friend int boxed(Number x) { return 1; }
   inline friend int untag(Number x) { return x->tag; }
   /////////////////////////////////////////////////////////////////
   // Downcasting functions for datatype Number
   /////////////////////////////////////////////////////////////////
   inline friend Number_num * _num(a_Number * _x_) { return (Number_num *)_x_; }
   inline friend Number_limit * _limit(a_Number * _x_) { return (Number_limit *)_x_; }
///////////////////////////////////////////////////////////////////////
//  Additional interface methods for relation type Number:
///////////////////////////////////////////////////////////////////////
public:
   static  RelTag relation_tag;
   virtual RelTag get_tag() const;
   inline  friend int isa_Number(Number _f_)
   { return _f_->get_tag() == a_Number::relation_tag; }
};


////////////////////////////////////////////////////////////////////////
// Subclass for implementing constructor 'num int ' of Number 
////////////////////////////////////////////////////////////////////////
class Number_num : public a_Number {
public:
#line 14 "tri.pcc"
   int num;
public:
   inline Number_num(int _x_) 
      : a_Number(a_Number::tag_num), num(_x_) {}
   inline friend a_Number * num(int _x_) 
      { return new Number_num (_x_); }
};


////////////////////////////////////////////////////////////////////////
// Subclass for implementing constructor 'limit int ' of Number 
////////////////////////////////////////////////////////////////////////
class Number_limit : public a_Number {
public:
#line 15 "tri.pcc"
   int limit;
public:
   inline Number_limit(int _x_) 
      : a_Number(a_Number::tag_limit), limit(_x_) {}
   inline friend a_Number * limit(int _x_) 
      { return new Number_limit (_x_); }
};

#line 15 "tri.pcc"

#line 16 "tri.pcc"
///////////////////////////////////////////////////////////////////////
//  Initialiser for relation Number
///////////////////////////////////////////////////////////////////////
Fact::RelTag a_Number::relation_tag = 0;
static InitialiseFact _dummy_Number_(a_Number::relation_tag);
Fact::RelTag a_Number::get_tag() const { return a_Number::relation_tag; }

#line 16 "tri.pcc"


//
// The following inference construct defines an inference class
// with two rules and one axiom.
//
#line 22 "tri.pcc"

//////////////////////////////////////////////////////////////////////////
//   Definition of inference class Triangle
//////////////////////////////////////////////////////////////////////////
class Triangle : public Rete {
   Triangle(const Triangle&);
   void operator = (const Triangle&);
protected:
   static const Node          network_table[];
   static const RelationTable relation_table[];
public:
   Triangle();
   virtual const char * name_of() const;
   void initialise_axioms();
protected:
   virtual void alpha_test (int, int, Fact *);
   virtual int  beta_test  (Join, const Fact * []);
   virtual void action     (RuleId, Fact * []);
public:
   };
#line 22 "tri.pcc"


#line 24 "tri.pcc"

/////////////////////////////////////////////////////////////////////////////
//  Action method for inference class Triangle
/////////////////////////////////////////////////////////////////////////////
void Triangle::action(ReteNet::RuleId _r_, Fact * _f_[])
{
   switch (_r_) {
      case 1: {
         const Number  _0_ = (const Number )_f_[0];
         const Number  _1_ = (const Number )_f_[1];
#line 36 "tri.pcc"
assert_fact(num((_num(_0_)->num) + 1));
      } break;
      case 2: {
         const Number  _0_ = (const Number )_f_[0];
         const Number  _1_ = (const Number )_f_[1];
         const Number  _2_ = (const Number )_f_[2];
#line 57 "tri.pcc"
 cout << (_num(_0_)->num) << " * " << (_num(_0_)->num) << " + "
             << (_num(_1_)->num) << " * " << (_num(_1_)->num) << " = "
             << (_num(_2_)->num) << " * " << (_num(_2_)->num) << '\n';
            } break;
   }
}

//////////////////////////////////////////////////////////////////////////
//  Alpha test method for class Triangle
//////////////////////////////////////////////////////////////////////////
void Triangle::alpha_test(int _j_, int _i_, Fact * _fact_)
{
   Fact * _f_[3];
   switch (_j_) {
   //////////////////////////////////////////////////////////////////////
   //  Alpha entry tests for relation Number
   //////////////////////////////////////////////////////////////////////
   case 1: {
      _f_[0] = _fact_;
      Number _0_ = (Number)_fact_;
      Number _1_ = (Number)_fact_;
      Number _2_ = (Number)_fact_;
{  const unsigned char * _m_ = 0;
if (_0_->untag()) {    static unsigned char _x0[] = { 2 };
   _m_ = _x0;
 } else {    static unsigned char _x1[] = { 29 };
   _m_ = _x1;
 }
      if (_m_[0] & 1) {
#line 89 "tri.pcc"
if (_i_) insert_beta(1,_f_); else remove_beta(1,_f_);}
      if (_m_[0] & 2) {
#line 89 "tri.pcc"
if (_i_) insert_alpha(1,_fact_); else remove_alpha(1,_fact_);}
      if (_m_[0] & 4) {
#line 89 "tri.pcc"
if (_i_) insert_beta(3,_f_); else remove_beta(3,_f_);}
      if (_m_[0] & 8) {
#line 89 "tri.pcc"
if (_i_) insert_alpha(3,_fact_); else remove_alpha(3,_fact_);}
      if (_m_[0] & 16) {
#line 89 "tri.pcc"
if (_i_) insert_alpha(4,_fact_); else remove_alpha(4,_fact_);}
}
   } break;
   }
}

/////////////////////////////////////////////////////////////////////////////
//  Beta test method for class Triangle
/////////////////////////////////////////////////////////////////////////////
int Triangle::beta_test(Join _j_, const Fact * _f_[])
{  switch (_j_) {
      case 1: {
         const Number  _0_ = (const Number )_f_[0];
         const Number  _1_ = (const Number )_f_[1];
            return ((_num(_0_)->num) < (_limit(_1_)->limit));
      }
      case 2: {
         const Number  _0_ = (const Number )_f_[0];
         const Number  _1_ = (const Number )_f_[1];
            return ((_num(_0_)->num) < (_num(_1_)->num));
      }
      case 3: {
         const Number  _0_ = (const Number )_f_[0];
         const Number  _1_ = (const Number )_f_[1];
         const Number  _2_ = (const Number )_f_[2];
            return ((_num(_1_)->num) < (_num(_2_)->num) && (_num(_0_)->num) * (_num(_0_)->num) + (_num(_1_)->num) * (_num(_1_)->num) == (_num(_2_)->num) * (_num(_2_)->num));
      }
      default: return 0;
   }
}

/////////////////////////////////////////////////////////////////////////////
//  Method to initialise the axioms of inference class Triangle
/////////////////////////////////////////////////////////////////////////////
void Triangle::initialise_axioms()
{
#line 29 "tri.pcc"
assert_fact(num(1));
}


/////////////////////////////////////////////////////////////////////////////
//  Network table for inference class Triangle
/////////////////////////////////////////////////////////////////////////////
const ReteNet::Node Triangle::network_table [] = {
   { 0, 0, ReteNet::Node::Bot,  0, 0 },
   { 1, 2, ReteNet::Node::And,  1, 2 },
   { 0, 2, ReteNet::Node::Bot,  0, 1 },
   { 1, 3, ReteNet::Node::And,  2, 4 },
   { 2, 3, ReteNet::Node::And,  3, 5 },
   { 0, 3, ReteNet::Node::Bot,  0, 2 }
};

//////////////////////////////////////////////////////////////////////////
// Dispatch table for class Triangle
//////////////////////////////////////////////////////////////////////////
Triangle::RelationTable Triangle::relation_table[] = {
   { &a_Number::relation_tag, 1, "Number" }
};

//////////////////////////////////////////////////////////////////////////
//  Identifying name for inference class Triangle
//////////////////////////////////////////////////////////////////////////
const char * Triangle::name_of() const { return "Triangle"; }


//////////////////////////////////////////////////////////////////////////
//  Constructor for inference class Triangle
//////////////////////////////////////////////////////////////////////////
Triangle::Triangle() : Rete(6,Triangle::network_table,1,Triangle::relation_table)
   { initialise_axioms(); }
#line 61 "tri.pcc"

      
int main()
{
   Triangle triangle;   // instantiate an inference module
   int top;

   //
   // Get the limit
   //
   cout << "Please input a limit (say, between 10 - 100): " << flush;
   cin >> top;
   cout << "Trying all numbers from 1 to " << top << '\n';  
    
   //
   // Insert the initial parameter into the database.
   //
   triangle << limit (top);

   //
   // Run the inference engine until it is stable.
   // The inference rules defined above will be fired and triangular
   // identities will be printed.
   //
   triangle.infer();

   return 0;
}
/*
----------------------------- Statistics -------------------------------
Number of decision nodes merged = 0
Number of switches generated    = 0
Number of ifs      generated    = 6
Number of labels   generated    = 0
Number of gotos    generated    = 0
Number of temporary variables   = 2
Number of productions           = 3
Number of rete nodes            = 6
Number of inter-object tests    = 3
Number of axioms                = 1
------------------------------------------------------------------------
*/
