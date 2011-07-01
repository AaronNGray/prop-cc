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

#include <iostream>
#include <AD/pretty/pistream.h>

PrettyIStream::PrettyIStream() : the_stream(&std::cin) {}
PrettyIStream::PrettyIStream(std::istream& s) : the_stream(&s) {}
PrettyIStream::~PrettyIStream() {}

std::istream& PrettyIStream::set_stream( std::istream& s)
{
  std::istream * old = the_stream;
  the_stream = &s;
  return *old;
}

PrettyIStream& PrettyIStream::operator >> (char)
{
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (short& n)
{
  int i;
  operator>>(i);
  n = i;
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (unsigned short& n)
{
  int i;
  operator>>(i);
  n = i;
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (int&)
{
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (unsigned int& n)
{
  int i;
  operator>>(i);
  n = i;
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (long& n)
{
  int i;
  operator>>(i);
  n = i;
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (unsigned long& n)
{
  int i;
  operator>>(i);
  n = i;
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (float& n)
{
  double i;
  operator>>(i);
  n = i;
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (double&)
{
  return *this;
}

PrettyIStream& PrettyIStream::operator >> (char *)
{
  return *this;
}
