//  Test strings

#include <stdio.h>
#include <assert.h>
#include <AD/strings/bm.h>      // Boyer Moore
#include <AD/strings/kmp.h>     // Knuth Morris Pratt
#include <AD/strings/kr.h>      // Karp Rabin 
#include <AD/strings/quark.h>   // Atomic strings
#include <AD/strings/regexp.h>  // Regular expression search
#include <AD/strings/string.h>  // Dynamic strings
#include <AD/strings/twoway.h>  // Two way string matcher

int main(int argc, char * argv[])
{  
   if (RegExp("[a-z]+").Match("The quick brown fox jumps over the lazy dog")
        == 1) 
      printf("matched\n");
   else 
      printf("unmatched\n");

   const char * a = "The quick brown fox";
   const char * b = "The lazy dog";
   const char * c = "The quick brown fox";
   KMP kmp ("The");
   assert(kmp.Match(a) == 0);
   kmp = "fox";
   assert(kmp.Match(a) == 16);
   kmp = "dog";
   assert(kmp.Match(b) == 9);
   assert(kmp.Match(c) == -1);
   kmp = "XYXYZ";
   assert(kmp.Match("abcdeXYXYXYYXYXYZXXY") == 12);
   printf("located\n");

   BoyerMoore bm;
   bm = "XYXYZ";
   assert(bm.Match("abcdeXYXYXYYXYXYZXXY") == 12);
   bm = "WXYZ";
   assert(bm.Match("abcdWXYWYXYWXYXYWXYZ") == 16);
   bm = "ZXYXY";
   assert(bm.Match("abcdWXYWYZYWXZXYWXYZXYXYZ") == 19);
   bm = "variable length";
   assert(bm.Match(
      "Description: TeX macros for drawing variable length wiggily lines.") 
       == 36);

   KR kr;
   kr = "XYXYZ";
   assert(kr.Match("abcdeXYXYXYYXYXYZXXY") == 12);
   kr = "WXYZ";
   assert(kr.Match("abcdWXYWYXYWXYXYWXYZ") == 16);
   kr = "ZXYXY";
   assert(kr.Match("abcdWXYWYZYWXZXYWXYZXYXYZ") == 19);

   Quark q = "The quick brown fox";
   Quark s = "The lazy dog";
   Quark r = "The quick brown fox";
   Quark t;

   t = s;
   assert(q != s && q == r && t == s);

   RegExp re = "fox";
   assert(re.ok());
   assert(re.Match("The quick brown fox") == 16); 
   assert(re.Match("The quick brown fofox") == 18);
   RegExp re2 = re;
   assert(re2.Match("The quick brown fofox") == 18);
   assert(re2.Match("The lazy dog f") == -1);
   
   re = "fox$";
   assert(re.Match("The quick brown fox") == 16); 

   RegExp dirname = "^((\\w*/)*)([^/]+)$";
   assert(dirname.ok());
   printf("%d\n",dirname.Match("/usr/etc/net/spool/worm.hack\n"));
   assert(dirname.Match("/usr/etc/net/spool/worm.hack\n") >= 0);
   assert(dirname.Match("/usr/etc/net/spool/worm.hack") >= 0);

   printf("dir = %*.*s, base = %*.*s\n",
          dirname.len(0), dirname.len(0), dirname[0],
          dirname.len(2), dirname.len(2), dirname[2]);

   printf("start(0) = %d\n", dirname.start(0));
   printf("len(0) = %d\n", dirname.len(0));
   printf("start(2) = %d\n", dirname.start(2));
   printf("len(2) = %d\n", dirname.len(2));

   assert(dirname.start(0) == 0);
   assert(dirname.len(0) == 19);
   assert(dirname.start(2) == 19);
   assert(dirname.len(2) == 9);
      
   printf("OK\n");

   return 0;
}
