///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.3.8),
//  last updated on Sep 16, 2005.
//  The original source file is "..\..\prop-src\list.ph".
///////////////////////////////////////////////////////////////////////////////

#line 1 "../../prop-src/list.ph"
#ifndef list_operations_h
#define list_operations_h

#include "basics.h"

template <class T>
  int length( 
#line 7 "../../prop-src/list.ph"
a_List<T> *  
#line 7 "../../prop-src/list.ph"
 l)
  {
    int len = 0;
    
#line 12 "../../prop-src/list.ph"
{
  for (;;) {
    if (l) {
#line 12 "../../prop-src/list.ph"
     l = l->_2; len++; 
#line 12 "../../prop-src/list.ph"
    } else { goto L1; }
  }
  L1:;
}
#line 13 "../../prop-src/list.ph"
#line 13 "../../prop-src/list.ph"

    return len;
  }

template <class T>
  
#line 18 "../../prop-src/list.ph"
a_List<T> *  
#line 18 "../../prop-src/list.ph"
 append( a_List<T> *  
#line 18 "../../prop-src/list.ph"
 a, a_List<T> *  
#line 18 "../../prop-src/list.ph"
 b)
  {
    
#line 23 "../../prop-src/list.ph"
{
  if (a) {
#line 23 "../../prop-src/list.ph"
   return 
#line 23 "../../prop-src/list.ph"
#line 23 "../../prop-src/list.ph"
    list_1_(a->_1,append(a->_2,b))
#line 23 "../../prop-src/list.ph"
#line 23 "../../prop-src/list.ph"
    ; 
#line 23 "../../prop-src/list.ph"
  } else {
#line 22 "../../prop-src/list.ph"
   return b; 
#line 22 "../../prop-src/list.ph"
  }
}
#line 24 "../../prop-src/list.ph"
#line 24 "../../prop-src/list.ph"

  }

template <class T>
  
#line 28 "../../prop-src/list.ph"
a_List<T> *  
#line 28 "../../prop-src/list.ph"
 rev( a_List<T> *  
#line 28 "../../prop-src/list.ph"
 a)
  {
    a_List<T> *  
#line 30 "../../prop-src/list.ph"
 b = 
#line 30 "../../prop-src/list.ph"
nil_1_
#line 30 "../../prop-src/list.ph"
#line 30 "../../prop-src/list.ph"
;
    
#line 31 "../../prop-src/list.ph"
#line 33 "../../prop-src/list.ph"
{
  for (;;) {
    if (a) {
#line 33 "../../prop-src/list.ph"
     b = 
#line 33 "../../prop-src/list.ph"
#line 33 "../../prop-src/list.ph"
      list_1_(a->_1,b)
#line 33 "../../prop-src/list.ph"
#line 33 "../../prop-src/list.ph"
      ; a = a->_2; 
#line 33 "../../prop-src/list.ph"
    } else { goto L2; }
  }
  L2:;
}
#line 34 "../../prop-src/list.ph"
#line 34 "../../prop-src/list.ph"

    return b;
  }

#endif
#line 39 "../../prop-src/list.ph"
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
