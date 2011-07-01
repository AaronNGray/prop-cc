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
#include <stdlib.h>
#include <AD/strings/kr.h>

int grep( const char* fileName, FILE* file, KR& pattern)
{
   char buffer[BUFSIZ];
   int notMatched = 1;
   int line = 1;
   while (fgets(buffer,BUFSIZ,file)) {
      if (pattern.match(buffer) >= 0)
         if (fileName)
            printf("%s[%d]: %s", fileName, line, buffer);
         else
            printf("[%d]: %s", line, buffer);
      line++;
   }
   return notMatched;
}

int main(int argc, char * argv[])
{
   if (argc == 1) {
      fprintf(stderr,"usage: %s pattern [files ...]\n",argv[0]);
      return 0;
   }
   KR pattern = argv[1];
   int failure = 0;
   if (argc == 2) {
      failure += grep("",stdin,pattern);
   } else {
      for (int i = 2; i < argc; i++) {
         FILE * file = fopen(argv[i],"r");
         if (file == NULL) { perror(argv[i]); exit(1); }
         failure += grep(argv[i],file,pattern);
         fclose(file);
      }
   }
   return failure;
}
