#ifndef persistent_input_stream_implementation_h
#define persistent_input_stream_implementation_h

#define PSTREAM_IMPLEMENTATION
#include <AD/persist/pconfig.h>
#include <AD/persist/ptype.h>
#include <AD/contain/vararray.h>
#include <AD/contain/varptrarray.h>

//////////////////////////////////////////////////////////////////////////////
//  The marker log is simply implemented as an array table indexed
//  by the markers
//////////////////////////////////////////////////////////////////////////////

class PMarkerLog
{
  void operator = (const PMarkerLog&);
  PMarkerLog(const PMarkerLog&);
public:
  VarArray<PObject *>            objects;  // set of pointers serialized
  VarArray<PObjectType::Entry *> object_types;
  PMarkerLog(int n);
  ~PMarkerLog();
  void clean();
};

#endif
