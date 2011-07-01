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

#ifndef selectors_h
#define selectors_h

#include <AD/objc/objc.h>

class O_SelectorTable
{
  O_SelectorTable(const O_SelectorTable&);  // no copy constructor
  void operator = (const O_SelectorTable&); // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef O_Object::O_SEL O_SEL;

  ///////////////////////////////////////////////////////////////////////////
  //  The implementation is private
  ///////////////////////////////////////////////////////////////////////////

private:
  class O_SelectorTable_Impl * impl;
  unsigned int                 new_names;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  O_SelectorTable();
  ~O_SelectorTable();

  ///////////////////////////////////////////////////////////////////////////
  //  Intern or lookup a new selector name
  ///////////////////////////////////////////////////////////////////////////
  O_SEL        create_selector (const char * selector_name);
  const char * print_name_of   (O_SEL) const;
};

#endif
