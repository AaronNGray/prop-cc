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

#ifndef quicksort_h
#define quicksort_h

#include <AD/sort/sorting.h>
#include <AD/sort/insort.h>   // Insertion sort
//
// Quick sort with middle element as pivot\cite{alg-hand-book,comp-algo}
//
// e.g.  quickSort(char *, names, 100, strcmp(key,A[i]) < 0);
//

///////////////////////////////////////////////////////////////////////////
//  Macro version
///////////////////////////////////////////////////////////////////////////
#define quickSort(TYPE,X,N,predicate)                            \
   do { TYPE * subproblems[32];                                  \
        int sizes[32];                                           \
        int sp = 0;                                              \
        subproblems[0] = X; sizes[0] = N;                        \
        while (sp >= 0) {                                        \
           register TYPE * A = subproblems[sp];                  \
           register int n = sizes[sp--];                         \
           while (n >= 2) {                                      \
              if (n < 10) {                                      \
                 insertionSort(TYPE,A,n,predicate);              \
                 break;                                          \
              } else {                                           \
                 register int i, hi, lo;                         \
                 register TYPE key = A[i = n/2];                 \
                 A[i] = A[0];                                    \
                 for (lo = 0, hi = n-1; lo < hi; ) {             \
                    i = hi; while (i > lo && (predicate)) i--;   \
                    hi = i; A[lo] = A[hi];                       \
                    i = lo; while (i < hi && ! (predicate)) i++; \
                    lo = i; A[hi] = A[lo];                       \
                 }                                               \
                 A[lo] = key;                                    \
                 if (lo > n - lo) {                              \
                    subproblems[++sp] = A;                       \
                    sizes[sp] = lo;                              \
                    A += lo + 1;                                 \
                    n -= lo + 1;                                 \
                 } else {                                        \
                    subproblems[++sp] = A + lo + 1;              \
                    sizes[sp] = n - lo - 1;                      \
                    n = lo;                                      \
                 }                                               \
              }                                                  \
           }                                                     \
        }                                                        \
   } while(0)


///////////////////////////////////////////////////////////////////////////
//  Template version
///////////////////////////////////////////////////////////////////////////

template <class T, class Ord>
class QuickSort : public Sorting<T,Ord>
{
public:
  void sort(int, T []);
};

template <class T, class Ord>
void QuickSort<T,Ord>::sort(int N, T array[])
{
  quickSort(T, array, N, Ord::less(key, A[i]));
}


#endif
