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

#include <AD/automata/acgen.h>

void ACGen::gen_fast_automaton( std::ostream& out, const char class_name[]) const
{
  out << "class " << class_name
  << " : public FastAC {\npublic:\n"
  << "   State go(register State s, register Symbol c) const\n";

  out << "  {  for (;;) {\n      switch(s) {\n";
  register State s;
  register Symbol c;

  for (s = 0; s < number_of_states; s++)
  {
    register Offset offset = base[s];
    out << "        case " << s << ": L_" << s << ": switch(c) {\n";
    for (c = min_symbol; c <= max_symbol; c++)
    {
      if (check[offset + c] == s)
      {
        out << "           case " << c << ": return "
        << next[offset + c] << ";\n";
      }
    }
    out << "           default: goto L_" << epsilon[s] << ";\n"
    << "        }\n";
  }

  out << "      }\n    }\n  }\n};\n";
}
