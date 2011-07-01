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

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <AD/memory/buddy.h>     // Fibonacci buddy system
#include <AD/generic/tables.h>   // Fibonacci numbers table

static const long * fib = fibonacci + 2;  // 1, 2, 3, 5, 8, ...

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////

Buddy::Buddy( void* pool, size_t poolSize) : Mem("Buddy")
{
  init_pool(pool, poolSize);
}

//////////////////////////////////////////////////////////////////////////////
//  Destructor.  Nothing to do
//////////////////////////////////////////////////////////////////////////////

Buddy::~Buddy()
{}

//////////////////////////////////////////////////////////////////////////////
// Method to initialize the pools
//////////////////////////////////////////////////////////////////////////////

void Buddy::init_pool( void* pool, size_t poolSize)
{
  my_pool      = pool;
  my_pool_size = poolSize;

  assert(sizeof(Block *) * levels <= poolSize);
  free_lists = (Block**)pool;
  pool = (Byte*)pool + sizeof(Block*) * levels;
  poolSize -= sizeof(Block*) * levels;

  register size_t elements = (poolSize + sizeof(Block) - 1) / sizeof(Block);
  register Block * block = (Block *)pool;
  register int i;

  //
  // Initialize free lists to empty
  //
  for (i = 0; i < levels; i++)
    free_lists[i] = NULL;

  //
  // Find the maximum |i| such that |fib[i] < elements|
  //
  for (i = 0; (size_t)fib[i] <= elements; i++)
    ;
  i--;

  begin = block;
  end = block + elements;
  //
  // Split block into chunks and append them onto the free lists.
  //
  while (elements > 0)
  {
    while (elements < (size_t)fib[i])
      i--;
    register int size = fib[i];
    block->fib_number = i;
    block->right_buddies = 0;
    block->allocated = false;
    block->next = free_lists[i];
    if (block->next)
      block->next->last = block;
    free_lists[i] = block;
    block += size;
    elements -= size;
  }
}

//////////////////////////////////////////////////////////////////////////////
// Allocate some memory and initialize it to zeros
//////////////////////////////////////////////////////////////////////////////

void * Buddy::c_alloc(size_t size)
{
  void * core = m_alloc(size);
  memset(core,0,size);
  return core;
}

//////////////////////////////////////////////////////////////////////////////
// Method to allocate memory
//////////////////////////////////////////////////////////////////////////////

void * Buddy::m_alloc(size_t size)
{
  register int i, j;
  register size_t elements =
    (size + sizeof(Block) + offsetof(Block,next) - 1) / sizeof(Block);

  //
  // Locate the smallest index |i| such that |fib[i] >= elements|
  // with a binary search.
  //
  {  register int low, high;
    for (low = 0, high = levels-1; low < high; )
    {
      i = (low + high)/2;
      if ((size_t)fib[i] < elements)
        low = i+1;
      else if ((size_t)fib[i] == elements)
        break;
      else
        high = i-1;
    }
  }

  //
  // Now, locate a non-empty free list with a sequential search.
  //
  while ((size_t)fib[i] < elements)
    i++;
  for (j = i; j < levels && ! free_lists[j]; j++)
    ;
  if (j >= levels)
    return NULL;

  //
  // Unlink the free block from the free list.
  //
  register Block * block = free_lists[j];
  free_lists[j] = block->next;
  if (block->next)
    block->next->last = NULL;

  //
  // Split block into smaller chunks if |j > i|.
  // The size of the left buddy is the larger one.
  //
  for ( ;j > i && j > 1; j--)
  {
    register Block * right_buddy = block + fib[j-1];
    right_buddy->fib_number    = j-2;
    right_buddy->right_buddies = 0;
    right_buddy->next = free_lists[j-2];
    right_buddy->allocated = false;
    if (right_buddy->next)
      right_buddy->next->last = right_buddy;
    free_lists[j-2] = right_buddy;
    block->fib_number = j-1;
    block->right_buddies++;
  }

  //
  // Mark the block to be allocated
  //
  block->allocated = true;
  return &(block->next);
}

//////////////////////////////////////////////////////////////////////////////
//  Frees memory
//////////////////////////////////////////////////////////////////////////////

void Buddy::free(void * core)
{
  register Block * block =
    (Block *)(((char *)core) - offsetof(Block,next));
  register int n;         // fibonacci number of current block
  assert(block->allocated);

  block->allocated = false;   // Mark block as unallocated first.

  //
  // Keep merging with neighbors until done.
  //
  for (;;)
  {
    register Block * buddy; // potential buddy
    n = block->fib_number;
    if (block->right_buddies == 0)
    {  // Are we a right buddy??
      buddy = block - fib [ n + 1 ];
      if (buddy >= begin && buddy->right_buddies > 0 &&
          ! buddy->allocated && buddy->fib_number == n+1)
      {
        //
        // Merge with left buddy
        //
        if (buddy == free_lists[ n+1 ])
          free_lists[ n+1 ] = buddy->next;
        if (buddy->last)
          buddy->last->next = buddy->next;
        if (buddy->next)
          buddy->next->last = buddy->last;
        block = buddy;
        block->fib_number++;
        block->right_buddies--;
      }
      else
        break;
    }
    else
    {  // No, we are a left buddy
      buddy = block + fib [ n ];
      if (buddy + fib[n-1] < end && buddy->right_buddies == 0 &&
          ! buddy->allocated && buddy->fib_number == n-1)
      {
        //
        // Merge with right buddy
        //
        if (buddy == free_lists[ n-1 ])
          free_lists[ n-1 ] = buddy->next;
        if (buddy->last)
          buddy->last->next = buddy->next;
        if (buddy->next)
          buddy->next->last = buddy->last;
        block->fib_number++;
        block->right_buddies--;
      }
      else
        break;
    }
  }

  //
  // Link block back to the free list
  //
  n = block->fib_number;
  block->next = free_lists[n];
  if (block->next)
    block->next->last = block;
  free_lists[n] = block;
}

//////////////////////////////////////////////////////////////////////////////
// Additional Mem protocol
//////////////////////////////////////////////////////////////////////////////

void   Buddy::clear   ()
{
  init_pool(my_pool, my_pool_size);
}

//////////////////////////////////////////////////////////////////////////////
// Returns the size of a block
//////////////////////////////////////////////////////////////////////////////

size_t Buddy::size(const void * core) const
{
  register const Block * block =
    (const Block *)(((char *)core) - offsetof(Block,next));
  assert(block->allocated);
  return fib[block->fib_number] * sizeof(Block);
}
