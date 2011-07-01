//////////////////////////////////////////////////////////////////////////////
//  This program tests the garbage collector classes.
//  We'll allocate a long linked list in the collectable heap, then invoke
//  garbage collection a few times. 
//
//  Note: In your application you'll only have to include <AD/gc/gcobject.h>.
//  In this case we'll have to import some other implementation dependent 
//  information since we'll have do some poking around with the heap.
//////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <iostream.h>
#include <AD/gc/bgc.h>
#include <AD/gc/gcobject.h>
#include <AD/gc/gcheaps.h>

#define LENGTH (256 * 64)
#define UNIT   (16 * 64)

//////////////////////////////////////////////////////////////////////////////
//  The list class defined below is made a garbage collectable class by
//  deriving from GCObject and adding a tracing method ``trace.''
//////////////////////////////////////////////////////////////////////////////
class LIST : public GCObject {
public:
   char   c;      // some position dependent   storage
   int    x[20];  // some other position independent junk
   LIST * next;   // the link

   // The constructor
   LIST(LIST * n, char c1) : next(n), c(c1) 
      { for (int i = 0; i < 20; i++) x[i] = i; }

private:
   // The tracing method. 
   void trace(GC * gc) { next = (LIST *)gc->trace(next); } 
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
      assert (HM::is_mapped(x) && HM::page_gc(x) == bgc.gc_id());
      assert (HM::get_object_map().is_marked(x));

      // Check its contents
      for (int i = 0; i < 20; i++)
         assert (x->x[i] == i);
      assert (x->c == (LENGTH - count - 1) / UNIT + 'a');
   }  

   // Make sure that it has the right length.
   assert (count == LENGTH);
   cout << "List is okay\n" << flush;
}


void do_some_stuff()
{  
   LIST * x  = 0; 

   // Allocate a list
   for (int i = 0; i < LENGTH; i++) {
      x = new LIST (x,i / UNIT + 'a');
      // The following line generates some garbage.
      new LIST (x, i / UNIT + 'a');  
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
   GC::Statistics stats = GC::get_default_gc().statistics();
   cout << "Algorithm:        " << stats.algorithm << '\n'
        << "Version:          " << stats.version << '\n';

   do_some_stuff();
   GC::get_default_gc().collect();

   stats = GC::get_default_gc().statistics();
   size_t memory_allocated = sizeof(LIST) * LENGTH * 2;

   cout << "\n"
           "Memory allocated: " << memory_allocated << '\n'
        << "Final heap size:  " 
            << stats.bytes_managed + GCHeapManager::bytes_free() << '\n'
        << "Bytes retained:   " << stats.bytes_used << '\n'
        << "Retention rate:   " 
           << (stats.bytes_used * 100 / memory_allocated) << "%\n"
        << "\n"
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
