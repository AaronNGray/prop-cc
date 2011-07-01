//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1997
//////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <AD/gc/weakptr.h>    // weak pointers
#include <AD/gc/gcheaps.h>    // heap manager
#include <AD/gc/gcmacros.h>   // useful macros

//////////////////////////////////////////////////////////////////////////////
//  Import some types
//////////////////////////////////////////////////////////////////////////////

typedef WeakPointerManager::WP_Index     WP_Index;
typedef WeakPointerManager::WP_TimeStamp WP_TimeStamp;
typedef WeakPointerManager::WP_Entry     WP_Entry;

//////////////////////////////////////////////////////////////////////////////
//  Static data.
//
//  The dummy entry is needed to make sure that when we dereference
//  an empty weak pointer before we have any entries in the weak pointer table
//  we don't dereference the null pointer.
//////////////////////////////////////////////////////////////////////////////

static WP_Entry dummy_entry[1];
WP_Entry *   WeakPointerManager::wp_table          = dummy_entry;
WP_Entry *   WeakPointerManager::wp_next_free      = 0;
void     *   WeakPointerManager::wp_table_core     = 0;
size_t       WeakPointerManager::wp_table_size     = 0;
size_t       WeakPointerManager::wp_table_capacity = 0;
WP_TimeStamp WeakPointerManager::wp_timestamp      = 0;

//////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
//////////////////////////////////////////////////////////////////////////////

WeakPointerManager:: WeakPointerManager()
{}
WeakPointerManager::~WeakPointerManager()
{}

//////////////////////////////////////////////////////////////////////////////
//  Method to add a new pointer into the weakpointer table.
//  We have a BIG problem: since objects can be moved around by the
//  collectors we can't really hash their addresses.   So in the meantime
//  we won't bother with hashing at all.
//
//  In the current setup the table is just an array.  Unused entries are
//  linked together in a freelist.  Assignment of weakpointer can be
//  accomplished in O(1) amortized time(and unfortunately O(1) space.)
//////////////////////////////////////////////////////////////////////////////

WP_Index WeakPointerManager::add_pointer( GCObject* obj, WP_TimeStamp& ts)
{
  if (obj == 0)
  {
    ts = 0;
    return 0;
  }

  for (;;)
  {
    if (wp_next_free)
    {
      WP_Index i = wp_next_free - wp_table;
      wp_next_free->object    = obj;
      wp_next_free->timestamp = ts = ++wp_timestamp;
      wp_next_free = wp_next_free->next;
      wp_table_size++;
      return i;
    }
    else
    {
      if (wp_table_capacity == wp_table_size)
      {
        GC::garbage_collect();
        if (wp_table_capacity == wp_table_size)
          grow_wp_table();
      }
      else
      {
        WP_Index i = wp_table_size;
        wp_table[i].object    = obj;
        wp_table[i].timestamp = ts = ++wp_timestamp;
        wp_table_size++;
        return i;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to expand the wp_table when necessary.
//  The wp_table *must* be blacklisted so that the entries are not
//  mistaken for ``strong'' pointers by the collectors.
//////////////////////////////////////////////////////////////////////////////

void WeakPointerManager::grow_wp_table()
{
  if (wp_table_capacity == wp_table_size)
  {

    // Compute the new size, round it up to page boundaries
    size_t new_size = GC_ROUNDUP_PAGE_SIZE(wp_table_size *3 / 2 + 1024);

    // Allocate a new table.
    void *     new_wp_table_core;
    WP_Entry * new_wp_table =
      (WP_Entry*)HM::allocate_pages_on_boundaries
      (new_size * sizeof(WP_Entry), new_wp_table_core);
    WP_Entry * new_limit   = new_wp_table + new_size;

    // Blacklist the new table and unblacklist the old one.
    HM::blacklist_system_heap (wp_table, wp_table + wp_table_capacity, false);
    HM::grow_page_table       (new_wp_table, new_limit);
    HM::blacklist_system_heap (new_wp_table, new_limit, true);

    // Copy the old table into the new
    memcpy (new_wp_table, wp_table, wp_table_capacity * sizeof(WP_Entry));

    // Delete the old table
    HM::deallocate_pages_on_boundaries
    (wp_table_core, wp_table_capacity * sizeof(WP_Entry));

    // Update various static data
    wp_table          = new_wp_table;
    wp_table_capacity = new_size;
    wp_table_core     = new_wp_table_core;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Method to scavenge and update the wp_table during finalization.
//  Only entries owned by the collector 'gc' will be touched.
//  Weakpointer entries to dying objects will be reclaimed.
//////////////////////////////////////////////////////////////////////////////

void WeakPointerManager::scavenge_wp_table( GC* gc)
{
  register GC::GC_ID id = gc->gc_id();
  for (register WP_Entry * p = wp_table, * q = wp_table + wp_table_capacity;
       p < q; p++)
  {
    register GCObject * obj = p->object;
    if (HM::is_mapped(obj) && HM::page_gc(obj) == id)
    {
      switch (HM::page_status(obj))
      {
      case HM::to_space:
      case HM::from_space:
        {  // See if object has been moved.
          if (HM::get_object_map().is_marked(obj))
          {
            if (HM::get_live_map().is_marked(obj))
            {
              // Object has been promoted.  Preserve it.
              break;
            }
            else
            {
              // Object has either been moved or is dying
              register GCHeader header = GC_OBJ_HEADER(obj);
              if (GC_OBJ_IS_FORWARDED(header))
              {
                // Object has been moved
                // Update and forward the address.
                p->object = GC_OBJ_FORWARD_ADDR(header);
                break;
              }
            }
          }
        }  // falls thru
      case HM::blacklisted:
      case HM::not_allocated:
        {  // Now delete the object.
          // The freed entry is recycled back into the free list.
          p->object = 0;
          p->timestamp = 0;
          wp_table_size--;
          p->next = wp_next_free;
          wp_next_free = p;
        }
        break;
      case HM::newly_allocated:
        // skip
        break;
      }
    }
  }
}
