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

#ifndef prop_pretty_printing_io_stream_h
#define prop_pretty_printing_io_stream_h

#include <AD/pretty/pistream.h>
#include <AD/pretty/postream.h>

class iostream;

class PrettyIOStream : public PrettyIStream, public PrettyOStream
{
  PrettyIOStream (PrettyIOStream&);
  void operator = (PrettyIOStream&);
public:
  PrettyIOStream();
  PrettyIOStream(std::istream&);
  PrettyIOStream(std::ostream&);
  PrettyIOStream(iostream&);
  PrettyIOStream(std::istream&,std::ostream&);
  ~PrettyIOStream();

  std::istream& get_instream()
  {
    return PrettyIStream::stream();
  }
  std::ostream& get_onstream()
  {
    return PrettyOStream::stream();
  }
  std::istream& set_instream(std::istream& s)
  {
    return PrettyIStream::set_stream(s);
  }
  std::ostream& set_outstream(std::ostream& s)
  {
    return PrettyOStream::set_stream(s);
  }
};

#endif
