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

//#include <iostream>
#include <string>
#include <stdlib.h>
#include <AD/automata/lrparser.h>
#include <AD/contain/stack.h>
#include <AD/strings/charesc.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Make hidden types visible
//
//////////////////////////////////////////////////////////////////////////////

typedef LR1Parser::Symbol           Symbol;
typedef LR1Parser::ShortSymbol      ShortSymbol;
typedef LR1Parser::State            State;
typedef LR1Parser::Offset           Offset;
typedef LR1Parser::Rule             Rule;
typedef LR1Parser::ProductionLength ProductionLength;

//////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
//////////////////////////////////////////////////////////////////////////////

LR1Parser::LR1Parser(
        const Offset           base_table  [],
        const State            check_table [],
        const State            def_table   [],
        const State            defact_table[],
        const State            next_table  [],
        const ProductionLength len_table   [],
        const ProductionLength ncount_table[],
        const ShortSymbol      lhs_table   [],
        const unsigned short   equiv_table [],
        Symbol                 error,
        Symbol                 max_term,
        Symbol                 max_nonterm
        )
   : LR1(base_table,check_table,def_table,defact_table,next_table,
         len_table,ncount_table,lhs_table,equiv_table),
     error_token(error), max_terminal(max_term),
     max_non_terminal(max_nonterm), error_status(0) {}

LR1Parser::~LR1Parser() {}

//////////////////////////////////////////////////////////////////////////////
//
//  Default parsing actions
//
//////////////////////////////////////////////////////////////////////////////

