///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the internal abstract machine of the
//  constraint compiler, which is based (very) loosely on the Warren
//  Abstract Machine (WAM).   It also describes various other semantic
//  objects used in the analysis of the logic clauses.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef WAM_definitions_h
#define WAM_definitions_h

#include "basics.ph"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward type definitions.
//
///////////////////////////////////////////////////////////////////////////////

datatype Ty      // type expressions
     and Cons    // constructor descriptor
     and Exp     // expressions
     and Stmt    // statements
     and Def     // definitions
     and Decl    // declarations
;

///////////////////////////////////////////////////////////////////////////////
//
//  Kind of variables.  These are characterized as follows, in order
//  of priority:
//  (a) Global variables are variables that occur as argument
//      in a structural pattern.  These may escape the life-time of
//      the clause.
//  (b) Local variables are variables that occur multiple times in a clause
//      (if they don't satisfy condition (a)).
//  (c) Void variables are variables with only one occurrence.  These
//      can be elided since they are always unifiable and never accessed.
//
///////////////////////////////////////////////////////////////////////////////

datatype VarKind : MEM
    = VOIDvar   (Ty)
    | LOCALvar  (Ty)
    | TEMPvar   (Ty)
    | GLOBALvar (Ty)

///////////////////////////////////////////////////////////////////////////////
//
//  Instantiateness of a clause parameter.
//
///////////////////////////////////////////////////////////////////////////////

and Instness : MEM
    = NOinst                            // unknown
    | IDinst     (Id)                   // named instness
    | FREEinst   (Ty)                   // free term
    | GROUNDinst (Ty)                   // ground term
    | BOUNDinst  (Ty,List<Instness>)    // bound term (disjunction)
    | APPinst    (Cons,List<Instness>)  // functor application
    | FUNinst    (Instness, Instness)   // instness mapping
    | VARinst    (Instness)             // instness variable

///////////////////////////////////////////////////////////////////////////////
//
//  Determinism of a clause.
//
///////////////////////////////////////////////////////////////////////////////

and Determinism : MEM
    = UNKNOWN_DET
    | DET                   // deterministic
    | SEMI_DET              // may succeed or fail once
    | MULTI_DET             // may succeed many times but only fail once
    | NON_DET               // non-deterministic
    | FAIL_DET              // always fail
    | ERROR_DET             // neither fail nor succeed
    | VAR_DET (Determinism) // determinstic variable

///////////////////////////////////////////////////////////////////////////////
//
//  Unification mode
//
///////////////////////////////////////////////////////////////////////////////

and UnificationMode = READ_MODE | WRITE_MODE

///////////////////////////////////////////////////////////////////////////////
//
//  The WAM instruction set.
//
//  Notice that our term representation is substantially different that
//  the traditional WAM.  This is mostly due to C++ interoperability
//  constraints (for example, it is not too nice to have tagged integers
//  if the user has to tag/untag them manually).  In general, we make
//  no distinction between structures or constants in the WAM level, since
//  we'll be re-using the pattern matching compiler to perform indexing
//  and semi-unification.  Also notice that terms in Prop are statically
//  typed in the style of ML.
//
///////////////////////////////////////////////////////////////////////////////

and WAM : MEM =
        "get_x"
    |   "get_y"
    |   "proceed"                    // WAM return
    |   "fail"                       // WAM failure
    |   "deref"
    |   "unify"
    |   "unify_variable"
    |   "unify_term"         (Ty, Cons)
    |   "try"                (Label)
    |   "retry"              (Label)
    |   "trust"              (Label)
    |   "try_me_else"        (Label)
    |   "retry_me_else"      (Label)
    |   "trust_me_else_fail"
    |   "label"              (Label)  // label in the code

///////////////////////////////////////////////////////////////////////////////
//
//  A program label.
//
///////////////////////////////////////////////////////////////////////////////

and Label : MEM = LABEL (Id) => _

///////////////////////////////////////////////////////////////////////////////
//
//  Miscellaneous types
//
///////////////////////////////////////////////////////////////////////////////

where type WAMs   = List<WAM>    // a list of wam instructions.
       and Labels = List<Label>  // a list of labels.
;

///////////////////////////////////////////////////////////////////////////////
//
//  Optimization and manipulation of WAM code.
//
///////////////////////////////////////////////////////////////////////////////

extern WAMs peep_hole (WAMs); // peep hole optimizer.

///////////////////////////////////////////////////////////////////////////////
//
//  Manipulation routines.
//
///////////////////////////////////////////////////////////////////////////////

extern Instness    deref( Instness);
extern Determinism deref( Determinism);

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printers.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, WAM);
extern std::ostream& operator << (std::ostream&, WAMs);
extern std::ostream& operator << (std::ostream&, Label);
extern std::ostream& operator << (std::ostream&, Labels);
extern std::ostream& operator << (std::ostream&, Instness);
extern std::ostream& operator << (std::ostream&, Determinism);

#endif
