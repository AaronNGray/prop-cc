// Test some lexer stuff

#include <stdio.h>
#include <assert.h>
#include <AD/automata/acgen.h>        // Aho-Corasick automaton
#include <AD/automata/lexergen.h>     // Lexical scanner

int main(int argc, const char * argv[])
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
   // lex.gen_code(cout, "lex");

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

   ac.gen_code(cout, "ac");
   assert(ac.size() == 11);

   printf("OK\n");
   return 0;
}
