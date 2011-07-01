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
  if (RegExp("[a-z]+").match("The quick brown fox jumps over the lazy dog")
      == 1)
    printf("matched\n");
  else
    printf("unmatched\n");

  const char * a = "The quick brown fox";
  const char * b = "The lazy dog";
  const char * c = "The quick brown fox";
  KMP kmp = "The";
  assert(kmp.match(a) == 0);
  kmp = "fox";
  assert(kmp.match(a) == 16);
  kmp = "dog";
  assert(kmp.match(b) == 9);
  assert(kmp.match(c) == -1);
  kmp = "XYXYZ";
  assert(kmp.match("abcdeXYXYXYYXYXYZXXY") == 12);
  printf("located\n");

  BoyerMoore bm;
  bm = "XYXYZ";
  assert(bm.match("abcdeXYXYXYYXYXYZXXY") == 12);
  bm = "WXYZ";
  assert(bm.match("abcdWXYWYXYWXYXYWXYZ") == 16);
  bm = "ZXYXY";
  assert(bm.match("abcdWXYWYZYWXZXYWXYZXYXYZ") == 19);
  bm = "variable length";
  assert(bm.match(
           "Description: TeX macros for drawing variable length wiggily lines.")
         == 36);

  KR kr;
  kr = "XYXYZ";
  assert(kr.match("abcdeXYXYXYYXYXYZXXY") == 12);
  kr = "WXYZ";
  assert(kr.match("abcdWXYWYXYWXYXYWXYZ") == 16);
  kr = "ZXYXY";
  assert(kr.match("abcdWXYWYZYWXZXYWXYZXYXYZ") == 19);

  Quark q = "The quick brown fox";
  Quark s = "The lazy dog";
  Quark r = "The quick brown fox";
  Quark t;

  t = s;
  assert(q != s && q == r && t == s);

  RegExp re = "fox";
  assert(re.ok());
  assert(re.match("The quick brown fox") == 16);
  assert(re.match("The quick brown fofox") == 18);
  RegExp re2 = re;
  assert(re2.match("The quick brown fofox") == 18);
  assert(re2.match("The lazy dog f") == -1);

  re = "fox$";
  assert(re.match("The quick brown fox") == 16);

  RegExp dirname = "^((\\w*/)*)([^/]+)$";
  assert(dirname.ok());
  printf("%d\n",dirname.match("/usr/etc/net/spool/worm.hack\n"));
  assert(dirname.match("/usr/etc/net/spool/worm.hack\n") >= 0);
  assert(dirname.match("/usr/etc/net/spool/worm.hack") >= 0);

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
