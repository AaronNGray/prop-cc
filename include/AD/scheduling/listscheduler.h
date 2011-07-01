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

#ifndef list_scheduler_base_class_h
#define list_scheduler_base_class_h

#include <AD/generic/generic.h>
#include <AD/machine/machineunits.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Opaque type declarations
//
//////////////////////////////////////////////////////////////////////////////

class Mem;
class Schedule;
class ResourceMapping;

//////////////////////////////////////////////////////////////////////////////
//
//  Class ListScheduler is a base class of all list scheduling algorithms.
//
//////////////////////////////////////////////////////////////////////////////

class ListScheduler : public MachineUnits
{
  ListScheduler(const ListScheduler&);    // no copy constructor
  void operator = (const ListScheduler&); // no assignment

protected:
  Mem& mem;  // memory manager used by the list scheduler

  ///////////////////////////////////////////////////////////////////////////
  //  Constructor and destructors
  ///////////////////////////////////////////////////////////////////////////

public:
  ListScheduler();
  ListScheduler(Mem&);
  virtual ~ListScheduler();

  virtual void compute_schedule ();

protected:
  virtual void compute_ranks () = 0;
  virtual void list_schedule () = 0;
};

#endif
