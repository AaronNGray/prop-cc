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
#include <string>
#include <AD/automata/iolexerbuf.h>

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

IOLexerBuffer:: IOLexerBuffer() : input(&std::cin)
{
  allocate_buffer(4096);
}

IOLexerBuffer:: IOLexerBuffer(std::istream& in) : input(&in)
{
  allocate_buffer(4096);
}

IOLexerBuffer::~IOLexerBuffer()
{}

//////////////////////////////////////////////////////////////////////////////
//  Allocate the space for a buffer
//////////////////////////////////////////////////////////////////////////////

void IOLexerBuffer::allocate_buffer( size_t n)
{
  buffer = buffer_limit = cursor = cursor_limit = new char [n+1];
  buffer_size = n;
  more_input = true;
  pinned = false; // buffer is not pinned, can be deleted
}

//////////////////////////////////////////////////////////////////////////////
//  Method to get new input from the std::istream
//////////////////////////////////////////////////////////////////////////////

size_t IOLexerBuffer::read_buffer(char * buf, size_t n)
{  // Input one line at a time for interactive use.
  size_t len;

  len = input->getline(buf, n - 1).gcount();

  if (len && buf[0] != 0x0A)
    buf[len-1] = 0x0A;

  buf[len] = '\0';

  return len;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to fill the input buffer
//////////////////////////////////////////////////////////////////////////////

size_t IOLexerBuffer::fill_buffer()
{  //  Shift the remaining contents to the begining of the buffer.
  size_t left_over = buffer_limit - cursor_limit;
  memcpy(buffer, cursor_limit, left_over);
  int count = read_buffer(buffer + left_over,buffer_size - left_over);
  more_input = count > 0;
  buffer_limit = buffer + left_over + count;
  cursor = cursor_limit = buffer;
  return count;
}

//////////////////////////////////////////////////////////////////////////////
//  Set/reset the input buffer
//////////////////////////////////////////////////////////////////////////////

void IOLexerBuffer::set_stream(std::istream& in)
{  // Yank back the saved character
  if (buffer && saved_char >= 0)
    *cursor_limit = saved_char;
  saved_char = -1;
  // Reset the buffer
  cursor = cursor_limit = buffer;
  input = &in;
}
