///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\..\app\setl-pe\foundation.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_GARBAGE_COLLECTION_USED
#include <propdefs.h>
#line 1 "../../../app/setl-pe/foundation.ph"
#ifndef foundational_stuff_h
#define foundational_stuff_h

#line 4 "../../../app/setl-pe/foundation.ph"
#line 4 "../../../app/setl-pe/foundation.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for List<a>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_List_defined
#define datatype_List_defined
template <class a> class a_List;
#define List(a) a_List<a> *
#endif

#  define v_nil_1_ 0

#  define nil_1_ v_nil_1_

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor List<a>::#[...]
//
///////////////////////////////////////////////////////////////////////////////
template <class a> class a_List : public GCObject {
public:
#line 4 "../../../app/setl-pe/foundation.ph"
  a _1; a_List<a> *  _2; 
  inline a_List (a x_1, a_List<a> *  x_2)
   : _1(x_1), _2(x_2)
  {
  }
  inline a_List (a x_1)
   : _1(x_1), _2((a_List<a> *)0)
  {
  }
  inline virtual ~a_List()
  {
  }
  /////////////////////////////////////////////////////////////////////////////
  //
  // Method for garbage collection tracing
  //
  /////////////////////////////////////////////////////////////////////////////
protected:
  virtual void trace(GC *);
public:
};
template <class a> inline int boxed(const a_List<a> * x) { return x != 0; }
template <class a> inline int untag(const a_List<a> * x) { return x ? 1 : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for List<a>
//
///////////////////////////////////////////////////////////////////////////////
template <class a> inline a_List<a> * list_1_ (a x_1, a_List<a> *  x_2)
{
  return new a_List<a> (x_1, x_2);
}
template <class a> inline a_List<a> * list_1_ (a x_1)
{
  return new a_List<a> (x_1);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for List<a>
//
///////////////////////////////////////////////////////////////////////////////


#line 4 "../../../app/setl-pe/foundation.ph"
#line 4 "../../../app/setl-pe/foundation.ph"

#line 5 "../../../app/setl-pe/foundation.ph"
#line 5 "../../../app/setl-pe/foundation.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Vector<a>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Vector_defined
#define datatype_Vector_defined
template <class a> class a_Vector;
#define Vector(a) a_Vector<a> *
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Vector<a>::[|...|]
//
///////////////////////////////////////////////////////////////////////////////
template <class a> class a_Vector : public GCObject {
public:
#line 5 "../../../app/setl-pe/foundation.ph"
  
  const int len_;
  a vector_1_[0]; 
  inline int len() const { return len_; }
  inline a  const&  at(int i) const { return vector_1_[i]; }
  inline a &        at(int i)       { return vector_1_[i]; }
  inline a  const * array() const   { return vector_1_; }
  inline a  *       array()         { return vector_1_; }
  inline a_Vector (int x__len_, a const * x_vector_1_)
   : len_(x__len_)
  {
    {
      for (int i__ = 0; i__ < (len_); i__++)
      {
        typedef a  ELEMENT_TYPE__;
        new (vector_1_ + i__) ELEMENT_TYPE__ (x_vector_1_[i__]);
      }
    }
  }
  inline virtual ~a_Vector()
  {
    {
      for (int i__; i__ < len_; i__++)
      {
        typedef a  ELEMENT_TYPE;
        (vector_1_+i__)->~ELEMENT_TYPE();
      }
    }
  }
  /////////////////////////////////////////////////////////////////////////////
  //
  // Method for garbage collection tracing
  //
  /////////////////////////////////////////////////////////////////////////////
protected:
  virtual void trace(GC *);
public:
};
template <class a> inline int boxed(const a_Vector<a> *) { return 1; }
template <class a> inline int untag(const a_Vector<a> *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Vector<a>
//
///////////////////////////////////////////////////////////////////////////////
template <class a> inline a_Vector<a> * vector_1_ (int x__len_, a const * x_vector_1_)
{
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ ()
{
  const int x__len_ = 0;
  a  x_vector_1_[0];
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1)
{
  const int x__len_ = 1;
  a  x_vector_1_[1];
  x_vector_1_[0] = x__1;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2)
{
  const int x__len_ = 2;
  a  x_vector_1_[2];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3)
{
  const int x__len_ = 3;
  a  x_vector_1_[3];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3, a x__4)
{
  const int x__len_ = 4;
  a  x_vector_1_[4];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  x_vector_1_[3] = x__4;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3, a x__4, a x__5)
{
  const int x__len_ = 5;
  a  x_vector_1_[5];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  x_vector_1_[3] = x__4;
  x_vector_1_[4] = x__5;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3, a x__4, a x__5, a x__6)
{
  const int x__len_ = 6;
  a  x_vector_1_[6];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  x_vector_1_[3] = x__4;
  x_vector_1_[4] = x__5;
  x_vector_1_[5] = x__6;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3, a x__4, a x__5, a x__6, a x__7)
{
  const int x__len_ = 7;
  a  x_vector_1_[7];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  x_vector_1_[3] = x__4;
  x_vector_1_[4] = x__5;
  x_vector_1_[5] = x__6;
  x_vector_1_[6] = x__7;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3, a x__4, a x__5, a x__6, a x__7, a x__8)
{
  const int x__len_ = 8;
  a  x_vector_1_[8];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  x_vector_1_[3] = x__4;
  x_vector_1_[4] = x__5;
  x_vector_1_[5] = x__6;
  x_vector_1_[6] = x__7;
  x_vector_1_[7] = x__8;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3, a x__4, a x__5, a x__6, a x__7, a x__8, a x__9)
{
  const int x__len_ = 9;
  a  x_vector_1_[9];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  x_vector_1_[3] = x__4;
  x_vector_1_[4] = x__5;
  x_vector_1_[5] = x__6;
  x_vector_1_[6] = x__7;
  x_vector_1_[7] = x__8;
  x_vector_1_[8] = x__9;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
template <class a> inline a_Vector<a> * vector_1_ (a x__1, a x__2, a x__3, a x__4, a x__5, a x__6, a x__7, a x__8, a x__9, a x__10)
{
  const int x__len_ = 10;
  a  x_vector_1_[10];
  x_vector_1_[0] = x__1;
  x_vector_1_[1] = x__2;
  x_vector_1_[2] = x__3;
  x_vector_1_[3] = x__4;
  x_vector_1_[4] = x__5;
  x_vector_1_[5] = x__6;
  x_vector_1_[6] = x__7;
  x_vector_1_[7] = x__8;
  x_vector_1_[8] = x__9;
  x_vector_1_[9] = x__10;
  return new (sizeof(a_Vector<a>)+sizeof(a )*x__len_) a_Vector<a> (x__len_, x_vector_1_);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Vector<a>
//
///////////////////////////////////////////////////////////////////////////////


#line 5 "../../../app/setl-pe/foundation.ph"
#line 5 "../../../app/setl-pe/foundation.ph"

#line 6 "../../../app/setl-pe/foundation.ph"
#line 6 "../../../app/setl-pe/foundation.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Pair<a, b>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Pair_defined
#define datatype_Pair_defined
template <class a, class b> class a_Pair;
#define Pair(a, b) a_Pair<a, b> *
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pair<a, b>::PAIR
//
///////////////////////////////////////////////////////////////////////////////
template <class a, class b> class a_Pair : public GCObject {
public:
#line 6 "../../../app/setl-pe/foundation.ph"
  a fst; b snd; 
  inline a_Pair (a x_fst, b x_snd)
   : fst(x_fst), snd(x_snd)
  {
  }
  inline virtual ~a_Pair()
  {
  }
  /////////////////////////////////////////////////////////////////////////////
  //
  // Method for garbage collection tracing
  //
  /////////////////////////////////////////////////////////////////////////////
protected:
  virtual void trace(GC *);
public:
};
template <class a, class b> inline int boxed(const a_Pair<a, b> *) { return 1; }
template <class a, class b> inline int untag(const a_Pair<a, b> *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Pair<a, b>
//
///////////////////////////////////////////////////////////////////////////////
template <class a, class b> inline a_Pair<a, b> * PAIR (a x_fst, b x_snd)
{
  return new a_Pair<a, b> (x_fst, x_snd);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Pair<a, b>
//
///////////////////////////////////////////////////////////////////////////////


#line 6 "../../../app/setl-pe/foundation.ph"
#line 6 "../../../app/setl-pe/foundation.ph"

#line 7 "../../../app/setl-pe/foundation.ph"
#line 7 "../../../app/setl-pe/foundation.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Option<a>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Option_defined
#define datatype_Option_defined
template <class a> class a_Option;
#define Option(a) a_Option<a> *
#endif

#  define v_NONE 0

#  define NONE v_NONE

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Option<a>::SOME
//
///////////////////////////////////////////////////////////////////////////////
template <class a> class a_Option : public GCObject {
public:
#line 7 "../../../app/setl-pe/foundation.ph"
  a SOME; 
  inline a_Option (a x_SOME)
   : SOME(x_SOME)
  {
  }
  inline virtual ~a_Option()
  {
  }
  /////////////////////////////////////////////////////////////////////////////
  //
  // Method for garbage collection tracing
  //
  /////////////////////////////////////////////////////////////////////////////
protected:
  virtual void trace(GC *);
public:
};
template <class a> inline int boxed(const a_Option<a> * x) { return x != 0; }
template <class a> inline int untag(const a_Option<a> * x) { return x ? 1 : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Option<a>
//
///////////////////////////////////////////////////////////////////////////////
template <class a> inline a_Option<a> * SOME (a x_SOME)
{
  return new a_Option<a> (x_SOME);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Option<a>
//
///////////////////////////////////////////////////////////////////////////////


#line 7 "../../../app/setl-pe/foundation.ph"
#line 7 "../../../app/setl-pe/foundation.ph"

#line 8 "../../../app/setl-pe/foundation.ph"
#line 8 "../../../app/setl-pe/foundation.ph"
///////////////////////////////////////////////////////////////////////////////
// Definition of type Id
///////////////////////////////////////////////////////////////////////////////
#line 8 "../../../app/setl-pe/foundation.ph"
typedef char const * Id;

#line 8 "../../../app/setl-pe/foundation.ph"
#line 8 "../../../app/setl-pe/foundation.ph"


#endif
#line 11 "../../../app/setl-pe/foundation.ph"
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
