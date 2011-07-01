#ifndef tiny_h
#define tiny_h

typedef char Variable;
datatype Value = INT (int) | REAL (double) 
               | BOOL (int) | STRING (char *) | UNDEF
and      Exp   = CONST (Value)
               | BINOP(BinOp,Exp,Exp)
               | VAR (Variable)
and      BinOp = ADD | SUB | MUL | DIV | MOD 
               | EQ | NE | GT | LT | GE | LE
and  Statement = ASSIGN (Variable,Exp)
               | WHILE (Exp, Statement)
               | IF (Exp, Statement, Statement)
               | SEQ (Statement, Statement)
; 

class Env {
   Value store[256];
public:   
   Env() { for (int i = 0; i < 256; i++) store[i] = UNDEF; }
   Value lookup(Variable x) { return store[x]; }
   Env   update(Variable x, Value v) 
      {  Env result = *this; store[x] = v; return result; }
};

extern Env   eval(Statement, Env);
extern Value eval(Exp, Env);

#endif
