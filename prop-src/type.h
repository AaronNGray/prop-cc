///////////////////////////////////////////////////////////////////////////////
//  Types, type environments and type inference.
///////////////////////////////////////////////////////////////////////////////

#ifndef type_h
#define type_h

#include "ir.h"
#include "ast.h"
#include "hashtab.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Predefined type constants.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty string_ty, integer_ty, bool_ty, real_ty, character_ty,
    quark_ty,  bigint_ty, void_ty;

///////////////////////////////////////////////////////////////////////////////
//
//  Flags to control printing.
//
///////////////////////////////////////////////////////////////////////////////

extern Bool      pretty_print_ty;
extern Bool      pretty_print_exp;
extern Bool      print_semantic_stack;
extern Bool      print_inner_action;
extern Bool      print_default_value;
extern Parameter ty_parameter;
extern Id        ty_id;

///////////////////////////////////////////////////////////////////////////////
//
//  Function to initialize the predefined type constants.
//
///////////////////////////////////////////////////////////////////////////////

extern void initialize_types();

///////////////////////////////////////////////////////////////////////////////
//
//  Functions to make a type variable and make a polymorphic type scheme.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty mkvar();
extern Ty mkpolyty(Ty, TyVars);
extern int tag_of(Cons);

///////////////////////////////////////////////////////////////////////////////
//
//  Functions for constructing some common type constructors.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty mkptrty    (Ty);              // create a pointer type
extern Ty mkrefty    (Ty);              // create a reference type
extern Ty mkfunty    (Ty, Ty);          // create a function type
extern Ty mkarrayty  (Ty, Exp);         // create an array type
extern Ty mkidty     (Id, Tys);         // create a type id
extern Ty mkidvarty  (Id, TyVars);      // create a type id
extern Ty mktuplety  (Tys);             // create a tuple type
extern Ty mktypety   ();                // create a predicate type
extern Ty extuplety  (Tys);             // create a prop tuple type
extern Ty mkrecordty (Ids, Tys, Bool);  // create a record type
extern Tys tyvars_to_tys (TyVars);
extern Inherits add_inherit(Id, TyVars,
                              Inherits, Scope=PUBLICscope, TyQual=QUALnone);

///////////////////////////////////////////////////////////////////////////////
//
//  Functions for constructing some SETL-like type constructors.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty mklistty     (Ty);              // create a list type
extern Ty mksetty      (Ty);              // create a set type
extern Ty mkbagty      (Ty);              // create a bag type
extern Ty mksetty      (Ty);              // create a set type
extern Ty mkmapty      (Ty, Ty);          // create a map type
extern Ty mkmultimapty (Ty, Ty);          // create a multimap type
extern Ty mkqueuety    (Ty);              // create a queue type
extern Ty mkpriqueuety (Ty);              // create a priority queue type
extern Ty mkdequety    (Ty);              // create a deque type

///////////////////////////////////////////////////////////////////////////////
//
//   Functions for deferencing a type expression.
//   Unification introduces indirect links which must be explicitly
//   deferenced by all routines manipulation types.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty deref      (Ty);
extern Ty deref_all  (Ty);

///////////////////////////////////////////////////////////////////////////////
//
//   Function to extract the default value from a type, if any.  If none
//   is defined then NOexp is returned.  This is used to implement
//   default constructor arguments.
//
///////////////////////////////////////////////////////////////////////////////

extern Exp default_val (Ty);

///////////////////////////////////////////////////////////////////////////////
//
//   Functions for testing for specific attributes of a type.
//
///////////////////////////////////////////////////////////////////////////////

extern Bool has_qual             (TyQual, Ty); // Test for qualifiers
extern Bool is_ground            (Ty);         // Is it a ground type?
extern Bool is_ground            (Tys);        // Is it a ground type?
extern Bool is_array_ty          (Ty);         // Is it an array type?
extern Bool is_datatype          (Ty);         // Is it a prop datatype?
extern Bool is_poly_datatype     (Ty);         // Is it a polymorphic datatype?
extern Bool is_pointer_ty        (Ty);         // Is it a pointer type?
extern Bool is_gc_ty             (Ty);         // Is the type garbage collected?
extern Bool is_embeddable_ty     (Ty);         // Can it be embedded in a ptr?
extern Bool is_array_constructor (Id);         // Is it an array constructor?
extern Bool is_list_constructor  (Id);         // Is it an list constructor?
extern Bool is_list_constructor  (Cons);       // Is it an list constructor?
extern int  arity_of          (Ty);            // Arity?
extern int  boxed_variants    (Ty);            // Number of boxed variants?
extern int  unboxed_variants  (Ty);            // Number of unboxed variants?

