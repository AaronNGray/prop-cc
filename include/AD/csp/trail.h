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
// 1994-1996
//////////////////////////////////////////////////////////////////////////////

#ifndef unification_trail_h
#define unification_trail_h

#include <AD/memory/mempool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Logical object class.
//
//////////////////////////////////////////////////////////////////////////////

class LogicalTerm;

//////////////////////////////////////////////////////////////////////////////
//
//  Unification trail
//
//////////////////////////////////////////////////////////////////////////////

class UnificationTrail : public MemPool
{
  UnificationTrail(const UnificationTrail&);  // no copy constructor
  void operator = (const UnificationTrail&);  // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //
  //  The unification trail is implemented as a stack of LogicalTerm
  // pointers.
  //
  ///////////////////////////////////////////////////////////////////////////

protected:
  LogicalTerm ** trail_pointer;  // trail pointer
  LogicalTerm ** trail_bottom;   // bottom of the trail
  LogicalTerm ** trail_top;      // top of the trail
  void init_trail();     // method to initialize the unification trail
  void cleanup_trail();  // method to clean up the unification trail
  virtual void grow_trail();     // method to expand the trail

  ///////////////////////////////////////////////////////////////////////////
  //
  //  The choice point is implemented as a stack of ChoicePoint's.
  //
  ///////////////////////////////////////////////////////////////////////////

  struct ChoicePoint
  {
    MemPoolMark memory_marker; // memory marker
    size_t      trail_offset;  // trail offset to bottom
  };
  ChoicePoint * CP_pointer;     // choice point pointer
  ChoicePoint * CP_bottom;      // bottom of the choice point stack
  ChoicePoint * CP_top;         // top of the choice point stack
  void init_CP();       // method to initialize the choice point stack
  void cleanup_CP();    // method to clean up the choice point stack
  virtual void grow_CP();       // method to expand the choice point stack

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Constructors and destructor
  //
  ///////////////////////////////////////////////////////////////////////////

public:
  UnificationTrail();
  virtual ~UnificationTrail();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Unification trail/choice point methods.
  //
  ///////////////////////////////////////////////////////////////////////////
  inline void trail_check()
  {
    if (trail_pointer >= trail_top)
      grow_trail();
  }
  inline void trail_enter(LogicalTerm * term)
  {
    *trail_pointer++ = term;
  }
  inline void choice_point_check()
  {
    if (CP_pointer >= CP_top)
      grow_CP();
  }
};

#endif
