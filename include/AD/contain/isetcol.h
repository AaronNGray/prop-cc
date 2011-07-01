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

#ifndef integer_set_collection_h
#define integer_set_collection_h

#include <AD/contain/set.h>

template <class I>
class IntSetCollection : public SetCollection<int>
{
  I intset;

  //////////////////////////////////////////////////
  //  Constructors and destructor
  //////////////////////////////////////////////////

public:
  IntSetCollection(int initial_size) : intset(initial_size)
  {}
  ~IntSetCollection()
  {}

  //////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////
  inline int size() const
  {
    return intset.size();
  }

  inline int capacity() const
  {
    return intset.capacity();
  }

  // Bool is_full()            const; // inherited
  // Bool is_empty()           const; // inherited

  inline Bool contains( const int& i) const
  {
    return intset.contains(i);
  }

  //////////////////////////////////////////////////
  //  Mutator
  //////////////////////////////////////////////////

  inline void clear()
  {
    intset.clear();
  }

  inline Ix insert(const int& i)
  {
    intset.insert(i);
  }

  inline Bool remove(const int& i)
  {
    intset.remove(i);
  }

  //////////////////////////////////////////////////
  //  Iteration
  //////////////////////////////////////////////////

  inline Ix first() const
    { }
  inline Ix next(Ix i) const
    { }

  inline const int& operator () (Ix i) const
  {
    return (int)i;
  }

  inline int& operator () (Ix i)
  {
    return (int)i;
  }
};

#endif
