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

#ifndef stackable_collection_h
#define stackable_collection_h

////////////////////////////////////////////////////////////////////////////
//  Stackable collection
////////////////////////////////////////////////////////////////////////////
#include <AD/collect/seqcol.h>

template <class T, class S>
class StackableCollection : SequenceableCollection<T>
{
  S stack;  // implementation

public:
  ////////////////////////////////////////////////////////////////
  // Inherit types
  ////////////////////////////////////////////////////////////////

  typedef SequenceableCollection<T> Super;
  typedef Super::Element            Element;

  ////////////////////////////////////////////////////////////////
  // Constructor and destructor
  ////////////////////////////////////////////////////////////////

  StackableCollection( int initial_size) : stack(initial_size)
  {}
  StackableCollection( const Collection<T>& C)
      : stack(initial_size)
  {
    *this = C;
  }
  StackableCollection( const StackableCollection& C)
      : stack(initial_size)
  {
    *this = C;
  }
  ~StackableCollection()
  {}

  ////////////////////////////////////////////////////////////////
  // Assignment
  ////////////////////////////////////////////////////////////////
  // void operator = (const Collection<T>&); // inherited

  ////////////////////////////////////////////////////////////////
  //  Selectors
  ////////////////////////////////////////////////////////////////

  int size() const
  {
    return stack.size();
  }

  int capacity() const
  {
    return stack.capacity();
  }
  // virtual Bool is_empty()          const; // inherited
  // virtual Bool is_full()           const; // inherited
  // virtual Bool contains(const T&) const; // inherited

  virtual T& top() const
  {
    return stack.top();
  }

  ////////////////////////////////////////////////////////////////
  //  Mutators
  ////////////////////////////////////////////////////////////////

  virtual void clear()
  {
    return stack.clear();
  }

  virtual Ix insert( const T& e)
  {
    stack.push(e);
    return &top();
  }

  virtual Bool remove( const T& e)
  {
    should_not_implement("remove");
  }

  virtual void push( const T& e)
  {
    stack.push(e);
  }

  virtual T&   pop()
  {
    return stack.pop(e);
  }

  ////////////////////////////////////////////////////////////////
  //  Iteration
  ////////////////////////////////////////////////////////////////

  Ix first() const
  {
    return size() == 0 ? 0 : 0;
  }

  Ix next(Ix i) const
  {
    return i >= (Ix)((T*)stack + size()) ? 0 : (((T*)i)+1);
  }

  T& operator () (Ix i) const
  {
    return *(T*)i;
  }

  ////////////////////////////////////////////////////////////////
  //  Other
  ////////////////////////////////////////////////////////////////

  const char * myName() const
  {
    return "StackableCollection";
  }
};

#endif
