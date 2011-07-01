#include <assert.h>
#include <string.h>
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


using namespace std;

////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
////////////////////////////////////////////////////////////////////////////
typedef LexerGen::Symbol  Symbol;
typedef LexerGen::State   State;
typedef LexerGen::Rule    Rule;
typedef LexerGen::Options Options;

void x()
{
	VarArray<int>	intArray;

	int i = intArray[0];
	intArray[1] = 1;

	typedef LexerGen::Rule    Rule;

	VarArray<Rule> ruleArray;

	i = 1;

	ruleArray[i] = 1;
	int a = ruleArray[1];

	VarArray<FastBitSet *> nstates;
	nstates[i]     = (FastBitSet*) 0;

	/*
	VarArray<Rule> accept_rule;
	Rule rule;
	accept_rule[1] = &rule;
	*/
}


/*
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
   if (! ok()) return;

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
      {  NFA_Node * theNFA = nfa.context_nfa(s-1);
         if (theNFA == 0) {
            nstates[s]     = 0;
            accept_rule[s] = 0;
         } else {
            FastBitSet * set = new (mem) FastBitSet(mem, nfa.state_count());
            theNFA->closure(set);
            accept_rule[s] = NFA_Node::accept_thinning(set,n);
            dstates.insert(set,s);
            nstates[s] = set;
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
   {  for (int i = nfa.equiv_class_count() - 1; i >= 0; i--)
         trans[i] = new (mem) FastBitSet(mem, nfa.state_count());
   }

   //{  for (int i = 0; i < nfa.state_count(); i++)
   //   if (nfa[i]) cerr << "State " << i << " = " << *nfa[i]->delta() << '\n';
   //}

   ////////////////////////////////////////////////////////////////////////
   //  Compute the rest of the states
   ////////////////////////////////////////////////////////////////////////
   State number_of_dfa_states = nfa.context_count() * 2 + 3;
   for (State s = 1; s < number_of_dfa_states; s++)
   {  register FastBitSet * set = nstates[s];
      if (set == 0) continue;
      Bool is_jammed = true; // assume no out transition for now.

      /////////////////////////////////////////////////////////////////////
      // Compute transitions from this state
      /////////////////////////////////////////////////////////////////////
      {  FastBitSet::Iter iter(*set);
         while (1)
         {  register int i = iter.next();
            if (i < 0) break;
            NFA_Delta * node = nfa[i];
            if (node)  // delta node
            {  Symbol c = node->symbol();
               if (c >= 0)
               {  node->add_delta(trans[equiv_classes[c]]);
               }
               else
               {  const FastBitSet& chars = *nfa.char_class_map(c);
                  int ch;
                  for (ch = nfa.equiv_class_count() - 1; ch >= 0; ch--)
                  {  if (chars[ch]) node->add_delta(trans[ch]);  }
               }
            }
         }
      }

      /////////////////////////////////////////////////////////////////////
      // Update delta.
      /////////////////////////////////////////////////////////////////////
      for (int i = nfa.equiv_class_count() - 1; i >= 0; i--)
      {  Ix d = dstates.lookup(trans[i]);
         if (d)
         {  // use old state
            delta[i] = dstates.value(d);
            if (delta[i] != 0) is_jammed = false;
            trans[i]->clear();
         } else
         {  // create a new state
            Rule r = NFA_Node::accept_thinning(trans[i],n);
            dstates.insert(trans[i], number_of_dfa_states);
            nstates[number_of_dfa_states] = trans[i];
            accept_rule[number_of_dfa_states] = r;
            trans[i] = new (mem) FastBitSet(mem, nfa.state_count());
            delta[i] = number_of_dfa_states++;
            is_jammed = false;
            // cerr << "State " << s << " = " << *set
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
*/