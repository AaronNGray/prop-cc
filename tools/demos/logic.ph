#ifndef logic_h
#define logic_h

//
//  This file defines a simple tree structure Wff representing a 
// well-formed formula in proposition calculus
//

typedef int Bool;
#define false 0
#define true  1

datatype Wff =  falsity       
             |  truth            
             |  prop (char)       // a proposition with a single character name
             |  disj(Wff, Wff)    // disjunction
             |  conj(Wff, Wff)    // conjunction
             |  implies(Wff, Wff) // implication
             |  not (Wff)         // negation
public:
{
   friend Bool eval(const Wff, const Bool []);  // Evaluate a wff
   friend Wff  simplify(Wff);                   // Simplify a wff
};

#endif
