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

#include <AD/automata/gentable.h>

void TablePrinter::print
( std::ostream& out, const char * table, int size, int width,
  const char * type, const char * name, const char * suffix,
  Bool is_unsigned )
{
  int i;
  out << type << name << '_' << suffix << " [ " << size <<" ] = {\n   ";
  for (i = 0; i < size; i++, table += width)
  {
    switch (width)
    {
    case 1:
      if (is_unsigned)
        out << (unsigned int)*((unsigned char*)table);
      else
        out << (int)*table;
      break;
    case 2:
      if (is_unsigned)
        out << (int)*((unsigned short*)table);
      else
        out << (int)*((short *)table);
      break;
    case 4:
      if (is_unsigned)
        out << (unsigned long)*((unsigned long*)table);
      else
        out << (long)*((long *)table);
      break;
    }
    if (i < size - 1)
      out << ", ";
    if ((i & 15) == 15)
      out << "\n   ";
  }
  if ((i & 15) != 0)
    out << '\n';
  out << "};\n";
}
