//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the 
// public domain.   The author(s) of this software reserve no copyrights on 
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that 
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in 
// your programs, and that this notice be preserved intact in all the source 
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1997
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Version 2.3.2 
//  This file provides linkage to various runtime support for code
//  generated using Prop.  
//////////////////////////////////////////////////////////////////////////////

// Notice that by writing code that assumes the type bool is defined
// may make it difficult to port code to other plaforms.
// #define PROP_BOOL_IS_IMPLEMENTED

#ifdef PROP_REFERENCE_COUNTING_USED  
   // Reference counting support
#  include <AD/memory/constref.h> // reference countable object base class
#endif

#ifdef PROP_GARBAGE_COLLECTION_USED  
   // Garbage collection support
#  include <AD/gc/gcobject.h>     // garbage collectable object base class
#endif

#ifdef PROP_HASH_CONSING_USED
   // Hash consing support
#  include <AD/hash/lhash.h>      // linear probing hash table
#endif

#ifdef PROP_LEXER_USED  
   // Lexer support
#  include <AD/automata/scanner.h>
#endif

#ifdef PROP_PARSER_USED 
   // Parser support
#  include <AD/automata/lrparser.h>
#endif

#ifdef PROP_INFERENCE_USED  
   // Inference support
#  include <AD/rete/rete.h>          // Rete network driver
#endif

#ifdef PROP_REWRITING_USED
   // Rewriting support
#  include <AD/automata/treetab.h>   // compressed tree automata tables
#  include <AD/automata/dfatable.h>  // compressed dfa tables
#  include <AD/rewrite/termobj.h>    // rewritable object base class
#  include <AD/rewrite/burs.h>       // rewriting base class
#  define PROP_REWRITE_STACK_SIZE 1024
#endif

#ifdef PROP_UNIFICATION_USED
    // Unification/constraint satisfaction support
// #  include <AD/csp/logicalterm.h>    // logical(unifiable) term
#endif

#ifdef PROP_REGEXP_MATCHING_USED
    // regular expression string matching support
#  include <AD/automata/regexmat.h>  // Regular expression string matcher
#endif

#ifdef PROP_PRINTER_USED
   // pretty printing support
#  include <AD/pretty/postream.h>  // pretty printer routines
#endif

#if defined(PROP_STRCMP_USED) || defined(PROP_EQUALITY_USED)
   // strcmp() support
#  include <string.h>                // standard string support
#endif

#ifdef PROP_PERSISTENCE_USED
   // Persistence used
#  include <AD/persist/pobject.h>    // persistent object base class
#  include <AD/persist/pstream.h>    // persistent streams
#  include <AD/persist/pfactory.h>   // persistent object factories
#endif

#ifdef PROP_DYNAMIC_MESSAGING
   // Dynamic messaging object base class
#  include <AD/objc/objc.h>          // base class to dynamic messaging objects
#  include <AD/objc/class.h>         // meta class and other stuff
#endif

#ifdef PROP_VECTOR_USED
#  include <new.h>
   //  Template for calling the constructor
   //  (without allocating any memory)
   template <class T>
      inline void * operator new (size_t, T * p) { return p; }

   //  Allocate extra memory
   inline void * operator new (size_t, size_t n) { return ::operator new(n); }
#endif

#ifdef PROP_QUARK_USED
#   include <AD/strings/quark.h>
#endif

#ifdef PROP_BIGINT_USED
#   include <AD/numeric/bigint.h>
#endif

#ifdef PROP_GRAPHTYPE_USED
#   include <AD/graphtype/graphtype.h>
#endif

// Does your compiler support the type bool.
// If it does, uncomment out the following.
// Comparison primitives
#ifndef PROP_MISC_EQUALITY_DEFINED
#define PROP_MISC_EQUALITY_DEFINED
#define _equal_integer(x,y)   ((x) == (y))
#define _equal_real(x,y)      ((x) == (y))
#define _equal_character(x,y) ((x) == (y))
#define _equal_boolean(x,y)   ((x) == (y))
#define _equal_string(x,y)    (strcmp(x,y) == 0)
#define _less_integer(x,y)    ((x) < (y))
#define _less_real(x,y)       ((x) < (y))
#define _less_character(x,y)  ((x) < (y))
#define _less_boolean(x,y)    ((x) < (y))
#define _less_string(x,y)     (strcmp(x,y) < 0)
#endif

#ifdef PROP_EQUALITY_USED
#ifndef PROP_EQUALITY_DEFINED
#define PROP_EQUALITY_DEFINED
inline int equality_of(char x, char y)                     { return x == y; }
inline int equality_of(unsigned char x, unsigned char y)   { return x == y; }
inline int equality_of(int x, int y)                       { return x == y; }
inline int equality_of(unsigned int x, unsigned int y)     { return x == y; }
inline int equality_of(short x, short y)                   { return x == y; }
inline int equality_of(unsigned short x, unsigned short y) { return x == y; }
inline int equality_of(long x, long y)                     { return x == y; }
inline int equality_of(unsigned long x, unsigned long y)   { return x == y; }
inline int equality_of(double x, double y)                 { return x == y; }
inline int equality_of(const char * x, const char * y)  
   { return strcmp(x,y) == 0;}
#endif
#endif

#ifdef PROP_TRACE_ON
#   define PROP_TRACE(msg,file,line) prop_trace(msg,file,line)
#   include <AD/prop/trace.h>   // tracing
#endif

#ifdef PROP_TUPLE2_USED
#   include <AD/prop/tuple2.h>
#endif
#ifdef PROP_TUPLE3_USED
#   include <AD/prop/tuple3.h>
#endif
#ifdef PROP_TUPLE4_USED
#   include <AD/prop/tuple4.h>
#endif
#ifdef PROP_TUPLE5_USED
#   include <AD/prop/tuple5.h>
#endif
#ifdef PROP_TUPLE6_USED
#   include <AD/prop/tuple6.h>
#endif
#ifdef PROP_TUPLE7_USED
#   include <AD/prop/tuple7.h>
#endif
#ifdef PROP_TUPLE8_USED
#   include <AD/prop/tuple8.h>
#endif
#ifdef PROP_TUPLE9_USED
#   include <AD/prop/tuple9.h>
#endif
#ifdef PROP_TUPLE10_USED
#   include <AD/prop/tuple10.h>
#endif
#ifdef PROP_TUPLE11_USED
#   include <AD/prop/tuple11.h>
#endif
#ifdef PROP_TUPLE12_USED
#   include <AD/prop/tuple12.h>
#endif
