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
#include <string.h>
#include <ctype.h>
#include <new.h>
#include <AD/automata/lexergen.h> // Lexical scanner generator
#include <AD/automata/gentable.h> // Table emitter  
#include <AD/strings/charesc.h>   // Escape sequence parsing
#include <AD/memory/mempool.h>    // Memory pools
#include <AD/hash/dchash.h>       // Direct chaining hash table
#include <AD/contain/vararray.h>  // Generic arrays
#include <AD/contain/bitset.h>    // bit set

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
LexerGen::LexerGen() : rule(0), bad_rule(-1), equiv_classes(0) {} 
LexerGen::~LexerGen() { delete [] rule; delete [] equiv_classes; }

////////////////////////////////////////////////////////////////////////////
//  Some flags and constants
////////////////////////////////////////////////////////////////////////////
#define nil 0                        // nil pointer
#define RANGE_BIT       0x80000000   // marks a range in character class
#define COMPLEMENT      0x40000000   // marks a set complement in the same
#define END_CHAR_CLASS  0x20000000   // marks the end of a character class

////////////////////////////////////////////////////////////////////////////
// To create a set of tables
////////////////////////////////////////////////////////////////////////////
void LexerGen::create_tables(int size, int states, Symbol min, Symbol max)
{  Super::create_tables(size,states,min,max);
   rule = new Rule [states];
}

////////////////////////////////////////////////////////////////////////////
// To grow the number of states
////////////////////////////////////////////////////////////////////////////
void LexerGen::grow_states(int increment)
{  Rule * new_rule = new Rule [ number_of_states + increment ];
   memcpy(new_rule,rule,sizeof(Rule) * number_of_states);
   delete [] rule;
   rule = new_rule; 
   Super::grow_states(increment);
}

////////////////////////////////////////////////////////////////////////////
//  A node in the nfa. 
////////////////////////////////////////////////////////////////////////////
struct Nfa {
   enum { Accept, Delta, Epsilon } tag;
   BitSet * epsilon_closure;
   union {
      struct Dummy2 {
         State  state;         // nfa state number  
         Symbol c;             // symbol to branch on 
         Nfa *  out;           // out transition
         BitSet * delta_set;   //
      } n;
      Nfa * epsilon[2]; // out transitions
   };

   void * operator new (int, MemPool& mem)
     { Nfa * nfa = (Nfa*)mem[sizeof(Nfa)]; 
       nfa->epsilon_closure = nil; return nfa;
     }

   void * operator new (int, MemPool& mem, Nfa * x, Nfa * y)
     { if (x == nil) return y;
       Nfa * nfa = (Nfa*)mem[sizeof(Nfa)];
       nfa->tag = Epsilon; nfa->epsilon_closure = nil;
       nfa->epsilon[0] = x; nfa->epsilon[1] = y; return nfa;
     }
};

