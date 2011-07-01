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

#include <stdlib.h>
#include <iostream>
#include <strstream>
#include <AD/visualize/vcg.h>
#include <AD/hash/lhash.h>
#include <AD/memory/strpool.h>
#include <AD/contain/varstack.h>
#include <AD/strings/charesc.h>
#include <AD/pretty/postream.h>

typedef VCG::Color Color;
typedef VCG::TextMode TextMode;
typedef VCG::Shape Shape;
typedef VCG::Algorithm Algorithm;



//////////////////////////////////////////////////////////////////////////////
//
//  Predefined colors
//
//////////////////////////////////////////////////////////////////////////////

VCG::Color  VCG::black          = VCG::Color("black"),
            VCG::blue           = VCG::Color("blue"),
            VCG::red            = VCG::Color("red"),
            VCG::green          = VCG::Color("green"),
            VCG::yellow         = VCG::Color("yellow"),
            VCG::magenta        = VCG::Color("magenta"),
            VCG::cyan           = VCG::Color("cyan"),
            VCG::white          = VCG::Color("white"),
            VCG::darkgrey       = VCG::Color("darkgrey"),
            VCG::darkblue       = VCG::Color("darkblue"),
            VCG::darkred        = VCG::Color("darkred"),
            VCG::darkgreen      = VCG::Color("darkgreen"),
            VCG::darkyellow     = VCG::Color("darkyellow"),
            VCG::darkmagneta    = VCG::Color("darkmagneta"),
            VCG::darkcyan       = VCG::Color("darkcyan"),
            VCG::gold           = VCG::Color("gold"),
            VCG::lightgrey      = VCG::Color("lightgrey"),
            VCG::lightblue      = VCG::Color("lightblue"),
            VCG::lightred       = VCG::Color("lightred"),
            VCG::lightgreen     = VCG::Color("lightgreen"),
            VCG::lightyellow    = VCG::Color("lightyellow"),
            VCG::lightmagenta   = VCG::Color("lightmagenta"),
            VCG::lightcyan      = VCG::Color("lightcyan"),
            VCG::lilac          = VCG::Color("lilac"),
            VCG::turquoise      = VCG::Color("turquoise"),
            VCG::aquamarine     = VCG::Color("aquamarine"),
            VCG::khaki          = VCG::Color("khaki"),
            VCG::purple         = VCG::Color("purple"),
            VCG::yellowgreen    = VCG::Color("yellowgreen"),
            VCG::pink           = VCG::Color("pink"),
            VCG::orange         = VCG::Color("orange"),
            VCG::orchid         = VCG::Color("orchid")
;

//////////////////////////////////////////////////////////////////////////////
//
//  Predefined textmodes
//
//////////////////////////////////////////////////////////////////////////////

VCG::TextMode
      VCG::center        = VCG::TextMode("center"),
      VCG::left_justify  = VCG::TextMode("left_justify"),
      VCG::right_justify = VCG::TextMode("right_justify")
;

//////////////////////////////////////////////////////////////////////////////
//
//  Predefined shapes
//
//////////////////////////////////////////////////////////////////////////////

VCG::Shape
      VCG::box      = VCG::Shape("box"),
      VCG::rhomb    = VCG::Shape("rhomb"),
      VCG::ellipse  = VCG::Shape("ellipse"),
      VCG::triangle = VCG::Shape("triangle")
;

//////////////////////////////////////////////////////////////////////////////
//
//  Predefined algorithms
//
//////////////////////////////////////////////////////////////////////////////

