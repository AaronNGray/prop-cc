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
#ifndef symbolic_atoms_h
#define symbolic_atoms_h

#include <AD/symbolic/string.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SymbolicAtom represents an atom
//
//////////////////////////////////////////////////////////////////////////////

class SymbolicAtom : public SymbolicString
{
  ///////////////////////////////////////////////////////////////////////////
  //  Constructors, destructor and cloning
  ///////////////////////////////////////////////////////////////////////////

public:
  SymbolicAtom(const char *);
  SymbolicAtom(const String&);
  virtual ~SymbolicAtom();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Interfaces to a symbolic expression.
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual Bool                 unify (SymbolicExpr *, SymbolicUnifier&);
  virtual SymbolicExpr *       eval  (SymbolicEnvironment&) const;
  virtual SymbolicExprPrinter& print (SymbolicExprPrinter&) const;
  virtual SymbolicExprReader&  read  (SymbolicExprReader&);
};

#endif
