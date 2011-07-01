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

#ifndef LR1_parser_driver_h
#define LR1_parser_driver_h

#include <iostream>
#include <AD/automata/lr1.h>   // LR driver basics
#include <AD/contain/stack.h>  // generic stacks


//////////////////////////////////////////////////////////////////////////////
//  Class LR1ParserDriver is used to implement a LR(1) style
//  parser driver with automatic semantic stack manipulation.
//  The class is parametrized with the type of the semantic stack
//  element(the semantic stack is current implemented as an array).
//
//  We assume the user will derive a subclass using this driver
//  as one of the superclass.  The following methods should be provided
//  by the user:
//
//      Terminal get_token()  --- this method retrieved the next token
//                                from the input stream.
//      void     act (Action) --- this method should be used to execute
//                                the semantic actions.
//////////////////////////////////////////////////////////////////////////////

template <class T>
class LR1ParserDriver : public LR1
{
  LR1ParserDriver( const LR1ParserDriver&);    // no copy constructor
  void operator = ( const LR1ParserDriver&);   // no assignment

public:

  ////////////////////////////////////////////////////////////////////////
  //  Make inherited types visible
  ////////////////////////////////////////////////////////////////////////
  typedef LR1                     Super;
  typedef Super::Symbol           Symbol;
  typedef Super::State            State;
  typedef Super::Offset           Offset;
  typedef Super::Rule             Rule;
  typedef Super::ProductionLength ProductionLength;

public:

  ////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ////////////////////////////////////////////////////////////////////////

  LR1ParserDriver(
      const Offset           base_table  [],
      const State            check_table [],
      const State            defact_table[],
      const State            next_table  [],
      const ProductionLength len_table   [],
      const unsigned short   equiv_table []
      );

  virtual ~LR1ParserDriver();

  ////////////////////////////////////////////////////////////////////////
  //  Parsing
  ////////////////////////////////////////////////////////////////////////
  virtual void parse ();

protected:
  ////////////////////////////////////////////////////////////////////////
  // Tokenizer (must be implemented in derived class)
  ////////////////////////////////////////////////////////////////////////
  virtual Terminal get_token() = 0;

  ////////////////////////////////////////////////////////////////////////
  //  Others:
  //     open()  -- prelude routine, redefinable by client.
  //     close() -- post processing routine, redefinable by client.
  //     act()   -- action routine, redefinable by client.
  //     init_stack_size() -- stack size, redefinable by client.
  //                          Notice that the stack is automatically
  //                          adjusted by the driver.
  //     stack_overflow()  -- handler for stack overflow.
  ////////////////////////////////////////////////////////////////////////
  virtual void open  ()
  {}
  virtual void close ()
  {}
  virtual void act   (Action A)
  {}
  virtual int  init_stack_size() const
  {
    return 4096;
  }
  virtual void stack_overflow()
  {}
}
;

///////////////////////////////////////////////////////////////////////////////
//  Parser driver for LR(1) style parser tables.
///////////////////////////////////////////////////////////////////////////////

template <class T> void LR1ParserDriver::parse()
{
  int          size = init_stack_size();
  Stack<State> S(size);  // the parse stack
  Stack<T>     V(size);  // the semantic value stack
  Terminal     T;

  open();              // prelude
  S.push(start_state); // push start state
  T = get_token();     // get next token

  //
  // the parsing loop
  //
  for (;;)
  {
    State s = S.top();
    State n = go(s,T);
    if (isError(n))
    {          // parse error
    }
    else if (isShift(n))  // shift action
    {
      s = n;
      T = get_token();
    }
    else  // reduce action
    {
      Rule r = reduceRule(n); // reduction rule
      act(r);                 // execute the action
      S.pop(reduceLen(r));    // pop the parse stack
      S.push(go(s = S.top(),T));
    }
  }

  close(); // coda
}

#endif
