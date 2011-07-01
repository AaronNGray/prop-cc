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
// Class |String|
//
//    Class |String| behaves very much like C's `char *' and can be
// used as such in most situations.   It handles its own storage management.
// For compatibility with C style strings, class String keeps an extra
// nul character at the end.  However, nul characters *are* allowed in
// class String.
/////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <AD/generic/generic.h>   // Generic definitions

////////////////////////////////////////////////////////////////////////////
// The GNU C++ class library already has classes String and SubString.
// Xlib already has typedef String.
////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) || defined(X11)
#   define String     String_
#   define SubString  SubString_
#   define StringImpl StringImpl_
#endif

////////////////////////////////////////////////////////////////////////////
// Forward declarations.
////////////////////////////////////////////////////////////////////////////

class String;
class SubString;
class StringImpl;
class RegExp;
class std::ostream;
class std::istream;

////////////////////////////////////////////////////////////////////////////
//  Class StringImpl, the actual implementation of a string.
//  We use a simple reference counted, copy on write implementation.
////////////////////////////////////////////////////////////////////////////

class StringImpl
{
  friend class String;
  friend class SubString;
  unsigned long ref;        // reference count
  size_t        len;        // logical length
  size_t        capacity;   // actual capacity
  char          string[1];  // actual data
  void * operator new (size_t, size_t, size_t);
  void   operator delete (void *);
  inline void dec_ref()
  {
    if (--ref == 0)
      delete this;
  }
  inline void inc_ref()
  {
    ++ref;
  }
  static StringImpl * empty_string;
  static StringImpl * make_empty_string();
};

////////////////////////////////////////////////////////////////////////////
//  Class SubString
////////////////////////////////////////////////////////////////////////////

class SubString
{
  friend class String;
  StringImpl * impl;   // the actual string implementation
  size_t       start;  // starting index
  size_t       len;    // logical length

  SubString(StringImpl *, size_t, size_t);

public:
  inline ~SubString()
  {
    if (--impl->ref == 0)
      delete impl;
  }

  ///////////////////////////////////////////////////////////////////////
  // Conversions
  ///////////////////////////////////////////////////////////////////////
  operator String () const;

  ///////////////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////////////
  inline size_t length()   const
  {
    return len;
  }
  inline size_t size()     const
  {
    return len;
  }
  inline size_t capacity() const
  {
    return impl->capacity;
  }
  inline Bool   is_empty() const
  {
    return len == 0;
  }
  inline Bool   is_full()  const
  {
    return false;
  }
  inline char   operator [] (int i) const
  {
    return impl->string[start+i];
  }
  inline char&  operator [] (int i)
  {
    return impl->string[start+i];
  }
};

////////////////////////////////////////////////////////////////////////////
//  Class String
////////////////////////////////////////////////////////////////////////////

class String
{
  StringImpl * impl; // the actual string implementation
  inline String(StringImpl * s) : impl(s)
  {}
  void copy_on_write(size_t extra);

  ///////////////////////////////////////////////////////////////////////
  // Constructors and destructor
  ///////////////////////////////////////////////////////////////////////

public:
  String();                           // Make empty String
  String(size_t initial_capacity);    // Make an uninitialized String
  String(char c, size_t times = 1);   // Make String initialized with c's
  String(const char * s, int l = -1); // e.g. String = "abcde";
  inline  String(const String& s)     // e.g. String s1 = s2;
      :
      impl(s.impl)
  {
    impl->inc_ref();
  }
  inline ~String()
  {
    impl->dec_ref();
  }

  ///////////////////////////////////////////////////////////////////////
  // Conversion
  ///////////////////////////////////////////////////////////////////////
  inline operator const char * () const
  {
    return impl->string;
  }
  inline const char * str() const
  {
    return impl->string;
  }

  ///////////////////////////////////////////////////////////////////////
  // Assignment
  ///////////////////////////////////////////////////////////////////////
  inline String& operator = (const String& s)
  {
    if (this != &s)
    {
      s.impl->inc_ref();
      dec_ref();
      impl = s.impl;
    }
    return *this;
  }
  String& operator = (const char *);

  ///////////////////////////////////////////////////////////////////////
  // Splice a new (sub)string into location:
  //   e.g.  String S = "The quick brown fox";
  //         S.splice(4,5,"slow");
  //
  //    S now becomes "The slow brown fox";
  ///////////////////////////////////////////////////////////////////////
  String& splice(int location, int len, const char *, int size = -1);
  String& splice(int location, int len, char c, int size = 1);
  String& splice(int location, int len, const String& s);

