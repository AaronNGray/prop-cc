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

#ifndef bubble_sort2_h
#define bubble_sort2_h

#include <AD/sort/sorting2.h>

//
// Lazy bubble sort, for those who don't care for anything better.
//
// e.g.:  bubbleSort2(char *, int, names, salaries, 100, strcmp(names[i], names[i+1]) < 0);
//

/////////////////////////////////////////////////////////////////////////////
//  Macro version
/////////////////////////////////////////////////////////////////////////////
#define bubbleSort2(KEY,VALUE,A,B,N,predicate)    \
  do                                              \
  {                                               \
    for (register int j = (N) - 1; j >= 0; j--)   \
    {                                             \
      for (register int i = 0; i < j; i++)        \
      {                                           \
        if (! (predicate))                        \
        {                                         \
          register KEY   key   = A[i];            \
          register VALUE value = B[i];            \
          A[i] = A[i+1]; A[i+1] = key;            \
          B[i] = B[i+1]; B[i+1] = value;          \
        }                                         \
      }                                           \
    }                                             \
  } while(0)

/////////////////////////////////////////////////////////////////////////////
//  Template version
/////////////////////////////////////////////////////////////////////////////

template <class K, class V, class Ord>
class BubbleSort2 : public Sorting2<K,V,Ord>
{
public:
  void sort(int, K [], V []);
};

template <class K, class V, class Ord>
void BubbleSort2<K,V,Ord>::sort(int N, K keys[], V values[])
{
  bubbleSort2(K, V, keys, values, N, Ord::less(keys[i], keys[i+1]));
}

#endif
