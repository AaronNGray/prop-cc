///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\timespace.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/timespace.ph"
///////////////////////////////////////////////////////////////////////////////
//
//  This file describes the structure of the time and space complexity
//  datatypes.  These datatypes are used to represent time and space
//  complexity in the SETL-like extension language.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef time_and_space_complexity_h
#define time_and_space_complexity_h

#include <iostream>
#include "basics.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Forward type declaration
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Complexity expression is represented by the datatype Complexity.
//
///////////////////////////////////////////////////////////////////////////////

#line 28 "../../prop-src/timespace.ph"
#line 55 "../../prop-src/timespace.ph"
///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Complexity
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Complexity_defined
#define datatype_Complexity_defined
  class a_Complexity;
  typedef a_Complexity * Complexity;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Time
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Time_defined
#define datatype_Time_defined
  class a_Time;
  typedef a_Time * Time;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Forward class definition for Space
//
///////////////////////////////////////////////////////////////////////////////
#ifndef datatype_Space_defined
#define datatype_Space_defined
  class a_Space;
  typedef a_Space * Space;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Base class for datatype Complexity
//
///////////////////////////////////////////////////////////////////////////////
class a_Complexity : public MEM {
public:
  enum Tag_Complexity {
    tag_Var = 0, tag_Add = 1, tag_Mul = 2, 
    tag_Div = 3, tag_Power = 4, tag_Log = 5, 
    tag_Const = 6, tag_BigOh = 7, tag_Omega = 8, 
    tag_LittleOh = 9
  };

public:
  const Tag_Complexity tag__; // variant tag
protected:
  inline a_Complexity(Tag_Complexity t__) : tag__(t__) {}
public:
};
inline int boxed(const a_Complexity *) { return 1; }
inline int untag(const a_Complexity * x) { return x->tag__; }
///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Var
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Var : public a_Complexity {
public:
#line 28 "../../prop-src/timespace.ph"
  Id Var; 
  inline Complexity_Var (Id x_Var)
   : a_Complexity(tag_Var), Var(x_Var)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Add
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Add : public a_Complexity {
public:
#line 30 "../../prop-src/timespace.ph"
  Complexity _1; Complexity _2; 
  inline Complexity_Add (Complexity x_1, Complexity x_2)
   : a_Complexity(tag_Add), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Mul
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Mul : public a_Complexity {
public:
#line 31 "../../prop-src/timespace.ph"
  Complexity _1; Complexity _2; 
  inline Complexity_Mul (Complexity x_1, Complexity x_2)
   : a_Complexity(tag_Mul), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Div
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Div : public a_Complexity {
public:
#line 32 "../../prop-src/timespace.ph"
  Complexity _1; Complexity _2; 
  inline Complexity_Div (Complexity x_1, Complexity x_2)
   : a_Complexity(tag_Div), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Power
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Power : public a_Complexity {
public:
#line 33 "../../prop-src/timespace.ph"
  Complexity _1; Complexity _2; 
  inline Complexity_Power (Complexity x_1, Complexity x_2)
   : a_Complexity(tag_Power), _1(x_1), _2(x_2)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Log
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Log : public a_Complexity {
public:
#line 34 "../../prop-src/timespace.ph"
  Complexity Log; 
  inline Complexity_Log (Complexity x_Log)
   : a_Complexity(tag_Log), Log(x_Log)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Const
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Const : public a_Complexity {
public:
#line 35 "../../prop-src/timespace.ph"
  double Const; 
  inline Complexity_Const (double x_Const)
   : a_Complexity(tag_Const), Const(x_Const)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::BigOh
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_BigOh : public a_Complexity {
public:
#line 36 "../../prop-src/timespace.ph"
  Complexity BigOh; 
  inline Complexity_BigOh (Complexity x_BigOh)
   : a_Complexity(tag_BigOh), BigOh(x_BigOh)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::Omega
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_Omega : public a_Complexity {
public:
#line 37 "../../prop-src/timespace.ph"
  Complexity Omega; 
  inline Complexity_Omega (Complexity x_Omega)
   : a_Complexity(tag_Omega), Omega(x_Omega)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Complexity::LittleOh
//
///////////////////////////////////////////////////////////////////////////////
class Complexity_LittleOh : public a_Complexity {
public:
#line 38 "../../prop-src/timespace.ph"
  Complexity LittleOh; 
  inline Complexity_LittleOh (Complexity x_LittleOh)
   : a_Complexity(tag_LittleOh), LittleOh(x_LittleOh)
  {
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Complexity
//
///////////////////////////////////////////////////////////////////////////////
inline a_Complexity * Var (Id x_Var)
{
  return new Complexity_Var (x_Var);
}
inline a_Complexity * Add (Complexity x_1, Complexity x_2)
{
  return new Complexity_Add (x_1, x_2);
}
inline a_Complexity * Mul (Complexity x_1, Complexity x_2)
{
  return new Complexity_Mul (x_1, x_2);
}
inline a_Complexity * Div (Complexity x_1, Complexity x_2)
{
  return new Complexity_Div (x_1, x_2);
}
inline a_Complexity * Power (Complexity x_1, Complexity x_2)
{
  return new Complexity_Power (x_1, x_2);
}
inline a_Complexity * Log (Complexity x_Log)
{
  return new Complexity_Log (x_Log);
}
inline a_Complexity * Const (double x_Const)
{
  return new Complexity_Const (x_Const);
}
inline a_Complexity * BigOh (Complexity x_BigOh)
{
  return new Complexity_BigOh (x_BigOh);
}
inline a_Complexity * Omega (Complexity x_Omega)
{
  return new Complexity_Omega (x_Omega);
}
inline a_Complexity * LittleOh (Complexity x_LittleOh)
{
  return new Complexity_LittleOh (x_LittleOh);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Complexity
//
///////////////////////////////////////////////////////////////////////////////
inline Complexity_Var * _Var(const a_Complexity * _x_) { return (Complexity_Var *)_x_; }
inline Complexity_Add * _Add(const a_Complexity * _x_) { return (Complexity_Add *)_x_; }
inline Complexity_Mul * _Mul(const a_Complexity * _x_) { return (Complexity_Mul *)_x_; }
inline Complexity_Div * _Div(const a_Complexity * _x_) { return (Complexity_Div *)_x_; }
inline Complexity_Power * _Power(const a_Complexity * _x_) { return (Complexity_Power *)_x_; }
inline Complexity_Log * _Log(const a_Complexity * _x_) { return (Complexity_Log *)_x_; }
inline Complexity_Const * _Const(const a_Complexity * _x_) { return (Complexity_Const *)_x_; }
inline Complexity_BigOh * _BigOh(const a_Complexity * _x_) { return (Complexity_BigOh *)_x_; }
inline Complexity_Omega * _Omega(const a_Complexity * _x_) { return (Complexity_Omega *)_x_; }
inline Complexity_LittleOh * _LittleOh(const a_Complexity * _x_) { return (Complexity_LittleOh *)_x_; }

///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Time::TIME
//
///////////////////////////////////////////////////////////////////////////////
class a_Time : public MEM {
public:
#line 46 "../../prop-src/timespace.ph"
  Complexity TIME; 
  inline a_Time (Complexity x_TIME)
   : TIME(x_TIME)
  {
  }
};
inline int boxed(const a_Time *) { return 1; }
inline int untag(const a_Time *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Time
//
///////////////////////////////////////////////////////////////////////////////
inline a_Time * TIME (Complexity x_TIME)
{
  return new a_Time (x_TIME);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Time
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Class for datatype constructor Space::SPACE
//
///////////////////////////////////////////////////////////////////////////////
class a_Space : public MEM {
public:
#line 54 "../../prop-src/timespace.ph"
  Complexity SPACE; 
  inline a_Space (Complexity x_SPACE)
   : SPACE(x_SPACE)
  {
  }
};
inline int boxed(const a_Space *) { return 1; }
inline int untag(const a_Space *) { return 0; }
///////////////////////////////////////////////////////////////////////////////
//
// Datatype constructor functions for Space
//
///////////////////////////////////////////////////////////////////////////////
inline a_Space * SPACE (Complexity x_SPACE)
{
  return new a_Space (x_SPACE);
}
///////////////////////////////////////////////////////////////////////////////
//
// Downcasting functions for Space
//
///////////////////////////////////////////////////////////////////////////////


#line 55 "../../prop-src/timespace.ph"
#line 55 "../../prop-src/timespace.ph"


///////////////////////////////////////////////////////////////////////////////
//
//  Pretty printing routines.
//
///////////////////////////////////////////////////////////////////////////////

extern std::ostream& operator << (std::ostream&, Complexity);
extern std::ostream& operator << (std::ostream&, Time);
extern std::ostream& operator << (std::ostream&, Space);

///////////////////////////////////////////////////////////////////////////////
//
//  Functions to simplify and manipulate complexity expressions.
//
///////////////////////////////////////////////////////////////////////////////

extern Complexity simplify( Complexity);

#endif
#line 76 "../../prop-src/timespace.ph"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
