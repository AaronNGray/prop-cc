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

#ifndef graph_object_h
#define graph_object_h

#include <AD/graph/graph_base.h>
#include <AD/graph/node.h>

//////////////////////////////////////////////////////////////////////////////
//
//  A node set object
//
//////////////////////////////////////////////////////////////////////////////

class NodeSet
{
  NodeObject ** my_nodes;
  int           my_capacity;
  int           my_size;

public:
  NodeSet();
  NodeSet(const NodeSet&);
  ~NodeSet();

  void operator = (const NodeSet&);

  int size() const
  {
    return my_size;
  }
  Bool is_empty () const
  {
    return my_size == 0;
  }
  const NodeObject * operator [] (int i) const
  {
    return my_nodes[i];
  }
  NodeObject * operator [] (int i)
  {
    return my_nodes[i];
  }

  class iterator
  {
    NodeSet& node_set;
    int i;
  public:
    iterator(NodeSet& S) : node_set(S), i(0)
    {}
    iterator(iterator& iter) : node_set(iter.node_set), i(iter.i)
    {}
    NodeObject * operator * ()
    {
      return node_set[i];
    }
    NodeObject * operator -> ()
    {
      return node_set[i];
    }
    operator Bool () const
    {
      return node_set.size() >= i;
    }
    void operator ++ ()
    {
      ++i;
    }
    void operator ++ (int)
    {
      ++i;
    }
  };

private:
  friend class GraphObject;
  friend class iterator;

  void add_node (NodeObject *);

  Bool contains (int) const;
  void grow(int i);
};

//////////////////////////////////////////////////////////////////////////////
//
//  An edge set object
//
//////////////////////////////////////////////////////////////////////////////

class EdgeSet
{
  EdgeObject ** my_edges;
  int           my_capacity;
  int           my_size;
public:
  EdgeSet();
  EdgeSet(const EdgeSet&);
  ~EdgeSet();

  void operator = (const EdgeSet&);

  int size() const
  {
    return my_size;
  }
  Bool is_empty () const
  {
    return my_size == 0;
  }
  const EdgeObject * operator [] (int i) const
  {
    return my_edges[i];
  }
  EdgeObject * operator [] (int i)
  {
    return my_edges[i];
  }

  class iterator
  {
    EdgeSet& edge_set;
    int i;
  public:
    iterator(EdgeSet& S) : edge_set(S), i(0)
    {}
    iterator(iterator& iter) : edge_set(iter.edge_set), i(iter.i)
    {}
    EdgeObject * operator * ()
    {
      return edge_set[i];
    }
    EdgeObject * operator -> ()
    {
      return edge_set[i];
    }
    operator Bool () const
    {
      return edge_set.size() >= i;
    }
    void operator ++ ()
    {
      ++i;
    }
    void operator ++ (int)
    {
      ++i;
    }
  };

private:
  friend class GraphObject;
  friend class iterator;

  void add_edge (EdgeObject *);
  void grow(int i);
};

//////////////////////////////////////////////////////////////////////////////
//
//  An adjlist object
//
//////////////////////////////////////////////////////////////////////////////

class AdjList
{
  AdjList(const AdjList&);
  void operator = (const AdjList&);

  EdgeSet ** my_edge_sets;
  int        my_capacity;
  int        my_size;

public:
  AdjList();
  ~AdjList();

  int size() const
  {
    return my_size;
  }
  Bool is_empty () const
  {
    return my_size == 0;
  }

private:
  friend class GraphObject;

  const EdgeSet * operator [] (const NodeObject * node) const
  {
    return my_edge_sets[node->label_num()];
  }
  EdgeSet * operator [] (const NodeObject * node);
  void add_node (NodeObject *);
  void grow(int i);
};


//////////////////////////////////////////////////////////////////////////////
//
//  A graph object
//
//////////////////////////////////////////////////////////////////////////////

