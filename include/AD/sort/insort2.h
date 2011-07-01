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

#ifndef insertion_sort2_h
#define insertion_sort2_h

#include <AD/sort/sorting2.h>

//
//  Insertion sort
//
//  e.g. insertionSort2(char *, int, names, salaries,
//                      100, strcmp(key,names[i]) < 0);
//

///////////////////////////////////////////////////////////////////////////
//  Macro version
///////////////////////////////////////////////////////////////////////////
#define insertionSort2(KEY,VALUE,A,B,N,predicate)    \
   do {                                              \
      for (register int j = 1; j < (N); j++) {       \
         register KEY   key   = (A)[j];              \
         register VALUE value = (B)[j];              \
         register int i;                             \
         for (i = j - 1; i >= 0; i--) {              \
            if (! (predicate)) break;                \
            (A)[i+1] = (A)[i];                       \
            (B)[i+1] = (B)[i];                       \
         }                                           \
         (A)[i+1] = key;                             \
         (B)[i+1] = value;                           \
      }                                              \
   } while(0)

///////////////////////////////////////////////////////////////////////////
//  Template version
///////////////////////////////////////////////////////////////////////////
template <class K, class V, class Ord>
class InsertionSort2 : public Sorting2<K,V,Ord>
{
public:
  void sort(int, K [], V []);
};

template <class K, class V, class Ord>
void InsertionSort2<K,V,Ord>::sort(int N, K keys[], V values[])
{
  insertionSort2(K, V, keys, values, N, Ord::less(key, keys[i]));
}

#endif
