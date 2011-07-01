#include <iostream.h>
#include "elem.h"

int main()
{
  SETLelem<int> a;
  SETLelem<int> b;
  SETLelem<int> c;

  a = 1;
  b = 2;
  a = a + 1;
  // a += 10;

  cout << "a = " << a << '\n';
  return 0;
}
