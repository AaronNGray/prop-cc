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

#include <string>
#include <AD/automata/compdfa.h>
#include <AD/automata/gentable.h>

//////////////////////////////////////////////////////////////////////////
// Make hidden types visible
//////////////////////////////////////////////////////////////////////////

typedef CompressedDFA::Symbol Symbol;
typedef CompressedDFA::State  State;

//////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////

CompressedDFA::CompressedDFA() : base(0), check(0), next(0)
{}

CompressedDFA::~CompressedDFA()
{
  delete [] base;
  delete [] check;
  delete [] next;
}

//////////////////////////////////////////////////////////////////////////
// Create an initial compressed dfa table
//////////////////////////////////////////////////////////////////////////

void CompressedDFA::create_tables( int size, int states, Symbol min, Symbol max)
{
  min_symbol = min;
  max_symbol = max;
  table_size = size;
  number_of_states = states;
  max_check = 0;
  max_state = 0;
  base  = new Offset [ number_of_states ];
  check = new State  [ table_size ];
  next  = new State  [ table_size ];

  int i;
  for (i = table_size - 1; i >= 0; i--)
    check[i] = next[i] = error_state;
  for (i = number_of_states - 1; i >= 0; i--)
    base[i] = 0;
}

//////////////////////////////////////////////////////////////////////////
// Expand the check/next tables
//////////////////////////////////////////////////////////////////////////

void CompressedDFA::grow_tables(int increment)
{
  State * new_check = new State [ table_size + increment ];
  State * new_next  = new State [ table_size + increment ];
  memcpy(new_check,check,table_size * sizeof(State));
  memcpy(new_next ,next ,table_size * sizeof(State));
  delete [] check;
  delete [] next;
  check = new_check;
  next  = new_next;
  for (register int i = table_size + increment - 1; i >= table_size; i--)
    check[i] = next[i] = error_state;
  table_size += increment;
}

//////////////////////////////////////////////////////////////////////////
// Expand the number of states
//////////////////////////////////////////////////////////////////////////

void CompressedDFA::grow_states(int increment)
{
  Offset * new_base = new Offset [ number_of_states+increment ];
  memcpy(new_base,base,number_of_states * sizeof(Offset));
  for (int i = number_of_states; i < number_of_states + increment; i++)
    new_base[i] = 0;
  delete [] base;
  base = new_base;
  number_of_states += increment;
}

std::ostream& CompressedDFA::gen_state_table
( std::ostream& out, const char name[], const char table[],
  const State s[], int size, const char * mytype) const
{
  TablePrinter pr;
  if (mytype == 0)
    mytype = "static const DFATables::State ";
  pr.print(out, (const char *)s, size, sizeof(State),
           mytype, name, table, true);
  return out;
}

std::ostream& CompressedDFA::gen_offset_table
( std::ostream& out, const char name[], const char table[],
  const Offset s[], int size) const
{
  TablePrinter pr;
  pr.print(out, (const char *)s, size, sizeof(Offset),
           "static const DFATables::Offset ", name, table);
  return out;
}

std::ostream& CompressedDFA::gen_check_next_tables
(std::ostream& out, const char name[], const char * mytype) const
{
  gen_state_table(out,name,"check",check,max_check + 1,mytype);
  gen_state_table(out,name,"next",next,max_check + 1,mytype);
  return out;
}

std::ostream& CompressedDFA::gen_code (std::ostream& out, const char name[]) const
{
  gen_offset_table(out,name,"base",base, max_state + 1);
  CompressedDFA::gen_check_next_tables(out, name);
  return out;
}
