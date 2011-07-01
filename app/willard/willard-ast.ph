#ifndef willard_ast_h 
#define willard_ast_h

#include <AD/generic/generic.h>
class PrettyOStream;


struct ConsCounter { static int count; ConsCounter() { count++; } };

datatype List<T> = #[] | #[ T ... List<T> ];
type sharing Bool = bool;

//
//  This is the abstract syntax of the query language
//
datatype Literal = INT int
	         | STRING const char *
	         | BOOL Bool

and      Exp     = OP Id, Exps
   	         | APP Id, Exps
	         | LIT Literal
	         | ID Id
                 | TUPLE Exps                  // [ E1, E2, ... En ]
                 | FORALL Id, Exp, Exp         // forall x in E1 . E2
                 | EXISTS Id, Exp, Exp         // exists x in E1 . E2
		 | GUARD (Exp, Exp)            //
		 | GENERATOR (Ids, Exps, Exp)  // [x_1,...,x_n] in X_1*...*X_n
                 | LET  (Id, Exp, Exp)

law inline Int  i    = LIT(INT i)
|   inline Boolean b = LIT(BOOL b)
|          True      = Boolean true
|          False     = Boolean false
|   inline And a,b   = OP("and",#[a,b])
|   inline Or  a,b   = OP("or", #[a,b])
|   inline Not a     = OP("not",#[a])
|   inline Eq a,b    = OP("=",  #[a,b])
|   inline Ne a,b    = OP("/=", #[a,b])
|   inline Gt a,b    = OP(">",  #[a,b])
|   inline Ge a,b    = OP(">=", #[a,b])
|   inline Lt a,b    = OP("<",  #[a,b])
|   inline Le a,b    = OP("<=", #[a,b])
|   inline In a,b    = OP("in", #[a,b])
|   inline Union a,b = OP("union", #[a,b])
|   inline Count a   = OP("#", #[a])
|   inline Nonempty a = OP("nonempty",#[a])

where type Id         = const char *
and        Ids        = List<Id>
and        Exps       = List<Exp>
;

refine Exp :: rewrite;

refine Literal : ConsCounter;
refine Exp     : ConsCounter;
refine List<T> : ConsCounter;

// Avoid portability problems for now.

// refine Exp :: collectable;
// refine Literal :: collectable;
// refine List<T> :: collectable;

//
//  These are the pretty printing methods
//
extern PrettyOStream& operator << (PrettyOStream&, Exp);
extern PrettyOStream& operator << (PrettyOStream&, Ids);
extern PrettyOStream& operator << (PrettyOStream&, Exps);
extern PrettyOStream& operator << (PrettyOStream&, Literal);

#endif
