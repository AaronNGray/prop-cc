#include <AD/symbolic/bdd.h>
#include <AD/hash/lhash.h>

///////////////////////////////////////////////////////////////////////////////
//  Import some type definitions.
///////////////////////////////////////////////////////////////////////////////

typedef BDDSet::Var     Var;
typedef BDDSet::BDDNode BDDNode;
typedef BDDSet::BDD     BDD;
typedef BDDSet::Op      Op;

///////////////////////////////////////////////////////////////////////////////
//  Hashing and equality functions on a BDDNode
///////////////////////////////////////////////////////////////////////////////

inline unsigned int hash(const BDDNode& n)
{
  return n.var + n.branches[0] * 4 + n.branches[1] * 32;
}

inline Bool equal (const BDDNode& a, const BDDNode& b)
{
  return a.var == b.var && a.branches[0] == b.branches[0]
         && a.branches[1] == b.branches[1];
}

///////////////////////////////////////////////////////////////////////////////
//  The BDD table.
///////////////////////////////////////////////////////////////////////////////

struct BDDTable : public LHashTable< BDDNode, BDD>
  {}
;

///////////////////////////////////////////////////////////////////////////////
//  The memo table.
///////////////////////////////////////////////////////////////////////////////

struct BDDMemo : public LHashTable< BDDNode, BDD>
  {}
;

///////////////////////////////////////////////////////////////////////////////
//  Constructors
///////////////////////////////////////////////////////////////////////////////

BDDSet:: BDDSet(size_t default_nodes)
    : bdd_roots(0),
    bdd_count(0),
    bdd_capacity(0),
    table(new BDDTable), memo(new BDDMemo)
{
  bdds          = new BDDNode [default_nodes];
  bdd_next      = bdds + 2;
  int n         = default_nodes - 2;
  bdd_highwater = bdd_next + default_nodes;
  bdd_limit     = bdds + n / 2;
}

///////////////////////////////////////////////////////////////////////////////
//  Destructor
///////////////////////////////////////////////////////////////////////////////

BDDSet::~BDDSet()
{
  delete [] bdds;
  delete [] bdd_roots;
  delete table;
  delete memo;
}

///////////////////////////////////////////////////////////////////////////////
//  Initialization
///////////////////////////////////////////////////////////////////////////////

void BDDSet::clear()
{
  bdd_count = 0;
  bdd_next  = bdds + 2;
  memo->clear();
  table->clear();
}

///////////////////////////////////////////////////////////////////////////////
//  Hash cons.
///////////////////////////////////////////////////////////////////////////////

inline BDD BDDSet::hash_cons( Var v, BDD f, BDD g)
{
  if (bdd_next == bdd_limit)
    do_collect();  // garbage collect if full
  BDDNode n(v,f,g);
  Ix i = table->lookup(n);
  if (i)
    return table->value(i);
  BDDNode * next = bdd_next++;
  next->var = v;
  next->branches[0] = f;
  next->branches[1] = g;
  BDD h = next - bdds;
  table->insert(n,h);
  return h;
}

///////////////////////////////////////////////////////////////////////////////
//  Application
///////////////////////////////////////////////////////////////////////////////

