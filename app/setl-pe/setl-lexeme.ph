#ifndef SETL_lexemes_h
#define SETL_lexemes_h

///////////////////////////////////////////////////////////////////////////////
//  Common lexical aliases are defined as follows.
///////////////////////////////////////////////////////////////////////////////
lexeme digits    = /[0-9]+/
     | sign      = /[\+\-]/
     | integer   = /{sign}?{digits}/
     | exponent  = /[eE]{integer}/
     | mantassa  = /{digits}(\.{digits})?|\.{digits}/
     | real      = /{sign}?{mantassa}{exponent}?/
     | ident     = /[a-zA-Z_][a-zA-Z_0-9]*/
     | string    = /"([^"\n]|\\.)*"/ 
     | character = /'([^'\n]|\\.)*'/
     ;

///////////////////////////////////////////////////////////////////////////////
//  The lexemes of SETL are defined as follows as part of the characteristic
//  of the datatype SETL_Token.  Single character lexemes have been omitted 
//  from the following list since these are implicitly assumed.
///////////////////////////////////////////////////////////////////////////////
datatype SETL_Token :: lexeme 
   = "if"        | "then"      | "else"      | "while"     | "do" 
   | "for"       | "loop"      | "case"      | "of"        
   | "begin"     | "end"       | "exception" | "raise" 
   | "handle"    | "datatype"  | "type"      | "structure" | "struct" 
   | "signature" | "sig"       | "functor"   | "include"   | "open" 
   | "val"       | "fun"       | "sharing"   | "let"       | "local"
   | "in"        | MOD "mod"   | DIV "div"   | ARB "arb"       
   | ARROW "=>"  | ASSIGN ":=" | GE ">="     | LE "<="     | NE "/="       
   | WITH "with" | LESS "less" 
   | INTEGER	/{integer}/      => "<int>"
   | REAL       /{real}/         => "<real>"
   | IDENTIFIER	/{ident}/        => "<id>"
   | STRING     /{string}/       => "<string>"
   | CHARACTER  /{character}/    => "<character>"
   ;

#endif
