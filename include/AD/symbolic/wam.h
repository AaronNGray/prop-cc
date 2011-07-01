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
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef Warren_abstract_machine_h
#define Warren_abstract_machine_h

#include <AD/symbolic/wamconfig.h>

//////////////////////////////////////////////////////////////////////////////
//  This class implements a WAM-like abstract machine for Prolog compilation.
//  However, we diverge in a number of (potentially) significant ways
//  with traditional implementations.  In particular, the surface language
//  we have in mind is based on strong static typing with parametric
//  polymorphism; furthermore, coexistence with C++ data structures must
//  be preserved.
//////////////////////////////////////////////////////////////////////////////

class WAM
{
  WAM(const WAM&);                // no copy constructor
  void operator = (const WAM&);   // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  WAM instructions.
  ///////////////////////////////////////////////////////////////////////////

public:
  enum Inst
  {  allocate,
     deallocate,
     call,
     proceed,
     try
       ,
       trust,
       try_me_else,
       retry_me_else,
       trust_me_else_fail,
       switch_on_term
    };

  typedef long Word;       // a word in memory
  typedef void (*Cont)();  // continuation

protected:

  Word * TP;  // trail pointer
  Word * CP;  // choice point

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  WAM();
  virtual ~WAM();
};

#endif
