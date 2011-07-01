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

#ifndef variable_sized_string_h
#define variable_sized_string_h

/////////////////////////////////////////////////////////////////////////////
// Class |String| and |SubString|:
//
//    Class |String| behaves very much like C's `char *' and can be
// used as such in most situations.   It handles its own storage management.
// For compatibility with C style strings, class String keeps an extra
// nul character at the end.  However, nul characters *are* allowed in
// class String.
/////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>
#include <AD/generic/generic.h>   // Generic definitions
#include <AD/strings/regexp.h>    // Regular expression search


////////////////////////////////////////////////////////////////////////////
// The GNU C++ class library already has classes String and SubString.
// Xlib already has typedef String.
////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) || defined(X11)
#   define String String_
#   define SubString SubString_
#endif

////////////////////////////////////////////////////////////////////////////
// Forward declarations.
////////////////////////////////////////////////////////////////////////////

class String;
class SubString;

////////////////////////////////////////////////////////////////////////////
// Class |SubString| is a first class object representing substrings.
////////////////////////////////////////////////////////////////////////////

class SubString
{
  friend class String;

  String& S;        // reference to the base string
  int start, len;   // the starting point and the length of the substring

  SubString(String& s, int left, int size)  // make a new substring
      :
      S(s), start(left), len(size)
  {}

  const char * get_string() const;

  ///////////////////////////////////////////////////////////////////
  // Type conversions
  ////////////////////////////////////////////////////////////////////

public:
  operator String () const;

  ////////////////////////////////////////////////////////////////////
  // Assignment, will overwrite original string.
  ////////////////////////////////////////////////////////////////////
  SubString& operator = (char);
  SubString& operator = (const char *);
  SubString& operator = (const String&);
  SubString& operator = (const SubString&);

  ////////////////////////////////////////////////////////////////////
  // Selectors
  ////////////////////////////////////////////////////////////////////
  int  length()  const
  {
    return len;
  }
  Bool isEmpty() const
  {
    return len == 0;
  }
  char operator [] (int i) const;
  char& operator [] (int i);

  ////////////////////////////////////////////////////////////////////
  // Multiplication
  ////////////////////////////////////////////////////////////////////
  friend String operator * (const SubString&, int n);
  friend String operator * (int n, const SubString& s);

  ////////////////////////////////////////////////////////////////////
  // Searching: returns a non-negative index if found
  ////////////////////////////////////////////////////////////////////
  int contains (RegExp&) const;
  int contains (char) const;
  int contains (const char *, int len = -1) const;
  int contains (const String&) const;
  int contains (const SubString&) const;

  Bool has (RegExp&) const;
  Bool has (char) const;
  Bool has (const char *, int len = -1) const;
  Bool has (const String&) const;
  Bool has (const SubString&) const;
};

////////////////////////////////////////////////////////////////////////////
//  Class String
////////////////////////////////////////////////////////////////////////////

class String
{
  friend class SubString;

  char * string;       // the storage for the string
  long len;            // its logical length
  long cap;            // its actual capacity


  void out_of_bounds(int i) const;   // error handler
  void check(int i) const
  {
    if (i < 0 || i >= len)
      out_of_bounds(i);
  }

  void grow(long len);  // expansion, for internal use only.

public:
  class SubScript
  {}
  ;  // Exception class

  ///////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  ///////////////////////////////////////////////////////////////////////
  String() : string(0), len(0), cap(0)
  {}  // Make empty String
  String(int initial_capacity);            // Make an uninitialized String
  String(char c, int times = 1);           // Make String initialized with c's
  String(const char * s);                  // e.g. String = "abcde";
  String(const char * s, int l);           // Make String and initialize
  String(const String& s);                 // e.g. String s1 = s2;
  ~String()
  {
    delete [] string;
  }

  ///////////////////////////////////////////////////////////////////////
  // Conversion
  ///////////////////////////////////////////////////////////////////////
  operator const char * () const
  {
    return string;
  }

  ///////////////////////////////////////////////////////////////////////
  // Assigment
  ///////////////////////////////////////////////////////////////////////
  String& operator = (const String&);
  String& operator = (const char *);
  String& operator = (const SubString&);

  ///////////////////////////////////////////////////////////////////////
  // Splice a new (sub)string into location:
  //   e.g.  String S = "The quick brown fox";
  //         S.splice(4,5,"slow");
  //
  //    S now becomes "The slow brown fox";
  ///////////////////////////////////////////////////////////////////////
  String& splice(int location, int len, const char *, int size = -1);
  String& splice(int location, int len, char c);
  String& splice(int location, int len, const String& s);
  String& splice(int location, int len, const SubString& s);

