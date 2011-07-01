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
#include <stdlib.h>
#include <AD/automata/iolexerstack.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Stack definition
//
//////////////////////////////////////////////////////////////////////////////

class IOLexerStackEntry
{
  IOLexerStackEntry(const IOLexerStackEntry&);
  void operator = (const IOLexerStackEntry&);
public:
  std::istream *           file_stream;
  char *              buffer;
  char *              buffer_limit;
  char *              cursor;
  char *              cursor_limit;
  size_t              buffer_size;
  int                 saved_char;
  Bool                anchored;
  Bool                pinned;
  Bool                more_input;
  int                 current_context;
  IOLexerStackEntry * next;

  inline
  IOLexerStackEntry(std::istream * f, char * b, char * bl, char * c, char * cl,
                    size_t n, int sc, Bool an, Bool pin, Bool more,
                    int context,
                    IOLexerStackEntry * nxt)
      : file_stream(f), buffer(b), buffer_limit(bl), cursor(c),
      cursor_limit(cl), buffer_size(n), saved_char(sc),
      anchored(an), pinned(pin), more_input(more), current_context(context),
      next(nxt)
  {}
  ~IOLexerStackEntry();
};

//////////////////////////////////////////////////////////////////////////////
//
//  Destructor for an entry
//
//////////////////////////////////////////////////////////////////////////////

IOLexerStackEntry::~IOLexerStackEntry()
{
  if (! pinned)
    delete [] buffer;
  if (next)
    delete next;
}

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

IOLexerStack:: IOLexerStack() : io_stack(0)
{}

IOLexerStack:: IOLexerStack(std::istream& in) : Super(in), io_stack(0)
{}

IOLexerStack::~IOLexerStack()
{
  delete io_stack;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Push a new stream
//
//////////////////////////////////////////////////////////////////////////////

void IOLexerStack::push_stream(std::istream& f)
{
  io_stack = new IOLexerStackEntry(
               input, buffer, buffer_limit, cursor, cursor_limit,
               buffer_size, saved_char, anchored, pinned, more_input,
               current_context, io_stack);
  init();
  allocate_buffer(4096);
  input = &f;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Pop the stream stack
//
//////////////////////////////////////////////////////////////////////////////

std::istream& IOLexerStack::pop_stream()
{
  if (io_stack == 0)
  {
    std::cerr << "Bug: IOLexerStack is empty in IOLexerStack::pop_stream()\n";
    exit(1);
  }
  if (! pinned)
    delete [] buffer;
  input           = io_stack->file_stream;
  buffer          = io_stack->buffer;
  buffer_limit    = io_stack->buffer_limit;
  cursor          = io_stack->cursor;
  cursor_limit    = io_stack->cursor_limit;
  buffer_size     = io_stack->buffer_size;
  saved_char      = io_stack->saved_char;
  anchored        = io_stack->anchored;
  pinned          = io_stack->pinned;
  more_input      = io_stack->more_input;
  current_context = io_stack->current_context;
  io_stack        = io_stack->next;
  return *input;
}
