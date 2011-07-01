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

#ifndef Shellsort_h
#define Shellsort_h

#include <AD/sort/sorting.h>
//
//  Shell sort\cite{algo-hand-book}
//
//  e.g: shellSort(char *, names, 100, strcmp(key,names[i]) < 0);
//

/////////////////////////////////////////////////////////////////////////////
// Macro version
/////////////////////////////////////////////////////////////////////////////
#define shellSort(TYPE,A,N,predicate)                                         \
   do {                                                                       \
      for ( register int gap = (N); gap > 1; ) {                              \
         if (gap < 5) gap = 1;                                                \
         else gap = (5 * gap - 1) / 11;                                       \
         for (register int j = (N) - gap; j >= 0; j--) {                      \
            register TYPE key = (A)[j];                                       \
            for (register int i = j + gap; i < (N) && !(predicate); i += gap) \
               (A)[i-gap] = (A)[i];                                           \
            (A)[i-gap] = key;                                                 \
         }                                                                    \
      }                                                                       \
   } while(0)

/////////////////////////////////////////////////////////////////////////////
// Template version
/////////////////////////////////////////////////////////////////////////////

template <class T, class Ord>
class ShellSort : public Sorting<T,Ord>
{
public:
  void sort(int, T []);
};

template <class T, class Ord>
void ShellSort<T,Ord>::sort(int N, T array[])
{
  shellSort(T, array, N, Ord::less(key, array[i]));
}

#endif