class GraphObject
{
public:
  typedef NodeObject::Label NodeLabel;

protected:
  Mem&         mem;                // internal memory manager
  NodeLabel    next_label;         // next available label
  int          number_of_nodes;    // number of nodes
  int          number_of_edges;    // number of edges
  NodeSet      node_set;           // set of nodes
  AdjList      pred_map;           // predecessor map
  AdjList      succ_map;           // successor map

private:
  void init();       // initialization and cleanup
  void cleanup();
public:

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Constructors and destructors
  //
  ///////////////////////////////////////////////////////////////////////////
  GraphObject();
  GraphObject(const GraphObject&);
  GraphObject(Mem&);
  virtual ~GraphObject();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Get a new label for a node
  //
  ///////////////////////////////////////////////////////////////////////////
  NodeLabel get_label();

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Selectors
  //
  ///////////////////////////////////////////////////////////////////////////

  int order() const
  {
    return number_of_edges;
  }
  int size() const
  {
    return number_of_nodes;
  }
  Bool is_empty() const
  {
    return number_of_nodes == 0;
  }
  int out_degree( NodeObject * node) const
  {
    return succ_map[node]->size();
  }
  int in_degree( NodeObject * node) const
  {
    return pred_map[node]->size();
  }
  Bool is_sink( NodeObject * node) const
  {
    return out_degree(node) == 0;
  }
  Bool is_source( NodeObject * node) const
  {
    return in_degree(node) == 0;
  }
  EdgeSet& out_edges( NodeObject * node)
  {
    return *succ_map[node];
  }
  EdgeSet& in_edges( NodeObject * node)
  {
    return *pred_map[node];
  }
  const EdgeSet& out_edges( NodeObject * node) const
  {
    return *succ_map[node];
  }
  const EdgeSet& in_edges( NodeObject * node) const
  {
    return *pred_map[node];
  }
  NodeSet& nodes()
  {
    return node_set;
  }
  const NodeSet& nodes() const
  {
    return node_set;
  }

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Mutators
  //
  ///////////////////////////////////////////////////////////////////////////

  void clear();                          // remove all edges and nodes
  void clear_edges();                    // remove all edges
  void operator = (const GraphObject&);  // copy a graph
  void operator += (const GraphObject&); // add a subgraph
  GraphObject& operator += (NodeObject *); // add a node
  GraphObject& operator += (EdgeObject *); // add an edge
  GraphObject& operator -= (NodeObject *); // remove a node
  //   (and all incident edges)
  GraphObject& operator -= (EdgeObject *); // remove an edge

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Pretty printing methods
  //
  ///////////////////////////////////////////////////////////////////////////

  friend PrettyOStream& operator << (PrettyOStream&, const GraphObject&);
  friend PrettyIStream& operator >> (PrettyIStream&, GraphObject&);

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Node iterator base class
  //
  ///////////////////////////////////////////////////////////////////////////

  class node_iterator
  {
    GraphObject * graph;
    NodeObject ** node_list;
    int           node_count;
    int           index;

  public:
    node_iterator(GraphObject& G);
    node_iterator(node_iterator&);
    ~node_iterator();

    void operator = (node_iterator&);

    int size() const
    {
      return node_count;
    }

    void set_pos(int i)
    {
      index = i;
    }
    void set_first()
    {
      index = 0;
    }
    void set_last()
    {
      index = node_count - 1;
    }

    operator Bool () const
    {
      return index > 0 && index < node_count;
    }

    NodeObject* operator * ()
    {
      return node_list[index];
    }
    const NodeObject * operator * () const
    {
      return node_list[index];
    }
    NodeObject* operator -> ()
    {
      return node_list[index];
    }
    const NodeObject * operator -> () const
    {
      return node_list[index];
    }

    NodeObject* operator [] (int i)
    {
      return node_list[i];
    }
    const NodeObject* operator [] (int i) const
    {
      return node_list[i];
    }

    void operator ++ ()
    {
      ++index;
    }
    void operator ++ (int)
    {
      ++index;
    }
    void operator -- ()
    {
      --index;
    }
    void operator -- (int)
    {
      --index;
    }
  };

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Edge iterator base class
  //
  ///////////////////////////////////////////////////////////////////////////
  class edge_iterator
  {
    GraphObject * graph;
    EdgeObject ** edge_list;
    int           edge_count;
    int           index;

