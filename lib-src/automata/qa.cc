//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the 
// public domain.   The author(s) of this software reserve no copyrights on 
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that 
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in 
// your programs, and that this notice be preserved intact in all the source 
// code.
//
// This software is still under development and we welcome any suggestions 
// and help from the users.
//
// Allen Leung 
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <assert.h>
#include <AD/automata/acgen.h>        // Aho-Corasick automaton
#include <AD/automata/lexergen.h>     // Lexical scanner

int main(int argc, char * argv[])
{
   static const char * grammar[] =
      {  "break", "class", "continue", "do", "for", "goto",
         "if", "struct", "typedef", "union", "while", "return",
         "for", "switch", "case", "else", "default", "public",
         "private", "protected", "virtual", 
         "[0-9]+", "[a-zA-Z_][a-zA-Z0-9_]*", 
         "==", "!=", "\\>", "\\<", "\\>=", "\\<=", "!", "\\(", "\\)",
         ",", ";", "\\+", "-", "\\*", "/", "\\>\\>", "\\<\\<", "~",
         "\\|", "&", "\\|\\|", "&&", "%", "\\.\\.\\.", 
         "\\+=", "-=", "\\*=", "/=", "%=", "\\<\\<=", "\\>\\>=",
         "\\|=", "&="
      };

   LexerGen lex;
   argc--; argv++;
   if (argc > 0) {
      lex.compile(argc,argv);
   } else {
      argv = grammar;
      lex.compile(sizeof(grammar) / sizeof(grammar[0]), grammar);
   }
   if (! lex.ok()) 
      printf("syntax error near rule %d: %s\n",lex.bad(),argv[lex.bad()]);
   // lex.gen_code(std::cout, "lex");

   ACGen ac;
   const struct {
      int           len;
      ACGen::Symbol string[4]; 
   } keywords[] =
   { { 2, { 'h', 'e' } },
     { 3, { 's', 'h', 'e' } },
     { 3, { 'h', 'i', 's' } },
     { 4, { 'h', 'e', 'r', 's' }}
   };
  
   ac.start('a','z');
   for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
      ac.add_string(i,keywords[i].len, keywords[i].string);
   ac.finish();

   ac.gen_code(std::cout, "ac");
   assert(ac.size() == 11);

   printf("OK\n");
   return 0;
}
