///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\basics.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/basics.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the basic definitions used in the
//  Prop -> C++ translator, including various flags and memory
//  pools definitions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef basic_definitions_h
#define basic_definitions_h

#include <iostream>
#include <new>
#include <stdarg.h>
#include <AD/generic/generic.h>    // generic definitions from the library
#include <AD/memory/mempool.h>     // memory pool
#include <AD/memory/strpool.h>     // string pool


///////////////////////////////////////////////////////////////////////////////
//
//  Forward declaration for the input/output streams.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  The following is used to deal with the new ANSI conformance
//  of the "for" statement involving scoping of variables defined in
//  an "if".   Variables defined inside a for statement are not visible
//  only with the scope of the construct.
//
///////////////////////////////////////////////////////////////////////////////

#define for if (0) ; else for

///////////////////////////////////////////////////////////////////////////////
//
//  Two memory pools are kept for fast memory allocation.
//  Memory allocated from the global pool is persistent during the run
//  of the translator, while memory allocated from the local pool can
//  be deallocated in a stack-like fashion.  Also, there is a pool for
//  string objects.  These are persistent like the global pool.
//
///////////////////////////////////////////////////////////////////////////////

extern MemPool    mem_pool;           // memory pool for local objects
extern MemPool    global_pool;        // memory pool for global objects
extern StringPool str_pool;           // string pool for strings

///////////////////////////////////////////////////////////////////////////////
//
//  Class 'MEM' is a memory management class.  Objects deriving from
//  this class are allocates from the memory pools.  By default,
//  the local memory pool is used.  The methods 'use_global_pools'
//  and 'use_local_pools' can be used to switch between the global
//  and local pools.
//
///////////////////////////////////////////////////////////////////////////////

class MEM
{
public:
  void * operator new (size_t);            // allocation member
  // void   operator delete(void *);       // disable deletion
  static void   use_global_pools();        // switch to the global pool
  static void   use_local_pools();         // switch to the local pol
                                           // allocate a vector from the pool
};

///////////////////////////////////////////////////////////////////////////////
//
//  The input/output/logging streams and the output file name(if applicable).
//
///////////////////////////////////////////////////////////////////////////////

extern std::istream* input_stream;          // The current input stream
extern std::ostream* output_stream;         // The current output stream
extern std::ostream* log_stream;            // The current logging stream
extern std::ostream&  open_logfile();        // Open the logfile
extern std::ostream*  open_output_file(const char []); // open a file for output
extern void encode_string(char *, const char *); // Encode a string.

///////////////////////////////////////////////////////////////////////////////
//
//  Errors and messages routines.
//
///////////////////////////////////////////////////////////////////////////////

extern int  errors;                        // number of errors found
std::ostream& pr_msg   (const char *, va_list); // generic print message routine
std::ostream& error    (const char *, ...);     // error message
std::ostream& msg      (const char *, ...);     // generic message
std::ostream& debug_msg(const char *, ...);     // debugging message
void     bug      (const char *, ...);     // abort and generate a bug report

///////////////////////////////////////////////////////////////////////////////
//
//  Polymorphic lists, pairs and identifiers.  These are used throughout the
//  rest of the translator.
//
///////////////////////////////////////////////////////////////////////////////

#line 104 "../../prop-src/basics.ph"
#line 108 "../../prop-src/basics.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for List<T>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_List_defined
#define datatype_List_defined
template <class T> class a_List;
#define List(T) a_List<T> *
#endif

#  define nil_1_ 0

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Pair<A, B>
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Pair_defined
#define datatype_Pair_defined
template <class A, class B> class a_Pair;
#define Pair(A, B) a_Pair<A, B> *
#endif

///////////////////////////////////////////////////////////////////////////////
// Definition of type Id
///////////////////////////////////////////////////////////////////////////////
#line 106 "../../prop-src/basics.ph"
typedef char const * Id;

///////////////////////////////////////////////////////////////////////////////
// Definition of type Ids
///////////////////////////////////////////////////////////////////////////////
#line 107 "../../prop-src/basics.ph"
typedef a_List<Id> *  Ids;

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor List<T>::#[...]
//
///////////////////////////////////////////////////////////////////////////////
template <class T> class a_List : public MEM {
public:
#line 104 "../../prop-src/basics.ph"
  T _1; a_List<T> *  _2; 
  inline a_List (T x_1, a_List<T> *  x_2)
   : _1(x_1), _2(x_2)
  {
  }
  inline a_List (T x_1)
   : _1(x_1), _2((a_List<T> *)0)
  {
  }
};
template <class T> inline int boxed(const a_List<T> * x) { return x != 0; }
template <class T> inline int untag(const a_List<T> * x) { return x ? 1 : 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for List<T>
//
///////////////////////////////////////////////////////////////////////////////
template <class T> inline a_List<T> * list_1_ (T x_1, a_List<T> *  x_2)
{
  return new a_List<T> (x_1, x_2);
}
template <class T> inline a_List<T> * list_1_ (T x_1)
{
  return new a_List<T> (x_1);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for List<T>
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Pair<A, B>::makepair
//
///////////////////////////////////////////////////////////////////////////////
template <class A, class B> class a_Pair : public MEM {
public:
#line 105 "../../prop-src/basics.ph"
  A fst; B snd; 
  inline a_Pair (A x_fst, B x_snd)
   : fst(x_fst), snd(x_snd)
  {
  }
};
template <class A, class B> inline int boxed(const a_Pair<A, B> *) { return 1; }
template <class A, class B> inline int untag(const a_Pair<A, B> *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Pair<A, B>
//
///////////////////////////////////////////////////////////////////////////////
template <class A, class B> inline a_Pair<A, B> * makepair (A x_fst, B x_snd)
{
  return new a_Pair<A, B> (x_fst, x_snd);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Pair<A, B>
//
///////////////////////////////////////////////////////////////////////////////


#line 108 "../../prop-src/basics.ph"
#line 108 "../../prop-src/basics.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Macro to iterate over a list.
//
///////////////////////////////////////////////////////////////////////////////

#define APPEND_(a,b)  a ## b
#define NEWVAR2_(a,b) APPEND_(a,b)
#define NEWVAR(a)    NEWVAR2_(a,__LINE__)
#define for_each(T,i,l)                          \
   T i;                                          \
   for (List(T) NEWVAR(_i_) = l;                 \
        NEWVAR(_i_) && (i = NEWVAR(_i_)->_1, 1); \
        NEWVAR(_i_) = NEWVAR(_i_)->_2)

///////////////////////////////////////////////////////////////////////////////
//
//  We keep track of the current source location in the following global
//  variables.  These are updated continuously by the parser, lexer and the
//  semantic processing routines.
//
///////////////////////////////////////////////////////////////////////////////

extern int line;        // the current line number
extern int first_line;  // the first line of the current construct
extern Id  file;        // the current input file.

///////////////////////////////////////////////////////////////////////////////
//
//  The following class, Loc, is used to keep track of the source location.
//  Objects derived from this class will contain the source location in
//  which it is constructed; useful for AST nodes.
//
///////////////////////////////////////////////////////////////////////////////

struct Loc : public MEM
{
public:
  Id file_name;
  int begin_line, end_line;
  Loc();
  Loc(int, int);
  inline const Loc * loc() const { return this; }
  void set_loc() const;
};

#endif
#line 157 "../../prop-src/basics.ph"
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