  ///////////////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////////////
  int   length()   const
  {
    return len;
  }
  int   capacity() const
  {
    return cap;
  }
  Bool  isEmpty()  const
  {
    return len == 0;
  }
  Bool  isFull()   const
  {
    return false;
  }
  char  operator [] (int i) const
  {
    return string[i];
  }
  char& operator [] (int i)
  {
    return string[i];
  }
  char& operator () (int i) const
  {
    check(i);
    return string[i];
  }

  ///////////////////////////////////////////////////////////////////////
  // Substring extraction
  ///////////////////////////////////////////////////////////////////////
  SubString operator () (int left, int right)
  {
    return (left < 0 || left >= len || right < left || right >= len)
           ? SubString(*this,left,0) : SubString(*this,left,right - left + 1);
  }

  SubString at (int left, int length)
  {
    return (left < 0 || left >= len || left + length >= len || length <= 0)
           ? SubString(*this,left,0) : SubString(*this,left,length);
  }

  SubString left (int length)
  {
    return SubString(*this,0,length > len ? len : length);
  }

  SubString right (int length)
  {
    return length > len ? SubString(*this, 0, len) :
           SubString(*this, len - length, length);
  }

  ///////////////////////////////////////////////////////////////////////
  // Concatenation
  ///////////////////////////////////////////////////////////////////////
  friend String operator + (const String&, const String&);
  friend String operator + (const String&, const char *);
  friend String operator + (const String&, char);
  friend String operator + (const char *, const String&);
  friend String operator + (char, const String&);

  ///////////////////////////////////////////////////////////////////////
  // Multiplication
  ///////////////////////////////////////////////////////////////////////
  friend String operator * (const String&, int n);
  friend String operator * (int n, const String& s);

  ///////////////////////////////////////////////////////////////////////
  // Append to end
  ///////////////////////////////////////////////////////////////////////
  String& operator += (const String&);
  String& operator += (const char *);
  String& operator += (char);

  ///////////////////////////////////////////////////////////////////////
  // Comparisons
  ///////////////////////////////////////////////////////////////////////
  friend Bool operator == (const String& a, const String& b)
  {
    return a.compare(b) == 0;
  }
  friend Bool operator == (const String& a, const char * b)
  {
    return a.compare(b) == 0;
  }
  friend Bool operator == (const char * a, const String& b)
  {
    return b.compare(a) == 0;
  }
  friend Bool operator != (const String& a, const String& b)
  {
    return a.compare(b) != 0;
  }
  friend Bool operator != (const String& a, const char * b)
  {
    return a.compare(b) != 0;
  }
  friend Bool operator != (const char * a, const String& b)
  {
    return b.compare(a) != 0;
  }
  friend Bool operator > (const String& a, const String& b)
  {
    return a.compare(b) > 0;
  }
  friend Bool operator > (const String& a, const char * b)
  {
    return a.compare(b) > 0;
  }
  friend Bool operator > (const char * a, const String& b)
  {
    return b.compare(a) < 0;
  }
  friend Bool operator < (const String& a, const String& b)
  {
    return a.compare(b) < 0;
  }
  friend Bool operator < (const String& a, const char * b)
  {
    return a.compare(b) < 0;
  }
  friend Bool operator < (const char * a, const String& b)
  {
    return b.compare(a) > 0;
  }
  friend Bool operator >= (const String& a, const String& b)
  {
    return a.compare(b) >= 0;
  }
  friend Bool operator >= (const String& a, const char * b)
  {
    return a.compare(b) >= 0;
  }
  friend Bool operator >= (const char * a, const String& b)
  {
    return b.compare(a) <= 0;
  }
  friend Bool operator <= (const String& a, const String& b)
  {
    return a.compare(b) <= 0;
  }
  friend Bool operator <= (const String& a, const char * b)
  {
    return a.compare(b) <= 0;
  }
  friend Bool operator <= (const char * a, const String& b)
  {
    return b.compare(a) >= 0;
  }

  ///////////////////////////////////////////////////////////////////////
  // More Comparisons
  ///////////////////////////////////////////////////////////////////////
  int compare (const String&) const;
  int compare (const SubString&) const;
  int compare (const char *, int len = -1) const;
  int case_insensitive_compare (const String&) const;
  int case_insensitive_compare (const SubString&) const;
  int case_insensitive_compare (const char *, int len = -1) const;
  int collate (const String&) const;
  int collate (const SubString&) const;
  int collate (const char *, int len = -1) const;

