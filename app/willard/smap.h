///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\..\app\willard\smap.ph".
///////////////////////////////////////////////////////////////////////////////

#define PROP_TUPLE2_USED
#include <propdefs.h>
#line 1 "../../../app/willard/smap.ph"
#ifndef smap_h
#define smap_h

#include <AD/hash/lhash.h>

//
//  Single valued map
//
template <class K, class V>
class SMap : public LHashTable<K, V>
{  
};

template <class A, class B>
   inline int hash (const 
#line 15 "../../../app/willard/smap.ph"
Tuple2<A, B>  
#line 15 "../../../app/willard/smap.ph"
& x) { return hash(x._1) + hash(x._2); }

template <class A, class B>
   inline int equal (const Tuple2<A, B>  
#line 18 "../../../app/willard/smap.ph"
& x, const Tuple2<A, B>  
#line 18 "../../../app/willard/smap.ph"
& y) 
      { return equal(x._1,y._1) && equal(x._2,y._2); }

#endif
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 0
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
