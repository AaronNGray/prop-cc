//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef lexical_scanning_stream_h
#define lexical_scanning_stream_h

/////////////////////////////////////////////////////////////////////////////
// Class LexScanner implements a lexical scanner with buffering.
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <AD/generic/generic.h>
#include <AD/automata/lexer.h>


/////////////////////////////////////////////////////////////////////////////
//  The implementation of the Lexer is hidden for safety.
/////////////////////////////////////////////////////////////////////////////

class LexScanner : private Lexer
{

  LexScanner(const LexScanner&);           // no copy constructor
  void operator = (const LexScanner&);  // no assignment

public:

  /////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  /////////////////////////////////////////////////////////////////////
  typedef Lexer         Super;
  typedef Super::State  State;
  typedef Super::Symbol Symbol;
  typedef Super::Offset Offset;
  typedef Super::Rule   Rule;

  /////////////////////////////////////////////////////////////////////
  //  Options
  /////////////////////////////////////////////////////////////////////
  enum Option
  {  Line_buffering  = 0, // use line buffering (for interactive scanners)
     Block_buffering = 1  // use block buffering (faster)
  };

protected:

  ////////////////////////////////////////////////////////////////////////
  //  Buffers and states information.
  ////////////////////////////////////////////////////////////////////////
  char *  buffer;         // caches the last bunch of input
  char *  limit;          // end of buffer
  char *  read_limit;     // end of data
  char *  cursor;         // points to the next input character
  char *  tok;            // points to the current token
  Bool    anchored;       // are we at the beginning of the line?
  int     len;            // the length of the current token
  int     save_char;      // character saved
  int     current_context;// current context

  /////////////////////////////////////////////////////////////////////
  //  Method to replenish the input buffer.  Returns the number of
  //  characters read.
  /////////////////////////////////////////////////////////////////////
  virtual int fill_buffer( std::istream& stream, int read_size, Option option);

public:

  ////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////
  LexScanner(
         const Offset        base_table  [],
         const State         check_table [],
         const State         def_table   [],
         const State         next_table  [],
         const Rule          rule_table  [],
         const unsigned char equiv_table []
         )
      : Lexer(base_table, check_table, def_table, next_table,
              rule_table, equiv_table),
      buffer(0), limit(0), read_limit(0), cursor(0)
  {
    open();
  }
  virtual ~LexScanner()
  {
    close();
  }

  ////////////////////////////////////////////////////////////////////////
  // Scanning:
  //     open()         -- begin scanning (set up buffer, etc)
  //     close()        -- end scanning (clean up buffer, etc)
  //     begin()        -- start at a new context
  //     advance()      -- scan and get the next rule
  //     fast_advance() -- scan without backtracking
  ////////////////////////////////////////////////////////////////////////
  virtual void   open();
  virtual void   close();
  void begin( int context = 0)
  {
    current_context = context;
  }
  Rule advance( std::istream&, int = 4096, Option = Line_buffering);
  Rule fast_advance( std::istream&, int = 4096, Option = Line_buffering);

  ////////////////////////////////////////////////////////////////////////
  //  Buffer management
  //     token()       -- return the current matched token
  //     length()      -- return the length of the current token
  //     peek_buffer() -- return the cached input characters
  //     peek_length() -- return the number of characters cached
  ////////////////////////////////////////////////////////////////////////
  char* token() const
  {
    return tok;
  }
  int length() const
  {
    return len;
  }
  char* peek_buffer() const
  {
    return cursor;
  }
  int peek_length() const
  {
    return read_limit - cursor;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Miscellaneous:
  //     error()        -- print error message and abort
  ////////////////////////////////////////////////////////////////////////
  virtual void error( const char file_name[], int line_number);
};

////////////////////////////////////////////////////////////////////////////
//  For efficiency, the scanning functions are inlined.
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  Advance the machine and return the matching rule.
//  The convention of accept state number is as follows:
//     0      --- not an accept state and have at least one outgoing state
//     -1     --- not an accept state and have no outgoing state.
//     r > 0  --- an accept state for rule $r-1$(zero based) with at least
//                one outgoing state.
//     r < -1 --- an accept state for rule $-r-2$ with no outgoing state.
//
//  Returns the rule number (zero based) normally.
//  Returns EOF if end of file is found.
//  Returns EOF-1 if the scanner is jammed.
/////////////////////////////////////////////////////////////////////////////

inline Lexer::Rule LexScanner::advance
(std::istream& stream, int read_size, LexScanner::Option option)
{
  register State s = current_context * 2 + (anchored ? 2 : 1);
  register unsigned char c;
  register Rule r = 0, last_accept_rule;
  register char * last_accept_pos;

  if (save_char >= 0)
    *cursor = save_char;
  last_accept_rule = 0;
  last_accept_pos  = 0;
  tok = cursor;

  for (;;)
  {
    if (cursor == read_limit)
      if (fill_buffer(stream, read_size, option) == 0)
      {
        if (tok == read_limit)
        {
          len = 0;
          tok = 0;
          return EOF;
        }
        else
        {
          r = -r-1;
          goto do_it;
        }
      }
    c = (unsigned char)*cursor++;
    s = go (s, c);
    r = accept(s);

do_it:
    if (r > 0)
    { // a backtrackable accept state; keep looking ahead
      last_accept_rule = r;
      last_accept_pos  = cursor;
    }
    else if (r == 0)
    { // not an accept state; scan further
      // scan scan scan
    }
    else if (r == -1)
    { // not an accept state and is a dead end
      if (last_accept_pos != 0)
      { // backtrack
        cursor = last_accept_pos;
        len = cursor - tok;
        save_char = *cursor;
        *cursor = '\0';
        anchored = cursor[-1] == '\n';
        return last_accept_rule - 1;
      }
      else
      { // no backtrackable position, error!!!
        tok = 0;
        len = 0; // nothing possible
        return EOF-1;
      }
    }
    else
    { // a dead end accept state is found
      len = cursor - tok;
      save_char = *cursor;
      *cursor = '\0';
      anchored = cursor[-1] == '\n';
      return -r-2;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//  This is similar to above except that we don't do any backtracking: i.e.
//  we return the first rule that matches rather than the first rule that
//  matches the longest.  The scanning algorithm is simpler and faster
//  with this routine.   The lexer should be generated without using the
//  Backtracking option.
/////////////////////////////////////////////////////////////////////////////

inline Lexer::Rule LexScanner::fast_advance
(std::istream& stream, int read_size, LexScanner::Option option)
{
  register State s = current_context * 2 + (anchored ? 2 : 1);
  tok = cursor;
  if (save_char >= 0)
    *cursor = save_char;
  for (;;)
  {
    if (cursor == read_limit)
      if (fill_buffer(stream, read_size, option) == 0)
      {
        if (tok == read_limit)
        { // end of file
          tok = 0;
          len = 0;
          return EOF;
        }
        else
        { // error
          tok = 0;
          len = 0;
          return EOF-1;
        }
      }
    register unsigned char c = (unsigned char)*cursor++;
    if ((s = go (s, c)) == 0)
    { // error state??
      tok = 0;
      len = 0; // nothing possible
      return EOF-1;
    }
    register Rule r = accept(s);
    if (r > 0)
    {
      len = cursor - tok;
      save_char = *cursor;
      *cursor = '\0';
      anchored = cursor[-1] == '\n';
      return r-1;
    }
  }
}

#endif
