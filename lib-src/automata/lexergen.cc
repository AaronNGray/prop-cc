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

#include <assert.h>
#include <string>
#include <ctype.h>
#include <new>
#include <AD/automata/lexergen.h> // Lexical scanner generator
#include <AD/automata/nfa.h>      // NFAs
#include <AD/automata/nfa_node.h> // NFA nodes
#include <AD/automata/gentable.h> // Table emitter
#include <AD/strings/charesc.h>   // Escape sequence parsing
#include <AD/memory/mempool.h>    // Memory pools
#include <AD/hash/dchash.h>       // Direct chaining hash table
#include <AD/contain/vararray.h>  // Generic arrays
#include <AD/contain/bitset.h>    // bit set
#include <AD/contain/fbitset.h>   // fast bit set


////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
////////////////////////////////////////////////////////////////////////////

typedef LexerGen::Symbol  Symbol;
typedef LexerGen::State   State;
typedef LexerGen::Rule    Rule;
typedef LexerGen::Options Options;

////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////

LexerGen::LexerGen()
    : bytes_used(0), bad_rule(-1), error_msg(0), rule(0), equiv_classes(0)
{}

LexerGen::~LexerGen()
{
  delete [] rule;
  delete [] equiv_classes;
}

////////////////////////////////////////////////////////////////////////////
// To create a set of tables
////////////////////////////////////////////////////////////////////////////

void LexerGen::create_tables( int size, int states, Symbol min, Symbol max)
{
  Super::create_tables( size, states, min, max);
  rule = new Rule [states];
}

////////////////////////////////////////////////////////////////////////////
// To grow the number of states
////////////////////////////////////////////////////////////////////////////

void LexerGen::grow_states( int increment)
{
  Rule * new_rule = new Rule [ number_of_states + increment ];
  memcpy(new_rule,rule,sizeof(Rule) * number_of_states);
  delete [] rule;
  rule = new_rule;
  Super::grow_states(increment);
}

////////////////////////////////////////////////////////////////////////////
//  The main entry point of the lexical scanner compiler
////////////////////////////////////////////////////////////////////////////

