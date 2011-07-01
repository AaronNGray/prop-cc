///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.1),
//  last updated on Mar 13, 1997.
//  The original source file is "poly1.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_GARBAGE_COLLECTION_USED
#define PROP_REFCOUNT_USED
#define PROP_PRINTER_USED
#include <propdefs.h>
#line 1 "poly1.pcc"
/////////////////////////////////////////////////////////////////////////////
//  Testing polymorphic datatypes.
//  (and garbage collection, reference counting etc.)
/////////////////////////////////////////////////////////////////////////////

//
// Define some polymorphic datatypes
// Polymorphic datatypes are not restricted to one type parameter.
// We test the ability to use these types in the context
//
#line 11 "poly1.pcc"
#line 26 "poly1.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for TREE<X, Y>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_TREE_defined
#define datatype_TREE_defined
template <class X, class Y> class a_TREE;
#define TREE(X, Y) a_TREE<X, Y> *
#endif

#  define empty 0

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for LIST<T>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_LIST_defined
#define datatype_LIST_defined
template <class T> class a_LIST;
#define LIST(T) a_LIST<T> *
#endif

#  define nil_1_ 0

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
// Base class for datatype TREE<X, Y>
//
///////////////////////////////////////////////////////////////////////////////
template <class X, class Y> class a_TREE : public GCObject {
public:
   enum Tag_TREE {
      tag_leaf = 0, tag_node = 1
   };

public:
   const Tag_TREE tag__; // variant tag
protected:
   inline a_TREE(Tag_TREE t__) : tag__(t__) {}
public:
   inline virtual ~a_TREE()
   {
   }
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   virtual void trace(GC *);
public:
};
template <class X, class Y> inline int boxed(const a_TREE<X, Y> * x) { return x != 0; }
template <class X, class Y> inline int untag(const a_TREE<X, Y> * x) { return x ? (x->tag__+1) : 0; }

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for TREE<X, Y>
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
template <class X, class Y> extern ostream& operator<<(ostream&, TREE(X, Y));
template <class X, class Y> extern PrettyOStream& operator<<(PrettyOStream&, TREE(X, Y));
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TREE<X, Y>::leaf
//
///////////////////////////////////////////////////////////////////////////////
template <class X, class Y> class TREE_leaf : public a_TREE<X, Y>  {
public:
#line 12 "poly1.pcc"
   X leaf; 
   inline TREE_leaf (X x_leaf)
    : a_TREE<X, Y>(tag_leaf), leaf(x_leaf)
   {
   }
   inline ~TREE_leaf()
   {
   }
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   virtual void trace(GC *);
public:
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor TREE<X, Y>::node
//
///////////////////////////////////////////////////////////////////////////////
template <class X, class Y> class TREE_node : public a_TREE<X, Y>  {
public:
#line 12 "poly1.pcc"
   a_TREE<X, Y> *  _1; Y _2; a_TREE<X, Y> *  _3; 
   inline TREE_node (a_TREE<X, Y> *  x_1, Y x_2, a_TREE<X, Y> *  x_3)
    : a_TREE<X, Y>(tag_node), _1(x_1), _2(x_2), _3(x_3)
   {
   }
   inline ~TREE_node()
   {
   }
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   virtual void trace(GC *);
public:
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for TREE<X, Y>
//
///////////////////////////////////////////////////////////////////////////////
template <class X, class Y> inline a_TREE<X, Y> * leaf (X x_leaf) { return new TREE_leaf<X, Y> (x_leaf); }
template <class X, class Y> inline a_TREE<X, Y> * node (a_TREE<X, Y> *  x_1, Y x_2, a_TREE<X, Y> *  x_3) { return new TREE_node<X, Y> (x_1, x_2, x_3); }
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for TREE<X, Y>
//
///////////////////////////////////////////////////////////////////////////////
template <class X, class Y> inline TREE_leaf<X, Y> * _leaf(const a_TREE<X, Y> * _x_) { return (TREE_leaf<X, Y> *)_x_; }
template <class X, class Y> inline TREE_node<X, Y> * _node(const a_TREE<X, Y> * _x_) { return (TREE_node<X, Y> *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor LIST<T>::#[...]
//
///////////////////////////////////////////////////////////////////////////////
template <class T> class a_LIST : public GCObject {
public:
#line 15 "poly1.pcc"
   T _1; a_LIST<T> *  _2; 
   inline a_LIST (T x_1, a_LIST<T> *  x_2 = 0)
    : _1(x_1), _2(x_2)
   {
   }
   inline virtual ~a_LIST()
   {
   }
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   virtual void trace(GC *);
public:
};
template <class T> inline int boxed(const a_LIST<T> * x) { return x != 0; }
template <class T> inline int untag(const a_LIST<T> * x) { return x ? 1 : 0; }

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods for LIST<T>
//
///////////////////////////////////////////////////////////////////////////////
class PrettyOStream;
template <class T> extern ostream& operator<<(ostream&, LIST(T));
template <class T> extern PrettyOStream& operator<<(PrettyOStream&, LIST(T));
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for LIST<T>
//
///////////////////////////////////////////////////////////////////////////////
template <class T> inline a_LIST<T> * list_1_ (T x_1, a_LIST<T> *  x_2 = 0) { return new a_LIST<T> (x_1, x_2); }
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for LIST<T>
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype EXP
//
///////////////////////////////////////////////////////////////////////////////
class a_EXP {
public:
   enum Tag_EXP {
      tag_num = 0, tag_var = 1, tag_add = 2, 
      tag_sub = 3, tag_mul = 4, tag_div = 5, 
      tag_list = 6
   };

public:
   const Tag_EXP tag__; // variant tag
protected:
   inline a_EXP(Tag_EXP t__) : tag__(t__) {}
public:
};
inline int boxed(const a_EXP * x) { return 1; }
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
#line 17 "poly1.pcc"
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
#line 18 "poly1.pcc"
   char const * var; 
   inline EXP_var (char const * x_var)
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
#line 19 "poly1.pcc"
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
#line 20 "poly1.pcc"
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
#line 21 "poly1.pcc"
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
#line 22 "poly1.pcc"
   EXP _1; EXP _2; 
   inline EXP_div (EXP x_1, EXP x_2)
    : a_EXP(tag_div), _1(x_1), _2(x_2)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor EXP::list
//
///////////////////////////////////////////////////////////////////////////////
class EXP_list : public a_EXP {
public:
#line 23 "poly1.pcc"
   a_LIST<EXP> *  list; 
   inline EXP_list (a_LIST<EXP> *  x_list)
    : a_EXP(tag_list), list(x_list)
   {
   }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for EXP
//
///////////////////////////////////////////////////////////////////////////////
inline a_EXP * num (int x_num) { return new EXP_num (x_num); }
inline a_EXP * var (char const * x_var) { return new EXP_var (x_var); }
inline a_EXP * add (EXP x_1, EXP x_2) { return new EXP_add (x_1, x_2); }
inline a_EXP * sub (EXP x_1, EXP x_2) { return new EXP_sub (x_1, x_2); }
inline a_EXP * mul (EXP x_1, EXP x_2) { return new EXP_mul (x_1, x_2); }
inline a_EXP * div (EXP x_1, EXP x_2) { return new EXP_div (x_1, x_2); }
inline a_EXP * list (a_LIST<EXP> *  x_list) { return new EXP_list (x_list); }
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
inline EXP_list * _list(const a_EXP * _x_) { return (EXP_list *)_x_; }

#line 26 "poly1.pcc"
#line 26 "poly1.pcc"


/////////////////////////////////////////////////////////////////////////////
//  Instantiate the datatypes. 
//  This will generate a bunch of methods, functions and classes
//  to implement printing and garbage collection.
/////////////////////////////////////////////////////////////////////////////
#line 33 "poly1.pcc"
#line 33 "poly1.pcc"
///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype TREE<int, char const *>
///////////////////////////////////////////////////////////////////////////////
#line 33 "poly1.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for TREE<int, char const *>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, TREE(int, char const *)  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, TREE(int, char const *)  obj__);

///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype LIST<int>
///////////////////////////////////////////////////////////////////////////////
#line 33 "poly1.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for LIST<int>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, LIST(int)  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, LIST(int)  obj__);

///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype LIST<EXP>
///////////////////////////////////////////////////////////////////////////////
#line 33 "poly1.pcc"
///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for LIST<EXP>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, LIST(EXP)  obj__);
PrettyOStream& operator << (PrettyOStream& strm__, LIST(EXP)  obj__);

#line 33 "poly1.pcc"
#line 33 "poly1.pcc"

#line 34 "poly1.pcc"
#line 34 "poly1.pcc"
///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype TREE<int, char const *>
///////////////////////////////////////////////////////////////////////////////
#line 34 "poly1.pcc"
void a_TREE<int, char const *>::trace(GC * gc__)
{
}

///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for TREE<int, char const *>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, TREE(int, char const *)  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, TREE(int, char const *)  obj__)
{
   switch (untag(obj__))
   {
      case (int)empty: 
         strm__ << "empty";
         break;
      case 0 + 1: 
         strm__ << "leaf";
         strm__ << "(";
         strm__ << _leaf(obj__)->leaf; // int
         strm__ << ")";
         break;
      case 1 + 1: 
         strm__ << ")";
         strm__ << _node(obj__)->_1; // TREE<int, char const *> 
         strm__ << ",";
         strm__ << _node(obj__)->_2; // char const *
         strm__ << ",";
         strm__ << _node(obj__)->_3; // TREE<int, char const *> 
         strm__ << "node";
         strm__ << "(";
         break;
   }
   return strm__;
}

void TREE_leaf<int, char const *>::trace(GC * gc__)
{
   // call to method a_TREE<int, char const *>::trace() has been optimized out
   // omitted int
}

void TREE_node<int, char const *>::trace(GC * gc__)
{
   // call to method a_TREE<int, char const *>::trace() has been optimized out
   this->_1 = (TREE(int, char const *) )gc__->trace(this->_1); // TREE<int, char const *> 
   // omitted char const *
   this->_3 = (TREE(int, char const *) )gc__->trace(this->_3); // TREE<int, char const *> 
}



///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype LIST<int>
///////////////////////////////////////////////////////////////////////////////
#line 34 "poly1.pcc"
void a_LIST<int>::trace(GC * gc__)
{
   // omitted int
   this->_2 = (LIST(int) )gc__->trace(this->_2); // LIST<int>  = 0
}

///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for LIST<int>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, LIST(int)  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, LIST(int)  obj__)
{
   switch (untag(obj__))
   {
      case (int)nil_1_: 
         strm__ << "#[]";
         break;
      case 1: 
         strm__ << ")";
         strm__ << obj__->_1; // int
         strm__ << ",";
         strm__ << obj__->_2; // LIST<int>  = 0
         strm__ << "#[...]";
         strm__ << "(";
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype LIST<EXP>
///////////////////////////////////////////////////////////////////////////////
#line 34 "poly1.pcc"
void a_LIST<EXP>::trace(GC * gc__)
{
   // omitted EXP
   this->_2 = (LIST(EXP) )gc__->trace(this->_2); // LIST<EXP>  = 0
}

///////////////////////////////////////////////////////////////////////////////
//
// Pretty printing methods for LIST<EXP>
//
///////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& strm__, LIST(EXP)  obj__)
{  PrettyOStream S(strm__); S << obj__; return strm__; }

PrettyOStream& operator << (PrettyOStream& strm__, LIST(EXP)  obj__)
{
   switch (untag(obj__))
   {
      case (int)nil_1_: 
         strm__ << "#[]";
         break;
      case 1: 
         strm__ << ")";
         strm__ << obj__->_1; // EXP
         strm__ << ",";
         strm__ << obj__->_2; // LIST<EXP>  = 0
         strm__ << "#[...]";
         strm__ << "(";
         break;
   }
   return strm__;
}



///////////////////////////////////////////////////////////////////////////////
// Instantiation of datatype EXP
///////////////////////////////////////////////////////////////////////////////
#line 34 "poly1.pcc"
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
      case a_EXP::tag_num: 
         strm__ << _num(obj__)->num; // int
         break;
      case a_EXP::tag_var: 
         strm__ << _var(obj__)->var; // char const *
         break;
      case a_EXP::tag_add: 
         strm__ << "(";
         strm__ << _add(obj__)->_1; // EXP
         strm__ << " + ";
         strm__ << _add(obj__)->_2; // EXP
         strm__ << ")";
         break;
      case a_EXP::tag_sub: 
         strm__ << "(";
         strm__ << _sub(obj__)->_1; // EXP
         strm__ << " - ";
         strm__ << _sub(obj__)->_2; // EXP
         strm__ << ")";
         break;
      case a_EXP::tag_mul: 
         strm__ << "(";
         strm__ << _mul(obj__)->_1; // EXP
         strm__ << " * ";
         strm__ << _mul(obj__)->_2; // EXP
         strm__ << ")";
         break;
      case a_EXP::tag_div: 
         strm__ << "(";
         strm__ << _div(obj__)->_1; // EXP
         strm__ << " / ";
         strm__ << _div(obj__)->_2; // EXP
         strm__ << ")";
         break;
      case a_EXP::tag_list: 
         strm__ << _list(obj__)->list; // LIST<EXP> 
         break;
   }
   return strm__;
}



#line 34 "poly1.pcc"
#line 34 "poly1.pcc"


/////////////////////////////////////////////////////////////////////////////
//  Define functions to test pattern matching
/////////////////////////////////////////////////////////////////////////////
template <class T>
   int length(
#line 40 "poly1.pcc"
a_LIST<T> *  
#line 40 "poly1.pcc"
 l)
   {  
#line 43 "poly1.pcc"
{
   if (l) {
#line 43 "poly1.pcc"
     return 1 + length(l->_2); 
#line 43 "poly1.pcc"
   } else {
#line 42 "poly1.pcc"
     return 0; 
#line 42 "poly1.pcc"
   }
}
#line 44 "poly1.pcc"
#line 44 "poly1.pcc"

   }

/////////////////////////////////////////////////////////////////////////////
//  Sum an integer list
/////////////////////////////////////////////////////////////////////////////
int sum (
#line 50 "poly1.pcc"
a_LIST<int> *  
#line 50 "poly1.pcc"
 l)
{  
#line 53 "poly1.pcc"
{
   if (l) {
#line 53 "poly1.pcc"
     return l->_1 + sum(l->_2); 
#line 53 "poly1.pcc"
   } else {
#line 52 "poly1.pcc"
     return 0; 
#line 52 "poly1.pcc"
   }
}
#line 54 "poly1.pcc"
#line 54 "poly1.pcc"
 
}

/////////////////////////////////////////////////////////////////////////////
//  Append two lists
/////////////////////////////////////////////////////////////////////////////
template <class T>
   
#line 61 "poly1.pcc"
a_LIST<T> *  
#line 61 "poly1.pcc"
 append (a_LIST<T> *  
#line 61 "poly1.pcc"
 x, a_LIST<T> *  
#line 61 "poly1.pcc"
 y)
   {  
#line 65 "poly1.pcc"
{
   if (x) {
#line 64 "poly1.pcc"
     return 
#line 64 "poly1.pcc"
#line 64 "poly1.pcc"
      list_1_(x->_1,append(x->_2,y))
#line 64 "poly1.pcc"
#line 64 "poly1.pcc"
      ;
      
#line 65 "poly1.pcc"
   } else {
#line 63 "poly1.pcc"
  return y;
      
#line 64 "poly1.pcc"
   }
}
#line 65 "poly1.pcc"
#line 65 "poly1.pcc"

   }

/////////////////////////////////////////////////////////////////////////////
//   Exercise the list patterns
/////////////////////////////////////////////////////////////////////////////
int dummy_len (
#line 71 "poly1.pcc"
a_LIST<int> *  
#line 71 "poly1.pcc"
 l)
{  
#line 78 "poly1.pcc"
{
   if (l) {
      if (l->_2) {
         if (l->_2->_2) {
            if (l->_2->_2->_2) {
               if (l->_2->_2->_2->_2) {
#line 78 "poly1.pcc"
                 return 5; 
#line 78 "poly1.pcc"
               } else {
#line 77 "poly1.pcc"
                 return 4; 
#line 77 "poly1.pcc"
               }
            } else {
#line 76 "poly1.pcc"
              return 3; 
#line 76 "poly1.pcc"
            }
         } else {
#line 75 "poly1.pcc"
           return 2; 
#line 75 "poly1.pcc"
         }
      } else {
#line 74 "poly1.pcc"
        return 1; 
#line 74 "poly1.pcc"
      }
   } else {
#line 73 "poly1.pcc"
     return 0; 
#line 73 "poly1.pcc"
   }
}
#line 79 "poly1.pcc"
#line 79 "poly1.pcc"

}

/////////////////////////////////////////////////////////////////////////////
//  Depth of a tree
/////////////////////////////////////////////////////////////////////////////
template <class X, class Y>
   int depth (
#line 86 "poly1.pcc"
a_TREE<X, Y> *  
#line 86 "poly1.pcc"
 t)
   {  
#line 92 "poly1.pcc"
{
   if (t) {
      if (t->tag__) {
         
#line 90 "poly1.pcc"
        int a = depth(_node(t)->_1), b = depth(_node(t)->_3);
         return 1 + (a > b ? a : b);
         
#line 92 "poly1.pcc"
      } else {
         
#line 89 "poly1.pcc"
   return 1;
         
#line 90 "poly1.pcc"
      }
   } else {
#line 88 "poly1.pcc"
 return 0;
      
#line 89 "poly1.pcc"
   }
}
#line 92 "poly1.pcc"
#line 92 "poly1.pcc"

   }


int main()
{  
   // Due to a compiler problem in g++ 2.5.8, I'm unable to use a
   // typedef to abbreviate TREE<int, const char *>.  
   
#line 100 "poly1.pcc"
a_TREE<int, char const *> *  
#line 100 "poly1.pcc"
 E = empty;
   const char * This = "this";
   const char * That = "that";
   a_TREE<int, char const *> *  
#line 103 "poly1.pcc"
 tree1 = node( E, This, leaf(2) );
   a_TREE<int, char const *> *  
#line 104 "poly1.pcc"
 tree2 = node( E, That, E );

   EXP       e1    = add(var("x"),num(1));
   EXP       e2    = sub(var("y"),num(2));

   a_LIST<int> *  
#line 109 "poly1.pcc"
 list1 = 
#line 109 "poly1.pcc"
list_1_(1,list_1_(2))
#line 109 "poly1.pcc"
#line 109 "poly1.pcc"
;
   
#line 110 "poly1.pcc"
a_LIST<EXP> *  
#line 110 "poly1.pcc"
 list2 = 
#line 110 "poly1.pcc"
list_1_(e1,list_1_(e2,list_1_(var("z"))))
#line 110 "poly1.pcc"
#line 110 "poly1.pcc"
;
   
#line 111 "poly1.pcc"
a_LIST<EXP> *  
#line 111 "poly1.pcc"
 list3 = 
#line 111 "poly1.pcc"
list_1_(num((- 1)),list_1_(list(list2),list_1_(list(list2))))
#line 111 "poly1.pcc"
#line 111 "poly1.pcc"
;
  
   cout << "tree1 = " << tree1 << "\tdepth = " << depth(tree1) << '\n';
   cout << "tree2 = " << tree2 << "\tdepth = " << depth(tree2) << '\n';
  
   cout << "list1 = " << list1 
        << "\tlength = " << length(list1) 
        << "\tsum = " << sum(list1) << '\n';
   cout << "list2 = " << list2 << "\tlength = " << length(list2) << '\n';
   cout << "list3 = " << list3 << "\tlength = " << length(list3) << '\n';
   cout << "list1 + list1 = " << append(list1, list1) << '\n';
   cout << "list2 + list3 = " << append(list2, list3) << '\n';

   return 0;
}
#line 126 "poly1.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 4
Number of ifs generated      = 10
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
