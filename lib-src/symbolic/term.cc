#include <AD/symbolic/term.h>

SymbolicTerm:: SymbolicTerm(int i)
   : entries(i), args(new SymbolicExpr * [i]) {}

SymbolicTerm:: SymbolicTerm(int i, SymbolicExpr * a[])
   : entries(i), args(new SymbolicExpr * [i])
   { for (int j = 0; j < i; j++) args[j] = a[j]; }

SymbolicTerm::~SymbolicTerm() { delete [] args; }
