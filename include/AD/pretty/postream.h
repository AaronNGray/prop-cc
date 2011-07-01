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

#ifndef prop_pretty_printing_output_stream_h
#define prop_pretty_printing_output_stream_h

#include <iostream>
#include <AD/generic/generic.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Output to a pretty printed stream
//
//////////////////////////////////////////////////////////////////////////////

class PrettyOStream
{
  PrettyOStream(const PrettyOStream&);
protected:
  enum TokenClass { NONE, IDENTIFIER, DELIMITER, NUMBER, OBJECT };
  std::ostream*   the_stream;
  int        indentation;
  TokenClass last_token;
  int        spaces_in_tab;

  void init();
public:
  PrettyOStream();
  explicit PrettyOStream(std::ostream&);
  virtual ~PrettyOStream();

  std::ostream& stream() const
  {
    return *the_stream;
  }
  virtual PrettyOStream& set_tab_spacing(int);
  virtual std::ostream& set_stream(std::ostream&);
  virtual PrettyOStream& indent();
  virtual PrettyOStream& unindent();
  virtual PrettyOStream& tab();
  virtual PrettyOStream& newline();
  virtual PrettyOStream& nospace();
  virtual PrettyOStream& space();

  //   PrettyOStream& operator << (void *);
  PrettyOStream& operator << (char);
  PrettyOStream& operator << (int);
  PrettyOStream& operator << (double);
  PrettyOStream& operator << (const char *);
  PrettyOStream& operator << (void (*f)(PrettyOStream&))
  {
    (*f)(*this);
    return (*this);
  }
};

extern void indent(PrettyOStream&);
extern void unindent(PrettyOStream&);
extern void tab(PrettyOStream&);
extern void newline(PrettyOStream&);
extern void begin_group(PrettyOStream&);
extern void end_group(PrettyOStream&);
extern void nospace(PrettyOStream&);
extern void space(PrettyOStream&);

#endif
