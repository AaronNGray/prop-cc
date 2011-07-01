#include <AD/graph/node.h>
#include <AD/pretty/postream.h>

NodeObject::~NodeObject() {}

PrettyOStream& NodeObject::print(PrettyOStream& S) const
{
  return S << '[' << "node" << label_num() << ']';
}
