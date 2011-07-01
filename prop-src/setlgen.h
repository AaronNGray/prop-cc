///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\setlgen.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../prop-src/setlgen.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the interface of the SETL-like sublanguage compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SETL_data_mapping_compiler_h
#define SETL_data_mapping_compiler_h

#include "matchcom.h"
#include "setl-ast.h"
#include "env.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations
//
///////////////////////////////////////////////////////////////////////////////

#line 20 "../../prop-src/setlgen.ph"
#line 20 "../../prop-src/setlgen.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Time
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Time_defined
#define datatype_Time_defined
  class a_Time;
  typedef a_Time * Time;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Space
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Space_defined
#define datatype_Space_defined
  class a_Space;
  typedef a_Space * Space;
#endif

#line 20 "../../prop-src/setlgen.ph"
#line 20 "../../prop-src/setlgen.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Type checking methods
//
///////////////////////////////////////////////////////////////////////////////

extern Ty         type_of (Exp,  const Env&);  // type checking an expression
extern Tys        type_of (Exps, const Env&);  // type checking an expression list
extern 
#line 30 "../../prop-src/setlgen.ph"
Tuple2<Id, Ty>  
#line 30 "../../prop-src/setlgen.ph"
   type_of (LabExp,  const Env&);  // type checking an labeled expression
extern Tuple2<Ids, Tys>  
#line 31 "../../prop-src/setlgen.ph"
 type_of (LabExps, const Env&);  // type checking an labeled expression list
extern Env  type_of (Def,   const Env&);  // type checking a definition
extern Env  type_of (Defs,  const Env&);  // type checking a definition list
extern void type_of (Stmt,  const Env&);  // type checking a statement
extern void type_of (Stmts, const Env&);  // type checking a statement list

///////////////////////////////////////////////////////////////////////////////
//
//  We inherit from the code generator and the match compiler.
//
///////////////////////////////////////////////////////////////////////////////

class SETLCompiler : virtual public CodeGen,
                     virtual public MatchCompiler
{
  SETLCompiler(const SETLCompiler&);       // no copy constructor
  void operator = (const SETLCompiler&);   // no assignment
public:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor and destructor
  //
  ////////////////////////////////////////////////////////////////////////////
           SETLCompiler();
  virtual ~SETLCompiler();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Generate SETL-like statements and definitions
  //
  ////////////////////////////////////////////////////////////////////////////
  void gen_setl (Stmt);
  void gen_setl (Def);

private:

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Domain inference methods
  //
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Time and space complexity inference methods
  //
  ////////////////////////////////////////////////////////////////////////////
  Tuple2<Time, Space>  
#line 78 "../../prop-src/setlgen.ph"
 complexity_of (Exp, const Env&);
  Tuple2<Time, Space>  
#line 79 "../../prop-src/setlgen.ph"
 complexity_of (Stmt, const Env&);

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Code generation methods
  //
  ////////////////////////////////////////////////////////////////////////////
  void gen_def   (Def);      // code generation for definitions
  void gen_defs  (Defs);     // code generation for definition lists
  void gen_stmt  (Stmt);     // code generation for statements
  void gen_stmts (Stmts);    // code generation for statement lists
  void gen_exp   (Exp);      // code generation for expressions
  void gen_exps  (Exps);     // code generation for expression lists
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
