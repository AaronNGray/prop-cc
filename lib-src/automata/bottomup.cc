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

////////////////////////////////////////////////////////////////////////////
//  This file implements a pattern matcher compiler for bottom-up tree
//  matching.  Instead of representing states using match sets as in
//  Hoffmann O'Donnell, we'll use most general linear unifiers as in
//  Lippe instead.  Notice that the closure set of unifiers form a complete
//  partial order.  We'll use this property to devise our algorithms.
////////////////////////////////////////////////////////////////////////////

#include <string>
#include <stdlib.h>
#include <AD/automata/bottomup.h> // bottomup tree matcher/matcher-compiler
#include <AD/contain/dchmap.h>    // Map based on direct chaining hash tables
#include <AD/contain/stack.h>     // generic stacks
#include <AD/contain/vararray.h>  // generic array
#include <AD/contain/varqueue.h>  // generic queue
#include <AD/memory/mempool.h>    // memory pool

////////////////////////////////////////////////////////////////////////////
//  Make hidden types visible
////////////////////////////////////////////////////////////////////////////

typedef BottomUp::Arity   Arity;
typedef BottomUp::Functor Functor;
typedef BottomUp::State   State;

////////////////////////////////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////////////////////////////////

BottomUp:: BottomUp(Mem& m) : TreeAutomaton(m)
{}

BottomUp::~BottomUp()
{}

////////////////////////////////////////////////////////////////////////////
// Class |Pair| represents a 2-tuple, of course.
////////////////////////////////////////////////////////////////////////////

#define Pair Pair__
template <class A, class B>
class Pair
{
public:
  A a;
  B b;
  Pair(A x, B y) : a(x), b(y)
  {}
  Pair()
  {}
  A fst() const
  {
    return a;
  }
  B snd() const
  {
    return b;
  }
  //friend Bool operator == (const Pair&, const Pair&);
};

////////////////////////////////////////////////////////////////////////////
//  Class |UnifierSet| represents a set of unifiers in a bit vector format
////////////////////////////////////////////////////////////////////////////

class UnifierSet
{
  int  n;
  Byte bits[1];

public:
  inline operator const Byte* () const
  {
    return bits;
  }

  inline operator Byte* ()
  {
    return bits;
  }

  inline void setUnion (int i)
  {
    bitSet(bits,i);
  }

  inline void setUnion( UnifierSet& set)
  {
    for (register int i = n - 1; i >= 0; i--)
      bits[i] |= set.bits[i];
  }

  inline int  size () const
  {
    return n;
  }

  inline Bool operator [] (int i)
  {
    return bitOf(bits,i);
  }

  inline void clear()
  {
    for (register int i = n - 1; i >= 0; i--)
      bits[i] = 0;
    bitSet(bits,0);
  }

  inline Byte operator () (int i)
  {
    return bits[i];
  }

  inline void * operator new (size_t, MemPool& pool, int n)
  {
    UnifierSet * x =
      (UnifierSet*)pool[sizeof(UnifierSet) + (n-1) * sizeof(Byte)];
    for (register int i = n - 1; i >= 0; i--)
      x->bits[i] = 0;
    x->n = n;
    bitSet(x->bits,0);
    return x;
  }

  inline void operator delete (void *)
  {}
};

////////////////////////////////////////////////////////////////////////////
// A quick test to screen out non unifiable terms
////////////////////////////////////////////////////////////////////////////

inline Bool nonunifiable( const TreePat * a, const TreePat * b)
{
  return a->tag() != b->tag();
}

////////////////////////////////////////////////////////////////////////////
//  A pair of arguments to the unification routine, and
//  A pair of subterm and its state number
////////////////////////////////////////////////////////////////////////////

typedef TreePat *                        TreePatPtr;
typedef Pair<TreePatPtr,TreePatPtr>      TreePatPair;
typedef Pair<TreePatPtr,State>           Unifier;
typedef UnifierSet *                     UnifierSetPtr;

//////////////////////////////////////////////////////////////////////////////
// Shallow equality comparison for a term pattern; used by the memo functions.
// Shallow equality(and hashing) rather than deep equality(and hashing)
// is sufficient since we'll be using ``hash-consing'' to share all terms
// maximally.
//////////////////////////////////////////////////////////////////////////////

