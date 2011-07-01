///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.2),
//  last updated on Mar 14, 1997.
//  The original source file is "foundation.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_GARBAGE_COLLECTION_USED
#include <propdefs.h>
#line 1 "foundation.ph"
#ifndef foundational_stuff_h
#define foundational_stuff_h

#line 4 "foundation.ph"
#line 4 "foundation.ph"
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

#  define nil_1_ 0

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor List<a>::#[...]
//
///////////////////////////////////////////////////////////////////////////////
template <class a> class a_List : public GCObject {
public:
#line 4 "foundation.ph"
   a _1; a_List<a> *  _2; 
   a_List (a x_1, a_List<a> *  x_2);
   a_List (a x_1, int x_2);
   virtual ~a_List();
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
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
template <class a> extern a_List<a> * list_1_ (a x_1, a_List<a> *  x_2);

#line 4 "foundation.ph"
#line 4 "foundation.ph"

#line 5 "foundation.ph"
#line 5 "foundation.ph"
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
#line 5 "foundation.ph"
   
   const int len_;
   a vector_1_[0]; 
   inline int len() const { return len_; }
   inline a  const&  at(int i) const { return vector_1_[i]; }
   inline a &        at(int i)       { return vector_1_[i]; }
   inline a  const * array() const   { return vector_1_; }
   inline a  *       array()         { return vector_1_; }
   a_Vector (int x__len_, a const * x_vector_1_);
   virtual ~a_Vector();
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
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
template <class a> extern a_Vector<a> * vector_1_ (int x__len_, a const * x_vector_1_);

#line 5 "foundation.ph"
#line 5 "foundation.ph"

#line 6 "foundation.ph"
#line 6 "foundation.ph"
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
#line 6 "foundation.ph"
   a fst; b snd; 
   a_Pair (a x_fst, b x_snd);
   virtual ~a_Pair();
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
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
template <class a, class b> extern a_Pair<a, b> * PAIR (a x_fst, b x_snd);

#line 6 "foundation.ph"
#line 6 "foundation.ph"

#line 7 "foundation.ph"
#line 7 "foundation.ph"
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

#  define NONE 0

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Option<a>::SOME
//
///////////////////////////////////////////////////////////////////////////////
template <class a> class a_Option : public GCObject {
public:
#line 7 "foundation.ph"
   a SOME; 
   a_Option (a x_SOME);
   virtual ~a_Option();
   ////////////////////////////////////////////////////////////////////////////
   //
   // Method for garbage collection tracing
   //
   ////////////////////////////////////////////////////////////////////////////
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
template <class a> extern a_Option<a> * SOME (a x_SOME);

#line 7 "foundation.ph"
#line 7 "foundation.ph"

#line 8 "foundation.ph"
#line 8 "foundation.ph"
///////////////////////////////////////////////////////////////////////////////
// Definition of type Id
///////////////////////////////////////////////////////////////////////////////
#line 8 "foundation.ph"
typedef char const * Id;

#line 8 "foundation.ph"
#line 8 "foundation.ph"


#endif
#line 11 "foundation.ph"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = enabled
Fast string matching         = enabled
Inline downcasts             = enabled
--------------------------------------------------------------------------
*/