  ///////////////////////////////////////////////////////////////////////
  // Selectors
  ///////////////////////////////////////////////////////////////////////
  inline size_t length()   const
  {
    return impl->len;
  }
  inline size_t size()     const
  {
    return impl->len;
  }
  inline size_t capacity() const
  {
    return impl->capacity;
  }
  inline Bool   is_empty() const
  {
    return impl->len == 0;
  }
  inline Bool   is_full()  const
  {
    return false;
  }
  inline char   operator [] (int i) const
  {
    return impl->string[i];
  }
  inline char&  operator [] (int i)
  {
    return impl->string[i];
  }

  ///////////////////////////////////////////////////////////////////////
  // Substring extraction
  ///////////////////////////////////////////////////////////////////////
  SubString at (int left, int length) const;
  SubString left (int length) const;
  SubString right (int length) const;

  ///////////////////////////////////////////////////////////////////////
  // Concatenation
  ///////////////////////////////////////////////////////////////////////
  friend String operator + (const String&, const String&);
  friend String operator + (const String&, const char *);
  friend String operator + (const char *,  const String&);

  ///////////////////////////////////////////////////////////////////////
  // Multiplication
  ///////////////////////////////////////////////////////////////////////
  String operator * (int times);

  ///////////////////////////////////////////////////////////////////////
  // Append to end
  ///////////////////////////////////////////////////////////////////////
  String& operator += (const String&);
  String& operator += (const char *);
  String& operator += (char);

  ///////////////////////////////////////////////////////////////////////
  // Comparisons
  ///////////////////////////////////////////////////////////////////////
  inline friend Bool operator == (const String& a, const String& b)
  {
    return a.compare(b) == 0;
  }
  inline friend Bool operator == (const String& a, const char * b)
  {
    return a.compare(b) == 0;
  }
  inline friend Bool operator == (const char * a, const String& b)
  {
    return b.compare(a) == 0;
  }
  inline friend Bool operator != (const String& a, const String& b)
  {
    return a.compare(b) != 0;
  }
  inline friend Bool operator != (const String& a, const char * b)
  {
    return a.compare(b) != 0;
  }
  inline friend Bool operator != (const char * a, const String& b)
  {
    return b.compare(a) != 0;
  }
  inline friend Bool operator > (const String& a, const String& b)
  {
    return a.compare(b) > 0;
  }
  inline friend Bool operator > (const String& a, const char * b)
  {
    return a.compare(b) > 0;
  }
  inline friend Bool operator > (const char * a, const String& b)
  {
    return b.compare(a) < 0;
  }
  inline friend Bool operator < (const String& a, const String& b)
  {
    return a.compare(b) < 0;
  }
  inline friend Bool operator < (const String& a, const char * b)
  {
    return a.compare(b) < 0;
  }
  inline friend Bool operator < (const char * a, const String& b)
  {
    return b.compare(a) > 0;
  }
  inline friend Bool operator >= (const String& a, const String& b)
  {
    return a.compare(b) >= 0;
  }
  inline friend Bool operator >= (const String& a, const char * b)
  {
    return a.compare(b) >= 0;
  }
  inline friend Bool operator >= (const char * a, const String& b)
  {
    return b.compare(a) <= 0;
  }
  inline friend Bool operator <= (const String& a, const String& b)
  {
    return a.compare(b) <= 0;
  }
  inline friend Bool operator <= (const String& a, const char * b)
  {
    return a.compare(b) <= 0;
  }
  inline friend Bool operator <= (const char * a, const String& b)
  {
    return b.compare(a) >= 0;
  }

  ///////////////////////////////////////////////////////////////////////
  // More Comparisons
  ///////////////////////////////////////////////////////////////////////
  int compare (const String&) const;
  int compare (const char *, int len = -1) const;
  int case_insensitive_compare (const String&) const;
  int case_insensitive_compare (const char *, int len = -1) const;
  int collate (const String&) const;
  int collate (const char *, int len = -1) const;

  ///////////////////////////////////////////////////////////////////////
  // In place operations
  ///////////////////////////////////////////////////////////////////////
  String& toupper();        // make all upper case
  String& tolower();        // make all lower case
  String& trunc(int len);   // truncate the length to `len'

  ///////////////////////////////////////////////////////////////////////
  // Searching: returns a non-negative index if found
  ///////////////////////////////////////////////////////////////////////
  int contains (RegExp&) const;
  int contains (char) const;
  int contains (const char *, int len = -1) const;
  int contains (const String&) const;

  ///////////////////////////////////////////////////////////////////////
  //  Input and Output
  ///////////////////////////////////////////////////////////////////////
  friend std::ostream& operator << (std::ostream& out, const String& s);
  friend std::istream& operator >> (std::istream&, String&);
};

#endif
