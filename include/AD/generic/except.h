//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef exception_h
#define exception_h

//
//  This class is used to simulate a limited form of
//  exception and exception handling.
//

#include <setjmp.h>

class Exception
{
  const char * myName;

public:
  Exception(const char * n = 0) : myName(n)
  {}
  operator const char * ()
  {
    return myName;
  }
  const char * name ()
  {
    return myName;
  }
  void raise();
};

extern jmp_buf * __current_handler__;
extern Exception * __current_exception__;

#endif
