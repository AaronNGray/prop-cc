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

#ifndef fact_h
#define fact_h

//////////////////////////////////////////////////////////////////////////////
// Class |Fact| is a base class representing a fact within our
// Rete inference engine.  User defined facts will be derived from this class.
//////////////////////////////////////////////////////////////////////////////

class Fact
{
public:
  typedef int Age;     // time stamp
  typedef int RelTag;  // relation tag of subclass
  typedef int RuleId;  // rule id

protected:
  Age age;             // time stamp of last update;
  // used by the inference engine

  /////////////////////////////////////////////////////////////////////////
  //  Constructor and destructor
  /////////////////////////////////////////////////////////////////////////

public:
  Fact()
  {}
  virtual ~Fact()
  {}

  /////////////////////////////////////////////////////////////////////////
  //  Get and set timestamps; used by the inference engine only
  /////////////////////////////////////////////////////////////////////////
  virtual RelTag get_tag() const = 0;
  inline  Age    get_age() const
  {
    return age;
  }
  inline  void   set_age(Age a)
  {
    age = a;
  }
};

//////////////////////////////////////////////////////////////////////////////
//  Class InitialiseFact is used to assign unique runtime tags to each
//  class of facts.
//////////////////////////////////////////////////////////////////////////////

class InitialiseFact
{
  typedef Fact::RelTag RelTag;  // A tag
  static RelTag tag_count;      // global tag counter
public:
  InitialiseFact(RelTag& tag);
};

#endif
