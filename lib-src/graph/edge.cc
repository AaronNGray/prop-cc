#include <AD/graph/edge.h>
#include <AD/graph/node.h>
#include <AD/pretty/postream.h>

EdgeObject::~EdgeObject()
{}

PrettyOStream& EdgeObject::print(PrettyOStream& S) const
{
  S << '(';
  the_src->print(S);
  S << ',';
  the_dst->print(S);
  S << ')';

  return S;
}
