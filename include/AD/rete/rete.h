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

#ifndef Rete_network_with_retraction_h
#define Rete_network_with_retraction_h

////////////////////////////////////////////////////////////////////////////
//  The class |Rete| represents a complete Rete network using a simple
//  aging conflict resolution strategy with priorities:
//  each rule is assigned a priority and each fact an age.
//  At each point, the rule with the highest priority triggered by the oldest
//  facts is selected.  Ambigiuity is arbitrarily resolved.
////////////////////////////////////////////////////////////////////////////

#include <AD/rete/retenet.h> // Rete network base class
#include <AD/contain/priq.h> // Binary heap based priority queue

class Rete : public ReteNet
{
  Rete(const Rete&);              // no copy constructor
  void operator = (const Rete&);  // no assignment

  /////////////////////////////////////////////////////////////////////////
  // Import some types
  /////////////////////////////////////////////////////////////////////////

public:
  typedef ReteNet         Super;
  typedef Super::Priority Priority;
  typedef Super::RuleId   RuleId;
  typedef Super::Node     Node;
  typedef Super::Age      Age;
  typedef Super::RelTag   RelTag;

  /////////////////////////////////////////////////////////////////////////
  // Definition of the
  /////////////////////////////////////////////////////////////////////////

  struct RelationTable
  {
    RelTag *     relation_tag;  // tag of relation type
    int          inject;        // injection method number
    const char * relation_name; // name of this relation
  };

  ////////////////////////////////////////////////////////////////////////
  // The implemetation of the conflict set is hidden.
  ////////////////////////////////////////////////////////////////////////

protected:
  class ReteConflictSet& conflict_set;
  int                    inject_table_size;
  int *                  inject_table;

  ////////////////////////////////////////////////////////////////////////
  // Constructor and destructor
  ////////////////////////////////////////////////////////////////////////

public:
  Rete( int                 N,           // size of the network table
        const Node          network [],  // network table
        int                 M,           // size of the alpha dispatch table
        const RelationTable T[]          // the dispatch table
      );
  ~Rete();

  ////////////////////////////////////////////////////////////////////////
  // Method to return the name of the inference class
  ////////////////////////////////////////////////////////////////////////
  virtual const char * name_of () const;

  ////////////////////////////////////////////////////////////////////////
  // Selectors
  ////////////////////////////////////////////////////////////////////////
  virtual int size() const;   // number of facts in the database

  ////////////////////////////////////////////////////////////////////////
  // Iterators
  ////////////////////////////////////////////////////////////////////////
  Ix           first()    const;
  Ix           next (Ix)  const;
  Fact * operator () (Ix) const;

  ////////////////////////////////////////////////////////////////////////
  // Conflict resolution
  ////////////////////////////////////////////////////////////////////////
  virtual void activate   (RuleId, int, Fact * []);
  virtual void deactivate (RuleId, int, Fact * []);
  virtual void fire       ();
  virtual Bool is_stable  () const;
  virtual void infer      ();
  virtual void add
    (const Rete&);

  ////////////////////////////////////////////////////////////////////////
  //  Action routine, to be defined by subclass.
  ////////////////////////////////////////////////////////////////////////
  virtual void action(RuleId, Fact * []) = 0; // Action routine

  ////////////////////////////////////////////////////////////////////////
  //  Functions to insert/remove facts from the database.
  ////////////////////////////////////////////////////////////////////////
  virtual ReteNet& assert_fact  ( Fact * );
  virtual ReteNet& retract_fact ( Fact * );

  ////////////////////////////////////////////////////////////////////////
  //  Clear entire database
  ////////////////////////////////////////////////////////////////////////
  virtual void clear();
};

#endif