inline Bool equal( const TreePat * a, const TreePat * b)
{
  if (isWild(a) && isWild(b))
    return true;
  if (isWild(a) || isWild(b))
    return false;
  if (a->tag() != b->tag())
    return false;
  for (register int i = a->arity() - 1; i >= 0; i--)
    if (a->nth(i) != b->nth(i))
      return false;
  return true;
}

////////////////////////////////////////////////////////////////////////////
//  Shallow hash function for a term; used by the memo functions
////////////////////////////////////////////////////////////////////////////

inline unsigned int hash( const TreePat * a)
{
  if (isWild(a))
    return 73;  // some prime number for better hashing
  unsigned int hash_value;
  int i;
  for (hash_value = a->tag(), i = a->arity() - 1; i >= 0; i--)
    hash_value += hash_value + (unsigned int)a->nth(i);
  return hash_value;
}

////////////////////////////////////////////////////////////////////////////
//  Equality for a pair of term patterns; used in the unification memo
//  function.  Notice that since linear unification is commutitive, we'll
//  also commute the pairs and check for equality.
////////////////////////////////////////////////////////////////////////////

inline Bool operator == (const TreePatPair& a, const TreePatPair& b)
{
  return equal(a.fst(), b.fst()) && equal(a.snd(), b.snd()) ||
         equal(a.fst(), b.snd()) && equal(a.snd(), b.fst());
}

inline Bool equal(const TreePatPair& a, const TreePatPair& b)
{
  return a == b;
}

////////////////////////////////////////////////////////////////////////////
//  Hash function for a pair of term patterns
////////////////////////////////////////////////////////////////////////////

inline unsigned int hash( const TreePatPair& a)
{
  return hash(a.fst()) + hash(a.snd());
}

////////////////////////////////////////////////////////////////////////////
//  The map that maps unifiers to its state number is called UnifiersMemo.
//  The map that memorizes unification is called UnifyMemo.
////////////////////////////////////////////////////////////////////////////

typedef DCHMap <TreePatPtr, State>       UnifiersMemo;
typedef DCHMap <TreePatPair, TreePatPtr> UnifyMemo;
typedef UnifiersMemo ApproxMemo;

////////////////////////////////////////////////////////////////////////////
//  Compute the set of subterms bottom-up recursively and memorize them.
//  Notice that all isomorphic subterms are shared after this construction;
//  we'll also give each subterm each own state number.
////////////////////////////////////////////////////////////////////////////

static TreePat * collect_subterms
( TreePat * a, UnifiersMemo& memo, MemPool& pool,
  VarArray<TreePat *>& states, State& new_state )
{
  TreePatBuf D;
  Ix previous;
  TreePat * a_term;

  if (isWild(a))
    return a;

  for (int i = 0; i < a->arity(); i++)
    D.p.subterms[i] = collect_subterms(a->nth(i),memo,pool,states,new_state);
  D.p.f = a->tag();
  D.p.n = a->arity();
  previous = memo.lookup(&D.p);
  if (previous)
    return memo.key(previous);
  a_term = new (pool,a->tag(),a->arity(),D.p.subterms) TreePat;
  memo.insert(a_term, new_state);
  states[new_state++] = a_term;
  return a_term;
}

////////////////////////////////////////////////////////////////////////////
//  Compute the linear unifier of terms a and b with memorization.
//  Returns the variable X if the two terms a and b are not unifiable.
//  Also, if a new unifier is computed, we'll generate a new
//  state and enter it into the unifiers map.
////////////////////////////////////////////////////////////////////////////
#define X (TreePat *)0
#define Fail (TreePat *)1

