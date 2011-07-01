//  Test memory stuff
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <AD/memory/arena.h>      // Arenas
#include <AD/memory/boundtag.h>   // Boundary tag memory manager
#include <AD/memory/buddy.h>      // Fibonacci buddy system
#include <AD/memory/mempool.h>    // Memory pool
#include <AD/memory/strpool.h>    // String pool

int main(int argc, char * argv[])
{
   StringPool A; MemPool B;
   BoundaryTag C(4096);
   int i;

   A["Shure"];
   A["Waters"];
   B[100];

   void * core[257]; 

   for (i = 0; i < 257; i++)
      { core[i] = C[i]; memset(core[i],255,i);
      }
   printf("\n");

   BoundaryTag::Statistics S = C.statistics();
   printf("pages = %d\n", S.page_count);
   printf("bytes allocated = %d\n", S.bytes_allocated);
   printf("bytes available = %d\n", S.bytes_available);
   printf("free blocks = %d\n", S.free_block_count); 

   i = 0;
   do {
      i = (i+8) % 257;
      C.free(core[i]); 
   } while (i != 0);
   printf("\n");

   S = C.statistics();

   printf("pages = %d\n", S.page_count);
   printf("bytes allocated = %d\n", S.bytes_allocated);
   printf("bytes available = %d\n", S.bytes_available);
   printf("free blocks = %d\n", S.free_block_count); 

   // Arena arena(100);

   // double * x = arena(); 
   // double * y = arena();

   // arena.free(x); arena.free(y);

   char block[70*1024];
   Buddy buddy(block, sizeof(block));

   for (i = 0; i < 257; i++)
      { core[i] = buddy[i]; memset(core[i],255,i); }
   printf("\n");

   i = 0;
   do {
      i = (i+8) % 257;
      buddy.free(core[i]); 
   } while (i != 0);
   printf("\n");


   printf("OK\n");
   return 0;
}
