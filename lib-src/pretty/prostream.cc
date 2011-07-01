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
#include <AD/strings/charesc.h>
#include <AD/pretty/postream.h>

PrettyOStream::PrettyOStream() : the_stream(&std::cout)
{
  init();
}

PrettyOStream::PrettyOStream(std::ostream& s) : the_stream(&s)
{
  init();
}

PrettyOStream::~PrettyOStream()
{
  init();
}

void PrettyOStream::init()
{
  indentation   = 0;
  last_token    = DELIMITER;
  spaces_in_tab = 3;
}

std::ostream& PrettyOStream::set_stream(std::ostream& s)
{
  std::ostream * old = the_stream;
  the_stream = &s;
  return *old;
}

PrettyOStream& PrettyOStream::set_tab_spacing(int s)
{
  spaces_in_tab = s;
  return *this;
}

PrettyOStream& PrettyOStream::indent()
{
  indentation++;
  return *this;
}

PrettyOStream& PrettyOStream::unindent()
{
  indentation--;
  return *this;
}

PrettyOStream& PrettyOStream::tab()
{
  int spaces = indentation * spaces_in_tab;
  for (int i = 0; i < spaces; i++)
    (*the_stream) << ' ';
  last_token = PrettyOStream::DELIMITER;
  return *this;
}

PrettyOStream& PrettyOStream::newline()
{
  last_token = PrettyOStream::DELIMITER;
  (*the_stream) << '\n';
  return *this;
}

PrettyOStream& PrettyOStream::nospace()
{
  last_token = PrettyOStream::DELIMITER;
  return *this;
}

PrettyOStream& PrettyOStream::space()
{
  if (last_token != DELIMITER)
    (*the_stream) << ' ';
  last_token = PrettyOStream::NONE;
  return *this;
}

// PrettyOStream& PrettyOStream::operator << (void *)
// {
//   return *this;
// }

PrettyOStream& PrettyOStream::operator << (char x)
{
  switch (x)
  {
  case '[':
  case '(':
  case '{':
  case ',':
  case ';':
  case '<':
    last_token = DELIMITER;
    break;
  default:
    last_token = NONE;
    break;
  }
  (*the_stream) << x;
  return *this;
}

PrettyOStream& PrettyOStream::operator << ( int x)
{
  if (last_token != DELIMITER)
    (*the_stream) << ' ';
  last_token = NUMBER;
  (*the_stream) << x;
  return *this;
}

PrettyOStream& PrettyOStream::operator << (double x)
{
  if (last_token != DELIMITER)
    (*the_stream) << ' ';
  last_token = NUMBER;
  (*the_stream) << x;
  return *this;
}

PrettyOStream& PrettyOStream::operator << (const char * x)
{
  if (last_token != DELIMITER)
    (*the_stream) << ' ';
  last_token = IDENTIFIER;
  (*the_stream) << x;
  return *this;
}

void indent( PrettyOStream& s)
{
  s.indent();
}

void unindent( PrettyOStream& s)
{
  s.unindent();
}

void tab( PrettyOStream& s)
{
  s.tab();
}

void newline( PrettyOStream& s)
{
  s.newline();
}

void nospace( PrettyOStream& s)
{
  s.nospace();
}

void space( PrettyOStream& s)
{
  s.space();
}
