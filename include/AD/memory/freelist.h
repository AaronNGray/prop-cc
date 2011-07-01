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

#ifndef free_lists_h
#define free_lists_h

//////////////////////////////////////////////////////////////////////////////
//  This trick is borrowed from the LEDA library.
//////////////////////////////////////////////////////////////////////////////

#include <new>


#define Max_free_list_cell_size 1023 // we keep free lists up to 1023 bytes.

struct Free_list_cell
{
  Free_list_cell * next;
};
extern Free_list_cell * free_lists[];

#define Use_free_list_manager(type)                                       \
  void * operator new (int)                                               \
      {                                                                   \
        Free_list_cell * cell = free_lists[sizeof(type)];                 \
        if (cell) { free_lists[sizeof(type)] = cell->next; return cell; } \
        else return ::new char [sizeof(type)];                            \
      }                                                                   \
   void operator delete(void * t)                                         \
      {                                                                   \
        Free_list_cell * cell = (Free_list_cell*)t;                       \
        cell->next = free_lists[sizeof(type)];                            \
        free_lists[sizeof(type)] = cell;                                  \
      }                                                                   \

#define Implement_free_list_manager(max_size) \
  Free_list_cell * free_lists[max_size];

#endif
