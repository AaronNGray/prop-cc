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

#ifndef objc_method_table_h
#define objc_method_table_h

#include <AD/objc/objc.h>
#include <AD/hash/lhash.h>

//////////////////////////////////////////////////////////////////////////////
//  Class O_MethodTable implements a mapping from selector to
//  method for a class
//////////////////////////////////////////////////////////////////////////////

class O_MethodTable
{
  O_MethodTable(const O_MethodTable&);     // no copy constructor
  void operator = (const O_MethodTable&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Import some types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef O_Object::ObjectMethod ObjectMethod;
  typedef O_Object::O_SEL        O_SEL;

  ///////////////////////////////////////////////////////////////////////////
  //  The actual table is an hash table.
  //  Due a compiler bug in gcc, I'm unable to parametrize the template
  //  with ObjectMethod directly.  Thus the funny wrapper business;
  ///////////////////////////////////////////////////////////////////////////

public:
  struct Wrapper
  {
    ObjectMethod m;
    inline Wrapper()
    {}
    inline Wrapper(ObjectMethod meth) : m(meth)
    {}
  }
  ;
  LHashTable<O_SEL,Wrapper> table;

public:
  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////
  O_MethodTable(int initial_size) : table(initial_size)
  {}
  ~O_MethodTable()
  {}

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for manipulating the method table
  ///////////////////////////////////////////////////////////////////////////
  inline void clear_method_table ()
  {
    table.clear();
  }
  inline void update_method_table(O_SEL s, ObjectMethod m)
  {
    table.insert(s,Wrapper(m));
  }
  inline Ix lookup_method_table(O_SEL s) const
  {
    return table.lookup(s);
  }
  inline void remove_method_table(O_SEL s)
  {
    table.remove(s);
  }
  inline ObjectMethod method_of (Ix i) const
  {
    return table.value(i).m;
  }
  inline int  method_table_size() const
  {
    return table.size();
  }
};

#endif
