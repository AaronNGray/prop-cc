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

#include <limits.h>
#include <string.h>
#include <AD/automata/densedfa.h>

//#define DEBUGMSG(e) e
#define DEBUGMSG(e)

//////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
//////////////////////////////////////////////////////////////////////////

typedef DenseDFA::Symbol Symbol;
typedef DenseDFA::State  State;

//////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////

DenseDFA::DenseDFA() : def(0)
{}

DenseDFA::~DenseDFA()
{
  delete [] def;
}

//////////////////////////////////////////////////////////////////////////
//  Create tables for dense dfa
//////////////////////////////////////////////////////////////////////////

void DenseDFA::create_tables( int size, int states, Symbol min, Symbol max)
{
  Super::create_tables(size,states,min,max);
  def = new State [number_of_states];
  for (int i = 0; i < number_of_states; i++)
    def[i] = 0;
}

//////////////////////////////////////////////////////////////////////////
//  Increment the size of tables
//////////////////////////////////////////////////////////////////////////

void DenseDFA::grow_states( int increment)
{
  State * new_def = new State [number_of_states + increment];
  memcpy(new_def, def, number_of_states * sizeof(State));
  for (int i = number_of_states; i < number_of_states + increment; i++)
    new_def[i] = 0;
  delete [] def;
  def = new_def;
  Super::grow_states(increment);
}

//////////////////////////////////////////////////////////////////////////
//  Start generating tabels and initialize temporary tables
//////////////////////////////////////////////////////////////////////////

void DenseDFA::start()
{
  Super::start();
  number_of_symbols = max_symbol - min_symbol + 1;
  diffs[0]    = new State  [ number_of_symbols ];
  diffs[1]    = new State  [ number_of_symbols ];
  transitions = new State  [ number_of_symbols ];
  symbols     = new Symbol [ number_of_symbols ];
  my_delta    = new State  [ number_of_symbols ];
  if (number_of_symbols <= 32)
    max_template_diff = number_of_symbols / 3;
  else if (number_of_symbols <= 64)
    max_template_diff = number_of_symbols / 4;
  else
    max_template_diff = number_of_symbols / 5;
  max_template_diff = number_of_symbols / 3;
  max_template_diff = number_of_symbols;

  //
  // Create a template for state 0, the error state
  //
  templates[0].state = 0;
  templates[0].delta = new State [ number_of_symbols ];
  templates[0].age   = 0;
  templates[0].uses  = 100000; // prevent us from removing this template
  for (int i = 0; i < number_of_symbols; i++)
    templates[0].delta[i] = error_state;
  number_of_templates = 1;
  misses      = 0;
  current_age = 0;
  empty_slots = true;
}

//////////////////////////////////////////////////////////////////////////
//  Finish generating tables and free up temporary tables
//////////////////////////////////////////////////////////////////////////

void DenseDFA::finish()
{
  Super::finish();
  for (int i = 0; i < number_of_templates; i++)
    delete [] templates[i].delta;
  delete [] diffs[0];
  delete [] diffs[1];
  delete [] transitions;
  delete [] symbols;
  delete [] my_delta;
}

//////////////////////////////////////////////////////////////////////////
//  Add a new state into the automaton
//////////////////////////////////////////////////////////////////////////

void DenseDFA::add_state
(State s, int fan_out, const Symbol syms[], const State delta[])
{
  register int i;
  for (i = number_of_symbols - 1; i >= 0; i--)
    my_delta[i] = error_state;
  for (i = fan_out - 1; i >= 0; i--)
    my_delta[ syms[ i ] - min_symbol ] = delta [ i ];
  add_state(s, my_delta);
}

//////////////////////////////////////////////////////////////////////////
//  Add a new state into the automaton
//////////////////////////////////////////////////////////////////////////

