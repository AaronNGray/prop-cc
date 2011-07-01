///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.6),
//  last updated on Nov 2, 1999.
//  The original source file is "b_rules.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "b_rules.pcc"
/////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#define TreeGrammar_Iterators
#include <iostream>
#include <string.h>
#include <AD/automata/treegram.h>
#include <assert.h>
#include <AD/rewrite/b_rules.h>
#include <AD/hash/dchash.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Make hidden types visible for use.
//
//////////////////////////////////////////////////////////////////////////////

typedef TreeGrammar::Functor        Functor;
typedef TreeGrammar::NonTerminal    NonTerminal;
typedef TreeGrammar::Rule           Rule;
typedef TreeGrammar::Cost           Cost;
typedef BURS_RuleSet::LeafReduction LeafReduction;
typedef BURS_RuleSet::Reduction     Reduction;
typedef BURS_RuleSet::ChainRule     ChainRule;

//////////////////////////////////////////////////////////////////////////////
//
//  Hash functions and equality functions for leaf reductions.
//
//////////////////////////////////////////////////////////////////////////////

inline Bool equal( const LeafReduction* a, const LeafReduction* b)
{
  return a->f == b->f && a->cost == b->cost && a->rule == b->rule;
}
inline unsigned hash( const LeafReduction* a)
{
  return a->f + a->cost + a->rule;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Hash functions and equality functions for non-leaf reductions.
//
//////////////////////////////////////////////////////////////////////////////

inline Bool equal( const Reduction* a, const Reduction* b)
{
  if (a->f != b->f || a->cost != b->cost || a->rule != b->rule || a->n != b->n)
    return false;
  for (int i = a->n - 1; i >= 0; i--)
    if (a->rhs[i] != b->rhs[i])
      return false;
  return true;
}

inline unsigned hash( const Reduction* a)
{
  unsigned h = a->f + a->cost + a->rule + a->n;
  for (int i = a->n - 1; i >= 0; i--)
    h += a->rhs[i];
  return h;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Hash functions and equality functions for chain reductions.
//
//////////////////////////////////////////////////////////////////////////////

inline Bool equal( const ChainRule* a, const ChainRule* b)
{
  return a->rhs == b->rhs && a->cost == b->cost && a->rule == b->rule;
}

inline unsigned hash( const ChainRule* a)
{
  return a->rhs + a->cost + a->rule;
}

//////////////////////////////////////////////////////////////////////////////
//
// Internal implementation
//
//////////////////////////////////////////////////////////////////////////////

class BURS_RuleSet_Impl
{
  BURS_RuleSet_Impl(const BURS_RuleSet_Impl&);
  void operator = (const BURS_RuleSet_Impl&);

public:
  DCHashTable <LeafReduction*, int> leaf_map;
  DCHashTable <Reduction*, int> non_leaf_map;
  DCHashTable <ChainRule*, int> chain_rule_map;

  inline  BURS_RuleSet_Impl()
  {}
  inline ~BURS_RuleSet_Impl()
  {}
}
;

//////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
//////////////////////////////////////////////////////////////////////////////

BURS_RuleSet:: BURS_RuleSet( Mem& mem, const TreeGrammar& g) : G(g)
{
  ///////////////////////////////////////////////////////////////////////////
  // Create a new set of hash tables.
  ///////////////////////////////////////////////////////////////////////////

  impl = new BURS_RuleSet_Impl;

  ///////////////////////////////////////////////////////////////////////////
  //  Count the number of rules of each kind.
  ///////////////////////////////////////////////////////////////////////////

  leaf_reduction_count = 0;         // e.g.  A -> c
  reduction_count      = 0;         // e.g.  A -> f (A_1, A_2, ..., A_n)
  chain_rule_count     = G.size();  // e.g.  A -> B
  has_wild_card        = false; // assume we don't have wildcard in grammar

  foreach_production (i, g) count_rules( g[i].term);

  ///////////////////////////////////////////////////////////////////////////
  //  Allocate the tables.
  ///////////////////////////////////////////////////////////////////////////

  leaf_reduction_table  = new LeafReduction [ leaf_reduction_count ];
  reduction_table       = new Reduction *   [ reduction_count ];
  chain_rule_table      = new ChainRule     [ chain_rule_count ];
  int non_term_count = g.max_variable() + 1 + leaf_reduction_count +
                       reduction_count + chain_rule_count;
  non_term_to_tree      = new TreeTerm [non_term_count];

  Bool* var_used = (Bool*) mem.c_alloc(sizeof(Bool) * (g.max_variable()+1));

  for (int i = 0; i < non_term_count; i++)
    non_term_to_tree[i] = wild_term;

  ///////////////////////////////////////////////////////////////////////////
  //  Now normalise the patterns into canonical form.
  ///////////////////////////////////////////////////////////////////////////

  reduction_count      = 0;
  leaf_reduction_count = 0;
  chain_rule_count     = 0;
  non_terminal_count   = g.max_variable() + 1;

  ///////////////////////////////////////////////////////////////////////////
  // Compute the reduction rules
  ///////////////////////////////////////////////////////////////////////////

  {
    foreach_production (i, g)
    {
      NonTerminal v = g[i].var;
      NonTerminal rhs = add_reduction(mem, i, g[i].term, g[i].cost);
      if (v > 0)
      {
        chain_rule_table[ chain_rule_count ].rhs   = rhs;
        chain_rule_table[ chain_rule_count ].cost  = 0;
        chain_rule_table[ chain_rule_count ].rule  = i;
        chain_rule_table[ chain_rule_count++ ].lhs = g[i].var;
        var_used[v] = true;
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////
  //  Compute the chain rules
  ///////////////////////////////////////////////////////////////////////////
  {
    for (NonTerminal v = g.min_variable(); v <= g.max_variable(); v++)
    {
      if (var_used[v])
      {
        chain_rule_table[ chain_rule_count ].lhs  = 0;
        chain_rule_table[ chain_rule_count ].rhs  = v;
        chain_rule_table[ chain_rule_count ].cost = 0;
        chain_rule_table[ chain_rule_count ].rule = -1;
        chain_rule_count++;
      }
    }
  }

  assert(non_terminal_count <= non_term_count);

  ///////////////////////////////////////////////////////////////////////////
  //  Finally compute the list of non-unit reductions partitioned by
  //  the functors.
  ///////////////////////////////////////////////////////////////////////////
  reductions = new ReductionList * [ g.max_functor() + 1 ];

  {
    foreach_functor (f,g) reductions[f] = 0;
  }
  {
    for (int i = 0; i < reduction_count; i++)
    {
      Functor f = reduction_table[i]->f;
      reductions[f] =
        new (mem, reduction_table[i], reductions[f]) ReductionList;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // Clean up
  ///////////////////////////////////////////////////////////////////////////
  delete impl;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Destructor
//
//////////////////////////////////////////////////////////////////////////////

BURS_RuleSet::~BURS_RuleSet()
{
  delete [] reduction_table;
  delete [] chain_rule_table;
  delete [] leaf_reduction_table;
  delete [] reductions;
}

//////////////////////////////////////////////////////////////////////////////
//
// Method to count the number of canonical rules.
//
//////////////////////////////////////////////////////////////////////////////

void BURS_RuleSet::count_rules(TreeTerm t)
{
#line 214 "b_rules.pcc"
#line 222 "b_rules.pcc"
  {
    if (t)
    {
      switch (t->tag__)
      {
      case a_TreeTerm::tag_tree_term:
        {
          switch (_tree_term(t)->_2)
          {
          case 0:
            {
#line 217 "b_rules.pcc"
              leaf_reduction_count++;

#line 218 "b_rules.pcc"

            }
            break;
          default:
            {
#line 218 "b_rules.pcc"

              for (int i = _tree_term(t)->_2 - 1; i >= 0; i--)
                count_rules(_tree_term(t)->_3[i]);
              reduction_count++;

#line 221 "b_rules.pcc"

            }
          }
        }
        break;
      case a_TreeTerm::tag_var_term:
        {
#line 216 "b_rules.pcc"
          chain_rule_count++;

#line 217 "b_rules.pcc"

        }
        break;
      default:
        {
#line 221 "b_rules.pcc"
          assert("Error in BURS_RuleSet::count_rules");

#line 222 "b_rules.pcc"

        }
        break;
      }
    }
    else
    {
#line 215 "b_rules.pcc"
      has_wild_card = true;
      chain_rule_count++;

#line 216 "b_rules.pcc"

    }
  }
#line 222 "b_rules.pcc"
#line 222 "b_rules.pcc"

}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to add an reduction rule into the table
//
//////////////////////////////////////////////////////////////////////////////
NonTerminal BURS_RuleSet::add_reduction
(Mem& mem, Rule r, TreeTerm t, Cost cost)
{
#line 232 "b_rules.pcc"
#line 276 "b_rules.pcc"
  {
    if (t)
    {
      switch (t->tag__)
      {
      case a_TreeTerm::tag_tree_term:
        {
          switch (_tree_term(t)->_2)
          {
          case 0:
            {
#line 233 "b_rules.pcc"

              leaf_reduction_table[ leaf_reduction_count ].f    = _tree_term(t)->_1;
              leaf_reduction_table[ leaf_reduction_count ].cost = cost;
              leaf_reduction_table[ leaf_reduction_count ].rule = r;
              Ix i = impl->leaf_map.lookup(leaf_reduction_table + leaf_reduction_count);
              if (i)
              {
                return impl->leaf_map.key(i)->lhs;
              }
              else
              {
                impl->leaf_map.insert(leaf_reduction_table + leaf_reduction_count,0);
                NonTerminal T = non_terminal_count++;
                non_term_to_tree[T] = t;
                // std::cerr << "Non-term " << T << " = "; G.print(std::cerr,t) << '\n';
                return leaf_reduction_table[ leaf_reduction_count++ ].lhs = T;
              }

#line 247 "b_rules.pcc"

            }
            break;
          default:
            {
#line 247 "b_rules.pcc"

              {  Reduction * red = new (mem, _tree_term(t)->_2) Reduction;
                red->f    = _tree_term(t)->_1;
                red->n    = _tree_term(t)->_2;
                red->cost = cost;
                red->rule = r;
                {
                  for (int i = 0; i < _tree_term(t)->_2; i++)
                  {

#line 254 "b_rules.pcc"
#line 257 "b_rules.pcc"
                    {
                      TreeTerm _V1 = _tree_term(t)->_3[i];
                      if (_V1)
                      {
#line 256 "b_rules.pcc"
                        red->rhs[i] = add_reduction(mem, -1, _tree_term(t)->_3[i], 0);

#line 257 "b_rules.pcc"

                      }
                      else
                      {
#line 255 "b_rules.pcc"
                        red->rhs[i] = 0;

#line 256 "b_rules.pcc"

                      }
                    }
#line 257 "b_rules.pcc"
#line 257 "b_rules.pcc"

                  }
                }
                Ix i = impl->non_leaf_map.lookup(red);
                if (i)
                {
                  return impl->non_leaf_map.key(i)->lhs;
                }
                else
                {
                  reduction_table[ reduction_count++ ] = red;
                  impl->non_leaf_map.insert(red,0);
                  NonTerminal T = non_terminal_count++;
                  non_term_to_tree[T] = t;
                  // std::cerr << "Non-term " << T << " = "; G.print(std::cerr,t) << '\n';
                  return red->lhs = T;
                }
              }

#line 272 "b_rules.pcc"

            }
          }
        }
        break;
      case a_TreeTerm::tag_var_term:
        {
#line 273 "b_rules.pcc"
          return _var_term(t)->var_term;

#line 274 "b_rules.pcc"

        }
        break;
      default:
        {
#line 274 "b_rules.pcc"
          assert("Error in BURS_RuleSet::add_reduction\n");
          return 0;

#line 276 "b_rules.pcc"

        }
        break;
      }
    }
    else
    {
#line 272 "b_rules.pcc"
      return 0;

#line 273 "b_rules.pcc"

    }
  }
#line 276 "b_rules.pcc"
#line 276 "b_rules.pcc"

}


//////////////////////////////////////////////////////////////////////////////
//
//  Printing methods
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Print a leaf reduction rule
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& BURS_RuleSet::print (std::ostream& f, const BURS_RuleSet::LeafReduction& r) const
{
  G.print_variable(f, r.lhs);
  f << "\t -> ";
  G.print_functor (f, r.f);
  if (r.cost > 0)
    f << "\t(cost " << r.cost << ')';
  if (r.rule >= 0)
    f << "\t[rule " << r.rule << ']';
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//
// Print a reduction rule
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& BURS_RuleSet::print (std::ostream& f, const BURS_RuleSet::Reduction& r) const
{
  G.print_variable(f, r.lhs);
  f << "\t -> ";
  const char * f_name = G.functor_name(r.f);
  if (f_name[0] == '#')
  {
    char begin_s = f_name[1];
    char end_s   = f_name[strlen(f_name)-1];
    f << '#' << begin_s;
    for (int i = 0; i < r.n; i++)
    {
      print (f, r.rhs[i]);
      if (i < r.n - 1)
        f << " ... ";
    }
    f << end_s;
  }
  else
  {
    G.print_functor (f, r.f);
    f << '(';
    for (int i = 0; i < r.n; i++)
    {
      print (f, r.rhs[i]);
      if (i < r.n - 1)
        f << ',';
    }
    f << ')';
  }
  if (r.cost > 0)
    f << "\t(cost " << r.cost << ')';
  if (r.rule >= 0)
    f << "\t[rule " << r.rule << ']';
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Print a chain rule
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& BURS_RuleSet::print (std::ostream& f, const BURS_RuleSet::ChainRule& r) const
{
  G.print_variable(f,r.lhs);
  f << "\t -> ";
  G.print_variable(f,r.rhs);
  if (r.cost > 0)
    f << "\t(cost " << r.cost << ')';
  if (r.rule >= 0)
    f << "\t[rule " << r.rule << ']';
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Print a rule set
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& f, const BURS_RuleSet& r)
{
  int i;
  if (r.number_of_leaf_reductions() > 0)
    f << "Leaf reductions:\n";
  for (i = 0; i < r.number_of_leaf_reductions(); i++)
    r.print(f,r.leaf(i)) << '\n';
  if (r.number_of_reductions() > 0)
    f << "Non-leaf reductions:\n";
  for (i = 0; i < r.number_of_reductions(); i++)
    r.print(f,r.reduction(i)) << '\n';
  if (r.number_of_chain_rules() > 0)
    f << "Chain rules:\n";
  for (i = 0; i < r.number_of_chain_rules(); i++)
    r.print(f,r.chain_rule(i)) << '\n';
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Print a non-terminal
//
//////////////////////////////////////////////////////////////////////////////
std::ostream& BURS_RuleSet::print (std::ostream& f, NonTerminal n) const
{
  TreeTerm t = non_term_to_tree[n];
  if (t != wild_term || n == 0)
  {
    G.print(f,t);
  }
  else
  {
    G.print_variable(f,n);
  }
  return f;
}
#line 379 "b_rules.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 15
Number of ifs generated      = 3
Number of switches generated = 4
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
