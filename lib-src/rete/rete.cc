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

#include <iostream>
#include <AD/rete/rete.h>         // RETE inference engine
#include <AD/hash/lhash.h>        // coalesced chaining hash table
#include <AD/contain/varqueue.h>  // generic queue
#include <AD/memory/arena.h>      // arenas


/////////////////////////////////////////////////////////////////////////
// Make hidden types visible
/////////////////////////////////////////////////////////////////////////

typedef Rete::Priority Priority;  // priority of rule
typedef Rete::RuleId   RuleId;    // rule number
typedef Rete::Node     Node;      // a node in the RETE network
typedef Rete::Age      Age;       // age of fact

/////////////////////////////////////////////////////////////////////////
// Equality and hashing for facts.
/////////////////////////////////////////////////////////////////////////

Bool equal(Fact * a, Fact * b)
{
  return a == b;
}
unsigned int hash(Fact * f)
{
  return (unsigned int)f;
}

/////////////////////////////////////////////////////////////////////////
// A token
/////////////////////////////////////////////////////////////////////////

class ReteToken
{

  RuleId rule_id;   // rule id
  int    arity;     // length of the token
  Age    _age;      // age
  Fact * token[1];  // the token

public:

  //////////////////////////////////////////////////////////////////////
  //  Method to allocate a new token
  //////////////////////////////////////////////////////////////////////
  inline void * operator new
  (size_t, Arena& arena, int n, RuleId id, Fact * f[], Age a)
  {
    ReteToken * t = (ReteToken*) arena();
    t->arity = n;
    t->rule_id = id;
    t->_age = a;
    for (int i = n - 1; i >= 0; i--)
      t->token[i] = f[i];
    return t;
  }

  //////////////////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////////////////
  // inline         operator Fact ** ()     { return token; }
  inline Fact** get_token()
  {
    return token;
  }

  inline int size() const
  {
    return arity;
  }

  inline Fact* operator [] (int i) const
  {
    return token[i];
  }

  inline RuleId rule() const
  {
    return rule_id;
  }

  inline Age age() const
  {
    return _age;
  }

  //////////////////////////////////////////////////////////////////////
  //  Equality and hashing
  //////////////////////////////////////////////////////////////////////

  inline friend Bool equal( ReteToken* a, ReteToken* b)
  {
    if (a->rule_id != b->rule_id || a->arity != b->arity)
      return false;
    for (int i = a->arity - 1; i >= 0; i--)
      if (a->token[i] != b->token[i])
        return false;
    return true;
  }

  inline friend unsigned hash( ReteToken* a)
  {
    unsigned int h = a->rule_id + a->arity;
    for (int i = a->arity - 1; i >= 0; i--)
      h += (unsigned int)a->token[i];
    return h;
  }
};

/////////////////////////////////////////////////////////////////////////
//  Definition of the conflict set
/////////////////////////////////////////////////////////////////////////

class ReteConflictSet
{

  ReteConflictSet(const ReteConflictSet&);  // no copy constructor
  void operator = (const ReteConflictSet&); // no assignment

protected:
  friend class Rete;

  //////////////////////////////////////////////////////////////////////
  // Internal members
  //////////////////////////////////////////////////////////////////////
  Age                         timestamp; // current time
  VarQueue   <ReteToken *>    tokens;    // queue of tokens
  LHashTable <Fact *, Fact *> facts;     // database of facts
  Arena                       arena;     // arena (for tokens only)

public:

  //////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  //////////////////////////////////////////////////////////////////////
  ReteConflictSet(int max_token_arity, int n = 64, int m = 1025);
  ~ReteConflictSet()
  {}

  //////////////////////////////////////////////////////////////////////
  // Timestamp and priority management.
  //////////////////////////////////////////////////////////////////////

  inline void reset_time()
  {
    timestamp = 0;
  }

  inline Age now () const
  {
    return timestamp;
  }

  inline Age new_time()
  {
    return timestamp++;
  }
};

/////////////////////////////////////////////////////////////////////////
//  Constructor for the conflict set.
/////////////////////////////////////////////////////////////////////////

ReteConflictSet::ReteConflictSet(int max_token_arity, int n, int m)
    : timestamp(0),
    tokens(n),
    facts(m),
    arena(sizeof(ReteToken) + (max_token_arity - 1) * sizeof(Fact *))
{}

/////////////////////////////////////////////////////////////////////////
//  An auxiliary function calculate the maximum arity of all tokens.
/////////////////////////////////////////////////////////////////////////

static int max_arity_of(int N, const ReteNet::Node network[])
{
  int max_arity = 0;
  for (int i = N - 1; i >= 0; i--)
    if (network[i].arity > max_arity)
      max_arity = network[i].arity;
  return max_arity;
}

/////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////