static TreePat * unify
( TreePat * a, TreePat * b,
  UnifiersMemo& unifiers, UnifyMemo& memo, MemPool& pool,
  VarArray<TreePat *>& states, State& new_state )
{
  TreePat * answer;
  TreePatBuf D;

  //
  //  We'll check for simple situations first
  //
  if (a->tag() != b->tag())
    return Fail;

  //
  // If these tests do not apply, we'll lookup up the pair a and b
  // from the map instead.
  //
  Ix previous;
  if ((previous = memo.lookup(TreePatPair(a,b))))
    return memo.value(previous);

  //
  // If the answer is not in the map, we'll have to compute them recursively.
  //
  int i;
  for (i = a->arity() - 1; i >= 0; i--)
  {
    if (isWild(a->nth(i)))
    {
      D.p.subterms[i] = b->nth(i);
      continue;
    }
    if (isWild(b->nth(i)))
    {
      D.p.subterms[i] = a->nth(i);
      continue;
    }
    if ((D.p.subterms[i] =
           unify(a->nth(i),b->nth(i),unifiers,memo,pool,states,new_state))
        == Fail)
      return Fail;
  }

  //
  // Add a new unifier if we have computed a new one.
  //

  D.p.f = a->tag();
  D.p.n = a->arity();
  Ix last;
  if ((last = unifiers.lookup(&D.p)))
  {
    answer = unifiers.key(last);
    goto update_table;
  }
  answer = new (pool, a->tag(),a->arity(),D.p.subterms) TreePat;
  unifiers[answer] = new_state;
  states[new_state++] = answer;

update_table:

  //
  // Now, update the result so that we'll find them again from the table
  // next time.
  //
  if (memo.size() < 500)
    memo[TreePatPair(a,b)] = answer;
  return answer;
}

////////////////////////////////////////////////////////////////////////////
//  Compute the subset of terms at each position of each functor.
////////////////////////////////////////////////////////////////////////////

static void collect_arguments
( TreePat * p, UnifiersMemo& unifiers, UnifierSet ** relevant_sets[])
{
  if (! isWild(p))
  {
    //
    // For each argument, compute the set of patterns that
    // can appear at each functor
    //
    for (int i = p->arity() - 1; i >= 0; i--)
    {
      collect_arguments(p->nth(i), unifiers, relevant_sets);
      relevant_sets[p->tag()][i]->setUnion(unifiers[p->nth(i)]);
    }
  }
}

////////////////////////////////////////////////////////////////////////////
//  Compute the relevant set of unifiers of argument $i$ of a functor $f$
////////////////////////////////////////////////////////////////////////////

static UnifierSet *** compute_relevant_sets
( TreePatterns& patterns, UnifiersMemo& unifiers, UnifyMemo& memo,
  MemPool& pool, VarArray<TreePat *>& states, State number_of_states )
{
  UnifierSet *** relevant_sets;
  Functor f;
  int i;
  int size;

  //
  // Step 1. allocate storage for the relevant sets.
  //
  relevant_sets =
    (UnifierSet***)pool.m_alloc(patterns.functors() * sizeof(UnifierSet **)) -
    patterns.min_functor() * sizeof(UnifierSet **);

  size = (number_of_states + 7) / 8;   // Size of the bit vectors

  for (f = patterns.min_functor(); f <= patterns.max_functor(); f++)
  {
    relevant_sets[f] =
      (UnifierSet**)pool.m_alloc(patterns.arity(f) * sizeof(UnifierSet*));
    for (i = patterns.arity(f) - 1; i >= 0; i--)
      relevant_sets[f][i] = new(pool,size) UnifierSet;
  }

  //
  // Step 2.  Collect the arguments for each functor at each argument.
  //          This is done concurrently for all functors at all positions.
  //
  for (i = patterns.size() - 1; i >= 0; i--)
    collect_arguments(patterns[i], unifiers, relevant_sets);

  //
  // Step 3.  Compute the unifier closure for each relevant set.
  //
  Stack<State> stack(number_of_states);
  for (f = patterns.min_functor(); f <= patterns.max_functor(); f++)
  {
    for (i = patterns.arity(f) - 1; i >= 0; i--)
    {
      stack.clear();
      UnifierSet * set
        = relevant_sets[f][i];
      register int j, k;
      State s;
      for (j = 0, s = 0; j < size; j++)
      {
        if ((*set
            )(j) == 0)
        {
          s += 8;
          continue;
        }
        for ( k = 0; k < 8; k++, s++)
          if ((*set
              )(j) & (1 << k)) stack.push(s);
      }
      for (j = 2; j < stack.size(); j++)
      {
        TreePat * a = states[stack[j]];
        for (k = 1; k < j; k++)
        {
          TreePat * b = states[stack[k]];
          if (nonunifiable(a,b))
            continue;
          TreePat * u = unify( a, b, unifiers, memo, pool,
                               states, number_of_states );
          if (u == Fail)
            continue;
          s = unifiers[u];
          if (! (*set
                )[s])
          {
            set
              ->setUnion(s);
            stack.push(s);
          }
        }
      }
    }
  }

  return relevant_sets;
}

