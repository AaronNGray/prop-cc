#include <iostream.h>
#include <assert.h>
#include <AD/gc/gc.h>
#include <AD/gc/markswp.h>
#include <AD/gc/bgc.h>
#include <AD/gc/gcobject.h>
#include <AD/gc/gcheaps.h>

#define TRIALS 50   // number of times to test
#define DEPTH  6   // depth of the tree
#define JUNKSIZE 500
//#define JUNKSIZE 2000

MarkSweepGC heap1;
BGC heap2;
BGC& heap3 = bgc;

class TREE : public GCObject {
  static int tagcnt;
  int    tag;
  int    junk[JUNKSIZE];
public:
  TREE * left_child;
  TREE * right_child;
  TREE(TREE * l, TREE * r) : left_child(l), right_child(r)
  {
    tag = 0;
    tag = tagcnt;
    tagcnt += 5*JUNKSIZE+17;
    for (int i = 0; i < JUNKSIZE; i++) junk[i] = i + tag;
  }
  ~TREE() {}
  void verify() const
  { int i;
    for (i = 0; i < JUNKSIZE; i++) assert(junk[i] == i+tag);
    if (left_child) left_child->verify();
    if (right_child) right_child->verify();
  }
  void trace(GC * gc)
  {
    left_child  = (TREE*)gc->trace(left_child);
    right_child = (TREE*)gc->trace(right_child);
  }
  int size() const;
};

int TREE::tagcnt = 0;

int TREE::size() const
{
  int sz = 1;
  if (left_child)  sz += left_child->size();
  if (right_child) sz += right_child->size();
  return sz;
}

TREE * make_tree_1(int);
TREE * make_tree_2(int);
TREE * make_tree_3(int);

TREE * make_tree_1(int depth)
{
  if(depth==0) return (TREE*) 0;
  --depth;
  TREE * l = make_tree_2(depth);
  TREE * r = make_tree_2(depth);
  return new (heap1) TREE(l,r);
}


TREE * make_tree_2(int depth)
{
  if(depth==0) return (TREE*) 0;
  --depth;
  TREE * l = make_tree_3(depth);
  TREE * r = make_tree_3(depth);
  return new (heap2) TREE(l,r);
}

TREE * make_tree_3(int depth)
{
  if(depth==0) return (TREE*) 0;
  --depth;
  TREE * l = make_tree_1(depth);
  TREE * r = make_tree_1(depth);
  return new (heap3) TREE(l,r);
}

void do_something()
{  TREE * t;
   t = make_tree_1(DEPTH);
   t->verify();
   assert(t->size() == ((1 << DEPTH)-1));
}

int main()
{
   cout << "Testing gc of trees\n";
   for (int trial = 1; trial <= TRIALS; trial++) {
      cout << "Trial " << trial << "\n" << flush;
      do_something();
      cout << "Trial " << trial << " has passed\n" << flush;
   }
   cout << "Final cleanup\n" << flush;
   heap1.collect();
   heap2.collect();
   heap3.collect();
   return 0;
}
