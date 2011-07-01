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

#ifndef queue_collection_h
#define queue_collection_h

//////////////////////////////////////////////////////////////////////////////
//  Queue Collection derives a collection class using an existing
//  queue concrete type.
//  Suitable concrete types include:
//     Queue<T>     --- array based queue with capacity fixed at creation
//     FixQueue<T>  --- array based queue with capacity fixed at compile time
//     VarQueue<T>  --- array based expandable queue
//     ListQueue<T> --- linked list based queue
//     IndexableQueue<T> --- queue based on an indexable structure
//////////////////////////////////////////////////////////////////////////////

#include <AD/contain/seqcol.h>

template <class T, class Q>
class QueueCollection : public SequenceableCollection<T>
{
  Q queue; // implementation

  //////////////////////////////////////////////////////////////
  //  Inherit types
  //////////////////////////////////////////////////////////////

public:
  typedef SequenceableCollection<T> Super;
  typedef Super::Element            Element;

  //////////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////////

  inline int size() const
  {
    return stack.size();
  }

  inline int capacity() const
  {
    return stack.capacity();
  }

  inline Bool is_empty() const
  {
    return stack.is_empty();
  }

  inline Bool is_full() const
  {
    return stack.is_full();
  }

  // virtual Bool contains(const T&) const;  // inherited
  // virtual Ix   lookup() const;            // inherited
  // virtual int length() const;             // inherited
  // virtual T& operator [] (int i) const;   // inherited

  //////////////////////////////////////////////////////////////
  //  Mutators
  ///////////////////////////////////////////////////////////////

  inline void clear()
  {
    stack.clear();
  }
  // virtual Ix   insert(const T&); // inherited
  // virtual Bool remove(const T&); // inherited

  ///////////////////////////////////////////////////////////////
  //  Iteration
  ///////////////////////////////////////////////////////////////

  inline Ix first() const
  {
    return stack.first();
  }

  inline Ix next(Ix i) const
  {
    return stack.next(i);
  }

  inline const T& operator [] (Ix) const
  {
    return stack(i);
  }

  inline T& operator [] (Ix)
  {
    return stack(i);
  }
};

#endif
