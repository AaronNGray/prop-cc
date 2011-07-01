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

#ifndef nondeterministic_finite_automata_h
#define nondeterministic_finite_automata_h

#include <AD/generic/generic.h>    // Generic definitions
#include <AD/automata/dfatable.h>  // DFA tables internals

//////////////////////////////////////////////////////////////////////////////
//  Opaque definitions
//////////////////////////////////////////////////////////////////////////////

class MemPool;
class NFA_Node;
class NFA_Delta;
class FastBitSet;

//////////////////////////////////////////////////////////////////////////////
//
//  Class NFA represents an NFA.  Used in lexer generation.
//
//////////////////////////////////////////////////////////////////////////////

class NFA : public DFATables {
   NFA( const NFA&);               // no copy constructor
   void operator = ( const NFA&);  // no assignment
public:
   enum { MAX_STAR_HEIGHT    = 256,
          MAX_REGEXP_LENGTH  = 4096,
          MAX_CONTEXTS       = 256,
          MAX_CONTEXT_LENGTH = 1024
        };
   enum { RANGE_BIT      = 0x80000000,
          COMPLEMENT     = 0x40000000,
          END_CHAR_CLASS = 0x20000000,
          MASK_BITS      = 0x0000ffff
        };

protected:
   ///////////////////////////////////////////////////////////////////////////
   // Interal members
   ///////////////////////////////////////////////////////////////////////////
   MemPool&             mem;              // current memory pool
   Bool                 own_mem;          // memory owned by us?
   NFA_Node *           nfa;              // root of the nfa
   const char * const * contexts;         // current set of contexts
   Symbol               max_char;         // maximum character encoding
   State                number_of_states; // number of states
   char *               is_singleton;     // is character a singleton?
   Bool                 case_insensitive; // case insensitive?
   NFA_Node *           save_top;
   NFA_Node *           save_root;
   NFA_Node *           save_next;
   NFA_Delta **         nfa_states;
   const char *         regexp_begin;
   Bool                 anchored;

   ///////////////////////////////////////////////////////////////////////////
   // Error reporting
   ///////////////////////////////////////////////////////////////////////////
   int                  number_of_errors;
   Rule                 bad_rule;
   const char *         error_message;

   ///////////////////////////////////////////////////////////////////////////
   //  Context stuff
   ///////////////////////////////////////////////////////////////////////////
   NFA_Node **          context_nfas;
   int                  number_of_contexts;

   ///////////////////////////////////////////////////////////////////////////
   //  Character class stuff
   ///////////////////////////////////////////////////////////////////////////
   Symbol *      char_classes;
   Symbol **     char_class_table;
   char   *      partitions;
   int           number_of_char_classes;
   FastBitSet ** char_class_maps;

   ///////////////////////////////////////////////////////////////////////////
   //  Equivalence class stuff
   ///////////////////////////////////////////////////////////////////////////
   Symbol *  equiv_classes;
   int       number_of_equiv_classes;

   ///////////////////////////////////////////////////////////////////////////
   // Helper methods
   ///////////////////////////////////////////////////////////////////////////
   virtual void error( const char * message);
   virtual NFA_Node * parse( Rule rule, const char * regexp);
   Symbol parse_dot ();
   const char * parse_char_class( const char *, Symbol&);
   const char * parse_context( const char *, Bool []);
   NFA_Node *  construct( const char *&, NFA_Node *&);
   NFA_Node *  construct_concat( const char *&, NFA_Node *&);
   NFA_Node *  construct_one( const char *&, NFA_Node *&);
   void compute_equiv_classes();
   void compute_char_class_map();

public:
   ///////////////////////////////////////////////////////////////////////////
   // Constructors and destructor
   ///////////////////////////////////////////////////////////////////////////
            NFA();
            NFA( MemPool&);
   virtual ~NFA();

   ///////////////////////////////////////////////////////////////////////////
   // Method to compile a set of regular expressions into an NFA.
   ///////////////////////////////////////////////////////////////////////////
   virtual void compile
      ( int                  number_of_rules,
        const char * const * regexps,
        const char * const * contexts,
        Symbol               max_character = 255,
        Bool                 case_insensitive = false
      );

   ///////////////////////////////////////////////////////////////////////////
   // Method to compute the equiv class table.
   ///////////////////////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////////////////////
   //  Selectors
   ///////////////////////////////////////////////////////////////////////////
   inline int    errors ()            const { return number_of_errors; }
   inline Rule   bad()                const { return bad_rule; }
   inline const char * error_msg ()   const { return error_message; }
   inline int    state_count ()       const { return number_of_states; }
   inline int    context_count ()     const { return number_of_contexts; }
   inline int    equiv_class_count () const { return number_of_equiv_classes; }
   inline int    char_class_count ()  const { return number_of_char_classes; }
   inline NFA_Node * nfa_unanchored(int i) const { return context_nfas[i*2]; }
   inline NFA_Node * nfa_anchored(int i)   const { return context_nfas[i*2+1];}
   inline NFA_Node * context_nfa(int i)    const { return context_nfas[i];}
   inline NFA_Node * root ()               const { return nfa; }
   inline NFA_Delta * operator [] (int i)        { return nfa_states[i]; }
   inline Symbol   * get_equiv_classes ()        { return equiv_classes; }
   inline const Symbol * char_class(int i) const
      { return char_class_table[-i-1];}
   inline const FastBitSet * char_class_map(int i) const
      { return char_class_maps[-i-1]; }
};

#endif
