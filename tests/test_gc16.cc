//////////////////////////////////////////////////////////////////////////////
//  This program tests the garbage collector classes.
//  We'll allocate a long linked list in the collectable heap, then invoke
//  garbage collection a few times. 
//
//  List cells of of random length.
//
//  Note: In your application you'll only have to include <AD/gc/gcobject.h>.
//  In this case we'll have to import some other implementation dependent 
//  information since we'll have do some poking around with the heap.
//////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream.h>
#include <AD/gc/bgc.h>
#include <AD/gc/gcobject.h>
#include <AD/gc/gcheaps.h>
#include <AD/gc/markswp.h>

MarkSweepGC marksweep_gc;

#define LENGTH (256 * 32)
#define UNIT   (16 * 64)
#define JUNK   100

//////////////////////////////////////////////////////////////////////////////
//  The list class defined below is made a garbage collectable class by
//  deriving from GCObject and adding a tracing method ``trace.''
//////////////////////////////////////////////////////////////////////////////
class LIST : public GCObject {
public:
   char   c;      // some position dependent   storage
   LIST * next;   // the link
   int    len;    // len of junk
   int    x[1];   // some other junk

   // The constructor
   LIST(LIST * n, char c1, int l) : next(n), c(c1), len(l)
      { for (int i = 0; i < l; i++) x[i] = l - i; }

   // The tracing method. 
   void trace(GC * gc) { next = (LIST*)gc->trace(next); } 
};

//////////////////////////////////////////////////////////////////////////////
//  Method to print a list, currently unused.
//////////////////////////////////////////////////////////////////////////////
void print(LIST * x)
{  if (x) { cout << x->c; print(x->next); }
}

//////////////////////////////////////////////////////////////////////////////
//  This method checks that a list is well and okay.
//////////////////////////////////////////////////////////////////////////////
void verify (LIST * x)
{  int count = 0;
   cout << "Verifying list\n" << flush;
   for ( ; x; x = x->next, count++) {
      //
      // Make sure that it lies within the collectable heap. 
      //
      assert (HM::is_mapped(x) && HM::page_gc(x) == marksweep_gc.gc_id());
      assert (HM::get_object_map().is_marked(x));

      // Check its contents
      for (int i = 0; i < x->len; i++)
         assert (x->x[i] == x->len - i);
      assert (x->c == (LENGTH - count - 1) / UNIT + 'a');
   }  

   // Make sure that it has the right length.
   assert (count == LENGTH);
   cout << "List is okay\n" << flush;
}


void do_some_stuff()
{  
   LIST * x  = 0; 

   srand(getpid());

   // Allocate a list
   for (int i = 0; i < LENGTH; i++) {
      int l = rand() % JUNK;
      x = new (sizeof(LIST) + (l-1) * sizeof(int)) LIST (x,i / UNIT + 'a', l);
      // The following line generates some garbage.
      new (sizeof(LIST) + (l-1) * sizeof(int)) LIST (x, i / UNIT + 'a', l);  
   }

   // cout << "&x = " << (void*)&x << '\n';
   // cout << "&x = " << (void*)&x << " x = " << (void*)x << '\n';
   cout << "List allocated\n";
   verify(x);
   GC::get_default_gc().collect();

   verify(x);
   GC::get_default_gc().collect();

   verify(x);
   x = 0;
   GC::get_default_gc().collect();
}

int main()
{
   GC::set_default_gc(marksweep_gc);
   GC::Statistics stats = GC::get_default_gc().statistics();
   cout << "Algorithm:        " << stats.algorithm << '\n'
        << "Version:          " << stats.version << '\n';

   do_some_stuff();
   GC::get_default_gc().collect();

   cout << "\n"
           "If you don't see a crash by now then it's probably ok :-)\n"
           "Ideally, the heap should be completely reclaimed at this\n"
           "point, but since the collector is conservative, retention\n"
           "may occur.\n"
           "\n"
           "Actually this test is bit unfair, since we are allocating\n"
           "a long linked list, a strongly connected data structure, and if\n"
           "any one part of the list is incorrectly promoted then a large\n"
           "portion of the storage will be retained.\n"
           "\n"
           "Happy GC!\n";
   return 0;
}
