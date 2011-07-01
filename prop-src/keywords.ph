///////////////////////////////////////////////////////////////////////////////
//
//  This file defines the lexical structure of the Prop language.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef prop_lexemes_h
#define prop_lexemes_h

///////////////////////////////////////////////////////////////////////////////
//
//  Here are some regular expression abbreviations.
//
///////////////////////////////////////////////////////////////////////////////

lexeme digits      = /[0-9]+/
     | sign        = /[\+\-]/
     | integer     = /{digits}/
     | exponent    = /[eE]{sign}?{digits}/
     | mantissa    = /({digits}\.{digits}?|\.{digits})/
     | real        = /{mantissa}{exponent}?/
     | ident	   = /([a-zA-Z\$][a-zA-Z0-9_\$]*|[a-zA-Z_][a-zA-Z0-9_]+)/
     | patvar      = /([\?\#\$]*{ident}[\'\?]*|\#\#)/
     | string      = /"([^\\"\n]|\\.)*"/
     | character   = /'([^\\'\n]|\\.[0-9a-f]*)'/
     | regexp      = /\/([^\/\n*]|\\.)([^\/\n]|\\.)*\//
     | logical_var = /\'{ident}/
     | meta        = /`([^`]|\\.)*`/
     ;

///////////////////////////////////////////////////////////////////////////////
//
//  Main keywords are keywords that can start Prop constructs.
//
///////////////////////////////////////////////////////////////////////////////

lexeme class MainKeywords =
    "rewrite" | "inference" | "match" | "matchall" | "matchscan"
  | "refine"  | "classof" | "type" | "datatype" | "instantiate"
  | "lexeme"  | "bitfield" | "begin" | "syntax"
  | "dataflow" | "module" | "signature" | "constraint" | "declare"
  | "procedure" | "fun" | "function"
  | "graphtype" | "graphrewrite" | "cutrewrite" | "failrewrite"
  | "attributegrammar"

///////////////////////////////////////////////////////////////////////////////
//
//  Keywords are the normal kinds of keywords
//
///////////////////////////////////////////////////////////////////////////////

and Keywords =
    "if" | "then" | "else" | "elsif" | "while" | "loop" | "is"
  | "class" | "unifiable" | "of"
  | "do" | "break" | "continue" | "goto"
  | "where" | "as" | "public" | "protected"
  | "private" | "const" | "extern" | "mutable" | "applicative"
  | "virtual" | "true" | "false" | "collectable" | "finalizable"
  | "printable" | "traced" | "persistent"
  | "treeparser" | "inline" | "with" | "switch" | "unsigned"
  | "signed" | "for" | "category" | "functor" | "feature"
  | "sharing" | "relation" | "view" | "inherited" | "return"
  | "synthesized" | "law" | "left:" | "right:" | "expect:" | "prec:"
  | "mapof" | "setof" | "bagof" | "multimapof" | "listof" | "priqueueof"
  | "queueof" | "dequeof" | "tupleof" | "forall" | "exists"
  | "dom" | "ran" | "arb" | "less" | "include"
  | "lfp" | "gfp" | "hom"
  | "implies:" | "xor:" | "equiv:" | "time:" | "space:"
  | "nodes:" | "edges:" | "index:" | "hash:" | "equality:"
  | "preorder:" | "postorder:" | "before:"
  | "topdown:" | "bottomup:" | "strategy:" | "order:"
  | "pragma:"

and SepKeywords = "case" | "and" | "end"

///////////////////////////////////////////////////////////////////////////////
//
//  Symbols are multi-character symbols used in Prop.
//  Single character symbols are implicit and unlisted here.
//
///////////////////////////////////////////////////////////////////////////////

and  Symbols =
    ".." | "..." | "<->" | "::" | "&&" | "||" | "++" | "--" | "->"
  | "<<" | ">>" | ">=" | "<=" | "+=" | "-=" | "*=" | "/=" | "%=" | "=="
  | "!=" | "<<=" | ">>=" | "&=" | "|=" | "^=" | "=>" | "<-" | "<=>"
  | ":=" | ":-" | LONG_BAR /\-\-\-\-\-+/

///////////////////////////////////////////////////////////////////////////////
//
//  Special symbols are symbols that is used for ad hoc syntactic features.
//
///////////////////////////////////////////////////////////////////////////////

and Special =
    CONS_TOK | DOMAIN_TOK | CONS_EXP | META_QUOTE | POLY_DATATYPE | ATTRIB_ID
  | "(|" | "|)" | "[|" | "|]" | "{|" | "|}" | ".(" | ".[" | "``" | "''"

///////////////////////////////////////////////////////////////////////////////
//
//  Literal values
//
///////////////////////////////////////////////////////////////////////////////

and Literals =
    INT_TOK     /{integer}/
  | REAL_TOK    /{real}/
  | CHAR_TOK    /{character}/
  | STRING_TOK  /{string}/
  ;

///////////////////////////////////////////////////////////////////////////////
//
//  PropToken is the class of all terminals in Prop.
//
///////////////////////////////////////////////////////////////////////////////

datatype PropToken :: lexeme =
    lexeme class MainKeywords
  | lexeme class Keywords
  | lexeme class SepKeywords
  | lexeme class Symbols
  | lexeme class Special
  | lexeme class Literals
  | ID_TOK       /{patvar}/
  | REGEXP_TOK   /{regexp}/
  | QUARK_TOK    /#{string}/
  | BIGINT_TOK   /#{sign}{integer}/
  | PUNCTUATIONS /[\<\>\,\.\;\&\|\^\!\~\+\-\*\/\%\?\=\:\\]/
  ;

#endif
