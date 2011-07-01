#include <sys/time.h>       
#include <sys/resource.h>

int main()
{
   struct rusage usage_at_start;
   getrusage(RUSAGE_SELF, &usage_at_start);
   struct rusage usage_at_end;
   getrusage(RUSAGE_SELF, &usage_at_end);
   timeval x = usage_at_start.ru_utime;
   timeval y = usage_at_start.ru_stime;
   return 0;
}
