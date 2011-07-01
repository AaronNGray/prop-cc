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

#ifndef bottomup_prioritized_reducer_generator_h
#define bottomup_prioritized_reducer_generator_h

#include <iostream.h>
#include <AD/automata/treegen.h>  // bottom up tree matcher generator

//////////////////////////////////////////////////////////////////////////////
//  This class implements prioritized bottom-up tree reducer generator
//////////////////////////////////////////////////////////////////////////////

class Reducer : public TreeGen
{
  Reducer(const Reducer&);            // no copy constructor
  void operator = (const Reducer&);   // no assignment

  ///////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  Reducer();
  virtual ~Reducer();

  ///////////////////////////////////////////////////////////////////////////
  // Code emission
  ///////////////////////////////////////////////////////////////////////////
  std::ostream& gen_code(std::ostream&, const char []) const;
};

#endif
