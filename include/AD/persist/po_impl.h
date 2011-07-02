#ifndef pstd::ostream_implementation_h
#define pstd::ostream_implementation_h
#include <stdlib.h>
#include <string>
#include <AD/hash/lhash2.h>       // linear probing hash table
#include <AD/contain/variset.h>   // variable length integer set

//////////////////////////////////////////////////////////////////////////////
//  The object log is implemented simply as a hash table.
//
//  Object log maps object pointers to
//
//////////////////////////////////////////////////////////////////////////////

class PObjectOrdering
{
public:
  inline static unsigned int hash (P_ObjectAddr obj)
  {
    return (unsigned int)obj;
  }
  inline static Bool equal (P_ObjectAddr a, P_ObjectAddr b)
  {
    return a == b;
  }
};

class PObjectLog
{
  void operator = (const PObjectLog&);
  PObjectLog(const PObjectLog&);
public:
  struct PObjectInfo
  {
    const PObject * obj;
    P_OBJECT_MARKER marker;
    inline PObjectInfo()
    {}
    inline PObjectInfo(const PObject * p, P_OBJECT_MARKER m)
        : obj(p), marker(m)
    {}
  }
  ;
  LHashTable2<P_ObjectAddr, PObjectLog::PObjectInfo, PObjectOrdering> markers;
  VarIntSet object_types;
  PObjectLog(int n);
  ~PObjectLog();
  void clean();
};

#endif
