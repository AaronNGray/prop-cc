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

#include <ctype.h>
#include <string>
#include <AD/automata/nfa_node.h>
#include <AD/automata/nfa.h>
#include <AD/memory/mempool.h>
#include <AD/contain/fbitset.h>
#include <AD/strings/charesc.h>
#include <AD/strings/quark.h>

//////////////////////////////////////////////////////////////////////////////
//  Import some type definitions
//////////////////////////////////////////////////////////////////////////////

typedef DFATables::State  State;
typedef DFATables::Rule   Rule;
typedef DFATables::Symbol Symbol;

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor for class NFA
//////////////////////////////////////////////////////////////////////////////

NFA:: NFA()
    : mem(* new MemPool), own_mem(true), nfa(0), contexts(0), max_char(0),
    number_of_states(0), is_singleton(0), nfa_states(0), context_nfas(0),
    number_of_contexts(0), partitions(0)
{
  number_of_errors = 0;
  bad_rule = -1;
  error_message = 0;
}

NFA:: NFA( MemPool& m)
    : mem(m), own_mem(false), nfa(0), contexts(0), max_char(0),
    number_of_states(0), is_singleton(0), nfa_states(0), context_nfas(0),
    number_of_contexts(0), partitions(0)
{
  number_of_errors = 0;
  bad_rule = -1;
  error_message = 0;
}

NFA::~NFA()
{
  if (own_mem)
    delete (&mem);
}

//////////////////////////////////////////////////////////////////////////////
//  Error handler
//////////////////////////////////////////////////////////////////////////////

