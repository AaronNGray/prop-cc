#ifndef logic3_demo_h
#define logic3_demo_h

#include <stdlib.h>
#include <AD/strings/quark.h>

datatype Wff :: rewrite
   = True             
   | False             
   | Var (class Quark)  =>  _
   | Op  (class Quark, Wff, Wff) => "(" 2 1 3 ")"
   | Not (Wff)          => "not(" _ ")"

law 
    inline And(a,b)     = Op(#"and",a,b)
and inline Or(a,b)      = Op(#"or",a,b)
and inline Implies(a,b) = Op(#"->",a, b)
and inline Xor(a,b)     = Op(#"xor",a,b)
and inline Equiv(a,b)   = Op(#"<->",a,b)
;

#endif
