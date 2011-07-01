#include <iostream.h>
#include <assert.h>
#include <AD/gc/gc.h>
#include <AD/gc/bgc.h>
#include <AD/gc/gcobject.h>
#include <AD/gc/gcheaps.h>

#define TRIALS 500   // number of times to test
#define DEPTH  4    // depth of the tree
#define SIZE 500

class TREE;

struct Junk : public GCObject {
   const char * name; 
   TREE * tree;
   int junk[SIZE];
   Junk(TREE * t) : tree(t) {}
   void trace (GC * gc); 
};

class TREE : public GCObject {
   TREE();
   int    tag;
   int    junk[SIZE];
   Junk * junk2;
   Junk * junk3;
   Junk * junk4;
   Junk * junk5;
public:
   TREE * left;
   TREE * right;
   TREE(TREE *l , TREE*r) 
     : left(l), right(r), 
       junk2(new Junk(this)), junk3(new Junk(this)),
       junk4(new Junk(this)), junk5(new Junk(this))
     { for (int i = 0; i < SIZE; i++) junk[i] = i + tag; }
  ~TREE() {}
   void verify() const
   {  assert(junk2->tree == this);
      for (int i = 0; i < SIZE; i++) assert(junk[i] == i+tag);
      if (left) left->verify();
      if (right) right->verify();
   }
   virtual void trace(GC * gc) {
    left = (TREE*)gc->trace(left);
    right = (TREE*)gc->trace(right);
    junk2 = (Junk*)gc->trace(junk2);
    junk3 = (Junk*)gc->trace(junk3);
    junk4 = (Junk*)gc->trace(junk4);
    junk5 = (Junk*)gc->trace(junk5);
  }
  int size() const;
};

void Junk::trace(GC * gc) { tree = (TREE*)gc->trace(tree); }
TREE * tree(TREE *l, TREE *r) { return new TREE(l,r); }


int TREE::size() const
{
  int sz = 1;
  if (left)  sz += left->size();
  if (right) sz += right->size();
  return sz;
}

TREE * make_tree(int depth)
{
  if(depth==0) return (TREE*) 0;
  --depth;
  TREE * t = tree(make_tree(depth), make_tree(depth));
  return t;
}


void do_something()
{  TREE * t;
   t = make_tree(DEPTH);
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
   return 0;
}
