#ifndef SETL_syntax_h
#define SETL_syntax_h

#include "setl-lexeme.ph"
#include <AD/automata/iolexerbuf.h>

///////////////////////////////////////////////////////////////////////////////
//
//  Parser class for typed-SETL
//
///////////////////////////////////////////////////////////////////////////////
syntax class SETLSyntax
{
protected:
   IOLexerBuffer lexer_buf;
public:
   int get_token();
};

#endif
