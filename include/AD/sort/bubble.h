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

#ifndef bubble_sort_h
#define bubble_sort_h

#include <AD/sort/sorting.h>

//
// Lazy bubble sort, for those who don't care for anything better.
//
// e.g.:  bubbleSort(char *, names, 100, strcmp(names[i], names[i+1]) < 0);
//

/////////////////////////////////////////////////////////////////////////////
//  Macro version
/////////////////////////////////////////////////////////////////////////////
#define bubbleSort(TYPE,A,N,predicate)              \
   do {                                             \
      for (register int j = (N) - 1; j >= 0; j--) { \
         for (register int i = 0; i < j; i++) {     \
            if (! (predicate)) {                    \
               register TYPE temp = A[i];           \
               A[i] = A[i+1]; A[i+1] = temp;        \
            }                                       \
         }                                          \
      }                                             \
   } while(0)

/////////////////////////////////////////////////////////////////////////////
//  Template version
/////////////////////////////////////////////////////////////////////////////
template <class T, class Ord>
class BubbleSort : public Sorting<T,Ord>
{
public:
  void sort(int, T []);
};

template <class T, class Ord>
void BubbleSort<T,Ord>::sort(int N, T array[])
{
  bubbleSort(T, array, N, Ord::less(array[i], array[i+1]));
}

#endif
