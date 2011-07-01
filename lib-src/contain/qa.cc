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
#include <AD/contain/array.h>     // Arrays
#include <AD/contain/arraycol.h>  // Array collections
#include <AD/contain/charset.h>   // Set of ASCII characters
#include <AD/contain/dchbag.h>    // Multiset
#include <AD/contain/dchset.h>    // Set
#include <AD/contain/dchmap.h>    // Associative table
#include <AD/contain/fixstack.h>  // Fixed sized stack
#include <AD/contain/fixqueue.h>  // Fixed sized queue
#include <AD/contain/intset.h>    // Set of integers
#include <AD/contain/linklist.h>  // Linked lists
#include <AD/contain/priqueue.h>  // Priority queue
#include <AD/contain/queue.h>     // Queues
#include <AD/contain/seq.h>       // Sequences
#include <AD/contain/stack.h>     // Stacks
#include <AD/contain/unionfnd.h>  // Union find data structure
#include <AD/contain/vararray.h>  // Variable sized array
#include <AD/contain/varqueue.h>  // Variable sized queue
#include <AD/contain/varstack.h>  // Variable sized stack

int main(int argc, char * argv[])
{
  CharSet C;
  DCHBag<char *> bag;
  DCHSet<char *> set;
  DCHMap<char *,char *> M;
  FixStack<int,100> S;
  VarStack<char *> s1, s2;
  Seq<char> text;
  PriQueue<int, Array<int> > pq(256);
  LinkedList<char *> list;
  VarArray<char *> array(0,3);

  C.clear();
  C += 'a';
  C += 'b';
  assert(C.size() == 2);

  S.push(1);
  S.push(2);
  S.push(3);
  S.pop();
  assert(S.size() == 2);

  s1.push("allen");
  s1.push("leung");
  s2 = s1;
  s2.pop();
  assert(s1.size() == 2);
  assert(s2.size() == 1);

  M[ "John" ]     = "Gleese";
  M[ "Neal"  ]    = "Skyer";
  M[ "Freud" ]    = "Fraud";
  M[ "Judy" ]     = "Davis";
  M[ "Robert" ]   = "DeNiro";
  M[ "Lawrence" ] = "Oliver";
  M[ "Woody" ]    = "Allen";
  M[ "Harrison" ] = "Ford";
  M[ "Mickey" ]   = "Rourke";
  M[ "Humphry" ]  = "Bogart";

  for (Ix i = M.first(); i; i = M.next(i))
    printf("First = %s, last = %s\n", M.key(i), M.value(i));

  assert(M.size() == 10);

  ((list += "Bell") += "Cleary") += "Witten";

  assert(list.length() == 3);

  for (LinkedListIter<char *> j = list; j; j++)
    printf("Name = %s\n", j());

  array[0] = "Eva";
  array[1] = "Luna";
  array[2] = "Isaac";
  array[3] = "Albeniz";
  array[4] = "Villa";
  array[5] = "Lobos";
  array[-2] = "Manuel";
  array[-1] = "Ponce";

  for (int n = -2; n <= 5; n++)
    printf("array[%d] = %s\n", n, array[n]);

  VarQueue<int> VQ;
  for (n = 0; n < 20; n++)
    VQ.insertTail(n);
  while (! VQ.isEmpty())
  {
    printf("%d ",VQ.removeHead());
  }
  printf("\n");

  ArrayCollection< int, Array<int> > ac;

  printf("OK\n");
  return 0;
}
