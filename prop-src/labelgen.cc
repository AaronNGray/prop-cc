#include "labelgen.h"
#include <AD/strings/quark.h>

LabelGen:: LabelGen(const char * p) : prefix(p), counter(0)
{
  last = "";
}

LabelGen::~LabelGen()
{}

const char * LabelGen::new_label()
{
  return last = Quark( prefix, Quark( ++counter));
}
