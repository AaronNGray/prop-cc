///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "paige.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "paige.pcc"
#include <assert.h>
#include <iostream.h>
#include <fstream.h>
#include <AD/pretty/postream.h>
#include "paige.h"
#include "willard-ast.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor for the Paige/Goyal query transformer
//
///////////////////////////////////////////////////////////////////////////////
PaigeGoyal::PaigeGoyal() : log(*new ofstream), errlog(cerr)
{  True     = LIT(BOOL(true));
   False    = LIT(BOOL(false));
   Zero     = LIT(INT(0));
   One      = LIT(INT(1));
   Two      = LIT(INT(2));
   EmptySet = GENERATOR(
#line 19 "paige.pcc"
#line 19 "paige.pcc"
nil_1_
#line 19 "paige.pcc"
#line 19 "paige.pcc"
,
#line 19 "paige.pcc"
#line 19 "paige.pcc"
nil_1_
#line 19 "paige.pcc"
#line 19 "paige.pcc"
,Zero);
   new_name = 0;
   subquery_names = 
#line 21 "paige.pcc"
#line 21 "paige.pcc"
nil_1_
#line 21 "paige.pcc"
#line 21 "paige.pcc"
;
   subqueries = 
#line 22 "paige.pcc"
#line 22 "paige.pcc"
nil_1_
#line 22 "paige.pcc"
#line 22 "paige.pcc"
;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Destructor for the Paige/Goyal query transformer
//
///////////////////////////////////////////////////////////////////////////////
PaigeGoyal::~PaigeGoyal() 
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to add a subquery
//
///////////////////////////////////////////////////////////////////////////////
void PaigeGoyal::add_subquery(Id x, Exp e) 
{  // PrettyOStream S; 
   // S << "Subquery: " << x << '=' << e << '\n';
   subquery_names = 
#line 42 "paige.pcc"
#line 42 "paige.pcc"
list_1_(x,subquery_names)
#line 42 "paige.pcc"
#line 42 "paige.pcc"
;
   subqueries     = 
#line 43 "paige.pcc"
#line 43 "paige.pcc"
list_1_(e,subqueries)
#line 43 "paige.pcc"
#line 43 "paige.pcc"
;
}
Bool PaigeGoyal::has_subqueries() const { return subqueries != 
#line 45 "paige.pcc"
#line 45 "paige.pcc"
nil_1_
#line 45 "paige.pcc"
#line 45 "paige.pcc"
; }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to collect subqueries into a LET
//
///////////////////////////////////////////////////////////////////////////////
Exp PaigeGoyal::collect_subqueries(Exp exp) 
{  exp = make_let(subquery_names, subqueries, exp);
   subquery_names = 
#line 54 "paige.pcc"
#line 54 "paige.pcc"
nil_1_
#line 54 "paige.pcc"
#line 54 "paige.pcc"
;
   subqueries     = 
#line 55 "paige.pcc"
#line 55 "paige.pcc"
nil_1_
#line 55 "paige.pcc"
#line 55 "paige.pcc"
;
   return exp;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to make a nested LET
//
///////////////////////////////////////////////////////////////////////////////
Exp PaigeGoyal::make_let(Ids xs, Exps es, Exp exp) 
{  
#line 65 "paige.pcc"
#line 71 "paige.pcc"
{
   for (;;) {
      if (xs) {
         if (es) {
#line 67 "paige.pcc"
          Id  x = xs->_1;
            	 Exp e = es->_1; 
            	 exp = LET(x,e,exp); 
            	 xs = xs->_2; es = es->_2;
                  
#line 71 "paige.pcc"
         } else { goto L1; }
      } else { goto L1; }
   }
   L1:;
}
#line 72 "paige.pcc"
#line 72 "paige.pcc"

   return exp;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to define/lookup the range of a variable
//
///////////////////////////////////////////////////////////////////////////////
void PaigeGoyal::define_range(Id x, Exp e) { var_range.insert(x,e); }
void PaigeGoyal::define_range(Ids xs, Exps es) 
{  Ids  ids = xs;
   Exps exps = es;
   
#line 85 "paige.pcc"
#line 86 "paige.pcc"
{
   for (;;) {
      if (ids) {
         if (exps) {
#line 86 "paige.pcc"
           define_range(ids->_1,exps->_1); ids = ids->_2; exps = exps->_2; 
#line 86 "paige.pcc"
         } else { goto L2; }
      } else { goto L2; }
   }
   L2:;
}
#line 87 "paige.pcc"
#line 87 "paige.pcc"

   if (ids != 
#line 88 "paige.pcc"
#line 88 "paige.pcc"
nil_1_
#line 88 "paige.pcc"
#line 88 "paige.pcc"
 || exps != 
#line 88 "paige.pcc"
#line 88 "paige.pcc"
nil_1_
#line 88 "paige.pcc"
#line 88 "paige.pcc"
)
      errlog << "Arity mismatch in " << xs << "in" << es << ::newline; 
}

Exp  PaigeGoyal::range_of(Id x) 
{  assert(var_range.contains(x));
   return var_range[x]; 
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print messages
//
///////////////////////////////////////////////////////////////////////////////
void PaigeGoyal::message(const char * msg, Exp e) 
{  log << ::indent << e << ::newline << ::newline << ::unindent
       << '[' << msg << ']' << ::newline << ::newline;
}

void PaigeGoyal::error(const char * msg, Exp e) 
{  errlog << '[' << "ERROR:" << msg << ']' << ::newline << ::indent
          << e << ::newline << ::unindent; 
}

void PaigeGoyal::set_log(ostream& f) { log.set_stream(f); }
void PaigeGoyal::set_error(ostream& f) { errlog.set_stream(f); }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to add an edge into the query graph
//
///////////////////////////////////////////////////////////////////////////////
void PaigeGoyal::add_edge(Id x, Id y)
{  if (parent.contains(y))
   {  Id z = parent[y];
      if (x != z)
	 errlog << "Edge: " << x << "->" << y << "conflicts with" 
		<< z << "->" << y << "in the query graph\n";
   }
   parent.insert(y,x);
}

Bool PaigeGoyal::has_edge(Id x, Id y) const
{  if (! parent.contains(y)) return false;
   return parent[y] == x; 
}

void PaigeGoyal::add_edge_query(Id x, Id y, Exp q) 
{
   edge_queries.insert(
#line 137 "paige.pcc"
#line 137 "paige.pcc"
mkTuple2(x,y)
#line 137 "paige.pcc"
#line 137 "paige.pcc"
,q);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compute the transitive closure of the query graph
//
///////////////////////////////////////////////////////////////////////////////
void PaigeGoyal::compute_transitive_closure() 
{  foreach (i,parent)
   {  parent_closure.insert(parent.key(i),parent.value(i));
   }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Methods to push/pop from the quantifier stack
//
///////////////////////////////////////////////////////////////////////////////
void PaigeGoyal::push_quantifier(Id x) { quantifier_vars.push(x); }
void PaigeGoyal::push_quantifier(Ids xs) 
{  
#line 158 "paige.pcc"
#line 158 "paige.pcc"
{
   for (;;) {
      if (xs) {
#line 158 "paige.pcc"
        push_quantifier(xs->_1); xs = xs->_2; 
#line 158 "paige.pcc"
      } else { goto L3; }
   }
   L3:;
}
#line 158 "paige.pcc"
#line 158 "paige.pcc"
 }
void PaigeGoyal::pop_quantifier(Id x) { quantifier_vars.pop(); }
void PaigeGoyal::pop_quantifier(Ids xs) 
{  
#line 161 "paige.pcc"
#line 161 "paige.pcc"
{
   for (;;) {
      if (xs) {
#line 161 "paige.pcc"
        pop_quantifier(xs->_1); xs = xs->_2; 
#line 161 "paige.pcc"
      } else { goto L4; }
   }
   L4:;
}
#line 161 "paige.pcc"
#line 161 "paige.pcc"
 }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to print the query graph
//
///////////////////////////////////////////////////////////////////////////////
void PaigeGoyal::print_query_graph() 
{  log << ::tab << "[Query Graph]" << ::newline << ::indent;
   foreach (i,parent)
   {  Id x = parent.value(i);
      Id y = parent.key(i);
      log << ::tab << "edge" << x << "->" << y;
      if (edge_queries.contains(
#line 174 "paige.pcc"
#line 174 "paige.pcc"
mkTuple2(x,y)
#line 174 "paige.pcc"
#line 174 "paige.pcc"
))
	  log << '\t' << edge_queries[
#line 175 "paige.pcc"
#line 175 "paige.pcc"
mkTuple2(x,y)
#line 175 "paige.pcc"
#line 175 "paige.pcc"
]; 
      log << ::newline;
   }
   log << ::unindent;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Main method to decompose a query
//
///////////////////////////////////////////////////////////////////////////////
Exp PaigeGoyal::decompose(Exp e) 
{  subqueries = 
#line 187 "paige.pcc"
#line 187 "paige.pcc"
nil_1_
#line 187 "paige.pcc"
#line 187 "paige.pcc"
;
   do {
      changed = false;
      e = remove_duplicate_names(e);
      e = phase1(e);   // DNF construction
      e = construct_query_graph(e); // query graph construction
      e = phase2(e);   // quantifier elimination
      e = phase3(e);   // disjunction removal
      e = phase4(e);   // conjunction removal 
      e = projection_recognition(e);
      e = phase5(e);
      if (changed) message("Reiterating the transformation",e);
   } while (changed);
   return e;
}
#line 202 "paige.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 8
Number of ifs generated      = 6
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
