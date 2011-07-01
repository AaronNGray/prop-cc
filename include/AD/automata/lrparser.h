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

#ifndef LR1_full_parser_h
#define LR1_full_parser_h

#include <iostream>
#include <string.h>
#include <AD/automata/lr1.h>


//////////////////////////////////////////////////////////////////////////////
//  This base class is an abstract datatype representing a full LR(1)-based
//  parser with semantics stack manipulation methods.
//////////////////////////////////////////////////////////////////////////////
class LR1Parser : public LR1
{
  LR1Parser( const LR1Parser&);          // no copy constructor
  void operator = ( const LR1Parser&);   // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  ///////////////////////////////////////////////////////////////////////////
  typedef LR1                     Super;
  typedef Super::Symbol           Symbol;
  typedef Super::State            State;
  typedef Super::Offset           Offset;
  typedef Super::Rule             Rule;
  typedef Super::ProductionLength ProductionLength;
  enum ErrorAction
  {  Abort,
     Retry
  };

  struct ParserState
  {
    int      token_count;  // tokens on stack
    Symbol * token_stack;  // token stack
    State    state;        // current state
    int      top;          // top of the state stack
    State  * state_stack;  // state stack
  };

  enum {  STATE_STACK_SIZE    = 4096,
          TOKEN_STACK_SIZE    = 256,
          SEMANTIC_STACK_SIZE = 4096
       };

public:

  ///////////////////////////////////////////////////////////////////////////
  // Parsing actions (overridable by derived classes)
  ///////////////////////////////////////////////////////////////////////////
  virtual void accept();               // accept the parse
  virtual ErrorAction error_report( const char * message);
  virtual ErrorAction error_repair( ParserState&);
  virtual void adjust_stack( int);

protected:

  virtual void parser_prefix();  // the default does nothing
  virtual void parser_suffix();  // the default does nothing
  virtual void print_user_symbol( std::ostream&, Symbol);
  virtual void print_symbol( std::ostream&, Symbol);
  void nice_explain( std::ostream&);  // method to explain nicely
  void debug_explain( std::ostream&); // method to dump the state
  virtual void explain_error();  // the default does nothing
  const Symbol error_token;
  const Symbol max_terminal;
  const Symbol max_non_terminal;
  ParserState * error_status;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

  LR1Parser( const Offset           base_table  [],
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
             Symbol                 max_non_term
           );

  virtual ~LR1Parser();
  inline Symbol error_symbol() const
  {
    return error_token;
  }
  virtual int get_token () = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Parsing
  ///////////////////////////////////////////////////////////////////////////
  virtual void parse() = 0;
};

template <class P, LR1Parser::State final_state>
class LR1ParserDriver
{
public:
  void driver( P& parser);
};

//////////////////////////////////////////////////////////////////////////////
//
//  LR(1) parser driver method
//
//////////////////////////////////////////////////////////////////////////////

template <class P, LR1Parser::State final_state>
inline void LR1ParserDriver<P,final_state>::driver(P& parser)
{
  typedef LR1Parser::Symbol Symbol;
  typedef LR1Parser::State  State;
  typedef LR1Parser::Offset Offset;
  typedef LR1Parser::Rule   Rule;

  int    token_count;                               // tokens on stack
  Symbol token_stack[LR1Parser::TOKEN_STACK_SIZE];  // token stack
  State  state;                                     // current state
  int    top;                                       // top of the state stack
  State  state_stack[LR1Parser::STATE_STACK_SIZE];  // state stack

  ///////////////////////////////////////////////////////////////////////////
  // Initialization
  ///////////////////////////////////////////////////////////////////////////
  state       = LR1Parser::start_state;
  token_count = 0;
  top         = 0;

  ///////////////////////////////////////////////////////////////////////////
  // The parsing loop
  ///////////////////////////////////////////////////////////////////////////
  for (;;)
  {
    Symbol token = token_count > 0 ? token_stack[--token_count]
                   : parser.get_token();
    State  new_state = parser.go(state, token);

    // Process state
    for (;;)
    {
      if (new_state == LR1Parser::error_state)
      {  // parse error
        // std::cerr << "[New state = " << new_state
        //      << " state = " << state
        //      << " token = " << token
        //      << " new = " << parser.go(state,token) << "]";
        LR1Parser::ParserState parser_state;
        token_stack[token_count++] = token;
        parser_state.token_count = token_count;
        parser_state.token_stack = token_stack;
        parser_state.state       = state;
        parser_state.top         = top;
        parser_state.state_stack = state_stack;
        switch (parser.error_repair(parser_state))
        {
        case LR1Parser::Abort:
          goto FINISH;
        default:
          ;
        }
        token_count = parser_state.token_count;
        state       = parser_state.state;
        top         = parser_state.top;
        break;
      }
      else if (new_state == final_state)
      {  // parse succeeds
        goto DONE;
      }
      else if (LR1::isShift(new_state))
      {  // shift token
        state_stack[top++] = state;
        // std::cerr << "[Shift " << state << " -> " << new_state << "]";
        state = new_state;
        break;
      }
      else
      {
        if (LR1::isShiftReduce(new_state))
        {  // shift token then immediately reduce.
          // no token to save.
          state_stack[top++] = state;
          state = LR1::state_of(new_state);
          new_state = parser.defaultAction(state);
          // std::cerr << "[Shift reduce from state " << state
          //      << " to state " << new_state << "]";
        }
        else
        {  // reduce only.
          // save lookahead token.
          token_stack[token_count++] = token;
        }
        Rule rule = parser.reduceRule(new_state);
        parser.action_driver(rule);
        int length = parser.reduceLen(rule);
        if (length > 0)
        {
          top -= length;
          state = state_stack[top];
        }
        new_state = parser.go_rule(state,rule);
        // std::cerr << "[Reduce rule " << rule << " state = " << state
        //      << " length = " << length << " new_state = "
        //      << new_state << "]";
      }
    }
  }
DONE:
  parser.accept();
FINISH:
  ;
}

#endif
