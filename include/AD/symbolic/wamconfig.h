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

#ifndef Warren_abstract_machine_configuration_h
#define Warren_abstract_machine_configuration_h

//////////////////////////////////////////////////////////////////////////////
//  Low level macros for implementing direct and indirect jumps.
//  This technique of fooling the C compiler to generate jumps appears
//  in the wamcc Prolog compiler system by Phillippe Codognet
//  and Daniel Diaz, INRIA-Rocquencourt.
//////////////////////////////////////////////////////////////////////////////

#if defined(__linux__)

#   define DEFINE_LABEL(label)  asm ("_" # label # ":");
#   define DIRECT_JUMP(label)   asm ("jmp _" # label);
#   define INDIRECT_JUMP(addr)  goto *(void *)addr;

#elif defined(sparc)

#   define DEFINE_LABEL(label)  asm ("_" # label # ":");
#   define DIRECT_JUMP(label)   { label(); return; }
#   define INDIRECT_JUMP(addr)  { (*(void (*)())addr)(); return; }

#else

#endif

#endif
