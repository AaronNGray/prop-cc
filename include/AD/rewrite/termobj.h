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
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef rewriting_term_base_class_h
#define rewriting_term_base_class_h

#include <AD/automata/treetab.h>

class TermObj
{
  ///////////////////////////////////////////////////////////////////////////
  //  Some type definitions
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef TreeTables::State State;     // state type
  typedef TreeTables::Rule  Rule;      // rule type
  enum { undefined_state = 65535 };    // number for undefined state

  union StateOrStateRec {
    void * state_rec;
    struct
    {
      unsigned short state;
      short rule;
    }
    u;
  };


  ///////////////////////////////////////////////////////////////////////////
  // Each term object has the current tree automaton state cached.
  ///////////////////////////////////////////////////////////////////////////

private:
  StateOrStateRec the_rewrite_state;

public:
  TreeTables::Cost cost;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and methods
  ///////////////////////////////////////////////////////////////////////////
  inline TermObj()
  {
    the_rewrite_state.u.state = undefined_state;
  }

  inline Bool   has_rewrite_state() const
  {
    return the_rewrite_state.u.state != undefined_state;
  }

  inline State get_rewrite_state() const
  {
    return the_rewrite_state.u.state;
  }
  inline void  set_rewrite_state(State s)
  {
    the_rewrite_state.u.state = s;
  }
  inline Rule  get_rewrite_rule() const
  {
    return the_rewrite_state.u.rule;
  }
  inline void  set_rewrite_rule(Rule s)
  {
    the_rewrite_state.u.rule = s;
  }

  inline void * get_state_rec()
  {
    return the_rewrite_state.state_rec;
  }
  inline void   set_state_rec(void * r)
  {
    the_rewrite_state.state_rec = r;
  }
};

#endif