void DenseDFA::add_state(State s, const State delta[])
{   //
  // First compute the current state with the set of templates.
  // If one of the template is similar enough with the current state,
  // use the template state as the default basis.
  //
  int fan_out;                       // the fan out, or difference of fan out
  int available     = 0;             // index into the diffs table
  int best_fan_out  = INT_MAX;       //  mimimum fan out
  int best_template = -1;            // template that fits the best
  int best_diffs = 0;                // index of the minimal difference
  const State same_state = error_state-1;
  register int i;
  for (i = number_of_templates - 1; i >= 0; i--)
  {
    //
    // compute the difference between delta and the templates
    //
    register State * a_template = templates[i].delta;
    register State * result = diffs[available];
    register int j;
    for (fan_out = 0, j = 0; j < number_of_symbols; j++)
    {
      if (a_template[j] != delta[j])
      {
        result[j] = delta[j];
        fan_out++;
      }
      else
        result[j] = same_state;
    }

    //
    // If a better template is found, update the new minimum and
    // switch the buffer so that the minimal difference is always
    // available in |diffs[best_diffs]|.
    //
    if (fan_out < best_fan_out)
    {
      best_template = i;
      best_fan_out = fan_out;
      best_diffs = available;
      available = 1 - available;
    }
  }

  Bool using_template;  // Are we using a template
  const State * out;    // the final out transitions

  //
  // Check whether a suitable template has been located.  If so,
  // use the template as the default state; otherwise, the error state
  // is the default state.
  //
  DEBUGMSG(std::cerr << "[best fan out = " << best_fan_out
           << " max_template_diff = " << max_template_diff);
  if (best_template >= 0 && best_fan_out < max_template_diff)
  {
    out = diffs[best_diffs];
    using_template = true;
    templates[best_template].uses++;
    templates[best_template].age = current_age;
    DEBUGMSG(std::cerr << " using template " << best_template
             << " uses = " << templates[best_template].uses << "]\n");
  }
  else
  {
    out = delta;
    using_template = false;
    DEBUGMSG(std::cerr << "]\n");
  }

  //
  // Eliminate all transitions from the transition function that
  // goes to the same state as our template.
  //
  for (fan_out = 0, i = number_of_symbols - 1; i >= 0; i--)
    if (out[i] != same_state)
    {
      symbols[fan_out]     = i + min_symbol;
      transitions[fan_out] = out[i];
      fan_out++;
    }

  //
  // Emit into the table using the regular sparse compression
  // strategy.  The idea is that hopefully we'll have a useful template
  // most of the time and thus being able to ``thin'' out the transitions.
  //
  Super::add_state(s, fan_out, symbols, transitions);

  //
  // Emit the default state of this state, which is the state of
  // the template if available.
  //
  def[s] = using_template ? templates[best_template].state
           : (State)error_state;

  //
  // Insert new current entry into template queue if it does not
  // have a template and if the queue is not full.
  //
  // if ((! using_template ||
  //      (max_template_diff - best_fan_out) < number_of_symbols / 6)
  //     && number_of_templates < Max_templates) {
  Bool add_template =
    ! using_template ||
    best_fan_out > 1 && templates[best_template].uses > 10 ||
    best_fan_out >= number_of_symbols / 3;

  if (add_template)
  {
    if (number_of_templates < Max_templates)
    {
      // Create new template
      DEBUGMSG(std::cerr << "[creating template "
               << number_of_templates << "]\n");
      templates[number_of_templates].state = s;
      templates[number_of_templates].age   = current_age;
      templates[number_of_templates].uses  = 0;
      memcpy(
        templates[number_of_templates].delta
        = new State [ number_of_symbols ],
        delta,number_of_symbols * sizeof(State));
      number_of_templates++;
    }
    else if (empty_slots)
    {
      // Replace template with the oldest used template
      int min_age = 1000000;
      int min_use = -1;
      int target  = -1;
      for (int j = 1; j < Max_templates; j++)
      {
        if (templates[j].age < min_age)
        {
          target = j;
          min_age = templates[j].age;
        }
        if (templates[j].uses == 0)
        {
          min_use = j;
        }
      }
      if (min_use >= 0)
        target = min_use;
      if (target > 0 && (templates[target].uses == 0 || best_fan_out > 10))
      {
        DEBUGMSG(std::cerr << "[replacing template " << target << " with age "
                 << min_age << " uses = "
                 << templates[target].uses << "]\n");
        templates[target].state = s;
        templates[target].age   = current_age;
        templates[target].uses  = 0;
        memcpy(templates[target].delta, delta,
               number_of_symbols * sizeof(State));
      } //else empty_slots = false;
    }
  }
  current_age++;
}

//////////////////////////////////////////////////////////////////////////
//  Emit C++ code that reconstructs the tables
//////////////////////////////////////////////////////////////////////////

std::ostream& DenseDFA::gen_code( std::ostream& out, const char name []) const
{
  Super::gen_code( out,name);
  gen_state_table( out,name, "def", def + error_state, max_state-error_state+1);
  return out;
}

//////////////////////////////////////////////////////////////////////////
//  Emit C++ code that reconstructs the tables (sans base)
//////////////////////////////////////////////////////////////////////////

std::ostream& DenseDFA::gen_check_next_tables
(std::ostream& out, const char name [], const char * mytype) const
{
  Super::gen_check_next_tables( out, name, mytype);
  gen_state_table( out, name, "def", def + error_state, max_state-error_state+1,
                  mytype);
  return out;
}
