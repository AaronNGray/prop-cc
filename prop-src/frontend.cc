#include <iostream>
#include "basics.h"
#include "parser.h"


void front_end(const char * input_file_name, Compiler& C)
{
  PropParser P;
  extern Decls program;
  P.initialize(C);
  P.initialize_lexer(input_file_name);
  P.parse();
  P.cleanup_lexer();
  program = P.program;
}
