///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\..\app\setl-pe\setl-syntax.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PRINTER_USED
#define PROP_REGEXP_MATCHING_USED
#define PROP_PARSER_USED
#include <propdefs.h>
#line 1 "../../../app/setl-pe/setl-syntax.ph"
#ifndef SETL_syntax_h
#define SETL_syntax_h

#include "setl-lexeme.h"
#include <AD/automata/iolexerbuf.h>

///////////////////////////////////////////////////////////////////////////////
//
//  Parser class for typed-SETL
//
///////////////////////////////////////////////////////////////////////////////
#line 12 "../../../app/setl-pe/setl-syntax.ph"
#line 18 "../../../app/setl-pe/setl-syntax.ph"
class SETLSyntax : public LR1Parser {
public:
  /////////////////////////////////////////////////////////////////////////////
  // Parser table type definitions
  /////////////////////////////////////////////////////////////////////////////
  typedef LR1Parser               Super;
  typedef Super::Offset           Offset;
  typedef Super::State            State;
  typedef Super::Rule             Rule;
  typedef Super::Symbol           Symbol;
  typedef Super::ProductionLength ProductionLength;
  typedef Super::ShortSymbol      ShortSymbol;
  typedef Super::EquivMap         EquivMap;
  enum { INITIAL_STACK_SIZE_ = 256,
         MAX_STACK_SIZE_     = 8192
       };
protected:
  /////////////////////////////////////////////////////////////////////////////
  // Semantic value stack
  /////////////////////////////////////////////////////////////////////////////
  union SETLSyntax_semantic_stack_type * t__, * bot__;
  int stack_size__;
  int heap_allocated__;
public:
  /////////////////////////////////////////////////////////////////////////////
  // Constructor and parsing method
  /////////////////////////////////////////////////////////////////////////////
  SETLSyntax();
  virtual void parse();
  void action_driver(const Rule);
private:
  void adjust_stack(int);
  void grow_semantic_stack();
#line 13 "../../../app/setl-pe/setl-syntax.ph"
  
  protected:
     IOLexerBuffer lexer_buf;
  public:
     int get_token();
#line 18 "../../../app/setl-pe/setl-syntax.ph"
};
#line 18 "../../../app/setl-pe/setl-syntax.ph"
#line 18 "../../../app/setl-pe/setl-syntax.ph"


#endif
#line 21 "../../../app/setl-pe/setl-syntax.ph"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
