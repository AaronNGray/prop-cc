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

#ifndef LR1_parser_h
#define LR1_parser_h

#include <iostream>
#include <AD/generic/generic.h>    // generic definitions
#include <AD/automata/dfatable.h>  // Compressed DFA tables


//////////////////////////////////////////////////////////////////////////////
//  Class |LR1| represents a bareboned LR(1) parser driver.
//  The compression algorithm is assumed to be the one as implemented
//  in class DenseDFA.
//////////////////////////////////////////////////////////////////////////////

class LR1 : public DFATables
{
  LR1(const LR1&);                // no copy constructor
  void operator = (const LR1&);   // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////
  typedef DFATables               Super;
  typedef Super::Symbol           Symbol;
  typedef Super::Offset           Offset;
  typedef Super::State            State;
  typedef Super::ShortSymbol      ShortSymbol;
  typedef Super::Rule             Rule;
  typedef Super::ProductionLength ProductionLength;

  ///////////////////////////////////////////////////////////////////////////
  //  Parsing actions:
  //    (i)   parse error encountered
  //    (ii)  a complete parse has been constructed
  //    (iii) shift token onto parse stack
  //    (iv)  reduce using production
  ///////////////////////////////////////////////////////////////////////////
  enum Action { Error, Accept, Shift, Reduce };

  ///////////////////////////////////////////////////////////////////////////
  // Common states
  // and other common constants
  ///////////////////////////////////////////////////////////////////////////
  enum LR1_constants { error_state           = 0,
                       start_state           = 1,
                       Parse_stack_size      = 2048,
                       Parse_stack_increment = 1024
                     };

protected:

  ///////////////////////////////////////////////////////////////////////////
  //  Compressed state and transition tables.
  //
  //  A note concerning the interpretation of these tables:
  //
  //    base[]   is indexed by the state number.
  //    check[]  is indexed by the state number.
  //    next[]   is the next transition state indexed by the offset.
  //
  //   The offset of state 's' with input symbol 'c' is
  //       base[s] + c   iff    check[base[s] + c] == s
  //
  //  Notice that the next[] table is actually a combination of the
  //  ``action'' and ``goto'' table in LR parsing, and
  //  should be interpreted in the following manner:
  //
  //  Let n = next[base[s] + c]
  //     (a) n == 0                parse error
  //     (b) n > 0 && n < 32768    shift symbol and goto state n
  //     (c) n >= 32768
  //        reduce using production rule r = n - 32768 and where
  //        len[r] is the length of the production.
  ///////////////////////////////////////////////////////////////////////////

  const Offset           * const base;
  const State            * const check;
  const State            * const def;
  const State            * const defact;
  const State            * const next;
  const ProductionLength * const len;
  const ProductionLength * const ncount;
  const ShortSymbol      * const lhs;
  const unsigned short   * const equiv_classes;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  inline
  LR1( const Offset           base_table  [],
       const State            check_table [],
       const State            def_table   [],
       const State            defact_table[],
       const State            next_table  [],
       const ProductionLength len_table   [],
       const ProductionLength ncount_table[],
       const ShortSymbol      lhs_table   [],
       const unsigned short   equiv_table []
     )
      : base(base_table), check(check_table), def(def_table),
      defact(defact_table), next(next_table), len(len_table),
      ncount(ncount_table), lhs(lhs_table),
      equiv_classes(equiv_table)
  {}

  ///////////////////////////////////////////////////////////////////////////
  // Our convention:
  //    State 0 is the unique error state.
  //    State n, n < 32768 are shifting actions.
  //    State n, n >= 32768 are reducing actions.
  //    State n, n >= 32768 + 16384 are single reducing actions.
  ///////////////////////////////////////////////////////////////////////////
  inline static Bool isShift( State s)
  {
    return s < 0x4000;
  }
  inline static Bool isReduce( State s)
  {
    return s >= 0x8000;
  }
  inline static Bool isSingleReduce( State s)
  {
    return s >= 0xc000;
  }
  inline static Bool isShiftReduce( State s)
  {
    return s & 0x4000;
  }
  inline static Bool isError( State s)
  {
    return s == 0;
  }
  inline static Rule reduceRule( State s)
  {
    return s & 0x3fff;
  }
  inline static Rule singleReduceRule( State s)
  {
    return s & 0x3fff;
  }
  inline static State state_of( State s)
  {
    return s & 0x3fff;
  }
  inline int  reduceLen( Rule r) const
  {
    return len[r];
  }
  inline int  reduceNcount( Rule r) const
  {
    return ncount[r];
  }
  inline State  defaultAction( State s) const
  {
    return defact[s];
  }

  ///////////////////////////////////////////////////////////////////////////
  //  State transitions
  ///////////////////////////////////////////////////////////////////////////

  inline State go( State s, Symbol c) const
  {
    register int offset;
    register int disp  = equiv_classes[c-EOF];
    register int state = s;
    while (check[offset = base[state] + disp] != state)
    {
      register int new_state = def[state];
      if (new_state == error_state)
        return defact[s];
      state = new_state;
    }
    return ((state = next[offset]) == error_state) ? defact[s] : state;
  }

  inline State go_rule( State s, Rule r) const
  {
    register int offset;
    register int disp  = lhs[r];
    register int state = s;
    while (check[offset = base[state] + disp] != state)
    {
      register int new_state = def[state];
      if (new_state == error_state)
        return defact[s];
      state = new_state;
    }
    return ((state = next[offset]) == error_state) ? defact[s] : state;
  }
};

#endif
