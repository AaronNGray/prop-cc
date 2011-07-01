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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <AD/strings/str.h>
#include <AD/strings/regexp.h>


///////////////////////////////////////////////////////////////////////////////
// Allocator for the string objects
///////////////////////////////////////////////////////////////////////////////

void * StringImpl::operator new(size_t, const char * s, size_t len, size_t cap)
{}

///////////////////////////////////////////////////////////////////////////////
// Deallocator for the string objects
///////////////////////////////////////////////////////////////////////////////

void StringImpl::operator delete (void * s)
{}

///////////////////////////////////////////////////////////////////////////////
// Constructors and destructor
///////////////////////////////////////////////////////////////////////////////

String:: String()
    : impl(empty_string ? empty_string : make_empty_string())
{}

String:: String(size_t initial_capacity)
    : impl(new StringImpl(initial_capacity, 0))
{}

String:: String(char c, size_t times)
    : impl(new StringImpl(times+1,times))
{
  memset(impl->string,c,times);
  impl->string[times] = '\0';
}

String:: String(const char * s, int len)
    : impl(new StringImpl(len+1,len))
{
  memcpy(impl->string,s,len);
  impl->string[len] = '\0';
}

///////////////////////////////////////////////////////////////////////////////
//  Assignment
///////////////////////////////////////////////////////////////////////////////

String& String::operator = (const char * s)
{
  impl->dec_ref();
  int len = strlen(s);
  impl = new StringImpl(len+1,len);
  strcpy(impl->string,s);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//  Splicing
///////////////////////////////////////////////////////////////////////////////

String& String::splice( int location, int len, const char * s, int size)
{}

String& String::splice( int location, int len, char c, int size)
{}

String& String::splice( int location, int len, const String& s)
{}

///////////////////////////////////////////////////////////////////////////////
//  Substring extraction
///////////////////////////////////////////////////////////////////////////////

String String::at( int left, int length) const
  {}

String String::left( int length) const
  {}

String String::right( int length) const
  {}

///////////////////////////////////////////////////////////////////////////////
//  Concatenation
///////////////////////////////////////////////////////////////////////////////

String operator + (const String& a, const String& b)
{
  size_t new_len = a.impl->len + b.impl->len;
  StringImpl s = new StringImpl(new_len+1,new_len);
  memcpy(s->string,a.impl->string,a.impl->len);
  memcpy(s->string + a.impl->len, b.impl->string, b.impl->len);
  s->string[new_len] = '\0';
  return s;
}

String operator + (const String& a, const char * b)
{
  size_t b_len   = strlen(b);
  size_t new_len = a.impl->len + len;
  StringImpl s = new StringImpl(new_len+1,new_len);
  memcpy(s->string,a.impl->string,a.impl->len);
  memcpy(s->string + a.impl->len, b, b_len);
  s->string[new_len] = '\0';
  return s;
}

String operator + (const char * a, const String& b)
{
  size_t a_len   = strlen(a);
  size_t new_len = a_len + b.impl->len;
  StringImpl s = new StringImpl(new_len+1,new_len);
  memcpy(s->string,a,a_len);
  memcpy(s->string + a_len, b.impl->string, b.impl->len);
  s->string[new_len] = '\0';
  return s;
}

///////////////////////////////////////////////////////////////////////////////
//  Multiplication
///////////////////////////////////////////////////////////////////////////////

String String::operator * (int times) const
{
  size_t my_length  = length();
  size_t new_length = my_length * times;
  StringImpl * s = new StringImpl(new_length+1,new_length);
  int i;
  char * p, * q;
  const char * r;
  for (i = times - 1, p = impl->string; i >= 0; i--)
  {
    for (q = p + my_length, r = impl->string; p < q; p++, r++)
      *p = *r;
  }
  *p = '\0';
  return s;
}

///////////////////////////////////////////////////////////////////////////////
//  Append to end
///////////////////////////////////////////////////////////////////////////////

String& String::operator += (const String& s)
{
  copy_on_write (s.impl->len);
  memcpy(impl->string + impl->len, s->impl->string, s.impl->len);
  impl->len += s.impl->len;
  impl->string[impl->len] = '\0';
  return *this;
}

String& String::operator += (char c)
{
  copy_on_write (s.impl->len);
  impl->string[impl->len++] = c;
  impl->string[impl->len] = '\0';
  return *this;
}

String& String::operator += (const char * s)
{
  size_t len = strlen(s);
  copy_on_write (len);
  memcpy(impl->string + len, s->impl->string, len);
  impl->len += len;
  impl->string[impl->len] = '\0';
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//  Comparisons
///////////////////////////////////////////////////////////////////////////////

int String::compare (const String& s) const
  {}

int String::compare (const char * s, int len) const
  {}

///////////////////////////////////////////////////////////////////////////////
//  I/O
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator << (std::ostream& f, const String& s)
{
  f.write(s.impl->string, s.impl->len);
  return f;
}

std::istream& operator >> (std::ostream& f, String& s)
{}
