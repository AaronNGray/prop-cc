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
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef persistent_configuration_h
#define persistent_configuration_h

//////////////////////////////////////////////////////////////////////////////
//  Hardwired types with fixed sizes.
//////////////////////////////////////////////////////////////////////////////

typedef char            P_char;
typedef unsigned char   P_uchar;
typedef short           P_int16;
typedef unsigned short  P_uint16;
typedef long            P_int32;
typedef unsigned long   P_uint32;
typedef float           P_real32;
typedef double          P_real64;

typedef P_int32 P_OBJECT_TYPEID;
typedef P_int32 P_OBJECT_MARKER;

//////////////////////////////////////////////////////////////////////////////
//  Special control tags
//////////////////////////////////////////////////////////////////////////////

#ifdef PSTREAM_IMPLEMENTATION
typedef P_int32 P_STREAM_TAG;
typedef P_uint32 P_ObjectAddr;
//typedef void * P_ObjectAddr;

#define P_VERSION_STRING     "ADLIB persistent store format version 1.0"
#define P_GROUP_START_TAG    P_STREAM_TAG(0xff00)
#define P_GROUP_END_TAG      P_STREAM_TAG(0xff01)
#define P_VERSION_TAG        P_STREAM_TAG(0xff02)
#define P_DOCUMENTATION_TAG  P_STREAM_TAG(0xff03)
#define P_DATA_TAG           P_STREAM_TAG(0xff04)
#define P_NEW_OBJECT_TAG     P_STREAM_TAG(0xff05)
#define P_OBJECT_NAME_TAG    P_STREAM_TAG(0xff11)
#define P_OBJECT_ID_TAG      P_STREAM_TAG(0xff12)
#define P_STRING_TAG         P_STREAM_TAG(0xff13)
#define P_NULL_STRING_TAG    P_STREAM_TAG(0xff14)

#define P_FIRST_MARKER       P_OBJECT_MARKER(-4096)

#define P_IS_MARKER(m)     ((m) <= P_FIRST_MARKER)
#define P_IS_UNBOXED(p)    (P_uint32(p) < -P_FIRST_MARKER)
#define P_IS_TYPEID(id)    ((id) > 0)
#define P_IS_NEW_OBJECT(m) ((m) == P_NEW_OBJECT_TAG)

#define P_ADDR_MASK        P_ObjectAddr(0xcdcdcdcd)
#define P_WRAP_ADDR(addr)  (P_ObjectAddr(addr) ^ P_ADDR_MASK)
//#define P_WRAP_ADDR(addr)  (P_ObjectAddr(addr))
#endif

#endif