///////////////////////////////////////////////////////////////////////////////
//
//   Instantiation and application of type schemes.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty  inst (Ty, int, Id [], Ty []);
extern Tys inst (Tys, int, Id [], Ty []);
extern Ty  inst (Ty);
extern Ty  apply_ty(Ty, Tys);
extern Ty  component_ty(Ty, Cons);
extern Ty  component_ty(Ty, Id);
extern Ty  component_ty(Ty, int);

///////////////////////////////////////////////////////////////////////////////
//
//   Unification routines.
//
///////////////////////////////////////////////////////////////////////////////

extern Bool unify (TyCon, TyCon);  // Unify two type constructors
extern Bool unify (Ty, Ty);        // Unify two types
extern Bool unify (Tys, Tys);      // Unify two type lists
extern Bool unify (Pat, Ty, Ty);   // Unify two type; report error if found.

///////////////////////////////////////////////////////////////////////////////
//
//   Type inference methods.
//
///////////////////////////////////////////////////////////////////////////////

extern HashTable * patvar_typemap; // additional pattern var type map.
extern Ty  type_of (Literal);  // Type of a literal
extern Ty  type_of (Pat);      // Type of a pattern
extern Tys type_of (Pats);     // Type of a pattern list
extern Tys type_of (LabPats);  // Type of a labeled pattern list

///////////////////////////////////////////////////////////////////////////////
//
//   Function to extract the label list from a labeled pattern list.
//
///////////////////////////////////////////////////////////////////////////////

extern Ids labels_of (LabPats);

///////////////////////////////////////////////////////////////////////////////
//
//   Function to type check a set of pattern matching rules.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty type_match_rules (MatchRules);

///////////////////////////////////////////////////////////////////////////////
//
//  Type and constructor environment methods.
//  These interface with the type, constructor and persistence environments.
//
///////////////////////////////////////////////////////////////////////////////

extern Ty         lookup_ty            (Id);
extern Cons       lookup_cons          (Id);
extern Cons       lookup_token         (Id);
extern Protocols  lookup_rewrite_class (Id);
extern Cons       find_cons            (Id);

extern void       add_type           (Id, TyVars, Ty);
extern void       add_datatype       (const Loc *, Id, TyVars, Inherits,
                                        TyQual, Exp, TermDefs, Decls);
extern void       add_rewrite_class  (Id, Protocols, TyQual);
extern void       update_datatype    (Id, TyVars, Inherits, TyQual, Decls);
extern void       update_constructor (Id, Tys, Inherits, PrintFormats, Decls);
extern void       update_persistent  (Id, Tys, Pid);

///////////////////////////////////////////////////////////////////////////////
//
//  Lexeme and regular expression conversions.
//  These interface with the lexeme environment.
//
///////////////////////////////////////////////////////////////////////////////

extern void         update_lexeme       (Id, Ids, Pat);
extern void         update_lexeme_class (Id, TermDefs);
extern TermDefs     lookup_lexeme_class (Id);
extern Pat          mk_regexp_pat       (const char *);
extern const char * convert_regexp      (const char *, Bool = true);
extern Pat          add_contexts        (Conses, Pat);
extern Pat          expand_lexeme_pat   (Pat, Ty, int, Cons []);
extern const char * make_quoted_string  (const char *);

///////////////////////////////////////////////////////////////////////////////
//
//   Function to mangle a constructor name into a C++ usable name.
//
///////////////////////////////////////////////////////////////////////////////

extern Id mangle (Id);

///////////////////////////////////////////////////////////////////////////////
//
//   Hashing and equality on qualifier identifiers and types.
//   These are used in various hashtables and environments.
//
///////////////////////////////////////////////////////////////////////////////

extern Bool         qualid_equal(QualId, QualId);
extern unsigned int ty_hash   (HashTable::Key);
extern Bool         ty_equal  (HashTable::Key, HashTable::Key);
extern unsigned int tys_hash  (HashTable::Key);
extern Bool         tys_equal (HashTable::Key, HashTable::Key);

#endif