////////////////////////////////////////////////////////////////////////////
//  Compute the subsumption ordering between two patterns a and b
//  Returns:  -1  if a < b
//            0   if a = b
//            1   if a > b
//            2   if a and b are incomparable
////////////////////////////////////////////////////////////////////////////

static int subsumes( TreePat * a, TreePat * b)
{
  if (isWild(a) && isWild(b))
    return 0;
  if (isWild(a))
    return -1;
  if (isWild(b))
    return 1;
  if (a->tag() != b->tag())
    return 2;
  int pos = 0, neg = 0;
  for (int i = a->arity() - 1; i >= 0; i--)
  {
    switch (subsumes(a->nth(i),b->nth(i)))
    {
    case 1:
      if (neg == 0)
        pos++;
      else
        return 2;
      break;
    case -1:
      if (pos == 0)
        neg++;
      else
        return 2;
      break;
    case 2:
      return 2;
    }
  }
  if (pos > 0)
    return 1;
  if (neg > 0)
    return -1;
  return 0;
}

////////////////////////////////////////////////////////////////////////////
//  A list of states
////////////////////////////////////////////////////////////////////////////

struct StateList
{
  State s;
  StateList * tl;
  void * operator new (size_t,MemPool& pool, State a, StateList * t = 0)
  {
    StateList * l = (StateList*)pool[sizeof(StateList)];
    l->s = a;
    l->tl = t;
    return l;
  }
};

////////////////////////////////////////////////////////////////////////////
//  Compute the subsumption ordering for all states.
//  When this routine finishes the array |ordering| will contain
//  for each state t, a list of maximal predecessors t1, t2 ... tn;
//  that is, for each i, t > ti and there is no other s such that
//  t > s > ti.
////////////////////////////////////////////////////////////////////////////

static void compute_subsumption_ordering
( TreePat * states[], int number_of_states,
  StateList * ordering[], MemPool& pool )
{
  int i, j;
  StateList * l;
  ordering[0] = 0;
  for (i = 1; i < number_of_states; i++)
    ordering[i] = 0;
  for (i = 2; i < number_of_states; i++)
  {
    TreePat * a = states[i];
    for (j = 1; j < i; j++)
    {
      TreePat * b = states[j];
      if (nonunifiable(a,b))
        continue;  // skip incomparable terms early
      switch (subsumes(a,b))
      {
      case 1: // a > b; now check if a > b > ap_i for all i
        for (l = ordering[i]; l; l = l->tl)
          switch (subsumes(b,states[l->s]))
          {
          case 1:
            {
              l->s = j;
              goto next;
            }
          case -1:
            goto next;
          }
        ordering[i] = new(pool,j,ordering[i]) StateList;
        break;
      case -1: // b > a; now check if b > a > bp_i for all i
        for (l = ordering[j]; l; l = l->tl)
          switch (subsumes(a,states[l->s]))
          {
          case 1:
            {
              l->s = i;
              goto next;
            }
          case -1:
            goto next;
          }
        ordering[j] = new(pool,i,ordering[j]) StateList;
        break;
      }
next:
      ;
    }
  }
}

////////////////////////////////////////////////////////////////////////////
//  Compute the best approximation of state t with respect to a set of
//  unification closed states S.  Use breath first search since we
//  want to find the best, not the first, approximation.
//  Notice that since the set S is unification closed,
//  the best approximation is uniquely defined.
/////////////////////////////////////////////////////////////////////////////

