///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\parser.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PARSER_USED
#include <propdefs.h>
#line 1 "../../prop-src/parser.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  Definition of the Prop parser.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef prop_parser_interface_h
#define prop_parser_interface_h

#include <iostream>
#include <AD/automata/iolexerstack.h>
#include "ir.h"
#include "ast.h"
#include "patenv.h"
#include "textbuf.h"


class Compiler;
class GraphTypeDef;

///////////////////////////////////////////////////////////////////////////////
//
//  Lexical contexts
//
///////////////////////////////////////////////////////////////////////////////

#line 27 "../../prop-src/parser.ph"
#line 27 "../../prop-src/parser.ph"
enum LexicalContext {
  NONE = 0, C = 1, PROP = 2, 
  COMMENT = 3, QUOTE = 4, ANTIQUOTE = 5
};




#line 27 "../../prop-src/parser.ph"
#line 27 "../../prop-src/parser.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  The syntax class PropParser describe the interface to the
//  parsing/lexing front end.
//
///////////////////////////////////////////////////////////////////////////////

#line 36 "../../prop-src/parser.ph"
#line 196 "../../prop-src/parser.ph"
class PropParser : public LR1Parser {
public:
  /////////////////////////////////////////////////////////////////////////////
  // Parser table type definitions
  /////////////////////////////////////////////////////////////////////////////
  typedef LR1Parser               Super;
  typedef Super::Offset           Offset;
  typedef Super::State            State;
  typedef Super::Rule             Rule;
  typedef Super::Symbol           Symbol;
  typedef Super::ProductionLength ProductionLength;
  typedef Super::ShortSymbol      ShortSymbol;
  typedef Super::EquivMap         EquivMap;
  enum { INITIAL_STACK_SIZE_ = 256,
         MAX_STACK_SIZE_     = 8192
       };
protected:
  /////////////////////////////////////////////////////////////////////////////
  // Semantic value stack
  /////////////////////////////////////////////////////////////////////////////
  union PropParser_semantic_stack_type * t__, * bot__;
  int stack_size__;
  int heap_allocated__;
public:
  /////////////////////////////////////////////////////////////////////////////
  // Constructor and parsing method
  /////////////////////////////////////////////////////////////////////////////
  PropParser();
  virtual void parse();
  void action_driver(const Rule);
private:
  void adjust_stack(int);
  void grow_semantic_stack();
#line 37 "../../prop-src/parser.ph"
  
  PropParser(const PropParser&);
  void operator = (const PropParser&);
  
  private:
  enum
  {
    MAX_LEXICAL_DEPTH = 256,
    MAX_ARITY         = 256,
    MAX_INCLUDE_FILES = 256
  };
  
  ////////////////////////////////////////////////////////////////////////////
  //  Lexical buffer
  ////////////////////////////////////////////////////////////////////////////
  IOLexerStack lexbuf;
  
  ////////////////////////////////////////////////////////////////////////////
  //  Lexical context stack.  This is used to keep track of the
  //  current lexical context.
  ////////////////////////////////////////////////////////////////////////////
  LexicalContext SCs[MAX_LEXICAL_DEPTH];
  int            SCs_top;
  int            levels[MAX_LEXICAL_DEPTH];
  int            levels_top;
  Decls          code_stack[MAX_LEXICAL_DEPTH];
  int            code_top;
  void start_sc (LexicalContext); // enter a new lexical context
  void end_sc   ();               // leave the current lexical context
  
  ////////////////////////////////////////////////////////////////////////////
  //  Quoting stack
  ////////////////////////////////////////////////////////////////////////////
  struct Quote
  {
    const char * file_name;
    int          line_number;
    char         open, close;
    Quote() {}
    Quote(const char * file, int line, char a, char b)
        : file_name(file), line_number(line), open(a), close(b) {}
  };
  Quote quote_stack[MAX_LEXICAL_DEPTH];
  int   quote_top;
  void  start_quote(char, char);
  char  end_quote  (char);
  void  start_statement ();
  void  end_statement ();
  
