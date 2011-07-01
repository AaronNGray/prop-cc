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

#ifndef LL1_parser_driver_h
#define LL1_parser_driver_h

#include <AD/automata/ll1.h>

//
//  The following template is used to instantiate a new version
//  of a parser.
//

template<
          class InputStream,     // Class for retrieving a character
          class SemanticType,    // The contents of the semantics stack
          int stackSize,         // The size of the semantics stack
          class ActionFunction,  // Action function class
          class ErrorHandler     // Error handler class
        >
void LL1_parser
( LL1& parser, InputStream& stream, SemanticType stack[],
  ActionFunction& action, ErrorHandler& errorHandler
)
{
  union ParseStack {
    Grammar::Symbol symbol;
    SemanticType * entry;
  };
  ParseStack parseStack[stackSize];
  register ParseStack * SP = parseStack;
  SemanticType * top, * current, * lhs, * rhs;
  register Grammar::Symbol lookahead;

  lhs = rhs = stack;
  top = lhs + 1;
  lookahead = stream.get();
  for ( (SP++)->symbol = parser.grammar.start(); SP > parseStack; )
  {
    Grammar::Symbol symbol = (--SP)->symbol;
    if (symbol == Grammar::END_PRODUCTION)
    {
      rhs     = SP[-1].entry;
      lhs     = SP[-2].entry;
      current = SP[-3].entry;
      top     = SP[-4].entry;
      SP     -= 4;
    }
    else if (parser.grammar.isTerminal(symbol))
    {
      if (symbol == lookahead)
      {
        lookahead = stream.get();
      }
      else
      {
        errorHandler(lookahead);
      }
    }
    else if (parser.grammar.isAction(symbol))
    {
      action(symbol);
    }
    else
    {
      register Grammar::Production production =
        parser.grammar.productions +
        parser.next[parser.base[symbol] + lookahead];
      if (production[0] == symbol)
      {
        sp[0].entry  = top;
        sp[1].entry  = current;
        sp[2].entry  = lhs;
        sp[3].entry  = rhs;
        sp[4].symbol = Grammar::END_PRODUCTION;
        sp += 5;
        lhs = current;
        current = rhs = top;
        for (register Grammar::Production P =
               production + production[-1]; production < P; )
          if (! parser.grammar.isAction((sp++)->symbol = *P--))
            top++;
      }
      else
      {
        errorHandler(lookahead);
      }
    }
  }
}

#endif
