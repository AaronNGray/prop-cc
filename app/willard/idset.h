#ifndef id_set_h
#define id_set_h

#include "willard-ast.ph"
#include <AD/hash/lhash.h>

class IdSet : public LHashTable<Id, Id>
{  typedef LHashTable<Id,Id> Super;
public:
   inline void insert(Id id) { Super::insert(id,id); }
};

#endif
