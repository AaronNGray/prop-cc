///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\metasyntax.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/metasyntax.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the meta-syntax compiler.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "metasyntax.h"
#include "ir.h"
#include "ast.h"
#include "hashtab.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Implementation of the meta syntax compiler
//
///////////////////////////////////////////////////////////////////////////////

class MetaSyntaxCompilerImpl
{
  MetaSyntaxCompilerImpl(const MetaSyntaxCompilerImpl&);
  void operator = (const MetaSyntaxCompilerImpl&);
public:

  size_t    memory_used;   // total memory used for the parsers and lexers
  HashTable grammar_map;   // mapping from name to grammar
  int       timer;         // use count timer

  MetaSyntaxCompilerImpl()
     : memory_used(0),
       grammar_map(string_hash,string_equal)
       {}
};

///////////////////////////////////////////////////////////////////////////////
//
//  Definition of a grammar record
//
///////////////////////////////////////////////////////////////////////////////

struct GrammarRecord
{
  Id      grammar_name;   // grammar name
  GramExp grammar_exp;    // grammar expression
  size_t  memory_used;    // memory used for this grammar
  int     last_used;      // time of last use
  int     use_count;      // number of uses
};

///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
///////////////////////////////////////////////////////////////////////////////

MetaSyntaxCompiler:: MetaSyntaxCompiler()
    : impl(new MetaSyntaxCompilerImpl)
    {}

MetaSyntaxCompiler::~MetaSyntaxCompiler()
    { delete impl; }

///////////////////////////////////////////////////////////////////////////////
//
//  Method to compile a grammar give it an unique name.
//  We'll invoke the parser generator subclass to create a new parser.
//  Then the parser table is stored inside internal tables.
//
///////////////////////////////////////////////////////////////////////////////

void MetaSyntaxCompiler::install_grammar( Id grammar_name, GramExp grammar)
{
  gen_parser( grammar_name, grammar);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to parse the text as an expression.
//
///////////////////////////////////////////////////////////////////////////////

Exp MetaSyntaxCompiler::parse_exp( Id grammar_name, const char *text)
{
  error( "%Lunrecognized quoted expression `%s`\n", text);
  return NOexp;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to parse the text as a pattern.
//
///////////////////////////////////////////////////////////////////////////////

Pat MetaSyntaxCompiler::parse_pat( Id grammar_name, const char *text)
{
  error( "%Lunrecognized quoted pattern `%s`\n", text);
  return NOpat;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to flush out a grammar when memory is low.
//  This is invoked whenever a new grammar is to be compiled
//  and the total memory used has reached a limit.   The least
//  recently used grammars are flushed in this process.
//
///////////////////////////////////////////////////////////////////////////////

void MetaSyntaxCompiler::flush_grammar( size_t memory_needed)
{
  long memory_to_free = memory_needed;
  while (memory_to_free > 0 && impl->grammar_map.size() > 0)
  {
    GrammarRecord * kill_candidate = 0; // the candidate to invalidate.
    HashTable& grammar_map = impl->grammar_map;

    // Locate the least frequently used entry

    foreach_entry ( e, grammar_map)
    {
      if (kill_candidate == 0 ||
           ((GrammarRecord *)(e->v))->use_count < kill_candidate->use_count)
        kill_candidate = (GrammarRecord *)(e->v);
    }

    // Locate the oldest used entry

    foreach_entry ( e, grammar_map)
    {
      if (kill_candidate == 0 ||
           ((GrammarRecord *)(e->v))->last_used < kill_candidate->last_used)
        kill_candidate = (GrammarRecord *)(e->v);
    }

    // Kill entry and update the available memory

    if (kill_candidate)
    {
      if (options.generate_report)
          open_logfile() << "[Invalidating meta-language '"
                         << kill_candidate->grammar_name << "']\n";
      impl->memory_used -= kill_candidate->memory_used;
      memory_to_free    -= kill_candidate->memory_used;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Method to generate a report of all the grammars generated.
//
///////////////////////////////////////////////////////////////////////////////

std::ostream& MetaSyntaxCompiler::print_report( std::ostream& f)
{
  return f;
}
#line 160 "../../prop-src/metasyntax.pcc"
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
