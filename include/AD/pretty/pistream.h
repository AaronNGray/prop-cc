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

#ifndef prop_pretty_printing_input_stream_h
#define prop_pretty_printing_input_stream_h

#include <iostream>
#include <AD/generic/generic.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Input from a pretty printed stream
//
//////////////////////////////////////////////////////////////////////////////

class PrettyIStream
{
  PrettyIStream(const PrettyIStream&);
protected:
  std::istream* the_stream;
public:
  PrettyIStream();
  explicit PrettyIStream(std::istream&);
  virtual ~PrettyIStream();

  std::istream& stream() const
  {
    return *the_stream;
  }
  virtual std::istream& set_stream(std::istream&);

  PrettyIStream& operator >> (char);
  PrettyIStream& operator >> (short&);
  PrettyIStream& operator >> (unsigned short&);
  PrettyIStream& operator >> (int&);
  PrettyIStream& operator >> (unsigned int&);
  PrettyIStream& operator >> (long&);
  PrettyIStream& operator >> (unsigned long&);
  PrettyIStream& operator >> (float&);
  PrettyIStream& operator >> (double&);
  PrettyIStream& operator >> (char *);
  PrettyIStream& operator >> (void (*f)(PrettyIStream&))
  {
    (*f)(*this);
    return *this;
  }
};

#endif
