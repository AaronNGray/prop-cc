///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.5),
//  last updated on Jun 18, 1997.
//  The original source file is "list.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REWRITING_USED
#define PROP_STRCMP_USED
#define PROP_QUARK_USED
#include <propdefs.h>
#line 1 "list.ph"
#ifndef list_util_h
#define list_util_h

#include "willard-ast.h"

template <class T>
   
#line 7 "list.ph"
a_List<T> *  
#line 7 "list.ph"
 append (a_List<T> *  
#line 7 "list.ph"
 a, a_List<T> *  
#line 7 "list.ph"
 b)
   {  
#line 10 "list.ph"
{
   if (a) {
#line 10 "list.ph"
     return 
#line 10 "list.ph"
#line 10 "list.ph"
      list_1_(a->_1,append(a->_2,b))
#line 10 "list.ph"
#line 10 "list.ph"
      ; 
#line 10 "list.ph"
   } else {
#line 9 "list.ph"
     return b; 
#line 9 "list.ph"
   }
}
#line 11 "list.ph"
#line 11 "list.ph"

   }

template <class T>
   
#line 15 "list.ph"
a_List<T> *  
#line 15 "list.ph"
 rev (a_List<T> *  
#line 15 "list.ph"
 a)
   {  a_List<T> *  
#line 16 "list.ph"
 r = 
#line 16 "list.ph"
nil_1_
#line 16 "list.ph"
#line 16 "list.ph"
;
      
#line 17 "list.ph"
#line 18 "list.ph"
{
   for (;;) {
      if (a) {
#line 18 "list.ph"
        r = 
#line 18 "list.ph"
#line 18 "list.ph"
         list_1_(a->_1,r)
#line 18 "list.ph"
#line 18 "list.ph"
         ; a = a->_2; 
#line 18 "list.ph"
      } else { goto L1; }
   }
   L1:;
}
#line 19 "list.ph"
#line 19 "list.ph"

      return r;
   }

template <class T>
   int length (
#line 24 "list.ph"
a_List<T> *  
#line 24 "list.ph"
 a)
   {  int i = 0;
      
#line 27 "list.ph"
{
   for (;;) {
      if (a) {
#line 27 "list.ph"
        a = a->_2; i++; 
#line 27 "list.ph"
      } else { goto L2; }
   }
   L2:;
}
#line 28 "list.ph"
#line 28 "list.ph"

      return i;
   }

#endif
#line 33 "list.ph"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 2
Number of ifs generated      = 3
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
