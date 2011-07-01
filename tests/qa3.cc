//  Test hash table stuff

#include <assert.h>
#include <stdio.h>
#include <AD/hash/chash.h>   // coalesced hashing hash table
#include <AD/hash/dchash.h>  // direct chaining hash table
#include <AD/hash/dhash.h>   // double hashing hash table
#include <AD/hash/lhash.h>   // linear probing hash table
#include <AD/hash/ohash.h>   // ordered hashing hash table
#include <AD/hash/chash2.h>   // coalesced hashing hash table
#include <AD/hash/dchash2.h>  // direct chaining hash table
#include <AD/hash/dhash2.h>   // double hashing hash table
#include <AD/hash/lhash2.h>   // linear probing hash table
#include <AD/hash/ohash2.h>   // ordered hashing hash table

typedef const char * string; 

int main()
{  
   CHashTable<string,string>  a(10);
   DCHashTable<string,string> b(10,2);
   DHashTable<string,string>  c(10);
   LHashTable<string,string>  d(10);
   OHashTable<string,string>  e(10); 

   static struct { string first, last; } authors[] =
   {  { "Edgar",    "Doctorow"   },
      { "James",    "Joyce"      },
      { "Vladimir", "Nabokov"    },
      { "Pablo",    "Neruda",    },
      { "William",  "Faulkner",  },
      { "Ernest",   "Hemingway"  },
      { "Gabriel",  "Garcia Marquez" },
      { "Isabel",   "Allende" },
      { "Thomas",   "Pynchon" },
      { "Kurt",     "Vonnegurt" },
      { "Ken",      "Casey" },
      { "Norman",   "Mailer" },
   };

   static struct { string first, last; } old_authors[] =
   {  { "William", "Shakespear" },
      { "Edgar",   "Poe" },
      { "Thomas",  "Jefferson" }
   };

   int size = sizeof(authors)/sizeof(authors[0]);
   int i, n;

   for (i = 0; i < sizeof(old_authors)/sizeof(old_authors[0]); i++) {
      a.insert(old_authors[i].first, old_authors[i].last);
      b.insert(old_authors[i].first, old_authors[i].last);
      c.insert(old_authors[i].first, old_authors[i].last);
      d.insert(old_authors[i].first, old_authors[i].last);
      e.insert(old_authors[i].first, old_authors[i].last);
   }

   for (i = 0; i < sizeof(authors)/sizeof(authors[0]); i++) {
      a.insert(authors[i].first, authors[i].last);
      b.insert(authors[i].first, authors[i].last);
      c.insert(authors[i].first, authors[i].last);
      d.insert(authors[i].first, authors[i].last);
      e.insert(authors[i].first, authors[i].last);
   }

   Ix ix;
   printf("[Coalesced hashing (size = %d, capacity = %d)]\n", a.size(), a.capacity());
   for (n = 0, ix = a.first(); ix; ix = a.next(ix), n++) {
      printf("Name %s %s\n", a.key(ix), a.value(ix));
      assert(a.lookup(a.key(ix)));
   }
   assert(a.size() == n);

   printf("[Direct chaining (size = %d, capacity = %d)]\n", e.size(), e.capacity());
   for (n = 0, ix = b.first(); ix; ix = b.next(ix), n++) {
      printf("Name %s %s\n", b.key(ix), b.value(ix));
      assert(b.lookup(b.key(ix)));
   }
   assert(b.size() == n);

   printf("[Double hashing (size = %d, capacity = %d)]\n", a.size(), a.capacity());
   for (n = 0, ix = c.first(); ix; ix = c.next(ix), n++) {
      printf("Name %s %s\n", c.key(ix), c.value(ix));
      assert(c.lookup(c.key(ix)));
   }
   assert(c.size() == n);

   printf("[Linear hashing (size = %d, capacity = %d)]\n", b.size(), b.capacity());
   for (n = 0, ix = d.first(); ix; ix = d.next(ix), n++) {
      printf("Name %s %s\n", d.key(ix), d.value(ix));
      assert(d.lookup(d.key(ix)));
   }
   assert(d.size() == n);

   printf("[Ordered hashing (size = %d, capacity = %d)]\n", c.size(), c.capacity());
   for (n = 0, ix = e.first(); ix; ix = e.next(ix), n++) {
      printf("Name %s %s\n", e.key(ix), e.value(ix));
      assert(e.lookup(e.key(ix)));
   }
   assert(e.size() == n);

   assert(a.size() == size);
   assert(b.size() == size);
   assert(c.size() == size);
   assert(d.size() == size);
   assert(e.size() == size);

   printf("OK\n");
   return 0;
}