////////////////////////////////////////////////////////////////////////////
//  Parse a regular expression and construct a sub-nfa
////////////////////////////////////////////////////////////////////////////
static Nfa * construct_nfa 
   ( const char * regexp, Rule rule, MemPool& mem, 
     int& number_of_nfa_states, Bool partitions[], Bool singletons[],
     Symbol ** char_classes, Symbol * character_classes[],
     int& char_class_num, const char * const * contexts, int number_of_contexts,
     Nfa * context_nfas[], Bool foldcase
   )
{  Nfa * stack[LexerGen::Max_star_height];
   register const char * p;  // current pointer to regular expression 
   register Symbol c;        // current character
   register Nfa * root;      // the root of the current sub-nfa
   register Nfa * current;   // the current point of the sub-nfa
   register Nfa * next;      // the next availble node of the nfa
   Nfa ** sp = stack;
   char ch; int i;
   Bool in_context[LexerGen::Max_contexts];
   Bool anchored = false;    // pattern must start at beginning of line??
   Bool in_any_context = false;

   //
   // Determine the context, if any
   //
   if (regexp[0] == '<') {
      char name[256];
      char * q;
      int i;
      memset(in_context,0,sizeof(in_context));
      if (contexts == nil) goto syntax_error;
      for (p = regexp+1, q = name;; ) {
         switch (c = *p++) {
            case '\0': goto syntax_error;
            case '>': case ',':
               q = '\0';
               for (i = 0; contexts[i]; i++) 
                  if (strcmp(contexts[i], name) == 0) goto found;
               goto syntax_error;
            found:  q = name;
               in_context[i]  = true;
               in_any_context = true;
               if (c == '>') goto finish;
               break;
            default: *q++ = c; break;
         }
      }
   finish: ;
   } else p = regexp;

   //
   // Now scan the pattern and parse
   //
   root = current = next = new(mem) Nfa;
   for (;;) {
      Nfa * next_node = new(mem) Nfa;  // Get a new node
      switch (c = (unsigned char)*p++) {
         case '(':  // grouping
         case '|':  // disjunction 
         {  sp[0] = root; sp[1] = next; sp[2] = c == '|' ? (Nfa*)1 : nil;
            sp += 3; root = current = next = next_node;
         }  break;
         case '\0': case ')':  // end of pattern or end of grouping
         {  while (sp > stack && sp[-1]) {
               Nfa * old_root = sp[-3];
               Nfa * old_next = sp[-2];
               sp -= 3;
               Nfa * n = new(mem) Nfa;
               old_next->tag = Nfa::Epsilon;
               old_next->epsilon[0] = next;
               old_next->epsilon[1] = nil; 
               n->tag = Nfa::Epsilon;
               n->epsilon[0] = old_root;
               n->epsilon[1] = root;
               root = n;
            }
            if (c == ')') {
               if (sp == stack) goto syntax_error;
               Nfa * old_next = sp[-2];
               Nfa * old_root = sp[-3];
               sp -= 3;
               old_next->tag = Nfa::Epsilon;
               old_next->epsilon[0] = root;
               old_next->epsilon[1] = nil;
               root = current = old_root;
            } else {
               if (sp > stack) goto syntax_error;
               goto done;
            }
         }  break;
         case '^': if (p-1 > regexp) goto build_delta; 
                   anchored = true; break;
         case '$': c = '\n'; goto build_delta;
         case '*': if (root == next) goto syntax_error;
         {  *next_node          = *current;
            current->tag        = Nfa::Epsilon;
            current->epsilon[0] = next_node; 
            current->epsilon[1] = next; 
            next->tag           = Nfa::Epsilon;
            next->epsilon[0]    = next_node;
            next->epsilon[1]    = new(mem) Nfa;
            next = next->epsilon[1];
         }  break;
         case '+': if (root == next) goto syntax_error; 
         {  next->tag        = Nfa::Epsilon;
            next->epsilon[0] = current;
            next->epsilon[1] = next_node;
            next = next_node;
         }  break;
         case '?': if (root == next) goto syntax_error;
         {  *next_node          = *current;
            current->tag        = Nfa::Epsilon;
            current->epsilon[0] = next_node; 
            current->epsilon[1] = next;
         }  break;
         case '.':   // wild card
         {  Symbol * char_class = *char_classes;
            *char_class++ = '\n' | COMPLEMENT;
            *char_class++ = END_CHAR_CLASS;
            singletons['\n'] = true; 
            character_classes[char_class_num++] = *char_classes;
            *char_classes = char_class;
            c = -char_class_num;
            goto build_delta;
         }  break;
         case '[':   // process a character class
         {  Symbol start_range = -1;
            const char * start = p;
            Bool complement = false;
            Symbol last_char;
            Symbol * char_class = *char_classes;
            for (last_char = -1; (c = (unsigned char)*p++) != ']'; ) {
               switch (c) {
                  case '\0': goto syntax_error;
                  case '-':  if (last_char < 0) goto syntax_error;
                             start_range = last_char; 
                             break;
                  case '^':  if (p-1 == start) { complement = true; break; }
                  case '\\': p = parse_char(p-1,ch); c = (unsigned char)ch;
                  default:    
                     if (foldcase) c = toupper(c);
                     *char_class++ = c;
                     if (start_range >= 0) {
                        if (start_range >= c) goto syntax_error;
                        char_class[-2] |= RANGE_BIT;
                        start_range = -1;
                        last_char = -1;
                        partitions[c+1] = true;
                     } else {
                        partitions[c] = true;
                        last_char = c;
                        if (*p != '-') singletons[c] = true;
                     }
                     break;
               }
            }
            *char_class++ = END_CHAR_CLASS;
            if (complement) (*char_classes)[0] |= COMPLEMENT;
            character_classes[char_class_num++] = *char_classes;
            *char_classes = char_class;
            c = -char_class_num;
            goto build_delta;
         }  
         case '\\':   p = parse_char(p-1,ch); c = ch;
         build_delta: default:    // process normal characters
         {  next->tag     = Nfa::Delta;
            next->n.state = number_of_nfa_states++;
            if (foldcase && c >= 0) c = toupper(c);
            next->n.c     = c;
            next->n.out   = next_node;
            current = next; next = next->n.out;
            if (c >= 0) singletons[c] = true;
         }  break;
      }
   }
done:
   next->tag     = Nfa::Accept;
   next->n.state = rule;
   for (i = 0; i < number_of_contexts; i++) {
      if (in_context[i]) {
         if (! anchored) 
            context_nfas[2*i+2] = new(mem,context_nfas[2*i+2],root) Nfa;
         context_nfas[2*i+3] = new(mem,context_nfas[2*i+3],root) Nfa;
      }
   } 
   if (! in_any_context) {
      if (! anchored)
         context_nfas[0] = new(mem,context_nfas[0],root) Nfa;
      context_nfas[1] = new(mem,context_nfas[1],root) Nfa;
   }
   return root;

syntax_error: 
   return nil;
}