  ////////////////////////////////////////////////////////////////////////////
  //  Internal code and documentation buffer.
  ////////////////////////////////////////////////////////////////////////////
  Bool       emit_code;
  TextBuffer scan;
  TextBuffer doc;
  TextBuffer meta;
  void emit ();
  void emit (char);
  void emit (const char *, long = -1);
  void emit (Exp);
  void emit_cons (Id cons_name);
  void emit_doc  ();
  void emit_meta ();
  void emit_header ();
  void count_lines ();
  
  ////////////////////////////////////////////////////////////////////////////
  //  Pattern variable environment and match expression stack
  ////////////////////////////////////////////////////////////////////////////
  PatternVarEnv pv_env;                        // pattern variable environment
  MatchExps     me_stack[MAX_LEXICAL_DEPTH];   // match expression stack
  MatchOptions  match_kind[MAX_LEXICAL_DEPTH]; // kind of match construct
  int           me_top;                        // top of me stack
  
  ////////////////////////////////////////////////////////////////////////////
  //  Variable binding stack
  ////////////////////////////////////////////////////////////////////////////
  Id   var_stack[MAX_ARITY];
  Pat  pat_stack[MAX_ARITY];
  int  var_top;
  
  ////////////////////////////////////////////////////////////////////////////
  //  Include file stack
  ////////////////////////////////////////////////////////////////////////////
  struct IncludeFile
  {
    int          line;
    int          first_line;
    const char * file;
    std::istream    * file_stream;
    TextBuffer   scan;
    TextBuffer   doc;
    TextBuffer   meta;
  };
  IncludeFile  includes[MAX_INCLUDE_FILES];
  int          includes_top;
  const char * included_files[MAX_INCLUDE_FILES];
  int          included_count;
  
  ////////////////////////////////////////////////////////////////////////////
  //  Miscellaneous flags and counters
  ////////////////////////////////////////////////////////////////////////////
  int  antecedent_count;  // number of antecedents in an inference rule
  Bool in_rewrite;        // are we in rewriting?
  int  rule_count;        // number of rules
  int  is_view_def;       // are we in a view definition?
  int  symbol_count;      // number of symbols in a production
  int  item_count;        // number of items in a production
  int  nonterm_count;     // number of non-terminals in a production
  int  match_rule;
  int  constraint_rule;
  
  struct rewrite_info
  {
    MatchRuleInfo::RewritingMode mode; // current rewrite mode
    MatchRuleInfo::RewritingOption option;
    TyQual qual;
  } rw_stack[MAX_LEXICAL_DEPTH]; // kind of rewriting mode
  int rw_top;                    // top of rw stack
  void push_rw_stack();
  void pop_rw_stack();
  
  ////////////////////////////////////////////////////////////////////////////
  //  The program being constructed.
  ////////////////////////////////////////////////////////////////////////////
  Cons  my_cons;
  Exp   my_exp;
  Compiler * compiler;          // the current compiler
  GraphTypeDef * graphtype_def; // the current graph type definition
  
  public:
  ////////////////////////////////////////////////////////////////////////////
  //  The public interface
  ////////////////////////////////////////////////////////////////////////////
  virtual ~PropParser();
  
  int get_token();             // method to retrieve a token
  int get_token2();             // method to retrieve a token
  ErrorAction error_report (const char *); // error reporting.
  void initialize(Compiler&);
  void initialize_lexer(const char * file_name);
  void cleanup_lexer();
  void print_header(Compiler&);
  Decls program;
  
  private:
  void open_include_file (const char *);   // open a new include file
  void close_include_file ();              // close include file
  
  Decls mkcode(Decls);
  Pat   mkconspat(Cons);
  Exp   lookup_exp(Id);
  Ty    lookup_tyvar(Id);
  Pat   lookup_patvar(Id);
  void  add_parse_stack_binding( int, int, int);
  
  // For error explanation
  void  print_user_symbol( std::ostream&, Symbol);
  void  explain_error();
#line 196 "../../prop-src/parser.ph"
};
#line 196 "../../prop-src/parser.ph"
#line 196 "../../prop-src/parser.ph"


#endif
#line 199 "../../prop-src/parser.ph"
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