VCG::Algorithm  VCG::maxdepth = VCG::Algorithm("Algorithm  VCG::maxdepth"),
		VCG::mindepth = VCG::Algorithm("mindepth"),
		VCG::maxdepthslow = VCG::Algorithm("maxdepthslow"),
		VCG::mindepthslow = VCG::Algorithm("mindepthslow"),
		VCG::maxdegree = VCG::Algorithm("maxdegree"),
		VCG::mindegree = VCG::Algorithm("mindegree"),
		VCG::maxindegree = VCG::Algorithm("maxindegree"),
		VCG::minindegree = VCG::Algorithm("minindegree"),
	        VCG::maxoutdegree = VCG::Algorithm("maxoutdegree"),
		VCG::minoutdegree = VCG::Algorithm("minoutdegree"),
		VCG::minbackward = VCG::Algorithm("minbackward"),
		VCG::dfs = VCG::Algorithm("dfs"),
		VCG::tree = VCG::Algorithm("tree");

VCG::LineStyle VCG::continuous = VCG::LineStyle("continuous"),
	       VCG::dashed = VCG::LineStyle("dashed"),
	       VCG::dotted = VCG::LineStyle("dotted"),
	       VCG::invisible = VCG::LineStyle("invisible")
;

VCG::ArrowStyle VCG::solid = VCG::ArrowStyle("solid"),
		VCG::line = VCG::ArrowStyle("line"),
		VCG::none = VCG::ArrowStyle("none")
;

//////////////////////////////////////////////////////////////////////////////
//
//  Hashing and equality functions for nodes
//
//////////////////////////////////////////////////////////////////////////////

static int hash(VCG::Node x) { return (int)x; }
static Bool equal(VCG::Node x, VCG::Node y) { return x == y; }

//////////////////////////////////////////////////////////////////////////////
//
//  Internal representation of a node
//
//////////////////////////////////////////////////////////////////////////////

struct VCG_Node
{
  int        title;  // unique node title in VCG
  static int next_title;
  VCG::Node  a;
  Bool       visited;
  VarStack<VCG_Node *> children; // children of node
  VarStack<char *>     attribs;  // attributes of node

  VCG_Node() : a(0), visited(false) {}
  virtual ~VCG_Node() {}
  VCG_Node(VCG::Node n)
     :	title(++next_title),
	    a(n), visited(false),
       children(0), attribs(0) {}
  virtual Bool is_node()  const { return true; }
  virtual Bool is_graph() const { return false; }
  virtual Bool is_edge()  const { return false; }
  virtual PrettyOStream& print_GDL_on(PrettyOStream& f) const;
protected:
  virtual const char * kind() const
     { return children.size() > 0 ? "graph" : "node"; }
  PrettyOStream& print_header(PrettyOStream& f) const;
  PrettyOStream& print_footer(PrettyOStream& f) const;
  PrettyOStream& print_attrib(PrettyOStream& f) const;
  PrettyOStream& print_children(PrettyOStream& f) const;
};

int VCG_Node::next_title = 0;