void LR1Parser::accept() {}
void LR1Parser::parser_prefix() {}
void LR1Parser::parser_suffix() {}
void LR1Parser::adjust_stack(int) {}
LR1Parser::ErrorAction LR1Parser::error_report(const char * message)
{  std::cerr << message << '\n';
   return Abort;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Error repair method.  We'll just repeatedly discard input tokens until
//  we reach a point when a non-error transition can be performed.
//
//////////////////////////////////////////////////////////////////////////////

LR1Parser::ErrorAction LR1Parser::error_repair( ParserState& P)
{  //
   //  Pop state stack until a state that shifts <error> is found.
   //
   ErrorAction my_action = error_report("parse error");
   error_status = &P;
   explain_error();
   State new_state;
   while (1)
   {  new_state = go(P.state,error_token);
      //std::cerr << "[state = " << P.state << "]";
      if (new_state != error_state &&
          (isShift(new_state) || isShiftReduce(new_state)))
         goto REPAIR_STATE_FOUND;
      if (P.top == 0) goto REPAIR_STATE_NOT_FOUND;

      State old_state = P.state_stack[--P.top];
      Bool  pop_semantic_stack = true;
      for (Symbol c = EOF; c <= max_terminal; c++)
      {  State delta = go(old_state, c);
         if (delta != error_state &&
             ((isShift(delta) && delta == P.state) ||
              (isShiftReduce(delta) && state_of(delta) == P.state)))
         {  pop_semantic_stack = false; break; }
      }
      if (pop_semantic_stack)
      {  // std::cerr << "[pop stack]";
         adjust_stack(-1);
      }
      // else { std::cerr << "[don't pop stack]"; }
      P.state = old_state;
   }

REPAIR_STATE_FOUND:
   // Shift to the new state after <error>
   //std::cerr << "Repair state = " << new_state << '\n';
   if (isShift(new_state))
   {  // shift to new state
      P.state_stack[P.top++] = P.state;
      P.state = new_state;
   } else if (isShiftReduce(new_state))
   {  // shift to new state, then reduce immediately
      P.state_stack[P.top++] = P.state;
      P.state = state_of(new_state);
      new_state = defact[P.state];
      Rule rule = reduceRule(new_state);
      adjust_stack(-ncount[rule]);
      int length = len[rule];
      if (length > 0) { P.top -= length; P.state = P.state_stack[P.top]; }
   } else goto REPAIR_ERROR;

   // Discard tokens until we find one that doesn't cause an error.
   while (1)
   {  Symbol token = P.token_count > 0 ? P.token_stack[--P.token_count]
                                       : get_token();
      new_state = go(P.state, token);
      if (new_state != error_state)
      {  P.token_stack[P.token_count++] = token;
         break;
      }
      if (token == EOF) goto REPAIR_NOT_POSSIBLE;
      //std::cerr << "[Discarding " << token << "]";
   }

   return my_action;

REPAIR_STATE_NOT_FOUND:
   // error_report("Syntax error");
   return Abort;
REPAIR_NOT_POSSIBLE:
   // error_report("Syntax error(no repair possible)");
   return Abort;
REPAIR_ERROR:
   // error_report("Syntax error(error in repair)");
   return Abort;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Default symbol printing method.  Should be redefined by user.
//
//////////////////////////////////////////////////////////////////////////////

void LR1Parser::print_symbol( std::ostream& f, Symbol S)
{  if (S < 0) f << "<eof>";
   else if (S < 256) f << '\'' << print_char((char)S) << '\'';
   else if (S <= max_terminal) print_user_symbol(f,S);
   else f << "[token " << (int)S << "]";
}

void LR1Parser::print_user_symbol( std::ostream& f, Symbol S)
{  f << "[token " << (int)S << "]"; }

//////////////////////////////////////////////////////////////////////////////
//
//  Default method does not explain anything
//
//////////////////////////////////////////////////////////////////////////////

void LR1Parser::explain_error()
{
}

//////////////////////////////////////////////////////////////////////////////
//
//  This method prints out the expected tokens.
//
//////////////////////////////////////////////////////////////////////////////

void LR1Parser::nice_explain(std::ostream& f)
{
   f << "expecting: ";
   for (Symbol c = 0; c <= max_terminal; c++)
   {  State delta = go(error_status->state, c);
      if (delta != error_state)
      {  // if (isShift(delta) || isShiftReduce(delta))
         {  print_symbol(f,c); f << ' '; }
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
//
//  This method explains things in great detail.
//
//////////////////////////////////////////////////////////////////////////////

void LR1Parser::debug_explain( std::ostream& f)
{  if (error_status == 0) return;
   int j;

   f << "Tokens: ";
   for (j = error_status->token_count - 1; j >= 0; j--)
   {  print_symbol(f,error_status->token_stack[j]); f << " "; }

   f << "\nState stack: ";
   for (j = error_status->top - 1; j >= 0; j--)
   {  f << "<" << error_status->state_stack[j] << "> "; }

   f << "\nAt state <" << error_status->state << ">:\n";

   Bool one_reduce = defact[error_status->state];

   for (Symbol c = 0; c <= max_non_terminal; c++)
   {  State delta = go(error_status->state, c);
      if (delta != error_state)
      {  if (isShift(delta))
         {  f << "\tOn "; print_symbol(f,c);
            f << " shift, and goto state <" << delta << ">\n";
         } else if (isShiftReduce(delta))
         {  f << "\tOn "; print_symbol(f,c);
            Rule r = reduceRule(defaultAction(state_of(delta)));
            f << " shift, goto state <" << state_of(delta)
              << "> and reduce using rule {" << r
              << "}, lhs = " << lhs[r];
            f << " length = " << reduceLen(r) << "\n";
         } else if (! one_reduce)
         {  f << "\tOn "; print_symbol(f,c);
            Rule r = reduceRule(delta);
            f << " reduce using rule {" << r
              << "}, lhs = " << lhs[r];
            f << " length = " << reduceLen(r) << "\n";
         }
      }
   }
   if (one_reduce)
   {  Rule r = reduceRule(one_reduce);
      f << "\tOn <default> reduce using rule {"
        << reduceRule(one_reduce)
        << "}, lhs = " << lhs[r];
      f << " length = " << reduceLen(r) << "\n";
   }
   if (error_status->token_count > 0)
   {  Symbol token     = error_status->token_stack[error_status->token_count-1];
      State  new_state = go(error_status->state,token);
      f << "\tToken = "; print_symbol(f,token);
      f << "(" << token << ", equiv = " << equiv_classes[token-EOF] << ")";
      f << " new state = " << new_state << "\n";
      f << "\tMax_non_terminal = " << max_non_terminal << "\n";
      f << "\tMax_terminal = " << max_terminal << "\n";
   }
}