////////////////////////////////////////////////////////////////////////////
//  Compute the epsilon closure for one state
////////////////////////////////////////////////////////////////////////////
static void compute_epsilon_closure(Nfa * nfa, BitSet * closure)
{  if (nfa == nil) return;
   switch (nfa->tag) {
      case Nfa::Accept:
      case Nfa::Delta:   closure->add(nfa->n.state); return;
      case Nfa::Epsilon:
          compute_epsilon_closure(nfa->epsilon[0],closure);
          compute_epsilon_closure(nfa->epsilon[1],closure);
          return;
      default:
          assert("bug: compute_epsilon_closure()");
   }
}

////////////////////////////////////////////////////////////////////////////
//  Find the accept rule of the state, if any
////////////////////////////////////////////////////////////////////////////
inline Rule accept_thinning(BitSet * set, int n)
{  for (int i = 0; i < n; i++) 
      if ((*set)[i]) {
         for (int j = i+1; j < n; j++) set->remove(j);
         return i+1;
      }
   return 0;
}

////////////////////////////////////////////////////////////////////////////
//  Compute epsilon closure for each state of the nfa.
////////////////////////////////////////////////////////////////////////////
static BitSet * epsilon_closure
   ( Nfa * nfa, MemPool& mem, int number_of_nfa_states, Nfa * nfa_states[], int n)
{  BitSet * set;
   if (nfa == nil) return nil;
   if (nfa->epsilon_closure) return nfa->epsilon_closure;
   switch (nfa->tag) {
      case Nfa::Accept:
         nfa_states[nfa->n.state] = nfa;
         set = nfa->epsilon_closure = new(mem,number_of_nfa_states) BitSet;
         set->add(nfa->n.state);
         return set;
      case Nfa::Delta:
         nfa_states[nfa->n.state] = nfa;
         set = nfa->epsilon_closure = new(mem,number_of_nfa_states) BitSet;
         set->add(nfa->n.state); 
         nfa->n.delta_set = new(mem,number_of_nfa_states) BitSet;
         compute_epsilon_closure(nfa->n.out,nfa->n.delta_set);
         epsilon_closure(nfa->n.out,mem,number_of_nfa_states,nfa_states,n);
         return set;
      case Nfa::Epsilon:
         set = nfa->epsilon_closure = new(mem,number_of_nfa_states) BitSet;
         compute_epsilon_closure(nfa->epsilon[0],set);
         compute_epsilon_closure(nfa->epsilon[1],set);
         accept_thinning(set, n);
         epsilon_closure(nfa->epsilon[0],mem,number_of_nfa_states,nfa_states,n);
         epsilon_closure(nfa->epsilon[1],mem,number_of_nfa_states,nfa_states,n);
         return set;
      default: 
         assert("bug: epsilon_closure()");
         return nil;
   }
}

