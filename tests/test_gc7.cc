//////////////////////////////////////////////////////////////////////////////
//  Testing the ability to trace cross heap pointers.
//  We'll allocate a list in two different collectors.
//  Garbage collection should preserve the shape of the list.
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <assert.h>
#include <AD/gc/gc.h>
#include <AD/gc/bgc.h>
#include <AD/gc/gcobject.h>
#include <AD/gc/gcheaps.h>

BGC heap1; 
BGC& heap2 = bgc;

#define TRIALS 5    // number of times to test
#define LENGTH 100  // length of list to allocate

class LIST : public GCObject {
   int    tag;
   int    junk[500];
public:
   LIST * next;
   LIST(LIST * n) : next(n) 
     { for (int i = 0; i < 500; i++) junk[i] = i + tag; }
  ~LIST() {}
   void verify() const 
   {  for (int i = 0; i < 500; i++) assert(junk[i] == i+tag); 
      if (next) next->verify();
   }  
   void trace(GC * gc) { next = (LIST*)gc->trace(next); }
};

int length(LIST * l)
{  int len; 
   for (len = 0; l; l = l->next)
      len++;
   return len;
}


void do_something() 
{  LIST * l = 0;
   for (int i = 0; i < LENGTH; i++) {
      l = new (heap1) LIST(l);
          new (heap1) LIST(l);  // some garbage for heap1
          new (heap1) LIST(l);  // some garbage for heap1
          new (heap1) LIST(l);  // some garbage for heap1
      l = new (heap2) LIST(l);
          new (heap2) LIST(l);  // some garbage for heap2
          new (heap2) LIST(l);  // some garbage for heap2
          new (heap2) LIST(l);  // some garbage for heap2
   }
   l->verify();
   assert(length(l) == LENGTH * 2);
}

int main()
{
   std::cout << "Testing crossheap pointers\n";
   for (int trial = 1; trial <= TRIALS; trial++) {
      std::cout << "Trial " << trial << "\n" << std::flush;
      do_something();
      std::cout << "Trial " << trial << " has passed\n" << std::flush;
   }
   std::cout << "Now cleaning up\n";
   heap1.collect();
   heap2.collect();
   return 0;
}
