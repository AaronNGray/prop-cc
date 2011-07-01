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

#include <iostream>
#include <string.h>
#include <AD/automata/lexerbuf.h>
#include <AD/strings/charesc.h>

void LexerBuffer::init()
{
  buffer = buffer_limit = cursor = cursor_limit = 0;
  anchored = true;
  current_context = 0;
  saved_char = -1;
  pinned = false;
  more_input = false;
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////
LexerBuffer:: LexerBuffer()
{
  init();
  pinned = false;
}

LexerBuffer::LexerBuffer( char * s)
{
  init();
  pinned = true;
  cursor = cursor_limit = buffer = s;
  buffer_limit = s + strlen(s);
}

LexerBuffer::LexerBuffer( char * s, size_t l)
{
  init();
  pinned = true;
  cursor = cursor_limit = buffer = s;
  buffer_limit = s + l;
}

LexerBuffer::~LexerBuffer()
{
  reset();
}

//////////////////////////////////////////////////////////////////////////////
//  Default reseting method
//////////////////////////////////////////////////////////////////////////////

void LexerBuffer::reset()
{
  if (! pinned)
    delete [] buffer;
  init();
}

//////////////////////////////////////////////////////////////////////////////
//  Default fill buffer method does nothing
//////////////////////////////////////////////////////////////////////////////

size_t LexerBuffer::fill_buffer()
{
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Set the buffer size
//////////////////////////////////////////////////////////////////////////////

void LexerBuffer::set_buffer( char * s, size_t len)
{
  pinned = true;
  cursor = cursor_limit = buffer = s;
  buffer_limit = s + len;
}

void LexerBuffer::set_buffer( char * buf)
{
  set_buffer( buf, strlen(buf));
}

//////////////////////////////////////////////////////////////////////////////
//  Default error handler just prints the buffer.
//  We'll be nice and print all non-printable character in escaped
//  format.
//////////////////////////////////////////////////////////////////////////////

void LexerBuffer::error( const char * start, const char * stop)
{
  std::cerr << "[ Scanner error in context " << current_context << ": '";
  char buf[32];
  for ( ;start < stop; start++)
  {
    print_char(buf,*start);
    std::cerr << buf;
  }
  std::cerr << "' ]\n";
}

//////////////////////////////////////////////////////////////////////////////
//  Default end_of_file does nothing.
//////////////////////////////////////////////////////////////////////////////

void LexerBuffer::end_of_file()
{}
