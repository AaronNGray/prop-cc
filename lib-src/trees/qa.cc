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

#include <assert.h>
#include <stdio.h>
#include <AD/trees/avl.h>
#include <AD/trees/splay.h>
#include <AD/trees/leftist.h>
#include <AD/trees/pagoda.h>

typedef const char * string;

void print_tree( BinaryTree< string, string>& tree, Ix i)
{
  if (i == 0)
  {
    printf(".");
    return;
  }
  printf("%s(",tree.key(i));
  print_tree(tree,tree.left(i));
  printf(",");
  print_tree(tree,tree.right(i));
  printf(")");
}

int main()
{
  AVLTree<string,string> avl;
  SplayTree<string,string> splay;
  LeftistTree<string,string> leftist;
  Pagoda<string,string> pagoda;

  static struct
  {
    string first, last;
  }
  authors[] =
    {  { "Edgar",    "Doctorow"   },
       { "James",    "Joyce"      },
       { "Vladimir", "Nabokov"    },
       { "Pablo",    "Neruda",    },
       { "William",  "Faulkner",  },
       { "Ernest",   "Hemingway"  },
       { "Gabriel",  "Garcia Marquez" },
       { "Isabel",   "Allende" },
       { "Thomas",   "Pynchon" },
       { "Kurt",     "Vonnegurt" },
       { "Ken",      "Casey" },
       { "Norman",   "Mailer" },
    };

  static struct
  {
    string first, last;
  }
  old_authors[] =
    {  { "William", "Shakespear" },
       { "Edgar",   "Poe" },
       { "Thomas",  "Jefferson" }
    };

  int size = sizeof(authors)/sizeof(authors[0]);
  int i, n;
  Ix ix, iy;
  int count;


  for (i = 0; i < sizeof(old_authors)/sizeof(old_authors[0]); i++)
  {
    avl.insert(old_authors[i].first, old_authors[i].last);
    assert(avl.contains(old_authors[i].first));
    assert(avl.avl_balanced());
    splay.insert(old_authors[i].first, old_authors[i].last);
    assert(splay.contains(old_authors[i].first));
  }

  for (i = 0; i < size; i++)
  {
    avl.insert(authors[i].first, authors[i].last);
    assert(avl.contains(authors[i].first));
    assert(avl.avl_balanced());
    splay.insert(authors[i].first, authors[i].last);
    assert(splay.contains(authors[i].first));
  }

  printf( "AVL tree: size = %d\n", avl.size());
  for (count = 0, ix = avl.first(); ix; ix = avl.next(ix), count++)
    printf("[%s %s] ", avl.key(ix), avl.value(ix));
  printf("\n");
  assert(count == size);

  for (count = 0, ix = avl.last(); ix; ix = avl.prev(ix), count++)
    ;
  assert(count == size);

  printf( "Splay tree: size = %d\n", splay.size());
  for (count = 0, ix = splay.first(); ix; ix = splay.next(ix), count++)
    printf("[%s %s] ", splay.key(ix), splay.value(ix));
  printf("\n");
  assert(count == size);

  for (count = 0, ix = splay.last(); ix; ix = splay.prev(ix), count++)
    ;
  assert(count == size);

  for (i = 0; i < size; i++)
  {
    assert(avl.remove(authors[i].first));
    assert(avl.lookup(authors[i].first) == 0);
    assert(avl.avl_balanced());
    for (count = 0, ix = avl.first(); ix; ix = avl.next(ix), count++)
      ;
    assert(count == size - i - 1);
    for (count = 0, ix = avl.last(); ix; ix = avl.prev(ix), count++)
      ;
    assert(count == size - i - 1);
  }
  assert(avl.size() == 0);

  for (i = 0; i < size; i++)
  {
    assert(splay.remove(authors[i].first));
    assert(splay.lookup(authors[i].first) == 0);
    for (count = 0, ix = splay.first(); ix; ix = splay.next(ix), count++)
      ;
    assert(count == size - i - 1);
    for (count = 0, ix = splay.last(); ix; ix = splay.prev(ix), count++)
      ;
    assert(count == size - i - 1);
  }
  assert(splay.size() == 0);

  for (i = 0; i < size; i++)
    leftist.insert(authors[i].first,authors[i].last);
  assert(leftist.size() == size);

  for (i = 0; i < size; i++)
    pagoda.insert(authors[i].first,authors[i].last);
  assert(pagoda.size() == size);

  while (! leftist.isEmpty())
  {
    ix = leftist.min();
    printf("[%s %s] ",leftist.key(ix),leftist.value(ix));
    assert(leftist.delete_min());
  }
  printf("\n");
  assert(leftist.size() == 0);

  while (! pagoda.isEmpty())
  {
    ix = pagoda.min();
    printf("[%s %s] ",pagoda.key(ix),pagoda.value(ix));
    assert(pagoda.delete_min());
  }
  printf("\n");
  assert(pagoda.size() == 0);

  printf("OK\n");
  return 0;
}
