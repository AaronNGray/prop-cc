#include <AD/symbolic/atom.h>

SymbolicAtom:: SymbolicAtom(const char * s) : SymbolicString(s) {}
SymbolicAtom:: SymbolicAtom(const String& s) : SymbolicString(s) {}
SymbolicAtom::~SymbolicAtom() {}
