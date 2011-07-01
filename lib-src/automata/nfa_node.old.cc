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

#include <AD/automata/nfa_node.h>
#include <AD/memory/mempool.h>
#include <AD/contain/bitset.h>

//////////////////////////////////////////////////////////////////////////////
//  Import some type definitions
//////////////////////////////////////////////////////////////////////////////
typedef DFATables::State  State;
typedef DFATables::Rule   Rule;
typedef DFATables::Symbol Symbol;

//////////////////////////////////////////////////////////////////////////////
//  Memory allocation routine 
//////////////////////////////////////////////////////////////////////////////
//inline void * NFA_Node::operator new(size_t n, MemPool& mem) { return mem[n]; }

//////////////////////////////////////////////////////////////////////////////
//  Constructors and destructors
//////////////////////////////////////////////////////////////////////////////
inline NFA_Node   :: NFA_Node() : closure_set(0) {}
inline NFA_Delta  :: NFA_Delta() : delta_bit(NoDeltaBit) {}
inline NFA_Accept :: NFA_Accept() {}
inline NFA_Or     :: NFA_Or() {}
inline NFA_Epsilon:: NFA_Epsilon() {}
NFA_Node   ::~NFA_Node() {}
NFA_Accept ::~NFA_Accept() {} 
NFA_Or     ::~NFA_Or() {} 
NFA_Delta  ::~NFA_Delta() {} 
NFA_Epsilon::~NFA_Epsilon() {} 

//////////////////////////////////////////////////////////////////////////////
//  Functions to construct NFA nodes
//  (Note: Placement new does not work with constructor with arguments
//   in g++ 2.5.8)
//////////////////////////////////////////////////////////////////////////////
NFA_Accept * mkaccept(MemPool& mem, State s) 
   {  NFA_Accept * n = new (mem) NFA_Accept; 
      n->state = s;
      return n; 
   }
NFA_Or * mkor(MemPool& mem, NFA_Node * x, NFA_Node * y) 
   {  NFA_Or * n = new (mem) NFA_Or; 
      n->out2 = x;
      n->out  = y;
      return n; 
   }
NFA_Delta * mkdelta(MemPool& mem, State s, Symbol c, NFA_Node * out) 
   {  NFA_Delta * n = new (mem) NFA_Delta; 
      n->state = s;
      n->c     = c;
      n->out   = out;
      return n;
   }
NFA_Epsilon * mkepsilon(MemPool& mem, NFA_Node * out) 
   {  NFA_Epsilon * n = new (mem) NFA_Epsilon; 
      n->out = out;
      return n;
   }

//////////////////////////////////////////////////////////////////////////////
//  Compute the epsilon closure from one state
//  Returns the state if the closure is guaranteed to be just a singleton.
//////////////////////////////////////////////////////////////////////////////
int NFA_Accept ::closure(BitSet * set) { set->add(state); return state; }
int NFA_Delta  ::closure(BitSet * set) { set->add(state); return state; }
int NFA_Epsilon::closure(BitSet * set) { out->closure(set); return NoDeltaBit; }
int NFA_Or::closure(BitSet * set) 
   { out->closure(set); out2->closure(set); return NoDeltaBit; }

//////////////////////////////////////////////////////////////////////////////
//  Compute the epsilon closure for all states
//////////////////////////////////////////////////////////////////////////////
BitSet * NFA_Accept::epsilon_closure
   (MemPool& mem, size_t N, size_t rules, NFA_Delta * A[])
{  if (closure_set) return closure_set;
   closure_set = new(mem,N) BitSet;
   closure_set->add(state);            // add accept state 
   return closure_set;
}

BitSet * NFA_Epsilon::epsilon_closure
   (MemPool& mem, size_t N, size_t rules, NFA_Delta * A[])
{  if (closure_set) return closure_set;
   return closure_set = out->epsilon_closure(mem,N,rules,A);
}

BitSet * NFA_Delta::epsilon_closure
   (MemPool& mem, size_t N, size_t rules, NFA_Delta * A[])
{  if (closure_set) return closure_set;
   A[state] = this;
   closure_set = new(mem,N) BitSet;
   closure_set->add(state);
   delta_bit = out->closure(delta_set = new(mem,N) BitSet);
   out->epsilon_closure(mem, N, rules, A);
   return closure_set;
}

BitSet * NFA_Or::epsilon_closure
   (MemPool& mem, size_t N, size_t rules, NFA_Delta * A[])
{  if (closure_set) return closure_set;

   closure_set = new(mem,N) BitSet;
   out->closure(closure_set);
   out2->closure(closure_set);

   accept_thinning(closure_set,rules);

   out->epsilon_closure(mem, N, rules, A);  
   out2->epsilon_closure(mem, N, rules, A); 

   return closure_set;
}