//////////////////////////////////////////////////////////////////////////////
//
//  Internal representation of
//
//////////////////////////////////////////////////////////////////////////////
struct VCG_Graph : public VCG_Node
{
  VCG_Graph() {}
  VCG_Graph(VCG::Graph n) : VCG_Node(n) {}
  virtual Bool is_node()  const { return false; }
  virtual Bool is_graph() const { return true; }
  virtual Bool is_edge()  const { return false; }
  virtual const char * kind() const { return "graph"; }
  virtual PrettyOStream& print_GDL_on(PrettyOStream& f) const;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Internal representation of an edge
//
//////////////////////////////////////////////////////////////////////////////
struct VCG_Edge : public VCG_Node
{
  VCG::Node b;
  VCG::EdgeType edge_type;
  VCG_Node * src, * dest;
  VCG_Edge() : b(0), src(0), dest(0) {}
  VCG_Edge(VCG::Node x,VCG::Node y, VCG::EdgeType e,
	    VCG_Node * s = 0, VCG_Node * d = 0)
     : VCG_Node(x), b(y), edge_type(e), src(s), dest(d) {}
  friend int hash(const VCG_Edge* a) { return ::hash(a->a) + ::hash(a->b) * 9; }
  friend Bool equal(const VCG_Edge* a, const VCG_Edge* b)
     { return a->a == b->a && a->b == b->b; }
  virtual const char * kind() const { return "edge"; }
  virtual Bool is_node()  const { return false; }
  virtual Bool is_graph() const { return false; }
  virtual Bool is_edge()  const { return true; }
  virtual PrettyOStream& print_GDL_on(PrettyOStream& f) const;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Print GDL on a pretty printing stream
//
//////////////////////////////////////////////////////////////////////////////

PrettyOStream& VCG_Node::print_header(PrettyOStream& f) const
{
  f << tab << kind() << ':' << '{' << newline << indent
    << tab << "title: \"" << nospace << title << nospace << "\"" << newline;
  return f;
}

PrettyOStream& VCG_Node::print_footer(PrettyOStream& f) const
{
  return f << unindent << tab << '}' << newline;
}

PrettyOStream& VCG_Node::print_attrib(PrettyOStream& f) const
{
  foreach (i,attribs)
  {
    const char * text = attribs(i);
    f << tab << text << newline;
  }
  return f;
}

PrettyOStream& VCG_Node::print_children(PrettyOStream& f) const
{
  foreach (i,children) // print nodes
  {
    VCG_Node * node = children(i);
    if (!node->is_edge())
      node->print_GDL_on(f);
  }
  foreach (j,children) // print edges
  {
    VCG_Node * edge = children(j);
    if (edge->is_edge())
      edge->print_GDL_on(f);
  }
  return f;
}

PrettyOStream& VCG_Node::print_GDL_on(PrettyOStream& f) const
{
  print_header(f);
  print_attrib(f);
  print_footer(f);
  return f;
}

PrettyOStream& VCG_Graph::print_GDL_on(PrettyOStream& f) const
{
  print_header(f);
  print_attrib(f);
  print_children(f);
  print_footer(f);
  return f;
}

PrettyOStream& VCG_Edge::print_GDL_on(PrettyOStream& f) const
{
  f << tab;
  switch (edge_type)
  {
    case VCG::NORMAL_EDGE:    f << "edge"; break;
    case VCG::BACK_EDGE:      f << "backedge"; break;
    case VCG::NEAR_EDGE:      f << "nearedge"; break;
    case VCG::BENT_NEAR_EDGE: f << "bentnearedge"; break;
  }
  f << ':' << '{' << newline << indent;
  f << tab << "sourcename: \"" << nospace << src->title
    << nospace << "\"" << newline
    << tab << "targetname: \"" << nospace
    << dest->title << nospace << "\"" << newline;
  print_attrib(f);
  print_children(f);
  print_footer(f);
  return f;
}

//////////////////////////////////////////////////////////////////////////////
//
// Internal representation of VCG
//
//////////////////////////////////////////////////////////////////////////////

class VCG_Internal
{
  VCG_Internal(const VCG_Internal&);
  void operator = (const VCG_Internal&);
public:
  LHashTable<VCG::Node, VCG_Node *> object_table; // table of visited objects
  LHashTable<VCG_Edge *, VCG_Edge *> edge_table; // table of visited edges
  StringPool pool;    // string pool
  VarStack<VCG_Node *> obj_stack; // stack of unresolved objects
  VarStack<VCG_Node *> graph_stack; // stack of graphs
  VCG_Node * root_node;
  const char * default_prefix;

  VCG_Internal() : root_node(0), default_prefix(0) {}
 ~VCG_Internal() { cleanup(); }

  VCG_Node* create_node( VCG::Node n) // create new node
  {
    if (object_table.contains(n))
      return object_table[n];
    VCG_Node * node = new VCG_Node(n);
    object_table.insert(n,node);
    return node;
  }

  VCG_Node* create_graph( VCG::Graph G) // create new graph
  {
    if (object_table.contains(G))
      return object_table[G];
    VCG_Graph * graph = new VCG_Graph(G);
    object_table.insert(G,graph);
    return graph;
  }

