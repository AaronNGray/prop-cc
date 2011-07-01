#ifndef dataflow_domain_h
#define dataflow_domain_h

#include <AD/generic/generic.h>

class DataflowDomain
{
public:
  DataflowDomain();
  virtual ~DataflowDomain();
public:

  virtual Bool top() = 0;
  virtual Bool bot() = 0;
  virtual Bool meet_with(DataflowDomain&) = 0;
  virtual Bool join_with(DataflowDomain&) = 0;
};

#endif
