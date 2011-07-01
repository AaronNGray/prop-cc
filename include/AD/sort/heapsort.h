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

#ifndef heap_sort_h
#define heap_sort_h

#include <AD/sort/sorting.h>

//
// Heap sort using Floyd's heap construction algorithm\cite{algo-hand-book}
//
// The sorting algorithm is divided into two phases.  In the
// first, a heap is constructed in place, with the maximum
// element in location 0.  The second phase repeatedly extract
// the maximum and move it to the end of the array.
//
//
// e.g.:   heapSort(char *, names, 100, strcmp(key,names[i]) < 0);
//

///////////////////////////////////////////////////////////////////////////
//  Macro version
///////////////////////////////////////////////////////////////////////////
#define heapSort(TYPE,A,N,predicate)                     \
   do { register int i, j, k;                            \
        for (k = 1; k < (N); k++) {                      \
           register TYPE key = (A)[k];                   \
           for (j = k; j > 0; j = i) {                   \
              i = (j-1)/2;                               \
              if (predicate) break;                      \
              (A)[j] = (A)[i];                           \
           }                                             \
           (A)[j] = key;                                 \
        }                                                \
        for (k = (N)-1; k > 0; k--) {                    \
           TYPE max = (A)[0];                            \
           register TYPE key = (A)[k];                   \
           for (j = 0; (i = j+j+1) < k; j = i) {         \
              if (! (predicate)) {                       \
                 i++; if (i > k || ! (predicate)) break; \
              } else if (i + 1 < k) {                    \
                 register TYPE& key = (A)[i+1];          \
                 if (! (predicate)) i++;                 \
              }                                          \
              (A)[j] = (A)[i];                           \
           }                                             \
           (A)[j] = key; (A)[k] = max;                   \
        }                                                \
   } while(0)

///////////////////////////////////////////////////////////////////////////
//  Template version
///////////////////////////////////////////////////////////////////////////
template <class T, class Ord>
class HeapSort : public Sorting<T,Ord>
{
public:
  void sort(int, T []);
};

template <class T, class Ord>
void HeapSort<T,Ord>::sort(int N, T array[])
{
  heapSort(T, array, N, Ord::less(key,array[i]));
}

#endif