inline State approx
( State t, UnifierSet& S, StateList * ordering[],
  VarQueue<State>& Q, TreePat * [] )
{  // int head = 0, tail = 0;
  Q.clear();
  Q.insert_tail(t);
  // TreePat * p = states[t];
  while (! Q.is_empty())
  {
    t = Q.remove_head();
    if (S[t])
      return t;
    for (StateList * l = ordering[t]; l; l = l->tl)
      Q.insert_tail(l->s);
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////
//  Given a new term t, compute the best approximation within the set
// of states.  This new state becomes the transition of the tree automata.
////////////////////////////////////////////////////////////////////////////

inline State approx
( TreePat * t, UnifiersMemo& unifiers, StateList * ordering[],
  TreePat * states[], ApproxMemo& memo, MemPool& pool )
{
  TreePatBuf D;
  //
  // First, try looking up the new term to see if is it in the unifiers
  //
  Ix st;
  if ((st = unifiers.lookup(t)))
    return unifiers.value(st);

  //
  // Else try looking it up from the memo function
  //
  if ((st = memo.lookup(t)))
    return memo.value(st);

  //
  // If it is not there, we proceed to compute the approximations
  // one by one until it is found.
  //
  int i;
  D.p.f = t->tag();
  D.p.n = t->arity();
  for (i = t->arity() - 1; i >= 0; i--)
    D.p.subterms[i] = t->nth(i);
  TreePat * max = X;
  StateList zero;
  zero.s = 0;
  zero.tl = 0;
  for (i = t->arity() - 1; i >= 0; i--)
  {
    if (isWild(t->nth(i)))
      continue;
    State s = unifiers[t->nth(i)];
    StateList * l = ordering[s];
    if (l == 0)
      l = &zero;
    for ( ; l; l = l->tl)
    {
      D.p.subterms[i] = states[l->s];
      TreePat * a =
        states[approx(&D.p, unifiers, ordering, states, memo, pool)];
      if (subsumes(a,max) == 1)
        max = a;
    }
    D.p.subterms[i] = t->nth(i);
  }
  State best = unifiers[max];
  memo.insert(new(pool, t->tag(), t->arity(), t->subterms) TreePat, best);
  return best;
}

////////////////////////////////////////////////////////////////////////////
//  The main entry point of the pattern matching compiler
////////////////////////////////////////////////////////////////////////////

void BottomUp::compile( TreePatterns& patterns)
{
  //
  // Compute the size of the memorization tables.   This number is
  // only used as a general guide and does not have to be exact
  // since the tables can handle overflow gracefully.
  //
  int functors   = patterns.functors();
  //int size       = patterns.size();
  int table_size = functors * patterns.max_arity() * 2;
  if (table_size < 256)
    table_size = 256;

  //
  // Here are some of the auxiliary tables used during the compilation
  // process.  The algorithm makes heavy use of memo functions to cut
  // down on the complexity of computing unifiers and match sets.  These
  // tables are implemented as |Maps| of |TreePat *|.  Furthermore, all
  // memory needs are handled by our own fast memory pool instead of
  // C++'s new/delete to ease the demands placed on the system(note: class
  // |MemPool| lets us free all allocated objects in one single unit when
  // this function exits.)
  //
  MemPool             pool(2048);             // set default page size to 2K bytes
  UnifiersMemo        unifiers(table_size);   // unifier to state mapping
  UnifyMemo           unifyMemo(table_size);  // memorization map for unification
  VarArray<TreePat *> states;                 // state to unifier mapping
  ApproxMemo          approxMemo(table_size);

  //
  // Step 1: compute the set of subterms of this pattern set.
  //
  int i;
  unifiers.insert(X,(State)0);  // initially, state 0 is the variable X.
  State number_of_states = 1;   // we'll start at state 1
  for (i = 0; i < patterns.size(); i++)
    patterns.update(i,
                    collect_subterms(patterns[i],unifiers,pool,states,number_of_states));

  //
  // Step 2: compute the closure of the unifiers set.  Initially the
  // set of unifiers is just the set of subterms.  We'll generate new unifiers
  // by pairing all two previous unifiers and stop until we
  // reached the fixpoint.  Notice that since the set of
  // patterns is finite, we'll always terminate.  (However, in pathological
  // cases the number of unifiers is a powerset of the size of the subterms.)
  // Also notice that we take advantage of the fact that linear unification
  // is commutative to half the number of iterations.
  //
  int j;
  for (i = 2; i < number_of_states; i++)
  {
    TreePat * a = states[i];
    for (j = 1; j < i; j++)
    {
      TreePat * b = states[j];
      if (nonunifiable(a,b))
        continue;
      unify( a, b, unifiers, unifyMemo, pool, states, number_of_states );
    }
  }

  //
  // Step 3: Generate the relevant set of unifier closures for
  //         each argument of each functor.
  //
  UnifierSet *** relevant_sets =
    compute_relevant_sets
    ( patterns, unifiers, unifyMemo, pool, states, number_of_states );

  //
  // Step 4: Compute the subsumption ordering for each state.
  //         When this is done the array ordering will contain
  //         a list maximal approximations for each state.
  //
  StateList ** ordering =
    (StateList**)pool[number_of_states * sizeof(StateList*)];

  compute_subsumption_ordering(states, number_of_states, ordering, pool);

  //
  // Step 5.  Compute the approximation mu(f,i) for each functor f and arity i
  //    mus    is a mapping from   offset -> state
  //    offset is its inverse from state -> offset
  //
  State ** mus    = (State **)pool[ patterns.max_arity() * sizeof(State*)];
  State ** offset = (State **)pool[ patterns.max_arity() * sizeof(State*)];
  int bounds [TreeGrammar::Max_arity];
  for (i = patterns.max_arity() - 1; i >= 0; i--)
  {
    mus[i]       = (State*)pool[ number_of_states * sizeof(State) ];
    offset[i]    = (State*)pool[ number_of_states * sizeof(State) ];
    mus[i][0]    = 0;
    offset[i][0] = 0;
  }

  VarQueue<State> queue(number_of_states, number_of_states);
  for (Functor f = patterns.min_functor(); f <= patterns.max_functor(); f++)
  {
    int top = patterns.arity(f) - 1;
    for (i = top; i >= 0; i--)
    {
      State * mu_i      = mus[i];
      State * offset_i  = offset[i];
      int&    bounds_i  = bounds[i];
      UnifierSet& S     = *relevant_sets[f][i];
      mu_i[0] = 0;
      bounds_i = 1;
      for (j = number_of_states - 1; j >= 1; j--)
      {
        State a = approx(j, S, ordering, queue, states);
        State off = offset_i[a];
        if (off < bounds_i && mu_i[off] == a)
          offset_i[a] = off;
        else
        {
          mu_i[bounds[i]] = a;
          offset_i[a] = bounds_i++;
        }
      }
    }
    //
    // Step 6. Compute the transition table based on the approximations.
    // At this point the table |bounds| will contain the compressed
    // arities of the functor; the table |mu| will contain the list
    // of (unique) relevant states and table |offset| will contain the
    // offset mapping(suitable for emission.)
    //
    TreePatBuf D;
    D.p.f = f;
    D.p.n = patterns.arity(f);
    State indices [TreeGrammar::Max_arity];
    for (i = top; i >= 0; i--)
    {
      indices[i] = bounds[i] - 1;
      D.p.subterms[i] = states[mus[i][bounds[i] - 1]];
    }
    do
    {
      //State d = approx(&D.p, unifiers, ordering, states, approxMemo, pool);
      for (i = top; i >= 0; i--)
      {
        if (indices[i] > 0)
        {
          D.p.subterms[i] = states[mus[i][--indices[i]]];
          break;
        }
        else
        {
          D.p.subterms[i] = states[mus[i][indices[i] = bounds[i] - 1]];
        }
      }
    }
    while (i >= 0);
  }
}

////////////////////////////////////////////////////////////////////////////
//
//  Algorithm name
//
////////////////////////////////////////////////////////////////////////////

const char * BottomUp::algorithm() const
{
  return "Bottomup";
}
