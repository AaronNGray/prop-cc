//////////////////////////////////////////////////////////////////////////////
//
//  This file defines the Prop visualizer.  It provides an interface
//  to various low level VCG functionalities.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef prop_visualizer_h
#define prop_visualizer_h

#include <strstream>
#include <AD/visualize/vcg.h>
#include "codegen.h"


//////////////////////////////////////////////////////////////////////////////
//
//  The PropVisualizer class controls datatype layout formats.
//
//////////////////////////////////////////////////////////////////////////////

class PropVisualizer : public VCG, private CodeGen
{
  PropVisualizer (const PropVisualizer&);   // no copy constructor
  void operator = (const PropVisualizer&); // no assignment

private:

  char       text_buffer[1024];
  std::ostrstream label_text;

public:

  PropVisualizer();
  virtual ~PropVisualizer();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Methods to visualize various form of Prop constructs.
  //
  ///////////////////////////////////////////////////////////////////////////
  void visualize_datatype_definitions ();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Methods to make a nice label
  //
  ///////////////////////////////////////////////////////////////////////////
  void add_label   (const char *, ...);
  void make_label  ();
  void add_type    (Id constructor_name, Id label, Ty ty, int anchor);
private:
  va_list printer(char,va_list);
};

#endif
