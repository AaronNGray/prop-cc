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

#ifndef heap_sort2_h
#define heap_sort2_h

#include <AD/sort/sorting2.h>

//
// Heap sort using Floyd's heap construction algorithm\cite{algo-hand-book}
//
// The sorting algorithm is divided into two phases.  In the
// first, a heap is constructed in place, with the maximum
// element in location 0.  The second phase repeatedly extract
// the maximum and move it to the end of the array.
//
//
// e.g.:   heapSort2(char *, int, names, salaries, 100, strcmp(key,names[i]) < 0);
//

///////////////////////////////////////////////////////////////////////////
//  Macro version
///////////////////////////////////////////////////////////////////////////
#define heapSort2(KEY,VALUE,A,B,N,predicate)             \
   do { register int i, j, k;                            \
        for (k = 1; k < (N); k++) {                      \
           register KEY   key   = (A)[k];                \
           register VALUE value = (B)[k];                \
           for (j = k; j > 0; j = i) {                   \
              i = (j-1)/2;                               \
              if (predicate) break;                      \
              (A)[j] = (A)[i];                           \
              (B)[j] = (B)[i];                           \
           }                                             \
           (A)[j] = key;                                 \
           (B)[j] = value;                               \
        }                                                \
        for (k = (N)-1; k > 0; k--) {                    \
           KEY   max     = (A)[0];                       \
           VALUE max_val = (B)[0];                       \
           register KEY   key   = (A)[k];                \
           register VALUE value = (B)[k];                \
           for (j = 0; (i = j+j+1) < k; j = i) {         \
              if (! (predicate)) {                       \
                 i++; if (i > k || ! (predicate)) break; \
              } else if (i + 1 < k) {                    \
                 register KEY& key = (A)[i+1];           \
                 if (! (predicate)) i++;                 \
              }                                          \
              (A)[j] = (A)[i];                           \
              (B)[j] = (B)[i];                           \
           }                                             \
           (A)[j] = key;   (A)[k] = max;                 \
           (B)[j] = value; (B)[k] = max_val;             \
        }                                                \
   } while(0)

///////////////////////////////////////////////////////////////////////////
//  Template version
///////////////////////////////////////////////////////////////////////////
template <class K, class V, class Ord>
class HeapSort2 : public Sorting2<K,V,Ord>
{
public:
  void sort(int, K [], V []);
};

template <class K, class V, class Ord>
void HeapSort2<K,V,Ord>::sort(int N, K keys[], V values[])
{
  heapSort2(K, V, keys, values, N, Ord::less(key,keys[i]));
}

#endif
