#include <stdlib.h>
#include <iostream.h>
#include <AD/memory/mempool.h>
#include <AD/contain/fbitset.h>

int main()
{
  MemPool mem;
  int N = 128;
  FastBitSet set
    (mem,N);
  for (int i = 0; i < N; i++)
  {
    int j = drand48() * N;
    std::cerr << "+" << j << ' ';
    set.add(j);
    std::cerr << set
      << '\n';
  }
  return 0;
}