////////////////////////////////////////////////////////////////////////////
// Compute transition from a set of nfa states
////////////////////////////////////////////////////////////////////////////
inline void compute_transitions
    (Nfa * nfa, Nfa * nfa_states[], BitSet * transitions[], 
     BitSet * char_class_map[], int number_of_equiv_classes, 
     Symbol equiv_classes[])
{  register int s;
   register BitSet& set = *nfa->epsilon_closure;
   foreach_bit (s, set) {
      Nfa * node = nfa_states[s];
      if (node->tag == Nfa::Delta) {
         Symbol c = node->n.c;
         if (c >= 0) {
            transitions[equiv_classes[c]]->Union(*node->n.delta_set);  
         } else {
            BitSet& chars = *char_class_map[-c-1];
            for (int ch = 0; ch < number_of_equiv_classes; ch++)
            if (chars[ch]) transitions[ch]->Union(*node->n.delta_set);
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////
//  The main entry point of the lexical scanner compiler
////////////////////////////////////////////////////////////////////////////
void LexerGen::compile
   ( int n, const char * const * regexp, const char * const * contexts, 
     int max_ch, int options
   )
{  
   //
   // Here are the tables and maps that we'll need
   //
   MemPool               mem(4096);   // Memory pool with page size of 4K 
   DCHashTable<BitSet *,State> dstates(257); // Map sets of nfa states to dfa states
   VarArray<BitSet *>    nstates;     // Inverse of above
   VarArray<Rule>        accept_rule; // Accept rule of state, if any
   Nfa ** context_nfas;               // Sub-nfas of each context

   //
   // Local variables
   //
   int   i;                                  // loop index
   State processed;                          // current state to be processed
   State number_of_dfa_states         = 1;   
   int   number_of_nfa_states         = n;  
   int   number_of_equiv_classes      = 0; 
   int   number_of_character_classes  = 0;  
   int   character_class_size         = 0;
   int   number_of_contexts           = 0;

   //
   // Count the number of contexts and allocate space 
   //
   if (contexts) while (contexts[number_of_contexts]) number_of_contexts++; 
   context_nfas = 
      (Nfa**)mem.c_alloc(sizeof(Nfa*) * (number_of_contexts + 1) * 2);

   //
   // Estimate the number of character classes and their combined size
   //
   for (i = 0; i < n; i++) {
      character_class_size += strlen(regexp[i]) + 1;
      for (register const char * p = regexp[i]; *p; p++) 
         if (*p == '[' || *p == '.') number_of_character_classes++;
   }

   //
   // Allocate storage for the character classes
   //
   Bool partitions[257];
   Bool singletons[257];
   Symbol *  char_classes       = 
      (Symbol*)mem[sizeof(Symbol) * character_class_size ];
   Symbol ** character_classes  = 
      (Symbol**)mem[sizeof(Symbol*) * number_of_character_classes];
   number_of_character_classes = 0;

   //
   // Set the partition map to all equivalent initially
   //
   memset(partitions,0,sizeof(partitions));
   memset(singletons,0,sizeof(singletons));

   //
   //
   // Parse the regular expressions and create a non-deterministic
   // automaton.
   //
   Nfa * the_nfa = nil;
   for (bad_rule = -1, i = 0; i < n; i++) {
      Nfa * sub_nfa = 
         construct_nfa(regexp[i],i,mem,number_of_nfa_states,
                       partitions,singletons,
                       &char_classes,character_classes,
                       number_of_character_classes,contexts,
                       number_of_contexts, context_nfas,
                       options & CaseInsensitive
                      );
      if (sub_nfa == nil) { bad_rule = i; return; }
      the_nfa = new(mem,the_nfa,sub_nfa) Nfa;
   }

   //
   // Compute the equivalence class map
   //
   int partition_number = -1;
   max_char = max_ch;
   equiv_classes = new Symbol [max_char + 1];
   for (i = 0; i <= max_char; i++) {
      if ((options & CaseInsensitive) && i >= 'a' && i <= 'z')
         { equiv_classes[i] = equiv_classes[i - 'a' + 'A']; continue; }
      if (partitions[i] || partition_number < 0) 
         partition_number = number_of_equiv_classes++;
      if (singletons[i]) 
         { equiv_classes[i] = number_of_equiv_classes++; continue; }
      equiv_classes[i] = partition_number;
   }

   //
   // Compute the characteristic map for each character class
   //
   BitSet ** char_class_map = 
      (BitSet**)mem[sizeof(BitSet*) * number_of_character_classes];
   for (i = 0; i < number_of_character_classes; i++) {
      BitSet * map = char_class_map[i] = 
         new(mem,number_of_equiv_classes) BitSet;
      register Symbol * p;
      for (p = character_classes[i]; *p != END_CHAR_CLASS; p++) {
         if (*p & RANGE_BIT) {
            for (int a = (*p & 0xff), b = (*++p & 0xff); a <= b; a++) 
               map->add(equiv_classes[a]);
         } else map->add(equiv_classes[*p & 0xff]);
      }
      if (character_classes[i][0] & COMPLEMENT) map->complement();
   }

   //
   // Compute epsilon closure for each state
   //
   Nfa ** nfa_states = 
      (Nfa**) mem.c_alloc(sizeof(Nfa*) * number_of_nfa_states);
   epsilon_closure(the_nfa, mem, number_of_nfa_states, nfa_states, n);

   //
   // Start emitting table
   //
   create_tables(number_of_nfa_states * number_of_equiv_classes,
                 number_of_nfa_states, 0, number_of_equiv_classes-1);
   start();

   //
   // Some auxiliary tables
   //
   BitSet * transitions [256];  // Outgoing state indexed by equiv class
   State      delta       [256];  // DFA state number of outgoing state

   for (i = number_of_equiv_classes - 1; i >= 0; i--)
      transitions[i] = new(mem,number_of_nfa_states) BitSet;

   //
   // Create an error state (state number 0).  This state always jams.
   //
   BitSet * err = new (mem,number_of_nfa_states) BitSet;
   dstates.insert(err,(State)0);
   nstates[0] = err;
   rule[0] = (options & Backtracking) ? -1 : 0;

   //
   // Create two start states for each context, one for the context
   // and one for the context anchored to the beginning of the line.
   //
   for (State s = 1; s < number_of_contexts * 2 + 3; s++) {
      if (context_nfas[s-1] == nil) continue;
      BitSet * set;
      set = new(mem,number_of_nfa_states) BitSet;
      compute_epsilon_closure(context_nfas[s-1],set);
      accept_rule[s] = accept_thinning(set,n);
      dstates.insert(set,s);
      nstates[s] = set;
   } 

   number_of_dfa_states = number_of_contexts * 2 + 3;
  
   //
   // Compute new states
   // 
   for (processed = 1; processed < number_of_dfa_states; processed++) {
      BitSet * set = nstates[processed];
      Bool is_jammed = true;  // no out transitions??
      if (set == nil) continue;
      int j, s;
      for (i = number_of_equiv_classes - 1; i >= 0; i--)
         transitions[i]->clear(); 
      foreach_bit (s, *set) 
         compute_transitions(nfa_states[s],nfa_states,transitions,
                             char_class_map,number_of_equiv_classes,
                             equiv_classes);
      for (i = number_of_equiv_classes - 1; i >= 0; i--) {
         Rule accept = accept_thinning(transitions[i],n);
         Ix d = dstates.lookup(transitions[i]);
         if (d == nil) {
            dstates.insert(transitions[i],number_of_dfa_states);
            nstates[number_of_dfa_states] = transitions[i];
            accept_rule[number_of_dfa_states] = accept;
            delta[i] = number_of_dfa_states++;
            transitions[i] = new(mem,number_of_nfa_states) BitSet;
            is_jammed = false;
         } else {
            delta[i] = dstates.value(d);
            if (delta[i] != 0) is_jammed = false;
         }
      }
      add_state(processed,delta);

      ///////////////////////////////////////////////////////////////////
      //  The rule table actually contains more information than
      //  just the rule number.  It encodes the following information:
      //    (a) the accept rule number $r$ if the state is an accept state 
      //    (b) whether the state is jammed, i.e. having no out going state
      ///////////////////////////////////////////////////////////////////
      if (is_jammed && (options & Backtracking)) 
         rule[processed] = -accept_rule[processed]-1;
      else
         rule[processed] = accept_rule[processed];
   }

   //
   // Finish emitting table
   //
   finish();
}

////////////////////////////////////////////////////////////////////////////
//  Emit C++ code 
////////////////////////////////////////////////////////////////////////////
ostream& LexerGen::gen_code(ostream& out, const char name[]) const
{  if (ok()) { 
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
