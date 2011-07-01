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

#ifndef vcg_visualizer_h
#define vcg_visualizer_h

#include <iostream>
#include <AD/generic/generic.h>
#include <stdarg.h>

class VCG_Internal;


//////////////////////////////////////////////////////////////////////////////
//
//  Visualizer base class
//
//////////////////////////////////////////////////////////////////////////////

class VCG
{
  VCG(const VCG&);
  void operator = (const VCG&);

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
  typedef Node Graph;
  typedef const struct text_mode * TextMode;
  typedef const struct shape * Shape;
  typedef const struct algorithm * Algorithm;
  typedef const struct linestyle * LineStyle;
  typedef const struct arrowstyle * ArrowStyle;
  enum EdgeType { NORMAL_EDGE, BACK_EDGE, NEAR_EDGE, BENT_NEAR_EDGE };

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

  static Shape    box, rhomb, ellipse, triangle;

  static Algorithm maxdepth, mindepth, maxdepthslow, mindepthslow,
  maxdegree, mindegree, maxindegree, minindegree,
  maxoutdegree, minoutdegree, minbackward, dfs, tree;

  static LineStyle continuous, dashed, dotted, invisible;

  static ArrowStyle solid, line, none;

public:
  VCG();
  virtual ~VCG();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Test whether a node/graph or an edge has already been visited.
  //
  ///////////////////////////////////////////////////////////////////////////
  Bool visited(Node) const;
  Bool visited(Node, Node) const;

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Error handling method
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual VCG& error (const char *, ...);

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Create graph objects
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual VCG& begin_graph(Graph);
  virtual VCG& end_graph(Graph);
  virtual VCG& begin_node(Node);
  virtual VCG& end_node(Node);
  virtual VCG& begin_edge(Node, Node, EdgeType = NORMAL_EDGE);
  virtual VCG& end_edge(Node, Node);
  VCG& node(Node);
  VCG& edge(Node, Node, EdgeType = NORMAL_EDGE);
  VCG& begin_backedge(Node, Node);
  VCG& begin_nearedge(Node, Node);
  VCG& begin_bentnearedge(Node, Node);

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Print Graph Description Language(GDL)
  //
  ///////////////////////////////////////////////////////////////////////////
  virtual VCG& print_GDL_on(std::ostream&);

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Object attributes
  //
  ///////////////////////////////////////////////////////////////////////////
  VCG& begin_node_default();
  VCG& begin_edge_default();
  VCG& end_default();
  virtual VCG& attrib(String,String);
  virtual VCG& attrib_quoted(String,String);
  virtual VCG& attrib_int(String,int);
  virtual VCG& attrib_bool(String,Bool);

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Common object attributes
  //
  ///////////////////////////////////////////////////////////////////////////
  VCG& label(Label);
  VCG& label(int);
  VCG& color(Color);
  VCG& textcolor(Color);
  VCG& width(int);
  VCG& height(int);
  VCG& borderwidth(int);
  VCG& x(int);
  VCG& y(int);
  VCG& folding(int);
  VCG& shrink(int);
  VCG& stretch(int);
  VCG& textmode(TextMode);
  VCG& shape(Shape);
  VCG& vertical_order(int);
  VCG& horizontal_order(int);
  VCG& xmax(int);
  VCG& ymax(int);
  VCG& xbase(int);
  VCG& ybase(int);
  VCG& xlspace(int);
  VCG& xspace(int);
  VCG& yspace(int);
  VCG& xlraster(int);
  VCG& ylraster(int);
  VCG& hidden(int);
  VCG& classname(String);
  VCG& infoname(String);
  VCG& layoutalgorithm(Algorithm);
  VCG& layout_downfactor(int);
  VCG& layout_upfactor(int);
  VCG& layout_nearfactor(int);
  VCG& layout_splinefactor(int);
  VCG& late_edge_labels(Bool);
  VCG& display_edge_labels(Bool);
  VCG& dirty_edge_labels(Bool);
  VCG& finetuning(Bool);

  VCG& thickness(int i);
  VCG& linestyle(LineStyle s);
  VCG& arrowstyle(ArrowStyle s);
  VCG& backarrowstyle(ArrowStyle s);
  VCG& arrowsize(int i);
  VCG& backarrowsize(int i);
  VCG& arrowcolor(Color c);
  VCG& backarrowcolor(Color c);
  VCG& priority(int i);
  VCG& anchor(int i);

protected:
  VCG_Internal * impl;
};

#endif
