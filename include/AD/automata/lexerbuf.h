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

#ifndef lexer_buffer_h
#define lexer_buffer_h

#include <stdlib.h>
#include <AD/generic/generic.h>    // generic definitions
#include <AD/automata/dfatable.h>  // automata tables
#include <AD/automata/regexmat.h>  // regular expression string matcher

//////////////////////////////////////////////////////////////////////////////
//  This calls implements a backtrackable buffer for implementing
//  scanners.
//////////////////////////////////////////////////////////////////////////////

class LexerBuffer : public DFATables
{
public:
  ///////////////////////////////////////////////////////////////////////////
  //  Type definitions
  ///////////////////////////////////////////////////////////////////////////
  typedef DFATables     Super;
  typedef Super::Symbol Symbol;
  typedef Super::State  State;
  typedef Super::Offset Offset;
  typedef Super::Rule   Rule;

protected:
  ///////////////////////////////////////////////////////////////////////////
  //  Internal buffer and other members
  ///////////////////////////////////////////////////////////////////////////
  friend class RegexMatch;
  char * buffer;           // buffer
  char * buffer_limit;     // end of the buffer
  char * cursor;           // pointer to current token
  char * cursor_limit;     // pointer to the end of the token
  Bool   anchored;         // are we at the beginning of the line.
  Bool   pinned;           // is the buffer pinned?
  Bool   more_input;       // has more input?
  int    saved_char;       // saved last character from last token.
  int    current_context;  // current context number

  void   init();

public:
  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  LexerBuffer();
  LexerBuffer( char *);
  LexerBuffer( char *, size_t);
  virtual ~LexerBuffer();

  ///////////////////////////////////////////////////////////////////////////
  //  Some selectors
  ///////////////////////////////////////////////////////////////////////////
  inline int capacity() const
  {
    return buffer_limit - buffer;
  }

  inline int length() const
  {
    return cursor_limit - cursor;
  }

  inline operator const char* () const
  {
    return cursor;
  }

  inline operator char* ()
  {
    return cursor;
  }

  inline int context() const
  {
    return current_context;
  }

  inline Bool is_anchored() const
  {
    return anchored;
  }

  inline const char* text() const
  {
    return cursor;
  }

  inline char* text()
  {
    return cursor;
  }

  inline char operator [] (int i) const
  {
    return cursor[i];
  }

  inline char& operator [] (int i)
  {
    return cursor[i];
  }

  inline int lookahead() const
  {
    return saved_char;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Mutators
  ///////////////////////////////////////////////////////////////////////////
  virtual void reset();
  virtual void set_buffer( char *, size_t);
  void set_buffer( char *);
  inline  void set_anchored( Bool a = true)
  {
    anchored = a;
  }

  inline  void set_context( int c = 0)
  {
    current_context = c;
  }

  inline  void push_back( int n)
  {
    if (saved_char >= 0)
      *cursor_limit = saved_char;
    cursor_limit -= n;
    saved_char    = -1;
  }

protected:
  ///////////////////////////////////////////////////////////////////////////
  //  Default method for filling the buffer.
  //  This should be redefined in derive classes
  ///////////////////////////////////////////////////////////////////////////
  virtual size_t fill_buffer();
  virtual void   end_of_file();
  virtual void   error( const char * start, const char * stop);
};

//////////////////////////////////////////////////////////////////////////////
//  Tokenization method
//////////////////////////////////////////////////////////////////////////////

inline LexerBuffer::Rule RegexMatch::MatchText
    (State, LexerBuffer& B, const char *) const
{
  const char * nxt;
  // restore the saved character
  if (B.saved_char >= 0)
    *B.cursor_limit = B.saved_char;
  // Locate the next token
  for (;;)
  {
    Rule r = MatchText (B.current_context*2 + (B.anchored ? 2 : 1),
                        B.cursor_limit, B.buffer_limit - B.cursor_limit,
                        nxt, B.more_input);
    if (r == 0)
    {
      // No match, invoke the error handler
      B.error (B.cursor_limit, nxt);
      return -1;
    }
    else if (r == -1)
    {
      // Out of buffer, invoke the fill buffer handler
      size_t len = B.fill_buffer();
      if (len == 0)
        return -1;
    }
    else
    {
      // Got a rule.
      // Compute info
      B.cursor       = B.cursor_limit;
      B.cursor_limit = (char*)nxt;
      B.anchored     = B.cursor_limit[-1] == '\n';
      B.saved_char   = *B.cursor_limit;
      B.cursor_limit[0] = '\0';
      return r;
    }
  }
}

#endif
