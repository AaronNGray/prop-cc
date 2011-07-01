#include <sys/times.h>

int main()
{
   struct tms usage_at_start;
   times(&usage_at_start);
   struct tms usage_at_end;
   times(&usage_at_end);
   clock_t x = usage_at_end.tms_utime - usage_at_start.tms_utime;
   clock_t y = usage_at_end.tms_stime - usage_at_start.tms_stime;
   return 0;
}
