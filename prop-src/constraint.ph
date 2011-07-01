///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the interface of the constraint compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef constraint_compiler_h
#define constraint_compiler_h

#include "basics.ph"
#include "codegen.h"
#include "matchcom.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward datatype declarations
//
///////////////////////////////////////////////////////////////////////////////

datatype Ty          //  Type expressions
     and Pat         //  Patterns
     and Exp         //  Expressions
     and Decl        //  Prop declarations
     and Def         //  Definitions
     and Stmt        //  Statements
     and Instness    //  Instantiatedness
     and Determinism //  Determinism of a predicate
;

class HashTable;

///////////////////////////////////////////////////////////////////////////////
//
//  The grammar of the constraint rules is defined as follows:
//
///////////////////////////////////////////////////////////////////////////////

datatype ConstraintSet : Loc =
           CONSTRAINTset (ConstraintDefs)

and      ConstraintDef : Loc =
           CONSTRAINTruledef ConstraintRule            // rule definition
         | CONSTRAINTtype     (Id, Ty)                 // type constraint
         | CONSTRAINTinstness (Id, Pat)                // instness definition
         | CONSTRAINTdet      (Id, Pats, Determinism)  // determinism const.

and      ConstraintRule    : Loc =
           CONSTRAINTrule
           {
             id   : Id,             // the functor name
             pat  : Pat,            // pattern argument
             body : ConstraintBody, // clause body
             ty   : Ty = NOty       // optional type
           }

and      ConstraintBody    : Loc =
           CONSTRAINTnone
         | CONSTRAINTcut
         | CONSTRAINTand     (ConstraintBody, ConstraintBody)
         | CONSTRAINTif      (ConstraintBody, ConstraintBody, ConstraintBody)
         | CONSTRAINTbody    (List<Decl>)
         | CONSTRAINTcall    (Exp)

where type ConstraintDefs  = List<ConstraintDef>
       and ConstraintRules = List<ConstraintRule>
;

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing routines.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, ConstraintSet);
extern std::ostream& operator << (std::ostream&, ConstraintDef);
extern std::ostream& operator << (std::ostream&, ConstraintDefs);
extern std::ostream& operator << (std::ostream&, ConstraintRule);
extern std::ostream& operator << (std::ostream&, ConstraintRules);
extern std::ostream& operator << (std::ostream&, ConstraintBody);

///////////////////////////////////////////////////////////////////////////////
//
//  Forward declaration.
//
///////////////////////////////////////////////////////////////////////////////

class ConstraintCompilerInternal;

///////////////////////////////////////////////////////////////////////////////
//
//  The constraint compiler is inherited from the code generator.
//
///////////////////////////////////////////////////////////////////////////////

class ConstraintCompiler : virtual public CodeGen,
                           virtual public MatchCompiler
{
  ConstraintCompiler(const ConstraintCompiler&); // no copy constructor
  void operator = (const ConstraintCompiler&);   // no assignment

protected:

  ConstraintCompilerInternal * internal;  // internal implementation

public:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor and destructor
  //
  ////////////////////////////////////////////////////////////////////////////
           ConstraintCompiler();
  virtual ~ConstraintCompiler();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods for compiling a set of constraint rules.
  //
  ////////////////////////////////////////////////////////////////////////////
  void compile_ruleset( Id class_name, ConstraintSet rule_set);

private:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Private implementation methods.
  //
  ////////////////////////////////////////////////////////////////////////////
  void process_typing_rules( Id, List<.[Id,Ty]>);
  void process_ruleset( Id, ConstraintRules);
  void add_predicate_type( Id, Ty);
  void analyze_rule( ConstraintBody);
};


#endif
