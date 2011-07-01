/*
 *  This is a simple filter to typeset Prop code embedded in a LaTeX file.
 *  It recognizes the environment \begin{prop} ... \end{prop} and typesets
 *  everything in the environment as Prop code.  Also, inlined Prop code
 *  can be embedded as in <|...|>.  For example, <| datatype T = ... |>.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

id		[a-zA-Z_][a-zA-Z_0-9]*
c_keywords_1	if|else|while|for|goto|break|case|continue|return
c_keywords_2	volatile|register|auto|static|const|inline
c_keywords_3	struct|class|union|switch|extern|unsigned|signed
c_keywords_4	public|private|protected|virtual
c_keywords	({c_keywords_1}|{c_keywords_2}|{c_keywords_3}|{c_keywords_4})
int		[0-9]+
char		\'([^\'\n]|\\.[0-9a-f]*)\'
real		{int}(\.[0-9]*)?[eE]{int}|{int}\.[0-9]*([eE]{int})?
string		\"([^\"\n]|\\.)*\"
regexp		\/([^\/\n*]|\\.)([^\/\n]|\\.)*\/
pat_var		([\?\#\$]*{id}[\'\?]*|\#\#)
logical_var	\'{id}
back_quoted	\`([^\`]|\\.)*\`
prop_keywords_1	datatype|type|view|collectable|printable|refine|match|matchall
prop_keywords_2	rewrite|inference|sharing|traced|persistent|unifiable|and
prop_keywords_3	where|with|instantiate|finalizable|constraint|syntax
prop_keywords_4 unique|matchscan|sythesized|law|inherited|relation|applicative
prop_keywords	({prop_keywords_1}|{prop_keywords_2}|{prop_keywords_3}|{prop_keywords_4})

keywords	({c_keywords}|{prop_keywords})	

binop1		(\+|\-|\*|\/|\%|\||\&|\^)
binop2		(\&\&|\|\||\=)
unaryop		(\-|\!|\~)
relop		(\>|\<|\>\=|\<\=|\=\=|\!\=)
punct		(\(|\)|\{|\}|\[|\]|\?|;|:|,|\.|\:\:|\-\>|\=\>)
punct2		(\(\||\|\)|\{\||\|\}|\[\||\|\]|\#\(|\#\{|\#\[)
symbols		({binop1}|{binop1}=|{binop2}|{unaryop}|{relop}|{punct}|{punct2})

%S	TeX Prop1 Prop2 Comment1 Comment2

%{

int stack[256];
int top = 0; 
int sc  = 0;
#define PUSH(S) ((stack[top++] = sc), (BEGIN((sc = S))))
#define POP()   (BEGIN((sc = stack[--top])))

#define echo(text) fputs(text,stdout)
#define BEGIN_PROP1 "{\\CF\\begin{tabular}{l}\n"
#define END_PROP1   "\\end{tabular}}"
#define BEGIN_PROP2 "{\\CF "
#define END_PROP2   "}"
#define BEGIN_COMMENT1 "---{\\em "
#define END_COMMENT1   "}\\\\\n"
#define BEGIN_COMMENT2 "\verb./*.{\\em "
#define END_COMMENT2   "}\verb.*/."

void begin_prop1()    { PUSH(Prop1); echo(BEGIN_PROP1); }
void begin_prop2()    { PUSH(Prop2); echo(BEGIN_PROP2); }
void end_prop1()      { POP(); echo(END_PROP1); }
void end_prop2()      { POP(); echo(END_PROP2); }
void begin_comment1() { PUSH(Comment1); echo(BEGIN_COMMENT1); }
void begin_comment2() { PUSH(Comment2); echo(BEGIN_COMMENT2); }
void end_comment1()   { POP(); echo(END_COMMENT1); }
void end_comment2()   { POP(); echo(END_COMMENT2); }

void ident (const char * id)
{  for ( ; *id; id++)
   {  if (*id == '_') echo("\\_"); 
      else            putchar(*id);
   }
}

void math (const char * symbol) { putchar('$'); echo(symbol); putchar('$'); }

void keyword (const char * text) { printf("{\\KW %s}",text); }