BDD BDDSet::do_apply( Op op, BDD f, BDD g)
{
  switch (op)
  {
  case Or:
    if (f == 1 || g == 1)
      return 1;
    if (f == 0)
      return g;   // 0 + g = g
    if (g == 0)
      return f;   // f + 0 = f
    break;
  case And:
    if (f == 0 || g == 0)
      return 0;
    if (f == 1)
      return g;   // 1 * g = g
    if (g == 1)
      return f;   // f * 1 = f
    break;
  case Not:
    return do_negate(f);
  case Nor:
    if (f == 1 || g == 1)
      return 0;
    if (f == 0)
      return do_negate(g);
    if (g == 0)
      return do_negate(g);
    break;
  case Nand:
    if (f == 0 || g == 0)
      return 1;
    if (f == 1)
      return do_negate(g);
    if (g == 1)
      return do_negate(g);
    break;
  case Xor:
    if (f == 0)
      return g;   // 0 xor g = g
    if (g == 0)
      return f;   // f xor 0 = f
    if (f == 1)
      return do_negate(g);
    if (g == 1)
      return do_negate(f);
    break;
  case Xnor:
    if (f == 0)
      return g;    // 1 xnor g = g
    if (g == 0)
      return f;    // f xnor 1 = f
    if (f == 1)
      return do_negate(g);
    if (g == 1)
      return do_negate(f);
    break;
  default:
    break;
  }
  // Check if result is already in place.
  BDDNode n(op, f, g);
  Ix i = memo->lookup(n);
  if (i)
    return memo->value(i);

  register Var fv = var_of(f);
  register Var gv = var_of(g);
  BDD r;
  if (fv == gv)
    r = hash_cons(fv, do_apply(op,bdds[f].branches[0],bdds[g].branches[0]),
                  do_apply(op,bdds[f].branches[1],bdds[g].branches[1]));
  else if (fv < gv)
    r = hash_cons(fv, do_apply(op,bdds[f].branches[0],g),
                  do_apply(op,bdds[f].branches[1],g));
  else
    r = hash_cons(gv, do_apply(op,f,bdds[g].branches[0]),
                  do_apply(op,f,bdds[g].branches[1]));

  memo->insert(n, r);  // update the memo map.
  return r;
}

///////////////////////////////////////////////////////////////////////////////
//  Restriction
///////////////////////////////////////////////////////////////////////////////

BDD BDDSet::do_restrict( BDD f, Var var, BDD value)
{
  if (f == 0)
    return 0;
  if (f == 1)
    return 1;
  Var fv = var_of(f);
  if (fv == var)
    return bdds[f].branches[value];
  BDDNode n(Restrict, f, var);
  Ix i = memo->lookup(n);
  if (i)
    return memo->value(i);
  BDD r = hash_cons(fv,do_restrict(bdds[f].branches[0], var, value),
                    do_restrict(bdds[f].branches[1], var, value));
  memo->insert(n,r);
  return r;
}

///////////////////////////////////////////////////////////////////////////////
//  Negate
///////////////////////////////////////////////////////////////////////////////

BDD BDDSet::do_negate( BDD f)
{
  if (f == 0)
    return 1;
  if (f == 1)
    return 0;
  BDDNode n(Not, f, 0);
  Ix i = memo->lookup(n);
  if (i)
    return memo->value(i);
  BDD r = hash_cons (var_of(f),
                     do_negate(bdds[f].branches[0]),
                     do_negate(bdds[f].branches[1]));
  memo->insert(n,r);
  return r;
}

///////////////////////////////////////////////////////////////////////////////
//  Apply
///////////////////////////////////////////////////////////////////////////////

BDD BDDSet::apply( Op op, BDD f, BDD g)
{
  memo->clear();
  bdd_last = bdd_next;
  return do_apply(op, f, g);
}

///////////////////////////////////////////////////////////////////////////////
//  Restrict
///////////////////////////////////////////////////////////////////////////////

BDD BDDSet::restrict( BDD f, Var var, BDD value)
{
  memo->clear();
  bdd_last = bdd_next;
  return do_restrict(f, var, value);
}

///////////////////////////////////////////////////////////////////////////////
//  Negate
///////////////////////////////////////////////////////////////////////////////

BDD BDDSet::negate( BDD f)
{
  memo->clear();
  bdd_last = bdd_next;
  return do_negate(f);
}

///////////////////////////////////////////////////////////////////////////////
//  Top level method to involve garbage collection.
///////////////////////////////////////////////////////////////////////////////

void BDDSet::collect()
{
  bdd_last = bdd_next;
  collect();
}

///////////////////////////////////////////////////////////////////////////////
//  Garbage collection.
///////////////////////////////////////////////////////////////////////////////

void BDDSet::do_collect()
{
  // Mark all user roots
  for (int i = 0; i < size(); i++)
    ;

  // Everything from [bdd_last ... bdd_limit) must be non-garbage.
  // Mark them.
  {  for (register BDDNode * p = bdd_last, * q = bdd_limit; p < q; p++)
      ;
  }

  //
  // Copy phase, use the to space as a queue.
  //

  //
  // Exchange from/to space.
  //
}
