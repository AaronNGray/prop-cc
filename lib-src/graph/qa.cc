#include <AD/graph/graph.h>
#include <stdlib.h>

int main()
{
  GraphObject G;

  for (NodeSet::iterator i = G.nodes(); i; i++)
  {
    const NodeObject * n = *i;
    if (n)
      exit(1);
  }
  return 0;
}