  public:
    edge_iterator(GraphObject& G);
    edge_iterator(node_iterator&);
    ~edge_iterator();

    void operator = (edge_iterator&);

    int size() const
    {
      return edge_count;
    }

    void set_pos(int i)
    {
      index = i;
    }
    void set_first()
    {
      index = 0;
    }
    void set_last()
    {
      index = edge_count - 1;
    }

    operator Bool () const
    {
      return index > 0 && index < edge_count;
    }

    EdgeObject* operator * ()
    {
      return edge_list[index];
    }
    const EdgeObject* operator * () const
    {
      return edge_list[index];
    }
    EdgeObject* operator -> ()
    {
      return edge_list[index];
    }
    const EdgeObject* operator -> () const
    {
      return edge_list[index];
    }

    EdgeObject* operator [] (int i)
    {
      return edge_list[i];
    }
    const EdgeObject* operator [] (int i) const
    {
      return edge_list[i];
    }

    void operator ++ ()
    {
      ++index;
    }
    void operator ++ (int)
    {
      ++index;
    }
    void operator -- ()
    {
      --index;
    }
    void operator -- (int)
    {
      --index;
    }
  };

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Depth first search
  //
  ///////////////////////////////////////////////////////////////////////////

class dfs_iterator : public node_iterator
  {
  public:
    dfs_iterator(GraphObject& G);
    dfs_iterator(dfs_iterator&);
    ~dfs_iterator();
    void operator = (dfs_iterator&);
  private:
    void init();
  };

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Postfix depth first search
  //
  ///////////////////////////////////////////////////////////////////////////

class post_dfs_iterator : public node_iterator
  {
  public:
    post_dfs_iterator(GraphObject& G);
    post_dfs_iterator(post_dfs_iterator&);
    ~post_dfs_iterator();
    void operator = (post_dfs_iterator&);
  private:
    void init();
  };

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Breath first search
  //
  ///////////////////////////////////////////////////////////////////////////

class bfs_iterator : public node_iterator
  {
  public:
    bfs_iterator(GraphObject& G);
    bfs_iterator(bfs_iterator&);
    ~bfs_iterator();
    void operator = (bfs_iterator&);
  private:
    void init();
  };

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Postfix breath first search
  //
  ///////////////////////////////////////////////////////////////////////////

class post_bfs_iterator : public node_iterator
  {
  public:
    post_bfs_iterator(GraphObject& G);
    post_bfs_iterator(bfs_iterator&);
    ~post_bfs_iterator();
    void operator = (post_bfs_iterator&);
  private:
    void init();
  };

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Node filter class
  //
  ///////////////////////////////////////////////////////////////////////////

class node_filter : public node_iterator
  {
    typedef Bool (*Filter)(NodeObject *);
    node_iterator& iter;
    Filter f;
  public:
    node_filter(Filter, node_iterator&);
    node_filter(node_filter&);
    ~node_filter();
    void operator = (node_filter&);
  private:
    void init();
  };

  ///////////////////////////////////////////////////////////////////////////
  //
  //  Edge filter class
  //
  ///////////////////////////////////////////////////////////////////////////

class edge_filter : public edge_iterator
  {
    typedef Bool (*Filter)(EdgeObject *);
    edge_iterator& iter;
    Filter f;
  public:
    edge_filter(Filter, edge_iterator&);
    edge_filter(edge_filter&);
    ~edge_filter();
    void operator = (node_filter&);
  private:
    void init();
  };

protected:
  virtual PrettyOStream& print (PrettyOStream&) const;

private:
  friend class node_iterator;
  friend class edge_iterator;
  friend class dfs_iterator;
  friend class post_dfs_iterator;
  friend class bfs_iterator;
  friend class post_bfs_iterator;
  friend class node_filter;
  friend class edge_filter;
};

#endif
