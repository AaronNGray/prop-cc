///////////////////////////////////////////////////////////////////////////////
//
//  This file contains the definitions used in the parser generator
//  and meta syntax compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef parser_generator_h
#define parser_generator_h

#include <AD/automata/grammar.h>
#include "basics.ph"
#include "ir.ph"
#include "codegen.h"
#include "classdef.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations
//
///////////////////////////////////////////////////////////////////////////////

class Grammar;      // grammar class
class LALR1Gen;     // lalr1 parser class
class OpPrecedence; // operator precedence class

datatype Exp and Decl

///////////////////////////////////////////////////////////////////////////////
//
//  Parametric grammar expression.
//
///////////////////////////////////////////////////////////////////////////////

and      GramExp : Loc
                 = EXPgram (List<PrecRule>, ShiftReduceErrors, List<BNF>)
                                                   // a grammar expresson
                 | POLYgram (int, Id [], GramExp)  // polymorphic scheme
                 | UNIONgram (GramExp, GramExp)    // union
                 | RESTRICTgram (GramExp)          // restriction
                 | APPgram (GramExp, GramExp)      // application

///////////////////////////////////////////////////////////////////////////////
//
//  BNF rules
//
///////////////////////////////////////////////////////////////////////////////

and  BNF : Loc = BNFrule (Id, Ty, List<ProductionSymbols>)

///////////////////////////////////////////////////////////////////////////////
//
//  Precedence rules
//
///////////////////////////////////////////////////////////////////////////////

and PrecRule : Loc = PRECrule (PrecMode, int, ProductionSymbols)

///////////////////////////////////////////////////////////////////////////////
//
//  Operator association
//
///////////////////////////////////////////////////////////////////////////////

and PrecMode = LEFTassoc | RIGHTassoc | NONassoc

///////////////////////////////////////////////////////////////////////////////
//
//  Type abbreviations
//
///////////////////////////////////////////////////////////////////////////////

where type ProductionSymbols = List<ProductionSymbol>
and        PrecRules         = List<PrecRule>
and        BNFs              = List<BNF>
and        GramExps          = List<GramExp>
and        ShiftReduceErrors = int
;

///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing methods.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, ProductionSymbol);
extern std::ostream& operator << (std::ostream&, ProductionSymbols);
extern std::ostream& operator << (std::ostream&, PrecRule);
extern std::ostream& operator << (std::ostream&, PrecRules);
extern std::ostream& operator << (std::ostream&, BNF);
extern std::ostream& operator << (std::ostream&, BNFs);
extern std::ostream& operator << (std::ostream&, GramExp);
extern std::ostream& operator << (std::ostream&, GramExps);

///////////////////////////////////////////////////////////////////////////////
//
//  Class to represent a syntax class
//
///////////////////////////////////////////////////////////////////////////////

class SyntaxClass : public ClassDefinition
{
  SyntaxClass(const SyntaxClass&);
  void operator = (const SyntaxClass&);

public:

  typedef Grammar::Terminal    Terminal;
  typedef Grammar::NonTerminal NonTerminal;
  typedef Grammar::Action      Action;
  typedef Grammar::Production  Production;

protected:

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Internal data for generating a parser
  //
  ////////////////////////////////////////////////////////////////////////////
  BNFs                 production_rules;       // production rules
  PrecRules            precedence_rules;       // precedence rules
  Production *         productions;            // products array
  Grammar *            G;                      // Grammar object
  LALR1Gen *           parserGen;              // Parser generator object
  OpPrecedence *       prec;                   // operator precedence object
  int                  number_of_productions;  // Number of productions
  HashTable            nonterm_map;            // map nonterm -> Nonterminal
  HashTable            action_map;             // map Action -> Decls
  HashTable            inner_action_map;       //
  HashTable            line_map;               // map Action -> line#
  HashTable            predicate_map;          // ??
  Terminal             min_term;               // min Terminal #
  Terminal             max_term;               // max Terminal #
  Terminal             error_term;             // error Terminal #
  NonTerminal          max_nonterm;            // max NonTerminal #
  NonTerminal          start_symbol;           // start symbol of grammar
  Action               min_action;             // min Action #
  Id *                 symbol_names;           // map NonTerminal -> Id
  Ty *                 ty_map;                 // map NonTerminal -> Ty

public:
  SyntaxClass( CLASS_TYPE, Id, Inherits, TyQual, Decls);
  ~SyntaxClass();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to generate a syntax class
  //
  ////////////////////////////////////////////////////////////////////////////

  virtual void gen_parser( CodeGen&, GramExp);
  virtual void gen_class_interface( CodeGen&);
  virtual void gen_class_implementation( CodeGen&, Tys, DefKind);

private:
  // compile a set of rules
  virtual void compile_rules( CodeGen&, PrecRules, ShiftReduceErrors, BNFs);
  // compile a grammar expression
  virtual void compile_grammar( CodeGen&, GramExp);

  // Various phases of the compilation process
  void initialize();
  void cleanup();
  void preprocess_grammar();
  void translate_into_grammar();
  void define_operator_precedence();
  void process_parser_errors(ShiftReduceErrors);

  // Various phases of the code generation process
  void generate_semantic_stack_definition( CodeGen&);
  void generate_semantic_stack_growth( CodeGen&);
  void generate_semantic_stack_adjustment( CodeGen&);
  void generate_debugging_tables( CodeGen&);
  void generate_parse_method( CodeGen&);
  void generate_parser_tables( CodeGen&);
  void generate_action_driver( CodeGen&);
  virtual void generate_semantic_actions( CodeGen&);

  virtual void gen_class_constructor_initializers( CodeGen&, Tys, DefKind);
};

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of the parser generator
//
///////////////////////////////////////////////////////////////////////////////

class ParserCompiler : virtual public CodeGen
{
  ParserCompiler( const ParserCompiler&);  // no copy constructor
  void operator = ( const ParserCompiler&); // no assignment

public:
  ParserCompiler();
  ~ParserCompiler();

  ////////////////////////////////////////////////////////////////////////////
  //  Method to generate a syntax class
  ////////////////////////////////////////////////////////////////////////////
  virtual void  gen_parser( Id, GramExp);
};

#endif
