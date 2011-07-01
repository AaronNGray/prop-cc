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

datatype List<T> : public MEM :: inline = #[] | #[ T ... List<T> ]
and Pair<A,B> : public MEM :: inline = makepair { fst : A, snd : B }
where type Id  = const char *  // Identifier
and Ids = List<Id>      // Identifier list
;

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