Rete::Rete( int N, const Node my_network[], int M, const RelationTable T[])
    : Super( N, my_network),
    conflict_set (*new ReteConflictSet( max_arity_of( N, my_network)))
{
  int max_tag = 0;
  for (int i = 0; i < M; i++)
  {
    if (*T[i].relation_tag > max_tag)
      max_tag = *T[i].relation_tag;
    if (*T[i].relation_tag <= 0)
      std::cerr << "Bug: relation " << T[i].relation_name
      << " has not been properly initialised in inference class "
      << name_of() << '\n';
  }
  inject_table_size = max_tag + 1;
  inject_table = (int*)mem.c_alloc(sizeof(int) * inject_table_size );
  for (int j = 0; j < M; j++)
    inject_table[ *T[j].relation_tag ] = T[j].inject;
}

/////////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////////

Rete::~Rete()
{
  delete (&conflict_set);
}

/////////////////////////////////////////////////////////////////////////
// Return the name of the inference class
/////////////////////////////////////////////////////////////////////////

const char * Rete::name_of() const
{
  return "Rete";
}

////////////////////////////////////////////////////////////////////////
// Conflict resolution methods
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Method to add a new token into the conflict set
////////////////////////////////////////////////////////////////////////

void Rete::activate( RuleId rule, int arity, Fact * token[])
{
  ReteToken * T = new(conflict_set.arena, arity, rule, token,
                      conflict_set.new_time()) ReteToken;
  conflict_set.tokens.insert_tail(T);
}

////////////////////////////////////////////////////////////////////////
// Method to remove a token from the conflict set
////////////////////////////////////////////////////////////////////////

void Rete::deactivate( RuleId /*rule*/, int /*arity*/, Fact * /*token*/[])
{}

////////////////////////////////////////////////////////////////////////
//  Method: fire()
//    Select the highest priority rule to execute( which may as a result
//  alter the discriminant network.)
////////////////////////////////////////////////////////////////////////

void Rete::fire()
{
  if ( !conflict_set.tokens.is_empty())
  {
    ReteToken * T =
      conflict_set.tokens.remove_head(); // look for any token
    // action(T->rule(), *T);               // execute the action
    action(T->rule(), T->get_token());    // execute the action
    conflict_set.arena.free(T);           // frees the token.
  }
}

////////////////////////////////////////////////////////////////////////
//  Method to perform infernence until stabilised.
////////////////////////////////////////////////////////////////////////

void Rete::infer()
{
  while (! is_stable())
    fire();
}

////////////////////////////////////////////////////////////////////////
//  Method to check whether the conflict set is empty.
////////////////////////////////////////////////////////////////////////

Bool Rete::is_stable() const
{
  return conflict_set.tokens.is_empty();
}

////////////////////////////////////////////////////////////////////////
//  Auxiliary methods to assert and retract facts from the conflict set
////////////////////////////////////////////////////////////////////////

void Rete::clear()
{
  conflict_set.tokens.clear();
  conflict_set.reset_time();
}

////////////////////////////////////////////////////////////////////////
//  Method to assert a fact.
//  Steps:
//    (1) Lookup the unique relation tag of the fact.
//        Each relation type is given an unique tag by the runtime
//        system.
//    (2) Lookup the entry number using the dispatch table.
//    (3) Then run the alpha test.
////////////////////////////////////////////////////////////////////////

ReteNet& Rete::assert_fact( Fact * fact)
{
  conflict_set.facts.insert(fact,fact);
  RelTag tag = fact->get_tag();
  if (tag < inject_table_size)
  {
    int inj = inject_table[tag];
    if (inj > 0)
      alpha_test(inj, 1, fact);
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////
//  Method to retract a fact.
////////////////////////////////////////////////////////////////////////

ReteNet& Rete::retract_fact( Fact * fact)
{
  if (conflict_set.facts.remove(fact))
  {
    RelTag tag = fact->get_tag();
    if (tag < inject_table_size)
    {
      int inj = inject_table[tag];
      if (inj > 0)
        alpha_test(inj, 0, fact);
    }
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////
//  Selectors
////////////////////////////////////////////////////////////////////////

int Rete::size() const
{
  return conflict_set.facts.size();
}

////////////////////////////////////////////////////////////////////////
//  Iterator methods
////////////////////////////////////////////////////////////////////////

Ix Rete::first() const
{
  return conflict_set.facts.first();
}

Ix Rete::next( Ix i) const
{
  return conflict_set.facts.next(i);
}
Fact * Rete::operator () (Ix i) const
{
  return conflict_set.facts.value(i);
}

////////////////////////////////////////////////////////////////////////
//  Add all the facts of a database into another
////////////////////////////////////////////////////////////////////////

void Rete::add( const Rete& rete)
{
  for (Ix i = rete.first(); i; i = rete.next(i))
    assert_fact(rete(i));
}
