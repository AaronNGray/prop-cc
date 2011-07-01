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

#ifndef array_collection_h
#define array_collection_h

////////////////////////////////////////////////////////////////////////////
// ArrayCollection<T,A> is a template for implementing concrete collection
// classes that behave like an array.
// Suitable concrete classes include
//    FixArray<T>  in <A/contain/fixarray.h>
//    Array<T>     in <A/contain/array.h>
//    VarArray<T>  in <A/contain/vararray.h>
//    Indexable<T> in <A/contain/idxable.h>
////////////////////////////////////////////////////////////////////////////

#include <AD/contain/seqcol.h>

////////////////////////////////////////////////////////////////////////////
//  Template ArrayCollection<T,A> takes concrete implementation of an
//  array type and makes an instantiable collection class.
////////////////////////////////////////////////////////////////////////////

template <class T, class A>
class ArrayCollection : public SequenceableCollection<T>
{

  A array;  // implementation

  //////////////////////////////////////////////////////////////
  //  Inherit some types
  //////////////////////////////////////////////////////////////

public:
  typedef SequenceableCollection<T> Super;
  typedef Super::Element            Element;

  //////////////////////////////////////////////////////////////
  //  Constructor and destructor
  //////////////////////////////////////////////////////////////

  ArrayCollection(int size = Collection_default_size)  : array(size)
  {}
  ArrayCollection(const Collection<T>& C)   : array(C.size())
  {
    *this = C;
  }
  ArrayCollection(const ArrayCollection& C) : array(C.size())
  {
    *this = C;
  }
  ~ArrayCollection()
  {}

  //////////////////////////////////////////////////////////////
  //  Assignment
  //////////////////////////////////////////////////////////////

  void operator = (const Collection<T>&);

  //////////////////////////////////////////////////////////////
  //  Selectors
  //////////////////////////////////////////////////////////////

  inline int  size()       const
  {
    return array.length();
  }
  inline int  capacity()   const
  {
    return array.capacity();
  }
  // Bool is_empty() const;          // inherited
  // Bool is_full()  const;          // inherited
  // Bool contains(const T&) const; // inherited
  // Ix   lookup(const T&) const;   // inherited

  //////////////////////////////////////////////////////////////
  //  Mutators
  //  Notice that methods clear(), insert() and remove() are
  //  override since they do not make sense in this context
  //////////////////////////////////////////////////////////////

  void clear ()
  {
    should_not_implement("clear");
  }
  inline const T& operator [] (int i) const
  {
    return array[i];
  }
  inline T& operator [] (int i)
  {
    return array[i];
  }
  Ix   insert (const T&)
  {
    should_not_implement("insert");
    return 0;
  }
  Bool remove
    (const T&)
  {
    should_not_implement("remove");
    return false;
  }
  Bool del    (Ix)
  {
    should_not_implement("del");
    return false;
  }

  //////////////////////////////////////////////////////////////
  //  Iteration
  //////////////////////////////////////////////////////////////

  inline Ix       first()            const
  {
    return array.first();
  }
  inline Ix       next(Ix i)         const
  {
    return array.next(i);
  }
  inline const T& operator () (Ix i) const
  {
    return array(i);
  }
  inline       T& operator () (Ix i)
  {
    return array(i);
  }

  //////////////////////////////////////////////////////////////
  //  Other
  //////////////////////////////////////////////////////////////

  const char * myName() const
  {
    return "ArrayCollection";
  }
};

////////////////////////////////////////////////////////////////////////
//  The default assignment just iterates over all the elements
//  of a collection and inserts them into the array
////////////////////////////////////////////////////////////////////////

template <class T, class A>
void ArrayCollection<T, A>::operator = (const Collection<T>& C)
{
  Ix i;
  int j;
  for (i = C.first(), j = 0; i; i = C.next(i), j++)
    (*this)[j] = C(i);
}

#endif
