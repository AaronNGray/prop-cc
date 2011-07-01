//////////////////////////////////////////////////////////////////////////////
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

#ifndef alpha_memory_h
#define alpha_memory_h

#include <AD/rete/fact.h>   // database fact
#include <AD/memory/mem.h>  // memory manager

//////////////////////////////////////////////////////////////////////////////
//
//  Alpha memory is used to cache facts that pass intra-object tests.
//
//////////////////////////////////////////////////////////////////////////////

class AlphaMem
{
  AlphaMem(const AlphaMem&);         // no copy constructor
  void operator = (const AlphaMem&); // no assignment

protected:
  int     count;     // number of facts in the list.
  int     capacity;  // number of facts that we can hold.
  Fact ** facts;     // list of facts.

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  AlphaMem() : count(0), capacity(0), facts(0)
  {}
  ~AlphaMem()
  {}

  ///////////////////////////////////////////////////////////////////////////
  //  Conversion.
  ///////////////////////////////////////////////////////////////////////////
  // inline operator Fact ** () const { return facts; }
  inline Fact ** get_facts ()
  {
    return facts;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Selectors
  ///////////////////////////////////////////////////////////////////////////
  inline int    size()               const
  {
    return count;
  }
  inline Fact * operator [] (int i)  const
  {
    return facts[i];
  }
  inline int    find(const Fact * f) const
  {
    for (int i = capacity - 1; i >= 0; i--)
      if (f == facts[i])
        return i;
    return -1;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Method to insert a new fact into the alpha memory.
  ///////////////////////////////////////////////////////////////////////////
  inline void add_fact(Mem& mem, Fact * f)
  {
    if (count < capacity)
    {
      facts[count++] = f;
    }
    else
    {
      int     new_capacity = 4 + capacity * 3 / 2;
      Fact ** new_facts =
        (Fact**)mem.m_alloc(sizeof(Fact*) * new_capacity);
      for (int i = capacity - 1; i >= 0; i--)
        new_facts[i] = facts[i];
      mem.free(facts);
      new_facts[count++] = f;
      capacity           = new_capacity;
      facts              = new_facts;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Method to remove an old fact from the alpha memory.
  ///////////////////////////////////////////////////////////////////////////
  inline void remove_fact(int i)
  {
    facts[--count] = facts[i];
  }
};

#endif
