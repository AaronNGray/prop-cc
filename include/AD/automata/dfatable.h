//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#ifndef prop_basic_definitions_for_compressed_dfa_tables_h
#define prop_basic_definitions_for_compressed_dfa_tables_h

#include <limits>

class DFATables
{
public:
  ///////////////////////////////////////////////////////////////////////////
  //  These are some of the predefined types representing various
  //  quantities:
  //
  //  Rule             --- rule number, usually client defined.
  //  Symbol           --- input symbol, again, usually defined by the client.
  //  Offset           --- this is limited to 16 bits for space efficiency; but
  //                       may rule out extremely large state tables.
  //  State            --- same reasoning.
  //  ProductionLength --- length of a production in a grammar
  ///////////////////////////////////////////////////////////////////////////

  typedef short          Rule;   // A rule number
  typedef int            Symbol; // an input symbol
  typedef short          ShortSymbol;
  typedef short          Offset; // offset in state tables
  typedef unsigned short State;  // a DFA state (maximum states = 65535)
  //   typedef unsigned int State;  // a DFA state (maximum states = 65535)
  typedef unsigned char  ProductionLength;  // length of productions (max 255)
  typedef unsigned short EquivMap; // equivalence class mapping

  ///////////////////////////////////////////////////////////////////////////
  //  Some manifest constants.
  ///////////////////////////////////////////////////////////////////////////
  // const Symbol Min_Symbol = INT_MIN;
  // const Symbol Max_Symbol = INT_MAX;
  // const State error_state = 0;  // the unique error state of the machine

  enum dfatable_constants
  {  error_state = 0,
     Min_Symbol  = -65535 /*INT_MIN */,
     Max_Symbol  = 65535 /*INT_MAX */
  };
};

#endif
