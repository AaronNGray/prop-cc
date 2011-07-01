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
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1997
//////////////////////////////////////////////////////////////////////////////

#ifndef visualizer_h
#define visualizer_h

#include <AD/generic/generic.h>
#include <stdarg.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Visualizer base class
//
//////////////////////////////////////////////////////////////////////////////

class Visualizer
{
  Visualizer(const Visualizer&);
  operator = (const Visualizer&);

  //////////////////////////////////////////////////////////////////////////
  //
  //  Attribute types
  //
  //////////////////////////////////////////////////////////////////////////

public:
  typedef const char * Label;
  typedef const char * String;
  typedef const struct color * Color;
  typedef const void * Node;
  typedef const void * Graph;
  typedef const struct text_mode * TextMode;
  typedef const struct shape * Shape;

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Predefined constants
  //
  ///////////////////////////////////////////////////////////////////////////

  static Color black, blue, red, green, yellow, magenta, cyan,
  white, darkgrey, darkblue, darkred, darkgreen,
  darkyellow, darkmagneta, darkcyan, gold, lightgrey,
  lightblue, lightred, lightgreen, lightyellow,
  lightmagenta, lightcyan, lilac, turquoise, aquamarine,
  khaki, purple, yellowgreen, pink, orange, orchid;

  static TextMode center, left_justify, right_justify;

  static Shape    box, rhomb, ellispe, triangle;

public:
  Visualizer();
  virtual ~Visualizer();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Create graph objects
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual Visualizer& begin_graph(Graph);
  virtual Visualizer& end_graph();
  virtual Visualizer& begin_node(Node);
  virtual Visualizer& end_node();
  virtual Visualizer& begin_edge(Node, Node);
  virtual Visualizer& end_edge();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Object attributes
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual Visualizer& label(Label);
  virtual Visualizer& color(Color);
  virtual Visualizer& textcolor(Color);
  virtual Visualizer& width(int);
  virtual Visualizer& height(int);
  virtual Visualizer& borderwidth(int);
  virtual Visualizer& x(int);
  virtual Visualizer& y(int);
  virtual Visualizer& folding(int);
  virtual Visualizer& shrink(int);
  virtual Visualizer& stretch(int);
  virtual Visualizer& textmode(TextMode);
  virtual Visualizer& shape(Shape);
  virtual Visualizer& vertical_order(int);
  virtual Visualizer& horizontal_order(int);
  virtual Visualizer& xmax(int);
  virtual Visualizer& ymax(int);
  virtual Visualizer& xbase(int);
  virtual Visualizer& ybase(int);
  virtual Visualizer& xlspace(int);
  virtual Visualizer& yspace(int);
  virtual Visualizer& xlraster(int);
  virtual Visualizer& ylraster(int);
  virtual Visualizer& hidden(int);
  virtual Visualizer& classname(String);
  virtual Visualizer& infoname(String);
  virtual Visualizer& layoutalgorithm(Algorithm);
  virtual Visualizer& layout_downfactor(int);
  virtual Visualizer& layout_upfactor(int);
  virtual Visualizer& layout_nearfactor(int);
  virtual Visualizer& layout_splinefactor(int);
  virtual Visualizer& late_edge_labels(Bool);
  virtual Visualizer& display_edge_labels(Bool);
  virtual Visualizer& dirty_edge_labels(Bool);
  virtual Visualizer& finetuning(Bool);
};

#endif
