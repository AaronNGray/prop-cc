#ifndef differential_calculus_h
#define differential_calculus_h

datatype Term = X
              | Int (int)
              | Term + Term
              | Term - Term
              | Term op * Term
              | Term / Term
              | Term ^ Term
public
{   friend Term dx(Term);
    friend Term simplify(Term);
};

#endif
