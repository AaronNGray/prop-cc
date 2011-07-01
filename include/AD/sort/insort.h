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

#ifndef insertion_sort_h
#define insertion_sort_h

#include <AD/sort/sorting.h>

//
//  Insertion sort
//
//  e.g. insertionSort(char *, names, 100, strcmp(key,names[i]) < 0);
//

///////////////////////////////////////////////////////////////////////////
//  Macro version
///////////////////////////////////////////////////////////////////////////
#define insertionSort(TYPE,A,N,predicate)            \
   do {                                              \
      for (register int j = 1; j < (N); j++) {       \
         register TYPE key = (A)[j];                 \
         register int i;                             \
         for (i = j - 1; i >= 0; i--) {              \
            if (! (predicate)) break;                \
            (A)[i+1] = (A)[i];                       \
         }                                           \
         (A)[i+1] = key;                             \
      }                                              \
   } while(0)

///////////////////////////////////////////////////////////////////////////
//  Template version
///////////////////////////////////////////////////////////////////////////
template <class T, class Ord>
class InsertionSort : public Sorting<T,Ord>
{
public:
  void sort(int, T []);
};

template <class T, class Ord>
void InsertionSort<T,Ord>::sort(int N, T array[])
{
  insertionSort(T, array, N, Ord::less(key, array[i]));
}

#endif
