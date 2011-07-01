//////////////////////////////////////////////////////////////////////////////
//  Testing the weak pointers facilities
//  We'll allocate a bunch of dummy objects and store weakpointer referencing
//  them into an array.  The dummy objects are then throw away.
//  We'll test three things:
//     (1) Weakpointers do not prevent objects from being collected.
//     (2) The objects that are still alive is reachable from the
//         weakpointers.
//     (3) The counts add up.
//////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <iostream.h>
#include <AD/gc/gcobject.h>
#include <AD/gc/weakptr.h>
#include <AD/gc/gcheaps.h>
#include <AD/gc/markswp.h>

#define TRIALS 10000

MarkSweepGC marksweep;

int created = 0;
int destroyed = 0;
int total_created = 0;
int total_destroyed = 0;
int current_trial = 0;
int alive = 0;

class TEST : public GCObject {
   int tag;
   int junk[30];
   int trial;
public:
   TEST(int t, int tr) : tag(t), trial(tr)
      { for (int i = 0; i < 30; i++) junk[i] = i + tag; 
	total_created++; created++; }
  ~TEST() { total_destroyed++; if (trial == current_trial) destroyed++; }
   void trace(GC *) {} 
   void verify(int t) 
   {   assert(HM::page_gc(this) == GC::get_default_gc().gc_id());
       assert(t == tag);
       for (int i = 0; i < 30; i++) assert(junk[i] == i + tag); 
   }
};

TEST *            ps [TRIALS];
WeakPointer<TEST> wps[TRIALS];

void do_tests(int trial)
{
   int i;

   cout << "Trial number " << trial << "\n" << flush;

   current_trial = trial;

   created = 0;
   destroyed = 0;

   //
   // Allocate a bunch of stuff
   //
   for (i = 0; i < TRIALS; i++) 
      wps[i] = ps[i] = new TEST(i,trial);

   cout << "Data has been allocated\n" << flush;

   GC::garbage_collect();

   //
   // Make sure all the weakpointers are alive even after garbage collection.
   //
   for (i = 0; i < TRIALS; i++) {
      assert (! wps[i].is_null());
      wps[i]->verify(i);
   }

   //
   // Delete the non-weak version.
   //
   for (i = 0; i < TRIALS; i++) {
      ps[i] = 0;
   }

   //
   // Check the ones that are still alive
   //
   for (alive = 0, i = 0; i < TRIALS; i++) {
      if (! wps[i].is_null()) {
         alive++;
         wps[i]->verify(i);
      }
   }


   GC::garbage_collect();

   //
   // Check the ones that are still alive, again.
   //
   for (alive = 0, i = 0; i < TRIALS; i++) {
      if (! wps[i].is_null()) {
         alive++;
         wps[i]->verify(i);
      }
   }

   cout << " Created = " << created
        << " Destroyed = " << destroyed
        << " Alive = " << alive << '\n' << flush;

   assert (created == alive + destroyed);

   // Make sure at least 80% of all objects are collected.
   assert (TRIALS * 8 / 10 <= destroyed);
}

int main()
{
   GC::set_default_gc(marksweep);
   GC::get_default_gc().set_finalization(true);
   cout << "Testing the weak pointers facility\n" << flush;
   int trials = 10;
   for (int i = 1; i <= trials; i++)
     do_tests(i);

   cout << " Total created = " << total_created
        << " Total destroyed = " << total_destroyed << '\n';

   GC::get_default_gc().print_statistics(cout);
   cout << "The weakpointers facility seems to be ok\n" << flush;
   return 0;
}