void NFA::error(const char * message)
{
  number_of_errors++;
  error_message = message;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Tags for the parse stack
//
//////////////////////////////////////////////////////////////////////////////

#define PAREN       (NFA_Node*)0
#define DISJUNCTION (NFA_Node*)1
#define CONS        (NFA_Node*)2

//////////////////////////////////////////////////////////////////////////////
// Method to construct a character class for '.'
//////////////////////////////////////////////////////////////////////////////

Symbol NFA::parse_dot()
{
  is_singleton['\n'] = true;
  char_classes[0] = '\n' | COMPLEMENT;
  char_classes[1] = END_CHAR_CLASS;
  char_class_table[number_of_char_classes++] = char_classes;
  char_classes += 2;
  return -number_of_char_classes;
}

//////////////////////////////////////////////////////////////////////////////
// Method to parse a character class
//////////////////////////////////////////////////////////////////////////////

const char * NFA::parse_char_class( const char * p, Symbol& c)
{
  Bool is_complemented = false;
  const char * start = p;
  Symbol * P = char_classes;
  Symbol * Q = 0;
  Symbol range_begin = -1;
  for (;;)
  {
    switch (*p)
    {
    case '-':
      {
        if (range_begin < 0)
        {
          error ("missing lhs in '-'");
          return 0;
        }
        if (Q)
        {
          error ("duplicated '-'");
          return 0;
        }
        Q = P-1;
        p++;
      }
      break;
    case '\0':
      {
        error ("missing ']' in character class");
        return 0;
      }
    case ']':
      {
        *P++ = END_CHAR_CLASS;
        if (is_complemented)
          char_classes[0] |= COMPLEMENT;
        char_class_table[number_of_char_classes++]
        = char_classes;
        char_classes = P;
        c = -number_of_char_classes;
        return p+1;
      }
    case '^':
      {
        if (p == start)
        {
          is_complemented = true;
          p++;
          break;
        }
      }  // falls thru
    default:
      {
        char ch;
        Symbol ch2;
        p = parse_char(p,ch);
        if (case_insensitive)
          ch = toupper(ch);
        *P++ = ch2 = (unsigned char)ch;
        if (Q)   // end of range???
          {  if (range_begin >= ch2)
          {
            error ("bad range in character class");
            return 0;
          }
          *Q |= RANGE_BIT;
          range_begin = -1;
          Q = 0;
          partitions[ch2+1] = true;
        }
        else
        {
          range_begin = ch2;
          partitions[ch2] = true;
          if (*p != '-')
            is_singleton[ch2] = true;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
// Method to parse the context
//////////////////////////////////////////////////////////////////////////////

const char * NFA::parse_context( const char * p, Bool context_used[])
{
  char name[NFA::MAX_CONTEXT_LENGTH];
  char * cursor = name;
  for (int i = 0; i < number_of_contexts; i++)
    context_used[i] = false;

  for (;;)
  {
    switch (*p)
    {
    case ',':
    case '>':
      {
        *cursor = '\0';
        Bool found = false;
        if (contexts)
        {
          const char * const * q;
          int context_number = 0;
          for (q = contexts; *q; q++, context_number++)
          {
            if (strcmp(*q,name) == 0)
            {
              found = context_used[context_number] = true;
              break;
            }
          }
        }
        if (!found)
        {
          error (Quark("undefined context <",name,">"));
          return 0;
        }
        if (*p == '>')
          return p+1;
        cursor = name;
        p++;
      }
      break;
    case 0:
      {
        error ("missing '>' in contexts");
        return 0;
      }
    default:
      *cursor++ = *p++;
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Join two nodes together
//////////////////////////////////////////////////////////////////////////////
inline NFA_Node * join( MemPool& mem, NFA_Node * a, NFA_Node * b)
{
  return a ? mkor( mem, a, b) : b;
}

//////////////////////////////////////////////////////////////////////////////
//  Parse a regular expression and constructor an NFA.
//////////////////////////////////////////////////////////////////////////////

NFA_Node * NFA::construct
( const char *& regexp,   // the regular expression string
  NFA_Node *&   new_cont  // new continuation
)
{
  NFA_Node * root = construct_concat(regexp,new_cont);
  for (;;)
  {
    switch (*regexp)
    {
    case '|':
      {
        regexp++;
        NFA_Node * cont2;
        NFA_Node * root2 = construct(regexp,cont2);
        if (root == 0 && root2 == 0)
        {
          root = 0;
        }
        else if (root == 0)
        {
          NFA_Node * join = mkepsilon(mem,0);
          NFA_Node * sel   = mkor(mem,root2,join);
          cont2->set_out(join);
          new_cont = join;
          root = sel;
        }
        else if (root2 == 0)
        {
          NFA_Node * join = mkepsilon(mem,0);
          NFA_Node * sel   = mkor(mem,root,join);
          new_cont->set_out(join);
          new_cont = join;
          root = sel;
        }
        else
        {
          NFA_Node * sel = mkor(mem,root,root2);
          NFA_Node * join = mkepsilon(mem,0);
          new_cont->set_out(join);
          cont2->set_out(join);
          new_cont = join;
          root = sel;
        }
      }
      return root;
    case '\0':
    case ')':
      {
        return root;
      }
    default:
      {
        error("Syntax error");
        return 0;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Parse a concatenation
//////////////////////////////////////////////////////////////////////////////

NFA_Node * NFA::construct_concat
( const char *& regexp,   // the regular expression string
  NFA_Node *&   new_cont  // new continuation
)
{
  NFA_Node * root = 0;
  new_cont = 0;
  for (;;)
  {
    NFA_Node * cont = 0;
    NFA_Node * one  = construct_one(regexp,cont);
    if (root)
    {
      if (new_cont == 0)
      {
        error ("missing ')'???");
        return 0;
      }
      new_cont->set_out(one);
      new_cont = cont;
    }
    else
    {
      root = one;
      new_cont = cont;
    }
    switch (*regexp)
    {
    case '|':
    case ')':
    case '\0':
      return root;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Parse one component of a regular expression
//////////////////////////////////////////////////////////////////////////////

NFA_Node * NFA::construct_one
( const char *& regexp,   // the regular expression string
  NFA_Node *&   new_cont  // new continuation
)
{
  Symbol c;
  char ch;
  NFA_Node * root = 0;
  new_cont = 0;
  do
  {
    switch (*regexp++)
    {
    case '|':
    case '\0':
      {
        regexp--;
        return root;
      }
    case '(':
      {
        root = construct(regexp,new_cont);
        if (*regexp != ')')
        {
          error ("missing closing ')'");
          return 0;
        }
        regexp++;
      }
      break;
    case ')':
      {
        error ("missing opening '('");
        return 0;
      }
    case ']':
      {
        error ("missing opening '['");
        return 0;
      }
    case '+':
      {
        if (root == 0)
        {
          error ("missing prefix for +");
          return 0;
        }
        NFA_Node * n = mkor(mem,root,0);
        new_cont->set_out(n);
        new_cont = n;
      }
      break;
    case '*':
      {
        if (root == 0)
        {
          error ("missing prefix for *");
          return 0;
        }
        NFA_Node * n = mkor(mem,root,0);
        new_cont->set_out(n);
        root = new_cont = n;
      }
      break;
    case '?':
      {
        if (root == 0)
        {
          error ("missing prefix for ?");
          return 0;
        }
        NFA_Node * n1 = mkepsilon(mem,0);
        NFA_Node * n2 = mkor(mem,root,n1);
        root     = n2;
        new_cont->set_out(n1);
        new_cont = n1;
      }
      break;
    case '.':
      {
        c = parse_dot();
        goto MAKE_DELTA;
      }
    case '[':
      {
        regexp = parse_char_class(regexp,c);
        if (regexp == 0)
          return 0;
        else
          goto MAKE_DELTA;
      }
    case '^':
      {
        if (regexp-1 == regexp_begin)
        {
          anchored = true;
          break;
        }
      } // falls thru
    default:
      regexp = parse_char(regexp-1,ch);
      c = (unsigned char)ch;
      if (case_insensitive)
        c = toupper(c);
MAKE_DELTA:
      {
        if (c >= 0)
          is_singleton[c] = true;
        State s = number_of_states++;
        root = new_cont = mkdelta(mem,s,c,0);
      }
      break;
    }
  }
  while (*regexp == '*' || *regexp == '+' || *regexp == '?');
  return root;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to construct an NFA from a regular expression
//////////////////////////////////////////////////////////////////////////////

NFA_Node * NFA::parse( Rule rule, const char * regexp)
{
  NFA_Node * root, * cont;  // root and pointer to next node
  const char * p;           // current pointer
  anchored = false;         // should pattern start at beginning of line?
  Bool context_used[NFA::MAX_CONTEXTS];
  Bool has_context = false;

  ///////////////////////////////////////////////////////////////////////////
  //  Initialize
  ///////////////////////////////////////////////////////////////////////////
  p    = regexp;
  root = cont = 0;

  ///////////////////////////////////////////////////////////////////////////
  //  Look for context (if any)
  ///////////////////////////////////////////////////////////////////////////
  if (*p == '<')
  {
    has_context = true;
    p = parse_context(p+1,context_used);
    if (p == 0)
      goto ERROR;
    regexp = p;
  }
  regexp_begin = regexp;

  ///////////////////////////////////////////////////////////////////////////
  //  Now parse the regexp
  ///////////////////////////////////////////////////////////////////////////
  root = construct(regexp,cont);
  if (*regexp != '\0')
    error ("syntax error");
  if (*regexp == ')')
    error ("missing opening '('");

  ///////////////////////////////////////////////////////////////////////////
  // Create an accept node
  ///////////////////////////////////////////////////////////////////////////
  {  NFA_Node * n = mkaccept(mem,rule);
    if (cont)
    {
      cont->set_out(n);
    }
    else
    {
      root = n;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // For each context in which the nfa appears, add it to the context table.
  ///////////////////////////////////////////////////////////////////////////
  if (! anchored)
    context_nfas[0] = join(mem, context_nfas[0], root);
  context_nfas[1] = join(mem, context_nfas[1], root);
  {
    for (int i = 0; i < number_of_contexts; i++)
    {
      if (!has_context || context_used[i])
      {
        if (! anchored)
        {
          context_nfas[2 * i + 2] =
            join(mem, context_nfas[2 * i + 2], root);
        }
        context_nfas[2 * i + 3] = join(mem, context_nfas[2 * i + 3], root);
      }
    }
  }

  return root;

ERROR:
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compile a set of regular expressions into an NFA.
//////////////////////////////////////////////////////////////////////////////

void NFA::compile(
            int                  number_of_rules,
            const char * const * regexps,
            const char * const * my_contexts,
            Symbol               max_character,
            Bool                 is_case_insensitive
            )
{
  ///////////////////////////////////////////////////////////////////////////
  // Initialization
  ///////////////////////////////////////////////////////////////////////////
  number_of_errors = 0;
  bad_rule         = -1;
  contexts = my_contexts;   // set the current set of contexts
  max_char = max_character; // set the current maximal character
  // in the character set.
  case_insensitive = is_case_insensitive;
  nfa = 0;                  // reset the nfa.
  //  State 0 is the error state
  //  State 1 ... number_of_rules are the accept states.
  number_of_states = number_of_rules;
  is_singleton = (char*)mem.c_alloc(sizeof(char) * (max_character + 1));
  partitions   = (char*)mem.c_alloc(sizeof(char) * (max_character + 2));

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate space for the character classes stuff
  ///////////////////////////////////////////////////////////////////////////
  number_of_char_classes = 0;
  {
    int max_char_classes = 0;
    int max_storage      = 0;
    for (int i = 0; i < number_of_rules; i++)
    {
      max_storage += strlen(regexps[i]) + 1;
      for (const char * p = regexps[i]; *p; p++)
      {
        if (*p == '.' || *p == '[')
        {
          max_char_classes++;
          max_storage++;
        }
      }
    }
    char_classes = (Symbol*)mem.c_alloc(sizeof(Symbol) * max_storage);
    char_class_table =
      (Symbol**)mem.c_alloc(sizeof(Symbol*) * max_char_classes);
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate space for the context stuff
  ///////////////////////////////////////////////////////////////////////////
  {  const char * const * p = my_contexts;
    number_of_contexts = 0;
    context_nfas = 0;
    if (p)
      while (*p)
      {
        p++;
        number_of_contexts++;
      }
    context_nfas =
      (NFA_Node**)mem.c_alloc
      (sizeof(NFA_Node*) * (2 * number_of_contexts + 2));
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Now construct the nfa.
  ///////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < number_of_rules; i++)
  {
    NFA_Node * sub_nfa = parse(i, regexps[i]);
    if (number_of_errors > 0 && bad_rule < 0)
      bad_rule = i;
    if (sub_nfa != 0)
      nfa = join(mem,nfa,sub_nfa);
  }

  if (number_of_errors > 0)
    return;

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the epsilon closure
  ///////////////////////////////////////////////////////////////////////////
  nfa_states = (NFA_Delta**)mem.c_alloc(sizeof(NFA_Delta*) * number_of_states);
  nfa->epsilon_closure(mem, number_of_states, number_of_rules, nfa_states);

  ///////////////////////////////////////////////////////////////////////////
  //  Compute the equivalence class and character class maps
  ///////////////////////////////////////////////////////////////////////////
  compute_equiv_classes();
  compute_char_class_map();
}

//////////////////////////////////////////////////////////////////////////////
//  Method to compute the equivalence class map.
//////////////////////////////////////////////////////////////////////////////

void NFA::compute_equiv_classes()
{
  equiv_classes = new Symbol [max_char+1];
  int partition_number = -1;
  number_of_equiv_classes = 0;
  for (int i = 0; i <= max_char; i++)
  {
    if (case_insensitive && i >= 'a' && i <= 'z')
    {
      equiv_classes[i] = equiv_classes[i - 'a' + 'A'];
      continue;
    }
    if (partitions[i] || partition_number < 0)
    {
      partition_number = number_of_equiv_classes++;
    }
    if (is_singleton[i])
    {
      equiv_classes[i] = number_of_equiv_classes++;
      continue;
    }
    equiv_classes[i] = partition_number;
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//  Compute the characteristic map for each character classes
//
//////////////////////////////////////////////////////////////////////////////

void NFA::compute_char_class_map()
{
  char_class_maps =
    (FastBitSet**)mem.m_alloc(sizeof(FastBitSet*) * number_of_char_classes);
  for (int i = 0; i < number_of_char_classes; i++)
  {
    FastBitSet * set
      =
        char_class_maps[i] = new (mem) FastBitSet(mem, number_of_equiv_classes);
    const Symbol * C = char_class_table[i];
    for (const Symbol * P = C; *P != END_CHAR_CLASS; P++)
    {
      register Symbol A = *P & MASK_BITS;
      if (*P & RANGE_BIT)
      {
        for (register Symbol B = *++P & MASK_BITS; A <= B; A++)
          set
            ->add
            (equiv_classes[A]);
      }
      else
      {
        set
          ->add
          (equiv_classes[A]);
      }
    }
    if (*C & COMPLEMENT)
      set
        ->complement();
  }
}
