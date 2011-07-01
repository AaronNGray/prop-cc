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

#ifndef VanEmde_Boas_priority_queues_h
#define VanEmde_Boas_priority_queues_h

#include <AD/generic/ordering.h>

////////////////////////////////////////////////////////////////////////////
//  VanEmde-Boas priority queue
////////////////////////////////////////////////////////////////////////////

class VBPriQueue
{
  int N;
  int minimum, maximum;
  int count;

  //////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  //////////////////////////////////////////////////////////////////////

public:
  VBPriQueue(int n);
  VBPriQueue(const VBPriQueue&);
  ~VBPriQueue();

  //////////////////////////////////////////////////////////////////////
  // Selectors
  //////////////////////////////////////////////////////////////////////
  int  size()     const
  {
    return count;
  }
  int  capacity() const;
  Bool is_empty() const
  {
    return count == 0;
  }
  Bool is_full()  const
  {
    return false;
  }
  int  min()      const;
  int  max()      const;

  //////////////////////////////////////////////////////////////////////
  // Mutators
  //////////////////////////////////////////////////////////////////////
  Ix   insert(int);
  Bool delete_min();
  Bool delete_max();

  //////////////////////////////////////////////////////////////////////
  // Iterators
  //////////////////////////////////////////////////////////////////////
  Ix  first()  const;
  Ix  last()   const;
  Ix  next(Ix) const;
  Ix  prev(Ix) const;
  int operator () (Ix) const;
};

#endif
