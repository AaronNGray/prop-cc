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

#include <stdlib.h>
#include <setjmp.h>
#include <iostream.h>
#include <AD/generic/except.h>

jmp_buf * __current_handler__;
Exception * __current_exception__;

void Exception::raise()
{  if (__current_handler__) {
      __current_exception__ = this;
      longjmp(*__current_handler__,1);
   }
   std::cerr << "Uncaught exception " << name() << '\n';
   exit(1);
}
