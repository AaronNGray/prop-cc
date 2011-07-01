#ifndef dataflow_analyzer_base_class_h
#define dataflow_analyzer_base_class_h

#include <AD/generic/generic.h>
#include <AD/memory/mem.h>

class FlowGraphBase;

class DataflowBasic
{
  DataflowBasic(const DataflowBasic&);
  void operator = (const DataflowBasic&);

protected:

  Mem& mem;      // internal memory manager
  Bool changed;  // state has changed

public:
  DataflowBasic(Mem&);
  virtual ~DataflowBasic();

  virtual void analyze(FlowGraphBase&);

protected:

  virtual void construct_evaluation_graph (FlowGraphBase&) = 0;
  virtual void simplify_evaluation_graph ();
  virtual void compute_fixpoint () = 0;
};

#endif
