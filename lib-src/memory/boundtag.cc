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
#include <string.h>
#include <AD/memory/boundtag.h>   // Boundary tag memory manager

//////////////////////////////////////////////////////////////////////////////
// Constructor: initialize the memory manager.  The free list initially
// contains one ``stub'' element.
//////////////////////////////////////////////////////////////////////////////

BoundaryTag::BoundaryTag(long size) : Mem("BoundaryTag"), pages(0)
{
  pageSize = size > 256 ? size : 256;         // The default page size
  clear();
}

BoundaryTag::BoundaryTag(Mem& m, long size) : Mem(m, "BoundaryTag"), pages(0)
{
  pageSize = size > 256 ? size : 256;         // The default page size
  clear();
}
//////////////////////////////////////////////////////////////////////////////
// Destructor:  frees all the pages allocated
//////////////////////////////////////////////////////////////////////////////

BoundaryTag::~BoundaryTag()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////
// Release all memory from the manager
//////////////////////////////////////////////////////////////////////////////

void BoundaryTag::clear()
{
  Page * current, * next;
  for (current = pages; current; current = next)
  {
    next = current->next;
    manager_mem->free(current);
  }
  pages = NULL;                               // Linked list of pages
  freeList = stub.next = stub.last = &stub;   // Dummy element
  stub.size = stub.last_size = 0;
  allocated = 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Allocate a new string from the manager.
//////////////////////////////////////////////////////////////////////////////

char * BoundaryTag::operator [] (const char * string)
{
  char * newString = (char *) (*this)[strlen(string) + 1];
  strcpy(newString,string);
  return newString;
}

//////////////////////////////////////////////////////////////////////////////
//  Allocate a chunk of storage from the memory manager
//////////////////////////////////////////////////////////////////////////////

void * BoundaryTag::m_alloc(size_t size)
{
  register unsigned long elements =
    (size + 2*sizeof(Block) - offsetof(Block,next)-1) / sizeof(Block);
  register Block * B, * start;

  //
  // Use first fit strategy starting from the free list
  //
  for (;;)
  {
    for (B = start = freeList;  ;B = B->next)
    {
      if (B->size >= elements)
      {         // Size fitting??
        if (B->size - elements < 2)
        {   // Split block or not??
          //
          // The block should not be split.  Mark the block as allocated,
          // unlink it from the free list and returns the free block
          // to the client.  We'll also advance the free list to the
          // next block after the current block so that we will not
          // stuck at one end of the free list.
          //
          B[B->size].last_size |= Block::USED_BIT;
          B->size |= Block::USED_BIT;
          B->next->last = B->last;
          B->last->next = B->next;
          freeList = B->next;
          return &B->next;
        }
        else
        {
          //
          // The block will be split.  We'll keep the top chunk
          // and return the bottom chunk to the client.  Nothing
          // will have to be deleted from the free list.
          //
          register long leftOver = B->size - elements;
          register Block * newBlock = B + leftOver;
          newBlock[elements].last_size =
            newBlock->size = elements | Block::USED_BIT;
          newBlock->last_size = B->size = leftOver;
          freeList = B;
          return &newBlock->next;
        }
      }
      if (B->next == start)
        break;  // back to the start??
    }
    this->grow(size);  // Allocate a new page
  }
}

//////////////////////////////////////////////////////////////////////////////
// This auxiliary function allocate a new page and puts it onto the
// free list.
//////////////////////////////////////////////////////////////////////////////

void BoundaryTag::grow(long bytes)
{
  if (bytes < pageSize)
    bytes = pageSize;
  long elements =
    (bytes + 2*sizeof(Block) - offsetof(Block,next)-1) / sizeof(Block);

  Page * newPage = (Page*)
                   manager_mem->m_alloc(sizeof(Page) + elements * sizeof(Block));
  Block * B = newPage->blocks;

  newPage->next = pages;   // Chain the pages together
  pages = newPage;

  allocated += elements * sizeof(Block);

  //
  // The new page is split into two blocks.  One is of size |elements|
  // and the other is of size 1 and is located just after the first
  // block.  The latter block is a stub and is marked with the used bit
  // so that it will not be accidently merged with the first.
  //

  B[elements].last_size = B->size = elements;
  B[elements].size = B->last_size = (LongWord)Block::USED_BIT | 1;

  //
  // Link the new block |B| so that it is located after the
  // current starting point of the free list
  //

  B->next = freeList->next;
  B->last = freeList;
  freeList->next = B;
  B->next->last = B;
  freeList = B;          // Point the free list directly to the new block
  // so that we'll won't have to search for it
  // when we return
}

//////////////////////////////////////////////////////////////////////////////
//  Free block, combines it with adjacent blocks if that is possible.
//////////////////////////////////////////////////////////////////////////////

void BoundaryTag::free(void * core)
{
  if (core != 0)
  {
    register Block * B = (Block*) (((char *)core) - offsetof(Block,next));
    register Block * aBlock;

    assert( (B->size & Block::USED_BIT) == Block::USED_BIT);

    B->size &= ~Block::USED_BIT;                  // Unmark the used bit
    aBlock = B + B->size;                         // This is the next block
    if ( (aBlock->size & Block::USED_BIT) == 0)
    { // Merge with next block??
      aBlock->next->last = aBlock->last;         // Unlink the next block
      aBlock->last->next = aBlock->next;
      if (aBlock == freeList)
        freeList = aBlock->next;
      B->size += aBlock->size;                   // and merge
      B[B->size].last_size = B->size;
    }
    else
    {
      aBlock->last_size &= ~Block::USED_BIT;
    }

    if ( (B->last_size & Block::USED_BIT) == 0)
    { // Merge with last block??
      aBlock = B - B->last_size;                 // This is the last block
      aBlock->size += B->size;                   // and merge
      aBlock[aBlock->size].last_size = aBlock->size;
      return;
    }

    // Now, merges |B|, the (possibly coalesed) free block,
    // to the position {\em before} the current starting point
    // of the free list.   This way there is time before this same
    // block is encountered again.  This gives this block more opportunity
    // to be merged with some other adjacent blocks, which might be
    // freed during this time.

    B->next = freeList;
    B->last = freeList->last;
    freeList->last = B;
    B->last->next = B;
  }
}

//////////////////////////////////////////////////////////////////////////////
// Compute allocation statistics of the memory manager.
//////////////////////////////////////////////////////////////////////////////

BoundaryTag::Statistics BoundaryTag::statistics() const
{
  Statistics S;
  register Page * page;
  register Block * B;

  S.bytes_allocated = allocated;

  // Count the number of pages allocated

  for (S.page_count = 0, page = pages; page; page = page->next)
    S.page_count++;

  //
  // Count the number of free blocks within freelist and compute
  // the amount of bytes free

  for (S.free_block_count = 0, S.bytes_available = 0,
       B = freeList; ; B = B->next)
  {
    S.bytes_available += B->size;
    S.free_block_count++;
    if (B->next == freeList)
      break;
  }

  S.bytes_available *= sizeof(Block);

  return S;
}

//////////////////////////////////////////////////////////////////////////////
//  Returns the size of an allocated block
//////////////////////////////////////////////////////////////////////////////

size_t BoundaryTag::size(const void * core) const
{
  register Block * B = (Block*) (((char *)core) - offsetof(Block,next));
  assert( (B->size & Block::USED_BIT) == Block::USED_BIT);
  return B->size & ~Block::USED_BIT;
}
