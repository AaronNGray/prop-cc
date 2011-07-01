///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "paige.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "paige.ph"
#ifndef paige_doyal_h
#define paige_doyal_h

#include <AD/pretty/postream.h>
#include <AD/contain/varstack.h>
#include "willard-ast.h"
#include "idset.h"
#include "smap.h"

class ostream;

///////////////////////////////////////////////////////////////////////////////
//
//   This class implements the transformation algorithm as developed by
//   Bob Paige and Deepak Goyal.
//
///////////////////////////////////////////////////////////////////////////////
class PaigeGoyal 
{  PaigeGoyal(const PaigeGoyal&);
   void operator = (const PaigeGoyal&);

   ////////////////////////////////////////////////////////////////////////////
   //
   //  Internal data 
   //
   ////////////////////////////////////////////////////////////////////////////
protected:
   PrettyOStream    log, errlog; // pretty printing stream for message logging 
   int              new_name;    // counter for new names
   Ids              subquery_names; // set of subqueries currently generated.
   Exps             subqueries;  // set of subqueries currently generated.
   SMap<Id,Exp>     var_range;   // record the range of each variable
   SMap<Id,Id>      parent;      // the query graph: 
				 //   mapping from child to parent
   SMap<Id,Id>      parent_closure; // the query graph (in closure form): 
   SMap<
#line 36 "paige.ph"
Tuple2<Id, Id>  
#line 36 "paige.ph"
,Exp> edge_queries; // mapping from edge (x,y) to query Q(x,y)
   VarStack<Id> quantifier_vars;    // quantifier vars currently in scope
protected:

   ////////////////////////////////////////////////////////////////////////////
   //
   // Internal methods 
   //
   ////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////
   // Common predefined constants
   ////////////////////////////////////////////////////////////////////////////
   Exp True, False, Zero, One, Two, EmptySet;  

   ////////////////////////////////////////////////////////////////////////////
   // Methods to construct the query graph
   ////////////////////////////////////////////////////////////////////////////
   void add_edge(Id x, Id y);
   Bool has_edge(Id x, Id y) const;
   void add_edge_query(Id x, Id y, Exp query);
   void compute_transitive_closure(); 
   void print_query_graph();

   ////////////////////////////////////////////////////////////////////////////
   // Methods to collect free variables in an expression.
   ////////////////////////////////////////////////////////////////////////////
   void free_vars(Ids,  IdSet&) const;
   void free_vars(Exp,  IdSet&) const;
   void free_vars(Exps, IdSet&) const;
   void remove_vars (IdSet&, Ids) const;
   void remove_vars (IdSet&, const IdSet&) const;

   ////////////////////////////////////////////////////////////////////////////
   // Is x free in e?
   ////////////////////////////////////////////////////////////////////////////
   Bool is_free(Id x, Exp e) const;
   Bool is_free(Ids xs, Exp e) const;

   ////////////////////////////////////////////////////////////////////////////
   // Methods to generate new names
   ////////////////////////////////////////////////////////////////////////////
   Id gensym();
   Id gensym(Id prefix);

   ////////////////////////////////////////////////////////////////////////////
   // Methods to generate and collect subqueries
   ////////////////////////////////////////////////////////////////////////////
   void add_subquery(Id, Exp);
   Exp collect_subqueries(Exp);
   Bool has_subqueries() const;

   ////////////////////////////////////////////////////////////////////////////
   // Method to record the range of each variable.
   ////////////////////////////////////////////////////////////////////////////
   void define_range(Id, Exp);
   void define_range(Ids, Exps);
   Exp  range_of(Id);

   ////////////////////////////////////////////////////////////////////////////
   // Methods to push/pop from the quantifier stack
   ////////////////////////////////////////////////////////////////////////////
   void push_quantifier(Id x);
   void push_quantifier(Ids xs);
   void pop_quantifier(Id x);
   void pop_quantifier(Ids xs);

   ////////////////////////////////////////////////////////////////////////////
   // Set by subclasses if re-iteration of the transformation process
   // is required.
   ////////////////////////////////////////////////////////////////////////////
   Bool changed;    

   ////////////////////////////////////////////////////////////////////////////
   // Method to create a nested let
   ////////////////////////////////////////////////////////////////////////////
public:
   static Exp make_let(Ids, Exps, Exp);
public:
            PaigeGoyal();
   virtual ~PaigeGoyal();

   ////////////////////////////////////////////////////////////////////////////
   // Main decomposition method
   ////////////////////////////////////////////////////////////////////////////
   virtual Exp decompose(Exp);

   ////////////////////////////////////////////////////////////////////////////
   // Method to print messages
   ////////////////////////////////////////////////////////////////////////////
   void message(const char * mesg, Exp e);
   void error(const char * mesg, Exp e);
   void set_log  (ostream&);
   void set_error(ostream&);
protected:

   ////////////////////////////////////////////////////////////////////////////
   // The following are the different phases implemented in subclasses.
   ////////////////////////////////////////////////////////////////////////////
   virtual Exp remove_duplicate_names(Exp) = 0;
   virtual Exp construct_query_graph(Exp) = 0; // query graph construction
   virtual Exp projection_recognition(Exp) = 0;
   virtual Exp phase1(Exp) = 0;  // DNF construction
   virtual Exp phase2(Exp) = 0;  // quantifier elimination
   virtual Exp phase3(Exp) = 0;  // disjunction removal
   virtual Exp phase4(Exp) = 0;  // join decomposition 
   virtual Exp phase5(Exp) = 0;  // simple count/find query decomposition 
};

#endif
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
