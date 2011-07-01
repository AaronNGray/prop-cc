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
// Allen Leung (leunga@valis.cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef backend_tools_code_emitter_h
#define backend_tools_code_emitter_h

#include <stdarg.h>
#include <iostream>
#include <AD/generic/generic.h>

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for code emitters
//
///////////////////////////////////////////////////////////////////////////////

class CodeEmitter
{
  CodeEmitter(const CodeEmitter&);         // no copy constructor
  void operator = (const CodeEmitter&);    // no assignment
  ////////////////////////////////////////////////////////////////////////////
  //
  //   Type definitions
  //
  ////////////////////////////////////////////////////////////////////////////

public:
  typedef const char *  ActionName;
  typedef unsigned char ActionAbbrev;
  typedef va_list (*Action)(CodeEmitter&, va_list);
  typedef va_list (*CharAction)(CodeEmitter&,unsigned char,va_list);

protected:
  std::ostream *                 out;               // internal stream.
  Action                    abbrev_table[256]; // action table
  CharAction                char_table[256];   // character action table
  int                       line_number;       // line numbering
  int                       tabbing;           // spaces to indent
  Bool                      anchored;          // is anchored?
  const char *              format_ptr;        // current format pointer
  class CodeEmitterIntern * intern;            // internal stuff

  ////////////////////////////////////////////////////////////////////////////
  //
  //   Constructors and destructor
  //
  ////////////////////////////////////////////////////////////////////////////

public:
  CodeEmitter();
  CodeEmitter(std::ostream&);
  virtual ~CodeEmitter();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to open and close the code emitter
  //
  ////////////////////////////////////////////////////////////////////////////

  virtual CodeEmitter& open(std::ostream&);
  virtual CodeEmitter& close();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Method to emit code (takes variable argument list)
  //
  ////////////////////////////////////////////////////////////////////////////
  virtual CodeEmitter& emit (const char *, ...);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to register new actions.
  //
  ////////////////////////////////////////////////////////////////////////////

  void register_action(ActionName, ActionAbbrev, Action);
  void register_char(unsigned char, CharAction);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Miscellaneous default printing routines
  //
  ////////////////////////////////////////////////////////////////////////////

  virtual CodeEmitter& operator << (char);
  virtual CodeEmitter& operator << (unsigned char);
  virtual CodeEmitter& operator << (short);
  virtual CodeEmitter& operator << (unsigned short);
  virtual CodeEmitter& operator << (int);
  virtual CodeEmitter& operator << (unsigned int);
  virtual CodeEmitter& operator << (long);
  virtual CodeEmitter& operator << (unsigned long);
  virtual CodeEmitter& operator << (double);
  virtual CodeEmitter& operator << (float);
  virtual CodeEmitter& operator << (const char *);
  virtual CodeEmitter& operator << (void (*)(CodeEmitter&));

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Pretty printing driver.
  //
  ////////////////////////////////////////////////////////////////////////////

protected:
  virtual va_list emit_driver (const char *, va_list);
  virtual void    error       (const char *, ...);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Private initialization/cleanup stuff
  //
  ////////////////////////////////////////////////////////////////////////////

private:
  void init_emitter();
  void cleanup_emitter();
  void register_default_actions();

  static va_list do_newline(CodeEmitter&,unsigned char,va_list);
  static va_list do_meta(CodeEmitter&,unsigned char,va_list);

  static va_list do_char   (CodeEmitter&,va_list);
  static va_list do_uchar  (CodeEmitter&,va_list);
  static va_list do_short  (CodeEmitter&,va_list);
  static va_list do_ushort (CodeEmitter&,va_list);
  static va_list do_int    (CodeEmitter&,va_list);
  static va_list do_uint   (CodeEmitter&,va_list);
  static va_list do_long   (CodeEmitter&,va_list);
  static va_list do_ulong  (CodeEmitter&,va_list);
  static va_list do_float  (CodeEmitter&,va_list);
  static va_list do_double (CodeEmitter&,va_list);
  static va_list do_string (CodeEmitter&,va_list);
};

#endif
