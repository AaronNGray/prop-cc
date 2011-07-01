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
// Allen Leung (leunga@valis.cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef persistent_object_store_h
#define persistent_object_store_h

//////////////////////////////////////////////////////////////////////////////
//
//  Forward type declarations
//
//////////////////////////////////////////////////////////////////////////////

class Piostream;
class std::ostrstream;
class PObject;
class PKeyedObject;

//////////////////////////////////////////////////////////////////////////////
//
//  Class 'PStore' describes the interface to a persistent object store.
//
//////////////////////////////////////////////////////////////////////////////

class PStore
{
  PStore(const PStore&);
  void operator = (const PStore&);
protected:
  Piostream *  pistd::ostream_;
  std::ostrstream * ostrstream_;
public:
  ///////////////////////////////////////////////////////////////////////////
  //
  //  Constructor and destructor
  //
  ///////////////////////////////////////////////////////////////////////////
  PStore();
  virtual ~PStore();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Read/write interface
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual PStore& operator << (const PObject&)   = 0;
  virtual PStore& operator << (const PObject *)  = 0;
  virtual PStore& operator >> (const PObject&)   = 0;
  virtual PStore& operator >> (const PObject *&) = 0;

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Indexing interface
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual void at (const PKeyedObject&)  = 0;
  virtual void at (const PKeyedObject *) = 0;

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Transaction interface
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual void begin_transaction() = 0;
  virtual void end_transaction()   = 0;
  virtual void commit()            = 0;
  virtual void rollback()          = 0;
};

#endif
