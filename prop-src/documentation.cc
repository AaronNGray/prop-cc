///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\documentation.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_PARSER_USED
#include <propdefs.h>
#line 1 "../../prop-src/documentation.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//  This file implements the source documentation features.
//
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>
#include "parser.h"

void PropParser::emit_doc()
{
  doc.emit(lexbuf.text(), lexbuf.length());
}
#line 15 "../../prop-src/documentation.pcc"
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
