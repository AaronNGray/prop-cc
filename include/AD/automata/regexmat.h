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
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef DFA_based_regular_expression_string_matcher_h
#define DFA_based_regular_expression_string_matcher_h

#include <AD/generic/generic.h>
#include <AD/automata/lexer.h>

//////////////////////////////////////////////////////////////////////////////
//  Class |RegexMatch| implements a dfa based regular expression
//  string matcher.
//////////////////////////////////////////////////////////////////////////////

class RegexMatch : public Lexer
{
  RegexMatch( const RegexMatch&);        // no copy constructor
  void operator = ( const RegexMatch&);  // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  // Inherit some types
  ///////////////////////////////////////////////////////////////////////////

  typedef Lexer         Super;
  typedef Super::Symbol Symbol;
  typedef Super::State  State;
  typedef Super::Offset Offset;
  typedef Super::Rule   Rule;

public:

  ///////////////////////////////////////////////////////////////////////////
  // Constructor
  ///////////////////////////////////////////////////////////////////////////

  RegexMatch( const Offset        base_table  [],
              const State         check_table [],
              const State         def_table   [],
              const State         next_table  [],
              const Rule          rule_table  [],
              const unsigned char equiv_table []
            )
      : Lexer(base_table, check_table, def_table, next_table,
              rule_table, equiv_table)
  {}

  ///////////////////////////////////////////////////////////////////////////
  // String matching operations.
  //    Returns the matching rule number (which is compiled in the tables).
  //    If more than one rule matches that the highest priority rule is
  //    returned.  Rules are numbered from 1 - n.
  //
  //    If nothing matches then 0 is returned.
  ///////////////////////////////////////////////////////////////////////////

  inline Rule MatchText( const char *) const;
  inline Rule MatchText( const char *, int) const;
  inline Rule MatchText( const char *, const char *&) const;
  inline Rule MatchText( const char *, int, const char *&) const;
  inline Rule MatchText( State, const char *, const char *&) const;
  inline Rule MatchText( State, const char *, int, const char *&, Bool = false) const;
  Rule MatchText( State, class LexerBuffer&, const char *) const;
};

//////////////////////////////////////////////////////////////////////////////
//  Matching operation on strings.  The entire string is scanned and no
//  backtracking is performed.  The string must be null-terminated.
//////////////////////////////////////////////////////////////////////////////

inline RegexMatch::Rule RegexMatch::MatchText( register const char * string) const
{
  register State state;
  register unsigned char c;
  for (state = start_state; (c = *string) != '\0'; string++)
    if ((state = go(state,c)) == 0)
      return 0;
  return accept(state);
}

//////////////////////////////////////////////////////////////////////////////
//  Matching operations on strings.  This is the same as the previous
//  version except that an extra length parameters is used.  Nul's may
//  be embedded in the string.
//////////////////////////////////////////////////////////////////////////////

inline RegexMatch::Rule RegexMatch::MatchText
(register const char * string, register int len) const
{
  register State state;
  for (state = start_state; len > 0; len--)
  {
    register unsigned char c = *string++;
    if ((state = go(state,c)) == 0)
      return 0;
  }
  return accept(state);
}

//////////////////////////////////////////////////////////////////////////////
//  Matching operation on string.
//  This version assumes backtracking is used.  We'll only try to Match
//  the longest substring.  A pointer to the rest of the string is returned.
//  The user must also supply a start state.
//
//  The special code -1 is returned if the buffer space has run out
//  without reaching the end of the stream.
//
//  Caution: the tables must be generated with the backtracking option.
//////////////////////////////////////////////////////////////////////////////

inline RegexMatch::Rule RegexMatch::MatchText
(register State state, register const char * s, const char *& nxt) const
{
  register unsigned char c;
  Rule          last_rule = 0;
  const char *  last_position;
  do
  {
    register Rule r = accept(state = go(state,c = *s++));
    if (r > 0)
    {          // state is backtrackable
      last_rule = r;
      last_position = s;
    }
    else if (r == -1)
    { // dead end state
      // try to backtrack if possible
      if (last_rule > 0)
      {
        // we have a last rule and position, just use it dude!
        nxt = last_position;
        return last_rule;
      }
      else
      {
        // problem, return 0 for error
        // next is set to the error position.
        nxt = s;
        return 0;
      }
    }
    else if (r < -1)
    { // last posible accept state
      // this is the last possible position
      nxt = s;
      return -r-1;
    }
  }
  while (c);

  // we have run out of buffer
  // return -1 to signal this condition
  return -1;
}

//////////////////////////////////////////////////////////////////////////////
//  The version assumes that the buffer length has been explicitly
//  supplied.
//////////////////////////////////////////////////////////////////////////////

inline RegexMatch::Rule RegexMatch::MatchText
(
  State         state,
  const char *  s,
  int           len,
  const char *& n,
  Bool          more
) const
{
  Rule          last_rule = 0;
  const char *  last_position;
  for (;;)
  {
    Rule r;
    if (len == 0)
    {
      if (more)
        break;
      else
        goto DONE;
    }
    else
    {
      state = go(state,*s++);
      r     = accept(state);
    }
    if (r > 0)
    {          // state is backtrackable
      last_rule = r;
      last_position = s;
      --len;
    }
    else if (r == -1)
    { // dead end state
DONE:
      // try to back track if possible
      if (last_rule > 0)
      {
        // we have a last rule and position, just use it dude!
        n = last_position;
        return last_rule;
      }
      else
      {
        // problem, return 0 for error
        // n is set to the error position.
        n = s;
        return 0;
      }
    }
    else if (r < -1)
    { // last posible accept state
      // this is the last possible position
      n = s;
      return -r-1;
    }
  }

  // we have run out of buffer
  // return -1 to signal this condition
  return -1;
}

//////////////////////////////////////////////////////////////////////////////
//  These version assumes the default start state should be used.
//////////////////////////////////////////////////////////////////////////////

inline RegexMatch::Rule RegexMatch::MatchText( const char * s, const char *& n) const
{
  return MatchText( start_state, s, n);
}
inline RegexMatch::Rule RegexMatch::MatchText( const char * s, int len, const char *& n) const
{
  return MatchText( start_state, s, len, n);
}

#endif