void LexerGen::compile
( int n, const char * const * regexps, const char * const * contexts,
  int max_ch, int options
)
{
  ////////////////////////////////////////////////////////////////////////
  // Here are the tables and maps that we'll need.
  ////////////////////////////////////////////////////////////////////////
  MemPool               mem(4096);    // Memory pool with page size of 4K
  DCHashTable<FastBitSet *,State> dstates(1023,1.0);
  // Map sets of nfa states to dfa states
  VarArray<FastBitSet *> nstates;     // Inverse of above
  VarArray<Rule>         accept_rule; // Accept rule of state, if any
  NFA                    nfa(mem);    // create the nfa

  ////////////////////////////////////////////////////////////////////////
  //  Compile the regexps into an NFA
  ////////////////////////////////////////////////////////////////////////
  nfa.compile(n, regexps, contexts, max_ch, options & CaseInsensitive);
  bad_rule  = nfa.bad();
  error_msg = nfa.error_msg();
  if (! ok())
    return;

  ////////////////////////////////////////////////////////////////////////
  //  Compile the equivalence class table.
  ////////////////////////////////////////////////////////////////////////
  max_char = max_ch;
  equiv_classes = nfa.get_equiv_classes();

  ////////////////////////////////////////////////////////////////////////
  //  Start generating the tables.
  ////////////////////////////////////////////////////////////////////////
  create_tables(nfa.state_count() * nfa.equiv_class_count(),
                nfa.state_count(), 0, nfa.equiv_class_count() - 1);
  start();

  ////////////////////////////////////////////////////////////////////////
  //  Create an error state.  This state always jams
  ////////////////////////////////////////////////////////////////////////
  {  FastBitSet * err = new (mem) FastBitSet(mem, nfa.state_count());
    dstates.insert(err,(State)0);
    nstates[0] = err;
    rule[0]    = (options & Backtracking) ? -1 : 0;
  }

  ////////////////////////////////////////////////////////////////////////
  //  Create two start states for each context.
  ////////////////////////////////////////////////////////////////////////
  {  for (State s = 1; s <= nfa.context_count() * 2 + 2; s++)
    {
      NFA_Node * theNFA = nfa.context_nfa(s-1);
      if (theNFA == 0)
      {
        nstates[(int)s]     = (FastBitSet*) 0;
        accept_rule[(int)s] = 0;
      }
      else
      {
        FastBitSet * set
          = new (mem) FastBitSet(mem, nfa.state_count());
        theNFA->closure(set
                       );
        accept_rule[(int)s] = NFA_Node::accept_thinning(set
                              ,n);
        dstates.insert(set
                       ,s);
        nstates[s] = set
                       ;
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////
  //  Out going transitions indexed by equiv classes.
  ////////////////////////////////////////////////////////////////////////
  FastBitSet ** trans =
    (FastBitSet**)mem.m_alloc
    (sizeof(FastBitSet *) * nfa.equiv_class_count());
  State *   delta =  // out going state
    (State *)mem.c_alloc(sizeof(State) * nfa.equiv_class_count());
  {
    for (int i = nfa.equiv_class_count() - 1; i >= 0; i--)
      trans[i] = new (mem) FastBitSet(mem, nfa.state_count());
  }

  //{  for (int i = 0; i < nfa.state_count(); i++)
  //   if (nfa[i]) std::cerr << "State " << i << " = " << *nfa[i]->delta() << '\n';
  //}

  ////////////////////////////////////////////////////////////////////////
  //  Compute the rest of the states
  ////////////////////////////////////////////////////////////////////////
  State number_of_dfa_states = nfa.context_count() * 2 + 3;
  for (State s = 1; s < number_of_dfa_states; s++)
  {
    register FastBitSet * set
      = nstates[s];
    if (set
        == 0) continue;
    Bool is_jammed = true; // assume no out transition for now.

    /////////////////////////////////////////////////////////////////////
    // Compute transitions from this state
    /////////////////////////////////////////////////////////////////////
    {
      FastBitSet::Iter iter(*set
                           );
      while (1)
      {
        register int i = iter.next();
        if (i < 0)
          break;
        NFA_Delta * node = nfa[i];
        if (node)  // delta node
        {  Symbol c = node->symbol();
          if (c >= 0)
          {
            node->add_delta(trans[equiv_classes[c]]);
          }
          else
          {
            const FastBitSet& chars = *nfa.char_class_map(c);
            int ch;
            for (ch = nfa.equiv_class_count() - 1; ch >= 0; ch--)
            {
              if (chars[ch])
                node->add_delta(trans[ch]);
            }
          }
        }
      }
    }

    /////////////////////////////////////////////////////////////////////
    // Update delta.
    /////////////////////////////////////////////////////////////////////
    for (int i = nfa.equiv_class_count() - 1; i >= 0; i--)
    {
      Ix d = dstates.lookup(trans[i]);
      if (d)
      {  // use old state
        delta[i] = dstates.value(d);
        if (delta[i] != 0)
          is_jammed = false;
        trans[i]->clear();
      }
      else
      {  // create a new state
        Rule r = NFA_Node::accept_thinning(trans[i],n);
        dstates.insert(trans[i], number_of_dfa_states);
        nstates[number_of_dfa_states] = trans[i];
        accept_rule[number_of_dfa_states] = r;
        trans[i] = new (mem) FastBitSet(mem, nfa.state_count());
        delta[i] = number_of_dfa_states++;
        is_jammed = false;
        // std::cerr << "State " << s << " = " << *set
        //      << " n = " << n << " rule = " << r << "\n";
      }
    }

    /////////////////////////////////////////////////////////////////////
    // insert transition into table.
    /////////////////////////////////////////////////////////////////////
    add_state(s, delta);

    /////////////////////////////////////////////////////////////////////
    // The rule table actually contains information concerning whether
    // a state has any out going states.
    /////////////////////////////////////////////////////////////////////
    if ((options & Backtracking) && is_jammed)
      rule[s] = -accept_rule[s]-1;
    else
      rule[s] = accept_rule[s];
  }

  ////////////////////////////////////////////////////////////////////////
  //  Finish the table compression
  ////////////////////////////////////////////////////////////////////////
  finish();

  ////////////////////////////////////////////////////////////////////////
  //  Compute statistics
  ////////////////////////////////////////////////////////////////////////
  bytes_used        = mem.bytes_used();
  equiv_class_count = nfa.equiv_class_count();
}

////////////////////////////////////////////////////////////////////////////
//  Emit C++ code
////////////////////////////////////////////////////////////////////////////

std::ostream& LexerGen::gen_code( std::ostream& out, const char name[]) const
{
  if (ok())
  {
    Super::gen_code(out,name);
    TablePrinter pr;
    pr.print(out, (const char *)equiv_classes,
             max_char + 1, sizeof(Symbol),
             "static const unsigned char ", name, "equiv_classes", true);
    pr.print(out, (const char *)rule,
             max_state + 1, sizeof(Rule),
             "static const DFATables::Rule ", name, "accept_rule");
  }
  return out;
}

////////////////////////////////////////////////////////////////////////////
//  Method to generate a report.
////////////////////////////////////////////////////////////////////////////

std::ostream& LexerGen::print_report( std::ostream& log) const
{
  log <<   "Lexer statistics:"
  "\nNumber of states                        = " << (max_state + 1)
  << "\nNumber of next/check entries            = " << (max_check + 1)
  << "\nNumber of equivalence character classes = " << equiv_class_count
  << "\nBytes used                              = "
  << ((bytes_used + 512)/1024) << "(k)\n\n";
  return log;
}