void tab (const char * spaces)
{  for ( ;*spaces; spaces++)
   {  if (*spaces == '\t') echo("\\ \\ \\ ");
      else echo("\\ ");
   }
}

void verbatim(const char * text)
{  const char * quotes = ".|!~#$%^&-+=";
   for ( ; *quotes; quotes++)
   {  if (! strchr(text,*quotes))
      {  printf("\\verb%c%s%c",*quotes,text,*quotes); return; }
   }
   fprintf(stderr,"Bad string %s\n", text);
   exit(1);
}

void rule(const char * text)
{  for( ; *text; text++)
     if (*text == '/') echo ("--");
}

%}
%%

<TeX>\\begin\{prop\}[\t ]*\n			{ begin_prop1(); }
<TeX>\\begin\{prop\}				{ begin_prop1(); }
<TeX>\<\|					{ begin_prop2(); }
<TeX>.|\n					{ echo(yytext); }

<Prop1>\\end\{prop\}				{ end_prop1(); }
<Prop2>\|\>					{ end_prop2(); }
<Prop1,Prop2>{keywords}				{ keyword(yytext); }
<Prop1,Prop2,Comment1,Comment2>{string}		{ verbatim(yytext); }
<Prop1,Prop2,Comment1,Comment2>{char}		{ verbatim(yytext); }
<Prop1,Prop2,Comment1,Comment2>\* 		{ math("\\times"); }
<Prop1,Prop2,Comment1,Comment2>\-\>		{ math("\\rightarrow"); }
<Prop1,Prop2,Comment1,Comment2>\=\> 		{ math("\\Rightarrow"); }
<Prop1,Prop2,Comment1,Comment2>\>= 		{ math("\\ge"); }
<Prop1,Prop2,Comment1,Comment2>\<= 		{ math("\\le"); }
<Prop1,Prop2,Comment1,Comment2>\!\= 		{ math("\\ne"); }
<Prop1,Prop2,Comment1,Comment2>\% 		{ math("\\%"); }
<Prop1,Prop2,Comment1,Comment2>\%\= 		{ math("\\%="); }
<Prop1,Prop2,Comment1,Comment2>\^ 		{ math("\\verb.^."); }
<Prop1,Prop2,Comment1,Comment2>\&		{ echo("\\verb.&."); }
<Prop1,Prop2,Comment1,Comment2>\&\&		{ math("\\land"); }
<Prop1,Prop2,Comment1,Comment2>\|\|		{ math("\\lor"); }
<Prop1,Prop2,Comment1,Comment2>\*\= 		{ math("\\times="); }
<Prop1,Prop2,Comment1,Comment2>\#\( 		{ math("\\verb.#.("); }
<Prop1,Prop2,Comment1,Comment2>\#\{ 		{ math("\\verb.#.\{"); }
<Prop1,Prop2,Comment1,Comment2>\#\[ 		{ math("\\verb.#.["); }
<Prop1,Prop2,Comment1,Comment2>\{  		{ math("\\{"); }
<Prop1,Prop2,Comment1,Comment2>\}  		{ math("\\}"); }
<Prop1,Prop2,Comment1,Comment2>{symbols}	{ math(yytext); }
<Prop1,Prop2,Comment1,Comment2>\#		{ echo("\\verb.#."); }
<Prop1,Prop2,Comment1,Comment2>{id}		{ ident(yytext); }
<Prop1,Prop2,Comment2>^[\t ]+			{ tab(yytext); }
<Prop1,Prop2,Comment2>.				{ echo(yytext); }
<Prop1,Prop2>\n					{ echo("\\\\\n"); }
<Prop1,Prop2>\/\/				{ begin_comment1(); }
<Prop1,Prop2>\/\*				{ begin_comment2(); }

<Comment1>\/+\ */\n				{ rule(yytext); end_comment1(); }
<Comment1>\n					{ end_comment1(); }
<Comment2>\*\/					{ end_comment2(); }

%%
#undef yywrap
int yywrap() { return 1; }

int main()
{  printf("\\newfont{\\KW}{cmssbx9}\n"
          "\\newfont{\\CF}{cmssq8}\n");
   PUSH(TeX);
   yylex();
   return 0;
}
