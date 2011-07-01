//  Test some numeric stuff

#include <stdio.h>
#include <iostream.h>
#include <assert.h>
#include <AD/numeric/bigint.h>
#include <AD/numeric/complex.h>
#include <AD/numeric/matrix.h>
#include <AD/numeric/ratio.h>
#include <AD/numeric/z.h>

int main(int argc, char * argv[])
{  Z<9> a = 0, b = 1, c = 0;

   assert(sizeof(a) == 4); 
   assert(a != b && a == c);

   Complex i(0,1);

   assert (i * i == -1);

   BigInt x = 123456, y = 8765;
   cout << x << " % " << y << " = " << (x%y) << '\n';
   cout << x << " / " << y << " = " << (x/y) << '\n';
   cout << x << " * " << y << " = " << (x*y) << '\n';
   cout << x << " + " << y << " = " << (x+y) << '\n';
   cout << x << " - " << y << " = " << (x-y) << '\n';

   cout << x << " % " << y << " = " << (123456%8765) << '\n';
   cout << x << " / " << y << " = " << (123456/8765) << '\n';
   cout << x << " * " << y << " = " << (123456*8765) << '\n';
   cout << x << " + " << y << " = " << (123456+8765) << '\n';
   cout << x << " - " << y << " = " << (123456-8765) << '\n';

   assert (x % y == 123456%8765);
   assert (x / y == 123456/8765);
   assert (x * y == 123456*8765);
   assert (x + y == 123456+8765);
   assert (x - y == 123456-8765);

   BigInt fact = 1;
   int limit = 100;
   if (argc == 2) sscanf(argv[1],"%d",&limit);
   for (int n = 1; n <= limit; n++) {   
      fact *= n;
   }
   cout << "Done\n"; cout.flush();
   cout << "  my fact(" << limit << ") = " << fact << '\n';

   BigInt fact2 = 
      "93326215443944152681699238856266700490715968264381621468592963895217"
      "59999322991560894146397615651828625369792082722375825118521091686400"
      "0000000000000000000000";

   cout << "real fact(" << limit << ") = " << fact2 << '\n';
   assert(fact == fact2);

   //for (n = 1; n <= 10000; n++) fact /= n;
   //cout << "one = " << fact << '\n';

   printf("OK\n");
   return 0;
}
