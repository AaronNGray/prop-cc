//  Test tries stuff

#include <assert.h>
#include <stdio.h>
#include <AD/tries/briandai.h>
#include <AD/tries/hashtrie.h>
#include <AD/tries/patricia.h>
#include <AD/tries/trie.h>

int main()
{
   Trie<256,char *> trie;
   HashTrie t(1024);
   Briandais b;

   printf("OK\n");
   return 0;
}
