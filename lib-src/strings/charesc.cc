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

#include <ctype.h>
#include <AD/strings/charesc.h>

char * quote_string (char * buf, const char * s)
{
  while (*s)
  {
    char c;
    s = parse_char(s,c);
    buf = print_char(buf,c);
  }
  *buf = '\0';
  return buf;
}

const char * parse_char(const char * s, char& c)
{
  if (*s == '\\')
  {
    s++;
    switch (*s)
    {
    case '0':
    case '1':
      {
        char ch;
        int count;
        for (ch = 0, count = 0; *s >= '0' && *s <= '7' && count < 3; s++, count++)
          ch = ch * 8 + *s - '0';
        c = ch;
        return s;
      }
    case 'n':
      c = '\n';
      break;
    case 't':
      c = '\t';
      break;
    case 'x':
    case 'X':
      {
        int digit1;
        int digit2;
        s++;
        if (isdigit(*s))
          digit1 = *s - '0';
        else if (*s >= 'a' && *s <= 'f')
          digit1 = *s - 'a' + 10;
        else if (*s >= 'A' && *s <= 'F')
          digit1 = *s - 'A' + 10;
        else
          digit1 = 0;
        s++;
        if (isdigit(*s))
          digit2 = *s - '0';
        else if (*s >= 'a' && *s <= 'f')
          digit2 = *s - 'a' + 10;
        else if (*s >= 'A' && *s <= 'F')
          digit2 = *s - 'A' + 10;
        else
          digit2 = 0;
        c = digit1 * 16 + digit2;
        return s+1;
      }
      break;
    default:
      c = *s;
    }
  }
  else
    c = *s;
  return s + 1;
}

char * print_char(char * s, char c)
{
  if (c == '\n')
  {
    *s++ = '\\';
    *s++ = 'n';
    *s = '\0';
    return s;
  }
  else if (c == '\t')
  {
    *s++ = '\\';
    *s++ = 't';
    *s = '\0';
    return s;
  }
  else if (c == '\'' || c == '\"' || c == '\\')
  {
    *s++ = '\\';
    *s++ = c;
    *s= '\0';
    return s;
  }
  else if (isprint(c))
  {
    *s++ = c;
    *s = '\0';
    return s;
  }
  else
  {
    unsigned char ch = c;
    s[0] = '\\';
    s[1] = ch / 64 + '0';
    s[2] = (ch / 8) % 8 + '0';
    s[3] = ch % 8 + '0';
    s[4] = '\0';
    return s + 4;
  }
}

const char * print_char(char c)
{
  static char buf[10];
  print_char(buf,c);
  return buf;
}
