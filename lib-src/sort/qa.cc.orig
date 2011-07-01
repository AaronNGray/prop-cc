#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <AD/sort/bubble.h>     // bubble sort 
#include <AD/sort/insort.h>     // Insertion sort
#include <AD/sort/heapsort.h>   // Heap sort 
#include <AD/sort/mergesrt.h>   // Merge sort
#include <AD/sort/quicksrt.h>   // Quicker sort
#include <AD/sort/radixsrt.h>   // Radix sort
#include <AD/sort/shellsrt.h>   // Shell sort 
#include <AD/sort/bubble2.h>    // bubble sort 
#include <AD/sort/insort2.h>    // Insertion sort
#include <AD/sort/heapsrt2.h>   // Heap sort 
#include <AD/sort/shellst2.h>   // Shell sort 

int sorted(const char * names[], int size)
{
   for (int i = 0; i < size - 1; i++)
      if (strcmp(names[i],names[i+1]) >= 0) return 0;
   return 1;
}

int rev_sorted(const char * names[], int size)
{
   for (int i = 0; i < size - 1; i++)
      if (strcmp(names[i],names[i+1]) <= 0) return 0;
   return 1;
}

void pr(const char * algorithm, const char * names[], int size) 
{   printf("%s: [ ",algorithm);
    for (int i = 0; i < size; i++) {
       printf("%s",names[i]);
       if (i < size - 1) printf(", ");
    }
    printf(" ]\n");
}

int main(int argc, char * argv[])
{  static const char * people[] = 
      { "Godel", "Post", "Russel", "Church", "Turing",
        "Thue", "von Neuman", "Davis", "Scott", "Rogers",
        "Newton", "Euler", "Markov", "Herbrand", "Bucchi",
        "Kleene", "Skolem", "Martin Lof", "Zemelo", "Fraenkel",  
        "Euclid", "Rice", "Cantor", "Dedekind", "Taylor",
        "Fermat", "Hilbert", "Riemann", "Jacobi", "Dirichlet"
      };

    const char * names[sizeof(people)/sizeof(people[0])];
        
    memcpy(names,people,sizeof(people));
    heapSort(const char *, names, sizeof(names)/sizeof(names[0]),
             strcmp(key,names[i]) < 0);
    pr ("Heap sort",names, sizeof(names)/sizeof(names[0]));
    assert ( sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    heapSort(const char *, names, sizeof(names)/sizeof(names[0]),
             strcmp(key,names[i]) > 0);
    pr ("Heap sort",names, sizeof(names)/sizeof(names[0]));
    assert ( rev_sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    bubbleSort(const char *, names, sizeof(names)/sizeof(names[0]),
               strcmp(names[i],names[i+1]) < 0);
    pr ("Bubble sort",names, sizeof(names)/sizeof(names[0]));
    assert ( sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    bubbleSort(const char *, names, sizeof(names)/sizeof(names[0]),
               strcmp(names[i],names[i+1]) > 0);
    pr ("Bubble sort",names, sizeof(names)/sizeof(names[0]));
    assert ( rev_sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    shellSort(const char *, names, sizeof(names)/sizeof(names[0]),
              strcmp(key,names[i]) < 0);
    pr ("Shell sort",names, sizeof(names)/sizeof(names[0]));
    assert ( sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    shellSort(const char *, names, sizeof(names)/sizeof(names[0]),
              strcmp(key,names[i]) > 0);
    pr ("Shell sort",names, sizeof(names)/sizeof(names[0]));
    assert ( rev_sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    insertionSort(const char *, names, sizeof(names)/sizeof(names[0]),
              strcmp(key,names[i]) < 0);
    pr ("Insertion sort",names, sizeof(names)/sizeof(names[0]));
    assert ( sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    insertionSort(const char *, names, sizeof(names)/sizeof(names[0]),
              strcmp(key,names[i]) > 0);
    pr ("Insertion sort",names, sizeof(names)/sizeof(names[0]));
    assert ( rev_sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    quickSort(const char *, names, sizeof(names)/sizeof(names[0]),
              strcmp(key,A[i]) < 0);
    pr ("Quick sort",names, sizeof(names)/sizeof(names[0]));
    assert ( sorted(names, sizeof(names)/sizeof(names[0]) ) );

    memcpy(names,people,sizeof(people));
    quickSort(const char *, names, sizeof(names)/sizeof(names[0]),
              strcmp(key,A[i]) > 0);
    pr ("Quick sort",names, sizeof(names)/sizeof(names[0]));
    assert ( rev_sorted(names, sizeof(names)/sizeof(names[0]) ) );


    printf("OK\n");
    return 0;
}
