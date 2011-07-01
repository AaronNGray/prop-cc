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

#ifndef iostream_lexer_buffer_h
#define iostream_lexer_buffer_h

#include <iostream>
#include <AD/automata/lexerbuf.h>  // lexer buffer


//////////////////////////////////////////////////////////////////////////////
//  IOstream based lexer buffers.
//////////////////////////////////////////////////////////////////////////////

class IOLexerBuffer : public LexerBuffer
{
public:
  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////
  typedef LexerBuffer   Super;
  typedef Super::Symbol Symbol;
  typedef Super::State  State;
  typedef Super::Offset Offset;
  typedef Super::Rule   Rule;

protected:
  ///////////////////////////////////////////////////////////////////////////
  //  Internal buffer and other members
  ///////////////////////////////////////////////////////////////////////////
  size_t    buffer_size;  // size of the buffer
  std::istream * input;        // input stream

public:
  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  IOLexerBuffer();
  IOLexerBuffer(std::istream&);
  virtual ~IOLexerBuffer();

  ///////////////////////////////////////////////////////////////////////////
  //  Mutators
  ///////////////////////////////////////////////////////////////////////////
  virtual void set_stream (std::istream&);

protected:
  ///////////////////////////////////////////////////////////////////////////
  //  Default method for filling the buffer.
  //  This should be redefined in derive classes
  ///////////////////////////////////////////////////////////////////////////
  virtual size_t fill_buffer();
  virtual size_t read_buffer(char *, size_t);
  void allocate_buffer(size_t);
};

#endif
