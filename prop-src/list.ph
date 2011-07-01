#ifndef list_operations_h
#define list_operations_h

#include "basics.ph"

template <class T>
  int length( List<T> l)
  {
    int len = 0;
    match while (l)
    {
      #[ _ ... t]: { l = t; len++; }
    }
    return len;
  }

template <class T>
  List<T> append( List<T> a, List<T> b)
  {
    match (a)
    {
      #[]:        { return b; }
    | #[h ... t]: { return #[ h ... append(t, b)]; }
    }
  }

template <class T>
  List<T> rev( List<T> a)
  {
    List<T> b = #[];
    match while (a)
    {
      #[one ... rest]: { b = #[ one ... b ]; a = rest; }
    }
    return b;
  }

#endif
