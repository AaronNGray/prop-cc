//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@valis.cs.nyu.edu)
// 1994-1995
//////////////////////////////////////////////////////////////////////////////

#ifndef symbolic_terms_h
#define symbolic_terms_h

#include <AD/symbolic/expr.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SymbolicTerm is a base class for all composite symbolic terms.
//
//////////////////////////////////////////////////////////////////////////////

class SymbolicTerm : public SymbolicExpr
{
protected:
  int             entries;
  SymbolicExpr ** args;

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Constructor, destructor and cloning
  //
  ///////////////////////////////////////////////////////////////////////////

public:
  SymbolicTerm(int);
  SymbolicTerm(int, SymbolicExpr * []);
  virtual ~SymbolicTerm();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Selectors
  //
  ///////////////////////////////////////////////////////////////////////////
  inline int length () const
  {
    return entries;
  }
  inline int size   () const
  {
    return entries;
  }
  inline int arity  () const
  {
    return entries-1;
  }
  inline const SymbolicExpr *  operator [] (int i) const
  {
    return args[i];
  }
  inline       SymbolicExpr *& operator [] (int i)
  {
    return args[i];
  }
  inline const SymbolicExpr *  head () const
  {
    return args[0];
  }
  inline       SymbolicExpr *  head ()
  {
    return args[0];
  }

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Interfaces to a symbolic expression.
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool                 unify (SymbolicExpr *, SymbolicUnifier&) = 0;
  virtual SymbolicExpr *       eval  (SymbolicEnvironment&) const;
  virtual SymbolicExprPrinter& print (SymbolicExprPrinter&) const = 0;
  virtual SymbolicExprReader&  read  (SymbolicExprReader&) = 0;
};

#endif
