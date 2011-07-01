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

#ifndef labeled_tree_for_regular_expressions_h
#define labeled_tree_for_regular_expressions_h

//
// The class |LabeledTree| is used to construct a labeled position
// tree representing a regular expression.  This auxiliary data structure
// is used by the lexical scanner generation algorithm.
//

#include <AD/generic/generic.h>   // Generic definitions

class LabeledTree
{
public:

  //
  // Each leaf node in the labeled tree is marked by a unique ``position''
  // marker, which is basically a positive integer.   To conserve storage,
  // this position type is limited to 2 bytes, in the range of 1 to 65535.
  // Since the number of nodes is also limited to the number of
  // positions, the type |NodeIndex| is also kept to 2-byte number.
  //

  typedef ShortWord Position;   // Position number of labeled tree
  typedef ShortWord NodeIndex;  // Index to a node

  //
  // The following three defined constants are used to annotate a
  // character set in compact form.  In this compact form,
  // character sets are represented as an array of |short|'s linearly.
  // For example, the char set [a-zA-Z] is represented as the array
  //     { 'a' | START_RANGE, 'z', 'A' | START_RANGE, 'Z', END_CHAR_SET }
  // while the set [^allen] is represented as the array
  //     { COMPLEMENT, 'a', 'l', 'l', 'e', 'n', END_CHAR_SET }.
  //
  typedef short Char;

  enum LabTree_constants {
    END_CHAR_SET = -1,     // mark the end of a char set.
    COMPLEMENT   = -2,     // mark the set as complemented.
    START_RANGE  = 256,    // bit to mark the start of range
    ACCEPT       = 256     // Accept state character number
  };

  //
  // The following are the possible types of labeled tree nodes
  //
  enum LabeledTag {
    NODE_CHAR       = 0,    // character node
    NODE_EPSILON    = 1,    // epsilon node, i.e. null string
    NODE_ACCEPT     = 2,    // special node representing an accept state
    NODE_CHAR_CLASS = 3,    // character class node
    NODE_WILD_CARD  = 4,    // node representing a wild card
    NODE_STAR       = 5,    // Kleene star '*'
    NODE_PLUS       = 6,    // non-empty Kleene star '+'
    NODE_APPEND     = 7,    // appending two trees
    NODE_OR         = 8,    // disjunction
    NODE_BEGIN_LINE = 9,    // begin of line matching '^'
    MARKED_NODE     = 16    // marked node for recursive traversal
  };

  //
  // Each node of a labeled tree is represented by the following
  // variant type.  This type should be 8 bytes large on most
  // architectures.
  //
  struct LabNode
  {
    char     tag;              // Type of node; use one byte to save space
    Position pos;              // position number of node
    union {
      unsigned char c;        // character of a delta node
      int accept_rule;        // rule number of accept node
      int char_class;         // index to character class
      NodeIndex child;        // pointer to child of '*' or '+' nodes
      struct
      {
        NodeIndex left, right;   // pointers for append or '|' nodes
      }
      branch;
    } node;
  };

  //
  // The type |Union| defined bellow is a dag structure
  // that represents a finite union of position sets.
  //
  enum UnionType { UNION, SINGLETON };
  struct Union
  {
    UnionType tag;                      // Is it a union or a set
    union {
      Position * set;                   // pointer to a set of positions
      struct
      {
        Union * left, * right;
      }
      u; // union of two sets
    } u;

    Union( Position* set) : tag(SINGLETON)
    {
      u.set = set;
    }

    Union( Union* a, Union* b) : tag(UNION)
    {
      u.u.left = a;
      u.u.right = b;
    }
  };

private:

  //  Information about the labeled tree
  LabNode * tree;              // nodes within a position tree
  LabNode * limit;             // next available node
  LabNode * forest;            // the forest of all rules
  Char ** charsets;            // pointers to character sets
  Char ** next_charset;        // next available character set
  Char * chars;                // contents of character set
  Char * next_chars;           // next available character set array
  Position next_position;      // next available position number

  //  Information concerning the positions
  Char * char_at_position;     // The character or charset at position 'n'
  Bool *  nullable;            // Is the tree at node nullable ?
  int *   first;               // Positions that comes first at node
  int *   last;                // Positions that comes last at node
  int *   follow;              // Positions that can following position 'n'

  Position * position_sets;       //
  Position * next_pos_set;        //
  Position * position_sets_limit; //

  int bad_rule;                // number of the first bad rule

  LabNode * parse_one_rule( int rule_number, const char * pattern);
  void compute_tables();
  Position * expand_sets( Position *);

public:

  LabeledTree( const char * regular_expressions[], int count = -1);
  ~LabeledTree();

  LabNode * root()
  {
    return forest;
  }
  LabNode * child( LabNode * t)
  {
    return tree + t->node.child;
  }
  LabNode * left( LabNode * t)
  {
    return tree + t->node.branch.left;
  }
  LabNode * right( LabNode * t)
  {
    return tree + t->node.branch.right;
  }
  Char * charsetOf( LabNode * t)
  {
    return charsets[t->node.char_class];
  }

  int bad()                      const
  {
    return bad_rule;
  }
  Position number_of_positions() const
  {
    return next_position;
  }

  int compute_equiv_classes( short []);
  void print( const LabNode *);
};

#endif
