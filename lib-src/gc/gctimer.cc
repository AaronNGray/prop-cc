//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung (leunga@cs.nyu.edu)
// 1994-1995
//
// Kudos to James Litsios <litsios@iis.ee.ethz.ch> for his tireless
// testing efforts and useful feedbacks.  Certain part of Prop
// now incorporates some of James' ideas on reference counting and
// hash consing.
//////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <iomanip.h>
#include <AD/gc/gcconfig.h>
#include <AD/gc/gctimer.h>

// Use getrusage instead of times when the former is available
// since getrusage has higher resolution

#ifdef PROP_HAS_GETRUSAGE
#   include <sys/time.h>
#   include <sys/resource.h>
#else
#   ifdef PROP_HAS_TIMES
#      include <sys/times.h>
#   endif
#endif

GCTimer::GCTimer() : sec(0), usec(0)
{}

GCTimer::GCTimer( long s, long us) : sec(s), usec(us)
{}

void GCTimer::clear()
{
  sec = 0;
  usec = 0;
}

GCTimer GCTimer::operator + (const GCTimer& b)
{
  long the_usec = (usec + b.usec) % 1000000;
  long the_sec  = sec + b.sec + (usec + usec) / 1000000;
  return GCTimer(the_sec,the_usec);
}

GCTimer GCTimer::operator - (const GCTimer& b)
{
  long the_usec = (1000000 + usec - b.usec) % 1000000;
  long the_sec  = sec - b.sec - (usec < usec);
  return GCTimer(the_sec,the_usec);
}

void GCTimer::operator += (const GCTimer& b)
{
  *this = *this + b;
}

std::ostream& operator << (std::ostream& f, const GCTimer& t)
{
  int ms = t.usec / 1000;
  f << t.sec << '.'
  << (char)(ms/100 + '0')
  << (char)((ms/10) % 10 + '0')
  << (char)(ms % 10 + '0')
  << 's';
  return f;
}

void GCTimer::get_system_time()
{
#ifdef PROP_HAS_GETRUSAGE
  struct rusage usage;
  getrusage(RUSAGE_SELF,&usage);
  usec =  usage.ru_stime.tv_usec;
  sec  =  usage.ru_stime.tv_sec;
#else
#   ifdef PROP_HAS_TIMES

  struct tms timing;
  times(&timing);
  usec = (timing.tms_stime % 60) * 1000000 / 60;
  sec  = timing.tms_stime / 60;
#   endif
#endif
}

void GCTimer::get_user_time()
{
#ifdef PROP_HAS_GETRUSAGE
  struct rusage usage;
  getrusage(RUSAGE_SELF,&usage);
  usec =  usage.ru_utime.tv_usec;
  sec  =  usage.ru_utime.tv_sec;
#else
#   ifdef PROP_HAS_TIMES

  struct tms timing;
  times(&timing);
  usec = (timing.tms_utime % 60) * 1000000 / 60;
  sec  = timing.tms_utime / 60;
#   endif
#endif
}
