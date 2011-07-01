//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream.h>
#include <assert.h>
#include <AD/numeric/bigint.h>
#include <AD/numeric/complex.h>
#include <AD/numeric/matrix.h>
#include <AD/numeric/ratio.h>
#include <AD/numeric/z.h>

int main(int argc, char * argv[])
{
  Z<9> a = 0, b = 1, c = 0;

  assert(sizeof(a) == 4);
  assert(a != b && a == c);

  Complex i(0,1);

  assert (i * i == -1);

  /*
  BigInt x = 123456, y = 8765;
  std::cout << x << " % " << y << " = " << (x%y) << '\n';
  std::cout << x << " / " << y << " = " << (x/y) << '\n';
  std::cout << x << " * " << y << " = " << (x*y) << '\n';
  std::cout << x << " + " << y << " = " << (x+y) << '\n';
  std::cout << x << " - " << y << " = " << (x-y) << '\n';

  std::cout << x << " % " << y << " = " << (123456%8765) << '\n';
  std::cout << x << " / " << y << " = " << (123456/8765) << '\n';
  std::cout << x << " * " << y << " = " << (123456*8765) << '\n';
  std::cout << x << " + " << y << " = " << (123456+8765) << '\n';
  std::cout << x << " - " << y << " = " << (123456-8765) << '\n';
  */

  BigInt fact = 1;
  int limit = 100;
  if (argc == 2)
    sscanf(argv[1],"%d",&limit);
  for (int n = 1; n <= limit; n++)
  {
    fact *= n;
  }
  std::cout << "Done\n";
  std::cout.flush();
  std::cout << "fact(" << limit << ") = " << fact << '\n';

  //for (n = 1; n <= 10000; n++) fact /= n;
  //std::cout << "one = " << fact << '\n';

  printf("OK\n");
  return 0;
}
