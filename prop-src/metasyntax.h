///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\metasyntax.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/metasyntax.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the interface to the meta-syntax compiler.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef meta_syntax_h
#define meta_syntax_h

#include <new>
#include "parsegen.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations
//
///////////////////////////////////////////////////////////////////////////////

class MetaSyntaxCompilerImpl;

///////////////////////////////////////////////////////////////////////////////
//
//  The meta-syntax compiler is responsible for translating patterns and
//  expressions written in meta-syntaxes into the equivalent in concrete
//  syntax.
//
///////////////////////////////////////////////////////////////////////////////

class MetaSyntaxCompiler : public virtual ParserCompiler
{
  MetaSyntaxCompiler (const MetaSyntaxCompiler&);
  void operator = (const MetaSyntaxCompiler&);
public:
  ////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor and destructor
  //
  ////////////////////////////////////////////////////////////////////////////
           MetaSyntaxCompiler ();
  virtual ~MetaSyntaxCompiler ();

  ////////////////////////////////////////////////////////////////////////////
  //
  //  Methods to install a new grammar, parse expressions and patterns,
  //  and generate a new report.
  //
  ////////////////////////////////////////////////////////////////////////////
  void install_grammar( Id grammar_name, GramExp grammar);
  Exp parse_exp( Id grammar_name, const char *);
  Pat parse_pat( Id grammar_name, const char *);
  std::ostream& print_report( std::ostream&);

private:
   ////////////////////////////////////////////////////////////////////////////
   //
   //  Private implementation stuff.
   //
   ////////////////////////////////////////////////////////////////////////////
   MetaSyntaxCompilerImpl * impl;
   void compile_new_grammar( Id grammar_name, GramExp grammar);
   void flush_grammar( size_t memory_needed);
};

#endif
#line 66 "../../prop-src/metasyntax.ph"
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