  ///////////////////////////////////////////////////////////////////////
  // In place operations
  ///////////////////////////////////////////////////////////////////////
  String& to_upper();       // make all upper case
  String& to_lower();       // make all lower case
  String& trunc(int len);   // truncate the length to `len'

  ///////////////////////////////////////////////////////////////////////
  // Searching: returns a non-negative index if found
  ///////////////////////////////////////////////////////////////////////
  int contains (RegExp&) const;
  int contains (char) const;
  int contains (const char *, int len = -1) const;
  int contains (const String&) const;
  int contains (const SubString&) const;

  Bool has (RegExp&) const;
  Bool has (char) const;
  Bool has (const char *, int len = -1) const;
  Bool has (const String&) const;
  Bool has (const SubString&) const;

  ///////////////////////////////////////////////////////////////////////
  //  Input and Output
  ///////////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream& out, const String& s)
  {
    return out << s.string;
  }
  friend std::istream& operator >> (std::istream&, String&);

  ///////////////////////////////////////////////////////////////////////
  //  Iterators
  ///////////////////////////////////////////////////////////////////////
  char * first()        const
  {
    return len > 0 ? string : 0;
  }
  char * last()         const
  {
    return len > 0 ? string + len - 1 : 0;
  }
  char * next(char * p) const
  {
    return p >= string + len ? 0 : p+1;
  }
  char * prev(char * p) const
  {
    return p <= string ? 0 : p-1;
  }
};

////////////////////////////////////////////////////////////////////////////
//  Some inlined methods
////////////////////////////////////////////////////////////////////////////
inline const char * SubString::get_string() const
{
  return (const char*)S + start;
}
inline SubString::operator String () const
{
  return String(get_string(),len);
}
inline char  SubString::operator [] (int i) const
{
  return S[i + start];
}
inline char& SubString::operator [] (int i)
{
  return S[i + start];
}
inline String operator * (int n, const String& s)
{
  return s * n;
}
inline String operator * (int n, const SubString& s)
{
  return s * n;
}

inline String& String::splice(int location, int l, char c)
{
  return splice(location,l,&c,1);
}
inline String& String::splice(int location, int l, const String& s)
{
  return splice(location,l,s.string,s.len);
}
inline String& String::splice(int location, int l, const SubString& s)
{
  return splice(location,l,s.S.string + s.start, s.len);
}

inline SubString& SubString::operator = (char c)
{
  S.splice(start,len,c);
  return *this;
}
inline SubString& SubString::operator = (const char * s)
{
  S.splice(start,len,s);
  return *this;
}
inline SubString& SubString::operator = (const String& s)
{
  S.splice(start,len,s);
  return *this;
}
inline SubString& SubString::operator = (const SubString& s)
{
  S.splice(start,len,s);
  return *this;
}

inline Bool SubString::has (RegExp& re) const
{
  return contains(re) >= 0;
}
inline Bool SubString::has (char c) const
{
  return contains(c) >= 0;
}
inline Bool SubString::has (const char * s, int l) const
{
  return contains(s,l) >= 0;
}
inline Bool SubString::has (const String& s) const
{
  return contains(s) >= 0;
}
inline Bool SubString::has (const SubString& s) const
{
  return contains(s) >= 0;
}
inline Bool String::has (RegExp& re) const
{
  return contains(re) >= 0;
}
inline Bool String::has (char c) const
{
  return contains(c) >= 0;
}
inline Bool String::has (const char * s, int l) const
{
  return contains(s,l) >= 0;
}
inline Bool String::has (const String& s) const
{
  return contains(s) >= 0;
}
inline Bool String::has (const SubString& s) const
{
  return contains(s) >= 0;
}

////////////////////////////////////////////////////////////////////////////
// Iterator macros:
//
// e.g.:
//
//    String s;
//    char c;
//    foreach_char(c,s)
//       std::cout.put(c);
//
////////////////////////////////////////////////////////////////////////////
#define foreach_char(c,s) \
   for(char * _p_##__LINE__ = (s).first(); _p_##__LINE__ && (c = *_p_##__LINE__, 1); _p_##__LINE__ = (s).next(_p_##__LINE__))
#define foreach_char_rev(c,s) \
   for(char * _p_##__LINE__ = (s).last(); _p_##__LINE__ && (c = *_p_##__LINE__, 1); _p_##__LINE__ = (s).prev(_p_##__LINE__))

#endif
