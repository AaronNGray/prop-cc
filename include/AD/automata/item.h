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

#ifndef parse_item_h
#define parse_item_h

#include <new>
#include <AD/generic/ordering.h>
#include <AD/automata/grammar.h>
#include <AD/automata/operprec.h>
#include <AD/memory/mem.h>


//////////////////////////////////////////////////////////////////////////////
//  Class |LRItem| represents a item (or configuration) during
//  the shift/reduce parser generation.
//////////////////////////////////////////////////////////////////////////////

struct LRItem
{
public:

  ///////////////////////////////////////////////////////////////////////////
  //  Imported types
  ///////////////////////////////////////////////////////////////////////////
  typedef Grammar::Symbol      Symbol;
  typedef Grammar::Terminal    Terminal;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Production  Production;
  typedef OpPrecedence::Associativity Associativity;
  typedef OpPrecedence::Precedence    Precedence;

  Production    P;
  int           pos;
  Associativity associativity;
  Precedence    precedence;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //  Allocation
  ///////////////////////////////////////////////////////////////////////////
  inline void * operator new
  (size_t size, Mem& pool, const Grammar& G, int production_num,
   Production p, int n, const OpPrecedence& prec)
  {
    LRItem * item = (LRItem*) pool.m_alloc(size);
    item->P = p;
    item->pos = n;
    // Scan backwards to find the operator symbol
    // (used in operator precedence parsing)
    for (int pos = n; pos > 0; pos--)
    {
      if (G.isTerminal(p[pos]))
      {
        item->associativity = prec.associativity(p[pos]);
        item->precedence    = prec.precedence(p[pos]);
        return item;
      }
    }
    item->associativity = prec.p_associativity(production_num);
    item->precedence    = prec.p_precedence(production_num);
    return item;
  }
  ///////////////////////////////////////////////////////////////////////////
  //  Length (with or without terminals)
  ///////////////////////////////////////////////////////////////////////////
  inline int len () const
  {
    return pos;
  } // prefix length
  int ncount( const Grammar&) const; // non-terminal count

  ///////////////////////////////////////////////////////////////////////////
  //  Testing for predicting and reducing items
  ///////////////////////////////////////////////////////////////////////////
  inline Bool isPredicting() const
  {
    return pos == 0;
  }
  inline Bool isReducing()   const
  {
    return P[pos+1] <= Grammar::END_PRODUCTION;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Comparison and hashing
  ///////////////////////////////////////////////////////////////////////////
  inline friend Bool equal( const LRItem * a, const LRItem * b)
  {
    return a->P == b->P && a->pos == b->pos;
  }

  inline friend unsigned int hash( const LRItem * a)
  {
    return (unsigned int)a->P + a->pos;
  }
};

#endif
