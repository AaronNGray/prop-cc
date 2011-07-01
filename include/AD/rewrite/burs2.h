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

#ifndef BURS_tree_matcher_with_attribute_evaluation_h
#define BURS_tree_matcher_with_attribute_evaluation_h

//////////////////////////////////////////////////////////////////////////
//
// Class |BURS| represents a tree automaton with compressed
// lookup tables.  See class |BURS_Gen| for the generator.
//
//////////////////////////////////////////////////////////////////////////

#include <AD/rewrite/burs.h>

template <class T>
class BURS2 : public BURS
{
  BURS2(const BURS2&);              // no copy constructor
  void operator = (const BURS2&);   // no assignment

  ///////////////////////////////////////////////////////////////////////
  //  Inport some types
  ///////////////////////////////////////////////////////////////////////

public:
  typedef BURS           Super;
  typedef Super::Functor Functor;
  typedef Super::Arity   Arity;
  typedef Super::State   State;
  typedef Super::Offset  Offset;
  typedef Super::Rule    Rule;

  ///////////////////////////////////////////////////////////////////////
  //  The attribute value stack is implemented as an array.
  ///////////////////////////////////////////////////////////////////////

protected:
  int   _max_capacity;  // capacity of the value stack
  int   _max_nesting;   // capacity of the scope stack
  T *   _values;        // attribute values
  int * _scopes;        // scope stack
  T *   _sp;            // pointer to the top of the value stack
  T *   _fp;            // pointer to the current scope

  ///////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////

public:
  BURS2(int max_capacity, int max_nesting)
      : _max_capacity(max_capacity),
      _max_nesting (max_nesting),
      _values      (new T   [max_capacity]),
      _scopes      (new int [max_nesting]),
      _sp          (_values),
      _fp          (_values)
  {}
  virtual ~BURS2()
  {
    delete [] _values;
    delete [] _scopes;
  }

  ///////////////////////////////////////////////////////////////////////
  //  Methods for manipulating the value stack.
  ///////////////////////////////////////////////////////////////////////
  inline const T  operator [] (int i) const
  {
    return _fp[i];
  }
  inline       T& operator [] (int i)
  {
    return _fp[i];
  }
};

#endif
