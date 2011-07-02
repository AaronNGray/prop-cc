///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\visualize.pcc".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/visualize.pcc"
//////////////////////////////////////////////////////////////////////////////
//
//  This file implements the datatype definitions layout generator
//  for visualizing datatype definitions using vcg.
//
//////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <iostream>
#include <strstream>
#include <string>
#include "options.h"
#include "compiler.h"
#include "visualize.h"


//////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor for class PropVisualizer
//
//////////////////////////////////////////////////////////////////////////////

PropVisualizer::PropVisualizer()
    : label_text( text_buffer, sizeof( text_buffer))
    { set_stream( label_text); }

PropVisualizer::~PropVisualizer() {}

va_list PropVisualizer::printer( char fmt, va_list arg)
{
  bug("%LPropVisualizer::printer %%%c", (int)fmt);
  return arg;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to make a label
//
//////////////////////////////////////////////////////////////////////////////

void PropVisualizer::add_label( const char *fmt, ...)
{
  va_list arg;
  va_start( arg, fmt);
  outv( fmt, arg);
  va_end( arg);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Method to make a label.
//
//////////////////////////////////////////////////////////////////////////////

void PropVisualizer::make_label()
{
  label_text << std::ends;
  label( text_buffer);
   // reset buffer
//   label_text.rdbuf()->seekpos(0);
}

//////////////////////////////////////////////////////////////////////////////
//
//  This method takes a stream and prints out all the definitions
//  currently processed as Graph Description Language (GDL).
//
//////////////////////////////////////////////////////////////////////////////

void Compiler::print_definitions_as_GDL()
{
  PropVisualizer v;

  const char * G = "Program definitions";

  v . begin_graph(G);

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Specify the layout format
  //
  ///////////////////////////////////////////////////////////////////////////
  v . label(G)                          // the name of the graph
    . display_edge_labels(true)         // display labels on edges
    . xspace(40)                        // x distance between nodes
    . yspace(40)                        // y distance between nodes
    . layoutalgorithm(VCG::minbackward) // minimize back edges
    . color(VCG::lightblue)             // default color
  ;

  ///////////////////////////////////////////////////////////////////////////
  //
  // Layout datatype definitions
  //
  ///////////////////////////////////////////////////////////////////////////
  v . visualize_datatype_definitions();

  ///////////////////////////////////////////////////////////////////////////
  //
  // Layout type definitions
  //
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //
  // Layout graph type definitions
  //
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  //
  // Finish constructing the graph and print out the entire GDL
  //
  ///////////////////////////////////////////////////////////////////////////
  v . end_graph(G);


  ///////////////////////////////////////////////////////////////////////////
  //
  // Finally output the graph
  //
  ///////////////////////////////////////////////////////////////////////////
  {
    char vcg_file[256];
    strcpy(vcg_file, options.file_prefix);
    strcat(vcg_file, "vcg");
    std::ostream * F = open_output_file(vcg_file);
    msg("[Writing vcg output to %s]\n",vcg_file);
    v . print_GDL_on(*F);
    delete F;
  }
}
#line 133 "../../prop-src/visualize.pcc"
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
