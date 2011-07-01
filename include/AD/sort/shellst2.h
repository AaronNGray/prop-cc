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

#ifndef Shellsort2_h
#define Shellsort2_h

#include <AD/sort/sorting2.h>
//
//  Shell sort\cite{algo-hand-book}
//
//  e.g: shellSort2(char *, int, names, salaries, 100, strcmp(key,names[i]) < 0);
//

/////////////////////////////////////////////////////////////////////////////
// Macro version
/////////////////////////////////////////////////////////////////////////////

#define shellSort2(KEY,VALUE,A,B,N,predicate)                                 \
   do {                                                                       \
      for ( register int gap = (N); gap > 1; ) {                              \
         if (gap < 5) gap = 1;                                                \
         else gap = (5 * gap - 1) / 11;                                       \
         for (register int j = (N) - gap; j >= 0; j--) {                      \
            register KEY   key   = (A)[j];                                    \
            register VALUE value = (B)[j];                                    \
            for (register int i = j + gap; i < (N) && !(predicate); i += gap){\
               (A)[i-gap] = (A)[i];                                           \
               (B)[i-gap] = (B)[i];                                           \
            }                                                                 \
            (A)[i-gap] = key;                                                 \
            (B)[i-gap] = value;                                               \
         }                                                                    \
      }                                                                       \
   } while(0)

/////////////////////////////////////////////////////////////////////////////
// Template version
/////////////////////////////////////////////////////////////////////////////

template <class K, class V, class Ord>
class ShellSort2 : public Sorting2<K,V,Ord>
{
public:
  void sort(int, K [], V []);
};

template <class K, class V, class Ord>
void ShellSort2<K,V,Ord>::sort(int N, K keys[], V values[])
{
  shellSort2(K, V, keys, values, N, Ord::less(key, keys[i]));
}

#endif
