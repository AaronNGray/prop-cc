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

#ifndef regular_expression_search_h
#define regular_expression_search_h

/////////////////////////////////////////////////////////////////////////////
//  Class |RegExp| implements a regular expression searching package.
//  A regular expression pattern is first ``compiled'' into a
//  non-deterministic finite automata (NFA) in a compact form.
//  Searching then involved actually running a text string through
//  this NFA.  Non-determinism is handled by recursion and backtracking.
//
/////////////////////////////////////////////////////////////////////////////

#include <AD/generic/generic.h>    // Generic definitions

class RegExp
{
public:
  enum MetaChar {
    META_STAR,      // Meta character for Kleene star `*'
    META_PLUS,      // Meta character Non-reflexive Kleene star `+'
    META_OPEN,      // Meta character for '('
    META_CLOSE,     // Meta character for ')'
    META_SET_OPEN,  // Meta character '['
    META_SET_CLOSE, // Meta character ']'
    META_OPTIONAL,  // Meta character for '?'
    META_BEGIN,     // Meta character for '^', the beginning of a line
    META_END,       // Meta character for '$', the end of a line
    META_RANGE,     // Meta character for '-', range for characters
    META_WILD,      // Meta character for '.', the wild card
    META_OR,        // Meta character for '|', disjunction
    META_ESCAPE,    // Escape meta character `\'
    META_EOP,       // End of pattern, normally '\0'
    META_NONE       // A non-meta character
  };

  typedef char Opcode;

  /////////////////////////////////////////////////////////////////////////
  // If matching is successful, the location of each pair of
  // matching substrings within the patterns '(' and ')' is
  // marked and remembered.  This make it possible to extract
  // substring within a pattern easily.
  //
  // We'll allow a maximum of 10 groups within a pattern and
  // these are cached within the following fields.
  /////////////////////////////////////////////////////////////////////////

private:
  // maximum number of paranthesized groups
  enum { REGEXP_MAX_GROUPS = 10 };
  const char * myText;               // The current text string.
  int left  [ REGEXP_MAX_GROUPS ];   // starting point of group `n'
  int right [ REGEXP_MAX_GROUPS ];   // ending of group `n'
  const char * matchedText;
  const char * matchedTextEnd;

  /////////////////////////////////////////////////////////////////////////
  // We'll represent the NFA in linear form as a set primitive string
  // matching and branching(backtracking) instructions.  These instructions
  // will appear like ``opcodes'' of some abstract machine.  Like this:
  /////////////////////////////////////////////////////////////////////////
  Opcode * nfa;        // The list of instructions representing the nfa
  int size;            // The size of the nfa.
  int minMatchLen;     // The minimum length of matching text.

  /////////////////////////////////////////////////////////////////////////
  // Constructors and destructors
  /////////////////////////////////////////////////////////////////////////

public:
  RegExp() : nfa(0)
  {}
  RegExp(const RegExp&);
  RegExp(const char * pattern, const char * meta = 0) : nfa(0)
  {
    this->compile(pattern,meta);
  }
  ~RegExp()
  {
    delete nfa;
  }

  /////////////////////////////////////////////////////////////////////////
  // Assignment
  /////////////////////////////////////////////////////////////////////////
  RegExp& operator = (const RegExp&);

  /////////////////////////////////////////////////////////////////////////
  // Recompile a pattern
  /////////////////////////////////////////////////////////////////////////
  RegExp& compile (const char * pattern, const char * meta = 0);
  inline RegExp& operator = (const char * pattern)
  {
    return this->compile(pattern);
  }
  inline Bool ok()
  {
    return nfa != 0;
  }

  /////////////////////////////////////////////////////////////////////////
  // String matching
  /////////////////////////////////////////////////////////////////////////
  int Match(const char * text, int length = -1);

  /////////////////////////////////////////////////////////////////////////
  // Retrieve information about matching substrings
  /////////////////////////////////////////////////////////////////////////
  inline const char * operator[] (int i) const
  {
    return myText + left[i];
  }
  inline const char * operator[] (char i) const
  {
    return myText + left[i];
  }
  inline int begin()      const
  {
    return matchedText - myText;
  }
  inline int end()        const
  {
    return matchedTextEnd - myText;
  }
  inline int start(int i) const
  {
    return left[i];
  }
  inline int stop(int i)  const
  {
    return right[i];
  }
  inline int len(int i)   const
  {
    return right[i] - left[i] + 1;
  }

  /////////////////////////////////////////////////////////////////////////
  // Internal matching and compilation function
  /////////////////////////////////////////////////////////////////////////

private:
  const char * grep(const Opcode *, const char *, const char *);
  const char * times(int m, int n, const char *, const char *, const Opcode *);
  int comp(const char * pattern, const MetaChar [], Bool emit);
  friend void shift(Opcode *,Opcode *,int);
  int minMatch(const Opcode *);
};

#endif
