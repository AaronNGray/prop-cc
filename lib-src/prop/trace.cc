#include <iostream>
#include <AD/generic/generic.h>


Bool trace_enabled = true;

void prop_trace( const char * rule, const char * file_name, int line_number)
{
  if (trace_enabled)
    std::cerr << "\"" << file_name << "\", line " << line_number
         << ": " << rule << "\n" << std::flush;
}
