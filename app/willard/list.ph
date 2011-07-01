#ifndef list_util_h
#define list_util_h

#include "willard-ast.ph"

template <class T>
   List<T> append (List<T> a, List<T> b)
   {  match (a) of
         #[]:        { return b; }
      |  #[h ... t]: { return #[h ... append(t,b)]; }
      end match;
   }

template <class T>
   List<T> rev (List<T> a)
   {  List<T> r = #[];
      match while (a) of
         #[h ... t]: { r = #[h ... r]; a = t; }
      end match;
      return r;
   }

template <class T>
   int length (List<T> a)
   {  int i = 0;
      match while (a) of
	 #[_ ... t]: { a = t; i++; }
      end match;
      return i;
   }

#endif
