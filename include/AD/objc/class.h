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

#ifndef class_and_metaclass_base_classes_h
#define class_and_metaclass_base_classes_h

#include <AD/objc/objc.h>        // object base class

//////////////////////////////////////////////////////////////////////////////
//  Forward and opaque definitions
//////////////////////////////////////////////////////////////////////////////

class O_Class;          // class object base class
class O_MetaClass;      // metaclass object base class
class O_Protocol;       // protcol base class
class O_SelectorCache;  // cache for a selector
class O_MethodTable;    // method table

//////////////////////////////////////////////////////////////////////////////
//  Definition of class O_Class
//////////////////////////////////////////////////////////////////////////////
class O_Class : public O_Object
{
  O_Class(const O_Class&);           // no copy constructor
  void operator = (const O_Class&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Description for a class
  ///////////////////////////////////////////////////////////////////////////

protected:
  O_Class *         super_class;     // super class in the hierarchy
  O_MethodTable *   method_table;    // table of selectors -> method
  O_SelectorCache * selector_cache;  // method cache

  ///////////////////////////////////////////////////////////////////////////
  //  Some imported types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef O_Object            Super;
  typedef Super::ObjectMethod ObjectMethod;
  typedef Super::O_SEL        O_SEL;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  O_Class(O_Class * my_super_class, O_MetaClass * my_meta_class);
  virtual ~O_Class();

  ///////////////////////////////////////////////////////////////////////////
  //  Attributes
  ///////////////////////////////////////////////////////////////////////////

  inline const O_Class * my_super() const
  {
    return super_class;
  }
  inline       O_Class * my_super()
  {
    return super_class;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Methods for manipulating the method table and cache
  ///////////////////////////////////////////////////////////////////////////

  virtual ObjectMethod lookup_method  (O_SEL);
  virtual void         add_method     (O_SEL, ObjectMethod);
  virtual void         delete_method  (O_SEL);
  virtual Bool         is_defined     (O_SEL) const;
  virtual Bool         can_understand (O_SEL);
};

//////////////////////////////////////////////////////////////////////////////
//  Definition of class MetaClass
//////////////////////////////////////////////////////////////////////////////
class O_MetaClass : public O_Class
{
  O_MetaClass(const O_MetaClass&);       // no copy constructor
  void operator = (const O_MetaClass&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Some imported types
  ///////////////////////////////////////////////////////////////////////////

public:
  typedef O_Class             Super;
  typedef Super::ObjectMethod ObjectMethod;
  typedef Super::O_SEL        O_SEL;

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  O_MetaClass(O_Class * my_super_class, O_MetaClass * my_meta_class);
  virtual ~O_MetaClass();
};

#endif