  // create new edge
  VCG_Node* create_edge( VCG::Node a, VCG::Node b, VCG::EdgeType e)
  {
    VCG_Edge E(a,b,e);
    VCG_Node * src  = create_node(a);
    VCG_Node * dest = create_node(b);
    Ix i;
    if ((i = edge_table.lookup(&E)))
      return edge_table.value(i);
    VCG_Edge * edge = new VCG_Edge(a,b,e,src,dest);
    return edge;
  }

  void cleanup() // remove all nodes and edges created
  {
    foreach(i,object_table)
      { delete object_table.value(i); }
    foreach(j,edge_table)
      { delete edge_table.value(j); }
  }
};

//////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor
//
//////////////////////////////////////////////////////////////////////////////

VCG::VCG() : impl(new VCG_Internal) {}
VCG::~VCG() { delete impl; }

//////////////////////////////////////////////////////////////////////////////
//
//  Methods to check whether a node or an edge has been visited.
//
//////////////////////////////////////////////////////////////////////////////

Bool VCG::visited(Node n) const
{
  Ix i = impl->object_table.lookup(n);
  if (i == 0) return false;
  return impl->object_table.value(i)->visited;
}
Bool VCG::visited(Node a, Node b) const
{
  VCG_Edge E(a,b,NORMAL_EDGE);
  return impl->edge_table.contains(&E);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Error handling method
//
//////////////////////////////////////////////////////////////////////////////

VCG& VCG::error(const char * message,...)
{
  std::cerr << "VCG error: " << message << '\n';
  exit(1);
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Insert a new graph
//
//////////////////////////////////////////////////////////////////////////////

VCG& VCG::begin_graph(Graph G)
{
  VCG_Node * graph = impl->create_graph(G);
  if (impl->graph_stack.is_empty())
  {
    if (impl->root_node == 0)
      impl->root_node = graph;
  }
  else
  {
    VCG_Node * PG = impl->graph_stack.top();
    PG->children.push(graph);
  }
  impl->graph_stack.push(graph);
  impl->obj_stack.push(graph);
  graph->visited = true;
  return *this;
}

VCG& VCG::end_graph(Graph G)
{
  if (impl->obj_stack.is_empty())
    error("object stack is empty in VCG::end_graph");
  VCG_Node * obj = impl->obj_stack.pop();
  if (obj->is_edge())
    error("expecting VCG::end_graph");
  if (obj->a != G)
    error("mismatch graph in VCG::begin_graph and VCG::end_graph");

  impl->graph_stack.pop(); // pop graph
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Insert a new node
//
//////////////////////////////////////////////////////////////////////////////

VCG& VCG::begin_node(Node n)
{
  if (impl->graph_stack.is_empty())
    error("no graph has been defined in VCG::begin_node");
  VCG_Node * G = impl->graph_stack.top();
  VCG_Node * N = impl->create_node(n);
  N->visited = true;
  G->children.push(N);
  impl->obj_stack.push(N);
  return *this;
}

VCG& VCG::end_node(Node n)
{
  if (impl->obj_stack.is_empty())
    error("object stack is empty in VCG::end_node");
  VCG_Node * obj = impl->obj_stack.pop();
  if (! obj->is_node())
    error("expecting VCG::end_node");
  if (obj->a != n)
    error("mismatch node in VCG::begin_node and VCG::end_node");
  return *this;
}

VCG& VCG::node(Node n) { begin_node(n); end_node(n); return *this; }

//////////////////////////////////////////////////////////////////////////////
//
//  Insert a new edge
//
//////////////////////////////////////////////////////////////////////////////

VCG& VCG::begin_edge(Node a, Node b, EdgeType edgeType)
{
  if (impl->graph_stack.is_empty())
    error("no graph has been defined in VCG::begin_node");
  VCG_Node * G = impl->graph_stack.top();
  VCG_Node * e = impl->create_edge(a,b,edgeType);
  e->visited = true;
  G->children.push(e);
  impl->obj_stack.push(e);
  return *this;
}

VCG& VCG::begin_backedge(Node a, Node b) { return begin_edge(a,b,BACK_EDGE); }
VCG& VCG::begin_nearedge(Node a, Node b) { return begin_edge(a,b,NEAR_EDGE); }
VCG& VCG::begin_bentnearedge(Node a, Node b)
  { return begin_edge(a,b,BENT_NEAR_EDGE); }

VCG& VCG::end_edge(Node a, Node b)
{
  if (impl->obj_stack.is_empty())
    error("object stack is empty in VCG::end_edge");
  VCG_Node * obj = impl->obj_stack.pop();
  if (! obj->is_edge())
    error("expecting VCG::end_edge");
  VCG_Edge * edge = (VCG_Edge*)obj;
  if (edge->a != a || edge->b != b)
    error("mismatch edge in VCG::begin_edge and VCG::end_edge");
  return *this;
}

VCG& VCG::edge(Node a, Node b, EdgeType edgeType)
{
  begin_edge(a,b,edgeType);
  end_edge(a,b);
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Print graph as GDL new graph
//
//////////////////////////////////////////////////////////////////////////////

VCG& VCG::print_GDL_on(std::ostream& f)
{
  if (impl->root_node == 0)
    error("root node has not been defined in VCG::print_GDL_on");
  if (! impl->graph_stack.is_empty())
    error("graph stack is non-empty in VCG::print_GDL_on");
  if (! impl->obj_stack.is_empty())
    error("object stack is non-empty in VCG::print_GDL_on");
  PrettyOStream S(f);
  impl->root_node->print_GDL_on(S);
  return *this;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Insert attributes
//
//////////////////////////////////////////////////////////////////////////////

VCG& VCG::begin_node_default() { impl->default_prefix = "node."; return *this; }
VCG& VCG::begin_edge_default() { impl->default_prefix = "edge."; return *this; }
VCG& VCG::end_default()        { impl->default_prefix = 0; return *this; }

VCG& VCG::attrib(VCG::String name, VCG::String attrib)
{
  if (impl->obj_stack.is_empty())
    error("object stack is empty in VCG::attrib");
  VCG_Node * obj = impl->obj_stack.top();
  char buffer[4096];
  buffer[0] = '\0';
  if (impl->default_prefix)
    strcpy(buffer,impl->default_prefix);
  strcat(buffer,name);
  strcat(buffer,": ");
  strcat(buffer,attrib);
  char * new_attr = impl->pool[buffer];
  obj->attribs.push(new_attr);
  return *this;
}

VCG& VCG::attrib_quoted(VCG::String name, VCG::String s)
{
  char buffer[4096];
  buffer[0] = '"';
  char * p = quote_string(buffer+1,s);
  p[0] = '"';
  p[1] = '\0';
  attrib(name,buffer);
  return *this;
}

VCG& VCG::attrib_int(VCG::String name, int i)
{
  char buffer[256];
  std::ostrstream S(buffer,sizeof(buffer));
  S << i << std::ends;
  attrib(name,S.str());
  return *this;
}

VCG& VCG::attrib_bool(VCG::String name, Bool b)
{
  return attrib(name,b ? "yes" : "no");
}

//////////////////////////////////////////////////////////////////////////////
//
//  Common attributes
//
//////////////////////////////////////////////////////////////////////////////

VCG& VCG::label(Label l)       { return attrib_quoted("label", l); }
VCG& VCG::label(int i)
{
  char buffer[256];
  std::ostrstream S(buffer,sizeof(buffer));
  S << i << std::ends;
  return label(S.str());
}

VCG& VCG::color(Color c)       { return attrib("color",String(c)); }
VCG& VCG::textcolor(Color c)   { return attrib("textcolor",String(c)); }
VCG& VCG::textmode(TextMode m) { return attrib("textmode",String(m)); }
VCG& VCG::shape(Shape s)       { return attrib("shape",String(s)); }
VCG& VCG::width(int i)         { return attrib_int("width",i); }
VCG& VCG::height(int i)        { return attrib_int("heigth",i); }
VCG& VCG::borderwidth(int i)   { return attrib_int("borderwidth",i); }
VCG& VCG::x(int i)             { return attrib_int("x", i); }
VCG& VCG::y(int i)             { return attrib_int("y", i); }
VCG& VCG::folding(int i)          { return attrib_int("folding", i); }
VCG& VCG::shrink(int i)           { return attrib_int("shrink", i); }
VCG& VCG::stretch(int i)          { return attrib_int("stretch", i); }
VCG& VCG::vertical_order(int i)   { return attrib_int("vertical_order",i); }
VCG& VCG::horizontal_order(int i) { return attrib_int("horizontal_order",i); }
VCG& VCG::xmax(int i)             { return attrib_int("xmax",i); }
VCG& VCG::ymax(int i)             { return attrib_int("ymax",i); }
VCG& VCG::xbase(int i)            { return attrib_int("xbase",i); }
VCG& VCG::ybase(int i)            { return attrib_int("ybase",i); }
VCG& VCG::xlspace(int i)          { return attrib_int("xlspace",i); }
VCG& VCG::xspace(int i)           { return attrib_int("xspace",i); }
VCG& VCG::yspace(int i)           { return attrib_int("yspace",i); }
VCG& VCG::xlraster(int i)         { return attrib_int("xlraster",i); }
VCG& VCG::ylraster(int i)         { return attrib_int("ylraster",i); }
VCG& VCG::hidden(int i)           { return attrib_int("hidden",i); }
VCG& VCG::classname(String s)     { return attrib_quoted("classname",s); }
VCG& VCG::infoname(String s)      { return attrib_quoted("infoname",s); }
VCG& VCG::layoutalgorithm(Algorithm a) { return attrib("layoutalgorithm",String(a)); }
VCG& VCG::layout_downfactor(int i)  { return attrib_int("layout_downfactor",i); }
VCG& VCG::layout_upfactor(int i)    { return attrib_int("layout_upfactor",i); }
VCG& VCG::layout_nearfactor(int i)  { return attrib_int("layout_nearfactor",i); }
VCG& VCG::layout_splinefactor(int i){ return attrib_int("layout_splinefactor",i); }

VCG& VCG::late_edge_labels(Bool i)
  { return attrib_bool("late_edge_labels",i); }
VCG& VCG::display_edge_labels(Bool i)
  { return attrib_bool("display_edge_labels",i); }
VCG& VCG::dirty_edge_labels(Bool i)
  { return attrib_bool("dirty_edge_labels",i); }
VCG& VCG::finetuning(Bool i)
  { return attrib_bool("finetuning",i); }

VCG& VCG::thickness(int i) { return attrib_int("thickness",i); }
VCG& VCG::linestyle(LineStyle s) { return attrib("linestyle",String(s)); }
VCG& VCG::arrowstyle(ArrowStyle s) { return attrib("arrowstyle",String(s)); }
VCG& VCG::backarrowstyle(ArrowStyle s)
  { return attrib("backarrowstyle",String(s)); }
VCG& VCG::arrowsize(int i) { return attrib_int("arrowsize",i); }
VCG& VCG::backarrowsize(int i) { return attrib_int("backarrowsize",i); }
VCG& VCG::arrowcolor(Color c) { return attrib("arrowcolor",String(c)); }
VCG& VCG::backarrowcolor(Color c)
   { return attrib("backarrowcolor",String(c)); }
VCG& VCG::priority(int i) { return attrib_int("priority",i); }
VCG& VCG::anchor(int i) { return attrib_int("anchor",i); }
