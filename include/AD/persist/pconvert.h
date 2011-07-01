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

#ifndef persistent_conversions_h
#define persistent_conversions_h

#include <AD/persist/pconfig.h>

//////////////////////////////////////////////////////////////////////////////
//  Conversions on SUN sparc and Linux
//////////////////////////////////////////////////////////////////////////////

#if defined(sparc) || defined(linux)
#  include <sys/types.h>
#  include <netinet/in.h>
   inline void P_canonic_to_local(P_int16&  x)     { x = ntohs(x); }
   inline void P_canonic_to_local(P_uint16& x)     { x = ntohs(x); }
   inline void P_canonic_to_local(int&  x)         { x = ntohl(x); }
   inline void P_canonic_to_local(unsigned int& x) { x = ntohl(x); }
   inline void P_canonic_to_local(P_int32&  x)     { x = ntohl(x); }
   inline void P_canonic_to_local(P_uint32& x)     { x = ntohl(x); }
   inline void P_canonic_to_local(P_real32&)       {}
   inline void P_canonic_to_local(P_real64&)       {}

   inline void P_local_to_canonic(P_int16&  x)     { x = htons(x); }
   inline void P_local_to_canonic(P_uint16& x)     { x = htons(x); }
   inline void P_local_to_canonic(int&  x)         { x = htonl(x); }
   inline void P_local_to_canonic(unsigned int& x) { x = htonl(x); }
   inline void P_local_to_canonic(P_int32&  x)     { x = htonl(x); }
   inline void P_local_to_canonic(P_uint32& x)     { x = htonl(x); }
   inline void P_local_to_canonic(P_real32&)       {}
   inline void P_local_to_canonic(P_real64&)       {}
#  define P_FOUND
#endif

//////////////////////////////////////////////////////////////////////////////
// Default: assume BSD platforms.
//////////////////////////////////////////////////////////////////////////////

#if !defined(P_FOUND) && defined(unix)
#  include <sys/types.h>
#  include <netinet/in.h>
   inline void P_canonic_to_local(P_int16&  x)     { x = ntohs(x); }
   inline void P_canonic_to_local(P_uint16& x)     { x = ntohs(x); }
   inline void P_canonic_to_local(P_int32&  x)     { x = ntohl(x); }
   inline void P_canonic_to_local(P_uint32& x)     { x = ntohl(x); }
   inline void P_canonic_to_local(int&  x)         { x = ntohl(x); }
   inline void P_canonic_to_local(unsigned int& x) { x = ntohl(x); }
   inline void P_canonic_to_local(P_real32& x)     {}
   inline void P_canonic_to_local(P_real64& x)     {}

   inline void P_local_to_canonic(P_int16&  x)     { x = htons(x); }
   inline void P_local_to_canonic(P_uint16& x)     { x = htons(x); }
   inline void P_local_to_canonic(int&  x)         { x = htonl(x); }
   inline void P_local_to_canonic(unsigned int& x) { x = htonl(x); }
   inline void P_local_to_canonic(P_int32&  x)     { x = htonl(x); }
   inline void P_local_to_canonic(P_uint32& x)     { x = htonl(x); }
   inline void P_local_to_canonic(P_real32& x)     {}
   inline void P_local_to_canonic(P_real64& x)     {}
#  define P_FOUND
#endif

//////////////////////////////////////////////////////////////////////////////
//  The rest.  No conversions are used so it'll not work across
//  platforms if the byteorder is wrong.
//////////////////////////////////////////////////////////////////////////////

#if !defined(P_FOUND)
   inline void P_canonic_to_local(P_int16&  x)     {}
   inline void P_canonic_to_local(P_uint16& x)     {}
   inline void P_canonic_to_local(int&  x)         {}
   inline void P_canonic_to_local(unsigned int& x) {}
   inline void P_canonic_to_local(P_int32&  x)     {}
   inline void P_canonic_to_local(P_uint32& x)     {}
   inline void P_canonic_to_local(P_real32& x)     {}
   inline void P_canonic_to_local(P_real64& x)     {}

   inline void P_local_to_canonic(P_int16&  x)     {}
   inline void P_local_to_canonic(P_uint16& x)     {}
   inline void P_local_to_canonic(int&  x)         {}
   inline void P_local_to_canonic(unsigned int& x) {}
   inline void P_local_to_canonic(P_int32&  x)     {}
   inline void P_local_to_canonic(P_uint32& x)     {}
   inline void P_local_to_canonic(P_real32& x)     {}
   inline void P_local_to_canonic(P_real64& x)     {}
#endif

#endif
