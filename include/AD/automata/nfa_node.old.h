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

#ifndef nondeterministic_finite_automata_nodes_h
#define nondeterministic_finite_automata_nodes_h

#include <stdlib.h>
#include <AD/automata/dfatable.h>  // DFA tables internals
#include <AD/contain/bitset.h>

//////////////////////////////////////////////////////////////////////////////
//  Opaque definitions
//////////////////////////////////////////////////////////////////////////////
class MemPool;
class NFA_Delta;

//////////////////////////////////////////////////////////////////////////////
//  Base class for an NFA node
//////////////////////////////////////////////////////////////////////////////
class NFA_Node {
   NFA_Node(const NFA_Node&);          // no copy constructor
   void operator = (const NFA_Node&);  // no assignment
public:
   typedef DFATables::Symbol Symbol;
   typedef DFATables::State  State;
   typedef DFATables::Rule   Rule;
protected:
   enum { NoDeltaBit = -1 };
   BitSet   * closure_set;  // epsilon_closure
   NFA_Node * out;          // out transition
   NFA_Node(); 
   virtual ~NFA_Node();
public:
   inline void set_out(NFA_Node * n) { out = n; }

   virtual int closure (BitSet *) = 0;
   virtual BitSet * epsilon_closure 
     (MemPool&    mem_pool, 
      size_t      number_of_states, 
      size_t      number_of_rules, 
      NFA_Delta * state_table[]
     ) = 0;

   ///////////////////////////////////////////////////////////////////////////
   //  Thin the accept states.  I.e. select the first accept state
   //  and eliminate the rest
   ///////////////////////////////////////////////////////////////////////////
   inline static Rule accept_thinning
      (register BitSet * set, register size_t rules)
   {  for (register int i = 0; i < rules; i++)
      {  if ((*set)[i]) {
            //for (register int j = i+1; j < rules; j++) set->remove(j);
            return i+1;
         }
      }
      return 0;
   }
};

//////////////////////////////////////////////////////////////////////////////
//  Base class for an accept NFA node
//////////////////////////////////////////////////////////////////////////////
class NFA_Accept : public NFA_Node {
   NFA_Accept(const NFA_Accept&);        // no copy constructor
   void operator = (const NFA_Accept&);  // no assignment
protected:
   State state;  // nfa state
   virtual int closure (BitSet *);
   NFA_Accept();
  ~NFA_Accept();
public:
   virtual BitSet * epsilon_closure (MemPool&, size_t, size_t, NFA_Delta * []);
   friend NFA_Accept * mkaccept(MemPool&, State);
};

//////////////////////////////////////////////////////////////////////////////
// Epsilon node
//////////////////////////////////////////////////////////////////////////////
class NFA_Epsilon : public NFA_Node {
   NFA_Epsilon(const NFA_Epsilon&);       // no copy constructor
   void operator = (const NFA_Epsilon&);  // no assignment
private:
   virtual int closure (BitSet *);
   NFA_Epsilon();
  ~NFA_Epsilon();
public:
   virtual BitSet * epsilon_closure (MemPool&, size_t, size_t, NFA_Delta * []);
   friend NFA_Epsilon * mkepsilon(MemPool&, NFA_Node *);
};

//////////////////////////////////////////////////////////////////////////////
//  Disjunction
//////////////////////////////////////////////////////////////////////////////
class NFA_Or : public NFA_Node {
   NFA_Or(const NFA_Or&);            // no copy constructor
   void operator = (const NFA_Or&);  // no assignment
private:
   NFA_Node * out2;  // the second out transition
   virtual int closure (BitSet *);
   NFA_Or();
  ~NFA_Or();
public:
   inline void set_out2(NFA_Node * n) { out2 = n; }
   virtual BitSet * epsilon_closure (MemPool&, size_t, size_t, NFA_Delta * []);
   friend NFA_Or * mkor(MemPool&, NFA_Node *, NFA_Node *);
};

//////////////////////////////////////////////////////////////////////////////
//  Delta NFA node
//////////////////////////////////////////////////////////////////////////////
class NFA_Delta : public NFA_Accept {
   NFA_Delta(const NFA_Delta&);         // no copy constructor
   void operator = (const NFA_Delta&);  // no assignment
private:
   Symbol     c;         // out transition character
   int        delta_bit; // state bit of delta_set if delta_set is
                         // a singleton or empty.
   BitSet   * delta_set; // set of out transition states(after closure)
   virtual int closure (BitSet *);
   NFA_Delta();
  ~NFA_Delta();
public:
   virtual BitSet * epsilon_closure (MemPool&, size_t, size_t, NFA_Delta * []);
   inline BitSet * delta  () const { return delta_set; }
   inline void     add_delta (BitSet * set) const 
      { if (delta_bit >= 0) set->add(delta_bit);
        else set->Union(*delta_set);
      }
   inline Symbol   symbol () const { return c; }
   friend NFA_Delta * mkdelta(MemPool&, State, Symbol, NFA_Node *);
};

#endif
